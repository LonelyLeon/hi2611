
#ifndef _D_P_USB_UPGRADE_H_
#define _D_P_USB_UPGRADE_H_

#include "dTypes.h"
#include "dusb_upgrade.h"
#include "dQueue.h"
#include "dDebug.h"
#include "dMsg.h"


typedef enum {
	D_MSG_USBUPGRADE_NULL = -1,	
	D_MSG_USBUPGRADE_PROGRESS, 	/**< ��������*/
	D_MSG_USBUPGRADE_OK,			/**< �������*/
	D_MSG_USBUPGRADE_FAILED,		/**< ����ʧ��*/
	
} D_USBUPGRADEMsgType;
	

/** @brief����usb��������
* @param [in] ms_hq	�ϲ���Ͼ���
* @param[in]  full_path �����ļ�ȫ·��
* @param[in]  priority	�������ȼ�
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_Handle d_usb_upgrade_create(D_HQueue ms_hq,const char *full_path,D_S8 priority)D_FUNCPOSTFIT;

/** @brief  ����USB����
* @param[in] handle���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_usb_upgrade_destroy (D_Handle handle)D_FUNCPOSTFIT;
#endif
