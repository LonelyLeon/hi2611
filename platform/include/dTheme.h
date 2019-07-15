/** @file
* @brief �ؼ���ʾ����ģ��
* @author ����
* @date 2013-8-9 ����: �����ļ�
*/

#ifndef _D_THEME_H_
#define _D_THEME_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dVisual.h"
#include "dFont.h"
#include "dRect.h"
#include "dControl.h"
#include "dMem.h"
#include "dGUI.h"
#include "dGraph.h"
#include "dFrame.h"



/** @brief �ı��������*/
#define TEXT_SHOW_MAX_LINE (100)


/** @brief ��ʾʱ��������*/
typedef struct
{
    D_U16 fontType;     /*��������*/
    D_U16 fontSize;     /*�����С*/
    D_Color fontColor;  /*������ɫ*/
}D_FontAttribute;

/** @brief ��ʾʱ�ı���ʽ*/
typedef struct
{
    D_Bool valid;           /*�Ƿ���Ч*/
    D_U16 align;            /*ˮƽ��ֱ���뷽ʽ*/
    D_Bool multiple;     /*���ж�����ʾ��־*/
    D_Bool fullShow;     /*��������ʾ�Ĵʲ���ʾ*/
    D_Bool pageFlag;    /*��ҳ��ʾ*/
    D_U16 currPage;     /*��ǰҳ��*/
    D_U16 currLine;     /*��ǰ�к�*/
    D_Coord lineSpace;/*�м��*/
}D_TextFormat;


/** @brief ÿ����ʾ��Ϣ*/
typedef struct
{
    D_Char*text;
    D_Size cnt;
    D_Bool  show;
    D_Coord x;
    D_Coord y;
    D_Coord w;
    D_Coord h;
    D_Coord b;   
}D_LineShowInfo;

/** @brief �ı���ʾ��Ϣ*/
typedef struct
{
    D_U16  pageCnt;         /* ��ҳ��*/
    D_U16  lineCnt;         /* ������*/
    D_U16  width;           /* �ܿ��*/
    D_U16  height;          /* �ܸ߶�*/
    D_LineShowInfo lineInfo[TEXT_SHOW_MAX_LINE];
}D_TextShowInfo;

/** @brief ��ʼ������*/
D_Result	d_theme_open (void) D_FUNCPOSTFIT;

/** @brief �ͷ�������Դ*/
D_Result	d_theme_close (void) D_FUNCPOSTFIT;

/** @brief ��������
* @param [in] vis	�ؼ�
* @param [in] rect �������
* @param [in] color ��ɫargb
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	
d_draw_fill_rect (D_Visual *vis, D_Rect *rect, D_Color color) D_FUNCPOSTFIT;

/** @brief ����������ı���Ϣ
* @param [in] vis   �ؼ�(��show_enable == D_FALSEʱ������ΪNULL)
* @param [in] rect ��ʾ����
* @param [in] text �ı�
* @param [in] cnt �ı�����
* @param [in] font ��������
* @param [in] form ��ʽ����
* @param [in] show_enable �Ƿ���ʾ��D_FALSEʱ��ֻ���������Ϣ
* @return �ɹ�������ʾ��¼��ϢD_TextShowInfo,ʧ�ܷ���NULL
* @ remarks ��¼��ϢΪ���ڴ����ṩ֧�֡����续��ꡢ�»��ߵȵȡ�
*/
D_TextShowInfo*
d_draw_text_new(D_Visual *vis, D_Rect *rect, D_Char *text, D_Size cnt, D_FontAttribute *font, D_TextFormat *form, D_Bool show_enable) D_FUNCPOSTFIT;

/** @brief ����������ı���Ϣ
* @param [in] vis   �ؼ�
* @param [in] rect ��ʾ����
* @param [in] text �ı�
* @param [in] cnt �ı�����
* @param [in] font ��������
* @param [in] form ��ʽ����
* @return �ɹ�������ʾ��¼��ϢD_TextShowInfo,ʧ�ܷ���NULL
* @ remarks ��¼��ϢΪ���ڴ����ṩ֧�֡����续��ꡢ�»��ߵȵȡ�
*/
D_TextShowInfo*
d_draw_text(D_Visual *vis, D_Rect *rect, D_Char *text, D_Size cnt, D_FontAttribute *font, D_TextFormat *form) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
