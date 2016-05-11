// TP9000.h : main header file for the TP9000 DLL
//

#pragma once

#ifdef TP9000_EXPORTS

#define TP9_API __declspec(dllexport)

#else

#define TP9_API __declspec(dllimport)

#ifndef __TPDEFINE_H
#define	TP_TRUE                                 -1
#define	TP_FALSE                                -2
#define	TP_DLL_NOT_LOADED                       -3
#define	TP_NOT_SUPPORTED_IMAGE                  -4
#endif

#endif

#ifdef TP9000_EXPORTS

	// ---------------------------
	// LOG FILE SETTING
	// ---------------------------
	TP9_API	int __stdcall SetLogPathFile ( char *pLogFile );
	TP9_API	int __stdcall SetLogPathFileMonth ( char *pLogPath, char *pLogFile, int nMonth );

	// ---------------------------
	// DEVICE INFO. SETTING, SEARCH, OPEN, CLOSE
	// ---------------------------
	TP9_API	int __stdcall GetTpclType ( int *nType );
	TP9_API	int __stdcall SetOpenType ( int OpenType );
	TP9_API	int __stdcall SetRetryTimes ( int nTimes );
	TP9_API	int __stdcall SetDescription ( char *pDescription );
	TP9_API	int __stdcall SetConnectPort ( int DevicePort );
	TP9_API	int __stdcall ListDevices ( DWORD *pArg1, char *pArg2, DWORD pArg3 );
	TP9_API	int __stdcall OpenDevice (char *pName, int iPortNum );
	TP9_API	int __stdcall OpenDeviceEx ( char *pName, DWORD dwFlags );
	TP9_API int __stdcall CloseDevice (int iDeviceType);
	TP9_API int __stdcall TP9_FreeLibrary (int nType);
	TP9_API	int __stdcall GetConnectedDevices ( DWORD dwDevice, DWORD *pdwCount );
	TP9_API	int __stdcall GetDeviceInformation ( DWORD dwDevice, DWORD dwIndex, BYTE *pDesc, BYTE *pSerial );
	TP9_API int __stdcall GetNetworkBoard ( int *pCount, LPBYTE pConfig );
	TP9_API int __stdcall SetNetworkBoard ( LPBYTE pConfig );
//	TP9_API int __stdcall GetDevicePath(char *pSerial, char *pPath);
	// ---------------------------
	// DEVICE RESET, Get Firmware/RF Version
	// ---------------------------
	TP9_API int __stdcall ResetDevice( );
	TP9_API int __stdcall Get_PrinterInfo(char*InfoBuffer);
	TP9_API int __stdcall Get_PrinterInfoEx( char *pVersion, int *pType, int *pModel );
	TP9_API int __stdcall Get_ModuleInfo(char ModuleType, char* InfoBuffer);

	// ---------------------------
	// GET STATUS/MESSAGE, CLEAR ERROR
	// ---------------------------
	TP9_API int __stdcall Get_Status(char* st0, char *st1);
	TP9_API int __stdcall Get_StatusEx(char* st0, char *st1);
	TP9_API int __stdcall GetStatusCode( int *pStatus );
	TP9_API int __stdcall DeviceErrorClear( );
	TP9_API int __stdcall Set_LanguageID(WORD nLangID);
	TP9_API int __stdcall Get_StatusMessage(int nError, int nType, char *pMessage);

	// ---------------------------
	// CARD CHECK, INSERT, EJECT, FLIP
	// ---------------------------
	TP9_API int __stdcall CheckFeeder(int *pStatus);
	TP9_API int __stdcall Card_Insert ( );
	TP9_API int __stdcall Card_InsertEx ( int nOption );
	TP9_API int __stdcall Card_Eject (int cmd);
	TP9_API int __stdcall Card_EjectEx (int nOption);	// [20110722]
	TP9_API int __stdcall Card_Flip( );
	TP9_API int __stdcall Card_MoveFlipperToPrinter( );

	TP9_API int __stdcall Card_Reject ( int p1 );
	TP9_API int __stdcall CheckRibbon (int *nRibbon);
	TP9_API int __stdcall CheckRibbonEx( int *pRibbon, int *pRfRibbon );
	TP9_API int __stdcall SetRibbonSync( );
	TP9_API int __stdcall SetRibbonSyncEx( int p1 );
	TP9_API int __stdcall CheckRibbonCount(int *pCount);

	// ---------------------------
	// 프린터의 인쇄 설정 (제어)
	// ---------------------------
	TP9_API int __stdcall GetRibbonSensor (int *nSensor);
	TP9_API int __stdcall GetRibbonSensorEx (int *pSensor, int *pSensor2);
	TP9_API int __stdcall GetRibbonInfo(int nType, char *pData, int *pLen );
	TP9_API int __stdcall GetRibbonInfoEx( int p1, int *pTagRibbon, int *pTagCount );
	TP9_API int __stdcall GetMACAddress(BYTE *pAddress);

	TP9_API int __stdcall GetParameters( int nItem, char *pData, int *pLen );
	TP9_API int __stdcall GetParametersEx( int p1, int *pValue );
	TP9_API int __stdcall SetParametersEx( int p1, int p2 );
	TP9_API int __stdcall SetTPHResistance( int nResistance );
	TP9_API int __stdcall AdjustIntensity( int nColor, int nIntensity );
	TP9_API int __stdcall SetCardInputDirection( int nDir );
	TP9_API int __stdcall SetRibbonType (int nRibbon, int nHalfStart, int nHalfWidth);
	TP9_API int __stdcall SetRibbonTypeEx( int p1, int p2 );
	TP9_API int __stdcall OffsetXaxisPrintStartPosition( int nXstart, int nXend );
	TP9_API int __stdcall OffsetYaxisPrintStartPosition( int nYstart );
	TP9_API int __stdcall PrintPintAdjust( int nOffset );
	TP9_API int __stdcall SetMonoPrintMode( int nMode );
	TP9_API int __stdcall SetCardInputOption( int nMode );
	TP9_API int __stdcall GetPrintCount( DWORD *pCount );
	TP9_API int __stdcall GetProduction ( char *pManufacturer, char *pDescription, char *pSerialNumber );
//	TP9_API int __stdcall SetProduction ( char *pManufacturer, char *pDescription, char *pSerialNumber );
	TP9_API int __stdcall GetProductSerialNo ( char *pSerialNumber );
//	TP9_API int __stdcall SetProductSerialNo ( char *pSerialNumber );
	TP9_API int __stdcall SetLCDContrast( int nValue );
	TP9_API int __stdcall GetLCDContrast( int *pnValue );
	TP9_API int __stdcall SetRibbonSensorADC( int nValue );
	TP9_API int __stdcall GetRibbonSensorADC( int *pnValue );
	TP9_API int __stdcall SetRibbonSensor ( );	// Resistance
	TP9_API int __stdcall GetRibbonMotorDuty( int *pnValue );	// [20120328]
	TP9_API int __stdcall SetRibbonMotorDuty( int nValue );		// [20120328]
	TP9_API int __stdcall SetRibbonSyncOption(int nType);
	TP9_API int __stdcall SetCardReadyPosition(int nType);
	TP9_API int __stdcall GetCardControlTime( int *pEjectTime, int *pInsertTime );
	TP9_API int __stdcall SetCardControlTime( int  nEjectTime, int nInsertTime );
	TP9_API int __stdcall GetModelNation( int *pModelType, int *pOemType );
	TP9_API int __stdcall CleaningMode( );
	TP9_API int __stdcall SelfTestMode( int  nMode );
	TP9_API int __stdcall ChangePassword( int iType, char *pOldPassword, char *pNewPassword );
	TP9_API int __stdcall LockPrinter( int iType, char *pPassword );
	TP9_API int __stdcall SetEncryption( int iType, LPBYTE pKeyData );
//	TP9_API int __stdcall SetDigitalPotentiometer ( int type, int value );		// [20120423] NEW CIT
//	TP9_API int __stdcall GetDigitalPotentiometer ( int type, int *pvalue );	// [20120423] NEW CIT

	// ---------------------------
	// FOR DOWNLOAD
	// ---------------------------
	TP9_API int __stdcall DownloadFirmware ( char *pFile );
	TP9_API int __stdcall DownloadFWFile( char *pFile );
	TP9_API int __stdcall DownloadFWErase();
	TP9_API int __stdcall DownloadFWDataLoad();
	TP9_API int __stdcall DownloadFWVerify();
	TP9_API int __stdcall DownloadFWReset(int nType);
	TP9_API int __stdcall DownloadFWStatus( int *pStep, int *pStatus );

	// ---------------------------
	// FOR BUZZER
	// ---------------------------
	TP9_API int __stdcall Buzzer( BYTE byCount, int iOntime, int iOfftime ); //bkyoun modify

	// ---------------------------
	// FOR LCD CONTROL/DISPLAY
	// ---------------------------
	TP9_API int __stdcall LCD_DISPLAY( BYTE byMode, BYTE *byData, int nDataLen );
	TP9_API int __stdcall UserLCDMemoryWrite( int iType, int nLCDLine, int nDataFormat, char *pTxData );
	TP9_API int __stdcall UserLCDMemoryWriteEx( int iType, int nLCDLine, int nDataFormat, char *pFilename );
	TP9_API int __stdcall UserLCDMemoryRead( int iType, int nLCDLine, char *pRxBuf, long *pRxLen );
	TP9_API int __stdcall UserLCDMemoryReadEx( int iType, int nLCDLine, char *pFilename );

	// ---------------------------
	// FOR USER'S MEMORY
	// ---------------------------
	TP9_API int __stdcall UserMemoryInit( );
	TP9_API int __stdcall UserMemoryInitEx( int iType );
	TP9_API int __stdcall UserMemoryWrite( int nOffset, int nWriteLength, BYTE *pWriteData  );
	TP9_API int __stdcall UserMemoryWriteEx( int iType, long nOffset, long nLength, char *pTxData );
	TP9_API int __stdcall UserMemoryRead( int nOffset, int nReadLength, BYTE *pReadData );
	TP9_API int __stdcall UserMemoryReadEx( int iType, long nOffset, long nLength, char *pRxBuf, long *pRxLen );

	// ---------------------------
	// Directly Send/Receive
	// ---------------------------
	TP9_API int __stdcall DeviceDirectSend(char *cmdbuf);
	TP9_API int __stdcall DeviceDirectSend2( char *cmdbuf, int nLen, int nTimeOut, int nRcv );
	TP9_API int __stdcall DeviceDirectGet2( char *pGetbuf, int *pLen );

	// ---------------------------
	// FOR MS CARD
	// ---------------------------
	TP9_API	int __stdcall MS_GetCoercivity ( int nTrack, int *pnCoercivity );
	TP9_API int __stdcall MS_EncodeOption( int nTrack, int nOption, int nCoercivity );
	TP9_API int __stdcall MS_SendEncodeData( char* sziso1, char* sziso2, char* sziso3 );
	TP9_API int __stdcall MS_Coercivity( int p1 );
	TP9_API int __stdcall MS_Write   (int iTrack, char* sziso1, char* sziso2, char* sziso3) ;
	TP9_API int __stdcall MS_WriteEx (int iTrack, char* sziso1, char* sziso2, char* sziso3, int nCoercivity) ;
	TP9_API int __stdcall MS_WriteExW(int iTrack, LPWSTR sziso1, LPWSTR sziso2, LPWSTR sziso3, int nCoercivity) ;
	TP9_API int __stdcall MS_WriteAll(int iTrack, int nCoercivity, char* sziso1, char* sziso2, char* sziso3, char* szjis, int njis );
	TP9_API int __stdcall MS_Read    (int iTrack, char* sziso1, char* sziso2, char* sziso3);
	TP9_API int __stdcall MS_ReadAll (int iTrack, char* sziso1, char* sziso2, char* sziso3, char* szjis, int *njis);

	// ---------------------------
	// FOR IC CARD
	// ---------------------------
	TP9_API int __stdcall CheckBoardType(BYTE *pStatus);
	TP9_API int __stdcall CheckBoardTypeEx( char *pIfmType, char *pSamType );
	TP9_API int __stdcall CheckSIM(int nSlot, int *pStatus);
	TP9_API int __stdcall CheckSAM(BYTE *pStatus); //bkyoun modify
	TP9_API int __stdcall IC_ContactOn( );
	TP9_API int __stdcall IC_Eject(int nCmd);
	TP9_API int __stdcall IC_PowerOn (int cno, DWORD * pdwRXSize, LPBYTE lpbRXData);
	TP9_API int __stdcall IC_PowerOff(int cno);
	TP9_API int __stdcall IC_Input(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData );
	TP9_API int __stdcall IC_Output(int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData );
#if 1	//defined(GSC_FUNC)
	TP9_API int __stdcall IC_GSCPowerUp( int cno, BYTE bCardType, BYTE bSubCardType, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength );
	TP9_API int __stdcall IC_GSCPowerDown( int cno );
	TP9_API int __stdcall IC_GSCWrite( int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToWrite, DWORD dwLengthToWrite, LPBYTE pbByteToWrite );
	TP9_API int __stdcall IC_GSCRead( int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToRead, DWORD dwLengthToRead, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength );
	TP9_API int __stdcall IC_GSCVerify( int cno, BYTE bCardType, DWORD dwCodeLength, LPBYTE pbCodeToVerify );
	TP9_API int __stdcall IC_GSCErase( int cno, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToErase, DWORD dwLengthToErase );
	TP9_API int __stdcall IC_GSCRestore( int cno, BYTE bCardType, BYTE bSubCardType );
#endif

	// ---------------------------
	// FOR RF CARD
	// ---------------------------
	TP9_API int __stdcall RF_CardInsert( );
	TP9_API int __stdcall RF_CardCheck(int nDev, int nCardType);
	TP9_API int __stdcall RF_PowerOn(int nDev, int* pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData);
	TP9_API int __stdcall RF_PowerOnEx(int nDev, int pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData);
	TP9_API int __stdcall RF_PowerOff(int nDev);
	TP9_API int __stdcall RF_Read(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, char nKey, DWORD* pdwRXSize, BYTE* lpbRXData);
	TP9_API int __stdcall RF_Write(int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, DWORD* pdwRXSize, BYTE* lpbRXData, char nKey, BYTE* pPW);
	TP9_API int __stdcall RF_Increment( int nDev, int nSourceBlock, int nTargetBlock, BYTE* pIncValue, char nKey, BYTE* pPW );
	TP9_API int __stdcall RF_Decrement( int nDev, int nSourceBlock, int nTargetBlock, BYTE* pDecValue, char nKey, BYTE* pPW );
	TP9_API int __stdcall RF_Download( char *pFile );

	// ---------------------------
	// 텍스트를 이미지 파일로 변환
	// ---------------------------
	TP9_API int __stdcall TextToBmpMake(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize);
	TP9_API int __stdcall TextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution);
	TP9_API int __stdcall ColorTextToBmpMakeEx(char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution, DWORD Color);
	#if defined(USE_BARCODE)
	TP9_API int __stdcall Image_BarcodeFile(int output_type, char *pFile, void *pData);
	TP9_API int __stdcall Image_BarcodeHBitmap(int output_type, HBITMAP *phBitmap, void *pData);
	#endif

	// ---------------------------
	// 이미지 파일을 원하는 크기로 조정
	// ---------------------------
	TP9_API int __stdcall Image_Adjust(char *pSrcFile, LPRECT pSrcRect, char *pDstFile, LPRECT pDstRect, int iMode1, int iMode2, int iMode3);

	// ---------------------------
	// 인쇄할 이미지를 버퍼에 저장/인쇄하는 함수
	// ---------------------------
	TP9_API int __stdcall SetPrinterProfile( int nBPC, int nRGB, char *pMonitorProfile, char *pPrinterProfile );
	TP9_API int __stdcall Image_SaveMode(int nMode);
	TP9_API int __stdcall Image_Buffer_Clear (int iType);
	TP9_API int __stdcall Image_Send_Memory( int nImageType, HANDLE hMemory, int nDstX, int nDstY, int nRibbonType, int nPanel );
	TP9_API int __stdcall Image_Send (DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode);
	TP9_API int __stdcall Image_SendEx (DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode, BYTE nGrayLevel);
	TP9_API int __stdcall Image_ProcessSend (DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE nGrayLevel, BYTE nMode);
	TP9_API int __stdcall Image_VarnishSend (DWORD xPos, DWORD yPos, char* varnishimage, BYTE level, BYTE mode);
	TP9_API int __stdcall Image_VarnishSendEx (int nType, LPRECT pBlack, LPRECT pWhite);
	TP9_API int __stdcall Panel_Skip( int nPanel, int nPrintSide );
	TP9_API int __stdcall Image_Transfer(int nRibbon, int nPanel, int nPrintSide);
	TP9_API int __stdcall Image_Print (int nColorMode , int nOverlayMode);
	TP9_API int __stdcall Image_PrintEx (int nRibbonType , int nBlackMode);
	TP9_API int __stdcall Print_Panel(int nRibbon, int nPanel, int nPrintSide, int nCardPosition);

	TP9_API int __stdcall GetRFTagRibbonType(int *type);
	TP9_API	int __stdcall N_StartOfPrinting ( int p1 );
	TP9_API	int __stdcall N_SetPrintType ( int p1, int p2, int p3 );
	TP9_API	int __stdcall N_ClearImageBuffer ( int p1, int p2 );
	TP9_API	int __stdcall N_SetImageBuffer ( int p1, int p2, int p3, int p4, int p5, int p6, char *pFile );
	TP9_API	int __stdcall N_TransferImageData ( int p1, int p2, int p3, int p4, int p5, char *pFile );
	TP9_API	int __stdcall N_PrintPanel ( int p1, int p2 );
	TP9_API	int __stdcall N_EndOfPrint ( int nPanel, int *pPanelCount, int *pJobNo );
	TP9_API	int __stdcall N_CancelPrintJob ( int nJobNo );
	TP9_API	int __stdcall N_PrintJobStatus ( int *pJobStatus );
	TP9_API	int __stdcall N_PrintSpeed ( int p1 );
	TP9_API	int __stdcall N_SetIPAddress ( int p1, BYTE *pAddress);
	TP9_API	int __stdcall N_GetIPAddress ( int p1, BYTE *pAddress);

	// ---------------------------
	// 프린터 드라이버에서 인쇄 색상 조정하기 위해 호출한다.
	// ---------------------------
	TP9_API int __stdcall SetColorAdjust( WORD Type );

	#if defined(USE_DISPENSER)
	TP9_API int __stdcall DP_Enquiry( BYTE *pStatus );
	TP9_API int __stdcall DP_ErrorClear( BYTE *pStatus );
	TP9_API int __stdcall DP_GetStatusRequest( BYTE *pStatus );
	TP9_API int __stdcall DP_SetBaudRate( int nBPS, BYTE *pStatus );
	TP9_API int __stdcall DP_GetFirmwareVersion( BYTE *pStatus );
	TP9_API int __stdcall DP_Dispensing( int nStacker, int nExit, BYTE *pStatus );
	TP9_API int __stdcall DP_MoveOption( int nOption, BYTE *pStatus );
	TP9_API int __stdcall DP_DirectCommand( int setTimeOut, BYTE *pCommand, int nCmdSize, BYTE *pResponse, int *pnRspSize );
	#endif	// USE_DISPENSER

#else

	// ---------------------------
	// LOG FILE SETTING
	// ---------------------------
	typedef	int (__stdcall *pfnSetLogPathFile ) ( char *pLogFile );
	typedef	int (__stdcall *pfnSetLogPathFileMonth ) ( char *pLogPath, char *pLogFile, int nMonth );

	// ---------------------------
	// DEVICE INFO. SETTING, SEARCH, OPEN, CLOSE
	// ---------------------------
	typedef	int (__stdcall *pfnGetTpclType )( int *nType );
	typedef	int (__stdcall *pfnSetOpenType )( int OpenType );
	typedef	int (__stdcall *pfnSetRetryTimes )( int nTimes );
	typedef	int (__stdcall *pfnSetDescription ) ( char *pDescription );
	typedef	int (__stdcall *pfnSetConnectPort ) ( int DevicePort );
	typedef	int (__stdcall *pfnListDevices ) ( DWORD *pArg1, char *pArg2, DWORD pArg3 );
	typedef	int (__stdcall *pfnOpenDevice )( char *pName, int iPortNum );
	typedef	int (__stdcall *pfnOpenDeviceEx )( char *pName, DWORD dwFlags );
	typedef int (__stdcall *pfnCloseDevice )( int iDeviceType );
	typedef int (__stdcall *pfnTP9_FreeLibrary ) ( int nType );
	typedef	int (__stdcall *pfnGetConnectedDevices )( DWORD dwDevice, DWORD *pdwCount );
	typedef	int (__stdcall *pfnGetDeviceInformation )( DWORD dwDevice, DWORD dwIndex, BYTE *pDesc, BYTE *pSerial );
	typedef	int (__stdcall *pfnGetNetworkBoard )( int *pCount, LPBYTE pConfig );
	typedef	int (__stdcall *pfnSetNetworkBoard )( LPBYTE pConfig );

	// ---------------------------
	// DEVICE RESET, Get Firmware/RF Version
	// ---------------------------
	typedef int (__stdcall *pfnResetDevice )( );
	typedef int (__stdcall *pfnGet_PrinterInfo)( char*InfoBuffer );
	typedef	int (__stdcall *pfnGet_PrinterInfoEx )( char *pVersion, int *pType, int *pModel );
	typedef int (__stdcall *pfnGet_ModuleInfo)( char ModuleType, char *InfoBuffer );

	// ---------------------------
	// GET STATUS/MESSAGE, CLEAR ERROR
	// ---------------------------
	typedef int (__stdcall *pfnGet_Status )( char* st0, char *st1 );
	typedef int (__stdcall *pfnGet_StatusEx )( char* st0, char *st1 );
	typedef	int (__stdcall *pfnGetStatusCode )( int *pStatus );
	typedef int (__stdcall *pfnDeviceErrorClear )( );
	typedef int (__stdcall *pfnSet_LanguageID )( WORD nLangID );
	typedef int (__stdcall *pfnGet_StatusMessage )( int nError, int nType, char *pMessage );

	// ---------------------------
	// CARD CONTROL (CHECK, INSERT, EJECT, FLIP)
	// ---------------------------
	typedef int (__stdcall *pfnCheckFeeder )( int *pStatus );
	typedef int (__stdcall *pfnCard_Insert )( );
	typedef int (__stdcall *pfnCard_InsertEx )( int nOption);	// [20120314]
	typedef int (__stdcall *pfnCard_Eject )( int cmd );
	typedef int (__stdcall *pfnCard_EjectEx )( int nOption);	// [20110722]
	typedef int (__stdcall *pfnCard_Flip )( );
	typedef int (__stdcall *pfnCard_MoveFlipperToPrinter )( );
	typedef int (__stdcall *pfnCard_Reject )( int p1 );
	typedef int (__stdcall *pfnCheckRibbon )( int *nRibbon );
	typedef	int (__stdcall *pfnCheckRibbonEx )( int *pRibbon, int *pRfRibbon );
	typedef int (__stdcall *pfnSetRibbonSync )( );
	typedef	int (__stdcall *pfnSetRibbonSyncEx )( int p1 );
	typedef	int (__stdcall *pfnCheckRibbonCount )(int *pCount);

	// ---------------------------
	// 프린터의 인쇄 설정 (제어)
	// ---------------------------
	typedef int (__stdcall *pfnGetRibbonSensor )( int *nSensor );
	typedef int (__stdcall *pfnGetRibbonSensorEx )(int *pSensor, int *pSensor2);
	typedef int (__stdcall *pfnGetRibbonInfo )( int nType, char *pData, int *pLen );
	typedef int (__stdcall *pfnGetRibbonInfoEx )( int nType, int *pTagRibbon, int *pTagCount );
	typedef int (__stdcall *pfnGetMACAddress )( BYTE *pAddress );

	typedef int (__stdcall *pfnGetParameters )( int nItem, char *pData, int *pLen );
	typedef	int (__stdcall *pfnGetParametersEx )( int p1, int *pValue );
	typedef	int (__stdcall *pfnSetParametersEx )( int p1, int p2 );
	typedef int (__stdcall *pfnSetTPHResistance )( int nResistance );
	typedef int (__stdcall *pfnAdjustIntensity )( int nColor, int nIntensity );
	typedef int (__stdcall *pfnSetCardInputDirection )( int nDir );
	typedef int (__stdcall *pfnSetRibbonType )( int nRibbon , int nHalfStart, int nHalfWidth );
	typedef	int (__stdcall *pfnSetRibbonTypeEx )( int p1, int p2 );
	typedef int (__stdcall *pfnOffsetXaxisPrintStartPosition )( int nXstart, int nXend );
	typedef int (__stdcall *pfnOffsetYaxisPrintStartPosition )( int nYstart );
	typedef int (__stdcall *pfnPrintPintAdjust )( int nOffset );
	typedef int (__stdcall *pfnSetMonoPrintMode )( int nMode );
	typedef int (__stdcall *pfnSetCardInputOption )( int nMode );
	typedef	int (__stdcall *pfnGetPrintCount )( DWORD *pCount );
	typedef	int (__stdcall *pfnGetProduction )( char *pManufacturer, char *pDescription, char *pSerialNumber );
	typedef	int (__stdcall *pfnSetProduction )( char *pManufacturer, char *pDescription, char *pSerialNumber );
	typedef	int (__stdcall *pfnGetProductSerialNo )( char *pSerialNumber );
	typedef	int (__stdcall *pfnSetProductSerialNo )( char *pSerialNumber );
	typedef int (__stdcall *pfnSetLCDContrast )( int nValue );
	typedef int (__stdcall *pfnGetLCDContrast )( int *pnValue );
	typedef int (__stdcall *pfnSetRibbonSensorADC )( int nValue );
	typedef int (__stdcall *pfnGetRibbonSensorADC )( int *pnValue );
	typedef int (__stdcall *pfnSetRibbonSensor )( );
	typedef int (__stdcall *pfnGetRibbonMotorDuty )( int *pnValue );
	typedef int (__stdcall *pfnSetRibbonMotorDuty )( int nValue );
	typedef int (__stdcall *pfnSetRibbonSyncOption )( int nType );
	typedef int (__stdcall *pfnSetCardReadyPosition )( int nType );
	typedef int (__stdcall *pfnGetCardControlTime )( int *pEjectTime, int *pInsertTime );
	typedef int (__stdcall *pfnSetCardControlTime )( int  nEjectTime, int nInsertTime );
	typedef int (__stdcall *pfnGetModelNation )( int *pModelType, int *pOemType );
	typedef int (__stdcall *pfnCleaningMode )( );
	typedef int (__stdcall *pfnSelfTestMode )( int  nMode );
	typedef int (__stdcall *pfnChangePassword )( int iType, char *pOldPassword, char *pNewPassword );
	typedef int (__stdcall *pfnLockPrinter )( int iType, char *pPassword );
	typedef int (__stdcall *pfnSetEncryption )( int iType, LPBYTE pKeyData );
	typedef int (__stdcall *pfnSetDigitalPotentiometer )( int type, int value );
	typedef int (__stdcall *pfnGetDigitalPotentiometer )( int type, int *pvalue );

	// ---------------------------
	// FOR DOWNLOAD
	// ---------------------------
	typedef int (__stdcall *pfnDownloadFirmware )( char *pFile );
	typedef	int (__stdcall *pfnDownloadFWFile )( char *pFile );
	typedef	int (__stdcall *pfnDownloadFWErase )( );
	typedef	int (__stdcall *pfnDownloadFWDataLoad )( );
	typedef	int (__stdcall *pfnDownloadFWVerify )( );
	typedef	int (__stdcall *pfnDownloadFWReset )(int nType );
	typedef	int (__stdcall *pfnDownloadFWStatus )( int *pStep, int *pStatus  );
	typedef	int (__stdcall *pfnDownloadStatus )( int *pStep, int *pStatus  );

	// ---------------------------
	// FOR BUZZER
	// ---------------------------
	typedef int (__stdcall *pfnBuzzer )( BYTE byCount, int iOntime, int iOfftime );

	// ---------------------------
	// FOR LCD CONTROL/DISPLAY
	// ---------------------------
	typedef int (__stdcall *pfnLCD_DISPLAY )( BYTE byMode, BYTE *byData, int nDataLen );
	typedef int (__stdcall *pfnUserLCDMemoryWrite )( int iType, int nLCDLine, int nDataFormat, char *pTxData );
	typedef int (__stdcall *pfnUserLCDMemoryWriteEx )( int iType, int nLCDLine, int nDataFormat, char *pFilename );
	typedef int (__stdcall *pfnUserLCDMemoryRead )( int iType, int nLCDLine, char *pRxBuf, long *pRxLen );
	typedef int (__stdcall *pfnUserLCDMemoryReadEx )( int iType, int nLCDLine, char *pFilename );

	// ---------------------------
	// FOR USER'S MEMORY
	// ---------------------------
	typedef int (__stdcall *pfnUserMemoryInit )( );
	typedef int (__stdcall *pfnUserMemoryInitEx )( int iType );
	typedef int (__stdcall *pfnUserMemoryWrite )( int nOffset, int nWriteLength, BYTE *pWriteData  );
	typedef int (__stdcall *pfnUserMemoryWriteEx )( int iType, long nOffset, long nLength, char *pTxData );
	typedef int (__stdcall *pfnUserMemoryRead )( int nOffset, int nReadLength, BYTE *pReadData );
	typedef int (__stdcall *pfnUserMemoryReadEx )( int iType, long nOffset, long nLength, char *pRxBuf, long *pRxLen );

	// ---------------------------
	// Directly Send/Receive
	// ---------------------------
	typedef int (__stdcall *pfnDeviceDirectSend )( char *cmdbuf );
	typedef int (__stdcall *pfnDeviceDirectSend2 )( char *cmdbuf, int nLen, int nTimeOut, int nRcv );
	typedef int (__stdcall *pfnDeviceDirectGet2 )( char *pGetbuf, int *pLen );

	// ---------------------------
	// FOR MS CARD
	// ---------------------------
	typedef	int (__stdcall *pfnMS_GetCoercivity )( int nTrack, int *pnCoercivity );
	typedef	int (__stdcall *pfnMS_EncodeOption )( int nTrack, int nOption, int nCoercivity );
	typedef int (__stdcall *pfnMS_SendEncodeData )( char* sziso1, char* sziso2, char* sziso3 );
	typedef	int (__stdcall *pfnMS_Coercivity )( int p1 );
	typedef int (__stdcall *pfnMS_Write )( int iTrack, char* sziso1, char* sziso2, char* sziso3 );
	typedef int (__stdcall *pfnMS_WriteEx )( int iTrack, char* sziso1, char* sziso2, char* sziso3, int nCoercivity );
	typedef int (__stdcall *pfnMS_WriteExW)( int iTrack, LPWSTR sziso1, LPWSTR sziso2, LPWSTR sziso3, int nCoercivity );
	typedef int (__stdcall *pfnMS_WriteAll )( int iTrack, int nCoercivity, char* sziso1, char* sziso2, char* sziso3, char* szjis, int njis );
	typedef int (__stdcall *pfnMS_Read )( int iTrack, char* sziso1, char* sziso2, char* sziso3 );
	typedef int (__stdcall *pfnMS_ReadAll )( int iTrack, char* sziso1, char* sziso2, char* sziso3, char* szjis, int *njis );

	// ---------------------------
	// FOR IC CARD
	// ---------------------------
	typedef int (__stdcall *pfnCheckBoardType )( BYTE *pStatus) ;
	typedef	int (__stdcall *pfnCheckBoardTypeEx )( char *pIfmType, char *pSamType );
	typedef int (__stdcall *pfnCheckSIM )( int nSlot, int *pStatus) ;
	typedef int (__stdcall *pfnCheckSAM )( BYTE *pStatus) ;
	typedef int (__stdcall *pfnIC_ContactOn )( );
	typedef int (__stdcall *pfnIC_Eject )( int nCmd );
	typedef int (__stdcall *pfnIC_PowerOn )( int cno, DWORD * pdwRXSize, LPBYTE lpbRXData );
	typedef int (__stdcall *pfnIC_PowerOff )( int cno );
	typedef int (__stdcall *pfnIC_Input )( int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData );
	typedef int (__stdcall *pfnIC_Output )( int cno, DWORD dwTXSize, LPBYTE lpbTXData, DWORD *pdwRXSize, LPBYTE lpbRXData );
#if 1 //defined(GSC_FUNC)
	typedef int (__stdcall *pfnIC_GSCPowerUp )( int cno, BYTE bCardType, BYTE bSubCardType, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength );
	typedef int (__stdcall *pfnIC_GSCPowerDown )( int cno );
	typedef int (__stdcall *pfnIC_GSCWrite )( int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToWrite, DWORD dwLengthToWrite, LPBYTE pbByteToWrite );
	typedef int (__stdcall *pfnIC_GSCRead )( int cno, int iType, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToRead, DWORD dwLengthToRead, LPBYTE pbRecvBuffer, LPDWORD pcbRecvLength );
	typedef int (__stdcall *pfnIC_GSCVerify )( int cno, BYTE bCardType, DWORD dwCodeLength, LPBYTE pbCodeToVerify );
	typedef int (__stdcall *pfnIC_GSCErase )( int cno, BYTE bCardType, BYTE bSubCardType, DWORD dwAddressToErase, DWORD dwLengthToErase );
	typedef int (__stdcall *pfnIC_GSCRestore )( int cno, BYTE bCardType, BYTE bSubCardType );
#endif

	// ---------------------------
	// FOR RF CARD
	// ---------------------------
	typedef int (__stdcall *pfnRF_CardInsert )( );
	typedef int (__stdcall *pfnRF_CardCheck )( int nDev, int nCardType );
	typedef int (__stdcall *pfnRF_PowerOn )( int nDev, int* pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData );
	typedef int (__stdcall *pfnRF_PowerOnEx )( int nDev, int pnCardType,	DWORD* pdwRXSize, BYTE* lpbRXData );
	typedef int (__stdcall *pfnRF_PowerOff )( int nDev);
	typedef int (__stdcall *pfnRF_Read )( int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, char nKey, DWORD* pdwRXSize, BYTE* lpbRXData );
	typedef int (__stdcall *pfnRF_Write )( int nDev, int nCardType, int nBlock, DWORD nInLen, BYTE* pInBuf, DWORD* pdwRXSize, BYTE* lpbRXData, char nKey, BYTE* pPW );
	typedef int (__stdcall *pfnRF_Increment )( int nDev, int nSourceBlock, int nTargetBlock, BYTE* pIncValue, char nKey, BYTE* pPW );
	typedef int (__stdcall *pfnRF_Decrement )( int nDev, int nSourceBlock, int nTargetBlock, BYTE* pDecValue, char nKey, BYTE* pPW );
	typedef	int (__stdcall *pfnRF_Download )( char *pFile );

	// ---------------------------
	// 텍스트를 이미지 파일로 변환
	// ---------------------------
	typedef int (__stdcall *pfnTextToBmpMake )( char *cFileName, char *cStr, char *FontName, char FontType, int FontSize );
	typedef int (__stdcall *pfnTextToBmpMakeEx )( char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution );
	typedef int (__stdcall *pfnColorTextToBmpMakeEx )( char *cFileName, char *cStr, char *FontName, char FontType, int FontSize, int Resolution, DWORD Color );
	#if defined(USE_BARCODE)
	typedef int (__stdcall *pfnImage_BarcodeFile )(int output_type, char *pFile, void *pData);
	typedef int (__stdcall *pfnImage_BarcodeHBitmap )(int output_type, HBITMAP *phBitmap, void *pData);
	#endif

	// ---------------------------
	// 이미지 파일을 원하는 크기로 조정
	// ---------------------------
	typedef int (__stdcall *pfnImage_Adjust )( char *pSrcFile, LPRECT pSrcRect, char *pDstFile, LPRECT pDstRect, int iMode1, int iMode2, int iMode3 );

	// ---------------------------
	// 인쇄할 이미지를 버퍼에 저장/인쇄하는 함수
	// ---------------------------
	typedef int (__stdcall *pfnSetPrinterProfile )( int nBPC, int nRGB, char *pMonitorProfile, char *pPrinterProfile );
	typedef int (__stdcall *pfnImage_SaveMode )( int nMode );
	typedef int (__stdcall *pfnImage_Buffer_Clear )( int iType );
	typedef int (__stdcall *pfnImage_Send_Memory )( int nImageType, HANDLE hMemory, int nDstX, int nDstY, int nRibbonType, int nPanel );
	typedef int (__stdcall *pfnImage_Send )( DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode );
	typedef int (__stdcall *pfnImage_SendEx )( DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE level, BYTE mode, BYTE nGrayLevel );
	typedef int (__stdcall *pfnImage_ProcessSend )( DWORD xPos, DWORD yPos, char* imagefilename, char sw1,char sw2, BYTE nGrayLevel, BYTE nMode );
	typedef int (__stdcall *pfnImage_VarnishSend )( DWORD xPos, DWORD yPos, char* varnishimage, BYTE level, BYTE mode );
	typedef int (__stdcall *pfnImage_VarnishSendEx )( int nType, LPRECT pBlack, LPRECT pWhite );
	typedef int (__stdcall *pfnPanel_Skip )( int nPanel, int nPrintSide );
	typedef int (__stdcall *pfnImage_Transfer )( int nRibbon , int nPanel, int nPrintSide );
	typedef int (__stdcall *pfnImage_Print )( int nColorMode , int nOverlayMode );
	typedef int (__stdcall *pfnImage_PrintEx )( int nRibbonType , int nBlackMode );
	typedef int (__stdcall *pfnPrint_Panel )( int nRibbon, int nPanel, int nPrintSide, int nCardPosition );

	typedef	int (__stdcall *pfnGetRFTagRibbonType)(int *type);
	typedef	int (__stdcall *pfnN_StartOfPrinting )( int p1 );
	typedef	int (__stdcall *pfnN_SetPrintType )( int p1, int p2, int p3 );
	typedef	int (__stdcall *pfnN_ClearImageBuffer )( int p1, int p2 );
	typedef	int (__stdcall *pfnN_SetImageBuffer )( int p1, int p2, int p3, int p4, int p5, int p6, char *pFile );
	typedef	int (__stdcall *pfnN_TransferImageData )( int p1, int p2, int p3, int p4, int p5, char *pFile );
	typedef	int (__stdcall *pfnN_PrintPanel )( int p1, int p2 );
	typedef	int (__stdcall *pfnN_EndOfPrint )( int nPanel, int *pPanelCount, int *pJobNo );
	typedef	int (__stdcall *pfnN_CancelPrintJob )( int nJobNo );
	typedef	int (__stdcall *pfnN_PrintJobStatus )( int *pJobStatus );
	typedef	int (__stdcall *pfnN_PrintSpeed )( int p1 );
	typedef	int (__stdcall *pfnN_SetIPAddress )( int p1, BYTE *pAddress);
	typedef	int (__stdcall *pfnN_GetIPAddress )( int p1, BYTE *pAddress);
	// ---------------------------
	// 프린터 드라이버에서 인쇄 색상 조정하기 위해 호출한다.
	// ---------------------------
	typedef int (__stdcall *pfnSetColorAdjust )( WORD Type );

	#if defined(USE_DISPENSER)
	typedef	int (__stdcall *pfnDP_Enquiry )( BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_ErrorClear )( BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_GetStatusRequest )( BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_SetBaudRate )( int nBPS, BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_GetFirmwareVersion )( BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_Dispensing )( int nStacker, int nExit, BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_MoveOption )( int nOption, BYTE *pStatus );
	typedef	int (__stdcall *pfnDP_DirectCommand )( int setTimeOut, BYTE *pCommand, int nCmdSize, BYTE *pResponse, int *pnRspSize );
	#endif	// USE_DISPENSER

#endif	// TP9000_EXPORTS (end)
