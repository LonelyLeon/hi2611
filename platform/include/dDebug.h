/** @file
* @brief ���Բ���
* @author ����
* @date 2005-5-16 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, �������
*/

#ifndef _D_DEBUG_H_
#define _D_DEBUG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include <assert.h>
#include <stdio.h>

#define	DBG_CRIT	"<0>"	/**< ������ӡ*/
#define	DBG_ERR		"<1>"	/**< ������Ϣ*/
#define	DBG_WARN	"<2>"	/**< ������Ϣ*/
#define	DBG_INFO	"<3>"	/**< ��ʾ��Ϣ*/
#define	DBG_DEBUG	"<4>"	/**< ������Ϣ*/

typedef enum
{
	D_Lev_None = -1, /* Ϊ��D_DbgLevel����Ϊ�з���int*/
	D_Lev_Critical = 0,
	D_Lev_Error,
	D_Lev_Warn,
	D_Lev_Info,
	D_Lev_Debug,
}D_DbgLevel;

typedef D_Int (*D_DbgGetc)(void);
typedef D_Int (*D_DbgPutc)(D_Int);

/** @brief ��ʼ�����Խӿ�
*
*/
D_Result d_dbg_open(void);

/** @brief ��ӡ�ӿ�
*
*/
void d_dbg_printf (char *fmt, ...) D_FUNCPOSTFIT;

/** @brief �ַ�����ӿ�
*
*/
D_Int d_dbg_get_char(void);

/** @brief �ַ�����ӿ�
*
*/
D_Int d_dbg_put_char(D_Int chr);

/** @brief �ַ�������ӿ�
*
*/
void d_dbg_puts(char *str);

/** @brief ����io�ӿ�
*
*/
D_Result d_dbg_set_io_func(D_DbgGetc i_func, D_DbgPutc o_func);

/** @brief ���ô�ӡ����
*
*/
D_Result d_dbg_set_level(D_DbgLevel level);

/** @brief Assert���ʽ
*
* �����ʽֵΪ��ʱ�������������ء�
* �����ʽֵΪ��ʱ�������������������ش���
*/
#define D_ASSERT(x)	assert(x)

/** @brief ���������Ϣ
*
*/
#ifdef D_DEVTOOLS_MSVC
    /* VC7.0���°汾��֧�ֱ�����궨�� */
    void D_CRIT(char *fmt, ...);
    void D_ERROR(char *fmt, ...);
    void D_WARNING(char *fmt, ...);
    void D_INFO(char *fmt, ...);
    void D_DUMP(char *fmt, ...);
#else
#	define D_CRIT(_x_, ...)		d_dbg_printf(DBG_CRIT _x_, ##__VA_ARGS__)
#	define D_ERROR(_x_, ...)	d_dbg_printf(DBG_ERR _x_, ##__VA_ARGS__)
#	define D_WARNING(_x_, ...)	d_dbg_printf(DBG_WARN _x_, ##__VA_ARGS__)
#	define D_INFO(_x_, ...)		d_dbg_printf(DBG_INFO _x_, ##__VA_ARGS__)
#	define D_DUMP(_x_, ...)		d_dbg_printf(DBG_DEBUG _x_, ##__VA_ARGS__)
#endif




#if defined(D_MEDIA_DEBUG)
#	define D_TRACE_FUNC()	                D_ERROR("%s:%s\n", __FILE__, __FUNCTION__)
#	define D_TRACE_FUNC_BEGIN()	            D_ERROR(">>>>>>%s BEGIN\n", __FUNCTION__)
#	define D_TRACE_FUNC_END()	            D_ERROR(">>>>>>%s END\n", __FUNCTION__)
#	define D_TRACE_FUNC_LINE_EX(x, ...)     D_ERROR("   %s(%d)" x, __FILE__, __LINE__, ##__VA_ARGS__)
#	define D_TRACE_FUNC_LINE()              D_ERROR("   %s(%d)\n", __FILE__, __LINE__)
#else
#	define D_TRACE_FUNC()	                do {} while(0)
#	define D_TRACE_FUNC_BEGIN()	            do {} while(0)
#	define D_TRACE_FUNC_END()	            do {} while(0)
#	define D_TRACE_FUNC_LINE_EX(x, ...)     do {} while(0)
#	define D_TRACE_FUNC_LINE()              do {} while(0)
#endif





#ifdef LOG_TAG
#   define D_ERROR_TAG(fmt, ...)  D_ERROR(LOG_TAG fmt, ##__VA_ARGS__)
#else
#   define D_ERROR_TAG(fmt, ...)  D_ERROR(fmt, ##__VA_ARGS__)
#endif








#ifdef  __cplusplus
}
#endif

#endif
