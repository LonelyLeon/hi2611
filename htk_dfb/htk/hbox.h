#ifndef __HTK_HBOX_H__
#define __HTK_HBOX_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_HBOX            (htk_hbox_get_type ())
#define HTK_HBOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HBOX, HtkHBox))
#define HTK_HBOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HBOX, HtkHBoxClass))
#define HTK_IS_HBOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HBOX))
#define HTK_IS_HBOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HBOX))
#define HTK_HBOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HBOX, HtkHBoxClass))

struct HtkHBox {
	HtkBox box;
};

struct HtkHBoxClass {
	HtkBoxClass parent_class;
};

GType htk_hbox_get_type(void) G_GNUC_CONST;

HtkWidget * htk_hbox_new(gboolean homogeneous, gint spacing);

G_END_DECLS

#endif//__HTK_HBOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
