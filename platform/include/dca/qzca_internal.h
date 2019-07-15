#ifndef QZCA_INTERNAL_H_
#define QZCA_INTERNAL_H_

#include <stdint.h>

//#define CA_MAX_PIN_LENGTH       6U  //Ϊ�˱���ͨ����ʵ�ʵ���ֵ�д�ȷ?

//�ʼ�
#define EMAIL_COUNT 				50
#define QZCA_MAXLEN_EMAIL_CONTENT 		1024
#define QZCA_MAXLEN_EMAIL_SENDERNAME 	256
#define QZCA_MAXLEN_EMAIL_TITLE	 		256
//����Ϣ������
#define QZCA_MAXLEN_SHORT_MSG			1024
//reserve
//#define OPERATOR_COUNT				1
//#define ENTITLE_COUNT				1


//�ʼ�ͷ
typedef struct{
	uint32_t     actionId;								//Email id
    uint8_t      newEmail;  							//״̬��0���Ѷ��ʼ���1�����ʼ�
    char		 createtime[24];  	    				//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
    char     	 senderName[QZCA_MAXLEN_EMAIL_SENDERNAME];   //��Ϣ���������� 
	char         title[QZCA_MAXLEN_EMAIL_TITLE]; 			//����
}hrqzca_emailInfo_t;

//�ʼ�����
typedef struct{
	char        email[QZCA_MAXLEN_EMAIL_CONTENT];           //��Ϣ����
}hrqzca_emailContent_t;

//�ʼ����������ʼ���
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hrqzca_emailGeneral;

//�洢�ʼ��õĽṹ��
typedef struct{
	hrqzca_emailInfo_t	email_head;							//�ʼ�ͷ
	hrqzca_emailContent_t email_content;						//�ʼ�����
}QZemail;

//emm�����ʼ��Ľṹ
typedef struct
{
	uint8_t mail_id;
	uint8_t year_high_byte;
	uint8_t year_low_byte;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t sender_length;									//������
	uint8_t sender[QZCA_MAXLEN_EMAIL_SENDERNAME];
	uint8_t caption_length;									//����
	uint8_t caption[QZCA_MAXLEN_EMAIL_TITLE];
	uint8_t content_length;									//����
	uint8_t content[QZCA_MAXLEN_EMAIL_CONTENT];
}emm_email;

//���ܿ�
typedef struct
{
	char    system_id[8];		                            //ϵͳid
	char    sub_system_id[8];								//��ϵͳid
	char    smart_card_number[8];							//����
	uint8_t date[30];										//����
}hrqzca_scBasicInfo_t;

//-----------------���½ṹ����ʱδʹ��---------------------

//����Ǯ��
typedef struct
{
	uint8_t reserve;

}hrqzca_slotInfo_t;

//��Ӫ����Ϣ
typedef struct{	

	uint8_t reserve;

}hrqzca_operatorInfo_t; 

typedef struct
{
	uint8_t reserve;

}hrqzca_scAddedInfo_t;

//IPP��Ȩ��Ϣ
typedef struct
{
	uint8_t reserve;

}hrqzca_viewedIpp_t;	

//IPP���������
typedef struct
{
	uint8_t reserve;

}hrqzca_ippBuyInfo_t;

//��Ȩ��Ϣ
typedef struct
{
	uint8_t reserve;

}hrqzca_serviceEntitles_t;

//����Ȩ
typedef struct
{
	uint8_t reserve;

}hrqzca_detitleInfo_t;

typedef struct {
	uint8_t reserve;
}hrqzca_SwitchChannel_t;

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

#endif

