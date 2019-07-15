
#ifndef _D_P_USB_UPGRADE_H_
#define _D_P_USB_UPGRADE_H_

#include "dTypes.h"
#include "dusb_upgrade.h"
#include "dQueue.h"
#include "dDebug.h"
#include "dMsg.h"


typedef enum {
	D_MSG_USBUPGRADE_NULL = -1,	
	D_MSG_USBUPGRADE_PROGRESS, 	/**< 升级进度*/
	D_MSG_USBUPGRADE_OK,			/**< 升级完成*/
	D_MSG_USBUPGRADE_FAILED,		/**< 升级失败*/
	
} D_USBUPGRADEMsgType;
	

/** @brief创建usb升级任务
* @param [in] ms_hq	上层消暇浔
* @param[in]  full_path 升级文件全路径
* @param[in]  priority	任务优先级
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_Handle d_usb_upgrade_create(D_HQueue ms_hq,const char *full_path,D_S8 priority)D_FUNCPOSTFIT;

/** @brief  结束USB升级
* @param[in] handle句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_usb_upgrade_destroy (D_Handle handle)D_FUNCPOSTFIT;
#endif
