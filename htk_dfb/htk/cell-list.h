#ifndef __HTK_CELL_LIST_H__
#define __HTK_CELL_LIST_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_CELL_LIST            (htk_cell_list_get_type ())
#define HTK_CELL_LIST(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CELL_LIST, HtkCellList))
#define HTK_CELL_LIST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CELL_LIST, HtkCellListClass))
#define HTK_IS_CELL_LIST(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CELL_LIST))
#define HTK_IS_CELL_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CELL_LIST))
#define HTK_CELL_LIST_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CELL_LIST, HtkCellListClass))

struct HtkCellList {
	GObject parent_instance;

	GList * infos; /* owned List<owned CellInfo> */

	HtkOrientation orientation;
	gint spacing;
};

struct HtkCellListClass {
	GObjectClass parent_class;
};

GType htk_cell_list_get_type(void) G_GNUC_CONST;

HtkCellList * htk_cell_list_new(HtkOrientation orientation);

void htk_cell_list_clear(HtkCellList * cell_list);

GList * htk_cell_list_get_cells(HtkCellList * cell_list);

void htk_cell_list_pack_cell(HtkCellList * cell_list,
		HtkCellRenderer * cell, gboolean expand, HtkPackType pack);

/* will take ownership of info */
void htk_cell_list_pack_info(HtkCellList * cell_list, HtkCellInfo * info);

void htk_cell_list_add_attribute(HtkCellList * cell_list,
		HtkCellRenderer * cell, const gchar * attribute, gint column);

void htk_cell_list_clear_attributes(HtkCellList * list, HtkCellRenderer * cell);

HtkCellInfo * htk_cell_list_find_info(HtkCellList * cell_list,
		const HtkCellRenderer * cell);

void htk_cell_list_set_data(HtkCellList * cell_list,
		HtkTreeModel * model, HtkTreeIter * iter);

gboolean htk_cell_list_get_size(HtkCellList * cell_list,
		HtkWidget * widget, HtkRequisition * requisition);

void htk_cell_list_render(HtkCellList * cell_list,
		HtkWidget * widget, HdkDrawable * drawable,
		const HdkRectangle * rect, HtkCellRendererState flags);

void htk_cell_list_size_allocate(HtkCellList * cell_list,
		gint width, gint height);

G_END_DECLS

#endif//__HTK_CELL_LIST_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
