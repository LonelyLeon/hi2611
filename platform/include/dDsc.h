/** @file
* @brief 解扰器设备操作
* @author 龚克
* @date 2005-5-19 龚克: 建立文件
*	@date 2005-8-24 龚克: 设备属性增加前端设备ID成员
*/

#ifndef _D_DSC_H_
#define _D_DSC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dCA.h"

/** @brief 解扰器设备句柄*/
typedef D_Handle	D_HDsc;

/** @brief 解扰器设备属性*/
typedef struct {
	D_ID	id;	/**< 设备ID*/
	D_ID	fend_id;	/**< 解扰器对应的前端设备ID*/
} D_DscAttr;

/** @brief 解复用设备属性初始化为默认值*/
#define D_DSC_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 解扰方式*/
typedef enum {
	D_DSC_TS_LEVEL,		/**< TS层加扰*/
	D_DSC_PES_LEVEL		/**< PES层加扰*/
} D_DscType;

/** @brief 控制子类型*/
typedef enum {
	D_DSC_KEY_ODD,		/**< 奇控制字*/
	D_DSC_KEY_EVEN		/**< 偶控制字*/
} D_DscKeyType;

/** @brief 控制字*/
typedef struct {
	D_U8	key[8];
} D_DscKey;

/** @brief 解扰器系统初始化
*
*	在调用解扰器操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_dsc_open (void) D_FUNCPOSTFIT;

/** @brief 解扰器系统中止
*
* 程序结束时，释放解扰器系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_dsc_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个解扰器设备
* @param attr	解扰器设备属性结构指针，为NULL时使用缺省值
* @return 成功时返回解扰器设备句柄，失败返回D_INVALID_HANDLE
*/
D_HDsc		d_dsc_create (D_DscAttr	*attr) D_FUNCPOSTFIT;

/** @brief 销毁一个解扰器设备
* @param hdsc	解扰器设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_dsc_destroy (D_HDsc hdsc) D_FUNCPOSTFIT;

/** @brief 设置解扰器类型(TS层加扰/PES层加扰)
* @param hdsc	解扰器句柄
* @param type	解扰器类型(D_DSC_TS_LEVEL/D_DSC_PES_LEVEL)
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
*/
D_Result	d_dsc_set_type (D_HDsc hdsc, D_DscType type) D_FUNCPOSTFIT;

/** @brief 设定要解扰流的PID值
* @param hdsc	解扰器句柄
* @param pid	要解扰的PID
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	PID值无效
*/
D_Result	d_dsc_set_pid (D_HDsc hdsc, D_U16 pid) D_FUNCPOSTFIT;

/** @brief 设定控制字
* @param hdsc	解扰器句柄
* @param kt		控制子类型(奇/偶)
* @param key	控制字值
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	PID值无效
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
