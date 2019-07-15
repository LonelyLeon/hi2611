#ifndef __HDK_PIXBUF_H__
#define __HDK_PIXBUF_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HDK_TYPE_PIXBUF			(hdk_pixbuf_get_type ())
#define HDK_PIXBUF(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), HDK_TYPE_PIXBUF, HdkPixbuf))
#define HDK_PIXBUF_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass),  HDK_TYPE_PIXBUF, HdkPixbufClass))
#define HDK_IS_PIXBUF(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), HDK_TYPE_PIXBUF))
#define HDK_IS_PIXBUF_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass),  HDK_TYPE_PIXBUF))
#define HDK_PIXBUF_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj),  HDK_TYPE_PIXBUF, HdkPixbufClass))

struct HdkPixbuf {
	GObject object;

	IDirectFBSurface * surface;

	HdkPixbufDestroyNotify destroy_fn;
	gpointer destroy_fn_data;
};

struct HdkPixbufClass {
	GObjectClass parent_class;
};

HdkPixbuf * hdk_pixbuf_new(HdkColorspace colorspace, gboolean has_alpha,
		gint bits_per_sample, gint width, gint height);
HdkPixbuf * hdk_pixbuf_new_from_data(const guchar * data,
		HdkColorspace colorspace, gboolean has_alpha,
		gint bits_per_sample, gint width, gint height, gint rowstride,
		HdkPixbufDestroyNotify destroy_fn, gpointer destroy_fn_data);
HdkColorspace hdk_pixbuf_get_colorspace(HdkPixbuf * pixbuf);

GType hdk_pixbuf_get_type(void) G_GNUC_CONST;

HdkPixbuf * hdk_pixbuf_new_from_file(const gchar * filename, GError * error);
HdkPixbuf * hdk_pixbuf_new_from_file_rgb(const gchar * filename, gint width, gint height, GError * error);
HdkPixbuf * hdk_pixbuf_new_from_file_stretch(const gchar * filename, gint width, gint height, GError * error);
HdkPixbuf * hdk_pixbuf_new_from_file_auto_stretch(const gchar * filename, gint width, gint height, GError * error);

gint hdk_pixbuf_get_width(HdkPixbuf * pixbuf);
gint hdk_pixbuf_get_height(HdkPixbuf * pixbuf);
gint hdk_pixbuf_get_n_channels(HdkPixbuf * pixbuf);
gint hdk_pixbuf_get_bits_per_sample(HdkPixbuf * pixbuf);
gint hdk_pixbuf_get_rowstride(HdkPixbuf * pixbuf);
gboolean hdk_pixbuf_get_has_alpha(HdkPixbuf * pixbuf);
guchar * hdk_pixbuf_get_pixels(HdkPixbuf * pixbuf);

/* return unowned */
HdkPixbuf * _hdk_pixbuf__fake__(void);

/* return unowned */
IDirectFBSurface * hdk_pixbuf_get_dfb_surface(HdkPixbuf * pixbuf);

G_END_DECLS

#endif//__HDK_PIXBUF_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
