/** @file
* @brief  txt接口
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

#define ROW_INDEX_MAX   (120)  /*行序列最大值*/
#define TXT_READ_MAX    (ROW_INDEX_MAX * 128)  /*每次读出的最大txt内容*/
#define TAG_STR_MAX     14 	/*标签字符串最大长度*/

#define TXT_TAG_NUM     5	/*标签个数*/
#define TXT_SEG_NUM     500	/*.....*/

#define 	TXT_MAX_MALLOC_LENGTH   (16 * 1024)	/*TXT空间需要多大后期调整*/


#define DU8(x)                  (*(D_U8  *)(D_U32)(x))

/** @brief txt操作方向定义*/	
typedef enum{
    TXT_NONE,
    TXT_INIT_SHOW,
    TXT_LINE_PRE,
    TXT_LINE_NEXT,
    TXT_PAGE_UP,
    TXT_PAGE_DOWN,
}D_TxtOpertionType;


/** @brief txt编码类型*/	
typedef enum{
    UNICODE_UTF8,
    UNICODE_BE,
    UNICODE_LE,
    ANSI,
}D_TxtEncodeType;


/** @brief 字符编码类型*/	
typedef enum{
    ASCII = 0,
    GB2312,
    UNICODE
}D_CharacterEncodeMode;

/** @brief 每行txt文件的数据定义结构*/	
typedef struct {
    D_U32 rowIndex;	/*行序号*/
    D_U32 rowBeginAddr;	/*该行数据的起始地址*/
    D_U8  rowLength;  /*该行的数据长度*/ // contain "enter" 
    D_U32 offset_in_file;/*该行在文件中的偏移*/
}D_TxtRow;


/** @brief txt 文件的标签定义 */	
typedef struct{
    D_U8  Flag;
    D_U32 Seg;
    D_U32 Row;
    D_U8  HeadStr[TAG_STR_MAX];
}D_TxtTag;

/** @brief txt 文件的相关配置定义*/	
typedef struct{
    D_U32 StartCluster;
    D_U32 LastWrite;
    D_U32 CurSeg;	/*当前段号*/
    D_U32 CurRow;	 /*当前行号*/
    D_U8  TagCnt;	/*标签总数*/
    D_TxtTag Tag[TXT_TAG_NUM];
    D_U32 SegCnt;	/*段落总数*/
    D_U32 Seg[TXT_SEG_NUM];
    D_U32 LastSegRowCnt;	/*最后一段的行数*/
}D_TxtConf;


/**@brief txt 内容显示
*@param[in]cur_txt_motion: 当前txt文件移动方向
*@param[in]vis: 显示txt 内容的控件指针
*@retval 无返回值
*/
void d_txt_show(D_U16 cur_txt_motion,D_Visual *vis)D_FUNCPOSTFIT;

/**@brief初始化txt显示的位置及字体参数
*@param[in]filename : 要显示的txt文件全路径名称
*@param[in]x,y,w,h:显示窗体的大小及位置
*@param[in]fontColor,fontSize,fontType:分别为字体颜色，大小和类型
*@retval 无返回值
*/
D_Result d_txt_content_init(char *filename,D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_Color fontColor,D_U16 fontSize, D_U16 fontType, D_Color bg)D_FUNCPOSTFIT;

/**@brief 释放txt显示时分配的内存空间并关闭txt文件
*@retval 无返回值
*/
void d_txt_close(void)D_FUNCPOSTFIT;

/**@brief 给上层提供标志是否还可以继续翻页
*@retval 可以翻页返回D_TRUE 不可以则返回D_FALSE
*/
D_Bool d_txt_pgdown_flag(void)D_FUNCPOSTFIT;

/**@brief 给上层提供标志是否还可以继续翻页
*@retval 可以翻页返回D_TRUE 不可以则返回D_FALSE
*/
D_Bool d_txt_pgup_flag(void)D_FUNCPOSTFIT;

void d_txt_get_num(D_U32 *TotalPage)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
