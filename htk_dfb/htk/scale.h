#ifndef __HTK_SCALE_H__
#define __HTK_SCALE_H__

#include <glib-object.h>
#include <htk/range.h>
#include <gdk/gdk.h>
#include <math.h>
#include <string.h>

G_BEGIN_DECLS

#define HTK_TYPE_SCALE            (htk_scale_get_type ())
#define HTK_SCALE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_SCALE, HtkScale))
#define HTK_SCALE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_SCALE, HtkScaleClass))
#define HTK_IS_SCALE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_SCALE))
#define HTK_IS_SCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_SCALE))
#define HTK_SCALE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_SCALE, HtkScaleClass))

struct HtkScale {
	HtkRange range;

	/*extra cache pixbuf*/
	HdkPixbuf * bg_pix;
	HdkPixbuf * pot_pix;
	HdkPixbuf * act_pix;
};

struct HtkScaleClass {
	HtkRangeClass parent_class;
};

GType htk_scale_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_SCALE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
