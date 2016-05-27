#include <iostream>
#include "CKTXSerialPortCtrl.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h> /* POSIX terminal control definitions */



using namespace std;

/*
 *
 * Windows	COM1	COM2	-
Linux	/dev/ttyS0	/dev/ttyS1	/dev/ttyUSB0
usermod -aG dialout $USER
*/

CKTXSerialPortCtrl dev;

void entrycard()
{
    unsigned char send[1024]={0};
    unsigned char cRev[1024]={0};
    unsigned char cAck[10]={0};

    int iSendLen=0;
    int iRet = 0;
    int iRecvLen = 0;
    send[iSendLen++] = 0xF2;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x03;
    send[iSendLen++] = 0x43;
    send[iSendLen++] = 58;
    send[iSendLen++] = 48;
    send[iSendLen++] = 25;
    send[iSendLen++] = 208;

    iRet = dev.WriteData(send,iSendLen);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
    iRecvLen = 1;
    memset(cRev,0,iRecvLen);
    iRet =dev.ReadData(cRev,iRecvLen,1000);
    if(cRev[0] != 0x06)
        return;

    iRecvLen = 1000;
    iRet =dev.ReadDataEx(cRev+1,iRecvLen,100000);
    int in=1;
    iRet = dev.WriteData(cAck,in);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
}

void readtrack()
{
    unsigned char send[1024]={0};
    unsigned char cRev[1024]={0};
    unsigned char cAck[10]={0};

    int iRecvLen = 0;
    int iSendLen=0;
    int iRet = 0;

    send[iSendLen++] = 0xF2;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x03;
    send[iSendLen++] = 0x43;
    send[iSendLen++] = 54;
    send[iSendLen++] = 53;
    send[iSendLen++] = 12;
    send[iSendLen++] = 24;

    iRet = dev.WriteData(send,iSendLen);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
    iRecvLen = 1;
    memset(cRev,0,iRecvLen);
    iRet =dev.ReadData(cRev,iRecvLen,1000);
    if(cRev[0] != 0x06)
        return;

    iRecvLen = 1024;
    iRet =dev.ReadDataEx(cRev+1,iRecvLen,100000);

    cAck[0] = 0x06;
    int in=1;

    iRet = dev.WriteData(cAck,in);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
}
/*
void readtrack()
{
    unsigned char send[1024]={0};
    unsigned char cRev[1024]={0};
    unsigned char cAck[10]={0};

    int iRecvLen = 0;
    int iSendLen=0;
    int iRet = 0;

    send[iSendLen++] = 0xF2;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x03;
    send[iSendLen++] = 0x43;
    send[iSendLen++] = 54;
    send[iSendLen++] = 53;
    send[iSendLen++] = 12;
    send[iSendLen++] = 24;

    iRet = dev.WriteData(send,iSendLen);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
    iRecvLen = 1;
    memset(cRev,0,iRecvLen);
    iRet =dev.ReadData(cRev,iRecvLen,1000);
    if(cRev[0] != 0x06)
        return;

    iRecvLen = 1024;
    iRet =dev.ReadDataEx(cRev+1,iRecvLen,100000);

    cAck[0] = 0x06;
    int in=1;

    iRet = dev.WriteData(cAck,in);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
}
*/
int test_3q8(int iCom)
{

   int iRet = dev.OpenCom(0X0f02,38400,8,2,1,1);
    if(KTX_SUCCESS != iRet){
           cout <<"ERR="<<iRet<< endl;
           return -1;
    }
    cout <<"com="<<iCom<< endl;

    int iSendLen= 0,iRecvLen=0,in;

      unsigned char send[64]={0};
      unsigned char cRev[64]={0};
      unsigned char cAck[10]={0};

       send[iSendLen++] = 0xF2;
       send[iSendLen++] = 0x00;
       send[iSendLen++] = 0x0E;
       send[iSendLen++] = 0x43;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x33;
       send[iSendLen++] = 0x32;
       send[iSendLen++] = 0x34;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0x30;
       send[iSendLen++] = 0xc4;
       send[iSendLen++] = 0x2d;

//      send[iSendLen++] = 0xF2;
//      send[iSendLen++] = 0x00;
//      send[iSendLen++] = 0x03;
//      send[iSendLen++] = 0x43;
//      send[iSendLen++] = 0x3A;
//      send[iSendLen++] = 0x31;
//      send[iSendLen++] = 0x09;
//      send[iSendLen++] = 0xF1;



    //   while(1)
       {
           iRet = dev.WriteData(send,iSendLen);
           if(KTX_SUCCESS != iRet){
                  cout <<"Write ERR="<<iRet<< endl;
                  //break;
           }

           iRecvLen = 1;
           memset(cRev,0,iRecvLen);
           iRet =dev.ReadData(cRev,iRecvLen,1000);

           iRecvLen = 100;
           iRet =dev.ReadDataEx(cRev+1,iRecvLen,1000);
           printf("Recv(len=%d): %02X  %02X  %02X  %02X  \n",
                  iRecvLen,cRev[0],cRev[1],cRev[2],cRev[3]);

           printf("Recv: %02X  %02X  %02X  %02X  %02X %02X  %02X\n",
                  cRev[4],cRev[5],cRev[6],cRev[7],cRev[8],cRev[9],cRev[10]);

           if(KTX_SUCCESS != iRet){
                  cout <<"Read ERR="<<iRet<< endl;
                  //break;
           }

           cAck[0] = 0x06;
           in=1;

           iRet = dev.WriteData(cAck,in);
           if(KTX_SUCCESS != iRet){
                  cout <<"Write ERR="<<iRet<< endl;
                  //break;
           }
       }

       //entrycard();
       //readtrack();



    return 0;
}

int test_pt115()
{
    int iRet = dev.OpenCom(0x0f01,38400,8, 0,1,0);
    if(KTX_SUCCESS != iRet){
           cout <<"ERR="<<iRet<< endl;
    }

    unsigned char send[64]={0};
    unsigned char cRev[64]={0};
    unsigned char cAck[10]={0};
    int iSendLen = 0;

     send[iSendLen++] = 0x02;
     send[iSendLen++] = 0x00;
     send[iSendLen++] = 0x02;
     send[iSendLen++] = 0x5C;
     send[iSendLen++] = 0x41;
     send[iSendLen++] = 0x1F;
     send[iSendLen++] = 0x03;


     iRet = dev.WriteData(send,iSendLen);
     if(KTX_SUCCESS != iRet){
            cout <<"Write ERR="<<iRet<< endl;
            //break;
     }

     int  iRecvLen = 100;
     iRet =dev.ReadDataEx(cRev,iRecvLen,5000);
     printf("Recv(len=%d): ", iRecvLen);
     for(int index=0; index<iRecvLen;index++)
     {
         printf("%02X  ", cRev[index]);
     }
     printf("\n");

}

void test_r10()
{
    int iRet = dev.OpenCom(0x0F02,57600,8, 0,1,0);
    if(KTX_SUCCESS != iRet){
           cout <<"ERR="<<iRet<< endl;
    }

    unsigned char send[64]={0};
    unsigned char cRev[256]={0};
    unsigned char cAck[10]={0};
    int iSendLen = 0;

    send[iSendLen++] = 0x10;
    send[iSendLen++] = 0x02;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x14;
    send[iSendLen++] = 0x00;
    send[iSendLen++] = 0x41;
    send[iSendLen++] = 0x20;
    send[iSendLen++] = 0x0B;
    send[iSendLen++] = 0x0A;
    send[iSendLen++] = 0x09;
    send[iSendLen++] = 0x1E;
    send[iSendLen++] = 0x22;
    iSendLen += 13;
    send[iSendLen++] = 0x10;
    send[iSendLen++] = 0x03;
    send[iSendLen++] = 0xB3;
    send[iSendLen++] = 0xDB;
 //10 02 00 00 00 14 00 41 20 0B 0A 09 1E 22 00 00 00 00 00 00 00 00 00 00 00 00 00 10 03 B3 DB
    iRet = dev.WriteData(send,iSendLen);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }

    int  iRecvLen = 100;
    iRet =dev.ReadDataEx(cRev,iRecvLen,500);
    printf("Recv(len=%d): ", iRecvLen);
    for(int index=0; index<iRecvLen;index++)
    {
        printf("%02X  ", cRev[index]);
    }
    printf("\n");

    memset(send, 0, 64);
    send[0] = 0x10;
    send[1] = 0x05;
    iSendLen = 2;
    iRet = dev.WriteData(send,iSendLen);
    if(KTX_SUCCESS != iRet){
           cout <<"Write ERR="<<iRet<< endl;
           //break;
    }
    iRecvLen = 100;
    iRet =dev.ReadDataEx(cRev,iRecvLen,500);
    printf("Recv(len=%d): ", iRecvLen);
    for(int index=0; index<iRecvLen;index++)
    {
        printf("%02X  ", cRev[index]);
    }
    printf("\n");



}

void test_ty()
{
    int iRet = dev.OpenCom(0x0f01,38400,8, 0,1,0);
    if(KTX_SUCCESS != iRet){
           cout <<"ERR="<<iRet<< endl;
    }

    unsigned char send[64]={0};
    unsigned char cRev[64]={0};
    int iSendLen = 0;

     send[iSendLen++] = 0x68;
     send[iSendLen++] = 0x00;
     send[iSendLen++] = 0x08;
     send[iSendLen++] = 0x58;
     send[iSendLen++] = 0x63;
     send[iSendLen++] = 0x42;
     send[iSendLen++] = 0x20;
     send[iSendLen++] = 0x4b;


     iRet = dev.WriteData(send,iSendLen);
     if(KTX_SUCCESS != iRet){
            cout <<"Write ERR="<<iRet<< endl;
            //break;
     }

     int  iRecvLen = 100;
     iRet =dev.ReadDataEx(cRev,iRecvLen,5000);
     printf("Recv(len=%d): ", iRecvLen);
     for(int index=0; index<iRecvLen;index++)
     {
         printf("%02X  ", cRev[index]);
     }
     printf("\n");
}

int main()
{
    test_ty();
    //test_3q8(4);
    //test_pt115();
    //test_r10();

    return 0;

}
