#ifndef QZCA_INTERNAL_H_
#define QZCA_INTERNAL_H_

#include <stdint.h>

//#define CA_MAX_PIN_LENGTH       6U  //为了编译通过，实际的数值有待确?

//邮件
#define EMAIL_COUNT 				50
#define QZCA_MAXLEN_EMAIL_CONTENT 		1024
#define QZCA_MAXLEN_EMAIL_SENDERNAME 	256
#define QZCA_MAXLEN_EMAIL_TITLE	 		256
//短消息滚动条
#define QZCA_MAXLEN_SHORT_MSG			1024
//reserve
//#define OPERATOR_COUNT				1
//#define ENTITLE_COUNT				1


//邮件头
typedef struct{
	uint32_t     actionId;								//Email id
    uint8_t      newEmail;  							//状态：0－已读邮件；1－新邮件
    char		 createtime[24];  	    				//发送时间，格式为:2000-02-01 09:10:10
    char     	 senderName[QZCA_MAXLEN_EMAIL_SENDERNAME];   //消息发送者名称 
	char         title[QZCA_MAXLEN_EMAIL_TITLE]; 			//标题
}hrqzca_emailInfo_t;

//邮件内容
typedef struct{
	char        email[QZCA_MAXLEN_EMAIL_CONTENT];           //消息内容
}hrqzca_emailContent_t;

//邮件总数和新邮件数
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hrqzca_emailGeneral;

//存储邮件用的结构体
typedef struct{
	hrqzca_emailInfo_t	email_head;							//邮件头
	hrqzca_emailContent_t email_content;						//邮件内容
}QZemail;

//emm表中邮件的结构
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
	uint8_t sender_length;									//发件人
	uint8_t sender[QZCA_MAXLEN_EMAIL_SENDERNAME];
	uint8_t caption_length;									//标题
	uint8_t caption[QZCA_MAXLEN_EMAIL_TITLE];
	uint8_t content_length;									//内容
	uint8_t content[QZCA_MAXLEN_EMAIL_CONTENT];
}emm_email;

//智能卡
typedef struct
{
	char    system_id[8];		                            //系统id
	char    sub_system_id[8];								//子系统id
	char    smart_card_number[8];							//卡号
	uint8_t date[30];										//日期
}hrqzca_scBasicInfo_t;

//-----------------以下结构体暂时未使用---------------------

//电子钱包
typedef struct
{
	uint8_t reserve;

}hrqzca_slotInfo_t;

//运营商信息
typedef struct{	

	uint8_t reserve;

}hrqzca_operatorInfo_t; 

typedef struct
{
	uint8_t reserve;

}hrqzca_scAddedInfo_t;

//IPP授权信息
typedef struct
{
	uint8_t reserve;

}hrqzca_viewedIpp_t;	

//IPP弹出购买框
typedef struct
{
	uint8_t reserve;

}hrqzca_ippBuyInfo_t;

//授权信息
typedef struct
{
	uint8_t reserve;

}hrqzca_serviceEntitles_t;

//反授权
typedef struct
{
	uint8_t reserve;

}hrqzca_detitleInfo_t;

typedef struct {
	uint8_t reserve;
}hrqzca_SwitchChannel_t;

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

#endif

