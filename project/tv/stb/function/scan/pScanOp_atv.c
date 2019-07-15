/** @file
* @brief DVBC ???????????
* @author ??
* @date 2013-4-4 ??: ????
*/
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "dMem.h"
#include "dSys.h"
#include "dDebug.h"
#include "dScan.h"
#include "dFEnd.h"
#include "pStbScan.h"
#include "pMem.h"
#include "pConfig.h"
#include "pStb.h"
#include "pCustomConfig.h"
#include "pSIParse.h"
#include "dConfigFile.h"
#include "dAV.h"
#include "pStbFunctions.h"
#include "ptvConfig.h"

#define MAX_SEARCH_FREQ_C   874
#define MIN_SEARCH_FERQ_C   47


static D_ASGroupOp DVBC_AutoScanGroup_Op;
static D_Bool atv_play_status = D_FALSE;

#define SCAN_MEM_ALLOC(_s) d_mem_alloc(0,_s)
#define SCAN_MEM_FREE(_p) if(_p){d_mem_free(_p);_p = NULL;}
#if 1
/*freq in china*/
D_FEndFreq china_atv_freq_list[] =
{
    44250, 57750, 65750,
    77250, 85250,
    112250, 120250, 128250, 136250, 144250, 152250, 160250, 168250,
    176250, 184250, 192250, 200250, 208250, 216250, 224250, 232250,
    240250, 248250, 256250, 264250, 272250, 280250, 288250, 296250,
    304250, 312250, 320250, 328250, 336250, 344250, 352250, 360250,
    368250, 376250, 384250, 392250, 400250, 408250, 416250, 424250,
    432250, 440250, 448250, 456250, 464250,
    471250, 479250, 487250, 495250, 503250, 511250, 519250, 527250,
    535250, 543250, 551250, 559250, 567250, 575250, 583250, 591250,
    599250, 607250, 615250, 623250, 631250, 639250, 647250, 655250,
    663250, 671250, 679250, 687250, 695250, 703250, 711250, 719250,
    727250, 735250, 743250, 751250, 759250, 767250, 775250, 783250,
    791250, 799250, 807250, 815250, 823250, 831250, 839250, 847250,
    855250, 863250
};
#else
D_FEndFreq china_atv_freq_list[] =
{
    49750, 57750, 65750,
    77250, 85250,
    112250, 120250, 128250, 136250, 144250, 152250, 160250, 168250,
    176250, 184250, 192250, 200250, 208250, 216250, 224250, 232250,
    240250, 248250, 256250, 264250, 272250, 280250, 288250, 296250,
    304250, 312250, 320250, 328250, 336250, 344250, 352250, 360250,
    368250, 376250, 384250, 392250, 400250, 408250, 416250, 424250,
    432250, 440250, 448250, 456250,
    471250, 479250, 487250, 495250,
};

#endif

D_U32 china_atv_freq_cnt = sizeof(china_atv_freq_list) / sizeof(china_atv_freq_list[0]);


static D_Result
atv_scan_play_av(D_Bool play, D_FEndParam *param)
{
    if(atv_play_status != play)
    {
        if(play)
        {
            D_AVPlayParam play_param;

            play_param.mode = D_AV_PLAY_TV;
            d_av_play_while_searching(0, &play_param);
        }
        else
        {
            d_av_stop_while_searching(0);
        }
        atv_play_status = play;
    }
    return D_OK;
}

static D_Result
save_type_service(D_ScanSrvInfoNode *srvlist, D_ID *db_ts_id, D_U32 ts_cnt)
{
    D_ScanSrvInfoNode *srvnode;
    D_DBSrvInfo srvinfo;
    D_DBID dbid;

    if(!srvlist)
        return D_ERR;

    D_SI_FOR_EACH_BEGIN(D_ScanSrvInfoNode, srvlist, srvnode)
    if(!srvnode->valid || !(srvnode->srvinfo.valid))
    {
        continue;
    }
    D_DB_SRV_INFO_INIT(&srvinfo);
    D_SCANSRVINFO_TO_DBSRVINFO(&srvinfo, &(srvnode->srvinfo));

    srvinfo.srv_type = D_DB_SRV_ATV;

    if(srvnode->ts_no < ts_cnt)
    {
        srvinfo.db_ts_id = db_ts_id[srvnode->ts_no];
    }

    if(!g_custom_config.sys_setup.vol_compensate)
    {
        if(g_custom_config.scan.volume > D_STB_VOLUME_MAX)
        {
            g_custom_config.scan.volume = 0;
        }
        srvinfo.volume = g_custom_config.scan.volume;
    }

    if(srvinfo.chan_num == -1)
    {
        srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
    }

    sprintf(srvinfo.name, "ATV-%02d", srvinfo.chan_num);
    if(srvinfo.db_ts_id == -1)
    {
        //D_ERROR ("[Scan] %s srvinfo.db_ts_id == -1 !!!\n", strtype[typeid]);
    }
    else
    {
        dbid = d_dbase_insert_srv (&srvinfo);
        if (-1 == dbid)
        {
            D_ERROR ("[Scan] Cannot add new ATV service !!!\n");
        }
        else
        {
            D_DUMP("[Scan] Add ATV dbtsid: %03d dbsrvid:%03d -> num:%03d \n", srvinfo.db_ts_id, dbid, srvinfo.chan_num);
        }
    }
    D_SI_FOR_EACH_END(D_ScanSrvInfoNode, srvlist, srvnode);

    return D_OK;
}


static D_Result atv_auto_scan_init (D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    atv_play_status = D_FALSE;
    p_stb_player_stop(0);
    d_av_set_aud_mute(0, D_TRUE);
    atv_scan_play_av(D_TRUE, NULL);
    d_av_set_vid_blank(0, D_FALSE); /*黑屏*/
    return D_OK;
}

static D_Result atv_auto_scan_locked_action(D_FEndParam *param, D_Bool locked,D_U16 *cvbs_video_format)
{
    D_U8 lock_flag = 0;
    D_U8 times = 3;
    if(locked == 1)//等待判断出制式
    {
        D_AVPlayParam play_param;

        play_param.mode = D_AV_PLAY_TV;
        d_av_play_while_searching(0, &play_param);//为了重新设置播放
		
		times = 2;
        while((!lock_flag)&& times)
        {
	        d_task_wait(150);//500
	        lock_flag = d_av_getcvbslock_while_searching(0);
			
			times--;
        }          
        //lock_flag = d_av_getcvbslock_while_searching(0);

        if(lock_flag == 0)
            return D_ERR;
		
		param->atv.SoundSys = SoundSys_FmMono;
 	    //d_task_wait(500);//1000
        if(cvbs_video_format !=NULL )
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
            return D_OK;
        }
        else if(lock_flag == 2)//NTSC
        {
            param->atv.videoMode = D_VideoN;
            return D_OK;
        }
#endif
    }
	else if(locked == 2)//等待蓝屏取消
    {	
        D_AVPlayParam play_param;
		D_U8 video_mode;
        
        play_param.mode = D_AV_PLAY_TV;
	    video_mode = param->atv.videoMode;
#ifdef D_TV_IAMGE_SOURCE		
      	if(cvbs_video_format != NULL)
        {
            //存视频制式，类型为D_CVBS_Input_Mode
            play_param.tv.vid_codec = *cvbs_video_format;
        } 
#endif
        d_av_play_while_searching(0, &play_param);

         //停止播放
        d_av_Status_while_searching(0,video_mode);
 	    d_task_wait(300);//1000
        d_av_stop_while_searching(0);
    }
    else if(locked == 3)//等待蓝屏取消
    {	
        D_AVPlayParam play_param;
		D_U8 video_mode;
        
        play_param.mode = D_AV_PLAY_TV;
	video_mode = param->atv.videoMode;
#ifdef D_TV_IAMGE_SOURCE		
      	if(cvbs_video_format != NULL)
        {
            //存视频制式，类型为D_CVBS_Input_Mode
            play_param.tv.vid_codec = *cvbs_video_format;
        } 
#endif
        d_av_play_while_searching(0, &play_param);

        d_av_Status_while_searching(0,video_mode);
 	 //   d_task_wait(300);//1000
        //d_av_stop_while_searching(0);
    }
    else
    {    
        return D_ERR;
    }
	
    return D_ERR;
}

static D_Result atv_auto_scan_store(D_ScanResultValue scanResult, D_ScanTaskConfig *as_config)
{
    D_DBID dbid;
    D_ScanTsInfoNode *scants;
    D_DBTSID *db_ts_id;
    D_DBTSInfo ts_info;
    D_ATVSCAN_SET scan_set;


    /*搜索不到节目时，不删除原有节目*/
    if(0)//(scanResult.scan_tsinfo_cnt == 0 || scanResult.tv_cnt <= 0)
    {
        return D_OK;
    }

    d_dbase_set_rset_en(0);

    d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_ATV);
    d_dbase_delete_ts_by_type(D_FEND_ANALOG);

    p_tvconf_get_cur_atvscan(&scan_set);

    db_ts_id = (D_DBTSID*)SCAN_MEM_ALLOC(sizeof(D_DBTSID) * scanResult.scan_tsinfo_cnt);
    if(scanResult.scan_tsinfo_cnt && db_ts_id)
    {
        memset(db_ts_id, 0xff, sizeof(D_DBTSID) * scanResult.scan_tsinfo_cnt);

        /*存储频点信息*/
        D_SI_FOR_EACH_BEGIN(D_ScanTsInfoNode, scanResult.scan_tsinfo_list, scants)
        if(scants->valid && (scants->ts_no < scanResult.scan_tsinfo_cnt) && (scants->ts_info.tv_cnt > 0))
        {
            D_DB_TS_INFO_INIT(&ts_info);
            D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
            ts_info.tuner_type = D_FEND_ANALOG;//as_config->fend_type;
            ts_info.param.atv.fltCenterAdj = scan_set.fltCenterAdj;
            ts_info.param.atv.fltBwAdj = scan_set.fltBwAdj;

            /*添加频点，并更新频点记录集信息*/
            dbid = d_dbase_insert_ts(&ts_info);

            /*每个频点在数据库里的id*/
            db_ts_id[scants->ts_no] = dbid;

            D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", dbid, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);

        }
        D_SI_FOR_EACH_END(D_ScanTsInfoNode, scanResult.scan_tsinfo_list, scants);

        /*保存所有节目*/
        save_type_service((D_ScanSrvInfoNode *)scanResult.srvList_tv, db_ts_id, scanResult.scan_tsinfo_cnt);
    }

    SCAN_MEM_FREE(db_ts_id);

    d_dbase_flush();

    return D_OK;
}

static D_Result atv_auto_scan_destroy (D_ScanTaskConfig *as_config)
{
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
    atv_scan_play_av(D_FALSE, NULL);
    /*设置静音*/
    d_av_stop(0);//为了后面的静音效果
    p_stb_reset_mute_status();
    return D_OK;
}


D_AtvAutoScanOp ATV_AutoScan_Op =
{
    atv_auto_scan_init,
    atv_auto_scan_locked_action,//NULL,//
    atv_auto_scan_store,
    atv_auto_scan_destroy
};



/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表，此时搜索任务还没启动*/
static D_Result atv_manual_scan_init(D_ScanTaskConfig *ms_config)
{
    return D_OK;
}

/*开始搜索用户回调，此时任务已经启动，在任务回调时执行*/
static D_Result atv_manual_scan_start(D_ScanTaskConfig *ms_config)
{
    return D_OK;
}

static D_Result atv_manual_scan_store(D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    D_ScanTsInfoNode *scants;
    D_DBTSInfo ts_info;
    D_DBTSID ts_id;

    if((!ms_result) || (!(ms_result->scan_tsinfo_list)))
    {
        return D_ERR;
    }

    d_dbase_set_rset_en(0);

    scants = (D_ScanTsInfoNode*)ms_result->scan_tsinfo_list;
    D_DB_TS_INFO_INIT(&ts_info);
    D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
    ts_info.tuner_type = D_FEND_ANALOG;//ms_config->fend_type;

    ts_id = d_dbase_insert_ts(&ts_info);

    if(ms_result->tv_cnt > 0)
    {
        save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_tv, &ts_id, 1);
    }
    d_dbase_flush();
    return D_OK;
}



static D_Result atv_manual_scan_destroy(D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    return D_OK;
}

/*手动动搜索操作*/
D_AtvManualScanOp ATV_ManualScan_Op =
{
    atv_manual_scan_init,
    atv_manual_scan_start,
    atv_manual_scan_store,
    atv_manual_scan_destroy,
};






