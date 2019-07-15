/** @file
* @brief Subtitle控制
* @author 刘伟峰
* @date 2013-11-18 刘伟峰: 建立文件
*/
#ifndef __D_SUBTITLE_H__
#define __D_SUBTITLE_H__
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dScan.h"
#include "dFrame.h"
#include "dGUI.h"
#include "dGraph.h"
#include "dGDev.h"
#include "dVisual.h"


#define REGION_NUM				5		//一个page包含的region数目 
#define PALLETTE_NUM			256 	//色板大小
#define OBJECT_NUM				5		//一个region包含的object数目
#define PIXEL_PTR_LENGTH		1000
#define D_SUB_PES_MAX_LENGTH	0x6000	//设定PES包的最大长度


// 错误类型
typedef enum
{
	P_SUB_PMT_ERROR,
	P_SUB_PES_ERROR,
	P_SUB_UNKNOW_ERROR		
}D_Sub_Error_Type;

/** @brief 频道搜索任务配置(自动/手动)*/
typedef struct
{
	D_HQueue hqueue;			/*注册任务消息队列*/
	D_S8 	priority;
	D_U8 	*lang;
	D_U16 	pid;
	D_U8 	type;	
	D_U16	com_page_id;
	D_U16	anc_page_id;
} D_SubTaskConfig;

enum	//页的三种状态
{
	NORMAL_CASE,	
	ACQUISITON_POINT,
	MODE_CHANGE,
	RESERVED,
};

/** @brief 定义Object属性*/ //参考ets300743
typedef struct ObjectStruct_s
{
	D_U16 object_id;
	D_U8 object_type;					
	D_U8 object_provider_flag;
	D_U16 object_horizontal_position;//object 水平地址
	D_U16 object_vertical_position;		//object 垂直地址
	D_U8 foreground_pixel_code;
	D_U8 background_pixel_code;
}ObjectStruct_t;

/** @brief 定义页属性*/	//参考ets300743
typedef struct CompositionStruct_s
{
	D_U8 region_id;						
//	D_U16 region_horizontal_address;//区域垂直地址
//	D_U16 region_vertical_address;	//区域水平地址
	D_U8 region_fill_flag;
	D_U8 region_level_of_compatibility;
	D_U8 region_depth;
//	D_U16 region_width;				//区域宽度
//	D_U16 region_height;			//区域高度
	D_U8 CLUT_id;
	ObjectStruct_t object_group[OBJECT_NUM];
	D_Image	*region_img;				//区域数据buffer
	D_U32 Pixel_Position;			//象素个数
	D_Rect dr;
	D_Rect sr;
}CompositionStruct_t;

/** @brief 定义色板属性*/
typedef struct	PalletteStruct_s
{
	D_U8 Y;
	D_U8 Cb;
	D_U8 Cr;
	D_U8 weight;
}PalletteStruct_t;

typedef struct Color_s
{
	D_U8 R;
	D_U8 G;
	D_U8 B;
	D_U8 bSolid;
}Color_t;

/** @brief subtitle搜索资源*/
typedef struct
{
    D_U32       table_mode;		/**@brief < 过滤表的table id*/
	D_HQueue 	hqueue;			/*注册任务消息队列*/
    D_U8        *buf;			/**@brief < 为搜索分配的内存地址*/
    D_U8        *sec;			/**@brief < 过滤demux接收的数据*/
    D_HDemux    hdemuxpes;		/**@brief< 搜 索 的Demux句柄*/
    D_HMMan     hmm;			/**@brief < 为搜索分配的内存创建的内存管理器句柄*/
    D_HMMan     hsi_mm;		    /**@brief< 解析时申请内存用的内存管理器句柄*/
    D_HApp      hsub;			/**@brief< 搜索应用句柄*/
	D_U8 		lang[3];           /**@brief< 控制语言*/
	D_U16 		pid;
	D_U8 		type;	
	D_U16		com_page_id;
	D_U16		anc_page_id;

	D_U8* PixelPtr; 				//象素缓存区
	D_U16 		page_id;       
	D_U8 page_state;  
	CompositionStruct_t CompositionPtr[REGION_NUM];		 //页属性结构体
	PalletteStruct_t	SubtitlePallette[REGION_NUM][PALLETTE_NUM];//色板缓存区
	D_U32	SubPal[REGION_NUM][PALLETTE_NUM];//色板缓存区2
	D_U8 region_num;				//区域号
	D_U8 clut_num;					//色板个数
	D_U8 CLUT_IDT[REGION_NUM];		//色板ID
	D_U8 clut_num_array[REGION_NUM];		//色板个数
	D_U8 RegionID[REGION_NUM];		//区域ID
	D_U8 object_num[REGION_NUM];		//每个区域内object的个数
	D_U8 regionshownum;				//当前region
	D_U8 byte_flag;					//字节标志
	D_U16 pixel_num;				//象素个数
	D_U16 pixelcount;				//象素处理个数
	D_U32 PixePos;					//象素个数
	D_U8 linenum;					//线个数
	D_U8 HideColor;	
	D_U32 tpage_time_out;
} D_SUBESData;

/** @brief 定义显示接口*/
typedef struct	sub_osd_img_s
{
	D_U8 region_num;				//区域数
	D_Image	*region_img[REGION_NUM];				//区域数据buffer
	D_Rect dr[REGION_NUM];
	D_U32 tpage_time_out;
	D_S32 pts;
	D_U8 page_state;  	
}sub_osd_img_t;


/** @brief创建Subtitle搜索任务
* @param[in] priority 任务优先级
* @return 成功返回设备句柄,失败返回D_INVALID_HANDLE
*/
D_HScan d_sub_scan_create(D_SubTaskConfig taskconfig)D_FUNCPOSTFIT ;

D_Result d_sub_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT;

/** @brief 获得字幕数资源指针*/
sub_osd_img_t * p_get_subtitle_resource(void)D_FUNCPOSTFIT;

/** @brief 获取字幕数据解析完成标记*/
D_Bool p_get_sub_ready_flag(void)D_FUNCPOSTFIT;

/** @brief 初始化字幕数据解析完成标记*/
void p_reset_sub_ready_flag(void)D_FUNCPOSTFIT;

sub_osd_img_t * p_get_sub_last_osd(void)D_FUNCPOSTFIT;

void p_set_sub_last_osd(sub_osd_img_t *sub)D_FUNCPOSTFIT;


/** @brief 为显示而设置subtitle数据
* @param[in] es 资源指针
*/

#ifdef  __cplusplus
}
#endif
#endif
