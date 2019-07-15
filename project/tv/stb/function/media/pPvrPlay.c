/** @file 
*@brief pvr���ſ���ģ��
* @author zhuxl
* @date 2014-9-3
*/

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
#include "dDsc.h"
#include "pPvrPlay.h"


/*******************************************************************************************************/
/***************************************ȫ�ֱ�����������*/
/*******************************************************************************************************/

static D_HPvrRep  Pvr_Rep_Handle = D_INVALID_HANDLE;

/*******************************************************************************************************/
/***************************************��������*/
/*******************************************************************************************************/

/**@brief ����pvr��Ƶ��������
*@retval �ɹ�: D_OK,  ʧ��: D_ERR
*/
D_Result d_media_pvr_open(void) D_FUNCPOSTFIT
{
	d_pvr_rep_open();
	return D_OK;
}


/**@brief �ر�pvr��Ƶ���ţ��ͷ���Դ
*@retval �ɹ�: D_OK,  ʧ��: D_ERR
*/
D_Result  d_media_pvr_close(void) D_FUNCPOSTFIT
{
	d_pvr_rep_close();
	return D_OK;
}

/**@brief ����pvr��Ƶ�ļ�
* retval �ɹ�: D_OK,  ʧ��: D_ERR
*/
D_Result d_media_pvr_play(D_Char* path) D_FUNCPOSTFIT
{
	D_Char* ch_pos;
	D_PvrRepTaskConfig pvr_config={0};

	d_pvr_rep_open();
	Pvr_Rep_Handle = d_pvr_rep_create();

	ch_pos = strrchr(path, '/');
	memcpy(pvr_config.filepath, path, (ch_pos + 1 - path));
	strcpy(pvr_config.filename, ch_pos+1);
	ch_pos = strrchr(pvr_config.filename, '.');
	*ch_pos = '\0';

	pvr_config.ts_type = PVR_REP_HAIER_TS;
	d_pvr_rep_set_param_ptr(Pvr_Rep_Handle, &pvr_config);
	
	d_pvr_rep_start(Pvr_Rep_Handle);

	return D_OK;
	
}

/**@brief ֹͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_stop(void) D_FUNCPOSTFIT
{
	d_pvr_rep_stop(Pvr_Rep_Handle);
	d_pvr_rep_destroy(Pvr_Rep_Handle);
	d_pvr_rep_close();
	Pvr_Rep_Handle = D_INVALID_HANDLE;

	return D_OK;
}


/**@brief ��ͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_pause(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_pause(Pvr_Rep_Handle);
}

/**@brief �ָ���Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_resume(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_resume(Pvr_Rep_Handle);
}

/** @brief ȡ���ļ�����Ϣ
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_pvr_rep_get_pvr_info(D_Char* path, D_PvrInfo* PvrInfo) D_FUNCPOSTFIT
{
	D_Char* ch_pos;
	D_PvrRepTaskConfig pvr_config={0};


	d_pvr_rep_open();
	Pvr_Rep_Handle = d_pvr_rep_create();

	ch_pos = strrchr(path, '/');
	memcpy(pvr_config.filepath, path, (ch_pos + 1 - path));
	strcpy(pvr_config.filename, ch_pos+1);
	ch_pos = strrchr(pvr_config.filename, '.');
	*ch_pos = '\0';

	pvr_config.ts_type = PVR_REP_HAIER_TS;
	d_pvr_rep_set_param_ptr(Pvr_Rep_Handle, &pvr_config);


	PvrInfo->totaltime = (D_Double)d_pvr_rep_get_total_time(Pvr_Rep_Handle);
    PvrInfo->filesize = (D_S64)d_pvr_rep_get_file_size(Pvr_Rep_Handle);

	d_app_sync(Pvr_Rep_Handle);

	d_media_pvr_stop();

	return D_OK;
}

/**@brief ��ȡ����״̬
*@retval ������Ƶö�ٽṹ��D_MovieStatus�е�ֵ
*/
D_PvrStatus d_media_pvr_get_status(void) D_FUNCPOSTFIT
{
	D_PvrStatus pvr_state;
	D_PvrTaskState pvr_stat = d_pvr_rep_get_state(Pvr_Rep_Handle);

	switch(pvr_stat)
	{
	        case PVR_READY_OK:
	        case PVR_PLAYING:
	            pvr_state = PVR_STATUS_PLAY;
	            break;
	        case PVR_PAUSE:
	            pvr_state = PVR_STATUS_PAUSE;
	            break;
	        case PVR_STOP:
	        case PVR_INVALID:
	        default:
	            pvr_state = PVR_STATUS_STOP;
	            break;
	}

	return pvr_state;
}

/**@brief��Ƶ��ת��һ��ָ����ʱ��㿪ʼ��������
*@param[in] pos:Ҫseek���ŵ�ʱ���
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_pvr_seek(D_U64 pos) D_FUNCPOSTFIT
{
	return d_pvr_rep_set_jump(Pvr_Rep_Handle, (D_U32)pos);
}


/**@brief ��ȡ��ǰ����ʱ��
*@retval ����ֵΪD_Double���͵ĵ�ǰ����ʱ��ֵ
*/
D_U32 d_media_pvr_get_curtime(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_get_time(Pvr_Rep_Handle);
}

/**@brief ��ȡ��Ƶ�Ĳ��Ž���
*@retval ����ֵΪD_U32���͵Ĳ��Ž���
*/
D_U32 d_media_pvr_get_progress(void) D_FUNCPOSTFIT
{
	return d_pvr_rep_get_progress(Pvr_Rep_Handle);
}

