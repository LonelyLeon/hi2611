#ifndef __HTK_CHECK_BUTTON_H__
#define __HTK_CHECK_BUTTON_H__

#include <glib-object.h>
#include <htk/togglebutton.h>

G_BEGIN_DECLS

#define HTK_TYPE_CHECK_BUTTON            (htk_check_button_get_type ())
#define HTK_CHECK_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CHECK_BUTTON, HtkCheckButton))
#define HTK_CHECK_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CHECK_BUTTON, HtkCheckButtonClass))
#define HTK_IS_CHECK_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CHECK_BUTTON))
#define HTK_IS_CHECK_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CHECK_BUTTON))
#define HTK_CHECK_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CHECK_BUTTON, HtkCheckButtonClass))

struct HtkCheckButton {
	HtkToggleButton togglebutton;
};

struct HtkCheckButtonClass {
	HtkToggleButtonClass parent_class;
};

GType htk_check_button_get_type(void) G_GNUC_CONST;

HtkWidget * htk_check_button_new(void);
HtkWidget * htk_check_button_new_with_label(const gchar * label);

G_END_DECLS

#endif//__HTK_CHECK_BUTTON_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
