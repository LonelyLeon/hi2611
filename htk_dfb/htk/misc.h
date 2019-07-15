#ifndef __HTK_MISC_H__
#define __HTK_MISC_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_MISC            (htk_misc_get_type ())
#define HTK_MISC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_MISC, HtkMisc))
#define HTK_MISC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_MISC, HtkMiscClass))
#define HTK_IS_MISC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_MISC))
#define HTK_IS_MISC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_MISC))
#define HTK_MISC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_MISC, HtkMiscClass))

struct HtkMisc {
	HtkWidget widget;

	gfloat xalign;
	gfloat yalign;

	/* FIXME: xpad and ypad should be both uint16 */
	gint xpad;
	gint ypad;
};

struct HtkMiscClass {
	HtkWidgetClass parent_class;
};

GType htk_misc_get_type(void) G_GNUC_CONST;

void htk_misc_get_alignment(HtkMisc * misc, gfloat * xalign, gfloat * yalign);
void htk_misc_set_alignment(HtkMisc * misc, gfloat xalign, gfloat yalign);
void htk_misc_get_padding(HtkMisc * misc, gint * xpad, gint * ypad);
void htk_misc_set_padding(HtkMisc * misc, gint xpad, gint ypad);

G_END_DECLS

#endif//__HTK_MISC_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
