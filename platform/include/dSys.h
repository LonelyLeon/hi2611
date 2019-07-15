/** @file
* @brief 系统操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_SYS_H_
#define _D_SYS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dTask.h"
#include "dIO.h"
#include "dDebug.h"

/** @brief 系统各模块时钟配置 */
typedef struct
{
    D_U32 cpu_freq;     /**< 主CPU时钟 */
}D_ClockCfg;

/** @brief 系统内存配置 */
typedef struct
{
    D_U32 sys_mem_addr; /**< 用于d_mem_alloc()分配的内存基地址,通常映射为cache内存 */
    D_Size sys_mem_size;/**< 用于d_mem_alloc()分配的内存大小 */
    D_U32 av_mem_addr;  /**< 用于HRAvMemAllocateBlock()分配的内存基地址,通常给设备分配内存,映射为noncache内存 */
    D_Size av_mem_size;  /**< 用于HRAvMemAllocateBlock()分配的内存大小 */
    D_Size av_mem_block_cnt;/**< HRAvMemAllocateBlock()可分配的最大块数 */
}D_SysMemCfg;

/** @brief OS相关配置 */
typedef struct
{
    D_S32 time_slice;   /**< 时间片轮转调度的时间片, tick单位 */
}D_KernelCfg;

/** @brief 打印配置 */
typedef struct
{
    D_S8 uart_no;       /**< uart号(0,1...);-1为无效,表示不开串口打印 */
    D_U32 baudrate;     /**< 波特率 */
}D_UartPrintCfg;

/** @brief 系统初始化结构 */
typedef struct
{
    D_ClockCfg clock;
    D_SysMemCfg memory;
    D_KernelCfg kernel;
    D_UartPrintCfg uart_print;
}D_SysOpenParam;

/** @brief 系统地址类型 */
typedef enum
{
    D_SysAddr_Cached = 0,
    D_SysAddr_UnCached,
    D_SysAddr_Phys,
}D_SysAddressType;

/** @brief 系统初始化
*
*	程序中首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_sys_open (D_SysOpenParam *param) D_FUNCPOSTFIT;

/** @brief 系统中止
*
* 程序结束时，释放系统资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_sys_close (void) D_FUNCPOSTFIT;

/** @brief 取得从系统启动到调用时经历的时间
* @return	以毫秒为单位的系统时间
*/
D_U32	d_sys_get_time (void) D_FUNCPOSTFIT;

/** @brief 系统重新启动
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
void	d_sys_reboot (void) D_FUNCPOSTFIT;
/** @brief    开机检测，是第一次上电还是待机唤醒
* @param[in]  void
* @retvalflag 0:第一次上电，1:待机唤醒，2：MCU没有应答
*/
D_U8 d_sys_power_mode(void)D_FUNCPOSTFIT;

/** @brief 系统挂起,进入节电状态
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_sys_stand_by (void) D_FUNCPOSTFIT;

/** @brief	系统从挂起状态恢复
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_sys_wake_up (void) D_FUNCPOSTFIT;

/** @brief 将Cache中的内容刷新到SDRAM中*/
D_Result	d_sys_cache_flush (void) D_FUNCPOSTFIT;

/** @brief 取得系统每秒的tick单位
* @return	系统每秒的tick
*/
D_U32	d_sys_get_tick_per_sec (void) D_FUNCPOSTFIT;

/** @brief 取得从系统启动到调用时经历的时间
* @return	以tick为单位的系统时间
*/
D_U32	d_sys_get_tick (void) D_FUNCPOSTFIT;

/** @brief 将Cache中的指定内容刷新到SDRAM中*/
D_Result d_sys_cache_flush_range (D_Ptr from_addr, D_U32 size) D_FUNCPOSTFIT;

/** @brief 将地址映射成指定地址类型
* @param[in] type  指定的地址类型
* @param[in] addr  要转换的地址
* @param[in] size  要映射的地址范围大小
* @return  转换后的地址
*/
D_Ptr d_sys_map_address(D_SysAddressType type, D_Ptr addr, D_U32 size) D_FUNCPOSTFIT;

/** @brief 释放映射后的地址
* @param[in] mapped_addr 映射地址
*/
void d_sys_unmap_address(D_Ptr mapped_addr) D_FUNCPOSTFIT;

/** @brief 分配设备内存
* @param[in] size 要分配的内存大小
* @return 连续的物理地址
*/
D_Ptr d_sys_alloc_dev_mem(D_Size size, D_U32 align) D_FUNCPOSTFIT;

/** @brief 释放分配的设备内存
* @param[in] dev_addr 设备内存地址
*/
void d_sys_free_dev_mem(D_Ptr dev_addr) D_FUNCPOSTFIT;

void d_sys_set_atvclock(float frq,D_S16 offset) D_FUNCPOSTFIT;
void d_sys_watchdog_feeddog(D_U32 TimeOutMs, D_U8 Reset, D_U8 Interrupt) D_FUNCPOSTFIT;


/** @brief 获取demod需要使用的内存
* @param 
*/
D_Result d_sys_get_demod_mem(D_U32 id,D_U32 *addr,D_U32 *length)D_FUNCPOSTFIT;
/** @brief 获取demod需要使用的内存
* @param 
*/
D_Result d_sys_release_demod_mem(D_U32 addr)D_FUNCPOSTFIT;
/** @brief 检测芯片是否是开门狗复位
* @param 
*/
D_Result d_sys_check_watchdog_reset(void)D_FUNCPOSTFIT;


/** @brief 设置寄存器值
* @param 
*/
D_Result d_sys_set_reg(D_U32 addr, D_U8 value,D_U8 mask)D_FUNCPOSTFIT;

/** @brief 读取寄存器值
* @param 
*/
D_U8 d_sys_get_reg(D_U32 addr)D_FUNCPOSTFIT;

/** @brief 设置与3700相关的系统寄存器
* @param[in] NULL
*/
void d_sys_3700reg_set(void) D_FUNCPOSTFIT;

D_U8 d_sys_check_CVBS_signal(D_U8 flag) D_FUNCPOSTFIT;

/** @brief 设置与3701CVBS相关的系统寄存器
* @param[in] NULL
*/
void d_sys_3701CVBSreg_set(D_U8 flag,D_U8 mode) D_FUNCPOSTFIT;

/** @brief 设置与3701相关的系统寄存器
* @param[in] NULL
*/
void d_sys_3701reg_set(void) D_FUNCPOSTFIT;

void ADC_FIFO_RESET(void) D_FUNCPOSTFIT;

/** @brief 设置与3205相关的系统寄存器
* @param[in] NULL
*/
void d_sys_3205reg_set(void) D_FUNCPOSTFIT;

/** @brief 3308E相关系统配置
* @param[in] NULL
*/
void d_sys_3308Ereg_set(void) D_FUNCPOSTFIT;


/** @brief 设置与dtbm相关的系统寄存器
* @param[in] NULL
*/
void d_sys_dtmb_reg_set(void) D_FUNCPOSTFIT;


/** @brief 计时打印宏 */
#ifdef D_DEBUG_TIME_RECORD
extern D_U32 __time_record_start;
extern D_Bool __time_record_run;

#define TIME_RECORD_START(_s)   {\
                                    __time_record_start = d_sys_get_time();\
                                    __time_record_run = D_TRUE;\
                                    D_DUMP(_s "::Start time record AT \"%s\"(%d)\n", __FILE__, __LINE__);\
                                }
#define TIME_RECORD_ONE(_s)     if(__time_record_run == D_TRUE)\
                                {\
                                    D_U32 __t = d_sys_get_time() - __time_record_start;\
                                    D_DUMP(_s "::Record time %d ms AT \"%s\"(%d)\n", __t, __FILE__, __LINE__);\
                                }
#define TIME_RECORD_STOP(_s)    if(__time_record_run == D_TRUE)\
                                {\
                                    D_U32 __t = d_sys_get_time() - __time_record_start;\
                                    __time_record_run = D_FALSE;\
                                    D_DUMP(_s "::Stop time record %d ms AT \"%s\"(%d)\n", __t, __FILE__, __LINE__);\
                                }
#else
#define TIME_RECORD_START(_s)
#define TIME_RECORD_ONE(_s)
#define TIME_RECORD_STOP(_s)
#endif

#ifdef  __cplusplus
}
#endif

#endif
