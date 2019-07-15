/** @file
* @brief ��ý������ts����ģ��
* @author ����
* @date 2019-02-22 ����: �����ļ�
*/

#ifndef _D_NETTS_REPLAY_H_
#define _D_NETTS_REPLAY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dGUI.h"
#include "dControl.h"
#include "dMedia.h"
#include "dPvrPorting.h"
#include "dPvrReplay.h"

/**@brief ���� ����ts�ļ�
*@param[in] path:������Ƶ�ļ��ľ���·��
*@param[in] id:ֱ����Ŀlist id
*@param[in] x,y,w,h:������Ƶ�Ĵ��ڴ�Сλ��
*@param[in] type: ������Ƶ���� (��Ӱ��ʱδ�� �� ts �ڼ�·��Ŀ)
*@param[in] vis:������Ƶ�ļ��������Ļ�ļ��Ļ������������ʾ��Ļ�Ŀؼ�ָ��
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_netts_play(D_Char* path, D_U32 id, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_S8 type, D_Visual *vis)D_FUNCPOSTFIT;

/**@brief ֹͣ����ts�ļ�����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_netts_stop(void)D_FUNCPOSTFIT;


/**@brief ��ȡ����ts�ļ�����״̬
*@retval ������Ƶö�ٽṹ��D_MovieStatus�е�ֵ
*/
D_MovieStatus d_media_netts_get_status(void) D_FUNCPOSTFIT;


/**@brief ��ȡ��ǰ����ʱ��
*@retval ����ֵΪD_Double���͵ĵ�ǰ����ʱ��ֵ
*/
D_Double d_media_netts_get_curtime(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
