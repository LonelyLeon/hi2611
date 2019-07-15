/** @file
* @brief ͼ���豸����
* @author ����
* @date 2005-7-15 ����: �����ļ�
* @date 2013-03-20 lc: ͳһƽ̨, ��������
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

/** @brief ͼ���豸����*/
typedef struct {
	D_ID		id;	/**< �豸ID*/
} D_GDevAttr;

/** @brief ��ʾģʽ*/
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

/** @brief ��ʾ�豸������*/
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


/** @brief ��ȱʡ���Գ�ʼ��ͼ���豸����*/
#define D_GDEV_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief  ����ͼ���豸ģ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_open (void) D_FUNCPOSTFIT;

/** @brief ����һ��ͼ���豸
* @param attr	ͼ���豸����
* @return �ɹ�����ͼ���豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HGDev		d_gdev_create (D_GDevAttr *attr) D_FUNCPOSTFIT;

/** @brief ����ͼ���豸��ʾģʽ
* @param hgdev	ͼ���豸���
* @param mode		ͼ����ʾģʽ
* @param	x			��ʾ�����
* @param	Y			��ʾ���߶�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_set_mode (D_HGDev hgdev, D_GDevMode mode, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

D_Result d_gdev_set_mode_simple (D_HGDev hgdev, D_GDevMode mode, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

/** @brief ȡ����ʾ�豸��������ַ
* @param hgdev	ͼ���豸���
* @param buf		�����ʾ����������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_get_buffer (D_HGDev hgdev, D_GDevBuffer *buf) D_FUNCPOSTFIT;

/** @brief ������ʾ��ɫ��
* @param hgdev	ͼ���豸���
* @param palette	��ɫ����������
* @param start		���õ���ʼ��ɫ������
* @param cnt			���õ�ɫ����Ŀ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_set_palette (D_HGDev hgdev, D_Color *palette, D_U8 start, D_U16 cnt) D_FUNCPOSTFIT;

/** @brief ����ʾ�������ڵ����ݸ��µ���Ļ
* @param hgdev	ͼ���豸���
* @param Ҫ���µľ�������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_gdev_flip_screen(D_HGDev hgdev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief ����һ����ʾ�豸
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_destroy (D_HGDev hgdev) D_FUNCPOSTFIT;

/** @brief  �ر�ͼ���豸ģ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_gdev_close (void) D_FUNCPOSTFIT;

/** @brief ����OSD��͸����
* @param hgdev	ͼ���豸���
* @param GlobalAlpha	͸����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_gdev_set_global_alpha (D_HGDev hgdev, D_U8 GlobalAlpha) D_FUNCPOSTFIT;

/** @brief ʹ��ͼ���豸ģ��
* @param hgdev	ͼ���豸���
* @param enable	ʹ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_gdev_set_enable (D_HGDev hgdev, D_Bool enable) D_FUNCPOSTFIT;

/** @brief ʹ��ͼ���豸ģ���������
* @param hgdev	ͼ���豸���
* @param enable	ʹ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_gdev_enable_hw_antiflicker(D_HGDev hgdev, D_Bool enable) D_FUNCPOSTFIT;

/** @brief ����ͼ���豸��ʾģʽ��ʽ�仯ʱ��ʹ��
* @param hgdev	ͼ���豸���
* @param	Y			��ʾ���߶�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_gdev_set_param (D_HGDev hgdev, D_Coord y) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
