#ifndef __HTK_WORD_BOX_H__
#define __HTK_WORD_BOX_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_WORD_BOX            (htk_word_box_get_type ())
#define HTK_WORD_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_WORD_BOX, HtkWordBox))
#define HTK_WORD_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_WORD_BOX, HtkWordBoxClass))
#define HTK_IS_WORD_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_WORD_BOX))
#define HTK_IS_WORD_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_WORD_BOX))
#define HTK_WORD_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_WORD_BOX, HtkWordBoxClass))

struct HtkWordBox {
	HtkWidget widget;

	GString * buffer;
	GQueue * words; /* Queue<owned WordBoxPos> */

	/* cursor and iter ref to the selected word. */
	gint cursor;
	GList * iter; /* unowned List<unowned WordBoxPos> */

	const gchar * sep;

	DFBFontAttributes * attributes;
	IDirectFBFont * layout;
};

struct HtkWordBoxClass {
	HtkWidgetClass parent_class;

	void (* cursor_moved) (HtkWordBox * wordbox);
};

GType htk_word_box_get_type(void) G_GNUC_CONST;

HtkWidget * htk_word_box_new(void);

void htk_word_box_clear(HtkWordBox * wordbox);
void htk_word_box_append(HtkWordBox * wordbox, const char * word);

gint htk_word_box_count(HtkWordBox * wordbox);

gboolean htk_word_box_get_line_wrap(HtkWordBox * wordbox);
void htk_word_box_set_line_wrap(HtkWordBox * wordbox, gboolean line_wrap);

gchar * htk_word_box_get_text(HtkWordBox * wordbox);
const GList * htk_word_box_get_iter(HtkWordBox * wordbox);
gchar * htk_word_box_iter_get_text(HtkWordBox * wordbox, const GList * iter);

gint htk_word_box_get_cursor(HtkWordBox * wordbox);
void htk_word_box_set_cursor(HtkWordBox * wordbox, gint cursor);
void htk_word_box_set_cursor_by_index(HtkWordBox * wordbox, gint index);

gboolean htk_word_box_prev(HtkWordBox * wordbox);
gboolean htk_word_box_next(HtkWordBox * wordbox);
gboolean htk_word_box_prev_line(HtkWordBox * wordbox);
gboolean htk_word_box_next_line(HtkWordBox * wordbox);

void htk_word_box_cursor_moved(HtkWordBox * wordbox);

G_END_DECLS

#endif//__HTK_WORD_BOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
