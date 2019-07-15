#ifndef _DIVICA_INTERNAL_H_
#define _DIVICA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define DIVICA_CA_MAX_PIN_LENGTH    6U

#define DIVICA_MAX_TASK_NUMBER      4U

#define DIVICA_MAX_SEMA_NUMBER      11U

#define MAXLEN_TVSPRIINFO_DIVICA  	32U

#define MAXNUM_ACLIST_DIVICA        18U

#define MAXLEN_PRODUCT_NAME_IPP_DIVICA 	300U

#define MAXLEN_EMAIL_TITLE_DIVICA 	32U

#define MAXLEN_EMAIL_CONTENT_DIVICA 320U

#define MAXLEN_SN_DIVICA 			16U

#define EMAIL_COUNT_DIVICA			100U

#define OPERATOR_COUNT_DIVICA		4U

#define ENTITLE_COUNT_DIVICA 		300U

#define IPP_COUNT_DIVICA 			250U

#define SLOTID_TOTAL_DIVICA         20U

#define CA_EXNO_LEN_DIVICA         	24U

#define CA_COREVER_LEN_DIVICA       32U

#define CA_SWVER_LEN_DIVICA         20U

#define CA_AERA_LEN_DIVICA          12U

#define CA_CHIPID_LEN_DIVICA        20U

#define CA_RATING_LEN_DIVICA        20U

#define CA_WORKTIME_LEN_DIVICA      20U

#define CA_PARIED_LEN_DIVICA        6U

#define CA_SCTYPE_LEN_DIVICA        20U


/*-------------------------------------ipp������Ϣ-------------------------------------------*/
typedef struct{
	uint32_t IppvId;
	char	 IppvPrice[20];
}hrdivica_ippBuyInfo_t;  

/*-----------------------------------��ĸ��ι��״̬------------------------------------------*/
typedef enum
{
	CA_DIVI_PROMT_CLEAR_F,      //0x00 �����ʾ
	CA_DIVI_INSERT_M,       	//0x01 �����ĸ
	CA_DIVI_UNEFFECTIVE_M,  	//0x02 ��Ч��ĸ
	CA_DIVI_INSERT_C,			//0x03 �������
	CA_DIVI_UNEFFECTIVE_C,		//0x04 ��Ч����
	CA_DIVI_NOT_MATCH,			//0x05 ��ĸ����
	CA_DIVI_CHECK_M,			//0x06 ĸ��ͨѶ//0X1c ʧ�ܣ�����ĸ��
	CA_DIVI_CHECK_C,			//0x07 �ӿ�ͨѶʧ�ܣ������ӿ�
	CA_DIVI_NOTIN_ACTIVETIME,   //0x08���ڼ���ʱ����
	CA_DIVI_ACTIVE_SUCCESS,     //0x09����ɹ����������һ�ſ�
	CA_DIVI_STOP_ACTIVE = 0x10, //0x10��ֹ�ӿ��������
	CA_DIVI_UNKNOW_ERR_F,       //elseδ֪����
}hrdivica_caFeedS_t;

/*-----------------------------------���ܿ���Ϣ------------------------------------------*/
typedef struct {
	char	 CardNo[18]; 	//8�ֽ� BCD�룺����
	uint8_t  PairStatus; 	//1:��� 2��δ��� 0:����ʧ��
	char 	 CardType; 		//-1 ����  8 ĸ�� 9 �ӿ�
	char 	 CardLevel; 	//-1 ʧ�� 0���������� 1���������� 2��ʮ��������  3��ʮ��������
	char     WorkTime[20];	//����ʱ�� 00:00:00-00:00:00
	char	 Region[20];	//������Ϣ001.002.003.004
	char	 CAVersion[6];	//V2.1
	char     M_CardNo[18];  //���Ϊ�ӿ������ʾĸ�����ţ����Ϊĸ��������ֶ�Ϊ��
}hrdivica_scBasicInfo_t;

/*------------------------------------�ʼ���Ϣ------------------------------------------*/
typedef struct{
	char		CreateTime[20];  //ymdhms
	uint8_t 	EmailLevel;		 //��Ҫ�̶�
	uint8_t 	IsNew;			//1  :new  0: not new
	uint16_t	EmailID;
	char   		title[36];       //�ʼ����⣬�Ϊ36
}hrdivica_emailInfo_t;									

typedef struct{
	char		email[128];
	char        title[36];       //�ʼ����⣬�Ϊ36
}hrdivica_emailContent_t;								

/*********************************************��Ȩ��Ϣ************************************/
typedef struct{
	uint8_t	PackageId; 		    //��Ʒid
	char 	StartDate[12];
	char 	EndDate[12];
	char 	Price[8];
	char 	Description[40];    //��Ʒ����
} hrdivica_serviceEntitles_t;							

/*********************************************��Ӫ����Ϣ**********************************/
typedef struct{
	char provId[6];    								//��Ӫ�̵��ⲿ���
	uint8_t provName[MAXLEN_TVSPRIINFO_DIVICA];		//��Ӫ����ϸ��Ϣ	
} hrdivica_operatorInfo_t;						//SCDCAOperatorInfo in CDCA



/*********************************************����Ȩ��Ϣ**********************************/
typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrdivica_detitleInfo_t;


/*********************************************Ŀǰû����(ipp�˵�)************************/
typedef struct {
	char productId[12];							    //��Ŀ��ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_DIVICA];//��Ŀ����
 	uint8_t	tvSId[6];    						    //��Ӫ�̱��
 	uint8_t ippStatus;    						    //0 Ԥ���У� 1 �ѹ���
	uint8_t canTape;    						    //�Ƿ����¼��  0 ����  1 ����
	char price[4];      						    //��Ŀ�۸�
	char ippvPeriod[12]; 						    //ippv��Ŀ����ʱ��
	uint8_t	slotId;    							    //Ǯ��ID
	uint8_t isIppvOrIppt;    					    // 1: ippv  2: ippt  3: ippv and ippt
} hrdivica_viewedIpp_t;


/****************************************ι����Ϣ(ι���˵���Ϣ)**************************/
typedef struct {
	char wTVSid;									//��Ӫ��id
	uint8_t paired[CA_PARIED_LEN_DIVICA];			//���״̬
	uint8_t pbyIsChild;								//�Ƿ����ӿ�
	uint8_t pbIsCanFeed;							//�Ƿ�ι��
	char pDelayTime[4];				    			//ι������
	char pLastFeedTime[40];							//�ϴ�ι��ʱ��
	char parentCardSN[MAXLEN_SN_DIVICA+1];     		//ĸ��id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrdivica_scAddedInfo_t;

/*****************************************Ǯ����Ϣ**************************************/
typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//���ö�(����) 
    char balance[12];    							//�ѻ��ĵ���
}hrdivica_slotInfo_t;

/*****************************************ǿ�ƻ�̨*************************************/
typedef struct {
	uint8_t reserve;
}hrdivica_SwitchChannel_t;


/*****************************************���ò���*************************************/

/*----------------------------------------�ʼ���Ϣ-------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;
/*-----------------------------���ܿ���Ϣ���ۿ����𡢹���ʱ��--------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

/*-----------------------------------------��Ȩ��Ϣ------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

//��Ȩʣ������
extern uint32_t Expiredays[7];
#endif


