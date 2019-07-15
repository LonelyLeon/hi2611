#ifndef __HTK_CELL_VIEW_H__
#define __HTK_CELL_VIEW_H__

#include <glib-object.h>
#include <htk/widget.h>
#include <htk/tree-model.h>
#include <htk/cell-list.h>

G_BEGIN_DECLS

#define HTK_TYPE_CELL_VIEW            (htk_cell_view_get_type ())
#define HTK_CELL_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CELL_VIEW, HtkCellView))
#define HTK_CELL_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CELL_VIEW, HtkCellViewClass))
#define HTK_IS_CELL_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CELL_VIEW))
#define HTK_IS_CELL_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CELL_VIEW))
#define HTK_CELL_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CELL_VIEW, HtkCellViewClass))

/* implement HtkCellLayout */
struct HtkCellView {
	HtkWidget parent_instance;

	HtkTreeModel * model; /* owned */
	HtkTreeRowReference * displayed_row; /* owned */
	HtkCellList * cell_list; /* owned */
	IDirectFBFont * font;
};

struct HtkCellViewClass {
	HtkWidgetClass parent_class;
};

GType htk_cell_view_get_type(void) G_GNUC_CONST;

HtkWidget * htk_cell_view_new(void);

void htk_cell_view_set_model(HtkCellView * view, HtkTreeModel * model);
HtkTreeModel * htk_cell_view_get_model(HtkCellView * view);

void htk_cell_view_set_displayed_row(HtkCellView * view, HtkTreePath * path);
HtkTreePath * htk_cell_view_get_displayed_row(HtkCellView * view);

gboolean htk_cell_view_get_size_of_row(HtkCellView * view,
		HtkTreePath * path, HtkRequisition * requisition);

G_END_DECLS

#endif//__HTK_CELL_VIEW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
