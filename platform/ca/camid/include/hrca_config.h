/*************************************************************************************************

File Name      :  hrca_config.h

Description    :  CA configure file

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hanjf

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012.1.13  	hanjf           created             ---

**************************************************************************************************/
#ifndef _HRCA_CONFIG_H_
#define _HRCA_CONFIG_H_

#include <stdint.h>
#include "dMMan.h"
#include "dMutex.h"
#include "dDemux.h"

/******************************************************************************/ 
/***********************************CAѡ��*************************************/ 
/******************************************************************************/

#define FREEACCESS			 0        // 0           without CA		����CA
#define CDCA				(1 << 0)  // 1 	        novel-supertv		�����Ӳ�
#define DVTCA				(1 << 1)  // 2 	        sumavision		������Ѷ
#define CTICA				(1 << 2)  // 4 	        cti			    ��ͨ
#define MGCA				(1 << 3)  // 8 	        shadt			    ����Ѹ��
#define CHCA				(1 << 4)  // 16 	        changhong		    ����
#define GYCA				(1 << 5)  // 32 	        geeya			    ����
#define TRCA				(1 << 6)  // 64 	        trca               ����
#define WFCA				(1 << 7)  // 128 	    wfca              ��
#define QZCA				(1 << 8)  // 256 	    qz		         ȫ��
#define XGCA				(1 << 9)  // 512 	    xg			    �¹�
#define DIVICA				(1 << 10) // 1024        divi			    ����ͨ
#define DSCA				(1 << 11) // 2048        desaica            �Ĵ�����
#define DVNCA               (1 << 12) // 4096        dvnca	              ���
#define GOSCA               (1 << 13) // 8192        gospe              ��˹����
#define ABVCA               (1 << 14) // 16384       abvca			    ����������Ѷ
#define UNITENDCA           (1 << 15) // 32768       unitendca	         ��������̫��
#define THTFCA              (1 << 16) // 65536       thtfca	             ����ͬ����Ѷ
#define LXDTCA              (1 << 17) // 131072       lxdtca	         ��о
#define YJCA				(1 << 18) // 262144      yjca		      �ɶ�Ӣ��
#define KVCA				(1 << 19) // 524288      kvca		      ����ͨ
#define GTCA                (1 << 20) // 1048576    gtca                ��ͨ
#define XJCA                (1 << 21) // 2097152    xjca                ����
#define SCCA                (1 << 22) // 4194304    scca
#define COLABLECA			(1 << 23) // 8388608    colableca		
#define XSMCA			    (1 << 25) // 33554432  xsmca          ����о��è	

#ifdef D_SYS_SUPPORT_CA_TYPE
#define EMBED_CA            (D_SYS_SUPPORT_CA_TYPE)  //�����CA���͵Ķ�����platform.cfg�ļ���
#else
#define EMBED_CA			(CDCA | CTICA | MGCA | DVTCA | WFCA | QZCA | GOSCA | ABVCA | DSCA | XGCA | DIVICA | DVNCA | TRCA | UNITENDCA | THTFCA | LXDTCA | YJCA | KVCA | GTCA | XJCA | SCCA | COLABLECA | XSMCA)
#endif

#define ADVANCED_HEC			  0 //1:���߼���ȫ��0�������߼���ȫ
#define HR_CA_SCROLL_ON_OFF	      1 //����������: 1-on 0-off                                                     
#define HR_CA_DEBUG_TIME_RECORD   0  //1:�򿪻�̨��ʱ��ӡ 0:�رջ�̨��ʱ��ӡ 



/******************************************************************************/ 
/****************************��CA��ͬʱʹ�ñ���********************************/ 
/******************************************************************************/
typedef void            VOID;  //��ͨ������ͬʱʹ��
typedef void*           PVOID; //��ͨ������ͬʱʹ��

typedef char	        INT8;   //����������ͨͬʱʹ��
typedef unsigned char	UINT8;  //����������ͨͬʱʹ��
typedef short	        INT16;  //����������ͨͬʱʹ��
typedef unsigned short	UINT16; //����������ͨͬʱʹ��
typedef int             INT32;  //����������ͨͬʱʹ��
typedef unsigned int    UINT32; //����������ͨͬʱʹ��
typedef unsigned int   	U32;     //�������оͬʱʹ��
typedef unsigned short  U16;     //�������оͬʱʹ��
typedef unsigned char   U8;      //�������оͬʱʹ��

/**********************************END*****************************************/ 

#undef	CA_TRUE
#define CA_TRUE	    1

#undef	CA_FALSE
#define	CA_FALSE	0

/* LC��� */
#undef  TRUE
#define TRUE		CA_TRUE

#undef  FALSE
#define FALSE		CA_FALSE

typedef unsigned char  	CA_BOOL;

/****************************ͨ������********************************/ 

#define EMM_USED_FILTER_CNT	 8     //��������EMM��������������
#define DMUX_FORCALIB_CNT 	 8     //CA�����д���ʹ�õ����dumux����
#define DATA_TEMP_BUF 	     1024  //����յ���pmt cat�ռ��С

typedef struct
{
	/*���Խ��������õ���ȫ�ֱ������ڸýṹ��*/
	
	D_HMMan 	hmm; 		  /*CA�ڴ������*/
	D_Int 		trace_level;  /*��ӡ�������*/
	D_HMutex	lock;
	D_HQueue	hq; 	      /*CA APP��Ϣ���о��*/

	D_HDemux	hcatdemux; 	  /*cat demux���*/
	D_HDemux	hpmtdemux;    /*pmt demux���*/
	D_HDemux    hemmdemux[EMM_USED_FILTER_CNT];   /*emm demux���*/
	D_HDemux    hecmVdemux;   /*ecm video demux���*/
	D_HDemux    hecmAdemux;   /*ecm audio demux���*/
    D_HDemux    hnitdemux;    /*nit demux���*/

    D_U8        ecmVdemuxstart; /*ecm video demux start*/
    D_U8        ecmAdemuxstart; /*ecm Audio demux start*/        
    D_U32       ecmVdemuxtime;  /*ecm video demux start time*/
    D_U32       ecmAdemuxtime;  /*ecm Audio demux start time*/    
}D_CADev;

typedef struct
{
	D_HDemux 		hDemux;      //���뵽��dmux�豸
	D_DemuxFilter	hFilter;
    uint8_t         hFilterID;
    uint8_t         hUsed;       //0,�˹��������У�1���˹�������ʹ��
}DemuxFilterFor_CA;

typedef struct
{
    uint8_t            cSlot;     //ͨ��
    uint16_t           cSlotPid;  //ͨ��pid
    uint8_t            cUsed;     //0,��ͨ�����У�1����ͨ����ʹ��
    uint8_t            cReceive;  //0 �����ѱ�1�������ѱ�
    uint8_t            cCrc;      //0 ��У�飬 1��У��
    DemuxFilterFor_CA  cDmuxAndFilter[EMM_USED_FILTER_CNT];//ͨ����Ӧ�Ĺ�����
}DemuxFor_CA;

extern D_CADev  ca_dev;           //CA ����ʹ�õ���Ϣ���м�demux���
extern uint32_t CurCAS;           //��ǰSMART��������CA����

/******************************************************************************/ 
/*********��CA���в�ͬ�汾�Ŀ�ʱ����Ҫ�޸���ӦCA�µĺ궨������������***********/ 
/******************************************************************************/

#if ((EMBED_CA & DVTCA) == DVTCA)
//������������CA�Ĳ�ͬ�汾������Ӧ�ĺ꼴��
#define DVTCA_HUBEI_JINGZHOU  1       //1--Ϊ�˺���������Ŀ����ӵ����⹦��
#endif

#if ((EMBED_CA  & MGCA) == MGCA)
#ifndef MGCA_VERSION
//#define MGCA_VERSION
//#define MGCA_V312           7
//#define MGCA_V423           8
//#define MGCA_V              MGCA_V423  //����Ѹ��CA��ͬ��CA��汾
#endif
#endif

#if ((EMBED_CA  & DSCA) == DSCA)
#define DSCA_VER4_6		    1
#define DSCA_VER5_1		    2
#define DSCA_VER        	DSCA_VER5_1	//����CA��ͬ��CA��汾
#endif

#if ((EMBED_CA  & GOSCA) == GOSCA)
//#ifndef GOSCA_VERSION	
//#define GOSCA_VERSION
//#define GOSCA_V190                 15
//#define GOSCA_V208                 16
//#define GOSCA_V             GOSCA_V208 //��˹����CA��ͬ��CA��汾
//#endif
#define isSTB				1          //�����ǻ������������С��������� 1--STB software 0--TVPad software 
#endif


#if ((EMBED_CA & ABVCA) == ABVCA)
//#define ABVCA_GUANGSHUI           4//��ˮ��
//#define ABVCA_XINYANG             5//������
//#define ABVCA_INDIA               6//ӡ�ȿ�
//#define ABVCA_VER        	ABVCA_XINYANG	//����CA��ͬ��CA��汾
#endif
/*********************************����*****************************************/

/******************************************************************************/ 
/*******************************����ֵ����*************************************/ 
/******************************************************************************/
//�����з���ֵ��ֵ����
#define CAERR_CDCA_BASE		0x0100
#define CAERR_DVTCA_BASE	0x0200
#define CAERR_CTICA_BASE	0x0300
#define CAERR_MGCA_BASE	    0x0400
#define CAERR_CHCA_BASE	    0x0500
#define CAERR_GYCA_BASE	    0x0600
#define CAERR_TRCA_BASE	    0x0700
#define CAERR_WFCA_BASE	    0x0800
#define CAERR_DVNCA_BASE	0x0900
#define CAERR_ABVCA_BASE	0x0a00
#define CAERR_THTFCA_BASE	0x0b00

//CDCA ERR
#define CA_POINTER_INVALID             (CAERR_CDCA_BASE + 2)   //��ָ��
#define CA_CARD_INVALID                (CAERR_CDCA_BASE + 3)   //����Ч
#define CA_CARD_PAIROTHER              (CAERR_CDCA_BASE + 4)   //�����������������
#define CA_CARD_NOPAIR                 (CAERR_CDCA_BASE + 5)   //��δ���
#define CA_CARD_NO_ROOM                (CAERR_CDCA_BASE + 6)   //���ռ䲻��
#define CA_CARD_STATUS_OUT             (CAERR_CDCA_BASE + 7)
#define CA_CARD_STATUS_NOT_READY       (CAERR_CDCA_BASE + 8)   //��δ׼����
#define CA_DATA_NOT_FIND 		       (CAERR_CDCA_BASE + 9)   //û���ҵ�����
#define CA_PIN_INVALID   		       (CAERR_CDCA_BASE + 10)  //pin����Ч
#define CA_PIN_LEN_ERR 			       (CAERR_CDCA_BASE + 11)  //pin�볤�ȴ���
#define	CA_PIN_LOCKED     		       (CAERR_CDCA_BASE + 12)  //PIN�뱻��
#define CA_WATCHRATING_INVALID 	       (CAERR_CDCA_BASE + 13)  //�ۿ�������Ч
#define CA_WORKTIME_INVALID 	       (CAERR_CDCA_BASE + 14)  //����ʱ�δ���
#define CA_MONEY_LACK 			       (CAERR_CDCA_BASE + 15)  //Ǯ���࣬���ֵ
#define CA_PROG_STATUS_INVALID 	       (CAERR_CDCA_BASE + 16)
#define CA_FEEDTIME_NOT_ARRIVE         (CAERR_CDCA_BASE + 17)  //ι��ʱ��δ�������ӿ����ܱ�ι��


//DVTCA ERR 
#define CA_BOOK_OK                     (CAERR_DVTCA_BASE + 1)   //�����ɹ�
#define CA_UNBOOK_OK                   (CAERR_DVTCA_BASE + 2)   //�˶��ɹ�
#define CA_ERR_UNBOOK_FAIL    	       (CAERR_DVTCA_BASE + 3)   //�˶�ʧ�ܣ����ٴν���˵�����
#define CA_ERR_MONEY_LACK              (CAERR_DVTCA_BASE + 4)   //�����ɹ��������࣬�뼰ʱ��ֵ
#define CA_ERR_NEED_PIN_PASS           (CAERR_DVTCA_BASE + 5)   // ��Ҫͨ��PIN��֤
#define CA_ERR_IC_COMMUNICATE          (CAERR_DVTCA_BASE + 6)   //��IC��ͨѶ��������
#define CA_ERR_TVS_NOT_FOUND           (CAERR_DVTCA_BASE + 7)   //��Ӫ��ID��Ч
#define CA_ERR_SLOT_NOT_FOUND          (CAERR_DVTCA_BASE + 8)   //Ǯ��û�з���

#define CA_ERR_VER_EXPIRED             (CAERR_DVTCA_BASE + 9)   // ��Ʒ�Ѿ�����
#define CA_ERR_OPER_INVALID            (CAERR_DVTCA_BASE + 10)  // ��Ʒ�Ѿ����ڣ����ܲ���
#define CA_ERR_NO_SPACE                (CAERR_DVTCA_BASE + 11)  //û�пռ�
#define CA_ERR_PROD_NOT_FOUND          (CAERR_DVTCA_BASE + 12)  // ��Ʒû�з���
#define CA_ERR_PRICE_INVALID           (CAERR_DVTCA_BASE + 13)  //�۸���Ч
#define CA_ERR_PERIOD_INVLIAD          (CAERR_DVTCA_BASE + 14)  //��������Ч
#define CA_ERR_UNKNOWN                 (CAERR_DVTCA_BASE + 15)  //δ֪����
#define	CA_ERR_DVT_PIN_LOCKED     	   (CAERR_DVTCA_BASE + 16)  //PIN�뱻��


//CTICA ERR
#define CA_ERR_IPP_INVALID             (CAERR_CTICA_BASE + 1)  //ippv��Ŀ����
#define CA_ERR_IPP_PLAY_NOT_SUPPORT    (CAERR_CTICA_BASE + 2)  //�㲥��ʽ��֧��
#define CA_ERR_WORKTIME_SET_TIME       (CAERR_CTICA_BASE + 3)  //׼\��������ʱ�����ô���
#define CA_ERR_WORKTIME_SET_TIME_LONG  (CAERR_CTICA_BASE + 4)  //׼\��������ʱ�䳬��
#define CA_ERR_WORKTIME_SET_SLOT       (CAERR_CTICA_BASE + 5)  //׼\��������ͨ�����ô���
#define CA_ERR_WORKTIME_SET_MODE       (CAERR_CTICA_BASE + 6)  //׼\��������ģʽ���ô���
#define CA_ERR_WORKTIME_SET            (CAERR_CTICA_BASE + 7)  //׼\��������ģʽ���ô���

//GYCA ERR
#define	CA_CARD_PAIRCURRENTBOX         (CAERR_GYCA_BASE + 1)   //����Ե�ǰ������
#define CA_BOOK_FAILD		           (CAERR_GYCA_BASE + 2)   //����ʧ�ܣ�����򿨴���


//DVNCA ERR
#define CA_ERR_SC_COMMUNICATION        (CAERR_DVNCA_BASE + 1)  //����ͨѶ����
#define CA_ERR_SC_NOFUN                (CAERR_DVNCA_BASE + 2)  //���ܿ���֧�ָù���
#define CA_ERR_SC_ERROR                (CAERR_DVNCA_BASE + 3)  //���ܿ�����
#define CA_ERR_SC_CAK_STOP             (CAERR_DVNCA_BASE + 4)  //CAK stop
#define CA_ERR_SC_SEM_TIMEOUT          (CAERR_DVNCA_BASE + 5)  //�ź�����ʱ
#define CA_ERR_SC_PURSE_LACK           (CAERR_DVNCA_BASE + 6)  //����
#define CA_ERR_SC_PIN_ERROR            (CAERR_DVNCA_BASE + 7)  //�����PIN
#define CA_ERR_SC_OTHER_ERROR          (CAERR_DVNCA_BASE + 8)  //��������

#define CA_ERR_KP_SYSTEM_ERROR         (CAERR_DVNCA_BASE + 9)   //ϵͳ����
#define CA_ERR_KP_PARAMETER_ERROR      (CAERR_DVNCA_BASE + 10)  //��������
#define CA_ERR_KP_PIN_LENGHT_INVALID   (CAERR_DVNCA_BASE + 11)  //PINֵ���ȴ���
#define CA_ERR_KP_SAME_PIN             (CAERR_DVNCA_BASE + 12)  //�¾�PINֵ��ͬ
#define CA_ERR_KP_PIN_ERROR            (CAERR_DVNCA_BASE + 13)  //PINֵ����

//ABVCA ERR
#define CA_PIN_NO_MATCH        		    (CAERR_ABVCA_BASE + 1)  //�����벻ƥ��
#define CA_OTHER_ERROR                  (CAERR_ABVCA_BASE + 2)  //��������
#define CA_CARD_LOCKED                  (CAERR_ABVCA_BASE + 3)  //���ܿ�����
#define CA_PIN_ERROR				    (CAERR_ABVCA_BASE + 4)	//�������
#define CA_NO_CARD					    (CAERR_ABVCA_BASE + 5)  //�޿����������ܿ�
#define CA_BUY_IPPV_ERR			        (CAERR_ABVCA_BASE + 6)  //����IPPV��Ŀ����

//THTFCA ERR
#define CA_PIN_ERROR_1                  (CAERR_THTFCA_BASE + 1)  // PIN����ʣ��1�λ���PIN���ᱻ����
#define CA_PIN_ERROR_2                  (CAERR_THTFCA_BASE + 2)  // PIN����ʣ��2�λ���PIN���ᱻ����
#define CA_PIN_ERROR_3                  (CAERR_THTFCA_BASE + 3)  // PIN����ʣ��3�λ���PIN���ᱻ����
#define CA_TIME_ERROR                   (CAERR_THTFCA_BASE + 4)  // ʱ�����ݴ���
#define CA_TIME_SAME_ERROR              (CAERR_THTFCA_BASE + 5)  // ʱ�����ݴ��󣬿�ʼʱ�䲻�������ʱ����ͬ

/*********************************����*****************************************/

/******************************************************************************/ 
/***************************CA������ռ��С����*******************************/ 
/******************************************************************************/

//#define STACK_SIZE_SAFE 			    0
//#define SMART_TASK_STK_SIZE 		    0x600
//#define ECM_STK_SIZE			        0x600//0x800
//#define EMM_STK_SIZE			        0x600//0x800
//#define TASK_URGENCYBROADCAST_STK_SIZE 0x600//4000	   

#if ((EMBED_CA & CDCA) == CDCA)

	//#define CDSM_MSG_STK_SIZE			0x900//0x1100
	//#define CDSM_ECM_STK_SIZE			0x900//0x1100
	//#define CDSM_EMM_STK_SIZE			0x900//0x1100
	//#define CDSM_EMM_REC_STK_SIZE		0x900//0x1100
#endif	

#if ((EMBED_CA & DVTCA) == DVTCA)
	#define DVTSM_ECM_STK_SIZE 		    0x1600
	#define DVTSM_EMM_REC_STK_SIZE 	    0x1200
	#define DVTSM_EMM_STK_SIZE 		    0x1600
	#define DVTSM_OSD_STK_SIZE 		    0x1600
	#define DVTSM_FINGER_STK_SIZE	    0x1000
#endif

#if ((EMBED_CA & CTICA) == CTICA)
	//#define CTICA1_STK_SIZE	        0x500
	//#define CTICA2_STK_SIZE	        0x500
	//#define CTICA3_STK_SIZE	        0x500
	//#define CTICA4_STK_SIZE	        0x500
	//#define CTICA5_STK_SIZE	        0x500
	//#define CTICA6_STK_SIZE	        0x500
	//#define CTICA7_STK_SIZE	        0x500
	//#define CTICA8_STK_SIZE	        0x500
#endif
	
#if ((EMBED_CA & TRCA) == TRCA)
    //#define TRCA1_STK_SIZE	        0x1000//0x1000
    //#define TRCA2_STK_SIZE	        0x1000//0x1000
    //#define TRCA3_STK_SIZE	        0x1800//0x2000
    //#define TRCA4_STK_SIZE	        0x1600//0x2000
#endif
			
#if ((EMBED_CA & MGCA) == MGCA)
	//#define SM_EMM_STK_SIZE			0x1100
	//#define SM_EMM_REC_STK_SIZE		0x1100
#endif
				
#if ((EMBED_CA & WFCA) == WFCA)
	//#define WFCA1_STK_SIZE			0x2000
#endif
					
#if ((EMBED_CA & GYCA) == GYCA)
	//#define SM_CAST_STK_SIZE		    0x3000//0x2000
	//#define SM_SMTT_STK_SIZE		    0x3000
#endif
						
#if ((EMBED_CA & DIVICA) == DIVICA)
	//#define CASC_STK_SIZE 			0x1000
	//#define CACORE_STK_SIZE			0x1000
	//#define CAOSD_STK_SIZE			0x1000
	//#define CAUSER_STK_SIZE			0x1000
#endif
							
#if ((EMBED_CA & DSCA) == DSCA)
	//#define SM_ECM_STK_SIZE	        0x800
	//#define SM_EMM_STK_SIZE           0x800
	//#define SM_SK_STK_SIZE            0x800
	//#define SM_MAIL_STK_SIZE		    0x800
	//#define SM_OSD_STK_SIZE		    0x600
	//#define SM_CONFIG_STK_SIZE		0x600
	//#define SM_OSDDISP_REC_STK_SIZE   0x600
	//#define SM_MONITOR_STK_SIZE	    0x600
#endif
								
#if ((EMBED_CA & DVNCA) == DVNCA)
	//#define CAk_STK_SIZE	0x2000
#endif
									
#if ((EMBED_CA & GOSCA) == GOSCA)
	//#define GOSSM_ECM_STK_SIZE			0x1100
	//#define GOSSM_EMM_STK_SIZE			0x1100
	//#define GOSSM_MONITOR_STK_SIZE		0x1000
	//#define GOSSM_TIMER_STK_SIZE		0x1000
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    #define SCSM_STK_SIZE               0x8000
#endif
/*********************************����*****************************************/
/******************************************************************************/ 
/******************CA������ջ����(for only 2019 or 2016)***********************/ 
/******************************************************************************/
#if 0
#if (EMBED_CA != FREEACCESS)
	extern OS_STK SmartTask_Stk[SMART_TASK_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK EcmTask_Stk[ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK EmmTask_Stk[EMM_STK_SIZE + STACK_SIZE_SAFE];
#endif
										
#if ((EMBED_CA & CDCA) == CDCA)
	extern OS_STK CDCA_Stk4[CDSM_MSG_STK_SIZE + STACK_SIZE_SAFE];      //6k
	extern OS_STK CDCA_Stk1[CDSM_ECM_STK_SIZE + STACK_SIZE_SAFE];      //10k
	extern OS_STK CDCA_Stk3[CDSM_EMM_STK_SIZE + STACK_SIZE_SAFE];      //10k
	extern OS_STK CDCA_Stk5[CDSM_EMM_REC_STK_SIZE + STACK_SIZE_SAFE];  //6k
#endif

#if ((EMBED_CA & DVTCA) == DVTCA)
	extern OS_STK DVTCA_Stk1[DVTSM_ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk2[DVTSM_EMM_REC_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk3[DVTSM_EMM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk4[DVTSM_OSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk5[DVTSM_FINGER_STK_SIZE + STACK_SIZE_SAFE];
#endif
												
#if ((EMBED_CA & CTICA) == CTICA)
	extern OS_STK CTICA_Stk1[CTICA1_STK_SIZE];
	extern OS_STK CTICA_Stk2[CTICA2_STK_SIZE];
	extern OS_STK CTICA_Stk3[CTICA3_STK_SIZE];
	extern OS_STK CTICA_Stk4[CTICA4_STK_SIZE];
	extern OS_STK CTICA_Stk5[CTICA5_STK_SIZE];
	extern OS_STK CTICA_Stk6[CTICA6_STK_SIZE];
	extern OS_STK CTICA_Stk7[CTICA7_STK_SIZE];
	extern OS_STK CTICA_Stk8[CTICA8_STK_SIZE];

	extern void HRCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);  
#endif
													
#if ((EMBED_CA & WFCA) == WFCA)
	extern OS_STK WFCA_Stk1[WFCA1_STK_SIZE];
#endif
													
#if ((EMBED_CA & TRCA) == TRCA)
	extern OS_STK TRCA_Stk1[TRCA1_STK_SIZE];
	extern OS_STK TRCA_Stk2[TRCA2_STK_SIZE];
	extern OS_STK TRCA_Stk3[TRCA2_STK_SIZE];
	extern OS_STK TRCA_Stk4[TRCA3_STK_SIZE];
#endif
														
#if ((EMBED_CA & GYCA) == GYCA)
	extern OS_STK GYCA_Stk1[SM_CAST_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK GYCA_Stk2[SM_SMTT_STK_SIZE + STACK_SIZE_SAFE];
#endif
															
#if ((EMBED_CA & DIVICA) == DIVICA)
	extern OS_STK CaScStk[CASC_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaCoreStk[CACORE_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaOsdStk[CAOSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaUserStk[CAUSER_STK_SIZE + STACK_SIZE_SAFE];
#endif
																
#if ((EMBED_CA & DSCA) == DSCA)
	extern OS_STK     DSCA_Stk1[SM_ECM_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk2[SM_EMM_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk3[SM_SK_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk4[SM_MAIL_STK_SIZE + STACK_SIZE_SAFE];  
	extern OS_STK     DSCA_Stk5[SM_OSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK     DSCA_Stk6[SM_CONFIG_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK     DSCA_Stk7[SM_OSDDISP_REC_STK_SIZE + STACK_SIZE_SAFE]; 
 	extern OS_STK	  DSCA_Stk8[SM_MONITOR_STK_SIZE + STACK_SIZE_SAFE];
#endif
																	
#if ((EMBED_CA & DVNCA) == DVNCA)
	extern OS_STK CA_Stk_Cak[CAk_STK_SIZE + STACK_SIZE_SAFE];
#endif
																	
#if ((EMBED_CA & GOSCA) == GOSCA)
	extern OS_STK GOSCA_Stk1[CA_ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK GOSCA_Stk2[CA_EMM_STK_SIZE + STACK_SIZE_SAFE]; 
	extern OS_STK GOSCA_Stk3[CA_MONITOR_STK_SIZE + STACK_SIZE_SAFE]; 
	extern OS_STK GOSCA_Stk4[CA_TIMER_STK_SIZE + STACK_SIZE_SAFE];
#endif

#endif
/*********************************����*****************************************/
//#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
//#include "dca/unitendca_internal.h"
//#include "dca/unitendca_fun.h"
//#endif

/******************************************************************************/ 
/***************************CA���ݱ�ID����*************************************/ 
/******************************************************************************/

#define CAT_PID                   0x01
#define NIT_ACTUAL_NETWORK_TABLE_ID         0x40
#define NIT_OTHER_NETWORK_TABLE_ID          0x41
#define CAT_TABLE_ID              0x01
#define PMT_TABLE_ID              0x02
#define ECM_TABLE_ID0             0x80
#define ECM_TABLE_ID1             0x81
#define EMM_TABLE_ID2             0x82
#define EMM_TABLE_ID3             0x83
#define EMM_TABLE_ID4             0x84
#define EMM_TABLE_ID5             0x85
#define EMM_TABLE_ID6             0x86
#define EMM_TABLE_ID7             0x87
#define EMM_TABLE_ID8             0x88
#define EMM_TABLE_ID9             0x89
#define EMM_TABLE_IDA             0x8a
#define EMM_TABLE_IDB             0x8b
#define EMM_TABLE_IDC             0x8c
#define EMM_TABLE_IDD             0x8d
#define EMM_TABLE_IDE             0x8e
#define EMM_TABLE_IDF             0x8f
#define EMM_TABLE_ID90            0x90

/*********************************����*****************************************/

/******************************************************************************/ 
/******************************��Ƶ���붨��************************************/ 
/******************************************************************************/

#define CA_MPEG1_VIDEO_STREAM        0x01
#define CA_MPEG2_VIDEO_STREAM        0x02
#define CA_MPEG1_AUDIO_STREAM        0x03
#define CA_MPEG2_AUDIO_STREAM        0x04
#define CA_PRIVATE_DATA_STREAM       0x06

#define CA_iso_iec_14496_10_AVC_VIDEO_STREAM                     0x1B  //h.264  mpeg4	��Ƶ
#define CA_iso_iec_14496_2_visual_VIDEO_STREAM                   0x10
#define CA_avs_VIDEO_STREAM                                      0x42  //AVS��Ƶ

#define CA_iso_iec_14496_3_audio_w_LATM_transp_AUDIO_STREAM      0x11  //ACC��Ƶ
#define CA_iso_iec_13818_7_audio_w_ADTS_transp_AUDIO_STREAM      0x0F  //ACC��Ƶ
#define CA_atsc_A_53B_Annex_B_AUDIO_STREAM                       0x81  //AC3��Ƶ
#define CA_avs_AUDIO_STREAM                                      0x43  //AVS��Ƶ

/*********************************����*****************************************/

/*********************************����*****************************************/
#define NO_OF_CRC_DATA_BYTES         4
#define CA_DESC                      0x09
#define MAX_PPID_NUM                 8
/*********************************����*****************************************/

/******************************************************************************/ 
/******************************fun.c api***************************************/ 
/******************************************************************************/

#if EMBED_CA != FREEACCESS
	extern CA_BOOL HRCA_GetDateStrFromValC (uint16_t wInputDate, char* szOut);
	extern CA_BOOL HRCA_GetTimeStrFromValC (uint32_t nInputTime, char* szOut);
	extern CA_BOOL HRCA_GetTimeStrFromValC1(uint32_t nInputTime, char* szOut);
	extern CA_BOOL HRCA_EmailGetDateStrFromValC (uint16_t wInputDate, char* szOut);
	extern CA_BOOL HRCA_EmailGetTimeStrFromValC(uint32_t nInputTime, char* szOut);
	extern uint32_t HRCA_BCD2dec(uint32_t u32BCD);
    extern void HRTimer_Mjd2ymd(uint16_t MJD, uint32_t *Year, uint32_t *Month, uint32_t *Day);
    extern void HRTimer_dateToMJD(uint8_t mjd[2], uint32_t year, uint32_t month, uint32_t day);
    extern uint8_t* HexStringToBin(int8_t* name, uint32_t num);
    extern uint32_t hex2dec(uint8_t* hex);
  
    extern CA_BOOL  HRCA_FreeProg(void);
    extern CA_BOOL  HRCA_CurCAProg(void);
    extern int16_t HRCA_GetServiceID(void);
    extern int16_t HRCA_GetTSID(void);
    extern int16_t HRCA_GetOrgNetWorkID(void);
    extern uint16_t HRCA_GetNetWorkID(void);
 
#endif
/*********************************����*****************************************/
#endif
