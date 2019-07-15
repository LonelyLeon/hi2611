#ifndef __HTK_STOCK_H__
#define __HTK_STOCK_H__

#include <glib-object.h>

G_BEGIN_DECLS

void htk_stock_add(const HtkStockItem * items, guint n_items);
void htk_stock_add_static(const HtkStockItem * items, guint n_items);
GSList * htk_stock_list_ids(void);

G_END_DECLS

#endif//__HTK_STOCK_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
