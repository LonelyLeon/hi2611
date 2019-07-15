#ifndef __HTK_DRAWING_AREA_H__
#define __HTK_DRAWING_AREA_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_DRAWING_AREA            (htk_drawing_area_get_type ())
#define HTK_DRAWING_AREA(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_DRAWING_AREA, HtkDrawingArea))
#define HTK_DRAWING_AREA_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_DRAWING_AREA, HtkDrawingAreaClass))
#define HTK_IS_DRAWING_AREA(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_DRAWING_AREA))
#define HTK_IS_DRAWING_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_DRAWING_AREA))
#define HTK_DRAWING_AREA_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_DRAWING_AREA, HtkDrawingAreaClass))

struct HtkDrawingArea {
	HtkWidget widget;
};

struct HtkDrawingAreaClass {
	HtkWidgetClass parent_class;

	gboolean (* draw) (HtkDrawingArea * darea, IDirectFBSurface * surface);
};

GType htk_drawing_area_get_type(void) G_GNUC_CONST;

HtkWidget * htk_drawing_area_new(void);

gboolean htk_drawing_area_draw(HtkDrawingArea * darea, IDirectFBSurface * surface);

G_END_DECLS

#endif//__HTK_DRAWING_AREA_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
