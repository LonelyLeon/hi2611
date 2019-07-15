#ifndef __HTK_DIALOG_H__
#define __HTK_DIALOG_H__

#include <glib-object.h>
#include <htk/window.h>

G_BEGIN_DECLS

#define HTK_TYPE_DIALOG            (htk_dialog_get_type ())
#define HTK_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_DIALOG, HtkDialog))
#define HTK_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_DIALOG, HtkDialogClass))
#define HTK_IS_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_DIALOG))
#define HTK_IS_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_DIALOG))
#define HTK_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_DIALOG, HtkDialogClass))

struct HtkDialog {
	HtkWindow win;

	HtkResponseType rid;
};

struct HtkDialogClass {
	HtkWindowClass parent_class;
};

GType htk_dialog_get_type(void) G_GNUC_CONST;

HtkWidget * htk_dialog_new(void);

gint htk_dialog_run(HtkDialog * dialog);
void htk_dialog_response(HtkDialog * dialog, gint response_id);

G_END_DECLS

#endif//__HTK_DIALOG_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
