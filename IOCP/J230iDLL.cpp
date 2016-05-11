#include "StdAfx.h"
#include "J230iDLL.h"
#include "J230/J230i.h"


#define ERR_TP_OK						(0)
#define	ERR_TP_API_NOT_SUPPORT			(98)

CJ230iDLL::CJ230iDLL(void)
{
	m_hLib = NULL;
	m_LoadStatus = TP_DLL_NOT_LOADED;
	m_Status = ERR_TP_OK;
	m_bOpened = FALSE;
}

CJ230iDLL::~CJ230iDLL(void)
{
	MyFreeLibrary();
}

// Get a handle to the DLL module.
int CJ230iDLL::MyLoadLibrary(CHAR *pDllName)
{
	if (m_hLib == NULL)
	{
		m_hLib = LoadLibrary(pDllName);
		m_LoadStatus = GetLastError();
	}

	if ( m_hLib != NULL ) return TRUE;

	return FALSE;
}

int CJ230iDLL::MyFreeLibrary( )
{
	if (m_hLib)
	{
		FreeLibrary(m_hLib);
	}
	return TRUE;
}

int CJ230iDLL::MyCheckLibrary( BOOL bLoad )
{
	int iStatus = ERR_TP_OK;
	if (m_hLib == NULL)
	{
		if ( bLoad )
		{
			if (MyLoadLibrary("J230i.DLL") == TRUE)
			{
				return iStatus;
			}
			
		}
		if ( m_hLib == NULL )
		{
			iStatus = TP_DLL_NOT_LOADED;	//ERR_TP_API_NOT_SUPPORT;
		}
	}

	return iStatus;
}

BOOL CJ230iDLL::IsOpened()
{
	return (m_bOpened);
}

INT CJ230iDLL::SetLogPathFile(char *pLogFile)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetLogPathFile fnDll;
		fnDll = (pfnSetLogPathFile) GetProcAddress(m_hLib, "SetLogPathFile");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pLogFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetLogPathFileMonth(char *pLogPath, char *pLogFile, int nMonth)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetLogPathFileMonth fnDll;
		fnDll = (pfnSetLogPathFileMonth) GetProcAddress(m_hLib, "SetLogPathFileMonth");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pLogPath, pLogFile, nMonth);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

// ---------------------------
// DEVICE INFO. SETTING, SEARCH, OPEN, CLOSE
// ---------------------------

INT CJ230iDLL::GetTpclType(int *nType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetTpclType fnDll;
		fnDll = (pfnGetTpclType) GetProcAddress(m_hLib, "GetTpclType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetOpenType(int OpenType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetOpenType fnDll;
		fnDll = (pfnSetOpenType) GetProcAddress(m_hLib, "SetOpenType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(OpenType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRetryTimes(int nTimes)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRetryTimes fnDll;
		fnDll = (pfnSetRetryTimes) GetProcAddress(m_hLib, "SetRetryTimes");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nTimes);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetDescription(char *pDescription)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetDescription fnDll;
		fnDll = (pfnSetDescription) GetProcAddress(m_hLib, "SetDescription");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pDescription);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetConnectPort(int DevicePort)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetConnectPort fnDll;
		fnDll = (pfnSetConnectPort) GetProcAddress(m_hLib, "SetConnectPort");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(DevicePort);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::ListDevices(DWORD *pArg1, char *pArg2, DWORD pArg3)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnListDevices fnDll;
		fnDll = (pfnListDevices) GetProcAddress(m_hLib, "ListDevices");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pArg1, pArg2, pArg3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::OpenDevice(char *pName, int iPortNum)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnOpenDevice fnDll;
		fnDll = (pfnOpenDevice) GetProcAddress(m_hLib, "OpenDevice");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pName, iPortNum);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::OpenDeviceEx(char *pName, DWORD dwFlags)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnOpenDeviceEx fnDll;
		fnDll = (pfnOpenDeviceEx) GetProcAddress(m_hLib, "OpenDeviceEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pName, dwFlags);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CloseDevice(int iDeviceType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCloseDevice fnDll;
		fnDll = (pfnCloseDevice) GetProcAddress(m_hLib, "CloseDevice");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iDeviceType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::TP9_FreeLibrary(int nType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnTP9_FreeLibrary fnDll;
		fnDll = (pfnTP9_FreeLibrary) GetProcAddress(m_hLib, "TP9_FreeLibrary");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetConnectedDevices(DWORD dwDevice, DWORD *pdwCount )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetConnectedDevices fnDll;
		fnDll = (pfnGetConnectedDevices) GetProcAddress(m_hLib, "GetConnectedDevices");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(dwDevice, pdwCount);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetDeviceInformation(DWORD dwDevice, DWORD dwIndex, BYTE *pDesc, BYTE *pSerial)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetDeviceInformation fnDll;
		fnDll = (pfnGetDeviceInformation) GetProcAddress(m_hLib, "GetDeviceInformation");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(dwDevice, dwIndex, pDesc, pSerial);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetNetworkBoard(int *pCount, LPBYTE pConfig)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetNetworkBoard fnDll;
		fnDll = (pfnGetNetworkBoard) GetProcAddress(m_hLib, "GetNetworkBoard");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pCount, pConfig);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetNetworkBoard(LPBYTE pConfig)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetNetworkBoard fnDll;
		fnDll = (pfnSetNetworkBoard) GetProcAddress(m_hLib, "SetNetworkBoard");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pConfig);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// DEVICE RESET, Get Firmware/RF Version
// ---------------------------
INT CJ230iDLL::ResetDevice()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnResetDevice fnDll;
		fnDll = (pfnResetDevice) GetProcAddress(m_hLib, "ResetDevice");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Get_PrinterInfo(char*InfoBuffer)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_PrinterInfo fnDll;
		fnDll = (pfnGet_PrinterInfo) GetProcAddress(m_hLib, "Get_PrinterInfo");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(InfoBuffer);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Get_PrinterInfoEx(char *pVersion, int *pType, int *pModel)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_PrinterInfoEx fnDll;
		fnDll = (pfnGet_PrinterInfoEx) GetProcAddress(m_hLib, "Get_PrinterInfoEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pVersion, pType, pModel);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Get_ModuleInfo(char ModuleType, char *InfoBuffer)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_ModuleInfo fnDll;
		fnDll = (pfnGet_ModuleInfo) GetProcAddress(m_hLib, "Get_ModuleInfo");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(ModuleType, InfoBuffer);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// GET STATUS/MESSAGE, CLEAR ERROR
// ---------------------------
INT CJ230iDLL::Get_Status(char* st0, char *st1)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_Status fnDll;
		fnDll = (pfnGet_Status) GetProcAddress(m_hLib, "Get_Status");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(st0, st1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Get_StatusEx(char* st0, char *st1)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_StatusEx fnDll;
		fnDll = (pfnGet_StatusEx) GetProcAddress(m_hLib, "Get_StatusEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(st0, st1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetStatusCode(int *pStatus)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetStatusCode fnDll;
		fnDll = (pfnGetStatusCode) GetProcAddress(m_hLib, "GetStatusCode");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DeviceErrorClear()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDeviceErrorClear fnDll;
		fnDll = (pfnDeviceErrorClear) GetProcAddress(m_hLib, "DeviceErrorClear");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Set_LanguageID(WORD nLangID)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSet_LanguageID fnDll;
		fnDll = (pfnSet_LanguageID) GetProcAddress(m_hLib, "Set_LanguageID");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nLangID);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Get_StatusMessage(int nError, int nType, char *pMessage)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGet_StatusMessage fnDll;
		fnDll = (pfnGet_StatusMessage) GetProcAddress(m_hLib, "Get_StatusMessage");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nError, nType, pMessage);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// CARD CONTROL (CHECK, INSERT, EJECT, FLIP)
// ---------------------------
INT CJ230iDLL::CheckFeeder(int *pStatus)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckFeeder fnDll;
		fnDll = (pfnCheckFeeder) GetProcAddress(m_hLib, "CheckFeeder");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_Insert()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_Insert fnDll;
		fnDll = (pfnCard_Insert) GetProcAddress(m_hLib, "Card_Insert");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_InsertEx(int nOption)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_InsertEx fnDll;
		fnDll = (pfnCard_InsertEx) GetProcAddress(m_hLib, "Card_InsertEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nOption);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_Eject(int cmd)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_Eject fnDll;
		fnDll = (pfnCard_Eject) GetProcAddress(m_hLib, "Card_Eject");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cmd);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_EjectEx(int nOption)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_EjectEx fnDll;
		fnDll = (pfnCard_EjectEx) GetProcAddress(m_hLib, "Card_EjectEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nOption);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_Flip()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_Flip fnDll;
		fnDll = (pfnCard_Flip) GetProcAddress(m_hLib, "Card_Flip");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_MoveFlipperToPrinter()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_MoveFlipperToPrinter fnDll;
		fnDll = (pfnCard_MoveFlipperToPrinter) GetProcAddress(m_hLib, "Card_MoveFlipperToPrinter");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Card_Reject(int p1 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCard_Reject fnDll;
		fnDll = (pfnCard_Reject) GetProcAddress(m_hLib, "Card_Reject");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckRibbon(int *nRibbon)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckRibbon fnDll;
		fnDll = (pfnCheckRibbon) GetProcAddress(m_hLib, "CheckRibbon");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nRibbon);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckRibbonEx(int *pRibbon, int *pRfRibbon)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckRibbonEx fnDll;
		fnDll = (pfnCheckRibbonEx) GetProcAddress(m_hLib, "CheckRibbonEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pRibbon, pRfRibbon);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonSync()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonSync fnDll;
		fnDll = (pfnSetRibbonSync) GetProcAddress(m_hLib, "SetRibbonSync");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonSyncEx(int p1)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonSyncEx fnDll;
		fnDll = (pfnSetRibbonSyncEx) GetProcAddress(m_hLib, "SetRibbonSyncEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckRibbonCount(int *pCount)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckRibbonCount fnDll;
		fnDll = (pfnCheckRibbonCount) GetProcAddress(m_hLib, "CheckRibbonCount");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pCount);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// 프린터의 인쇄 설정 (제어)
// ---------------------------
INT CJ230iDLL::GetRibbonSensor(int *nSensor )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonSensor fnDll;
		fnDll = (pfnGetRibbonSensor) GetProcAddress(m_hLib, "GetRibbonSensor");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nSensor);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetRibbonSensorEx(int *pSensor, int *pSensor2)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonSensorEx fnDll;
		fnDll = (pfnGetRibbonSensorEx) GetProcAddress(m_hLib, "GetRibbonSensorEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pSensor, pSensor2);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetRibbonInfo(int nType, char *pData, int *pLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonInfo fnDll;
		fnDll = (pfnGetRibbonInfo) GetProcAddress(m_hLib, "GetRibbonInfo");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType, pData, pLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetRibbonInfoEx(int nType, int *pTagRibbon, int *pTagCount)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonInfoEx fnDll;
		fnDll = (pfnGetRibbonInfoEx) GetProcAddress(m_hLib, "GetRibbonInfoEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType, pTagRibbon, pTagCount);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetMACAddress(BYTE *pAddress)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetMACAddress fnDll;
		fnDll = (pfnGetMACAddress) GetProcAddress(m_hLib, "GetMACAddress");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pAddress);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetParameters(int nItem, char *pData, int *pLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetParameters fnDll;
		fnDll = (pfnGetParameters) GetProcAddress(m_hLib, "GetParameters");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( nItem, pData, pLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetParametersEx(int p1, int *pValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetParametersEx fnDll;
		fnDll = (pfnGetParametersEx) GetProcAddress(m_hLib, "GetParametersEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, pValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetParametersEx(int p1, int p2)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetParametersEx fnDll;
		fnDll = (pfnSetParametersEx) GetProcAddress(m_hLib, "SetParametersEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( p1, p2);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetTPHResistance(int nResistance)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetTPHResistance fnDll;
		fnDll = (pfnSetTPHResistance) GetProcAddress(m_hLib, "SetTPHResistance");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nResistance);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::AdjustIntensity(int nColor, int nIntensity)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnAdjustIntensity fnDll;
		fnDll = (pfnAdjustIntensity) GetProcAddress(m_hLib, "AdjustIntensity");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nColor, nIntensity);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetCardInputDirection(int nDir)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetCardInputDirection fnDll;
		fnDll = (pfnSetCardInputDirection) GetProcAddress(m_hLib, "SetCardInputDirection");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDir);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonType(int nRibbon , int nHalfStart, int nHalfWidth)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonType fnDll;
		fnDll = (pfnSetRibbonType) GetProcAddress(m_hLib, "SetRibbonType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nRibbon , nHalfStart, nHalfWidth);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonTypeEx(int p1, int p2)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonTypeEx fnDll;
		fnDll = (pfnSetRibbonTypeEx) GetProcAddress(m_hLib, "SetRibbonTypeEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::OffsetXaxisPrintStartPosition(int nXstart, int nXend)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnOffsetXaxisPrintStartPosition fnDll;
		fnDll = (pfnOffsetXaxisPrintStartPosition) GetProcAddress(m_hLib, "OffsetXaxisPrintStartPosition");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nXstart, nXend);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::OffsetYaxisPrintStartPosition(int nYstart)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnOffsetYaxisPrintStartPosition fnDll;
		fnDll = (pfnOffsetYaxisPrintStartPosition) GetProcAddress(m_hLib, "OffsetYaxisPrintStartPosition");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nYstart);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::PrintPintAdjust(int nOffset)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnPrintPintAdjust fnDll;
		fnDll = (pfnPrintPintAdjust) GetProcAddress(m_hLib, "PrintPintAdjust");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nOffset);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetMonoPrintMode(int nMode)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetMonoPrintMode fnDll;
		fnDll = (pfnSetMonoPrintMode) GetProcAddress(m_hLib, "SetMonoPrintMode");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetCardInputOption(int nMode)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetCardInputOption fnDll;
		fnDll = (pfnSetCardInputOption) GetProcAddress(m_hLib, "SetCardInputOption");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetPrintCount(DWORD *pCount)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetPrintCount fnDll;
		fnDll = (pfnGetPrintCount) GetProcAddress(m_hLib, "GetPrintCount");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pCount);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetProduction(char *pManufacturer, char *pDescription, char *pSerialNumber)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetProduction fnDll;
		fnDll = (pfnGetProduction) GetProcAddress(m_hLib, "GetProduction");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pManufacturer, pDescription, pSerialNumber);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetProduction(char *pManufacturer, char *pDescription, char *pSerialNumber)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetProduction fnDll;
		fnDll = (pfnSetProduction) GetProcAddress(m_hLib, "SetProduction");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pManufacturer, pDescription, pSerialNumber);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetProductSerialNo(char *pSerialNumber)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetProductSerialNo fnDll;
		fnDll = (pfnGetProductSerialNo) GetProcAddress(m_hLib, "GetProductSerialNo");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pSerialNumber);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetProductSerialNo(char *pSerialNumber)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetProductSerialNo fnDll;
		fnDll = (pfnSetProductSerialNo) GetProcAddress(m_hLib, "SetProductSerialNo");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pSerialNumber);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetLCDContrast(int nValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetLCDContrast fnDll;
		fnDll = (pfnSetLCDContrast) GetProcAddress(m_hLib, "SetLCDContrast");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetLCDContrast(int *pnValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetLCDContrast fnDll;
		fnDll = (pfnGetLCDContrast) GetProcAddress(m_hLib, "GetLCDContrast");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pnValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonSensorADC(int nValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonSensorADC fnDll;
		fnDll = (pfnSetRibbonSensorADC) GetProcAddress(m_hLib, "SetRibbonSensorADC");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetRibbonSensorADC(int *pnValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonSensorADC fnDll;
		fnDll = (pfnGetRibbonSensorADC) GetProcAddress(m_hLib, "GetRibbonSensorADC");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pnValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonSensor()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonSensor fnDll;
		fnDll = (pfnSetRibbonSensor) GetProcAddress(m_hLib, "SetRibbonSensor");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetRibbonMotorDuty(int *pnValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRibbonMotorDuty fnDll;
		fnDll = (pfnGetRibbonMotorDuty) GetProcAddress(m_hLib, "GetRibbonMotorDuty");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pnValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonMotorDuty(int nValue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonMotorDuty fnDll;
		fnDll = (pfnSetRibbonMotorDuty) GetProcAddress(m_hLib, "SetRibbonMotorDuty");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nValue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetRibbonSyncOption(int nType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetRibbonSyncOption fnDll;
		fnDll = (pfnSetRibbonSyncOption) GetProcAddress(m_hLib, "SetRibbonSyncOption");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetCardReadyPosition(int nType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetCardReadyPosition fnDll;
		fnDll = (pfnSetCardReadyPosition) GetProcAddress(m_hLib, "SetCardReadyPosition");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetCardControlTime(int *pEjectTime, int *pInsertTime)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetCardControlTime fnDll;
		fnDll = (pfnGetCardControlTime) GetProcAddress(m_hLib, "GetCardControlTime");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pEjectTime, pInsertTime);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetCardControlTime(int  nEjectTime, int nInsertTime)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetCardControlTime fnDll;
		fnDll = (pfnSetCardControlTime) GetProcAddress(m_hLib, "SetCardControlTime");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nEjectTime, nInsertTime);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetModelNation(int *pModelType, int *pOemType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetModelNation fnDll;
		fnDll = (pfnGetModelNation) GetProcAddress(m_hLib, "GetModelNation");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pModelType, pOemType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CleaningMode()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCleaningMode fnDll;
		fnDll = (pfnCleaningMode) GetProcAddress(m_hLib, "CleaningMode");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SelfTestMode(int  nMode)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSelfTestMode fnDll;
		fnDll = (pfnSelfTestMode) GetProcAddress(m_hLib, "SelfTestMode");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::ChangePassword(int iType, char *pOldPassword, char *pNewPassword)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnChangePassword fnDll;
		fnDll = (pfnChangePassword) GetProcAddress(m_hLib, "ChangePassword");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, pOldPassword, pNewPassword);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::LockPrinter(int iType, char *pPassword)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnLockPrinter fnDll;
		fnDll = (pfnLockPrinter) GetProcAddress(m_hLib, "LockPrinter");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, pPassword);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetEncryption(int iType, LPBYTE pKeyData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetEncryption fnDll;
		fnDll = (pfnSetEncryption) GetProcAddress(m_hLib, "SetEncryption");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, pKeyData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::SetDigitalPotentiometer(int type, int value)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetDigitalPotentiometer fnDll;
		fnDll = (pfnSetDigitalPotentiometer) GetProcAddress(m_hLib, "SetDigitalPotentiometer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( type, value);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::GetDigitalPotentiometer(int type, int *pvalue)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetDigitalPotentiometer fnDll;
		fnDll = (pfnGetDigitalPotentiometer) GetProcAddress(m_hLib, "GetDigitalPotentiometer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(type, pvalue);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR DOWNLOAD
// ---------------------------
INT CJ230iDLL::DownloadFirmware(char *pFile)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFirmware fnDll;
		fnDll = (pfnDownloadFirmware) GetProcAddress(m_hLib, "DownloadFirmware");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWFile(char *pFile)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWFile fnDll;
		fnDll = (pfnDownloadFWFile) GetProcAddress(m_hLib, "DownloadFWFile");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWErase()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWErase fnDll;
		fnDll = (pfnDownloadFWErase) GetProcAddress(m_hLib, "DownloadFWErase");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWDataLoad()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWDataLoad fnDll;
		fnDll = (pfnDownloadFWDataLoad) GetProcAddress(m_hLib, "DownloadFWDataLoad");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWVerify()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWVerify fnDll;
		fnDll = (pfnDownloadFWVerify) GetProcAddress(m_hLib, "DownloadFWVerify");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWReset(int nType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWReset fnDll;
		fnDll = (pfnDownloadFWReset) GetProcAddress(m_hLib, "DownloadFWReset");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadFWStatus(int *pStep, int *pStatus)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadFWStatus fnDll;
		fnDll = (pfnDownloadFWStatus) GetProcAddress(m_hLib, "DownloadFWStatus");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStep, pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DownloadStatus(int *pStep, int *pStatus)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDownloadStatus fnDll;
		fnDll = (pfnDownloadStatus) GetProcAddress(m_hLib, "DownloadStatus");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStep, pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR BUZZER
// ---------------------------
INT CJ230iDLL::Buzzer(BYTE byCount, int iOntime, int iOfftime)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnBuzzer fnDll;
		fnDll = (pfnBuzzer) GetProcAddress(m_hLib, "Buzzer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(byCount, iOntime, iOfftime);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR LCD CONTROL/DISPLAY
// ---------------------------
INT CJ230iDLL::LCD_DISPLAY(BYTE byMode, BYTE *byData, int nDataLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnLCD_DISPLAY fnDll;
		fnDll = (pfnLCD_DISPLAY) GetProcAddress(m_hLib, "LCD_DISPLAY");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(byMode, byData, nDataLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserLCDMemoryWrite(int iType, int nLCDLine, int nDataFormat, char *pTxData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserLCDMemoryWrite fnDll;
		fnDll = (pfnUserLCDMemoryWrite) GetProcAddress(m_hLib, "UserLCDMemoryWrite");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nLCDLine, nDataFormat, pTxData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserLCDMemoryWriteEx(int iType, int nLCDLine, int nDataFormat, char *pFilename)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserLCDMemoryWriteEx fnDll;
		fnDll = (pfnUserLCDMemoryWriteEx) GetProcAddress(m_hLib, "UserLCDMemoryWriteEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nLCDLine, nDataFormat, pFilename);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserLCDMemoryRead(int iType, int nLCDLine, char *pRxBuf, long *pRxLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserLCDMemoryRead fnDll;
		fnDll = (pfnUserLCDMemoryRead) GetProcAddress(m_hLib, "UserLCDMemoryRead");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nLCDLine, pRxBuf, pRxLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserLCDMemoryReadEx(int iType, int nLCDLine, char *pFilename)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserLCDMemoryReadEx fnDll;
		fnDll = (pfnUserLCDMemoryReadEx) GetProcAddress(m_hLib, "UserLCDMemoryReadEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nLCDLine, pFilename);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR USER'S MEMORY
// ---------------------------
INT CJ230iDLL::UserMemoryInit()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryInit fnDll;
		fnDll = (pfnUserMemoryInit) GetProcAddress(m_hLib, "UserMemoryInit");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserMemoryInitEx(int iType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryInitEx fnDll;
		fnDll = (pfnUserMemoryInitEx) GetProcAddress(m_hLib, "UserMemoryInitEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserMemoryWrite(int nOffset, int nWriteLength, BYTE *pWriteData )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryWrite fnDll;
		fnDll = (pfnUserMemoryWrite) GetProcAddress(m_hLib, "UserMemoryWrite");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nOffset, nWriteLength, pWriteData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserMemoryWriteEx(int iType, long nOffset, long nLength, char *pTxData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryWriteEx fnDll;
		fnDll = (pfnUserMemoryWriteEx) GetProcAddress(m_hLib, "UserMemoryWriteEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nOffset, nLength, pTxData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserMemoryRead(int nOffset, int nReadLength, BYTE *pReadData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryRead fnDll;
		fnDll = (pfnUserMemoryRead) GetProcAddress(m_hLib, "UserMemoryRead");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nOffset, nReadLength, pReadData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::UserMemoryReadEx(int iType, long nOffset, long nLength, char *pRxBuf, long *pRxLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnUserMemoryReadEx fnDll;
		fnDll = (pfnUserMemoryReadEx) GetProcAddress(m_hLib, "UserMemoryReadEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType, nOffset, nLength, pRxBuf, pRxLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// Directly Send/Receive
// ---------------------------
INT CJ230iDLL::DeviceDirectSend(char *cmdbuf)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDeviceDirectSend fnDll;
		fnDll = (pfnDeviceDirectSend) GetProcAddress(m_hLib, "DeviceDirectSend");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cmdbuf);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DeviceDirectSend2(char *cmdbuf, int nLen, int nTimeOut, int nRcv)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDeviceDirectSend2 fnDll;
		fnDll = (pfnDeviceDirectSend2) GetProcAddress(m_hLib, "DeviceDirectSend2");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cmdbuf, nLen, nTimeOut, nRcv);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::DeviceDirectGet2(char *pGetbuf, int *pLen)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnDeviceDirectGet2 fnDll;
		fnDll = (pfnDeviceDirectGet2) GetProcAddress(m_hLib, "DeviceDirectGet2");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pGetbuf, pLen);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR MS CARD
// ---------------------------
INT CJ230iDLL::MS_GetCoercivity(int nTrack, int *pnCoercivity)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_GetCoercivity fnDll;
		fnDll = (pfnMS_GetCoercivity) GetProcAddress(m_hLib, "MS_GetCoercivity");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nTrack, pnCoercivity);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_EncodeOption(int nTrack, int nOption, int nCoercivity)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_EncodeOption fnDll;
		fnDll = (pfnMS_EncodeOption) GetProcAddress(m_hLib, "MS_EncodeOption");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nTrack, nOption, nCoercivity);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_SendEncodeData(char* sziso1, char* sziso2, char* sziso3)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_SendEncodeData fnDll;
		fnDll = (pfnMS_SendEncodeData) GetProcAddress(m_hLib, "MS_SendEncodeData");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(sziso1, sziso2, sziso3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_Coercivity(int p1 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_Coercivity fnDll;
		fnDll = (pfnMS_Coercivity) GetProcAddress(m_hLib, "MS_Coercivity");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_Write(int iTrack, char* sziso1, char* sziso2, char* sziso3)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_Write fnDll;
		fnDll = (pfnMS_Write) GetProcAddress(m_hLib, "MS_Write");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, sziso1, sziso2, sziso3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_WriteEx(int iTrack, char* sziso1, char* sziso2, char* sziso3, int nCoercivity)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_WriteEx fnDll;
		fnDll = (pfnMS_WriteEx) GetProcAddress(m_hLib, "MS_WriteEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, sziso1, sziso2, sziso3, nCoercivity);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_WriteExW( int iTrack, LPWSTR sziso1, LPWSTR sziso2, LPWSTR sziso3, int nCoercivity)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_WriteExW fnDll;
		fnDll = (pfnMS_WriteExW) GetProcAddress(m_hLib, "MS_WriteExW");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, sziso1, sziso2, sziso3, nCoercivity);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_WriteAll(int iTrack, int nCoercivity, char* sziso1, char* sziso2, char* sziso3, char* szjis, int njis)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_WriteAll fnDll;
		fnDll = (pfnMS_WriteAll) GetProcAddress(m_hLib, "MS_WriteAll");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, nCoercivity, sziso1, sziso2, sziso3, szjis, njis);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_Read(int iTrack, char* sziso1, char* sziso2, char* sziso3 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_Read fnDll;
		fnDll = (pfnMS_Read) GetProcAddress(m_hLib, "MS_Read");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, sziso1, sziso2, sziso3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::MS_ReadAll(int iTrack, char* sziso1, char* sziso2, char* sziso3, char* szjis, int *njis)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnMS_ReadAll fnDll;
		fnDll = (pfnMS_ReadAll) GetProcAddress(m_hLib, "MS_ReadAll");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iTrack, sziso1, sziso2, sziso3, szjis, njis);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// FOR IC CARD
// ---------------------------
INT CJ230iDLL::CheckBoardType(BYTE *pStatus) 
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckBoardType fnDll;
		fnDll = (pfnCheckBoardType) GetProcAddress(m_hLib, "CheckBoardType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckBoardTypeEx(char *pIfmType, char *pSamType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckBoardTypeEx fnDll;
		fnDll = (pfnCheckBoardTypeEx) GetProcAddress(m_hLib, "CheckBoardTypeEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pIfmType, pSamType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckSIM(int nSlot, int *pStatus) 
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckSIM fnDll;
		fnDll = (pfnCheckSIM) GetProcAddress(m_hLib, "CheckSIM");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nSlot, pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::CheckSAM(BYTE *pStatus) 
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnCheckSAM fnDll;
		fnDll = (pfnCheckSAM) GetProcAddress(m_hLib, "CheckSAM");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_ContactOn()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_ContactOn fnDll;
		fnDll = (pfnIC_ContactOn) GetProcAddress(m_hLib, "IC_ContactOn");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_Eject(int nCmd )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_Eject fnDll;
		fnDll = (pfnIC_Eject) GetProcAddress(m_hLib, "IC_Eject");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nCmd);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_PowerOn(int cno, DWORD * pdwRXSize, LPBYTE lpbRXData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_PowerOn fnDll;
		fnDll = (pfnIC_PowerOn) GetProcAddress(m_hLib, "IC_PowerOn");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_PowerOff(int cno )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_PowerOff fnDll;
		fnDll = (pfnIC_PowerOff) GetProcAddress(m_hLib, "IC_PowerOff");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_Input(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_Input fnDll;
		fnDll = (pfnIC_Input) GetProcAddress(m_hLib, "IC_Input");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, dwTXSize, lpbTXData, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_Output(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_Output fnDll;
		fnDll = (pfnIC_Output) GetProcAddress(m_hLib, "IC_Output");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, dwTXSize, lpbTXData, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCPowerUp(int cno, BYTE bCardType, BYTE bSubCardType, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCPowerUp fnDll;
		fnDll = (pfnIC_GSCPowerUp) GetProcAddress(m_hLib, "IC_GSCPowerUp");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, bCardType, bSubCardType, pbRecvBuffer, pcbRecvLength);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCPowerDown(int cno )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCPowerDown fnDll;
		fnDll = (pfnIC_GSCPowerDown) GetProcAddress(m_hLib, "IC_GSCPowerDown");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCWrite(int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToWrite, DWORD dwLengthToWrite, LPBYTE pbByteToWrite)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCWrite fnDll;
		fnDll = (pfnIC_GSCWrite) GetProcAddress(m_hLib, "IC_GSCWrite");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, iType, bCardType, bSubCardType, dwAddressToWrite, dwLengthToWrite, pbByteToWrite);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCRead(int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToRead,
								DWORD dwLengthToRead, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCRead fnDll;
		fnDll = (pfnIC_GSCRead) GetProcAddress(m_hLib, "IC_GSCRead");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, iType, bCardType, bSubCardType, dwAddressToRead,
				dwLengthToRead, pbRecvBuffer, pcbRecvLength);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCVerify(int cno, BYTE bCardType, DWORD dwCodeLength, LPBYTE pbCodeToVerify)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCVerify fnDll;
		fnDll = (pfnIC_GSCVerify) GetProcAddress(m_hLib, "IC_GSCVerify");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, bCardType, dwCodeLength, pbCodeToVerify);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCErase(int cno, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToErase, DWORD dwLengthToErase)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCErase fnDll;
		fnDll = (pfnIC_GSCErase) GetProcAddress(m_hLib, "IC_GSCErase");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, bCardType, bSubCardType, dwAddressToErase, dwLengthToErase);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::IC_GSCRestore(int cno, BYTE bCardType, BYTE bSubCardType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnIC_GSCRestore fnDll;
		fnDll = (pfnIC_GSCRestore) GetProcAddress(m_hLib, "IC_GSCRestore");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cno, bCardType, bSubCardType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}



// ---------------------------
// FOR RF CARD
// ---------------------------
INT CJ230iDLL::RF_CardInsert()
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_CardInsert fnDll;
		fnDll = (pfnRF_CardInsert) GetProcAddress(m_hLib, "RF_CardInsert");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( );
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_CardCheck(int nDev, int nCardType)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_CardCheck fnDll;
		fnDll = (pfnRF_CardCheck) GetProcAddress(m_hLib, "RF_CardCheck");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, nCardType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_PowerOn(int nDev, int* pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_PowerOn fnDll;
		fnDll = (pfnRF_PowerOn) GetProcAddress(m_hLib, "RF_PowerOn");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, pnCardType, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_PowerOnEx(int nDev, int pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_PowerOnEx fnDll;
		fnDll = (pfnRF_PowerOnEx) GetProcAddress(m_hLib, "RF_PowerOnEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, pnCardType, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_PowerOff(int nDev)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_PowerOff fnDll;
		fnDll = (pfnRF_PowerOff) GetProcAddress(m_hLib, "RF_PowerOff");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_Read(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, char nKey, DWORD* pdwRXSize, BYTE* lpbRXData )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_Read fnDll;
		fnDll = (pfnRF_Read) GetProcAddress(m_hLib, "RF_Read");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, nCardType, nBlock, nInLen, pInBuf, nKey, pdwRXSize, lpbRXData);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_Write(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, DWORD* pdwRXSize, BYTE* lpbRXData, char nKey, BYTE* pPW )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_Write fnDll;
		fnDll = (pfnRF_Write) GetProcAddress(m_hLib, "RF_Write");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, nCardType, nBlock, nInLen, pInBuf, pdwRXSize, lpbRXData, nKey, pPW);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_Increment(int nDev, int nSourceBlock, int nTargetBlock, BYTE* pIncValue, char nKey, BYTE* pPW )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_Increment fnDll;
		fnDll = (pfnRF_Increment) GetProcAddress(m_hLib, "RF_Increment");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nDev, nSourceBlock, nTargetBlock, pIncValue, nKey, pPW);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_Decrement(int nDev, int nSourceBlock, int nTargetBlock, BYTE* pDecValue, char nKey, BYTE* pPW )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_Decrement fnDll;
		fnDll = (pfnRF_Decrement) GetProcAddress(m_hLib, "RF_Decrement");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( nDev, nSourceBlock, nTargetBlock, pDecValue, nKey, pPW);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::RF_Download(char *pFile )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnRF_Download fnDll;
		fnDll = (pfnRF_Download) GetProcAddress(m_hLib, "RF_Download");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


INT CJ230iDLL::TextToBmpMake(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnTextToBmpMake fnDll;
		fnDll = (pfnTextToBmpMake) GetProcAddress(m_hLib, "TextToBmpMake");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cFileName, cStr, FontName, FontType, FontSize);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::TextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnTextToBmpMakeEx fnDll;
		fnDll = (pfnTextToBmpMakeEx) GetProcAddress(m_hLib, "TextToBmpMakeEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cFileName, cStr, FontName, FontType, FontSize, Resolution);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::ColorTextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution, DWORD Color )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnColorTextToBmpMakeEx fnDll;
		fnDll = (pfnColorTextToBmpMakeEx) GetProcAddress(m_hLib, "ColorTextToBmpMakeEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(cFileName, cStr, FontName, FontType, FontSize, Resolution, Color);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// 이미지 파일을 원하는 크기로 조정
// ---------------------------
INT CJ230iDLL::Image_Adjust(char *pSrcFile, LPRECT pSrcRect, char *pDstFile, LPRECT pDstRect, int iMode1, int iMode2, int iMode3 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Adjust fnDll;
		fnDll = (pfnImage_Adjust) GetProcAddress(m_hLib, "Image_Adjust");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pSrcFile, pSrcRect, pDstFile, pDstRect, iMode1, iMode2, iMode3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


// ---------------------------
// 인쇄할 이미지를 버퍼에 저장/인쇄하는 함수
// ---------------------------
INT CJ230iDLL::SetPrinterProfile(int nBPC, int nRGB, char *pMonitorProfile, char *pPrinterProfile )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetPrinterProfile fnDll;
		fnDll = (pfnSetPrinterProfile) GetProcAddress(m_hLib, "SetPrinterProfile");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nBPC, nRGB, pMonitorProfile, pPrinterProfile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_SaveMode(int nMode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_SaveMode fnDll;
		fnDll = (pfnImage_SaveMode) GetProcAddress(m_hLib, "Image_SaveMode");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_Buffer_Clear(int iType )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Buffer_Clear fnDll;
		fnDll = (pfnImage_Buffer_Clear) GetProcAddress(m_hLib, "Image_Buffer_Clear");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(iType);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_Send_Memory(int nImageType, HANDLE hMemory, int nDstX, int nDstY, int nRibbonType, int nPanel )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Send_Memory fnDll;
		fnDll = (pfnImage_Send_Memory) GetProcAddress(m_hLib, "Image_Send_Memory");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nImageType, hMemory, nDstX, nDstY, nRibbonType, nPanel);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_Send(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Send fnDll;
		fnDll = (pfnImage_Send) GetProcAddress(m_hLib, "Image_Send");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(xPos, yPos, imagefilename, sw1, sw2, level, mode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_SendEx(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode, BYTE nGrayLevel )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_SendEx fnDll;
		fnDll = (pfnImage_SendEx) GetProcAddress(m_hLib, "Image_SendEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(xPos, yPos, imagefilename, sw1, sw2, level, mode, nGrayLevel);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_ProcessSend(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE nGrayLevel, BYTE nMode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_ProcessSend fnDll;
		fnDll = (pfnImage_ProcessSend) GetProcAddress(m_hLib, "Image_ProcessSend");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(xPos, yPos, imagefilename, sw1,sw2, nGrayLevel, nMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_VarnishSend(DWORD xPos, DWORD yPos, char* varnishimage, BYTE level, BYTE mode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_VarnishSend fnDll;
		fnDll = (pfnImage_VarnishSend) GetProcAddress(m_hLib, "Image_VarnishSend");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(xPos, yPos, varnishimage, level, mode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_VarnishSendEx(int nType, LPRECT pBlack, LPRECT pWhite )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_VarnishSendEx fnDll;
		fnDll = (pfnImage_VarnishSendEx) GetProcAddress(m_hLib, "Image_VarnishSendEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nType, pBlack, pWhite);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Panel_Skip(int nPanel, int nPrintSide )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnPanel_Skip fnDll;
		fnDll = (pfnPanel_Skip) GetProcAddress(m_hLib, "Panel_Skip");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nPanel, nPrintSide);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_Transfer(int nRibbon , int nPanel, int nPrintSide )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Transfer fnDll;
		fnDll = (pfnImage_Transfer) GetProcAddress(m_hLib, "Image_Transfer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nRibbon , nPanel, nPrintSide);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_Print(int nColorMode , int nOverlayMode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_Print fnDll;
		fnDll = (pfnImage_Print) GetProcAddress(m_hLib, "Image_Print");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nColorMode , nOverlayMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Image_PrintEx(int nRibbonType , int nBlackMode )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnImage_PrintEx fnDll;
		fnDll = (pfnImage_PrintEx) GetProcAddress(m_hLib, "Image_PrintEx");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nRibbonType , nBlackMode);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::Print_Panel(int nRibbon, int nPanel, int nPrintSide, int nCardPosition )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnPrint_Panel fnDll;
		fnDll = (pfnPrint_Panel) GetProcAddress(m_hLib, "Print_Panel");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)( nRibbon, nPanel, nPrintSide, nCardPosition);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


INT CJ230iDLL::GetRFTagRibbonType(int *type)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnGetRFTagRibbonType fnDll;
		fnDll = (pfnGetRFTagRibbonType) GetProcAddress(m_hLib, "GetRFTagRibbonType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(type);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_StartOfPrinting(int p1 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_StartOfPrinting fnDll;
		fnDll = (pfnN_StartOfPrinting) GetProcAddress(m_hLib, "N_StartOfPrinting");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_SetPrintType(int p1, int p2, int p3 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_SetPrintType fnDll;
		fnDll = (pfnN_SetPrintType) GetProcAddress(m_hLib, "N_SetPrintType");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2, p3);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_ClearImageBuffer(int p1, int p2 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_ClearImageBuffer fnDll;
		fnDll = (pfnN_ClearImageBuffer) GetProcAddress(m_hLib, "N_ClearImageBuffer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_SetImageBuffer(int p1, int p2, int p3, int p4, int p5, int p6, char *pFile )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_SetImageBuffer fnDll;
		fnDll = (pfnN_SetImageBuffer) GetProcAddress(m_hLib, "N_SetImageBuffer");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2, p3, p4, p5, p6, pFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_TransferImageData(int p1, int p2, int p3, int p4, int p5, char *pFile )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_TransferImageData fnDll;
		fnDll = (pfnN_TransferImageData) GetProcAddress(m_hLib, "N_TransferImageData");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2, p3, p4, p5, pFile);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_PrintPanel(int p1, int p2 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_PrintPanel fnDll;
		fnDll = (pfnN_PrintPanel) GetProcAddress(m_hLib, "N_PrintPanel");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, p2);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_EndOfPrint(int nPanel, int *pPanelCount, int *pJobNo )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_EndOfPrint fnDll;
		fnDll = (pfnN_EndOfPrint) GetProcAddress(m_hLib, "N_EndOfPrint");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nPanel, pPanelCount, pJobNo);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_CancelPrintJob(int nJobNo )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_CancelPrintJob fnDll;
		fnDll = (pfnN_CancelPrintJob) GetProcAddress(m_hLib, "N_CancelPrintJob");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(nJobNo);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_PrintJobStatus(int *pJobStatus )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_PrintJobStatus fnDll;
		fnDll = (pfnN_PrintJobStatus) GetProcAddress(m_hLib, "N_PrintJobStatus");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(pJobStatus);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_PrintSpeed(int p1 )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_PrintSpeed fnDll;
		fnDll = (pfnN_PrintSpeed) GetProcAddress(m_hLib, "N_PrintSpeed");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_SetIPAddress(int p1, BYTE *pAddress)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_SetIPAddress fnDll;
		fnDll = (pfnN_SetIPAddress) GetProcAddress(m_hLib, "N_SetIPAddress");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, pAddress);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}

INT CJ230iDLL::N_GetIPAddress(int p1, BYTE *pAddress)
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnN_GetIPAddress fnDll;
		fnDll = (pfnN_GetIPAddress) GetProcAddress(m_hLib, "N_GetIPAddress");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(p1, pAddress);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}


INT CJ230iDLL::SetColorAdjust(WORD Type )
{
	m_Status = MyCheckLibrary();
	if ( m_Status == ERR_TP_OK )
	{
		pfnSetColorAdjust fnDll;
		fnDll = (pfnSetColorAdjust) GetProcAddress(m_hLib, "SetColorAdjust");
		if ( fnDll != NULL )
		{
			m_Status = (fnDll)(Type);
		}
		else
		{
			m_Status = ERR_TP_API_NOT_SUPPORT;
		}
	}
	return (m_Status);
}
