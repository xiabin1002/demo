#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define     MEMORY_SIZE     (4*1024)
#define     MEMORY_ADDR    (0xe31ff000)
#define     MEMORY_KEY      (0xe30ff000)


int main(int argc,char **argv)
{
    int shmid = 0;
    void *shmptr = NULL ;
    key_t   shmkey;
		/*ftok: ��ȡIPCͨѶ ����Ϣ���С��ź����͹����ڴ棩 ʱָ��һ��IDֵ����Ҫ�ڲ�ͬ���̼乲���ڴ�ʱʹ��*/
   if((shmkey = ftok("/dev/null", 1)) == (key_t)-1){
       perror("create ftok error");exit(1);
   }
		/*shmget: ��ȡһ������洢�ı�ʾ��*/
    shmid = shmget(shmkey, MEMORY_SIZE, 0600|IPC_CREAT|IPC_EXCL);
    if(shmid == -1){
        //perror("create share memory error");
        if(errno == EEXIST){
            printf("%s\n", strerror(errno));
            shmid = shmget(shmkey, MEMORY_SIZE, 0600);
        }
        else{
            printf("errno: %d, reason: %s.\n", errno, strerror(errno));
            exit(1);
        }
    }

    printf("shared memory shmid: %d.\n", shmid);

    if((shmptr =  shmat(shmid, (const void*)MEMORY_ADDR,0))  == (void*)-1){
        perror("attache share memory address fail");
        exit(1);
    }
    printf("share memory address: %08x\n",shmptr);
    system("ipcs -m");

    shmctl(shmid, IPC_RMID, NULL);
    shmdt( (const void*)shmptr);

    return 0;
}

