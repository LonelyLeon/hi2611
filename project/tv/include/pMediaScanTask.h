/** @file
* @brief 多媒体扫描任务模块
* @author
* @date 2018.01.08: 建立文件
**/
#ifndef  _P_MEDIA_H_
#define  _P_MEDIA_H_

#include "pFile_Scan.h"
#include "dTypes.h"
#include "dVisEvent.h"



#ifdef  __cplusplus
extern "C"
{
#endif


typedef enum
{
	CIRCLE_PLAY_MODE = 0,
	ORDER_PLAY_MODE,
	RAND_PLAY_MODE,
	LOOP_ONE_PLAY_MODE
}MEDIA_PLAY_MODE;
D_Result p_media_usb_plug_msg_process(D_U8 plug,D_U8 arg);
D_Result p_media_hotplug_rset(D_U8 plug,D_U8 arg);
D_Result p_media_delete_all_rset(void);
D_Result p_media_begin_deal(void);
D_U32 p_media_get_filescan_task_state(void);

#ifdef  __cplusplus
}
#endif

#endif

