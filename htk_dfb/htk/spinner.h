#ifndef __HTK_SPINNER_H__
#define __HTK_SPINNER_H__

#include <glib-object.h>
#include <htk/scrollbar.h>

G_BEGIN_DECLS

#define HTK_TYPE_SPINNER            (htk_spinner_get_type ())
#define HTK_SPINNER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_SPINNER, HtkSpinner))
#define HTK_SPINNER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_SPINNER, HtkSpinnerClass))
#define HTK_IS_SPINNER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_SPINNER))
#define HTK_IS_SPINNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_SPINNER))
#define HTK_SPINNER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_SPINNER, HtkSpinnerClass))

struct HtkSpinner {
	HtkDrawingArea scrollbar;

	gint step;
	guint activity;
};

struct HtkSpinnerClass {
	HtkDrawingAreaClass parent_class;
};

GType htk_spinner_get_type(void) G_GNUC_CONST;

HtkWidget * htk_spinner_new(void);
void htk_spinner_start(HtkSpinner * spinner);
void htk_spinner_stop(HtkSpinner * spinner);

G_END_DECLS

#endif//__HTK_SPINNER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
