/** @file
* @brief stb�ڴ�api
* @author �
* @date 2013-07-03 �: �����ļ�
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
	ProjectMemoryPart1 = 0, /**< ����1*/
	ProjectMemoryPart2, /**< ����2*/
	ProjectMemoryPartMax,
}ProjectMemoryPart;

/** @brief �����ڴ������ʼ��*/
D_Result project_mem_init(void);

/** @brief ���һ������*/
D_Result project_mem_clear(ProjectMemoryPart MemPart);

/** @brief �ӷ�������һ���ڴ�*/
D_Ptr project_mem_alloc(ProjectMemoryPart MemPart, D_Size size);

/** @brief �ӷ����ͷ�һ���ڴ�*/
void project_mem_free(ProjectMemoryPart MemPart, D_Ptr p);

#define PROJECT_ALLOC(_s_)	project_mem_alloc(ProjectMemoryPart1, (_s_))
#define PROJECT_FREE(_p_)	project_mem_free(ProjectMemoryPart1, (_p_))

#ifdef  __cplusplus
}
#endif
#endif
