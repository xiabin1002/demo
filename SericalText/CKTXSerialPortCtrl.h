#ifndef CKTXSERIALPORTCTRL_H
#define CKTXSERIALPORTCTRL_H

#include <termios.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define  KTX_SUCCESS        (0)
#define  KTX_ERR            (1)
#define  KTX_TIMEOUT        (2)

class CMyMutex
{
public:
    CMyMutex(){
        pthread_mutex_init(&m_mutex,NULL);
    }
    ~CMyMutex(){
        pthread_mutex_destroy(&m_mutex);
    }

    void Lock(){
        pthread_mutex_lock(&m_mutex);
    }

    void UnLock(){
        pthread_mutex_unlock(&m_mutex);
    }

public:
    class CAutoLock{
    public:
        CAutoLock(CMyMutex&  m_myMutex):m_lock(m_myMutex){
            m_lock.Lock();
        }
        ~CAutoLock(){
            m_lock.UnLock();
        }
    private:
        CAutoLock(CAutoLock&);
        CAutoLock& operator =(CAutoLock&);
    private:
        CMyMutex&   m_lock;
    };
private:
    CMyMutex(CMyMutex&);
    CMyMutex& operator =(CMyMutex&);
private:
    pthread_mutex_t     m_mutex;
};



class CKTXSerialPortCtrl
{
public:
    CKTXSerialPortCtrl();
    ~CKTXSerialPortCtrl();

    //com:0x0001-0x00FF  usb-to-Com:0xFF01-0xFFFF
    int OpenCom(int iPort,int iBraudrate=115200,int iByteSize=8,int iParity=0 ,int iStopBits=1,int iContorl=0);
    int CloseCom();
    int WriteData(void* lpData,int& iDataLen,unsigned long ulTimeout = 1000);
    int WriteDataEx(void* lpData,int iDataLen,unsigned long ulTimeout = 1000);
    int ReadData(void* lpData,int& iDataLen,unsigned long ulTimeout = 5000);
    int ReadDataEx(void* lpData, int& iDataLen, unsigned long ulTimeout = 5000);
    void ClearBuffer();

protected:
    int          m_iFD;

public:
    CMyMutex     m_mutex;
};

#endif // CKTXSERIALPORTCTRL_H
