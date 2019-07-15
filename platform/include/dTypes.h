/** @file
* @brief 基本数据类型定义
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 整理代码
*/

#ifndef _D_TYPES_H_
#define _D_TYPES_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDef.h"

/*已经过时的宏, 放空*/
#define D_FUNCPOSTFIT
#define D_FAR

#ifdef D_SYSTEM_WIN32
#define __inline__
#elif !defined(__KERNEL__)
#define __inline__		inline
#endif

/*基本数据类型*/
typedef unsigned char	D_U8; /**< 8位无符号数*/
typedef unsigned short 	D_U16;/**< 16位无符号数*/
typedef unsigned int	D_U32;/**< 32位无符号数*/
typedef char	D_S8;	/**< 8位有符号数*/
typedef short	D_S16;  /**< 16位有符号数*/
typedef int		D_S32;  /**< 32位有符号数*/
typedef float	D_Float;	/**< 32位浮点型*/
typedef double	D_Double;/**< 64位双精度型*/
typedef void*	D_Ptr;		/**< 通用指针*/
typedef int		D_Int;		/**< 整数*/
typedef long int D_Size;	/**< 空间大小*/
typedef D_S32 	D_ID;		/**< ID*/
typedef D_S32	D_Coord;	/**< 坐标*/
typedef D_U32	D_Time;		/**< 时间(秒为单位)*/
typedef D_U32	D_MSec;		/**< 毫秒*/
typedef D_S8	D_Char;		/**< 字符*/

#if defined(D_SYSTEM_WIN32)
typedef unsigned __int64 D_U64; /**< 64位无符号数*/
typedef __int64 D_S64; /**< 64位有符号数*/
#define DEF_S64(_x_)	_x_
#define DEF_U64(_x_)	_x_
#else
typedef unsigned long long D_U64; /**< 64位无符号数*/
typedef long long D_S64; /**< 64位有符号数*/
#define DEF_S64(_x_)	_x_##LL
#define DEF_U64(_x_)	_x_##ULL
#endif

#ifndef NULL
#define NULL (0)	/**< 空指针*/
#endif

/*函数指针类型*/
/** @brief 基本函数类型指针
* @param ptr	数据指针
* @param pd	调用参数
*/
typedef void	(*D_Func)   (D_Ptr ptr, D_Ptr pd) D_FUNCPOSTFIT;

/** @brief 三端比较函数
*
*			当 @a p1 等于 @a p2 时,返回0。
*			当 @a p1 小于 @a p2 时,返回一个负数。
*			当 @a p1 大于 @a p2 时,返回一个正数。
* @param p1	数据1指针
* @param p2	数据2指针
*/
typedef D_S32	(*D_CmpFunc)(D_Ptr p1, D_Ptr p2) D_FUNCPOSTFIT;

/** @brief 布尔型*/
typedef D_Int	D_Bool;
#define D_TRUE	(1)	/**< 逻辑真*/
#define D_FALSE	(0)	/**< 逻辑假*/

/** @brief 设备句柄*/
typedef D_S32	D_Handle;

#define D_INVALID_HANDLE	(-1)	/**< 无效句柄*/

#define D_TIMEOUT_INFINITE  ((D_MSec)-1) /**< 一直等待>*/
#define D_TIMEOUT_IMMEDIATE ((D_MSec)0) /**< 立即返回>*/

/** @brief 函数调用结果*/
typedef D_S32	D_Result;

#define D_OK						(0)	/**< 函数正确执行*/
#define D_ERR						(-1)/**< 函数执行错误*/
#define D_ERR_FULL			(-2)/**< 消息队列满错误*/
#define D_ERR_TIMEOUT		(-3)/**< 超时错误*/
#define D_ERR_NO_SPACE	(-4)/**< 无足够的内存空间*/
#define D_ERR_INVALID_HANDLE	(-5)	/**< 无效的句柄*/
#define D_ERR_INVALID_ARGUMENT	(-6)/**< 参数无效*/
#define D_ERR_EMPTY			(-7)/**< 消息队列中无数据*/
#define D_ERR_OVERFLOW	(-8)/**< 缓冲区溢出*/
#define D_ERR_FAULT			(-9)/**< 错误*/
#define D_ERR_NOT_SUPPORT	(-10)/**< 功能现在不支持*/
#define D_ERR_IO				(-11)	/**< IO错误*/
#define D_ERR_NO_DEV		(-12)	/**< 没有设备*/
#define D_ERR_ALREADY_DONE	(-13)	/**< 已经做过此操作*/

/** @brief 求 @a a 和 @a b 中的最大值*/
#define D_MAX(a,b)	((a)>(b)?(a):(b))

/** @brief 求 @a a 和 @a b 中的最小值*/
#define D_MIN(a,b)	((a)<(b)?(a):(b))

/** @brief 数值是否在范围内*/
#define D_IN_RANGE(a,l,b)	(((a)>=(l))&&((a)<=(b)))

/** @brief 在位操作数组中设置位*/
#define D_SET_MASK(m,n)		((m)[(n)>>3] |= (1<<((n)&7)))

/** @brief 在位操作数组中清除位*/
#define D_CLEAR_MASK(m,n)	((m)[(n)>>3] &= ~(1<<((n)&7)))

/** @brief 在位操作数组中检查一位是否已经设置设置*/
#define D_ISSET_MASK(m,n)	((m)[(n)>>3] & (1<<((n)&7)))

/** @brief 在2bit位操作数组中设置位*/
#define D_SET_2BIT(m,n,v)		{((m)[(n)>>2] &= ~(0x03 <<(((n)&0x03) << 1))); ((m)[(n)>>2] |= (((v)&0x03)<<(((n)&0x03) << 1)));}

/** @brief 在2bit位操作数组中读取位*/
#define D_GET_2BIT(m,n)		(0x03 & ((m)[(n)>>2] >> (((n)&0x03) << 1)))

/** @brief 在4bit位操作数组中设置位*/
#define D_SET_4BIT(m,n,v)		{((m)[(n)>>1] &= ~(0x0f<<(((n)&0x01)<<2))); ((m)[(n)>>1] |= (((v)&0x0f)<<(((n)&0x01)<<2)));}

/** @brief 在4bit位操作数组中读取位*/
#define D_GET_4BIT(m,n)		(0x0f & ((m)[(n)>>1] >> (((n)&0x01) << 2)))

/** @brief 求 @a a 的绝对值*/
#define D_ABS(a)		((a)>(0)?(a):-(a))

/** @brief 宏定义块开始*/
#define D_MACRO_BEGIN		do {

/** @brief 宏定义块结束*/
#define D_MACRO_END			} while(0)

/*字节序变换函数*/
/** @brief 变换一个16位数的字节序*/
#define d_swap16(_d)	((((D_U16)(_d)) << 8) | (((D_U16)(_d)) >> 8))

/** @brief 变换一个32位数的字节序*/
#define d_swap32(_d)\
		((((D_U32)(_d)) << 24) |\
		((((D_U32)(_d)) << 8) & 0x00FF0000) |\
		((((D_U32)(_d)) >> 8) & 0x0000FF00) |\
		(((D_U32)(_d)) >> 24))

#ifdef D_BIG_ENDIAN
#define d_htons(_s)	(_s)
#define d_htonl(_l)	(_l)
#define d_ntohs(_s)	(_s)
#define d_ntohl(_l)	(_l)
#else
#define d_htons(_s)	(D_U16)d_swap16(_s)
#define d_htonl(_l)	(D_U32)d_swap32(_l)
#define d_ntohs(_s)	(D_U16)d_swap16(_s)
#define d_ntohl(_l)	(D_U32)d_swap32(_l)
#endif

#define d_make_u16(_h, _l)  (((D_U16)((D_U8)(_h)) << 8) | (D_U8)(_l))
#define d_make_u32(_d)  ((((D_U32)(_d)[0]) << 24) | (((D_U32)(_d)[1]) << 16) | (((D_U32)(_d)[2]) << 8) | ((D_U32)(_d)[3]))
#define d_make_u64(_d)  ((((D_U64)((_d)[0])) << 56) | (((D_U64)((_d)[1])) << 48) | (((D_U64)((_d)[2])) << 40) | (((D_U64)((_d)[3])) << 32) | (((D_U64)((_d)[4])) << 24) | (((D_U64)((_d)[5])) << 16) | (((D_U64)((_d)[6])) << 8) | ((D_U64)((_d)[7])))

#define D_INVALID_PID_VALUE	(0x1FFF)

#if defined(D_DEVTOOLS_GHS)
#define D_UNUSED_VAR(_v_) (_v_) = (_v_)
#else
#define D_UNUSED_VAR(_v_) ((void)(_v_))
#endif

#ifdef  __cplusplus
}
#endif
#endif
