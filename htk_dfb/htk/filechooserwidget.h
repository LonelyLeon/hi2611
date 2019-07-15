#ifndef __HTK_FILE_CHOOSER_WIDGET_H__
#define __HTK_FILE_CHOOSER_WIDGET_H__

#include <glib-object.h>
#include <htk/filechooser.h>

G_BEGIN_DECLS

#define HTK_TYPE_FILE_CHOOSER_WIDGET            (htk_file_chooser_widget_get_type ())
#define HTK_FILE_CHOOSER_WIDGET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_FILE_CHOOSER_WIDGET, HtkFileChooserWidget))
#define HTK_FILE_CHOOSER_WIDGET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_FILE_CHOOSER_WIDGET, HtkFileChooserWidgetClass))
#define HTK_IS_FILE_CHOOSER_WIDGET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_FILE_CHOOSER_WIDGET))
#define HTK_IS_FILE_CHOOSER_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_FILE_CHOOSER_WIDGET))
#define HTK_FILE_CHOOSER_WIDGET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_FILE_CHOOSER_WIDGET, HtkFileChooserWidgetClass))

struct HtkFileChooserWidget {
	HtkFileChooser chooser;
};

struct HtkFileChooserWidgetClass {
	HtkFileChooserClass parent_class;
};

GType htk_file_chooser_widget_get_type(void) G_GNUC_CONST;

HtkWidget * htk_file_chooser_widget_new(HtkFileChooserAction action);

G_END_DECLS

#endif//__HTK_FILE_CHOOSER_WIDGET_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
