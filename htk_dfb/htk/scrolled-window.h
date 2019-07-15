#ifndef __HTK_SCROLLED_WINDOW_H__
#define __HTK_SCROLLED_WINDOW_H__

#include <glib-object.h>
#include <htk/adjustment.h>

G_BEGIN_DECLS

#define HTK_TYPE_SCROLLED_WINDOW            (htk_scrolled_window_get_type ())
#define HTK_SCROLLED_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_SCROLLED_WINDOW, HtkScrolledWindow))
#define HTK_SCROLLED_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_SCROLLED_WINDOW, HtkScrolledWindowClass))
#define HTK_IS_SCROLLED_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_SCROLLED_WINDOW))
#define HTK_IS_SCROLLED_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_SCROLLED_WINDOW))
#define HTK_SCROLLED_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_SCROLLED_WINDOW, HtkScrolledWindowClass))

struct HtkScrolledWindow {
	HtkBin bin;

	HtkAdjustment * hadjustment;
	HtkAdjustment * vadjustment;

	HtkWidget * hscrollbar;
	HtkWidget * vscrollbar;

	HtkPolicyType hpolicy; /* hscrollbar policy */
	HtkPolicyType vpolicy; /* vscrollbar policy */
};

struct HtkScrolledWindowClass {
	HtkBinClass parent_class;

	gboolean (* scroll_child) (HtkScrolledWindow * swin,
			HtkScrollType scroll, gboolean horizontal);
};

GType htk_scrolled_window_get_type(void) G_GNUC_CONST;

HtkWidget * htk_scrolled_window_new(HtkAdjustment * hadjustment,
		HtkAdjustment * vadjustment);

void htk_scrolled_window_add_with_viewport(HtkScrolledWindow * swin,
		HtkWidget * child);

gboolean htk_scrolled_window_scroll_child(HtkScrolledWindow * swin,
		HtkScrollType scroll, gboolean horizontal);

HtkWidget * htk_scrolled_window_get_hscrollbar(HtkScrolledWindow * swin);
HtkWidget * htk_scrolled_window_get_vscrollbar(HtkScrolledWindow * swin);

HtkAdjustment * htk_scrolled_window_get_hadjustment(HtkScrolledWindow * swin);
void            htk_scrolled_window_set_hadjustment(HtkScrolledWindow * swin,
		HtkAdjustment * hadjustment);
HtkAdjustment * htk_scrolled_window_get_vadjustment(HtkScrolledWindow * swin);
void            htk_scrolled_window_set_vadjustment(HtkScrolledWindow * swin,
		HtkAdjustment * vadjustment);

/* we treat AUTOMATIC as ALWAYS */
void htk_scrolled_window_set_policy(HtkScrolledWindow * swin,
		HtkPolicyType hscrollbar_policy,
		HtkPolicyType vscrollbar_policy);

G_END_DECLS

#endif//__HTK_SCROLLED_WINDOW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
