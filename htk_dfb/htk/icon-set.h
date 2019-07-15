#ifndef __HTK_ICON_SET_H__
#define __HTK_ICON_SET_H__

#include <glib-object.h>

G_BEGIN_DECLS

struct HtkIconSet {
	guint ref_count;

	GList * sources; /* List<owned IconSource> */
};

HtkIconSet * htk_icon_set_ref(HtkIconSet * iconset);
void         htk_icon_set_unref(HtkIconSet * iconset);

HdkPixbuf * htk_icon_set_render_icon(HtkIconSet * iconset,
		HtkStyle * style, HtkTextDirection direction,
		HtkStateType state, HtkIconSize size,
		HtkWidget * widget, const gchar * detail);

G_END_DECLS

#endif//__HTK_ICON_SET_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
