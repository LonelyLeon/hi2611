#ifndef __Hi_HELPER_H__
#define __Hi_HELPER_H__

#ifndef __
#define __ "HTK"
#endif//__

#include <errno.h>
#include <stdio.h>
#include <string.h>
#ifdef ENABLE_USE_HARDWARE_FLUSH
#include <src/usb_card/_time.h>
#endif

/****************************************************************************/
/** helpers */

#ifndef PRINT
#if 1
#define PRINT(x...) fprintf(stderr, x)
#else
#define PRINT(x...)
#endif
#endif

#define MSG(msg...)							\
({									\
	PRINT("\033[32m %s \033[0m %s(): %d: ",__, __func__, __LINE__);			\
	PRINT(msg);							\
})

#define ERR(msg...) MSG(msg)

#define SEE(fmt, val) MSG("%s: " fmt "\n", #val, val)
#define SES(fmt, val...) MSG("(%s): (" fmt ")\n", #val, val)

#define PERROR(msg)							\
({									\
	MSG("%s: %s\n", msg, strerror(errno));				\
})

#define ASSERT_ACTION(x...)
#define ASSERT(x...)\
({\
    if (x) {\
    } else {\
        MSG("assert failed: " #x "\n");\
        ASSERT_ACTION(x);\
    }\
})

#if 0
#define FREE(p)								\
({									\
	if (p) free(p);							\
	(p) = NULL;							\
})
#define CLOSE(fd)							\
({									\
	if (fd != -1) close(fd);					\
	(fd) = -1;							\
})
#define RESIZE(p, size)							\
({									\
	(p) = ((p) == NULL)						\
			? malloc(size)					\
			: realloc((p), (size));				\
})
#define RESIZE_T(p, size)						\
({									\
	RESIZE((p), (size) * sizeof(*(p)));				\
})
/**
 * dup a string in \a src to \a dst,
 * if \a dst is not null, realloc is automatically called
 * \return \a dst
 */
#define STRDUP(/* char * */ dst, /* char * */ src)			\
({									\
	if ((dst) == NULL) (dst) = strdup(src);				\
	else {								\
		int n = strlen(src);					\
		(dst) = (typeof(dst)) realloc((dst), n + 1);		\
		memcpy((dst), (src), n);				\
		((char *)(dst))[n] = 0;					\
	}								\
	(dst);								\
})
#if 1
#define SWAP(a, b)							\
({									\
	typeof(a) t = (a);						\
	(a) = (b);							\
	(b) = t;							\
})
#else
#define SWAP(a, b)							\
({									\
	(a) ^= (b);							\
	(b) ^= (a);							\
	(a) ^= (b);							\
})
#endif
#endif

/****************************************************************************/
/** time stamp */
#include <sys/time.h>

#if 0
static struct timeval __helper_tv_last = { 0, 0 };

#define STAMP()								\
({									\
	struct timeval tv;						\
	gulong count = GetTime();\
	tv.tv_sec = count / 200000;				\
	tv.tv_usec = (count % 200000) * 5;\
	MSG("tv.(sec, usec) = (%ld, %ld)\n", tv.tv_sec, tv.tv_usec);	\
									\
	__helper_tv_last = tv;						\
})
#define STAMP_D()							\
({									\
	struct timeval tv;						\
	gulong count = GetTime();\
	tv.tv_sec = count / 200000;\
	tv.tv_usec = (count % 200000) * 5;\
	time_t sec = tv.tv_sec - __helper_tv_last.tv_sec;		\
	suseconds_t usec = tv.tv_usec - __helper_tv_last.tv_usec;	\
	if (usec < 0) {							\
		sec  -= 1;						\
		usec += 1000 * 1000;					\
	}								\
	MSG("delta: (sec, usec) = (%ld, %ld)\n", sec, usec);		\
									\
	__helper_tv_last = tv;						\
})
#endif

/****************************************************************************/
/** converters */
#include <endian.h>

/** little endian to big endian, for 16 bits \b only */
#define L2B16(x)							\
({									\
	uint16_t y = x;							\
	uint16_t z = (y << 8) | (y >> 8);				\
	z;								\
})
/** big endian to little endian, for 16 bits \b only */
#define B2L16(x) L2B16(x)
/** little endian to big endian, for 32 bits \b only */
#define L2B32(x)							\
({									\
	uint32_t y = x;							\
	uint8_t * p = (uint8_t *) &y;					\
	uint32_t z = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];	\
	z;								\
})
/** big endian to little endian, for 32 bits \b only */
#define B2L32(x) L2B32(x)


#if (__BYTE_ORDER == __BIG_ENDIAN)
#  define L2M16(x) L2B16(x)
#  define M2L16(x) B2L16(x)
#  define B2M16(x) (x)
#  define M2B16(x) (x)
#  define L2M32(x) L2B32(x)
#  define M2L32(x) B2L32(x)
#  define B2M32(x) (x)
#  define M2B32(x) (x)
#elif (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define L2M16(x) (x)
#  define M2L16(x) (x)
#  define B2M16(x) B2L16(x)
#  define M2B16(x) L2B16(x)
#  define L2M32(x) (x)
#  define M2L32(x) (x)
#  define B2M32(x) B2L32(x)
#  define M2B32(x) L2B32(x)
#else
#  error unsupported endian!!!
#endif

/****************************************************************************/
#endif//__Hi_HELPER_H__
