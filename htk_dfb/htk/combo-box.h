#ifndef __HTK_COMBO_BOX_H__
#define __HTK_COMBO_BOX_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_COMBO_BOX            (htk_combo_box_get_type ())
#define HTK_COMBO_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_COMBO_BOX, HtkComboBox))
#define HTK_COMBO_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_COMBO_BOX, HtkComboBoxClass))
#define HTK_IS_COMBO_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_COMBO_BOX))
#define HTK_IS_COMBO_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_COMBO_BOX))
#define HTK_COMBO_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_COMBO_BOX, HtkComboBoxClass))

struct HtkComboBox{
	HtkBin bin;

	GList * list; /* GList<gchar *> */
	HtkMenu * menu; /* owned */
	gboolean should_restore_focus;
	gint active;

	HtkWidget * label; /* unowned */
	HtkWidget * hbox; /* unowned */
};

struct HtkComboBoxClass{
	HtkBinClass parent_class;

	void (* popup) (HtkComboBox * combo_box);
	gboolean (* popdown) (HtkComboBox * combo_box);
	void (* changed) (HtkComboBox * combo_box);

};

GType htk_combo_box_get_type(void) G_GNUC_CONST;

HtkWidget * htk_combo_box_new_text(void);

void htk_combo_box_append_text(HtkComboBox * combo_box, const gchar * text);
void htk_combo_box_insert_text(HtkComboBox * combo_box,
		gint position, const gchar * text);
void htk_combo_box_prepend_text(HtkComboBox * combo_box, const gchar * text);
void htk_combo_box_remove_text(HtkComboBox * combo_box, gint position);
const gchar * htk_combo_box_get_active_text(HtkComboBox * combo_box);
void htk_combo_box_popup(HtkComboBox * combo_box);
void htk_combo_box_popdown(HtkComboBox * combo_box);
void htk_combo_box_set_active(HtkComboBox * combo_box, gint active);
gint htk_combo_box_get_active(HtkComboBox * combo_box);

/*extra*/
void htk_combo_box_clear(HtkComboBox * combo_box);

G_END_DECLS

#endif//__HTK_COMBO_BOX_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
