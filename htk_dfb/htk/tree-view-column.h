#ifndef __HTK_TREE_VIEW_COLUMN_H__
#define __HTK_TREE_VIEW_COLUMN_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_TREE_VIEW_COLUMN            (htk_tree_view_column_get_type ())
#define HTK_TREE_VIEW_COLUMN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TREE_VIEW_COLUMN, HtkTreeViewColumn))
#define HTK_TREE_VIEW_COLUMN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TREE_VIEW_COLUMN, HtkTreeViewColumnClass))
#define HTK_IS_TREE_VIEW_COLUMN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TREE_VIEW_COLUMN))
#define HTK_IS_TREE_VIEW_COLUMN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TREE_VIEW_COLUMN))
#define HTK_TREE_VIEW_COLUMN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TREE_VIEW_COLUMN, HtkTreeViewColumnClass))

struct HtkTreeViewColumn {
	GObject parent_instance;

	HtkWidget * treeview; /* unowned */

	gchar * title;

	gint width;
	gint fixed_width;
	gint spacing;
	gfloat xalign;

	GList * cell_list; /* owned List<owned _Info> */

	gboolean visible;
};

struct HtkTreeViewColumnClass {
	GObjectClass parent_class;
};

GType htk_tree_view_column_get_type(void) G_GNUC_CONST;

HtkTreeViewColumn * htk_tree_view_column_new(void);
HtkTreeViewColumn * htk_tree_view_column_new_with_attributes(
		const gchar * title, HtkCellRenderer * cell, ...);

/* internal */
void htk_tree_view_column_set_tree_view(HtkTreeViewColumn * column,
		HtkTreeView * treeview);

/* internal */
void htk_tree_view_column_set_attributesv(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, va_list var_args);

void htk_tree_view_column_clear(HtkTreeViewColumn * column);
void htk_tree_view_column_pack_start(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, gboolean expand);
void htk_tree_view_column_pack_end(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, gboolean expand);

void htk_tree_view_column_add_attribute(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, const gchar * attribute,
		gint column_id);
void htk_tree_view_column_set_attributes(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, ...);
void htk_tree_view_column_clear_attributes(HtkTreeViewColumn * column,
		HtkCellRenderer * cell);

void htk_tree_view_column_set_spacing(HtkTreeViewColumn * column, gint spacing);
gint htk_tree_view_column_get_spacing(HtkTreeViewColumn * column);

void htk_tree_view_column_set_visible(HtkTreeViewColumn * column,
		gboolean visible);
gboolean htk_tree_view_column_get_visible(HtkTreeViewColumn * column);

gint htk_tree_view_column_get_width(HtkTreeViewColumn * column);

void htk_tree_view_column_set_fixed_width(HtkTreeViewColumn * column,
		gint width);
gint htk_tree_view_column_get_fixed_width(HtkTreeViewColumn * column);

void htk_tree_view_column_set_title(HtkTreeViewColumn * column,
		const gchar * title);
const gchar * htk_tree_view_column_get_title(HtkTreeViewColumn * column);

/* TODO: expand, alignment */

void htk_tree_view_column_cell_get_size(HtkTreeViewColumn * column,
		const HdkRectangle * cell_area,
		gint * x_offset, gint * y_offset, gint * width, gint * height);
gboolean htk_tree_view_column_cell_get_position(HtkTreeViewColumn * column,
		HtkCellRenderer * cell, gint * start_pos, gint * width);

void htk_tree_view_column_queue_resize(HtkTreeViewColumn * column);

G_END_DECLS

#endif//__HTK_TREE_VIEW_COLUMN_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
