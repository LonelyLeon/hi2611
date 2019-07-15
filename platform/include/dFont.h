/**@defgroup font �ֿ�
*@{*/
/** @file
* @brief �������
* @author
* @date 2013-03-25 lc: ͳһƽ̨, ��������
*/

#ifndef _D_FONT_H_
#define _D_FONT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dCharset.h"

/** @brief �ֿ����Ͷ��� */
typedef enum
{
	D_FONT_DIANZHEN_ASCII = 0,
	D_FONT_DIANZHEN_HANZI,
	D_FONT_DIANZHEN_OTHER,
	D_FONT_FREETYPE,
}D_FontEngine;

typedef struct _D_Font	D_Font;

/** @brief �ַ�ģ*/
typedef struct
{
    D_U8    *mask;      /*��ģ����*/
    D_S8     left;      /*��ģ�ڿ���е�x���꣨���أ�*/
    D_S8     top;       /*��ģ�ڿ���е�y���꣨���أ�*/
    D_S8     width;     /*��ģ�����أ�*/
    D_S8     height;    /*��ģ�ߣ����أ�*/
    D_U8     bpp;       /*�ַ�ͼƬ�����Ǽ�λɫ��1������*/
    D_U16    pitch;     /*һ����������ռ�����ֽ�*/
} D_FontCharMask;

/** @brief ���嶨��*/
typedef struct
{
	D_FontEngine font_type;
	D_Charset cset;
	D_S32 size;
	D_U8 *font_data;
	D_Size font_data_size;
    
       /*�ⲿ�ֿ�ʹ��*/
       D_Ptr    font_op;
} D_FontDesc;

typedef struct
{
	D_Result	(*init) (D_Font *fnt, D_FontDesc *fnt_desc) D_FUNCPOSTFIT;
	D_Result	(*deinit) (D_Font *fnt) D_FUNCPOSTFIT;
	D_Result	(*char_size) (D_Font *fnt, D_Char *chr, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;
	D_Result	(*get_char) (D_Font *fnt, D_Char *chr, D_FontCharMask *mask) D_FUNCPOSTFIT;
	D_Result	(*set_size)	(D_Font *fnt, D_U32 size) D_FUNCPOSTFIT;
#ifdef D_GUI_FREETYPE_CACHE_IMAGE_MODEL
    D_Result    (*put_char)(D_Font *fnt, D_GSurface *dev, D_Char *chr, D_Coord x, D_Coord y, D_Color *palette[]) D_FUNCPOSTFIT;
#endif
} D_FontOp;

struct _D_Font
{
	const D_FontOp	*op;
	D_Charset cset;
	D_U32 size;
	D_Ptr obj;
};

/** @brief ��ʼ������ϵͳ*/
D_Result	d_font_open (void) D_FUNCPOSTFIT;

/** @brief �ر�����ϵͳ*/
D_Result	d_font_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���ֿ�
* @param[in] attr ���嶨��ָ��
* @return fnt �ֿ�ָ��
*/
D_Font* d_font_create(D_FontDesc *attr) D_FUNCPOSTFIT;

/** @brief ж��һ���ֿ� 
* @param[in] fnt �ֿ�ָ��
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_font_destroy(D_Font *fnt) D_FUNCPOSTFIT;

/** @brief �趨��ǰ����
* @param[in] fnt �ֿ�ָ��
* @param[in] size �����С
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_font_set (D_Font *fnt, D_U32 size) D_FUNCPOSTFIT;

/** @brief ��ȡһ�����ʵ��ֿ�
* @param[in] cset �ַ���
* @return ����ָ��
*/
D_Font* d_font_get_font (D_Charset cset) D_FUNCPOSTFIT;

/** @brief �趨���������С
* @param[in] size �����С
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_font_set_size (D_U32 size) D_FUNCPOSTFIT;

/** @brief ����������ɫ
* @param[in] color �ֿ���ɫ
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_font_set_color(D_Color color) D_FUNCPOSTFIT;

/** @brief ȡһ���ַ��ĳߴ�
* @param[in] cset	�ַ���
* @param[in] chr	��ʾ�ַ�ָ��
* @param[out] w		�����ַ����
* @param[out] h		�����ַ��߶�
* @param[out] b		�����ַ�����λ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_font_char_size (D_Charset cset, D_Char *chr, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief �ڻ�ͼ�����ϻ���һ���ַ�
* @param[in] dev	��ʾ����
* @param[in] cset	�ַ���
* @param[in] chr	Ҫ��ʾ���ַ�
* @param[in] x		��ʾ������
* @param[in] y		��ʾ������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_font_put_char (D_GSurface *dev, D_Charset cset, D_Char *chr, D_Coord x, D_Coord y, D_FontAttrType type) D_FUNCPOSTFIT;

/** @brief ����һ���ַ����Ĵ�С
* @param[in] text	�ַ���
* @param[in] cnt	�ַ�������
* @param[out] w		�����ַ������
* @param[out] h		�����ַ����߶�
* @param[out] b		�����ַ�������λ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_font_text_size (D_Char *text, D_Size cnt, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief ��һ���ڼ���һ���ַ����Ĵ�С
* @param[in] text	�ַ���ָ���ַ
* @param[in] cnt	�ַ�������
* @param[in] rw		�п�
* @param[in] last	�Ƿ���㱻���е����һ���ַ�
* @param[out] w		�����ַ������
* @param[out] h		�����ַ����߶�
* @param[out] b		�����ַ�������λ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_font_text_size_in_range (D_Char **text, D_Size cnt, D_Coord rw, D_Bool last, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief ����һ���ַ������ض��Ŀ������������ʾ�Ĵ�С�������ֽ���
* @param[in] text	�ַ���
* @param[in] cnt	�ַ�������
* @param[in] width		�ַ���Լ�����
* @param[out] w		�����ַ���ʵ�ʿ��
* @param[out] h		�����ַ����߶�
* @param[out] b		�����ַ�������λ��
* @return �ɹ����ؿ���������ʾ���ֽ���,��������
*/
D_Size
d_font_text_cnt_in_range (D_Char *text, D_Size cnt,D_Size width, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief ȡ����Ƨ����ʾ�������ַ���
* @param[in] cset �洢���ص��ַ���
* @return ������ʾ����ָ�����ַ���
*/
D_Char*
d_font_get_unknown_char_and_cset (D_Charset *cset) D_FUNCPOSTFIT;

/** @brief ������Ƨ����ʾ�������ַ���
* @param[in] cset ��Ƨ���ַ���
* @param[in] unknown_char �����Ƨ�ֵı���
* @return ����D_OK
*/
D_Result d_font_set_unknown_char_and_cset (D_Charset cset, const D_Char *unknown_char) D_FUNCPOSTFIT;

/** @brief �ڻ�ͼ�����ϻ���һ���ַ�ͼ�Ľӿ�ר��
* @param[in] dev	��ʾ����
* @param[in] cset	�ַ���
* @param[in] chr	Ҫ��ʾ���ַ�
* @param[in] x		��ʾ������
* @param[in] y		��ʾ������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_font_put_char_ttx (D_GSurface *dev, D_U8 * charLib, D_U8 txt, D_U16 x, D_U16 y, D_U8 pix_W, D_U8 pix_H,D_U8 SizeMode) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
