#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#pragma once


#define SLEEP_TIME 10	//单位：ms

class CMessageQueue //Variational Length Message Queue
{

public:

	CMessageQueue();
	~CMessageQueue();

	INT	Create(VOID *pMsgQueueMem, UINT MsgQueueSize, UINT MaxMsgNum, BOOL bAutoCreateGetMutex);	//创建消息队列
	INT	GetMsg(CHAR* pBuf);										//出队，若pGetMutex不为空则启用mutex保护
	INT	PutMsg(CHAR* pBuf, UINT MsgLength, CHAR *szError);					//入队，若pPutMutex不为空则启用mutex保护
	INT	PeekMsg(CHAR* pBuf, UINT ulElem, UINT MsgLength);		//偷看(不出队),若pGetMutex不为空则启用mutex保护

	INT	SetGetMutex(HANDLE	GetMutex);			//设置取消息互斥体
	INT	SetPutMutex(HANDLE	PutMutex);			//设置存放消息互斥体

	INT	IsEmpty();		//判断队列是否为空，若为空则返回t
	INT IsFull();		//判断队列是否为满，若Index满则返回1，若消息体内存满则返回2
	INT	GetMsgNum();	//取得队列里的消息个数
	INT	Close();		//关闭队列，是Create的反操作，目前无意义

	INT CalcIndexInfoSize(UINT MaxMsgNum); //计算用来保存Index信息的内存大小

	friend  INT VMSMsgQueue_CalcIndexInfoSize(UINT MaxMsgNum); //计算用来保存Index信息的内存大小

	INT SetTag(const CHAR * MessageFormat,...);

	INT ClearQ();		//清空队列

protected:

	struct MSG_QUEUE{
		UINT MaxMsgNum;		//消息队列最大消息个数
		UINT DataHead;		//消息队列头指针，生产者修改
		UINT DataTail;		//消息队列尾指针，消费者修改
		UINT IndexHead;		//数据索引头指针，生产者修改
		UINT IndexTail;		//数据索引尾指针，消费者修改
		UINT MQSize;		//消息队列的大小
		UINT Index[1][2];	//数据指针数据
	}*Data; 

	CHAR*				szBuf;			//消息队列
	HANDLE				m_pPutMutex;	//消息队列互斥写信号灯
	HANDLE				m_pGetMutex;	//消息队列互斥读信号灯
	HANDLE				m_pMutex;
	CHAR				m_cAutoCreateGetMutex;
	CHAR				m_cAutoCreatePutMutex;

	INT					m_ifEnableDoubleMutex;

public:

	INT					m_ifBlock;		//阻塞标志,默认值为FALSE
	CHAR				m_szTag[MAX_PATH];//调试标识
	BOOL				m_bNoOutputErr;	//不输出错误日志 
	 
};
#endif
