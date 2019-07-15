/** @file
* @brief 自动频道搜索流程模块
* @author 覃宜
* @date 2013-5-17 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>

#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "dApp.h"
#include "dMMan.h"
#include "dMem.h"
#include "dSys.h"
#include "dResource.h"
#include "dTimer.h"
#include "dDebug.h"
#include "dScan.h"
#include "pStbScan.h"



#define ATV_MANUAL_SCAN_PRINT_EN 1
#define  START_FREQ		(44250)//(49750)
#define  END_FREQ 		(869750)

#define SEND_MSG(_a,_b,_c)  d_queue_send(_a, _b, _c)

/*向上层应用发送进度消息*/
#define SEND_PROGRESS_MSG()\
{\
    smsg.type = D_MSG_SCAN_PROGRESS;\
    smsg.hscan = d_app_self ();\
    smsg.progress = atv_ms->progress;\
    smsg.prog_cnt = atv_ms->atv_ms_lock_cnt;\
    SEND_MSG (atv_ms->atv_ms_hq, (D_U8*)&smsg, sizeof (smsg));\
}

/*去锁定频点*/
#define atv_ms_scan_lock()\
{\
    smsg.type = D_MSG_SCAN_TRY_LOCK;\
    smsg.hscan = d_app_self ();\
    SEND_MSG (d_app_get_queue(d_app_self ()), (D_U8*)&smsg, sizeof (smsg));\
}

/*向上层应用发送开始一个频点的搜索消息*/
#define SEND_SCAN_FREQ_MSG(_freq)\
{\
    smsg.type = D_MSG_SCAN_FREQ;\
    smsg.hscan = d_app_self ();\
    smsg.fendparam.atv.freq = _freq;\
    smsg.progress = atv_ms->progress;\
    SEND_MSG (atv_ms->atv_ms_hq, (D_U8*)&smsg, sizeof (smsg));\
}

#define ATV_CHECK_AUDIO_MODE(_mode) (_mode < D_AudioMax)
#define ATV_CHECK_VIDEO_MODE(_mode) (_mode < D_VideoMax)

/*空间定义*/
#define P_ATV_MANUAL_SCAN_BUF_SIZE_MIN        64*1024 /*搜索任务最小内存*/
#define P_ATV_MANUAL_SCAN_DATA_BUF      16*1024 /*其它数据空间*/

#define P_ATV_AV_MODE_CNT (16)

/*自动搜索数据结构定义*/
typedef struct
{
    D_U32               scan_type;
    D_U32               scan_mode;
    D_HFMan             hfman;
    D_FEndParam         param;          /*上层传入的频点参数*/
    D_U8                *atv_ms_buf;
    D_HMMan             atv_ms_hmm;
    D_HQueue            atv_ms_hq;
    D_HFEnd             hfend;
    D_FEndParam         current_fendparam;  /*当前正在搜索的频点参数*/
    D_FEndType          current_fendtype;   /*当前正在搜索的频点类型*/

    D_FEndParam         atv_fendparam;      /*节目实际频点参数，即校正后的参数*/
    
    D_U16               cvbs_video_format;  /*cvbs模块返回的视频制式*/
    
    D_U32               atv_ms_lock_cnt;        /*锁定的频点数*/
    D_U8                atv_ms_progress;
    D_U32               atv_ms_prog_cnt;
    D_Bool              send_progress_enable;
    D_U8                progress, send_progress;
    D_ScanResultValue   scanResult;
    D_FEndFreq          freq_curr;
    D_FEndFreq          freq_step;
    D_FEndFreq          freq_bw;
    D_FEndFreq          freq_start;     /*起始频率*/
    D_FEndFreq          freq_end;       /*结束频率*/

    D_FEndFreq          freq_offset;
    D_Bool 		blind_flag;
    D_Bool              curr_locked;
/*按频率表搜索时用到*/
    D_FEndFreq          *freq_list;
    D_U32               freq_list_cnt;
    D_U32               freq_list_id;

    D_U32               freq_start_id;
    D_Bool              scan_updown_flag;

    D_U32       audiomode_cnt;
    D_U32       videomode_cnt;
    D_AudioMode audiomode[P_ATV_AV_MODE_CNT];
    D_VideoMode videomode[P_ATV_AV_MODE_CNT];

    D_ScanTaskConfig    atv_ms_config;      /*任务配置参数*/
    D_AtvAutoScanOp     *AScanOp;       /*注册的自动搜索的操作*/
    D_Bool destroy_flag;
} P_ATVMsData;

//static D_HApp HAtvManualScan = D_INVALID_HANDLE;


/*将搜索的结果发送到gui，可用于显示*/
static D_Result atv_ms_send_end_msg(P_ATVMsData *atv_ms)
{
    D_ScanMsg        smsg;

    smsg.type = D_MSG_SCAN_OK;
    smsg.hscan = d_app_self ();
    smsg.progress = 100;
    smsg.prog_cnt = atv_ms->atv_ms_lock_cnt;

    SEND_MSG (atv_ms->atv_ms_hq, (D_U8*)&smsg, sizeof (smsg));

    return D_OK;
}

extern D_U16 ProgScanning;

/** @brief 向gui发送消息(搜索到的节目)，
菜单里根据此消息刷新搜索到的节目名称列表。*/
static D_Result atv_ms_send_srv(P_ATVMsData *atv_ms, D_ScanSrvInfo *srvinfo, D_FEndParam *param)
{
    D_ScanMsg        msg;
    D_DBSrvInfo info;

    if(!atv_ms || !srvinfo)
        return D_ERR;
    D_DB_SRV_INFO_INIT(&info);
    D_SCANSRVINFO_TO_DBSRVINFO(&info, srvinfo);

    msg.srvinfo = info;
    msg.fendparam = *param;
    msg.prog_cnt = atv_ms->atv_ms_prog_cnt;
    msg.tv_cnt = atv_ms->atv_ms_prog_cnt;
    msg.progress = atv_ms->progress;
    msg.type = D_MSG_SCAN_DATA;
    msg.hscan = d_app_self ();
    /*发送节目消息*/
    SEND_MSG (atv_ms->atv_ms_hq, (D_U8*)&msg, sizeof (msg));

    return D_OK;
}

/*模拟搜索时保存一个节目(频点)*/
static D_Result atv_ms_analog_add_srv(P_ATVMsData *atv_ms, D_FEndParam *param)
{
    D_ScanSrvInfo   srvinfo;
	D_U8 vid_codec;
	D_U8 aud1_codec;
    
    param->atv.mode = 0;

    D_SCAN_SRV_INFO_INIT(&srvinfo);
    srvinfo.valid = 1;
    if(param->atv.videoMode == D_VideoP)
    {
        srvinfo.vid_codec = D_VID_CODEC_PAL;
    }
    else if(param->atv.videoMode == D_VideoN)
    {
        srvinfo.vid_codec = D_VID_CODEC_NTSC;
    }
    else if(param->atv.videoMode == D_VideoSECAM)
    {
        srvinfo.vid_codec = D_VID_CODEC_SECAM;
    }
    else
    {
        srvinfo.vid_codec = D_VID_CODEC_PAL;
    }

    if(param->atv.audioMode == D_AudioBG)
    {
        srvinfo.aud1_codec = D_AUD_CODEC_BG;
    }
    else if(param->atv.audioMode == D_AudioDK)
    {
        srvinfo.aud1_codec = D_AUD_CODEC_DK;
    }
    else if(param->atv.audioMode == D_AudioI)
    {
        srvinfo.aud1_codec = D_AUD_CODEC_I;
    }
    else
    {
        srvinfo.aud1_codec = D_AUD_CODEC_M;
    }
    atv_ms_send_srv(atv_ms, &srvinfo, param);

    return D_OK;
}
static D_Result atv_scan_getcvbslock(D_FEndParam *param,D_U16 *cvbs_video_format)
{
    D_U8 lock_flag = 0;
    D_U8 times = 3;

    D_AVPlayParam play_param;

    play_param.mode = D_AV_PLAY_TV;
    d_av_play_while_searching(0, &play_param);
	
    lock_flag = d_av_getcvbslock_while_searching(0);

    if(lock_flag == 0)
        return D_ERR;
	d_task_wait(1000);
    if(cvbs_video_format != NULL )
    {
        *cvbs_video_format = lock_flag;
    }
#ifdef D_TV_IAMGE_SOURCE
    if((lock_flag == D_CVBS_PAL)||(lock_flag == D_CVBS_Y_50)||(lock_flag == D_CVBS_PAL_M))//PAL
    {       
	   param->atv.videoMode = D_VideoP;
        if(cvbs_video_format != NULL )
		{
            *cvbs_video_format = D_VID_CODEC_PAL;
		}
       return D_OK;
    }
    else if((lock_flag == D_CVBS_NTSC)||(lock_flag == D_CVBS_NTSC_M)||(lock_flag == D_CVBS_Y_60))
    {
		param->atv.videoMode = D_VideoN;
        if(cvbs_video_format != NULL )
		{
            *cvbs_video_format = D_VID_CODEC_NTSC;
		}
        return D_OK;
    }
#else
    if(lock_flag == 1)//PAL
    {       
        param->atv.videoMode = D_VideoP;
        if(cvbs_video_format != NULL )
        {
            *cvbs_video_format = D_VID_CODEC_PAL;
        }
		return D_OK;
    }
    else if(lock_flag == 2)//NTSC
    {
        param->atv.videoMode = D_VideoN;
        if(cvbs_video_format != NULL )
        {
            *cvbs_video_format = D_VID_CODEC_NTSC;
        }
        return D_OK;
    }
#endif
    return D_ERR;
}

//等待播出画面
static D_Result atv_scan_wait_resume(D_U8 mode,D_U16 video_format)
{
    D_U8 lock_flag = 0;
    D_U8 times = 3;
    D_AVPlayParam play_param;
    play_param.tv.vid_codec = video_format;
    play_param.mode = D_AV_PLAY_TV;
    d_av_play_while_searching(0, &play_param);
	d_av_Status_while_searching(0,mode);
	d_av_stop_while_searching(0);

    return D_ERR;
}
/*尝试锁定一个频点*/
static D_Bool
atv_ms_param_lock(P_ATVMsData *atv_ms, D_FEndParam fendparam)
{
    D_Bool locked = D_FALSE;
    D_FEndStatus status;
    D_U32 a_n, v_n;

    for(v_n = 0; v_n < atv_ms->videomode_cnt; v_n++)
    {
        if(! ATV_CHECK_VIDEO_MODE(atv_ms->videomode[v_n]))
        {
            continue;
        }

        for(a_n = 0; a_n < atv_ms->audiomode_cnt; a_n++)
        {
            if(! ATV_CHECK_AUDIO_MODE(atv_ms->audiomode[a_n]))
            {
                continue;
            }

            fendparam.atv.mode = 1;
            fendparam.atv.videoMode = (D_U8)atv_ms->videomode[v_n];
            fendparam.atv.audioMode = (D_U8)atv_ms->audiomode[a_n];
            d_fman_set_param_direct(atv_ms->hfman, &fendparam, 0);
            memset(&status, 0x00, sizeof(status));
            d_fman_get_status_direct(atv_ms->hfman, &status);
            if(status.locked == D_TRUE)
            {
                locked = D_TRUE;
                atv_ms->atv_fendparam = fendparam;
                if(status.ptr)
                {
                    /*取得tuner锁定的频点*/
                    memcpy(&(atv_ms->atv_fendparam), status.ptr, sizeof(atv_ms->atv_fendparam));
                    /*重新锁定，校正频偏*/
                    if(D_ABS((int)atv_ms->atv_fendparam.freq - (int)fendparam.freq) >= atv_ms->freq_offset)
                    {
                        locked = D_FALSE;
                        atv_ms->atv_fendparam.atv.mode = 1;
                        d_fman_set_param_direct(atv_ms->hfman, &(atv_ms->atv_fendparam), 0);
                        memset(&status, 0x00, sizeof(status));
                        d_fman_get_status_direct(atv_ms->hfman, &status);
                        if(status.locked == D_TRUE)
                        {
                            locked = D_TRUE;
                            if(status.ptr)
                            {
                                memcpy(&(atv_ms->atv_fendparam), status.ptr, sizeof(atv_ms->atv_fendparam));
                            }
                        }
                    }
                }
            }
        }
    }

    return locked;
}

/*盲扫驱动回调
action = 0，判断是否还要搜索；
action = 1，向任务发送进度及频率 param为进度值
*/
static D_Result atv_manual_blind_callback(D_U8 action, D_U32 cur_freq)
{
	D_ScanMsg smsg;
	D_U32 progress;

	if(ProgScanning == 0 || d_app_self () == D_INVALID_HANDLE)
	{
		return D_ERR;
	}

	if(action == 1)
	{
		cur_freq = 250*((cur_freq+50)/250);
		smsg.type = D_MSG_SCAN_FREQ;
		smsg.hscan = d_app_self ();
		smsg.fendparam.atv.freq = cur_freq;
		SEND_MSG (d_gui_get_queue(), (D_U8*)&smsg, sizeof (smsg));
	}	
	return D_OK;
}

/*模拟搜索时保存一个节目(频点)*/
static D_Result atv_manual_analog_add_srv(P_ATVMsData *atv_as, D_FEndParam *param)
{
    D_ScanTsInfoNode *scants;
    D_ScanSrvInfo   srvinfo;
    D_ScanSrvInfoNode   *srvnode;
		
	D_U8 vid_codec;
	D_U8 aud1_codec;
	
    D_SI_ALLOC(atv_as->atv_ms_hmm, scants);
    if(!scants)
    {
        return D_ERR;
    }
    D_SCAN_TS_INFO_INIT(&(scants->ts_info));
    scants->ts_no = atv_as->scanResult.tv_cnt;
    scants->valid = D_TRUE;

    memcpy(&(scants->ts_info.param), param, sizeof(D_FEndParam));
	D_DUMP("param freq =%d",param->atv.freq);
	D_DUMP("scants->ts_info.param =%d",scants->ts_info.param.atv.freq);
    scants->ts_info.param.atv.mode = 0;
    scants->ts_info.param.atv.SoundSys = SoundSys_FmMono;

    D_SI_LIST_ADD((atv_as->scanResult.scan_tsinfo_list), scants);

    atv_as->scanResult.scan_tsinfo_cnt++;
    atv_as->scanResult.prog_cnt++;
    atv_as->atv_ms_prog_cnt++;

    D_SCAN_SRV_INFO_INIT(&srvinfo);
    srvinfo.valid = 1;	
	aud1_codec = param->atv.audioMode;
	vid_codec = param->atv.videoMode;
    
    if((atv_as->cvbs_video_format != D_CVBS_UNLOCK)||(atv_as->cvbs_video_format != D_CVBS_UNDEFINE))
    {
        srvinfo.vid_codec = atv_as->cvbs_video_format;
    }
    else
    {
	    srvinfo.vid_codec = vid_codec;
    }
	srvinfo.aud1_codec = aud1_codec;
	scants->ts_info.param.atv.videoMode = param->atv.videoMode;
	scants->ts_info.param.atv.audioMode = param->atv.audioMode;

    D_SI_ALLOC(atv_as->atv_ms_hmm, srvnode);
    if(srvnode)
    {
        srvnode->valid = 1;
        srvnode->ts_no = scants->ts_no;
        srvinfo.srv_type = D_DB_SRV_TV;
        srvnode->srvinfo = srvinfo;

        D_SI_LIST_ADD(atv_as->scanResult.srvList_tv, srvnode);
        scants->ts_info.tv_cnt++;
        atv_as->scanResult.tv_cnt++;
    }
    atv_ms_send_srv(atv_as, &srvinfo, param);
    return D_OK;
}

/*中断特定参数的盲扫*/
static D_Result atv_manual_blind_stop(P_ATVMsData *atv_as)
{
	D_ScanMsg smsg;
	D_Result ret = D_ERR;

	/*不再接中断的消息*/
	if(atv_as->blind_flag)
	{
		//atv_as->curr_locked = D_FALSE;		
		d_fman_blind_set_param_direct(atv_as->hfman, D_FEND_STOP, NULL,NULL);
		ProgScanning = 0;
	}
	atv_as->blind_flag = D_FALSE;
	//atv_as_scan_end();
	return ret;
}

static D_Result atv_manual_blind_start (P_ATVMsData *atv_ms)
{
	D_U32       		id, i, step, step_len, freq_id;
	D_FEndFreq  		freq,start_freq,end_freq;
	D_ScanMsg 		smsg;
	D_U16 			cvbs_video_format = D_CVBS_UNLOCK;
	D_FBlindParam	blindparam={0};
	D_Result 			ret = D_ERR;
	D_FEndParam 	param;

	ProgScanning = 1;

	if(atv_ms->scan_updown_flag)
	{
		blindparam.startfreq = atv_ms->freq_curr+4000;
		if( blindparam.startfreq >= END_FREQ )
		{
			blindparam.startfreq= START_FREQ;
		}
		blindparam.stopfreq = atv_ms->freq_end;
		atv_ms->blind_flag = D_TRUE;
		blindparam.ptr = atv_manual_blind_callback;
		while(1)
		{
			if(atv_ms->destroy_flag)
			{
				break;
			}

			ret =  d_fman_blind_set_param_direct(atv_ms->hfman, D_FEND_START, &param, &blindparam);
			if(ret == D_FEND_START_OK)
			{

				/*将要搜索的频点发送到gui，用于显示*/
				param.atv.freq = 250*((param.atv.freq+50)/250);
				SEND_SCAN_FREQ_MSG(param.atv.freq);

				if( (param.atv.videoMode == atv_ms->atv_ms_config.fend_param.atv.videoMode )&&\
					( param.atv.audioMode == atv_ms->atv_ms_config.fend_param.atv.audioMode))
				{
					atv_ms_analog_add_srv(atv_ms, &param);
					break;
				}
				else
				{
					blindparam.startfreq = param.atv.freq+4000;
					blindparam.stopfreq = END_FREQ;
				}
			}
			else
			{
				blindparam.startfreq = START_FREQ;
				blindparam.stopfreq = END_FREQ;
			}
			d_task_wait(10);
		}
	}
	else
	{
		blindparam.startfreq = atv_ms->freq_curr-8000;
		if( blindparam.startfreq <= atv_ms->freq_start )
		{
			blindparam.startfreq = END_FREQ;
		}
		blindparam.stopfreq = atv_ms->freq_start;
		atv_ms->blind_flag = D_TRUE;
		blindparam.ptr = atv_manual_blind_callback;
		while(1)
		{
			if(atv_ms->destroy_flag)
			{
				break;
			}

			ret =  d_fman_blind_set_param_direct(atv_ms->hfman, D_FEND_LAST, &param, &blindparam);
			if(ret == D_FEND_START_OK)
			{

				/*将要搜索的频点发送到gui，用于显示*/
				param.atv.freq = 250*((param.atv.freq+50)/250);
				SEND_SCAN_FREQ_MSG(param.atv.freq);
			
				if( (param.atv.videoMode == atv_ms->atv_ms_config.fend_param.atv.videoMode )&&\
					( param.atv.audioMode == atv_ms->atv_ms_config.fend_param.atv.audioMode))
				{
					atv_ms_analog_add_srv(atv_ms, &param);
					break;
				}	
				else
				{
					blindparam.startfreq = param.atv.freq-8000;
					blindparam.stopfreq = START_FREQ;
				}
			}
			else
			{
				blindparam.startfreq = END_FREQ;
				blindparam.stopfreq = START_FREQ;
			}
			d_task_wait(10);
		}		
	}

	/*结束搜索*/
	atv_manual_blind_stop(atv_ms);

	ProgScanning = 0;
	
	d_task_wait(5);
	
	return D_OK;
}

/** @brief 锁定频点*/
static D_Result atv_ms_lock (P_ATVMsData *atv_ms)
{
    D_U32       id, i, step, step_len, freq_id;
    D_ScanMsg smsg;
    D_FEndFreq  freq;
    D_U16 cvbs_video_format = D_CVBS_UNLOCK;
    if(1)//(atv_ms->scan_type == D_ATV_SCAN_TYPE_AUTO)
    {
        for(id = 0; id < atv_ms->freq_list_cnt; id++)
        {
            /*用户销毁任务，不再搜索*/
            if(atv_ms->destroy_flag)
            {
                break;
            }

            if(atv_ms->scan_updown_flag)
            {
                freq_id = (id + atv_ms->freq_start_id) % atv_ms->freq_list_cnt;
            }
            else
            {
                freq_id = (atv_ms->freq_start_id + atv_ms->freq_list_cnt - id) % atv_ms->freq_list_cnt;
            }

            if(id && freq_id == atv_ms->freq_start_id)
            {
                break;
            }

            /*将搜索的进度发送到gui，可用于显示*/
            atv_ms->progress = (D_U8)(id * 100 / atv_ms->freq_list_cnt);

            freq = atv_ms->freq_list[freq_id];
            /*将要搜索的频点发送到gui，用于显示*/
            SEND_SCAN_FREQ_MSG(freq);

            if(atv_ms->send_progress_enable && (atv_ms->send_progress != atv_ms->progress))
            {
                SEND_PROGRESS_MSG();
                atv_ms->send_progress = atv_ms->progress;
            }

            step_len = (atv_ms->freq_bw >> 1) / atv_ms->freq_step + 1;
            for(i = 0; i < step_len; i++)
            {

                freq = atv_ms->freq_list[freq_id] + i * atv_ms->freq_step;
                atv_ms->current_fendparam.atv.freq = freq;

                if(D_TRUE == atv_ms_param_lock(atv_ms, atv_ms->current_fendparam))
                {
					if(atv_scan_getcvbslock(&atv_ms->atv_fendparam,&cvbs_video_format)==D_OK)
                	{               	      
	                	atv_ms->atv_fendparam.atv.mode = 0;
                        atv_ms->cvbs_video_format = cvbs_video_format;
                     #ifndef D_TV_IAMGE_SOURCE
						if(atv_ms->atv_fendparam.atv.videoMode == D_VideoN)
							atv_ms->atv_fendparam.atv.audioMode = D_AudioM;         
						d_fman_set_param_direct(atv_ms->hfman, &(atv_ms->atv_fendparam), 0);
                     #endif
                        atv_scan_wait_resume(atv_ms->atv_fendparam.atv.videoMode,cvbs_video_format);
						atv_ms->atv_ms_lock_cnt ++;
						return D_OK;
                	}
                }

                if(i)
                {
                    freq = atv_ms->freq_list[freq_id] - i * atv_ms->freq_step;
                    atv_ms->current_fendparam.atv.freq = freq;
                    if(D_TRUE == atv_ms_param_lock(atv_ms, atv_ms->current_fendparam))
                    {
	                	if(atv_scan_getcvbslock(&atv_ms->atv_fendparam,&cvbs_video_format)==D_OK)
	                	{
		                	atv_ms->atv_fendparam.atv.mode = 0;
                            atv_ms->cvbs_video_format = cvbs_video_format;
                        #ifndef D_TV_IAMGE_SOURCE
							if(atv_ms->atv_fendparam.atv.videoMode == D_VideoN)
								atv_ms->atv_fendparam.atv.audioMode = D_AudioM;
							d_fman_set_param_direct(atv_ms->hfman, &(atv_ms->atv_fendparam), 0);
                        #endif
	                        atv_scan_wait_resume(atv_ms->atv_fendparam.atv.videoMode,cvbs_video_format);
							atv_ms->atv_ms_lock_cnt ++;
							return D_OK;
                		}
                    }
                }
                d_task_wait(2);
                /*用户销毁任务，不再搜索*/
                if(atv_ms->destroy_flag)
                {
                    break;
                }
            }
        }
        d_task_wait(5);
    }
    return D_ERR;
}

/** @brief 开始自动搜索，数据初始化*/
static P_ATVMsData* atv_ms_start (D_ScanTaskConfig config)
{
    D_U8            *buf;
    D_HMMan      hmm;
    P_ATVMsData *atv_ms;
    D_AtvScanParam *pscanparam;

    if(config.buf_size < P_ATV_MANUAL_SCAN_BUF_SIZE_MIN)
    {
        config.buf_size = P_ATV_MANUAL_SCAN_BUF_SIZE_MIN;
    }

    buf = (D_U8*) d_mem_alloc (0, config.buf_size);
    if (! buf)
    {
        return NULL;
    }

    hmm = d_mman_create (buf, config.buf_size, D_MMAN_SIMPLE);
    if (D_INVALID_HANDLE == hmm)
    {
        d_mem_free (buf);
        return NULL;
    }

    atv_ms = (P_ATVMsData*) d_mman_alloc (hmm, sizeof (P_ATVMsData));
    if (! atv_ms)
    {
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }

    memset(atv_ms, 0, sizeof(P_ATVMsData));

    /*记录参数*/
    atv_ms->atv_ms_buf = buf;
    atv_ms->atv_ms_hmm = hmm;

    atv_ms->atv_ms_hq = config.hqueue;
    atv_ms->hfman = d_fman_get_handle_by_type(config.fend_type, 0);
    /*同步一次fman，因为模拟搜索时直接调用fend的接口，因此要让fman调用的运行结束*/
    d_app_sync (atv_ms->hfman);

    atv_ms->atv_ms_config = config;
    atv_ms->AScanOp = (D_AtvAutoScanOp*)config.pScanOp;
    atv_ms->current_fendparam = atv_ms->atv_ms_config.fend_param;
    atv_ms->scan_type = atv_ms->atv_ms_config.scan_type;
    atv_ms->freq_start = atv_ms->atv_ms_config.startfreq;
    atv_ms->freq_curr = config.fend_param.freq;
    atv_ms->freq_end = atv_ms->atv_ms_config.endfreq;
    atv_ms->freq_bw = atv_ms->atv_ms_config.bandwitch;
    atv_ms->freq_step = atv_ms->atv_ms_config.stepfreq;
    atv_ms->freq_offset = 250;//by hgex

    atv_ms->send_progress_enable = atv_ms->atv_ms_config.sdt_srv_type_en;
    atv_ms->scan_updown_flag = atv_ms->atv_ms_config.Reserved;

    pscanparam = (D_AtvScanParam *)(atv_ms->atv_ms_config.pReserved);
    if(pscanparam)
    {
        D_ID idx;

        atv_ms->audiomode_cnt = D_MIN(P_ATV_AV_MODE_CNT, pscanparam->audiomode_cnt);
        atv_ms->videomode_cnt = D_MIN(P_ATV_AV_MODE_CNT, pscanparam->videomode_cnt);
        memcpy(atv_ms->audiomode, pscanparam->audiomode, (atv_ms->audiomode_cnt * sizeof (D_AudioMode)));
        memcpy(atv_ms->videomode, pscanparam->videomode, (atv_ms->videomode_cnt * sizeof (D_VideoMode)));

#ifndef D_TV_IAMGE_SOURCE
        if(pscanparam->freq_cnt && pscanparam->freq_list)
        {
            atv_ms->freq_list_cnt = pscanparam->freq_cnt;
            atv_ms->freq_list = (D_FEndFreq*) d_mman_alloc (hmm, (atv_ms->freq_list_cnt * sizeof (D_FEndFreq)));
            memcpy(atv_ms->freq_list, pscanparam->freq_list, (atv_ms->freq_list_cnt * sizeof (D_FEndFreq)));
        }

        if(atv_ms->scan_updown_flag)
        {
            atv_ms->freq_start_id = 0;
            for(idx = 0; idx < atv_ms->freq_list_cnt; idx++)
            {
                if(pscanparam->freq_list[idx] > atv_ms->current_fendparam.atv.freq)
                {
                    atv_ms->freq_start_id = idx;
                    break;
                }
            }
		}
		else
		{
            atv_ms->freq_start_id = atv_ms->freq_list_cnt - 1;
            for(idx = (atv_ms->freq_list_cnt - 1); idx >= 0; idx--)
            {
                if(pscanparam->freq_list[idx] < atv_ms->current_fendparam.atv.freq)
                {
                    atv_ms->freq_start_id = idx;
					break;
				}
			}
		}
#else
	 atv_ms->freq_list_cnt = (atv_ms->freq_end - atv_ms->freq_start)/4;
#endif
        atv_ms->audiomode[0] = (D_AudioMode)(pscanparam->audiomode[0]);
        atv_ms->audiomode_cnt = 1;
        atv_ms->videomode[0] = (D_VideoMode)(pscanparam->videomode[0]);
        atv_ms->videomode_cnt = 1;
    }

    if(atv_ms->audiomode_cnt == 0)
    {
        atv_ms->audiomode[0] = (D_AudioMode)(atv_ms->current_fendparam.atv.audioMode);
        atv_ms->audiomode_cnt = 1;
    }

    if(atv_ms->videomode_cnt == 0)
    {
        atv_ms->videomode[0] = (D_VideoMode)(atv_ms->current_fendparam.atv.videoMode);
        atv_ms->videomode_cnt = 1;
    }


    return atv_ms;
}

/** @brief 存储自动搜索数据*/
static D_Result atv_ms_store (P_ATVMsData *atv_ms)
{
//  AS_DUMP("\n[AtvManualScan] atv_ms_store   :\n");
    return D_OK;
}


/** @brief 结束自动搜索,释放资源*/
static D_Result atv_ms_destroy (P_ATVMsData *atv_ms)
{
    D_MManInfo minfo;

    /*自定义的操作*/
    if((atv_ms->AScanOp) && (atv_ms->AScanOp->auto_scan_destroy))
    {
        atv_ms->AScanOp->auto_scan_destroy(&(atv_ms->atv_ms_config));
    }
	
    if (atv_ms->atv_ms_hmm != D_INVALID_HANDLE)
    {
//        d_mman_get_info(atv_ms->atv_ms_hmm, &minfo);
//      AS_DUMP ("[AtvManualScan] memory size %x, free %x\n", minfo.size, minfo.free_size);
        d_mman_destroy (atv_ms->atv_ms_hmm);
        atv_ms->atv_ms_hmm = D_INVALID_HANDLE;
    }

    atv_manual_blind_stop(atv_ms);

    if (atv_ms->atv_ms_buf)
    {
        d_mem_free (atv_ms->atv_ms_buf);
    }

    return D_OK;
}

/** @brief 自动搜索消息回调函数*/
static D_Result atv_ms_callback (D_Msg *msg)
{
    D_ScanMsg        smsg;
    P_ATVMsData     *atv_ms;

    atv_ms = (P_ATVMsData *)d_app_get_data (d_app_self ());

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            atv_ms = (P_ATVMsData *) msg->app.arg;
            d_app_set_data (d_app_self (), (D_Ptr) atv_ms);
            atv_ms_scan_lock();
            break;
        case D_MSG_SCAN_TRY_LOCK:
	     #ifdef D_TV_IAMGE_SOURCE
            if(D_OK == atv_manual_blind_start(atv_ms))
            {
               //atv_ms_analog_add_srv(atv_ms, &(atv_ms->atv_fendparam));
            }
	     #else
            if(D_OK == atv_ms_lock(atv_ms))
            {
               atv_ms_analog_add_srv(atv_ms, &(atv_ms->atv_fendparam));
            }
	     #endif
            atv_ms_send_end_msg(atv_ms);
            break;
        case D_MSG_APP_DESTROY:
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 开始手动搜索
* @param config 搜索配置
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_HScan p_atv_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT
{
    P_ATVMsData *atv_ms;
    D_HApp       happ;

    D_INFO("[AtvManualScan] create\n");

    if (D_INVALID_HANDLE == config.hqueue)
    {
        return D_INVALID_HANDLE;
    }

    /*开始自动搜索，分配空间并初始化*/
    if (! (atv_ms = atv_ms_start (config)))
    {
        return D_INVALID_HANDLE;
    }

    /*启动应用*/
    happ = d_app_create ("AtvManualScan", config.priority, D_AUTO_SCAN_TASK_STACK_SIZE, D_AUTO_SCAN_QUEUE_SIZE, atv_ms_callback, (D_Ptr) atv_ms);

    if (D_INVALID_HANDLE == happ)
    {
        atv_ms_destroy (atv_ms);
        return happ;
    }
    
    return happ;
}

/** @brief 结束手动搜索
* @param hscan  搜索句柄
* @param store  是否存储搜索结果
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result p_atv_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT
{
    P_ATVMsData *atv_ms;

    atv_ms = (P_ATVMsData*) d_app_get_data (hscan);
    if (! atv_ms)
    {
        return D_ERR;
    }

    atv_ms->destroy_flag = D_TRUE;
    ProgScanning = 0;
    d_app_destroy ((D_HApp) hscan);
    if (store)
    {
        atv_ms_store (atv_ms);
    }

    atv_ms_destroy (atv_ms);

    D_INFO("[AtvManualScan] destroy\n");

    return D_OK;
}




