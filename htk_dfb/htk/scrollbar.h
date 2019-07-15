#ifndef __HTK_SCROLLBAR_H__
#define __HTK_SCROLLBAR_H__

#include <glib-object.h>
#include <htk/range.h>

G_BEGIN_DECLS

#define HTK_TYPE_SCROLLBAR            (htk_scrollbar_get_type ())
#define HTK_SCROLLBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_SCROLLBAR, HtkScrollbar))
#define HTK_SCROLLBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_SCROLLBAR, HtkScrollbarClass))
#define HTK_IS_SCROLLBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_SCROLLBAR))
#define HTK_IS_SCROLLBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_SCROLLBAR))
#define HTK_SCROLLBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_SCROLLBAR, HtkScrollbarClass))

struct HtkScrollbar {
	HtkRange range;
};

struct HtkScrollbarClass {
	HtkRangeClass parent_class;
};

GType htk_scrollbar_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_SCROLLBAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
