#ifndef __HTK_ICON_FACTORY_H__
#define __HTK_ICON_FACTORY_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_FACTORY            (htk_icon_factory_get_type ())
#define HTK_ICON_FACTORY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_FACTORY, HtkIconFactory))
#define HTK_ICON_FACTORY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_FACTORY, HtkIconFactoryClass))
#define HTK_IS_ICON_FACTORY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_FACTORY))
#define HTK_IS_ICON_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_FACTORY))
#define HTK_ICON_FACTORY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_FACTORY, HtkIconFactoryClass))

struct HtkIconFactory {
	GObject object;

	GHashTable * icons; /* HashTable<owned string, owned IconSet> */
};

struct HtkIconFactoryClass {
	GObjectClass parent_class;
};

GType htk_icon_factory_get_type(void) G_GNUC_CONST;

HtkIconFactory * htk_icon_factory_new(void);
HtkIconSet * htk_icon_factory_lookup(HtkIconFactory * factory,
		const gchar * stock_id);
HtkIconSet * htk_icon_factory_lookup_default(const gchar * stock_id);

G_END_DECLS

#endif//__HTK_ICON_FACTORY_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
