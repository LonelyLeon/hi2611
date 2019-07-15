#ifndef __HTK_HSCALE_H__
#define __HTK_HSCALE_H__

#include <glib-object.h>
#include <htk/scale.h>

G_BEGIN_DECLS

#define HTK_TYPE_HSCALE            (htk_hscale_get_type ())
#define HTK_HSCALE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HSCALE, HtkHScale))
#define HTK_HSCALE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HSCALE, HtkHScaleClass))
#define HTK_IS_HSCALE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HSCALE))
#define HTK_IS_HSCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HSCALE))
#define HTK_HSCALE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HSCALE, HtkHScaleClass))

struct HtkHScale {
	HtkScale scale;
};

struct HtkHScaleClass {
	HtkScaleClass parent_class;
};

GType htk_hscale_get_type(void) G_GNUC_CONST;

HtkWidget * htk_hscale_new(HtkAdjustment * adjustment);

G_END_DECLS

#endif//__HTK_HSCALE_H__

/* him: set ts=8 sts=8 sw=8 noet: */
