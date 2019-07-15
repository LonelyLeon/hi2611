#ifndef __HDK_BACKEND_H__
#define __HDK_BACKEND_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS
void              hdk_backend_init(gint argc, gchar * argv[]);
void              hdk_backend_flush_all(void);


void              hdk_backend_flush_to_dfb(IDirectFB * dfb);

IDirectFBSurface * hdk_backend_load_image(const gchar * filename, gint width, gint height);

IDirectFBFont * hdk_backend_create_dfb_font(HtkStyle * style, HtkFontSize fontsize);

const gchar *     hdk_backend_get_mime_type(const gchar * filename);
const gchar *     hdk_backend_get_magic_type(const gchar * filename);

IDirectFB * hdk_backend_dfb_get_default(void);
IDirectFBSurface * hdk_backend_dfb_create_surface(gint width, gint height, void * data);
void hdk_backend_dfb_set_video_mode(HdkVideoMode mode);

gboolean hdk_backend_fb_keyboard_init(void);
void hdk_disable_input(void);
void hdk_enable_input(void);
G_END_DECLS

#endif//__HDK_BACKEND_H__
