#ifndef _DVTCA_INTERNAL_H_
#define _DVTCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_DVTCA       8U

#define MAX_TASK_NUMBER_DVTCA         5U

#define MAX_SEMA_NUMBER_DVTCA         14U

#define MAXLEN_TVSNAME_DVTCA  		24U

#define MAXLEN_PRODUCT_NAME_IPP_DVTCA 24U

#define MAXLEN_FEEDDATA_LEN_DVTCA 	256U

#define MAXLEN_EMAIL_SENDERNAME_DVTCA 12U

#define MAXLEN_EMAIL_TITLE_DVTCA 		32U

#define MAXLEN_EMAIL_CONTENT_DVTCA 	1025U

#define EMAIL_COUNT_DVTCA		50U

#define EMAIL_COUNT_DVTCA_COS10	 20U //cos10�Ŀ������20���ʼ�

#define OPERATOR_COUNT_DVTCA	5U

#define ENTITLE_COUNT_DVTCA      300U

#define IPP_COUNT_DVTCA 				250U

#define SLOTID_TOTAL_DVTCA            20U

#define CA_INNO_LEN_DVTCA          	40U

#define CA_EXNO_LEN_DVTCA          	64U

#define CA_PCARD_LEN_DVTCA		 	24U

#define CA_COREVER_LEN_DVTCA       	20U

#define CA_SWVER_LEN_DVTCA         	21U

#define CA_AERA_LEN_DVTCA          	12U

#define CA_RATING_LEN_DVTCA         	20U

#define CA_WORKTIME_LEN_DVTCA         20U

#define CA_COS_LEN_DVTCA				4U

#define MAXLEN_PRODUCT_NAME_DVTCA 	24U

#define MAXLEN_SERVICE_NAME_DVTCA 	24U

#define CA_MAXLEN_OSD_DVTCA   		210U

#define CA_CHIPID_LEN_DVTCA		20U


typedef struct{
	char createVersion[40];                  	    //Email ����ʱ��
	int8_t senderName[MAXLEN_EMAIL_SENDERNAME_DVTCA];  	//����������
	uint8_t emailLength[6];                      	//�ʼ����ݳ���
	int8_t title[MAXLEN_EMAIL_TITLE_DVTCA];    			//�ʼ������� 
    uint8_t importance;                          	//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;                            	//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ� 
}hrdvtca_emailInfo_t;


typedef struct{
	char version[12];                        		//����ʱ��
	char emailLength[6];                     		//�ʼ����ݳ���
	int8_t	email[MAXLEN_EMAIL_CONTENT_DVTCA];        	//�ʼ�����
}hrdvtca_emailContent_t;



typedef struct{
	char provId[8];    								//��Ӫ�̵��ⲿ���
	char provName[MAXLEN_TVSNAME_DVTCA];	
}hrdvtca_operatorInfo_t;


typedef struct{
    char productId[8];     							//��ƷID   (SCDCAEntitle.m_dwProductID for cdca)	
	uint8_t tapingFlag;       						//¼���ʶ   1 ��¼�� 0 ����¼��
	char entitleTime[40];  							//��Ȩʱ�䣬time_t��ʽ��
	char startTime[40];    							//��ʼʱ�䣬time_t��ʽ��  (SCDCAEntitle.m_tBeginDate for cdca)
	char endTime[40];      							//����ʱ�䣬time_t��ʽ��   (SCDCAEntitle.mExpireDate for cdca)
	char productName[MAXLEN_PRODUCT_NAME_DVTCA];   	//��Ʒ����  (m_Entitles  for cdca) 
}hrdvtca_serviceEntitles_t;


//������Ѷû�з���Ȩ
typedef struct{
    uint8_t Detitle[2];
}hrdvtca_detitleInfo_t;


typedef struct {
	char tvSId[6];                          //��Ӫ��ID
	char productId[6];                      //��Ʒ���
	uint8_t slotId;                         //Ǯ��ID
	char prodName[MAXLEN_PRODUCT_NAME_DVTCA];    	//��Ŀ����
	char progType[5];                      	//��Ŀ����IPPV��IPPT
	char startTime[20];                    		//��ʼʱ��
	char durationTimeDay[4];               		//����ʱ��XXXX��XXʱXX��XX��
	char durationTimeHour[4];
	char durationTimeMin[4];
	char durationTimeSec[4];
	char serviceName[CA_SWVER_LEN_DVTCA];        //����Ƶ��
	char curTppTapPrice[7];                //���ش���¼��۸�
	char curTppNoTapPrice[7];              //���ش���¼��۸�(Ŀǰ��CA��ֻ��ʾ"���ش���¼��"���͵ļ۸�),  ��λ��Ԫ                             
	char curCppTapPrice[7];                //�ɻش���¼��۸�
	char curCppNoTapPrice[7];              //�ɻش���¼��۸�
	char bookPrice[7]; 					   //�����۸�,���۸�ֵΪ0ʱ����ʾ"��"
	uint8_t BookedPriceType;			   //�����۸�����(���ּ۸��е�һ��,Ŀǰ��CA��ֻ��ʾ"���ش���¼��"���͵ļ۸�)
	char BookedInterval[4];			       //�����۸���
	char CurInterval[4];				   //��ǰ�շѼ��		
	uint8_t ippStatus;					   //����״̬ 1: �Ѷ���0: δ����
    uint8_t	unit;					//�շѼ���ĵ�λ0 -����1-Сʱ2-��3-��4-��
	char ipptPeriod[6];			//�û�����IPPT�Ĺۿ�������,for Philippines LongIPPT��
	uint16_t ippIndex;              //Ϊ�˶���IPPʱ�� ��sdvtcaipp[IPP_COUNT]��    �ҵ���Ӧ��ֵ
}hrdvtca_ippBuyInfo_t;


typedef struct {
	char provName[MAXLEN_TVSNAME_DVTCA];	                //��Ӫ������
	char prodName[MAXLEN_PRODUCT_NAME_IPP_DVTCA];    		//��Ʒ����
	char startTime[20];    							//��ʼʱ�䣬time_t��ʽ��
	char durationTimeDay[4];               			//����ʱ��XXXX��XXʱXX��XX��
	char durationTimeHour[4];
	char durationTimeMin[4];
	char durationTimeSec[4];
	char otherInfo[48];    						//ippvʱΪ���˲�ƷΪippv��Ʒ����ipptʱΪ���ۿ���ʱ�䣺�����ӣ���Ǯ���������֡�
	char bookedPrice[6];    					//Ԥ���۸�(��)
	int8_t bookedPriceType;    					//Ԥ���۸����ͣ�0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap;
	char BookedInterval[4];			            //�����۸��� 
	int8_t unit;    							//�շѵ�λ��0 -����1-Сʱ2-��3-��4-��
	int8_t slotId;                             	//Ǯ��ID
	char tvSId[4];                             	//��Ӫ�̱��
	int8_t ippStatus;							//Ipp��Ʒ״̬ 1: �Ѷ���0: δ����
	uint8_t isCanTape;    						//�Ƿ��¼��
	uint8_t ippType;    						// 1: ippv  2: ippt
}hrdvtca_viewedIpp_t;



typedef struct {
    char scInNo[CA_INNO_LEN_DVTCA];			  //���ܿ��ڲ�����
    uint8_t scExNo[CA_EXNO_LEN_DVTCA];			  //���ܿ��ⲿ����
    char scCosVer[CA_COS_LEN_DVTCA];			  //���ܿ�cos�汾
    char casVer[CA_COREVER_LEN_DVTCA];           //������cas�汾
    uint8_t casNo[CA_SWVER_LEN_DVTCA];              //cas����
    char scRating[CA_RATING_LEN_DVTCA];          //���ܿ�����
    char scWorktime[CA_WORKTIME_LEN_DVTCA];      //���ܿ�����ʱ��
    char areaCode[CA_AERA_LEN_DVTCA];            //������
    char areaTime[CA_INNO_LEN_DVTCA];            //�յ�������ʱ��
    char chipID[CA_CHIPID_LEN_DVTCA];		//оƬID��һ����4���ֽ�
    uint8_t areaStatus;                       //����������״̬
    uint8_t isPinLocked;
}hrdvtca_scBasicInfo_t;


typedef struct {
    uint8_t scType;                           		//������ 0:ĸ��1:�ӿ�
    char pCardNo[CA_PCARD_LEN_DVTCA];			  			//ĸ������
    uint8_t scPscData[MAXLEN_FEEDDATA_LEN_DVTCA];   		//ι������
    uint8_t scDataLen;                        		//ι�����ݳ���
    
}hrdvtca_scAddedInfo_t;



typedef struct {
	uint8_t slotId;
	char  remainder[12];							//ʣ��Ǯ��
    char  balance[12];    							//�ѻ��ĵ���
}hrdvtca_slotInfo_t;

typedef struct {
    uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
}hrdvtca_SwitchChannel_t;

//��Ҫ�ʼ�������ʾ���û�������ң���˳�
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1030]; 
}hrdvtca_Anno_t;


/*------------------------------����ֵ���Ͷ���-------------------------------------*/

#undef	CA_TRUE
#define CA_TRUE	1

#undef	CA_FALSE
#define	CA_FALSE	0

//�����з���ֵ��ֵ����

#define CAERR_DVTCA_BASE	0x0200



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

/*------------------------------���ܿ���Ϣ-------------------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//���ܿ�������Ϣ
extern hrdvtca_scBasicInfo_t d_ScBasicInfo_dvtca;

/*------------------------------��ĸ����Ϣ----------------------------------------*/

extern hrdvtca_scAddedInfo_t d_ScAddedInfo_dvtca[OPERATOR_COUNT_DVTCA]; 

/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

//����Ľ�Ŀ��Ϣ
extern hrdvtca_serviceEntitles_t d_ServiceEntitles_dvtca[ENTITLE_COUNT_DVTCA];

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
extern hrdvtca_ippBuyInfo_t d_IppBuyInfo_dvtca;

//IPPV��Ŀ��Ϣ
extern hrdvtca_viewedIpp_t d_ViewedIPPV_dvtca[300];


/*--------------------------------Ǯ����Ϣ-----------------------------------------*/

//Ǯ������
extern uint8_t d_SlotCount;

//Ǯ��ID
extern uint8_t d_SlotID[20];

//��ֵ���
extern uint32_t ChargeValue;

extern hrdvtca_slotInfo_t  d_SlotInfo_dvtca[20];


/*-------------------------------��Ӫ����Ϣ--------------------------------------*/

//��Ӫ�̱��
extern uint16_t d_TVSId[5];

//��Ӫ������
extern uint8_t d_OperatorCount;

extern hrdvtca_operatorInfo_t d_OperatorInfo_dvtca[OPERATOR_COUNT_DVTCA]; 

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

//�ʼ�ͷ

extern hrdvtca_emailInfo_t d_EmailInfo_dvtca[EMAIL_COUNT_DVTCA];

//�ʼ�����

extern hrdvtca_emailContent_t d_EmailContent_dvtca;


#endif

