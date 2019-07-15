#ifndef __HTK_TOGGLE_BUTTON_H__
#define __HTK_TOGGLE_BUTTON_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_TOGGLE_BUTTON            (htk_toggle_button_get_type ())
#define HTK_TOGGLE_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TOGGLE_BUTTON, HtkToggleButton))
#define HTK_TOGGLE_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TOGGLE_BUTTON, HtkToggleButtonClass))
#define HTK_IS_TOGGLE_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TOGGLE_BUTTON))
#define HTK_IS_TOGGLE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TOGGLE_BUTTON))
#define HTK_TOGGLE_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TOGGLE_BUTTON, HtkToggleButtonClass))

struct HtkToggleButton {
	HtkButton button;

	gboolean active;
};

struct HtkToggleButtonClass {
	HtkButtonClass parent_class;

	gboolean (* get_active) (HtkToggleButton * toggle_button);
	void (* set_active) (HtkToggleButton * toggle_button, gboolean active);
};

GType htk_toggle_button_get_type(void) G_GNUC_CONST;

HtkWidget * htk_toggle_button_new(void);
HtkWidget * htk_toggle_button_new_with_label(const gchar * label);

gboolean htk_toggle_button_get_active(HtkToggleButton * toggle_button);
void     htk_toggle_button_set_active(HtkToggleButton * toggle_button,
		gboolean active);

G_END_DECLS

#endif//__HTK_TOGGLE_BUTTON_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
