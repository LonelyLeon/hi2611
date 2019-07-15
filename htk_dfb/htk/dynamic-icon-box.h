#ifndef __HTK_DYNAMIC_ICON_BOX_H__
#define __HTK_DYNAMIC_ICON_BOX_H__

#include <glib-object.h>
#include <htk/icon-box.h>

G_BEGIN_DECLS

#define HTK_TYPE_DYNAMIC_ICON_BOX            (htk_dynamic_icon_box_get_type ())
#define HTK_DYNAMIC_ICON_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_DYNAMIC_ICON_BOX, HtkDynamicIconBox))
#define HTK_DYNAMIC_ICON_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_DYNAMIC_ICON_BOX, HtkDynamicIconBoxClass))
#define HTK_IS_DYNAMIC_ICON_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_DYNAMIC_ICON_BOX))
#define HTK_IS_DYNAMIC_ICON_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_DYNAMIC_ICON_BOX))
#define HTK_DYNAMIC_ICON_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_DYNAMIC_ICON_BOX, HtkDynamicIconBoxClass))

struct HtkDynamicIconBox {
	HtkIconBox icon_box;

	gint distance;
	gint offset;
	gboolean extend;
};

struct HtkDynamicIconBoxClass {
	HtkIconBoxClass parent_class;
};

GType htk_dynamic_icon_box_get_type(void) G_GNUC_CONST;

HtkWidget * htk_dynamic_icon_box_new(void);
gboolean htk_dynamic_icon_box_is_extend(HtkDynamicIconBox * d_ibox);
void htk_dynamic_icon_box_set_focus(HtkDynamicIconBox * d_ibox, gint cursor);
G_END_DECLS

#endif//__HTK_DYNAMIC_ICON_BOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
