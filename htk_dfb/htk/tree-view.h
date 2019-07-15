#ifndef __HTK_TREE_VIEW_H__
#define __HTK_TREE_VIEW_H__

#include <glib-object.h>
#include <htk/widget.h>
#include <htk/tree-model.h>

G_BEGIN_DECLS

#define HTK_TYPE_TREE_VIEW            (htk_tree_view_get_type ())
#define HTK_TREE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TREE_VIEW, HtkTreeView))
#define HTK_TREE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TREE_VIEW, HtkTreeViewClass))
#define HTK_IS_TREE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TREE_VIEW))
#define HTK_IS_TREE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TREE_VIEW))
#define HTK_TREE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TREE_VIEW, HtkTreeViewClass))

struct HtkTreeView {
	HtkWidget parent_instance;

	HtkTreeModel * model; /* owned */

	HtkAdjustment * hadjustment; /* owned */
	HtkAdjustment * vadjustment; /* owned */

	HtkTreeRowReference * cursor; /* owned */
	HtkTreeViewColumn * focus_column; /* unowned */

	HtkTreeSelection * selection; /* owned */

	HtkTreeViewGridLines grid_lines;
	gint grid_line_width;

	gint n_columns;
	GList * columns; /* owned List<owned ...> */
	IDirectFBFont * font;

	gint fixed_height;
};

struct HtkTreeViewClass {
	HtkWidgetClass parent_class;

	void (* set_scroll_adjustments) (HtkTreeView * treeview,
			HtkAdjustment * hadjustment,
			HtkAdjustment * vadjustment);

	void (* row_activated) (HtkTreeView * treeview,
			HtkTreePath * path, HtkTreeViewColumn * column);

	void (* columns_changed) (HtkTreeView * treeview);
	void (* cursor_changed) (HtkTreeView * treeview);

	gboolean (* move_cursor) (HtkTreeView * treeview,
			HtkMovementStep step, gint count);
	gboolean (* select_all) (HtkTreeView * treeview);
	gboolean (* unselect_all) (HtkTreeView * treeview);
	gboolean (* select_cursor_row) (HtkTreeView * treeview,
			gboolean start_editing);
	gboolean (* toggle_cursor_row) (HtkTreeView * treeview);
};

GType htk_tree_view_get_type(void) G_GNUC_CONST;

HtkWidget * htk_tree_view_new(void);
HtkWidget * htk_tree_view_new_with_model(HtkTreeModel * model);

HtkTreeModel * htk_tree_view_get_model(HtkTreeView * treeview);
void htk_tree_view_set_model(HtkTreeView * treeview, HtkTreeModel * model);

HtkTreeSelection * htk_tree_view_get_section(HtkTreeView * treeview);

HtkAdjustment * htk_tree_view_get_hadjustment(HtkTreeView * treeview);
void htk_tree_view_set_hadjustment(HtkTreeView * treeview, HtkAdjustment * adj);
HtkAdjustment * htk_tree_view_get_vadjustment(HtkTreeView * treeview);
void htk_tree_view_set_vadjustment(HtkTreeView * treeview, HtkAdjustment * adj);

gboolean htk_tree_view_get_headers_visible(HtkTreeView * treeview);
void htk_tree_view_set_headers_visible(HtkTreeView * treeview, gboolean visible);

gboolean htk_tree_view_get_fixed_height_mode(HtkTreeView * treeview);
void htk_tree_view_set_fixed_height_mode(HtkTreeView * treeview,
		gboolean enable);

HtkTreeViewGridLines htk_tree_view_get_grid_lines(HtkTreeView * treeview);
void htk_tree_view_set_grid_lines(HtkTreeView * treeview,
		HtkTreeViewGridLines lines);

gint htk_tree_view_append_column(HtkTreeView * treeview,
		HtkTreeViewColumn * column);
gint htk_tree_view_remove_column(HtkTreeView * treeview,
		HtkTreeViewColumn * column);
gint htk_tree_view_insert_column(HtkTreeView * treeview,
		HtkTreeViewColumn * column, gint position);
gint htk_tree_view_insert_column_with_attributes(HtkTreeView * treeview,
		gint position, const gchar * title, HtkCellRenderer * cell, ...);
//gint htk_tree_view_insert_column_with_data_func(HtkTreeView * treeview,
//		gint position, const gchar * title, HtkCellRenderer * cell,
//		HtkTreeCellDataFunc func, gpointer data, GDestroyNotify notify);
HtkTreeViewColumn * htk_tree_view_get_column(HtkTreeView * treeview, gint n);

void htk_tree_view_scroll_to_point(HtkTreeView * treeview, gint x, gint y);
void htk_tree_view_scroll_to_cell(HtkTreeView * treeview,
		HtkTreePath * path, HtkTreeViewColumn * column,
		gboolean use_align, gfloat row_align, gfloat col_align);

void htk_tree_view_set_cursor_on_cell(HtkTreeView * treeview,
		HtkTreePath * path, HtkTreeViewColumn * column,
		HtkCellRenderer * cell, gboolean start_editing);
void htk_tree_view_set_cursor(HtkTreeView * treeview, HtkTreePath * path,
		HtkTreeViewColumn * column, gboolean start_editing);
void htk_tree_view_get_cursor(HtkTreeView * treeview,
		HtkTreePath ** path, HtkTreeViewColumn ** column);

gboolean htk_tree_view_get_path_at_pos(HtkTreeView * treeview, gint x, gint y,
		HtkTreePath ** path, HtkTreeViewColumn ** column,
		gint * cell_x, gint * cell_y);

void htk_tree_view_get_cell_area(HtkTreeView * treeview, HtkTreePath * path,
		HtkTreeViewColumn * column, HdkRectangle * rect);
void htk_tree_view_get_background_area(HtkTreeView * treeview,
		HtkTreePath * path, HtkTreeViewColumn * column,
		HdkRectangle * rect);
void htk_tree_view_get_visible_rect(HtkTreeView * treeview, HdkRectangle * rect);
gboolean htk_tree_view_get_visible_range(HtkTreeView * treeview,
		HtkTreePath ** start_path, HtkTreePath ** end_path);

void htk_tree_view_row_activated(HtkTreeView * treeview,
		HtkTreePath * path, HtkTreeViewColumn * column);

G_END_DECLS

#endif//__HTK_TREE_VIEW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
