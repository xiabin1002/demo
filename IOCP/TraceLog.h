#ifndef _TRACELOG_H
#define _TRACELOG_H


#pragma once

#include <string.h>
#include <time.h>
#include <fstream>
#include "MessagQueue.h"


#define  MAX_DATA_LEN				(2048)
#define  MAN_WRITE_LOG_LEN			(128*1024)   //һ��д��־128K
#define  CHECK_WRITELOG_TIMEOUT		(40)		//���д��־��ʱ������
#define  MAX_LOGITEM_LEN			(MAX_DATA_LEN+512)	//һ�ν���TRACE��־�ĵĳ���
#define  MAX_LOGLINE_NUM			(50000)
#define	 MAX_LOGITEM_NUM			(10240)
#define  CHECK_AUTORAR_INTERVAL		(30)		//����Զ�ѹ����־��ʱ��������λs
#define  CHECK_AUTODEL_INTERVAL		(3600)		//����Զ�ɾ����־��ʱ��������λs


class CTraceLog
{
public:
	CTraceLog(void);
	CTraceLog(LPCTSTR lpszFileName);
	~CTraceLog(void);


public:

	BOOL CreateLogPath();
	INT  InitData();
	INT	 Create(UINT ulMaxMsgNum, UINT ulMaxMsgMem, BOOL bAutoCreateMutex = TRUE);
	BOOL CloseLog();
	INT  Star();
	INT  LogTraceA(INT iLogType, const CHAR * MessageFormat, ...);
	INT  Log2WriteQ(CHAR* MessageB, INT iStrLen, INT iLogType);

private:

	BOOL OpenLog(SYSTEMTIME *pxt);
	INT  WriteLog(CHAR* Msg, INT iMsgLen, INT iLineNum);


	static DWORD  WINAPI WriteLogThreadEntry(LPVOID lpParam);
	DWORD  WriteLogThread();
	static DWORD  WINAPI DelLogThreadEntry(LPVOID lpParam);
	INT	DelLogThread();
	INT AutoDelFile(int DayNum);

	VOID RarLogFile();


private:
	
	CMessageQueue*	m_pLogQueue;			//д��־������
	
	fstream		m_fstream;					
	UCHAR*		m_pLogQMem;					//���䴴����־�ڴ�

	CHAR		m_szCurRunPath[MAX_PATH];	//��ǰ��������·��
	CHAR		m_szCurLogName[MAX_PATH];   //��ǰд��־��
	CHAR		m_szRarLogName[MAX_PATH];	//ѹ���ļ���
	BOOL		m_bOpenFile;				//��־�ļ��򿪱�־
	LONG		m_lLineCounts;				//һ����־�ļ�д��־������к�
	BOOL		m_bStopFlag;				//д��־ֹͣ
	DWORD		m_wCurDay;					
	HANDLE		m_hSemaphore;
	HANDLE		m_pWriteLogMutex;			//д��־������
	HANDLE		m_hWriteThread;				//д��־�߳̾��
	HANDLE		m_hDelThread;				//ɾ����־�߳̾��

	//��ȡ�����ļ�����
	CHAR		m_szLogPath[MAX_PATH];		//д��־·��
	DWORD		m_wLogFileSaveDay;			//��־�ļ���������
	BOOL		m_bEnableRarLog;			//����ѹ����־

};


#endif