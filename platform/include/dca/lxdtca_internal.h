#ifndef _LXDTCA_INTERNAL_H_
#define _LXDTCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define EXNO_LEN_LXDTCA          		24U
#define COREVER_LEN_LXDTCA      		32U
#define ATT_LEN_LXDTCA         			20U
//#define OP_COUNT_LXDTCA             	5U
#define MAXNUM_SLOT_LXDTCA          	20U   /*���洢�����Ǯ����*/
#define MAXLEN_TVSPRIINFO_LXDTCA    	20U
#define OPERATOR_COUNT_LXDTCA			4U    /*��Ӫ�̵�������*/
#define ENTITLE_COUNT_LXDTCA			240U  /*��Ȩ��Ϣ������*/
#define MAXLEN_EMAIL_TITLE_LXDTCA 		32U   /*�ʼ�����������*/
#define MAXLEN_EMAIL_CONTENT_LXDTCA     202U  /*�ʼ�����������*/
#define MAXNUM_IPPV_LXDTCA         		300U  /*IPPV��Ϣ������*/
#define MAX_TASK_NUMBER_LXDTCA         	3U    /*������������*/
#define MAX_SEMA_NUMBER_LXDTCA         	11U   /*���ź���������*/
#define EMAIL_COUNT_LXDTCA              30U   /*�ʼ�������*/

#if 0
#define CA_MAX_PIN_LENGTH_LXDTCA       	6U



#define MAXLEN_TVSPRIINFO_LXDTCA  		32U

#define MAXNUM_ACLIST_LXDTCA        	18U

#define MAXLEN_PRODUCT_NAME_IPP_LXDTCA 	300U

#define MAXLEN_EMAIL_TITLE_LXDTCA 		32U

#define MAXLEN_EMAIL_CONTENT_LXDTCA 	320U

#define MAXLEN_SN_LXDTCA 				16U

#define EMAIL_COUNT_LXDTCA              100U





#define IPP_COUNT_LXDTCA 				250U

#define SLOTID_TOTAL_LXDTCA             20U





#define CA_SWVER_LEN_LXDTCA         	20U

#define CA_AERA_LEN_LXDTCA          	12U

#define CA_CHIPID_LEN_LXDTCA         	20U



#define CA_WORKTIME_LEN_LXDTCA         	20U

#define CA_PARIED_LEN_LXDTCA         	6U

#define CA_SCTYPE_LEN_LXDTCA         	20U

#define LXDTCA_SCUPDATE_FLASH_ADD       0xFFE1	//���ܿ�������ŵ�ַƫ��


/*---------------------------�˵�����ֵ����-------------------*/
#define CA_TRUE	                                         1
#define CAERR_CDCA_BASE		             0x0100

#define CA_POINTER_INVALID                     (CAERR_CDCA_BASE + 2)   //��ָ��
#define CA_CARD_INVALID                           (CAERR_CDCA_BASE + 3)   //����Ч
#define CA_CARD_PAIROTHER                      (CAERR_CDCA_BASE + 4)   //�����������������
#define CA_CARD_NOPAIR                            (CAERR_CDCA_BASE + 5)   //��δ���
#define CA_CARD_NO_ROOM                         (CAERR_CDCA_BASE + 6)   //���ռ䲻��
#define CA_CARD_STATUS_OUT                   (CAERR_CDCA_BASE + 7)
#define CA_CARD_STATUS_NOT_READY       (CAERR_CDCA_BASE + 8)   //��δ׼����
#define CA_DATA_NOT_FIND 		             (CAERR_CDCA_BASE + 9)   //û���ҵ�����
#define CA_PIN_INVALID   		             (CAERR_CDCA_BASE + 10)  //pin����Ч
#define CA_PIN_LEN_ERR 			             (CAERR_CDCA_BASE + 11)  //pin�볤�ȴ���
#define CA_PIN_LOCKED     		             (CAERR_CDCA_BASE + 12)  //PIN�뱻��
#define CA_WATCHRATING_INVALID 	      (CAERR_CDCA_BASE + 13)  //�ۿ�������Ч
#define CA_WORKTIME_INVALID 	             (CAERR_CDCA_BASE + 14)  //����ʱ�δ���
#define CA_MONEY_LACK 			             (CAERR_CDCA_BASE + 15)  //Ǯ���࣬���ֵ
#define CA_PROG_STATUS_INVALID 	      (CAERR_CDCA_BASE + 16)
#define CA_FEEDTIME_NOT_ARRIVE            (CAERR_CDCA_BASE + 17)  //ι��ʱ��δ�������ӿ����ܱ�ι��

/*--------------------------------------------------------------------*/
#endif
/*���ܿ���Ϣ*/
typedef struct {
	char scExno[EXNO_LEN_LXDTCA];							//���ܿ�����
	char scMExno[EXNO_LEN_LXDTCA];							//ĸ������(ֻ����ӿ�)
	char caCorever[COREVER_LEN_LXDTCA];						//CA�ں˰汾
	char attTime[ATT_LEN_LXDTCA];                        	//��֤ʱ��
    uint8_t pairstate;                                      //���״̬
    uint8_t cardType;                                       //������
    uint8_t scRating;										//�ۿ�����
    uint16_t cardAreaCode;									//��������
	uint16_t tsAreaCode;	                    			//��(����)������
    uint16_t wTVSid[OPERATOR_COUNT_LXDTCA];					//��Ӫ��id
    uint16_t attPeriod;                                     //��֤����
}hrlxdtca_scBasicInfo_t;


/*Ǯ����Ϣ*/
typedef struct {
	uint8_t 	u8SlotID;        							//Ǯ��ID
	uint8_t 	u8Ver;           							//��ֵ�汾
	uint16_t    wTVSid;          							//��Ӫ��ID
	uint16_t	u16CreditLimit;  							//ʣ�����
	uint16_t	u16Balance;      							//�ѻ��ĵ���(������)
}hrlxdtca_slotInfo_t;


/*��Ӫ����Ϣ*/
typedef struct{
	uint16_t u16OperatorID;    								//��Ӫ�̵��ⲿ���
	uint8_t  u8TVSPriInfo[MAXLEN_TVSPRIINFO_LXDTCA];		//��Ӫ����ϸ��Ϣ	
} hrlxdtca_operatorInfo_t;		


/*��Ȩ��Ϣ*/
typedef struct{

	uint16_t u16OperatorID;                                 //��Ӫ��ID
    uint16_t u16ProductID;                                  //��Ŀ��
	char u16ExpriData[12];								    //����ʱ��
} hrlxdtca_serviceEntitles_t;							


/*�ʼ���Ϣ*/
typedef struct{
    uint16_t actionId;  									//Email ID
    uint16_t importance; 								    //��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t u8EmailFlag;    							   //0��ɾ���ʼ�,1 ���Ѷ��ʼ�, 3�����ʼ�
	char title[MAXLEN_EMAIL_TITLE_LXDTCA]; 				   //�ʼ�������
	char createtime[40];  							       //EMAIL������ʱ��
}hrlxdtca_emailInfo_t;								


/*�ʼ�����*/
typedef struct{
	uint8_t version[12];  									//����ʱ�䣬ͬʱ��Ϊ�ʼ�id
	uint8_t emailLength[6]; 								//�ʼ����ݳ���
	char email[MAXLEN_EMAIL_CONTENT_LXDTCA]; 				//�ʼ�����
	char title[MAXLEN_EMAIL_TITLE_LXDTCA]; 					//�ʼ�������
}hrlxdtca_emailContent_t;						


/*IPPV������Ϣ*/
typedef struct {
	uint16_t u16ProductId;									//��Ŀ��ID
	uint16_t u16OperatorID;    								//��Ӫ�̵��ⲿ���
	uint16_t u16Price;      								//��Ŀ�۸�
	char ippvPeriod[12]; 									//ippv��Ŀ����ʱ��
	uint8_t	u8SlotID;    									//Ǯ��ID
} hrlxdtca_viewedIpp_t;

/*IPPV��������Ϣ*/
typedef struct{
    uint8_t	 u8SlotID;          //Ǯ��ID
	uint16_t u16TVSID;          //��Ӫ��ID
	uint16_t u16ProductID;      //��Ŀ��ID
	uint16_t u16Price;          //��Ŀ�۸�
	char u16ExpiredDate[20];	//��Ŀ����ʱ��
}hrlxdtca_ippBuyInfo_t;

/*����Ȩ��Ϣ(��)*/
typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrlxdtca_detitleInfo_t;

#if 0
typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrlxdtca_detitleInfo_t;


typedef struct{
    uint8_t	 u8SlotID;          //Ǯ��ID
	uint16_t u16TVSID;          //��Ӫ��ID
	uint16_t u16ProductID;      //��Ŀ��ID
	uint16_t u16Price;          //��Ŀ�۸�
	uint16_t u16ExpiredDate;	//��Ŀ����ʱ��
}hrlxdtca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//��Ŀ��ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_CDCA];  	//��Ŀ����
	uint8_t	tvSId[6];    						//��Ӫ�̱��
	uint8_t ippStatus;    						//0 Ԥ���У� 1 �ѹ���
	uint8_t canTape;    						//�Ƿ����¼��  0 ����  1 ����
	char price[4];      						//��Ŀ�۸�
	char ippvPeriod[12]; 						//ippv��Ŀ����ʱ��
	uint8_t	slotId;    							//Ǯ��ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrlxdtcaca_viewedIpp_t;





typedef struct {
	char wTVSid;									//��Ӫ��id
	uint8_t paired[CA_PARIED_LEN_CDCA];					//���״̬
	uint8_t pbyIsChild;								//�Ƿ����ӿ�
	uint8_t pbIsCanFeed;							//�Ƿ�ι��
	char pDelayTime[4];				    			//ι������
	char pLastFeedTime[40];							//�ϴ�ι��ʱ��
	char parentCardSN[MAXLEN_SN_CDCA+1];     			//ĸ��id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrlxdtcaca_scAddedInfo_t;




typedef struct {
	uint8_t Modulation;
    uint16_t VPid;
	uint16_t APid;
	uint16_t PcrPid; 	
	uint32_t Frequency;
	uint32_t symbol_rate;
}hrlxdtcaca_SwitchChannel_t;

//extern void *pSemaRegisterTable[30];
//extern uint32_t TaskIdTable[9];
//extern uint32_t SemIndex;
//����Ȩ��Ϣ����
extern uint8_t d_DetitleCount;
extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;
//����Ľ�Ŀ��Ϣ
extern hrcdca_serviceEntitles_t d_ServiceEntitles_cdca[ENTITLE_COUNT_CDCA];
//��ĸ�������Ϣ
extern hrcdca_scAddedInfo_t d_ScAddedInfo_cdca[OPERATOR_COUNT_CDCA]; 
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
extern hrcdca_ippBuyInfo_t d_IppBuyInfo_cdca;
//IPPV��Ŀ��Ϣ
extern hrcdca_viewedIpp_t d_ViewedIPPV_cdca[300];
/*--------------------------------Ǯ����Ϣ-----------------------------------------*/
//Ǯ������
extern uint8_t d_SlotCount;
//Ǯ��ID
extern uint8_t d_SlotID[20];
//��ֵ���
extern uint32_t ChargeValue;
//Ǯ����Ϣ
extern hrcdca_slotInfo_t  d_SlotInfo_cdca[20];
/*-------------------------------��Ӫ����Ϣ--------------------------------------*/
//��Ӫ�̱��
extern uint16_t d_TVSId[5];
//��Ӫ������
extern uint8_t d_OperatorCount;
//��Ӫ����Ϣ
extern hrcdca_operatorInfo_t d_OperatorInfo_cdca[OPERATOR_COUNT_CDCA];
/*-------------------------------�ʼ���Ϣ-----------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;
//�ʼ�ͷ
extern hrcdca_emailInfo_t d_EmailInfo_cdca[EMAIL_COUNT_CDCA];
//�ʼ�����
extern hrcdca_emailContent_t d_EmailContent_cdca;
/*------------------------------���ܿ���Ϣ-------------------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//���ܿ�������Ϣ
extern hrcdca_scBasicInfo_t d_ScBasicInfo_cdca;
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

/*------------------------------����osd---------------------------------*/

//extern D_DCAOSDInfo  pOSDbuf;		
			  
/*-------------------------------����---------------------------------------*/

//ʣ���ο�����
extern uint8_t TryTimes;

//������id
extern uint8_t d_StbId[12];    //������id

//�Ƿ����Զ����(only for DVNCA)
extern uint8_t g_bAutoPair;   

/*0�� ��ǰ���ŵĽ�ĿΪ���ӽ�Ŀ 1����ǰ���ŵĽ�ĿΪ�㲥��Ŀ*/
extern uint8_t ChangeFlag;

/*0�� ǿ�ƻ�̨ʱû�н��е��ӹ㲥��ת�� 1��ǿ�ƻ�̨ʱ�����˵��ӹ㲥��ת��*/
extern uint8_t ToChange;

//�����ɹ�״̬
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;

#endif

/*��Ȩ��Ϣ*/
extern uint8_t d_ServiceCount;

/*IPPV��Ŀ����*/
extern uint16_t d_IPPVProNum;

/*�ۿ�����*/
extern uint8_t d_ViewRating;

/*������Ӧ����*/
extern uint8_t  d_pNumber;

/*������Ӧ�б�*/
extern uint8_t d_pSTBIdList[5][13];

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

#endif


