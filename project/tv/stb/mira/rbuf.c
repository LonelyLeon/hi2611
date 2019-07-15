#include "rbuf.h"

#ifndef min
#define min(a, b) ( (a) <= (b) ? (a) : (b) )
#endif

static int
hidrv_rbuf_default_ops_get_rp(struct hidrv_rbuf * rbuf)
{
	return rbuf->rp;
}

static int
hidrv_rbuf_default_ops_get_wp(struct hidrv_rbuf * rbuf)
{
	return rbuf->wp;
}

static void
hidrv_rbuf_default_ops_set_rp(struct hidrv_rbuf * rbuf, int rp)
{
	rbuf->rp = rp;
}

static void
hidrv_rbuf_default_ops_set_wp(struct hidrv_rbuf * rbuf, int wp)
{
	rbuf->wp = wp;
}

struct hidrv_rbuf_ops hidrv_rbuf_default_ops = {
	.get_rp = hidrv_rbuf_default_ops_get_rp,
	.get_wp = hidrv_rbuf_default_ops_get_wp,
	.set_rp = hidrv_rbuf_default_ops_set_rp,
	.set_wp = hidrv_rbuf_default_ops_set_wp,
};

int
hidrv_rbuf_read(struct hidrv_rbuf * rbuf, void * buf, int len)
{
	int rp = hidrv_rbuf_get_rp(rbuf);
	int wp = hidrv_rbuf_get_wp(rbuf);

//	assert(rp >= 0 && rp < rbuf->size, -1);
//	assert(wp >= 0 && wp < rbuf->size, -1);

	if (wp == rp) {
		return 0;
	} else if (wp > rp) {
		int n = min(len, wp - rp);

		if (buf != NULL)
			memcpy(buf, rbuf->head + rp, n);

		rp += n;
	//	g_return_val_if_fail(rp < rbuf->size, -1);

		hidrv_rbuf_set_rp(rbuf, rp);

		return n;
	} else /* (wp < rp) */ {
		int n = min(len, rbuf->size - rp);
		int count = n;

		if (buf != NULL)
			memcpy(buf, rbuf->head + rp, n);

		rp += n;
		if (rp == rbuf->size)
			rp = 0;

		len -= n;
		buf += n;

		if (len > 0) {
			//g_return_val_if_fail(rp == 0, -1);

			n = min(len, wp - rp);
			count += n;

			if (buf != NULL)
				memcpy(buf, rbuf->head + rp, n);

			rp += n;
			//g_return_val_if_fail(rp < rbuf->size, -1);
		}

		hidrv_rbuf_set_rp(rbuf, rp);

		return count;
	}
}

int
hidrv_rbuf_write(struct hidrv_rbuf * rbuf, void * buf, int len)
{
	int n;
	int wp = hidrv_rbuf_get_wp(rbuf);

	//g_return_val_if_fail(len >= 0, -1);
	//g_return_val_if_fail(rp >= 0 && rp < rbuf->size, -1);
	//g_return_val_if_fail(wp >= 0 && wp < rbuf->size, -1);

	len = min(len, hidrv_rbuf_space(rbuf) - 1);

	if (len <= 0)
		return 0;

	n = min(len, rbuf->size - wp);
	memcpy((void *) rbuf->head + wp, buf, n);
	buf += n;

	if (n == len) {
		wp += n;

		if (wp == rbuf->size)
			wp = 0;
	} else {
		n = len - n;
		memcpy((void *) rbuf->head, buf, n);
		wp = n;
	}

	hidrv_rbuf_set_wp(rbuf, wp);

	return len;
}
