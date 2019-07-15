#ifndef __HTK_OBJECT_H__
#define __HTK_OBJECT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_OBJECT            (htk_object_get_type ())
#define HTK_OBJECT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_OBJECT, HtkObject))
#define HTK_OBJECT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_OBJECT, HtkObjectClass))
#define HTK_IS_OBJECT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_OBJECT))
#define HTK_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_OBJECT))
#define HTK_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_OBJECT, HtkObjectClass))

struct HtkObject {
	GInitiallyUnowned parent_instance;
};

struct HtkObjectClass {
	GInitiallyUnownedClass parent_class;
};

GType htk_object_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif//__HTK_OBJECT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
