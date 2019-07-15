#ifndef __HTK_CELL_LAYOUT_H__
#define __HTK_CELL_LAYOUT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_CELL_LAYOUT            (htk_cell_layout_get_type())
#define HTK_CELL_LAYOUT(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),    HTK_TYPE_CELL_LAYOUT, HtkCellLayout))
#define HTK_IS_CELL_LAYOUT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),    HTK_TYPE_CELL_LAYOUT))
#define HTK_CELL_LAYOUT_GET_IFACE(obj)  (G_TYPE_INSTANCE_GET_INTERFACE((obj), HTK_TYPE_CELL_LAYOUT, HtkCellLayoutIface))

/* require GObject */
struct HtkCellLayoutIface {
	GTypeInterface parent_iface;

	/* virtual functions */

	void (* clear) (HtkCellLayout * layout);
	GList * (* get_cells) (HtkCellLayout * layout);
	void (* pack_start) (HtkCellLayout * layout,
			HtkCellRenderer * cell, gboolean expand);
	void (* pack_end) (HtkCellLayout * layout,
			HtkCellRenderer * cell, gboolean expand);
	void (* add_attribute) (HtkCellLayout * layout, HtkCellRenderer * cell,
			const gchar * attribute, gint column);
	void (* clear_attributes) (HtkCellLayout * layout,
			HtkCellRenderer * cell);
};

GType htk_cell_layout_get_type(void) G_GNUC_CONST;

void htk_cell_layout_clear(HtkCellLayout * layout);
GList * htk_cell_layout_get_cells(HtkCellLayout * layout);

void htk_cell_layout_pack_start(HtkCellLayout * layout,
		HtkCellRenderer * cell, gboolean expand);
void htk_cell_layout_pack_end(HtkCellLayout * layout,
		HtkCellRenderer * cell, gboolean expand);

void htk_cell_layout_add_attribute(HtkCellLayout * layout,
		HtkCellRenderer * cell, const gchar * attribute, gint column);
void htk_cell_layout_clear_attributes(HtkCellLayout * layout,
		HtkCellRenderer * cell);

void htk_cell_layout_set_attributes(HtkCellLayout * layout,
		HtkCellRenderer * cell, ...);

G_END_DECLS

#endif//__HTK_CELL_LAYOUT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
