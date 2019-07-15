
#ifndef __htk_marshal_MARSHAL_H__
#define __htk_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* BOOL:NONE (marshal.list:1) */
extern void htk_marshal_BOOLEAN__VOID (GClosure     *closure,
                                       GValue       *return_value,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint,
                                       gpointer      marshal_data);
#define htk_marshal_BOOL__NONE	htk_marshal_BOOLEAN__VOID

/* BOOL:POINTER (marshal.list:2) */
extern void htk_marshal_BOOLEAN__POINTER (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);
#define htk_marshal_BOOL__POINTER	htk_marshal_BOOLEAN__POINTER

/* NONE:BOXED (marshal.list:3) */
#define htk_marshal_VOID__BOXED	g_cclosure_marshal_VOID__BOXED
#define htk_marshal_NONE__BOXED	htk_marshal_VOID__BOXED

/* NONE:BOXED,BOXED (marshal.list:4) */
extern void htk_marshal_VOID__BOXED_BOXED (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);
#define htk_marshal_NONE__BOXED_BOXED	htk_marshal_VOID__BOXED_BOXED

/* NONE:INT,INT (marshal.list:5) */
extern void htk_marshal_VOID__INT_INT (GClosure     *closure,
                                       GValue       *return_value,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint,
                                       gpointer      marshal_data);
#define htk_marshal_NONE__INT_INT	htk_marshal_VOID__INT_INT

/* NONE:INT,INT,POINTER (marshal.list:6) */
extern void htk_marshal_VOID__INT_INT_POINTER (GClosure     *closure,
                                               GValue       *return_value,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint,
                                               gpointer      marshal_data);
#define htk_marshal_NONE__INT_INT_POINTER	htk_marshal_VOID__INT_INT_POINTER

/* NONE:NONE (marshal.list:7) */
#define htk_marshal_VOID__VOID	g_cclosure_marshal_VOID__VOID
#define htk_marshal_NONE__NONE	htk_marshal_VOID__VOID

/* NONE:STRING (marshal.list:8) */
#define htk_marshal_VOID__STRING	g_cclosure_marshal_VOID__STRING
#define htk_marshal_NONE__STRING	htk_marshal_VOID__STRING

/* NONE:ENUM (marshal.list:9) */
#define htk_marshal_VOID__ENUM	g_cclosure_marshal_VOID__ENUM
#define htk_marshal_NONE__ENUM	htk_marshal_VOID__ENUM

G_END_DECLS

#endif /* __htk_marshal_MARSHAL_H__ */

