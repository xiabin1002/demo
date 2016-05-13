#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


#define     WAIT_OBJECT_0   (__SIGRTMIN+2)

void new_op(int,siginfo_t*,void*);

int main(int argc,char**argv)
{
    
    
    
    struct sigaction act;
    int sig;
    sig=WAIT_OBJECT_0;//SIGUSR1;
    union sigval mysigval;
    char data[] = {"ABCDEFGHIJK"};
    __pid_t pid = getpid();
    //mysigval.sival_ptr = data;
    mysigval.sival_int = pid;
    printf("process ID:%d\n", pid);
    
    sigemptyset(&act.sa_mask);
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=new_op;
    
    if(sigaction(sig,&act,NULL) < 0)
    {
        printf("install sigal error\n");
    }
    
    while(1)
    {
        sleep(2);
        printf("wait for the signal\n");
        sigqueue(pid, sig, mysigval);//向本进程发送信号，并传递附加信息
    }
    
}

void new_op(int signum,siginfo_t *info,void *myact)
{
    printf("receive siginfo_t  si_signo: %d\n", info->si_signo);
    printf("receive siginfo_t  si_code: %d\n", info->si_code);
    printf("receive siginfo_t  si_int: %d\n ",(int*)((*info).si_ptr));
    printf("receive signal %d\n", signum);
    //printf("%s\n ",(char*)((*info).si_ptr));
    sleep(5);
}

