#ifndef _YJCA_INTERNAL_H
#define _YJCA_INTERNAL_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//---------------全局变量---------------

#define EMAIL_COUNT_YJCA   30
#define AUTHOR_COUNT_YJCA  64


//邮件头
typedef struct{
	uint16_t     emailId;								//Email id
    uint8_t      newEmail;  							//状态：0－已读邮件；1－新邮件
    char		 createtime[24];  	    				//发送时间
	char         title[21]; 			//标题
}hryjca_emailInfo_t;

//邮件内容
typedef struct{
	char        email[1024+1];           //消息内容
}hryjca_emailContent_t;

//邮件总数和新邮件数
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hryjca_emailGeneral;

//存储邮件用的结构体
typedef struct{
	hryjca_emailInfo_t	email_head;				//邮件头
	hryjca_emailContent_t email_content;		//邮件内容
}YJemail;

//授权
typedef struct{
    char        proid[12];  					//产品编号
	char        autortime[30];    				//授权时间
} hryjca_serviceEntitles_t;							

//智能卡
typedef struct
{
    char    smart_card_number[22];			//卡号
	char    user_id[20];		            //用户号
	char    device_id[22];                  //机器编号
	char    card_match_id[22];				//卡绑定号
}hryjca_scBasicInfo_t;

//子母卡
typedef struct {
	uint8_t pbyIsChild;						//是否是子卡
	char pDelayTime[4];				    	//喂养周期
	char pLastFeedTime[40];					//上次喂养时间
	char parentCardSN[22];     		        //母卡id
}hryjca_scAddedInfo_t;


//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

//购买的节目总数
extern uint8_t d_ServiceCount;



#endif

