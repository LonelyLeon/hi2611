/** @file
* @brief 图形设备操作
* @author 龚克
* @date 2005-7-15 龚克: 建立文件
* @date 2013-03-20 lc: 统一平台, 代码整理
*/

#ifndef _D_GDEV_H_
#define _D_GDEV_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

typedef D_Handle	D_HGDev;
typedef D_U32		D_Pixel;
typedef D_U32		D_Color;

#define D_RGBA(r,g,b,a) \
		(((D_U32)b) | (((D_U32)g) << 8) | (((D_U32)r) << 16) | (((D_U32)a) << 24))
#define D_RGB(r,g,b)	D_RGBA(r, g, b, 0xFF)
#define D_BLUE(c)		((D_U8)((c) & 0xFF))
#define D_GREEN(c)		((D_U8)(((c) >> 8) & 0xFF))
#define D_RED(c)		((D_U8)(((c) >> 16) & 0xFF))
#define D_ALPHA(c)		((D_U8)(((c) >> 24) & 0xFF))

//breif roundRect lxing_20130520
typedef enum{
	UP_LEFT = 1,
	UP_RIGHT = 2,
	DOWN_RIGHT = 4,
	DOWN_LEFT = 8
}D_RoundRectType;
		    
typedef struct {
	D_Coord		x;
	D_Coord		y;
} D_Point;

typedef struct {
	D_Coord		x;
	D_Coord		y;
	D_Coord		w;
	D_Coord		h;
} D_Rect;

/** @brief 图形设备属性*/
typedef struct {
	D_ID		id;	/**< 设备ID*/
} D_GDevAttr;

/** @brief 显示模式*/
typedef enum {
	D_GDEV_MODE_1BPP = 0,
	D_GDEV_MODE_2BPP,
	D_GDEV_MODE_4BPP,
	D_GDEV_MODE_8BPP,
	D_GDEV_MODE_16BPP_565,
	D_GDEV_MODE_16BPP,
	D_GDEV_MODE_16BPP_1555 = D_GDEV_MODE_16BPP,
	D_GDEV_MODE_16BPP_4444,
	D_GDEV_MODE_24BPP,
	D_GDEV_MODE_24BPP_8565,
	D_GDEV_MODE_24BPP_6666,
	D_GDEV_MODE_32BPP,
	D_GDEV_MODE_32BPP_BGRA,	
} D_GDevMode;

#define D_GDEV_MODE_HAVE_PALETTE(_m)	((_m) < D_GDEV_MODE_16BPP_565)

/** @brief 显示设备缓冲区*/
typedef struct {
	D_GDevMode mode;
	D_U8 bpp;	/*8b*/
	D_U8 Bpp;
	D_Coord	width;/*16b*/
	D_Coord	height;
	D_Coord	pitch;
	D_U8 *buf;
	D_Ptr drv_obj;
} D_GDevBuffer;


/** @brief 按缺省属性初始化图形设备属性*/
#define D_GDEV_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief  启动图形设备模块
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_open (void) D_FUNCPOSTFIT;

/** @brief 创建一个图形设备
* @param attr	图形设备属性
* @return 成功返回图形设备句柄，失败返回D_INVALID_HANDLE
*/
D_HGDev		d_gdev_create (D_GDevAttr *attr) D_FUNCPOSTFIT;

/** @brief 设置图形设备显示模式
* @param hgdev	图形设备句柄
* @param mode		图形显示模式
* @param	x			显示区宽度
* @param	Y			显示区高度
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_set_mode (D_HGDev hgdev, D_GDevMode mode, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

D_Result d_gdev_set_mode_simple (D_HGDev hgdev, D_GDevMode mode, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

/** @brief 取得显示设备缓冲区地址
* @param hgdev	图形设备句柄
* @param buf		存放显示缓冲区数据
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_get_buffer (D_HGDev hgdev, D_GDevBuffer *buf) D_FUNCPOSTFIT;

/** @brief 设置显示调色板
* @param hgdev	图形设备句柄
* @param palette	调色板数据数组
* @param start		设置的起始调色板索引
* @param cnt			设置调色板数目
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_set_palette (D_HGDev hgdev, D_Color *palette, D_U8 start, D_U16 cnt) D_FUNCPOSTFIT;

/** @brief 将显示缓冲区内的数据更新到屏幕
* @param hgdev	图形设备句柄
* @param 要更新的矩形区域
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_gdev_flip_screen(D_HGDev hgdev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 销毁一个显示设备
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_destroy (D_HGDev hgdev) D_FUNCPOSTFIT;

/** @brief  关闭图形设备模块
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gdev_close (void) D_FUNCPOSTFIT;

/** @brief 设置OSD层透明度
* @param hgdev	图形设备句柄
* @param GlobalAlpha	透明度
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_gdev_set_global_alpha (D_HGDev hgdev, D_U8 GlobalAlpha) D_FUNCPOSTFIT;

/** @brief 使能图形设备模块
* @param hgdev	图形设备句柄
* @param enable	使能
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_gdev_set_enable (D_HGDev hgdev, D_Bool enable) D_FUNCPOSTFIT;

/** @brief 使能图形设备模块防闪功能
* @param hgdev	图形设备句柄
* @param enable	使能
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_gdev_enable_hw_antiflicker(D_HGDev hgdev, D_Bool enable) D_FUNCPOSTFIT;

/** @brief 设置图形设备显示模式制式变化时候使用
* @param hgdev	图形设备句柄
* @param	Y			显示区高度
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_gdev_set_param (D_HGDev hgdev, D_Coord y) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
