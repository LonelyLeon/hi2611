#ifndef __HTK_FILE_CHOOSER_DIALOG_H__
#define __HTK_FILE_CHOOSER_DIALOG_H__

#include <glib-object.h>
#include <htk/filechooser.h>

G_BEGIN_DECLS

#define HTK_TYPE_FILE_CHOOSER_DIALOG            (htk_file_chooser_dialog_get_type ())
#define HTK_FILE_CHOOSER_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_FILE_CHOOSER_DIALOG, HtkFileChooserDialog))
#define HTK_FILE_CHOOSER_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_FILE_CHOOSER_DIALOG, HtkFileChooserDialogClass))
#define HTK_IS_FILE_CHOOSER_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_FILE_CHOOSER_DIALOG))
#define HTK_IS_FILE_CHOOSER_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_FILE_CHOOSER_DIALOG))
#define HTK_FILE_CHOOSER_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_FILE_CHOOSER_DIALOG, HtkFileChooserDialogClass))

struct HtkFileChooserDialog {
	HtkDialog dialog;

	HtkWidget * filechooser;
	HtkWidget * hbar;
	HtkHelperbarSlot * hbslot;
	HtkHelperbarContext * hbcontext;
};

struct HtkFileChooserDialogClass {
	HtkDialogClass parent_class;
};

GType htk_file_chooser_dialog_get_type(void) G_GNUC_CONST;

HtkWidget * htk_file_chooser_dialog_new(void);

G_END_DECLS

#endif//__HTK_FILE_CHOOSER_DIALOG_H__

/* vim: set ts=8 sts=8 sw=8 noet: */

