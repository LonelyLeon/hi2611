/** @file
* @brief �ڴ�Ķ�̬������ͷ�
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_MEM_H_
#define _D_MEM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include <string.h>

/** @brief �ڴ����
* @param id	�ڴ���ID
* @param size	�����ڴ�Ĵ�С
* @return	�ɹ�ʱ���ط����ڴ��ָ��,ʧ��ʱ����NULL
*/
D_Ptr	d_mem_alloc (D_ID id, D_Size size) D_FUNCPOSTFIT;

/** @brief �����趨�ڴ����Ĵ�С
*
*	��� @a ptr ΪNULL,������ͬ��d_mem_alloc��
*	��� @a ptr ��NULL,�����趨�ڴ����Ĵ�С��
* @param id �ڴ���ID
* @param ptr	NULL,��һ���ڴ���ָ��
* @param size	�ڴ��������趨�Ĵ�С
* @return	�ɹ�ʱ�������ڴ�����ָ�룬ʧ��ʱ����NULL
*/
D_Ptr	d_mem_realloc (D_ID id, D_Ptr ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief �ͷŷ�����ڴ�
* @param ptr	�ѷ�����ڴ���ָ��
*/
void	d_mem_free (D_Ptr ptr) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
