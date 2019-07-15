#ifndef __HTK_STYLE_H__
#define __HTK_STYLE_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_STYLE            (htk_style_get_type ())
#define HTK_STYLE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_STYLE, HtkStyle))
#define HTK_STYLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_STYLE, HtkStyleClass))
#define HTK_IS_STYLE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_STYLE))
#define HTK_IS_STYLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_STYLE))
#define HTK_STYLE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_STYLE, HtkStyleClass))

struct HtkStyle {
	GObject object;

	HdkColor fg[5];
	HdkColor bg[5];
	HdkColor light[5];
	HdkColor dark[5];
	HdkColor text[5];

	gint xthickness;
	gint ythickness;

	/* font desc for each size */
	IDirectFBFont * fonts[9]; /* owned */
	/* pointer to font_descs[HTK_FONT_SIZE_MEDIUM] */
	IDirectFBFont * font; /* unowned */
};

struct HtkStyleClass {
	GObjectClass parent_class;

	/* extra. signal */
	void (* modified) (HtkStyle * style);

	void (* paint_flat_box) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkShadowType shadow,
			HdkRectangle * area, HtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);

	void (* paint_focus) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);

	void (* paint_layout) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, gboolean use_text,
			HdkRectangle * area, HtkWidget * widget,
			const gchar * detail, gint x, gint y,
			IDirectFBFont * layout, const gchar * str);

	void (* paint_slider) (HtkStyle * style, HdkWindow * window,
				HtkStateType state, HtkShadowType shadow,
				HdkRectangle * area, HtkWidget * widget,
				const gchar * detail,
				gint x, gint y, gint width, gint height,
				HtkOrientation orientation);

	void (* paint_check) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkShadowType shadow,
			HdkRectangle * area, HtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);

	void (* paint_option) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkShadowType shadow,
			HdkRectangle * area, HtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);

	void (* paint_hline) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, const HdkRectangle * area,
			HtkWidget * widget, const gchar * detail,
			gint x1, gint x2, gint y);

	void (* paint_vline) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, const HdkRectangle * area,
			HtkWidget * widget, const gchar * detail,
			gint y1, gint y2, gint x);

	void (* paint_arrow) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkShadowType shadow,
			const HdkRectangle * area, HtkWidget * widget,
			const gchar * detail, HtkArrowType arrow, gboolean fill,
			gint x, gint y, gint width, gint height);

	void (* paint_shadow) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, HtkShadowType shadow,
			const HdkRectangle * area, HtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);

	void (* paint_spinner) (HtkStyle * style, HdkWindow * window,
			HtkStateType state, const HdkRectangle * area,
			HtkWidget * widget, const gchar * detail, guint step,
			gint x, gint y, gint width, gint height);

	/* extra. see gtk_draw_insertion_cursor(). */
	void (* draw_insertion_cursor) (HtkStyle * style, HtkWidget * widget,
			HdkDrawable * drawable, HdkRectangle * area,
			HdkRectangle * location, gboolean is_primary,
			HtkTextDirection direction, gboolean draw_arrow);

	/* extra. see gdk_draw_pixbuf(). */
	void (* draw_pixbuf) (HtkStyle * style, HdkDrawable * drawable,
			void * gc, HdkPixbuf * pixbuf,
			gint src_x, gint src_y, gint dest_x, gint dest_y,
			gint width, gint height,
			HdkRgbDither dither, gint x_dither, gint y_dither);
};

#define RUN_CLIPPED(surface, update_area, region, func) {\
	int i = 0; \
	for (i = 0 ; i < hdk_region_num_rectangles(update_area); ++i) { \
		DFBRegion reg = region; \
		DFBRegion cli; \
		HdkRectangle that; \
		hdk_region_get_rectangle(update_area, i, &that); \
		cli.x1 = that.x; \
		cli.y1 = that.y; \
		cli.x2 = that.x + that.width; \
		cli.y2 = that.y + that.height; \
		if (reg.x2 < cli.x1 || reg.y2 < cli.y1 || \
				reg.x1 > cli.x2 || reg.y1 > cli.y2) \
		continue; \
		if (reg.x1 < cli.x1)\
		reg.x1 = cli.x1;\
		if (reg.y1 < cli.y1)\
		reg.y1 = cli.y1;\
		if (reg.x2 > cli.x2)\
		reg.x2 = cli.x2;\
		if (reg.y2 > cli.y2)\
		reg.y2 = cli.y2;\
		surface->SetClip (surface, &reg);\
		func;\
	}\
}




GType htk_style_get_type(void) G_GNUC_CONST;

void htk_style_modified(HtkStyle * style);

/* extra */
gboolean htk_style_set_default(GType style_type);
/* extra, unowned */
HtkStyle * htk_style_get_default(void);

HtkIconSet * htk_style_lookup_icon_set(HtkStyle * style,
		const gchar * stock_id);

void htk_style_apply_default_background(HtkStyle * style, HdkWindow * window,
		gboolean set_bg, HtkStateType state, const HdkRectangle * area,
		gint x, gint y, gint width, gint height);

void htk_style_paint_flat_box(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		HdkRectangle * area, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height);

void htk_style_paint_focus(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height);

void htk_style_paint_layout(HtkStyle * style, HdkWindow * window,
		HtkStateType state, gboolean use_text,
		HdkRectangle * area, HtkWidget * widget,
		const gchar * detail, gint x, gint y,
		IDirectFBFont * layout, const gchar * str);

void htk_style_paint_slider(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		HdkRectangle * area, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height,
		HtkOrientation orientation);

void htk_style_paint_check(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		HdkRectangle * area, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height);

void htk_style_paint_option(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		HdkRectangle * area, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height);

void htk_style_paint_hline(HtkStyle * style, HdkWindow * window,
		HtkStateType state, const HdkRectangle * area,
		HtkWidget * widget, const gchar * detail,
		gint x1, gint x2, gint y);

void htk_style_paint_vline(HtkStyle * style, HdkWindow * window,
		HtkStateType state, const HdkRectangle * area,
		HtkWidget * widget, const gchar * detail,
		gint y1, gint y2, gint x);

void htk_style_paint_arrow(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		const HdkRectangle * area, HtkWidget * widget,
		const gchar * detail, HtkArrowType arrow, gboolean fill,
		gint x, gint y, gint width, gint height);

void htk_style_paint_shadow(HtkStyle * style, HdkWindow * window,
		HtkStateType state, HtkShadowType shadow,
		const HdkRectangle * area, HtkWidget * widget,
		const gchar * detail,
		gint x, gint y, gint width, gint height);

void htk_style_paint_spinner(HtkStyle * style, HdkWindow * window,
		HtkStateType state, const HdkRectangle * area,
		HtkWidget * widget, const gchar * detail, guint step,
		gint x, gint y, gint width, gint height);

/* extra. see gtk_draw_insertion_cursor(). */
void htk_style_draw_insertion_cursor(HtkStyle * style, HtkWidget * widget,
		HdkDrawable * drawable, HdkRectangle * area,
		HdkRectangle * location, gboolean is_primary,
		HtkTextDirection direction, gboolean draw_arrow);

/* extra. see gdk_draw_pixbuf(). */
void htk_style_draw_pixbuf(HtkStyle * style, HdkDrawable * drawable,
		void * gc, HdkPixbuf * pixbuf,
		gint src_x, gint src_y, gint dest_x, gint dest_y,
		gint width, gint height,
		HdkRgbDither dither, gint x_dither, gint y_dither);

G_END_DECLS

#endif//__HTK_STYLE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
