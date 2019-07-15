#ifndef __HTK_NOTEBOOK_H__
#define __HTK_NOTEBOOK_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HTK_TYPE_NOTEBOOK            (htk_notebook_get_type ())
#define HTK_NOTEBOOK(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_NOTEBOOK, HtkNotebook))
#define HTK_NOTEBOOK_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_NOTEBOOK, HtkNotebookClass))
#define HTK_IS_NOTEBOOK(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_NOTEBOOK))
#define HTK_IS_NOTEBOOK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_NOTEBOOK))
#define HTK_NOTEBOOK_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_NOTEBOOK, HtkNotebookClass))

struct HtkNotebookPage {
	HtkWidget * widget;
	gboolean expand;
	gboolean fill;
	HtkRequisition requisition;
	HtkAllocation allocation;
};

struct HtkNotebook {
	HtkContainer container;

	GList * children;
	gint current;
	gint timeout;
	gint direction;

	gint dx;
	gint dy;
	gboolean quick_motion;
	GList * pages;
	gint offset_x;
	gboolean push;
	gint scroll_page;
	gint tag;
};

struct HtkNotebookClass {
	HtkContainerClass parent_class;

	void (* flush_commit) (HtkNotebook * notebook);

};

GType htk_notebook_get_type(void) G_GNUC_CONST;

HtkWidget * htk_notebook_new(void);

HtkWidget * htk_notebook_get_nth_page(HtkNotebook * notebook, gint page_num);
gint htk_notebook_append_page(HtkNotebook * notebook,
		HtkWidget * child, void * tab_label);
void htk_notebook_remove_page(HtkNotebook * notebook, gint page_num);
gint htk_notebook_get_current_page(HtkNotebook * notebook);
gint htk_notebook_get_n_pages(HtkNotebook * notebook);
void htk_notebook_next_page(HtkNotebook * notebook);
void htk_notebook_prev_page(HtkNotebook * notebook);
void htk_notebook_set_current_page(HtkNotebook * notebook, gint page_num);
gint htk_notebook_page_num(HtkNotebook * notebook, HtkWidget * child);

void htk_notebook_scroll_to_current_page(HtkNotebook * notebook, gint page_num, gint direction);
G_END_DECLS

#endif//__HTK_NOTEBOOK_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
