#ifndef __HTK_IM_CONTEXT_H__
#define __HTK_IM_CONTEXT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_IM_CONTEXT            (htk_im_context_get_type ())
#define HTK_IM_CONTEXT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_IM_CONTEXT, HtkIMContext))
#define HTK_IM_CONTEXT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_IM_CONTEXT, HtkIMContextClass))
#define HTK_IS_IM_CONTEXT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_IM_CONTEXT))
#define HTK_IS_IM_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_IM_CONTEXT))
#define HTK_IM_CONTEXT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_IM_CONTEXT, HtkIMContextClass))

struct HtkIMContext {
	GObject object;
};

struct HtkIMContextClass {
	GObjectClass parent_class;

	/* signals */
	void (* commit) (HtkIMContext * context, const gchar * str);
	void (* preedit_start) (HtkIMContext * context);
	void (* preedit_end) (HtkIMContext * context);
	void (* preedit_changed) (HtkIMContext * context);
	void (* retrieve_surrounding) (HtkIMContext * context);
	gboolean (* delete_surrounding) (HtkIMContext * context,
			gint offset, gint n_chars);

	/* virtual functions */

	void (* set_client_window) (HtkIMContext * context, HdkWindow * window);
	void (* get_preedit_string) (HtkIMContext * context,
			gchar ** str, DFBFontAttributes * attrs, gint * cursor_pos);
	gboolean (* filter_keypress) (HtkIMContext * context,
			HdkEventKey * event);
	void (* focus_in) (HtkIMContext * context);
	void (* focus_out) (HtkIMContext * context);
	void (* reset) (HtkIMContext * context);
	void (* set_cursor_location) (HtkIMContext * context,
			const HdkRectangle * area);
	void (* set_use_preedit) (HtkIMContext * context, gboolean use_preedit);
	void (* set_surrounding) (HtkIMContext * context,
			const gchar * text, gint len, gint cursor_index);
	gboolean (* get_surrounding) (HtkIMContext * context,
			gchar ** text, gint * cursor_index);

	/* extra, internal */
	void (* select_name) (HtkIMContext * context, const gchar * name);
};

GType htk_im_context_get_type(void) G_GNUC_CONST;

void htk_im_context_set_client_window(HtkIMContext * context,
		HdkWindow * window);
void htk_im_context_get_preedit_string(HtkIMContext * context,
		gchar ** str, DFBFontAttributes * attrs, gint * cursor_pos);
gboolean htk_im_context_filter_keypress(HtkIMContext * context,
		HdkEventKey * event);
void htk_im_context_focus_in(HtkIMContext * context);
void htk_im_context_focus_out(HtkIMContext * context);
void htk_im_context_reset(HtkIMContext * context);
void htk_im_context_set_cursor_location(HtkIMContext * context,
		const HdkRectangle * area);
void htk_im_context_set_use_preedit(HtkIMContext * context,
		gboolean use_preedit);
void htk_im_context_set_surrounding(HtkIMContext * context,
		const gchar * text, gint len, gint cursor_index);
gboolean htk_im_context_get_surrounding(HtkIMContext * context,
		gchar ** text, gint * cursor_index);

gboolean htk_im_context_delete_surrounding(HtkIMContext * context,
		gint offset, gint n_chars);

/* extra */
void htk_im_context_commit(HtkIMContext * context, const gchar * str);

/* extra, internal */
void htk_im_context_select_name(HtkIMContext * context, const gchar * name);

G_END_DECLS

#endif//__HTK_IM_CONTEXT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
