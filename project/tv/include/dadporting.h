/** @file
* @brief 广告模块支撑接口
* @author hegx
* @date 2014-03-03 和光雄: 建立文件
*/
#ifndef _D_ADPORTING_H_
#define _D_ADPORTING_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDebug.h"
#include <string.h>
#include "dMMan.h"
#include "dMem.h"
#include "dDemux.h"
#include "dTimer.h"
#include "dGraph.h"
#include "dResource.h"

#define D_AD_MODULE_TASK_PRIO			3

/** @brief 广告版本*/
#define AD_STB_HAIERV1  0x0 //海尔广告V1.0
#define AD_STB_HAIERV2  0x1 //海尔广告V2.0
#define AD_STB_DESAI 	0x2 //德赛广告
#define AD_STB_MG 		0x3 //三洲广告
#define AD_STB_IFABOO   0x4 //数联广告
#define AD_STB_DIVI	    0x5 //数视通广告
#define AD_STB_DVT	    0x6 //数码视讯广告
#define AD_STB_MAX  	0x7 //未知类型

/** @brief  滚动条数据源类型，文本还是图片*/
#define P_SCROLL_SRC_TYPE_TEXT (0)
#define P_SCROLL_SRC_TYPE_IMAGE (1)

#define DAD_DEMUX_TOTAL_TYPE  0x10//最大的demux支持数
#define DAD_PIC_TOTAL_TYPE    20//最多的图片数
#define DAD_TIMER_TOTAL_TYPE  0x20//最多的定时器

/** @brief 广告句柄*/
typedef D_Handle	D_AdHand;

/** @brief 机顶盒平台*/
typedef enum 
{
	DAD_STB_SD=1, 	/*标清*/
	DAD_STB_HD=2, 	/*高清*/
	DAD_STB_UNKNOWN,/*未知类型*/
}D_Ad_Stb_Decode_Type;

/** @brief 广告应用类型*/
typedef enum 
{
	DAD_STB_LOG = 1,         /*开机广告*/
	DAD_STB_EPG ,         /*EPG广告*/
	DAD_STB_FULLSCREEN ,  /*推送广告*/
	DAD_STB_VOLUME,      /*音量广告*/
	DAD_STB_MENU ,		 /*主菜单广告*/
	DAD_STB_MENU_UP,	 /*主菜单广告上*/
	DAD_STB_MENU_DOWN,	 /*主菜单广告上*/
	DAD_STB_UNAUTHORIZED,/*未授权节目广告*/
	DAD_STB_BANNER,      /*节目信息条广告*/
	DAD_STB_OSD,         /*OSD广告*/
	DAD_STB_RadioBackGround,
	DAD_STB_Nosignal,
	DAD_STB_NoProgram ,
	DAD_STB_ProgramList,//节目列表广告
	DAD_STB_PICOSD,		 /*图片OSD广告*/
	DAD_STB_FavorList,//喜爱列表广告 @qiny add 2015.03.20
	DAD_STB_POS_UNKNOWN,     /*未知类型*/
}D_Ad_Pos_Type;

/** @brief 广告数据类型*/
typedef enum 
{
	DAD_PIC_DATA = 1,       /*图片类型*/
	DAD_M2V_DATA = 2,       /*视频数据 */  
}D_Ad_Data_Type;

/** @brief OSD显示位置*/
typedef enum  
{
	TOP_BOTTOM = 1,				/*在顶部和底部同时显示*/  
	LEFT_RIGHT,				    /*在左边和右边同时显示*/  
	LOCAL_HORIZONTAL, 			/*坐标显示*/  
	LOCAL_VERTICAL,				/*坐标显示*/  
	UNKNOWN_TYPE,
}D_Ad_Osd_Show_Pos;


/** @brief 支持的广告类型*/
typedef enum 
{
	DAD_OPEN = 1,		 //打开广告模块
	DAD_CLOSE ,		 	 //关闭广告模块
	DAD_APP_INIT ,		 //进入一个广告应用
	DAD_APP_EXIT ,		 //退出一个广告应用
	DAD_SET_PARAM ,	 	 //设置节目参数
	DAD_RESET_DATA , 	 //设置节目参数
	DAD_APP_RELEASEDATA, //释放数据
	DAD_UPDATE_DATA ,	 //数据更新
	DAD_ERASE_DATA ,  //数据擦除
}D_Ad_Msg_Type;


/** @brief 广告配置参数*/
typedef struct
{
	D_Ad_Stb_Decode_Type type;  /*广告平台*/  
	D_U8 dstag;					/*DS广告TAG*/  
	D_U8 mgtag;					/*MG广告TAG*/  
	D_U8 ifabootag;				/*数联广告TAG*/  
	D_U8 hitag;					/*海尔广告TAG*/  
	D_U8 divitag;				/*数视通广告TAG*/ 
	D_U8 ucPriority;			/*广告任务优先级*/  
	D_U32 uiFlashStartAddress;  /*广告Flash 起始地址*/  
}d_ad_config;


/** @brief 作为图像广告的参数结构*/
typedef struct _D_Ad_Image_Param
{
	D_Ad_Data_Type data_type;   //图片类型
	D_U32 		   id;		    //图片ID      
	D_U32 		   times;		//显示时间，0xffffffff为 一直显示
	D_Ptr 		   data_rsc_ptr;//数据指针传递，用于释放数据资源
	D_U8 		   if_erase;	//擦除命令标志  
	D_U16		   left;		//起始坐标x
	D_U16		   top;			//起始坐标y
	D_Image* 	   image;		//图片资源
	D_U8 		   uctotal;     //图片总数，当大于1时候，上一个图片的显示时间到之后取下一个图片
}D_Ad_Image_Param ;

/** @brief 作为OSD广告的参数结构*/
typedef struct _D_Ad_Osd_Param
{
	D_Ptr data_rsc_ptr;			//数据指针传递，用于释放数据资源
	D_U8  if_erase;				//擦除命令标志  
	D_U8  enDisplayPos; 		//osd显示位置类型
	D_U32 aucBackgroundColor;	//背景颜色
	D_U32 aucDisplayColor;   	//字体颜色
	D_U8* pucDisplayBuffer;     //osd内容
	D_U16 usContentSize;        //osd内容长度
	D_U16 ucFontType;           //字体类型
	D_U16 ucFontSize;           //字体大小
	D_U32 ucShowTimes;          //显示次数
	D_U32 id;		   			//图片ID ,当id相当时候上层处理为是同一条，不会重新滚动  
	D_U8  uctotal;          	//总数
	D_U8  idx;          		//当前滚动条的idx，用于查找下一条
	D_U8  txtSpeed;          	//速度
	D_U16 ucstartposx;          //起始坐标x
	D_U16 ucstartposy;          //起始坐标y
	D_U16 ucendposx;          	//终点坐标x,当TOP_BOTTOM/LEFT_RIGHT时候使用为第二条的起始坐标x
	D_U16 ucendposy;          	//终点坐标y,当TOP_BOTTOM/LEFT_RIGHT时候使用为第二条的起始坐标y
	D_U8  ucType;               //图片滚动，文本滚动。 默认是文本滚动
}D_Ad_Osd_Param;


/** @brief 回调参数*/
typedef struct {
	D_U32			param1;	/**< 参数1*/
	D_U32			param2;	/**< 参数2*/
	D_U8*			param3;	/**< 参数2*/
} D_AdFunBack;

typedef void (* ADFunctionBack)(D_AdFunBack *param,D_U8* sec,D_U32 len);


/** @brief 用户自定义消息*/
typedef struct {
	D_MsgType		type;		/**< 消息类型*/
	D_U32			param1;	/**< 参数1*/
	D_U32			param2;	/**< 参数2*/
	D_Ptr 			handle;
	D_U16 			usNetworkId;
	D_U16 			usTsId;
	D_U16 			usServiceId;	
} D_AdMsg;

/** @brief 事件参数*/
typedef struct _D_Ad_Event_Param
{
	D_U8 		use_flag;
	D_HMutex	hm;						/*互斥锁*/
	D_HDemux    hdemux;
	D_U32 		starttime;
	ADFunctionBack Function;
	D_AdFunBack param;
    D_HTimer    htimer;	
	D_DemuxType	type;			/**< 解复用设备类型*/
	D_Size		buf_size;	/**< 解复用设备缓冲区大小*/
	D_Bool	    one_shot;	/**< 是否是单次型定时器*/
	
}D_Ad_Event_Param;

/** @brief 节目参数*/
typedef struct _D_Ad_Service_Param
{
	D_U16 usNetworkId;
	D_U16 usTsId;
	D_U16 usServiceId;
}D_Ad_Service_Param;

typedef D_Handle (*ADEVENTCALLBACK)(D_U8 event, D_Ad_Event_Param *param);

typedef struct _D_Ad_Init_Param
{
	D_Ad_Stb_Decode_Type type;
	D_HQueue	queue;
	D_U32 		uiFlashStartAddress;		
	D_Size		buf_size;	/**< 解复用设备缓冲区大小*/
	D_U8 ucPriority;
	ADEVENTCALLBACK cb;
}D_Ad_Init_Param;

typedef struct _D_Ad_Start_Param
{
	D_FEndAttr attr;
}D_Ad_Start_Param;

/** @brief 图片信息描述*/
typedef struct
{
	D_ImageType imgType;// 图片类型
	D_U32 id;			// id
	D_U16 times;		// img显示时间 100ms
	D_U16 left;			// img显示相对坐标
	D_Int top;			// img显示相对坐标
	D_Int width;		// img显示宽度
	D_Int height;		// img显示高度
	D_U8 *buf;			// img数据区指针
	D_Size img_size;	// img数据大小
}D_Ad_Img_Param;

typedef struct
{
	D_Ad_Pos_Type posType;
	D_Ad_Img_Param img_param;
}D_Ad_Store_Img_Param;


/** @brief 图片信息解析之后给应用的数据信息*/
typedef struct d_ad_pict_info_s
{
	D_U32 advType;		// 图片应用类型
	D_ImageType imgType;// 图片类型
	D_U32 id;			// id
	D_U8 *buffer;		//数据的指针
	D_Size img_size;	// img数据大小
	D_U32 times;		// img显示时间
	D_U16 left;			// img显示相对坐标
	D_Int top;			// img显示相对坐标
	D_Int width;		// img显示宽度
	D_Int height;		// img显示高度
	D_U8 *hand;			//链表的指针
}d_ad_pict_info;

/** @brief 回调事件*/
typedef enum  
{
	DAD_EVENT_CREATE_DEMUX = 1,				/*创建通道*/  
	DAD_EVENT_START_DEMUX,					/*打开通道*/  
	DAD_EVENT_DESTROY_DEMUX,				/*销毁通道*/  
	DAD_EVENT_STOP_DEMUX,					/*停止通道*/  
	DAD_EVENT_CREATE_TIMER, 			    /*创建定时器*/	
	DAD_EVENT_DESTROY_TIMER,				/*销毁定时器*/  
	DAD_EVENT_UPDATE_DATA,				/*有更新*/	
	DAD_EVENT_ERASE_DATA,					/*擦除*/	
	DAD_EVENT_MAX,
}D_Ad_EVENT_TYPE;

typedef struct _D_Ad_Op	D_Ad_Op;

struct _D_Ad_Op {
	D_Result (*check_scan)(void)D_FUNCPOSTFIT;
	D_Result (*init)(D_Ad_Init_Param *cfg)D_FUNCPOSTFIT;
	D_Result (*exit)(void)D_FUNCPOSTFIT;
	D_Result (*start)(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT;
	D_Result (*reset)(void)D_FUNCPOSTFIT;
	D_Result (*getversion)(D_U8 *sversion)D_FUNCPOSTFIT;
	D_Result (*enter_app)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*exit_app)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*get_img)(D_Ad_Service_Param *chan_param,D_Ad_Pos_Type type,D_U8 idx,D_U8* info)D_FUNCPOSTFIT;
	D_Result (*release_img)(D_Ad_Pos_Type type,D_U8* image)D_FUNCPOSTFIT;
	D_Result (*setdescr)(D_U8 * descr,D_U32 id)D_FUNCPOSTFIT;
	D_Result (*settag)(D_U8 ttag,D_U32 id)D_FUNCPOSTFIT;
	D_Result (*check_app)(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
	D_Result (*set_fp_key)(D_U32 key)D_FUNCPOSTFIT;
	D_Result (*check_fp_key)(D_Ad_Pos_Type type,D_U32 key)D_FUNCPOSTFIT;	
	D_Result (*scroll_callback)(D_U8 idx,D_U8 total)D_FUNCPOSTFIT;	
	D_Result (*chan_change)(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;	
/**以下几个函数是直接取保存的数据，用来给上层自己显示的时候使用*/
	D_U8 (*get_img_count_ex)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*load_img_data_ex)(D_Ad_Pos_Type type, D_U8 no,d_ad_pict_info *info)D_FUNCPOSTFIT;
	D_Result (*release_img_data_ex)(d_ad_pict_info *img_data)D_FUNCPOSTFIT;
};
extern D_U8 * d_dad_getop(void)D_FUNCPOSTFIT;
extern D_Result d_ad_modlue_Open(d_ad_config *cfg)D_FUNCPOSTFIT;
extern D_Result d_ad_enter_menu_ex(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Result d_ad_exit_menu_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
extern D_Result d_ad_set_chan_ex(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Ptr  d_ad_get_img_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
extern D_Result d_ad_release_img_ex(D_Ad_Pos_Type type,D_Ptr handle)D_FUNCPOSTFIT;
extern D_Result d_ad_modlue_start(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT;
extern D_Result d_ad_Check_App(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Result d_ad_set_fpkey_ex(D_U8 key)D_FUNCPOSTFIT;
extern D_Result d_ad_check_fpkey_ex(D_Ad_Pos_Type type,D_U8 key)D_FUNCPOSTFIT;
extern D_Result d_ad_scroll_callback(D_U8 idx,D_U8 total)D_FUNCPOSTFIT;
extern D_U8 d_ad_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT;
extern D_Result d_ad_load_img_data(D_Ad_Pos_Type type, D_U8 no, d_ad_pict_info *info)D_FUNCPOSTFIT;
extern D_Result d_ad_release_img_data(d_ad_pict_info *img_data)D_FUNCPOSTFIT;
extern D_Result d_ad_SetDescr(D_U8 * descr, D_U32 id)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif


#endif

