/** @file
* @brief CA模块
* @author 龚克
* @date 2005-9-8 龚克: 建立文件
*/

#ifndef _D_CA_H_
#define _D_CA_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dQueue.h"
#include "dDBase.h"
#include "dScroll.h"

#define FINGER_LABEL_BUF_LEN 64
#define MAX_OSD_NUM 6
#define MAX_OSD_LEN 2048

/** @brief CA系统TS流分析参数*/
typedef struct {
	D_DBTSID    db_ts_id;	/**< 要分析的TS流数据库记录ID*/
	D_ID		fend_id;    /**< 对应前端设备ID*/
} D_CATSParam;

/** @brief CA系统服务分析参数*/
typedef struct {
	D_DBSrvID db_srv_id;    /**< 要分析的服务数据库记录ID*/
	D_ID	  fend_id;		/**< 对应前端设备ID*/
} D_CASrvParam;

/** @brief CA加扰信息*/
typedef struct {
	D_U16		srv_id;     //srvid
    D_U16		pcr_pid;    //pcrid
    D_U16		vid_pid;    //视频id
    D_U16		aud1_pid;   //音频1id
    D_U16		aud2_pid;   //音频2id
    D_U16 		pmt_pid;    //pmtid
} D_CASrvInfo;

/**< @brief CA事件类型*/
typedef enum {
	D_CA_EVT_SC_IN,		        //智能卡插入
	D_CA_EVT_SC_OUT,	        //智能卡拔出
	
	D_CA_EVT_SHOWBUYMSG,        //ca提示信息事件
	
	D_CA_EVT_FINGERMSG,	        //指纹显示
	D_CA_EVT_HIDE_FINGERMSG,	//隐藏指纹显示
	
	D_CA_EVT_SHOWTOPOSDMSG,		//显示顶部滚动条
	D_CA_EVT_SHOWBOTTOMMSG,   	//显示底部滚动条
	D_CA_EVT_HIDETOPOSDMSG,		//隐藏顶部滚动条
	D_CA_EVT_HIDEBOTTOMOSDMSG,	//隐藏底部滚动条
	
	D_CA_EVT_EMAILNOTIFY,		//显示电子邮件
	D_CA_EVT_FULL_EMAILNOTIFY,  //邮箱已满
    D_CA_EVT_HIDE_EMAILNOTIFY,  //隐藏电子邮件
    
    D_CA_EVT_DETITLENOTIFY,		//显示反授权图标
	D_CA_EVT_FULL_DETITLENOTIFY,//反授权已满图标
    D_CA_EVT_HIDE_DETITLENOTIFY,//隐藏反授权图标
    
    D_CA_SHOW_SUPERLOOK_NOTE,   //显示高级预览
    D_CA_HIDE_SUPERLOOK_NOTE,   //隐藏高级预览
    
	D_CA_EVT_SHOWIPPVDLG,		//显示ippv	
	D_CA_EVT_HIDEIPPVDLG,		//隐藏ippv
	
    D_CA_EVT_PROGRESS,          //显示进度条
    D_CA_EVT_HIDE_PROGRESS,     //隐藏进度条
    
    D_CA_EVT_URGENCY_BRCAST,            //应急广播
    D_CA_EVT_URGENCY_BRCAST_CANCEL,     //取消应急广播
    
    D_CA_EVT_SHOW_SUPER_OSD,    //显示超级OSD
    D_CA_EVT_HIDE_SUPER_OSD,    //掩藏超级OSD
    
	D_CA_EVT_SHOWIPPVICON,		//显示ippv图标
    D_CA_EVT_SHOWIPPTICON,		//显示ippt图标
	D_CA_EVT_HIDEIPPVICON,		//隐藏ippv图标

	D_CA_EVT_SHOW_PREAUTH_ICON,	//显示预览图标
	D_CA_EVT_HIDE_PREAUTH_ICON,	//隐藏预览图标

	D_CA_EVT_SHOW_AUTH_REMAINDLG,//显示授权剩余xx天
	D_CA_EVT_HIDE_AUTH_REMAINDLG,//隐藏授权剩余xx天

	D_CA_EVT_SHOW_PURSEDLG,		//显示钱包充值金额提醒
	D_CA_EVT_HIDE_PURSEDLG,     //隐藏钱包充值金额提醒

	D_CA_EVT_SHOW_EXPIRDLG,		//显示节目过期提醒
	D_CA_EVT_HIDE_EXPIRDLG,		//隐藏节目过期提醒
	
	D_CA_EVT_SHOW_NORMAL_FINGER, //显示普通指纹
	D_CA_EVT_HIDE_NORMAL_FINGER, //隐藏普通指纹

	D_CA_EVT_SHOW_URGENCY_ICON, //应急广播提示图标
	D_CA_EVT_HIDE_URGENCY_ICON, //隐藏应急广播提示图标
    	
	D_CA_EVT_SHOW_SENIOR_PREVIEW, //显示高级预览		
	D_CA_EVT_HIDE_SENIOR_PREVIEW, //掩藏高级预览

    D_CA_EVT_SHOW_TIP_ANNOUN,    //显示全屏公告
	D_CA_EVT_HIDE_TIP_ANNOUN,    //掩藏全屏公告(目前20131018仅换台调用)

	D_CA_EVT_SHOW_PARENTALCTRL,  //显示父母锁控制
	D_CA_EVT_HIDE_PARENTALCTRL,  //掩藏父母锁控制

        D_CA_EVT_SHOW_INTERVAL_SCROLL, //显示间隔滚动条
	D_CA_EVT_HIDE_INTERVAL_SCROLL, //掩藏间隔滚动条

	D_CA_EVT_SHOW_AUTO_FEED,     //自动子母卡配对
	D_CA_EVT_HIDE_AUTO_FEED,     //隐藏子母卡配对

    D_CA_EVT_SHOW_PAIR,          //自动机卡配对
    D_CA_EVT_HIDE_PAIR,          //掩藏机卡配对

	D_CA_EVT_SHOW_SKIP_SELECT,   //显示节目跳转提示
	D_CA_EVT_HIDE_SKIP_SELECT,   //隐藏节目跳转提示
	D_CA_EVT_RESHOW,             //刷新当前菜单
    
	D_CA_EVT_SWITCH_CA,          //切换CA
	
	D_CA_EVT_TIMING_SHOWBUYMSG,  //CA提示消息定时消失事件
    D_CA_EVT_FLASH_SHOWBUYMSG,   //CA提示信息闪烁(显示和消失次数、时间可控制)

    D_CA_EVT_SHOW_MAURITY_PROGRAM,  //成人级节目
	D_CA_EVT_HIDE_MAURITY_PROGRAM,  //隐藏成人级节目
	
	D_CA_EVT_SHOW_SUPER_FINGERMSG,  //显示联广用户指纹
	D_CA_EVT_HIDE_SUPER_FINGERMSG,  //隐藏联广用户指纹
	
	D_CA_EVT_SHOW_EMM_FINGERMSG,    //显示联广EMM指纹
	D_CA_EVT_HIDE_EMM_FINGERMSG,    //隐藏联广EMM指纹
	
	D_CA_EVT_SHOW_COVERT_FINGERMSG, //显示隐藏指纹
	D_CA_EVT_HIDE_COVERT_FINGERMSG, //擦除隐藏指纹
	
	D_CA_EVT_SEND_OTAMSG,           //发送OTA信息
	D_CA_EVT_SENDMSG_TO_OTHERSTB,   //通过串口发送信息
	
    D_CA_EVT_SHOWOPERTEMSG,         //显示可操作的提示消息
    D_CA_EVT_SHOW_FEED_STATUS,
    
    D_CA_EVT_REMOTE_LOCK,           //锁遥控器
    D_CA_EVT_REMOTE_UNLOCK,         //解锁遥控器

    D_CA_EVT_START_SERVICE,         //开机默认换台节目
    D_CA_EVT_CANCLE_START_SERVICE,  //取消开机默认换台节目
    
    D_CA_EVT_RESTART_STB,           //重启机顶盒
    
    D_CA_EVT_CA_CTL_PROG_OFF,       //CA控制停止视频
    D_CA_EVT_CA_CTL_PROG_ON,        //CA控制开启视频

    D_CA_EVT_CA_CTL_NIT_SEARCH,     //条件搜索
    
    D_CA_EVT_HIDE_AUTO_CHARGE,      //掩藏自动充值(for dvnca)
    D_CA_EVT_SHOW_AUTO_CHARGE,      //显示自动充值(for dvnca)
    
    D_CA_EVT_FlAG_CHANGE,           //节目免费加扰切换标志

    D_CA_EVT_FORBID_PVR,           //禁止录像(for  abvca)

    D_CA_EVT_ABV_TIMING_SHOWBUYMSG,//ABV消息
    D_CA_EVT_ABV_SERIALIZE_STATUS, //ABV序列化状态

    D_CA_EVT_SHOW_NORMAL_EMMFINGER, //显示EMM指纹
	D_CA_EVT_HIDE_NORMAL_EMMFINGER, //隐藏EMM指纹
	
    D_CA_EVT_SHOW_EMERGENCY_ICON,   //显示"紧急事件"图标
    D_CA_EVT_HIDE_EMERGENCY_ICON,   //隐藏"紧急事件"图标

    D_CA_EVT_SHOW_IMMOBILE_TOPSCROLL, //显示静止不动的上滚动条
    D_CA_EVT_SHOW_IMMOBILE_BOTTOMSCROLL, //显示静止不动的下滚动条

    //再添加枚举放在这个之前
	D_CA_EVT_SC_USER
} D_CAEventType;

/**< @brief CA提示信息*/
typedef struct
{
	D_U8 language;
	D_U8 prio; 
	D_U8 osd_number; 
	D_Char *ch_msg; /*中文内容*/
	D_Char *en_msg; /*英文内容*/
	D_Char *ot_msg; /*其他内容*/
}D_CaOSDPreDefined;

/**< @brief ca osd管理*/

typedef struct
{
	D_CaOSDPreDefined *osd_predef;  //tig:此变量用不上
	D_U8 show_icon;                 // 1 显示 0 不显示	
}D_CaOSDMan;

typedef struct
{
	D_Char *osd_predef;             //指向显示内容的指针，注:存储显示内容的变量应该为全局变量
	D_U32 time;                     //显示时间(s) 0 不显示 
}D_CaTimerOSDMan;

typedef struct
{
    D_Char *osd_predef;             //指向显示内容的指针，注:存储显示内容的变量应该为全局变量
    D_U32  time;                    //显示次数
    D_U32  show_time;               //每次显示的时间
    D_U32  hide_time;               //每次隐藏的时间
}D_CaFlashOSDMan;

/*-- 普通指纹显示信息--*/
typedef struct{
	D_U8		byShowType; 	    //显示方式 :0 不闪烁  1闪烁
	D_U32		Duration;		    //显示时间，单位:秒 .  无时间限制时赋值为0.
	char		szContent[FINGER_LABEL_BUF_LEN]; //需要显示的指纹内容，用0结尾的字符串
}D_CAOrdinaryFinger;

/*-- 超级指纹显示信息--*/
typedef struct {
	D_U8		byShowType; 	    //显示方式0：字符串; 1：点阵；2：矩阵；其他值保留。
	D_U8		byContentType; 	    //显示类型0：卡号；1：机顶盒号；其他值保留。
	D_U8	    bIsVisible; 	    //可见性0：显性；1：隐性
	D_U8        bIsForcedShow;      //是否强制显示 0：非强制显示 1：强制显示。
	D_U8        byEncryption;       //加密算法号 0：不加密；非0：加密
	D_U16       wFlashing_EachShowTime; //每轮闪烁显示时长，为0时表示不闪烁。
	D_U16       wFlashing_EachHideTime; //每轮闪烁暂停时长，为0时表示不闪烁。
	D_U8        byFontSize; 	    //指纹字体大小，取值范围[0,255]，0表示默认字体大小，1表示大字体，2表示小字体，3~255表示实际字体大小，如果机顶盒不支持3~255则按照默认字体大小显示。byShowType为1和2时表示指纹区域的大小。
	D_U8		byReserved;	        //0x00	保留
	D_U32	    dwFontColor;	    //字体颜色，标准RGB值。byShowType为1时该值无意义。
	D_U32	    dwBackgroundColor;	//背景颜色，标准RGB值，byShowType为1和2时不做要求。
	D_U8		byX_position;		//指纹显示位置的X轴坐标，取值范围0~100
	D_U8		byY_position;		//指纹显示位置的Y轴坐标，取值范围0~100
	D_U8	    pbyMatrixInnerPos[16];	// byShowType为2时表示矩阵指纹每个字符对应的内部坐标值。byShowType为其他值时此字段无意义。
	char		szContent[21];      //需要显示的指纹内容，用0结尾的字符串。
}D_CAFingerInfo;
typedef struct {
	D_U8		byShowPosition; 	//显示位置:0 左上 1 右上 2 左下 3 右下
	D_U8	    bIsVisible; 	    //可见性0：显性；1：隐性
	D_U8        byFontSize; 	    //指纹字体大小，取值范围[0,255]，0表示默认字体大小，1表示大字体，2表示小字体，3~255表示实际字体大小，如果机顶盒不支持3~255则按照默认字体大小显示。byShowType为1和2时表示指纹区域的大小。
	D_U32	    dwFontColor;	    //字体颜色
	D_U32	    dwBackgroundColor;	//背景颜色
	D_U8        ifShowBCflag;       //是否显示背景颜色 0 不显示 1 显示
	D_U16		byX_position;		//指纹显示位置的X轴坐标
	D_U16		byY_position;		//指纹显示位置的Y轴坐标
	char		szContent[21];      //需要显示的指纹内容，用0结尾的字符串。
}D_DSCAFingerInfo;

/*-- 高斯贝尔CA超级指纹显示信息--*/
typedef struct {
	D_U8		byShowPosition;     //显示位置:0  右上 1 按坐标显示 2 随机
	D_U8		byContentType;  	//显示类型0：卡号；1：机顶盒号；2:卡号+ 机顶盒号; 3: 卡号+ 用户自定义内容; 4:机顶盒号+用户自定义内容; 5:卡号+机顶盒号+用户自定义内容; 其他值保留。
	D_U8	    bIsVisible; 	    //可见性0：显性；1：隐性
	D_U8        bIsForcedShow;      //是否强制显示 0：非强制显示 1：强制显示。
	D_U16	    wInterval;		    //时间间隔,两次显示之间的不显示指纹的时间长度
	D_U8        byFontSize; 	    //指纹字体大小，取值范围[0,255]，0表示默认字体大小，1表示大字体，2表示小字体，3~255表示实际字体大小，如果机顶盒不支持3~255则按照默认字体大小显示。byShowType为1和2时表示指纹区域的大小。
	D_U8		byReserved;	        //0x00	保留
	D_U32	    dwFontColor;	    //字体颜色，ARGB值
	D_U32	    dwBackgroundColor;	//背景颜色，ARGB值，
	D_U8		byX_position;		//指纹显示位置的X轴坐标，
	D_U8		byY_position;		//指纹显示位置的Y轴坐标，
    D_U16       wContentLen;        //需要显示的指纹内容的长度
	char		szContent[255];     //需要显示的指纹内容，用0结尾的字符串。
	D_U8        byChannelcnt;       //  指纹显示频道数，如果为0 ，表示所有频道都显示指纹  
    D_U16       wServiceID[10];     //显示指纹频道的service id 
}D_GOSCAFingerInfo;

/*高斯贝尔CA超级OSD 结构*/
typedef	struct{
    D_U8   byShowType;              //0:非强制显示，1:强制显示
    D_U8   byFontSize;              //OSD字体大小，
    D_U8   byBackgroundArea;        //表示占屏幕正中央部分的面积百分比，默认为80，范围（20~80）
    D_U32  dwFontColor;	            //字体颜色，ARGB值
    D_U32  dwBackgroundColor;       //背景颜色，ARGB值，
    char   szContent[256+1];        //osd字符串，用0结尾的字符串
    D_U8   byShowCardNo;            //0:不带卡号 1:带卡号
}D_GOSCAOSDInfo;

/*超级指纹结构*/
typedef	struct{
    D_U16	byrepitition;           //显示次数
    D_U16   wFlashing_EachShowTime;  //每轮显示时长
    D_U16   wFlashing_EachHideTime;  //每轮显示暂停时长
    D_U8    byFontSize;		        //字体大小
    D_U8    Sparkling;              // 闪烁

    D_U16   byX_position;		    //指纹显示位置的X轴坐标
    D_U16	byY_position;		    //指纹显示位置的Y轴坐标
    D_U8    bywidth;                /* %   ex: 80(80%), 64(64%), 0x64(100%)*/
    D_U8    byheight;               /*%*/
    D_U32   dwFontColor;	        //支持256色
    D_U32   dwBackgroundColor;		//支持256色
    D_U8    disp_Background;        // 1:显示背景
    D_U8    forcefinger;            // 1:强制指纹
    D_U8    disp_cardnum;           // 1:显示卡号
    D_U8    disp_stbnum;            // 1:显示机顶盒号
	
    D_U8    Transparency;           //透明度
    D_U16   OsdLen;                 //osd数据长度
    char    szContent[1024];        //osd字符串，用0结尾的字符串
}D_ABVCASuperFingerInfo;

/*超级OSD 结构*/
typedef	struct{
    D_U8   byShowType;              //0:非强制显示，1:强制显示
    D_U8   byFontSize;		        //0：默认，1：大号，2：小号
    D_U8   byBackgroundArea;		//表示占屏幕正中央部分的面积百分比，默认为80，范围（20~80）
    D_U32  dwFontColor;	            //支持256色
    D_U32  dwBackgroundColor;		//支持256色    
    char   szContent[512];          //osd字符串，用0结尾的字符串
}D_DCAOSDInfo;

/*超级OSD 结构*/
typedef	struct{
    D_U16   byrepitition;           //闪烁次数
    D_U16   wFlashing_EachShowTime; //每轮闪烁显示时长，为0时表示不闪烁。
    D_U16   wFlashing_EachHideTime; //每轮闪烁暂停时长，为0时表示不闪烁。
    D_U8    byFontSize;		        //字体大小
    D_U8    disp_Background;        //是否显示背景
    D_U32   dwFontColor;	        //支持256色
    D_U32   dwBackgroundColor;		//支持256色
    D_U8    Transparency;           //透明度
    D_U16   OsdLen;                 //osd数据长度
    char    szContent[1024];        //osd字符串，用0结尾的字符串
}D_ABVCAOSDInfo;

/*缓存OSD 结构*/
typedef struct
{
	D_U32 MaxNum;                   //OSD最大存储数
    D_U32 MaxLen;                   //OSD长度
    D_U32 CurNum;                   //OSD当前条数
    D_U32 SaveIndex;                //OSD存索引
    D_U32 GetIndex;                 //OSD取索引
    
}D_CaSaveOSDInfo;

/*监控OSD 结构*/
typedef struct
{
    D_U8 showPosition;              //0 top 2 bottom 3 top and tottom 
    D_U8 fontColor[4];              //R G B A   目前只有德赛CA的OSD字体也设置透明度
    D_U8 bgColor[4];                //R G B A
    D_U8 osdType;                   //不同版本使用的sod函数不一样1 支持颜色等0 不需支持
    D_U8 showCount;                 //显示次数
    char osdMsg[MAX_OSD_NUM][MAX_OSD_LEN];
}MonitorOSDInfo;

/*--间隔OSD 结构--*/
typedef struct{
	D_U8		u8Style; 		  //显示风格
	D_U8        u8JudgeValue;   //滚动一次显示遍数
	D_U32       u32Interval;      //间隔显示时间
	D_Char      u8OsdData[MAX_OSD_LEN];  //显示内容			
}D_CAIntervalScroll;

/*-- 静止滚动条显示信息--*/
typedef struct{
	D_U32		Duration;		 //显示时间，单位:秒 .  无时间限制时赋值为0.
	char		szContent[256]; //需要显示的滚动条内容，用0结尾的字符串
}D_CAImmobileScroll;

/*-- 进度条--*/
typedef struct
{
	D_U8   byProgress;              //具体进度值
	D_Char ShowType;                // 1 数据接收中 2 智能卡升级中 
}D_ProgressStrip;

/*-- IPPV,隐藏时为NULL--*/
typedef struct{
	char productId[12];				//节目的ID
    char tvSId[6];    			    //运营商编号
    D_U8 isIppvOrIppt;				//支持ippv或ippt  1 ippv  2  ippt  3  ippv and ippt
    D_U8 ippStatus;					//收费阶段   0 ippv免费阶段  1 ippv收费阶段  2 ippt收费阶段 
    char ippCanTapPrice[6]; 		//可录像的节目价格
    char ippCanNotTapPrice[6]; 		//不可录像的节目价格
	char ippvPeriod[12]; 			//ippv节目过期时间
	char ipptInterval[12];			//ippt节目收费间隔
	D_U8 slotId;					//钱包ID	
	D_U8 priceCode[2];              //购买类型，priceCode[0]不可录像的节目，priceCode[1]可录像的节目
}D_IppBuyInfo;

typedef struct{
	D_U8 IPPV_Type;
	char  IPPV_Time_Price[7];
	char  IPPV_View_Price[7];
	char  IPPV_Name[24];
	char  Pro_Start_Time[17];
	char  Pro_End_Time[17];
	D_U8  IPPV_ID;	                //节目序号
}D_abvca_IppBuyInfo;

/*-- 应急广播--*/
typedef struct {
    D_U8  RemoteCtl;                //0,锁定遥控器及前面板，1，不锁定
	D_U8  Modulation;               /* 调制方式 32QAM 64QAM*/
    D_U16 VPid;
	D_U16 APid;
	D_U16 PcrPid; 	
	D_U32 Frequency;                //频率
	D_U32 symbol_rate;              //符号率
}D_Ca_SwitchChannel_t;

/*-- 取消应急广播--*/
typedef struct {
    D_U8  CancelCtl;                //0,取消锁定遥控器；1,取消并返回之前播放的节目
}D_Ca_Channel_cancel_t;


/*-- 开机默认换台--*/
typedef struct {
	D_U16 ServiceId;
	D_U16 PcrPid; 	
}D_Ca_StartChannel_t;

/*-- 加扰免费切换--*/
typedef struct {
	D_U16   ServiceId;
	D_Bool  desflag; 	
}D_Ca_ProgDescflag_t;

/** @brief CA事件信息回调函数*/
typedef D_Result	(*D_CAEventCallback) (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief CA编译信息回调函数*/
typedef D_Result	(*D_CAComplieCallback) (D_U32* param) D_FUNCPOSTFIT;


/** @brief 判断当前是否是无卡CA
* @return 返回2表示是无卡CA，其他为有卡CA
*/
D_Result    d_ca_get_sc_status(void);


/** @brief CA系统初始化
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_open (void) D_FUNCPOSTFIT;

/** @brief 通知CA系统开始分析一个TS流中的用户授权数据
* @param	param 参数指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_start_ts (D_CATSParam *param) D_FUNCPOSTFIT;

/** @brief 通知CA系统停止分析一个TS流中的用户授权数据
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_stop_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief 通知CA系统开始分析一个服务的用户控制数据
* @param	param 参数指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_start_srv (D_CASrvParam *param) D_FUNCPOSTFIT;

/** @brief 通知CA系统停止分析一个服务的用户控制数据
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_stop_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 和CA系统同步
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_sync (void) D_FUNCPOSTFIT;

/** @brief CA系统ID检查
* @param ca_sys_id	CA系统ID
* @return 是可识别的CA返回D_TRUE,否则返回D_FALSE
*/
D_Bool		d_ca_sys_check (D_U16 ca_sys_id) D_FUNCPOSTFIT;

/** d_ca_sys_check 里写死返回1，为不影响以前功能，特增加此接口*/
D_Bool d_ca_sys_id_check (D_U16 ca_sys_id) D_FUNCPOSTFIT;

/** @brief 注册CA信息回调函数
* @param callback	要注册的回调函数指针
* @param old 返回旧的回调函数指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_register_callback (D_CAEventCallback callback, D_CAEventCallback *old) D_FUNCPOSTFIT;


/** @brief 注册CA编译信息回调函数
* @param callback	要注册的回调函数指针
* @param old 返回旧的回调函数指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_ca_register_comp_callback (D_CAComplieCallback callback, D_CAComplieCallback *old)D_FUNCPOSTFIT;


/** @brief 结束CA管理系统
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_ca_close (void) D_FUNCPOSTFIT;



/** @brief 停止CA管理系统
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_ca_stop(void) D_FUNCPOSTFIT;


/** @brief 启动CA管理系统
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_ca_run(void) D_FUNCPOSTFIT;

/** @brief 提示信息存储初始化
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ca_osd_man_init(void);

/** @brief 重新显示ca信息，邮件，指纹等
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ca_osd_reshow(void);

/** @brief 获取当前是哪个ca
* @return 返回当前ca值 参考hrca_config.h里ca值定义
*/
D_U32 d_ca_get_curcas(void);

/** @brief pmt cat表监控*/
D_Result d_ca_demux_data_cmp (D_U8 dType, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief机顶盒语言变化后，通知CA库或者刷新提示
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_ca_lan_change (D_U8 lanType);

/** @brief机顶盒获取卡号字符串
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_ca_get_scid(D_Char *str_scid, D_Size *len);

/** @brief  此接口返回的 ChipID是4字节的。
**供应用菜单中调用，目前仅WFCA使用*/
D_Result
d_ca_get_chipid(D_U8 *len, D_U8 *chipid);

/** @brief  此接口返回的是cardno。
**供应用菜单中调用，目前仅WFCA使用*/
D_Result
d_ca_get_cardno(D_U8 *len, D_U8 *cardno);

extern D_U16 g_CaNetWorkID;
D_Result d_ca_get_networkid(D_U16 *networkid);

/** @brief 擦除ca flash的数据，目前只有电视机联广无卡CA用到*/
D_Result d_ca_erase_ca_flash(void);

/** @brief ca system的所有任务(包括CA库任务和"CA"任务)停止运行*/
D_Result d_ca_system_stop(void);

/** @brief ca system的所有任务(包括CA库任务和"CA"任务)重新启动*/
D_Result d_ca_system_run(void);

/** @brief 通过usb烧写otp信息*/
D_Result d_ca_burn_otpinfo_by_usb(void);

/** @brief 通过串口烧写otp信息*/
D_Result d_ca_burn_otpinfo_by_serialport(D_U8 *potp, D_U16 len);

typedef void (*CallBackDspmessage)(D_U32 p);
extern CallBackDspmessage    SendMsgtoSC;

extern D_Bool	ca_inserted;

/*滚动条回调参数*/
typedef struct
{
    D_U32 curcas;
    D_U32 position;
    D_Char* text;
    D_U32 bg_color;
    D_U32 text_color;
    D_U8  font_size;
    D_U32 scroll_speed;
    D_U32 repeat_times;
    D_U32 duration;
    D_Bool immediate;
    D_ScrollCallback callback;
}D_CasScrollParam;

/*位置区 1: 左或上  2: 右或下*/
#define D_CAS_SCROLL_POSITION_1  (1)
#define D_CAS_SCROLL_POSITION_2 (2)

/*滚动条操作代码*/
#define D_CAS_SCROLL_ACTION_CREATE  (0)
#define D_CAS_SCROLL_ACTION_DESTROY (1)
#define D_CAS_SCROLL_ACTION_START   (2)
#define D_CAS_SCROLL_ACTION_STOP    (3)
#define D_CAS_SCROLL_ACTION_GETSTATE    (4)

typedef D_Result (*HRCAScrollAction)(D_Handle handle, D_U32 action, D_CasScrollParam *param);
extern HRCAScrollAction HRCA_Scroll_Action;
extern D_Result d_ca_register_scroll_callback(HRCAScrollAction callback, HRCAScrollAction *old);

typedef D_Result (*HRCABurnAction)(D_Ptr param);
extern HRCABurnAction HRCA_Burn_Action;
extern D_Result d_ca_register_burn_callback(HRCABurnAction callback, HRCABurnAction *old);

typedef D_Result (*HRCAScModeAction)(void);
extern HRCAScModeAction HRCA_ScMode_Action;
extern D_Result d_ca_register_scmode_callback(HRCAScModeAction callback, HRCAScModeAction *old);

#ifdef  __cplusplus
}
#endif

#endif
