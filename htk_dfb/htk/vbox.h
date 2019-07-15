#ifndef __HTK_VBOX_H__
#define __HTK_VBOX_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_VBOX            (htk_vbox_get_type ())
#define HTK_VBOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VBOX, HtkVBox))
#define HTK_VBOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VBOX, HtkVBoxClass))
#define HTK_IS_VBOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VBOX))
#define HTK_IS_VBOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VBOX))
#define HTK_VBOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VBOX, HtkVBoxClass))

struct HtkVBox{
	HtkBox box;
};

struct HtkVBoxClass{
	HtkBoxClass parent_class;
};

GType htk_vbox_get_type(void) G_GNUC_CONST;

HtkWidget * htk_vbox_new(gboolean homogeneous, gint spacing);

G_END_DECLS

#endif//__HTK_VBOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
