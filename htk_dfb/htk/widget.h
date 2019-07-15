#ifndef __HTK_WIDGET_H__
#define __HTK_WIDGET_H__

#include <glib-object.h>
#include <directfb.h>
#include <htk/object.h>

/**
* 
return :
	TRUE   表示回调函数对应的函数不能继续执行 
	FALSE   表示回调函数对应的函数可以继续执行 
  */
typedef gboolean (*HTK_WIDGET_SET_STYLE_CALLBACK)(HtkWidget *widget, gint id, const gchar *name, gpointer data);
typedef gboolean (*HTK_WIDGET_GET_STYLE_CALLBACK)(HtkWidget *widget, gint id, const gchar *name, gpointer data);
typedef void (*HTK_WIDGET_FINALIZE_CALLBACK)(HtkWidget *widget);

G_BEGIN_DECLS

#define HTK_TYPE_WIDGET            (htk_widget_get_type ())
#define HTK_WIDGET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_WIDGET, HtkWidget))
#define HTK_WIDGET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_WIDGET, HtkWidgetClass))
#define HTK_IS_WIDGET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_WIDGET))
#define HTK_IS_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_WIDGET))
#define HTK_WIDGET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_WIDGET, HtkWidgetClass))

#define HTK_WIDGET_WARN_INVALID_STYLE_PROPERTY_ID(widget, property_id, pspec) \
	G_OBJECT_WARN_INVALID_PSPEC((widget), "style property id", (property_id), (pspec))

struct HtkWidgetAuxInfo {
	gint width;
	gint height;
};

struct HtkWidget {
	HtkObject parent_instance;

	HtkStyle * style; /* unowned */
	HtkWidget * parent; /* unowned */
	HdkWindow * window; /* owned (FIXME: unowned for no_window). */

	HtkRequisition requisition;
	HtkAllocation allocation;

	HtkWidgetAuxInfo aux;

	HtkStateType state;

	gboolean toplevel;
	gboolean realized;
	gboolean mapped;
	gboolean visible;
	gboolean active;
	gboolean no_window;
	gboolean has_focus;
	gboolean can_focus;
	gboolean destroyed;
	guint has_tooltip : 1;

		/* extra */
	gboolean no_bg;
	GData * style_properties; /* owned */
	GSList *gestures;
	gboolean use_alpha;

	gboolean sensitive;
};

struct HtkWidgetClass {
	HtkObjectClass parent_class;

	/* virtual functions */

	gboolean (* get_can_focus) (HtkWidget * widget);
	void     (* set_can_focus) (HtkWidget * widget, gboolean can_focus);

	void (* size_request) (HtkWidget * widget, HtkRequisition * requisition);
	void (* size_allocate) (HtkWidget * widget, HtkAllocation * allocation);
	void (* show) (HtkWidget * widget);
	void (* hide) (HtkWidget * widget);
	void (* map) (HtkWidget * widget);
	void (* unmap) (HtkWidget * widget);
	void (* realize) (HtkWidget * widget);
	void (* unrealize) (HtkWidget * widget);
	void (* expose) (HtkWidget * widget);

	void (* grab_focus) (HtkWidget * widget);
	void (* get_focus_rect) (HtkWidget * widget, HdkRectangle * rect);

	gboolean (* child_focus) (HtkWidget * widget,
			HtkDirectionType direction);
	/* for `interface` Scrollable, which could be a ScrolledWindow child. */
	/* this should be place in the class struct. */
	gboolean (* set_scroll_adjustments) (HtkWidget * widget,
			HtkAdjustment * hadjustment,
			HtkAdjustment * vadjustment);

	void (* set_style_property) (HtkWidget * widget, guint property_id,
			const GValue * value, GParamSpec * pspec);
	void (* get_style_property) (HtkWidget * widget, guint property_id,
			GValue * value, GParamSpec * pspec);

	/* signals */

	gboolean (* focus_in_event) (HtkWidget * widget, HdkEventFocus * event);
	gboolean (* focus_out_event) (HtkWidget * widget, HdkEventFocus * event);
	gboolean (* key_press_event) (HtkWidget * widget, HdkEventKey * event);
	gboolean (* key_release_event) (HtkWidget * widget, HdkEventKey * event);
	gboolean (* motion_notify_event) (HtkWidget * widget, HdkEventMotion * event);
	gboolean (* button_press_event) (HtkWidget * widget, HdkEventButton * event);
	gboolean (* button_release_event) (HtkWidget * widget, HdkEventButton * event);
	gboolean (* long_tap_event) (HtkWidget * widget, HdkEventTap * event);
	gboolean (* gesture) (HtkWidget *widget,HtkGestureType * gesture);
};

GType htk_widget_get_type(void) G_GNUC_CONST;

gboolean htk_widget_is_ancestor(HtkWidget * widget, HtkWidget * ancestor);
gboolean htk_widget_is_toplevel(HtkWidget * widget);

gboolean htk_widget_get_has_focus(HtkWidget * widget);
void     htk_widget_set_has_focus(HtkWidget * widget, gboolean has_focus);
gboolean htk_widget_get_can_focus(HtkWidget * widget);
void     htk_widget_set_can_focus(HtkWidget * widget, gboolean can_focus);
gboolean htk_widget_get_realized(HtkWidget * widget);
void     htk_widget_set_realized(HtkWidget * widget, gboolean realized);
gboolean htk_widget_get_mapped(HtkWidget * widget);
void     htk_widget_set_mapped(HtkWidget * widget, gboolean mapped);
gboolean htk_widget_get_visible(HtkWidget * widget);
void     htk_widget_set_visible(HtkWidget * widget, gboolean visible);

void htk_widget_get_allocation(HtkWidget * widget, HtkAllocation * allocation);
void htk_widget_set_allocation(HtkWidget * widget,
		const HtkAllocation * allocation);

HdkWindow * htk_widget_get_window(HtkWidget * widget);
HtkWidget * htk_widget_get_parent(HtkWidget * widget);
void        htk_widget_set_parent(HtkWidget * widget, HtkWidget * parent);
void        htk_widget_unparent(HtkWidget * widget);

HtkTextDirection htk_widget_get_direction(HtkWidget * widget);

void htk_widget_get_size_request(HtkWidget * widget, gint * width, gint * height);
void htk_widget_set_size_request(HtkWidget * widget, gint width, gint height);

HtkWidget * htk_widget_get_toplevel(HtkWidget * widget);
HdkWindow * htk_widget_get_parent_window(HtkWidget * widget);

IDirectFBFont * htk_widget_create_dfb_font(HtkWidget * widget, HtkFontSize fontsize);
IDirectFBFont * htk_widget_get_dfb_font(HtkWidget * widget);
void htk_widget_change_dfb_font(HtkWidget * widget, IDirectFBFont * font);

HdkPixbuf * htk_widget_render_icon(HtkWidget * widget,
		const gchar * stock_id, HtkIconSize size, const gchar * detail);

void htk_widget_queue_resize(HtkWidget * widget);
void htk_widget_queue_draw(HtkWidget * widget);
void htk_widget_queue_draw_area(HtkWidget * widget,
		gint x, gint y, gint width, gint height);

/* extra, internal */
void htk_widget_queue_resize_internal(HtkWidget * widget);

void htk_widget_show_all(HtkWidget * widget);
void htk_widget_hide_all(HtkWidget * widget);

void htk_widget_size_request(HtkWidget * widget, HtkRequisition * requisition);
void htk_widget_size_allocate(HtkWidget * widget, HtkAllocation * allocation);
void htk_widget_show(HtkWidget * widget);
void htk_widget_hide(HtkWidget * widget);
void htk_widget_map(HtkWidget * widget);
void htk_widget_unmap(HtkWidget * widget);
void htk_widget_realize(HtkWidget * widget);
void htk_widget_unrealize(HtkWidget * widget);
/* extra, internal */
void htk_widget_expose(HtkWidget * widget);

void htk_widget_grab_focus(HtkWidget * widget);
void htk_widget_get_focus_rect(HtkWidget * widget, HdkRectangle * rect);
gboolean htk_widget_child_focus(HtkWidget * widget, HtkDirectionType direction);

gboolean htk_widget_set_scroll_adjustments(HtkWidget * widget,
		HtkAdjustment * hadjustment, HtkAdjustment * vadjustment);

/* extra, internal */
gboolean htk_widget_key_press_event(HtkWidget * widget, HdkEventKey * event);
/* extra, internal */
gboolean htk_widget_key_release_event(HtkWidget * widget, HdkEventKey * event);
/* extra, internal */
gboolean htk_widget_button_press_event(HtkWidget * widget, HdkEventButton * event);
/* extra, internal */
gboolean htk_widget_button_release_event(HtkWidget * widget, HdkEventButton * event);

void htk_widget_style_get(HtkWidget * widget, const gchar * name, ...);
void htk_widget_style_get_valist(HtkWidget * widget,
		const gchar * name, va_list var_args);

void htk_widget_style_set(HtkWidget * widget, const gchar * name, ...);
void htk_widget_style_set_valist(HtkWidget * widget,
		const gchar * name, va_list var_args);

void htk_widget_style_get_property(HtkWidget * widget,
		const gchar * property_name, GValue * value);
void htk_widget_style_set_property(HtkWidget * widget,
		const gchar * property_name, const GValue * value);

/* incompatible */
void htk_widget_class_install_style_property(HtkWidgetClass * klass,
		guint property_id, GParamSpec * pspec);
GParamSpec * htk_widget_class_find_style_property(HtkWidgetClass * klass,
		const gchar * property_name);

/* extra */
void htk_widget_modify_window_image(HtkWidget * widget, const gchar * path);
/* extra */
void htk_widget_modify_font_size(HtkWidget * widget, HtkFontSize font_size);

void htk_widget_set_state(HtkWidget * widget, HtkStateType state);

void htk_widget_modify_bg(HtkWidget * widget,
		HtkStateType state, const HdkColor * color);
void htk_widget_modify_fg(HtkWidget * widget,
		HtkStateType state, const HdkColor * color);
void htk_widget_modify_text(HtkWidget * widget,
		HtkStateType state, const HdkColor * color);

HtkWindow * htk_widget_get_tooltip_window(HtkWidget * widget);
void htk_widget_set_child_visible(HtkWidget * widget, gboolean visible);
gboolean htk_widget_motion_notify_event(HtkWidget * widget, HdkEventMotion * event);

void htk_widget_enable_gesture (HtkWidget *widget, HtkGestureType  gesture);
void htk_widget_disable_gesture (HtkWidget *widget, HtkGestureType  gesture);
void htk_widget_set_style_callback_register(HTK_WIDGET_SET_STYLE_CALLBACK cb);
void htk_widget_get_style_callback_register(HTK_WIDGET_GET_STYLE_CALLBACK cb);
void htk_widget_finalize_callback_register(HTK_WIDGET_FINALIZE_CALLBACK cb);

G_END_DECLS

#endif//__HTK_WIDGET_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
