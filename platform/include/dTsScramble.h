/** @file
* @brief TV模块
* @author 龚克
* @date 2006-5-18 龚克: 建立文件
	@date 2006-8-2 shanzs: 增加文字和图片广告处理
		增加d_tv_set_pic_param函数
		增加d_tv_set_pic_ratio函数
* @date 2013-05-16 lc: 统一平台, 代码整理
*/

#ifndef _D_TS_SCRAMBLE_H_
#define _D_TS_SCRAMBLE_H_

#ifdef  __cplusplus
extern "C"
{
#endif


#include "dTypes.h"

typedef  struct  
{
      D_U8  scrambling_enable;
      D_U8  continuity_counter;
      D_U8  ts_package_number;
      D_U8  scrambling_algorithm;
      D_U8  scrambling_value;
      D_U8  video_scramble;
      D_U8  audio_scramble;
      D_U16 video_pid;
      D_U16 audio_pid;    
}TS_SCRAMBLE_PARA;

/** @brief 数码ts包加扰功能，设置节目加扰参数，当ts_scramble_para == NULL时，才释放内存*/
void d_suma_ts_scramble_set_para (TS_SCRAMBLE_PARA  *ts_scramble_para);


#ifdef  __cplusplus
}
#endif

#endif
