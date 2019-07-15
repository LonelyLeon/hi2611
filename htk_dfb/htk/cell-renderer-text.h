#ifndef __HTK_CELL_RENDERER_TEXT_H__
#define __HTK_CELL_RENDERER_TEXT_H__

#include <glib-object.h>
#include <htk/cell-renderer.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_CELL_RENDERER_TEXT            (htk_cell_renderer_text_get_type ())
#define HTK_CELL_RENDERER_TEXT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CELL_RENDERER_TEXT, HtkCellRendererText))
#define HTK_CELL_RENDERER_TEXT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CELL_RENDERER_TEXT, HtkCellRendererTextClass))
#define HTK_IS_CELL_RENDERER_TEXT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CELL_RENDERER_TEXT))
#define HTK_IS_CELL_RENDERER_TEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CELL_RENDERER_TEXT))
#define HTK_CELL_RENDERER_TEXT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CELL_RENDERER_TEXT, HtkCellRendererTextClass))

struct HtkCellRendererText {
	HtkCellRenderer parent_instance;

	IDirectFBFont * font; /* owned */
	gchar * text;
};

struct HtkCellRendererTextClass {
	HtkCellRendererClass parent_class;
};

GType htk_cell_renderer_text_get_type(void) G_GNUC_CONST;

HtkCellRenderer * htk_cell_renderer_text_new(void);

G_END_DECLS

#endif//__HTK_CELL_RENDERER_TEXT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
