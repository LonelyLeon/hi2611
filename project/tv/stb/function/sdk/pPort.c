/** @file
* @brief Port
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#include "dPort.h"
#include "dMem.h"
#include "dSem.h"
#include "dTask.h"
#include "dMutex.h"
#include "dEvent.h"
#include "dQueue.h"
#include "dTimer.h"
#include "dSys.h"
#include "dSerial.h"
#include "dSCI.h"
#include "dFEnd.h"
#include "dDemux.h"
#include "dAV.h"
#include "dDsc.h"
#include "dNVRam.h"
#include "dEEPRom.h"
#include "dMMan.h"
#include "dMsg.h"
#include "dDebug.h"
#include "dCBMan.h"
#include "dtesttool.h"
#include "dRTCTimer.h"
#include "dPowerOff.h"
#include "pConfig.h"

#include <string.h>

#include "pMem.h"
#include "pCustomConfig.h"

/* 以下四个变量将会在汇编引导代码中被赋值 */
D_U32 SystemPartitionBaseAddress;
D_U32 SystemPartitionTotalSize;
D_U32 AvMemPartitionBaseAddress;
D_U32 AvMemPartitionTotalSize;

#ifdef D_DEBUG
#define LPS_PREC		8
#define HZ				1000
#define jiffies			d_sys_get_time()

static void __inline__ __delay(register D_U32 loops) D_FUNCPOSTFIT
{
	for(;loops != 0;loops --);
}

#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
static D_Bool BogoCmd(parse_t *parse_p, char *result_p) D_FUNCPOSTFIT
{
	D_U32 loops_per_jiffy = (1<<12);
	unsigned long ticks, loopbit;
	int lps_precision = LPS_PREC;
	
	while ((loops_per_jiffy <<= 1) != 0) {
		/* wait for "start of" clock tick */
		ticks = jiffies;
		while (ticks == jiffies)
			/* nothing */;
		/* Go .. */
		ticks = jiffies;
		__delay(loops_per_jiffy);
		ticks = jiffies - ticks;
		if (ticks)
			break;
	}

	/*
		* Do a binary approximation to get loops_per_jiffy set to
		* equal one clock (up to lps_precision bits)
	*/
	loops_per_jiffy >>= 1;
	loopbit = loops_per_jiffy;
	while (lps_precision-- && (loopbit >>= 1)) {
		loops_per_jiffy |= loopbit;
		ticks = jiffies;
		while (ticks == jiffies)
			/* nothing */;
		ticks = jiffies;
		__delay(loops_per_jiffy);
		if (jiffies != ticks)	/* longer than 1 tick */
			loops_per_jiffy &= ~loopbit;
	}

	D_INFO("%lu.%02lu BogoMIPS (lpj=%lu)\n",
			loops_per_jiffy/(500000/HZ),
			(loops_per_jiffy/(5000/HZ)) % 100, loops_per_jiffy);
			
	return D_FALSE;
}
#endif
#endif

#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
#if defined(D_SYSTEM_HROS)
extern void btrace_debug_open(void);
#endif
static void TestToolTask(D_Ptr p)
{
	HRTST_Start();
#if defined(D_SYSTEM_HROS)
	d_sys_reboot();
#else
	exit(1);
#endif
}
#endif

/** @brief 定时器回调函数*/
static D_Result
timer_callback (D_HTimer htimer, D_Handle handle) D_FUNCPOSTFIT
{
	D_TimerMsg	msg;
	
	if (handle == D_INVALID_HANDLE)
		return D_ERR;
	
	msg.type = D_MSG_TIMER;
	msg.htimer = htimer;
	
	return d_queue_try_send (handle, (D_U8*)&msg, sizeof (msg));
}

D_Result p_port_init(void) D_FUNCPOSTFIT
{
    D_SysOpenParam sys_open_param;
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    TESTTOOL_InitParams_t TST_InitParams;
#endif
    D_EEPRomOpenParam e2p_open_param;
    D_Int i;

    /* 设置打印级别 */
    d_dbg_set_level((D_DbgLevel)D_DEBUG_LEVEL);

    /* 系统初始化 */
    sys_open_param.clock.cpu_freq = 333000000;
    
#if defined(D_SYSTEM_HROS)|| defined(D_SYSTEM_WIN32)
    sys_open_param.memory.sys_mem_addr = SystemPartitionBaseAddress;
    sys_open_param.memory.sys_mem_size = SystemPartitionTotalSize;
    sys_open_param.memory.av_mem_addr = AvMemPartitionBaseAddress;
    sys_open_param.memory.av_mem_size = AvMemPartitionTotalSize;
#elif defined(D_SYSTEM_LINUX)
    sys_open_param.memory.sys_mem_addr = 0;
    sys_open_param.memory.sys_mem_size = 0;
    sys_open_param.memory.av_mem_addr = 0x6700000;//0x2f00000
    sys_open_param.memory.av_mem_size =0x9900000;//0x5100000
#else
#   error "内存布局需要根据OS来配置!"
#endif

    sys_open_param.memory.av_mem_block_cnt = 300;

    sys_open_param.kernel.time_slice = 1000;
    
#ifdef D_GAMA_TEST
    sys_open_param.uart_print.uart_no = -1;//(D_S8)D_DEBUG_TO_UART;
#else
    sys_open_param.uart_print.uart_no = (D_S8)D_DEBUG_TO_UART;
#endif
    sys_open_param.uart_print.baudrate = 115200;
    
    d_sys_open(&sys_open_param);
#if defined(D_SYSTEM_HROS)    
	 d_sys_watchdog_feeddog(5000,1,1);//feed watchdog正常调试要注掉
#endif	
    d_rtc_timer_open();

#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    memset(&TST_InitParams, 0, sizeof(TESTTOOL_InitParams_t));
    TST_InitParams.NbMaxOfSymbols = 500;


    if(HRTST_Init(&TST_InitParams))
    {
        D_ERROR("HRTST_Init()=Failed\n");
    }

	HRTST_SetMode(HRTST_INTERACTIVE_MODE);
#if defined(D_SYSTEM_HROS)
    btrace_debug_open();
#endif
    HRTST_RegisterCommand("BOGO", BogoCmd, "BogoMIPS");
#endif
    
	d_sem_open();
	d_mutex_open();
	d_cbman_open();
	d_mman_open();
	d_event_open();
	d_queue_open();
	d_task_open();
	d_timer_open();
    d_nvram_open();

    project_mem_init();
    /*
        加载用户配置, 需要用到内存分配和读flash, 目前
        只能放到系统初始化和flash初始化后面
    */
    p_custom_config_load();
    p_custom_config_dump();

    e2p_open_param.type = D_EEProm_Fake;
    e2p_open_param.size = D_EEPROM_RECOMMEND_SIZE; /* 虚拟设备使用推荐大小 */
    e2p_open_param.u.fake.nvram_offset_1 = (p_custom_config_get_app_offset() & ~(D_SPECIAL_BLOCK_SIZE - 1)) - D_SPECIAL_BLOCK_SIZE;
    e2p_open_param.u.fake.nvram_offset_2 = e2p_open_param.u.fake.nvram_offset_1 - D_SPECIAL_BLOCK_SIZE;
    e2p_open_param.u.fake.nvram_block_size = D_SPECIAL_BLOCK_SIZE;
    
	d_eeprom_open(&e2p_open_param);
    
	d_serial_open();
	d_dbg_open();
#ifndef D_DEBUG
    d_dbg_set_io_func(NULL, NULL);
#endif


#if   D_CA_SUPPORT_DEF
   d_sci_open_ex();
#ifdef D_CA_SUPPORT_DVNCA
    d_sci_set_param_ex (0, NULL) ;//为了设置smart卡特殊工作模式，目前只有天柏CA需要设置
#endif
#endif

    d_iic_open_ex();


    /**优先设置DEMUX初始化，MPEG_SYS如果未能使能，将导致HI_TS_CTRL_REG等系统层寄存器不能设置*/
    d_demux_open();
    d_fend_open_ex();
	
#ifdef HI_SOFT_TYPE_DVBS
    d_fend_register_hi3111();
    //d_fend_register_hi3701CVBS();
#else
#if (defined(D_ARCH_HI2610D))
	d_fend_register_hi3205_inside();
	d_fend_register_hi3700();
    d_fend_register_hi3308_inside();
#elif (defined(D_ARCH_HI2610E))
	d_fend_register_hi3205_inside();
	d_fend_register_hi3701();
	d_fend_register_hi3308E();
	d_fend_register_hi3701CVBS();
#endif
#endif
    d_av_open_ex();
    
	d_dsc_open();
	
	/*注册回调函数*/
	d_timer_register_callback(timer_callback, NULL);

#ifdef D_DEBUG
	//BogoCmd(NULL, NULL);
#endif
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    {
        D_TaskAttr ta;

        ta.id = 0;
        ta.name = "tool";
        ta.priority = 15;
        ta.stack_size = 8192;

        d_task_create(&ta, TestToolTask, NULL);
    }
#endif
	d_PowerOff_open();
	return D_OK;
}

