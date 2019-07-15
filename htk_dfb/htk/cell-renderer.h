#ifndef __HTK_CELL_RENDERER_H__
#define __HTK_CELL_RENDERER_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_CELL_RENDERER            (htk_cell_renderer_get_type ())
#define HTK_CELL_RENDERER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CELL_RENDERER, HtkCellRenderer))
#define HTK_CELL_RENDERER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CELL_RENDERER, HtkCellRendererClass))
#define HTK_IS_CELL_RENDERER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CELL_RENDERER))
#define HTK_IS_CELL_RENDERER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CELL_RENDERER))
#define HTK_CELL_RENDERER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CELL_RENDERER, HtkCellRendererClass))

struct HtkCellRenderer {
	GObject parent_instance;

	gint width;
	gint height;

	gint xpad;
	gint ypad;

	gfloat xalign;
	gfloat yalign;

	HdkColor * cell_background;

	gboolean visible;
	gboolean cell_background_set;
};

struct HtkCellRendererClass {
	GObjectClass parent_class;

	/* virtual functions */

	void (* get_size) (HtkCellRenderer * cell, HtkWidget * widget,
			HdkRectangle * cell_area, gint * x_offset,
			gint * y_offset, gint * width, gint * height);

	void (* render) (HtkCellRenderer * cell, HdkDrawable * window,
			HtkWidget * widget, HdkRectangle * bg_area,
			HdkRectangle * cell_area, HdkRectangle * expose_area,
			HtkCellRendererState state);

	gboolean (* activate) (HtkCellRenderer * cell, HdkEvent * event,
			HtkWidget * widget, const gchar * path,
			HdkRectangle * bg_area, HdkRectangle * cell_area,
			HtkCellRendererState state);
};

GType htk_cell_renderer_get_type(void) G_GNUC_CONST;

void htk_cell_renderer_set_fixed_size(HtkCellRenderer * cell,
		gint width, gint height);
void htk_cell_renderer_get_fixed_size(HtkCellRenderer * cell,
		gint * width, gint * height);

void htk_cell_renderer_set_alignment(HtkCellRenderer * cell,
		gfloat xalign, gfloat yalign);
void htk_cell_renderer_get_alignment(HtkCellRenderer * cell,
		gfloat * xalign, gfloat * yalign);

void htk_cell_renderer_set_padding(HtkCellRenderer * cell,
		gint xpad, gint ypad);
void htk_cell_renderer_get_padding(HtkCellRenderer * cell,
		gint * xpad, gint * ypad);

void htk_cell_renderer_set_visible(HtkCellRenderer * cell, gboolean visible);
gboolean htk_cell_renderer_get_visible(HtkCellRenderer * cell);

void htk_cell_renderer_get_size(HtkCellRenderer * cell,
		HtkWidget * widget, const HdkRectangle * cell_area,
		gint * x_offset, gint * y_offset, gint * width, gint * height);

void htk_cell_renderer_render(HtkCellRenderer * cell,
		HdkDrawable * window, HtkWidget * widget,
		const HdkRectangle * bg_area, const HdkRectangle * cell_area,
		const HdkRectangle * expose_area, HtkCellRendererState flags);

gboolean htk_cell_renderer_activate(HtkCellRenderer * cell,
		HdkEvent * event, HtkWidget * widget, const gchar * path,
		HdkRectangle * bg_area, HdkRectangle * cell_area,
		HtkCellRendererState flags);

G_END_DECLS

#endif//__HTK_CELL_RENDERER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
