#ifndef __HTK_BIN_H__
#define __HTK_BIN_H__

#include <glib-object.h>
#include <htk/container.h>

G_BEGIN_DECLS

#define HTK_TYPE_BIN            (htk_bin_get_type ())
#define HTK_BIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_BIN, HtkBin))
#define HTK_BIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_BIN, HtkBinClass))
#define HTK_IS_BIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_BIN))
#define HTK_IS_BIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_BIN))
#define HTK_BIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_BIN, HtkBinClass))

struct HtkBin {
	HtkContainer container;

	HtkWidget * child;
};

struct HtkBinClass {
	HtkContainerClass parent_class;
};

GType htk_bin_get_type(void) G_GNUC_CONST;

HtkWidget * htk_bin_get_child(HtkBin * bin);

G_END_DECLS

#endif//__HTK_BIN_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
