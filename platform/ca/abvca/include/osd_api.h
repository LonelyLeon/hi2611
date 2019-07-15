/*****************************************************************************
File name     : osd_api.h

Description   : 定义出STB CA 两部分的函数接口

Copyright (C) : ABV 2006

R&D Group	    : ABV_CA

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_OSD_API_H__
#define __ABV_OSD_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"

typedef enum
{
/*调试使用，不强制用户显示*/
   MSG_CA_NO_ERR,					/*正确   0*/
   MSG_STB_GET_ENTITLE,         		/*智能卡获得新授权*/
   MSG_UPDATE_ECM_EMM,			/*用于通知用户收到新的ECM和EMM数据*/ 
/*与节目不相关的需要显示信息*/
   MSG_STB_SC_NO_PAIRED,     		/*机卡不匹配*/
   MSG_SC_ERROR,					/* 错误的智能卡*/
   MSG_NO_SC,                				/*请插入智能卡  5*/
   MSG_CARD_IN_BEGIN,				/* 卡开始初始化*/
   MSG_CARD_IN_END_SUCCESS,		/* 卡初始化成功*/
   MSG_CARD_IN_END_FAIL,			/* 卡初始化失败*/
   MSG_READ_WRITER_ERR,			/*卡交互失败*/
   MSG_SC_PIN_RESET,				/*密码重置成功   10*/
   MSG_STB_SC_PAIRED,				/*机卡配对成功*/
   MSG_STB_SC_FREE_PAIRED,			/*解除机卡配对成功*/
   MSG_STB_SC_PAIRED_FAILED,		/*机卡配对失败*/
   MSG_STB_MODIFY_WATCH_TIME_SUC,		/*修改观看时间成功*/
   MSG_STB_MODIFY_WATCH_TIME_FAILED,	/*修改观看时间失败  15*/
   MSG_MAIL_FULL,					/*邮件已满*/
   MSG_GET_MAIL,					/*邮箱中有未读邮件*/
   MSG_GET_SUB ,					/*有新的屏显*/
   MSG_GET_OTA,						/*有新的OTA信息*/ 
   MSG_EMM_FINGERPRINT,			/*显示用户指纹  20*/
   MSG_NOT_IN_WATCH_TIME,			/*不在设置的节目观看时间之内*/
/*与节目相关需要显示的信息   */
   MSG_OUT_OF_DATE,				/*智能卡过期*/
   MSG_NO_ENTITLE,           			/*没有授权*/
   MSG_MATURE_PRO,           			/*成人级节目*/
   MSG_IPPV_PRO,           				/*IPPV节目    25*/  
   MSG_IPPV_PRO_NO_ENOUGH_TOKEN,/*IPPV节目,余额不足*/   
   MSG_STB_FINGERPRINT,				/* 显示ECM fingerprint*/
   MSG_STB_CLEAR_FINGERPRINT,		/*擦除ECM fingerprint的显示*/
   MSG_STB_AREA_RESTRECT,			/*区域阻塞*/
   MSG_CA_NO_PAIRED,				/*需要机卡配对   30*/
   MSG_ECM_UNKNOWEN_ERROR,		/*错误的节目信息*/
   MST_CLEAR_EMM_FP,				/*擦除正在显示的用户 指纹*/
   MST_CLEAR_CHANNEL_EMM_FP,		/*擦除正在显示的对Channel 的EMM 指纹*/
   									
   MSG_WAIT_ENTITLE,				 /*等待接收授权*/
   MSG_NOT_CONTACT_MASTER,		/*没有母卡 35*/
   MSG_CLEAR_IPPV_SHOW,
   MSG_CHANNEL_EMM_FP,			/*显示对channel 的EMM 指纹*/
   MSG_STB_EXTEND,					/*机顶盒扩展*/
   MSG_FORBID_PVR,   				/*禁止录像*/
   MSG_STBID_ERR,					/*STBID 错误 40*/
   MSG_COVERT_FP,					/*隐藏指纹 41*/
   MSG_STBID_NULL,					/*STBID 为空，需要先烧写stbid 42*/
   MSG_VERSION_UNSUPPORT,		/*not support current version 43*/
   MSG_CHIPID_ERR,					/*pair failed, chipid err*/
   MSG_SC_PAIRSTATUS_ERR,			/*smart card has paird with other stb,STBID lost, or chipid err*///45
   MSG_STOP_FTA,					/*STB can't play FTA program, if receive this message*/
   MSG_START_FTA,					/*STB get the authorization of playing FTA program,when receiv this message*/
   MSG_PPID_UNSUPPORT,			/*not support ppid of the smartcard.*/
   MSG_CHIP_WRONG,				/*CRC of public key not the same with CRC that get from ecm*/
   MSG_AREA_NOT_MATCH,			/*area code err*///50
   MSG_AREA_UPDATE,				/*set new area code*/
   MSG_ALREADY_PAIRED,				/*soft ca allready paired*/
   MSG_CHIP_NOT_MATCH,			/*flash 主芯片不匹配*/
} CA_ERROR_TYPE;

typedef struct _CAS_ERROR_Type
{		
			ABV_UInt16  ServiceID;/*CAS发送此消息时的节目的ServiceID*/
									/*用来判断用户是不是该在当前节目显示此信息*/
			CA_ERROR_TYPE   ca_error_type;
}CAS_ERROR_Type_t;

typedef enum
{
	Disp_All_Mesg,		/*显示所有的调试信息*/
 	Disp_Err_Mesg,		/*只显示错误的调试信息*/
	Disp_Debug_Mesg,	/*只显示正确的调试信息*/
	Disp_No_Mesg		/*CA 内核不显示任何信息*/
} ABV_Print_Type;


/*****************************************************************************************************
*************************Usif Driver ( 提示信息部分)***********************************************
******************************************************************************************************/

/****************************************************************************
name          	 : 	ABV_STBCA_Send_Message_Ca2Stb
Description      :      some necessary information to display
Parameters     : 	message_info			
Return Value   : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		 :      
****************************************************************************/
ABV_Boolean ABV_STBCA_Send_Message_Ca2Stb(CAS_ERROR_Type_t *message_info)FUNC_TYPE;
/****************************************************************************
name          	 : 	ABV_STBCA_Init_Print_Type
Description      :     CA  Lib Print type
Parameters     : 	Type:Print type			
Return Value   : 	ABV_Print_Type
NOTES		 :      
****************************************************************************/
ABV_Print_Type ABV_STBCA_Init_Print_Type(void)FUNC_TYPE;


/****************************************************************************
name          	 : 	ABV_STBCA_Print_Data2Screen
Description      :     Display data on the screen 
Parameters     : 	pBuffer:data
				Length:Data Length
Return Value   : 	ABV_VOID	
NOTES		 :      
****************************************************************************/
void ABV_STBCA_Print_Data2Screen(ABV_UInt8 *pBuffer,ABV_UInt16 Length)FUNC_TYPE;

/*****************************************************************************************************
**************************************************END***********************************************
******************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif

