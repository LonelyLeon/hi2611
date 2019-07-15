#ifndef __HTK_TOOLTIP_H__
#define __HTK_TOOLTIP_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_TOOLTIP            (htk_tooltip_get_type ())
#define HTK_TOOLTIP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_TOOLTIP, HtkTooltip))
#define HTK_TOOLTIP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_TOOLTIP, HtkTooltipClass))
#define HTK_IS_TOOLTIP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_TOOLTIP))
#define HTK_IS_TOOLTIP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_TOOLTIP))
#define HTK_TOOLTIP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_TOOLTIP, HtkTooltipClass))

struct HtkTooltip {
	GObject parent_instance;

	HtkWidget *window;
	HtkWidget *box;
	HtkWidget *image;
	HtkWidget *label;
	HtkWidget *custom_widget;

	HtkWindow *current_window;

	HtkWidget *tooltip_widget;
	HdkWindow *toplevel_window;

	gdouble last_x;
	gdouble last_y;
	HdkWindow * last_window;

	guint timeout_id;
	guint browse_mode_timeout_id;

	HdkRectangle tip_area;

	guint browse_mode_enabled : 1;
	guint keyboard_mode_enabled : 1;
	guint tip_area_set : 1;
	guint custom_was_reset : 1;

};

struct HtkTooltipClass {
	GObjectClass parent_class;
};

GType htk_tooltip_get_type(void) G_GNUC_CONST;

void htk_tooltip_set_markup              (HtkTooltip         *tooltip,
                                          const gchar        *markup);
void htk_tooltip_set_text                (HtkTooltip         *tooltip,
                                          const gchar        *text);
void htk_tooltip_set_icon                (HtkTooltip         *tooltip,
                                          GdkPixbuf          *pixbuf);
//void htk_tooltip_set_icon_from_stock     (HtkTooltip         *tooltip,
  //                                        const gchar        *stock_id,
    //                                      htkIconSize         size);
//void htk_tooltip_set_icon_from_icon_name (HtkTooltip         *tooltip,
//				          const gchar        *icon_name,
//				          htkIconSize         size);
//void htk_tooltip_set_icon_from_gicon     (HtkTooltip         *tooltip,
//					  GIcon              *gicon,
//					  htkIconSize         size);
void htk_tooltip_set_custom	         (HtkTooltip         *tooltip,
                                          HtkWidget          *custom_widget);

void htk_tooltip_set_tip_area            (HtkTooltip         *tooltip,
                                          const HdkRectangle *rect);

void htk_tooltip_trigger_tooltip_query   (HtkTooltip         *tooltip);
HtkTooltip * htk_tooltip_get_default();

void _htk_tooltip_focus_in               (HtkWidget          *widget);
void _htk_tooltip_focus_out              (HtkWidget          *widget);
void _htk_tooltip_toggle_keyboard_mode   (HtkWidget          *widget);
void _htk_tooltip_handle_event           (HdkEvent           *event);
void _htk_tooltip_hide                   (HtkWidget          *widget);

/*extra*/
void htk_tooltip_set_tooltip_widget(HtkTooltip * tooltip, HtkWidget * widget);
G_END_DECLS

#endif//__HTK_TOOLTIP_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
