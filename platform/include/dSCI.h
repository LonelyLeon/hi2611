/** @file
* @brief Smart卡接口设备操作
* @author 李建国
* @date 2005-8-18 李建国: 建立文件
*/

#ifndef _D_SCI_H_
#define _D_SCI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

#define  D_SMART_MAX_HISTORY     15
#define  D_SMART_MAX_ATR         30

/**	@brief 智能卡接口设备句柄*/
typedef D_Handle	D_HSCI;

typedef struct
{
    D_GPIO_PortBit detect;
    D_GPIO_PortBit reset;
    D_GPIO_PortBit vcc_cmd;
    D_Bool open_close;
    D_U8 uart_no;
    D_U8 pwm_sel;
    D_GPIO_PortBit sw_3_5v;
    D_U8 sc_mode;//0小卡 1大卡
}D_SCOpenParam;

/** @brief 数据传输方向*/
typedef enum {
	D_SCI_DIR_READ,		/**< 读数据*/
	D_SCI_DIR_WRITE		/**< 写数据*/
} D_SCIDirection;

/**< @brief 智能卡传输协议*/
typedef enum {
	D_SCI_PROTOCOL_T0,/**< T0传输协议*/
	D_SCI_PROTOCOL_T1	/**< T1传输协议*/
} D_SCIProtocol;

/** @brief 智能卡接口设备属性*/
typedef struct {
	D_ID		id;		/**< 卡设备ID*/
} D_SCIAttr;

/** @brief 用缺省值初始化SCI属性*/
#define D_SCI_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 智能卡状态*/
typedef struct {
	D_Bool	inserted;	/**< 智能卡已经插入*/
} D_SCIStatus;

/** @brief 停止位类型 */
typedef enum StopBits
{
    STOPBITS__0_5 = 0,
    STOPBITS__1_0 = 1,
    STOPBITS__1_5 = 2,
    STOPBITS__2_0 = 3
} D_StopBits;

/** @brief SCI communication parameters */
typedef struct _D_SCIParam
{
    D_U32  baud;
		D_U32	 wwt;
		D_U32	 guard_time;
    D_StopBits      	StopBits;

} D_SCIParam;

/** @brief 智能卡接口系统初始化
*
*	在调用智能卡操作函数时首先调用此函数
* @param param  初始化结构
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_sci_open (D_SCOpenParam *param) D_FUNCPOSTFIT;

/** @brief 智能卡接口系统初始化增强型
*
*	在调用智能卡操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_sci_open_ex (void) D_FUNCPOSTFIT;

/** @brief 智能卡接口系统中止
*
* 程序结束时，释放智能卡接口系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_sci_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个智能卡接口设备
* @param attr	智能卡接口设备属性结构指针，为NULL时使用缺省值
* @return       成功时返回智能卡接口设备句柄，失败返回D_INVALID_HANDLE
*/
D_HSCI		d_sci_create (D_SCIAttr	*attr) D_FUNCPOSTFIT;

/**	@brief 对设备加锁
* @param  hsci										智能卡句柄
* @retval D_OK										操作成功
* @ertval D_ERR_INVALID_HANDLE		设备句柄无效		
*/
D_Result	d_sci_lock(D_HSCI hsci) D_FUNCPOSTFIT;

/**	@brief 对设备解锁
* @param  hsci										智能卡句柄
* @retval D_OK										操作成功
* @ertval D_ERR_INVALID_HANDLE		设备句柄无效		
*/
D_Result	d_sci_unlock(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief 销毁一个智能卡接口设备
* @param hsci	                    	设备句柄
* @retval D_OK	                    释放成功
* @retval	D_ERR_INVALID_HANDLE			句柄无效
*/
D_Result	d_sci_destroy (D_HSCI hsci) D_FUNCPOSTFIT;


/** @brief 取智能卡状态
* @param hsci		                	智能卡句柄
* @param status	                  智能卡状态
* @retval D_OK	                  操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
* @retval D_ERR_IO								数据IO错误
*/
D_Result	d_sci_get_status (D_HSCI hsci, D_SCIStatus *status) D_FUNCPOSTFIT;

/** @brief 设定智能卡接口参数
* @param hsci		                	智能卡句柄
* @param param	                  SCI参数
* @retval D_OK	                  操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
* @retval D_ERR_NO_DEV						没有卡插入
* @retval D_ERR_IO								数据IO错误
*/
D_Result	d_sci_set_param (D_HSCI hsci, D_SCIParam *param) D_FUNCPOSTFIT;

/** @协议类型选择
* @param hsci                     智能卡句柄
* @param pts_bytes_p              协议类型选择数据
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_NO_DEV						没有卡插入
* @retval D_ERR_IO								数据IO错误
* @retval D_OK										操作成功
* @retval D_ERR_INVALID_ARGUMENT	参数无效
*/
D_Result    d_sci_pts(D_HSCI hsci, D_U8 *pts_bytes_p) D_FUNCPOSTFIT;

/** @brief 智能卡复位
* @param hsci											智能卡句柄
* @param atr											存放ATR数据的缓冲区
* @param len											ATR数据缓冲区的大小
* @retval D_OK										操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
* @retval D_ERR_NO_DEV						没有卡插入
* @retval D_ERR_IO								数据IO错误
*/
D_Result	d_sci_reset (D_HSCI hsci, D_U8 *atr, D_Size *len) D_FUNCPOSTFIT;

/** @brief 智能卡T0协议数据传输
* @param hsci											智能卡句柄
* @param capdu										命令缓冲区
* @param clen											命令缓冲区大小
* @param rapdu										接收缓冲区
* @param rlen											接收缓冲区大小
* @retval D_OK										操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
* @retval D_ERR_NO_DEV						没有卡插入
* @retval D_ERR_IO								数据IO错误
*/
D_Result	d_sci_t0_command (D_HSCI hsci, D_U8 *capdu, D_Size clen, D_U8 *rapdu, D_Size *rlen) D_FUNCPOSTFIT;

/** @brief 智能卡T1协议数据传输
* @param hsci											智能卡句柄
* @param capdu										命令缓冲区
* @param clen											命令缓冲区大小
* @param rapdu										接收缓冲区
* @param rlen											接收缓冲区大小
* @retval D_OK										操作成功
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	参数无效
* @retval D_ERR_NO_DEV						没有卡插入
* @retval D_ERR_IO								数据IO错误
*/
D_Result	d_sci_t1_command (D_HSCI hsci, D_U8 *capdu, D_Size clen, D_U8 *rapdu, D_Size *rlen) D_FUNCPOSTFIT;


/** @brief 解除智能卡的操作
* @param hsci                   智能卡句柄 
* @@retval D_OK	                操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效 
*/
D_Result	d_sci_deactivate(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief 智能卡重起
* @param hsci                       设备句柄
* @retval D_OK                      操作成功
* @retval D_ERR_INVALID_HANDLE			设备句柄无效
*/      

D_Result	d_sci_hw_reset(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief 从接口读数据到智能卡上
* @param hsci		                	智能卡句柄
* @param buf	                    存放读入数据的缓冲区
* @param size											读入数据的大小
* @retval                         返回实际读入的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_FAULT	            操作失败
*/
D_Size	d_sci_hw_read (D_HSCI hsci,  D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief 从智能卡写入接口
* @param hsci		                	智能卡句柄
* @param buf	                    写数据的缓冲区
* @param size                     写入数据的大小
* @retval 0	                  返回实际写入的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_FAULT	            操作失败
*/
D_Size	d_sci_hw_write (D_HSCI hsci, D_U8 *buf,  D_Size size) D_FUNCPOSTFIT;

/** @brief 获取历史字节
* @param history											返回历史字节
* @param historylength_p									返回历史字节大小

*/
D_Result
d_sci_gethistory (D_U8 *history, D_U8 *historylength_p) D_FUNCPOSTFIT;

/** @brief 设定智能卡接口参数特殊使用*/
D_Result
d_sci_set_param_ex (D_HSCI hsci, D_SCIParam *param) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
