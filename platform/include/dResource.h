/** @file
* @brief 资源定义
* @author 龚克
* @date 2005-7-1 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 整理代码
*/

#ifndef _D_RESOURCE_H_
#define _D_RESOURCE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

#define K	(1024)
#define M	(K*K)


/*任务优先级*/
#define D_MAIN_TASK_PRIO						5
#define D_FP_TASK_PRIO							14
#define D_RC_TASK_PRIO							6
#define D_AV_TASK_PRIO							6
#define D_TV_TASK_PRIO							6
#define D_TEST_TASK_PRIO						4
#define D_TEST_TASK_1_PRIO					    4
#define D_TEST_TASK_2_PRIO					    4
#define D_TIMER_TASK_PRIO						4
#define D_DEMUX_TASK_PRIO						4//8
#define D_PIP_TASK_PRIO                         3//liuxz added for "pip test"
#define D_FMAN_TASK_PRIO						7
#define D_AUTO_SCAN_TASK_PRIO				    8
#define D_MANUAL_SCAN_TASK_PRIO			        6
#define D_EPG_SCAN_TASK_PRIO				    4
#define D_SUBT_TASK_PRIO						4
#define D_TTXT_TASK_PRIO						4
#define D_CA_TASK_PRIO							8
#define D_MEDIA_PICTURE_TASK_PRIO				3
#define D_MEDIA_MUSIC_TASK_PRIO				    3
#define D_MEDIA_MOVIE_TASK_PRIO				    1 //3
#define D_MEDIA_EBK_TASK_PRIO					    3
#define D_MEDIA_MOVIE_DECODE_TASK_PRIO			4
#define D_DBASE_TASK_PRIO						4
#define D_DB_TASK_PRIO							2
#define D_DB_DEMUX_TASK_PRIO				    2
#define D_FP_164TASK_PRIO						14
#define D_FP_TM1618ATASK_PRIO					7
#define D_FP_FD650KTASK_PRIO					7
#define D_EEPROM_FLUSH_TASK_PRIO				6
#define D_FILE_SYSTEM_PROBE_TASK_PRIO           3
#define D_USB_UPGRADE_TASK_PRIO           		4
#define D_RS232_UPGRADE_TASK_PRIO               4
#define D_INTERRUPT_TASK_PRIO					15

#define D_PVR_REPLAY_TASK_PRIO					1 //4	// add by yulz
#define D_PVR_REC_TASK_PRIO					4//caig  for  test
#define D_NEND_DRIVER_TASK_PRIO                 10
#define D_AD_MODULE_TASK_PRIO					3
#define D_USB_HCD_POLLING_TASK_PRIO             1

/*任务栈空间*/
#define D_MAIN_TASK_STACK_SIZE			(64*K)
#define D_FP_TASK_STACK_SIZE				(4*K)
#define D_RC_TASK_STACK_SIZE				(4*K)
#define D_AV_TASK_STACK_SIZE				(4*K)
#define D_TV_TASK_STACK_SIZE				(4*K)
#define D_TEST_TASK_STACK_SIZE			(4*K)
#define D_TEST_TASK_1_STACK_SIZE		(4*K)
#define D_TEST_TASK_2_STACK_SIZE		(4*K)
#define D_TIMER_TASK_STACK_SIZE			(4*K)
#define D_DEMUX_TASK_STACK_SIZE			(4*K)
#define D_DEMUX_TASK_1_STACK_SIZE		(4*K)
#define D_FMAN_TASK_STACK_SIZE			(4*K)
#define D_AUTO_SCAN_TASK_STACK_SIZE	(4*K)
#define D_MANUAL_SCAN_TASK_STACK_SIZE			(4*K)
#define D_EPG_SCAN_TASK_STACK_SIZE	(4*K)
#define D_PROG_SCAN_TASK_STACK_SIZE	(4*K)
#define D_SUBT_TASK_STACK_SIZE			(4*K)
#define D_TTXT_TASK_STACK_SIZE			(4*K)
#define D_CA_TASK_STACK_SIZE				(8*K)
#define D_MEDIA_PICTURE_TASK_STACK_SIZE   (4*K)
#define D_MEDIA_MUSIC_TASK_STACK_SIZE   (4*K)
#define D_MEDIA_MOVIE_TASK_STACK_SIZE   (4*K)
#define D_MEDIA_EBK_TASK_STACK_SIZE   (4*K)
#define D_MEDIA_MOVIE_DECODE_TASK_STACK_SIZE   (4*K)
#define D_DBASE_TASK_STACK_SIZE			(4*K)
#define D_DB_TASK_STACK_SIZE				(96*K)
#define D_DB_DEMUX_TASK_STACK_SIZE	(32*K)
#define D_PIP_TASK_STACK_SIZE			(4*K)//PIP任务调用栈
#define D_EEPROM_FLUSH_TASK_STACK_SIZE	(4*K)
#define D_FILE_SYSTEM_PROBE_TASK_STACK_SIZE (4*K)
#define D_USB_UPGRADE_TASK_STACK_SIZE	(4*K)
#define D_RS232_UPGRADE_TASK_STACK_SIZE	(4*K)
#define D_SERIAL_MONI_TASK_STACK_SIZE	(16*K)
#define D_PVR_REPLAY_TASK_STACK_SIZE	(4*K)	// PVR REPLAY task add by yulz
#define D_PVR_REC_TASK_STACK_SIZE	    (32*K)//	(4*K)//16k  caig test 
#define D_TTX_SCAN_TASK_STACK_SIZE	(4*K)
#define D_NEND_DRIVER_TASK_STACK_SIZE   (8*K)
#define D_AD_MODULE_TASK_STACK_SIZE		(32*K)
#define D_USB_HCD_POLLING_TASK_STACK_SIZE (4*K)

/*消息队列大小*/
#define D_MAIN_QUEUE_SIZE						(32*K)
#define D_FP_QUEUE_SIZE							(1*K)
#define D_RC_QUEUE_SIZE							(1*K)
#define D_AV_QUEUE_SIZE							(1*K)
#define D_TV_QUEUE_SIZE							(8*K)
#define D_TEST_QUEUE_SIZE						(1*K)
#define D_TEST_QUEUE_1_SIZE					(1*K)
#define D_TEST_QUEUE_2_SIZE					(1*K)
#define D_TIMER_QUEUE_SIZE					(1*K)
#define D_DEMUX_QUEUE_SIZE					(1*K)
#define D_DEMUX_QUEUE_1_SIZE				(1*K)
#define D_FMAN_QUEUE_SIZE						(1*K)
#define D_AUTO_SCAN_QUEUE_SIZE			(8*K)
#define D_MANUAL_SCAN_QUEUE_SIZE		(1*K)
#define D_EPG_SCAN_QUEUE_SIZE				(8*K)
#define D_PROG_SCAN_QUEUE_SIZE			(1*K)
#define D_SUBT_QUEUE_SIZE						(1*K)
#define D_TTXT_QUEUE_SIZE						(1*K)
#define D_CA_QUEUE_SIZE							(1*K)
#define D_MEDIA_PICTURE_QUEUE_SIZE			(1*K)
#define D_MEDIA_MUSIC_QUEUE_SIZE			(1*K)
#define D_MEDIA_MOVIE_QUEUE_SIZE			(1*K)
#define D_MEDIA_EBK_QUEUE_SIZE			(1*K)
#define D_MEDIA_MOVIE_DECODE_QUEUE_SIZE		(1*K)
#define D_DB_QUEUE_SIZE							(1*K)
#define D_DB_DEMUX_QUEUE_SIZE				(1*K)
#define D_USBUPGRADE_QUEUE_SIZE              (1*K)
#define D_RS232UPGRADE_QUEUE_SIZE              (1*K)
#define D_SERIAL_MONI_QUEUE_SIZE              (1*K)
#define D_PVR_REPLAY_QUEUE_SIZE				(1*K)// PVR REPLAY task add by yulz
#define D_PVR_REC_QUEUE_SIZE				(1*K)
#define D_TTX_SCAN_QUEUE_SIZE				(8*K)
#define D_AD_MODULE_QUEUE_SIZE              (8*K)


#ifdef  __cplusplus
}
#endif

#endif
