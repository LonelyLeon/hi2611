#ifndef __HTK_ARROW_H__
#define __HTK_ARROW_H__

#include <glib-object.h>
#include <directfb.h>
#include <htk/misc.h>

G_BEGIN_DECLS

#define HTK_TYPE_ARROW            (htk_arrow_get_type ())
#define HTK_ARROW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ARROW, HtkArrow))
#define HTK_ARROW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ARROW, HtkArrowClass))
#define HTK_IS_ARROW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ARROW))
#define HTK_IS_ARROW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ARROW))
#define HTK_ARROW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ARROW, HtkArrowClass))

struct HtkArrow {
	HtkMisc misc;

	HtkArrowType arrow_type;
	HtkShadowType shadow_type;
};

struct HtkArrowClass {
	HtkMiscClass parent_class;
};

GType htk_arrow_get_type(void) G_GNUC_CONST;

HtkWidget * htk_arrow_new(HtkArrowType arrow_type, HtkShadowType shadow_type);

void htk_arrow_set(HtkArrow * arrow,
		HtkArrowType arrow_type, HtkShadowType shadow_type);

G_END_DECLS

#endif//__HTK_ARROW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
