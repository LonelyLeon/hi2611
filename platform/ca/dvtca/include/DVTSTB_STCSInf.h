//本文件定义要求机顶盒实现并提供给安全管控模块模块使用的接口。所有HRESULT返回值为DVTSTC_OK都表示成功，其他值表示失败。

#ifndef _DVTSTB_STCSINTERFACE_H_2004_12_31_
#define _DVTSTB_STCSINTERFACE_H_2004_12_31_

#include "DVTSTCS_STBDataPublic.h"

#ifdef  __cplusplus
extern "C" {
#endif 
//线程函数地址类型
typedef void (*pThreadFunc) (void);

/*----------------------------------以下接口是STB提供给STCS调用--------------------------------------------*/
/*++
功能：获得机顶盒分配给STCS的flash空间的起点地址和大小（以字节为单位）。
参数：
	ppStartAddr:			机顶盒分配给STCS的flash空间的开始地址。
	lSize:					输出机顶盒分配给STCS的flash空间的大小。
--*/
HRESULT DVTSTBSTC_GetDataBufferAddr(long * lSize, char ** ppStartAddr);

/*++
功能：读取保存在机顶盒flash中的信息。
参数：
	pStartAddr:				要读取的存储空间的开始地址。
	plDataLen:				输入为要读取的最长数据值；输出为实际读取的大小。
	pData:					存放输出数据。
--*/
HRESULT DVTSTBSTC_ReadDataBuffer(const char * pStartAddr, long * plDataLen, BYTE * pData);

/*++
功能：向机顶盒的存储空间写信息。
参数：
	lStartAddr:				要写的存储空间的开始地址。
	plDataLen:				输入为要写的数据的长度；输出为写入的实际长度。
	pData:					要写的数据。
--*/
HRESULT DVTSTBSTC_WriteDataBuffer(const char * pStartAddr, long * plDataLen, const BYTE * pData);

/*++
功能：读取保存在机顶盒eeprom中的信息。
参数：
	plDataLen:				输入为要读取的最长数据值；输出为实际读取的大小。
	pData:					存放输出数据。
注意: 用flash模拟的话，必须分配一个独立的page,以防丢失
--*/
HRESULT DVTSTBSTC_GetDataFromEeprom(long * plDataLen, BYTE * pData);

/*++
功能：向机顶盒的eeprom存储空间写信息。
参数：
	plDataLen:				输入为要写的数据的长度；输出为写入的实际长度。
	pData:					要写的数据。
注意: 用flash模拟的话，必须分配一个独立的page,以防丢失
--*/
HRESULT DVTSTBSTC_SaveDataToEeprom(long * plDataLen, const BYTE * pData);

/*++
功能：挂起当前线程。
参数：
	dwMicroseconds:			毫秒。
--*/
HRESULT DVTSTBSTC_Sleep( int dwMicroseconds );

/*++
功能：初始化信号量,初始化后信号量没有信号。
参数：
	pSemaphore:				指向信号量的指针。
--*/
HRESULT DVTSTBSTC_SemaphoreInit( DVTSTC_Semaphore * pSemaphore );

/*++
功能：给信号量加信号。
参数：
	pSemaphore: 			指向信号量的指针。
--*/
HRESULT DVTSTBSTC_SemaphoreSignal( DVTSTC_Semaphore * pSemaphore );

/*++
功能：等待信号量,等待成功之后,信号量为无信号。
参数：
	pSemaphore: 			指向信号量的指针。
--*/
HRESULT DVTSTBSTC_SemaphoreWait( DVTSTC_Semaphore * pSemaphore );

/*++
功能：STCS模块向机顶盒注册线程。
参数：
	szName:					注册的线程名称。
	pTaskFun:				要注册的线程函数。
--*/
HRESULT DVTSTBSTC_RegisterTask(const char * szName, pThreadFunc pTaskFun);

/*++
功能：设置过滤器接收STCS私有数据。
参数：
	byReqID:				请求收表的请求号。机顶盒应该保存该数据，接收到STCS私有数据后调用DVTSTCSTB_StreamGuardDataGot()时应该将该数据返回。
	wEcmPID:				需要过滤的流的PID。
	szFilter:				过滤器的值
	szMask:					过滤器的掩码，与过滤器对应，当szMask的某一bit位为0时表示要过滤的表对应的bit位不需要与szFilter里对应的bit位相同，当szMask某一位为1时表示要过滤的表对应的bit位一定要与szFilter里对应的bit位相同。
	byLen:					过滤器的长度，为8或12。
	nWaitSeconds:			收此表最长的等待时间，如果为0则无限等待，单位秒。
--*/
HRESULT DVTSTBSTC_SetStreamGuardFilter(BYTE byReqID, WORD wPID, const BYTE * szFilter, const BYTE * szMask, BYTE byLen, int nWaitSeconds);

/*++
功能：CA程序用此函数，将解扰数据设置给高安芯片。
参数：
	wEcmPID:				CW所属的ECMPID。
	byDataLen:				szData的长度。
	szData:					加密的CW和Key。
	bTapingControl:			true：允许录像,false：不允许录像。
返回值：需将真实的芯片底层接口返回值直接返回给CA
--*/
HRESULT DVTSTBSTC_SetDescrCW(WORD wEcmPID, BYTE byDataLen, const BYTE * szData, bool bTapingControl);
/*++
功能：打印调试信息。
参数：
	pszMsg:					调试信息内容。
--*/
void DVTSTBSTC_AddDebugMsg(const char * pszMsg);

/*--------------------------- 类型1的界面：不允许用户通过遥控器取消显示的界面 -----------------------*/

/*
功能：显示用户不能观看节目等提示信息，下面两个函数对应使用。
参数：	
	byMesageNo:				要显示的消息编号。
--*/
void   DVTSTBSTC_ShowPromptMessage(BYTE byMesageNo);
void   DVTSTBSTC_HidePromptMessage(void);

/*
功能：CA模块用此函数通知机顶盒按CA前端的发送的OSD优先级（0~3）来有区别地显示普通、重要OSD。重要OSD用大号字体和特殊颜色显示。可以是同步显示，也可以是异步显示。
参数:	
	byPriority:	OSD优先级，0~3，优先级递增。
	szOSD:		用于显示的OSD信息。
说明：
	用户可以通过遥控器取消当前OSD显示。
--*/
void	DVTSTBSTC_ShowOSDMsg(BYTE byPriority,const char * szOSD);

/*--------------------------- 应急广播 -----------------------*/
/*++
功能：应急广播, 切换到指定频道。
参数：
	wOriNetID:				原始网络ID。
	wTSID:					传送流ID。
	wServiceID:				业务ID。
	wDuration:				持续秒数。
--*/
void DVTSTBSTC_UrgencyBroadcast(WORD wOriNetID, WORD wTSID, WORD wServiceID, WORD wDuration);

/*++
功能：取消应急广播，切换回应急广播前用户观看的频道。
参数：无。
--*/
void DVTSTBSTC_CancelUrgencyBroadcast( void );

/*++
功能:获取芯片的CPUID。
参数:
	pbyChipID:		芯片提供的ChipID，最多8个字节
	pbyChipIDLen:	ChipID实际长度
返回值:
	true:			获取ChipID成功
	false:			获取ChipID失败
--*/
bool DVTSTBSTC_GetChipID(BYTE * pbyChipID,BYTE * pbyChipIDLen);

/*++
功能:获取PSI表中的台站号，用于台站锁定功能
参数:
	pdwData:	机顶盒提供的，从Station表中获取的PDSD值
返回值:
	0:		获取成功
	其它值:	获取失败
	
使用说明:
	如果不实现Station区域锁定功能，此函数返回-1且(*pdwData)置为0即可
--*/
HRESULT	DVTSTBSTC_GetStationValue(DWORD * pdwData);

/*
功能：通知STB隐藏指纹。
--*/
void DVTSTBSTC_HideFingerPrint (void);
/*
功能：通知STB按字符格式显示指纹。
--*/
void DVTSTBSTC_ShowCharaterFingerPrint(const SDVTSTCCharaterFingerMsg *pCharaterFingerMsg);

/*
功能：通知STB按点阵格式显示指纹。
--*/
void DVTSTBSTC_ShowDotMatrixFingerPrint(const SDVTSTCDotMatrixFingerMsg *pDotMatrixFingerMsg);

/*++
功能：显示新邮件的标志。
参数：
	byShow:					标志类型。含义如下：
							DVTSTCS_NEW_EAMIL				新邮件通知。
							DVTSTCS_NEW_EMAIL_NO_ROOM		有新邮件，但Email空间不够。
							DVTSTCS_EMAIL_NONE				没有新邮件。
--*/
void DVTSTBSTC_EmailNotify(BYTE byShow);

/*++
功能：重要邮件弹出显示，用户不可以遥控退出。
参数：
pEmailMsg:				要显示的内容，机顶盒需要留1500字节空间
--*/
void DVTSTBSTC_ShowForceEmailMsg(const SDVTSTCEmailMsg *pEmailMsg );

/*++
功能：取消强制显示信息
参数：
无
--*/
void DVTSTBSTC_HideForceEmailMsg(void);
/*------------------------------------------以上接口是STB供给STCS调用---------------------------------------------------*/

#ifdef  __cplusplus
}
#endif
#endif  
