#ifndef _YJCA_INTERNAL_H
#define _YJCA_INTERNAL_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//---------------ȫ�ֱ���---------------

#define EMAIL_COUNT_YJCA   30
#define AUTHOR_COUNT_YJCA  64


//�ʼ�ͷ
typedef struct{
	uint16_t     emailId;								//Email id
    uint8_t      newEmail;  							//״̬��0���Ѷ��ʼ���1�����ʼ�
    char		 createtime[24];  	    				//����ʱ��
	char         title[21]; 			//����
}hryjca_emailInfo_t;

//�ʼ�����
typedef struct{
	char        email[1024+1];           //��Ϣ����
}hryjca_emailContent_t;

//�ʼ����������ʼ���
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hryjca_emailGeneral;

//�洢�ʼ��õĽṹ��
typedef struct{
	hryjca_emailInfo_t	email_head;				//�ʼ�ͷ
	hryjca_emailContent_t email_content;		//�ʼ�����
}YJemail;

//��Ȩ
typedef struct{
    char        proid[12];  					//��Ʒ���
	char        autortime[30];    				//��Ȩʱ��
} hryjca_serviceEntitles_t;							

//���ܿ�
typedef struct
{
    char    smart_card_number[22];			//����
	char    user_id[20];		            //�û���
	char    device_id[22];                  //�������
	char    card_match_id[22];				//���󶨺�
}hryjca_scBasicInfo_t;

//��ĸ��
typedef struct {
	uint8_t pbyIsChild;						//�Ƿ����ӿ�
	char pDelayTime[4];				    	//ι������
	char pLastFeedTime[40];					//�ϴ�ι��ʱ��
	char parentCardSN[22];     		        //ĸ��id
}hryjca_scAddedInfo_t;


//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;



#endif

