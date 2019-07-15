#ifndef __HTK_STYLE_DESKTOP_H__
#define __HTK_STYLE_DESKTOP_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_STYLE_DESKTOP            (htk_style_desktop_get_type ())
#define HTK_STYLE_DESKTOP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_STYLE_DESKTOP, HtkStyleDesktop))
#define HTK_STYLE_DESKTOP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_STYLE_DESKTOP, HtkStyleDesktopClass))
#define HTK_IS_STYLE_DESKTOP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_STYLE_DESKTOP))
#define HTK_IS_STYLE_DESKTOP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_STYLE_DESKTOP))
#define HTK_STYLE_DESKTOP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_STYLE_DESKTOP, HtkStyleDesktopClass))

struct HtkStyleDesktop {
	HtkStyleDefault style_default;
};

struct HtkStyleDesktopClass {
	HtkStyleDefaultClass parent_class;
};

GType htk_style_desktop_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_STYLE_DESKTOP_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
