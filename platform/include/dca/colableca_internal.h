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
	uint16_t length;//后续长度
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
	uint8_t   newflag;//  1 新邮件  0 旧邮件
	uint16_t  mail_id;
	//uint16_t length;//后续长度
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
	uint8_t CARD_LABEL[10];		//运营商
	uint8_t CAM_VER[4];			//CAS版本
	uint8_t CARD_STATUS[6];		//智能卡状态
	uint8_t PAIR_STATUS[6];		//配对状态
	uint8_t PARENTAL_RATING[6];	//成人级别
	uint8_t IC_NO[12];			//智能卡卡号
	uint8_t OPERATION_ID[8];	//运营商ID
}hcn_cardInfo_t;

typedef struct
{
	uint8_t provider_id[6];		//运营商钱包ID
	uint8_t credit[12];			//信誉点数
	uint8_t consume[12];		//消费点数
}hcn_purse_t;

typedef struct
{
	uint8_t entitle_id[4];
	uint8_t start_time[20];
	uint8_t end_time[20];
}hcn_entitle_t;


typedef struct
{
	uint8_t providerid[6];	//节目运营商ID
	uint8_t ippeventid[4];	//节目事件号
	uint8_t tokenprice[6];		//订购价格，点数表示
	uint8_t overtime[20];		//本次时间结束时间
}hcn_ipptv_t;



#endif
