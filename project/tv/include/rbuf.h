#ifndef __HIDRV_RBUF_H__
#define __HIDRV_RBUF_H__

#include <assert.h>

/**
 * ring buffer.
 *
 * rp means the read position, in range [0, size - 1],
 *   the position to be read.
 * wp means the write position, in range [0, size - 1],
 *   the position to be writen.
 *
 * so there is a problem, what is the meaning for (rp == wp).
 *
 * a empty rbuf has (rp == wp), and a full rbuf has (rp == wp), too.
 *
 * we ASSUME (rp == wp) is empty here, so if you get all be buffer written,
 * the length() will be `0' but not `size',
 * and space() will be `size' but not `0'.
 *
 * we do such a stupid assumption because this rbuf is designed to be used
 * for hardware buffer, the rp/wp maybe set by hardware, and not myself,
 * so when you detect that (rp == wp), you will just never know
 * if it is empty or full. some hardware has a special register to identify
 * the space() or length() of the buffer, but some not. so we just keep
 * this rbuf stupid, and what you should do is to always make sure there are
 * at least one byte left, so wp never catch up with rp.
 *
 * we do special check in write(), to make sure you can only write
 * (space() - 1) bytes at most.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#define MIN(x, y)	((x) < (y) ? (x) : (y))

struct hidrv_rbuf_ops;
struct hidrv_rbuf;

struct hidrv_rbuf_ops {
	int (* get_rp) (struct hidrv_rbuf * rbuf);
	int (* get_wp) (struct hidrv_rbuf * rbuf);
	void (* set_rp) (struct hidrv_rbuf * rbuf, int rp);
	void (* set_wp) (struct hidrv_rbuf * rbuf, int wp);
};

typedef struct hidrv_rbuf HidrvRbuf;
struct hidrv_rbuf {
	const void * head;
	int size;

	/* used by default ops. */
	int rp;
	int wp;

	/* ops must be set. if not ops needed, just set to default ops. */
	struct hidrv_rbuf_ops ops;
};

extern struct hidrv_rbuf_ops hidrv_rbuf_default_ops;

static inline void
hidrv_rbuf_init(struct hidrv_rbuf * rbuf, const void * head, int size)
{
	assert(size > 0);

	rbuf->head = head;
	rbuf->size = size;
}

static inline int
hidrv_rbuf_get_rp(struct hidrv_rbuf * rbuf)
{
	return rbuf->ops.get_rp(rbuf);
}

static inline int
hidrv_rbuf_get_wp(struct hidrv_rbuf * rbuf)
{
	return rbuf->ops.get_wp(rbuf);
}

static inline void
hidrv_rbuf_set_rp(struct hidrv_rbuf * rbuf, int rp)
{
	rbuf->ops.set_rp(rbuf, rp);
}

static inline void
hidrv_rbuf_set_wp(struct hidrv_rbuf * rbuf, int wp)
{
	rbuf->ops.set_wp(rbuf, wp);
}


/* return 0 if not empty */
static inline int
hidrv_rbuf_empty(struct hidrv_rbuf * rbuf)
{
	int rp = hidrv_rbuf_get_rp(rbuf);
	int wp = hidrv_rbuf_get_wp(rbuf);

	return rp == wp;
}

/* size for read */
static inline int
hidrv_rbuf_length(struct hidrv_rbuf * rbuf)
{
	int rp = hidrv_rbuf_get_rp(rbuf);
	int wp = hidrv_rbuf_get_wp(rbuf);

	if (wp == rp)
		return 0;
	else if (wp > rp)
		return wp - rp;
	else /* (wp < rp) */
		return rbuf->size - (rp - wp);
}

/* size for write */
static inline int
hidrv_rbuf_space(struct hidrv_rbuf * rbuf)
{
	return rbuf->size - hidrv_rbuf_length(rbuf);
}

int hidrv_rbuf_read(struct hidrv_rbuf * rbuf, void * buf, int len);
int hidrv_rbuf_write(struct hidrv_rbuf * rbuf, void * buf, int len);

#define hidrv_rbuf_skip(rbuf, len) hidrv_rbuf_read(rbuf, NULL, len)

#endif//__HIDRV_RBUF_H__
