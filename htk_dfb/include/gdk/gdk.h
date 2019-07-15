#ifndef __HTK_GDK_H__
#define __HTK_GDK_H__

#include <htk/htk.h>

G_BEGIN_DECLS

/* common.vala */
typedef HdkColorspace GdkColorspace;
#define GDK_COLORSPACE_RGB HDK_COLORSPACE_RGB
typedef HdkRgbDither GdkRgbDither;
#define GDK_RGB_DITHER_NONE   HDK_RGB_DITHER_NONE
#define GDK_RGB_DITHER_NORMAL HDK_RGB_DITHER_NORMAL
#define GDK_RGB_DITHER_MAX    HDK_RGB_DITHER_MAX
typedef HdkEventType GdkEventType;
#define GDK_NOTHING        HDK_NOTHING
#define GDK_KEY_PRESS      HDK_KEY_PRESS
#define GDK_KEY_RELEASE    HDK_KEY_RELEASE
#define GDK_FOCUS_CHANGE   HDK_FOCUS_CHANGE
#define GDK_BUTTON_PRESS   HDK_BUTTON_PRESS
#define GDK_2BUTTON_PRESS  HDK_2BUTTON_PRESS
#define GDK_3BUTTON_PRESS  HDK_3BUTTON_PRESS
#define GDK_BUTTON_RELEASE HDK_BUTTON_RELEASE

/* hdk/key.vala */
#define GDK_space             HDK_space
#define GDK_0                 HDK_0
#define GDK_1                 HDK_1
#define GDK_2                 HDK_2
#define GDK_3                 HDK_3
#define GDK_4                 HDK_4
#define GDK_5                 HDK_5
#define GDK_6                 HDK_6
#define GDK_7                 HDK_7
#define GDK_8                 HDK_8
#define GDK_9                 HDK_9
#define GDK_BackSpace         HDK_BackSpace
#define GDK_Return            HDK_Return
#define GDK_Escape            HDK_Escape
#define GDK_F1                HDK_F1
#define GDK_F2                HDK_F2
#define GDK_F3                HDK_F3
#define GDK_F4                HDK_F4
#define GDK_F5                HDK_F5
#define GDK_F6                HDK_F6
#define GDK_F7                HDK_F7
#define GDK_Left              HDK_Left
#define GDK_Right             HDK_Right
#define GDK_Up                HDK_Up
#define GDK_Down              HDK_Down
#define GDK_Menu              HDK_Menu
#define GDK_Home              HDK_Home
#define GDK_Favorites         HDK_Favorites
#define GDK_Media			  HDK_Media
#define GDK_Epg				  HDK_Epg
#define GDK_Back			  HDK_Back

/* common.vala */
typedef HdkColor GdkColor;
typedef HdkEvent GdkEvent;
typedef HdkEventButton GdkEventButton;
typedef HdkEventFocus GdkEventFocus;
typedef HdkEventKey GdkEventKey;
typedef HdkRectangle GdkRectangle;

/* common.vala */
typedef HdkPixbufDestroyNotify GdkPixbufDestroyNotify;

/* hdk/drawable.vala */
typedef HdkDrawable GdkDrawable;

/* hdk/key.vala */
#define gdk_keyval_from_name hdk_keyval_from_name
#define gdk_keyval_name hdk_keyval_name

/* hdk/pixbuf.vala */
typedef HdkPixbuf GdkPixbuf;
#define gdk_pixbuf_get_type hdk_pixbuf_get_type
#define gdk_pixbuf_new hdk_pixbuf_new
#define gdk_pixbuf_new_from_file hdk_pixbuf_new_from_file
#define gdk_pixbuf_new_from_data hdk_pixbuf_new_from_data

/* hdk/screen.vala */
typedef HdkScreen GdkScreen;
#define gdk_screen_get_active_window hdk_screen_get_active_window
#define gdk_screen_get_default hdk_screen_get_default
#define gdk_screen_get_height hdk_screen_get_height
#define gdk_screen_get_toplevel_windows hdk_screen_get_toplevel_windows
#define gdk_screen_get_width hdk_screen_get_width

/* hdk/window.vala */
typedef HdkWindow GdkWindow;
#define gdk_window_copy_area hdk_window_copy_area
#define gdk_window_get_accept_focus hdk_window_get_accept_focus
#define gdk_window_get_geometry hdk_window_get_geometry
#define gdk_window_get_update_area hdk_window_get_update_area
#define gdk_window_hide hdk_window_hide
#define gdk_window_invalidate_rect hdk_window_invalidate_rect
#define gdk_window_is_destroyed hdk_window_is_destroyed
#define gdk_window_is_viewable hdk_window_is_viewable
#define gdk_window_is_viewable hdk_window_is_viewable
#define gdk_window_lower hdk_window_lower
#define gdk_window_move hdk_window_move
#define gdk_window_move_resize hdk_window_move_resize
#define gdk_window_new hdk_window_new
#define gdk_window_raise hdk_window_raise
#define gdk_window_reparent hdk_window_reparent
#define gdk_window_resize hdk_window_resize
#define gdk_window_scroll hdk_window_scroll
#define gdk_window_set_accept_focus hdk_window_set_accept_focus
#define gdk_window_set_accept_focus hdk_window_set_accept_focus
#define gdk_window_show hdk_window_show

G_END_DECLS

#endif//__HTK_GDK_H__
