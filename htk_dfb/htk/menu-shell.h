#ifndef __HTK_MENU_SHELL_H__
#define __HTK_MENU_SHELL_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_MENU_SHELL            (htk_menu_shell_get_type ())
#define HTK_MENU_SHELL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_MENU_SHELL, HtkMenuShell))
#define HTK_MENU_SHELL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_MENU_SHELL, HtkMenuShellClass))
#define HTK_IS_MENU_SHELL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_MENU_SHELL))
#define HTK_IS_MENU_SHELL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_MENU_SHELL))
#define HTK_MENU_SHELL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_MENU_SHELL, HtkMenuShellClass))

struct HtkMenuShell {
	HtkContainer container;

	HtkWidget * parent_mshell; /* weak ref. */
	HtkWidget * parent_mitem;  /* weak ref. */

	GList * children; /* GList<owned MenuItem> */
	guint active;
};

struct HtkMenuShellClass {
	HtkContainerClass parent_class;

	void (* deactivate) (HtkMenuShell * mshell);
};

GType htk_menu_shell_get_type(void) G_GNUC_CONST;

void htk_menu_shell_insert(HtkMenuShell * mshell,
		HtkWidget * child, gint position);
void htk_menu_shell_append(HtkMenuShell * mshell, HtkWidget * child);
void htk_menu_shell_prepend(HtkMenuShell * mshell, HtkWidget * child);
void htk_menu_shell_activate_item(HtkMenuShell * mshell,
		HtkWidget * mitem, gboolean force_deactivate);
void htk_menu_shell_deactivate(HtkMenuShell * mshell);

G_END_DECLS

#endif//__HTK_MENU_SHELL_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
