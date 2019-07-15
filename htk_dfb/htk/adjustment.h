#ifndef __HTK_ADJUSTMENT_H__
#define __HTK_ADJUSTMENT_H__

#include <glib-object.h>
#include <htk/object.h>

G_BEGIN_DECLS

#define HTK_TYPE_ADJUSTMENT                  (htk_adjustment_get_type ())
#define HTK_ADJUSTMENT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_ADJUSTMENT, HtkAdjustment))
#define HTK_ADJUSTMENT_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_ADJUSTMENT, HtkAdjustmentClass))
#define HTK_IS_ADJUSTMENT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_ADJUSTMENT))
#define HTK_IS_ADJUSTMENT_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_ADJUSTMENT))
#define HTK_ADJUSTMENT_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_ADJUSTMENT, HtkAdjustmentClass))

struct HtkAdjustment {
	HtkObject parent_instance;

	gdouble lower;
	gdouble upper;
	gdouble value;
	gdouble step_increment;
	gdouble page_increment;
	gdouble page_size;
};

struct HtkAdjustmentClass {
	HtkObjectClass parent_class;
};

GType htk_adjustment_get_type(void) G_GNUC_CONST;

HtkObject * htk_adjustment_new(gdouble value, gdouble lower, gdouble upper,
		gdouble step_increment, gdouble page_increment,
		gdouble page_size);

gdouble htk_adjustment_get_value(HtkAdjustment * adjustment);
void    htk_adjustment_set_value(HtkAdjustment * adjustment, gdouble value);
gdouble htk_adjustment_get_lower(HtkAdjustment * adjustment);
void    htk_adjustment_set_lower(HtkAdjustment * adjustment, gdouble lower);
gdouble htk_adjustment_get_upper(HtkAdjustment * adjustment);
void    htk_adjustment_set_upper(HtkAdjustment * adjustment, gdouble upper);
gdouble htk_adjustment_get_step_increment(HtkAdjustment * adjustment);
void    htk_adjustment_set_step_increment(HtkAdjustment * adjustment, gdouble step_increment);
gdouble htk_adjustment_get_page_increment(HtkAdjustment * adjustment);
void    htk_adjustment_set_page_increment(HtkAdjustment * adjustment, gdouble page_increment);
gdouble htk_adjustment_get_page_size(HtkAdjustment * adjustment);
void    htk_adjustment_set_page_size(HtkAdjustment * adjustment, gdouble page_size);

void htk_adjustment_value_changed(HtkAdjustment * adjustment);

G_END_DECLS

#endif//__HTK_ADJUSTMENT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
