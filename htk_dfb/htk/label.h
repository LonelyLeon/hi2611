#ifndef __HTK_LABEL_H__
#define __HTK_LABEL_H__

#include <glib-object.h>
#include <directfb.h>
#include <htk/misc.h>

G_BEGIN_DECLS

#define HTK_TYPE_LABEL            (htk_label_get_type ())
#define HTK_LABEL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_LABEL, HtkLabel))
#define HTK_LABEL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_LABEL, HtkLabelClass))
#define HTK_IS_LABEL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_LABEL))
#define HTK_IS_LABEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_LABEL))
#define HTK_LABEL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_LABEL, HtkLabelClass))

struct HtkLabel {
	HtkMisc misc;

	gchar * text;
	IDirectFBFont * font;

	HtkJustification justify;
	guint activity;
	gboolean single_line;
	gboolean cut_mode;
};

struct HtkLabelClass {
	HtkMiscClass parent_class;
};

GType htk_label_get_type(void) G_GNUC_CONST;

HtkWidget * htk_label_new(const gchar * str);

void htk_label_set_text(HtkLabel * label, const gchar * text);
const gchar * htk_label_get_text(HtkLabel * label);

IDirectFBFont * htk_label_get_font(HtkLabel * label);

void htk_label_set_cut_mode(HtkLabel * label, gboolean mode);

G_END_DECLS

#endif//__HTK_LABEL_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
