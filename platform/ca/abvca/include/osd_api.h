/*****************************************************************************
File name     : osd_api.h

Description   : �����STB CA �����ֵĺ����ӿ�

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
/*����ʹ�ã���ǿ���û���ʾ*/
   MSG_CA_NO_ERR,					/*��ȷ   0*/
   MSG_STB_GET_ENTITLE,         		/*���ܿ��������Ȩ*/
   MSG_UPDATE_ECM_EMM,			/*����֪ͨ�û��յ��µ�ECM��EMM����*/ 
/*���Ŀ����ص���Ҫ��ʾ��Ϣ*/
   MSG_STB_SC_NO_PAIRED,     		/*������ƥ��*/
   MSG_SC_ERROR,					/* ��������ܿ�*/
   MSG_NO_SC,                				/*��������ܿ�  5*/
   MSG_CARD_IN_BEGIN,				/* ����ʼ��ʼ��*/
   MSG_CARD_IN_END_SUCCESS,		/* ����ʼ���ɹ�*/
   MSG_CARD_IN_END_FAIL,			/* ����ʼ��ʧ��*/
   MSG_READ_WRITER_ERR,			/*������ʧ��*/
   MSG_SC_PIN_RESET,				/*�������óɹ�   10*/
   MSG_STB_SC_PAIRED,				/*������Գɹ�*/
   MSG_STB_SC_FREE_PAIRED,			/*���������Գɹ�*/
   MSG_STB_SC_PAIRED_FAILED,		/*�������ʧ��*/
   MSG_STB_MODIFY_WATCH_TIME_SUC,		/*�޸Ĺۿ�ʱ��ɹ�*/
   MSG_STB_MODIFY_WATCH_TIME_FAILED,	/*�޸Ĺۿ�ʱ��ʧ��  15*/
   MSG_MAIL_FULL,					/*�ʼ�����*/
   MSG_GET_MAIL,					/*��������δ���ʼ�*/
   MSG_GET_SUB ,					/*���µ�����*/
   MSG_GET_OTA,						/*���µ�OTA��Ϣ*/ 
   MSG_EMM_FINGERPRINT,			/*��ʾ�û�ָ��  20*/
   MSG_NOT_IN_WATCH_TIME,			/*�������õĽ�Ŀ�ۿ�ʱ��֮��*/
/*���Ŀ�����Ҫ��ʾ����Ϣ   */
   MSG_OUT_OF_DATE,				/*���ܿ�����*/
   MSG_NO_ENTITLE,           			/*û����Ȩ*/
   MSG_MATURE_PRO,           			/*���˼���Ŀ*/
   MSG_IPPV_PRO,           				/*IPPV��Ŀ    25*/  
   MSG_IPPV_PRO_NO_ENOUGH_TOKEN,/*IPPV��Ŀ,����*/   
   MSG_STB_FINGERPRINT,				/* ��ʾECM fingerprint*/
   MSG_STB_CLEAR_FINGERPRINT,		/*����ECM fingerprint����ʾ*/
   MSG_STB_AREA_RESTRECT,			/*��������*/
   MSG_CA_NO_PAIRED,				/*��Ҫ�������   30*/
   MSG_ECM_UNKNOWEN_ERROR,		/*����Ľ�Ŀ��Ϣ*/
   MST_CLEAR_EMM_FP,				/*����������ʾ���û� ָ��*/
   MST_CLEAR_CHANNEL_EMM_FP,		/*����������ʾ�Ķ�Channel ��EMM ָ��*/
   									
   MSG_WAIT_ENTITLE,				 /*�ȴ�������Ȩ*/
   MSG_NOT_CONTACT_MASTER,		/*û��ĸ�� 35*/
   MSG_CLEAR_IPPV_SHOW,
   MSG_CHANNEL_EMM_FP,			/*��ʾ��channel ��EMM ָ��*/
   MSG_STB_EXTEND,					/*��������չ*/
   MSG_FORBID_PVR,   				/*��ֹ¼��*/
   MSG_STBID_ERR,					/*STBID ���� 40*/
   MSG_COVERT_FP,					/*����ָ�� 41*/
   MSG_STBID_NULL,					/*STBID Ϊ�գ���Ҫ����дstbid 42*/
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
   MSG_CHIP_NOT_MATCH,			/*flash ��оƬ��ƥ��*/
} CA_ERROR_TYPE;

typedef struct _CAS_ERROR_Type
{		
			ABV_UInt16  ServiceID;/*CAS���ʹ���Ϣʱ�Ľ�Ŀ��ServiceID*/
									/*�����ж��û��ǲ��Ǹ��ڵ�ǰ��Ŀ��ʾ����Ϣ*/
			CA_ERROR_TYPE   ca_error_type;
}CAS_ERROR_Type_t;

typedef enum
{
	Disp_All_Mesg,		/*��ʾ���еĵ�����Ϣ*/
 	Disp_Err_Mesg,		/*ֻ��ʾ����ĵ�����Ϣ*/
	Disp_Debug_Mesg,	/*ֻ��ʾ��ȷ�ĵ�����Ϣ*/
	Disp_No_Mesg		/*CA �ں˲���ʾ�κ���Ϣ*/
} ABV_Print_Type;


/*****************************************************************************************************
*************************Usif Driver ( ��ʾ��Ϣ����)***********************************************
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

