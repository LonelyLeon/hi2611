#ifndef __HTK_ICON_BAR_CORE_H__
#define __HTK_ICON_BAR_CORE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_BAR_CORE            (htk_icon_bar_core_get_type ())
#define HTK_ICON_BAR_CORE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_BAR_CORE, HtkIconBarCore))
#define HTK_ICON_BAR_CORE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_BAR_CORE, HtkIconBarCoreClass))
#define HTK_IS_ICON_BAR_CORE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_BAR_CORE))
#define HTK_IS_ICON_BAR_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_BAR_CORE))
#define HTK_ICON_BAR_CORE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_BAR_CORE, HtkIconBarCoreClass))

struct HtkIconBarCore {
	GObject g_object;

	gint fps;
	gint steps;
	gdouble distance; /* distance between two items */
	gdouble min; /* minimal step */
	gint current;
	gdouble offset; /* offset of distance */
};

struct HtkIconBarCoreClass {
	GObjectClass parent_class;

	void (* clear) (HtkIconBarCore * core);
	void (* place_item) (HtkIconBarCore * core, gint index, gdouble pos);
};

GType htk_icon_bar_core_get_type(void) G_GNUC_CONST;

void htk_icon_bar_core_next(HtkIconBarCore * core);
void htk_icon_bar_core_prev(HtkIconBarCore * core);
gboolean htk_icon_bar_core_timeout(HtkIconBarCore * core);
void htk_icon_bar_core_expose(HtkIconBarCore * core);
void htk_icon_bar_core_clear(HtkIconBarCore * core);
void htk_icon_bar_core_place_item(HtkIconBarCore * core,
		gint index, gdouble pos);

G_END_DECLS

#endif//__HTK_ICON_BAR_CORE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
