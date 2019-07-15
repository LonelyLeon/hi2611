#ifndef __HTK_TASK_H__
#define __HTK_TASK_H__

#include <glib-object.h>

/* extra, internal */

G_BEGIN_DECLS

struct HtkTaskManager {
	GList * tasklists; /* List<static TaskList> */
	guint tag;
};

struct HtkTaskList {
	GList * widgets; /* List<unowned Widget> */
	HtkTaskListFunc run;
};

void htk_task_manager_init(HtkTaskManager * manager);
void htk_task_manager_uninit(HtkTaskManager * manager);
void htk_task_manager_flush(HtkTaskManager * manager);
void htk_task_manager_start(HtkTaskManager * manager);
void htk_task_manager_cancel(HtkTaskManager * manager);
void htk_task_manager_register(HtkTaskManager * manager, HtkTaskList * tasklist);

void htk_tasklist_init(HtkTaskList * tasklist, HtkTaskListFunc run);
void htk_tasklist_uninit(HtkTaskList * tasklist);
void htk_tasklist_run(HtkTaskList * tasklist);
void htk_tasklist_add(HtkTaskList * tasklist, HtkWidget * widget);
void htk_tasklist_remove(HtkTaskList * tasklist, HtkWidget * widget);
void htk_tasklist_clear(HtkTaskList * tasklist);
gboolean htk_tasklist_empty(HtkTaskList * tasklist);

void htk_task_init(void);
void htk_task_uninit(void);
void htk_task_flush(void);

void htk_add_resize(HtkWidget * widget);
void htk_add_redraw(HtkWidget * widget);
void htk_remove_resize(HtkWidget * widget);
void htk_remove_redraw(HtkWidget * widget);

G_END_DECLS

#endif//__HTK_TASK_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
