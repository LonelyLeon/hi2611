#ifndef __HTK_RADIO_BUTTON_H__
#define __HTK_RADIO_BUTTON_H__

#include <glib-object.h>
#include <htk/togglebutton.h>

G_BEGIN_DECLS

#define HTK_TYPE_RADIO_BUTTON            (htk_radio_button_get_type ())
#define HTK_RADIO_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_RADIO_BUTTON, HtkRadioButton))
#define HTK_RADIO_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_RADIO_BUTTON, HtkRadioButtonClass))
#define HTK_IS_RADIO_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_RADIO_BUTTON))
#define HTK_IS_RADIO_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_RADIO_BUTTON))
#define HTK_RADIO_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_RADIO_BUTTON, HtkRadioButtonClass))

struct HtkRadioButton {
	HtkToggleButton toggle_button;
};

struct HtkRadioButtonClass {
	HtkToggleButtonClass parent_class;
};

GType htk_radio_button_get_type(void) G_GNUC_CONST;

HtkWidget * htk_radio_button_new(void);
HtkWidget * htk_radio_button_new_with_lable(const gchar * label);

G_END_DECLS

#endif//__HTK_RADIO_BUTTON_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
