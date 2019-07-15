#ifndef __HTK_STYLE_IPTV_H__
#define __HTK_STYLE_IPTV_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_STYLE_IPTV            (htk_style_iptv_get_type ())
#define HTK_STYLE_IPTV(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_STYLE_IPTV, HtkStyleIptv))
#define HTK_STYLE_IPTV_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_STYLE_IPTV, HtkStyleIptvClass))
#define HTK_IS_STYLE_IPTV(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_STYLE_IPTV))
#define HTK_IS_STYLE_IPTV_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_STYLE_IPTV))
#define HTK_STYLE_IPTV_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_STYLE_IPTV, HtkStyleIptvClass))

struct HtkStyleIptv {
	HtkStyleDefault style;
};

struct HtkStyleIptvClass {
	HtkStyleDefaultClass parent_class;
};

GType htk_style_iptv_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_STYLE_IPTV_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
