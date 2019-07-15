/** @file
* @brief 调试操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 整理代码
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

#define	DBG_CRIT	"<0>"	/**< 崩溃打印*/
#define	DBG_ERR		"<1>"	/**< 错误信息*/
#define	DBG_WARN	"<2>"	/**< 警告信息*/
#define	DBG_INFO	"<3>"	/**< 提示信息*/
#define	DBG_DEBUG	"<4>"	/**< 调试信息*/

typedef enum
{
	D_Lev_None = -1, /* 为让D_DbgLevel类型为有符号int*/
	D_Lev_Critical = 0,
	D_Lev_Error,
	D_Lev_Warn,
	D_Lev_Info,
	D_Lev_Debug,
}D_DbgLevel;

typedef D_Int (*D_DbgGetc)(void);
typedef D_Int (*D_DbgPutc)(D_Int);

/** @brief 初始化调试接口
*
*/
D_Result d_dbg_open(void);

/** @brief 打印接口
*
*/
void d_dbg_printf (char *fmt, ...) D_FUNCPOSTFIT;

/** @brief 字符输入接口
*
*/
D_Int d_dbg_get_char(void);

/** @brief 字符输出接口
*
*/
D_Int d_dbg_put_char(D_Int chr);

/** @brief 字符串输出接口
*
*/
void d_dbg_puts(char *str);

/** @brief 设置io接口
*
*/
D_Result d_dbg_set_io_func(D_DbgGetc i_func, D_DbgPutc o_func);

/** @brief 设置打印级别
*
*/
D_Result d_dbg_set_level(D_DbgLevel level);

/** @brief Assert表达式
*
* 当表达式值为真时，函数立即返回。
* 当表达式值为假时，程序立即结束，返回错误。
*/
#define D_ASSERT(x)	assert(x)

/** @brief 输出调试信息
*
*/
#ifdef D_DEVTOOLS_MSVC
    /* VC7.0以下版本不支持变参数宏定义 */
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
