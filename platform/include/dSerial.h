/** @file
* @brief �����豸����
* @author ����
* @date 2005-7-1 ����: �����ļ�
*/

#ifndef _D_SERIAL_H_
#define _D_SERIAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �����豸���*/
typedef D_Handle	D_HSerial;

/** @brief ���ڲ�����*/
typedef D_U32	D_SerialBaud;

/** @brief ��������λ��*/
typedef enum {
    D_SERIAL_7_DATABITS,
    D_SERIAL_8_DATABITS
} D_SerialDataBits;

/** @brief ����ֹͣλ��Ŀ*/
typedef enum {
    D_SERIAL_1_STOPBITS,
    D_SERIAL_2_STOPBITS
} D_SerialStopBits;

/** @brief ����У�췽ʽ*/
typedef enum {
    D_SERIAL_NO_PARITY,
    D_SERIAL_ODD_PARITY,
    D_SERIAL_EVEN_PARITY,
    D_SERIAL_SPACE_PARITY
} D_SerialParity;

/** @brief ���ڹ���ģʽ*/
typedef struct {
	D_SerialBaud			baud;				/**< ������*/
	D_SerialDataBits	data_bits;	/**< ����λ*/
	D_SerialStopBits	stop_bits;	/**< ֹͣλ*/
	D_SerialParity		parity;			/**< У�췽ʽ*/
} D_SerialMode;

/** @brief �����豸����*/
typedef struct {
	D_ID							id;					/**< �豸ID*/
} D_SerialAttr;

/** @brief ��ȱʡ���Գ�ʼ�������豸����*/
#define D_SERIAL_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ����ϵͳ��ʼ��
*
*	�ڵ��ô��ڲ�������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_serial_open (void) D_FUNCPOSTFIT;

/** @brief ����ϵͳ��ֹ
*
* �������ʱ���ͷŴ���ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_serial_close (void) D_FUNCPOSTFIT;

/** @brief usb���ڳ�ʼ��
*
*	�ڵ���usb���ڲ�������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result d_serial_open_usb(void) D_FUNCPOSTFIT;

/** @brief ����һ�������豸
* @param attr	�����豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(id=0)
* @return �ɹ�ʱ���ش����豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HSerial	d_serial_create (D_SerialAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ�������豸
* @param hs	�����豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_serial_destroy (D_HSerial hs) D_FUNCPOSTFIT;

/** @brief �趨���ڹ���ģʽ
* @param hs		�����豸���
* @param mode	���ڹ���ģʽ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result 	d_serial_set_mode (D_HSerial hs, D_SerialMode *mode) D_FUNCPOSTFIT; 

/** @brief ��һ�������豸д����
* @param hs	�����豸�ľ��
* @param pd	д���ݵĻ�����
* @param size	д�����ݵ��ֽ���
* @return	����ʵ��д����ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_FAULT	����ʧ��
*/
D_Size		d_serial_write (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief ��һ�������豸������
* @param hs 		�����豸�ľ��
* @param pd		��Ŷ������ݵĻ�����
* @param size	���ݻ�������С
* @return	����ʵ�ʶ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_FAULT	����ʧ��
*/
D_Size		d_serial_read (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;
/** @brief ��һ�������豸������
* @param hs 		�����豸�ľ��
* @param pd		��Ŷ������ݵĻ�����
* @param size	���ݻ�������С
* @param readtimeout	��ʱʱ��
* @return	����ʵ�ʶ������ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_FAULT	����ʧ��
*/
D_Size	d_serial_read_ex (D_HSerial hs, D_U8 *pd, D_Size size, D_U16 readtimeout) D_FUNCPOSTFIT;

D_Size		d_gprs_serial_read (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/*��մ���buffer*/
D_Result d_serial_flush (D_HSerial hs) D_FUNCPOSTFIT;

/** @brief ��ӡ�ַ��������豸
* @param Format_p ��ѭ��ͨ��ӡ�����ṹ
*/
void d_serial_printf(char *Format_p, ...)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
