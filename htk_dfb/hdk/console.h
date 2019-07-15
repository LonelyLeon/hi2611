#ifndef __HDK_CONSOLE_H__
#define __HDK_CONSOLE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#ifdef ENABLE_CONSOLE_INPUT

void hdk_console_init(void);
void hdk_console_uninit(void);

#endif//ENABLE_CONSOLE_INPUT

G_END_DECLS

#endif//__HDK_CONSOLE_H__
