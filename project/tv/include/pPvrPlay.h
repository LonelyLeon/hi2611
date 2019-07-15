/**@file
* @brief pvr���ſ���ģ��
* @author  zhuxl
* @date 2014-9-3
*/

#ifndef  _P_PVR_PLAY_H_
#define _P_PVR_PLAY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include <string.h>
#include "dTypes.h"
#include "dMedia.h"
#include "dDebug.h"
#include "dMsg.h"
#include "dFileSystem.h"
#include "dMutex.h"
#include "dMem.h"
#include "dQueue.h"
#include "dApp.h"
#include "dPvrReplay.h"


typedef enum 
{
	PVR_STATUS_STOP = 0,//��ͣ
	PVR_STATUS_PLAY,//������
	PVR_STATUS_PAUSE,//��ͣ��
	PVR_STATUS_SEEK
}D_PvrStatus;

/**@brief ��Ƶ��Ϣ*/
typedef struct
{
	D_U32 width;	//ԭʼ��
	D_U32 height;	//ԭʼ��
	D_Double totaltime;	//��ʱ��
	D_S64 filesize;	//�ļ���С���ֽ�
	D_U32 sample_rate;
	D_U32 channels;
}D_PvrInfo;





/**@brief ����pvr��Ƶ��������
*@retval �ɹ�: D_OK,  ʧ��: D_ERR
*/
D_Result d_media_pvr_open(void) D_FUNCPOSTFIT;


/**@brief �ر�pvr��Ƶ���ţ��ͷ���Դ
*@retval �ɹ�: D_OK,  ʧ��: D_ERR
*/
D_Result  d_media_pvr_close(void) D_FUNCPOSTFIT;

/**@brief ����pvr��Ƶ�ļ�
* retval �ɹ�: D_OK,  ʧ��: D_ERR
*/

D_Result d_media_pvr_play() D_FUNCPOSTFIT;

/**@brief ֹͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_stop(void) D_FUNCPOSTFIT;


/**@brief ��ͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_pause(void) D_FUNCPOSTFIT;	

/**@brief �ָ���Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_resume(void) D_FUNCPOSTFIT;

/** @brief ȡ���ļ�����Ϣ
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_pvr_rep_get_pvr_info() D_FUNCPOSTFIT;

/**@brief ��ȡ����״̬
*@retval ������Ƶö�ٽṹ��D_MovieStatus�е�ֵ
*/
D_PvrStatus d_media_pvr_get_status(void) D_FUNCPOSTFIT;


/**@brief��Ƶ��ת��һ��ָ����ʱ��㿪ʼ��������
*@param[in] pos:Ҫseek���ŵ�ʱ���
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_seek(D_U64 pos) D_FUNCPOSTFIT;


/**@brief ��ȡ��Ƶ�Ĳ��Ž���
*@retval ����ֵΪD_U32���͵Ĳ��Ž���
*/
D_U32 d_media_pvr_get_progress(void) D_FUNCPOSTFIT;


/**@brief ��ȡ��ǰ����ʱ��
*@retval ����ֵΪD_Double���͵ĵ�ǰ����ʱ��ֵ
*/
D_U32 d_media_pvr_get_curtime(void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}

#endif

#endif

