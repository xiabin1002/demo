#include "stdafx.h"
#include "IOCPServer.h"
#include <assert.h>
#include "Configure.h"


#define  MAX_MSG_NUM		(10240)
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

CIOCPServer::CIOCPServer(void)
{
	m_ThreadNums = 0;
	m_ListenSocket = INVALID_SOCKET;
	m_hCompletionPort = NULL;
	m_pMsgQueue = NULL;
	m_bStopFlag = FALSE;
	m_hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
	
}

CIOCPServer::~CIOCPServer(void)
{
	CloseHandle(m_hSemaphore);
	StopServer();
}
/**
初始化IOCP消息处理队列
*/
INT CIOCPServer::Initialize()
{
	INT iRet = FAIL;
	m_listenPort = atoi(g_Cfg->GetKeyValue("ListenPort"));

	if(!m_pMsgQueue) {
		m_pMsgQueue = new CMessageQueue();
		if(!m_pMsgQueue) 
			return FAIL;

		m_pMsgQueue->m_bNoOutputErr = TRUE;
		m_pMsgQueue->m_ifBlock = FALSE;

		UINT	ulNeedMemSize = m_pMsgQueue->CalcIndexInfoSize(MAX_MSG_NUM+1) + MAX_MSG_NUM*sizeof(COverLappedEx);

		UCHAR* m_pLogQMem = new UCHAR[ulNeedMemSize];
		memset(m_pLogQMem, 0, ulNeedMemSize);
		iRet = m_pMsgQueue->Create(m_pLogQMem, ulNeedMemSize, MAX_MSG_NUM+1, FALSE);

		if(iRet != 0)
		{
			delete m_pMsgQueue;
			delete[] m_pLogQMem;
			return iRet;
		}
	}

	iRet = StartServer();

	return iRet;
}

void CIOCPServer::SetLastErrorMsg(string strErrorMsg)
{
	m_strErrorMsg = strErrorMsg;
}

string CIOCPServer::GetLastErrorMsg()
{
	return m_strErrorMsg;
}

BOOL CIOCPServer::WinSockInit()
{
	WSADATA data = {0};
	if(WSAStartup(MAKEWORD(2, 2), &data))
		return FALSE;
	if ( LOBYTE(data.wVersion) !=2 || HIBYTE(data.wVersion) != 2 )
	{
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}
/**
功能：     给连接请求套接字创建完成端口并存放到list
tSocket:   给连接请求套接字
*/
CPerSocketData *CIOCPServer::AssignSockToCompletionPort(SOCKET tSocket)
{
	assert(tSocket != INVALID_SOCKET);
	CPerSocketData *pSockData = new CPerSocketData();
	pSockData->m_Socket = tSocket;
	m_ArrSocketData.push_back(pSockData);
	CreateIoCompletionPort((HANDLE)tSocket, m_hCompletionPort, (ULONG_PTR)pSockData, 0);
	return pSockData;
}

INT CIOCPServer::StartServer()
{
	sockaddr_in service;
	CPerSocketData *pSockData = NULL;

	if (!WinSockInit()) {
		SetLastErrorMsg("Socket 库初始化失败");
		return FAIL;
	}

	m_ListenSocket = WSASocket(AF_INET , SOCK_STREAM , IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if ( m_ListenSocket == INVALID_SOCKET ) {
		SetLastErrorMsg("新建Socket失败！");
		goto __Error_End;
	}

	//sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(m_listenPort);

	if ( bind(m_ListenSocket, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR ) {
		SetLastErrorMsg("绑定端口失败！");
		goto __Error_End;
	}

	if( listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR ) {
		SetLastErrorMsg("监听失败！");
		goto __Error_End;
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if ( m_hCompletionPort == NULL ) {
		SetLastErrorMsg("完成端口创建失败！");
		goto __Error_End;
	}

	pSockData = AssignSockToCompletionPort(m_ListenSocket);

	QueueUserWorkItem(ThreadPoolProcEntry, this, WT_EXECUTELONGFUNCTION);

	PostAccept(pSockData);
	return SUCCES;

__Error_End:
	if (m_ListenSocket != INVALID_SOCKET) {
		closesocket(m_ListenSocket);
	}

	if (m_hCompletionPort != NULL) {
		CloseHandle(m_hCompletionPort);
	}

	WSACleanup();
	return SUCCES;
}

void CIOCPServer::StopServer()
{
	m_bStopFlag = TRUE;

	CPerSocketData *pSocketData = NULL;	
	list<CPerSocketData*>::iterator itScoke;
	itScoke = m_ArrSocketData.begin();

	while (itScoke!=m_ArrSocketData.end())
	{
		pSocketData = *itScoke++;
		closesocket(pSocketData->m_Socket);
		delete pSocketData;
	}
	m_ArrSocketData.clear();

	while(m_ThreadNums > 0){
		PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, NULL);
		Sleep(100);
	}

	if (m_hCompletionPort != NULL) {
		CloseHandle(m_hCompletionPort);
	}

	WSACleanup();
}

BOOL CIOCPServer::PostAccept(CPerSocketData *pSockData)
{
	DWORD dwBytesRecv = 0;
	assert(pSockData != NULL);
	COverLappedEx *m_pOverLap = new COverLappedEx(IO_TYPE_ACCEPT);
	pSockData->m_AccSocket = WSASocket(AF_INET , SOCK_STREAM , IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	BOOL bRet = AcceptEx(pSockData->m_Socket, pSockData->m_AccSocket, m_pOverLap->m_szBuf, 0, sizeof(sockaddr_in)+16, 
							sizeof(sockaddr_in)+16, &dwBytesRecv, &m_pOverLap->m_OLap);
	if (!bRet)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CIOCPServer::PostRecv(CPerSocketData *pSockData)
{
	assert(pSockData != NULL);
	WSABUF wsaBuf = {0};
	COverLappedEx *m_pOverLap = new COverLappedEx(IO_TYPE_READ);
	
	wsaBuf.buf = m_pOverLap->m_szBuf;
	wsaBuf.len = MAX_BUF_SIZE;
	DWORD dwBytesRecv = 0, dwFlags = 0;
	int iRet = WSARecv(pSockData->m_Socket, &wsaBuf, 1, &dwBytesRecv, &dwFlags, &(m_pOverLap->m_OLap), NULL);
	if (iRet != NO_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return FALSE;
		}
		//char pContext[] = "aaaaaaaaaaaaaaaaa";
		//PostSend(pContext,sizeof(pContext)*2);
	}
	return TRUE;
}

BOOL CIOCPServer::PostSend(LPCTSTR lpszText, DWORD dwSizeInBytes)
{
	DWORD dwSend = 0;
	CPerSocketData *pSockData = NULL;
	COverLappedEx *pOverLapEx = NULL;

	list<CPerSocketData*>::iterator itSocket = m_ArrSocketData.begin();
	while (itSocket != m_ArrSocketData.end())
	{
		pSockData = *itSocket++;
		if (pSockData->m_Socket != m_ListenSocket)
		{
			pOverLapEx = new COverLappedEx(IO_TYPE_WRITE);
			memcpy_s(pOverLapEx->m_szBuf, MAX_BUF_SIZE, lpszText, dwSizeInBytes);
			WSABUF wsaBuf = {0};
			wsaBuf.buf = pOverLapEx->m_szBuf;
			wsaBuf.len = dwSizeInBytes;
			WSASend(pSockData->m_Socket, &wsaBuf, 1, &dwSend, 0, &(pOverLapEx->m_OLap), NULL);
			
		}
	}
	return TRUE;
}

DWORD WINAPI CIOCPServer::ThreadPoolProcEntry(LPVOID lpParam)
{
	CIOCPServer *pThisObj = (CIOCPServer *)lpParam;
	assert(pThisObj != NULL);

	pThisObj->ThreadPoolProc();
	
	return NULL;
}

DWORD CIOCPServer::ThreadPoolProc()
{
	COverLappedEx *pOverLaps = NULL;
	CPerSocketData *pPerSockData = NULL;
	CHAR	szError[MAX_DATA_LEN] = {0};

	
	InterlockedIncrement(&m_ThreadNums);
	BOOL bIORet = FALSE;
	DWORD dwTrans = 0;

	while (!m_bStopFlag) {
		bIORet = GetQueuedCompletionStatus(m_hCompletionPort, &dwTrans, (PULONG_PTR)&pPerSockData, (LPOVERLAPPED *)&pOverLaps, INFINITE);
		if (!bIORet) continue;

		if (dwTrans == 0 && pOverLaps && (
			pOverLaps->m_IOType == IO_TYPE_READ ||
			pOverLaps->m_IOType == IO_TYPE_WRITE ))
		{
			closesocket(pPerSockData->m_Socket);
			m_ArrSocketData.remove(pPerSockData);
			if(pPerSockData) delete pPerSockData;
			if(pOverLaps) delete pOverLaps;
			continue;
		}
		if(bIORet && pOverLaps && pPerSockData)
		{
			switch (pOverLaps->m_IOType)
			{
			case IO_TYPE_READ:
				pOverLaps->m_Socket = pPerSockData->m_Socket;
				if(pOverLaps)	delete pOverLaps;
				m_pMsgQueue->PutMsg((CHAR*)pOverLaps, sizeof(COverLappedEx), szError);
				PostRecv(pPerSockData);
				break;
			case IO_TYPE_WRITE:
				if(pOverLaps)
					delete pOverLaps;
				break;
			case IO_TYPE_ACCEPT:
				{
					if (pPerSockData->m_AccSocket == INVALID_SOCKET) {
						continue;
					}
					QueueUserWorkItem(ThreadPoolProcEntry, this, WT_EXECUTELONGFUNCTION);
					CPerSocketData *pData = AssignSockToCompletionPort(pPerSockData->m_AccSocket);
					PostRecv(pData);
					PostAccept(pPerSockData);
					delete pOverLaps;
				}
				break;
			default:break;
			}
		}
		else if (!pOverLaps && !pPerSockData) {
			//exit the thread;
			break;
		}
	}
	InterlockedDecrement(&m_ThreadNums);
	return TRUE;
}

DWORD WINAPI CIOCPServer::ProcessRecvMsgEntry(LPVOID lpParma)
{
	CIOCPServer *pThisObj = (CIOCPServer *)lpParma;
	assert(pThisObj != NULL);

	pThisObj->ThreadPoolProc();

	return NULL;

}
DWORD CIOCPServer::ProcessRecvMsg()
{
	INT iRetVal = 0;
	INT size = 0;
	CHAR *pBuffer = new CHAR[MAX_BUF_SIZE];
	COverLappedEx *pOverLapper = new COverLappedEx(IO_TYPE_UNKNOWN);

	while(!m_bStopFlag)
	{
		if(WaitForSingleObject(m_hSemaphore, 10)==WAIT_TIMEOUT)
			continue;
		if(!m_pMsgQueue) continue;
		iRetVal = m_pMsgQueue->GetMsg((CHAR*)pOverLapper);
		if (iRetVal== sizeof(COverLappedEx))
		{
			_snprintf(pBuffer, MAX_BUF_SIZE, "%s", pOverLapper->m_szBuf);
		}
	}
	
	return NULL;
}

wstring CIOCPServer::AnsciiToUnicode(LPCSTR str)
{
	int len = 0;
	len = strlen((const char*)str);
	int unicodeLen = ::MultiByteToWideChar( CP_ACP, 0, str, -1,	NULL, 0); 
	wchar_t * pUnicode; 
	pUnicode = new wchar_t[unicodeLen+1]; 
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
	::MultiByteToWideChar( CP_ACP, 0, str, -1, (LPWSTR)pUnicode, unicodeLen ); 
	wstring rt; 
	rt = ( wchar_t* )pUnicode;
	delete pUnicode; 

	return rt;
}