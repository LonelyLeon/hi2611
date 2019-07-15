#ifndef __HTK_SNOOPER_H__
#define __HTK_SNOOPER_H__

#include <glib-object.h>

G_BEGIN_DECLS

guint htk_key_snooper_install(HtkKeySnoopFunc snooper, gpointer data);
void htk_key_snooper_remove(guint snooper_id);

/* extra, internal */
gboolean htk_key_snooper_emit(HtkWidget * grab_widget, HdkEventKey * event);

G_END_DECLS

#endif//__HTK_SNOOPER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
