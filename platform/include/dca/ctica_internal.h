#ifndef _CTICA_INTERNAL_H
#define _CTICA_INTERNAL_H

#include "../../ca/ctica/include/ctiapi.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//---------------ȫ�ֱ���---------------


#define HRUSIFFUNCPOSTFIX

#define CTIMAX_TASK_NUMBER              9U

#define CA_MAX_PIN_LENGTH_CTICA       	4U

//----------------�ʼ�------------------
#define EMAIL_COUNT_CTICA  30
#define MAXLEN_EMAIL_SENDERNAME_CTICA 32
#define MAXLEN_EMAIL_SHORT_CONTENT_CTICA 256
#define MAXLEN_EMAIL_FROM_CONTENT_CTICA 256
#define MAXLEN_EMAIL_TITLE_CTICA 32
#define MAXLEN_EMAIL_CONTENT_CTICA 2048
//-----------------����-----------------


//----------------��Ӫ��------------------
#define OPERATOR_COUNT_CTICA     8
#define MAXLEN_TVSNAME_CTICA 24
#define ENTITLE_COUNT_CTICA         300U
//-----------------����-----------------

//----------------IPPV------------------
#define IPP_COUNT_CTICA 					250U

#define MAXLEN_PRODUCT_NAME_IPP_CTICA 300

//----------------����-------------------


//----------------reply------------------

typedef struct{
	uint8_t checkPinQueryReplyValue;
	uint8_t changePinQueryReplyValue;
	uint8_t ippvNotifyValue;
	uint8_t ippvQueryReplyValue;
	uint8_t scBasicInfoReplayValue;
	uint8_t ppidQueryReplyValue;
	uint8_t ppidInfoQueryReplyValue;
	uint8_t ppvListInfoQueryReplyValue;
	uint8_t ippvListInfoQueryReplyValue;
	uint8_t setParentalQueryReplyValue;
	uint8_t userViewQueryReplyValue;	
	
	uint16_t checkPinQueryReplyFlag;
	uint16_t changePinQueryReplyFlag;
	uint16_t ippvQueryReplyFlag;
	uint16_t scBasicInfoReplayFlag;
	uint16_t ppidQueryReplyFlag;
	uint16_t ppidInfoQueryReplyFlag;
	uint16_t ppvListInfoQueryReplyFlag;
	uint16_t ippvListInfoQueryReplyFlag;
	uint16_t setParentalQueryReplyFlag;
	uint16_t userViewQueryReplyFlag;
}hrctica_replyFalg_t;

//----------------����-------------------


typedef struct{
    uint8_t importance; 						//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;  							//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
    char createtime[40];  						//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
	char title_context[MAXLEN_EMAIL_SHORT_CONTENT_CTICA]; //�ʼ�������
	char from_context[MAXLEN_EMAIL_FROM_CONTENT_CTICA];	//��Դ
}hrctica_emailInfo_t;


typedef struct{
	uint8_t version[12];  						//����ʱ��
	uint8_t emailLength[6]; 					//�ʼ����ݳ���
	char email[MAXLEN_EMAIL_CONTENT_CTICA];           //�ʼ�����
	uint8_t reserved[6];  						//����
}hrctica_emailContent_t;


typedef struct{
	uint8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];
	uint8_t provName[MAXLEN_TVSNAME_CTICA];
	uint8_t id[3];
	char label[17];
	uint8_t usedstatus;
	uint8_t credit_deposit[4];
	char credit_date[11];
	uint8_t prog_right[65];
	char prog_right_start_date[11];
	char prog_right_end_date[11];
}hrctica_operatorInfo_t;


  typedef struct{
	uint8_t id[3];
	char label[17];
	uint8_t usedstatus;
	uint8_t credit_deposit[4];
	char credit_date[11];
	uint8_t prog_right[65];
	char prog_right_start_date[11];
	char prog_right_end_date[11];
}hrctica_serviceEntitles_t;


typedef struct{
    uint8_t newDetitle;     					//����Ȩ��ǣ�0��δ����1���Ѷ�
    uint8_t Detitle[12];    					//����Ȩ
}hrctica_detitleInfo_t;


typedef struct{
	uint8_t ippvBuyFlag;						//��־��P(==8)���߰�T(==1)����,���ڷ�װ�����Ϳ�
	uint8_t ippvProgNum[4];						//Ƶ����,���ڷ�װ�����Ϳ�
	int8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];			//����
	uint8_t isIppv;
	uint8_t isIppt;
	char operatorId[10];
	char operatorLabel[17];
	char ippvPrice[13];                        //��λ:Ԫ/��Ŀ
	char ipptPrice[13];                        //��λ:Ԫ/����
}hrctica_ippBuyInfo_t;


typedef struct{
	uint8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];
	uint8_t isPpv;
	uint8_t isIppv;
	uint8_t ppvListPage;						
	int8_t	ppvProgCount;
	char ppvStartProgNumber[256][4];
	char ppvEndProgNumber[256][4];    
	char ippvListPage;
	char ippvProgCount;
	char ippvProgNumber[32][4];
}hrctica_viewedIpp_t;	


typedef struct{
	char cardnumber[8];    //cardnumber[22]
    uint8_t scstatus;    //scstatusstatus�����ܿ���ǰ״̬
						//. ��0�������ܿ�״̬��ȷ
						//. ��1����δ�������ܿ�
						//. ��2�������ܿ�Ӳ������
						//. ��4�������ܿ��������
						//. ��6�����ӿ���֤ʧ��
						//. ��7�����ӿ���֤�ɹ�
						//. ��8����ĸ����֤ʧ��
    uint8_t usedstatus;    //usedstatus0�����ܿ���Ч��1�����ܿ���ͣ��2�����ܿ���ȡ����
    uint8_t systemid[2];    //CAϵͳ��ʶ
    uint8_t ecmsubsysid[2];    //ECM��ϵͳ��ʶ
    uint8_t emmsubsysid[2];    //EMM��ϵͳ��ʶ
    char cosversion[9];    //���ܿ��İ汾��
    char cardlabel[17];    //���ܿ�����������
    char issuetime[17];    //����ʱ��
    char expiretime[17];    //���ܿ���Ч�ڽ�ֹʱ��
    uint8_t parentalrating;    //���ܿ���ĸ�����Ƽ���0�������ƣ�4~18Ϊ����
    uint8_t groupcontrol;    //��Ŀ�����������ƴ���
    uint8_t antimovectrl[3];    //������ƴ��룬3�ֽ�����
    uint8_t smartcard_type;    //0�����ܿ�Ϊĸ����1�����ܿ�Ϊ�ӿ���2�����ܿ����ʹ���
    uint8_t smartcard_matching;    //���ܿ����״̬
    //��0�������ܿ�δ���
	//. ��1�������ܿ������
	//. ��5�������ܿ�δע��STB Number
	//. ��7�������ܿ���STB��ƥ��
    uint8_t stb_ird_matching;    //���������״̬
	//. ��2����STBδ���
	//. ��3����STB�����
	//. ��6����STBδע��STB Number
}hrctica_scBasicInfo_t;


  typedef struct{
	uint8_t cardstatus;
	char childCardInfoVerifyStartTime[8];    //�ӿ���֤ʱ��
    char childCardInfoWorkPeriod[2];         //�ӿ���������
    char childCardInfoMotherUa[5];     	 	//�ӿ�����ĸ��UA
    char caCoreVersion[30];					//CA�ں˰汾
	uint8_t securityInfo_id_len;    	  	 	//id_len
    uint8_t securityInfo_stb_id[16];     	   //stb_id[16]
    uint8_t securityInfo_sc_id[16];     	  //sc_id[16]
}hrctica_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    uint8_t slotCreditLimit[12];    //���ö�(����) 
    uint8_t balance[12];    		//�ѻ��ĵ���
}hrctica_slotInfo_t;


typedef struct{
	uint8_t id[3];				//PPID
	uint8_t password[4];		//����
}hrctica_ppidDetailInfo_t;		//������Ȩ��Ϣ�˵�����ĳһPPID��Ŀ


typedef struct{
	int8_t ppv_start_prog_number[12];
	int8_t ppv_end_prog_number[12];
}hrctica_ppvRecord_t;


typedef struct {
	int8_t ppv_list_page[9];						//ҳ��(��λu8��ת���ַ�����Ҫ9λ����)
	int8_t ppv_prog_count[9];						//PPV����
	hrctica_ppvRecord_t ppv_record[32];	
}hrctica_ipp_t;								//ppv�б���ʾ�淶�ַ����ṹ��
//------------------------

 typedef struct
{
    int8_t ippv_prog_number[12];
}hrctica_ippRecord_t;

typedef struct {
	int8_t ippv_list_page[3];					//ҳ��
	int8_t ippv_prog_count[3];					//��Ŀ����
	hrctica_ippRecord_t ippv_record[32];			//��Ŀ��
}hrctica_ippv_t;									//ippv�б���ʾ�淶�ַ����ṹ��

//--------------------


typedef struct
{
	uint8_t count;
	hrctica_operatorInfo_t info[MAX_PPID_NUM];
}hrctica_operator_t;//  ������CTI_PPidNotify_t;��������


//-------------------------------------

typedef struct
{
	uint8_t email_status; //email��״̬��0:�Ѷ���1:δ��
	CTI_CABmailInfo_t email_info; //email����Ϣ
}hrctica_email_t; //  �˽ṹ�����ڴ洢emailʹ��


typedef struct {
    uint16_t LockSerID;
	uint16_t LockNetworkID;
	uint16_t LockTSID;
	uint16_t LockFre;
	uint16_t LockMode;
	uint16_t LockSymbol;
}hrctica_SwitchChannel_t;

extern uint32_t StreamNum;
extern uint8_t StreamFlag;
extern hrctica_viewedIpp_t d_ViewedIPPV_ctica;
extern hrctica_ippBuyInfo_t d_IppBuyInfo_ctica;
//�ۿ�����
extern uint8_t d_ViewRating;
//��Ӫ����Ϣ
extern uint8_t d_OperatorCount;
//��Ӫ�̱��
extern uint16_t d_TVSId[5];
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

extern uint32_t ctiTaskIdTable[CTIMAX_TASK_NUMBER];

#endif

