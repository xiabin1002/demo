#ifndef  _IOCP_SERVER_H
#define  _IOCP_SERVER_H


#pragma once


//#include <ws2tcpip.h>
//#include <MSWSock.h>
//#include <WinSock2.h>
//#include <iostream>
#include <list>

#include "MessagQueue.h"

//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "mswsock.lib")

using namespace std;

#define MAX_BUF_SIZE 4096
#define WM_SHOW_MSG WM_USER+100

enum IO_TYPE {
	IO_TYPE_ACCEPT,
	IO_TYPE_READ,
	IO_TYPE_WRITE,
	IO_TYPE_UNKNOWN
};

class CPerSocketData {
public:
	SOCKET m_Socket;		//监听套接字
	SOCKET m_AccSocket;		//连接请求套接字

	CPerSocketData() {
		m_Socket = INVALID_SOCKET;
		m_AccSocket = INVALID_SOCKET;
	}
};

class COverLappedEx {
public:
	OVERLAPPED m_OLap;
	IO_TYPE m_IOType;
	SOCKET m_Socket;
	char m_szBuf[MAX_BUF_SIZE];
	 

	COverLappedEx(IO_TYPE ioType) {
		memset(&m_OLap, 0, sizeof(OVERLAPPED));
		m_IOType = ioType;
		memset(m_szBuf, 0, MAX_BUF_SIZE);
	}
};


class CIOCPServer
{
public:
	CIOCPServer(void);
	~CIOCPServer(void);

	INT Initialize();


private:

	void SetLastErrorMsg(string strErrorMsg);
	string GetLastErrorMsg();
	BOOL WinSockInit();
	INT  StartServer();
	BOOL PostAccept(CPerSocketData *pSockData);
	BOOL PostRecv(CPerSocketData *pSockData);
	BOOL PostSend(LPCTSTR lpszText, DWORD dwSizeInBytes);
	static DWORD WINAPI ThreadPoolProcEntry(LPVOID lpParam);
	DWORD  ThreadPoolProc();
	static DWORD WINAPI ProcessRecvMsgEntry(LPVOID lpParma);
	DWORD ProcessRecvMsg();
	CPerSocketData *AssignSockToCompletionPort(SOCKET tSocket);
	void StopServer();

private:

	wstring AnsciiToUnicode(LPCSTR str);


private:

	BOOL			m_bStopFlag;
	UINT			m_listenPort;
	LONG			m_ThreadNums;
	string			m_strErrorMsg;
	SOCKET			m_ListenSocket;
	HANDLE			m_hCompletionPort;
	HANDLE			m_hSemaphore;

	
	list<CPerSocketData*> m_ArrSocketData;		//保存连接socket发送的请求数据
	CMessageQueue*		  m_pMsgQueue;		//保存接收数据
};


#endif