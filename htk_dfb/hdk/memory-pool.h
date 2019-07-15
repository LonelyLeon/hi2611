#ifndef __HIMG_MEMORY_POOL_H__
#define __HIMG_MEMORY_POOL_H__

#include <hdk/types.h>

G_BEGIN_DECLS

#define HIMG_TYPE_MEMORY_POOL            (himg_memory_pool_get_type ())
#define HIMG_MEMORY_POOL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), HIMG_TYPE_MEMORY_POOL, HimgMemoryPool))
#define HIMG_MEMORY_POOL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  HIMG_TYPE_MEMORY_POOL, HimgMemoryPoolClass))
#define HIMG_IS_MEMORY_POOL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HIMG_TYPE_MEMORY_POOL))
#define HIMG_IS_MEMORY_POOL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  HIMG_TYPE_MEMORY_POOL))
#define HIMG_MEMORY_POOL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  HIMG_TYPE_MEMORY_POOL, HimgMemoryPoolClass))

typedef struct HimgMemoryPool HimgMemoryPool;
typedef struct HimgMemoryPoolClass HimgMemoryPoolClass;

typedef struct HimgMemoryBlock HimgMemoryBlock;

struct HimgMemoryBlock {
        guint block_size;
        gchar * a_data;
};

struct HimgMemoryPool {
	GObject object;

	GSList * block;

	gint current_phys;
	void * current_addr;
	gint total_size;
};

struct HimgMemoryPoolClass {
	GObjectClass parent_class;
};

GType himg_memory_pool_get_type(void) G_GNUC_CONST;

HimgMemoryPool * himg_memory_pool_new();
HimgMemoryPool * himg_memory_pool_get_default();

void * himg_memory_pool_alloc(HimgMemoryPool * memory_pool, 
		gint stride, gint height, gulong * phys_addr);
void * himg_memory_block_new(gint stride, gint height);

void himg_memory_block_free(void * p);
void himg_memory_pool_free(HimgMemoryPool * memory_pool, void * p_free);
G_END_DECLS

#endif//__HIMG_MEMORY_POOL_H__
