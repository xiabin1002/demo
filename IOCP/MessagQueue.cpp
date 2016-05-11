#include "StdAfx.h"
#include "MessagQueue.h"
#include <assert.h>
#include <stdio.h>


#define  WAIT_MUTEX_TIMER		(10)


CMessageQueue::CMessageQueue()
{
	Data=NULL;
	m_ifBlock=FALSE;
	m_pPutMutex=NULL;	
	m_pGetMutex=NULL;
	m_pMutex=NULL;
	szBuf=NULL;	
	m_szTag[0] = 0;
	m_bNoOutputErr = FALSE;
	m_ifEnableDoubleMutex = TRUE;
}

CMessageQueue::~CMessageQueue()
{
	if(m_ifEnableDoubleMutex) {
		CloseHandle(m_pGetMutex);
		CloseHandle(m_pPutMutex);
	} else {
		CloseHandle(m_pMutex);
	}
	
}

INT CMessageQueue::Close()
{
	return 0;
}

INT CMessageQueue::CalcIndexInfoSize(UINT MaxMsgNum)
{
	return sizeof(MSG_QUEUE)+(MaxMsgNum-1)*2*sizeof(UINT);
}

//实际最大消息个数为MaxMsgNum-1
/**
函数功能：				创建消息队列

参数说明：
pMsgQueueMem		队列内存的起始地址
MsgQueueSize		队列内存分配的大小
MaxMsgNum			消息队列的最大存放消息个数
*/
INT	CMessageQueue::Create(VOID *pMsgQueueMem, UINT MsgQueueSize, UINT MaxMsgNum, BOOL bAutoCreateGetMutex)	
{

	UINT lentmp=sizeof(MSG_QUEUE)+(MaxMsgNum-1)*2*sizeof(UINT);

	if(MsgQueueSize <= lentmp)	return FAIL;
	if(MaxMsgNum < 2) return FAIL;  

	Data=(MSG_QUEUE *)pMsgQueueMem;
	if(Data==NULL) return FAIL;
	
	Data->MaxMsgNum = MaxMsgNum;

	szBuf=(CHAR*)((ULONG)Data+lentmp);
	
	Data->MQSize=MsgQueueSize - lentmp;

	Data->IndexHead=0;
	Data->IndexTail=0;
	Data->DataHead=0;
	Data->DataTail=0;

	if(bAutoCreateGetMutex)
	{
		if(m_ifEnableDoubleMutex) {
			m_pPutMutex = CreateMutex(NULL, FALSE, NULL);
			m_pGetMutex = CreateMutex(NULL, FALSE, NULL);
		} else {
			m_pMutex = CreateMutex(NULL, FALSE, NULL);
		}
	}
	
	return SUCCES;
}

INT CMessageQueue::GetMsg(CHAR *Buffer)
{
	UINT IndexTail;
	UINT MsgBegin,MsgEnd;
	UINT len;
	DWORD rv;
		

	if(Buffer==NULL) return FAIL;
	if(Data==NULL)   return FAIL;

	HANDLE pMutex = m_pMutex;
	if(m_ifEnableDoubleMutex) pMutex = m_pGetMutex;
	
	//消息队列为空
	if(pMutex)
	{ 
		rv=WaitForSingleObject(pMutex, WAIT_MUTEX_TIMER);
		if(rv!= WAIT_OBJECT_0){
			ReleaseMutex(pMutex);
			return FAIL;
		}
	}
	if(Data->IndexHead==Data->IndexTail)
	{		
		for(;;)
		{
			if(m_ifBlock==FALSE)
			{
				if(pMutex) ReleaseMutex(pMutex);
				return FAIL;
			}
			Sleep(SLEEP_TIME);
			if(Data->IndexHead!=Data->IndexTail) break;
		}
	}

	IndexTail=Data->IndexTail;

	MsgBegin=Data->Index[IndexTail][0];
	MsgEnd  =Data->Index[IndexTail][1];
	if(MsgBegin==MsgEnd)
	{
		if(pMutex) ReleaseMutex(pMutex);
		return 0;
	}
	if(MsgEnd>MsgBegin)
	{
	    len=MsgEnd-MsgBegin;
	    memcpy(Buffer,(szBuf+MsgBegin),len);
	}
	else
	{
		len=Data->MQSize-MsgBegin;
		memcpy(Buffer,(szBuf+MsgBegin),len);
		memcpy((Buffer+len),szBuf,MsgEnd);
		len=Data->MQSize-MsgBegin+MsgEnd;
	}
	IndexTail=(IndexTail+1)%Data->MaxMsgNum;
	Data->IndexTail=IndexTail;
	Data->DataTail=MsgEnd;
	if(pMutex)	ReleaseMutex(pMutex);
	return len;
}

INT CMessageQueue::PutMsg(CHAR *Buffer,UINT MsgLength,CHAR *szError)
{
	UINT	DataHead,DataTail,len;
	UINT	MsgBegin;
	UINT	IndexHead;
	INT		RetVal;
	DWORD	rv;	

	if(Data==NULL)  
	{
		if(szError) sprintf(szError, "Data==NULL");
		return	FAIL;
	}

	HANDLE  pMutex = m_pMutex;
	if(m_ifEnableDoubleMutex) pMutex = m_pPutMutex;
	
	if(pMutex){
		rv=WaitForSingleObject(pMutex, WAIT_MUTEX_TIMER);
		if(rv != WAIT_OBJECT_0)
		{
			ReleaseMutex(pMutex);
			if(szError) sprintf(szError, "WaitForSingleObject(%p) fail.", pMutex);
			return FAIL;
		}
	}

	for(;;)	{
		DataHead=Data->DataHead;
		DataTail=Data->DataTail;
		RetVal=0;
		if((DataHead>=DataTail)&&(DataHead+MsgLength)>Data->MQSize){
			if((DataHead+MsgLength)%Data->MQSize>=DataTail) RetVal=-1;//full
		}
		if(DataHead<DataTail){
			if((DataHead+MsgLength)>=DataTail) RetVal=-1;//full
		}
		if(RetVal== (INT)-1){
			if(!m_bNoOutputErr)
			//printf("CMessageQueue::PutMsg>>> <%s> 1:FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL \r\n", m_szTag);
			if(m_ifBlock==FALSE){
				if(pMutex) ReleaseMutex(pMutex);
				if(szError) sprintf(szError, "(1)CMessageQueue FULL.");
				return FAIL;
			}
			Sleep(SLEEP_TIME);
		}
		else break;
	}
	MsgBegin=DataHead;
	if((DataHead+MsgLength)>=Data->MQSize)
	{
		len=Data->MQSize-DataHead;
		memcpy((szBuf+DataHead),Buffer,len);
		memcpy(szBuf,(Buffer+len),MsgLength-len);
		DataHead=MsgLength-len;
	}
	else
	{
		memcpy((szBuf+DataHead),Buffer,MsgLength);
		DataHead=DataHead+MsgLength;
	}

	if((Data->IndexHead+1)%Data->MaxMsgNum==Data->IndexTail)
	{		
		if(!m_bNoOutputErr)
		//printf("CMessageQueue::PutMsg>>> <%s> 2:FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL FULL \r\n", m_szTag);
		for(;;){			
			if(m_ifBlock==FALSE){
				if(pMutex) ReleaseMutex(pMutex);
				if(szError) sprintf(szError, "(2)CMessageQueue FULL.");
				return FAIL;
			}
			Sleep(SLEEP_TIME);
			if((Data->IndexHead+1)%Data->MaxMsgNum!=Data->IndexTail) break;
		}
	}
	IndexHead=Data->IndexHead;
	Data->Index[IndexHead][0]=MsgBegin;
	Data->Index[IndexHead][1]=DataHead;
	IndexHead=(IndexHead+1)%Data->MaxMsgNum;

	Data->IndexHead=IndexHead;
	Data->DataHead=DataHead;
	if(pMutex)	ReleaseMutex(pMutex);
	return 0;
}

INT	CMessageQueue::SetGetMutex(HANDLE	InGetMutex)
{	
	if(m_ifEnableDoubleMutex) {
		m_pGetMutex	= InGetMutex;
	} else {
		m_pMutex	= InGetMutex;
	}
	return 0;
}
	
INT	CMessageQueue::SetPutMutex(HANDLE	InPutMutex)
{
	if(m_ifEnableDoubleMutex) {
		m_pPutMutex	= InPutMutex;
	} else {
		m_pMutex	= InPutMutex;
	}
	return 0;
}


INT CMessageQueue::IsEmpty()
{
	return(Data->IndexHead == Data->IndexTail);
	
}

INT CMessageQueue::IsFull()
{
	if((Data->IndexHead+1)%Data->MaxMsgNum==Data->IndexTail) return 1; //index full

	UINT DataHead=Data->DataHead;
	UINT DataTail=Data->DataTail;
	if((DataHead>=DataTail)&&(DataHead+1)>Data->MQSize){
		if((DataHead+1)%Data->MQSize>=DataTail) return 2;	//msg mem full
	}
	if(DataHead<DataTail){
		if((DataHead+1)>=DataTail) return 2;				//msg full
	}

	return 0;
}

INT	CMessageQueue::GetMsgNum()
{
	if(Data->IndexHead >= Data->IndexTail)
		return (Data->IndexHead - Data->IndexTail);
	else
		return (Data->IndexHead+Data->MaxMsgNum - Data->IndexTail);
}

INT	CMessageQueue::ClearQ()
{
	Data->IndexHead = 0;
	Data->IndexTail = 0;
	return 0;
}

INT CMessageQueue::SetTag(const CHAR * MessageFormat,...)
{
	va_list args;

	va_start(args, MessageFormat);
	vsprintf(m_szTag, MessageFormat, args);

	return 0;
}

INT VMSMsgQueue_CalcIndexInfoSize(UINT MaxMsgNum)
{
	return sizeof(CMessageQueue::MSG_QUEUE)+(MaxMsgNum-1)*2*sizeof(UINT);
}

