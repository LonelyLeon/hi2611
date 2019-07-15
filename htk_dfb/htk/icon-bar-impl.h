#ifndef __HTK_ICON_BAR_IMPL_H__
#define __HTK_ICON_BAR_IMPL_H__

#include <glib-object.h>
#include <htk/icon-bar-core.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_BAR_IMPL            (htk_icon_bar_impl_get_type ())
#define HTK_ICON_BAR_IMPL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_BAR_IMPL, HtkIconBarImpl))
#define HTK_ICON_BAR_IMPL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_BAR_IMPL, HtkIconBarImplClass))
#define HTK_IS_ICON_BAR_IMPL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_BAR_IMPL))
#define HTK_IS_ICON_BAR_IMPL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_BAR_IMPL))
#define HTK_ICON_BAR_IMPL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_BAR_IMPL, HtkIconBarImplClass))

struct HtkIconBarImpl {
	HtkIconBarCore core;

	gdouble width;
	gdouble height;

	GList * images; /* owned List<owned IDirectFBSurface> */
	gint count;

	IDirectFBSurface * surface; /* owned */
};

struct HtkIconBarImplClass {
	HtkIconBarCoreClass parent_class;

	void (* resize) (HtkIconBarImpl * impl, gint width, gint height);
	void (* draw_item) (HtkIconBarImpl * impl,
			gint index, gdouble x, gdouble y, gdouble w, gdouble h);
};

GType htk_icon_bar_impl_get_type(void) G_GNUC_CONST;

HtkIconBarImpl * htk_icon_bar_impl_new(void);

gint htk_icon_bar_impl_count(HtkIconBarImpl * impl);
void htk_icon_bar_impl_remove_all(HtkIconBarImpl * impl);
void htk_icon_bar_impl_prepend(HtkIconBarImpl * impl, IDirectFBSurface * image);
void htk_icon_bar_impl_append(HtkIconBarImpl * impl, IDirectFBSurface * image);

const IDirectFBSurface * htk_icon_bar_impl_get_surface(HtkIconBarImpl * impl);
const IDirectFBSurface * htk_icon_bar_impl_get_image(HtkIconBarImpl * impl,
		guint index);
void htk_icon_bar_impl_set_image(HtkIconBarImpl * impl,
		guint index, IDirectFBSurface * image);

void htk_icon_bar_impl_resize(HtkIconBarImpl * impl, gint width, gint height);
void htk_icon_bar_impl_draw_item(HtkIconBarImpl * impl,
		guint index, gdouble x, gdouble y, gdouble w, gdouble h);

G_END_DECLS

#endif//__HTK_ICON_BAR_IMPL_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
