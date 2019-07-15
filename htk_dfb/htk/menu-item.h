#ifndef __HTK_MENU_ITEM_H__
#define __HTK_MENU_ITEM_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_MENU_ITEM            (htk_menu_item_get_type ())
#define HTK_MENU_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_MENU_ITEM, HtkMenuItem))
#define HTK_MENU_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_MENU_ITEM, HtkMenuItemClass))
#define HTK_IS_MENU_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_MENU_ITEM))
#define HTK_IS_MENU_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_MENU_ITEM))
#define HTK_MENU_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_MENU_ITEM, HtkMenuItemClass))

struct HtkMenuItem {
	HtkItem item;

	HtkMenu * submenu; /* owned */

	HtkWidget * hbox; /* unowned */
	HtkWidget * label; /* unowned */
	HtkWidget * arrow; /* unowned */
};

struct HtkMenuItemClass {
	HtkItemClass parent_class;

	void (* activate) (HtkMenuItem * mitem);
};

GType htk_menu_item_get_type(void) G_GNUC_CONST;

HtkWidget * htk_menu_item_new(void);
HtkWidget * htk_menu_item_new_with_label(const gchar * label);

void htk_menu_item_activate(HtkMenuItem * mitem);

void htk_menu_item_set_label(HtkMenuItem * mitem, const gchar * label);
const gchar * htk_menu_item_get_label(HtkMenuItem * mitem);

void htk_menu_item_set_submenu(HtkMenuItem * mitem, HtkMenu * submenu);
HtkMenu * htk_menu_item_get_submenu(HtkMenuItem * mitem);

G_END_DECLS

#endif//__HTK_MENU_ITEM_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
