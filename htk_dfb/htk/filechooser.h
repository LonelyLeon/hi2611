#ifndef __HTK_FILE_CHOOSER_H__
#define __HTK_FILE_CHOOSER_H__

#include <glib-object.h>
#include <gio/gio.h>
#include <htk/vbox.h>

G_BEGIN_DECLS

#define HTK_TYPE_FILE_CHOOSER            (htk_file_chooser_get_type ())
#define HTK_FILE_CHOOSER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_FILE_CHOOSER, HtkFileChooser))
#define HTK_FILE_CHOOSER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_FILE_CHOOSER, HtkFileChooserClass))
#define HTK_IS_FILE_CHOOSER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_FILE_CHOOSER))
#define HTK_IS_FILE_CHOOSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_FILE_CHOOSER))
#define HTK_FILE_CHOOSER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_FILE_CHOOSER, HtkFileChooserClass))

struct HtkFileChooser {
	HtkVBox vbox;

	HtkCList * clist;
	HtkFileChooserAction action;
	gchar * current_path;
	guint tag;
	gint idle_row;
	gboolean multiple;
	gboolean simple; /* simple type parsing */
};

struct HtkFileChooserClass {
	HtkVBoxClass parent_class;

	void (* current_folder_changed) (HtkFileChooser * chooser);
};

GType htk_file_chooser_get_type(void) G_GNUC_CONST;

void htk_file_chooser_set_action(HtkFileChooser * chooser,
		HtkFileChooserAction action);
HtkFileChooserAction htk_file_chooser_get_action(HtkFileChooser * chooser);

GFile * htk_file_chooser_get_file(HtkFileChooser * chooser);

void htk_file_chooser_set_select_multiple(HtkFileChooser * chooser,
		gboolean select_multiple);
gboolean htk_file_chooser_get_select_multiple(HtkFileChooser * chooser);

gchar * htk_file_chooser_get_filename(HtkFileChooser * chooser);
GSList * htk_file_chooser_get_filenames(HtkFileChooser * chooser);

gchar * htk_file_chooser_get_uri(HtkFileChooser * chooser);
gboolean htk_file_chooser_set_uri(HtkFileChooser * chooser, const gchar * uri);

void htk_file_chooser_select_filename(HtkFileChooser * chooser,
		const gchar * filename);
void htk_file_chooser_unselect_filename(HtkFileChooser * chooser,
		const gchar * filename);
void htk_file_chooser_select_all(HtkFileChooser * chooser);
void htk_file_chooser_unselect_all(HtkFileChooser * chooser);

G_END_DECLS

#endif//__HTK_FILE_CHOOSER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
