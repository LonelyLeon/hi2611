#ifndef __HTK_FIXED_H__
#define __HTK_FIXED_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_FIXED            (htk_fixed_get_type ())
#define HTK_FIXED(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_FIXED, HtkFixed))
#define HTK_FIXED_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_FIXED, HtkFixedClass))
#define HTK_IS_FIXED(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_FIXED))
#define HTK_IS_FIXED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_FIXED))
#define HTK_FIXED_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_FIXED, HtkFixedClass))

struct HtkFixedChild {
	HtkWidget * widget; /* owned */

	gint x;
	gint y;
};

struct HtkFixed {
	HtkContainer container;

	HtkFocusPolicy focus_policy;

	GList * children; /* owned List<FixedChild> */
};

struct HtkFixedClass {
	HtkContainerClass parent_class;
};

GType htk_fixed_get_type(void) G_GNUC_CONST;

HtkWidget * htk_fixed_new(void);

void htk_fixed_put(HtkFixed * fixed, HtkWidget * widget, gint x, gint y);
void htk_fixed_move(HtkFixed * fixed, HtkWidget * widget, gint x, gint y);

/* extra */
HtkFocusPolicy htk_fixed_get_focus_policy(HtkFixed * fixed);
/* extra */
void htk_fixed_set_focus_policy(HtkFixed * fixed, HtkFocusPolicy policy);

G_END_DECLS

#endif//__HTK_FIXED_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
