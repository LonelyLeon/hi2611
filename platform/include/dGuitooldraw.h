#ifndef _GUI_TOOL_DRAW_FILE_
#define	_GUI_TOOL_DRAW_FILE_


#ifdef  __cplusplus
extern "C"
{
#endif

#include "dRect.h"
#include "dGUI.h"
#include "dGraph.h"
#include "dFrame.h"

/*
typedef enum{
	UP_LEFT = 1,
	UP_RIGHT = 2,
	DOWN_RIGHT = 4,
	DOWN_LEFT = 8
}D_RoundRectType;
*/

/*圆角方位类型, 参考上面定义*/
#define D_ROUND_TYPE_UP_LEFT (1)
#define D_ROUND_TYPE_UP_RIGHT (2)
#define D_ROUND_TYPE_DOWN_RIGHT (4)
#define D_ROUND_TYPE_DOWN_LEFT (8)


/** @brief 设定透明度
* @param vis	控件可视体
* @param trans  透明度
*/
D_Result gui_tool_set_transparency(D_Visual *vis, D_U8 trans) D_FUNCPOSTFIT;


/** @brief 画直线
* @param vis	控件可视体
* @param x1,y1,x2,y2  在控件上的起点与终点位置
* @param color 填充颜色值ARGB
*/
D_Result gui_tool_draw_line(D_Visual *vis, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2, D_Color color) D_FUNCPOSTFIT;

/** @brief 画直角矩形边框
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param border	边框厚度
* @param color 填充颜色值ARGB
*/
D_Result gui_tool_draw_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord border, D_Color color) D_FUNCPOSTFIT;

/** @brief 画直角填充矩形
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param color 填充颜色值ARGB
*/
D_Result gui_tool_draw_fill_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Color color) D_FUNCPOSTFIT;

/** @brief 画圆角矩形边框
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param color 填充颜色值ARGB
* @param rad 圆角半径( 0 即为直角)
* @param border	边框厚度
*/
D_Result gui_tool_draw_round_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Coord border, D_Color color) D_FUNCPOSTFIT;

/** @brief 画圆角矩形边框(选择圆角)
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param color 填充颜色值ARGB
* @param rad 圆角半径
* @param border	边框厚度
* @param round_type 选择圆角类型(0~3bit)
*/
D_Result gui_tool_draw_round_rect_sel(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Coord border, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;

/** @brief 画填充圆角矩形
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param color 填充颜色值ARGB
* @param left_top_rad 左上角圆角半径( 0 即为直角)
*/
D_Result gui_tool_draw_fill_round_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Color color)D_FUNCPOSTFIT;

/** @brief 画填充圆角矩形边框(选择圆角)
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param color 填充颜色值ARGB
* @param rad 圆角半径
* @param round_type 选择圆角类型(0~3bit)
*/
D_Result gui_tool_draw_fill_round_rect_sel(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;

/** @brief 画圆弧(选择方位)
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小(弧所在圆的外切矩形位置)
* @param color 填充颜色值ARGB
* @param round_type 选择圆角类型1，2，4，8
*/
D_Result gui_tool_draw_arc(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord border, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;


/** @brief 画图片
* @param vis	控件可视体
* @param x,y,w,h  在控件上的位置大小
* @param imgid	图片id
* @param imgx,imgy,imgw,imgh  图片的数据区域
*/
D_Result gui_tool_draw_image(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, 
								D_ImageID imgid, D_Coord imgx, D_Coord imgy, D_Coord imgw, D_Coord imgh) D_FUNCPOSTFIT;


/** @brief 画文字
* @param vis	控件可视体
* @param x,y 在控件上的位置(左下角坐标)
* @param textid	文本id
* @param text	文本
* @param len	文本长度
* @param color 填充颜色值ARGB
注: 当textid为(-1) 时显示text
*/
D_Result gui_tool_draw_text(D_Visual *vis, D_Coord x, D_Coord y, D_TextID textid, D_Char *text, D_Color color) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_TOOL_DRAW_FILE_
