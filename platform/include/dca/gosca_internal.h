#ifndef _GOSCA_INTERNAL_H_
#define _GOSCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_GOSCA         6U

#define MAX_TASK_NUMBER_GOSCA         	5U

#define MAX_SEMA_NUMBER_GOSCA         	30U

#define MAXLEN_TVSNAME_GOSCA  		    24U

#define MAXLEN_PRODUCT_NAME_IPP_GOSCA   24U

#define MAXLEN_FEEDDATA_LEN_GOSCA 	    256U

#define MAXLEN_EMAIL_SENDERNAME_GOSCA   12U

#define MAXLEN_EMAIL_TITLE_GOSCA 		32U

#define MAXLEN_EMAIL_CONTENT_GOSCA 	    1025U

#define EMAIL_COUNT_GOSCA				20U

#define OPERATOR_COUNT_GOSCA			5U

#define ENTITLE_COUNT_GOSCA 			250U

#define ENTITLE_COUNT_PER_PAGE_GOSCA 	10U

#define IPP_COUNT_GOSCA 				250U

#define SLOTID_TOTAL_GOSCA            	20U

#define CA_INNO_LEN_GOSCA          		20U

#define CA_EXNO_LEN_GOSCA          		64U

#define CA_PCARD_LEN_GOSCA		 	    24U

#define CA_COREVER_LEN_GOSCA       		20U

#define CA_SWVER_LEN_GOSCA         		21U

#define CA_AERA_LEN_GOSCA          		12U

#define CA_RATING_LEN_GOSCA         	20U

#define CA_WORKTIME_LEN_GOSCA         	20U

#define CA_COS_LEN_GOSCA				4U

#define MAXLEN_PRODUCT_NAME_GOSCA 	    24U

#define MAXLEN_SERVICE_NAME_GOSCA 	    24U

#define MAXLEN_OSD_GOSCA   	    255U

#define MAX_OSD_NUM_GOSCA               10U

#define CHIPID_LEN_GOSCA		    6U

typedef enum
{
     MASTER_CARD,
     SLAVE_CARD,
     EXIT_MASTER_SLAVE
} Pair_Type;


typedef struct{
	uint8_t newEmail;  			//邮件状态，新邮件标记：0－已读邮件；1－新邮件
	char emaildate[40];                   //邮件日期、时间
    char emailtitle[CA_INNO_LEN_GOSCA];       //邮件标题
}hrgosca_emailInfo_t;								

typedef struct{
	char version[12];                        					//发送时间
	char emailLength[6];                     					//邮件内容长度
	int8_t	email[MAXLEN_EMAIL_CONTENT_GOSCA];        		//邮件内容
}hrgosca_emailContent_t;//GOSCA_V190

typedef struct{
   	char productId[5];     							//产品ID   (SCDCAEntitle.m_dwProductID for cdca)	
	char startTime[30];//huangbo 40    							//开始时间，time_t格式。 2012-05-07  09:12:34
	char endTime[30];  //huangbo 40					//结束时间，time_t格式。 2012-08-08  09:12:34
}hrgosca_serviceEntitles_t;//GOSCA_V190


//数码视讯没有反授权
typedef struct{
    uint8_t Detitle[2];
}hrgosca_detitleInfo_t;

typedef struct {
    uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
	uint8_t lock_flag; //强制切台后是否响应遥控器
}hrgosca_SwitchChannel_t;//huangbo 20130219

typedef struct {
	uint32_t price;     //  点/分钟
	uint32_t balance;   //余额  点
	uint32_t time;      //剩余时间
}hrgosca_ippBuyInfo_t;


typedef struct {
    uint8_t reserve;
}hrgosca_viewedIpp_t;



typedef struct {
    uint8_t scState;					//:智能卡已经插入；0：卡座无有效智能卡
    char scNo[CA_INNO_LEN_GOSCA];			  		//智能卡内部卡号
    char stbNo[CA_INNO_LEN_GOSCA];			//机顶盒序列号
    char scVer[CA_INNO_LEN_GOSCA];			//智能卡版本号;
    uint8_t isPinLocked;				//:智能卡被锁定，0：未被锁定
    char scRating[3];           			//智能卡观看级别
    char scWorktime[CA_WORKTIME_LEN_GOSCA];     	 	//智能卡工作时段
    char scMatureDays[CA_INNO_LEN_GOSCA];				//到期提示天数
    uint8_t ipptmode;				//IPPT模式
    char stbNo_v190[CA_INNO_LEN_GOSCA];		//机顶盒序列号,  V1.9版本的库或V2.08的库国内版本专用 
 //0永不使用；1换台选择使用(暂不支持）；2换台提示；3永远使用，换台不提示
    char chipID[CHIPID_LEN_GOSCA];				//芯片ID，一般是4个字节
}hrgosca_scBasicInfo_t;


typedef struct {
	
	char  scMasterCardID[CA_INNO_LEN_GOSCA];					//	母卡卡号
	char  scIntervaltime[CA_INNO_LEN_GOSCA];					//	配对间隔时间
	char  scRunArea[CA_INNO_LEN_GOSCA];						//	地区区号
	char  scUserAreaCode[CA_INNO_LEN_GOSCA];					//	用户区域码
	char   scUserVIPClass[CA_INNO_LEN_GOSCA];					//	用户级别
	char   scOperatorName[CA_INNO_LEN_GOSCA];					//	运营商名称
	char  scSTBAreaCode[CA_INNO_LEN_GOSCA];					//	机顶盒区域码
	uint8_t scardstate;//0 表示为子卡 1 表示为母卡
	
}hrgosca_operatorInfo_t;
typedef struct {
	
	char  scStbSeriesID[20];							//	机顶盒序列号
	char  scSmartcardID[20];							//	智能卡号
	char  scStbBindinfo[5][10];							//	机顶盒绑定信息
	char  scCardBindinfo[10];							//	卡绑定信息
}hrgosca_scBindInfo_t;//huangbo for STB

typedef struct {

    uint8_t scHour;          				//时
    uint8_t scMin;						//分
    uint8_t scSec;						//秒
    
}GOSTIME_SET;

typedef struct {

    uint8_t scRating;          				//智能卡观看级别
    uint8_t scMatureDays;				//到期提示天数
    GOSTIME_SET scStarttime;     	 	//智能卡开始工作时段
    GOSTIME_SET scEndtime;     	 		//智能卡结束工作时段
    uint8_t ipptmode;					//IPPT模式
	
}hrgosca_scCAOtherset_t;

typedef struct {
    uint8_t MesageNo;					//:提示消息号ID；

	uint32_t Message_ParaH;				//:提示消息参数H，根据消息ID有不同含义；
	uint32_t Message_ParaL;				//:提示消息参数L，根据消息ID有不同含义；

	uint8_t bShowNotify;				//:是否有自定义字符串提示；
    char Message_notify[1048];			//:自定义字符串提示内容；
}hrgosca_caMessage;

typedef struct {
    uint8_t scType;                           		//卡属性 0:母卡1:子卡
    char pCardNo[CA_PCARD_LEN_GOSCA];			  			//母卡卡号
    uint8_t scPscData[MAXLEN_FEEDDATA_LEN_GOSCA];   		//喂养数据
    uint8_t scDataLen;                        		//喂养数据长度
    
}hrgosca_scAddedInfo_t;

typedef struct {
	uint8_t slotId;
    char  slotCreditLimit[12];    					//信用度(点数) 
    char  balance[12];    							//已花的点数
}hrgosca_slotInfo_t;

typedef struct{
   	char productId[5];     							//产品ID   '0001'	
	char startTime[30];    							//开始时间'12/21/2012 09:12:34'
	char endTime[30];      						//结束时间'12/25/2012 23:59:59'
}hrgosca_Entitles_info_t;//GOSCA V208

typedef struct{
	char OsdMsg[CHIPID_LEN_GOSCA + 1];
	unsigned short times;
	char breakFlag;
}hrgosca_Osd_info_t;//huangbo 0326

typedef struct {
	uint16_t x;
	uint16_t y;	
}hrgosca_Point;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
}hrgosca_Rect;

typedef struct {
	uint8_t	region_no;	// 显示的区域OSD层号 	内部固定，改值不用传入																				
	hrgosca_Rect	bg_rect;	// 显示的范围，包括起始x坐标，起始Y坐标，宽度，高度				
	uint8_t	show_flag;	// 操作命令 0：擦除 1：显示																			

	uint8_t type;   		// osd type: 0: common 1: force
	uint8_t style;			//0: 滚动显示，1: 文本显示不带卡号，2：显示文本框带卡号
	uint8_t stylevalue;	 // style为0 ，本参数为1: 上方滚动， 2: 下方滚动，3:为中间滚动
				// style为1，本参数为设定文本框占屏幕的百分比，值为20%-80%
	uint8_t lock;
	uint32_t bg_color; 	// OSD bg color	  AGRB	 如0x80ffffff 为不透明白色
	hrgosca_Point fg_pos; 	// OSD fg pos	  显示字符的位置
	uint32_t fg_color; 	// OSD fg color	  AGRB
	uint8_t font_size; 	// osd fg font size 18~72
	char * text; 		// osd fg test point   显示内容指针
	uint16_t text_len; 		// osd fg test point   显示内容指针
	uint8_t repeat;		// 滚动条重复的次数
	uint8_t time;			// 滚动条滚动持续时间	  滚动osd时有效
}hrgosca_ForceOSD_info;

typedef struct {
	uint8_t	region_no;		// 显示的区域OSD层号 内部固定，改值不用传入																					
	hrgosca_Rect	bg_rect;		// 显示的范围，包括起始x坐标，起始Y坐标，宽度，高度				
	uint8_t	show_flag;		// 操作命令 0：擦除 1：显示	 前段发的命令																		

	uint8_t	type;   		//	fingerprint type: 0: common 1: force
	uint8_t	force_type; 	//	force fingerprint type: 0: not visible  1: show info
	uint32_t	bg_color; 	//	fingerprint bg color	  AGRB	如0x80ffffff 为不透明白色
//	D_Point fg_pos; 		//	fingerprint fg pos	  
	uint32_t	fg_color; 	//	fingerprint fg color	  AGRB
	uint8_t	font_size; 	//	osd fg font size 18~72
	uint8_t	text_type; 	//	低6位显示类型：（00：卡号；01：序列号；02卡号加序列号；0x03: 卡号+用户自定义内容, 0x04: 顶盒号+用户自定义内容, 0x05: 卡号+机顶盒号+用户自定义内容）
	char text[255]; 		//	fingerprint fg test point  要显示的字符串指针
	uint16_t	text_len; 	//	osd fg test point   显示内容指针
	uint8_t	chnl_cnt;	//	指纹显示频道数，如果为0 ，表示所有频道都显示指纹  非0，表示ServiceId参数service id数目，目前版本最大支持指定10个频道
	uint16_t service_id[10];	//	显示指纹频道的service id
	uint16_t	interval;		//	时间间隔,两次显示之间的不显示指纹的时间长度
	uint8_t	lock;		//	是否锁定用户操作 1: 锁定用户操作，0: 不锁定
	uint8_t	pos_type;	//	指纹位置类型，0 : 固定位置显示(通常在右上角），1: （用户自定义，按照Pos_X,Pos_Y进行坐标显示），2：随机
}hrgosca_ForceFinger_info;


//观看级别
extern uint8_t d_ViewRating;
//运营商信息
extern uint8_t d_OperatorCount;
//运营商编号
extern uint16_t d_TVSId[5];
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

#endif

