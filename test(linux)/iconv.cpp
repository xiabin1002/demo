#include <iostream>
#include <iconv.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int  main(int argc, int *argv[])
{ 
    string str = "asdfghjkl;正常退出/正常退出ke";
    
    int *p =NULL;
    *p = 123;
    iconv_t cd = iconv_open("gb2312", "utf-8");//IGNORE
    if(cd >=0)
    {
        char *pInStr = (char*)str.c_str();
        int iInStrLen = str.length();
        int iOutStrLen = iInStrLen*2;
        char *pOutStr = (char*)malloc(iOutStrLen);
        char *pOut = NULL;
        pOut = pOutStr;
        memset(pOutStr, 0, iOutStrLen);
        iconv(cd, &pInStr, (size_t*)&iInStrLen, &pOut, (size_t*)&iOutStrLen);
     
        cout<<"pOutStr:" <<pOutStr<<"len: "<<strlen(pOutStr)<<endl;
        free(pOutStr);
        
    }
    
    iconv_close(cd);
    
}
