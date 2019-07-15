#ifndef __HTK_RANGE_H__
#define __HTK_RANGE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_RANGE            (htk_range_get_type ())
#define HTK_RANGE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_RANGE, HtkRange))
#define HTK_RANGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_RANGE, HtkRangeClass))
#define HTK_IS_RANGE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_RANGE))
#define HTK_IS_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_RANGE))
#define HTK_RANGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_RANGE, HtkRangeClass))

struct HtkRange {
	HtkWidget widget;

	HtkAdjustment * adjustment;
	HtkOrientation orientation;
};

struct HtkRangeClass {
	HtkWidgetClass parent_class;
};

GType htk_range_get_type(void) G_GNUC_CONST;

void htk_range_set_adjustment(HtkRange * range, HtkAdjustment * adjustment);
HtkAdjustment * htk_range_get_adjustment(HtkRange * range);

G_END_DECLS

#endif//__HTK_RANGE_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
