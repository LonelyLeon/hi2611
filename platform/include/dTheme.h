/** @file
* @brief 控件显示主题模块
* @author 覃宜
* @date 2013-8-9 覃宜: 建立文件
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



/** @brief 文本最大行数*/
#define TEXT_SHOW_MAX_LINE (100)


/** @brief 显示时字体属性*/
typedef struct
{
    D_U16 fontType;     /*字体类型*/
    D_U16 fontSize;     /*字体大小*/
    D_Color fontColor;  /*字体颜色*/
}D_FontAttribute;

/** @brief 显示时文本格式*/
typedef struct
{
    D_Bool valid;           /*是否有效*/
    D_U16 align;            /*水平垂直对齐方式*/
    D_Bool multiple;     /*单行多行显示标志*/
    D_Bool fullShow;     /*能完整显示的词才显示*/
    D_Bool pageFlag;    /*按页显示*/
    D_U16 currPage;     /*当前页号*/
    D_U16 currLine;     /*当前行号*/
    D_Coord lineSpace;/*行间距*/
}D_TextFormat;


/** @brief 每行显示信息*/
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

/** @brief 文本显示信息*/
typedef struct
{
    D_U16  pageCnt;         /* 总页数*/
    D_U16  lineCnt;         /* 总行数*/
    D_U16  width;           /* 总宽度*/
    D_U16  height;          /* 总高度*/
    D_LineShowInfo lineInfo[TEXT_SHOW_MAX_LINE];
}D_TextShowInfo;

/** @brief 初始化主题*/
D_Result	d_theme_open (void) D_FUNCPOSTFIT;

/** @brief 释放主题资源*/
D_Result	d_theme_close (void) D_FUNCPOSTFIT;

/** @brief 画填充矩形
* @param [in] vis	控件
* @param [in] rect 填充区域
* @param [in] color 颜色argb
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	
d_draw_fill_rect (D_Visual *vis, D_Rect *rect, D_Color color) D_FUNCPOSTFIT;

/** @brief 计算与绘制文本信息
* @param [in] vis   控件(当show_enable == D_FALSE时，可以为NULL)
* @param [in] rect 显示区域
* @param [in] text 文本
* @param [in] cnt 文本长度
* @param [in] font 字体属性
* @param [in] form 格式属性
* @param [in] show_enable 是否显示，D_FALSE时，只计算相关信息
* @return 成功返回显示记录信息D_TextShowInfo,失败返回NULL
* @ remarks 记录信息为后期处理提供支持。比如画光标、下划线等等。
*/
D_TextShowInfo*
d_draw_text_new(D_Visual *vis, D_Rect *rect, D_Char *text, D_Size cnt, D_FontAttribute *font, D_TextFormat *form, D_Bool show_enable) D_FUNCPOSTFIT;

/** @brief 计算与绘制文本信息
* @param [in] vis   控件
* @param [in] rect 显示区域
* @param [in] text 文本
* @param [in] cnt 文本长度
* @param [in] font 字体属性
* @param [in] form 格式属性
* @return 成功返回显示记录信息D_TextShowInfo,失败返回NULL
* @ remarks 记录信息为后期处理提供支持。比如画光标、下划线等等。
*/
D_TextShowInfo*
d_draw_text(D_Visual *vis, D_Rect *rect, D_Char *text, D_Size cnt, D_FontAttribute *font, D_TextFormat *form) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
