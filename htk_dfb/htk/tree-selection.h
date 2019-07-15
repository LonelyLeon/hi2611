#ifndef __HTK_TREE_SELECTION_H__
#define __HTK_TREE_SELECTION_H__

#include <glib-object.h>
#include <htk/tree-view.h>

G_BEGIN_DECLS

#define HTK_TYPE_TREE_SELECTION            (htk_tree_selection_get_type ())
#define HTK_TREE_SELECTION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TREE_SELECTION, HtkTreeSelection))
#define HTK_TREE_SELECTION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TREE_SELECTION, HtkTreeSelectionClass))
#define HTK_IS_TREE_SELECTION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TREE_SELECTION))
#define HTK_IS_TREE_SELECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TREE_SELECTION))
#define HTK_TREE_SELECTION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TREE_SELECTION, HtkTreeSelectionClass))

struct HtkTreeSelection {
	GObject parent_instance;

	HtkTreeView * treeview; /* unowned */
	HtkSelectionMode type;
//	HtkSelectionFunc user_func;
//	gpointer user_data;
//	GDestroyNotify destroy;
};

struct HtkTreeSelectionClass {
	GObjectClass parent_class;

	void (* changed) (HtkTreeSelection * selection);
};

GType htk_tree_selection_get_type(void) G_GNUC_CONST;

/* internal */
HtkTreeSelection * htk_tree_selection_new(void);
/* internal */
HtkTreeSelection * htk_tree_selection_new_with_tree_view(HtkTreeView * treeview);
/* internal */
void htk_tree_selection_set_tree_view(HtkTreeSelection * selection,
		HtkTreeView * treeview);

/* internal */
void htk_tree_selection_emit_changed(HtkTreeSelection * selection);

G_END_DECLS

#endif//__HTK_TREE_SELECTION_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
