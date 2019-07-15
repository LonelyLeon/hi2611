/** @file
* @brief NVRam�豸����
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_NVRAM_H_
#define _D_NVRAM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/*֧�ֵ�Flash�ͺ�*/
#define FLASH_ST_M29W640DT	0
#define FLASH_ST_M29W320ET	1
#define FLASH_EMU						2
#define FLASH_ST_M29W320EB  3
#define FLASH_ST_M28W320HT	4

/** @brief NVRAM�豸���*/
typedef D_Handle	D_HNVRam;

typedef enum
{
	D_SECTOR_NONE,				/* ��Ч*/
	D_SECTOR_TYPE_4K=4096,		/* 4K�ֽڵ�����*/
	D_SECTOR_TYPE_8K=8192,		/* 8K�ֽڵ�����*/
	D_SECTOR_TYPE_16K=16384,		/* 16K�ֽڵ�����*/
	D_SECTOR_TYPE_32K=32768,		/* 32K�ֽڵ�����*/
	D_SECTOR_TYPE_64K=65536,		/* 64KB������*/
}D_NVRamSectType;

typedef	D_U16 SECTOR_NO;
#define	INVALID_SECTOR_NO	((SECTOR_NO)-1)
typedef struct
{
	D_NVRamSectType type;			/* �����������С*/
	SECTOR_NO start;				/* �����һ����������ʼ������*/
	D_U16 sect_cnt;					/* ������������*/
}D_NVRamGroup;

/** @brief NVRAM�豸����*/
typedef struct {
	D_ID						 id;				/**< �豸ID*/
	D_U32						 address;              /**<�豸��ʼ��ַ*/
	D_Size					 size;			/**< �豸��С*/
	D_NVRamGroup *sects;
	D_U16 sect_cnt;
} D_NVRamAttr;

typedef struct {
	D_U32					ManufactCode;              /*���Һ�*/
	D_U32					DeviceCode;              /*�豸��*/
	D_U32    				DeviceType;
} D_NVRamDevice;

/** @brief ��ȱʡֵ��ʼ��NVRam����*/
#define D_NVRAM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = -1;\
	D_MACRO_END

/** @brief NVRAMϵͳ��ʼ��
*
*	�ڵ���NVRam��������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_nvram_open (void) D_FUNCPOSTFIT;

/** @brief NVRAMϵͳ��ֹ
*
* �������ʱ���ͷ�NVRAMϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_nvram_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��NVRAM���豸
* @param attr	NVRAM���豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(�����豸)
* @return �ɹ�ʱ����NVRAM�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HNVRam	d_nvram_create (D_NVRamAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��NVRAM���豸
* @param hnvram NVRAM�豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_nvram_destroy (D_HNVRam hnvram) D_FUNCPOSTFIT;

/** @brief ȡ��һ��NVRAM�豸������
*
* ���԰���NVRAM�豸��ID,�ֽ�Ϊ��λ�Ĵ�С
* @param hnvram	NVRAM�豸�ľ��
* @param attr	�����豸���ԵĻ�����
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
* @retval D_ERR_INVALID_ARGUMENT	attrΪNULL
*/
D_Result	d_nvram_get_attr (D_HNVRam hnvram, D_NVRamAttr *attr) D_FUNCPOSTFIT;

/** @brief ��һ��NVRAM�豸д����
* @param hnvram	NVRAM�豸�ľ��
* @param offset	д������ʼλ���ڿ��豸�е�ƫ����
* @param pd	д���ݵĻ�����
* @param size	д�����ݵ��ֽ���
* @return	����ʵ�ʶ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_OVERFLOW	��ʼƫ�Ƴ����豸��С,��д�����������豸��С
*/
D_Size			d_nvram_write (D_HNVRam hnvram, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief ��һ��NVRAM�豸������
* @param hnvram	NVRAM�豸�ľ��
* @param offset	��������ʼλ���ڿ��豸�е�ƫ����
* @param pd	��Ŷ������ݵĻ�����
* @param size	���ݻ�������С
* @return	����ʵ�ʶ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_OVERFLOW	��ʼƫ�Ƴ����豸��С,��������������豸��С
*/
D_Size			d_nvram_read (D_HNVRam hnvram, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief ����NVRam�豸
* @param hnvram	NVRAM�豸�ľ��
* @param offset	������ʼλ���ڿ��豸�е�ƫ����
* @param size	��������С
* @return	����ʵ�ʲ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_OVERFLOW	��ʼƫ�Ƴ����豸��С,������������豸��С
*/
D_Size			d_nvram_erase (D_HNVRam hnvram, D_Size offset, D_Size size) D_FUNCPOSTFIT;

D_Size d_nvram_lockEnable (D_HNVRam hnvram);
D_Size d_nvram_lockstate (D_HNVRam hnvram, D_Size offset);
D_Size d_nvram_unlock (D_HNVRam hnvram, D_Size offset);
D_Size d_nvram_lock (D_HNVRam hnvram, D_Size offset);
D_Result d_nvram_get_device(D_NVRamDevice* NvDeviceInfo);

#ifdef  __cplusplus
}
#endif

#endif
