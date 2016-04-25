#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "KTX_Trace_Client.h"

using namespace std;

#define DATA_LEN    1*1024
#define A_STRING    "CDM100::LFPGetInfo(hService=3, dwCategory=403, lpCmdData=0, dwTimeOut=0, object_name=/lfs/cdm100test/listener, RequestID=111) = 0,processid=7976,Threadid=1\
[LFS_INF_CDM_CASH_UNIT_INFO] Input Param = None"

#define B_STRING    "CDM100::LFPGetInfo(hService=3, dwCategory=403, lpCmdData=0, dwTimeOut=0, object_name=/lfs/cdm100test/listener, RequestID=116) = 0,processid=7976,Threadid=1\
[LFS_INF_CDM_CASH_UNIT_INFO] Input Param = None"	 

#define C_STRING    "KTX_CRM_SP_R10::post LFS_GETINFO_COMPLETE(1031)lpResult=0x6bc00308{RequestID=116, hResult=LFS_SUCCESS(0), dwCommandCode=403, hService=3, tsTimestamp=2016-02-03 10:53:52:000, lpBuffer=0x7fb59ee93130}\
[LFS_INF_CDM_CASH_UNIT_INFO] Output Param = \
{0,2[1,LFS_CDM_TYPEBILLCASSETTE,RETRACT,111,CNY,100,1,100,1,1,1000,0,LFS_CDM_STATCUOK,1<CASSETTE1,PD1,1,100,1,1000,LFS_CDM_STATCUOK,0>]\
[2,LFS_CDM_TYPERETRACTCASSETTE,RETRACT,111,CNY,100,1,1,1,1,1000,0,LFS_CDM_STATCUOK,1<CASSETTE4,1234,1,1,1,1000,LFS_CDM_STATCUOK,0>]\
}"	

#define D_STRING    "KTX_CRM_SP_R10::post LFS_GETINFO_COMPLETE(1031)lpResult=0x6bc00408{RequestID=112, hResult=LFS_SUCCESS(0), dwCommandCode=409, hService=3, tsTimestamp=2016-02-03 10:49:01:000, lpBuffer=0x7fb59ee930b0}\
[LFS_INF_CDM_PRESENT_STATUS] Output Param = \
 {\
    denomination<0x7fb59ee930c8>=\
    {\
        currency_id =    \
        amount = 0\
        count = 0\
        values = [0x0000]\
        cash_box = 0\
    }\
    present_state(2) = \
    extra = NULL\
 }"

#define E_STRING "KTX_CRM_SP_R10::post LFS_OPEN_COMPLETE(1025) lpResult=0x6bc00a08{hService=3, RequestID=108, hResult=LFS_SUCCESS(0), dwCommandCode=1025, tsTimestamp=2016-02-03 10:48:43:000, lpBuffer=NULL}	 "

#define PSTR(a)   a##_STRING

static KTX_Trace_Client trace[6];

void write_log(int index)
 {   
        char data_info[DATA_LEN] = {0};
        char *character[6];
        switch(index)
        {
        
        case 0:
            character[0] = A_STRING;
            break;
        case 1:
            character[1] = B_STRING;
            break;
        case 2:
            character[2] = C_STRING;
            break;
        case 3:
            character[3] = D_STRING;
            break;
        case 4:
            character[4] = E_STRING;
            break;
        default:
            character[0] = "X";
            break;
        }
        trace[index].SetTraceName("character");
       // memset(data_info, character, DATA_LEN);
        //sprintf(data_info, "client logging event number  pid=%d ... ",getpid());
        while(1)
        {
         trace[index].SendTraceMsg(character[index]);
         usleep(1000);
        }
    
    
    
}

int main()
{
    //pid_t pid;
    for(int i=0; i<5; i++)
    {
       pid_t pid = fork();
        if(pid == 0)
        {
            write_log(i);
        }
        sleep(1);
    }
    
    
    while(1)
    {
        sleep(1);
    }
    cout << "Hello World!" << endl;
    return 0;
}

