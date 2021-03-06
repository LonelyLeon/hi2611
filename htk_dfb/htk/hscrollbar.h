#ifndef __HTK_HSCROLLBAR_H__
#define __HTK_HSCROLLBAR_H__

#include <glib-object.h>
#include <htk/scrollbar.h>

G_BEGIN_DECLS

#define HTK_TYPE_HSCROLLBAR            (htk_hscrollbar_get_type ())
#define HTK_HSCROLLBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HSCROLLBAR, HtkHScrollbar))
#define HTK_HSCROLLBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HSCROLLBAR, HtkHScrollbarClass))
#define HTK_IS_HSCROLLBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HSCROLLBAR))
#define HTK_IS_HSCROLLBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HSCROLLBAR))
#define HTK_HSCROLLBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HSCROLLBAR, HtkHScrollbarClass))

struct HtkHScrollbar {
	HtkScrollbar scrollbar;
};

struct HtkHScrollbarClass {
	HtkScrollbarClass parent_class;
};

GType htk_hscrollbar_get_type(void) G_GNUC_CONST;

HtkWidget * htk_hscrollbar_new(HtkAdjustment * adjustment);

G_END_DECLS

#endif//__HTK_HSCROLLBAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
