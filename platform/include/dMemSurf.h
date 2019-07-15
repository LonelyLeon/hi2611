/** @file
* @brief 内存图形操作
* @author 龚克
* @date 2005-7-29 龚克: 建立文件
* @date 2013-03-20 lc: 统一平台, 代码整理
*/

#ifndef _D_MEM_SURF_H_
#define _D_MEM_SURF_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dMem.h"
#include "dDebug.h"

/*像素指针*/
typedef struct {
	D_U8	*buf;
	D_U8	 bit;
} D_GPixelPtr;

/*复制像素指针*/
#define D_G_PIXEL_PTR_CPY(dev, dst, src)\
		((dst) = (src))

/*计算像素指针指定字节数偏移位置的指针*/
#define D_G_PIXEL_PTR_OFF(dev, ptr, pstart, off)\
		D_MACRO_BEGIN\
			(ptr).buf = (pstart).buf + (off);\
			(ptr).bit = (pstart).bit;\
		D_MACRO_END\

/*计算像素指针指定像素数偏移位置的指针*/
#define D_G_PIXEL_PTR_PIXEL_OFF(dev, ptr, pstart, off)\
		D_MACRO_BEGIN\
			switch ((dev)->buf.mode) {\
				case D_GDEV_MODE_1BPP:\
				case D_GDEV_MODE_2BPP:\
				case D_GDEV_MODE_4BPP:\
					{\
						D_Coord	length = (dev)->buf.bpp * (off) + (pstart).bit;\
						(ptr).buf = (pstart).buf + (length >> 3);\
						(ptr).bit = 8 - (length & 0x07) - (dev)->buf.bpp;\
					}\
					break;\
				default:\
					((ptr).buf = (pstart).buf + (off)*(dev)->buf.Bpp);\
					break;\
			}\
		D_MACRO_END

/*根据坐标取得像素指针*/
#define D_G_PIXEL_PTR(dev, ptr, x, y)\
		D_MACRO_BEGIN\
			switch ((dev)->buf.mode) {\
				case D_GDEV_MODE_1BPP:\
				case D_GDEV_MODE_2BPP:\
				case D_GDEV_MODE_4BPP:\
					{\
						D_Coord	length = (dev)->buf.bpp * (x);\
						(ptr).buf = (dev)->buf.buf + (y) * (dev)->buf.pitch + (length >> 3);\
						(ptr).bit = 8 - (length & 0x07) - (dev)->buf.bpp;\
					}\
					break;\
				default:\
					(ptr).buf = (dev)->buf.buf + (y) * (dev)->buf.pitch + (x) * (dev)->buf.Bpp;\
					break;\
			}\
		D_MACRO_END

/*移动指针到下一个像素位置*/
#define D_G_NEXT_PIXEL(dev, ptr)\
		D_MACRO_BEGIN\
			switch ((dev)->buf.mode) {\
				case D_GDEV_MODE_1BPP:\
				case D_GDEV_MODE_2BPP:\
				case D_GDEV_MODE_4BPP:\
					if (! (ptr).bit) {\
						(ptr).buf ++;\
						(ptr).bit = 8 - (dev)->buf.bpp;\
					} else {\
						(ptr).bit -= (dev)->buf.bpp;\
					}\
					break;\
				default:\
					(ptr).buf+=(dev)->buf.Bpp;\
					break;\
			}\
		D_MACRO_END

/* 以下函数目前只针对小端CPU */
static D_Pixel __inline__ __16bit_buf2pixel(D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    return (((D_U16)*(__buf) << 8) | (*(__buf + 1)));
#else
	return (((D_U16)*(__buf + 1) << 8) | (*(__buf)));
#endif
}

static void __inline__ __16bit_pixel2buf(D_Pixel __pix, D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    *(__buf + 1) = (__pix) & 0xFF;
    *(__buf) = ((__pix) >> 8) & 0xFF;
#else
    *(__buf) = (__pix) & 0xFF;
    *(__buf + 1) = ((__pix) >> 8) & 0xFF;
#endif
}

static D_Pixel __inline__ __24bit_buf2pixel(D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    return (((D_U32)*(__buf) << 16) | (((D_U32)*(__buf + 1)) << 8) | (*(__buf + 2)));
#else
	return (((D_U32)*(__buf + 2) << 16) | (((D_U32)*(__buf + 1)) << 8) | (*(__buf)));
#endif
}

static void __inline__ __24bit_pixel2buf(D_Pixel __pix, D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    *(__buf + 2) = (__pix) & 0xFF;
	*(__buf + 1) = ((__pix) >> 8) & 0xFF;
	*(__buf) = ((__pix) >> 16) & 0xFF;
#else
	*(__buf) = (__pix) & 0xFF;
	*(__buf + 1) = ((__pix) >> 8) & 0xFF;
	*(__buf + 2) = ((__pix) >> 16) & 0xFF;
#endif
}

static D_Pixel __inline__ __32bit_buf2pixel(D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    return (((D_U32)*(__buf) << 24) | ((D_U32)*(__buf + 1) << 16) | (((D_U32)*(__buf + 2)) << 8) | (*(__buf + 3)));
#else
	return (((D_U32)*(__buf + 3) << 24) | ((D_U32)*(__buf + 2) << 16) | (((D_U32)*(__buf + 1)) << 8) | (*(__buf)));
#endif
}

static void __inline__ __32bit_pixel2buf(D_Pixel __pix, D_U8 *__buf)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    *(__buf + 3) = (__pix) & 0xFF;
    *(__buf + 2) = ((__pix) >> 8) & 0xFF;
	*(__buf + 1) = ((__pix) >> 16) & 0xFF;
	*(__buf) = ((__pix) >> 24) & 0xFF;
#else
	*(__buf) = (__pix) & 0xFF;
	*(__buf + 1) = ((__pix) >> 8) & 0xFF;
	*(__buf + 2) = ((__pix) >> 16) & 0xFF;
    *(__buf + 3) = ((__pix) >> 24) & 0xFF;
#endif
}

static D_U8 __inline__ __pix2alpha1555(D_Pixel __pix)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    return (D_U8)(__pix >> 7);
#else
	return (D_U8)(__pix >> 15);
#endif
}

static void __inline__ __pix2alpha4444(D_Pixel __pix, D_U8 *a, D_U8 *r, D_U8 *g, D_U8 *b)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    __pix = (__pix >> 8) | ((__pix & 0xFF) << 8);
#endif
	*a = (D_U8)((__pix >> 12) << 4);
    *a = D_MIN(0x80, *a);
    *r = (D_U8)((__pix >> 8) << 4);
    *g = (D_U8)(__pix >> 4) << 4;
    *b = (D_U8)(__pix << 4);
}

static D_Pixel __inline__ __argb4444_2_pixel(D_U8 a, D_U8 r, D_U8 g, D_U8 b)
{
    D_Pixel pixel;
    
    a = D_MIN(0x80, a);
    pixel = (((D_U32)(a >> 4) << 12) | ((D_U32)(r >> 4) << 8) | ((D_U32)(g >> 4) << 4) | (b >> 4));
#if defined(D_PDMA_BIGENDIAN_PATCH)
    pixel = (pixel >> 8) | ((pixel & 0xFF) << 8);
#endif

    return pixel;
}

static void __inline__ __pix2alpha8565(D_Pixel __pix, D_U8 *a, D_U8 *r, D_U8 *g, D_U8 *b)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    __pix = (__pix >> 16) | (__pix & 0xFF00) | ((__pix & 0xFF) << 16);
#endif
	*a = (D_U8)(__pix >> 16);
    *a = D_MIN(0x80, *a);
    *r = (D_U8)((__pix >> 11) << 3);
    *g = (D_U8)(__pix >> 5) << 2;
    *b = (D_U8)(__pix << 3);
}

static D_Pixel __inline__ __argb8565_2_pixel(D_U8 a, D_U8 r, D_U8 g, D_U8 b)
{
    D_Pixel pixel;
    
    a = D_MIN(0x80, a);
    pixel = (((D_U32)a << 16) | ((D_U32)(r >> 3) << 11) | ((D_U32)(g >> 2) << 5) | (b >> 3));
#if defined(D_PDMA_BIGENDIAN_PATCH)
    pixel = (pixel >> 16) | (pixel & 0xFF00) | ((pixel & 0xFF) << 16);
#endif

    return pixel;
}

static void __inline__ __pix2alpha6666(D_Pixel __pix, D_U8 *a, D_U8 *r, D_U8 *g, D_U8 *b)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    __pix = (__pix >> 16) | (__pix & 0xFF00) | ((__pix & 0xFF) << 16);
#endif
	*a = (D_U8)((__pix >> 18) << 2);
    *a = D_MIN(0x80, *a);
    *r = (D_U8)((__pix >> 12) << 2);
    *g = (D_U8)(__pix >> 6) << 2;
    *b = (D_U8)(__pix << 2);
}

static D_Pixel __inline__ __argb6666_2_pixel(D_U8 a, D_U8 r, D_U8 g, D_U8 b)
{
    D_Pixel pixel;
    
    a = D_MIN(0x80, a);
    pixel = (((D_U32)(a >> 2) << 18) | ((D_U32)(r >> 2) << 12) | ((D_U32)(g >> 2) << 6) | (b >> 2));
#if defined(D_PDMA_BIGENDIAN_PATCH)
    pixel = (pixel >> 16) | (pixel & 0xFF00) | ((pixel & 0xFF) << 16);
#endif

    return pixel;
}

static void __inline__ __pix2alpha8888(D_Pixel __pix, D_U8 *a, D_U8 *r, D_U8 *g, D_U8 *b)
{
#if defined(D_PDMA_BIGENDIAN_PATCH)
    *a = (D_U8)(__pix);
    *a = D_MIN(0x80, *a);
    *r = (D_U8)(__pix >> 8);
    *g = (D_U8)(__pix >> 16);
    *b = (D_U8)(__pix >> 24);
#else
	*a = (D_U8)(__pix >> 24);
    *a = D_MIN(0x80, *a);
    *r = (D_U8)(__pix >> 16);
    *g = (D_U8)(__pix >> 8);
    *b = (D_U8)(__pix);
#endif
}

static D_Pixel __inline__ __argb8888_2_pixel(D_U8 a, D_U8 r, D_U8 g, D_U8 b)
{
    a = D_MIN(0x80, a);
#if defined(D_PDMA_BIGENDIAN_PATCH)
    return (((D_U32)b << 24) | ((D_U32)g << 16) | ((D_U32)r << 8) | a);
#else
    return (((D_U32)a << 24) | ((D_U32)r << 16) | ((D_U32)g << 8) | b);
#endif
}

/*设置指针位置的一个像素,将指针移动到下一个像素位置*/
#define D_G_SET_PIXEL(dev, ptr, pixel)\
		D_MACRO_BEGIN\
			D_U8	__v, __mask;\
			switch ((dev)->buf.mode) {\
				case D_GDEV_MODE_1BPP:\
					__v = (ptr).buf[0];\
					__mask = (0x01 << (ptr).bit);\
					(ptr).buf[0] = (__v & ~__mask) | ((pixel) << (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 7;\
					} else {\
						(ptr).bit--;\
					}\
					break;\
				case D_GDEV_MODE_2BPP:\
					__v = (ptr).buf[0];\
					__mask = (0x03 << (ptr).bit);\
					(ptr).buf[0] = (__v & ~__mask) | ((pixel) << (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 6;\
					} else {\
						(ptr).bit-=2;\
					}\
					break;\
				case D_GDEV_MODE_4BPP:\
					__v = (ptr).buf[0];\
					__mask = (0x0F << (ptr).bit);\
					(ptr).buf[0] = (__v & ~__mask) | ((pixel) << (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 4;\
					} else {\
						(ptr).bit-=4;\
					}\
					break;\
				case D_GDEV_MODE_8BPP:\
					*((ptr).buf)++ = (D_U8)(pixel);\
					break;\
				case D_GDEV_MODE_16BPP_565:\
					__16bit_pixel2buf((pixel), (ptr).buf);\
					((ptr).buf) += 2;\
					break;\
				case D_GDEV_MODE_16BPP:\
					if((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHABLEND)\
					{\
						D_U16 __sa = ((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHA_FROM_CONST) \
							? (D_U8)((D_U32)(dev)->draw_param) : __pix2alpha1555((pixel));\
						if(__sa) __16bit_pixel2buf((pixel), (ptr).buf);\
					}\
					else\
						__16bit_pixel2buf((pixel), (ptr).buf);\
					((ptr).buf) += 2;\
					break;\
				case D_GDEV_MODE_16BPP_4444:\
                    {\
				        D_Pixel __pix;\
    					if((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHABLEND)\
    					{\
    						D_U8 __sa, __sr, __sg, __sb, __da, __dr, __dg, __db;\
    						__pix2alpha4444((pixel), &__sa, &__sr, &__sg, &__sb);\
    						__pix2alpha4444(__16bit_buf2pixel((ptr).buf), &__da, &__dr, &__dg, &__db);\
    						if(__sa && ((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHA_FROM_CONST))\
    							__sa = D_MIN(0x80, (D_U8)((D_U32)(dev)->draw_param));\
    						__dr = (D_U8)((D_U32)__sr * __sa / 128 + (D_U32)__dr * (128 - __sa) / 128);\
    						__dg = (D_U8)((D_U32)__sg * __sa / 128 + (D_U32)__dg * (128 - __sa) / 128);\
    						__db = (D_U8)((D_U32)__sb * __sa / 128 + (D_U32)__db * (128 - __sa) / 128);\
    						__da = (D_U8)((D_U32)__sa * __sa / 128 + (D_U32)__da * (128 - __sa) / 128);\
    				        __pix = __argb4444_2_pixel(__da, __dr, __dg, __db);\
    					}\
    					else\
                            __pix = (pixel);\
                        __16bit_pixel2buf(__pix, (ptr).buf);\
    					((ptr).buf) += 2;\
				    }\
                    break;\
				case D_GDEV_MODE_24BPP:\
					__24bit_pixel2buf((pixel), (ptr).buf);\
					(ptr).buf += 3;\
					break;\
				case D_GDEV_MODE_24BPP_8565:\
                    {\
				        D_Pixel __pix;\
    					if((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHABLEND)\
    					{\
    						D_U8 __sa, __sr, __sg, __sb, __da, __dr, __dg, __db;\
    						__pix2alpha8565((pixel), &__sa, &__sr, &__sg, &__sb);\
    						__pix2alpha8565(__24bit_buf2pixel((ptr).buf), &__da, &__dr, &__dg, &__db);\
    						if(__sa && ((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHA_FROM_CONST))\
    							__sa = D_MIN(0x80, (D_U8)((D_U32)(dev)->draw_param));\
    						__dr = (D_U8)((D_U32)__sr * __sa / 128 + (D_U32)__dr * (128 - __sa) / 128);\
    						__dg = (D_U8)((D_U32)__sg * __sa / 128 + (D_U32)__dg * (128 - __sa) / 128);\
    						__db = (D_U8)((D_U32)__sb * __sa / 128 + (D_U32)__db * (128 - __sa) / 128);\
    						__da = (D_U8)((D_U32)__sa * __sa / 128 + (D_U32)__da * (128 - __sa) / 128);\
    				        __pix = __argb8565_2_pixel(__da, __dr, __dg, __db);\
    					}\
    					else\
                            __pix = (pixel);\
                        __24bit_pixel2buf(__pix, (ptr).buf);\
    					((ptr).buf) += 3;\
				    }\
                    break;\
				case D_GDEV_MODE_24BPP_6666:\
                    {\
				        D_Pixel __pix;\
    					if((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHABLEND)\
    					{\
    						D_U8 __sa, __sr, __sg, __sb, __da, __dr, __dg, __db;\
    						__pix2alpha6666((pixel), &__sa, &__sr, &__sg, &__sb);\
    						__pix2alpha6666(__24bit_buf2pixel((ptr).buf), &__da, &__dr, &__dg, &__db);\
    						if(__sa && ((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHA_FROM_CONST))\
    							__sa = D_MIN(0x80, (D_U8)((D_U32)(dev)->draw_param));\
    						__dr = (D_U8)((D_U32)__sr * __sa / 128 + (D_U32)__dr * (128 - __sa) / 128);\
    						__dg = (D_U8)((D_U32)__sg * __sa / 128 + (D_U32)__dg * (128 - __sa) / 128);\
    						__db = (D_U8)((D_U32)__sb * __sa / 128 + (D_U32)__db * (128 - __sa) / 128);\
    						__da = (D_U8)((D_U32)__sa * __sa / 128 + (D_U32)__da * (128 - __sa) / 128);\
    				        __pix = __argb6666_2_pixel(__da, __dr, __dg, __db);\
    					}\
    					else\
                            __pix = (pixel);\
                        __24bit_pixel2buf(__pix, (ptr).buf);\
    					((ptr).buf) += 3;\
				    }\
                    break;\
				case D_GDEV_MODE_32BPP:\
				    {\
				        D_Pixel __pix;\
    					if((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHABLEND)\
    					{\
    						D_U8 __sa, __sr, __sg, __sb, __da, __dr, __dg, __db;\
    						__pix2alpha8888((pixel), &__sa, &__sr, &__sg, &__sb);\
    						__pix2alpha8888(__32bit_buf2pixel((ptr).buf), &__da, &__dr, &__dg, &__db);\
    						if(__sa && ((dev)->draw_mode & D_GSURF_DRAW_MODE_ALPHA_FROM_CONST))\
    							__sa = D_MIN(0x80, (D_U8)((D_U32)(dev)->draw_param));\
    						__dr = (D_U8)((D_U32)__sr * __sa / 128 + (D_U32)__dr * (128 - __sa) / 128);\
    						__dg = (D_U8)((D_U32)__sg * __sa / 128 + (D_U32)__dg * (128 - __sa) / 128);\
    						__db = (D_U8)((D_U32)__sb * __sa / 128 + (D_U32)__db * (128 - __sa) / 128);\
    						__da = (D_U8)((D_U32)__sa * __sa / 128 + (D_U32)__da * (128 - __sa) / 128);\
    				        __pix = __argb8888_2_pixel(__da, __dr, __dg, __db);\
    					}\
    					else\
                            __pix = (pixel);\
                        __32bit_pixel2buf(__pix, (ptr).buf);\
    					((ptr).buf) += 4;\
				    }\
					break;\
				default:\
					break;\
			}\
		D_MACRO_END
		
/*取得指针位置的一个像素,将指针移动到下一个像素位置*/
#define D_G_GET_PIXEL(dev, ptr, pixel)\
		D_MACRO_BEGIN\
			D_U8	__mask;\
			switch ((dev)->buf.mode) {\
				case D_GDEV_MODE_1BPP:\
					__mask = (0x01 << (ptr).bit);\
					pixel = (((ptr).buf[0] & __mask) >> (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 7;\
					} else {\
						(ptr).bit--;\
					}\
					break;\
				case D_GDEV_MODE_2BPP:\
					__mask = (0x03 << (ptr).bit);\
					pixel = (((ptr).buf[0] & __mask) >> (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 6;\
					} else {\
						(ptr).bit-=2;\
					}\
					break;\
				case D_GDEV_MODE_4BPP:\
					__mask = (0x0F << (ptr).bit);\
					pixel = (((ptr).buf[0] & __mask) >> (ptr).bit);\
					if (! (ptr).bit) {\
						(ptr).buf++;\
						(ptr).bit = 4;\
					} else {\
						(ptr).bit-=4;\
					}\
					break;\
				case D_GDEV_MODE_8BPP:\
					(pixel) = *((ptr).buf)++;\
					break;\
				case D_GDEV_MODE_16BPP_565:\
				case D_GDEV_MODE_16BPP:\
				case D_GDEV_MODE_16BPP_4444:\
					(pixel) = __16bit_buf2pixel((ptr).buf);\
					((ptr).buf) += 2;\
					break;\
				case D_GDEV_MODE_24BPP:\
				case D_GDEV_MODE_24BPP_8565:\
				case D_GDEV_MODE_24BPP_6666:\
					(pixel) = __24bit_buf2pixel((ptr).buf);\
					((ptr).buf) += 3;\
					break;\
				case D_GDEV_MODE_32BPP:\
					(pixel) = __32bit_buf2pixel((ptr).buf);\
					((ptr).buf) += 4;\
					break;\
				default:\
					break;\
			}\
		D_MACRO_END

/** @brief 释放内存绘图设备*/
D_Result	d_mem_surf_destroy (D_GSurface *dev) D_FUNCPOSTFIT;

/** @brief 找到颜色映射的像素值*/
D_Pixel		d_mem_surf_map_pixel (D_GSurface *dev, D_Color col) D_FUNCPOSTFIT;

/** @brief 找到像素映射的颜色*/
D_Color		d_mem_surf_map_color (D_GSurface *dev, D_Pixel pix) D_FUNCPOSTFIT;

D_Result	d_mem_surf_set_fg (D_GSurface *dev, D_Pixel fg) D_FUNCPOSTFIT;

D_Result	d_mem_surf_set_bg (D_GSurface *dev, D_Pixel bg) D_FUNCPOSTFIT;

D_Result d_mem_surf_set_mode(D_GSurface *dev, D_U32 mode);

D_Result d_mem_surf_set_param(D_GSurface *dev, D_Ptr param);

/** @brief 设定绘图剪切区*/
D_Result	d_mem_surf_set_clip (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 设定调色板*/
D_Result	d_mem_surf_set_palette (D_GSurface *dev, D_Color *pal, D_U8 start, D_U16 cnt);

/** @brief 画点*/
D_Result	d_mem_surf_point (D_GSurface *dev, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

/** @brief 画水平线*/
D_Result	d_mem_surf_hline (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord w) D_FUNCPOSTFIT;

/** @brief 画垂直线*/
D_Result	d_mem_surf_vline (D_GSurface *dev, D_Coord x, D_Coord y, D_Coord h) D_FUNCPOSTFIT;

/** @brief 画填充矩形*/
D_Result	d_mem_surf_fill_rect (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 显示区域拷贝*/
D_Result	d_mem_surf_copy (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr) D_FUNCPOSTFIT;

/** @brief 显示区域拷贝*/
D_Result	d_mem_surf_copy_mask (D_GSurface *dst, D_Rect *dr, D_GSurface *src, D_Rect *sr, D_Pixel mask) D_FUNCPOSTFIT;

D_Result	d_mem_surf_flush (D_GSurface *dev) D_FUNCPOSTFIT;

void d_mem_surf_lock(D_GSurface *dev) D_FUNCPOSTFIT;

void d_mem_surf_unlock(D_GSurface *dev) D_FUNCPOSTFIT;

D_Result	d_yuv_fill_rect (	D_U32	rect_y_addr,D_U32	rect_u_addr,D_U32	rect_v_addr,\
	D_U16	rect_yuv_x0,D_U16	rect_yuv_y0,D_U16	rect_yuv_x1,D_U16	rect_yuv_y1,D_U16	rect_width,\
	D_U8	rect_y_data,D_U8	rect_u_data,D_U8	rect_v_data,D_U8	rect_b_fac,D_U8	rect_mode)D_FUNCPOSTFIT;

D_Result	d_yuv_rotate(D_U32 rotate_src_addr,D_U32 rotate_dst_addr,D_U32	rotate_img_width,\
	D_U32	rotate_img_height,D_U32	rotate_src_width,D_U32	rotate_dst_width,D_U8	rotate_mode)D_FUNCPOSTFIT;

D_Result d_yuv_true_fill(D_U32 true_src_y_addr,D_U32 true_src_u_addr,D_U32 true_src_v_addr,\
	D_U32 true_dst_y_addr,D_U32 true_dst_u_addr,D_U32 true_dst_v_addr,D_U16 true_yuv_x0,\
	D_U16	true_yuv_y0,D_U16	true_yuv_x1,D_U16	true_yuv_y1,D_U16	dst_width,D_U16 src_width,\
    D_U8 rue_b_fac,D_U8 true_hide_color,D_U8 true_h_en)D_FUNCPOSTFIT;
D_Result d_argb_to_ayuv(D_U32 csc_dst_addr,D_U32 csc_src_addr,D_U32 csc_dst_ddr_line,\
	D_U32 csc_src_ddr_line,D_U32 csc_pic_width,D_U32 csc_pic_height,D_U16 csc_dst_x,\
	D_U16	csc_dst_y,D_U16	csc_src_x,D_U16	csc_src_y,D_U8 csc_input_type,D_U8 csc_output_type)D_FUNCPOSTFIT;
void d_argb_rotate(D_U32 rotate_src_addr,D_U32 rotate_dst_addr,D_U32 rotate_img_width,\
	D_U32 rotate_img_height,D_U32 rotate_src_x,D_U32 rotate_src_y,D_U32 rotate_dst_x,D_U32 rotate_dst_y);

#ifdef  __cplusplus
}
#endif

#endif
