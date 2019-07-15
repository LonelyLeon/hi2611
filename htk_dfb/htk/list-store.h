#ifndef __HTK_LIST_STORE_H__
#define __HTK_LIST_STORE_H__

#include <glib-object.h>
#include <htk/tree-model.h>

G_BEGIN_DECLS

#define HTK_TYPE_LIST_STORE            (htk_list_store_get_type ())
#define HTK_LIST_STORE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_LIST_STORE, HtkListStore))
#define HTK_LIST_STORE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_LIST_STORE, HtkListStoreClass))
#define HTK_IS_LIST_STORE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_LIST_STORE))
#define HTK_IS_LIST_STORE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_LIST_STORE))
#define HTK_LIST_STORE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_LIST_STORE, HtkListStoreClass))

struct HtkListStore {
	HtkTreeModel parent_instance;

	gint stamp;
	gint length;

	gint n_columns;
	GType * column_headers; /* owned Type[] */

	GSequence * seq; /* owned Sequence<owned pointer[]> */
};

struct HtkListStoreClass {
	HtkTreeModelClass parent_class;
};

GType htk_list_store_get_type(void) G_GNUC_CONST;

HtkListStore * htk_list_store_new(gint n_columns, ...);
HtkListStore * htk_list_store_newv(gint n_columns, GType * types);
void htk_list_store_set_column_types(HtkListStore * store,
		gint n_columns, GType * types);
void htk_list_store_set(HtkListStore * store, HtkTreeIter * iter, ...);
void htk_list_store_set_valist(HtkListStore * store,
		HtkTreeIter * iter, va_list var_args);
void htk_list_store_set_value(HtkListStore * store, HtkTreeIter * iter,
		gint column, GValue * value);
gboolean htk_list_store_remove(HtkListStore * store, HtkTreeIter * iter);
void htk_list_store_insert(HtkListStore * store,
		HtkTreeIter * iter, gint position);
void htk_list_store_insert_before(HtkListStore * store,
		HtkTreeIter * iter, HtkTreeIter * sibling);
void htk_list_store_insert_after(HtkListStore * store,
		HtkTreeIter * iter, HtkTreeIter * sibling);
void htk_list_store_prepend(HtkListStore * store, HtkTreeIter * iter);
void htk_list_store_append(HtkListStore * store, HtkTreeIter * iter);
void htk_list_store_clear(HtkListStore * store);
gboolean htk_list_store_iter_is_valid(HtkListStore * store, HtkTreeIter * iter);

G_END_DECLS

#endif//__HTK_LIST_STORE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
