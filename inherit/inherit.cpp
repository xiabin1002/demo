// inherit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <IOSTREAM>
#include <WINDOWS.H>
#include <WTYPES.H>
#include <STDARG.H>
#include <ASSERT.H>
using namespace std;
class C{

	int i;
	char *m_pSz;

public:
	C(){cout<< "construct C" <<endl;};
	C(const char *psz =NULL):m_pSz(strcpy(new char[strlen(psz? psz:NULL)+1], psz?psz:NULL)){}
	C(int I=0):i(I){}
	virtual ~C(){cout<< "destory C" <<endl;}
	


	void display1(){cout<<"c1"<<endl;}
	virtual	void display2(){cout<<"c2"<<endl;}
	virtual int sum() const{return i;}
	
};


class D : public C{

	int j;

public:
	D(int I=0, int J=0):C(I),j(J){}
	~D(){cout<< "destory D" <<endl;};

	void display1(){cout<<"d1"<<endl;}
	void display2(){cout<<"d2"<<endl;}
	
	virtual int sum() const {return C::sum() + j;}
};

void Call(C tmp)
{
	cout<<"sum = "<<tmp.sum()<<endl;
}

class CBase1
{
public:
	
	virtual void test(){cout<<"CBase1"<<endl;};
};


class CBase2
{
public:
	virtual void test(){cout<<"CBase2"<<endl;};
};

class Outer{
	class Inner1 : public CBase1
	{
	public:
		void test(){cout<<"Inner1"<<endl;}
		
	};

	class Inner2 : public CBase2
	{
		public:
		void test(){cout<<"Inner2"<<endl;}
		
	};
};



/*
void CombinationTest(Outer::Inner1 obj)
{
	obj.test();

}*/


char* str_replace(char *in, char *out, int outlen, const char *src, char *dst)
{
    char *p = in;
    unsigned int len = outlen;
	
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out))
    {
        return NULL;
    }
    if((strlen(in) == 0) || (strlen(src) == 0))
    {
        return NULL;
    }
    if(outlen <= 0)
    {
        return NULL;
    }
	
    while((*p != '\0')&&(len > 0))
    {
        int l = strlen(src);
        if(strncmp(p, src, strlen(src)))
        {
            int n = strlen(out);
            out[n] = *p;
            out[n+1] = '\0';
            p++;
            len--;
        }
        else
        {
            strcat(out, dst);
            p += strlen(src);
            len -=strlen(dst);
        }
    }
	
	
    return out;
}

int main(int argc, char* argv[])
{
	C *c = new C("qwe");
	C tmp(*c);
	D *d = new D(10, 20);
	//Call(*c);
	Call(*d);
	C *pd = new D(100,200);
	pd->display1();
	pd->display2();
	Call(*pd);
	delete pd;pd=NULL;
	delete c;pd=NULL;
	delete d;pd=NULL;
 		 
	printf("Hello World!\n");
	system("pause");
	return 0;
}

