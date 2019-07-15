#ifndef SCCA_FUNCTION_H
#define SCCA_FUNCTION_H

#include <stdint.h>

#define SCCA_EMAIL_COUNT  50
#define SCCA_MAX_SEMA_NUMBER 10
#define SCCA_MAX_QUE_NUMBER 10
#define SCCA_MAX_ENTITLE    100

//���ܿ���Ϣ
typedef struct
{
    uint8_t cardNo[24];
    uint8_t cardType;
    uint8_t cardStatus;
    uint8_t cardVer[32];
    uint8_t cardAddrCode[34];
    uint8_t CAVer[26];
}hrscca_cardInfo_t;

typedef struct {
	uint8_t unused;
}hrscca_scAddedInfo_t;

//��Ӫ������
typedef struct
{
	uint8_t operatorName[40];
	uint8_t operatorPhone[40];
	uint8_t operatorAddress[80];
    uint8_t operatorID[4];
}hrscca_operatorInfo_t;

//��Ʒ��Ȩ��Ϣ
typedef struct
{
	uint8_t			    enableType[2];		/*��Ȩģʽ*/
	uint8_t          	recoadFlag[2];		/* ��û���� ��0��������¼�� 1������¼��*/
	uint8_t        	    productID[12];		/* ��ƷID */
	uint8_t 	        beginTime[20];		/* ��Ʒ��ʼʱ��*/
	uint8_t 	        endTime[20];		/* ��Ʒ����ʱ��*/
	uint8_t			    ucProductName[30];
}hrscca_serviceEntitles_t;

//Ǯ����Ϣ
typedef struct
{
    uint8_t purseID[4];
    uint8_t balance[26];
}hrscca_slotInfo_t;

//Ǯ�����
typedef struct
{
    uint8_t purse1[10];
    uint8_t purse2[10];
    uint8_t purse3[10];
    uint8_t purse4[10];
}hrscca_slotIndex_t;


//�ʼ�����
typedef struct
{
    uint8_t actionId;  				//Email ID
    uint8_t newEmail;  				//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	uint8_t title[33]; 				//�ʼ�����
	uint8_t sender[33];  			//������
    uint8_t sendTime[20];           //����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
}hrscca_emailInfo_t;								

//�ʼ�����
typedef struct
{
	uint16_t emailLength; 							//�ʼ����ݳ���
	uint8_t  email[1024]; 			//�ʼ�����
}hrscca_emailContent_t;							

//ippv
typedef struct
{
    uint8_t ppvname[33];
    uint8_t eventID[4];
    uint8_t providerID[8];
	uint16_t providerID_num;
    uint8_t price[12];
    uint8_t ecmPID[8];
    uint8_t beginTime[24];
    uint8_t endTime[24];
}hrscca_ippBuyInfo_t;

typedef struct
{
	uint8_t unused;
}hrscca_viewedIpp_t;





#endif //SCCA_FUNCTION_H
