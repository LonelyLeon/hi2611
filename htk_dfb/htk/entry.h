#ifndef __HTK_ENTRY_H__
#define __HTK_ENTRY_H__

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * entry widget.
 *
 * we use \b position, \b index, and \b offset for different meanings.
 *
 * position is in the unit of characters, so is a logical unit.
 *
 * index is in the unit of bytes, so is used for string operation.
 *
 * offset is in the unit of px, so is used for drawing.
 */

#define HTK_TYPE_ENTRY            (htk_entry_get_type ())
#define HTK_ENTRY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ENTRY, HtkEntry))
#define HTK_ENTRY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ENTRY, HtkEntryClass))
#define HTK_IS_ENTRY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ENTRY))
#define HTK_IS_ENTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ENTRY))
#define HTK_ENTRY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ENTRY, HtkEntryClass))

struct HtkEntry {
	HtkWidget widget;

	GString * text;
	gboolean editable;
	/* cursor position, in characters */
	gint current_pos;
	IDirectFBFont * font;

	/* text length, in characters */
	gint text_length;

	/* display offset, in px */
	gint offset;
	gint extra_x;
	gboolean dirty;
	gboolean drawing; /* if in expose event */
	gboolean use_focus; /* if in expose event */

	HdkRectangle area; /* real area for text */

	HtkIMContext * im_context;
};

struct HtkEntryClass {
	HtkWidgetClass parent_class;

	void (* insert_at_cursor) (HtkEntry * entry, const gchar * text);
	void (* delete_from_cursor) (HtkEntry * entry,
			HtkDeleteType type, gint count);
};

GType htk_entry_get_type(void) G_GNUC_CONST;

HtkWidget * htk_entry_new(void);

void htk_entry_append_text(HtkEntry * entry, const gchar * text);
void htk_entry_prepend_text(HtkEntry * entry, const gchar * text);
void htk_entry_set_position(HtkEntry * entry, gint position);

void          htk_entry_set_text(HtkEntry * entry, const gchar * text);
const gchar * htk_entry_get_text(HtkEntry * entry);
guint         htk_entry_get_text_length(HtkEntry * entry);
IDirectFBFont * htk_entry_get_font(HtkEntry * entry);
void          htk_entry_set_editable(HtkEntry * entry, gboolean editable);
gboolean      htk_entry_get_editable(HtkEntry * entry);

void htk_entry_insert_text(HtkEntry * entry,
		const gchar * text, gint length, gint * position);
void htk_entry_delete_text(HtkEntry * entry, gint start_pos, gint end_pos);
void htk_entry_adjust_offset(HtkEntry * entry);
void htk_entry_im_selected(HtkIMContext * im, gpointer user_data);
gint htk_entry_get_current_pos(HtkEntry * entry);

G_END_DECLS

#endif//__HTK_ENTRY_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
