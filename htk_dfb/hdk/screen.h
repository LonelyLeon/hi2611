#ifndef __HDK_SCREEN_H__
#define __HDK_SCREEN_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HDK_TYPE_SCREEN			(hdk_screen_get_type ())
#define HDK_SCREEN(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), HDK_TYPE_SCREEN, HdkScreen))
#define HDK_SCREEN_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass),  HDK_TYPE_SCREEN, HdkScreenClass))
#define HDK_IS_SCREEN(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), HDK_TYPE_SCREEN))
#define HDK_IS_SCREEN_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass),  HDK_TYPE_SCREEN))
#define HDK_SCREEN_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj),  HDK_TYPE_SCREEN, HdkScreenClass))

struct HdkScreen {
	GObject object;

	HdkWindow * root; /* root window */
};

struct HdkScreenClass {
	GObjectClass parent_class;
};

GType hdk_screen_get_type(void) G_GNUC_CONST;

void hdk_screen_create_default(IDirectFBSurface * surface);
HdkScreen * hdk_screen_get_default(void);
gint hdk_screen_get_width(HdkScreen * screen);
gint hdk_screen_get_height(HdkScreen * screen);
HdkWindow * hdk_screen_get_active_window(HdkScreen * screen);
HdkWindow * hdk_screen_get_root_window(HdkScreen * screen);
GList * hdk_screen_get_toplevel_windows(HdkScreen * screen);

void hdk_screen_add(HdkScreen * screen, HdkWindow * window);
void hdk_screen_remove(HdkScreen * screen, HdkWindow * window);

G_END_DECLS

#endif//__GDK_SCREEN_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
