#ifndef __HDK_WINDOW_H__
#define __HDK_WINDOW_H__

#include <glib-object.h>
#include <directfb.h>
#include <htk/widget.h>

G_BEGIN_DECLS

#define HDK_TYPE_WINDOW            (hdk_window_get_type ())
#define HDK_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HDK_TYPE_WINDOW, HdkWindow))
#define HDK_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HDK_TYPE_WINDOW, HdkWindowClass))
#define HDK_IS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HDK_TYPE_WINDOW))
#define HDK_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HDK_TYPE_WINDOW))
#define HDK_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HDK_TYPE_WINDOW, HdkWindowClass))

struct HdkWindowAttr {
	HtkWidget * widget;

	HdkWindowType type;
	gint x;
	gint y;
	gint width;
	gint height;
};

void hdk_window_attr_init(HdkWindowAttr * attr,
		gint x, gint y, gint width, gint height);

struct HdkWindow {
	HdkDrawable drawable;

	HdkWindow * parent; /* weak ref */
	HtkWidget * widget; /* weak ref */
	HdkRegion * update_area;

	HdkRectangle geometry;
	HdkRectangle viewport;

	gboolean accept_focus;
	gboolean destroyed;
	gboolean viewable;

	GList * children; /* GList<weak HdkWindow *> */

	/* background image */
	HdkPixbuf * bg; /* owned */

	HdkWindowType type;
};

struct HdkWindowClass {
	HdkDrawableClass parent_class;

	gboolean (* scroll_event) (HdkWindow * window, HdkEventScroll * event);
};

GType       hdk_window_get_type(void) G_GNUC_CONST;

HdkWindow * hdk_window_new(HdkWindow * parent,
		HdkWindowAttr * attr, gint attributes_mask);

/* extra, internal */
HdkWindow * hdk_window_new_root(IDirectFBSurface * surface);

HdkRegion * hdk_window_get_update_area(HdkWindow * window);

HtkWidget * hdk_window_get_widget(HdkWindow * window);
void        hdk_window_set_widget(HdkWindow * window, HtkWidget * widget);

gboolean    hdk_window_get_accept_focus(HdkWindow * window);
void        hdk_window_set_accept_focus(HdkWindow * window,
		gboolean accept_focus);

void        hdk_window_get_geometry(HdkWindow * window,
		gint * x, gint * y, gint * width, gint * height, gint * depth);
void        hdk_window_get_viewport(HdkWindow * window, gint * x, gint * y);

gboolean    hdk_window_get_has_focus(HdkWindow * window);
gboolean    hdk_window_is_destroyed(HdkWindow * window);
gboolean    hdk_window_is_viewable(HdkWindow * window);

void        hdk_window_reparent(HdkWindow * window,
		HdkWindow * parent, gint x, gint y);

void        hdk_window_show(HdkWindow * window);
void        hdk_window_hide(HdkWindow * window);
void        hdk_window_move(HdkWindow * window, gint x, gint y);
void        hdk_window_move_resize(HdkWindow * window,
		gint x, gint y, gint width, gint height);
void        hdk_window_resize(HdkWindow * window, gint width, gint height);
void        hdk_window_scroll(HdkWindow * window, gint dx, gint dy);
void        hdk_window_raise(HdkWindow * window);
void        hdk_window_lower(HdkWindow * window);

void        hdk_window_scroll_to_rect(HdkWindow * window, HdkRectangle * area);

void        hdk_window_clear_update_area(HdkWindow * window);

void        hdk_window_copy_area(HdkWindow * window, void * gc, gint x, gint y,
		HdkDrawable * source_drawable, gint source_x, gint source_y,
		gint width, gint height);

void        hdk_window_invalidate_rect(HdkWindow * window,
		HdkRectangle * rect, gboolean invalidate_children);

/* extra, internal */
void hdk_window_add_child(HdkWindow * window, HdkWindow * child);
/* extra, internal */
void hdk_window_remove_child(HdkWindow * window, HdkWindow * child);
/* extra, internal */
HdkWindow * hdk_window_get_active_child(HdkWindow * window);

gboolean    hdk_window_scroll_event(HdkWindow * window, HdkEventScroll * event);
gboolean    hdk_window_key_event(HdkWindow * window, HdkEventKey * event);
gboolean    hdk_window_button_event(HdkWindow * window, HdkEventButton * event);
gboolean    hdk_window_tap_event(HdkWindow * window, HdkEventTap * event);
gboolean    hdk_window_motion_event(HdkWindow * window, HdkEventMotion * event);
gboolean    hdk_window_focus_event(HdkWindow * window, HdkEventFocus * event);
gboolean    hdk_window_focus_in_event(HdkWindow * window);
gboolean    hdk_window_focus_out_event(HdkWindow * window);

void hdk_window_set_back_pixbuf(HdkWindow * window, HdkPixbuf * pixbuf);

G_END_DECLS

#endif//__HDK_WINDOW_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
