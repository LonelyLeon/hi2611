/** @file
* @brief 图形操作
* @author 龚克
* @date 2005-7-17 龚克: 建立文件
* @date 2006-1-16 刘勋: 修改文件
*                   加入字体属性
* 修改函数          
*							(*put_char) 
* 加入函数
*							d_g_put_char_ex
*							d_g_text_ex
*							d_g_text_in_range_ex
* @date 2013-03-21 lc: 统一平台, 代码整理
* 
*/

#ifndef _D_GRAPH_H_
#define _D_GRAPH_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGDev.h"
#include "dCharset.h"
#include "dMutex.h"

typedef struct _D_GSurface	D_GSurface;

/** @brief 字体属性 */
typedef enum {
	D_FONT_ATTR_NORMAL = 0,
} D_FontAttrType;

#define D_GSURF_DRAW_MODE_NORMAL		0x00000000
#define D_GSURF_DRAW_MODE_ALPHABLEND	0x00000001
#define D_GSURF_DRAW_MODE_ALPHA_FROM_CONST 0x00000002
#define D_GSURF_DRAW_MODE_TILE			0x00000010
#define D_GSURF_DRAW_MODE_STRETCH		0x00000020

/** @brief 图形操作*/
typedef struct {
	D_Result (*destroy) (D_GSurface *dev) D_FUNCPOSTFIT;
	D_Pixel	(*map_color) (D_GSurface *dev, D_Color col) D_FUNCPOSTFIT;
	D_Color	(*map_pixel) (D_GSurface *dev, D_Pixel pix) D_FUNCPOSTFIT;
	D_Result (*set_fg) (D_GSurface *dev, D_Pixel pix) D_FUNCPOSTFIT;
	D_Result (*set_bg) (D_GSurface *dev, D_Pixel pix) D_FUNCPOSTFIT;
	D_Result (*set_mode)(D_GSurface *dev, D_U32 mode) D_FUNCPOSTFIT;
	D_Result (*set_param)(D_GSurface *dev, D_Ptr param) D_FUNCPOSTFIT;
	D_Result (*set_clip) (D_GSurface *dev, D_Rect *clip) D_FUNCPOSTFIT;
	D_Result (*set_palette) (D_GSurface *dev, D_Color *pal, D_U8 start, D_U16 cnt) D_FUNCPOSTFIT;
	D_Result (*point) (D_GSurface *dev, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
	D_Result (*hline) (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord len) D_FUNCPOSTFIT;
	D_Result (*vline) (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord len) D_FUNCPOSTFIT;
	D_Result (*line) (D_GSurface *dev, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2) D_FUNCPOSTFIT;
	D_Result (*fill_rect) (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
#ifdef D_GUI_SUPPORT_FILL_POLY
	D_Result (*fill_poly) (D_GSurface *dev, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
#endif
#ifdef D_GUI_SUPPORT_FILL_ELLIPSE
	D_Result (*fill_ellipse) (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
#endif
#ifdef D_GUI_SUPPORT_ELLIPSE
	D_Result (*ellipse) (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
#endif
#ifdef D_GUI_SUPPORT_FILL_ARC
	D_Result (*fill_arc) (D_GSurface *dev, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
#endif
#ifdef D_GUI_SUPPORT_ARC
	D_Result (*arc) (D_GSurface *dev, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
#endif
	D_Result (*fill_roundarc)(D_GSurface *dev, D_Rect *rect, D_Coord r,D_RoundRectType type) D_FUNCPOSTFIT;
	D_Result (*fill_roundrect)(D_GSurface *dev, D_Rect *rect, D_Coord r) D_FUNCPOSTFIT;
	D_Result (*copy) (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr) D_FUNCPOSTFIT;
	D_Result (*copy_mask) (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr, D_Pixel mask) D_FUNCPOSTFIT;
	D_Result (*flush) (D_GSurface *dev) D_FUNCPOSTFIT; /* 图形驱动同步 */
    void (*lock)(D_GSurface *dev) D_FUNCPOSTFIT;
    void (*unlock)(D_GSurface *dev) D_FUNCPOSTFIT;
} D_GSurfaceOp;

/** @brief 图形表面*/
struct _D_GSurface {
	const D_GSurfaceOp *op;
	D_GDevBuffer buf;
	D_Color	*palettes;
	D_Pixel	transparence;
	D_U16 pal_cnt;
	D_HGDev	hgdev;
	D_Pixel	fg;
	D_Pixel	bg;
	D_Rect clip;
	D_U32 draw_mode;
	D_Ptr draw_param;
    D_HMutex lock;
};

/** @brief 图像*/
typedef struct _D_Image	D_Image;
struct _D_Image {
	const D_GSurfaceOp	*op;
	D_GDevBuffer buf;
	D_Color	*palettes;
	D_Pixel	transparence;
	D_U16 pal_cnt;
	D_U8 disposal;
	D_Coord	left, top;
	/*gif logical screen width and height*/
	D_U16 logical_width, logical_height;
	D_U16 frame;
	D_S32 latency;
	D_Image	*next;
};

/** @brief	支持的图片格式*/
typedef enum {
	D_IMAGE_JPEG,
	D_IMAGE_PNG,
	D_IMAGE_GIF,
	D_IMAGE_BMP,
	D_IMAGE_MPEG2_FRAME_I,
	D_IMAGE_AUTO
} D_ImageType;

/** @brief 图像解码输入参数 */
typedef struct
{
    D_Rect output_rect;  /**< 输出图像剪切区(目前GIF忽略此值) */
    D_Result (*read)(D_U8 *buf, D_Size size, void *arg) D_FUNCPOSTFIT;  /**< 读操作函数指针 */
    void *read_arg;  /**< 读操作参数 */
    D_Result (*seek)(D_S32 offset, void *arg) D_FUNCPOSTFIT;  /**< 设置读位置函数指针 */
    void *seek_arg;  /**< 设置读位置参数 */
    D_GSurface *dev;  /**< 绘图设备上下文 */
}D_ImageInputParam;

/** @brief 图像解码输出参数 */
typedef struct
{
    D_ImageType type;  /**< 原始图像格式 */
    D_Coord width;  /**< 图像原始宽度 */
    D_Coord height;  /**< 图像原始高度 */
}D_ImageOutputParam;

D_Result d_g_mem_surface_init (D_GSurface *dev, D_GDevMode mode, D_U8 *buf, D_Color *pal, D_Coord x, D_Coord y, D_Coord pitch, D_Bool hwaccel) D_FUNCPOSTFIT;
D_Result d_g_dev_surface_init (D_GSurface *dev, D_GDevMode mode, D_HGDev hgdev, D_Color *pal, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
D_Result d_g_surface_deinit (D_GSurface *dev) D_FUNCPOSTFIT;
D_Color d_g_map_pixel (D_GSurface *dev, D_Pixel pix) D_FUNCPOSTFIT;
D_Pixel d_g_map_color (D_GSurface *dev, D_Color col) D_FUNCPOSTFIT;
D_Result d_g_set_fg (D_GSurface *dev, D_Pixel fg) D_FUNCPOSTFIT;
D_Result d_g_set_bg (D_GSurface *dev, D_Pixel bg) D_FUNCPOSTFIT;
D_Result d_g_set_mode(D_GSurface *dev, D_U32 mode) D_FUNCPOSTFIT;
D_Result d_g_set_param(D_GSurface *dev, D_Ptr param) D_FUNCPOSTFIT;
D_Result d_g_set_clip (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
D_Result d_g_set_palette (D_GSurface *dev, D_Color *pal, D_U8 start, D_U16 cnt) D_FUNCPOSTFIT;
D_Result d_g_point (D_GSurface *dev, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
D_Result d_g_hline (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord len) D_FUNCPOSTFIT;
D_Result d_g_vline (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord len) D_FUNCPOSTFIT;
D_Result d_g_line (D_GSurface *dev, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2) D_FUNCPOSTFIT;
D_Result d_g_rect (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
D_Result d_g_fill_rect (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
D_Result d_g_poly (D_GSurface *dev, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
D_Result d_g_fill_poly (D_GSurface *dev, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
D_Result d_g_ellipse (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
D_Result d_g_fill_ellipse (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;
D_Result d_g_arc (D_GSurface *dev, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
D_Result d_g_fill_arc (D_GSurface *dev, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
D_Result d_g_fill_roundarc(D_GSurface *dev, D_Rect *rect,D_Coord  r,D_RoundRectType type)D_FUNCPOSTFIT;
D_Result d_g_fill_roundrect(D_GSurface *dev, D_Rect *rect,D_Coord  r)D_FUNCPOSTFIT;
D_Result d_g_copy (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr) D_FUNCPOSTFIT;
D_Result d_g_copy_mask (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr, D_Pixel mask) D_FUNCPOSTFIT;
D_Result d_g_put_char (D_GSurface *dev, D_Charset cset, D_Char *chr, D_Coord x, D_Coord y) D_FUNCPOSTFIT;
D_Result d_g_char_size (D_GSurface *dev, D_Charset cset, D_Char *chr, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT;
D_Result d_g_text (D_GSurface *dev, D_Coord x, D_Coord y, D_Char *str, D_Size cnt) D_FUNCPOSTFIT;
D_Result d_g_text_in_range (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord w, D_Char **str, D_Size cnt, D_Bool draw_last) D_FUNCPOSTFIT;
D_Result d_g_flush (D_GSurface *dev) D_FUNCPOSTFIT;

/* add by liux */
D_Result d_g_put_char_ex (D_GSurface *dev, D_Charset cset, D_Char *chr, D_Coord x, D_Coord y, D_FontAttrType type) D_FUNCPOSTFIT;
D_Result d_g_text_ex (D_GSurface *dev, D_Coord x, D_Coord y, D_Char *str, D_Size cnt, D_FontAttrType type) D_FUNCPOSTFIT;
D_Result d_g_text_in_range_ex (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord w, D_Char **str, D_Size cnt, D_Bool draw_last, D_FontAttrType type) D_FUNCPOSTFIT;

/*--add by qiny 2012-09-05*/
D_Result d_g_text_middle_ex (D_GSurface *dev, D_Coord x, D_Coord y, D_Char *str, D_Size cnt, D_FontAttrType type,D_Coord lineH) D_FUNCPOSTFIT;
/*--end*/

D_Image* d_g_load_image (D_GSurface *dev, D_ImageType type, D_U8 *adata, D_Size cnt) D_FUNCPOSTFIT;

D_Image* d_image_new (D_GDevMode mode, D_Coord w, D_Coord h) D_FUNCPOSTFIT;
D_Image* d_image_new_ex (D_GDevMode mode, D_Coord w, D_Coord h, D_Bool global_pal) D_FUNCPOSTFIT;
D_Result d_image_free (D_Image *img) D_FUNCPOSTFIT;

D_Image* d_image_new_in_sys (D_GDevMode mode, D_Coord w, D_Coord h) D_FUNCPOSTFIT;
D_Result d_image_free_in_sys (D_Image *img) D_FUNCPOSTFIT;

// Add by luo
D_Result
d_image_copy (D_Image * src, D_Rect * rect, D_Image ** dst) D_FUNCPOSTFIT;

D_Result d_g_copy_image (D_GSurface *dev, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;
D_Result d_g_copy_image_mask (D_GSurface *dev, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;

D_Result d_g_lock(D_GSurface *dev) D_FUNCPOSTFIT;
D_Result d_g_unlock(D_GSurface *dev) D_FUNCPOSTFIT;

/** @brief 图像解码, 
           支持部分解码(bmp, jpeg, png), 流式输入数据
* @param[in] input  输入参数
* @param[out] output  输出参数
* @param[out] image  输出图像
*/
D_Result d_g_image_decode(D_ImageInputParam *input, D_ImageOutputParam *output, D_Image **image) D_FUNCPOSTFIT;

/*--add by hegx 2014-01-24  for teletext*/
D_Result        d_g_text_ex_ttx (D_GSurface *dev,D_U8 * charLib, D_U8 txt, D_U16 x, D_U16 y, D_U8 pix_W, D_U8 pix_H,D_U8 SizeMode) D_FUNCPOSTFIT;
/*--end*/
D_Result jpeg_decode_sc(D_U8* file, D_U32 length, D_U8* dsttbuffer, D_U32 dstwidth,D_U16 outwidth, D_U16 outheight)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
