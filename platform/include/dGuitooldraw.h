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

/*Բ�Ƿ�λ����, �ο����涨��*/
#define D_ROUND_TYPE_UP_LEFT (1)
#define D_ROUND_TYPE_UP_RIGHT (2)
#define D_ROUND_TYPE_DOWN_RIGHT (4)
#define D_ROUND_TYPE_DOWN_LEFT (8)


/** @brief �趨͸����
* @param vis	�ؼ�������
* @param trans  ͸����
*/
D_Result gui_tool_set_transparency(D_Visual *vis, D_U8 trans) D_FUNCPOSTFIT;


/** @brief ��ֱ��
* @param vis	�ؼ�������
* @param x1,y1,x2,y2  �ڿؼ��ϵ�������յ�λ��
* @param color �����ɫֵARGB
*/
D_Result gui_tool_draw_line(D_Visual *vis, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2, D_Color color) D_FUNCPOSTFIT;

/** @brief ��ֱ�Ǿ��α߿�
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param border	�߿���
* @param color �����ɫֵARGB
*/
D_Result gui_tool_draw_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord border, D_Color color) D_FUNCPOSTFIT;

/** @brief ��ֱ��������
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param color �����ɫֵARGB
*/
D_Result gui_tool_draw_fill_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Color color) D_FUNCPOSTFIT;

/** @brief ��Բ�Ǿ��α߿�
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param color �����ɫֵARGB
* @param rad Բ�ǰ뾶( 0 ��Ϊֱ��)
* @param border	�߿���
*/
D_Result gui_tool_draw_round_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Coord border, D_Color color) D_FUNCPOSTFIT;

/** @brief ��Բ�Ǿ��α߿�(ѡ��Բ��)
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param color �����ɫֵARGB
* @param rad Բ�ǰ뾶
* @param border	�߿���
* @param round_type ѡ��Բ������(0~3bit)
*/
D_Result gui_tool_draw_round_rect_sel(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Coord border, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;

/** @brief �����Բ�Ǿ���
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param color �����ɫֵARGB
* @param left_top_rad ���Ͻ�Բ�ǰ뾶( 0 ��Ϊֱ��)
*/
D_Result gui_tool_draw_fill_round_rect(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Color color)D_FUNCPOSTFIT;

/** @brief �����Բ�Ǿ��α߿�(ѡ��Բ��)
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param color �����ɫֵARGB
* @param rad Բ�ǰ뾶
* @param round_type ѡ��Բ������(0~3bit)
*/
D_Result gui_tool_draw_fill_round_rect_sel(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord rad, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;

/** @brief ��Բ��(ѡ��λ)
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С(������Բ�����о���λ��)
* @param color �����ɫֵARGB
* @param round_type ѡ��Բ������1��2��4��8
*/
D_Result gui_tool_draw_arc(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, D_Coord border, D_Color color, D_U32 round_type) D_FUNCPOSTFIT;


/** @brief ��ͼƬ
* @param vis	�ؼ�������
* @param x,y,w,h  �ڿؼ��ϵ�λ�ô�С
* @param imgid	ͼƬid
* @param imgx,imgy,imgw,imgh  ͼƬ����������
*/
D_Result gui_tool_draw_image(D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h, 
								D_ImageID imgid, D_Coord imgx, D_Coord imgy, D_Coord imgw, D_Coord imgh) D_FUNCPOSTFIT;


/** @brief ������
* @param vis	�ؼ�������
* @param x,y �ڿؼ��ϵ�λ��(���½�����)
* @param textid	�ı�id
* @param text	�ı�
* @param len	�ı�����
* @param color �����ɫֵARGB
ע: ��textidΪ(-1) ʱ��ʾtext
*/
D_Result gui_tool_draw_text(D_Visual *vis, D_Coord x, D_Coord y, D_TextID textid, D_Char *text, D_Color color) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_TOOL_DRAW_FILE_
