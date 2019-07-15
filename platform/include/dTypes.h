/** @file
* @brief �����������Ͷ���
* @author ����
* @date 2005-5-16 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, �������
*/

#ifndef _D_TYPES_H_
#define _D_TYPES_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDef.h"

/*�Ѿ���ʱ�ĺ�, �ſ�*/
#define D_FUNCPOSTFIT
#define D_FAR

#ifdef D_SYSTEM_WIN32
#define __inline__
#elif !defined(__KERNEL__)
#define __inline__		inline
#endif

/*������������*/
typedef unsigned char	D_U8; /**< 8λ�޷�����*/
typedef unsigned short 	D_U16;/**< 16λ�޷�����*/
typedef unsigned int	D_U32;/**< 32λ�޷�����*/
typedef char	D_S8;	/**< 8λ�з�����*/
typedef short	D_S16;  /**< 16λ�з�����*/
typedef int		D_S32;  /**< 32λ�з�����*/
typedef float	D_Float;	/**< 32λ������*/
typedef double	D_Double;/**< 64λ˫������*/
typedef void*	D_Ptr;		/**< ͨ��ָ��*/
typedef int		D_Int;		/**< ����*/
typedef long int D_Size;	/**< �ռ��С*/
typedef D_S32 	D_ID;		/**< ID*/
typedef D_S32	D_Coord;	/**< ����*/
typedef D_U32	D_Time;		/**< ʱ��(��Ϊ��λ)*/
typedef D_U32	D_MSec;		/**< ����*/
typedef D_S8	D_Char;		/**< �ַ�*/

#if defined(D_SYSTEM_WIN32)
typedef unsigned __int64 D_U64; /**< 64λ�޷�����*/
typedef __int64 D_S64; /**< 64λ�з�����*/
#define DEF_S64(_x_)	_x_
#define DEF_U64(_x_)	_x_
#else
typedef unsigned long long D_U64; /**< 64λ�޷�����*/
typedef long long D_S64; /**< 64λ�з�����*/
#define DEF_S64(_x_)	_x_##LL
#define DEF_U64(_x_)	_x_##ULL
#endif

#ifndef NULL
#define NULL (0)	/**< ��ָ��*/
#endif

/*����ָ������*/
/** @brief ������������ָ��
* @param ptr	����ָ��
* @param pd	���ò���
*/
typedef void	(*D_Func)   (D_Ptr ptr, D_Ptr pd) D_FUNCPOSTFIT;

/** @brief ���˱ȽϺ���
*
*			�� @a p1 ���� @a p2 ʱ,����0��
*			�� @a p1 С�� @a p2 ʱ,����һ��������
*			�� @a p1 ���� @a p2 ʱ,����һ��������
* @param p1	����1ָ��
* @param p2	����2ָ��
*/
typedef D_S32	(*D_CmpFunc)(D_Ptr p1, D_Ptr p2) D_FUNCPOSTFIT;

/** @brief ������*/
typedef D_Int	D_Bool;
#define D_TRUE	(1)	/**< �߼���*/
#define D_FALSE	(0)	/**< �߼���*/

/** @brief �豸���*/
typedef D_S32	D_Handle;

#define D_INVALID_HANDLE	(-1)	/**< ��Ч���*/

#define D_TIMEOUT_INFINITE  ((D_MSec)-1) /**< һֱ�ȴ�>*/
#define D_TIMEOUT_IMMEDIATE ((D_MSec)0) /**< ��������>*/

/** @brief �������ý��*/
typedef D_S32	D_Result;

#define D_OK						(0)	/**< ������ȷִ��*/
#define D_ERR						(-1)/**< ����ִ�д���*/
#define D_ERR_FULL			(-2)/**< ��Ϣ����������*/
#define D_ERR_TIMEOUT		(-3)/**< ��ʱ����*/
#define D_ERR_NO_SPACE	(-4)/**< ���㹻���ڴ�ռ�*/
#define D_ERR_INVALID_HANDLE	(-5)	/**< ��Ч�ľ��*/
#define D_ERR_INVALID_ARGUMENT	(-6)/**< ������Ч*/
#define D_ERR_EMPTY			(-7)/**< ��Ϣ������������*/
#define D_ERR_OVERFLOW	(-8)/**< ���������*/
#define D_ERR_FAULT			(-9)/**< ����*/
#define D_ERR_NOT_SUPPORT	(-10)/**< �������ڲ�֧��*/
#define D_ERR_IO				(-11)	/**< IO����*/
#define D_ERR_NO_DEV		(-12)	/**< û���豸*/
#define D_ERR_ALREADY_DONE	(-13)	/**< �Ѿ������˲���*/

/** @brief �� @a a �� @a b �е����ֵ*/
#define D_MAX(a,b)	((a)>(b)?(a):(b))

/** @brief �� @a a �� @a b �е���Сֵ*/
#define D_MIN(a,b)	((a)<(b)?(a):(b))

/** @brief ��ֵ�Ƿ��ڷ�Χ��*/
#define D_IN_RANGE(a,l,b)	(((a)>=(l))&&((a)<=(b)))

/** @brief ��λ��������������λ*/
#define D_SET_MASK(m,n)		((m)[(n)>>3] |= (1<<((n)&7)))

/** @brief ��λ�������������λ*/
#define D_CLEAR_MASK(m,n)	((m)[(n)>>3] &= ~(1<<((n)&7)))

/** @brief ��λ���������м��һλ�Ƿ��Ѿ���������*/
#define D_ISSET_MASK(m,n)	((m)[(n)>>3] & (1<<((n)&7)))

/** @brief ��2bitλ��������������λ*/
#define D_SET_2BIT(m,n,v)		{((m)[(n)>>2] &= ~(0x03 <<(((n)&0x03) << 1))); ((m)[(n)>>2] |= (((v)&0x03)<<(((n)&0x03) << 1)));}

/** @brief ��2bitλ���������ж�ȡλ*/
#define D_GET_2BIT(m,n)		(0x03 & ((m)[(n)>>2] >> (((n)&0x03) << 1)))

/** @brief ��4bitλ��������������λ*/
#define D_SET_4BIT(m,n,v)		{((m)[(n)>>1] &= ~(0x0f<<(((n)&0x01)<<2))); ((m)[(n)>>1] |= (((v)&0x0f)<<(((n)&0x01)<<2)));}

/** @brief ��4bitλ���������ж�ȡλ*/
#define D_GET_4BIT(m,n)		(0x0f & ((m)[(n)>>1] >> (((n)&0x01) << 2)))

/** @brief �� @a a �ľ���ֵ*/
#define D_ABS(a)		((a)>(0)?(a):-(a))

/** @brief �궨��鿪ʼ*/
#define D_MACRO_BEGIN		do {

/** @brief �궨������*/
#define D_MACRO_END			} while(0)

/*�ֽ���任����*/
/** @brief �任һ��16λ�����ֽ���*/
#define d_swap16(_d)	((((D_U16)(_d)) << 8) | (((D_U16)(_d)) >> 8))

/** @brief �任һ��32λ�����ֽ���*/
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
