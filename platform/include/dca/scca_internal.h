#ifndef SCCA_FUNCTION_H
#define SCCA_FUNCTION_H

#include <stdint.h>

#define SCCA_EMAIL_COUNT  50
#define SCCA_MAX_SEMA_NUMBER 10
#define SCCA_MAX_QUE_NUMBER 10
#define SCCA_MAX_ENTITLE    100

//智能卡信息
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

//运营商信心
typedef struct
{
	uint8_t operatorName[40];
	uint8_t operatorPhone[40];
	uint8_t operatorAddress[80];
    uint8_t operatorID[4];
}hrscca_operatorInfo_t;

//产品授权信息
typedef struct
{
	uint8_t			    enableType[2];		/*授权模式*/
	uint8_t          	recoadFlag[2];		/* 暂没有用 ，0：不可以录像 1：可以录像*/
	uint8_t        	    productID[12];		/* 产品ID */
	uint8_t 	        beginTime[20];		/* 产品起始时间*/
	uint8_t 	        endTime[20];		/* 产品结束时间*/
	uint8_t			    ucProductName[30];
}hrscca_serviceEntitles_t;

//钱包信息
typedef struct
{
    uint8_t purseID[4];
    uint8_t balance[26];
}hrscca_slotInfo_t;

//钱包序号
typedef struct
{
    uint8_t purse1[10];
    uint8_t purse2[10];
    uint8_t purse3[10];
    uint8_t purse4[10];
}hrscca_slotIndex_t;


//邮件标题
typedef struct
{
    uint8_t actionId;  				//Email ID
    uint8_t newEmail;  				//新邮件标记：0－已读邮件；1－新邮件
	uint8_t title[33]; 				//邮件标题
	uint8_t sender[33];  			//发信人
    uint8_t sendTime[20];           //发送时间，格式为:2000-02-01 09:10:10
}hrscca_emailInfo_t;								

//邮件内容
typedef struct
{
	uint16_t emailLength; 							//邮件内容长度
	uint8_t  email[1024]; 			//邮件内容
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
