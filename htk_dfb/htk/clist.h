#ifndef __HTK_CLIST_H__
#define __HTK_CLIST_H__

#include <glib-object.h>
#include <directfb.h>

G_BEGIN_DECLS

#define HTK_TYPE_CLIST            (htk_clist_get_type ())
#define HTK_CLIST(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HTK_TYPE_CLIST, HtkCList))
#define HTK_CLIST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HTK_TYPE_CLIST, HtkCListClass))
#define HTK_IS_CLIST(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HTK_TYPE_CLIST))
#define HTK_IS_CLIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HTK_TYPE_CLIST))
#define HTK_CLIST_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HTK_TYPE_CLIST, HtkCListClass))

struct HtkCListCell {
	HtkCellType type;

	union {
		void * empty;
		gchar * text;
		HdkPixbuf * pixbuf;
		HtkWidget * widget;
		gboolean check;
	} data;

	gint width;
	gint height;

	gint xpad;
	gint ypad;

	gfloat xalign;
	gfloat yalign;

};

struct HtkCListRow {
	HtkCListCell * cell;
	gpointer data;
	HtkStateType state;
};

struct HtkCListColumn {
	gint desired_width;
	gint width;
	gchar * title;
	HdkPixbuf * check_pixbuf;



};

struct HtkCList {
	HtkWidget widget;

	gboolean show_titles;

	HdkRectangle rows_area;

	gint rows;
	gint columns;
	gint focus_row;
	gint row_height;
	gint page_size;
	gint cur_page;
	gint tol_page;

	HtkCListColumn * column; /* HtkCListColumn[] */
	GList * row_list; /* List<CListRow *> */

	HtkAdjustment * hadjustment;
	HtkAdjustment * vadjustment;

	/* special background colors */
	HdkColor * odd_row_color; /* owned */
	HdkColor * even_row_color; /* owned */
	HdkColor * focus_row_color; /* owned */

	gboolean middle_alignment;
	gboolean should_keep_focus;
	gint max_rows;
	gint motion_x;
	gint motion_y;
	/*extra for button press event*/
	gint sel_column;
	IDirectFBFont * font;

	HtkViewport * viewport;

	gint cell_xpad;
	gint cell_ypad;

	gfloat cell_xalign;
	gfloat cell_yalign;
};

struct HtkCListClass {
	HtkWidgetClass parent_class;

	/* FIXME: 'event' in select_row() and unselect_row()
	 *        should have type 'HdkEvent'. */
	void (* select_row) (HtkCList * clist, gint row, gint column, HdkEventKey * event);
	void (* unselect_row) (HtkCList * clist, gint row, gint column, HdkEventKey * event);
};

GType htk_clist_get_type(void) G_GNUC_CONST;

HtkWidget * htk_clist_new(gint columns);

/* extra, internal */
void htk_clist_set_columns(HtkCList * clist, guint columns);

void htk_clist_clear(HtkCList * clist);
void htk_clist_remove(HtkCList * clist, gint row);
gint htk_clist_append(HtkCList * clist, const gchar * text[]);
gint htk_clist_prepend(HtkCList * clist, const gchar * text[]);
gint htk_clist_insert(HtkCList * clist, gint row, const gchar * text[]);

void htk_clist_select_row(HtkCList * clist, gint row, gint column);
void htk_clist_unselect_row(HtkCList * clist, gint row, gint column);

void htk_clist_set_selection_mode(HtkCList * clist, HtkSelectionMode mode);

void htk_clist_column_titles_show(HtkCList * clist);
void htk_clist_column_titles_hide(HtkCList * clist);

gboolean htk_clist_get_pixbuf(HtkCList * clist, gint row, gint column, HdkPixbuf ** pixbuf);
void     htk_clist_set_pixbuf(HtkCList * clist, gint row, gint column, HdkPixbuf * pixbuf);
gboolean htk_clist_get_text(HtkCList * clist, gint row, gint column, const gchar ** text);
void     htk_clist_set_text(HtkCList * clist, gint row, gint column, const gchar * text);
gboolean htk_clist_get_check(HtkCList * clist, gint row, gint column, gboolean * check);
void     htk_clist_set_check(HtkCList * clist, gint row, gint column, gboolean check);
gboolean htk_clist_toggle_check(HtkCList * clist, gint row, gint column);
void     htk_clist_set_column_title(HtkCList * clist, gint column, const gchar * title);
void     htk_clist_set_column_auto_resize(HtkCList * clist, gint column, gboolean auto_resize);
void     htk_clist_set_column_width(HtkCList * clist, gint column, gint width);
void     htk_clist_set_row_height(HtkCList * clist, gint row_height);
void     htk_clist_set_row_data(HtkCList * clist, gint row, void * data);
gpointer htk_clist_get_row_data(HtkCList * clist, gint row);
void	 htk_clist_get_row_rect_externel(HtkCList *clist, gint row, HdkRectangle *rect);
gint	 htk_clist_get_selected_row(HtkCList * clist);
/* extra */

void     htk_clist_set_row_color(HtkCList * clist, const HdkColor * color);
void     htk_clist_set_odd_row_color(HtkCList * clist, const HdkColor * color);
void     htk_clist_set_even_row_color(HtkCList * clist, const HdkColor * color);
void     htk_clist_set_focus_row_color(HtkCList * clist, const HdkColor * color);

void htk_clist_set_column_check_pixbuf(HtkCList * clist, gint column, const gchar * filename);
void	 htk_clist_set_cell_middle_alignment(HtkCList * clist, gboolean middle_alignment);
gboolean htk_clist_get_cell_middle_alignment(HtkCList * clist);

void htk_clist_page_up(HtkCList * clist);
void htk_clist_page_down(HtkCList * clist);
G_END_DECLS

#endif//__HTK_CLIST_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
