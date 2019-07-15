#ifndef __BENCH_H__
#define __BENCH_H__

#include <glib.h>

typedef struct BenchContext BenchContext;
typedef struct BenchConfig  BenchConfig;
typedef struct BenchItem    BenchItem;

struct BenchContext {
	const gchar * name;
	gpointer priv;

	GTimer * timer;

	gboolean (* prepare) (BenchContext * context);
	gboolean (* cleanup) (BenchContext * context);
};

struct BenchConfig {
	gint scale;
	gint loop;

	gpointer data0;
	gpointer data1;
	gpointer data2;
	gpointer data3;
};

struct BenchItem {
	const gchar * name;

	gpointer data0;
	gpointer data1;
	gpointer data2;
	gpointer data3;

	gboolean (* prepare) (BenchContext * context, BenchConfig * config, BenchItem * item);
	gboolean (* run    ) (BenchContext * context, BenchConfig * config, BenchItem * item);
	gboolean (* cleanup) (BenchContext * context, BenchConfig * config, BenchItem * item);
};

void bench(BenchContext * context, BenchConfig * configs, BenchItem * items);

static inline gboolean
bench_context_prepare(BenchContext * context)
{
	return context->prepare ? context->prepare(context) : TRUE;
}

static inline gboolean
bench_context_cleanup(BenchContext * context)
{
	return context->cleanup ? context->cleanup(context) : TRUE;
}

static inline gboolean
bench_item_prepare(BenchContext * context, BenchConfig * config, BenchItem * item)
{
	return item->prepare ? item->prepare(context, config, item) : TRUE;
}

static inline gboolean
bench_item_cleanup(BenchContext * context, BenchConfig * config, BenchItem * item)
{
	return item->cleanup ? item->cleanup(context, config, item) : TRUE;
}

static inline gboolean
bench_item_run(BenchContext * context, BenchConfig * config, BenchItem * item)
{
	return item->run ? item->run(context, config, item) : FALSE;
}

#endif//__BENCH_H__
