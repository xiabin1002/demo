#include "stdafx.h"

#include "Configure.h"
#include <fstream>
#include <string.h>

#define  CONFIGURE_FILE_NAME	".\\Configure.ini"

CConfigure* g_Cfg = NULL;

CConfigure::CConfigure()
{
}


CConfigure::~CConfigure()
{
}

INT CConfigure::ReadConfigure(LPCTSTR lpAbsolutePath)
{
	INT bRet = InitIniKeyValue();
	
	return bRet;
}

INT CConfigure::InitIniKeyValue()
{
	INT bRet = FAIL;
	string fileNmae(CONFIGURE_FILE_NAME);
	char buff[MAX_DATA_LEN] = {0};

	fstream fs;
	fs.open(fileNmae, fstream::in | fstream::binary);
	if (!fs.is_open())
	{
		printf("InitIniKeyValue fail Reason: cannot open %s.\n", CONFIGURE_FILE_NAME);
		bRet = FAIL; 
	}
	else
	{
		string strLine;
		while (fs.getline(buff, strLine.max_size()))
		{
			if(buff[strlen(buff)-1] == '\r')
				buff[strlen(buff)-1] = '\0';
			AnalysisLineData(buff);
			memset(buff, 0, sizeof(char)*MAX_DATA_LEN);
		}

		bRet = SUCCES;
		printf("InitIniKeyValue successful.\n");
	}

	return bRet;
}
/**
*分析读取的一行数据保存到map
*/
VOID CConfigure::AnalysisLineData(const char* data)
{
	
	if((NULL == data) || (0 == strlen(data)))
		return;
	
	if( (0== strcmp(data, "\n")) || (0==strcmp(data, "\r")) || *data=='#' || *data==';')
		return;

	const char* delim = "=";
	char* key = NULL;
	char* value = NULL;
	char* context = NULL;

	key = strtok_s((char*)data, delim, &context);
	value=strtok_s(NULL, delim, &context);
	if(*value=='\r')
		value = "";
	m_IniKeyValue.insert(make_pair(key, value));
	
}

const char* CConfigure::GetKeyValue(string keyWord)
{
	string key;
	const char* pRetVal = NULL;
	
	map<string, string>::iterator it = m_IniKeyValue.begin();

	while(it!=m_IniKeyValue.end())
	{
		key = it->first;
		if(key == keyWord){
			pRetVal = it->second.c_str();
			break;
		}
			
		it++;
	}

	return pRetVal;
}
