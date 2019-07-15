#ifndef __HDK_KEY_H__
#define __HDK_KEY_H__

#include <glib-object.h>

G_BEGIN_DECLS

const gchar * hdk_keyval_name(guint keyval);
guint hdk_keyval_from_name(const gchar * keystr);

G_END_DECLS

#endif//__HDK_KEY_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
