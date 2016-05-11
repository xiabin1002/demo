#include "stdafx.h"
#include "KT_RiBBON.h"


CKT_Ribbon::CKT_Ribbon()
{
	m_AppExit = FALSE;
	g_Cfg = new CConfigure();
}

CKT_Ribbon::~CKT_Ribbon()
{
	if(g_Cfg)
		delete g_Cfg;
	m_TracrLog.CloseLog();
	
}
/**
*
*/
INT CKT_Ribbon::Initialize(LPCTSTR lpAbsolutePath)
{
	INT iRet = FAIL;

	if((iRet = g_Cfg->ReadConfigure(lpAbsolutePath)) == FAIL)
		return iRet;

	if((iRet = m_TracrLog.InitData()) == FAIL)
		return iRet;

	UINT m_listenPort = atoi(g_Cfg->GetKeyValue("ListenPort"));

	if(!m_listenPort)
	{
		printf("SOCKE listen port null.\n");
		return FAIL;
	}

	if((iRet = m_IocpServer.Initialize()) == FAIL)
		return iRet;

	m_TracrLog.LogTraceA(0, "Initialize OK");
	return iRet;
}

void CKT_Ribbon::Run()
{
	while(1)
	{
		if(m_AppExit)
			break;

		Sleep(500);
	}

}