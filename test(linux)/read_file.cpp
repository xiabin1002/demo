#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string>
#include <unistd.h>
using namespace std;

//string m_strFilePath;
#define MAX_PATH 260

void delete_file(const char *dir_path)
{
    DIR *dir;
    struct dirent *dt;
    struct stat *_stat;
    struct tm *local_tm, *file_tm;
    string m_strFilePath = dir_path;
    char path_file[MAX_PATH] = {0};

    dir = opendir(m_strFilePath.c_str());
    if(NULL == dir)
    {
       printf("open dir failed! dir: %s. \n", m_strFilePath.c_str());
       return;
    }
    local_tm = localtime(&_stat->st_mtim.tv_sec);
    while(dt = readdir(dir))
    {
        if(strstr(dt->d_name,".ini")!=NULL)
        {
            memset(path_file, 0, MAX_PATH);
            snprintf(path_file, MAX_PATH, "%s//%s", dir_path,dt->d_name);
            stat(path_file, _stat);
            file_tm = gmtime(&_stat->st_mtim.tv_sec);
            printf("file name:   %s\n",dt->d_name);
            printf("Last file modification:   %s", ctime(&_stat->st_mtim.tv_sec));
            printf("Last file modification:  year %04d  day  %d  millsecond %d\n ",file_tm->tm_year+1900,  file_tm->tm_mday,
                _stat->st_mtim.tv_nsec/1000000 );

            if(_stat->st_mode == S_IFDIR)
            {
                delete_file(path_file);
            }
            else if( (local_tm->tm_yday-file_tm->tm_yday) > 1 )
            {
               remove(path_file);
            }
        }
    }

    closedir(dir);

}

void GetDefPath(string &strPath)
{
    //string strPath;
    char buf[260]={0};
    readlink( "/proc/self/exe", buf, 260 );

    strPath = buf;
    strPath = strPath.substr(0,strPath.rfind('/')+1);



}

int main()
{
     string exe;
     GetDefPath(exe);
     string path = "//home//mywork//02.SP//build-KTX_SP-Debug//bin//bv";
      delete_file(path.c_str());
      return 0;
  }
