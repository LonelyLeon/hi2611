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
    char scno[10];                                              //卡号
    uint8_t entitle;                                            //授权状态
    uint16_t areaID;                                         //网络ID号
}hrxsmca_scBasicInfo_t;

typedef struct{
    uint16_t emailID;  							//Email ID
    uint8_t importance; 							//重要性： 0－普通，1－重要 
    uint8_t newEmail;  								//新邮件标记：0－已读邮件；1－新邮件
	char title[EMAIL_TITLE_LEN_XSMCA]; 				//邮件短内容
	char createtime[40];  							//发送时间，格式为:2000-02-01 09:10:10
}hrxsmca_emailInfo_t;							


typedef struct{
    char title[EMAIL_TITLE_LEN_XSMCA]; 				//邮件短内容
	char email[EMAIL_CONTENT_LEN_XSMCA]; 				//邮件内容
}hrxsmca_emailContent_t;				




/*-------------------------------邮件信息-----------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;


#endif


