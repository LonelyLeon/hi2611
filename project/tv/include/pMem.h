/** @file
* @brief stb内存api
* @author 李臣
* @date 2013-07-03 李臣: 建立文件
*/
#ifndef __MEM_API_H
#define __MEM_API_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

typedef enum
{
	ProjectMemoryPart1 = 0, /**< 分区1*/
	ProjectMemoryPart2, /**< 分区2*/
	ProjectMemoryPartMax,
}ProjectMemoryPart;

/** @brief 工程内存分区初始化*/
D_Result project_mem_init(void);

/** @brief 清除一个分区*/
D_Result project_mem_clear(ProjectMemoryPart MemPart);

/** @brief 从分区分配一块内存*/
D_Ptr project_mem_alloc(ProjectMemoryPart MemPart, D_Size size);

/** @brief 从分区释放一块内存*/
void project_mem_free(ProjectMemoryPart MemPart, D_Ptr p);

#define PROJECT_ALLOC(_s_)	project_mem_alloc(ProjectMemoryPart1, (_s_))
#define PROJECT_FREE(_p_)	project_mem_free(ProjectMemoryPart1, (_p_))

#ifdef  __cplusplus
}
#endif
#endif
