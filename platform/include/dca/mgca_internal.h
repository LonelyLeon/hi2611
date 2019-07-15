#ifndef _MGCA_INTERNAL_H_
#define _MGCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_MGCA       6U  //Ϊ�˱���ͨ����ʵ�ʵ���ֵ�д�ȷ��

#define MAX_TASK_NUMBER_MGCA        5

#define MAX_SEMA_NUMBER_MGCA         14

#define MAXLEN_PRODUCT_NAME_IPP_MGCA 300

#define MAXLEN_FEEDDATA_LEN_MGCA 256

#define MAXLEN_EMAIL_SENDERNAME_MGCA 32

#define MAXLEN_EMAIL_SHORT_CONTENT_MGCA 50

#define MAXLEN_EMAIL_TITLE_MGCA 50

#define MAXLEN_EMAIL_CONTENT_MGCA 520

#define EMAIL_COUNT_MGCA		100U
            
#define OPERATOR_COUNT_MGCA	10

#define IPP_COUNT_MGCA 250

#define CA_EXNO_LEN_MGCA          33
#define CA_SWVER_LEN_MGCA         20
#define CA_CHIPID_LEN_MGCA         20
#define CA_SCTYPE_LEN_MGCA         20

#define CA_INNO_LEN_MGCA          20

#define MAXLEN_PRODUCT_NAME_MGCA 24
#define MAXLEN_SERVICE_NAME_MGCA 24

#define ENTITLE_COUNT_MGCA 				300U

//----------�ʼ�
typedef struct{
	char createtime[22];  //����ʱ��
	char title[MAXLEN_EMAIL_SHORT_CONTENT_MGCA]; //�ʼ�����
    uint8_t newEmail;  // ���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ� 
}hrmgca_emailInfo_t;


typedef struct{
	char senderName[MAXLEN_EMAIL_SENDERNAME_MGCA];  //������21
	char title[MAXLEN_EMAIL_SHORT_CONTENT_MGCA]; //�ʼ����� 21
	char email[MAXLEN_EMAIL_CONTENT_MGCA]; //�ʼ�����
}hrmgca_emailContent_t;


typedef struct
{
	uint8_t EMPTY;
}hrmgca_operatorInfo_t;


typedef struct{
    uint8_t EMPTY;   
}hrmgca_serviceEntitles_t;


typedef struct {
	uint8_t EMPTY;
}hrmgca_detitleInfo_t;


//---------IPPV
typedef struct {
	uint8_t ProgState; 	//����״̬ 1�Ѷ��� 0 δ����
	uint16_t price;  //   ��/����
	uint32_t balance;//���  ��
}hrmgca_ippBuyInfo_t;




typedef struct {
	uint8_t	EMPTY;   
}hrmgca_viewedIpp_t;


//------���ܿ���Ϣ-----
typedef struct {
	char CA_operator[20];//ca����									
	char CASoftver[8];//����汾																										
    char sc_exno[CA_EXNO_LEN_MGCA];//���ܿ�����																											
	uint16_t sc_ctrlCode;//���ܿ��޲��� 2�ֽ�					        
	uint16_t expireday;//�����Ȩ���ڣ��죩								
	uint8_t paired;//�Ƿ��������   1 ����  0δ����
    uint8_t aera_code;//������											 
	uint32_t balance;//����Ǯ���ܶ�                                      
    uint32_t consumed;//�û������ѽ��										 
	char buff[65];//�������������ʾ��ÿ��32���ַ����Ѿ�ת�����ַ���																																								
}hrmgca_scBasicInfo_t;


//--------��ĸ��
typedef struct {
	uint8_t ismcard; //1ĸ��
	char    Mcardnumb[9];
	uint16_t active_day_leaving;//�ɹۿ�ʱ��
	uint16_t active_day_remain;//�ӿ�����ʱ��
}hrmgca_scAddedInfo_t;



typedef struct {
	uint32_t balance;//����Ǯ���ܶ�                                      
    uint32_t consumed;//�û������ѽ��
}hrmgca_slotInfo_t;

typedef struct {
    uint16_t Service_ID;
}hrmgca_SwitchChannel_t;

//��Ȩʣ������
extern uint16_t d_NearDay;

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
extern hrmgca_ippBuyInfo_t d_IppBuyInfo_mgca;


/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

/*--------------------------------Ǯ����Ϣ-----------------------------------------*/

//Ǯ������
extern uint8_t d_SlotCount;

//Ǯ��ID
extern uint8_t d_SlotID[20];

//��ֵ���
extern uint32_t ChargeValue;

/*-------------------------------��Ӫ����Ϣ--------------------------------------*/

//��Ӫ�̱��
extern uint16_t d_TVSId[5];

//��Ӫ������
extern uint8_t d_OperatorCount;

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

/*------------------------------���ܿ���Ϣ-------------------------------------*/

//�ۿ�����
extern uint8_t d_ViewRating;

//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//���ܿ�������Ϣ
extern hrmgca_scBasicInfo_t d_ScBasicInfo_mgca;

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

/*0�� ��ǰ���ŵĽ�ĿΪ���ӽ�Ŀ 1����ǰ���ŵĽ�ĿΪ�㲥��Ŀ*/
extern uint8_t ChangeFlag;

/*0�� ǿ�ƻ�̨ʱû�н��е��ӹ㲥��ת�� 1��ǿ�ƻ�̨ʱ�����˵��ӹ㲥��ת��*/
extern uint8_t ToChange;

//�����ɹ�״̬
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;
/*--------------------------------------------------------------------------*/
#endif

