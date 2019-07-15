#ifndef __HTK_VIEWPORT_H__
#define __HTK_VIEWPORT_H__

#include <glib-object.h>
#include <htk/adjustment.h>

G_BEGIN_DECLS

#define HTK_TYPE_VIEWPORT            (htk_viewport_get_type ())
#define HTK_VIEWPORT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VIEWPORT, HtkViewport))
#define HTK_VIEWPORT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VIEWPORT, HtkViewportClass))
#define HTK_IS_VIEWPORT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VIEWPORT))
#define HTK_IS_VIEWPORT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VIEWPORT))
#define HTK_VIEWPORT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VIEWPORT, HtkViewportClass))

struct HtkViewport {
	HtkBin bin;

	HtkAdjustment * hadjustment;
	HtkAdjustment * vadjustment;

	/* offset in hdk window */
	gint x;
	gint y;
};

struct HtkViewportClass {
	HtkBinClass parent_class;
};

GType htk_viewport_get_type(void) G_GNUC_CONST;

HtkWidget * htk_viewport_new(HtkAdjustment * hadjustment,
		HtkAdjustment * vadjustment);

HtkAdjustment * htk_viewport_get_hadjustment(HtkViewport * viewport);
void            htk_viewport_set_hadjustment(HtkViewport * viewport,
		HtkAdjustment * hadjustment);

HtkAdjustment * htk_viewport_get_vadjustment(HtkViewport * viewport);
void            htk_viewport_set_vadjustment(HtkViewport * viewport,
		HtkAdjustment * vadjustment);

G_END_DECLS

#endif//__HTK_VIEWPORT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
