#ifndef __HTK_CONTAINER_H__
#define __HTK_CONTAINER_H__

#include <glib-object.h>
#include <htk/widget.h>

G_BEGIN_DECLS

#define HTK_TYPE_CONTAINER            (htk_container_get_type ())
#define HTK_CONTAINER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CONTAINER, HtkContainer))
#define HTK_CONTAINER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CONTAINER, HtkContainerClass))
#define HTK_IS_CONTAINER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CONTAINER))
#define HTK_IS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CONTAINER))
#define HTK_CONTAINER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CONTAINER, HtkContainerClass))

#define HTK_CONTAINER_WARN_INVALID_CHILD_PROPERTY_ID(object, property_id, pspec) \
	G_OBJECT_WARN_INVALID_PSPEC((object), "child property id", (property_id), (pspec))

struct HtkContainer {
	HtkWidget widget;

	HtkWidget * focus_child; /* unowned */
};

struct HtkContainerClass {
	HtkWidgetClass parent_class;

	void (* add) (HtkContainer * container, HtkWidget * child);
	void (* remove) (HtkContainer * container, HtkWidget * child);
	void (* forall) (HtkContainer * container, gboolean include_internal,
			HtkCallback callback, gpointer callback_data);

	HtkWidget * (* find_focusable_child) (HtkContainer * container);
	void (* set_focus_child) (HtkContainer * container, HtkWidget * child);
	GList * (* get_children) (HtkContainer * container);

	void (* set_child_property) (HtkContainer * container,
			HtkWidget * child, guint property_id,
			const GValue * value, GParamSpec * pspec);
	void (* get_child_property) (HtkContainer * container,
			HtkWidget * child, guint property_id,
			GValue * value, GParamSpec * pspec);
};

GType htk_container_get_type(void) G_GNUC_CONST;

void htk_container_add(HtkContainer * container, HtkWidget * child);
void htk_container_remove(HtkContainer * container, HtkWidget * child);

void htk_container_foreach(HtkContainer * container,
		HtkCallback callback, gpointer callback_data);
void htk_container_forall(HtkContainer * container,
		HtkCallback callback, gpointer callback_data);
GList * htk_container_get_children(HtkContainer * container);

HtkWidget * htk_container_find_focusable_child(HtkContainer * container);

void htk_container_set_focus_child(HtkContainer * container, HtkWidget * child);
HtkWidget * htk_container_get_focus_child(HtkContainer * container);

void htk_container_child_set_property(HtkContainer * container,
		HtkWidget * child, const gchar * property_name,
		const GValue * value);
void htk_container_child_get_property(HtkContainer * container,
		HtkWidget * child, const gchar * property_name, GValue * value);

GParamSpec * htk_container_class_find_child_property(GObjectClass * cclass,
		const gchar * property_name);
void htk_container_class_install_child_property(HtkContainerClass * cclass,
		guint property_id, GParamSpec * pspec);

G_END_DECLS

#endif//__HTK_CONTAINER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
