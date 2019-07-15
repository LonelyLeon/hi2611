#ifndef __HDK_TYPES_H__
#define __HDK_TYPES_H__

#include <glib-object.h>

/***************************************************************************/

#define HDK_0			1
#define HDK_1			2
#define HDK_2			3
#define HDK_3			4
#define HDK_4			5
#define HDK_5			6
#define HDK_6			7
#define HDK_7			8
#define HDK_8			9
#define HDK_9			10
#define HDK_Power		11	
#define HDK_Info		12	
#define HDK_Subtitle		13
#define HDK_Mute		14
#define HDK_Video_prev		15
#define HDK_Video_next		16
#define HDK_Playpause		17
#define HDK_Stop		18
#define HDK_Back		19
#define HDK_Forward		20
#define HDK_Menu		21
#define HDK_Exit		22
#define HDK_Up			23
#define HDK_Down		24
#define HDK_Left		25
#define HDK_Right		26
#define HDK_Return		27
#define HDK_Record		28
#define HDK_Time		29
#define HDK_Epg			30
#define HDK_Tab			31
#define HDK_Media		32
#define HDK_Tv			33
#define HDK_Audio		34
#define HDK_List		35
#define HDK_Red			36
#define HDK_Green		37
#define HDK_Yellow		38
#define HDK_Blue		39
#define HDK_Favorites		40  

#define HDK_Space		41
#define HDK_BackSpace		42
#define HDK_Escape		43
#define HDK_Channel		44
#define HDK_Pause		45
#define HDK_Home		46
#define HDK_Home1		47

#define HDK_Vol_Down		60
#define HDK_Vol_Up		61

#define HDK_F1			101 //red
#define HDK_F2			102 //green
#define HDK_F3			103 //yellow
#define HDK_F4			104 //blue
#define HDK_F5			33 //HDK_Tv
#define HDK_F6			12//HDK_Info	
#define HDK_F7			44 //HDK_Channel	
#define HDK_F13			113
#define HDK_F14			114
#define HDK_F15			115	
#define HDK_Recall		116	

#define HDK_F21			151
#define HDK_F22			152
#define	HDK_F23			153
#define HDK_F24			154
#define HDK_FUp			155
#define HDK_FDown		156
#define HDK_FLeft		157
#define HDK_FRight		158

/***************************************************************************/

typedef struct HdkDrawable      HdkDrawable;
typedef struct HdkDrawableClass HdkDrawableClass;

typedef struct HdkPixbuf      HdkPixbuf;
typedef struct HdkPixbufClass HdkPixbufClass;

typedef struct HdkScreen      HdkScreen;
typedef struct HdkScreenClass HdkScreenClass;

typedef struct HdkWindow       HdkWindow;
typedef struct HdkWindowClass  HdkWindowClass;


/***************************************************************************/

typedef struct HdkRectangle HdkRectangle;

typedef struct HdkRegion HdkRegion;

typedef struct HdkWindowAttr   HdkWindowAttr;

/***************************************************************************/
typedef enum {
	HDK_VIDEOMODE_480I,
	HDK_VIDEOMODE_576I,
	HDK_VIDEOMODE_480P,
	HDK_VIDEOMODE_576P,
	HDK_VIDEOMODE_720P_50,
	HDK_VIDEOMODE_720P_60,
	HDK_VIDEOMODE_1080I_25,
	HDK_VIDEOMODE_1080I_30,
	HDK_VIDEOMODE_1080P_50,
	HDK_VIDEOMODE_1080P_60,
} HdkVideoMode;

typedef enum {
	HDK_COLORSPACE_RGB,
} HdkColorspace;

typedef enum {
	HDK_NOTHING                     = -1,
	HDK_MOTION_NOTIFY		=  3,
	HDK_BUTTON_PRESS                =  4,
	HDK_2BUTTON_PRESS               =  5,
	HDK_3BUTTON_PRESS               =  6,
	HDK_BUTTON_RELEASE              =  7,
	HDK_KEY_PRESS                   =  8,
	HDK_KEY_RELEASE                 =  9,
	HDK_FOCUS_CHANGE                = 12,
	HDK_SCROLL                      = 31,
	HDK_LONG_TAP                    = 128,//not compatible with gtk
} HdkEventType;

typedef enum {
	HDK_OVERLAP_RECTANGLE_IN,
	HDK_OVERLAP_RECTANGLE_OUT,
	HDK_OVERLAP_RECTANGLE_PART,
} HdkOverlapType;

typedef enum {
	HDK_RGB_DITHER_NONE,
	HDK_RGB_DITHER_NORMAL,
	HDK_RGB_DITHER_MAX,
} HdkRgbDither;

/***************************************************************************/

typedef struct {
	/* incompatible with GdkColor */
	guchar red;
	guchar green;
	guchar blue;
	guchar alpha;
} HdkColor;

typedef struct {
	HdkEventType type;
	gint x;
	gint y;
	gint dx;
	gint dy;
	gboolean quick;
	gboolean pos_changed;
} HdkEventMotion;
typedef struct {
	HdkEventType type;
	gint x;
	gint y;
} HdkEventButton;

typedef struct {
	HdkEventType type;

	gboolean in;
} HdkEventFocus;

typedef struct {
	HdkEventType type;

	guint keyval;
} HdkEventKey;

typedef struct {
	HdkEventType type;
} HdkEventScroll;

typedef struct {
	HdkEventType type;
	gint x;
	gint y;
} HdkEventTap;
typedef union {
	HdkEventType type;
	HdkEventMotion motion;
	HdkEventButton button;
	HdkEventFocus focus_change;
	HdkEventKey key;
	HdkEventScroll scroll;
	HdkEventTap sTap;
} HdkEvent;

typedef enum
{
  HDK_WINDOW_ROOT,
  HDK_WINDOW_TOPLEVEL,
  HDK_WINDOW_CHILD,
  HDK_WINDOW_DIALOG,
  HDK_WINDOW_TEMP,
  HDK_WINDOW_FOREIGN,
  HDK_WINDOW_OFFSCREEN,
  HDK_WINDOW_TOOLTIP,
} HdkWindowType;

typedef struct {
	gint x;
	gint y;
} HdkPoint;

/***************************************************************************/

typedef void (* HdkPixbufDestroyNotify) (guchar * pixels, gpointer user_data);
gboolean hdk_event_get_coords (const HdkEvent *event,gdouble *x_win,gdouble *y_win);
/***************************************************************************/

#endif//__HDK_TYPES_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
