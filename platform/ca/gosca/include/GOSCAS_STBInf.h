#ifndef _GOSCAS_STBINF_H
#define _GOSCAS_STBINF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "GOSCAS_STBDataPublic.h"

//一下四个接口是为了维护老的集成建议不采用，采用新的接口extern HRESULT GOSCASTB_MasterSlave_PareProcess( Master_Pare_Slave process) ;
extern HRESULT GOSCASTB_GetCardMontherSonInfo(SGOSCAMontherSonInfo *MontherSonInfo);
extern HRESULT GOSCASTB_SetCardSonInfo(SGOSCAMontherSonInfo *MontherSonInfo);
extern HRESULT GOSCASTB_IsMotherCard( ) ;
extern HRESULT GOSCASTB_MotherSon_Pair( ) ;



/*-----------------------------------以下接口是CAS提供给STB调用----------------------------------*/
/*
备注，从2.02版本开始，部分接口函数的命名进行了修改，如果直接替换库编译有函数未定义错误，请查看下列函数更名情况：
GOSSYS_GetSerNo()						改 GOSCASTB_GetSerNo()
GOSSYS_CasSysTime_Get()					改 GOSCASTB_GetCasSysTime()
GOSCASTB_GetVer()						改 GOSCASTB_GetCASVer()
GOSCA_ISSystemID()						改 GOSCASTB_ISSystemID()
GOSSTBCA_SetForceOSDStatusEnd() 		改 GOSCASTB_SetForceOSDStatusEnd()
GOSSTBCA_GetSTB_BindSerID() 			改 GOSCASTB_GetSTB_BindSerID()

GOSSYS_Parent_PassWord_Get() 			改 GOSCASTB_Parent_PassWord_Get()
GOSSYS_Parent_PassWord_Check() 			改 GOSCASTB_Parent_PassWord_Check()
GOSSYS_Parent_PassWord_Set() 			改 GOSCASTB_Parent_PassWord_Set()
GOSSYS_Parent_PassWord_Reset() 			改 GOSCASTB_Parent_PassWord_Reset()
extern void GOSCASTB_PVR_Process(void) ;已经去掉；改在GOSCASTB_PVR_SetRunState（）中执行

*/
/*++

功能：
机顶盒调用该接口控制库信息的打印开个

参数：bDebugMsgSign
1：表示打开库的打印开个；0：关闭开关

返回值：
无
--*/
extern void GOSCASTB_AddDebugMsgSign(bool bDebugMsgSign) ;

/*++

功能：
主从卡配对接口函数（通常的字母卡配对接口函数）

参数：
无

返回值：
0 表示当前的处理流程OK!其它表示错误代码，详细操作请见附件实例举例：
--*/
extern HRESULT GOSCASTB_MasterSlave_PareProcess( Master_Pare_Slave process) ;

/*++

功能：
机顶盒启动的时候调用，对CAS模块初始化

参数：
byReaderNo：StreamGuard所属的智能卡读卡器号，一般设置0

返回值：
true     初始化成功
false    初始化失败
--*/
extern bool GOSCASTB_Init(unsigned char byReaderNo) ;

#if (defined(GOSCA_V208))
/*++

功能：
机顶盒从CAS库中获取配对机号

参数：
无

返回值：
四个字节的机号。如果返回0xFFFFFFFF，表示该机顶盒未进行初始化
--*/
extern unsigned long GOSCASTB_GetSerNo(void);
#elif (defined(GOSCA_V109))
/*++

功能：
机顶盒获取机卡配对后的机号

参数：
无

返回值：
四个字节的机号。如果没有进行过机卡配对。返回0xFFFFFFFF
--*/
extern unsigned long GOSSYS_GetSerNo(void);
#endif
/*++

功能：
机顶盒获取卡工作信息

参数：
*pCardWorkInfo:    获取结构体SCardWorkInfo信息

返回值： ==0 成功
!=0 失败
说明：
pCardWorkInfo->bCardPinStatus <= 1 PIN未锁定，>4PIN已锁定；
pCardWorkInfo->bWatchRating   实际的年龄显示需要加3
pCardWorkInfo->bMatureDays 到期提示天数的设置参数(1-18天）。
pCardWorkInfo->tStarttime
pCardWorkInfo->tEndtime
pCardWorkInfo->m_bIPPTWorkMode（0：永不使用；1：换台选择使用（该功能不用实现）2：提示使用；3：永远使用）
pCardWorkInfo->m_bReserved0
pCardWorkInfo->m_bReserved1
--*/
extern HRESULT GOSCASTB_GetCardWorkInfo(SCardWorkInfo* pCardWorkInfo);
/*++

功能：
机顶盒设置卡工作信息

参数：
*pCardWorkInfo:    设置结构体SCardWorkInfo信息，如果对某个结构体变量进行设置
需要先读出该结构体变量，再修改需要设置的结构体变量；

返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_SetCardWorkInfo(SCardWorkInfo* pCardWorkInfo);

/*++

功能：
OSD的滚动分两种。包括滚动

参数：
无

返回值：
--*/
extern void GOSCASTB_ShowOSDMsgOver(signed short wDuration);

/*++

功能：
指纹显示完后调用该接口；

参数：
无

返回值：
--*/
extern void GOSCASTB_ShowFingerOver(unsigned long version);

#if (defined(GOSCA_V208))
/*++

功能：
如果有字幕图片滚动广告，需要结束先前的CA强制OSD需要调用接口；

参数：
osd_Id：强制OSD的ID

返回值：
--*/
extern void GOSCASTB_SetForceOSDStatusEnd(unsigned long osd_Id);

/*++

功能：
机顶盒获取CAS库的版本号

参数：
pdwVer:    版本号字符串，后面带T的是测试版本
plen:		字符串缓冲区大小，通常是40B
返回值：
true	成功
false   失败
说明：
返回CA模块的版本号
例如:Goscas_Ver:2.08T1
--*/
extern bool GOSCASTB_GetCASVer(char *pdwVer, unsigned short *plen) ;
#elif (defined(GOSCA_V109))
/*++

功能：
机顶盒获取CAS库的版本号

参数：
pdwVer:    返回版本号

返回值：
true	成功
false   失败
说明：
返回CA模块的版本号
举例如果是0x00000104意思就是0.00.01.04
--*/
extern bool GOSCASTB_GetVer(long *pdwVer) ;
#endif
/*++

功能：
机顶盒获取CAS库的方案商ID和发布日期

参数：
pid:    方案ID
pTime	库发布日期
返回值：
true	成功
false   失败
说明：
返回CA库信息
pid = 0x00100 MSTAR
pTime = 0x20120514
--*/
extern bool GOSCASTB_GetCASLibInfo(unsigned long *pid, unsigned long *pTime) ;

/*++

功能：
调用CAS模块，获得智能卡内部ID。

参数：
*pID:    返回智能卡号。
*pSoftVer 返回卡的软件版本号
举例如果是0x32意思就是3.2

返回值：
true	成功
false   失败
说明：

--*/
extern bool GOSCASTB_GetCardInfo(unsigned long* pID, unsigned char* pSoftVer) ;

#if (defined(GOSCA_V208))
/*++
功能：
机顶盒获得CASID后调用该接口判断CASID是否有效，如果有效则返回true，否则返回false

参数：
wCaSystemID:		机顶盒分析SI/PSI信息获得的CASID

返回值：
true  (1)   CASID有效
false (0)   CASID无效
--*/
extern bool GOSCASTB_ISSystemID(const unsigned int wCaSystemID) ;

/*++
功能：
当用户插卡时机顶盒主程序调用，通知CAS模块

参数：
pAtr:		卡复位后返回的ATR数据
atr_size：	ATR数据的大小（通常是4B)

返回值：
如果某些方案不方便获取这两个参数，可以传入空指针，atr_size = 0
--*/
extern unsigned char GOSCASTB_SCInsert(unsigned char *pAtr, unsigned short atr_size);
#elif (defined(GOSCA_V109))
/*++
功能：
机顶盒获得CASID后调用该接口判断CASID是否有效，如果有效则返回true，否则返回false

参数：
wCaSystemID:		机顶盒分析SI/PSI信息获得的CASID

返回值：
true  (1)   CASID有效
false (0)   CASID无效
--*/
extern bool GOSCA_ISSystemID(const unsigned int wCaSystemID) ;

/*++
功能：
当用户插卡时机顶盒主程序调用，通知CAS模块

参数：
byReaderNo:		读卡器的编号

返回值：
--*/
extern unsigned char GOSCASTB_SCInsert(void);
#endif
/*++
功能：
获取CAS库模块里面卡的状态标识，如果插入了卡但状态
仍然是GOSCAS_SC_OUT，需要对卡复位从新执行一下插拔
卡动作。

参数：
*pState == GOSCAS_SC_OUT 库里面监控卡通信不可用。
*pState == GOSCAS_SC_IN  库里面监控卡通信正常。
*pState == GOSCAS_SC_IN_ERROR  库里面监控卡通信不正常。

返回值：
--*/
extern void GOSCASTB_SCGetState( unsigned char* pState );

/*++

功能：
当用户拔出智能卡时机顶盒主程序调用，通知CAS模块

参数：
返回值：
--*/
extern void GOSCASTB_SCRemove(void) ;

/*++
功能：
	用户转换频道的时候调用这个函数
	设置当前正在收看的节目的详细信息
参数：
pServiceInfos：	SGOSCAServiceInfo结构，描述节目的详细信息。
	byCount:		EcmPid的个数，目前只支持byCount=1
注意：该接口在每次换台前需调用一下，ECM PID = 0x1FFF;换台后分析PMT表信息，如果CASID合法，再调用一次
，ECM PID为实际的PID;

返回值
说明：
当用户换频道时，机顶盒需要调用CAS提供的此函数，将当前节目的原始信息及ECM PID传递给CAS模块，CAS模块会
根据当前频道的信息处理与当前频道相关的操作，如果当前频道为不加扰的频道，则需要将ECM的PID设为0。
--*/
extern void GOSCASTB_SetCurEcmInfos(unsigned char byCount,const SGOSCAServiceInfo* pServiceInfos) ;

/*++

功能：
设置EMMPID，CAS模块将根据设置的EMMPID信息进行EMM数据接收处理。
参数：
pwEmmPids:	CAT表中包含的descriptor中将有CA_system_ID及CA_PID，调用GOSCA_ISSystemID()校验有效的CA_PID即为EMM PID。
nEmmCount：	EmmPid的个数，目前只支持nEmmCount＝1
返回值：

说明:
当机顶盒收到CAT表后，机顶盒需要调用CA提供的此函数，将EMM PID传过来，这样CA程序就可以根据此PID收取
私有表，更新用户卡里的授权及为用户提供增值服务，当设置EMM的PID为0时，CA模块会停止收取EMM。
--*/
extern void GOSCASTB_SetEmmPids(long nEmmCount,const unsigned short* pwEmmPids) ;

/*++

功能：
机顶盒主程序在收到CAS私有数据或者Time_Out，调用这个接口将数据提供给CAS模块处理。
参数：
byReqID：			当前请求收取私有表的请求号，与GOSSTBCA_SetStreamGuardFilter里的byReqID对应
bSuccess：			收取数据有没有成功，成功为true，失败为false
wPID:				接收的数据的流的PID。
byszReceiveData：		收取的私有数据
wLen：				收取到的私有数据的长度
返回值：
true  (1)   有效
false (0)   无效
说明：
byReqID == GOSCA_STB_ECM_SLOT		供给CAS模块的数据类型是ECM
byReqID == GOSCA_STB_EMM_Private_SLOT	供给CAS模块的数据类型是EMM 私有	
byReqID == GOSCA_STB_EMM_Public_SLOT	供给CAS模块的数据类型是EMM 公有	
byReqID == GOSCA_STB_EMM_Serial_SLOT	供给CAS模块的机顶盒序列号EMM 私有	
byReqID == GOSCA_STB_EMM_SerialEx_SLOT	供给CAS模块的机顶盒序列号EMM 公有	

wLen = Section_lenth 		
--*/
extern bool GOSCASTB_StreamGuardDataGet(unsigned char byReqID, bool bSuccess, unsigned short wPID,unsigned short wLen,unsigned char* byszReceiveData) ;

/*++
功能：
判断智能卡的PIN码
参数：
sPin:				PIN码
返回值：
GOSSTB_OK          			成功
GOSCAERR_STB_DATA_LEN_ERROR		PIN码数据长度错误
GOSCAERR_STB_PIN_ERR			输入PIN码错误
GOSCAERR_STB_PIN_LOCKED			PIN被锁定
说明：
HRESULT Check_PinFunc(unsigned char* PINInput_Value){
SGOSPIN  verify_pin;
verify_pin.m_byLen = 3;
verify_pin.m_byszPin[0] = (PINInput_Value[0]<<4) | PINInput_Value[1];
verify_pin.m_byszPin[1] = (PINInput_Value[2]<<4) | PINInput_Value[3];
verify_pin.m_byszPin[2] = (PINInput_Value[4]<<4) | PINInput_Value[5];
if( GOSCASTB_VerifyPin(&verify_pin) != 0 )
{
return -1;
}
return 0;
}			
--*/
extern HRESULT GOSCASTB_VerifyPin(SGOSPIN *p_sPIN) ;

/*++
功能：
	判断卡是否被锁住。

参数：
	pbLocked:					- 输出时true表示锁住了，false，表示没有。
						
返回值：
	公共返回值1					- 详见注释

--*/
extern HRESULT GOSCASTB_IsPinLocked(bool * pbLocked) ;

/*++
功能：
修改智能卡的PIN码
参数：
sNewPin:			   新的PIN码

返回值：
GOSSTB_OK          				成功
GOSCAERR_STB_PIN_LOCKED			PIN被锁定
GOSCAERR_STB_DATA_LEN_ERROR		PIN码数据长度错误

说明:
调用该函数之前要求确保调用过GOSCASTB_VerifyPin()，并且是成功的。

--*/
extern HRESULT GOSCASTB_ModifyPin(SGOSPIN *p_sNewPin) ;

/*++
功能：
获得CAS运营商信息
参数：
pOperation   指向保存返回信息的数组地址
说明:
运营商执行了发卡信息通过EMM发送给卡。相应的信息会显示处理,里面的内容可用选择显示。
if(pOperation->m_dwMotherCardID == 0 )
{
该卡是一张母卡；
}
else
{
该卡是一张子卡，且母卡号是该号；
}

pOperation->m_bStandardFlag		子母卡配对失效判断标准
pOperation->m_dwDecryptCWTimes		解密CW 的次数
pOperation->m_dwIntervalTime/86400	间隔时间(天)
pOperation->m_wRunArea			用于区分运营的地方
pOperation->m_bUserVIPClass		用户等级
pOperation->m_dwUserArea		用于区分用户区域码
pOperation->m_bTVSName			运营商的名称
pOperation->m_bTVSOtherInfo		运营商的其他信息
--*/
extern HRESULT GOSCASTB_GetOperation(SOperatorInfo *pOperation) ;

/*++

功能：
获得普通授权节目购买的情况，用于在机顶盒界面上显示。

参数：
wTVSID:							- 运营商的内部编号,暂时未用到，不管。
pEntitleCount					- 输入时为数组的最大个数，输出时为实际获得的个数。
psEntitles:						- 返回的授权数组。

返回值： ==0 成功
!=0 失败
说明:
psEntitles->m_wProductID;				产品号
psEntitles->m_tStartTime;				开始时间
psEntitles->m_tEndTime;					结束时间

--*/
extern HRESULT GOSCASTB_GetServiceEntitles(unsigned char *pEntitleCount, SGOSCAServiceEntitle_Ex* psEntitles) ;

#if (defined(GOSCA_V208))
/*++

功能：
获得普通授权节目总数，需要在CA2.04以上版本调用该接口。

参数：
pEntitleCount					输出时为实际获得的个数。

返回值： ==0 成功
!=0 失败
说明:
--*/
extern HRESULT GOSCASTB_GetEntitlesSumEx(unsigned int *pEntitleCount) ;

/*++

功能：
获得普通授权详细信息，需要在CA2.04以上版本调用该接口。

参数：
m_StartIndex					授权信息读取开始索引号,以0为开始索引。
m_Readcount						计划读取个数。
*pReadedSCount					实际读取个数的返回值。
*psEntitles						实际读取授权信息打印返回。

返回值： ==0 成功
!=0 失败
说明:
--*/
extern HRESULT GOSCASTB_GetEntitlesTotalEx(unsigned int m_StartIndex, unsigned int m_Readcount, unsigned int *pReadedSCount, SGOSCAServiceEntitle_Ex_Print* psEntitles) ;
#endif
/*++

功能：
锁定中心频点，将中心频点NIT的网络ID送给卡接口，某些客户的分区控制会使用以上功能

参数：
NetID:							- 中心频点NIT网络ID。
注意：该动作需要在开机时只做一次；

返回值： ==0 成功
!=0 失败

--*/
extern HRESULT GOSCASTB_SetNetWorkID(unsigned short  NetID);

#if (defined(GOSCA_V208))
/*++
功能：
	获取所插入卡收到的绑定机号ID信息。
参数：
*ptrID：ID数组，自己以4个字节凑成整数，如果是0xFFFFFFFF表示空的没有被绑定。	
*prtLen = 4的整数倍个数，暂时支持3组号绑定。
返回值：
	无。
--*/
extern HRESULT GOSCASTB_GetSmart_BindSerID(unsigned char*  ptrID, unsigned int *ptrLen );

/*++
功能：
	获取本机顶盒收到的绑定卡号ID信息。
参数：
*ptrID：ID数组，自己以4个字节凑成整数，如果是0xFFFFFFFF表示空的没有被绑定。	
*prtLen = 4的整数倍个数，暂时支持3组号绑定。
返回值：
	无。
--*/
extern HRESULT GOSCASTB_GetSTB_BindSerID( unsigned char *ptrID, unsigned int *prtLen ) ;
#endif
/*++
功能:
机顶盒获取E-mail总信息接口。
参数:
*pEmail_Total:		输入时为数组总个数，输出时为机顶盒中E-mail总个数。
返回值： ==0 成功
!=0 失败
说明:

pEmail_Total->m_Email_All;
pEmail_Total->m_Email_New;
pEmail_Total->m_Email_versions[GOSCA_MAX_EMAIL_ID_COUNT].m_state == FREE; NEW ;OLD表示无效索引；新邮件；已读邮件
pEmail_Total->m_Email_versions[GOSCA_MAX_EMAIL_ID_COUNT].m_version 邮件的版本
--*/
extern HRESULT GOSCASTB_GetEmailTotal(GOSCAEmailTotal *pEmail_Total);

/*++
功能:
机顶盒通过邮件的版本获取单个E-mail的标题内容。
参数:
tVersion:			E-mail版本。
*pEmail:			获取的E-mail结构。
返回值： ==0 成功
!=0 失败
--*/
extern HRESULT GOSCASTB_GetEmailTitle(unsigned long tVersion, GOSCAEmailHead *pEmail) ;


/*++
功能:
机顶盒通过邮件的版本获取单个E-mail的内容。
参数:
tVersion:			E-mail版本。
*pEmail:			获取的E-mail结构。
返回值： ==0 成功
!=0 失败
--*/
extern HRESULT GOSCASTB_GetEmailContent(unsigned long tVersion, GOSCAEmailContent *pEmail) ;

/*++
功能:
机顶盒看完E-mail后，通过邮件的版本通知CAS的接口该邮件设置为已读状态。
参数:
tVersion:			E-mail版本。
返回值:
GOSCA_OK:						获取E-mail成功。
--*/
extern HRESULT GOSCASTB_EmailRead(unsigned long tVersion) ;

/*++
功能:
机顶盒通过邮件的版本删除单个E-mail接口。
参数:
tVersion:			E-mail版本。如果为-1，表示删除邮箱中所有email，否则，为具体的id。
返回值:
GOSCA_OK:						删除E-mail成功。
GOSCAERR_STB_NO_EMAIL:			要删除的E-mail不存在。
--*/
extern HRESULT GOSCASTB_DelEmail(unsigned long tVersion) ;

/*++
功能:
机顶盒删除所有E-mail接口。
参数:

返回值： ==0 成功
!=0 失败
--*/
extern HRESULT GOSCASTB_DelAllEmail( void );

/*++
功能:
机顶盒换台时调用该接口。
参数:

返回值： 无
--*/
extern void GOSCASTB_SetCurIPPT(unsigned int nServerID) ;

/*++
功能：
	进入播放PVR(带EMM数据)前和退出后各调用一次该接口，以便CA库能正常识别工作。
参数：
	
返回值：
	无。
--*/
/*-----------------------------------以下接口是PVR授权调用接口----------------------------------*/

/*++
功能：
	录制PVR节目前，获取PVR文件名称，以便以后通过上报PVR文件名进行授权。
参数：
	pFileID：创建的属性文件的文件ID（以后的操作需要通过该文件ID进行相应的操作）
	pName：名称的字符串，带结束符号
	pNamelen：名称的字符串长度；
返回值： ==0 成功
-1：获取当前系统时间失败，可能是调用接口GOSSTBCA_GetSTB_CurrentTime（）返回失败；
-2：产品PVR文件名字符串时出错；
-3：创建属性文件系统出错；
--*/
extern HRESULT GOSCASTB_PVR_GetFileName(GOSCAPVR_File_ID* pFileID, unsigned char* pName, int* pNamelen) ;

/*++
功能：
	更新PVR属性文件备注，通常是在录制PVR节目时获取EPG等相关信息备份到属性文件中，一般采用“节目名+当前EPG信息”。
参数：
	pComments：节目名+EPG信息,长度不超过40个字符（带结束符）；
	pCommentslen：字符串长度；
返回值： ==0 成功
!=0 失败
--*/
extern HRESULT GOSCASTB_PVR_SetFileComments(GOSCAPVR_File_ID* pFileID, unsigned char* pComments, int* pCommentslen) ;

/*++
功能：
	录制PVR节目过程状态设置，通常分为录制开始，录制结束，播放开始，播放结束等流程；
参数：
nState:PVR_RECORD_START,PVR_RECORD_STOP,PVR_PLAY_START,PVR_PLAY_STOP
返回值： ==0 成功
!=0 失败
--*/
extern HRESULT GOSCASTB_PVR_SetRunState(GOSCAPVR_File_ID* pFileID, Pvr_Run_State nState ) ;

/*++
功能：
	播放PVR文件前，将PVR的文件名传给库校验是否合法，合法直接进入PVR的播放流程。。
参数：
	pName：输入名称的字符串，带结束符号
	pNamelen：名称的字符串长度；
	pComment：输出提示信息的字符串，带结束符号
	pCommentlen：提示信息的字符串长度；
	pFileID：输出文件的ID；
	pOverDueTime：PVR授权过期时间字符串，如2012-12-1；
	pSysCurTime：系统当前时间，如2012-12-1 19:24:12；
返回值： ==0 成功合法
!=0 失败
--*/
extern HRESULT GOSCASTB_PVR_CheckFileName(unsigned char* pName, int* pNamelen, unsigned char* pComment, int* pCommentlen, GOSCAPVR_File_ID* pFileID, unsigned char* pOverDueTime, unsigned char* pSysCurTime) ;

/*++
功能：
	查询是否允许PVR录制接口,该功能由前端系统命令发出，默认情况下不允许录制
参数：
	pState：0：禁止录制，1：允许录制
返回值： ==0 成功合法
!=0 失败
--*/
extern HRESULT GOSCASTB_PVR_RecordOk(unsigned char* pState) ;

/*++
功能：
	PVR集成的测试打印，打印关键数据便于查找问题，通常正式版本不提供该接口；
参数：无

返回值： ==0 成功合法
!=0 失败
--*/
extern HRESULT GOSCAS_PVR_TestPrint(void) ;


/*-----------------------------------以下接口是某些特殊需求定义接口----------------------------------*/

/*++
功能：
	设置机顶盒定义到期提示的最后剩余多少小时,该接口调用需要重新编译库定义才有效。
参数：
	
返回值：
	无。
--*/
extern void GOSCASTB_SetLastDay_PromtHours( unsigned int nHours ) ;

/*++

功能：
机顶盒通过CAS获取当前系统时间，该接口通常在某些没有TDT表系统中使用；

参数：
*year:    	xxxx年
*month		x月
*day		xx日
*week		星期x
*hour		xx时
*min		xx分

返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_GetCasSysTime( unsigned int*  year, unsigned char*month, unsigned char*day, unsigned char* week, unsigned char* hour, unsigned char* min, unsigned char* sec);

/*-----------------------------------以下接口是CA库提供一个密码接口供某些特殊需求----------------------------------*/

/*++

功能：
获取一个六位的密码，超级密码281201

参数：
*pOut 密码ASC字符串

返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Get( unsigned char* pOut );

/*++

功能：
校验一个六位的密码，校验出错，错误计数器自动加1，大于3次锁定

参数：
*pIn 密码ASC字符串

返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Check( unsigned char* pIn );

/*++

功能：
设置一个六位的密码，超级密码281201，
使用超级密码可以清空密码，该功能是某些客户要求对父母锁远程操作下使用，
及可以归SMS管理；

参数：
*pIn 密码ASC字符串

返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Set( unsigned char* pIn );

/*++

功能：
复位清空一个六位的密码，超级密码281201，
使用超级密码可以清空密码，该功能是某些客户要求对父母锁远程操作下使用，
及可以归SMS管理；

参数：
date_time 时间戳
version 版本号
返回值： ==0 成功
!=0 失败
说明：
同上
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Reset( unsigned long date_time, unsigned char version );

#ifdef __cplusplus
}
#endif

#endif
