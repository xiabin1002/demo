#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>


//#define    M_SIGNAL_EXIT     SIGUSR1 +1
#define     WAIT_OBJECT_0   (__SIGRTMIN+2)
#define     WAIT_OBJECT_1   (__SIGRTMIN+3)
#define     WAIT_OBJECT_2   (__SIGRTMIN+4)
#define     MY_SIGNAL       sysv_signal
void uinit_timer()
{
    struct itimerval value, ovalue;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);
}
void init_timer()
{
    struct itimerval value, ovalue;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);
}
void test_signal(int type)
{
    switch (type) {
    case WAIT_OBJECT_0:
        sleep(5);
        printf("WAIT_OBJECT_0\n");       
        break;
    case WAIT_OBJECT_1:
        printf("WAIT_OBJECT_1\n");
        break;
    case WAIT_OBJECT_2:
        printf("WAIT_OBJECT_2\n");
        break;
    case SIGHUP:
        printf("Get a signal -- SIGHUP \n");
        break;
    case SIGINT:
        printf("Get a signal -- SIGINT \n");
        break;
    case SIGQUIT:
        printf("Get a signal -- SIGQUIT \n");
        break;
    case SIGALRM:
        printf("Get a signal -- SIGALRM \n");
        break;
    default:
        break;
    }
}

void create_signal()
{
    MY_SIGNAL(SIGHUP, test_signal);
    MY_SIGNAL(SIGINT, test_signal);
    MY_SIGNAL(SIGQUIT, test_signal);
    MY_SIGNAL(SIGALRM, test_signal);
    signal(WAIT_OBJECT_0, test_signal);
    MY_SIGNAL(WAIT_OBJECT_1, test_signal);
    MY_SIGNAL(WAIT_OBJECT_2, test_signal);
    
    //    int oflags;
    //    //1 从设备驱动发出的信号被本进程接收
    //    fcntl(WAIT_OBJECT_0, F_SETOWN, getpid());
    
    //    //2 设为异步通知模式
    //    oflags = fcntl(WAIT_OBJECT_0, F_GETFL);
    //    fcntl(WAIT_OBJECT_0, F_SETFL, oflags | FASYNC);
    
    
}

void ouput_timer()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    printf("current second time: %d\n ", tv.tv_sec);
    printf("current microsecond time: %d\n", tv.tv_usec);
}

void work_thread()
{
    while(1)
    {
        ouput_timer();
        sysv_signal(WAIT_OBJECT_0);
        ouput_timer();
        printf("\n\n\n\n");
        sleep(5);
    }
}
int main(void)
{
    char buf[256] = {0};
    readlink("/proc/self/exe", buf, 256);
    
    pid_t pid_child = vfork();
    if(pid_child==0)
    {
        printf("child pid= %d\n", getpid());
        
    }
    
    create_signal();
    
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, work_thread, NULL);
    
    
    /*    init_timer();
   int father_pid   = getpid();
    printf("father process id is %d \n",father_pid);
    //char *argv[ ] ={{"//home//mywork//test_tool//signal//sig_recv.out"}, {father_pid}, {(char*)0}};
    char pid[8]={0};
    sprintf(pid, "%d",father_pid );
    __pid_t child_pid   = vfork();
    
    if(child_pid==0)
    {
        printf("child pid= %d\n", getpid());
       int ret =  execl("//home//mywork//test_tool//signal//sig_recv.out",pid, NULL);
       printf("execl : %d \n",ret);
       exit(1);
    }
    printf("child process id : %d \n",child_pid);
*/
    
    
    
    
    for(;;){
        
        ouput_timer();
        raise(WAIT_OBJECT_0);
        ouput_timer();
        //        printf("\n\n\n\n");
        usleep(5*1000*1000);
        //        kill(0, WAIT_OBJECT_1);
        //        sleep(5);
        //     uinit_timer();
        //     kill(child_pid, WAIT_OBJECT_2);
        //    sleep(5);
    }
    return 0;
}
