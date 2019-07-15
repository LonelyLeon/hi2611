#ifndef __HDK_REGION_H__
#define __HDK_REGION_H__

#include <glib-object.h>
#include <directfb.h>
#include <pixman.h>

G_BEGIN_DECLS

struct HdkRegion {
	pixman_region32_t rgn;
};

HdkRegion * hdk_region_new(void);
HdkRegion * hdk_region_copy(const HdkRegion * region);
void hdk_region_destroy(HdkRegion * region);
HdkRegion * hdk_region_rectangle(const HdkRectangle * rect);

void hdk_region_get_clipbox(const HdkRegion * region, HdkRectangle * rect);
/* extra */
gint hdk_region_num_rectangles(const HdkRegion * region);
/* extra */
void hdk_region_get_rectangle(const HdkRegion * region,
		gint nth, HdkRectangle * rect);
/* extra, internal */
void hdk_region_intersect_with_rect(HdkRegion * region,
		const HdkRectangle * rect);
void hdk_region_union_with_rect(HdkRegion * region,
		const HdkRectangle * rect);
/* extra, internal */
void hdk_region_subtract_with_rect(HdkRegion * region,
		const HdkRectangle * rect);
HdkOverlapType hdk_region_rect_in(const HdkRegion * region,
		const HdkRectangle * rect);
void hdk_region_do_clip_on_dfb(HdkRegion * region, IDirectFBSurface * surface);

DFBRegion * hdk_rectangle_to_region(DFBRectangle * rect);

G_END_DECLS

#endif//__HDK_REGION_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
