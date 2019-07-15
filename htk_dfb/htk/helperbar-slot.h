#ifndef __HTK_HELPERBAR_SOLT_H__
#define __HTK_HELPERBAR_SOLT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_HELPERBAR_SLOT            (htk_helperbar_slot_get_type ())
#define HTK_HELPERBAR_SLOT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HELPERBAR_SLOT, HtkHelperbarSlot))
#define HTK_HELPERBAR_SLOT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HELPERBAR_SLOT, HtkHelperbarSlotClass))
#define HTK_IS_HELPERBAR_SLOT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HELPERBAR_SLOT))
#define HTK_IS_HELPERBAR_SLOT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HELPERBAR_SLOT))
#define HTK_HELPERBAR_SLOT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HELPERBAR_SLOT, HtkHelperbarSlotClass))

struct HtkHelperbarSlot {
	GObject object;

	/* internal */
	HtkHelperbar * hbar; /* unowned */

	/* internal */
	GList * contexts; /* List<unowned Context> */
};

struct HtkHelperbarSlotClass {
	GObjectClass parent_class;
};

GType htk_helperbar_slot_get_type(void) G_GNUC_CONST;

/* internal */
HtkHelperbarSlot * htk_helperbar_slot_new(HtkHelperbar * hbar);

/* internal */
void htk_helperbar_slot_changed(HtkHelperbarSlot * slot);

void htk_helperbar_slot_active(HtkHelperbarSlot * slot);
void htk_helperbar_slot_deactive(HtkHelperbarSlot * slot);

/* internal */
HtkHelperbarContext * htk_helperbar_slot_get_current_context(
		HtkHelperbarSlot * slot);

G_END_DECLS

#endif//__HTK_HELPERBAR_SOLT_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
