#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

/*
 * 测试有名信号量，采用fork创建父子进程，使用sem进行进程间同步
 * 
*/
using namespace std;

#define SEM_FILENAME    "test semphore iii"
sem_t *sem = NULL;
bool   quit = false;

void mysem(const char *str)
{
    int n = 0;
    sem_wait(sem);
    while('\0' != str[n])
    {
        cout<<str[n]<<endl;
        sleep(1);
        n++;
    }
    sem_post(sem);
}
/*处理子进程退出,但是必须在主进程退出之前调用*/
void child_process_exit(int type)
{
    cout<<"child process exit"<<endl;
    wait(NULL);
}

int main(int argc, char *argv[])
{
    
    int status = 0;
    int value = 0;

    sem = sem_open(SEM_FILENAME, O_CREAT | O_RDWR | O_EXCL, 0666, 1);
    if(sem == SEM_FAILED )
    {
        if(errno == EEXIST){
            sem = sem_open(SEM_FILENAME, O_RDWR, 0666, 1);
        }
        else{
            cout<<"unable to create semaphore"<<endl;
            sem_unlink(SEM_FILENAME);
            exit(-1);
        }

    }
    
    sem_getvalue(sem, &value);
    //signal(SIGCHLD, child_process_exit);
    pid_t pid =vfork();//fork（）的返回值有两个，子进程返回 0， 父进程返回子进程的
                      //进程号，进程号都是非零的正整数，所以父进程返回的值一定大于零
    if(pid < 0){
        cout<<"create fork error "<<endl; 
    }
    else if(pid==0){
        cout<<"child process pid = "<<getpid()<<endl;
        //setsid();   //new session
        //execlp("KTX_Trace_Server",NULL,NULL);
        mysem("child fork");        
        _exit(0);//不对标准I/O流进行任何操作。而exit(0)则会关闭进程的所有标准I/O流
    }
    else if( pid > 0){    
        printf("child process pid = %d, father process pid = %d\n", pid, getpid());
        wait(&status);
        mysem("father fork");      
        sem_unlink(SEM_FILENAME);
        sem_close(sem);
    }
    
    
    return 0;
}
