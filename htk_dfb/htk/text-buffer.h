#ifndef __HTK_TEXT_BUFFER_H__
#define __HTK_TEXT_BUFFER_H__

#include <glib-object.h>
#include <htk/text-iter.h>

G_BEGIN_DECLS

#define HTK_TYPE_TEXT_BUFFER            (htk_text_buffer_get_type ())
#define HTK_TEXT_BUFFER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TEXT_BUFFER, HtkTextBuffer))
#define HTK_TEXT_BUFFER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TEXT_BUFFER, HtkTextBufferClass))
#define HTK_IS_TEXT_BUFFER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TEXT_BUFFER))
#define HTK_IS_TEXT_BUFFER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TEXT_BUFFER))
#define HTK_TEXT_BUFFER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TEXT_BUFFER, HtkTextBufferClass))

struct HtkTextBuffer {
	GObject object;

	gboolean modified;
	IDirectFBFont * font;
	HtkTextIter cursor;
	gchar * text;
};

struct HtkTextBufferClass {
	GObjectClass parent_class;

	void (* cursor_moved) (HtkTextBuffer * buffer);
	void (* modified_changed) (HtkTextBuffer * buffer);
};

GType htk_text_buffer_get_type(void) G_GNUC_CONST;

HtkTextBuffer * htk_text_buffer_new(void * table);

/* extra. will take ownership of font */
HtkTextBuffer * htk_text_buffer_new_with_font(void * table,
		IDirectFBFont * font);

void htk_text_buffer_get_start_iter(HtkTextBuffer * buffer, HtkTextIter * iter);

void htk_text_buffer_insert_at_cursor(HtkTextBuffer* buffer,
		const gchar * text, gint len);
void htk_text_buffer_backspace(HtkTextBuffer * buffer, HtkTextIter * iter,
		gboolean interactive, gboolean default_editable);
void htk_text_buffer_insert(HtkTextBuffer * buffer,
		HtkTextIter * iter, const gchar * text, gint len);
void htk_text_buffer_delete(HtkTextBuffer * buffer,
		HtkTextIter * start, HtkTextIter * end);

const gchar * htk_text_buffer_get_text(HtkTextBuffer * buffer);
void htk_text_buffer_set_text(HtkTextBuffer * buffer, const gchar * text);

gboolean htk_text_buffer_get_modified(HtkTextBuffer * buffer);
void htk_text_buffer_set_modified(HtkTextBuffer * buffer, gboolean setting);

G_END_DECLS

#endif//__HTK_TEXT_BUFFER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
