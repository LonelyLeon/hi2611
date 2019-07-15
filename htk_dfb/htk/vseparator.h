#ifndef __HTK_VSEPARATOR_H__
#define __HTK_VSEPARATOR_H__

#include <glib-object.h>
#include <htk/separator.h>

G_BEGIN_DECLS

#define HTK_TYPE_VSEPARATOR            (htk_vseparator_get_type ())
#define HTK_VSEPARATOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_VSEPARATOR, HtkVSeparator))
#define HTK_VSEPARATOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_VSEPARATOR, HtkVSeparatorClass))
#define HTK_IS_VSEPARATOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_VSEPARATOR))
#define HTK_IS_VSEPARATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_VSEPARATOR))
#define HTK_VSEPARATOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_VSEPARATOR, HtkVSeparatorClass))

struct HtkVSeparator {
	HtkSeparator separator;
};

struct HtkVSeparatorClass {
	HtkSeparatorClass parent_class;
};

GType       htk_vseparator_get_type(void) G_GNUC_CONST;
HtkWidget * htk_vseparator_new(void);

G_END_DECLS

#endif//__HTK_VSEPARATOR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
