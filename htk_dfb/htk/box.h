#ifndef __HTK_BOX_H__
#define __HTK_BOX_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_BOX            (htk_box_get_type ())
#define HTK_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_BOX, HtkBox))
#define HTK_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_BOX, HtkBoxClass))
#define HTK_IS_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_BOX))
#define HTK_IS_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_BOX))
#define HTK_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_BOX, HtkBoxClass))

struct HtkBoxChild {
	HtkWidget * widget;
	gboolean expand;
	gboolean fill;
	guint padding;
};

struct HtkBox {
	HtkContainer container;

	GList * children; /* List<owned BoxChild> */

	gboolean homogeneous;
	gint spacing;
};

struct HtkBoxClass {
	HtkContainerClass parent_class;
};

GType htk_box_get_type(void) G_GNUC_CONST;

void htk_box_pack_start(HtkBox * box, HtkWidget * widget,
		gboolean expand, gboolean fill, guint padding);
void htk_box_pack_end(HtkBox * box, HtkWidget * widget,
		gboolean expand, gboolean fill, guint padding);

G_END_DECLS

#endif//__HTK_BOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
