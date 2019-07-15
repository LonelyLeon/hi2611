#ifndef __HTK_HPANED_H__
#define __HTK_HPANED_H__

#include <glib-object.h>
#include <htk/paned.h>

G_BEGIN_DECLS

#define HTK_TYPE_HPANED            (htk_hpaned_get_type ())
#define HTK_HPANED(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HPANED, HtkHPaned))
#define HTK_HPANED_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HPANED, HtkHPanedClass))
#define HTK_IS_HPANED(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HPANED))
#define HTK_IS_HPANED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HPANED))
#define HTK_HPANED_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HPANED, HtkHPanedClass))

struct HtkHPaned {
	HtkPaned paned;
};

struct HtkHPanedClass {
	HtkPanedClass parent_class;
};

GType htk_hpaned_get_type(void) G_GNUC_CONST;

HtkWidget * htk_hpaned_new(void);

G_END_DECLS

#endif//__HTK_HPANED_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
