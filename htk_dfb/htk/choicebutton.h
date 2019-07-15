#ifndef __HTK_CHOICE_BUTTON_H__
#define __HTK_CHOICE_BUTTON_H__

#include <glib-object.h>
#include <htk/togglebutton.h>

G_BEGIN_DECLS

#define HTK_TYPE_CHOICE_BUTTON            (htk_choice_button_get_type())
#define HTK_CHOICE_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CHOICE_BUTTON, HtkChoiceButton))
#define HTK_CHOICE_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CHOICE_BUTTON, HtkChoiceButtonClass))
#define HTK_IS_CHOICE_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CHOICE_BUTTON))
#define HTK_IS_CHOICE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CHOICE_BUTTON))
#define HTK_CHOICE_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CHOICE_BUTTON, HtkChoiceButtonClass))

struct HtkChoiceButton {
	HtkToggleButton toggle_button;
};

struct HtkChoiceButtonClass {
	HtkToggleButtonClass parent_class;
};

GType htk_choice_button_get_type(void) G_GNUC_CONST;

HtkWidget * htk_choice_button_new(void);
HtkWidget * htk_choice_button_new_with_label(const gchar * label);

G_END_DECLS

#endif//__HTK_CHOICE_BUTTON_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
