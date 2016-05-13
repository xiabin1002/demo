#include <iosfwd>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

typedef struct {
    unsigned short	HeadStart[4];
    unsigned short	HeadString[6];
    unsigned int	    Counter;
    unsigned short	HeadEnd[4];
} TFsnHeader, *LPTFsnHeader;

TFsnHeader m_tFsnHeader = {0};

void	InitHeader()
{
    memset(&m_tFsnHeader, 0, sizeof(TFsnHeader));
    m_tFsnHeader.HeadStart[0] = 20;
    m_tFsnHeader.HeadStart[1] = 10;
    m_tFsnHeader.HeadStart[2] = 7;
    m_tFsnHeader.HeadStart[3] = 26;

    m_tFsnHeader.HeadString[0]= 0;
    m_tFsnHeader.HeadString[1]= 1;
    m_tFsnHeader.HeadString[2]= 0x2E;
    m_tFsnHeader.HeadString[3]= 'S';
    m_tFsnHeader.HeadString[4]= 'N';
    m_tFsnHeader.HeadString[5]= 'o';

    m_tFsnHeader.Counter=8;

    m_tFsnHeader.HeadEnd[0]=0;
    m_tFsnHeader.HeadEnd[1]=1;
    m_tFsnHeader.HeadEnd[2]=2;
    m_tFsnHeader.HeadEnd[3]=3;
}

int main(int argc, char *argv[])
{

    std::fstream file;
    InitHeader();
    file.open("./tmp.txt", std::fstream::in | fstream::out | ios::binary | ios::app);//, ios::in | ios::out | ios::binary
    if( !file.is_open())
    {
        return -1;
    }

    file.seekg(0, ios::end);
    int size = file.tellg();

    if(size==0 || (size-1)<sizeof(TFsnHeader))
    {
        file.seekg(0, ios::beg);
        //file.read((char*)&m_tFsnHeader,sizeof(TFsnHeader));
        InitHeader();
        file.write((char*)&m_tFsnHeader,sizeof(TFsnHeader));
    }
    else
    {
        file.seekg(0, ios::beg);
        file.read((char*)&m_tFsnHeader,sizeof(TFsnHeader));
    }

    file.close();
    file.open("./tmp.txt", std::fstream::in | fstream::out);
    m_tFsnHeader.Counter++;
    file.seekg(0, std::ios::beg);
    file.write((char*)&m_tFsnHeader,sizeof(TFsnHeader));

    file.close();

    FILE* fp = fopen("./tmp.FSN", "w");
    if(!fp)
        return 0;
    assert ( 0 == fseek(fp, 0, SEEK_END));
    unsigned int   usize = ftell(fp);
    if(usize < sizeof(TFsnHeader))
    {
        InitHeader();
    }
    else
    {
        fseek(fp, 0, SEEK_SET);

        fread((void*)&m_tFsnHeader, 1,sizeof(TFsnHeader), fp);
    }
    usize = sizeof(TFsnHeader);
    usize = sizeof(m_tFsnHeader.Counter);
    usize = sizeof(m_tFsnHeader.HeadStart);
    usize = sizeof(m_tFsnHeader.HeadEnd);
    usize = sizeof(m_tFsnHeader.HeadString);

    m_tFsnHeader.Counter =m_tFsnHeader.Counter + 6;

    fseek(fp, 0L, SEEK_SET);
    fwrite((void*)&m_tFsnHeader, sizeof(TFsnHeader), sizeof(char), fp);
    cout<<usize<<endl;
    fclose(fp);

    return 0;
}



