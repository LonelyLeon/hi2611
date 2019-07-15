#ifndef __HTK_IMAGE_H__
#define __HTK_IMAGE_H__

#include <glib-object.h>
#include <htk/misc.h>

G_BEGIN_DECLS

#define HTK_TYPE_IMAGE            (htk_image_get_type ())
#define HTK_IMAGE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_IMAGE, HtkImage))
#define HTK_IMAGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_IMAGE, HtkImageClass))
#define HTK_IS_IMAGE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_IMAGE))
#define HTK_IS_IMAGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_IMAGE))
#define HTK_IMAGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_IMAGE, HtkImageClass))

struct HtkImage {
	HtkMisc misc;

	HtkImageType storage_type;
	HtkIconSize icon_size;

	IDirectFBSurface * surface;
	gchar * stock_id;

	HdkPixbuf * pixbuf; /* for HTK_IMAGE_STOCK */
};

struct HtkImageClass {
	HtkMiscClass parent_class;
};

GType htk_image_get_type(void) G_GNUC_CONST;

HtkWidget * htk_image_new(void);
HtkWidget * htk_image_new_from_file(const gchar * filename);
HtkWidget * htk_image_new_from_stock(const gchar * stock_id, HtkIconSize size);

void htk_image_clear(HtkImage * image);

void htk_image_set_from_file(HtkImage * image, const gchar * filename);
void htk_image_set_from_stock(HtkImage * image,
		const gchar * stock_id, HtkIconSize size);
void htk_image_set_from_surface(HtkImage * image, IDirectFBSurface * surface);

G_END_DECLS

#endif//__HTK_IMAGE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
