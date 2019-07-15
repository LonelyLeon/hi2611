#ifndef HCN_INTERNAL_H
#define HCN_INTERNAL_H

#include "stdint.h"

#define HCN_MAX_SEMA_NUMBER  15
#define HCN_MAX_QUE_NUMBER   15
#define HCN_QUE_MSG_SIZE 	 256
#define HCN_QUE_MSG_COUNT    20
#define HCN_MAX_EMAIL		 15
#define HCN_MAX_ENTITLE		 50

/*typedef struct{
	uint8_t  reserve1;	
	uint16_t mail_id;
	uint16_t length;//��������
	//uint32_t reserve2;
	uint8_t  mail_header_len;
	uint8_t  mail_header[40];
	uint16_t mail_content_len;
	uint8_t  mail_content[1024];
	uint8_t  mail_tail_len;
	uint8_t  mail_tail[20];
}hcn_get_mail_t;
*/
typedef struct{
	uint8_t   newflag;//  1 ���ʼ�  0 ���ʼ�
	uint16_t  mail_id;
	//uint16_t length;//��������
	//uint8_t  mail_header_len;
	uint8_t  mail_header[255+1];
	//uint16_t mail_content_len;
	uint8_t  mail_content[1024+1];
	//uint8_t  mail_tail_len;
	uint8_t  mail_tail[20+1];
}hcn_mail_t;

typedef struct{
	uint8_t newflag;
	uint16_t mail_id;
	uint8_t mail_header[255+1];
}hcn_mail_head;


typedef struct{
	uint8_t mail_content[1024+1];
	uint8_t mail_tail[20+1];
}hcn_mail_content;

typedef struct{
	uint8_t CARD_LABEL[10];		//��Ӫ��
	uint8_t CAM_VER[4];			//CAS�汾
	uint8_t CARD_STATUS[6];		//���ܿ�״̬
	uint8_t PAIR_STATUS[6];		//���״̬
	uint8_t PARENTAL_RATING[6];	//���˼���
	uint8_t IC_NO[12];			//���ܿ�����
	uint8_t OPERATION_ID[8];	//��Ӫ��ID
}hcn_cardInfo_t;

typedef struct
{
	uint8_t provider_id[6];		//��Ӫ��Ǯ��ID
	uint8_t credit[12];			//��������
	uint8_t consume[12];		//���ѵ���
}hcn_purse_t;

typedef struct
{
	uint8_t entitle_id[4];
	uint8_t start_time[20];
	uint8_t end_time[20];
}hcn_entitle_t;


typedef struct
{
	uint8_t providerid[6];	//��Ŀ��Ӫ��ID
	uint8_t ippeventid[4];	//��Ŀ�¼���
	uint8_t tokenprice[6];		//�����۸񣬵�����ʾ
	uint8_t overtime[20];		//����ʱ�����ʱ��
}hcn_ipptv_t;



#endif
