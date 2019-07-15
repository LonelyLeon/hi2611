#ifndef __HTK_STOCK_ITEM_H__
#define __HTK_STOCK_ITEM_H__

#include <glib-object.h>

G_BEGIN_DECLS

struct HtkStockItem {
	gchar * stock_id;
	gchar * label;
	guint keyval;
	gchar * translation_domain;
};

void htk_stock_item_free(HtkStockItem * item);

G_END_DECLS

#endif//__HTK_STOCK_ITEM_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
