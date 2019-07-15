#ifndef _DVNCA_INTERNAL_H_
#define _DVNCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_DVNCA       	6U

#define MAX_TASK_NUMBER_DVNCA         	3U

#define MAX_SEMA_NUMBER_DVNCA         	11U

#define MAXLEN_TVSPRIINFO_DVNCA  		32U

#define MAXNUM_ACLIST_DVNCA        		18U

#define MAXLEN_PRODUCT_NAME_IPP_DVNCA 	300U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS�궨������project�㶨���
#define MAXLEN_EMAIL_TITLE_DVNCA 		32U 
#else
#define MAXLEN_EMAIL_TITLE_DVNCA 		11U //�����11���ַ��ǷǺ��ֵı��룬����ʾ10���ַ���������ʾ10����9���ַ�
#endif

#define MAXLEN_EMAIL_CONTENT_DVNCA 		1100U

#define MAXLEN_SN_DVNCA 				16U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS�궨������project�㶨���
#define EMAIL_COUNT_DVNCA				32U//100U //100���ʼ��ᵼ���ڴ����
#else
#define EMAIL_COUNT_DVNCA				50U//100U //100���ʼ��ᵼ���ڴ����
#endif

#define ACCOUNT_COUNT_DVNCA             100U

#define OPERATOR_COUNT_DVNCA			4U

#define ENTITLE_COUNT_DVNCA 			300U

#define IPP_COUNT_DVNCA 				100U

#define SLOTID_TOTAL_DVNCA              20U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS�궨������project�㶨���
#define CA_EXNO_LEN_DVNCA          		32U
#else
#define CA_EXNO_LEN_DVNCA          		24U 
#endif

#define CA_COREVER_LEN_DVNCA       		9U 

#define CA_SWVER_LEN_DVNCA         		20U

#define CA_AERA_LEN_DVNCA          		12U

#define CA_CHIPID_LEN_DVNCA         	20U

#define CA_RATING_LEN_DVNCA         	20U

#define CA_WORKTIME_LEN_DVNCA         	20U

#define CA_PARIED_LEN_DVNCA         	6U

#define CA_SCTYPE_LEN_DVNCA         	20U

#define CA_OSD_LEN_DVNCA         	    256U //ʵ����Ч�ĳ�����255

#define MAXLEN_FORMAT_TEXT_DVNCA        292U //5+32+255

#define MAXLEN_FILTER_DATA_DVNCA        1024U 

typedef struct
{    
	float p;       //��ֵ����
    int32_t Index; //��ֵ����
}hrdvnca_autoChange_t;


typedef struct
{    
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS))
	uint8_t email_id;
#endif
	uint8_t status;
	char email_Time[8];    
	char body_context[MAXLEN_EMAIL_CONTENT_DVNCA+2];
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS))
	char body_text[MAXLEN_EMAIL_TITLE_DVNCA+2];
#endif 
}CA_MAIL_T; //�洢�ʼ�(�п�ca���޿�ca),��ʾ�ʼ�(�޿�ca)ʱʹ�ô˽ṹ��

typedef struct
{    
	uint8_t email_id;  //�п�ca���email_idѡ�Ϊ��ʾ�ʼ�ʱ����ʹ��
	uint8_t status;
	char email_Time[8];    
	char body_context[MAXLEN_EMAIL_CONTENT_DVNCA+2];
}DVNCA_MAIL_T; //�п�ca��ʾ�ʼ�ʱʹ�ô˽ṹ��

typedef struct{
    uint8_t importance; 							//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;  								//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	char title[MAXLEN_EMAIL_TITLE_DVNCA]; 				//�ʼ�������
	char createtime[40];  							//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
}hrdvnca_emailInfo_t;									


typedef struct{
	char email[MAXLEN_EMAIL_CONTENT_DVNCA]; 	    //�ʼ�����
	char title[36];                                 //�ʼ����⣬�Ϊ36
}hrdvnca_emailContent_t;								


typedef struct{
	char provId[6];    								//��Ӫ�̵��ⲿ���
	char provName[MAXLEN_TVSPRIINFO_DVNCA];			//��Ӫ����ϸ��Ϣ	
} hrdvnca_operatorInfo_t;								


typedef struct{
    char productId[6];  							//��Ȩ��
	char startTime[20];  							//��Ȩ��ʼʱ�䣬��ʽΪ:2000-02-01 00:00:01
	char endTime[20];    							//��Ȩ����ʱ�䣬��ʽΪ:2000-02-01 00:00:01
} hrdvnca_serviceEntitles_t;							


typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrdvnca_detitleInfo_t;


typedef struct{
	uint8_t type;								    //IPPV����
    uint8_t Product_ID[2];    						//��Ŀ��
    uint8_t Reserved[2];							//Ԥ��
    uint8_t Price[4];								//�۸�
    uint8_t Start_Time[8];                          //��ʼʱ��
    uint8_t End_Time[8]; 						    //����ʱ��
    uint8_t Trans_Time[8];                          //Ԥ��ʱ��(��ǰʱ��)
}hrdvnca_ippBuyInfo_t;


typedef struct {
	char Product_ID[6];    						//��Ŀ��
    char Price[8];								//�۸񣬸�ʽΪ.2f
    char Start_Time[20];                        //��ʼʱ��2000-00-00  00:00:00
    char End_Time[20]; 						    //����ʱ�� 2000-00-00  00:00:00
} hrdvnca_viewedIpp_t;


typedef struct {
    char scExno[CA_EXNO_LEN_DVNCA];					//���ܿ��ⲿ����
    char caCorever[CA_COREVER_LEN_DVNCA];				//CA�ں˰汾
 }hrdvnca_scBasicInfo_t;

typedef struct {
	char stbID[32 + 1];							//�����к�
	uint8_t paired;				                //���״̬0: δ���, 1:�����
	char accNo[8 + 1];				    		//�˺�
	char token[14];     		                //��� , ��ʽΪ %ld.%02d
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS�궨������project�㶨���
	char licenceID[32 + 1];		               //licenceID, �޿�ʱʹ��
    char groupID[32 + 1];		               //groupID, �޿�ʱʹ��
#endif
}hrdvnca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char balance[12];    					    //���õĵ���
    char cost[12];    						   //�ѻ��ĵ���
}hrdvnca_slotInfo_t;


typedef struct{
    char type[4];  							//����
    char TransID[7];  						//���׺�  
	char startTime[20];  				    //��ʼʱ�䣬��ʽΪ:2000-02-01 00:00:01
	char price[14];    					    //��� , ��ʽΪ %ld.%02d
	char confirmCode[17];                   //ȷ����
} hrdvnca_accountRecords_t;							

typedef struct
{
	CA_MAIL_T email_info; //email����Ϣ
}hrdvnca_email_t; //  �˽ṹ�����ڴ洢emailʹ��


typedef struct {
	uint8_t reserve;
}hrdvnca_SwitchChannel_t;

//ȫ��osd
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1024]; 
}hrdvnca_Anno_t;


/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

/*------------------------------���ܿ���Ϣ-------------------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

/*-------------------------------��Ӫ����Ϣ--------------------------------------*/
//��Ӫ�̱��
extern uint16_t d_TVSId[5];
//��Ӫ������
extern uint8_t d_OperatorCount;

/*--------------------------------Ǯ����Ϣ-----------------------------------------*/
//Ǯ������
extern uint8_t d_SlotCount;
//Ǯ��ID
extern uint8_t d_SlotID[20];

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;


/*------------------------------IPP��Ϣ-----------------------------------------------*/
//IPPV��Ŀ����
extern uint16_t d_IPPVProNum;
#endif


