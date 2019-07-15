#ifndef __HTK_PROGRESS_H__
#define __HTK_PROGRESS_H__

#include <glib-object.h>
#include <htk/scrollbar.h>

G_BEGIN_DECLS

#define HTK_TYPE_PROGRESS            (htk_progress_get_type ())
#define HTK_PROGRESS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_PROGRESS, HtkProgress))
#define HTK_PROGRESS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_PROGRESS, HtkProgressClass))
#define HTK_IS_PROGRESS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_PROGRESS))
#define HTK_IS_PROGRESS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_PROGRESS))
#define HTK_PROGRESS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_PROGRESS, HtkProgressClass))

struct HtkProgress {
	HtkWidget widget;

	gchar * format; /* owned */
	gdouble percentage;

	guint show_text : 1;
};

struct HtkProgressClass {
	HtkWidgetClass parent_class;
};

GType htk_progress_get_type(void) G_GNUC_CONST;

void htk_progress_set_show_text(HtkProgress * progress, gboolean show_text);
void htk_progress_set_format_string(HtkProgress * progress,
		const gchar * format);
void htk_progress_set_percentage(HtkProgress * progress, gdouble percentage);
gdouble htk_progress_get_current_percentage(HtkProgress * progress);

G_END_DECLS

#endif//__HTK_PROGRESS_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
