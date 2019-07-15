#ifndef __HTK_TEXT_ITER_H__
#define __HTK_TEXT_ITER_H__

#include <glib-object.h>

G_BEGIN_DECLS

struct HtkTextIter {
	HtkTextBuffer * buffer;
	gint line;
	gint index;
};

gboolean htk_text_iter_equal(HtkTextIter * lhs, HtkTextIter * rhs);
gboolean htk_text_iter_backward_line(HtkTextIter * iter);
gboolean htk_text_iter_forward_line(HtkTextIter * iter);
gboolean htk_text_iter_backward_char(HtkTextIter * iter);
gboolean htk_text_iter_forward_char(HtkTextIter * iter);

G_END_DECLS

#endif//__HTK_TEXT_ITER_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
