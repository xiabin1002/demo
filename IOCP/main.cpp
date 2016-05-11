#include "stdafx.h"
#include "KT_RiBBON.h"

int main(int argc, char* argv[])
{
	CKT_Ribbon ribbon;
	INT iRet = ribbon.Initialize((LPCTSTR)argv[0]);

	if(SUCCES == iRet)
		ribbon.Run();

	return 0;	
}