#include "StdAfx.h"
#include "TraceLog.h"
#include "Configure.h"

#include "winbase.h"
#include <direct.h>
#include <io.h>


INT  CreateDirectoryIfNeed(CHAR* szFileName)
{
	CHAR szTemp[MAX_PATH] = {0};
	CHAR szName[MAX_PATH] = {0};

	_snprintf(szName, MAX_PATH, "%s", szFileName);
	INT iStrLen = strlen(szFileName);
	INT i;

	for(i=0; i<iStrLen; i++)
	{
		if(szName[i] == '\\' || szName[i] == '\r' || szName[i] == '\0')
		{
			strncpy(szTemp, szName, i);
			szTemp[i] = 0;
			if(0 != access(szTemp, 0))
			{
				CreateDirectory(szTemp, NULL);
				SetFileAttributes(szTemp, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_DIRECTORY);
			}
		}
	}

	return 0;
}

CTraceLog::CTraceLog(void)
{
	m_pLogQueue = NULL;
	m_bEnableRarLog = FALSE;
	m_wLogFileSaveDay = 0;
	m_hWriteThread = 0;
	m_hDelThread = 0;
	m_bStopFlag = FALSE;
	m_bOpenFile = FALSE;
	memset(m_szLogPath, 0, sizeof(m_szLogPath));
	memset(m_szCurRunPath, 0, sizeof(m_szCurRunPath));
	memset(m_szCurLogName, 0, sizeof(m_szCurLogName));
	memset(m_szRarLogName, 0, sizeof(m_szRarLogName));

	m_pWriteLogMutex = CreateMutex(NULL, FALSE, NULL);
	m_hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
	GetCurrentDirectory(sizeof(m_szCurRunPath), (LPSTR)m_szCurRunPath);
}

CTraceLog::CTraceLog(LPCTSTR lpszFileName)
{

}

CTraceLog::~CTraceLog(void)
{
	if(m_hWriteThread)
		CloseHandle(m_hWriteThread);
	if(m_hDelThread)
		CloseHandle(m_hDelThread);

	CloseHandle(m_pWriteLogMutex);
	CloseHandle(m_hSemaphore);
}

BOOL CTraceLog::OpenLog(SYSTEMTIME *pxt)
{
	CHAR	FileName[MAX_PATH] = {0};

	if(CreateLogPath()==FALSE) return FALSE;

	//YYYYMMDD_hhmmss_uuu
	_snprintf(FileName, MAX_PATH, "%s\%04d%02d%02d_%02d%02d%02d.txt", m_szLogPath, 
		pxt->wYear, pxt->wMonth, pxt->wDay, pxt->wHour, pxt->wMinute, pxt->wSecond);
	m_fstream.open(FileName, ios::out|ios::app|ios::binary);
	if(!m_fstream.is_open()){
		printf("Create log file: %s fail.\n", FileName);
		return FALSE;
	}

	_snprintf(m_szCurLogName, MAX_PATH, FileName); 

	m_wCurDay = pxt->wDay;
	m_lLineCounts = 0;

	return TRUE;
}

DWORD  CTraceLog::WriteLogThreadEntry(LPVOID lpParam)
{
	CTraceLog *pThis = (CTraceLog*)lpParam;
	pThis->WriteLogThread();

	return 0;
}
/**
*写日志线程
*/
DWORD CTraceLog::WriteLogThread()
{
	INT  iRetVal = 0, iLogSize = 0, iLineOffset = 0;
	INT  nTMCnt =0;		//等待信号超时次数，当超时40次后，要触发写文件操作。

	/*每次取出满128K后写文件，但如果在指定时间内未达到128K，也需要写文件并重新计时*/
	CHAR* szBuf = new CHAR[MAN_WRITE_LOG_LEN];
	CHAR *pBuffer = szBuf;
	memset(szBuf, 0, MAN_WRITE_LOG_LEN);
	
	while(!m_bStopFlag)
	{
		if(WaitForSingleObject(m_hSemaphore, 10)==WAIT_TIMEOUT)
			nTMCnt++;
		if(!m_pLogQueue) continue;
		iRetVal = m_pLogQueue->GetMsg(pBuffer);
		if(iRetVal >0) 
		{
			iLogSize += iRetVal;
			iLineOffset++;
			pBuffer += iRetVal;
		}

		if( iLogSize<MAN_WRITE_LOG_LEN && nTMCnt< CHECK_WRITELOG_TIMEOUT )
			continue;

		if(iLogSize>0) 
		{
			WriteLog(szBuf, iLogSize, iLineOffset);
			nTMCnt = 0;
			iLogSize = 0;
			iLineOffset = 0;
			pBuffer = szBuf;
		}
	}

	delete [] szBuf;

	return 0;
}
/**
*删除日志线程
*/
DWORD CTraceLog::DelLogThreadEntry(LPVOID lpParam)
{
	if(lpParam == NULL) return NULL;

	CTraceLog* pThisObj = (CTraceLog*)lpParam;

	pThisObj->DelLogThread();

	return NULL;
}

INT CTraceLog::DelLogThread()
{
	LARGE_INTEGER litmp;
	LONGLONG	tInterval, tStart, tIntervalRar, tStartRar;
	double dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);
	dff = (double)litmp.QuadPart;

	QueryPerformanceCounter(&litmp);
	tStart = litmp.QuadPart;
	tStartRar = tStart;

	while(!m_bStopFlag){
		Sleep(500*1000);
		QueryPerformanceCounter(&litmp);
		tInterval = litmp.QuadPart;

		if (((tInterval-tStart)/dff > CHECK_AUTODEL_INTERVAL) && m_wLogFileSaveDay>0)
		{
			tStart = QueryPerformanceCounter(&litmp);
			AutoDelFile(m_wLogFileSaveDay);
		}

		QueryPerformanceCounter(&litmp);
		tIntervalRar = litmp.QuadPart;
		if((tIntervalRar-tStartRar)/dff > CHECK_AUTORAR_INTERVAL) {
			RarLogFile();
			QueryPerformanceCounter(&litmp);
			tStartRar = litmp.QuadPart;
		}
	}

	return 0;
}
/**
*日志信息格式化放入队列
*/
INT CTraceLog::LogTraceA(INT iLogType, const CHAR * MessageFormat, ...)
{
	va_list args;
	CHAR MessageA[MAX_LOGITEM_LEN] = {0};
	CHAR MessageB[MAX_LOGITEM_LEN] = {0};

	va_start(args, MessageFormat);
	vsprintf(MessageA, MessageFormat, args);

	SYSTEMTIME  _tm;
	 
	GetLocalTime(&_tm);	

	_snprintf(MessageB, MAX_LOGITEM_LEN, "[%02d:%02d:%02d.%03d]%s", 
		_tm.wHour, _tm.wMinute, _tm.wSecond, _tm.wMilliseconds, MessageA);

	MessageB[MAX_LOGITEM_LEN-2]=0;

	INT iStrLen = strlen(MessageB);
	Log2WriteQ(MessageB, iStrLen, iLogType);

	return 0;
}
/**
*写日志信息放入队列
*/
INT CTraceLog::Log2WriteQ(CHAR* MessageB, INT iStrLen, INT iLogType)
{

	if(m_pWriteLogMutex) WaitForSingleObject(m_pWriteLogMutex, INFINITE);
	CHAR szTemp[32] = {0};
	CHAR szLogStr[MAN_WRITE_LOG_LEN] = {0};
	CHAR szError[MAX_DATA_LEN] = {0};

	if(m_pLogQueue) {
		_snprintf(szLogStr, MAN_WRITE_LOG_LEN, "%s%s", szTemp, MessageB);
		iStrLen = iStrLen + strlen(szTemp);
		if(iStrLen>MAN_WRITE_LOG_LEN) {
			iStrLen = MAN_WRITE_LOG_LEN -1;
			szLogStr[MAN_WRITE_LOG_LEN-1] = 0;
		}
		//printf("Log2WriteQ >>> %s", szLogStr);
		if(m_pLogQueue->PutMsg(szLogStr, iStrLen, szError)<0) {
			
		} else ReleaseSemaphore(m_hSemaphore,1, NULL);
	}
	if(m_pWriteLogMutex) ReleaseMutex(m_pWriteLogMutex);

	return 0;
}
/**
*写txt文件日志
*/
INT CTraceLog::WriteLog(CHAR* Msg, INT iMsgLen, INT iLineNum)
{
	DWORD  dwWriteBytes = 0;
	SYSTEMTIME  _tm;

	GetLocalTime(&_tm);

	if(!m_bOpenFile)
	{
		m_bOpenFile=OpenLog(&_tm);
		if(!m_bOpenFile) 
		{
			//WEIL_TRACE("$E >>> open fail, %s m_bOpenFile=%d \r\n", m_szCurLogName, m_bOpenFile);
			return FAIL;
		}
	}

	if(m_lLineCounts >= MAX_LOGLINE_NUM || m_wCurDay != _tm.wDay) 
	{
		CloseLog();
		//切换文件了，记住日志路径，然后把当前日志压缩并删除
		sprintf(m_szRarLogName, m_szCurLogName);

		m_bOpenFile=OpenLog(&_tm);
		if(!m_bOpenFile)
		{
			return FALSE;
		}
	}	

	if(m_lLineCounts == 0 || m_wCurDay != _tm.wDay)
	{
		CHAR szTemp[MAX_PATH] = {0};
		_snprintf(szTemp, MAX_PATH, "RIBBIN SERVER    [PID:%08d]============ VER(%s): %d-%02d-%02d %02d:%02d:%02d:%03d ============ \r\n", 
			GetCurrentProcessId(), SERVER_VER, _tm.wYear, _tm.wMonth, _tm.wDay, 
			_tm.wHour, _tm.wMinute, _tm.wSecond, _tm.wMilliseconds);		
		dwWriteBytes = strlen(szTemp);
		m_fstream.seekp(0, ios::end);
		m_fstream.write(szTemp, strlen(szTemp));
		m_fstream.flush();
	}

	dwWriteBytes = iMsgLen;
	m_wCurDay = _tm.wDay;
	m_fstream.seekp(0, ios::end);
	m_fstream.write(Msg, dwWriteBytes);
	m_fstream.flush();

	m_lLineCounts = m_lLineCounts + iLineNum;

	return 0;
}
/**
*压缩日志
*/
VOID CTraceLog::RarLogFile()
{
	if(!m_bEnableRarLog) return;

	CHAR szRarFile[1024];
	CHAR szDelFile[1024];
	if(m_szRarLogName[0]!=0) 
	{
		sprintf(szRarFile, "makecab /d compressiontype=lzx /d compressionmemory=21 %s %s.cab", m_szRarLogName, m_szRarLogName);
		sprintf(szDelFile, "del -f %s", m_szRarLogName);
		memset(m_szRarLogName, 0, sizeof(m_szRarLogName));
		WinExec((LPCSTR)szRarFile, SW_HIDE);
		WinExec((LPCSTR)szDelFile, SW_HIDE);
	}
}
/**
*创建写日志目录
*/
BOOL CTraceLog::CreateLogPath()
{
	if(m_szLogPath[0]!=0) 
	{
		CreateDirectoryIfNeed(m_szLogPath);
		return TRUE;
	}

	_snprintf(m_szLogPath, sizeof(m_szLogPath), "%s", m_szCurRunPath);

	return TRUE;
}
INT CTraceLog::InitData()
{
	INT iRet = FAIL;
	

	strncpy(m_szLogPath, g_Cfg->GetKeyValue("LogPath"), MAX_PATH);
	m_wLogFileSaveDay = atoi(g_Cfg->GetKeyValue("LogFileSaveDay"));
	m_bEnableRarLog = atoi(g_Cfg->GetKeyValue("EnableRarLog"));
	iRet = Create(MAX_LOGITEM_NUM, MAX_LOGITEM_LEN*MAX_LOGITEM_NUM);
	
	if(SUCCES == iRet)
		Star();

	return iRet;
}
/**
*创建日志队列
*/
INT CTraceLog::Create(UINT ulMaxMsgNum, UINT ulMaxMsgMem, BOOL bAutoCreateMutex)
{	

	if(!m_pLogQueue) {
		m_pLogQueue = new CMessageQueue();
		if(!m_pLogQueue) 
			return FAIL;
	
		m_pLogQueue->m_bNoOutputErr = TRUE;
		m_pLogQueue->m_ifBlock = FALSE;

		UINT	ulNeedMemSize;
		ulNeedMemSize = m_pLogQueue->CalcIndexInfoSize(ulMaxMsgNum+1) + ulMaxMsgMem;

		m_pLogQMem = new UCHAR[ulNeedMemSize];
		memset(m_pLogQMem, 0, ulNeedMemSize);
		INT RetVal = m_pLogQueue->Create(m_pLogQMem, ulNeedMemSize, ulMaxMsgNum+1, bAutoCreateMutex);

		if(RetVal != 0)
		{
			delete m_pLogQueue;
			delete[] m_pLogQMem;
			return RetVal;
		}
	}

	return 0;
}
/**
*启动工作线程
*/
INT CTraceLog::Star()
{
	HANDLE hThread = 0;

	m_hWriteThread = CreateThread(NULL,0, WriteLogThreadEntry, this, 0, NULL);
	m_hDelThread = CreateThread(NULL,0, DelLogThreadEntry, this, 0, NULL);

	return SUCCES;
}
/**
*关闭日志文件
*/
BOOL CTraceLog::CloseLog( )
{
	if(m_fstream.is_open() && m_bOpenFile)
	{
		m_fstream.close();
		m_bOpenFile = FALSE; 
	}	
	m_bStopFlag = TRUE;


	return TRUE;
}
/**
*删除日志函数
*/
INT CTraceLog::AutoDelFile(int DayNum)
{
	if (DayNum != 0)
		return FAIL;

	char szFile[MAX_PATH] = {0};
	char szFind[MAX_PATH] = {0};
	WIN32_FIND_DATA FindFileData;

	strcpy(szFind, m_szLogPath);
	strcat(szFind, "*.*");
	HANDLE hFind = FindFirstFile((LPCSTR)szFind,&FindFileData);

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{

			strcpy(szFile, m_szLogPath);
			strcat(szFile, (const char*)FindFileData.cFileName);
		}


		if(!FindNextFile(hFind,&FindFileData)) break;
	}
	FindClose(hFind);

	
	return SUCCES;
}
