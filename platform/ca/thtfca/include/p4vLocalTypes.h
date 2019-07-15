/******************************************************************************
 * p4vLocalTypes.h: 定义Lib所需的原始基本类型
 *-----------------------------------------------------------------------------
 *  北京同方凌讯科技有限公司
 *
 *  2008，版权所有，保留一切权利。
 *-----------------------------------------------------------------------------
 *
 * 修订历史
 *     叶魏彬   2009/01/06      创建文件。
 *
 ******************************************************************************/

#ifndef P4V_LOCAL_TYPES_H
#define P4V_LOCAL_TYPES_H

// 八位无符号整型
typedef unsigned char   ird_uint8_t;
// 十六位无符号整型
typedef unsigned short  ird_uint16_t;
// 三十二位无符号整型
typedef unsigned int    ird_uint32_t;

// 八位有符号整型
typedef char            ird_int8_t;
// 十六位有符号整型
typedef short           ird_int16_t;
// 三十二位有符号整型
typedef int             ird_int32_t;
// 本地文件操作符类型
typedef ird_uint32_t    ird_FILE_t;

// 布尔类型
typedef ird_uint8_t     ird_bool_t;

// 无效指针
#ifndef NULL
#define NULL (void *)0
#endif

#ifndef P4V_TRUE
#define P4V_TRUE    1
#endif

#ifndef P4V_FALSE
#define P4V_FALSE   0
#endif

#endif  /* end_of_file */
