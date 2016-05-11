#ifndef  _J23OIDLL_H
#define	 _J23OIDLL_H

/************************************************************************/
/*   ∑‚◊∞…Ë±∏…Ë±∏≥ß…ÃÃ·π©µƒ«˝∂Øø‚Ω”ø⁄                                   */
/************************************************************************/



#pragma once


class CJ230iDLL
{
public:
	CJ230iDLL(void);
	~CJ230iDLL(void);

private:

	HMODULE		m_hLib;
	int  MyLoadLibrary(CHAR *pDllName);
	int  MyFreeLibrary( );
	int  MyCheckLibrary( BOOL bLoad = TRUE );

public:

	int			m_Status;
	DWORD		m_LoadStatus;
	BOOL		m_bOpened;

	BOOL IsOpened();
	// ---------------------------
	// LOG FILE SETTING
	// ---------------------------
	INT SetLogPathFile(char *pLogFile);
	INT SetLogPathFileMonth(char *pLogPath, char *pLogFile, int nMonth);

	// ---------------------------
	// DEVICE INFO. SETTING, SEARCH, OPEN, CLOSE
	// ---------------------------
	INT GetTpclType(int *nType);
	INT SetOpenType(int OpenType);
	INT SetRetryTimes(int nTimes);
	INT SetDescription(char *pDescription);
	INT SetConnectPort(int DevicePort);
	INT ListDevices(DWORD *pArg1, char *pArg2, DWORD pArg3);
	INT OpenDevice(char *pName, int iPortNum);
	INT OpenDeviceEx(char *pName, DWORD dwFlags);
	INT CloseDevice(int iDeviceType);
	INT TP9_FreeLibrary(int nType);
	INT GetConnectedDevices(DWORD dwDevice, DWORD *pdwCount );
	INT GetDeviceInformation(DWORD dwDevice, DWORD dwIndex, BYTE *pDesc, BYTE *pSerial);
	INT GetNetworkBoard(int *pCount, LPBYTE pConfig);
	INT SetNetworkBoard(LPBYTE pConfig);

	// ---------------------------
	// DEVICE RESET, Get Firmware/RF Version
	// ---------------------------
	INT ResetDevice();
	INT Get_PrinterInfo(char*InfoBuffer);
	INT Get_PrinterInfoEx(char *pVersion, int *pType, int *pModel);
	INT Get_ModuleInfo(char ModuleType, char *InfoBuffer);

	// ---------------------------
	// GET STATUS/MESSAGE, CLEAR ERROR
	// ---------------------------
	INT Get_Status(char* st0, char *st1);
	INT Get_StatusEx(char* st0, char *st1);
	INT GetStatusCode(int *pStatus);
	INT DeviceErrorClear();
	INT Set_LanguageID(WORD nLangID);
	INT Get_StatusMessage(int nError, int nType, char *pMessage);

	// ---------------------------
	// CARD CONTROL (CHECK, INSERT, EJECT, FLIP)
	// ---------------------------
	INT CheckFeeder(int *pStatus);
	INT Card_Insert();
	INT Card_InsertEx(int nOption);	// [20120314]
	INT Card_Eject(int cmd);
	INT Card_EjectEx(int nOption);	// [20110722]
	INT Card_Flip();
	INT Card_MoveFlipperToPrinter();
	INT Card_Reject(int p1 );
	INT CheckRibbon(int *nRibbon);
	INT CheckRibbonEx(int *pRibbon, int *pRfRibbon);
	INT SetRibbonSync();
	INT SetRibbonSyncEx(int p1);
	INT CheckRibbonCount(int *pCount);

	// ---------------------------
	// «¡∏∞≈Õ¿« ¿Œº‚ º≥¡§ (¡¶æÓ)
	// ---------------------------
	INT GetRibbonSensor(int *nSensor );
	INT GetRibbonSensorEx(int *pSensor, int *pSensor2);
	INT GetRibbonInfo(int nType, char *pData, int *pLen);
	INT GetRibbonInfoEx(int nType, int *pTagRibbon, int *pTagCount);
	INT GetMACAddress(BYTE *pAddress);

	INT GetParameters(int nItem, char *pData, int *pLen);
	INT GetParametersEx(int p1, int *pValue);
	INT SetParametersEx(int p1, int p2);
	INT SetTPHResistance(int nResistance);
	INT AdjustIntensity(int nColor, int nIntensity);
	INT SetCardInputDirection(int nDir);
	INT SetRibbonType(int nRibbon , int nHalfStart, int nHalfWidth);
	INT SetRibbonTypeEx(int p1, int p2);
	INT OffsetXaxisPrintStartPosition(int nXstart, int nXend);
	INT OffsetYaxisPrintStartPosition(int nYstart);
	INT PrintPintAdjust(int nOffset);
	INT SetMonoPrintMode(int nMode);
	INT SetCardInputOption(int nMode);
	INT GetPrintCount(DWORD *pCount);
	INT GetProduction(char *pManufacturer, char *pDescription, char *pSerialNumber);
	INT SetProduction(char *pManufacturer, char *pDescription, char *pSerialNumber);
	INT GetProductSerialNo(char *pSerialNumber);
	INT SetProductSerialNo(char *pSerialNumber);
	INT SetLCDContrast(int nValue);
	INT GetLCDContrast(int *pnValue);
	INT SetRibbonSensorADC(int nValue);
	INT GetRibbonSensorADC(int *pnValue);
	INT SetRibbonSensor();
	INT GetRibbonMotorDuty(int *pnValue);
	INT SetRibbonMotorDuty(int nValue);
	INT SetRibbonSyncOption(int nType);
	INT SetCardReadyPosition(int nType);
	INT GetCardControlTime(int *pEjectTime, int *pInsertTime);
	INT SetCardControlTime(int  nEjectTime, int nInsertTime);
	INT GetModelNation(int *pModelType, int *pOemType);
	INT CleaningMode();
	INT SelfTestMode(int  nMode);
	INT ChangePassword(int iType, char *pOldPassword, char *pNewPassword);
	INT LockPrinter(int iType, char *pPassword);
	INT SetEncryption(int iType, LPBYTE pKeyData);
	INT SetDigitalPotentiometer(int type, int value);
	INT GetDigitalPotentiometer(int type, int *pvalue);

	// ---------------------------
	// FOR DOWNLOAD
	// ---------------------------
	INT DownloadFirmware(char *pFile);
	INT DownloadFWFile(char *pFile);
	INT DownloadFWErase();
	INT DownloadFWDataLoad();
	INT DownloadFWVerify();
	INT DownloadFWReset(int nType);
	INT DownloadFWStatus(int *pStep, int *pStatus);
	INT DownloadStatus(int *pStep, int *pStatus);

	// ---------------------------
	// FOR BUZZER
	// ---------------------------
	INT Buzzer(BYTE byCount, int iOntime, int iOfftime);

	// ---------------------------
	// FOR LCD CONTROL/DISPLAY
	// ---------------------------
	INT LCD_DISPLAY(BYTE byMode, BYTE *byData, int nDataLen);
	INT UserLCDMemoryWrite(int iType, int nLCDLine, int nDataFormat, char *pTxData);
	INT UserLCDMemoryWriteEx(int iType, int nLCDLine, int nDataFormat, char *pFilename);
	INT UserLCDMemoryRead(int iType, int nLCDLine, char *pRxBuf, long *pRxLen);
	INT UserLCDMemoryReadEx(int iType, int nLCDLine, char *pFilename);

	// ---------------------------
	// FOR USER'S MEMORY
	// ---------------------------
	INT UserMemoryInit();
	INT UserMemoryInitEx(int iType);
	INT UserMemoryWrite(int nOffset, int nWriteLength, BYTE *pWriteData );
	INT UserMemoryWriteEx(int iType, long nOffset, long nLength, char *pTxData);
	INT UserMemoryRead(int nOffset, int nReadLength, BYTE *pReadData);
	INT UserMemoryReadEx(int iType, long nOffset, long nLength, char *pRxBuf, long *pRxLen);

	// ---------------------------
	// Directly Send/Receive
	// ---------------------------
	INT DeviceDirectSend(char *cmdbuf);
	INT DeviceDirectSend2(char *cmdbuf, int nLen, int nTimeOut, int nRcv);
	INT DeviceDirectGet2(char *pGetbuf, int *pLen);

	// ---------------------------
	// FOR MS CARD
	// ---------------------------
	INT MS_GetCoercivity(int nTrack, int *pnCoercivity);
	INT MS_EncodeOption(int nTrack, int nOption, int nCoercivity);
	INT MS_SendEncodeData(char* sziso1, char* sziso2, char* sziso3);
	INT MS_Coercivity(int p1 );
	INT MS_Write(int iTrack, char* sziso1, char* sziso2, char* sziso3);
	INT MS_WriteEx(int iTrack, char* sziso1, char* sziso2, char* sziso3, int nCoercivity);
	INT MS_WriteExW( int iTrack, LPWSTR sziso1, LPWSTR sziso2, LPWSTR sziso3, int nCoercivity);
	INT MS_WriteAll(int iTrack, int nCoercivity, char* sziso1, char* sziso2, char* sziso3, char* szjis, int njis);
	INT MS_Read(int iTrack, char* sziso1, char* sziso2, char* sziso3 );
	INT MS_ReadAll(int iTrack, char* sziso1, char* sziso2, char* sziso3, char* szjis, int *njis);

	// ---------------------------
	// FOR IC CARD
	// ---------------------------
	INT CheckBoardType(BYTE *pStatus) ;
	INT CheckBoardTypeEx(char *pIfmType, char *pSamType);
	INT CheckSIM(int nSlot, int *pStatus) ;
	INT CheckSAM(BYTE *pStatus) ;
	INT IC_ContactOn();
	INT IC_Eject(int nCmd );
	INT IC_PowerOn(int cno, DWORD * pdwRXSize, LPBYTE lpbRXData);
	INT IC_PowerOff(int cno );
	INT IC_Input(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData);
	INT IC_Output(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData);

	INT IC_GSCPowerUp(int cno, BYTE bCardType, BYTE bSubCardType, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength);
	INT IC_GSCPowerDown(int cno );
	INT IC_GSCWrite(int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToWrite, DWORD dwLengthToWrite, LPBYTE pbByteToWrite);
	INT IC_GSCRead(int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToRead, DWORD dwLengthToRead, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength);
	INT IC_GSCVerify(int cno, BYTE bCardType, DWORD dwCodeLength, LPBYTE pbCodeToVerify);
	INT IC_GSCErase(int cno, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToErase, DWORD dwLengthToErase);
	INT IC_GSCRestore(int cno, BYTE bCardType, BYTE bSubCardType);


	// ---------------------------
	// FOR RF CARD
	// ---------------------------
	INT RF_CardInsert();
	INT RF_CardCheck(int nDev, int nCardType);
	INT RF_PowerOn(int nDev, int* pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData);
	INT RF_PowerOnEx(int nDev, int pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData);
	INT RF_PowerOff(int nDev);
	INT RF_Read(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, char nKey, DWORD* pdwRXSize, BYTE* lpbRXData );
	INT RF_Write(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, DWORD* pdwRXSize, BYTE* lpbRXData, char nKey, BYTE* pPW );
	INT RF_Increment(int nDev, int nSourceBlock, int nTargetBlock, BYTE* pIncValue, char nKey, BYTE* pPW );
	INT RF_Decrement(int nDev, int nSourceBlock, int nTargetBlock, BYTE* pDecValue, char nKey, BYTE* pPW );
	INT RF_Download(char *pFile );

	// ---------------------------
	// ≈ÿΩ∫∆Æ∏¶ ¿ÃπÃ¡ˆ ∆ƒ¿œ∑Œ ∫Ø»Ø
	// ---------------------------
	INT TextToBmpMake(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize );
	INT TextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution );
	INT ColorTextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution, DWORD Color );

	// ---------------------------
	// ¿ÃπÃ¡ˆ ∆ƒ¿œ¿ª ø¯«œ¥¬ ≈©±‚∑Œ ¡∂¡§
	// ---------------------------
	INT Image_Adjust(char *pSrcFile, LPRECT pSrcRect, char *pDstFile, LPRECT pDstRect, int iMode1, int iMode2, int iMode3 );

	// ---------------------------
	// ¿Œº‚«“ ¿ÃπÃ¡ˆ∏¶ πˆ∆€ø° ¿˙¿Â/¿Œº‚«œ¥¬ «‘ºˆ
	// ---------------------------
	INT SetPrinterProfile(int nBPC, int nRGB, char *pMonitorProfile, char *pPrinterProfile );
	INT Image_SaveMode(int nMode );
	INT Image_Buffer_Clear(int iType );
	INT Image_Send_Memory(int nImageType, HANDLE hMemory, int nDstX, int nDstY, int nRibbonType, int nPanel );
	INT Image_Send(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode );
	INT Image_SendEx(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode, BYTE nGrayLevel );
	INT Image_ProcessSend(DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE nGrayLevel, BYTE nMode );
	INT Image_VarnishSend(DWORD xPos, DWORD yPos, char* varnishimage, BYTE level, BYTE mode );
	INT Image_VarnishSendEx(int nType, LPRECT pBlack, LPRECT pWhite );
	INT Panel_Skip(int nPanel, int nPrintSide );
	INT Image_Transfer(int nRibbon , int nPanel, int nPrintSide );
	INT Image_Print(int nColorMode , int nOverlayMode );
	INT Image_PrintEx(int nRibbonType , int nBlackMode );
	INT Print_Panel(int nRibbon, int nPanel, int nPrintSide, int nCardPosition );

	INT GetRFTagRibbonType(int *type);
	INT N_StartOfPrinting(int p1 );
	INT N_SetPrintType(int p1, int p2, int p3 );
	INT N_ClearImageBuffer(int p1, int p2 );
	INT N_SetImageBuffer(int p1, int p2, int p3, int p4, int p5, int p6, char *pFile );
	INT N_TransferImageData(int p1, int p2, int p3, int p4, int p5, char *pFile );
	INT N_PrintPanel(int p1, int p2 );
	INT N_EndOfPrint(int nPanel, int *pPanelCount, int *pJobNo );
	INT N_CancelPrintJob(int nJobNo );
	INT N_PrintJobStatus(int *pJobStatus );
	INT N_PrintSpeed(int p1 );
	INT N_SetIPAddress(int p1, BYTE *pAddress);
	INT N_GetIPAddress(int p1, BYTE *pAddress);
	// ---------------------------
	// «¡∏∞≈Õ µÂ∂Û¿Ãπˆø°º≠ ¿Œº‚ ªˆªÛ ¡∂¡§«œ±‚ ¿ß«ÿ »£√‚«—¥Ÿ.
	// ---------------------------
	INT SetColorAdjust(WORD Type );
};

#endif