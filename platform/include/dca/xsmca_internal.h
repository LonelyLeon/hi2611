#ifndef _XSMCA_INTERNAL_H_
#define _XSMCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>



#define MAX_QUEUE_CNT_XSMCA             10
#define MAX_SEMA_COUNT_XSMCA            20

#define MAX_OSD_LEN_XSMCA               250

#define MAX_EMAIL_NUM_XSMCA             10
#define EMAIL_TITLE_LEN_XSMCA           40
#define EMAIL_CONTENT_LEN_XSMCA         130



typedef struct {
    char scno[10];                                              //����
    uint8_t entitle;                                            //��Ȩ״̬
    uint16_t areaID;                                         //����ID��
}hrxsmca_scBasicInfo_t;

typedef struct{
    uint16_t emailID;  							//Email ID
    uint8_t importance; 							//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;  								//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	char title[EMAIL_TITLE_LEN_XSMCA]; 				//�ʼ�������
	char createtime[40];  							//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
}hrxsmca_emailInfo_t;							


typedef struct{
    char title[EMAIL_TITLE_LEN_XSMCA]; 				//�ʼ�������
	char email[EMAIL_CONTENT_LEN_XSMCA]; 				//�ʼ�����
}hrxsmca_emailContent_t;				




/*-------------------------------�ʼ���Ϣ-----------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;


#endif


