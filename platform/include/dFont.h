/**@defgroup font 字库
*@{*/
/** @file
* @brief 字体相关
* @author
* @date 2013-03-25 lc: 统一平台, 代码整理
*/

#ifndef _D_FONT_H_
#define _D_FONT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dCharset.h"

/** @brief 字库类型定义 */
typedef enum
{
	D_FONT_DIANZHEN_ASCII = 0,
	D_FONT_DIANZHEN_HANZI,
	D_FONT_DIANZHEN_OTHER,
	D_FONT_FREETYPE,
}D_FontEngine;

typedef struct _D_Font	D_Font;

/** @brief 字符模*/
typedef struct
{
    D_U8    *mask;      /*字模数据*/
    D_S8     left;      /*字模在框格中的x坐标（像素）*/
    D_S8     top;       /*字模在框格中的y坐标（像素）*/
    D_S8     width;     /*字模宽（像素）*/
    D_S8     height;    /*字模高（像素）*/
    D_U8     bpp;       /*字符图片数据是几位色，1：点阵*/
    D_U16    pitch;     /*一行像素数据占几个字节*/
} D_FontCharMask;

/** @brief 字体定义*/
typedef struct
{
	D_FontEngine font_type;
	D_Charset cset;
	D_S32 size;
	D_U8 *font_data;
	D_Size font_data_size;
    
       /*外部字库使用*/
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

/** @brief 初始化字体系统*/
D_Result	d_font_open (void) D_FUNCPOSTFIT;

/** @brief 关闭字体系统*/
D_Result	d_font_close (void) D_FUNCPOSTFIT;

/** @brief 加载一个字库
* @param[in] attr 字体定义指针
* @return fnt 字库指针
*/
D_Font* d_font_create(D_FontDesc *attr) D_FUNCPOSTFIT;

/** @brief 卸载一个字库 
* @param[in] fnt 字库指针
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_font_destroy(D_Font *fnt) D_FUNCPOSTFIT;

/** @brief 设定当前字体
* @param[in] fnt 字库指针
* @param[in] size 字体大小
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_font_set (D_Font *fnt, D_U32 size) D_FUNCPOSTFIT;

/** @brief 获取一个合适的字库
* @param[in] cset 字符集
* @return 字体指针
*/
D_Font* d_font_get_font (D_Charset cset) D_FUNCPOSTFIT;

/** @brief 设定所有字体大小
* @param[in] size 字体大小
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_font_set_size (D_U32 size) D_FUNCPOSTFIT;

/** @brief 设置字体颜色
* @param[in] color 字库颜色
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_font_set_color(D_Color color) D_FUNCPOSTFIT;

/** @brief 取一个字符的尺寸
* @param[in] cset	字符集
* @param[in] chr	显示字符指针
* @param[out] w		返回字符宽度
* @param[out] h		返回字符高度
* @param[out] b		返回字符基线位置
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_font_char_size (D_Charset cset, D_Char *chr, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief 在绘图区域上绘制一个字符
* @param[in] dev	显示区域
* @param[in] cset	字符集
* @param[in] chr	要显示的字符
* @param[in] x		显示横坐标
* @param[in] y		显示纵坐标
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_font_put_char (D_GSurface *dev, D_Charset cset, D_Char *chr, D_Coord x, D_Coord y, D_FontAttrType type) D_FUNCPOSTFIT;

/** @brief 计算一个字符串的大小
* @param[in] text	字符串
* @param[in] cnt	字符串长度
* @param[out] w		返回字符串宽度
* @param[out] h		返回字符串高度
* @param[out] b		返回字符串基线位置
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_font_text_size (D_Char *text, D_Size cnt, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief 在一行内计算一个字符串的大小
* @param[in] text	字符串指针地址
* @param[in] cnt	字符串长度
* @param[in] rw		行宽
* @param[in] last	是否计算被剪切的最后一个字符
* @param[out] w		返回字符串宽度
* @param[out] h		返回字符串高度
* @param[out] b		返回字符串基线位置
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_font_text_size_in_range (D_Char **text, D_Size cnt, D_Coord rw, D_Bool last, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief 计算一个字符串在特定的宽度下能完整显示的大小并返回字节数
* @param[in] text	字符串
* @param[in] cnt	字符串长度
* @param[in] width		字符串约束宽度
* @param[out] w		返回字符串实际宽度
* @param[out] h		返回字符串高度
* @param[out] b		返回字符串基线位置
* @return 成功返回可以完整显示的字节数,其他错误
*/
D_Size
d_font_text_cnt_in_range (D_Char *text, D_Size cnt,D_Size width, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;

/** @brief 取得生僻字显示编码与字符集
* @param[in] cset 存储返回的字符集
* @return 返回显示编码指针与字符集
*/
D_Char*
d_font_get_unknown_char_and_cset (D_Charset *cset) D_FUNCPOSTFIT;

/** @brief 设置生僻字显示编码与字符集
* @param[in] cset 生僻字字符集
* @param[in] unknown_char 替代生僻字的编码
* @return 返回D_OK
*/
D_Result d_font_set_unknown_char_and_cset (D_Charset cset, const D_Char *unknown_char) D_FUNCPOSTFIT;

/** @brief 在绘图区域上绘制一个字符图文接口专用
* @param[in] dev	显示区域
* @param[in] cset	字符集
* @param[in] chr	要显示的字符
* @param[in] x		显示横坐标
* @param[in] y		显示纵坐标
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_font_put_char_ttx (D_GSurface *dev, D_U8 * charLib, D_U8 txt, D_U16 x, D_U16 y, D_U8 pix_W, D_U8 pix_H,D_U8 SizeMode) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
