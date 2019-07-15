/** @file
* @brief 网络适配器驱动
* @author 李臣
* @date 2014-05-07 : 李臣
                     建立文件
*/
#ifndef _D_NETEND_H_
#define _D_NETEND_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 网端设备句柄*/
typedef D_Handle D_HNEnd;
/** @brief 接收回调类型 */
typedef void (*D_NEnd_ReceiveIndicate_Func)(D_HNEnd hnend, D_Ptr packet, D_U32 packet_length, D_Ptr ctx) D_FUNCPOSTFIT;

/** @brief 网端设备控制信息类型 */
#define NEND_OIDDATA_BASE                       0x80000000

#define NEND_OIDDATA_GETMACADDRESS              (NEND_OIDDATA_BASE + 1)   /**< 获得MAC地址 */
#define NEND_OIDDATA_SETMACADDRESS              (NEND_OIDDATA_BASE + 2)   /**< 设置MAC地址 */
#define NEND_OIDDATA_GETMULTICASTADDRLIST       (NEND_OIDDATA_BASE + 3)   /**< 获得多播列表 */
#define NEND_OIDDATA_SETMULTICASTADDRLIST       (NEND_OIDDATA_BASE + 4)   /**< 设置多播列表 */
#define NEND_OIDDATA_GETFILTER                  (NEND_OIDDATA_BASE + 5)   /**< 获得过滤模式 */
#define NEND_OIDDATA_SETFILTER                  (NEND_OIDDATA_BASE + 6)   /**< 设置过滤模式 */
#define NEND_OIDDATA_RESET                      (NEND_OIDDATA_BASE + 7)   /**< 复位设备 */

/** @brief 过滤模式*/
typedef enum
{
    NEND_FILTERMODE_DIRECT = 1,  /**< 直接模式, 只允许接收本机MAC地址的数据 */
    NEND_FILTERMODE_BROADCAST,   /**< 广播模式, 只允许接收广播数据 */
    NEND_FILTERMODE_PROMISCUOUS, /**< 混杂模式, 接收进入适配器的任何数据 */
}D_NEndParamFilterMode;

/** @brief 网端设备状态值*/
#define NEND_STATUS_LINKED                      0x00000001

/** @brief 网端设置参数*/
typedef struct
{
    D_U32 oid_type; /**< 控制信息类型 */
    D_Ptr oid_data;  /**< 控制信息数据缓冲区 */
    D_U32 oid_datalength; /**< 控制信息数据长度 */
}D_NEndParam;

/** @brief 网端状态*/
typedef struct {
    D_U32 status;
} D_NEndStatus;

/** @brief 网端设备属性*/
typedef struct {
	D_ID id; /**< 网端设备ID*/
} D_NEndAttr;

/** @brief 用缺省配置初始化网端设备属性*/
#define D_NEND_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 网端系统初始化
*
*	在调用网端操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始n化失败
*/
D_Result d_nend_open(void) D_FUNCPOSTFIT;

/** @brief 网端管理系统中止
*
* 程序结束时，释放网端系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result d_nend_close(void) D_FUNCPOSTFIT;

/** @brief 创建一个网端设备
* @param attr	网端设备属性结构指针，为NULL时使用缺省值
* @return 成功时返回网端设备句柄，失败返回D_INVALID_HANDLE
*/
D_HNEnd	d_nend_create(D_NEndAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个网端设备
* @param hnend 网端设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result d_nend_destroy(D_HNEnd hnend) D_FUNCPOSTFIT;

/** @brief 设定一个网端设备的参数
* @param hnend	网端设备句柄
* @param param	网端参数
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_HANDLE		句柄无效
* @retval	D_ERR_INVALID_ARGUMENT	参数 @a param 无效
*/
D_Result d_nend_set_param(D_HNEnd hnend, D_NEndParam *param) D_FUNCPOSTFIT;


/** @brief 取得一个网端设备当前状态
* @param hnend	网端设备句柄
* @param status	网端设备状态结构缓冲区指针
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE		句柄无效
* @retval D_ERR_INVALID_ARGUMENT	status为NULL
*/
D_Result d_nend_get_status(D_HNEnd hnend, D_NEndStatus *status) D_FUNCPOSTFIT;


/** @brief 往一个网端设备发送数据
* @param hnend	网端设备句柄
* @param buf 	数据缓冲区指针
* @param buf_length 数据长度
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE		句柄无效
* @retval D_ERR_INVALID_ARGUMENT	buf为NULL, 或buf_length为0
*/
D_Result d_nend_send_data(D_HNEnd hnend, D_U8* buf, D_U32 buf_length) D_FUNCPOSTFIT;

/** @brief 注册一个接收回调函数
* @param hnend	网端设备句柄
* @param receiveindicate_func 回调指针
* @param ctx  回调参数
* @retval D_ERR_INVALID_ARGUMENT	receiveindicate_func为NULL
*/
D_Result d_nend_register_receiveindicate_callback(D_HNEnd hnend, D_NEnd_ReceiveIndicate_Func receiveindicate_func, D_Ptr ctx) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

