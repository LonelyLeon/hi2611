#ifndef __HTK_XAML_H__
#define __HTK_XAML_H__

#include <glib-object.h>
#include <gmodule.h>

G_BEGIN_DECLS

#define HTK_TYPE_XAML            (htk_xaml_get_type ())
#define HTK_XAML(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_XAML, HtkXaml))
#define HTK_XAML_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_XAML, HtkXamlClass))
#define HTK_IS_XAML(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_XAML))
#define HTK_IS_XAML_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_XAML))
#define HTK_XAML_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_XAML, HtkXamlClass))

#define HTK_XAML_ERROR           (htk_xaml_error_quark())

struct HtkXaml {
	GObject parent_instance;

	/* all private */

	GHashTable * objects; /* HashTable<owned string, owned Object> */
	GSList * handlers; /* SList<onwed Handler> */
	GSList * object_stack; /* SList<unowned Object> */
};

struct HtkXamlClass {
	GObjectClass parent_class;

	/* all private */

	GModule * module; /* owned */
};

GType htk_xaml_get_type(void) G_GNUC_CONST;
 
GQuark htk_xaml_error_quark(void);

HtkXaml * htk_xaml_new(void);

guint htk_xaml_add_from_file(HtkXaml * xaml,
		const gchar * filename, GError ** error);
guint htk_xaml_add_from_string(HtkXaml * xaml,
		const gchar * buffer, gsize length, GError ** error);

GObject * htk_xaml_get_object(HtkXaml * xaml, const gchar * name);

void htk_xaml_connect_signals(HtkXaml * xaml, gpointer user_data);
//void htk_xaml_connect_signals_full(HtkXaml * xaml,
//		HtkXamlConnectFunc func, gpointer user_data);

GType htk_xaml_get_type_from_name(HtkXaml * xaml, const gchar * type_name);
gboolean htk_xaml_value_from_string(HtkXaml * xaml,
		const GParamSpec * pspec, const gchar * string,
		GValue * value, GError ** error);
gboolean htk_xaml_value_from_string_type(HtkXaml * xaml,
		GType type, const gchar * string,
		GValue * value, GError ** error);

G_END_DECLS

#endif//__HTK_XAML_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
