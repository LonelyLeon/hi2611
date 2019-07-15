#ifndef __HTK_TEXT_VIEW_H__
#define __HTK_TEXT_VIEW_H__

#include <glib-object.h>
#include <htk/text-iter.h>
#include <htk/text-buffer.h>

G_BEGIN_DECLS

#define HTK_TYPE_TEXT_VIEW            (htk_text_view_get_type ())
#define HTK_TEXT_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TEXT_VIEW, HtkTextView))
#define HTK_TEXT_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TEXT_VIEW, HtkTextViewClass))
#define HTK_IS_TEXT_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TEXT_VIEW))
#define HTK_IS_TEXT_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TEXT_VIEW))
#define HTK_TEXT_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TEXT_VIEW, HtkTextViewClass))

struct HtkTextView {
	HtkWidget widget;

	HtkTextBuffer * buffer;

	HtkIMContext * im_context;

	HtkAdjustment * hadjustment; /* owned */
	HtkAdjustment * vadjustment; /* owned */

	gboolean editable;
	IDirectFBFont * font;
};

struct HtkTextViewClass {
	HtkWidgetClass parent_class;
};

GType htk_text_view_get_type(void) G_GNUC_CONST;

HtkWidget * htk_text_view_new(void);

HtkTextBuffer * htk_text_view_get_buffer(HtkTextView * textview);
void htk_text_view_set_buffer(HtkTextView * textview, HtkTextBuffer * buffer);
void htk_text_view_set_editable(HtkTextView * textview, gboolean editable);
gboolean htk_text_view_get_editable(HtkTextView * textview);

G_END_DECLS

#endif//__HTK_TEXT_VIEW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
