#ifndef __HTK_SEPARATOR_H__
#define __HTK_SEPARATOR_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_SEPARATOR            (htk_separator_get_type ())
#define HTK_SEPARATOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_SEPARATOR, HtkSeparator))
#define HTK_SEPARATOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_SEPARATOR, HtkSeparatorClass))
#define HTK_IS_SEPARATOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_SEPARATOR))
#define HTK_IS_SEPARATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_SEPARATOR))
#define HTK_SEPARATOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_SEPARATOR, HtkSeparatorClass))

struct HtkSeparator {
	HtkWidget widget;

	HtkOrientation orientation;
};

struct HtkSeparatorClass {
	HtkWidgetClass parent_class;
};

GType htk_separator_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_SEPARATOR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
