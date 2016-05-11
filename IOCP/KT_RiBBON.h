#ifndef _RIBBON_H
#define _RIBBON_H

#pragma once

#include "IOCPServer.h"
#include "Configure.h"
#include "TraceLog.h"


class CKT_Ribbon
{
public:
	CKT_Ribbon();
	~CKT_Ribbon();

public:
	BOOL Initialize(LPCTSTR lpAbsolutePath);
	void Run();


protected:


private:
	
	CIOCPServer		m_IocpServer;
	CTraceLog		m_TracrLog;
	BOOL			m_AppExit;

};

#endif