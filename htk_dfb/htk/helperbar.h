#ifndef __HTK_HELPERBAR_H__
#define __HTK_HELPERBAR_H__

#include <glib-object.h>
#include <htk/hbox.h>
#include <htk/helperbar-slot.h>
#include <htk/helperbar-context.h>

G_BEGIN_DECLS

#define HTK_TYPE_HELPERBAR            (htk_helperbar_get_type ())
#define HTK_HELPERBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_HELPERBAR, HtkHelperbar))
#define HTK_HELPERBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_HELPERBAR, HtkHelperbarClass))
#define HTK_IS_HELPERBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_HELPERBAR))
#define HTK_IS_HELPERBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_HELPERBAR))
#define HTK_HELPERBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_HELPERBAR, HtkHelperbarClass))

struct HtkHelperbar {
	HtkHBox hbox;;

	/* internal */
	GList * slots; /* List<unowned Slot> */

	/* internal */
	HtkHelperbarSlot * current_slot;

	/* internal */
	HtkWidget * button[4]; /* unowned Button[] */

	/* internal */
	guint snoop_id;

	/* internal */
	HtkWidget * toplevel_widget;
};

struct HtkHelperbarClass {
	HtkHBoxClass parent_class;
};

GType htk_helperbar_get_type(void) G_GNUC_CONST;

HtkWidget * htk_helperbar_create(HtkWidget * toplevel);
HtkWidget * htk_helperbar_get_default(HtkWidget * toplevel);

void htk_helperbar_changed(HtkHelperbar * hbar);

HtkHelperbarSlot * htk_helperbar_get_current_slot(HtkHelperbar * hbar);
void htk_helperbar_set_current_slot(HtkHelperbar * hbar,
		HtkHelperbarSlot * slot);

HtkHelperbarContext * htk_helperbar_create_context(HtkWidget * toplevel);
HtkHelperbarContext * htk_helperbar_get_current_context(HtkHelperbar * hbar);

G_END_DECLS

#endif//__HTK_HELPERBAR_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
