#ifndef __HTK_STYLE_DVB_H__
#define __HTK_STYLE_DVB_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_STYLE_DVB            (htk_style_dvb_get_type ())
#define HTK_STYLE_DVB(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_STYLE_DVB, HtkStyleDvb))
#define HTK_STYLE_DVB_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_STYLE_DVB, HtkStyleDvbClass))
#define HTK_IS_STYLE_DVB(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_STYLE_DVB))
#define HTK_IS_STYLE_DVB_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_STYLE_DVB))
#define HTK_STYLE_DVB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_STYLE_DVB, HtkStyleDvbClass))

struct HtkStyleDvb {
	HtkStyleDefault style;
};

struct HtkStyleDvbClass {
	HtkStyleDefaultClass parent_class;
};

GType htk_style_dvb_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_STYLE_DVB_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
