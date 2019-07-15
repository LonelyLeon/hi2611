#ifndef __HTK_STYLE_DEFAULT_H__
#define __HTK_STYLE_DEFAULT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_STYLE_DEFAULT            (htk_style_default_get_type ())
#define HTK_STYLE_DEFAULT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_STYLE_DEFAULT, HtkStyleDefault))
#define HTK_STYLE_DEFAULT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_STYLE_DEFAULT, HtkStyleDefaultClass))
#define HTK_IS_STYLE_DEFAULT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_STYLE_DEFAULT))
#define HTK_IS_STYLE_DEFAULT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_STYLE_DEFAULT))
#define HTK_STYLE_DEFAULT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_STYLE_DEFAULT, HtkStyleDefaultClass))

struct HtkStyleDefault {
	HtkStyle style;
};

struct HtkStyleDefaultClass {
	HtkStyleClass parent_class;
};

GType htk_style_default_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_STYLE_DEFAULT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
