#ifndef __HTK_VPANED_H__
#define __HTK_VPANED_H__

#include <glib-object.h>
#include <htk/paned.h>

G_BEGIN_DECLS

#define HTK_TYPE_VPANED            (htk_vpaned_get_type ())
#define HTK_VPANED(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VPANED, HtkVPaned))
#define HTK_VPANED_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VPANED, HtkVPanedClass))
#define HTK_IS_VPANED(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VPANED))
#define HTK_IS_VPANED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VPANED))
#define HTK_VPANED_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VPANED, HtkVPanedClass))

struct HtkVPaned {
	HtkPaned paned;
};

struct HtkVPanedClass {
	HtkPanedClass parent_class;
};

GType htk_vpaned_get_type(void) G_GNUC_CONST;

HtkWidget * htk_vpaned_new(void);

G_END_DECLS

#endif//__HTK_HPANED_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
