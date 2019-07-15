#ifndef __HTK_IM_H__
#define __HTK_IM_H__

#include <glib-object.h>

G_BEGIN_DECLS

void htk_im_init(void);
void htk_im_register(const gchar * name, GType type);
HtkIMContext * htk_im_create(const gchar * name);
void htk_im_select_context_in_popup(HtkIMNotify notify, gpointer notify_data);

G_END_DECLS

#endif//__HTK_IM_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
