#ifndef __HTK_PANED_H__
#define __HTK_PANED_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_PANED            (htk_paned_get_type ())
#define HTK_PANED(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_PANED, HtkPaned))
#define HTK_PANED_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_PANED, HtkPanedClass))
#define HTK_IS_PANED(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_PANED))
#define HTK_IS_PANED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_PANED))
#define HTK_PANED_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_PANED, HtkPanedClass))

struct HtkPaned {
	HtkContainer container;

	HtkWidget * child1;
	HtkWidget * child2;

	HtkOrientation orientation;
	gint position;
	gboolean child1_resize;
	gboolean child2_resize;
	gboolean child1_shrink;
	gboolean child2_shrink;
};

struct HtkPanedClass {
	HtkContainerClass parent_class;
};

GType htk_paned_get_type(void) G_GNUC_CONST;

void htk_paned_add1(HtkPaned * paned, HtkWidget * child);
void htk_paned_add2(HtkPaned * paned, HtkWidget * child);

void htk_paned_pack1(HtkPaned * paned,
		HtkWidget * child, gboolean resize, gboolean shrink);
void htk_paned_pack2(HtkPaned * paned,
		HtkWidget * child, gboolean resize, gboolean shrink);

HtkWidget * htk_paned_get_child1(HtkPaned * paned);
HtkWidget * htk_paned_get_child2(HtkPaned * paned);

gint htk_paned_get_position(HtkPaned * paned);
void htk_paned_set_position(HtkPaned * paned, gint position);

G_END_DECLS

#endif//__HTK_PANED_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
