/** @file
* @brief TVģ��
* @author ����
* @date 2006-5-18 ����: �����ļ�
	@date 2006-8-2 shanzs: �������ֺ�ͼƬ��洦��
		����d_tv_set_pic_param����
		����d_tv_set_pic_ratio����
* @date 2013-05-16 lc: ͳһƽ̨, ��������
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

/** @brief ����ts�����Ź��ܣ����ý�Ŀ���Ų�������ts_scramble_para == NULLʱ�����ͷ��ڴ�*/
void d_suma_ts_scramble_set_para (TS_SCRAMBLE_PARA  *ts_scramble_para);


#ifdef  __cplusplus
}
#endif

#endif
