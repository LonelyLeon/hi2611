#ifndef __HTK_VSCROLLBAR_H__
#define __HTK_VSCROLLBAR_H__

#include <glib-object.h>
#include <htk/scrollbar.h>

G_BEGIN_DECLS

#define HTK_TYPE_VSCROLLBAR            (htk_vscrollbar_get_type ())
#define HTK_VSCROLLBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VSCROLLBAR, HtkVScrollbar))
#define HTK_VSCROLLBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VSCROLLBAR, HtkVScrollbarClass))
#define HTK_IS_VSCROLLBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VSCROLLBAR))
#define HTK_IS_VSCROLLBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VSCROLLBAR))
#define HTK_VSCROLLBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VSCROLLBAR, HtkVScrollbarClass))

struct HtkVScrollbar {
	HtkScrollbar scrollbar;
};

struct HtkVScrollbarClass {
	HtkScrollbarClass parent_class;
};

GType htk_vscrollbar_get_type(void) G_GNUC_CONST;

HtkWidget * htk_vscrollbar_new(HtkAdjustment * adjustment);

G_END_DECLS

#endif//__HTK_VSCROLLBAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
