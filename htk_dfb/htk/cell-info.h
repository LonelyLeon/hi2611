#ifndef __HTK_ICON_INFO_H__
#define __HTK_ICON_INFO_H__

#include <glib-object.h>
#include <htk/cell-renderer.h>

G_BEGIN_DECLS

struct HtkCellInfo {
	HtkCellRenderer * cell; /* owned */

	gint requested_size;
	gint real_size;

	GSList * attributes; /* owned List<owned string, Type> */

	HtkPackType pack;
	gboolean expand;
};

HtkCellInfo * htk_cell_info_new(HtkCellRenderer * cell,
		gboolean expand, HtkPackType pack);
void htk_cell_info_free(HtkCellInfo * info);
void htk_cell_info_add_attribute(HtkCellInfo * info,
		const gchar * attribute, gint column);
void htk_cell_info_clear_attributes(HtkCellInfo * info);

G_END_DECLS

#endif//__HTK_ICON_INFO_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
