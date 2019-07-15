/*************************************************************************************************

File Name      :  hrca_display.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-02     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_DISPLAY_H_
#define _HRCA_DISPLAY_H_

#include <stdint.h>
#include "dCA.h"
#include "dScroll.h"
#include "hrca_config.h"
#if EMBED_CA != FREEACCESS

/************************************************************************************************/
/*************************************Static  Variable  for  CA *******************************************/
/*************************************��ƽ̨CA��ʾ����ȫ�ֱ�������*******************************************/
/************************************************************************************************/
						
#if ((EMBED_CA & CDCA) == CDCA) 
    #include "../../cdca/include/CDCASS.h"
    #include "dca/cdca_fun.h"
    #include "dca/cdca_internal.h"
    extern D_CAFingerInfo CdcaFinger;
    extern D_CaOSDPreDefined cdca_pre_defined_osds[];
#endif
								
#if ((EMBED_CA & DVTCA) == DVTCA)
    #include "dca/dvtca_fun.h"
    #include "dca/dvtca_internal.h"
    extern D_CaOSDPreDefined dvtca_pre_defined_osds[];
#endif

#if ((EMBED_CA & CTICA) == CTICA)
    #include "../../ctica/include/ctiapi.h"
    #include "dca/ctica_fun.h"
	#include "dca/ctica_internal.h"
	extern D_CaOSDPreDefined ctica_pre_defined_osds[];
	extern D_CAOrdinaryFinger CticaFinger;
#endif
											
#if ((EMBED_CA & MGCA) == MGCA)
	#include "dca/mgca_fun.h"
   	#include "dca/mgca_internal.h"
	extern D_CaOSDPreDefined mgca_pre_defined_osds[];
#endif

#if ((EMBED_CA & GYCA) == GYCA)
	#include "../gyca/include/gyca_fun.h"
	#include "../gyca/include/gyca_internal.h"
#endif

#if ((EMBED_CA & TRCA) == TRCA) 
    #include "../../trca/include/Tr_Cas.h"
    #include "dca/trca_fun.h"
	#include "dca/trca_internal.h"
    extern D_CaOSDPreDefined trca_pre_defined_osds[];
#endif	

#if ((EMBED_CA & WFCA) == WFCA)
	#include "dca/wfca_fun.h"
	extern D_CaOSDPreDefined wfca_pre_defined_osds[];
#endif
													
#if ((EMBED_CA & QZCA) == QZCA)
	#include "dca/qzca_fun.h"
	extern D_CaOSDPreDefined qzca_pre_defined_osds[];
#endif
															
#if ((EMBED_CA & XGCA) == XGCA) 
	#include "dca/xgca_fun.h"
	extern D_CaOSDPreDefined xgca_pre_defined_osds[];
#endif
																
#if ((EMBED_CA & DIVICA) == DIVICA)
    #include "dca/divica_fun.h"
	#include "dca/divica_internal.h"
	extern D_CaOSDPreDefined divica_pre_defined_osds[];

#endif
																	
#if ((EMBED_CA & DSCA) == DSCA)
    #include "dca/dsca_fun.h"
    #include "dca/dsca_internal.h"	
    extern D_CaOSDPreDefined dsca_pre_defined_osds[];
#endif
																		
#if ((EMBED_CA & DVNCA) == DVNCA)
    #include "dca/dvnca_fun.h"
	#include "dca/dvnca_internal.h"
    extern D_CaOSDPreDefined dvnca_pre_defined_osds[];
    extern D_CaOSDPreDefined dvnca_smpair_defined_osds[];
#endif
																			
#if ((EMBED_CA & GOSCA) == GOSCA)
	#include "dca/gosca_internal.h"
    #include "dca/gosca_fun.h"    
    #include "../../gosca/include/GOSCAS_STBDataPublic.h"
	#include "../../gosca/include/GOSCAS_STBInf.h"
	extern D_CaOSDPreDefined gosca_pre_defined_osds[];
#endif

#if ((EMBED_CA & ABVCA) == ABVCA)
    #include "dca/abvca_fun.h"
	#include "dca/abvca_internal.h"
	extern D_CaOSDPreDefined abvca_pre_defined_osds[];
#endif

#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
    #include "dca/unitendca_fun.h"
	#include "dca/unitendca_internal.h"
    #include "../../unitendca/include/udrm.h"
    extern D_CaOSDPreDefined unitendca_pre_defined_osds[];
#endif

#if ((EMBED_CA & THTFCA) == THTFCA)
    #include "dca/thtfca_fun.h"
	#include "dca/thtfca_internal.h"
    extern D_CaOSDPreDefined thtfca_pre_defined_osds[];
#endif

#if ((EMBED_CA & LXDTCA) == LXDTCA)
    #include "dca/lxdtca_fun.h"
	#include "dca/lxdtca_internal.h"
    #include "../../lxdtca/include/LxDtCa_Usr.h"
    extern D_CaOSDPreDefined lxdtca_pre_defined_osds[];
#endif

#if ((EMBED_CA & YJCA) == YJCA)
    #include "dca/yjca_fun.h"
	#include "dca/yjca_internal.h"
    extern D_CaOSDPreDefined yjca_pre_defined_osds[];
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    #include "dca/scca_fun.h"
    #include "dca/scca_internal.h"
    extern D_CaOSDPreDefined scca_pre_defined_osds[];
#endif

#if ((EMBED_CA & COLABLECA) == COLABLECA)
	#include "dca/colableca_fun.h"
	#include "dca/colableca_internal.h"
    extern D_CaOSDPreDefined hcnca_pre_defined_osds[];
	extern uint8_t  feeInfo[100];
#endif

#if ((EMBED_CA & XSMCA) == XSMCA)
	#include "dca/xsmca_fun.h"
	#include "dca/xsmca_internal.h"
    extern D_CaOSDPreDefined xsmca_pre_defined_osds[];
#endif


typedef    enum
{
	CA_EMAIL_NEW_DISP,				// ���ʼ���ʾ
	CA_EMAIL_HIDE_DISP,				// �������ʼ���ʾ
	CA_EMAIL_FULL_DISP,				// ��������
	CA_EMAIL_OSD_DISP
}hrca_ca_email_e;

typedef    enum
{
#if ((EMBED_CA & CDCA) == CDCA)
	CDCA_PROMPT_CLEAR = 0x00,		//0x00 ȡ����ǰ����ʾ 
	CA_PROMPT_BADCARD,				//0x01 �޷�ʶ��Ŀ� 
	CA_PROMPT_EXPICARD,				//0x02 ���ܿ����ڣ�������¿�
	CA_PROMPT_NOT_INSERTCARD,		//0x03 ���Ž�Ŀ����������ܿ� 
	CA_PROMPT_NOOPER,				//0x04 ���в����ڽ�Ŀ��Ӫ�� 
	CA_PROMPT_BLACKOUT,				//0x05 ��������   
	CA_PROMPT_OUTWORKTIME,			//0x06 ��ǰʱ�α��趨Ϊ���ܹۿ� 
	CA_PROMPT_WATCHLEVEL,			//0x07 ��Ŀ��������趨�Ĺۿ����� 
	CA_PROMPT_PAIRING,				//0x08 ���ܿ��뱾�����в���Ӧ 
	CA_PROMPT_NOENTITLE,			//0x09 û����Ȩ  
	CA_PROMPT_DECRYPTFAIL,			//0x0A ��Ŀ����ʧ�� 
	CA_PROMPT_NOMONEY,				//0x0B ���ڽ��� 
	CA_PROMPT_ERRREGION,			//0x0C ������ȷ 
	CA_PROMPT_NEEDFEED,				//0x0D �ӿ���Ҫ��ĸ����Ӧ�������ĸ�� 
	CA_PROMPT_ERRCARD,				//0x0E ���ܿ�У��ʧ�ܣ�����ϵ��Ӫ�� 
	CA_PROMPT_UPDATE,				//0x0F ���ܿ��������벻Ҫ�ο����߹ػ� 
	CA_PROMPT_LOWCARDVER,			//0x10 ���������ܿ� 
    CA_PROMPT_VIEWLOCK,				//0x11 ����Ƶ���л�Ƶ��
	CA_PROMPT_MAXRESTART,			//0x12 ���ܿ���ʱ���ߣ���5���Ӻ����¿��� 
	CA_PROMPT_FREEZE,				//0x13 ���ܿ��Ѷ��ᣬ����ϵ��Ӫ�� 
	CA_PROMPT_CALLBACK,				//0x14 ���ܿ�����ͣ����ش����Ӽ�¼����Ӫ�� 
	CA_PROMPT_CURTAIN,				//0x15 �߼�Ԥ����Ŀ���ý׶β�����ѹۿ�
	CA_PROMPT_CARDTESTSTART,		//0x16 �������Կ�������...
	CA_PROMPT_CARDTESTFAILD,		//0x17 �������Կ�����ʧ�ܣ��������ͨѶģ��
	CA_PROMPT_CARDTESTSUCC,			//0x18 �������Կ����Գɹ�
   	CA_PROMPT_NOCALIBOPER,			//0x19 ���в�������ֲ�ⶨ����Ӫ��
	CA_PROMPT_STBLOCKED,			//0x1A ������������ 
   	CA_PROMPT_STBFREEZE,			//0x1B �����б�����
   	CA_FEEDING_NOTE,				//0x1C ĸ�����ݶ�ȡ�ɹ�������ӿ�
	CA_FEEDFAIL_NOTE,				//0x1D ĸ�����ݶ�ȡʧ��
	CA_NOT_XXCA,					//0x1E ��ͬ��CA
    
	CDCA_SHOW_FINGER_PRINTING,		//0x1F ��ʾָ��
	CDCA_HIDE_FINGER_PRINTING,		//0x20 ����ָ��
	CDCA_SHOW_OSD_MESSAGE,			//0x21 ��ʾosd
	CA_HIDE_OSD_MESSAGE,			//0x22 ����osd
	CDCA_NEW_EMAIL_NOTE,			//0x23���ʼ���ʾ
	CDCA_HIDE_EMAIL_NOTE,			//0x24 �������ʼ���ʾ
	CDCA_EMAIL_FULL_NOTE,			//0x25 ��������
	CA_PROMPT_IPPVSTART,			//0x26 ��ʾippv
	CA_PROMPT_IPPVHIDE,				//0x27 ����ippv
	CA_NEW_DETITLE_NOTE,			//0x28 �µķ���Ȩ��ʾ
	CA_HIDE_DETITLE_NOTE,			//0x29 ���ط���Ȩ
	CA_DETITLE_FULL_NOTE,			//0x2A ����Ȩ��Ϣ����
	CA_FEED_HIDE,					//0x2B �����ӿ�ι����ʾ
	CA_PROMPT_NOTP,					//0x2C
	CDCA_SHOW_URGENCY_BROADCAST,	//0x2D //���ڽ����㲥
	CDCA_HIDE_URGENCY_BROADCAST,	//0x2E
	CA_SHOW_SUPERLOOK_NOTE,			//0x2F
	CA_HIDE_SUPERLOOK_NOTE,    		//0x30
#endif

#if ((EMBED_CA & DVTCA) == DVTCA)
	CA_PROMPT_RATING_TOO_LOW = 0x00,		//0x00//�տ����𲻹�
	CA_PROMPT_NOT_IN_WATCH_TIME,			//0x01//�����տ�ʱ����
	CA_PROMPT_NOT_PAIRED,					//0x02//û�л�����Ӧ
	CA_PROMPT_IS_PAIRED_OTHER,				//0x03//IC�������������ж�Ӧ
	CA_PROMPT_PLEASE_INSERT_CARD,			//0x04//��忨	
	CA_PROMPT_NO_ENTITLE,					//0x05//û�й���˽�Ŀ
	CA_PROMPT_PRODUCT_RESTRICT,				//0x06//��Ӫ�����ƹۿ��ý�Ŀ
	CA_PROMPT_AREA_RESTRICT,				//0x07//��Ӫ����������ۿ�
	CA_PROMPT_MOTHER_RESTRICT,				//0x08//�˿�Ϊ�ӿ����Ѿ��������տ�������ĸ�����
	CA_PROMPT_NO_MONEY,						//0x09//���㣬���ܹۿ��˽�Ŀ���뼰ʱ��ֵ
	CA_PROMPT_IPPV_NO_CONFIRM,				//0x0A//�˽�ĿΪIPPV��Ŀ���뵽IPPV��Ŀȷ��/ȡ������˵���ȷ�Ϲ���˽�Ŀ
	CA_PROMPT_IPPV_NO_BOOK,					//0x0B//�˽�ĿΪIPPV��Ŀ����û��Ԥ����ȷ�Ϲ��򣬲��ܹۿ��˽�Ŀ
	CA_PROMPT_IPPT_NO_CONFIRM,				//0x0C//�˽�ĿΪIPPT��Ŀ���뵽IPPT��Ŀȷ��/ȡ������˵���ȷ�Ϲ���˽�Ŀ
	CA_PROMPT_IPPT_NO_BOOK,					//0x0D//�˽�ĿΪIPPT��Ŀ����û��Ԥ����ȷ�Ϲ��򣬲��ܹۿ��˽�Ŀ
	CA_PROMPT_IPPV_NO_MONEY,				//0x0E//�˽�ĿΪIPPV��Ŀ�����㣬���ܹۿ����뼰ʱ��ֵ
	CA_PROMPT_IPPT_NO_MONEY,				//0x0F//�˽�ĿΪIPPT��Ŀ�����㣬���ܹۿ����뼰ʱ��ֵ
   	CA_PROMPT_DATA_INVALID,					//0x10//������Ч��STB�����κ���ʾ������Կ���⡣
	CA_PROMPT_SLOT_NOT_FOUND,				//0x11//Ǯ��������
	CA_PROMPT_SC_NOT_SERVER, 				//0x12//IC������ֹ����
	CA_PROMPT_TVS_NOT_FOUND,				//0x13//��Ӫ�̲�����
	CA_PROMPT_KEY_NOT_FOUND, //20			//0x14//�˿�δ���������ϵ��Ӫ��
	CA_PROMPT_IPPNEED_CALLBACK,				//0x15//����ϵ��Ӫ�̻ش�IPP��Ŀ��Ϣ
	CA_PROMPT_FREE_PREVIEWING,              //0X16�û����ã��˽�Ŀ����δ�����������Ԥ����
	CA_PROMPT_TERMINAL_NOT_ACTIVATE,	    //0x17�ն�δ����terminal is not activated
    CA_PROMPT_TERMINAL_NOT_SERVER,			//0x18�ն˱�����terminal is forbidden 
    CA_PROMPT_FREEPREVIEW_OVER,			    //0x19����Ԥ������preview is over
    CA_PROMPT_FREEPREVIEW_ALLOVER,		    //0x1A����Ŀ����Ԥ�������ѵ�today's preview of this program has been used up  

	DVTCA_PROMPT_CLEAR,  				    //0X1E

	DVTCA_SHOW_FINGER_PRINTING, 			//0x1F
	DVTCA_HIDE_FINGER_PRINTING,  			//0x20
	CA_SHOW_OSD_MESSAGE,
	DVTCA_SHOW_URGENCY_BROADCAST,			//���ڽ����㲥
	DVTCA_HIDE_URGENCY_BROADCAST,
	CA_SHOW_INQUIRE_IPP,
	DVTCA_NEW_EMAIL_NOTE,
	DVTCA_HIDE_EMAIL_NOTE,					//
	DVTCA_EMAIL_FULL_NOTE,					//   
	CA_SINGLE_AREA_LOCK,
	CA_UNKNOWN_ERR,

	CA_DECRYPT_FAILURE,
	DVTCA_HIDE_FREE_PREVIEWING,             //������Ԥ��
	DVTCA_ANNO_SHOW,
	DVTCA_ANNO_HIDE,
#endif

#if ((EMBED_CA & CTICA) == CTICA)
	CTICA_PROMPT_CLEAR = 0x00,             //0x00 �����ʾ��Ϣ
	CA_PROMPT_SC_OUT,                      //0x01 ��������ܿ�
	CA_PROMPT_SC_UNKNOWN,                  //0x02 �޷�ʶ�����ܿ�
	CA_PROMPT_SC_CHECK,                    //0x03 ����У�����ܿ�
	CA_PROMPT_STB_NOT_MATCH,               //0x04  ��������Ӧ

	CA_PROMPT_LOW_PARENTAL_RATING,         //0x05 ��ĸ������̫��
	CA_PROMPT_UNKNOWN_ENCRYPT_PROGRAMME,   //0x06 �޷�ʶ��ļ��ܽ�Ŀ
	CA_PROMPT_NOT_ENTITLE,                 //0x07 û�н�����Ȩ
	STATUS_CA_DESCRAMBLE_SUCCESS,          //0x08 
	STATUS_CA_IPPV_PROGRAMME,              //0x09

	STATUS_CA_SC_IN,                       //0x0a
	STATUS_SUBTITLE_GOT,                   //0x0b 
	STATUS_NEW_MAIL_GOT,                   //0x0c
	STATUS_IPPV_PIN_ERROR,                 //0x0d
	STATUS_IPPV_NO_ENOUGH_CREDIT,          //0x0e

	CA_PROMPT_IPPV_NOTIFY,                 //0x0f  IPPV��Ŀ	������
	STATUS_NO_SIGNAL,                      //0x10
	STATUS_SERVICE_UNKNOWN,                //0x11
	STATUS_PPID_CALL,                      //0x12
	STATUS_PIN_CORRECT,                    //0x13

	STATUS_PIN_INCORRECT,                  //0x14
	STATUS_IPPV_BUY,                       //0x15
	STATUS_IPPV_OK,                        //0x16
	STATUS_IPPV_FAIL,                      //0x17
	STATUS_IPPVP_PIN_ERROR,                //0x18

	STATUS_IPPV_NO_MONEY,                  //0x19
	STATUS_IPPVP_UNSUPPORT_MODE,           //0x1a  
	STATUS_PPV_LIST_INFO_NOTIFY_OK,        //0x1b   
	STATUS_IPPV_LIST_INFO_NOTIFY_OK,       //0x1c
	STATUS_PIN_CHANGE,                     //0x1d

	STATUS_PIN_FAIL,                       //0X1e
	STATUS_RAT_CHANGE,                     //0X1f
	STATUS_RAT_FAIL,                       //0X20
	STATUS_RAT_PINERR,                     //0x21
	STATUS_OLDPIN_ERROR,                   //0x22

	CTICA_SHOW_FINGER_PRINTING,            //0x23
	CTICA_HIDE_FINGER_PRINTING,            //0x24
	STATUS_ENTITLE_PWSUCCESS,              //0x25
	STATUS_ENTITLE_PWFAIL,                 //0x26
	CA_PROMPT_ECM_FILTER_ERROR,            //0x27 ����ECMͨ��ʧ��

	CA_PROMPT_OPEN_DES_FAILED,             //0x28 ����ͨ������ʧ��
	CA_PROMPT_SC_DES,                      //0x29 ����ʱ���ܿ�����
	CA_PROMPT_CW_ERROR,                    //0x2a �����ֳ���
	CA_PROMPT_IPPV_EXPIRED,                //0x2b IPPV��Ŀ����
	STATUS_ANTI_OK,                        //0x2c

	STATUS_ANIT_NOT,                       //0x2d
	STATUS_MAIL_NO_ENOUGH_SPACE,           //0x2e
	CA_PROMPT_NOT_CTICA,                   //0x2f  ��CTICA
	CA_PROMPT_FORCE_CHANGE_CHANNEL,        //0x30 ǿ���л�Ƶ��
	STATUS_REQ_CHANGE_CHANNEL,             //0x31

	CA_PROMPT_AF_PLAY_SET_OK,              //0x32 �û�׼�������óɹ�
	CA_PROMPT_AF_PLAY_READ_OK,             //0x33 �û�׼�������ݶ�ȡ�ɹ�
	CA_PROMPT_AF_PLAY_SET_TIME_ERROR,      //0x34 �û�׼��������ʱ�����
	CA_PROMPT_AF_PLAY_SET_TIME_LONG_ERROR, //0x35 �û�׼��������ʱ�䳬��
	CA_PROMPT_AF_PLAY_SET_SLOT_ERROR,      //0x36 �û�׼��������ͨ������

	CA_PROMPT_AF_PLAY_SET_MODE_ERROR,      //0x37 �û�׼��������ģʽ����
	CA_PROMPT_AF_PLAY_SET_PIN_ERROR,       //0x38 �û�׼��������PIN�����
	CA_PROMPT_AF_PLAY_SET_ERROR,           //0x39 �û�׼��������ʧ��
	CA_PROMPT_CHILD_CARD_VERIFY_OK,        //0x3a �ӿ���֤�ɹ�
	CA_PROMPT_CARD_OK,                     //0x3b ���ܿ�OK

	CA_PROMPT_CHILD_CARD_VERIFY_ERROR,     //0x3c �ӿ���֤ʧ��
	CA_PROMPT_MOTHER_CARD_VERIFY_ERROR,    //0x3d ĸ����֤ʧ��
	CA_PROMPT_CHILD_CARD_EXPIRED_ERROR,    //0x3e �ӿ���֤����
	CA_PROMPT_STB_REGION_ERROR,            //0x3f �����벻��ȷ
	CA_PROMPT_USER_AF_PLAY_CTRL,           //0x40 �û�׼��������

	CA_PROMPT_REGION_AF_PLAY_CTRL,         //0x41 ����׼��������
	STATUS_PROG_SKIP_CANCEL,               //0x42

	CTICA_NEW_EMAIL_NOTE,				   //���ʼ�
	CTICA_HIDE_EMAIL_NOTE,				   //�����ʼ���־
	CTICA_EMAIL_FULL_NOTE,				   //�ʼ�����
	//CTICA_SHOW_URGENCY_BROADCAST,		   //�����㲥
	CA_CHOOSE_URGENCY,					   //ѡ���Ƿ����������㲥�ĶԻ���,�Ի�����Ҫ��ʾ�����㲥������

#endif

#if ((EMBED_CA & MGCA) == MGCA)

	MGCA_ERR_SCARD_NOT_ACT = 0x00,	   	   //�뼤���ӿ�
	MGCA_ERR_SCARD_DISABLED,         //�뼤���ӿ�/*the leavetimelength<0 in the son card 20071218 eileen*/
	MGCA_ERR_ZONE_CODE,              //���ܿ����������    /*the zone code is not compatible with networkid in NIT 20080328 eileen*/
	MGCA_ERR_NO_MONEY,		   	   //���ܿ�����
	MGCA_ERR_NOT_AUTHORED,		   //��Ŀδ��Ȩ
	MGCA_ERR_CARD_LOCKED,			   //���ܿ�����
	MGCA_ERR_APP_LOCKED,			   //��������
	MGCA_ERR_PIN_AUTHEN,			   //������Դ���
	MGCA_ERR_PINERR_STB_PAIRED,	   //������Դ������ܿ�δ��ԣ������������
	MGCA_ERR_PINERR_CARD_PAIRED,	   //������Դ������ܿ�����ԣ�������δ���
	MGCA_ERR_EXTER_AUTHEN,		   //���ܿ���֤ʧ��
	MGCA_ERR_GET_CARD_DATA,		   //���ܿ����ݴ���
	MGCA_ERR_ILLEGAL_CARD,		   //���ܿ�ͨ�Ŵ���
	MGCA_ERR_DONOT_TELEVIEW_PPV,	   //PPV�շѽ�Ŀ
	MGCA_ERR_CARD_NOTFOUND,		   //��������ܿ�
	MGCA_ERR_CARD_NOTMATCH, 		   //���ܿ���ƥ��  /* v3.1.2 added, hanjf */
	MGCA_ERR_UPDATE_GK, 			   //���ܿ�����ʧ��   /* v3.1.2 added, hanjf */

	MGCA_EMM_APP_STOP,			   //���ܿ���ͣ����
	MGCA_EMM_APP_RESUME,			   //���ܿ��ָ�����
	MGCA_EMM_PROG_UNAUTH,			   //ȡ����Ŀ����
	MGCA_EMM_PROG_AUTH ,			   //���ӽ�Ŀ����
	MGCA_EMM_EN_PARTNER,			   //���û������
	MGCA_EMM_DIS_PARTNER,			   //ȡ���������
	MGCA_EMM_UPDATE_GNO,			   //���ܿ���Ÿ���
	MGCA_EMM_UPDATE_GK,			   //���ܿ�����������������
	MGCA_EMM_SONCARD,				   //������ĸ��
	MGCA_EMM_URGENT_SERVICE, 		   //���л���Ŀ��Ƶ������������
	MGCA_EMM_MODIFY_ZONECODE,		   //���ܿ����������
	MGCA_EMM_UPDATE_CRT,			   //��Ȩ����
	MGCA_EMM_MODIFY_CTRLCODE,		   //���ܿ��޲������
	MGCA_ERR_CONTROL_PLAY,		   //����Ŀ�����޲�
	MGCA_ERR_AUTH_CLOSED,			   //����Ŀ��Ȩ�ر�
	MGCA_ERR_AUTH_OVERDUE,		   //���ܿ���Ȩ����
	MGCA_ERR_AUTH_UPDATE,			   //��Ȩˢ�£����Ժ�
	MGCA_ERR_ILLEGAL_AUTH,		   //���ܿ���Ȩ����
	MGCA_ERR_CARD_STATUS_RENEW,	   //���ܿ�״̬���£�������������
	MGCA_ERR_CARD_OPERATE,		   //���ܿ�����ʧ��
    MGCA_ERR_CARDOUT_PLEASEIN,	   //��������ܿ�
    MGCA_NOT_MGCA,				   //��MGCAS (0x26)


	MGCA_SUCCESS,				       //����������
	MGCA_ERR_PINERR_SC_NOTMATCH,	   //������Դ��󣺻����ٲ���X�κ󽫱�����//-------2012.06.11--------------------
	MGCA_EMM_EMAIL,				   //��ʾ���ʼ�ͼ��
	MGCA_EMM_CHARGE,				   //����Ǯ����ֵ�ɹ�����ֵ���X��
	MGCA_ECM_PPV_UPD,				   //��PPV��ͼ�꣨�������ʼ�����IPPV����ǰ���֣���ʾ����ppv��Ŀ��������
	MGCA_ECM_PreAuth_UPD,			   //"Ԥ��Ȩ"ͼ�꣨�������ʼ�����IPPV����ǰ���֣���ʾ����Ԥ��Ȩ�Ľ�Ŀ��
	MGCA_PreAuth_UPD_VANISH,		   //���"Ԥ��Ȩ"ͼ��
	MGCA_HIDE_EMAIL_NOTE,			   //�ʼ�
	MGCA_ERR_QUESTION_TELEVIEW_PPV,  //PPV��Ŀ�빺��					
	MGCA_ERR_AUTHNEARBOOT_REMIND,	   //��Ŀ��Ȩʣ��X�죬�뼰ʱ����
	MGCA_ERR_AUTHNEARTIME_REMIND,	   //��Ŀ��Ȩʣ��X�죬�뼰ʱ����
	MGCA_ERR_AUTHEXPIRE_REMIND,	   //��Ŀ��Ȩ�ѹ��ڣ��뼰ʱ����

	MGCA_HIDE_IPPV_ICON,
	MGCA_SHOW_URGENCY_ICON,
	MGCA_HIDE_URGENCY_ICON,
	MGCA_HIDE_AUTH_REMAIN_DLG,
	MGCA_HIDE_PURSE_DLG,
	MGCA_HIDE_EXPIR_DLG,

#endif

#if ((EMBED_CA & GYCA) == GYCA)
//---����Ϊ����ʾ--
	CA_NO_CASH = 0x00, 						//���ܿ����޽��
	CA_NOT_ENOUGH_CASH,						//���ܿ�����
	CA_ENTITLEMENT_EXPIRED,					//���ķ����ѵ���
	CA_LOGOUT,								//���ܿ���ע��
	CA_NOT_ENTITLED_USER, 					//����Ƶ��, �û�����Ȩ
	CA_SMARTCARD_DISABLED, 				  	//���ܿ�δ����
	CA_UPGADING_PLEASE_WAIT, 				//���������㷨,���Ժ�...
	CA_DECRYPT_ERROR,  					    //���ܿ������쳣
	CA_CALL_FOR_STOP, 					    //���ܿ��ѱ�ͣ
	CA_READING_SMARTCARD, 			   		//���ڶ�ȡ���ܿ�, ���Ժ�
	CA_CHECK_SMARTCARD, 					//����Ƶ��, �������ܿ�
	CA_CHECK_CARD_DIRECTION, 				//�޷�ʶ��, ����忨����
	CA_UNKNOWN_SMART_CONTACT_SUPPLIERS, 	//���ܿ��汾��, ����ϵ��Ӧ��
	CA_READSMART_ERR_PLEASE_CHECK,   		//��������, �������ܿ�
	CA_WRITESMART_ERR_PLEASE_CHECK,  		//д������, �������ܿ�
	CA_INSERT_SMART_PLEASE, 				//��������ܿ�
	CA_UNKNOWN_SMART_PLEASE_CHECK,  		//����ʶ��ÿ�, �������ܿ�
	CA_SMART_BOX_NOT_MATCHED, 			    //������ƥ��
	CA_PIN_ERR, 							//PIN�����
	CA_SMART_LEVEL_NOT_ENOUGH,  			//���ܿ����𲻹�
	CA_UNKNOWN_BOX_TYPE, 					//�������ͺŲ�֧��
	CA_INSERT_PARENT_CARD,    				//���Ȳ�������
	CA_SON_CARDERR_INSERT_PARENT, 			//�ӿ�������ʱ, ���������
	CA_UNCORRECT_SUBSCRIBER, 				//�ӿ��û�����ƥ��
	CA_CARD_AREA_ERR,						//�û�������ȷ
	CA_STB_AREA_ERR, 						//��������������
	CA_CONDITIONAL_LIMITED,					//��������
	CA_DEBUG_VERSION, 						//���԰�, ��ֹ����
	CA_UNKNOWN_ERR = 28,					//δ֪��Ϣ
	CA_NEED_ADD_ENUM,                       //û���ҵ��Ϳ���ʾһ�µ�ö�����ͣ�������Ҫ���ö�ٶ��壡
//-----------------

	CA_NOTICE_SHOW,         // ��ʾ��Ŀ���ܲ��ŵ���ʾ��Ϣ--
	CA_NOTICE_ERASE,		// ������ʾ��Ϣ					 --
	CA_OSD_ERASE,			// ����OSD��Ϣ					 --
	CA_RESTART_CHAN,		// ����Ӧ�ó������²��ŵ�ǰ��Ŀ
	CA_OSD_INFO,			// ��EMM,PEMM OSD��Ϣ֪ͨ
	CA_MAIL_INFO,			// ��EMM,PEMM Mail��Ϣ֪ͨ
	CA_EXECUTE_OP_INFO,	    // Ҫ�������ִ�о���Ļ����в���
	CA_SW_UPDATE_INFO,		// ��EMM,PEMM ���������Ϣ֪ͨ
	CA_TRANSPARENT_INFO,	// CA ͸���������е�˽����Ϣ
	CA_FINGER_SHOW,		    // Ҫ����ʾָ����Ϣ
	CA_FINGER_ERASE,		// Ҫ�����ָ����Ϣ
	CA_IPPV_INFO,			// IPPV ��Ϣ
	GYCA_NEW_EMAIL_NOTE,		// ���ʼ�(ͼ��)
	GYCA_HIDE_EMAIL_NOTE,
	GYCA_EMAIL_FULL_NOTE,
	CA_SWITCH_CHANNEL,
	CA_SEARCH_CHANNEL,
	CA_NOT_XXCA,
	CA_CARD_NOTFOUND,		//��������ܿ�
	GYCA_PROMPT_CLEAR,		//�Ǽ���̨����

#endif

#if ((EMBED_CA & TRCA) == TRCA)
    CA_PROMPT_E00 = 0x00,  // 0x00  E00 ��ǰ��Ŀû����(�����ʾ��Ϣ)
    CA_PROMPT_E01,  // 0x01  E01 �����CAģ��
    CA_PROMPT_E02,  // 0x02  E02 CAģ��EEPROMʧ��
    CA_PROMPT_E03,  // 0x03  E03 CAģ��ʧ��
    CA_PROMPT_E04,  // 0x04  E04 ��������ܿ�
    CA_PROMPT_E05,  // 0x05  E05 ϵͳ��ʶ��˿�
    CA_PROMPT_E06,  // 0x06  E06 ���ܿ�ʧ��
    CA_PROMPT_E07,  // 0x07  E07 ���ڼ�����ܿ�
    CA_PROMPT_E08,  // 0x08  E08 CAģ��ʧ��
    CA_PROMPT_E09,  // 0x09  E09 ���ܿ�EEPROMʧ��
    CA_PROMPT_E10,  // 0x0A  E10 PMT��ʽ����
    CA_PROMPT_E11,  // 0x0B  E11 ������ƥ��
    CA_PROMPT_E12,  // 0x0C  E12 ����ĸ��ͬ��
    CA_PROMPT_E13,  // 0x0D  E13 û����Ч�Ľ�Ŀ
    CA_PROMPT_E14,  // 0x0E  E14 ��Ŀû����Ȩ
    CA_PROMPT_E15,  // 0x0F  E15 ���յ���Ȩ
    CA_PROMPT_E16,  // 0x10  E16 ��ǰ��Ŀ�Ѽ���
    CA_PROMPT_E17,  // 0x11  E17 ��ǰ��Ŀ�Ѽ���
    CA_PROMPT_E18,  // 0x12  E18
    CA_PROMPT_E19,  // 0x13  E19
    CA_PROMPT_E20,  // 0x14  E20 ����Ӫ����Ȩ
    CA_PROMPT_E21,  // 0x15  E21
    CA_PROMPT_E22,  // 0x16  E22
    CA_PROMPT_E23,  // 0x17  E23 ��ǰ��Ŀ���ڽ���
    CA_PROMPT_E24,  // 0x18  E24 �ޱ�������Ȩ
    CA_PROMPT_E25,  // 0x19  E25 ���ܿ�������
    CA_PROMPT_E26,  // 0x1A  E26 ϵͳ����ʶ��ǰ��Ŀ
    CA_PROMPT_E27,  // 0x1B  E27 ��ǰ��Ŀ��������
    CA_PROMPT_E28,  // 0x1C  E28 �������ܿ�
    CA_PROMPT_E29,  // 0x1D  E29
    CA_PROMPT_E30,  // 0x1E  E30 ��ǰ��Ŀ��Ч
    CA_PROMPT_E31,  // 0x1F  E31 ��ĸ��������
    CA_PROMPT_E32,  // 0x20  E32 ���Ҵ���û����Ȩ
    CA_PROMPT_E33,  // 0x21  E33 û����Ȩ����
    CA_PROMPT_E34,  // 0x22  E34 ����Ȩ������
    CA_PROMPT_E35,  // 0x23  E35 û���ź�
    CA_PROMPT_E36,

    CA_NOTICE_SHOW = 37,    // ��ʾ��Ŀ���ܲ��ŵ���ʾ��Ϣ
	CA_NOTICE_ERASE,		// ������ʾ��Ϣ
	CA_OSD_ERASE,			// ����OSD��Ϣ
	CA_OSD_INFO,			// ��EMM,PEMM OSD��Ϣ֪ͨ
	CA_MAIL_INFO,			// ��EMM,PEMM Mail��Ϣ֪ͨ
	CA_EXECUTE_OP_INFO,	    // Ҫ�������ִ�о���Ļ����в���
	CA_SW_UPDATE_INFO,		// ��EMM,PEMM ���������Ϣ֪ͨ
	CA_TRANSPARENT_INFO,	// CA ͸���������е�˽����Ϣ
	CA_FINGER_SHOW,		    // Ҫ����ʾָ����Ϣ
	CA_FINGER_ERASE,		// Ҫ�����ָ����Ϣ
	CA_IPPV_INFO,			// IPPV ��Ϣ
	CA_IPPT_INFO,           // IPPT ��Ϣ
    CA_HIDE_IPP,            // ���� IPPͼ��
	CA_IPP_BUY,				//IPP���򵯳���
	CA_ANNO_INFO,			//������ʾ
	CA_ANNO_HIDE,           //�����ڲ�
	CA_PARENTALCTRL_HIDE,   //��ĸ���ڲ�
#endif

#if ((EMBED_CA & WFCA) == WFCA)
	WFCA_WFERR_COMMON_NO	= 0x00	    		,/* û�д��� */
	WFCA_WFERR_COMMON_PARAMETER 				,/* �����Ĳ����Ƿ� */
	WFCA_WFERR_COMMON_MEMALLOC				,/* ����洢��ʧ�� */
	WFCA_WFERR_COMMON_MEMFREE					,/* �ͷŴ洢��ʧ�� */
	WFCA_WFERR_COMMON_ILLEAGAL				,/* �Ƿ��Ĳ��� */
	WFCA_WFERR_COMMON_VERIFY					,/* У��ʧ�� */
	WFCA_WFERR_COMMON_MEMEXEC					,/* �ڴ��쳣 */

	WFCA_WFERR_SMART_SW1SW2  					, /* ִ������ʱ״̬�ֲ�����0x9000,��16λΪ״̬��SW1SW2 */
	WFCA_WFERR_SMART_RWSIZE					, /* ʵ����Ӧ�ֽ�����Ҫ����� */
	WFCA_WFERR_SMART_ABSENT					, /* û�в������ܿ� */
	WFCA_WFERR_SMART_INVALID					, /* �Ƿ������ܿ� */
	WFCA_WFERR_SMART_DRIVER					, /* ���ܿ����������������￪ʼ��ţ���С��WFERR_FILE_FORMAT */

	WFCA_WFERR_FILE_FORMAT					, /* �ļ���ʽ���� */
	WFCA_WFERR_FILE_CONFLICT					,/* �����ͻ */
	WFCA_WFERR_FILE_FULL						,/* �ļ����� */
	WFCA_WFERR_FILE_EMPTY						,/* �ļ��ѿ� */
	WFCA_WFERR_FILE_QUERY						,/* δ�ܲ�ѯ����¼ */
    WFCA_WFERR_FILE_ABNORMAL                    ,/*�ļ������쳣*/

	WFCA_WFERR_CAS_ABSENT						, /* CAS��δ��ʼ�� */
	WFCA_WFERR_CAS_PRESENT					,/* CAS�Ѿ���ʼ�� */
	WFCA_WFERR_CAS_INVALIDSTB					,/* �Ƿ��Ļ�����,���߻�����ƥ�� */
	WFCA_WFERR_CAS_UNLICENSED					,/* ��Ŀδ����Ȩ */
	WFCA_WFERR_CAS_OUTOFPERIOD				,/* ��Ŀ������Ȩ���ڼ��� */
	WFCA_WFERR_CAS_FORBIDDEN					,/* ��ֹ���� */
	WFCA_WFERR_CAS_COMMAND					,/* �Ƿ���ǰ������ */
	WFCA_WFERR_CAS_LENGTH						,/* ����Ĳ������Ȳ���ȷ */
	WFCA_WFERR_CAS_ADDRESS					,/* ǰ��Ѱַû��Ѱ������ */
	WFCA_WFERR_CAS_BALANCE					,/* ���� */
	WFCA_WFERR_CAS_UNMATCHED					,/* �ӻ���ĸ����ƥ�� */
	WFCA_WFERR_CAS_EXPIRATION					,/* ���ڵ��ӻ���Ȩ */
	WFCA_WFERR_CAS_ZONE						,/* ��������� */
	WFCA_WFERR_CAS_PROTOCOL					,/* CMTЭ�鲻��ȷ *///30

	WFCA_EMM_MESSAGE_DISPLAY ,		   		//ca Message����ȫ�ֱ���WFSTB_EMMMessage�У�������ʾ
    WFCA_EMAIL_NOTE			,
    WFCA_EMAIL_CLEAR			,
	WFCA_PPT_NOTE			,
   	WFCA_PPT_CLEAR			,
	WFCA_OSDMSG_NOTE			,
	WFCA_DBC_SUBMIT			,
	WFCA_SHOW_URGENCY_BROADCAST ,
	WFCA_ENTITLEMENT		,              //�ý�Ŀ����Ȩ�޻�ʣ%u��
    WFCA_AUTHNEARBOOT_REMIND,
    WFCA_HIDE_AUTH_REMAIN_DLG,

#endif

#if ((EMBED_CA & QZCA) == QZCA)
	CA_OK	= 0x00			,  /*0x00 ״̬��ȷ,ȡ����ʾ*/
	CA_NO_SW1SW2		,  /*û��״̬��*/
	CA_MEMORY_ERROR		,  /*���ܿ��ڴ����*/
	CA_WRONG_LC_LENGTH	,  /*APDU�����(lc)����*/
	CA_WRONG_DATA		,  /*���ݴ��� ͨ����CRC����*/
	CA_WRONG_PARA		,  /*APDU��������*/
	CA_WRONG_LE_LENGTH	,  /*APDU �����ֽڳ��ȣ�le������*/
	CA_INS_NOT_SUPPORT	,  /*APDU���֧��*/
	CA_CLA_NOT_SUPPORT	,  /*APDU �����벻֧��*/
	CA_GENERAL_ERROR	,  /*δ֪���ʹ���һ����ͨѶ����*/
	CA_EXPIRED			,  /*��Ȩ����*/

	CA_STB_NOT_MATCH	,  /*���������*/
	CA_CARD_NOT_INIT	,  /*���ܿ�δ��ʼ��*/
	CA_WRONG_SUPER_CASID,  /*�����SUPER_CAS_ID*/
	CA_WRONG_SC_ID		,  /*��������ܿ��ţ� ���˵����ݲ������ſ���*/
	CA_PPV_EXCEED		,  /*PPV����*/
	CA_NOT_PAIRED		,  /*���ܿ�û������Ϊ�������*/
	CA_ECM_NOT_AUTH		,  /*Ƶ��δ��Ȩ*/
	CA_LIMIT_AREA		,  /*�����޲�*/
	CA_LIMIT_CARD		,  /*���޲�*/
	CA_NOT_CHILD_MODE	,  /*���ܿ�û������Ϊ�ӿ�ģʽ*/
	CA_NO_CHILD_AUTH	,  /*û���ӿ���Ȩ*/
	CA_CHILD_NOT_AUTH	,  /*�ӿ�δ��Ȩ*/
	CA_CHILD_AUTH_TIMEOUT, /*�����ӿ���Ȩ��ʱ*/
	CA_CHILD_AUTH_EXPIRED, /*0x18�ӿ���Ȩ����*/

   	CA_ERR_CRC			,  /*CRC����*/
	CA_ERR_NOT_INT		,  /*δ��ʼ��*/
	CA_CARD_NO_FOUND	,  /*��������ܿ�*/
	CA_CARD_ERROR		,  /*��������ܿ�*/
	CA_CARD_ERR_COMM    ,  /*ͨѶ����*/
	CA_WRONG_DATA_PACK  ,  /*���ݰ�����*/
	CA_NOT_AUTH_OR_EXPIRED,/*��Ȩδ��ʼ���ѹ���*/

	CA_NEW_EMAIL		,
	CA_HIDE_EMAIL		,
	CA_FULL_EMAIL		,
	CA_SHORT_MSG		,  /*������*/

#endif

#if ((EMBED_CA & XGCA) == XGCA)
	
	/*����Ӧ�����*/	
	CA_XG_SUCCESS = 0x00	        , 	//�ɹ�
	CA_XG_INVALID_INSTRUCTION		, 	//�Ƿ�����
	CA_XG_WRONG_LENGTH				, 	//�򳤶ȴ���
	CA_XG_CARD_FORMAT1_FAIL			, 	//��Ƭδ����ʽ��
	CA_XG_CARD_FORMAT2_FAIL			, 	//��Ƭδ���Ӧ�ø�ʽ��
	CA_XG_WRONG_P1_P2				, 	//p1��p2��������
	CA_XG_INVALID_NOT_SUPPORT		, 	//���֧��
	CA_XG_NO_DATA					, 	//�����ݿ�ȡ
	/*Ӧ�����*/
	CA_XG_TABLE_FORMAT_NOT_SUPP		,	  //��֧�ֵİ���ʽ�汾	 0x08
	CA_XG_CA_NOT_SUPPORT			,	  //��֧�ֵ�CA�汾
	CA_XG_NET_NOT_SUPPORT			,	  //��֧�ֵ�����ϵͳ
	CA_XG_WRONG_FILTER				,	  //����Ĺ��˹���
	CA_XG_OPERATE_FAIL				,	  //����ʧ��
	CA_XG_START_SER_SUCCESS			,	  //�������ò����ɹ�
	CA_XG_STOP_SER_SUCCESS			,	  //���񶳽�����ɹ�
	CA_XG_NEED_MATCH				,	  //��Ҫ�������
	CA_XG_BALANCE_NOT_ENOUGH		,	  //Ǯ������
	CA_XG_CARD_EXPIRE				,	  //�ӿ�������
	CA_XG_NIT_ZONE_FAIL				,	  //NIT��������֤ʧ��
	CA_XG_NEED_CORRECT_NIT			,	  //��δͨ��������֤����Ҫ��ȷ��NIT
	CA_XG_SER_STOPED				,	  //���񱻶���//20
	CA_XG_CARD_DELETED				,	  //����ɾ��
	CA_XG_FILE_SYS_WRONG			,	  //�ļ�ϵͳ����
	CA_XG_LEVEL_LIMITED				,	  //�����տ��Ľ�Ŀ����
	CA_XG_DECRYPT_FAIL				,	  //���ܴ���
	CA_XG_NO_AUTHORIZATION			,	  //����Ȩ
	CA_XG_TABLE_FORMAT_WRONG		,	  //����İ���ʽ
	CA_XG_PAY_IPP_FAIL				,	  //����IPPVʧ��
	CA_XG_NO_VALID_INFO				,	  //�޿��õ���Ϣ
	CA_XG_CARD_INIT_FAIL			,	  //��Ƭδ���Ӧ�ó�ʼ��
	CA_XG_INVALID_CAID				,	  //δ֪��CAID //30
	CA_XG_CARD_NOT_INIT				,	  //��Ƭδ��ɳ�ʼ��
	CA_XG_CARD_NOT_MATCH_STB		,	  //��δ���κ�STB���	
	CA_XG_CARD_ALREADY_MATCH		,	  //���Ѿ���ĳһSTB���	
	CA_XG_BOUND_FAIL				,	  //������ʧ��
	CA_XG_VERIFY_FAIL				,	  //�������У��ʧ��
	CA_XG_BOUND_UNEXPECTED_WRONG	,	  //�󶨳ɹ��������ؿ�Ƭ����������������
	CA_XG_VERIFY_UNEXPECTED_WRONG	,	  //У��ɹ��������ؿ�Ƭ����������������
	CA_XG_CARD_NOT_REGISTER			,	  //��δע��
 	CA_XG_PLEASE_INSERT_CARD		,	  //��忨	
	CA_XG_PPC						,	  //��Ȩ������,�뼰ʱ����//40
	CA_XG_CARD_INI_SUCCESS			,     //����ʼ���ɹ�
	CA_XG_CARD_INI_FAIL				,	  //����ʼ��ʧ��
	CA_XG_MATCH_STB_SUCCESS			,	  //������Գɹ�
	CA_XG_MATCH_STB_ALREADY			,	  //�����Ѿ����
	CA_XG_NIT_MODIFYING				,	  //���ڽ���������֤�����Եȡ�����
	CA_XG_UNKNOWN_ERROR				,	  //δ֪����
	CA_XG_FORCE_SHUTDOWN            ,     //ǿ�ƹض�
    CA_XG_FEED_MACHINE             ,     //�ӻ���Ȩ�������ڣ��뵽ĸ����ȡ��Ȩ��
    CA_XG_FEED_MACHINE_SUCCESS      ,     //ι���ɹ�
    CA_XG_FEED_MACHINE_FAIL         ,       //ι��ʧ��//50
    CA_XG_CASYS_NOT_INIT             ,       //CAϵͳδ��ʼ��
    CA_XG_CASYS_UNKNOWN             ,       //�޷�ʶ���CAϵͳ
    CA_XG_DECRYPT_ERROR             ,       //����У��ʧ��


	/*��ʾ���ʼ���ָ�ơ�OSD*/
	CA_XG_PLEASE_CONFIRM			,	  //�밴��ȷ�ϡ���ʼ�����ĸ��	
	CA_XG_PLEASE_INSERT_MAINCARD	,	  //�����ĸ����������ȷ�ϡ���ȡι������
	CA_XG_GET_FEED_FAIL				,	  //��Ϊ�ӿ����޷���ȡι�����ݣ������ĸ����������ȷ�ϡ�
	CA_XG_UNKNOWN_TIME				,	  //δ֪�ĵ�ǰʱ�䣬����Ҫ�Ȼ�ȡECM����
	CA_XG_UNKNOWN_CAID				,	  //δ֪��CA-ID
	CA_XG_PLEASE_INSERT_SUBCARD		,	  //��ĸ�����ݳɹ���������ӿ�������ȷ�ϡ�
	CA_XG_NO_SUBCARD				,	  //�������޿���������ӿ���������ȷ�ϡ�
	CA_XG_DONOT_NEED_FEED			,	  //��Ϊĸ��������Ҫι�����ݣ�������ӿ�������ȷ�ϡ�
	CA_XG_WRONG_FEED_DATA			,	  //�����ι������						
	CA_XG_FEED_SUCCESS				,	  //ι���ɹ�
	CA_XG_NEED_FEED_CARD			,	  //�ӿ����ڣ���Ҫι���������ĸ����ȡι������	 
	CA_XG_NEW_EMAIL					,
	CA_XG_HIDE_EMAIL				,     //
	CA_XG_FULL_EMAIL				,     
	CA_XG_FINGER					,
	CA_XG_FINGER_HIDE               ,
	CA_XG_SHORT_MSG					, 	  //������
	CA_XG_SHOW_IPPV					,
	CA_XG_HIDE_IPPV					,
	CA_XG_PPV_NOTE					,	 


#endif

#if ((EMBED_CA & DIVICA) == DIVICA)
	CA_DIVI_PROMT_CLEAR = 0x00, 	//0x00 ������ʾ����
	CA_DIVI_NO_ENTITLE , 	        //0x01 ��Ŀδ��Ȩ
	CA_DIVI_BLACKOUT   , 			//0x02 �����޲�
	CA_DIVI_INITIAL_CARD, 		    //0x03 ��ʼ����װ��������ʹ��
	CA_DIVI_WAIT_CARD  , 			//0x04 ���ڰ�װ�����ȴ�����
	CA_DIVI_OUTOF_SERVICE,  		//0x05 Ƿ��ͣ��
	CA_DIVI_PAIR_SERVICE,   		//0x06 ά��ͣ��
	CA_DIVI_APPLY_SERVICE,  		//0x07 ���뱨ͣͣ��
	CA_DIVI_LOGOUT		,   		//0x08 ע��״̬
	CA_DIVI_NOT_IN_WORKTIME,	    //0x09���ڹ���
	CA_DIVI_RATE_TOO_LOW,   		//0x0a �������
	CA_DIVI_MONEY_NOT_ENOUGH,	    //0x0b ���ڽ��?
	CA_DIVI_TEMP_LIVE,			    //0x0c �ӿ�����
	CA_DIVI_TIMEOUT,				//0x0d �ӿ�����
	CA_DIVI_NOT_PAIRED,			    //0x0e �������
	CA_DIVI_INVALID_CARD,		    //0x0f ��Ч��
	CA_DIVI_INSERT_CARD,			//0X10 ��忨
	CA_DIVI_UNKNOW_ERR,			    //0X11 δ֪����
    CA_DIVI_ENTITLE_EXPIRERDAYS,    //0X12 ��������
#endif
																													
#if ((EMBED_CA & DSCA) == DSCA)
	DSCA_CANCEL_TYPE		= 0x00,           
	DSCA_BADCARD_TYPE		= 0x01,		/*�޷�ʶ�𿨣�����ʹ��*/
	DSCA_EXPICARD_TYPE		= 0x02,		/*���ܿ��Ѿ����ڣ�������¿�*/
	DSCA_CARD_INIT_TYPE		= 0x03,		/*���ܿ����ڳ�ʼ��*/
	DSCA_INSERTCARD_TYPE	= 0x04,		/*���ܽ�Ŀ����������ܿ�*/
	DSCA_CARD_INIT_ERR_TYPE	= 0x05,		/*���ܿ���ʼ��ʧ��*/
	DSCA_STB_NO_CARD_TYPE	= 0x06,		/*�������в��������ܿ�*/

	DSCA_NOOPER_TYPE		= 0x10,		/*���в����ڽ�Ŀ��Ӫ��*/
	DSCA_CARDSTOP_TYPE		= 0x11,		/*���ܿ���ͣ��*/
	DSCA_OUTWORKTIME_TYPE	= 0x12,		/*���ڹ���ʱ����*/
	DSCA_WATCHLEVEL_TYPE	= 0x13,		/*��Ŀ��������趨�ۿ�����*/
	DSCA_PAIRING_TYPE		= 0x14,		/*����û�ж�Ӧ*/

	DSCA_NOENTITLE_TYPE		= 0x20,		/*��û�й���ý�Ŀ*/
	DSCA_DECRYPTFAIL_TYPE	= 0x21,		/*��Ŀ����ʧ��*/
	DSCA_NOMONEY_TYPE		= 0x22,		/*���ڽ���*/
	DSCA_ERRREGION_TYPE		= 0x23,		/*������ȷ*/
	//DSCA_FINGER_SHOW		= 0x24,		/*ָ����ʾ*/

	//DSCA_FINGER_DISAPPEAR	= 0x30,		/*ָ������*/
	DSCA_CARDNOTACTIVE_TYPE	= 0x31,		/*���ܿ�δ����*/
	DSCA_CARDLOGOUT_TYPE	= 0x32,		/*���ܿ���ע��*/
	DSCA_CONDITION_CTL_TYPE	= 0x33,		/*�ò�Ʒ���޲�*/
	DSCA_DESCRA_NOENTITLE_TYPE	= 0x34,	/*��Ȩ�ѵ��ڣ�����ϵ��Ӫ��*/
	DSCA_ENTITLE_UPDATE_TYPE    = 0x35,	/*��Ȩ�����У����Եȣ�*/
	DSCA_CARD_UNWONTED_TYPE		= 0x36,	/*���ܿ��ڲ��쳣*/
	DSCA_CHANGEPRO_TOO_FAST_TYPE= 0x37,	/*�벻ҪƵ����̨*/
#if (defined(DSCA_56) || defined(DSCA_COS) || defined(DSCA_56_OVERSEAS))
	DSCA_SYSTEM_DATA_ERR_TYPE   = 0x38,	/*ϵͳ�쳣���޷�����*/
#else
	DSCA_STB_NEED_UPDATE_TYPE   = 0x38,	/*��������Ҫ���������Ե�*/
#endif
	DSCA_CARD_IN_BLACKLIST_TYPE = 0x39,	/*���Ŀ��ѱ������������*/
#if defined(DSCA_56_OVERSEAS)	
	DSCA_STB_NEED_UPDATE_TYPE   = 0x3A,	/*��������Ҫ���������Ե�*/
#endif	
   	DSCA_ZBCardPAIRING_OK	= 0x40,		/* ��ĸ����Գɹ� */
   	DSCA_ZBCardPAIRING_Err	= 0x41,		/* ��ĸ�����ʧ��,�����²�����ȷ��ĸ�� */
   	DSCA_ZCardPAIRING_REQ	= 0x42,		/* �ӿ������º�ĸ����� */
	DSCA_CARD_MATCH_OK		= 0x43,		/*������Գɹ�*/
	DSCA_REMATCH_TYPE		= 0x44,		/*���»������*/
	DSCA_CANCEL_MATCH_TYPE	= 0x45,		/*ȡ���������*/

	DSCA_SHOWNEWEMAIL		= 0x50,		/* ��ʾ���ʼ�ͼ�� */  
	DSCA_SHOWOVEREMAIL		= 0x51,		/* ��ʾ�ʼ����� */
	DSCA_HIDENEWEMAIL		= 0x52,		/* �������ʼ�ͼ��*/
	DSCA_EXIGENT_PROGRAM	= 0x53,		/*�����㲥*/
	DSCA_STOP_EXIGENT_PROGRAM	= 0x54,	/*���ؽ����㲥����*/
	DSCA_CARD_UNLOCK_OK			= 0x55,	/*���ܿ���������ɹ�*/
	DSCA_CARD_PURSER_UPDATE_OK	= 0x56,	/*����Ǯ������*/
	DSCA_NET_ERR_LOCK_TYPE		= 0x57,	/*�����쳣����������*/
	DSCA_SYSTEM_ERR_LOCK_TYPE	= 0x58,	/*ϵͳ�쳣����������*/
	DSCA_NET_ERR_UNLOCK_TYPE	= 0x59,	/*�����쳣����*/
	DSCA_SYSTEM_ERR_UNLOCK_TYPE	= 0x60,	/*ϵͳ�쳣����*/

	/*���ܿ�����.��ʾ�����������ȣ���ʧ�ܴ�����*/
	DSCA_CARD_UPDATE_BEGIN_TYPE		= 0x65,		/*���ܿ���ʼ���£���ʾ������,��ʱ����Ϊ0*/
	DSCA_CARD_UPDATE_PROGRESS_TYPE	= 0x66,		/*���½���*/
	DSCA_CARD_UPDATE_ERR_TYPE		= 0x67,		/*���³����������*/
	DSCA_CARD_UPDATE_END_TYPE		= 0x68,		/*���³ɹ�����������ʧ*/
	DSCA_CARD_NEED_UPDATE_TYPE		= 0x69,		/*���ܿ���Ҫ���£����Ժ�*/


	/*��ʾ�Ի���*/
	DSCA_CARDISDUE_TYPE		= 0x70,		/*���ܿ�����Ƿ�Ѵ߽�(����ȷ������ť�ĶԻ���)*/
	DSCA_IPPVBUY			= 0x71,		/*Ippv������ʾ�� */
	DSCA_IPPV_OUT_TIME		= 0x72,		/*Ippv��Ŀ����*/
	DSCA_HIDE_IPPVBUY		= 0x73,		/*���� Ippv������ʾ�� */
	DSCA_ReqPAIRING_TYPE	= 0x74,		/*�����Ŀ�����������*/
#endif
																						
#if ((EMBED_CA & DVNCA) == DVNCA)
/* Ϊ��ʹDVNCA_SHOW_PAIR�Ժ�ö�����͵�ֵ�����п����޿����������ͬ
    �޿����п���PROMPT��ʾ��Ϣ��������Ҫ��ͬ��
*/
	DVNCA_PROMPT_CLEAR = 0x00,    //0x00 �ر�������ʾ(������ʾ)
#if (!defined(DVNCA_COS))	
	DVNCA_PROMPT_SCNOTPAIR,       //0x01 ����δ���
	DVNCA_PROMPT_NGTTOKEN,        //0x02 ����ȷ
	DVNCA_PROMPT_NOTENGHTOKEN,    //0x03 Ǯ������
	DVNCA_PROMPT_PAIRFAIL,        //0x04 ���δ���
	DVNCA_PROMPT_INSERT_CARD,     //0x05 ��������ܿ�
	DVNCA_PROMPT_ANOTMACH,        //0x06 ����ƥ��
	DVNCA_PROMPT_ECMBACKOUT,      //0x07 ��������
	DVNCA_PROMPT_SUBEXP,          //0x08 ��Ŀ�ѹ���
	DVNCA_PROMPT_SUBMOVED,        //0x09 ��Ŀδ��Ȩ
	DVNCA_PROMPT_STBLOCK,         //0x0A �����б�����
	DVNCA_PROMPT_SUBNOTSTART,     //0x0B ��Ȩδ��ʼ
	DVNCA_PROMPT_SCEXP,           //0x0C ���ܿ�����
	DVNCA_PROMPT_ECMDATAERR,      //0x0D ECM���ݴ���
	DVNCA_PROMPT_SECURITYERR,     //0x0E ��ȫͨ������
	DVNCA_PROMPT_LOWRATING,       //0x0F �ۿ����𲻹�
	DVNCA_PROMPT_CHECKSUMERR,     //0x10 ��ĿУ�����
	DVNCA_PROMPT_ECMERR,          //0x11 ECM ���ܴ���
	DVNCA_PROMPT_NOTIDENTIFYSC,   //0x12 ����ʶ�����ܿ�
	DVNCA_PROMPT_LIB_EXPIRED,     //0x13 CAK lib����  
	DVNCA_PROMPT_SCCOM_ERR,       //0x14 ����ͨѶ����̫��
	DVNCA_PROMPT_UNSUPPORT_ECM,   //0x15 ��֧��ECMЭ��汾
    DVNCA_PROMPT_NOT_INWORKTIME,   //0x16 ���ڹ���ʱ����
#else //�޿�CA
    DVNCA_KP_PROMPT_NO_MATCH,       //0x01      //0x1 CA ��汾��ǰ�˲�ƥ��
    DVNCA_KP_PROMPT_NO_ACTIVE,      //0x02     //0x2 CA δ����, ������Ӫ����ϵ
    DVNCA_KP_PROMPT_AREA_NOT_MATCH, //0x03     //0x3  �����벻ƥ��
    DVNCA_KP_PROMPT_ERROR_PRODUCT,  //0x04     //0x7 ��ƷID ����, ��������û�иò�Ʒ
    DVNCA_KP_PROMPT_ERROR_PROVIDER, //0x05     //0x8  ��Ӫ��ID ����, ��������û�и���Ӫ��
    DVNCA_KP_PROMPT_NO_ENTITLE,     //0x06     //0x9 ��Ŀû����Ȩ
    DVNCA_KP_PROMPT_ENTITLE_EXPIRED,//0x07     //0xa ��Ŀ��Ȩ�ѹ���
    DVNCA_KP_PROMPT_ENTITLE_NOSTART,//0x08     //0xb  ��Ŀ��Ȩδ��ʼ
    DVNCA_KP_PROMPT_PRODUCT_CLASH,  //0x09     //0xc  ��ƷID ��ͻ
    DVNCA_KP_PROMPT_SERVICE_FORCE,  //0x0A     //0xd  ��������
    DVNCA_KP_PROMPT_OUT_RATING,     //0x0B     //0x11 �ۿ��ȼ�����
    DVNCA_KP_PROMPT_OUT_WORKTIME,   //0x0C     //0x12  ���ڹ���ʱ����
    DVNCA_KP_PROMPT_RESET_PIN,      //0x0D     //0x13  PIN ������
    DVNCA_KP_PROMPT_GROUP_FORCE,    //0x0E     //0x14 �������
    DVNCA_KP_PROMPT_EMERGENCY,      //0x0F     // 0x15  �����¼�
    DVNCA_KP_PROMPT_PRODUCT_UPDATE, //0x10     //0x1A  ��Ʒ��Ϣ�Ѹ���
    DVNCA_KP_PROMPT_FREEZE,         //0x11     //0x20  CA �ѹ���
    DVNCA_KP_PROMPT_RESERVED1,      //0x12     
    DVNCA_KP_PROMPT_RESERVED2,      //0x13     
    DVNCA_KP_PROMPT_RESERVED3,      //0x14   
    DVNCA_KP_PROMPT_RESERVED4,      //0x15     
    DVNCA_KP_PROMPT_RESERVED5,      //0x16     
#endif

    DVNCA_SHOW_PAIR,              //0x17��ʾ�������
    DVNCA_HIDE_PAIR,              //0x18�ڲػ������
    DVNCA_SHOW_OSD,               //0x19��ʾ����OSD
    DVNCA_HIDE_OSD,               //0x1A�ڲع���OSD
    DVNCA_SHOW_URGENCY_ICON,      //0x1B��ʾ"�����¼�"ͼ��
    DVNCA_HIDE_URGENCY_ICON,      //0x1C����"�����¼�"ͼ��
#endif

#if ((EMBED_CA & GOSCA) == GOSCA)
	CA_PROMPT_CLEAR = 0x00,					//0x00����
	CA_PROMPT_SMART_STOP,					//0x01���ܿ�������
	CA_PROMPT_SMART_AREA_NOPAIR, 			//0x02���ܿ�����ƥ��
	CA_PROMPT_SMART_IPPT_SWITCH,            //0x03��    /*��ʱû��*/	
	CA_PROMPT_SMART_STB_NOPAIR,			 	//0x04���������
	CA_PROMPT_SMART_PROG_NOENTITLE,		 	//0x05��Ŀδ��Ȩ
	CA_PROMPT_SMART_PROG_NOENTITLE_IPPT,    //0x06�� /*��ʱû��*/
	CA_PROMPT_SMART_MOTHER_SON_PAIR,		//0x07��ĸ�����������
	CA_PROMPT_SMART_MOTHER_SON_TIMEOUT, 	//0x08��ĸ����Գ�ʱ
	CA_PROMPT_SMART_PAIR_OK,            	//0x09�� /*��ʱû��*/
	CA_PROMPT_SMART_AREA_LOCK,				//0x0a���ܿ���������
	CA_PROMPT_SMART_CARD_LOCK, 				//0x0b���ܿ�������
	CA_PROMPT_SMART_LIMIT_WATCH, 			//0x0c�������տ�
	CA_PROMPT_SMART_NO_WORK_TIME, 			//0x0d�����ڹ���ʱ��

    /*0x0e~0x12��V2.08����*/
	CA_PROMPT_SMART_AREA_CONTROL_ERROR,     //0x0e��û�й�������ȷ�ķ�����
	CA_PROMPT_BIND_INFO_ERROR,              //0x0f�����󶨴���+����ID
	CA_PROMPT_SMART_IDRUN_ERROR,            //0x10��������������Ч����
	CA_PROMPT_SMART_LEVEL_ERROR,	        //0x11���Ĺۿ�������ڽ�Ŀ����
	CA_PROMPT_PVR_ENTITLE_TIMEOUT,          //0x12PVR ��Ȩ�ļ�����
    
	CA_PROMPT_SMART_OUT,				    //0x13��Ŀ���ţ���忨

    /*0x14~0x17��V2.08����*/
	CA_PROMPT_SMART_INVALID,                //0x14�����뿨�Ǹ�˹����CA��
	CA_PROMPT_SMART_STB_NOBIND,             //0x15����δ��ʱ��ʾ
	CA_PROMPT_CASID_BIND_ERROR,             //0x16��������Ӫ��ID����Ӫ��ID�󶨴���
    CA_PROMPT_CASID_SOL_ERROR,              //0x17 ��������SOL��Ϣ���մ���

	CA_PROMPT_SMART_UNKNOWN_ERROR, 			//0x18δ֪����

	CA_PROMPT_SMART_LAST_DAY, 				//0x19���ֹ����ʣ������
	CA_PROMPT_SMART_IPPT, 					//0x1A��

	CA_SHOW_FINGER_PRINTING = 31, 			//0x1F
	CA_HIDE_FINGER_PRINTING = 32,  			//0x20
	GOSCA_SHOW_OSD_MESSAGE = 33,
	CA_SHOW_URGENCY_BROADCAST = 34,			//���ڽ����㲥
	CA_HIDE_URGENCY_BROADCAST = 35,
	GOSCA_SHOW_INQUIRE_IPP = 36,
	GOSCA_NEW_EMAIL_NOTE = 37,
	GOSCA_HIDE_EMAIL_NOTE = 38,						
	GOSCA_EMAIL_FULL_NOTE = 39,
	GOSCA_HIDE_SMART_LAST_DAY,             //����ʣ����Ȩ������ʾ������
#endif						   
#if ((EMBED_CA & ABVCA) == ABVCA)
	//����ʹ�ã���ǿ���û���
   ABVCA_PROMPT_CLEAR = 0x00,			//��ȷ   0
   ABVCA_STB_GET_ENTITLE,         	//���ܿ��������Ȩ
   ABVCA_UPDATE_ECM_EMM,			//����֪ͨ�û��յ��µ�ECM��EMM����
/*���Ŀ����ص���Ҫ��ʾ��Ϣ*/
   ABVCA_STB_SC_NO_PAIRED,     		/*������ƥ��*/
   ABVCA_SC_ERROR,			/* ��������ܿ�*/
   ABVCA_NO_SC,                		/*��������ܿ�  5*/
   ABVCA_CARD_IN_BEGIN,			/* ����ʼ��ʼ��*/
   ABVCA_CARD_IN_END_SUCCESS,		/* ����ʼ���ɹ�*/
   ABVCA_CARD_IN_END_FAIL,		/* ����ʼ��ʧ��*/
   ABVCA_READ_WRITER_ERR,			/*������ʧ��*/
   ABVCA_SC_PIN_RESET,			/*�������óɹ�   10*/
   ABVCA_STB_SC_PAIRED,			/*������Գɹ�*/
   ABVCA_STB_SC_FREE_PAIRED,		/*���������Գɹ�*/
   ABVCA_STB_SC_PAIRED_FAILED,		/*�������ʧ��*/
  // ABVCA_STB_MODIFY_WATCH_TIME_SUC,	/*�޸Ĺۿ�ʱ��ɹ�*/
   //ABVCA_STB_MODIFY_WATCH_TIME_FAILED,	/*�޸Ĺۿ�ʱ��ʧ��  15*/
   ABVCA_NOT_IN_WATCH_TIME,		/*�������õĽ�Ŀ�ۿ�ʱ��֮��*/
/*���Ŀ�����Ҫ��ʾ����Ϣ   */
   ABVCA_OUT_OF_DATE,			/*���ܿ�����*/
   ABVCA_NO_ENTITLE,           		/*û����Ȩ*/
   ABVCA_IPPV_PRO_NO_ENOUGH_TOKEN,	/*IPPV��Ŀ,����*/   
   ABVCA_STB_AREA_RESTRECT,		/*��������*/
   ABVCA_CA_NO_PAIRED,			/*��Ҫ�������   30*/
   ABVCA_ECM_UNKNOWEN_ERROR,		/*����Ľ�Ŀ��Ϣ*/
   
   ABVCA_WAIT_ENTITLE,				 /*�ȴ�������Ȩ*/
   ABVCA_STBID_NULL,			/*STBID Ϊ�գ���Ҫ����дstbid*/
   ABVCA_ALREADY_PAIRED,		/*���Ѱ󶨣���������Ч*/
   ABVCA_CHIP_NOT_MATCH,		/*flash ��оƬ��ƥ��*/
   ABVCA_NOT_CONTACT_MASTER,	/*û��ĸ��*/
   ABVCA_CLEAR_IPPV_SHOW,
   ABVCA_CHANNEL_EMM_FP,
   ABVCA_STB_EXTEND,
   ABVCA_FORBID_PVR,
   
   ABVCA_MAIL_FULL,			/*�ʼ�����*/
   ABVCA_GET_MAIL,			/*��������δ���ʼ�*/
   ABVCA_GET_SUB ,			/*���µ�����*/
   ABVCA_GET_OTA,				/*���µ�OTA��Ϣ*/ 
   ABVCA_EMM_FINGERPRINT,			/*User Fingerprint   20*/
   ABVCA_MATURE_PRO,           		/*���˼���Ŀ*/
   ABVCA_IPPV_PRO,           		/*IPPV��Ŀ    25*/  
   ABVCA_STB_FINGERPRINT,			/* ��ʾfingerprint*/
   ABVCA_STB_CLEAR_FINGERPRINT,		/*����fingerprint����ʾ*/
   ABVCA_CLEAR_EMM_FP,				/*����������ʾ��EMM ָ��*/
   ABVCA_CLEAR_CHANNEL_EMM_FP,		/*����������ʾ�Ķ�Channel ��EMM ָ��*/
   									/*�յ�����Ϣ������EMMָ�ƣ�STB���ٶ�ʱ��ʾEMMָ��*/
#endif	
#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
    UNITENDCA_PROMPT_INFO_00 = 0x00,    //�Ǽ��Ž�Ŀ
    UNITENDCA_PROMPT_INFO_01,           //uti��ȫоƬ����
    UNITENDCA_PROMPT_INFO_02,           //uti��ȫоƬ��Ч
    UNITENDCA_PROMPT_INFO_03,           //�ն�û�д���Ӫ��
    UNITENDCA_PROMPT_INFO_04,           //nvram����
    UNITENDCA_PROMPT_INFO_05,           //û���ź�
    UNITENDCA_PROMPT_INFO_06,           //��Ŀ�쳣������ϵ��Ӫ��
    UNITENDCA_PROMPT_INFO_07,           //��Ŀû����Ȩ
    UNITENDCA_PROMPT_INFO_08,           //��Ŀ���ųɹ�
    UNITENDCA_PROMPT_INFO_09,           //��Ŀ�������Ʋ���
    UNITENDCA_PROMPT_INFO_10,           //��Ŀ���˼�������
    UNITENDCA_PROMPT_INFO_11,           //ָ����ʾ
    UNITENDCA_PROMPT_INFO_12,           //������������
    UNITENDCA_PROMPT_INFO_13,           //��ĿԤ��
    UNITENDCA_PROMPT_INFO_14,           //��Ʒ�Ѿ�����
    UNITENDCA_PROMPT_INFO_15,           //��Ȩ��¼�ﵽ�����
    UNITENDCA_PROMPT_INFO_16,           //δ����
    UNITENDCA_PROMPT_INFO_17,           //��������
    UNITENDCA_PROMPT_INFO_18,           //����������
    UNITENDCA_PROMPT_INFO_19,           //���ӷ�����ʧ��
    UNITENDCA_PROMPT_INFO_20,           //����Ŀ��drm����
    UNITENDCA_PROMPT_INFO_21,           //uti��ȫоƬ����
    UNITENDCA_PROMPT_INFO_22,           //uti��ȫоƬ�������
    UNITENDCA_PROMPT_INFO_23,           //��Ҫ�ʼ���ʾ
    UNITENDCA_PROMPT_INFO_24,           //��Ҫ�ʼ��ڲ�
    UNITENDCA_PROMPT_INFO_10_HIDE,      //���˼��������ڲ�
#endif

#if ((EMBED_CA & THTFCA) == THTFCA)
    THTFCA_CLEAR_SCREEN =  0x00,         // ������
    THTFCA_UNSUPPORTED_FRONTEND,         // �Ǳ�ϵͳ���ܣ��޷��տ���
    THTFCA_GCA_BLOCKED,                  // �����������޷��տ��˽�Ŀ��
    THTFCA_BLACKLISTED,                  // ���������˺��������޷��տ��˽�Ŀ��
    THTFCA_USER_FROZEN,                  // ���û���ǰ�˽���
    THTFCA_USER_UNFROZEN,                // ���û���ǰ�˽ⶳ
    THTFCA_NOT_IN_WORKING_PERIOD,        // ϵͳ���ڹ���ʱ����
    THTFCA_NO_SUCH_ENTITLEMENT,          // û����Ȩ���޷��տ��˽�Ŀ��
    THTFCA_EMERGENCY_BROADCASTING,       //Ӧ���㲥
    THTFCA_ENTITLEMENT_OVERDUE,          // �û���Ȩ�ѹ���
    THTFCA_INACTIVE,                     // ϵͳ��δ����
    THTFCA_ACTIVE_ERROR,                 // �������
    THTFCA_RECOVER_PIN,                  // PIN���ѻָ�ΪĬ��ֵ000000
    THTFCA_ATTRIBUTE_BLOCKING,           // �û��⵽���Զ������ԡ�����
#endif

#if ((EMBED_CA & LXDTCA) == LXDTCA)
    LXDTCA_MESSAGE_CANCEL_TYPE = 0x00,  /*���CAMESSAGE��ʾ*/
    LXDTCA_MESSAGE_BADCARD_TYPE,	    /*�޷�ʶ��*/
    LXDTCA_MESSAGE_EXPICARD_TYPE,		/*���ܿ��Ѿ����ڣ�������¿�*/
    LXDTCA_MESSAGE_INSERTCARD_TYPE,     /*���Ž�Ŀ����������ܿ�*/
    LXDTCA_MESSAGE_NOOPER_TYPE,			/*���в����ڽ�Ŀ��Ӫ��*/
    LXDTCA_MESSAGE_BLACKOUT_TYPE,		/*��������*/
    LXDTCA_MESSAGE_WATCHLEVEL_TYPE,		/*��Ŀ��������趨�ۿ�����*/
    LXDTCA_MESSAGE_PAIRING_TYPE,		/*��ĿҪ�������Ӧ*/
    LXDTCA_MESSAGE_NOENTITLE_TYPE,		/*û����Ȩ*/
    LXDTCA_MESSAGE_NOMONEY_TYPE,		/*���ڽ���*/
    LXDTCA_MESSAGE_ERRREGION_TYPE,      /*������ȷ*/
    LXDTCA_MESSAGE_STOP_SERVICE,		/*�û���ͣ��*/
    LXDTCA_MESSAGE_STB_CARD_NOMARCH,	/*������ƥ��*/
    LXDTCA_MESSAGE_INSERT_PARENTCARD,   /*�����ĸ����֤*/
    LXDTCA_MSSAGE_CARDINIT_FAIL,		/*����ʼ��ʧ��*/
    LXDTCA_MSSAGE_CHILDCARD_AUTHE_FAIL,	/*�ӿ���֤ʧ��*/
    LXDTCA_MSSAGE_CHILDCARD_AUTHE_SUCCE,/*�ӿ���֤�ɹ�*/
    LXDTCA_MSSAGE_CHILDCARD_INSERT,		/*�������֤�ӿ�*/
    LXDTCA_MSSAGE_CHILDCARD_CANCELOK,	/*�ӿ�ȡ���ɹ�*/
    LXDTCA_MSSAGE_CHILDCARD_SETUPOK,	/*�ӿ����óɹ�*/
    LXDTCA_MSSAGE_PARENT_CONFIRM_FAIL,	/*ĸ��ȷ��ʧ��*/
    LXDTCA_MSSAGE_PARENT_CONFIRM_SUCCE,	/*ĸ��ȷ�ϳɹ�*/
#endif

#if ((EMBED_CA & YJCA) == YJCA)
    YJCA_CANCEL_TYPE = 0x00,					/*ȡ����ǰ����ʾ  0*/
    YJCA_BADCARD_TYPE,			 		        /*�޷�ʶ�𿨣�����ʹ��*/
	YJCA_EXPICARD_TYPE,			 		        /*���ܿ��Ѿ����ڣ�������¿�*/
    YJCA_INSERTCARD_TYPE,			 		    /*��������ܿ�*/
    YJCA_STOP_SERVICE,				 		    /*�û���ͣ��*/
    YJCA_CONDITIONSTOP_TYPE,		    		/*��������          5*/
    YJCA_PAIRING_TYPE,				 		    /*������ƥ��*/
    YJCA_NOENTITLE_TYPE,			 		    /*����Ч��Ȩ*/
    YJCA_DECRYPTFAIL_TYPE,			 		    /*��Ŀ����ʧ��*/
    YJCA_ERRREGION_TYPE,          		 	    /*���������ʹ�û�����*/
    YJCA_INSERTMAIN_CARD,					    /*�����ĸ����֤  10*/
    YJCA_CARDINIT_SUCCE,			 		    /*����ʼ���ɹ�*/
    YJCA_CARDINIT_FAIL,				 		    /*����ʼ��ʧ��*/
    YJCA_CARD_AUTHENTICAT_FAIL,	 		        /*�ֿ���֤ʧ��*/
    YJCA_CARD_AUTHENTICAT_SUCCE, 	     		/*�ӿ���֤�ɹ�*/
    YJCA_CARD_SUB_INSERT,			    		/*�������֤�ӿ�    15*/
    YJCA_CARD_SUB_CANCEL,			    		/*�ӿ�ȡ���ɹ�*/
    YJCA_CARD_SUB_SETUP,			    		/*�ӿ����óɹ�*/
    YJCA_CARD_MAIN_CONFIR_FAIL,	    		    /*ĸ��ȷ��ʧ��*/
    YJCA_CARD_MAIN_CONFIR_SUCCE,	    		/*ĸ��ȷ�ϳɹ�*/
    YJCA_NOT_YJCA,				    		    /*��Ӣ��CA�����ܽ��ܽ�Ŀ  20*/
    YJCA_CARD_ERROR,				    		/*����������������Ͳ����*/ 
    YJCA_STRING,
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    SCCA_MESSAGE_CANCEL_TYPE = 0x00,                /*���*/
    SCCA_MESSAGE_BADCARD_TYPE,						/*�޷�ʶ�𿨣�����ʹ��*/
    SCCA_MESSAGE_EXPICARD_TYPE,						/*���ܿ��Ѿ����ڣ�������¿�*/
    SCCA_MESSAGE_CARD_INIT_TYPE,						/*���ܿ����ڳ�ʼ��*/
    SCCA_MESSAGE_INSERTCARD_TYPE,					/*���ܽ�Ŀ����������ܿ�*/
    SCCA_MESSAGE_CARD_INIT_ERR_TYPE,					/*���ܿ���ʼ��ʧ��*/
    SCCA_MESSAGE_STB_NO_CARD_TYPE,				/*�������в��������ܿ�*/
    SCCA_MESSAGE_CARD_INIT_OK_TYPE,				/*���ܿ���ʼ�����*/
    SCCA_MESSAGE_NOOPER_TYPE,						/*���в����ڽ�Ŀ��Ӫ��*/
    SCCA_MESSAGE_CARDSTOP_TYPE,						/*���ܿ���ͣ��*/
    SCCA_MESSAGE_OUTWORKTIME_TYPE,					/*���ڹ���ʱ����*/
    SCCA_MESSAGE_WATCHLEVEL_TYPE,					/*��Ŀ��������趨�ۿ�����*/
    SCCA_MESSAGE_PAIRING_TYPE,						/*����û�ж�Ӧ*/
    SCCA_MESSAGE_NOENTITLE_TYPE,						/*��û�й���ý�Ŀ*/
    SCCA_MESSAGE_DECRYPTFAIL_TYPE,					/*��Ŀ����ʧ��*/
    SCCA_MESSAGE_NOMONEY_TYPE,						/*���ڽ���*/
    SCCA_MESSAGE_ERRREGION_TYPE,						/*������ȷ*/
      SCCA_MESSAGE_FINGER_SHOW_TYPE,					/*ָ����ʾ*/
      SCCA_MESSAGE_FINGER_DISAPPEAR_TYPE,				/*ָ������*/
    SCCA_MESSAGE_CARDNOTACTIVE_TYPE,					/*���ܿ�δ����*/
    SCCA_MESSAGE_CARDLOGOUT_TYPE,					/*���ܿ���ע��*/
    SCCA_MESSAGE_CONDITION_CTL_TYPE,					/*�ò�Ʒ���޲�*/
    SCCA_MESSAGE_DESCRA_NOENTITLE_TYPE,				/*��Ȩ�ѵ��ڣ�����ϵ��Ӫ��*/
    SCCA_MESSAGE_ENTITLE_UPDATE_TYPE,				/*��Ȩ�����У����Եȣ�*/
    SCCA_MESSAGE_CARD_UNWONTED_TYPE,					/*���ܿ��ڲ��쳣*/
    SCCA_MESSAGE_CHANGEPRO_TOO_FAST_TYPE,			/*�벻ҪƵ����̨*/
    SCCA_MESSAGE_MS_PAIR_OK_TYPE,		    		/* ��ĸ����Գɹ� */
    SCCA_MESSAGE_MS_PAIR_FAILED_TYPE,				/* ��ĸ�����ʧ��,�����²�����ȷ��ĸ�� */
    SCCA_MESSAGE_MS_REPAIR_TYPE,						/* �ӿ������º�ĸ����� */
    SCCA_MESSAGE_CARD_MATCH_OK_TYPE,					/*������Գɹ�*/
    SCCA_MESSAGE_CARD_REMATCH_TYPE,					/*���»������*/
    SCCA_MESSAGE_CANCEL_MATCH_TYPE,					/*ȡ���������*/

    SCCA_MESSAGE_NEWEMAIL_TYPE,						/* ��ʾ���ʼ�ͼ�� */
    SCCA_MESSAGE_OVEREMAIL_TYPE,						/* ��ʾ�ʼ����� */
    SCCA_MESSAGE_HIDE_NEWEMAIL_TYPE,					/* �������ʼ�ͼ��*/
    SCCA_MESSAGE_EXIGENT_PROG_TYPE,					/*�����㲥*/
    SCCA_MESSAGE_EXIGENT_PROG_STOP_TYPE,				/*ֹͣ�����㲥*/
    SCCA_MESSAGE_CARD_UNLOCK_OK_TYPE,				/*���ܿ���������ɹ�*/
    SCCA_MESSAGE_PURSER_UPDATE_TYPE,					/*����Ǯ������*/
    SCCA_MESSAGE_NET_ERR_LOCK_TYPE,					/*�����쳣����������*/
    SCCA_MESSAGE_SYSTEM_ERR_LOCK_TYPE,				/*ϵͳ�쳣����������*/
    SCCA_MESSAGE_NET_ERR_UNLOCK_TYPE,				/*�����쳣����*/
    SCCA_MESSAGE_SYSTEM_ERR_UNLOCK_TYPE,				/*ϵͳ�쳣����*/

    /*OSD��Ϣ*/
    SCCA_MESSAGE_SHOWOSD_TYPE,						/*��ʾOSD��Ϣ*/
    SCCA_MESSAGE_HIDEOSD_TYPE,						/*����OSD��Ϣ*/

    /*��ʾ�Ի���*/
    SCCA_MESSAGE_CARDISDUE_TYPE,						/*���ܿ�����Ƿ�Ѵ߽�*/
    SCCA_MESSAGE_IPPVBUY_TYPE,						/*IPPV������ʾ�� */
    SCCA_MESSAGE_IPPV_OUTTIME_TYPE,					/*IPPV��Ŀ����*/
    SCCA_MESSAGE_HIDE_IPPVBUY_TYPE,					/*���� IPPV������ʾ�� */
    SCCA_MESSAGE_CONDITION_SEARCH_TYPE,				/*����NIT��������Ŀ*/
#endif

#if ((EMBED_CA & COLABLECA) == COLABLECA)

	HCN_NO_MSG = 0,		//��CA��Ϣ
	HCN_PLS_INSERT_SMC,	//��忨
	HCN_SMC_INSERT,		//���ܿ�����
	HCN_SMC_REMOVED,		//���ܿ�ȡ��
	HCN_SMC_INIT_SUCCEES,	//���ܿ���ʼ���ɹ�
	HCN_SMC_INIT_FAIL, 	//���ܿ���ʼ��ʧ��
	HCN_SMC_READ_ERROR,	//��������
	HCN_CARD_NOMATCH,		//���������
	HCN_MATCH_SUCCESS, 	//��Գɹ�
	HCN_MATCH_FAIL,		//���ʧ��
	HCN_NO_RIGHT,			//�޽�ĿȨ��010
	HCN_TIMEEXPIRED,		//��Ч���ѹ�
	HCN_INSTANCE_CLOSE,	//��ʱ�ض�
	HCN_OUT_WORKTIME,		//���ڹ���ʱ��
	HCN_MASK_LIMITED,		//�����޲�
	HCN_OUT_LEVEL, 		//�������տ�����
	HCN_TYPE_LIMIT,		//¼���������
	HCN_PPV,				//ppv��Ŀ
	HCN_PPC,				//ppc��Ŀ
	HCN_PPV_AWARD_SUCCESS, //ppv��Ŀ��Ȩ�ɹ�
	HCN_PPV_AWARD_FAIL,	//ppv��Ŀ��Ȩʧ��20
	HCN_PPC_AWARD_SUCCESS, //ppc��Ŀ��Ȩ�ɹ�
	HCN_PPC_AWARD_FAIL,	//ppc��Ŀ��Ȩʧ��
	HCN_REMAIN_DAY,		//�տ���Ч�ڻ��� 9�죬������
//////////////////////
	HCN_CANCEL_MATCH,		//��ȡ�����
	HCN_CANCEL_MATCHFAIL,	//ȡ�����ʧ��
	HCN_SMC_NOTOPEN,//26		//���ܿ�δ����
	HCN_CREDIT_CONUT_FULL, //��������
	HCN_UNRECOGNISED_CARD, //�޷�ʶ�����ܿ�
	HCN_ERRORVERSION_CARD, //���ܿ��汾����
	HCN_ippv_eventzreo,	//ippv�¼���Ϊ��
 /////////////////////////		
	//����֪ͨ
	HCN_MAIL_NOTIFY = 0x62,//�ʼ�
	HCN_SUBTITLE_NOTIFY, //��Ļ
	HCN_DISPALY_FINGER_NOTIFY,//��ʾָ��
	HCN_STOP_FINGER_NOTIFY,	//ָֹͣ��	
	HCN_DISPLAY_URGE_FEE_NOTIFY,//display upge_fee
	HCN_STOP_URGE_FEE_NOTIFY,//stop display	upge_fee	
	HCN_IPPV_SHOW,		//IPPV show
	HCN_IPPV_CLOSE,		//IPPV close
	HCN_REFILT_PMT,		//���´���PMT�����������������������CA

#endif

#if ((EMBED_CA & XSMCA) == XSMCA)
    XSMCA_SC_NORMAL = 0x00,                 // 0  ����״̬
    XSMCA_SC_NO_CARD,   			        // 1   δ�忨 
    XSMCA_SC_NO_PPV_RIGHT,  		        // 2  û��PPV��Ȩ 
    XSMCA_SC_NO_PPC_RIGHT,  		        // 3  û��PPC��Ȩ 
    XSMCA_SC_PARENT_CTRL,  	                // 4  �ҳ����� 
    XSMCA_SC_NO_CONDITION,  	            // 5  �����޲� 
    XSMCA_SC_INVALID_CARD,                  // 6  ��Ч�� 
    XSMCA_SC_TYPEERROR,		                // 7   ��ĸ��ι��ʧ��,�������ܿ����ʹ��� 
    XSMCA_SC_NEEDFEED,		                // 8   �ӿ���Ҫ��ĸ����Ӧ,��ι���ӿ� 
    XSMCA_SC_ZONEERROR,                     // 9   ������� 
    XSMCA_SC_FEEDTIMEERROR,                 // 10  ι��ʱ����� 
    XSMCA_SC_FEEDDATEERROR,                 // 11  ι�����ڴ��� 
    XSMCA_SC_FEEDSYSTEMTIMEERROR,           // 12  ϵͳʱ��û����ȷ��ȡ,ι��ʧ�� 
    XSMCA_SC_ACSEVICEIDEERROR,              // 13 ���Ż�AC ���� 
    XSMCA_SC_CARDSTBNOTPAIR,                // 14  ���Ż�AC ���� 
    XSMCA_SC_CARDENTITLEREMAINTDAY,         // 15  ��Ȩʣ������ 
    XSMCA_SC_UPDATAINT,                     //16   ���ܿ����ݸ��£�����ϵ�! 
    XSMCA_SC_EXIRATION_REMINDER,            // 17  ��������! 
    XSMCA_SC_HIDE_AUTH_REMAINDAY,           //18  ������Ȩʣ������ ��ʾ
#endif
	CA_OSD_NONE,
} hrca_ca2us_state_t;

/*---------- -----------------��������ʾ��Ϣ------------------------ ---------*/

#define CA_SCALE_DATA		    1     /* �������ݽ����� */
#define CA_SCALE_SCUPDATE       2     /* ���ܿ������� */


//�����ɹ�״̬
extern uint8_t g_cur_updata_time_flag;

/*----------------------------����Ȩ��Ϣ----------------------------------------*/

//����Ȩ��Ϣ����
extern uint8_t d_DetitleCount;

//����Ȩ
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_detitleInfo_t   d_DetitleInfo_dvtca[10];
#endif


/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/

//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

//����Ľ�Ŀ��Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_serviceEntitles_t *d_ServiceEntitles_cdca; //[ENTITLE_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_serviceEntitles_t d_ServiceEntitles_dvtca[ENTITLE_COUNT_DVTCA];
#endif



/*------------------------------��ĸ����Ϣ----------------------------------------*/

//��ĸ�������Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_scAddedInfo_t d_ScAddedInfo_cdca[OPERATOR_COUNT_CDCA]; 
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_scAddedInfo_t d_ScAddedInfo_dvtca[OPERATOR_COUNT_DVTCA]; 
#endif


/*------------------------------IPP��Ϣ-----------------------------------------------*/

//IPPV��Ŀ����
extern uint16_t d_IPPVProNum;

//ippv ecm pid
extern uint16_t IppvECMPID;

//ippv����
extern uint8_t IppvType;

//�鿴ipp ����
extern uint16_t viewIppCount;  

//ipp��������
extern uint16_t bookIppCount;

//��������ipp��Ŀ
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_ippBuyInfo_t d_IppBuyInfo_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_ippBuyInfo_t d_IppBuyInfo_dvtca;
#endif
#if ((EMBED_CA & CTICA) == CTICA)
extern hrctica_ippBuyInfo_t d_IppBuyInfo_ctica;
#endif
#if ((EMBED_CA & MGCA) == MGCA)
extern hrmgca_ippBuyInfo_t d_IppBuyInfo_mgca;
#endif
#if ((EMBED_CA & DSCA) == DSCA)
extern hrdsca_ippBuyInfo_t d_IppBuyInfo_dsca;
#endif
#if ((EMBED_CA & GOSCA) == GOSCA)
extern hrgosca_ippBuyInfo_t d_IppBuyInfo_gosca;
#endif
#if ((EMBED_CA & ABVCA) == ABVCA)
extern hrabvca_ippBuyInfo_t d_IppBuyInfo_abvca[2];
#endif
#if ((EMBED_CA & XGCA) == XGCA)
extern hrxgca_ippBuyInfo_t d_IppBuyInfo_xgca;
#endif
#if ((EMBED_CA & LXDTCA) == LXDTCA)
extern hrlxdtca_ippBuyInfo_t d_IppBuyInfo_lxdtca;
#endif
#if ((EMBED_CA & DVNCA) == DVNCA)
extern hrdvnca_ippBuyInfo_t d_IppBuyInfo_dvnca;
#endif

//IPPV��Ŀ��Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_viewedIpp_t d_ViewedIPPV_cdca[300];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_viewedIpp_t d_ViewedIPPV_dvtca[300];
#endif
#if ((EMBED_CA & SCCA) == SCCA)
extern hrscca_ippBuyInfo_t d_IppBuyInfo_scca;
#endif
#if ((EMBED_CA & COLABLECA) == COLABLECA)
extern hcn_ipptv_t d_IppBuyInfo_hcnca;
#endif
/*--------------------------------Ǯ����Ϣ-----------------------------------------*/

//Ǯ������
extern uint8_t d_SlotCount;

//Ǯ��ID
extern uint8_t d_SlotID[20];

//��ֵ���
extern uint32_t ChargeValue;

//Ǯ����Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_slotInfo_t  d_SlotInfo_cdca[20];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_slotInfo_t  d_SlotInfo_dvtca[20];
#endif
/*-------------------------------��Ӫ����Ϣ--------------------------------------*/

//��Ӫ�̱��
extern uint16_t d_TVSId[5];

//��Ӫ������
extern uint8_t d_OperatorCount;


//��Ӫ����Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_operatorInfo_t d_OperatorInfo_cdca[OPERATOR_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_operatorInfo_t d_OperatorInfo_dvtca[OPERATOR_COUNT_DVTCA]; 
#endif

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

//�ʼ�ͷ
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_emailInfo_t d_EmailInfo_cdca[EMAIL_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_emailInfo_t d_EmailInfo_dvtca[EMAIL_COUNT_DVTCA];
#endif


//�ʼ�����
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_emailContent_t d_EmailContent_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_emailContent_t d_EmailContent_dvtca;
#endif

/*------------------------------���ܿ���Ϣ-------------------------------------*/

//�ۿ�����
extern uint8_t d_ViewRating;

//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//���ܿ�������Ϣ
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_scBasicInfo_t d_ScBasicInfo_cdca;
extern hrcdca_scmInfo_t d_ScmInfo_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_scBasicInfo_t d_ScBasicInfo_dvtca;
#endif
#if ((EMBED_CA & CTICA) == CTICA)
extern hrctica_replyFalg_t caCoreReply;
#endif
#if ((EMBED_CA & MGCA) == MGCA)
extern hrmgca_scBasicInfo_t d_ScBasicInfo_mgca;
#endif
#if ((EMBED_CA & XGCA) == XGCA)
extern hrxgca_scBasicInfo_t d_ScBasicInfo_xgca;
#endif

/*------------------------------������Ӧ--------------------------------------*/

//������Ӧ����
extern uint8_t  d_pNumber;

//������Ӧ�б�
extern uint8_t d_pSTBIdList[5][13];

//������Ӧ״̬
extern int32_t d_pairedStatue;


/*-------------------------------Ӧ���㲥---------------------------------*/

//��ȡ��ǰ��Ŀ��Ƶ����
extern uint16_t g_ChNO; 

//�Ƿ��ֹ��̨����,TRUE:��������̨;FALSE:������̨
extern uint8_t forbidSwitchChannel;

//��¼Ӧ���㲥�ĳ���ʱ�䳤��
extern uint16_t broadcastDuration;    

//��¼�Ƿ���Ӧ���㲥��,TRUE:��;FALSE:��
extern uint8_t g_bUrgency; 

 //��¼�Ƿ��һ����Ӧ���㲥
extern uint8_t g_First_Urgency;

 //Ӧ���㲥ʱ��
extern uint32_t g_wDuration;       

			  
/*-------------------------------����---------------------------------------*/

//ʣ���ο�����
extern uint8_t TryTimes;

//������id
extern uint8_t d_StbId[12];    //������id

//�Ƿ����Զ����(only for DVNCA)
extern CA_BOOL g_bAutoPair;   

/*0�� ��ǰ���ŵĽ�ĿΪ���ӽ�Ŀ 1����ǰ���ŵĽ�ĿΪ�㲥��Ŀ*/
extern uint8_t ChangeFlag;

/*0�� ǿ�ƻ�̨ʱû�н��е��ӹ㲥��ת�� 1��ǿ�ƻ�̨ʱ�����˵��ӹ㲥��ת��*/
extern uint8_t ToChange;

//�����ɹ�״̬
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;

extern uint16_t d_NearDay;//��Ȩʣ������


/***********************************End of Static Variables for CA**************************************/

/************************************************************************************************/
/**********************************Function for CA******************************************************/
/**********************************��ƽ̨CA��ʾ���ֺ�������******************************************************/
/************************************************************************************************/
extern void HRCA_ShowAnnouncement(char * data, hrca_ca2us_state_t u8MessageType);
extern void HRCA_ShowEmailNotifyMessage(hrca_ca_email_e byShow);
extern void HRCA_ShowSuperLookPic(uint8_t picFlag,CA_BOOL* state);
extern void HRCA_AutoChargeMessage(void* ChargeInfo);
extern void HRCA_ShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t MessageType);
extern void HRCA_TimerShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t u8MessageType,uint32_t time);
extern void HRCA_FlashShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t u8MessageType,uint32_t time, uint32_t show_time, uint32_t hide_time);
extern void HRCA_ShowOperateMsg(uint8_t bMessage);
extern void HRCA_ShowLogoIcon(hrca_ca2us_state_t bLogoType, uint16_t keep_seconds);
extern void HRCA_SaveOsdInit(uint8_t OSDMaxNum);
extern CA_BOOL HRCA_SaveOsdMessage(char* u8OsdData);
extern char* HRCA_GetOsdMessage(void);
extern void HRCA_SaveOsdExit(void);
extern void HRCA_ShowOsdMessage(uint8_t u8Style, char* u8OsdData, uint8_t u8Prio,uint32_t time, uint32_t judge_value);
extern void HRCA_ShowOsdMessageWithColor(uint8_t u8Style, char* u8OsdData, uint8_t u8Prio,uint16_t u16Time, uint8_t u8JudgeValue, uint8_t *u8bgColor, uint8_t *u8fontColor, uint8_t u8FontSize);
extern void HRCA_HideOsdMessage(uint8_t u8Style);
extern void HRCA_ShowIntervalOsdMessage(uint8_t u8Style, char* u8OsdData,uint32_t u32IntervalTime,uint8_t u8JudgeValue);
extern void HRCA_HideIntervalOsdMessage(uint8_t u8Style);
extern uint8_t HRCA_GetOSDStatus(uint8_t u8Style);
extern void HRCA_ShowFinger(uint32_t u32EcmPID, char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_ShowEmmFinger(char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_ShowSuperFinger(uint32_t u32EcmPID, char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_StartIppvBuyDlg(uint32_t u32EcmPID, uint32_t u32Ippv, void *ippvBuyInfo); //hanjf
extern int32_t HRCA_IppvBuy(uint8_t* u8Pin,uint8_t buyIppType, void *ippvBuyInfo);
extern void HRCA_HideppvBuyDlg(uint32_t ecmPid, uint32_t IppType);
extern void HRCA_ForceSwitchChannel(void *ChannelInfo, uint8_t Type);
extern void HRCA_CancelForceSwitchChannel(void *cType);
extern void HRCA_GetCurentEpgTime(uint8_t *pu8Time);
extern uint8_t	HRCA_SendStringToCom(uint8_t *u8String, uint16_t u16StrLen);
extern void HRCA_ShowProgressStrip(uint8_t u8Progress, uint8_t u8Type);
extern void HRCA_HideProgressStrip(void);
extern void HRCA_RefreshShowMenu(void);
extern void HRCA_ShowSuperOSD(void *oType,uint8_t ShowOrHide);
extern void HRCA_ShowFeedStatus(uint32_t *FeedStatus);
extern void HRCA_STBShowDialog(hrca_ca2us_state_t u8MessageType, uint32_t value);
extern void HRCA_STBHideDialog(hrca_ca2us_state_t u8MessageType, uint32_t value);
extern uint8_t HRCA_Startplay(void);
extern uint8_t HRCA_Stopplay(void);
extern void HRCA_LanChange(uint8_t lanType);
extern void HRCA_RemoteLock(uint8_t LockOrUnlock);		


/*************************************Static  Variable  for  2019 *******************************************/
/***********************************   2309CA��ʾ����ȫ�ֱ������� ******************************************/
/************************************************************************************************/

/***********************************End of Static Variables for 2019**************************************/

/************************************************************************************************/
/**********************************Function for 2019******************************************************/
/********************************2309CA��ʾ���ֺ�������*************************************************/
/************************************************************************************************/
#if HR_CA_SCROLL_ON_OFF
extern D_HScroll HRCA_Text_Scroll_Create(void);
extern D_Result HRCA_Text_Scroll_Destroy(D_HScroll hscroll);
extern D_Result HRCA_Text_Scroll_Stop(D_HScroll hscroll);
extern D_Result HRCA_Text_Scroll_Start(
    D_HScroll hscroll, 
    D_U32 position, 
    D_Char* text, 
    D_U32 bg_color, 
    D_U32 text_color, 
    D_U8  font_size, 
    D_U32 scroll_speed, 
    D_U32 repeat_times, 
    D_U32 duration, 
    D_Bool immediate, 
    D_ScrollCallback callback);
extern D_ScrollState HRCA_Text_Scroll_GetState(D_HScroll hscroll);

extern int  HRCA_Scroll_Create(void);
extern D_Result HRCA_TopScroll_Start(D_HScroll handle, char *text, uint32_t repeat, uint32_t duration);
extern D_Result HRCA_BottomScroll_Start(D_HScroll handle, char *text, uint32_t repeat, uint32_t duration);
extern CA_BOOL HRCA_DeleteEnterFlags(char* OsdMessageContent, uint32_t len);
#endif
/**************************************end of function for CA********************************************************/


#endif

#endif

