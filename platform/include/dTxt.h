/** @file
* @brief  txt�ӿ�
* @author 
* @date 
*/

#ifndef __TXT_H_
#define __TXT_H_

#ifdef  __cplusplus
extern "C"
{
#endif


#include "dTypes.h"
#include "dVisual.h"

#define	TXT_USE_LANG_CHN	1
#define	TXT_USE_LANG_CHN2500_SIMPLE	0
#define	TXT_USE_LANG_CHN2500_TRADITION	0

#define ROW_INDEX_MAX   (120)  /*���������ֵ*/
#define TXT_READ_MAX    (ROW_INDEX_MAX * 128)  /*ÿ�ζ��������txt����*/
#define TAG_STR_MAX     14 	/*��ǩ�ַ�����󳤶�*/

#define TXT_TAG_NUM     5	/*��ǩ����*/
#define TXT_SEG_NUM     500	/*.....*/

#define 	TXT_MAX_MALLOC_LENGTH   (16 * 1024)	/*TXT�ռ���Ҫ�����ڵ���*/


#define DU8(x)                  (*(D_U8  *)(D_U32)(x))

/** @brief txt����������*/	
typedef enum{
    TXT_NONE,
    TXT_INIT_SHOW,
    TXT_LINE_PRE,
    TXT_LINE_NEXT,
    TXT_PAGE_UP,
    TXT_PAGE_DOWN,
}D_TxtOpertionType;


/** @brief txt��������*/	
typedef enum{
    UNICODE_UTF8,
    UNICODE_BE,
    UNICODE_LE,
    ANSI,
}D_TxtEncodeType;


/** @brief �ַ���������*/	
typedef enum{
    ASCII = 0,
    GB2312,
    UNICODE
}D_CharacterEncodeMode;

/** @brief ÿ��txt�ļ������ݶ���ṹ*/	
typedef struct {
    D_U32 rowIndex;	/*�����*/
    D_U32 rowBeginAddr;	/*�������ݵ���ʼ��ַ*/
    D_U8  rowLength;  /*���е����ݳ���*/ // contain "enter" 
    D_U32 offset_in_file;/*�������ļ��е�ƫ��*/
}D_TxtRow;


/** @brief txt �ļ��ı�ǩ���� */	
typedef struct{
    D_U8  Flag;
    D_U32 Seg;
    D_U32 Row;
    D_U8  HeadStr[TAG_STR_MAX];
}D_TxtTag;

/** @brief txt �ļ���������ö���*/	
typedef struct{
    D_U32 StartCluster;
    D_U32 LastWrite;
    D_U32 CurSeg;	/*��ǰ�κ�*/
    D_U32 CurRow;	 /*��ǰ�к�*/
    D_U8  TagCnt;	/*��ǩ����*/
    D_TxtTag Tag[TXT_TAG_NUM];
    D_U32 SegCnt;	/*��������*/
    D_U32 Seg[TXT_SEG_NUM];
    D_U32 LastSegRowCnt;	/*���һ�ε�����*/
}D_TxtConf;


/**@brief txt ������ʾ
*@param[in]cur_txt_motion: ��ǰtxt�ļ��ƶ�����
*@param[in]vis: ��ʾtxt ���ݵĿؼ�ָ��
*@retval �޷���ֵ
*/
void d_txt_show(D_U16 cur_txt_motion,D_Visual *vis)D_FUNCPOSTFIT;

/**@brief��ʼ��txt��ʾ��λ�ü��������
*@param[in]filename : Ҫ��ʾ��txt�ļ�ȫ·������
*@param[in]x,y,w,h:��ʾ����Ĵ�С��λ��
*@param[in]fontColor,fontSize,fontType:�ֱ�Ϊ������ɫ����С������
*@retval �޷���ֵ
*/
D_Result d_txt_content_init(char *filename,D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_Color fontColor,D_U16 fontSize, D_U16 fontType, D_Color bg)D_FUNCPOSTFIT;

/**@brief �ͷ�txt��ʾʱ������ڴ�ռ䲢�ر�txt�ļ�
*@retval �޷���ֵ
*/
void d_txt_close(void)D_FUNCPOSTFIT;

/**@brief ���ϲ��ṩ��־�Ƿ񻹿��Լ�����ҳ
*@retval ���Է�ҳ����D_TRUE �������򷵻�D_FALSE
*/
D_Bool d_txt_pgdown_flag(void)D_FUNCPOSTFIT;

/**@brief ���ϲ��ṩ��־�Ƿ񻹿��Լ�����ҳ
*@retval ���Է�ҳ����D_TRUE �������򷵻�D_FALSE
*/
D_Bool d_txt_pgup_flag(void)D_FUNCPOSTFIT;

void d_txt_get_num(D_U32 *TotalPage)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
