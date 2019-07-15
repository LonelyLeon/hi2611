/** @file
* @brief stb内存api
* @author 李臣
* @date 2013-07-03 李臣: 建立文件
*/
#include "dMem.h"
#include "dMMan.h"
#include "dDebug.h"
#include "pMem.h"

static D_Ptr mem_ProjectMemPart[ProjectMemoryPartMax];
static D_HMMan hmm_ProjectMemPart[ProjectMemoryPartMax];

/** @brief 工程内存分区初始化*/
D_Result project_mem_init(void) D_FUNCPOSTFIT
{
	if(D_MEM1_SIZE)
	{
		mem_ProjectMemPart[0] = d_mem_alloc(0, D_MEM1_SIZE);
		if(mem_ProjectMemPart[0] == NULL)
		{
			D_ERROR("Can not allocate '%d' bytes for ProjectMemPart1!\n", D_MEM1_SIZE);
			return D_ERR_NO_SPACE;
		}

		hmm_ProjectMemPart[0] = d_mman_create(mem_ProjectMemPart[0], D_MEM1_SIZE, D_MMAN_HEAP);
		if(hmm_ProjectMemPart[0] == D_INVALID_HANDLE)
		{
			d_mem_free(mem_ProjectMemPart[0]);
			D_ERROR("Can not create mman for ProjectMemPart1!\n");
			return D_ERR;
		}
	}

	if(D_MEM2_SIZE)
	{
		mem_ProjectMemPart[1] = d_mem_alloc(0, D_MEM2_SIZE);
		if(mem_ProjectMemPart[1] == NULL)
		{
			D_ERROR("Can not allocate '%d' bytes for ProjectMemPart2!\n", D_MEM2_SIZE);
			return D_ERR_NO_SPACE;
		}

		hmm_ProjectMemPart[1] = d_mman_create(mem_ProjectMemPart[1], D_MEM2_SIZE, D_MMAN_HEAP);
		if(hmm_ProjectMemPart[1] == D_INVALID_HANDLE)
		{
			d_mem_free(mem_ProjectMemPart[1]);
			D_ERROR("Can not create mman for ProjectMemPart2!\n");
			return D_ERR;
		}
	}

	D_INFO("Project mem part1 at 0x%X, size %u\n", mem_ProjectMemPart[0], D_MEM1_SIZE);
	D_INFO("Project mem part2 at 0x%X, size %u\n", mem_ProjectMemPart[1], D_MEM2_SIZE);

	return D_OK;
}

/** @brief 清除一个分区*/
D_Result project_mem_clear(ProjectMemoryPart MemPart) D_FUNCPOSTFIT
{
	if(MemPart >= ProjectMemoryPartMax)
	{
		D_WARNING("Invalid ProjectMemoryPart '%d'!\n", MemPart);
		return D_ERR_INVALID_HANDLE;
	}

	if(hmm_ProjectMemPart[MemPart] == D_INVALID_HANDLE)
	{
		D_WARNING("Invalid ProjectMemoryPart handle!\n");
		return D_ERR_INVALID_ARGUMENT;
	}

	d_mman_clear(hmm_ProjectMemPart[MemPart]);

	return D_OK;
}

/** @brief 从分区分配一块内存*/
D_Ptr project_mem_alloc(ProjectMemoryPart MemPart, D_Size size) D_FUNCPOSTFIT
{
	if(MemPart >= ProjectMemoryPartMax)
	{
		D_WARNING("Invalid ProjectMemoryPart '%d'!\n", MemPart);
		return NULL;
	}

	if(hmm_ProjectMemPart[MemPart] == D_INVALID_HANDLE)
	{
		D_WARNING("Invalid ProjectMemoryPart handle!\n");
		return NULL;
	}

	return d_mman_alloc(hmm_ProjectMemPart[MemPart], size);
}

/** @brief 从分区释放一块内存*/
void project_mem_free(ProjectMemoryPart MemPart, D_Ptr p) D_FUNCPOSTFIT
{
	if(MemPart >= ProjectMemoryPartMax)
	{
		D_WARNING("Invalid ProjectMemoryPart '%d'!\n", MemPart);
		return;
	}

	if(hmm_ProjectMemPart[MemPart] == D_INVALID_HANDLE)
	{
		D_WARNING("Invalid ProjectMemoryPart handle!\n");
		return;
	}

	d_mman_free(hmm_ProjectMemPart[MemPart], p);
}

