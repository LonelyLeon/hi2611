#ifndef __HDK_RECTANGLE_H__
#define __HDK_RECTANGLE_H__

#include <glib-object.h>

G_BEGIN_DECLS

struct HdkRectangle {
	gint x;
	gint y;
	gint width;
	gint height;
};

gboolean hdk_rectangle_intersect(const HdkRectangle * rect,
		const HdkRectangle * that, HdkRectangle * dest);
void hdk_rectangle_union(const HdkRectangle * rect,
		const HdkRectangle * that, HdkRectangle * dest);

G_END_DECLS

#endif//__HDK_RECTANGLE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
