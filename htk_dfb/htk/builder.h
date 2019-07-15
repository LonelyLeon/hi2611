#ifndef __HTK_BUILDER_H__
#define __HTK_BUILDER_H__

#include <glib-object.h>
#include <gmodule.h>

G_BEGIN_DECLS

#define HTK_TYPE_BUILDER            (htk_builder_get_type ())
#define HTK_BUILDER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_BUILDER, HtkBuilder))
#define HTK_BUILDER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_BUILDER, HtkBuilderClass))
#define HTK_IS_BUILDER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_BUILDER))
#define HTK_IS_BUILDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_BUILDER))
#define HTK_BUILDER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_BUILDER, HtkBuilderClass))

#define HTK_BUILDER_ERROR           (htk_builder_error_quark())

struct HtkBuilder {
	GObject parent_instance;

	/* all private */

	GHashTable * objects; /* HashTable<owned string, owned Object> */
	GSList * object_stack; /* SList<unowned Object> */
	GSList * child_stack; /* SList<unowned Object> */
	GObject * child; /* unowned */
	GSList * handlers; /* SList<onwed Handler> */

	gchar * property_name;
	gboolean child_property;

};

struct HtkBuilderClass {
	GObjectClass parent_class;

	/* all private */

	GModule * module; /* owned */
};

GType htk_builder_get_type(void) G_GNUC_CONST;
 
GQuark htk_builder_error_quark(void);

HtkBuilder * htk_builder_new(void);

guint htk_builder_add_from_file(HtkBuilder * builder,
		const gchar * filename, GError ** error);
guint htk_builder_add_from_string(HtkBuilder * builder,
		const gchar * buffer, gsize length, GError ** error);

GObject * htk_builder_get_object(HtkBuilder * builder, const gchar * name);

void htk_builder_connect_signals(HtkBuilder * builder, gpointer user_data);
//void htk_builder_connect_signals_full(HtkBuilder * builder,
//		HtkBuilderConnectFunc func, gpointer user_data);

GType htk_builder_get_type_from_name(HtkBuilder * builder,
		const gchar * type_name);
gboolean htk_builder_value_from_string(HtkBuilder * builder,
		GParamSpec * pspec, const gchar * string,
		GValue * value, GError ** error);
gboolean htk_builder_value_from_string_type(HtkBuilder * builder,
		GType type, const gchar * string,
		GValue * value, GError ** error);

G_END_DECLS

#endif//__HTK_BUILDER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
