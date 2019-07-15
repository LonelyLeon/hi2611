#ifndef __HTK_MENU_H__
#define __HTK_MENU_H__

#include <glib-object.h>
#include <htk/menu-shell.h>

G_BEGIN_DECLS

#define HTK_TYPE_MENU            (htk_menu_get_type ())
#define HTK_MENU(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_MENU, HtkMenu))
#define HTK_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_MENU, HtkMenuClass))
#define HTK_IS_MENU(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_MENU))
#define HTK_IS_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_MENU))
#define HTK_MENU_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_MENU, HtkMenuClass))

struct HtkMenu {
	HtkMenuShell mshell;

	HtkWidget * popup_window; /* ref for toplevel, weak ref for sublevel. */
	HtkWidget * notebook; /* weak ref. */

	gboolean popped;

	gchar * title;
};

struct HtkMenuClass {
	HtkMenuShellClass parent_class;
};

GType htk_menu_get_type(void) G_GNUC_CONST;

HtkWidget * htk_menu_new(void);

void htk_menu_popup(HtkMenu * menu,
		HtkWidget * parent_mshell, HtkWidget * parent_mitem,
		HtkMenuPositionFunc func, gpointer func_data,
		guint button, guint32 activate_time);
void htk_menu_popdown(HtkMenu * menu);

void htk_menu_set_title(HtkMenu * menu, const gchar * title);

G_END_DECLS

#endif//__HTK_MENU_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
