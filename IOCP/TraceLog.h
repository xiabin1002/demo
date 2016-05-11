#ifndef _TRACELOG_H
#define _TRACELOG_H


#pragma once

#include <string.h>
#include <time.h>
#include <fstream>
#include "MessagQueue.h"


#define  MAX_DATA_LEN				(2048)
#define  MAN_WRITE_LOG_LEN			(128*1024)   //一次写日志128K
#define  CHECK_WRITELOG_TIMEOUT		(40)		//检测写日志超时的周期
#define  MAX_LOGITEM_LEN			(MAX_DATA_LEN+512)	//一次接收TRACE日志的的长度
#define  MAX_LOGLINE_NUM			(50000)
#define	 MAX_LOGITEM_NUM			(10240)
#define  CHECK_AUTORAR_INTERVAL		(30)		//检测自动压缩日志的时间间隔，单位s
#define  CHECK_AUTODEL_INTERVAL		(3600)		//检测自动删除日志的时间间隔，单位s


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
	
	CMessageQueue*	m_pLogQueue;			//写日志队列类
	
	fstream		m_fstream;					
	UCHAR*		m_pLogQMem;					//分配创建日志内存

	CHAR		m_szCurRunPath[MAX_PATH];	//当前进程运行路径
	CHAR		m_szCurLogName[MAX_PATH];   //当前写日志名
	CHAR		m_szRarLogName[MAX_PATH];	//压缩文件名
	BOOL		m_bOpenFile;				//日志文件打开标志
	LONG		m_lLineCounts;				//一个日志文件写日志的最大行号
	BOOL		m_bStopFlag;				//写日志停止
	DWORD		m_wCurDay;					
	HANDLE		m_hSemaphore;
	HANDLE		m_pWriteLogMutex;			//写日志互斥量
	HANDLE		m_hWriteThread;				//写日志线程句柄
	HANDLE		m_hDelThread;				//删除日志线程句柄

	//读取配置文件变量
	CHAR		m_szLogPath[MAX_PATH];		//写日志路径
	DWORD		m_wLogFileSaveDay;			//日志文件保存天数
	BOOL		m_bEnableRarLog;			//启动压缩日志

};


#endif