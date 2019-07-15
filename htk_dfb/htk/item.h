#ifndef __HTK_ITEM_H__
#define __HTK_ITEM_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_ITEM            (htk_item_get_type ())
#define HTK_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ITEM, HtkItem))
#define HTK_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ITEM, HtkItemClass))
#define HTK_IS_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ITEM))
#define HTK_IS_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ITEM))
#define HTK_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ITEM, HtkItemClass))

struct HtkItem {
	HtkBin bin;
};

struct HtkItemClass {
	HtkBinClass parent_class;

	void (* select) (HtkItem * item);
	void (* deselect) (HtkItem * item);
	void (* toggle) (HtkItem * item);
};

GType htk_item_get_type(void) G_GNUC_CONST;

void htk_item_select(HtkItem * item);
void htk_item_deselect(HtkItem * item);
void htk_item_toggle(HtkItem * item);

G_END_DECLS

#endif//__HTK_ITEM_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
