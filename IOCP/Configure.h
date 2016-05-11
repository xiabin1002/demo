#ifndef _CONFIGURE_H
#define _CONFIGURE_H


#pragma once

#include "TraceLog.h"
#include <map>
#include <string>


class CConfigure
{
public:

	CConfigure();
	~CConfigure();

public:
	INT ReadConfigure(LPCTSTR lpAbsolutePath);
	const char* GetKeyValue(string keyWord);

private:
	
	INT InitIniKeyValue();
	VOID AnalysisLineData(const char* data);
	

private:

	struct ptrCmp
	{
		int operator()(string str1, string str2) const
		{
			return str1.compare(str2);
		}
	};

	map<string,string> m_IniKeyValue;

};

extern CConfigure* g_Cfg;

#endif