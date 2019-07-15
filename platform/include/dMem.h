/** @file
* @brief 内存的动态分配和释放
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_MEM_H_
#define _D_MEM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include <string.h>

/** @brief 内存分配
* @param id	内存区ID
* @param size	分配内存的大小
* @return	成功时返回分配内存的指针,失败时返回NULL
*/
D_Ptr	d_mem_alloc (D_ID id, D_Size size) D_FUNCPOSTFIT;

/** @brief 重新设定内存区的大小
*
*	如果 @a ptr 为NULL,函数等同于d_mem_alloc。
*	如果 @a ptr 非NULL,重新设定内存区的大小。
* @param id 内存区ID
* @param ptr	NULL,或一个内存区指针
* @param size	内存区重新设定的大小
* @return	成功时返回新内存区的指针，失败时返回NULL
*/
D_Ptr	d_mem_realloc (D_ID id, D_Ptr ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief 释放分配的内存
* @param ptr	已分配的内存区指针
*/
void	d_mem_free (D_Ptr ptr) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
