#ifndef __HDK_DRAWABLE_H__
#define __HDK_DRAWABLE_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HDK_TYPE_DRAWABLE		(hdk_drawable_get_type ())
#define HDK_DRAWABLE(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), HDK_TYPE_DRAWABLE, HdkDrawable))
#define HDK_DRAWABLE_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass),  HDK_TYPE_DRAWABLE, HdkDrawableClass))
#define HDK_IS_DRAWABLE(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), HDK_TYPE_DRAWABLE))
#define HDK_IS_DRAWABLE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass),  HDK_TYPE_DRAWABLE))
#define HDK_DRAWABLE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj),  HDK_TYPE_DRAWABLE, HdkDrawableClass))

struct HdkDrawable {
	GObject object;

	IDirectFBSurface * surface;
	/*for hardware flush*/
	gulong phys_addr;
};

struct HdkDrawableClass {
	GObjectClass parent_class;
};

GType hdk_drawable_get_type(void) G_GNUC_CONST;

#ifdef ENABLE_USE_HARDWARE_FLUSH
void hdk_drawable_resize_surface(HdkDrawable * drawable,
		gint x, gint y, gint width, gint height);
#else
void hdk_drawable_resize_surface(HdkDrawable * drawable,
		gint width, gint height);
#endif

G_END_DECLS

#endif//__HDK_DRAWABLE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
