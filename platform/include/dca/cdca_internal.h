#ifndef _CDCA_INTERNAL_H_
#define _CDCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_CDCA       	6U

#define MAX_TASK_NUMBER_CDCA         	3U

#define MAX_SEMA_NUMBER_CDCA         	20U//11U

#define MAXLEN_TVSPRIINFO_CDCA  			32U

#define MAXNUM_ACLIST_CDCA        		18U

#define MAXLEN_PRODUCT_NAME_IPP_CDCA 	300U

#define MAXLEN_EMAIL_TITLE_CDCA 			32U

#define MAXLEN_EMAIL_CONTENT_CDCA 		320U

#define MAXLEN_SN_CDCA 					16U

#define EMAIL_COUNT_CDCA                  100U

#define OPERATOR_COUNT_CDCA		4U

#if (defined(SCPUCOS) || defined(D_CA_SUPPORT_CDCA_COS)) //D_CA_SUPPORT_CDCA_COS�궨������project�㶨���
#define ENTITLE_COUNT_CDCA				500U
#else
#define ENTITLE_COUNT_CDCA				300U
#endif

#define IPP_COUNT_CDCA 					250U

#define SLOTID_TOTAL_CDCA                20U

#define CA_EXNO_LEN_CDCA          		24U

#define CA_COREVER_LEN_CDCA       		32U

#define CA_SWVER_LEN_CDCA         		20U

#define CA_AERA_LEN_CDCA          		12U

#define CA_CHIPID_LEN_CDCA         		20U

#define CA_RATING_LEN_CDCA         		20U

#define CA_WORKTIME_LEN_CDCA         	20U

#define CA_PARIED_LEN_CDCA         		6U

#define CA_SCTYPE_LEN_CDCA         		20U

#define CDCA_SCUPDATE_FLASH_ADD 0xFFE1	//���ܿ�������ŵ�ַƫ��


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

typedef struct {
    uint8_t updateTime[8];
    uint8_t scUpdateStatus;
} cdca_scUpdate;                       //���ܿ�����

typedef struct{
    uint32_t actionId;  							//Email ID
    uint8_t importance; 							//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;  								//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	char title[MAXLEN_EMAIL_TITLE_CDCA]; 				//�ʼ�������
	char createtime[40];  							//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
}hrcdca_emailInfo_t;									//SCDCAEmailHead in CDCA


typedef struct{
	uint8_t version[12];  							//����ʱ�䣬ͬʱ��Ϊ�ʼ�id
	uint8_t emailLength[6]; 						//�ʼ����ݳ���
	char email[MAXLEN_EMAIL_CONTENT_CDCA]; 				//�ʼ�����
	uint8_t reserved[6];  							//����
}hrcdca_emailContent_t;								//SCDCAEmailContent in CDCA


typedef struct{
	char provId[6];    								//��Ӫ�̵��ⲿ���
	uint8_t provName[MAXLEN_TVSPRIINFO_CDCA];			//��Ӫ����ϸ��Ϣ	
} hrcdca_operatorInfo_t;								//SCDCAOperatorInfo in CDCA


typedef struct{
    char productId[12];  							//��ĿID 
	uint8_t tapingFlag;	    						//�û��Ƿ���¼��:1������¼��0��������¼�� 
	char startTime[12];  							//��Ȩ��ʼʱ�䣬��ʽΪ:2000-02-01
	char endTime[12];    							//��Ȩ����ʱ�䣬��ʽΪ:2000-02-01
	uint8_t reserved[3];    						//����   
} hrcdca_serviceEntitles_t;							//SCDCAEntitles in CDCA


typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrcdca_detitleInfo_t;


typedef struct{
	char productId[12];								//��Ŀ��ID
    char tvSId[6];    								//��Ӫ�̱��
    uint8_t isIppvOrIppt;							//֧��ippv��ippt  1 ippv  2  ippt  3  ippv and ippt
    uint8_t ippStatus;								//�շѽ׶�   0 ippv��ѽ׶�  1 ippv�շѽ׶�  2 ippt�շѽ׶� 
    char ippCanTapPrice[6]; 						//��¼��Ľ�Ŀ�۸�
    char ippCanNotTapPrice[6]; 						//����¼��Ľ�Ŀ�۸�
	char ippvPeriod[12]; 							//ippv��Ŀ����ʱ��
	char ipptInterval[12];							//ippt��Ŀ�շѼ��
	uint8_t	slotId;									//Ǯ��ID	
	uint8_t priceCode[2];                           //�������ͣ�priceCode[0]����¼��Ľ�Ŀ��priceCode[1]��¼��Ľ�Ŀ
}hrcdca_ippBuyInfo_t;


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
} hrcdca_viewedIpp_t;


typedef struct {
	char wTVSid[OPERATOR_COUNT_CDCA][5];						//��Ӫ��id
    char scExno[CA_EXNO_LEN_CDCA];							//���ܿ��ⲿ����
    char caCorever[CA_COREVER_LEN_CDCA];						//CA�ں˰汾
    uint8_t swVer[CA_SWVER_LEN_CDCA];						//loader�汾
    uint8_t chipId[CA_CHIPID_LEN_CDCA];						//���߰�ʱΨһ
    uint8_t scRating[CA_RATING_LEN_CDCA];					//���ܿ�����
    uint8_t scWorktime[CA_WORKTIME_LEN_CDCA];				//���ܿ�����ʱ��
    char areaCode[OPERATOR_COUNT_CDCA][12];					//������
    char bouquetId[OPERATOR_COUNT_CDCA][12];					//bouquetid
	char eigenvalue[OPERATOR_COUNT_CDCA][12 * 7];			//����ֵ
	uint8_t verArry[32];
}hrcdca_scBasicInfo_t;


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
}hrcdca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//���ö�(����) 
    char balance[12];    							//�ѻ��ĵ���
}hrcdca_slotInfo_t;

typedef struct {
	uint8_t Modulation;
    uint16_t VPid;
	uint16_t APid;
	uint16_t PcrPid; 	
	uint32_t Frequency;
	uint32_t symbol_rate;
}hrcdca_SwitchChannel_t;

typedef struct{
    char TVnumber[12];
    char SCMnumber[24];
    char STBnumber[13];
    char AreaCode[12];
    char chipID[20];
    char cardID[10];
    char cardSN[34];
}hrcdca_scmInfo_t;

//extern void *pSemaRegisterTable[30];
//extern uint32_t TaskIdTable[9];
//extern uint32_t SemIndex;
//����Ȩ��Ϣ����
extern uint8_t d_DetitleCount;
extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;
//����Ľ�Ŀ��Ϣ
extern hrcdca_serviceEntitles_t *d_ServiceEntitles_cdca;//[ENTITLE_COUNT_CDCA];
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
//scm��Ϣ
extern hrcdca_scmInfo_t d_ScmInfo_cdca;
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

/*0�� ��ǰ���ŵĽ�ĿΪ���ӽ�Ŀ 1����ǰ���ŵĽ�ĿΪ�㲥��Ŀ*/
extern uint8_t ChangeFlag;

/*0�� ǿ�ƻ�̨ʱû�н��е��ӹ㲥��ת�� 1��ǿ�ƻ�̨ʱ�����˵��ӹ㲥��ת��*/
extern uint8_t ToChange;

//�����ɹ�״̬
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;
#endif


