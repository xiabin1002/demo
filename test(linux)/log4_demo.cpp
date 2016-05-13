/*
 * =====================================================================================
 *
 *       Filename:  multiprocesslog.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/15/2011 02:48:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xu Zhe Ming,
 *        Company:
 *
 * =====================================================================================
 */

#include "log4cplus/fileappender.h"
#include "log4cplus/socketappender.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/layout.h"
#include "log4cplus/spi/loggingevent.h"
#include <time.h>
#include "log4cplus/configurator.h"
#include <iomanip>
#include "log4cplus/logger.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/helpers/socket.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace log4cplus;
using namespace std;
using namespace log4cplus::helpers;

//server端
int log_server(int port)
{
    //创建一个socket，绑定端口
    helpers::ServerSocket serverSocket(port);
    Logger debug_logger;
    Logger info_logger;

    //注意int会溢出
    long log_size = long(1024) * 1024 * 256;

    //初始化一个debug logger，并绑定到一个文件
   /* {
    SharedAppenderPtr pFileAppender_normal(new RollingFileAppender(("./log_file_debug") , log_size, 10));
    debug_logger = Logger::getInstance("debug_logger");
    debug_logger.addAppender(pFileAppender_normal);
    }*/
    {
    SharedAppenderPtr _append(new DailyRollingFileAppender(("./log_file_debug") ,  DAILY, true, log_size,true));
    _append->setName("debug_logger");

    string pattern = "%D{%Y-%m-%d %H:%M:%S.%q}\t %-5p\t %m\t %n";
    auto_ptr<Layout>_Layout(new PatternLayout(pattern));
    _append->setLayout(_Layout);

    debug_logger = Logger::getInstance("debug_logger");
    debug_logger.addAppender(_append);
    debug_logger.setLogLevel(ALL_LOG_LEVEL);
}

    //初始化一个info logger，并绑定到一个文件
    {
    SharedAppenderPtr pFileAppender_normal(new RollingFileAppender(("./log_file_info") , log_size, 10));
    info_logger = Logger::getInstance("info_logger");
    info_logger.addAppender(pFileAppender_normal);
    }


    //初始化其他的logger，如warn, error, fatal
    //...

    while(1)
    {
    //accept
    helpers::Socket clientsock = serverSocket.accept();
    SocketBuffer msgSizeBuffer(sizeof(unsigned int));
    if(!clientsock.read(msgSizeBuffer))
    {
        return 0;
    }
    unsigned int msgSize = msgSizeBuffer.readInt();
    SocketBuffer buffer(msgSize);
    //读取日志消息到buffer
    if(!clientsock.read(buffer))
    {
        return 0;
    }

    //转化成event
    spi::InternalLoggingEvent event = readFromBuffer(buffer);
    int level = event.getLogLevel();
    //判断日志的level
    if(level == DEBUG_LOG_LEVEL)
    {
        debug_logger.callAppenders(event);
    }
    else if(level == INFO_LOG_LEVEL)
    {
        info_logger.callAppenders(event);
    }
    //...
    }

    return 0;
}

//client端
int log_client(string server_ip, int server_port, int index)
{
    SharedAppenderPtr _append(new SocketAppender(server_ip, server_port, "ServerName"));
    Logger::getRoot().addAppender(_append);
    char data_info[1024] = {0};
    char character = 0;
    switch(index)
    {
    case 0:
        character = 'A';
        break;
    case 1:
        character = 'B';
        break;
    case 2:
        character = 'C';
        break;
    case 3:
        character = 'D';
        break;
    case 4:
        character = 'E';
        break;
    default:
        character = 'X';
        break;
    }
    memset(data_info, character, 1024);
    //sprintf(data_info, "client logging event number  pid=%d ... ",getpid());
    while(1)
    {
    int rand_num = rand();
    int remainder = rand_num % 2;
//    if (remainder == 0)
//        LOG4CPLUS_INFO(Logger::getRoot(), data_info);
//   else
       LOG4CPLUS_DEBUG(Logger::getRoot(), data_info);

    //sleep(1);
    }
}


int main()
{

 

    pid_t pid = fork();

    //child, let's run a log server process
    if(pid == 0)
    {
        printf("run a log server process pis=%d.\n",getpid());
        log_server(20000);
    }
    //parent, let's fork some more processes to write logs
    //else
    {
        for(int i = 0; i < 5; i++)
        {
            pid = fork();
            //child, let's run a log client process
            if(pid == 0)
            {
                printf("run a log client process pid=%d.\n", getpid());
                log_client("localhost", 20000, i);
            }
        }
    }

    while(1)
    {
        sleep(1);
    }

    return 0;
}
