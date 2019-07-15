#ifndef _D_SCROLL_H_
#define _D_SCROLL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGraph.h"

typedef D_Handle D_HScroll;

typedef enum _Scroll_Type				/**<滚动条类型*/	
{
	H_SCROLL_RIGHT_TO_LEFT,			/**<单行从右向左滚动*/	
	H_SCROLL_LEFT_TO_RIGHT,			/**<单行从左向右滚动*/	
	V_SCROLL_BOTTOM_TO_TOP,			/**<单列从下向上滚动*/	
	V_SCROLL_TOP_TO_BOTTOM,			/**<单列从上向下滚动*/	
//	MULTI_V_SCROLL_BOTTOM_TO_TOP,	/**<多行从下向上滚动*/	
//	MULTI_V_SCROLL_TOP_TO_BOTTOM,	/**<多行从上向下滚动*/	
}D_ScrollType;

typedef enum _H_Scroll_Direction				/**<滚动方向*/	
{
	H_SCROLL_HORIZONTAL,			/**<水平*/	
	H_SCROLL_VERTICAL,			    /**<垂直*/			
}D_ScrollDirection;

typedef struct {	
	D_Coord				pos_x;			/**< 滚动条显示窗口的起始x坐标*/
	D_Coord				pos_y;			/**< 滚动条显示窗口的起始y坐标*/
	D_Coord				win_w;			/**< 滚动条显示窗口的长度*/
	D_Coord				win_h;			/**< 滚动条显示窗口的高度*/
    D_Coord				win_max_w;		/**< 滚动条显示窗口的最大长度*/
	D_Coord				win_max_h;		/**< 滚动条显示窗口的最大高度*/
    D_ScrollDirection   direction;		/**< 滚动条显示窗口的方向*/
    D_U8*               text;           /**<滚动条显示内容*/
	D_Image*			image;			/**<滚动条显示图片*/
	D_U32				bg_color;		/**<滚动条背景颜色*/
	D_U32				text_color;		/**<滚动条文字颜色*/
    D_U8                font_size;      /**<滚动条文字大小*/    
	//D_U32				transparence;
	D_ScrollType		scroll_type;	/**<滚动条类型*/		
	D_U32				scroll_speed;	/**<滚动条滚动速度*/
	D_U32				repeat_times;	/**<滚动条重复滚动次数*/
	D_U32				duration;		/**<滚动条持续滚动时间*/
    D_U32				repeat_times_duration;/**<滚动条按次数滚动时花费的时间(单位是秒)*/
} D_ScrollUsrParas;

/** @brief 滚动条设备属性*/
typedef struct {
	D_Coord				w;	
	D_Coord				h;
	D_ScrollType			t;
} D_ScrollAttr;

/** @brief 滚动条状态*/
typedef enum 					
{
	SCROLL_IDLE = 1 << 0,					/*滚动条闲置*/
	SCROLL_BEGINNING = 1<<1,				/*滚动开始*/
	SCROLL_CONTINUAL = 1<<2,				/*滚动持续*/
	SCROLL_ENDING = 1<<3,					/*滚动结束,滚动一次结束*/
	SCROLL_DONE = 1<<4 ,					/*滚动任务完成(完成要求的时间或次数)*/
	SCROLL_USED = 1<<5 ,					/*滚动条已经被申请*/
    SCROLL_VALID = 1<<31

}D_ScrollState;

/** @brief 按缺省值初始化滚动条设备属性*/
#define D_SCROLL_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->w = 720;\
		(_a)->h = 30;\
		(_a)->t = H_SCROLL_RIGHT_TO_LEFT;\
	D_MACRO_END

/** @brief 滚动条显示状态*/
extern D_U32 ScrollShowStatus;

typedef D_Result (*D_ScrollCallback)(D_HScroll handle,D_ScrollUsrParas paras,D_ScrollState state);

/** @brief 滚动条管理初始化
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result d_scroll_open(void) D_FUNCPOSTFIT;

/** @brief 滚动条管理退出
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_scroll_close(void) D_FUNCPOSTFIT;

/** @brief 创建一个滚动条
* @param scroll_usr 滚动条配置的相关参数
* @return 成功时返回滚动条句柄,失败时返回D_INVALID_HANDLE
*/
D_HScroll d_scroll_create (D_Coord win_max_w,D_Coord win_max_h,D_ScrollDirection direction)D_FUNCPOSTFIT;

/** @brief 销毁一个滚动条
* @param handle 滚动条句柄
* @return 成功时返回D_OK, 失败返回D_ERR
*/
D_Result d_scroll_destory(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief 滚动条启动
* @param handle 滚动条句柄
* @return 成功时返回D_OK, 失败返回D_ERR
*/
D_Result d_scroll_start(
 D_HScroll handle
,D_Coord win_w  
,D_Coord win_h
,D_ScrollType scroll_type
,D_Coord pos_x		
,D_Coord pos_y		
,D_U8* text		
,D_U32 bg_color	
,D_U32 text_color
,D_U8  font_size
,D_U32 scroll_speed
,D_U32 repeat_times
,D_U32 duration	
,D_Bool immediate
,D_ScrollCallback callback)D_FUNCPOSTFIT;

D_Result d_scroll_start_image(
    D_HScroll handle
    , D_Coord win_w
    , D_Coord win_h
    , D_ScrollType scroll_type
    , D_Coord pos_x
    , D_Coord pos_y
    , D_Image* image
    , D_U32 bg_color
    , D_U32 text_color
    , D_U8  font_size
    , D_U32 scroll_speed
    , D_U32 repeat_times
    , D_U32 duration
    , D_Bool immediate
    , D_ScrollCallback callback)D_FUNCPOSTFIT;

/** @brief 滚动条停止
* @param handle 滚动条句柄
* @return 成功时返回D_OK, 失败返回D_ERR
*/
D_Result d_scroll_stop(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief 滚动条任务的状态
* @param handle 滚动条句柄
* @return 完成时返回D_TRUE, 失败返回D_FALSE
*/
D_ScrollState d_scroll_state(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief 滚动条清除
* @param handle 滚动条句柄
* @return 成功时返回D_OK, 失败返回D_ERR
*/
D_Result d_scroll_clear(D_HScroll handle) D_FUNCPOSTFIT;

D_HScroll hr_test_scroll_create(void)D_FUNCPOSTFIT;
D_Result hr_test_scroll_start(D_HScroll handle)D_FUNCPOSTFIT;
D_Result hr_test_scroll_start2(D_HScroll handle)D_FUNCPOSTFIT;
	
#ifdef  __cplusplus
}
#endif

#endif

