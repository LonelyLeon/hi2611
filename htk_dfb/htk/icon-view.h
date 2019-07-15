#ifndef __HTK_ICON_VIEW_H__
#define __HTK_ICON_VIEW_H__

#include <glib-object.h>
#include <htk/container.h>
#include <htk/tree-model.h>
#include <htk/cell-list.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_VIEW            (htk_icon_view_get_type ())
#define HTK_ICON_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_VIEW, HtkIconView))
#define HTK_ICON_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_VIEW, HtkIconViewClass))
#define HTK_IS_ICON_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_VIEW))
#define HTK_IS_ICON_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_VIEW))
#define HTK_ICON_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_VIEW, HtkIconViewClass))

/* implement HtkCellLayout */
struct HtkIconView {
	HtkContainer parent_instance;

	HtkTreeModel * model; /* owned */

	HtkCellList * cell_list; /* owned */

	HtkSelectionMode selection_mode;

	HtkAdjustment * hadjustment; /* owned */
	HtkAdjustment * vadjustment; /* owned */

	HdkRectangle items_area;

	gint cursor;

	gint item_width;
	gint item_height;

	/* grids = columns * rows.
	 * grids is the count of items can be drawn with no scroll */
	gint n_columns;
	gint n_rows;
	gint page;

	gint row_spacing;
	gint column_spacing;

	HtkOrientation orientation;

	guint direction;
	guint tag;
	gboolean focus_top;
	gboolean should_keep_focus;

	gdouble offset;
	guint tag_timeout;
	IDirectFBFont * font;
	gboolean enable_cycle;
	gboolean enable_wrap_line;
	const HdkColor * row_color;
};

struct HtkIconViewClass {
	HtkContainerClass parent_class;
	void (* cursor_changed) (HtkWidget * widget);
};

GType htk_icon_view_get_type(void) G_GNUC_CONST;

HtkIconView * htk_icon_view_new(void);
HtkIconView * htk_icon_view_new_with_model(HtkTreeModel * model);

HtkTreeModel * htk_icon_view_get_model(HtkIconView * view);
void htk_icon_view_set_model(HtkIconView * view, HtkTreeModel * model);

HtkOrientation htk_icon_view_get_item_orientation(HtkIconView * view);
void htk_icon_view_set_item_orientation(HtkIconView * view,
		HtkOrientation orientation);
void htk_icon_view_set_row_spacing(HtkIconView * view, gint row_spacing);
void htk_icon_view_set_cursor(HtkIconView * view, gint cursor);
void htk_icon_view_set_column_spacing(HtkIconView * view, gint column_spacing);

G_END_DECLS

#endif//__HTK_ICON_VIEW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
