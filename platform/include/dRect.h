/** @file
* @brief 矩形操作
* @author 龚克
* @date 2005-7-28 龚克: 建立文件
* @date 2013-03-21 lc: 统一平台, 代码整理
*/

#ifndef _D_RECT_H_
#define _D_RECT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGDev.h"

/** @brief 两个矩形的位置关系*/
typedef enum {
	D_RECT_POS_IN,	/**< 在另一个矩形内部*/
	D_RECT_POS_CUT,	/**< 两矩形相交*/
	D_RECT_POS_NOT_CUT,	/**< 两矩形不相交*/
	D_RECT_POS_OUT	/**< 两矩形不相交*/
} D_RectPos;

#define D_FAST_RECT_OP	1

/** @brief 设定矩形
* @param r	矩形结构
* @param x	x坐标
* @param y	y坐标
* @param w	矩形宽度
* @param h	矩形高度
* @return 成功返回D_OK,失败返回D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_set(_r,_x,_y,_w,_h)\
		D_MACRO_BEGIN\
			(_r)->x=(_x);\
			(_r)->y=(_y);\
			(_r)->w=(_w);\
			(_r)->h=(_h);\
		D_MACRO_END
#else
D_Result	d_rect_set (D_Rect *r, D_Coord x, D_Coord y, D_Coord w, D_Coord h) D_FUNCPOSTFIT;
#endif

/** @brief 拷贝矩形
* @param dr	目标矩形
* @param sr	源矩形
* @return 成功返回D_OK,失败返回D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_copy(_dr,_sr)\
		D_MACRO_BEGIN\
			(*(_dr)=*(_sr));\
		D_MACRO_END
#else
D_Result	d_rect_copy (D_Rect *dr, D_Rect *sr) D_FUNCPOSTFIT;
#endif

/** @brief 扩大矩形
* @param r	矩形结构
* @param off	扩大的像素数
* @return 成功返回D_OK,失败返回D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_enlarge(_r,_o)\
		D_MACRO_BEGIN\
			(_r)->x -= (_o);\
			(_r)->y -= (_o);\
			(_r)->w += ((_o) << 1);\
			(_r)->h += ((_o) << 1);\
		D_MACRO_END
#else
D_Result	d_rect_enlarge (D_Rect *r, D_Coord off) D_FUNCPOSTFIT;
#endif

/** @brief 缩小矩形
* @param r	矩形结构
* @param off	缩小的像素数
* @return 成功返回D_OK,失败返回D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_reduce(_r,_o)\
		D_MACRO_BEGIN\
			(_r)->x += (_o);\
			(_r)->y += (_o);\
			(_r)->w -= ((_o) << 1);\
			(_r)->h -= ((_o) << 1);\
		D_MACRO_END
#else
D_Result	d_rect_reduce (D_Rect *r, D_Coord off) D_FUNCPOSTFIT;
#endif

/** @brief 检查矩形的参数是否有效
* @param r	矩形结构
* @return 有效返回D_TRUE,无效返回D_FALSE
*/
#if D_FAST_RECT_OP
#define d_rect_valid(_r)\
		(((D_U32)(_r) != 0) && ((_r)->w>0) && ((_r)->h>0))
#else
D_Bool		d_rect_valid (D_Rect *r) D_FUNCPOSTFIT;
#endif

/** @brief 移动矩形
* @param r	矩形结构
* @param xoff	X坐标偏移的像素数
* @param yoff	Y坐标偏移的像素数
* @return 成功返回D_OK,失败返回D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_offset(_r,_x,_y)\
		D_MACRO_BEGIN\
			(_r)->x += (_x);\
			(_y)->y += (_y);\
		D_MACRO_END
#else
D_Result	d_rect_offset (D_Rect *r, D_Coord xoff, D_Coord yoff) D_FUNCPOSTFIT;
#endif

/** @brief 计算两个矩形的交集
* @param result	返回交集矩形
* @param r1	矩形1
* @param r2	矩形2
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_rect_cut (D_Rect *result, D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

/** @brief 计算两个矩形的并集
* @param result	返回并集矩形
* @param r1	矩形1
* @param r2	矩形2
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_rect_union (D_Rect *result, D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

/** @brief 检查一个点是否在矩形内
* @param r	矩形结构
* @param x	点的x坐标
* @param y	点的y坐标
* @return 点在矩形内返回D_TRUE,不在矩形内返回D_FALSE
*/
#if D_FAST_RECT_OP
#define d_rect_point_in(_r,_x,_y)\
		(!(((_x) < (_r)->x) || ((_x) >= (_r)->x + (_r)->w) || ((_y) < (_r)->y) || ((_y) >= (_r)->y + (_r)->h)))
#else
D_Bool		d_rect_point_in (D_Rect *r, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
#endif

/** @brief 计算两个矩形的位置关系
* @param r1	矩形1
* @param r2	矩形2
* @return	返回矩形位置关系
*/
D_RectPos	d_rect_check_pos (D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
