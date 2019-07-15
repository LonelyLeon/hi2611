#ifndef __HTK_WINDOW_H__
#define __HTK_WINDOW_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_WINDOW            (htk_window_get_type ())
#define HTK_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_WINDOW, HtkWindow))
#define HTK_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_WINDOW, HtkWindowClass))
#define HTK_IS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_WINDOW))
#define HTK_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_WINDOW))
#define HTK_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_WINDOW, HtkWindowClass))

struct HtkWindow {
	HtkBin bin;

	gint x;
	gint y;
	gboolean accept_focus;
	HtkWindowPosition position;
	HtkWindowType type;

	gchar * title;
	gint title_height;
	IDirectFBFont * font;
};

struct HtkWindowClass {
	HtkBinClass parent_class;
};

GType htk_window_get_type(void) G_GNUC_CONST;

HtkWidget * htk_window_new(HtkWindowType type);
void htk_window_set_accept_focus(HtkWindow * window, gboolean accept_focus);
void htk_window_set_position(HtkWindow * window, HtkWindowPosition position);
void htk_window_get_position(HtkWindow * window, gint * x, gint * y);
void htk_window_move(HtkWindow * window, gint x, gint y);
void htk_window_set_title(HtkWindow * window, const gchar * title);
HtkWidget * htk_window_get_focus(HtkWindow * window);

G_END_DECLS

#endif//__HTK_WINDOW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
