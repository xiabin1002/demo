#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

//#define    M_SIGNAL_EXIT     SIGUSR1 +1
#define     WAIT_OBJECT_0   (__SIGRTMIN+2)
#define     WAIT_OBJECT_1   (__SIGRTMIN+3)
#define     WAIT_OBJECT_2   (__SIGRTMIN+4)

void uinit_timer()
{
    struct itimerval value, ovalue;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);
}

void test_signal(int type)
{
    switch (type) {
    case WAIT_OBJECT_0:
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
int main(int argc, char* argv[])
{
    int i = 0;
    printf("sig_rec argc=%d\n", argc);
     for(i=0; i<argc; i++)
	{
        printf("sig_rec param[%d]: %s\n",i, argv[i]);
	}
     int pid = atoi(argv[0]);
    printf("sig_rec get father pid %d \n",pid);
    printf("sig_rec process id is %d \n",getpid());
   signal(WAIT_OBJECT_2, test_signal);


    for(;;){
        kill(pid, WAIT_OBJECT_1);
        sleep(1);
        printf("send WAIT_OBJECT_1\n");
    }
    return 0;
}

