#ifndef __HTK_BUTTON_H__
#define __HTK_BUTTON_H__

#include <glib-object.h>
#include <htk/label.h>

G_BEGIN_DECLS

#define HTK_TYPE_BUTTON            (htk_button_get_type ())
#define HTK_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_BUTTON, HtkButton))
#define HTK_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_BUTTON, HtkButtonClass))
#define HTK_IS_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_BUTTON))
#define HTK_IS_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_BUTTON))
#define HTK_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_BUTTON, HtkButtonClass))

struct HtkButton {
	HtkBin bin;

	HtkWidget * label; /* owned */
	HtkWidget * image; /* owned */

	IDirectFBSurface * image_normal;
	IDirectFBSurface * image_active;

	HtkPositionType position;
	
	GList * points;
	guint button_pressed :1;
	gboolean depressed;
};

struct HtkButtonClass {
	HtkBinClass parent_class;

	void (* clicked) (HtkButton * button);

	void (* draw_indicator) (HtkButton * button);
	gint (* get_indicator_size) (HtkButton * button);
};

GType htk_button_get_type(void) G_GNUC_CONST;

HtkWidget * htk_button_new(void);
HtkWidget * htk_button_new_with_label(const gchar * label);

const gchar * htk_button_get_label(HtkButton * button);
void htk_button_set_label(HtkButton * button, const gchar * label);
HtkWidget * htk_button_get_image(HtkButton * button);
void htk_button_set_image(HtkButton * button, HtkWidget * image);
void htk_button_set_image_path(HtkButton * button, HtkStateType type, const gchar * path);
HtkPositionType htk_button_get_image_position(HtkButton * button);
void htk_button_set_image_position(HtkButton * button, HtkPositionType position);

void htk_button_clicked(HtkButton * button);
void htk_button_draw_indicator(HtkButton * button);
gint htk_button_get_indicator_size(HtkButton * button);
void htk_button_add_point(HtkButton * button, int x, int y);
G_END_DECLS

#endif//__HTK_BUTTON_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
