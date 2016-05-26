/**
无名管道只能在具有共同祖先的进程间使用，
*/
#include <iostream>
#include <unistd.h>

using namespace std;
#define MAX_LINE     (1024)

int main(int argc, char* argv[])
{
	int n = 0;
	int fd[2];
    char line[MAX_LINE] = {0};
	pid_t pid;
	/*pipe： 创建全双工管道IO句柄 fd[0]（读句柄） fd[1]（写句柄）*/
    if(pipe(fd) == 0){


        pid = vfork();
        if(pid < 0){
            cout<<"error pipe"<<endl;
        } else if( pid == 0){
            cout<<"child process execute, pid = "<<getpid()<<endl;
            close(fd[0]);
            write(fd[1], "test pipe.",  sizeof("test pipe"));
            _exit(0);
        } else {
            cout<<"parent process execute, pid = "<<getpid()<<endl;
            close(fd[1]);
            n = read(fd[0], line, MAX_LINE);
            write(STDOUT_FILENO, line, n);

        }
    }
	return 0;
}
