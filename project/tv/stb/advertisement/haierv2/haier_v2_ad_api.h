/** @file
* @brief 广告模块支撑接口
* @author huangq
* @date 2014-06-16 huangq: 建立文件
*/
#ifndef _D_HIV2ADSTBAPI_H_
#define _D_HIV2ADSTBAPI_H_

#define AD_MAX_NUM				20//最多的组数
#define PIC_MAX_NUM				50//最多的图片数
#define TXT_MAX_NUM				10//滚动条资源个数(每组)
#define MAX_AREA_CODE_NUM		20
#define AD_LINK_PIC_MAX_NUM		20
#define AD_LINK_SERV_MAX_NUM	20

#define TOTAL_TXT_MAX_NUM				255//滚动条资源个数
#define TOTAL_TXT_SERV_MAX_NUM			255//滚动条资源个数

#define ADL_PLAY_PARAS_DES			0x80		//广告参数描述符
#define ADL_AREA_ID_DES				0x82		//区域ID描述符
#define ADL_DATA_DES				0x83        //广告数据描述符
#define	SCROLL_TXT_DES				0x84    //滚动字幕描述符
#define	SERVICE_ID_DES				0x85    //服务描述符
/** @brief 广告显示标识*/
#define HIV2AD_MSEEAGE_SHOWFULLSRCEEN_TYPE	(0X04)//显示挂角广告
#define HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE	(0X05)//隐藏挂角广告

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/** @brief haier广告应用类型*/
typedef enum
{
    HIV2AD_STB_LOG = 0,         //0 开机广告
    HIV2AD_STB_BANNER, 					//1换台吧
    HIV2AD_STB_VOLUME,					//2音量条
    HIV2AD_STB_MENU, 						//3主菜单
    HIV2AD_STB_PROGRAM_LIST,		//4节目列表
    HIV2AD_STB_EPG,             //5 EPG广告
    HIV2AD_STB_RADIO_BACK,      //6 广播背景
    HIV2AD_STB_NOSIGNAL,        //7 无信号
    HIV2AD_STB_NOPROGRAM,       //8 无节目
    HIV2AD_STB_FULLSCREEN,      //9 挂角广告
    HIV2AD_STB_ROLL_TXT,        //10 滚动字幕广告
    HIV2AD_STB_POS_UNKNOWN,     //11 未知类型
} HIV2_Ad_Pos_Type;

/** @brief haier广告图片类型*/
typedef enum
{
    HIV2AD_IMAGE_JPEG = 1,
    HIV2AD_IMAGE_GIF,
    HIV2AD_IMAGE_MPEG2_FRAME_I,
    HIV2AD_IMAGE_BMP,
    HIV2AD_IMAGE_AUTO,
} HIV2_Ad_Pic_Type;

/** @brief haier 资源库类型*/
typedef enum
{
    HIV2AD_TYPE_PIC = 1,        //0 开机广告
    HIV2AD_TYPE_TXT,     				//11 未知类型
		HIV2AD_TYPE_TS,		 					//11 未知类型
} HIV2_Ad_Resource_Type;


/** @brief 搜索表类型标识*/
typedef enum HIV2AD_FILTER_FLAG_
{
	HIV2AD_FILTER_FLAG_CONTROL = 0,
	HIV2AD_FILTER_FLAG_INFO = 1,
	HIV2AD_FILTER_FLAG_DATA = 2,
	HIV2AD_FILTER_FLAG_MAX ,
}HIV2AD_FILTER_FLAG;

/** @brief 搜索广告PID区分*/
typedef enum HIV2AD_Msg_PID_Type_
{
    HIV2AD_PID_TYPE_ADLIST        =  0,
    HIV2AD_PID_TYPE_DESCRIPTOR      =  1,
    HIV2AD_PID_TYPE_PIC_DATA    =  2,
    HIV2AD_PID_TYPE_MAX_NUM,
} HIV2AD_Msg_PID_Type;

/** @brief 广告模块打开标识*/
typedef enum 
{
	HIV2AD_SETPID = 1,		//打开广告模块
}D_HIV2AD_Msg_Type;

/** @brief haier 滚动条资源参数*/
typedef struct
{
    D_U16             txt_id;         //每条字幕的id号，用于和服务描述的pic_id对应
		D_U8							flag; 			//用于标识资源有效性
    D_U32             back_color;     //字幕背景颜色
    D_U32             font_color;     //字幕前景颜色
    D_U16             font_size;      //字体大小
    D_U32             language_code;  //字体编码
    D_U8              txt_speed;      //滚动速度
    D_U16             txt_length;     //字幕内容长度
    D_U8              *content;       //字幕内容
}txt_res_info_t;


/** @brief haier 图片资源参数*/
typedef struct
{
	D_U16 				pic_id;			//图片ID
	D_U8					flag;				//用于标识资源有效性
	D_ImageType	  img_type;		//图片类型
	D_U16					pic_width;		//图片宽度
	D_U16					pic_height;		//图片高度
	D_Size				pic_length;		//广告数据长度
	D_U8*					image;			//图片数据
}pic_res_info_t;


/** @brief 资源信息*/
typedef	struct
{
	D_U8										cnt;	//个数
	pic_res_info_t*					pictres;
}pic_resource_info;


/** @brief 资源信息*/
typedef	struct
{
	D_U8										cnt;	//个数
	txt_res_info_t*					txtres;
}txt_resource_info;

/************************************************************************************/
/************************************************************************************/

/** @brief haier 服务描述符参数*/
typedef struct
{
    D_U16             ts_id;      //指定TS流ID
    D_U16             service_id; //指定服务ID
    D_U16             pic_id;     //对应的广告ID,txt时候对应TXTID
}service_id_info_t;

/** @brief haier 广告播放参数*/
typedef	struct											//单条广告显示参数
{
	D_U16 		posx;
	D_U16 		posy;
	D_U16 		disp_w;
	D_U16 		disp_h;
	D_U32			duration;	
}play_paras_t;

/** @brief haier 广告属性参数*/
typedef struct
{
		D_U16 						ad_id;								//广告ID
		D_U8							flag; 								//用于标识资源有效性
		D_U8							ad_ver; 							//广告版本
		D_U8							ad_type;							//广告类型
    play_paras_t      play_paras;     			//广告播放参数
		D_U8							area_cnt;							//广告关联的区域ID的个数
		D_U32 						*area_code; 				  //关联的区域ID
    D_U8              pic_cnt;              //这种类型广告个数
    D_U16   					*pic;
    D_U8              ser_cnt;  						//个数
    service_id_info_t *service;
} ad_paras_info_t;

/************************************************************************************/
/************************************************************************************/

/************************************************************************************/
/************************************************************************************/

/** @brief 作为图像广告的参数结构*/
typedef struct _D_hiv2_fullscan
{
    D_U32          id;          /*图片ID       */
    D_Ad_Data_Type data_type;   /*图片类型*/
    D_Ptr          data_ptr;    /*图片数据指针*/
    D_U32          data_len;    /*图片数据长度*/
    D_U8           erase;   /*图片擦除*/
    D_U16          left;    /*图片左边距*/
    D_U16          top;     /*图片上边距*/
		D_U32 		duration; 
} D_hiv2_fullscan ;

/** @brief 节目参数*/
typedef struct _hiv2ad_program_para
{
    D_U16 usNetworkId;
    D_U16 usTsId;
    D_U16 usServiceId;
} hiv2ad_program_para;

/** @brief OSD显示信息*/
typedef struct _hiv2ad_osd_show_info
{
		D_U32 							txtId;//背景颜色
		D_U32               aucBackgroundColor;//背景颜色
    D_U32               aucDisplayColor;   //字体颜色
    D_U16               usContentSize;        //osd内容长度
    D_U16               usGetBufferSize;
    D_U8*               pucDisplayBuffer;     //osd内容
    D_U16               ucFontType;           //字体类型
    D_U16               ucFontSize;           //字体大小
    D_U8                ucShowTimes;          //显示次数
		D_U8								txtSpeed; 						//总数
		D_U16 							ucstartposx;						//总数
		D_U16 							ucstartposy;						//总数
		D_U16 							ucendposx;						//总数
		D_U16 							ucendposy;						//总数
    D_U8                scrollend;          //显示次数
}hiv2ad_osd_show_info;

/** @brief MG广告OSD显示对外信息接口*/
typedef struct _hiv2ad_osd_prog_show_info
{
	hiv2ad_osd_show_info stTextShow[255];	
	D_U8 ucOsdNum;
}hiv2ad_osd_prog_show_info;

/** @brief 广告用户自定义消息*/
typedef struct 
{
	D_HIV2AD_Msg_Type	type;	/**< 消息类型*/
	D_U32			param1;	/**< 参数1*/
	D_U32			param2;	/**< 参数2*/	
	D_U16			param3;	/**< 参数3*/
} D_HIV2AD_Msg;



extern D_Result hiv2ad_open(D_U8 ucPriority,ADEVENTCALLBACK cb)D_FUNCPOSTFIT;
extern D_Result hiv2ad_Close(void)D_FUNCPOSTFIT;
extern D_Result hiv2ad_SetDataPid(void)D_FUNCPOSTFIT;
extern D_Result hiv2ad_chan_change(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern void d_hiv2ad_ShowMessage(D_U8 ucMessageType, D_U8* pucMessage)D_FUNCPOSTFIT;
extern D_Image *hiv2ad_get_image_by_idx(HIV2_Ad_Pos_Type HiAd_type,hiv2ad_program_para *prog, D_U8 _idx, D_U8 *uctotal, D_U16 *left, D_U16 *top, D_U32 *time)D_FUNCPOSTFIT;
extern D_Result	 hiv2ad_ProgramGetOSD(hiv2ad_program_para prog, hiv2ad_osd_prog_show_info * pstOsdProgramShow)D_FUNCPOSTFIT;
extern D_Result hiv2ad_CallBackOSD(D_U32 txtid)D_FUNCPOSTFIT;
#endif

