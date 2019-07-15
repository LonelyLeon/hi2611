/** @file
* @brief EEPRom�豸����
* @author ����
* @date 2005-5-17 ����: �����ļ�
*/

#ifndef _D_EEPROM_H_
#define _D_EEPROM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief EEPRom�豸���*/
typedef D_Handle	D_HEEPRom;

/** @brief EEPRom�豸����*/
typedef struct {
	D_ID							id;					/**< �豸ID*/
	D_Size						size;				/**< ���С*/
} D_EEPRomAttr;

/** @brief ��ȱʡ���Գ�ʼ��EEPRom�豸����*/
#define D_EEPROM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = -1;\
	D_MACRO_END

/** @brief EEProm�豸���� */
typedef enum
{
    D_EEProm_Real = 0,  /**< EEProm�豸 */
    D_EEProm_Fake,      /**< �����豸 */
}D_EEPromType;

/** @brief EEProm�豸���� */
typedef struct
{
    D_U8 iic_bus_no;    /**< i2c���ߺ� */
    D_U8 page_size;     /**< ҳ��С */
}D_EEPromRealParam;

/** @brief EEProm�����豸���� */
typedef struct
{
    D_U32 nvram_offset_1;   /**< ����EEProm�豸��flash����λ�ÿ�1 */
    D_U32 nvram_offset_2;   /**< ����EEProm�豸��flash����λ�ÿ�2 */
    D_U32 nvram_block_size; /**< flash���С */
}D_EEPromFakeParam;

/** @brief EEProm�豸��ʼ���ṹ */
typedef struct
{
    D_EEPromType type;  /**< EEProm�豸���� */
    D_Size size;        /**< EEProm�豸��С */
    union
    {
        D_EEPromRealParam real;
        D_EEPromFakeParam fake;
    }u;
}D_EEPRomOpenParam;

/** @brief EEPRomϵͳ��ʼ��
*
*	�ڵ���EEPRom��������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result d_eeprom_open (D_EEPRomOpenParam *param) D_FUNCPOSTFIT;

/** @brief EEPRomϵͳ��ֹ
*
* �������ʱ���ͷ�EEPRomϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result d_eeprom_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��EEPRom�豸
* @param attr	EEProm�豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(id=0)
* @return �ɹ�ʱ����EEPRom�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HEEPRom d_eeprom_create (D_EEPRomAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��EEPRom�豸
* @param heeprom EEProm�豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result d_eeprom_destroy (D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief ȡ��һ��EEPRom�豸������
*
* ���԰���EEPRom�豸��ID,�ֽ�Ϊ��λ�Ĵ�С
* @param heeprom	EEPRom�豸�ľ��
* @param attr	�����豸���ԵĻ�����
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч
* @retval D_ERR_INVALID_ARGUMENT	attrΪNULL
*/
D_Result d_eeprom_get_attr (D_HEEPRom heeprom, D_EEPRomAttr *attr) D_FUNCPOSTFIT;

/** @brief ��һ��EEPRom�豸д����
* @param heeprom	EEProm�豸�ľ��
* @param offset	д������ʼλ���ڿ��豸�е�ƫ����
* @param pd	д���ݵĻ�����
* @param size	д�����ݵ��ֽ���
* @return	����ʵ��д����ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_OVERFLOW	��ʼƫ�Ƴ����豸��С,��д�����������豸��С
*/
D_Size	d_eeprom_write (D_HEEPRom heeprom, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief ��һ��EEPRom�豸������
* @param heeprom EEPRom�豸�ľ��
* @param offset	��������ʼλ���ڿ��豸�е�ƫ����
* @param pd	��Ŷ������ݵĻ�����
* @param size	���ݻ�������С
* @return	����ʵ�ʶ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_OVERFLOW	��ʼƫ�Ƴ����豸��С,��������������豸��С
*/
D_Size	d_eeprom_read (D_HEEPRom heeprom, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;


/** @brief ���һ��EEPRom�豸����
* @param heeprom EEPRom�豸�ľ��
* @return	�ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result  d_eeprom_clear_all(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief ���EEPRom��Ĳ�������
* @param heeprom EEPRom�豸�ľ��
* @return	�ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result  d_eeprom_clear_part(D_HEEPRom heeprom,D_Size offset, D_Size clearsize)D_FUNCPOSTFIT;

/** @brief eeprom��д����*/
void EEP_RW_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eepromƣ�Ͳ���*/
void EEP_FATIGUE_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eeprom��������*/
void EEP_LIFETIME_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eeprom�������*/
void EEPROM_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
