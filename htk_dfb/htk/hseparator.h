#ifndef __HTK_HSEPARATOR_H__
#define __HTK_HSEPARATOR_H__

#include <glib-object.h>
#include <htk/separator.h>

G_BEGIN_DECLS

#define HTK_TYPE_HSEPARATOR            (htk_hseparator_get_type ())
#define HTK_HSEPARATOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HSEPARATOR, HtkHSeparator))
#define HTK_HSEPARATOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HSEPARATOR, HtkHSeparatorClass))
#define HTK_IS_HSEPARATOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HSEPARATOR))
#define HTK_IS_HSEPARATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HSEPARATOR))
#define HTK_HSEPARATOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HSEPARATOR, HtkHSeparatorClass))

struct HtkHSeparator {
	HtkSeparator separator;
};

struct HtkHSeparatorClass {
	HtkSeparatorClass parent_class;
};

GType       htk_hseparator_get_type(void) G_GNUC_CONST;
HtkWidget * htk_hseparator_new(void);

G_END_DECLS

#endif//__HTK_HSEPARATOR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
