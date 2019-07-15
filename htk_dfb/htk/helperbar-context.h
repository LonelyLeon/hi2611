#ifndef __HTK_HELPERBAR_CONTEXT_H__
#define __HTK_HELPERBAR_CONTEXT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_HELPERBAR_CONTEXT            (htk_helperbar_context_get_type ())
#define HTK_HELPERBAR_CONTEXT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HELPERBAR_CONTEXT, HtkHelperbarContext))
#define HTK_HELPERBAR_CONTEXT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HELPERBAR_CONTEXT, HtkHelperbarContextClass))
#define HTK_IS_HELPERBAR_CONTEXT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HELPERBAR_CONTEXT))
#define HTK_IS_HELPERBAR_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HELPERBAR_CONTEXT))
#define HTK_HELPERBAR_CONTEXT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HELPERBAR_CONTEXT, HtkHelperbarContextClass))

struct HtkHelperbarContext {
	GObject object;

	/* internal */
	HtkHelperbarSlot * slot; /* unowned */

	/* internal */
	gchar * text[4];
	gchar * images[4];
	gchar * bg_images[4];
	/* internal */
	HtkHelperbarEvent callback;
	gpointer callback_data;
};

struct HtkHelperbarContextClass {
	GObjectClass parent_class;
};

GType htk_helperbar_context_get_type(void) G_GNUC_CONST;

/* internal */
HtkHelperbarContext * htk_helperbar_context_new(HtkHelperbarSlot * slot);

/* internal */
void htk_helperbar_context_changed(HtkHelperbarContext * context);

void htk_helperbar_context_get_labels(HtkHelperbarContext * context,
		const gchar ** red, const gchar ** green,
		const gchar ** yellow, const gchar ** blue);
void htk_helperbar_context_set_labels(HtkHelperbarContext * context,
		const gchar * red, const gchar * green,
		const gchar * yellow, const gchar * blue);

void htk_helperbar_context_set_callback(HtkHelperbarContext * context,
		HtkHelperbarEvent callback, gpointer callback_data);

G_END_DECLS

#endif//__HTK_HELPERBAR_CONTEXT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
