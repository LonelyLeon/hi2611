#ifndef __HDK_COLOR_H__
#define __HDK_COLOR_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HDK_TYPE_COLOR                 (hdk_color_get_type())

extern HdkColor hdk_color_white;
extern HdkColor hdk_color_black;

GType hdk_color_get_type(void) G_GNUC_CONST;
HdkColor * hdk_color_copy(const HdkColor * color);
void hdk_color_free(HdkColor * color);
gboolean hdk_color_parse(const gchar * spec, HdkColor * color);
gchar * hdk_color_to_string(const HdkColor * color);

/* a += b */
void hdk_color_add_color(HdkColor * a, const HdkColor * b);
/* a -= b */
void hdk_color_subtract_color(HdkColor * a, const HdkColor * b);
/* a *= k */
void hdk_color_multiply(HdkColor * a, gdouble k);

G_END_DECLS

#endif//__HDK_COLOR_H__
