#ifndef __HTK_GESTURES_INTERPRETER_H__
#define __HTK_GESTURES_INTERPRETER_H__

//#include <htk/htk.h>
#include <hdk/types.h>
#include <htk/types.h>

G_BEGIN_DECLS

#define HTK_TYPE_GESTURES_INTERPRETER         (htk_gestures_interpreter_get_type ())
#define HTK_GESTURES_INTERPRETER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), HTK_TYPE_GESTURES_INTERPRETER, HtkGesturesInterpreter))
#define HTK_GESTURES_INTERPRETER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST    ((c), HTK_TYPE_GESTURES_INTERPRETER, HtkGesturesInterpreterClass))
#define HTK_IS_GESTURES_INTERPRETER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), HTK_TYPE_GESTURES_INTERPRETER))
#define HTK_IS_GESTURES_INTERPRETER_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE    ((c), HTK_TYPE_GESTURES_INTERPRETER))
#define HTK_GESTURES_INTERPRETER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS  ((o), HTK_TYPE_GESTURES_INTERPRETER, HtkGesturesInterpreterClass))

typedef struct _HtkGesturesInterpreter HtkGesturesInterpreter;
typedef struct _HtkGesturesInterpreterClass HtkGesturesInterpreterClass;

struct _HtkGesturesInterpreter
{
	GObject parent_object;
	gpointer priv;
};

struct _HtkGesturesInterpreterClass
{
	GObjectClass parent_class;
};

GType htk_gestures_interpreter_get_type (void) G_GNUC_CONST;

HtkGesturesInterpreter * _htk_gestures_interpreter_new (void);

gboolean _htk_gestures_interpreter_feed_event (HtkGesturesInterpreter *interpreter,
		HdkEvent               *event);
gboolean _htk_gestures_interpreter_finish     (HtkGesturesInterpreter *interpreter,
		HdkEvent               *event,
		GSList                 *recognized_gestures,
		HtkGestureType         *gesture);

G_END_DECLS

#endif /* __HTK_GESTURES_INTERPRETER_H__ */
