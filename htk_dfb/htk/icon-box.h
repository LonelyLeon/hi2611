#ifndef __HTK_ICON_BOX_H__
#define __HTK_ICON_BOX_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_ICON_BOX            (htk_icon_box_get_type ())
#define HTK_ICON_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ICON_BOX, HtkIconBox))
#define HTK_ICON_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ICON_BOX, HtkIconBoxClass))
#define HTK_IS_ICON_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ICON_BOX))
#define HTK_IS_ICON_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ICON_BOX))
#define HTK_ICON_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ICON_BOX, HtkIconBoxClass))

struct HtkIconBoxChild {
	HdkPixbuf * pixbuf;
	gchar * text;
	gboolean check;
	void * user_data;
};

struct HtkIconBox {
	HtkWidget widget;

	GList * children;
	guint count;
	gint focus;

	gint item_width;
	gint item_height;
	gint rows;
	gint cols;
	gint col_spacing;
	gint row_spacing;

	HtkOrientation orientation;

	gboolean label_visible;

	HtkAdjustment * hadjustment;
	HtkAdjustment * vadjustment;

	IDirectFBFont * font;

	gboolean button_pressed;
	gint pressed_x;
	gint pressed_y;
	gint motion_x;
	gint motion_y;
	gint dx;
	gint dy;
	gboolean quick_motion;
	/*extra*/
	HdkPixbuf * select_pixbuf;
	HdkPixbuf * bg_pixbuf;
	HdkPixbuf * check_pixbuf;
};

struct HtkIconBoxClass {
	HtkWidgetClass parent_class;
};

GType htk_icon_box_get_type(void) G_GNUC_CONST;

HtkWidget * htk_icon_box_new(void);

void htk_icon_box_set_item_width(HtkIconBox * ibox, gint item_width);
gint htk_icon_box_get_item_width(HtkIconBox * ibox);
void htk_icon_box_set_item_height(HtkIconBox * ibox, gint item_height);
gint htk_icon_box_get_item_height(HtkIconBox * ibox);
void htk_icon_box_set_label_visible(HtkIconBox * ibox, gboolean label_visible);
gboolean htk_icon_box_get_label_visible(HtkIconBox * ibox);
void htk_icon_box_set_column_spacing(HtkIconBox * ibox, gint column_spacing);
gint htk_icon_box_get_column_spacing(HtkIconBox * ibox);
void htk_icon_box_set_row_spacing(HtkIconBox * ibox, gint row_spacing);
gint htk_icon_box_get_row_spacing(HtkIconBox * ibox);

void htk_icon_box_set_focus(HtkIconBox * ibox, gint focus);

HtkIconBoxChild * htk_icon_box_get_item(HtkIconBox * ibox, guint num);

void htk_icon_box_clear(HtkIconBox * ibox);
void htk_icon_box_remove(HtkIconBox * ibox, guint index);
//void htk_icon_box_sort(HtkIconBox * ibox, GCompareFunc compare_func);
guint htk_icon_box_insert(HtkIconBox * ibox, gint pos,
		HdkPixbuf * pixbuf, const gchar * text, gpointer user_data);
guint htk_icon_box_prepend(HtkIconBox * ibox,
		HdkPixbuf * pixbuf, const gchar * text, gpointer user_data);
guint htk_icon_box_append(HtkIconBox * ibox,
		HdkPixbuf * pixbuf, const gchar * text, gpointer user_data);
//guint htk_icon_box_insert_sorted(HtkIconBox * ibox,
//		HdkPixbuf * pixbuf, gchar * text, void * user_data,
//		GCompareFunc compare_func);

void htk_icon_box_set_select_pixbuf(HtkIconBox * ibox, HdkPixbuf * pixbuf);
void htk_icon_box_set_bg_pixbuf(HtkIconBox * ibox, HdkPixbuf * pixbuf);
void htk_icon_box_set_check(HtkIconBox * ibox, gint index, gboolean check);
void htk_icon_box_set_check_pixbuf(HtkIconBox * ibox, HdkPixbuf * pixbuf);
G_END_DECLS

#endif//__HTK_ICON_BOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
