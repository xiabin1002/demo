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

static void*  sig_thread(void *arg)
{
    sigset_t* set= (sigset_t*)arg;
    int s,sig,index=0;
    while(1)
    {
        s = sigwait(set, &sig);
        if(s == EINTR)
            continue;
        printf("Signal handling thread got signal %d\n", sig);
        //usleep(1*1000*1000);
        sigdelset(set, sig);
        pthread_sigmask(sig, set, NULL);
        printf("child fork times: %d\n", index);
        index++;
    }
}

int main(void)
{
    
    remove("/home/ktxsp/bv/SNRInfo.ini");
    //symlink("/home/ktxsp/bv/FSN/2016-04-18/17-00-08/SNRInfo.ini", "/home/ktxsp/bv/SNRInfo.ini");   
    system("cp /home/ktxsp/bv/FSN/2016-04-18/17-00-08/SNRInfo.ini /home/ktxsp/bv/SNRInfo.ini");
    char buf[256] = {0};
    readlink("/proc/self/exe", buf, 256);
    pthread_t thread_id;
    sigset_t set;
    int s,index=0;
    
    sigemptyset(&set);
    sigaddset(&set, WAIT_OBJECT_0);
    sigaddset(&set, WAIT_OBJECT_1);
    pthread_sigmask(SIG_SETMASK, &set, NULL);// SIG_BLOCK
    
    pthread_create(&thread_id, NULL, &sig_thread, &set);    
    
    for(;;){
        //raise(WAIT_OBJECT_0);
        //ouput_timer();
        sigaddset(&set, WAIT_OBJECT_0);
        sigaddset(&set, WAIT_OBJECT_1);
        pthread_sigmask(SIG_BLOCK, &set, NULL);// SIG_SETMASK
        pthread_kill(thread_id, WAIT_OBJECT_0);
        //ouput_timer();
        pthread_kill(thread_id, WAIT_OBJECT_1);
        //printf("main fork times: %d\n", index);
        index++;
        //sleep(5);
        //usleep(10*1000);
    }
    return 0;
}
