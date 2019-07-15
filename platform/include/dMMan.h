/** @file
* @brief 内存管理模块
* @author 龚克
* @date 2005-6-17 龚克: 建立文件
*/

#ifndef _D_MMAN_H_
#define _D_MMAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 内存管理器句柄*/
typedef D_Handle	D_HMMan;

/** @brief 内存管理策略*/
typedef enum {
	D_MMAN_SIMPLE,	/**< 简单方式,不释放*/
	D_MMAN_HEAP,	/**< 支持释放*/
	D_MMAN_HEAP_OPTIMISE_SPACE, /**< 分配空间优化的heap, 牺牲速度*/
} D_MManType;

/** @brief 内存管理器创建属性 */
typedef struct
{
    D_Ptr block;  /**< 内存起始地址 */
    D_Size size;  /**< 内存大小 */
    D_Size align;  /**< 内存分配对齐大小 */
    D_MManType type;  /**< 内存分配策略 */
}D_MManAttr;

/** @brief 内存管理器分区信息*/
typedef struct
{
	D_MManType type;  /**<  内存管理策略*/
	D_U32 size;  /**< 内存分区大小*/
	D_U32 free_size;  /**< 可分配大小*/
	D_U32 largest_free_block_size;  /**< 可分配最大块大小*/
	D_U32 alloc_blocks;  /**< 已分配内存块个数*/
}D_MManInfo;

/** @brief 内存管理系统初始化
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_mman_open (void) D_FUNCPOSTFIT;

/** @brief 内存管理系统退出
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_mman_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个内存管理器
* @param block	内存起始地址
* @param size		内存大小
* @param type		内存分配策略
* @return 成功时返回内存管理器句柄,失败时返回D_INVALID_HANDLE
*/
D_HMMan		d_mman_create (D_Ptr block, D_Size size, D_MManType type) D_FUNCPOSTFIT;

/** @brief 创建一个内存管理器
* @param attr	内存管理器创建属性
* @return 成功时返回内存管理器句柄,失败时返回D_INVALID_HANDLE
*/
D_HMMan		d_mman_create_ex (D_MManAttr *attr) D_FUNCPOSTFIT;

/** @brief 释放一个内存管理器
* @param hmm	内存管理器句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_mman_destroy (D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 清除内存管理器中全部以分配的空间
* @param hmm	内存管理器句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_mman_clear (D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 通过内存管理器分配一块内存
* @param hmm 内存管理器句柄
* @param size 分配空间大小
* @return 成功返回内存指针,失败返回NULL
*/
D_Ptr		d_mman_alloc (D_HMMan hmm, D_Size size) D_FUNCPOSTFIT;

/** @brief 通过内存管理器释放一块内存
* @param hmm 内存管理器句柄
* @param ptr 释放空间指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_mman_free (D_HMMan hmm, D_Ptr ptr) D_FUNCPOSTFIT;

/** @brief 通过内存管理器重新设定一块内存的大小
* @param hmm 内存管理器句柄
* @param old 旧区域指针
* @param size 新的区域大小
* @return 成功返回内存指针,失败返回NULL
*/
D_Ptr		d_mman_realloc (D_HMMan hmm, D_Ptr old, D_Size size) D_FUNCPOSTFIT;

/** @brief 获得内存管理器分区信息
* @param hmm 内存管理器句柄
* @param info 内存管理器分区信息结构指针
* @return 成功返回D_OK,失败返回err值
*/
D_Result	d_mman_get_info(D_HMMan hmm, D_MManInfo *info);

#ifdef  __cplusplus
}
#endif

#endif
