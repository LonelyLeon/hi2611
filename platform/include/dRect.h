/** @file
* @brief ���β���
* @author ����
* @date 2005-7-28 ����: �����ļ�
* @date 2013-03-21 lc: ͳһƽ̨, ��������
*/

#ifndef _D_RECT_H_
#define _D_RECT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGDev.h"

/** @brief �������ε�λ�ù�ϵ*/
typedef enum {
	D_RECT_POS_IN,	/**< ����һ�������ڲ�*/
	D_RECT_POS_CUT,	/**< �������ཻ*/
	D_RECT_POS_NOT_CUT,	/**< �����β��ཻ*/
	D_RECT_POS_OUT	/**< �����β��ཻ*/
} D_RectPos;

#define D_FAST_RECT_OP	1

/** @brief �趨����
* @param r	���νṹ
* @param x	x����
* @param y	y����
* @param w	���ο��
* @param h	���θ߶�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ��������
* @param dr	Ŀ�����
* @param sr	Դ����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
#if D_FAST_RECT_OP
#define d_rect_copy(_dr,_sr)\
		D_MACRO_BEGIN\
			(*(_dr)=*(_sr));\
		D_MACRO_END
#else
D_Result	d_rect_copy (D_Rect *dr, D_Rect *sr) D_FUNCPOSTFIT;
#endif

/** @brief �������
* @param r	���νṹ
* @param off	�����������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ��С����
* @param r	���νṹ
* @param off	��С��������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief �����εĲ����Ƿ���Ч
* @param r	���νṹ
* @return ��Ч����D_TRUE,��Ч����D_FALSE
*/
#if D_FAST_RECT_OP
#define d_rect_valid(_r)\
		(((D_U32)(_r) != 0) && ((_r)->w>0) && ((_r)->h>0))
#else
D_Bool		d_rect_valid (D_Rect *r) D_FUNCPOSTFIT;
#endif

/** @brief �ƶ�����
* @param r	���νṹ
* @param xoff	X����ƫ�Ƶ�������
* @param yoff	Y����ƫ�Ƶ�������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief �����������εĽ���
* @param result	���ؽ�������
* @param r1	����1
* @param r2	����2
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_rect_cut (D_Rect *result, D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

/** @brief �����������εĲ���
* @param result	���ز�������
* @param r1	����1
* @param r2	����2
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_rect_union (D_Rect *result, D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

/** @brief ���һ�����Ƿ��ھ�����
* @param r	���νṹ
* @param x	���x����
* @param y	���y����
* @return ���ھ����ڷ���D_TRUE,���ھ����ڷ���D_FALSE
*/
#if D_FAST_RECT_OP
#define d_rect_point_in(_r,_x,_y)\
		(!(((_x) < (_r)->x) || ((_x) >= (_r)->x + (_r)->w) || ((_y) < (_r)->y) || ((_y) >= (_r)->y + (_r)->h)))
#else
D_Bool		d_rect_point_in (D_Rect *r, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
#endif

/** @brief �����������ε�λ�ù�ϵ
* @param r1	����1
* @param r2	����2
* @return	���ؾ���λ�ù�ϵ
*/
D_RectPos	d_rect_check_pos (D_Rect *r1, D_Rect *r2) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
