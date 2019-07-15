/*****************************************************************************
File name     	: abv_ca_interface.h

Description   	: 定义出CA 提供给机顶盒的函数接口

Copyright (C) 	: ABV 2006

R&D Group	: ABV_CA

Author(s)	    	:  zhangxl    

Notes          	: 

History	    	: 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created 


remark:First byte of the text is lauguage code

*****************************************************************************/
#ifndef __ABV_CA_INTERFACE_H__
#define __ABV_CA_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"
#include  "sc_api.h"
#include "os_api.h"

#define 	MAX_ATTRIBUTE_BYTES   		20
#define 	MAX_VALUE_BYTES	       			40
#define 	SEG_MAX_NUM					5					//never changed


typedef enum
{
	ABV_Success, //success
	ABV_Failed, //failed 
	ABV_TimeOut //timeout
}ABV_MSG_Return_State_e;

typedef struct _ABV_TCPIP_
{
	ABV_UInt8 IP_Addr [4];
	ABV_UInt8 Mac_Addr[6];
	ABV_UInt16 Prot;
}ABV_TCPIP_Connect_s;

typedef enum
{
	PPID_FREE_ENTITLE,/*free entitlement*//*显示时只显示lable 和开始结束时间即可，并且时间不需要显示小时和分钟*/
	PPID_PPC_ENTITLE,/*PPC entitlement*//*结构中的信息均需要显示*/
	PPID_PPV_ENTITLE/*PPV entitlement*//*结构中的信息均需要显示*/
} ABV_PPID_Entitle_Type;

typedef enum
{
	CARD_OK,
	CARD_PIN_ERROR,
	CARD_PIN_LOCK,
	CARD_PIN_NO_MATCH,
	CARD_MR_ERROR,
	CARD_WT_ERROR,
	CARD_IPPV_ERROR,
	CARD_NO_ENOUGH_TOKENS,
	CARD_OUT_ERROR,
	CARD_TYPE_ERROR,
	CARD_OTHER_ERROR
}SC_MODIFY_TYPE;

typedef struct 
{
	ABV_UInt8 Provider_PPID[3];
	ABV_UInt8 Provider_Label[8];
	ABV_Int32 balance;
}Provider_Info_t;

typedef struct 
{                     
	ABV_UInt8 year[2];/*"%d"*/
	ABV_UInt8 month;/*"%d"*/
	ABV_UInt8 date;/*"%d"*/
	ABV_UInt8 hour;/*"%02x"*/
	ABV_UInt8 minute;/*"%02x"*/
}Entitle_time_t;

typedef struct 
{
	ABV_UInt16 LinkID;/*Packet ID*/
	ABV_UInt8 Label[8];/*Packet name*/
	ABV_UInt8 PayState;/*0	Already paid	1,2 Paid by time  3  Paid by prog  4 Have not paid */
	Entitle_time_t NDate;/*Send time*/
	Entitle_time_t SDate;/*Start time*/
	Entitle_time_t EDate;/*End time*/
}Entitlement_Info_t;

typedef struct  _fp_info_
{
	ABV_UInt16 data_len;/*no use*/
	ABV_UInt8 fp_type; /*1: common emm fp.  2: channel emm fp should be cleard when switch channel*/
	ABV_UInt16 X_Axis;/*X-coordinate*/
	ABV_UInt16 Y_Axis;/*Y-coordinate*/
	ABV_UInt16 duration;/*display duration*/
	ABV_UInt16 repetition;/*display times*/
	ABV_UInt16 interval	;/*time interval*/
	ABV_UInt8 font_color_id;/*font color index in color table*/
	ABV_UInt8 back_color_id;/*back ground color index in color table*/
	ABV_UInt8 font_colour[3];/*font colour*/
	ABV_UInt8 back_colour[3];/*Back colour*/
	ABV_UInt8 font_sparkling;/*Sparking*/
	ABV_UInt32 msg_id;/*emm msg_id*/
	ABV_UInt8 current_time[5];/*emm send date*/
	ABV_UInt8 start_time[5]; /*fp start date and time*/
	ABV_UInt8 width;/* %   ex: 80(80%), 64(64%), 0x64(100%)*/
	ABV_UInt8 height;/*%*/
	ABV_UInt8 location;/*(bit7)screen, (6bit)PIP, (bit5)EPG,(bit4) recorder, (bit3)other,(bit2) reserved, (bit1) reserved, (bit0) reserved.   bit value:  1 display , 0 not display*/
	ABV_UInt8 disp_bg;/* true :display backgroud . false: not display background*/
	ABV_UInt8 disp_ua; /*true:display UA, false:not display UA*/
	ABV_UInt8 disp_stbnum;/*true display stb number.  false: not display stb number*/
	ABV_UInt8 disp_msg;/*true: force fingerprint . false: common fingerprint*/
	ABV_UInt8  transparency;/* transparency of OSD layer */
	ABV_UInt8  font_size;/*font size :16 18 20 24 26 and so on*/
	ABV_UInt16 content_len;/*content length*/
}ABV_Fingerprint_t;

typedef struct 
{
    ABV_UInt16 	 ts_emm_pid; 		 /*EMM PID*/
    ABV_UInt16        audio_ecm_pid;      /*audio ECM PID*/
    ABV_UInt16        video_ecm_pid; 		/*video ECM PID*/
} ABV_Service_info_t;


typedef struct _Entitlement_Item
{
	Entitlement_Info_t EntitleData;	/*Entitlement information*/
	struct _Entitlement_Item *NextEntitle;/*Next entitlement*/
}Entitlement_Item_t;

typedef struct 
{
	ABV_UInt8 PPID_NO;/*PPID numbers*/
	ABV_UInt16 EntitleCount;/*PPID entitle totals*/
	struct _Entitlement_Item *ItemHead;
}Entitlement_List_t;

typedef struct 
{
	ABV_UInt16 HistoryCount;/*consume history total*/
	struct _IPPV_History_Item *ItemHead;
}IPPV_History_List_t;


typedef struct _IPPV_History_Item
{
	Entitle_time_t IPPV_Entitle_time;/*consume times*/
	ABV_Int32	IPPV_Entitle_tokens;/*consume tokens*/
	struct _IPPV_History_Item  *NextIPPV;
}IPPV_History_Item_t;

typedef struct  _ABV_IPPV_Pro_Info
{
	ABV_UInt8	IPPV_Type;/* 1 Pay per minute  2 Pay per View  0 Both types can be chosen by users*/
	ABV_UInt8	IPPV_Time_Price[3];/*price of pay per minute --long int---*/
	ABV_UInt8	IPPV_View_Price[3];/*price of pay per view ---long int---*/
	ABV_UInt8	IPPV_Name[24];/*Program instrction*/
	Entitle_time_t  Pro_Start_Time;/*Start time*/
	Entitle_time_t  Pro_End_Time;/*Finish time*/
	ABV_UInt16    IPPV_ID;
}ABV_IPPV_Pro_Info_t;
typedef struct _ABV_Mail_Head_info 
{
	ABV_Boolean	mail_status;/*0 unread；1 read*/
	ABV_UInt16 	mail_len;
	ABV_UInt32 	mail_Mesg_id;
	Entitle_time_t	mail_date;
	ABV_UInt8	mail_sender_len;
	ABV_UInt8	mail_sender_name[20];/*Send name*/
	ABV_UInt8	mail_title_len;
	ABV_UInt8	mail_tilte[50];/*Mail title*/
}ABV_Mail_Head_info_t;


typedef struct   _new_osd_s_
{
	ABV_UInt32 	sub_Mesg_id;/*Flag*/
	ABV_UInt8	start_time[5];/*start time*/
	ABV_UInt16	duration;/*Duration*/
	ABV_UInt16	repetition;/*times*/
	ABV_UInt16	interval;/*interval*/
	ABV_UInt16	FlashLen;/*data length*/
	ABV_UInt8	font_color_id;/*color index in color table*/
	ABV_UInt8	bg_color_id;/*back groud color index in color table*/
	ABV_UInt8 	font_color[3];/*font color RGB*/
	ABV_UInt8	bg_color[3];/*back ground color RGB*/
	ABV_UInt8	disp_bg;/*0: not display back ground . 1: display back ground*/
	ABV_UInt8	location;/*000: full screen 001: scroll from left to right in Top; 010 scroll from right to left in Top;011: scroll from left to right in Bottom; 100 scroll from right to left in Bottom;*/
	ABV_UInt8	transparency;/*Transparency of osd layer*/
	ABV_UInt8  	font_size;/*font size :16 18 20 24 26 and so on*/
	ABV_UInt8	msg_type;/*0x01 :old osd. 0x06: new osd. not used current*/
	
}ABV_Sub_info_t;

typedef struct 
{
	ABV_UInt16 		ota_len;/*OTA数据的总长度*/
	ABV_UInt32 		ota_Mesg_id;/*OTA消息的MessageID*/
	ABV_UInt8		ota_date[5];/*OTA数据的发送时间*/
	ABV_UInt16		ota_pid;/*OTA数据的PID*/
	ABV_UInt8		dvb_recieve_type;/*接收机的类型IRD Type :DVB-C   DVB-S DVB-T*/
	ABV_UInt8		dvb_manufactor;/*厂商代码*/
	ABV_UInt32		dvb_hardvesion;/*硬件版本号*/
	ABV_UInt32		dvb_softversion;/*软件版本号*/
	ABV_UInt8		dvb_Modulation;/*调制方式*/
	ABV_UInt32		dvb_freq;/*frequencyOTA数据所在的发送频点的频率*/
	ABV_UInt32		dvb_symb;/*symbolrateOTA数据所在的发送频点的符号率*/
	ABV_UInt8		dvb_polarization;/*极化方式*/
	ABV_UInt8		dvb_FEC;/*DVB-C和DVB-S中使用的前向纠错编码*/
	ABV_UInt8		dvb_Guard_interval;/*保护间隔*/
	ABV_UInt8		dvb_Transmission_mode;/*传输模式*/
	ABV_UInt8		dvb_code_rate;/*优先级码率*/
	ABV_UInt8		dvb_BandWidth;/*带宽*/
	ABV_UInt8		dvb_Constellation;/*卫星所在的经度*/
}ABV_Ota_info_t;

typedef struct
{
	ABV_UInt8 Label[8];/*Provider's name*/
	ABV_UInt8 Num[8];/*Card Number*/
	ABV_UInt8 Name[5];/*Smart card Name*/
	ABV_UInt8 Version;/*Smart card version*/
	ABV_UInt8 Matl;/*Adult level*/
	ABV_UInt8 Area[4];/*Aire*/
	ABV_UInt8 paired;/*%d display*/
	ABV_UInt8 start_time[2];/*BCD Code 4bit 2进制数表示一个10进制数*/
	ABV_UInt8 end_time[2];/*BCD code*/
	ABV_Boolean IsChildSC;/*ABV_TRUE : is child card  ABV_FALSE : is mother card*/
	ABV_UInt8 MasterNum[8];/*Master card number*/
}ABV_SC_Info_t;

typedef struct 
{
	ABV_UInt16 ECM_X_Axis;/*Ecm FingerPrint X-coordinate*/
	ABV_UInt16 ECM_Y_Axis;/*Ecm FingerPrint Y-coordinate*/
}ABV_ECM_Position_t;

typedef  struct  _Buy_IPPV_ABV_EPG
{
		ABV_UInt16 Orignal_Network_ID;//网络ID
		ABV_UInt16 TS_ID;//TS_ID
		ABV_UInt16 Service_ID;//ServiceID
		ABV_UInt16 Event_ID;//EPG中获得的节目的Event ID
		ABV_UInt8 Pay_Type;//购买类型：前端或者终端付费

} ABV_Buy_IPPV_EPG_s;


/*********************************************************************/
/* IRD should transfer following functions those were provided by CA core*/

/****************************************************************************
name          	: 	ABV_CASTB_Sys_Init
Description  	:	CA module system initialization(  CA 模块初始化)
Parameters    : 	NONE
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			: call this function when stb boot and initial 
****************************************************************************/
ABV_Boolean ABV_CASTB_Sys_Init(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_NotifySwitchChannel
Description  	:	call this function when switch channels or Card status change to card in( 切换频道通知)
Parameters    : 	pmtpid
				service_id
				audio_pid
				video_pid
Return Value  : 	success: ABV_FALSE  failed: ABV_TRUE
NOTES	       :      when user switch channels, this function must be called  
****************************************************************************/
ABV_Boolean ABV_CASTB_NotifySwitchChannel(ABV_UInt16 pmtpid,ABV_UInt16 service_id,ABV_UInt16 audio_pid,ABV_UInt16 video_pid)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_NotifySwitchFreq
Description  	:	call this function when switching frequency or Card status change to card in 
Parameters    : 	NONE
Return Value  : 	success: ABV_FALSE  failed: ABV_TRUE
NOTES	       :      when user switch frequency, this function must be called  
****************************************************************************/
ABV_Boolean ABV_CASTB_NotifySwitchFreq(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Smart_Report
Description     :   Send card status to CA core   
Parameters    : 	status:smart card status
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Smart_Report(SC_STATUS  status)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Table_Data
Description     :   CA core get useful data from IRD
Parameters    : 	cslot:channel ID
					PidFlag:Data PID
					Service_id:Program Service ID
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Table_Data(ABV_UInt8 cslot, ABV_UInt16 PidFlag,ABV_UInt16 Service_id)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Synchronize_System_Time()
Description     :   synchronize system time.
Parameters    : 	Timer
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_CASTB_Synchronize_System_Time(Entitle_time_t *Timer)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Stop_CA()
Description     :   Stop Ca,but don't free using channel and filter.
Parameters    : 	NONE
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_CASTB_Stop_CA(void)FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_CASTB_Get_CALIB_Version
Function		:Get CALIB version and time
Parameters	:version(IN_OUT) version of current CALIB,display as "%04x".
			 date:the date of this version. display as "%s".
			 time:the time of this version. display as "%s".
return 		:NONE
NOTES: if CAlIB version is 3.6 the version=0x0360,if CALIB version is 10.09 version = 0x1009
*******************************************************************************************************/
void ABV_CASTB_Get_CALIB_Version(ABV_UInt16* version,ABV_UInt8 *date,ABV_UInt8 *time)FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_Get_STBextention_Info
Function		:get stb extended infomation receive from CASserver
Parameters	:
info:buffer which will contain the info
info_len:the len of extend infomation
return 		:NONE
NOTES:
*******************************************************************************************************/
ABV_Boolean ABV_Get_STBextention_Info(ABV_UInt8 *info, ABV_UInt16* info_len)FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_AS_GetSTBID
Function		:  advance secrity get stbid
Parameters	:stbid  pointer to buffer that store the stbid. buffer max length is 14
return 		:NONE
NOTES:
*******************************************************************************************************/
ABV_Boolean ABV_AS_GetSTBID(ABV_UInt8* stbid)FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_Get_Emm_PID
Function		:Get current EMM PID
Parameters	:
return 		:NONE
NOTES:
*******************************************************************************************************/
ABV_Boolean ABV_Get_Emm_PID (ABV_UInt16*  EmmPID )FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_Get_UA
Function		: Get current UA, used for PVR.
Parameters	:
return 		:NONE
NOTES:
*******************************************************************************************************/
ABV_Boolean ABV_Get_UA (ABV_UInt8 UA[5] )FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_ChangePIN
Description     :      change  smart card pin code
Parameters    : 	old_pin : user input old smart card pin  
				old_pin_length : old pin length
				new_pin : user input smart card pin
				new_pin_length : new pin length 
				match_pin :  user input  new smart card match pin 
				match_pin_length :  new match pin length 
				reset_num:retry times
Return Value  : SC_MODIFY_TYPE
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_ChangePIN(ABV_UInt8* old_pin, ABV_UInt8 old_pin_length, ABV_UInt8* new_pin, ABV_UInt8 new_pin_length, ABV_UInt8* match_pin, ABV_UInt8 match_pin_length,ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_ModifyMR
Description     :      modify smart card  maturity level (  修改成人级别)
Parameters    : 	old_pin : user input smart card old pin  
				old_pin_length : old pin length
				new_level : new maturity level
				reset_num
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_ModifyMR(ABV_UInt8* old_pin, ABV_UInt8 old_pin_length, ABV_UInt8 new_level,ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Modify_Watch_Time
Description     :      watch maturity level program
Parameters    : 	pin:user pin 
				pin_length:pin length
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_Modify_Watch_Time(ABV_UInt8 *pin,  ABV_UInt8  pin_length,ABV_UInt8 start_h, ABV_UInt8 start_m,ABV_UInt8 End_h,ABV_UInt8 End_m,ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_PPID_Total
Description     :      get the total number of provider
Parameters    : 	none
Return Value  :      return the total number of provider	
NOTES	      : 
****************************************************************************/
ABV_UInt8 ABV_CASTB_Get_PPID_Total(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Provider_Info
Description     :      get one provider infomation by provider ppid
Parameters    : 	PPID_NO:provider ppid
				tProviderInfo:provider infomation data
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Provider_Info(ABV_UInt8 PPID_NO,Provider_Info_t *tProviderInfo)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Entitle_Total
Description     :      get Entitlement total
Parameters    : 	PPID_NO:provider ppid number
				Entitle_type:entitle type
Return Value  :     entitlement total or 0	
NOTES	      : 
****************************************************************************/
ABV_UInt16 ABV_CASTB_Get_Entitle_Total(ABV_UInt8  PPID_NO, ABV_PPID_Entitle_Type Entitle_type)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_One_Entitle_Info
Description     :      get one Entitlement infomation about the PPID_NO
Parameters    : 	PPID_NO:provider ppid number
					Entitle_No:entitle number: count from 0 to entitle total
					tEntitleInfo:entitlement infomation 
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_One_Entitle_Info(ABV_UInt8  PPID_NO, ABV_UInt16  Entitle_No,ABV_PPID_Entitle_Type Entitle_type, Entitlement_Item_t  *tEntitleInfo)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Smartcard_Info
Description     :      get smartcard info
Parameters    : 	SC_INFO : smartcard info
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Smartcard_Info(ABV_SC_Info_t *SC_INFO)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Hist_Record_Total
Description     :      get History record total
Parameters    : 	PPID_NO:provider ppid number
Return Value  :     entitlement total or 0	
NOTES	      : 
****************************************************************************/
ABV_UInt16 ABV_CASTB_Get_Hist_Record_Total(ABV_UInt8  PPID_NO)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_One_Hist_Record_Info
Description     :      get one Record infomation about the PPID_NO
Parameters    : 	PPID_NO:provider ppid number
					Record_No:Record number: count from 0 to record total
					pHistRecord:record infomation 
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_One_Hist_Record_Info(ABV_UInt8  PPID_NO, ABV_UInt16  Record_No, IPPV_History_Item_t  *pHistRecord)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Fingerprint_Info
Description     :      get fingering info
Parameters    : 	tfingerprintdisp:fingering info
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Fingerprint_Info(ABV_Fingerprint_t *fp_info,ABV_UInt8 *Content)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_IPPV_Info
Description     :      get ippv program info
Parameters    : 	IPPV_info : iPPV program info 需要提供两个数组空间
				Msg_ServiceID:
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_IPPV_Info(ABV_IPPV_Pro_Info_t tIPPV_info[2],ABV_UInt16 Msg_ServiceID)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Buy_IPPV
Description     :      buy ippv program
Parameters    : 	pin:user pin 
				length:pin length
				Pay_type:1:pay by time  2 Pay by product 0:both
				serial_number: 0:buy current product  1:buy next product
				reset_num:
Return Value  :      SC_MODIFY_TYPE	
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_Buy_IPPV(ABV_UInt8*pin , ABV_UInt8 length,ABV_UInt8 Pay_type,ABV_Boolean serial_number,OUT ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Watch_mr_program
Description     :      watch mature level program(收看智能卡节目,当用户输入密码后调用)
Parameters    : 	pin:user pin 
				pin_length:pin length
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_Watch_Mr_Program(ABV_UInt8* pin, ABV_UInt8 pin_length,ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_No_Watch_Program
Description     :      don't observe the program不收看此节目或者密码输入出错
Parameters    : 	type : ABV_TRUE 用户要求不观看 ABV_FALSE 机顶盒菜单下不能弹出某些菜单时调用
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_No_Watch_Program(ABV_Boolean type)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Current_program_Info
Description     :   	Disp current program info
Parameters    : 	Current_Program_Info 
Return Value  :     success: ABV_FALSE  failed: ABV_TRUE 	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Current_program_Info(ABV_Service_info_t* Current_Program_Info)FUNC_TYPE;

/****************************************************************************
name            : 	ABV_CASTB_Get_ECM_FingerPrint_Paraments()
Description    :   	Get ECM FingerPrint Parament,Call this function when STB recieved STB_ECM_FINGERPRINT message.
Parameters    : 	FingerPrintPara:Need STB offer space 
                            Type:Are users get the ECM FingerPrint Paramaters from CA Lib.
                         ABV_True:need get the Paramaters from CA Lib.
                         ABV_FALSE:needn't get the Paramaters from CA Lib,Users can define a fixed coordinate.
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_ECM_FingerPrint_Paraments(ABV_ECM_Position_t *FingerPrintPara,ABV_Boolean *Type)FUNC_TYPE;

/*******************************************************************************************************
name             :ABV_CASTB_Recieve_MSG_From_OtherSTB
Function		:Receive Message From other STB
Parameters	:pBuffer:data received from other STB.when the STB Get Message from Physical channel
return 		：ABV_Success：recieve message success.
		  ABV_Failed：receive message failed.
		  ABV_TimeOut：receive message timeout.
*******************************************************************************************************/
ABV_MSG_Return_State_e ABV_CASTB_Recieve_MSG_From_OtherSTB(ABV_UInt8 *pBuffer,ABV_UInt16 Length)FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_CASTB_Recieve_MSG_From_OtherSTB_TimeOut
Function		:Receive Message From other STB Timeout
Parameters	:NONE
return 		:NONE
*******************************************************************************************************/
void ABV_CASTB_Recieve_MSG_From_OtherSTB_TimeOut(void)FUNC_TYPE;

/****************************************************************************
name          : 	ABV_CASTB_Buy_IPPV_From_EPG()
Description   :   	Get Program infomation from EPG and buy the current EventID Program entitlement
Parameters    : 	IPPV_INFO:Program Infomation ,Get it from EPG
Return Value  :      	success: CARD_OK  failed: Other return
NOTES	      : 
****************************************************************************/
SC_MODIFY_TYPE ABV_CASTB_Buy_IPPV_From_EPG(ABV_Buy_IPPV_EPG_s  IPPV_INFO,ABV_UInt8 *pin,  ABV_UInt8  pin_length,ABV_UInt8 *reset_num)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Mail_Total
Description     :   get  mail total
Parameters    : 	NONE
Return Value  :     mail total	
NOTES	      : 
****************************************************************************/
ABV_UInt8 ABV_CASTB_Get_Mail_Total(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Mail_MaxNum
Description     :   get  max mail number of the lib to support
Parameters    : 	NONE
Return Value  :     mail max number	
NOTES	      : 
****************************************************************************/
ABV_UInt8 ABV_CASTB_Get_Mail_MaxNum(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Check_New_Mail
Description     :   Check Unread mail
Parameters    : 	NONE
Return Value  :     ABV_FALSE:no unread mail
					ABV_TRUE:exist unread mail
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Check_New_Mail(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Mail
Description     :   get text mail info,call it when STB recieved new Mail info
Parameters    : 	Message_id:Message_id of current mail
					mail_content:text mail data content,out parameters
					data_length:mail data length
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Mail(ABV_UInt32 MessageID,OUT ABV_UInt8* mail_content,OUT ABV_UInt16*data_length)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Mail_Head
Description     :   get text mail Head info,call it when STB disp mail head info
Parameters    : 	num:get num-th mail head
					mail:OUT parameter,all mail head info STB want to obtain
					mail_num:mail count that has been gotten
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Mail_Head(ABV_UInt8 num,OUT ABV_Mail_Head_info_t*mail)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Del_One_Mail
Description     :   Delete a mail
Parameters    : 	Message_id:Message_id of current mail
Return Value  :     mail total	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Del_One_Mail(ABV_UInt32 MessageID)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Clear_Mail_Addr
Description     :     clear all mail ,for receive the same mail 
Parameters    : 	void
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Clear_Mail_Addr(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_Subtitle
Description     :   get subtitle data,call it when STB recieved subtitle info 
Parameters    : 	subtitle:subtitle info ,out parameters 
			content: text content of subtitle  . 1024  bytes as max.
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_Subtitle(OUT ABV_Sub_info_t*subtitle , OUT ABV_UInt8* content)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_OTA
Description     :   get OTA data,call it when STB recieved OTA info 
Parameters    : 	OTA_Content:OTA data content ,out parameters
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_OTA(OUT ABV_Ota_info_t*OTA_Content)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Get_IPPV_History_Info
Description     :   	get  buy IPPV history info
Parameters    : 	IPPV_List: PPV history info 
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_CASTB_Get_IPPV_History_Info(ABV_UInt8 ppid_no,IPPV_History_List_t *IPPV_List)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_CAM_Req_ECM
Description     :   req ECM.This function was called when User used a CAM porting ABV CA.
Parameters    : 	AudioECMPid:Audio ECM PID
                    VideoECMPid:Video ECM PID
                    ca_sysID:The CA system ID under the AudioECMPid and VideoECMPid.
                    service_ID:Program Number of current Prog
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_CASTB_CAM_Req_ECM(ABV_UInt16 AudioECMPid,ABV_UInt16 VideoECMPid,ABV_UInt16 ca_sysID,ABV_UInt16 service_ID)FUNC_TYPE;

/****************************************************************************
name            :   ABV_CASTB_Get_Current_SysID(void)
Description     :   User can get current CA Systerm ID 
Parameters    :     NONE
Return Value  :     return CA_Systerm_ID
NOTES         :     
****************************************************************************/
ABV_UInt32 ABV_CASTB_Get_Current_SysID(void)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Clear_EMM_FP_Disp()
Description   	:   	STB show the EMM Fingerprint, if the stb need clear the disp, call the function 
Parameters    : 	IsComplete:
				ABV_TRUE: show finshed 
				ABV_FALSE:show unfinshed
				
Return Value  :      	success send message to STB : ABV_FALSE  
				failed send message to STB : ABV_TRUE
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_CASTB_Clear_EMM_FP_Disp(ABV_Boolean IsComplete)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_MobileMailGetUA
Description     :      get UA
Parameters    : 	ua : 
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 
****************************************************************************/
ABV_Boolean ABV_MobileMailGetUA(ABV_UInt8* ua)FUNC_TYPE;

/****************************************************************************
name          	: 
Description   	:   	
Parameters    : 	
Return Value	:
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_Pair_GetSTBID(ABV_UInt8 stbid[8])FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_CASTB_Get_Net_Status
Function		:get current net status.
Parameters	:NONE
return 		:
0: CASlib has't get CAT table.
1: there is ABV CAS in current net.
2:there is no ABV CAS in current net.
*******************************************************************************************************/
ABV_UInt8 ABV_CASTB_Get_Net_Status(void)FUNC_TYPE;
/****************************************************************************
name          	: 	ABV_CASTB_Get_Mail_Level
Description     :   get Level of one mail
Parameters    : 	Message_id:Message_id of current mail
Return Level of Mail  :   0 Very Important, 1 Middle Important 2 Important, 3 Normally Mail
NOTES	      : 
****************************************************************************/

ABV_UInt8 ABV_CASTB_Get_Mail_Level(ABV_UInt32 MessageID)FUNC_TYPE;

ABV_Boolean ABV_AS_GetSTBID_True(ABV_UInt8* stbid)FUNC_TYPE;
/*******************************************************************************************************
name		:ABVGetHDCPKey
Function		:Get HDCP key (used for HDMI protect)
Parameters    : 	
			 key : 304 BYTE memory buffer to store HDCPKey 
return 		:NONE
NOTES	      : 	
*******************************************************************************************************/
ABV_Boolean ABVGetHDCPKey(ABV_UInt8 key[304])FUNC_TYPE;

/*******************************************************************************************************
name		:ABV_Get_STBAreaCode
Function		:Get area code of STB
Parameters	: area array to store area code.  
return 		:NONE
NOTES		: 
*******************************************************************************************************/
ABV_Boolean ABV_Get_STBAreaCode(ABV_UInt8 area[4])FUNC_TYPE;
/*******************************************************************************************************
name		:ABVGetCardType
Function		:Get smart card type from CA lib
Parameters	: type  : 0 common card, 1 smart card, 2 master card
return 		: succes ABV_FALSE, failed ABV_TRUE.
NOTES		: STB Call this function to get smart card type ,in Master/slave project
*******************************************************************************************************/
ABV_Boolean ABVGetCardType(ABV_UInt8* type)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_Get_CustomerID()
Description   	:   	get customerid form CASlib for soft cas
Parameters    : 	CustomerID : buffer store customer id  20 BYTE MAX.

Return Value  :      void
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_Get_CustomerID(ABV_UInt8 *CustomerID)FUNC_TYPE;

/*******************************************************************************************************
Funtion		:Connect Provider Server
Parameters	:TCPIP_Struct:connect parameters,STB connect Provider server by this struct.
return 		:ABV_ FALSE：Set Connect Parameters suceess.
		 ABV_ TRUE：Set Connect Parameters failed.
*******************************************************************************************************/		  
ABV_Boolean ABV_STBCA_Connect_Provider(ABV_TCPIP_Connect_s TCPIP_Struct)FUNC_TYPE;

#ifdef __cplusplus
}
#endif
#endif /*end of __ABV_CA_INTERFACE_H__*/
