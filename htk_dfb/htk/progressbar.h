#ifndef __HTK_PROGRESS_BAR_H__
#define __HTK_PROGRESS_BAR_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_PROGRESS_BAR            (htk_progress_bar_get_type ())
#define HTK_PROGRESS_BAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_PROGRESS_BAR, HtkProgressBar))
#define HTK_PROGRESS_BAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), HTK_TYPE_PROGRESS_BAR, HtkProgressBarClass))
#define HTK_IS_PROGRESS_BAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_PROGRESS_BAR))
#define HTK_IS_PROGRESS_BAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HTK_TYPE_PROGRESS_BAR))
#define HTK_PROGRESS_BAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), HTK_TYPE_PROGRESS_BAR, HtkProgressBarClass))

struct HtkProgressBar {
	HtkProgress progress;

	IDirectFBFont * font; /* owned */
	HdkPixbuf * act_pix;
};

struct HtkProgressBarClass {
	HtkProgressClass parent_class;
};

GType htk_progress_bar_get_type(void) G_GNUC_CONST;

HtkWidget * htk_progress_bar_new(void);

void htk_progress_bar_set_text(HtkProgressBar * pbar, const char * text);
const gchar * htk_progress_bar_get_text(HtkProgressBar * pbar);
void htk_progress_bar_set_pic(HtkWidget *widget, const char *post_fix);

void htk_progress_bar_set_fraction(HtkProgressBar * pbar, gdouble fraction);
gdouble htk_progress_bar_get_fraction(HtkProgressBar * pbar);

G_END_DECLS

#endif//__HTK_PROGRESS_BAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
