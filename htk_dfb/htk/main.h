#ifndef __HTK_MAIN_H__
#define __HTK_MAIN_H__

#include <glib-object.h>

G_BEGIN_DECLS

extern GParamSpecPool * htk_widget_child_property_pool;
extern GParamSpecPool * htk_widget_style_property_pool;

void htk_init(int * argc, char *** argv);
void htk_uninit(void);
void htk_main(void);
void htk_main_quit(void);

guint htk_activity_add(GSourceFunc func, gpointer data);
void htk_activity_remove(guint tag);

G_END_DECLS

#endif//__HTK_MAIN_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
