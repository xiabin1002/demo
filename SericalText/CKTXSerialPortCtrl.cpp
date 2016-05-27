#include "CKTXSerialPortCtrl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define ERR_KEY (-1)

CKTXSerialPortCtrl::CKTXSerialPortCtrl()
{
    m_iFD = ERR_KEY;
}


CKTXSerialPortCtrl::~CKTXSerialPortCtrl()
{
    if(m_iFD != ERR_KEY)
     {
        CloseCom();
        m_iFD = ERR_KEY;
    }
}

void m_sethwf(int fd, int on)
{
  struct termios tty;
  tcgetattr(fd, &tty);
  if (on)
    tty.c_cflag |= CRTSCTS;
  else
    tty.c_cflag &= ~CRTSCTS;
  tcsetattr(fd, TCSANOW, &tty);
}
/*
 * Set baudrate, parity and number of bits.
 */
void setparms(int fd, int baudr, int par, int bit, int stopb,
                int hwf, int swf)
{
  int spd = -1;
  struct termios tty;
  tcgetattr(fd, &tty);

  switch (baudr) {
  case 2400:    spd = B2400;     break;
  case 19200:	spd = B19200;	break;
  case 38400:	spd = B38400;	break;
  case 57600:	spd = B57600;	break;
  case 115200:	spd = B115200;	break;
  case 9600:
  default:	spd = B9600;	break;
  }

  if (spd != -1) {
    cfsetospeed(&tty, (speed_t)spd);
    cfsetispeed(&tty, (speed_t)spd);
  }

  switch (bit) {
    case 5:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS5;
      break;
    case 6:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS6;
      break;
    case 7:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS7;
      break;
    case 8:
    default:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
      break;
  }

  /* Set into raw, no echo mode */
  tty.c_iflag =  IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_cflag |= CLOCAL | CREAD;

  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 5;

  if (swf)
    tty.c_iflag |= IXON | IXOFF;
  else
    tty.c_iflag &= ~(IXON|IXOFF|IXANY);

  tty.c_cflag &= ~(PARENB | PARODD);

 if (par == 1) //输入和输出是奇校验
    tty.c_cflag |= (PARENB | PARODD);
 else  if (par == 2)//输入和输出是偶校验
     tty.c_cflag |= PARENB;

  if (stopb == 2)
    tty.c_cflag |= CSTOPB;
  else
    tty.c_cflag &= ~CSTOPB;

  tcsetattr(fd, TCSANOW, &tty);
  m_sethwf(fd, hwf);
}

int	SetSerialPort(
    int		fd,					// 串口的文件描述符
    int		iSerialPortSpeed,	// 串口速率(读写速率一致)
    int		iBits,				// 数据位 或 字符大小 ???
    int		iParityCheck,		// 奇偶校验位
    int		iStop,				// 停止位
    int		iFlowControl		// 流控标志位
)
{
    /* 各变量的定义 */
    struct termios	TNewSerialPortParam;	// 新串口配置参数
    //struct termios	TOldSerialPortParam;	// 老串口配置参数
    /* 各变量值的赋值和初始化 */
    /* 函数任务开始 */
    // 保存测试现有串口的参数设置，如果串口号等出错，则有相关出错信息
    if ( 0 != tcgetattr( fd, &TNewSerialPortParam ) )
    {
        perror("SetupSerial 1");
        return	(-1);
    }
    // 新串口配置参数清零
    //bzero( &TNewSerialPortParam, sizeof(TNewSerialPortParam) );
	
	 TNewSerialPortParam.c_cflag &= ~HUPCL;
	 TNewSerialPortParam.c_iflag &= ~INPCK;
	 TNewSerialPortParam.c_iflag |= IGNBRK;
	 TNewSerialPortParam.c_iflag &= ~ICRNL;
	 TNewSerialPortParam.c_iflag &= ~IXON;
	 TNewSerialPortParam.c_lflag &= ~IEXTEN;
	 TNewSerialPortParam.c_lflag &= ~ECHOK;
	 TNewSerialPortParam.c_lflag &= ~ECHOCTL;
	 TNewSerialPortParam.c_lflag &= ~ECHOKE;
	 TNewSerialPortParam.c_oflag &= ~ONLCR;

    // 激活本地连接和接收使能
    TNewSerialPortParam.c_cflag |= CLOCAL | CREAD;
    // 设置数据位
    TNewSerialPortParam.c_cflag &= ~CSIZE;
    switch ( iBits )
    {
        case 7:
            TNewSerialPortParam.c_cflag |= CS7;
            break;
        case 8:
            TNewSerialPortParam.c_cflag |= CS8;
            break;
        default:				// 默认数据位为8
            TNewSerialPortParam.c_cflag |= CS8;
            break;
    }// end of switch ( iBits )
    // 设置波特率
    switch ( iSerialPortSpeed )
    {
        case 9600:
            cfsetispeed( &TNewSerialPortParam, B9600);
            cfsetospeed( &TNewSerialPortParam, B9600);
            break;
        case 19200:
              cfsetispeed( &TNewSerialPortParam, B19200);
             cfsetospeed( &TNewSerialPortParam, B19200);
             break;
        case 38400:
            cfsetispeed( &TNewSerialPortParam, B38400);
           cfsetospeed( &TNewSerialPortParam, B38400);
           break;
        case 57600:
            cfsetispeed( &TNewSerialPortParam, B57600);
           cfsetospeed( &TNewSerialPortParam, B57600);
           break;
        case 115200:
            cfsetispeed( &TNewSerialPortParam, B115200 );
            cfsetospeed( &TNewSerialPortParam, B115200);
            break;
        default:
            cfsetispeed( &TNewSerialPortParam, B9600 );
            cfsetospeed( &TNewSerialPortParam, B9600);
            break;
    }// end of switch ( iSerialPortSpeed )
    // 设置奇偶校验位
    switch ( iParityCheck )
    {
        case 1://ODD_CHECK:			// 奇校验

        TNewSerialPortParam.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  //Input替代原有的

            TNewSerialPortParam.c_cflag |= PARENB;
            TNewSerialPortParam.c_cflag |= PARODD;
            TNewSerialPortParam.c_iflag |= INPCK;
            break;
        case 2://EVEN_CHECK:			// 偶校验

        TNewSerialPortParam.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  //Input替代原有的

            TNewSerialPortParam.c_iflag |= INPCK;
            TNewSerialPortParam.c_cflag |= PARENB;
            TNewSerialPortParam.c_cflag &= ~PARODD;


            break;
        case 0://NO_CHECK:			// 无奇偶校验位
            //TNewSerialPortParam.c_cflag &= ~PARENB;
            TNewSerialPortParam.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  //Input替代原有的
			TNewSerialPortParam.c_oflag  &= ~OPOST; 
            break;
        default:				// 默认无奇偶校验位
            TNewSerialPortParam.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  //Input替代原有的
			TNewSerialPortParam.c_oflag  &= ~OPOST; 
            break;
    }// end of switch ( cParityCheck )
    // 设置停止位
    switch ( iStop )
    {
        case 2:				// 停止位为2，激活CSTOPB
            TNewSerialPortParam.c_cflag |= CSTOPB;
            break;
        case 1:				// 停止位为1，清除CSTOPB
            TNewSerialPortParam.c_cflag &= ~CSTOPB;
            break;
        default:				// 默认停止位为1
            TNewSerialPortParam.c_cflag &= ~CSTOPB;
            break;
    }// end of switch ( iStop )
    // 设置流控
    switch ( iFlowControl )
    {
        case 0:// NO_FLOW_CTRL:	    // 无流控
            TNewSerialPortParam.c_cflag &= ~CRTSCTS;	// 关闭硬件流控
            TNewSerialPortParam.c_iflag &= ~( IXON | IXOFF | IXANY );// 关闭软件流控
            break;
        case 1://HARD_FLOW_CTRL:	// 硬流控
            TNewSerialPortParam.c_cflag |= CRTSCTS;		// 开启硬件流控
            TNewSerialPortParam.c_iflag &= ~( IXON | IXOFF | IXANY );// 关闭软件流控
            break;
        case 2://SOFT_FLOW_CTRL:	// 软流控
            TNewSerialPortParam.c_cflag &= ~CRTSCTS;	// 关闭硬件流控
            TNewSerialPortParam.c_iflag |= ( IXON | IXOFF | IXANY );// 开启软件流控
            break;
        default:				// 默认无流控
            TNewSerialPortParam.c_cflag &= ~CRTSCTS;	// 关闭硬件流控
            TNewSerialPortParam.c_iflag &= ~( IXON | IXOFF | IXANY );// 关闭软件流控
            break;
    }// end of switch ( iFlowControl )
    // 设置等待时间和最小接收字符
    TNewSerialPortParam.c_cc[VTIME] = 5;
    TNewSerialPortParam.c_cc[VMIN] = 1;


    // 处理未接受字符
    tcflush( fd, TCIFLUSH );
    // 激活新配置
    if ( 0 != tcsetattr(fd, TCSANOW, &TNewSerialPortParam) )
    {
        perror("com set error");
        return	(-1);
    }
//	printf("set done!\n");
    /* 函数任务结束 */
    return	0;
}


int CKTXSerialPortCtrl::OpenCom(int iPort,int iBraudrate/*=115200*/,int iByteSize/*=8*/,int iParity/*=0*/ ,int iStopBits/*=1*/,int iContorl/*=0*/)
{
    CMyMutex::CAutoLock lock(m_mutex);

    if(ERR_KEY != m_iFD)
        return KTX_SUCCESS;

    if(0==(iPort&0xFF))
        return KTX_ERR;

    char csDevPath[100]={0};
    if(iPort&0x0F00)
        sprintf(csDevPath,"/dev/ttyUSB%d",(iPort&0xFF)-1);
    else if(iPort&0xF000)
        sprintf(csDevPath,"/dev/ttySNX%d",(iPort&0xFF)-1);
    else
        sprintf(csDevPath,"/dev/ttyS%d",iPort-1);

    int iRet = KTX_ERR;
    m_iFD = open(csDevPath,O_RDWR|O_NOCTTY|O_NDELAY);
    if(m_iFD<0)
        return iRet;

    if(fcntl(m_iFD,F_SETFL,0)<0)
    {
      CloseCom();
      return iRet;
    }

    setparms(m_iFD, iBraudrate, iParity, iByteSize,  iStopBits, iContorl, iContorl);
   // SetSerialPort(m_iFD,iBraudrate,iByteSize,iParity,iStopBits,iContorl);

    return KTX_SUCCESS;
}


int CKTXSerialPortCtrl::CloseCom()
{
    if(m_iFD != ERR_KEY)
    {
        close(m_iFD);
        m_iFD = ERR_KEY;
    }

    return KTX_SUCCESS;
}

int CKTXSerialPortCtrl::WriteData(void* lpData,int& iDataLen,unsigned long ulTimeout /*= 1000*/)
{
    CMyMutex::CAutoLock lock(m_mutex);

    if(ERR_KEY == m_iFD)
        return KTX_ERR;

    int iRet = KTX_ERR;
    tcflush(m_iFD, TCIOFLUSH);//TCOFLUSH刷新数据但不传送

    int iLen = write(m_iFD, lpData, iDataLen);//实际写入的长度
    if(iLen == iDataLen)
        iRet = KTX_SUCCESS;
    else
        iDataLen = iLen;

    return iRet;
}

 int CKTXSerialPortCtrl::WriteDataEx(void* lpData,int iDataLen,unsigned long ulTimeout /*= 1000*/)
 {
     CMyMutex::CAutoLock lock(m_mutex);

     if(ERR_KEY == m_iFD)
         return KTX_ERR;

     int iRet = KTX_ERR;
     tcflush(m_iFD, TCIOFLUSH);//TCOFLUSH刷新数据但不传送

     int iLen = write(m_iFD, lpData, iDataLen);//实际写入的长度
     if(iLen == iDataLen)
         iRet = KTX_SUCCESS;

     return iRet;
 }

int CKTXSerialPortCtrl::ReadData(void* lpData,int& iDataLen,unsigned long ulTimeout /*= 5000*/)
{
    CMyMutex::CAutoLock lock(m_mutex);

    if(ERR_KEY == m_iFD)
        return KTX_ERR;

    int iRet = KTX_ERR;
    fd_set fs_read;
    struct timeval tv_timeout;
    struct timeval tv_timeout2;

    FD_ZERO(&fs_read);
    FD_SET(m_iFD, &fs_read);
    tv_timeout.tv_sec  = ulTimeout/1000;
    tv_timeout.tv_usec = (ulTimeout%1000)*1000;

    tv_timeout2.tv_sec  = 0;
    tv_timeout2.tv_usec = 10000;

    if(0 == select(m_iFD+1, &fs_read, NULL, NULL, &tv_timeout))
    {
         iDataLen = 0;
        iRet = KTX_TIMEOUT;
    }
    else
    {
        int iTotal =0,iLen=0;
        do
        {
            if (FD_ISSET(m_iFD, &fs_read))
             {
               iLen = read(m_iFD, lpData+iTotal, iDataLen-iTotal);
               iTotal += iLen;

               if(iTotal>=iDataLen)
               {
                    iRet = KTX_SUCCESS;
                   break;
               }
            }

            if(0 == select(m_iFD+1, &fs_read, NULL, NULL, &tv_timeout2))
            {
                if(0 == select(m_iFD+1, &fs_read, NULL, NULL, &tv_timeout))
                {
                    iRet = KTX_TIMEOUT;
                    break;
                }
            }
        }while(iLen>0);

        iDataLen = iTotal;
    }

    return iRet;
}

int CKTXSerialPortCtrl::ReadDataEx(void* lpData,int& iDataLen,unsigned long ulTimeout /*= 5000*/)
{
    CMyMutex::CAutoLock lock(m_mutex);

    if(ERR_KEY == m_iFD)
        return KTX_ERR;

    int iRet = KTX_SUCCESS;
    fd_set fs_read;
    struct timeval tv_timeout;
    struct timeval tv_timeout2;

    FD_ZERO(&fs_read);
    FD_SET(m_iFD, &fs_read);
    tv_timeout.tv_sec  = ulTimeout/1000;
    tv_timeout.tv_usec = (ulTimeout%1000)*1000;

    tv_timeout2.tv_sec  = 0;
    tv_timeout2.tv_usec = 100000;

    if(0 == select(m_iFD+1, &fs_read, NULL, NULL, &tv_timeout))
    {
        iDataLen = 0;
        iRet = KTX_TIMEOUT;
    }
    else
    {
        int iTotal =0,iLen=0;
        do
        {
            if (FD_ISSET(m_iFD, &fs_read))
             {
               iLen = read(m_iFD, lpData+iTotal, iDataLen-iTotal);
               iTotal += iLen;
            }

            if(0 == select(m_iFD+1, &fs_read, NULL, NULL, &tv_timeout2))
            {
                break;
            }
        }while(iLen>0);

        iDataLen = iTotal;
    }

    return iRet;
}

void CKTXSerialPortCtrl::ClearBuffer()
{
    CMyMutex::CAutoLock lock(m_mutex);

    if(ERR_KEY == m_iFD)
        return;

    tcflush(m_iFD, TCIOFLUSH);//TCOFLUSH刷新数据但不传送
}
