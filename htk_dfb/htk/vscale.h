#ifndef __HTK_VSCALE_H__
#define __HTK_VSCALE_H__

#include <glib-object.h>
#include <htk/scale.h>

G_BEGIN_DECLS

#define HTK_TYPE_VSCALE            (htk_vscale_get_type ())
#define HTK_VSCALE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VSCALE, HtkVScale))
#define HTK_VSCALE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VSCALE, HtkVScaleClass))
#define HTK_IS_VSCALE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VSCALE))
#define HTK_IS_VSCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VSCALE))
#define HTK_VSCALE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VSCALE, HtkVScaleClass))

struct HtkVScale {
	HtkScale scale;
};

struct HtkVScaleClass {
	HtkScaleClass parent_class;
};

GType htk_vscale_get_type(void) G_GNUC_CONST;

HtkWidget * htk_vscale_new(HtkAdjustment * adjustment);

G_END_DECLS

#endif//__HTK_VSCALE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
