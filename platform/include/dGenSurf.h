/** @file
* @brief Í¼ÓÃÍ¼ÐÎ²Ù×÷
* @author ¹¨¿Ë
* @date 2005-8-12 ¹¨¿Ë: ½¨Á¢ÎÄ¼þ
*/
#ifndef _D_GEN_SURF_H_
#define _D_GEN_SURF_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGDev.h"
#include "dCharset.h"

/** @brief »­Ö±Ïß*/
D_Result	d_gen_surf_line (D_GSurface *dev, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2) D_FUNCPOSTFIT;

/** @brief »­Ìî³ä¾ØÐÎ*/
D_Result	d_gen_surf_fill_poly (D_GSurface *dev, D_Point *pointtable, D_U8 count) D_FUNCPOSTFIT;

/** @brief »­»¡*/
D_Result	d_gen_surf_arc (D_GSurface *dev, D_Rect *rect, D_S32 angle1, D_S32 angle2) D_FUNCPOSTFIT;

/** @brief »­ÉÈÐÍ*/
D_Result	d_gen_surf_fill_arc (D_GSurface *dev, D_Rect *rect, D_S32 angle1, D_S32 angle2) D_FUNCPOSTFIT;

/** @brief »­ÍÖÔ²*/
D_Result	d_gen_surf_ellipse (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief »­Ìî³äÍÖÔ²*/
D_Result	d_gen_surf_fill_ellipse (D_GSurface *dev, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief »­Ô²½Ç*/
D_Result
d_gen_surf_fill_roundarc(D_GSurface *dev, D_Rect *rect,D_Coord  r,D_RoundRectType type)D_FUNCPOSTFIT;

/** @brief »­Ô²½Ç¾ØÐÎ*/
D_Result
d_gen_surf_fill_roundrect(D_GSurface *dev, D_Rect *rect,D_Coord  r)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
