#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#pragma once


#define SLEEP_TIME 10	//��λ��ms

class CMessageQueue //Variational Length Message Queue
{

public:

	CMessageQueue();
	~CMessageQueue();

	INT	Create(VOID *pMsgQueueMem, UINT MsgQueueSize, UINT MaxMsgNum, BOOL bAutoCreateGetMutex);	//������Ϣ����
	INT	GetMsg(CHAR* pBuf);										//���ӣ���pGetMutex��Ϊ��������mutex����
	INT	PutMsg(CHAR* pBuf, UINT MsgLength, CHAR *szError);					//��ӣ���pPutMutex��Ϊ��������mutex����
	INT	PeekMsg(CHAR* pBuf, UINT ulElem, UINT MsgLength);		//͵��(������),��pGetMutex��Ϊ��������mutex����

	INT	SetGetMutex(HANDLE	GetMutex);			//����ȡ��Ϣ������
	INT	SetPutMutex(HANDLE	PutMutex);			//���ô����Ϣ������

	INT	IsEmpty();		//�ж϶����Ƿ�Ϊ�գ���Ϊ���򷵻�t
	INT IsFull();		//�ж϶����Ƿ�Ϊ������Index���򷵻�1������Ϣ���ڴ����򷵻�2
	INT	GetMsgNum();	//ȡ�ö��������Ϣ����
	INT	Close();		//�رն��У���Create�ķ�������Ŀǰ������

	INT CalcIndexInfoSize(UINT MaxMsgNum); //������������Index��Ϣ���ڴ��С

	friend  INT VMSMsgQueue_CalcIndexInfoSize(UINT MaxMsgNum); //������������Index��Ϣ���ڴ��С

	INT SetTag(const CHAR * MessageFormat,...);

	INT ClearQ();		//��ն���

protected:

	struct MSG_QUEUE{
		UINT MaxMsgNum;		//��Ϣ���������Ϣ����
		UINT DataHead;		//��Ϣ����ͷָ�룬�������޸�
		UINT DataTail;		//��Ϣ����βָ�룬�������޸�
		UINT IndexHead;		//��������ͷָ�룬�������޸�
		UINT IndexTail;		//��������βָ�룬�������޸�
		UINT MQSize;		//��Ϣ���еĴ�С
		UINT Index[1][2];	//����ָ������
	}*Data; 

	CHAR*				szBuf;			//��Ϣ����
	HANDLE				m_pPutMutex;	//��Ϣ���л���д�źŵ�
	HANDLE				m_pGetMutex;	//��Ϣ���л�����źŵ�
	HANDLE				m_pMutex;
	CHAR				m_cAutoCreateGetMutex;
	CHAR				m_cAutoCreatePutMutex;

	INT					m_ifEnableDoubleMutex;

public:

	INT					m_ifBlock;		//������־,Ĭ��ֵΪFALSE
	CHAR				m_szTag[MAX_PATH];//���Ա�ʶ
	BOOL				m_bNoOutputErr;	//�����������־ 
	 
};
#endif
