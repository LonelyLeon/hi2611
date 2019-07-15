/** @file
* @brief �������豸����
* @author ����
* @date 2005-5-19 ����: �����ļ�
*	@date 2005-8-24 ����: �豸��������ǰ���豸ID��Ա
*/

#ifndef _D_DSC_H_
#define _D_DSC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dCA.h"

/** @brief �������豸���*/
typedef D_Handle	D_HDsc;

/** @brief �������豸����*/
typedef struct {
	D_ID	id;	/**< �豸ID*/
	D_ID	fend_id;	/**< ��������Ӧ��ǰ���豸ID*/
} D_DscAttr;

/** @brief �⸴���豸���Գ�ʼ��ΪĬ��ֵ*/
#define D_DSC_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ���ŷ�ʽ*/
typedef enum {
	D_DSC_TS_LEVEL,		/**< TS�����*/
	D_DSC_PES_LEVEL		/**< PES�����*/
} D_DscType;

/** @brief ����������*/
typedef enum {
	D_DSC_KEY_ODD,		/**< �������*/
	D_DSC_KEY_EVEN		/**< ż������*/
} D_DscKeyType;

/** @brief ������*/
typedef struct {
	D_U8	key[8];
} D_DscKey;

/** @brief ������ϵͳ��ʼ��
*
*	�ڵ��ý�������������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_dsc_open (void) D_FUNCPOSTFIT;

/** @brief ������ϵͳ��ֹ
*
* �������ʱ���ͷŽ�����ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_dsc_close (void) D_FUNCPOSTFIT;

/** @brief ����һ���������豸
* @param attr	�������豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return �ɹ�ʱ���ؽ������豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HDsc		d_dsc_create (D_DscAttr	*attr) D_FUNCPOSTFIT;

/** @brief ����һ���������豸
* @param hdsc	�������豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_dsc_destroy (D_HDsc hdsc) D_FUNCPOSTFIT;

/** @brief ���ý���������(TS�����/PES�����)
* @param hdsc	���������
* @param type	����������(D_DSC_TS_LEVEL/D_DSC_PES_LEVEL)
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
*/
D_Result	d_dsc_set_type (D_HDsc hdsc, D_DscType type) D_FUNCPOSTFIT;

/** @brief �趨Ҫ��������PIDֵ
* @param hdsc	���������
* @param pid	Ҫ���ŵ�PID
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	PIDֵ��Ч
*/
D_Result	d_dsc_set_pid (D_HDsc hdsc, D_U16 pid) D_FUNCPOSTFIT;

/** @brief �趨������
* @param hdsc	���������
* @param kt		����������(��/ż)
* @param key	������ֵ
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	PIDֵ��Ч
*/
D_Result	d_dsc_set_key (D_HDsc hdsc, D_DscKeyType kt, D_DscKey *key, D_U8 bycwe) D_FUNCPOSTFIT;

D_Result d_hec_set(unsigned char dectype, unsigned char rtkeyctrl, unsigned char *level_data);
D_Result d_hec_set2(unsigned char dectype, unsigned char rtkeyctrl, unsigned char *level_data);
D_Result d_get_chipid(unsigned char *len, unsigned char *chipid);
D_Result d_get_chipid_16bytes(unsigned char *len, unsigned char *chipid);
D_Result d_get_cardno(unsigned char *len, unsigned char *cardno);
D_Result d_get_chipid_fromspu(unsigned char *len, unsigned char *chipid);
D_Result d_get_cardno_fromspu(unsigned char *len, unsigned char *cardno);
D_Result d_burn_otp(unsigned char *otp, D_U16 len, D_U16 addr);
D_Result d_read_otp(unsigned char *otp, D_U16 len, D_U16 addr);
D_Result d_read_tvtype(unsigned char *dtype);
D_U8 d_get_otplockstatus(unsigned char num);
D_Result d_set_otplock(unsigned char secureboot);
#ifdef  __cplusplus
}
#endif

#endif
