//本文件定义CA模块实现提供给STB调用的接口

#ifndef _DVTSTCS_STBINTERFACE_H_2004_12_31_
#define _DVTSTCS_STBINTERFACE_H_2004_12_31_

#include "DVTSTCS_STBDataPublic.h"

#ifdef  __cplusplus
extern "C" {
#endif 

/*-----------------------------------以下接口是STCS提供给STB调用----------------------------------*/

/*++
功能：机顶盒启动的时候调用，对STCS模块初始化。
返回值：
	true				初始化成功。
	false				初始化失败。
--*/
bool DVTSTCSTB_Init(void);

/*++
功能：机顶盒获得STCSID后调用该接口判断STCSID是否有效，如果有效则返回true，否则返回false。
参数：
	wCaSystemID:		机顶盒分析SI/PSI信息获得的STCSID。
返回值：
	true				STCSID有效
	false				STCSID无效
--*/
bool DVTSTCSTB_STCSIDVerify(WORD wCaSystemID);

/*++
功能：设置当前正在收看的节目的详细信息。
参数：
	pServiceInfo:		SDVTSTCServiceInfo结构，描述节目的详细信息。
说明：
	当用户换频道时，机顶盒必须要调用此函数。如果当前频道为不加扰的频道，传过来的m_wEcmPid设为0。
--*/
void DVTSTCSTB_SetCurEcmInfo(const SDVTSTCServiceInfo * pServiceInfo);

/*++
功能：设置EMMPID，STCS模块将根据设置的EMMPID信息进行EMM数据接收处理。
参数：
	wEmmPid:			CAT表中包含的descriptor中将有CA_system_ID及CA_PID，调用DVTSTCSTB_STCSIDVerify()校验有效的CA_PID即为EMM PID。
说明:
	当机顶盒收到CAT表后，机顶盒需要调用此函数，将EMM PID传过来。
--*/
void DVTSTCSTB_SetEmmPid(WORD wEmmPid);

/*++
功能：机顶盒主程序在收到STCS私有数据或者Time_Out，调用这个接口将数据提供给STCS模块处理。
参数：
	byReqID：				当前请求收取私有表的请求号，与DVTSTBSTC_SetStreamGuardFilter里的byReqID对应
	bSuccess：				收取数据有没有成功，成功为true，失败为false
	wPID:					接收的数据的流的PID。
	byszReceiveData：		收取的私有数据
	wLen：					收取到的私有数据的长度
--*/
void DVTSTCSTB_StreamGuardDataGot(BYTE byReqID, bool bSuccess, WORD wPID, WORD wLen, const BYTE * byszReceiveData);

/*++
功能：获得STCS供应商信息。
参数：
	pManu					指向保存返回信息的数组地址。
返回值：
	DVTSTC_OK				成功
	其他					失败
--*/
HRESULT DVTSTCSTB_GetStreamGuardManuInfo(SDVTSTCManuInfo * pManu);

/*++
功能：获得STCS运营商信息。
参数：
	wTVSID:					STCS运营商的ID  如果是－1 则返回所有的运营商信息
	pOperatorInfo:			指向保存返回信息的数组地址
	pbyCount:				传进来的是数组的长度，返回时是实际返回运营商信息的个数
返回值：
	DVTSTC_OK				成功
	其他					失败
--*/
HRESULT DVTSTCSTB_GetOperatorInfo(WORD wTVSID, BYTE * pbyCount, SDVTSTCTvsInfo * pOperatorInfo);

/*++
功能：获得普通授权节目购买的情况，用于在机顶盒界面上显示。
参数：
	wTVSID:					运营商的内部编号。
	pEntitleCount:			输入时为数组的最大个数，输出时为实际获得的个数。
	psEntitles:				返回的授权数组。						
返回值：
	DVTSTC_OK					成功
	DVTSTCERR_STB_TVS_NOT_FOUND	没有找到符合要求的运营商
	其他						失败
--*/
HRESULT DVTSTCSTB_GetServiceEntitles(WORD wTVSID, BYTE * pEntitleCount, SDVTSTCServiceEntitle * psEntitles);

/*++
功能：打开或关闭调试信息。
参数：
	bDebugMsgSign:			打开调试信息标志，1:打开调试信息;0:关闭调试信息。
--*/
void DVTSTCSTB_AddDebugMsgSign(bool bDebugMsgSign);

/*
功能：机顶盒显示完一个OSD消息后，用这个接口来通知CA模块。
参数:	
	wDuration:				消息显示的具体时间，单位为秒。
--*/
void DVTSTCSTB_ShowOSDMsgOver(WORD wDuration);

/*++
功能:机顶盒获取E-mail个数接口。
参数:
	*pEmailCount:			机顶盒中E-mail总个数。
	*pNewEmailCount:		机顶盒中未读过的E-mail个数。
返回值：
	DVTSTC_OK				成功
	其他					失败
--*/
HRESULT DVTSTCSTB_GetEmailCount(WORD * pEmailCount, WORD * pNewEmailCount);

/*++
功能:机顶盒获取多个E-mail简要信息接口。
参数:
	*pEmailCount:			输入时为数组总个数，输出时为机顶盒中E-mail总个数。
	*pEmail:				获取的E-mail数组。
返回值:
	DVTSTC_OK:				获取E-mail成功。
	DVTSTCERR_STB_EMAILBOX_EMPTY:	E-mail信箱为空。
--*/
HRESULT DVTSTCSTB_GetEmailHead(WORD * pEmailCount, SDVTSTCEmailInfo * pEmail);

/*++
功能:机顶盒获取一个E-mail的内容。
参数:
	tVersion:				E-mail版本。
	*pEmail:				获取的E-mail结构。
返回值:
	DVTSTC_OK:				获取E-mail成功。
	DVTSTCERR_STB_NO_EMAIL:	没有此E-mail。
--*/
HRESULT DVTSTCSTB_GetEmailContent(DWORD tVersion, SDVTSTCEmailContent * pEmail);

/*++
功能:机顶盒看完E-mail后，通知STCS的接口。
参数:
	tVersion:				E-mail版本。
返回值:
	DVTSTC_OK:				设置E-mail为已读成功。
	其他					失败
--*/
HRESULT DVTSTCSTB_EmailRead(DWORD tVersion);

/*++
功能:机顶盒删除E-mail接口。
参数:
	tVersion:				E-mail版本。如果为-1，表示删除邮箱中所有email，否则，为具体的id。
返回值:
	DVTSTC_OK:				删除E-mail成功。
	DVTSTCERR_STB_NO_EMAIL:	要删除的E-mail不存在。
	其他					失败
--*/
HRESULT DVTSTCSTB_DelEmail(DWORD tVersion);

/*
功能: 获取区域信息
参数:
	psStationInfo				区域信息
返回值:
	0:						成功
	其他值:					失败
*/	
HRESULT DVTSTCSTB_GetStationInfo(SDVTCAStationInfo * psStationInfo);

/*++
功能：机顶盒获得政务图片后调用该接口传入图片的CRC32判断图片是否合法，如果合法则返回true，否则返回false。
参数：
	 dwPicCRC32		图片的CRC32
返回值：
	true				政务图片合法
	false				政务图片非法
--*/
bool DVTCASTB_PICVerify(DWORD dwPicCRC32);
/*----------------------------------以上接口是STCS提供给STB调用--------------------------------------------*/




/*----------------------------------以下接口暂不实现，直接返回成功即可--------------------------------------------*/

/*++
功能：判断智能卡的PIN码
参数：
	pPin:					PIN码
返回值：
	DVTSTC_OK          				成功
	DVTSTCERR_STB_PIN_INVALID		输入PIN码错误
	DVTSTCERR_STB_PIN_LOCKED			PIN被锁定
--*/
HRESULT DVTSTCSTB_VerifyPin(const SDVTSTCPin * pPIN);

/*++
功能：判断卡是否被锁住。
参数：
	pbLocked:				输出参数，true表示锁住了，false表示没有。
返回值：
	DVTSTC_OK				成功
	其他					失败
--*/
HRESULT DVTSTCSTB_IsPinLocked(bool * pbLocked);

/*
功能：判断用户是否通过pin码验证。
参数：
	pbPass:				输出时true表示通过了了；false，表示没有。
*/
HRESULT DVTSTCSTB_IsPinPass(bool * pbPass);

/*++
功能：修改智能卡的PIN码。
参数：
	pNewPin:				新的PIN码。	
返回值：
	DVTSTC_OK          				成功
	DVTSTCERR_STB_PIN_LOCKED			PIN被锁定
说明:
	调用该函数之前要求确保调用过VerifyPin，并且成功。
--*/
HRESULT DVTSTCSTB_ChangePin(const SDVTSTCPin * pNewPin);

/*++
功能：获得智能卡目前最高观看级别。
参数：
	pbyRating:				保存观看级别。
返回值：
	DVTSTC_OK				成功
	其他					失败
说明:
	观看级别为3~18，共15级。初始值为18，即可以观看所有级别的节目。
--*/
HRESULT DVTSTCSTB_GetRating(BYTE * pbyRating);

/*++
功能：设置智能卡观看级别。
参数：
	byRating:				要设置的新的观看级别
返回值：
	DVTSTC_OK				成功
	其他					失败
说明:
	调用该函数之前要求确保调用过VerifyPin，并且成功。
--*/
HRESULT DVTSTCSTB_SetRating(BYTE byRating);

/*++
功能：获得智能卡当前设置的工作时间段。
说明：工作时段功能默认关闭，此时读到的工作时段始终是默认值00:00-23:59。局方需要时，可以在前端开启。
参数：
	pbyStartHour			开始工作的小时
	pbyStartMinute			开始工作的分钟
	pbyEndHour				结束工作的小时
	pbyEndMinute			结束工作的分钟
返回值：
	DVTSTC_OK				成功
	其他					失败
说明:
	工作时段初始值为00:00~23:59，即全天都能收看。
--*/
HRESULT DVTSTCSTB_GetWorkTime(BYTE * pbyStartHour, BYTE * pbyStartMinute, BYTE * pbyEndHour, BYTE * pbyEndMinute);

/*++
功能：设置智能卡工作时段。
参数：
	byStartHour			开始工作的小时
	byStartMinute			开始工作的分钟
	byEndHour				结束工作的小时
	byEndMinute			结束工作的分钟
返回值：
	DVTSTC_OK				成功
	其他					失败
说明:
	调用该函数之前要求确保调用过VerifyPin，并且成功。
--*/
HRESULT DVTSTCSTB_SetWorkTime(BYTE byStartHour, BYTE byStartMinute, BYTE byEndHour, BYTE byEndMinute);

/*
功能:获取用户自定义数据
参数:
	byType					自定义数据类型
	pdwUserDefData			用户自定义数据的DWORD类型指针
返回值:
	0:						成功
	其他值:					失败
*/
HRESULT DVTSTCSTB_GetUserDefData(BYTE byType, DWORD *pdwUserDefData);

/*
功能:切换提示语言，机顶盒CA模块初始化后调用
参数:
	byLanguage               语言类型DVTSTC_LANG_CHN_SIM为简体中文(默认) 	DVTSTC_LANG_ENG为英文
*/
void DVTSTCSTB_ChangeLanguage(BYTE byLanguage);
#ifdef  __cplusplus
}
#endif
#endif  

