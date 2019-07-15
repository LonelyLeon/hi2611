#ifndef __HTK_TREE_MODEL_H__
#define __HTK_TREE_MODEL_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_TREE_MODEL            (htk_tree_model_get_type ())
#define HTK_TREE_MODEL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TREE_MODEL, HtkTreeModel))
#define HTK_TREE_MODEL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TREE_MODEL, HtkTreeModelClass))
#define HTK_IS_TREE_MODEL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TREE_MODEL))
#define HTK_IS_TREE_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TREE_MODEL))
#define HTK_TREE_MODEL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TREE_MODEL, HtkTreeModelClass))

#define HTK_TYPE_TREE_ITER            (htk_tree_iter_get_type ())
#define HTK_TYPE_TREE_PATH            (htk_tree_path_get_type ())

struct HtkTreeIter {
	gint stamp;
	gpointer user_data;
	gpointer user_data2;
	gpointer user_data3;
};

struct HtkTreePath {
	gint depth;
	gint * indices;
};

struct HtkTreeRowReference {
	HtkTreeModel * model; /* owned */
	HtkTreePath * path; /* owned */
};

struct HtkTreeModel {
	GObject parent_instance;
};

struct HtkTreeModelClass {
	GObjectClass parent_class;

	/* signals */

	void (* row_changed) (HtkTreeModel * model,
			HtkTreePath * path, HtkTreeIter * iter);
	void (* row_inserted) (HtkTreeModel * model,
			HtkTreePath * path, HtkTreeIter * iter);
	void (* row_deleted) (HtkTreeModel * model, HtkTreePath * path);

	/* virtual functions */

	gint (* get_n_columns) (HtkTreeModel * model);
	GType (* get_column_type) (HtkTreeModel * model, gint index_);
	gboolean (* get_iter) (HtkTreeModel * model,
			HtkTreeIter * iter, HtkTreePath * path);
	void (* get_value) (HtkTreeModel * model, HtkTreeIter * iter,
			gint column, GValue * value);
	gboolean (* iter_next) (HtkTreeModel * model, HtkTreeIter * iter);
	gboolean (* iter_children) (HtkTreeModel * model,
			HtkTreeIter * iter, HtkTreeIter * parent);
	gboolean (* iter_has_child) (HtkTreeModel * model, HtkTreeIter * iter);
	gint (* iter_n_children) (HtkTreeModel * model, HtkTreeIter * iter);
	gboolean (* iter_nth_child) (HtkTreeModel * model,
			HtkTreeIter * iter, HtkTreeIter * parent, gint n);
	gboolean (* iter_parent) (HtkTreeModel * model,
			HtkTreeIter * iter, HtkTreeIter * child);
	void (* ref_node) (HtkTreeModel * model, HtkTreeIter * iter);
	void (* unref_node) (HtkTreeModel * model, HtkTreeIter * iter);
};

GType htk_tree_model_get_type(void) G_GNUC_CONST;

gboolean htk_tree_model_get_iter_first(HtkTreeModel * model,
		HtkTreeIter * iter);
void htk_tree_model_get(HtkTreeModel * model, HtkTreeIter * iter, ...);
void htk_tree_model_get_valist(HtkTreeModel * model,
		HtkTreeIter * iter, va_list var_args);

void htk_tree_model_row_changed(HtkTreeModel * model,
		HtkTreePath * path, HtkTreeIter * iter);
void htk_tree_model_row_inserted(HtkTreeModel * model,
		HtkTreePath * path, HtkTreeIter * iter);
void htk_tree_model_row_deleted(HtkTreeModel * model, HtkTreePath * path);

gint htk_tree_model_get_n_columns(HtkTreeModel * model);
GType htk_tree_model_get_column_type(HtkTreeModel * model, gint index_);
gboolean htk_tree_model_get_iter(HtkTreeModel * model,
		HtkTreeIter * iter, HtkTreePath * path);
void htk_tree_model_get_value(HtkTreeModel * model,
		HtkTreeIter * iter, gint column, GValue * value);
gboolean htk_tree_model_iter_next(HtkTreeModel * model, HtkTreeIter * iter);
gboolean htk_tree_model_iter_children(HtkTreeModel * model,
		HtkTreeIter * iter, HtkTreeIter * parent);
gboolean htk_tree_model_iter_has_child(HtkTreeModel * model,
		HtkTreeIter * iter);
gint htk_tree_model_iter_n_children(HtkTreeModel * model, HtkTreeIter * iter);
gboolean htk_tree_model_iter_nth_child(HtkTreeModel * model,
		HtkTreeIter * iter, HtkTreeIter * parent, gint n);
gboolean htk_tree_model_iter_parent(HtkTreeModel * model,
		HtkTreeIter * iter, HtkTreeIter * child);
void htk_tree_model_ref_node(HtkTreeModel * model, HtkTreeIter * iter);
void htk_tree_model_unref_node(HtkTreeModel * model, HtkTreeIter * iter);

GType htk_tree_iter_get_type(void) G_GNUC_CONST;

HtkTreeIter * htk_tree_iter_copy(const HtkTreeIter * iter);
void htk_tree_iter_free(HtkTreeIter * iter);

GType htk_tree_path_get_type(void) G_GNUC_CONST;

HtkTreePath * htk_tree_path_new(void);
HtkTreePath * htk_tree_path_new_first(void);
HtkTreePath * htk_tree_path_copy(const HtkTreePath * path);
void htk_tree_path_free(HtkTreePath * path);
void htk_tree_path_append_index(HtkTreePath * path, gint index_);

HtkTreeRowReference * htk_tree_row_reference_new(HtkTreeModel * model,
		HtkTreePath * path);
void htk_tree_row_reference_free(HtkTreeRowReference * reference);
gboolean htk_tree_row_reference_valid(HtkTreeRowReference * reference);
HtkTreeModel * htk_tree_row_reference_get_model(HtkTreeRowReference * reference);
HtkTreePath * htk_tree_row_reference_get_path(HtkTreeRowReference * reference);

G_END_DECLS

#endif//__HTK_TREE_MODEL_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
