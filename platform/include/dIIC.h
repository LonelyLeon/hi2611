/** @file
* @brief IIC�豸����
* @author ����
* @date 2005-5-16 ����: �����ļ�
*/

#ifndef _D_IIC_H_
#define _D_IIC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief IIC�豸���*/
typedef D_Handle    D_HIIC;

/** @brief IIC��ַģʽ*/
typedef enum {
    D_IIC_ADDR_7BITS,   /**< 7λ��ַ*/
    D_IIC_ADDR_10BITS   /**< 10λ��ַ*/
} D_IICAddrType;

/** @brief IIC�豸����*/
typedef struct {
    D_ID    id; /**<  IIC����ID*/
} D_IICAttr;

/** @brief ��ȱʡ������ʼ��IIC�豸����*/
#define D_IIC_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->id = 0;\
    D_MACRO_END

/** @brief i2c�豸��ʼ���ṹ */
typedef struct
{
    D_GPIO_PortBit sda;
    D_GPIO_PortBit sdc;
}D_IICOpenParam;

/**  @brief ������ʱ����
*    @param time  ��ʱ����
*/
void d_iic_set_time_delay (D_U8 time) D_FUNCPOSTFIT;

/** @brief IIC���߼���
*
*   ��IIC����ʱ����
* @param hiic   IIC�豸���   
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
*   
*/
D_Result d_iic_lock( D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief IIC���߽���
*
*   ��IIC����ʱ����
* @param hiic   IIC�豸���   
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
*   
*/
D_Result d_iic_unlock(D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief IICϵͳ��ʼ��
*
*   �ڵ���IIC��������ʱ���ȵ��ô˺���
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result d_iic_open (D_IICOpenParam *param, D_Size cnt) D_FUNCPOSTFIT;

D_Result d_iic_open_ex(void) D_FUNCPOSTFIT;

/** @brief IICϵͳ��ֹ
*
* �������ʱ���ͷ�IICϵͳ�ڵ���Դ
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_iic_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��IIC�豸
* @param attr   IIC���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(iic_id=0)
* @return �ɹ�ʱ����IIC�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HIIC d_iic_create (D_IICAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��IIC�豸
* @param hiic   IIC�豸���
* @retval D_OK  �ͷųɹ�
* @retval   D_ERR_INVALID_HANDLE    �����Ч
*/
D_Result d_iic_destroy (D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief �趨IIC��ַ
* @param hiic   IIC�豸���
* @param at     ��ַ����(7/10λ)
* @param addr   IIC��ַ
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
*/
D_Result d_iic_set_slave_addr (D_HIIC hiic, D_IICAddrType at, D_U16 addr) D_FUNCPOSTFIT;

/** @brief ����IIC�ٶ�
* @param hiic   IIC�豸���
* @param speed  IIC�ٶ�ֵ(��λ:kb/s)
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_iic_set_speed (D_HIIC hiic, D_U32 speed) D_FUNCPOSTFIT;

/** @brief  IIC������
* @param hiic   IIC�豸���
* @param slave  slave�豸��ַ
* @param addr   Ҫ���ļĴ����ĵ�ַ
* @param buffer �����ݻ�����ָ��
* @param size   Ҫ�����ֽ���
* @param addrlen�Ĵ�������ַ���ֽڸ���(0 - 2)
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_S32 d_iic_read(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *buffer, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;
D_S32 d_iic_read_stop(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *buffer, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;

/** @brief  IICд����
* @param hiic   IIC�豸���
* @param slave  slave�豸�ĵ�ַ
* @param addr   Ҫд�ļĴ����ĵ�ַ
* @param value  д���ݵĻ�����ָ��
* @param size   Ҫд����ֽ���
* @param addrlen�Ĵ�������ַ���ֽڸ���(0 - 2)
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_S32 d_iic_write(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *value, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;

/** @brief  IIC��ǰ��ַ������
* @param hiic   IIC�豸���
* @param slave  slave�豸��ַ
* @param buffer �����ݻ�����ָ��
* @param size   Ҫ�����ֽ���
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_S32 d_iic_cur_addr_read(D_HIIC hiic, D_U8 slave, D_U8 *buffer, D_U32 size)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

