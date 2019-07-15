#ifndef __HTK_ICON_BAR_H__
#define __HTK_ICON_BAR_H__

#include <glib-object.h>
#include <htk/icon-bar-impl.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_BAR            (htk_icon_bar_get_type ())
#define HTK_ICON_BAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_BAR, HtkIconBar))
#define HTK_ICON_BAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_BAR, HtkIconBarClass))
#define HTK_IS_ICON_BAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_BAR))
#define HTK_IS_ICON_BAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_BAR))
#define HTK_ICON_BAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_BAR, HtkIconBarClass))

struct HtkIconBar {
	HtkWidget widget;

	HtkIconBarImpl * impl;

	guint tag_timeout;
};

struct HtkIconBarClass {
	HtkWidgetClass parent_class;

	void (* cursor_changed) (HtkIconBar * ibar);
	void (* clicked) (HtkIconBar * ibar);
};

GType htk_icon_bar_get_type(void) G_GNUC_CONST;

HtkIconBar * htk_icon_bar_new(void);

gint htk_icon_bar_count(HtkIconBar * ibar);
gint htk_icon_bar_get_index(HtkIconBar * ibar);
void htk_icon_bar_clear(HtkIconBar * ibar);
void htk_icon_bar_prepend(HtkIconBar * ibar, IDirectFBSurface * image);
void htk_icon_bar_append(HtkIconBar * ibar, IDirectFBSurface * image);

const IDirectFBSurface * htk_icon_bar_get_image(HtkIconBar * ibar, guint index);
void htk_icon_bar_set_image(HtkIconBar * ibar,
		guint index, IDirectFBSurface * image);

G_END_DECLS

#endif//__HTK_ICON_BAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
