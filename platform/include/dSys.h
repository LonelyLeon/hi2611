/** @file
* @brief ϵͳ����
* @author ����
* @date 2005-5-16 ����: �����ļ�
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

/** @brief ϵͳ��ģ��ʱ������ */
typedef struct
{
    D_U32 cpu_freq;     /**< ��CPUʱ�� */
}D_ClockCfg;

/** @brief ϵͳ�ڴ����� */
typedef struct
{
    D_U32 sys_mem_addr; /**< ����d_mem_alloc()������ڴ����ַ,ͨ��ӳ��Ϊcache�ڴ� */
    D_Size sys_mem_size;/**< ����d_mem_alloc()������ڴ��С */
    D_U32 av_mem_addr;  /**< ����HRAvMemAllocateBlock()������ڴ����ַ,ͨ�����豸�����ڴ�,ӳ��Ϊnoncache�ڴ� */
    D_Size av_mem_size;  /**< ����HRAvMemAllocateBlock()������ڴ��С */
    D_Size av_mem_block_cnt;/**< HRAvMemAllocateBlock()�ɷ���������� */
}D_SysMemCfg;

/** @brief OS������� */
typedef struct
{
    D_S32 time_slice;   /**< ʱ��Ƭ��ת���ȵ�ʱ��Ƭ, tick��λ */
}D_KernelCfg;

/** @brief ��ӡ���� */
typedef struct
{
    D_S8 uart_no;       /**< uart��(0,1...);-1Ϊ��Ч,��ʾ�������ڴ�ӡ */
    D_U32 baudrate;     /**< ������ */
}D_UartPrintCfg;

/** @brief ϵͳ��ʼ���ṹ */
typedef struct
{
    D_ClockCfg clock;
    D_SysMemCfg memory;
    D_KernelCfg kernel;
    D_UartPrintCfg uart_print;
}D_SysOpenParam;

/** @brief ϵͳ��ַ���� */
typedef enum
{
    D_SysAddr_Cached = 0,
    D_SysAddr_UnCached,
    D_SysAddr_Phys,
}D_SysAddressType;

/** @brief ϵͳ��ʼ��
*
*	���������ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_sys_open (D_SysOpenParam *param) D_FUNCPOSTFIT;

/** @brief ϵͳ��ֹ
*
* �������ʱ���ͷ�ϵͳ��Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_sys_close (void) D_FUNCPOSTFIT;

/** @brief ȡ�ô�ϵͳ����������ʱ������ʱ��
* @return	�Ժ���Ϊ��λ��ϵͳʱ��
*/
D_U32	d_sys_get_time (void) D_FUNCPOSTFIT;

/** @brief ϵͳ��������
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
void	d_sys_reboot (void) D_FUNCPOSTFIT;
/** @brief    ������⣬�ǵ�һ���ϵ绹�Ǵ�������
* @param[in]  void
* @retvalflag 0:��һ���ϵ磬1:�������ѣ�2��MCUû��Ӧ��
*/
D_U8 d_sys_power_mode(void)D_FUNCPOSTFIT;

/** @brief ϵͳ����,����ڵ�״̬
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_sys_stand_by (void) D_FUNCPOSTFIT;

/** @brief	ϵͳ�ӹ���״̬�ָ�
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_sys_wake_up (void) D_FUNCPOSTFIT;

/** @brief ��Cache�е�����ˢ�µ�SDRAM��*/
D_Result	d_sys_cache_flush (void) D_FUNCPOSTFIT;

/** @brief ȡ��ϵͳÿ���tick��λ
* @return	ϵͳÿ���tick
*/
D_U32	d_sys_get_tick_per_sec (void) D_FUNCPOSTFIT;

/** @brief ȡ�ô�ϵͳ����������ʱ������ʱ��
* @return	��tickΪ��λ��ϵͳʱ��
*/
D_U32	d_sys_get_tick (void) D_FUNCPOSTFIT;

/** @brief ��Cache�е�ָ������ˢ�µ�SDRAM��*/
D_Result d_sys_cache_flush_range (D_Ptr from_addr, D_U32 size) D_FUNCPOSTFIT;

/** @brief ����ַӳ���ָ����ַ����
* @param[in] type  ָ���ĵ�ַ����
* @param[in] addr  Ҫת���ĵ�ַ
* @param[in] size  Ҫӳ��ĵ�ַ��Χ��С
* @return  ת����ĵ�ַ
*/
D_Ptr d_sys_map_address(D_SysAddressType type, D_Ptr addr, D_U32 size) D_FUNCPOSTFIT;

/** @brief �ͷ�ӳ���ĵ�ַ
* @param[in] mapped_addr ӳ���ַ
*/
void d_sys_unmap_address(D_Ptr mapped_addr) D_FUNCPOSTFIT;

/** @brief �����豸�ڴ�
* @param[in] size Ҫ������ڴ��С
* @return �����������ַ
*/
D_Ptr d_sys_alloc_dev_mem(D_Size size, D_U32 align) D_FUNCPOSTFIT;

/** @brief �ͷŷ�����豸�ڴ�
* @param[in] dev_addr �豸�ڴ��ַ
*/
void d_sys_free_dev_mem(D_Ptr dev_addr) D_FUNCPOSTFIT;

void d_sys_set_atvclock(float frq,D_S16 offset) D_FUNCPOSTFIT;
void d_sys_watchdog_feeddog(D_U32 TimeOutMs, D_U8 Reset, D_U8 Interrupt) D_FUNCPOSTFIT;


/** @brief ��ȡdemod��Ҫʹ�õ��ڴ�
* @param 
*/
D_Result d_sys_get_demod_mem(D_U32 id,D_U32 *addr,D_U32 *length)D_FUNCPOSTFIT;
/** @brief ��ȡdemod��Ҫʹ�õ��ڴ�
* @param 
*/
D_Result d_sys_release_demod_mem(D_U32 addr)D_FUNCPOSTFIT;
/** @brief ���оƬ�Ƿ��ǿ��Ź���λ
* @param 
*/
D_Result d_sys_check_watchdog_reset(void)D_FUNCPOSTFIT;


/** @brief ���üĴ���ֵ
* @param 
*/
D_Result d_sys_set_reg(D_U32 addr, D_U8 value,D_U8 mask)D_FUNCPOSTFIT;

/** @brief ��ȡ�Ĵ���ֵ
* @param 
*/
D_U8 d_sys_get_reg(D_U32 addr)D_FUNCPOSTFIT;

/** @brief ������3700��ص�ϵͳ�Ĵ���
* @param[in] NULL
*/
void d_sys_3700reg_set(void) D_FUNCPOSTFIT;

D_U8 d_sys_check_CVBS_signal(D_U8 flag) D_FUNCPOSTFIT;

/** @brief ������3701CVBS��ص�ϵͳ�Ĵ���
* @param[in] NULL
*/
void d_sys_3701CVBSreg_set(D_U8 flag,D_U8 mode) D_FUNCPOSTFIT;

/** @brief ������3701��ص�ϵͳ�Ĵ���
* @param[in] NULL
*/
void d_sys_3701reg_set(void) D_FUNCPOSTFIT;

void ADC_FIFO_RESET(void) D_FUNCPOSTFIT;

/** @brief ������3205��ص�ϵͳ�Ĵ���
* @param[in] NULL
*/
void d_sys_3205reg_set(void) D_FUNCPOSTFIT;

/** @brief 3308E���ϵͳ����
* @param[in] NULL
*/
void d_sys_3308Ereg_set(void) D_FUNCPOSTFIT;


/** @brief ������dtbm��ص�ϵͳ�Ĵ���
* @param[in] NULL
*/
void d_sys_dtmb_reg_set(void) D_FUNCPOSTFIT;


/** @brief ��ʱ��ӡ�� */
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
