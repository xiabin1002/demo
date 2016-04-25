// InterlockedCompareExchange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int mem=0,with=0,cmp =0;
	InterlockedCompareExchange(mem, with, cmp);
	printf("Hello World!\n");
	return 0;
}

