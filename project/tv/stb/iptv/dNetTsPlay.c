/** @file
* @brief ¶àÃœÌåÍøÂçts²¥·ÅÄ£¿é
* @author ñûÒË
* @date 2019-02-22 ñûÒË: œšÁ¢ÎÄŒþ
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dSys.h"
#include "dResource.h"
#include "dAV.h"
#include "dDebug.h"
#include "dCBMan.h"
#include "dMutex.h"
#include "dMem.h"
#include "dSI.h"
#include "dDescr.h"
#include "dGUI.h"
#include "dControl.h"
#include "dMedia.h"
#include "dApp.h"
#include "dPvrPorting.h"
#include "dPvrReplay.h"
#include "dNetTsPlay.h"
#include "rbuf.h"
#include "_helper.h"

#include "auth.h"

#define NETTS_PVR_REP_BUFFER_SIZE     (1*M)
#define NETTS_PVR_REP_BUFFER_ALIGN    (1*K)
#define NETTS_MIN_REP_LENGTH          (128*K) //replay buff wp limit size,for interrupting 
#define NETTS_MIN_VCD_SPACE           (256*K) //1024byte����
#define NETTS_MIN_ACD_SPACE           (4*K)   //1024byte����

#define NETTS_WAIT_DATA_SIZE           (128*K) // С�ڴ�ֵʱ��ʼ����
#define NETTS_PLAY_DATA_SIZE           (2048*K)   // ���ڴ�ֵʱ��ʼ����

#define NETTS_PLAY_RBUF_SIZE           (2*M)   // rbuf size


typedef struct
{
    D_U16 pid;
    D_U16 type;
} iptv_pidinfo;

typedef struct
{
    D_HApp hnetts_play; /* appŸä±ú*/

    D_ID dev_id;
    D_U8 *rep_buf_nc;
    D_U8 *rep_buf;
    D_U8 *rep_buf_phys;
    D_Bool running;
    D_HSem notify;
    D_PvrIntMask PvrReplayIntStatus;
    D_PvrRepTsParm ts_parm;
    D_PvrHandle hPvr;

    D_U32 recv_packet_cnt;
    D_U32 last_recv_packet_cnt;

    D_Bool get_ts_play_param;

    iptv_pidinfo pidinfo[5]; // 0 pcr, 1 video, 2.. audio
    D_Bool find_pmt;
    D_U16 pmt_pid;
    D_Bool video_ok;  /*ÊÇ·ñÒÑŸ­œâ³öÊÓÆµ*/
    D_Bool audio_ok;  /*ÊÇ·ñÒÑŸ­œâ³öÒôÆµ*/
    D_Bool pause;
    D_U32 wait_progress;  /*�������*/
    D_U32 last_check_time;

    D_U32 si_data_size;
    D_U32 si_data_wp;
    D_U32 si_data_rp;
    D_U32 si_data_total_size;

    D_Time start_play_time;
    D_U32 last_play_duration;

    D_U8 * rbuf_buf;
    D_U32 rbuf_size;
    HidrvRbuf rbuf;
} D_TSPLAYDATA;

static D_HMutex hmutex_tsplay = D_INVALID_HANDLE;
static D_Bool net_tsplay_open = D_FALSE;

#define __tsplay_lock() if(hmutex_tsplay != D_INVALID_HANDLE){d_mutex_lock(hmutex_tsplay);}
#define __tsplay_unlock() if(hmutex_tsplay != D_INVALID_HANDLE){d_mutex_unlock(hmutex_tsplay);}

static D_TSPLAYDATA *tsplay_data = NULL;
static D_Handle tsplay_pvr_rep_int_handle = D_INVALID_HANDLE;
static D_Handle tsplay_av_evt_handle = D_INVALID_HANDLE;
static D_U8  is_change_channel = D_TRUE;

extern volatile D_U8 is_loading;

static void _NetTsRepIntCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_PvrIntReason reason = (D_PvrIntReason)obj_data;

    if(tsplay_data && (reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow)))
    {
        tsplay_data->PvrReplayIntStatus = (D_PvrIntMask)(reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow));
    }
}

static void _NetTsAvDrvEventCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    if(tsplay_data)
    {
        D_AVEventParam *param = (D_AVEventParam*)obj_data;
        D_DUMP("%s:%d-----evt %x\n", __FUNCTION__, __LINE__, (int)param->evt);

        if(param->evt == D_AV_EVT_NEW_PIC_START)
        {
            tsplay_data->video_ok = D_TRUE;
            d_av_set_vid_blank(0, D_FALSE);
			d_av_set_aud_mute(0, D_FALSE);
        }
        else if(param->evt == D_AV_EVT_NEW_AUD_START)
        {
            tsplay_data->audio_ok = D_TRUE;
        }
    }
}

static D_Result tsplay_open(void) D_FUNCPOSTFIT
{
    int i;
    D_DUMP("########tsplay_open######## \n");

    tsplay_data = (D_TSPLAYDATA*)d_mem_alloc(0, sizeof(D_TSPLAYDATA));
    if(!tsplay_data)
        return D_ERR_NO_SPACE;

    if(hmutex_tsplay == D_INVALID_HANDLE)
    {
        hmutex_tsplay = d_mutex_create(NULL);
    }

    memset(tsplay_data, 0x00, sizeof(D_TSPLAYDATA));
    tsplay_pvr_rep_int_handle = D_INVALID_HANDLE;
    tsplay_av_evt_handle = D_INVALID_HANDLE;
    tsplay_data->hnetts_play = D_INVALID_HANDLE;
    tsplay_data->notify = D_INVALID_HANDLE;
    tsplay_data->hPvr = D_INVALID_HANDLE;
    tsplay_data->dev_id = 0;

    tsplay_data->find_pmt = 0;
    tsplay_data->pmt_pid = 0x1FFF;
    for(i = 0; i < (sizeof(tsplay_data->pidinfo) / sizeof(tsplay_data->pidinfo[0])); i++)
    {
        tsplay_data->pidinfo[i].pid = 0x1FFF;
        tsplay_data->pidinfo[i].type = 0;
    }

    tsplay_data->pause = D_TRUE;
    tsplay_data->wait_progress = 0;

    tsplay_data->rep_buf_nc = (D_U8*)d_sys_alloc_dev_mem(NETTS_PVR_REP_BUFFER_SIZE, NETTS_PVR_REP_BUFFER_ALIGN);
    if(!tsplay_data->rep_buf_nc)
    {
        d_mutex_destroy(hmutex_tsplay);
        hmutex_tsplay = D_INVALID_HANDLE;
        d_mem_free(tsplay_data);
        tsplay_data = NULL;
        D_ERROR("Cannot alloc rep_buf_nc\n");
        return D_ERR_NO_SPACE;
    }

    tsplay_data->rep_buf = (D_U8*)d_sys_map_address(D_SysAddr_Cached, tsplay_data->rep_buf_nc, NETTS_PVR_REP_BUFFER_SIZE);
    tsplay_data->rep_buf_phys = (D_U8*)d_sys_map_address(D_SysAddr_Phys, tsplay_data->rep_buf_nc, NETTS_PVR_REP_BUFFER_SIZE);

    tsplay_data->rbuf.ops = hidrv_rbuf_default_ops;
    tsplay_data->rbuf_size = NETTS_PLAY_RBUF_SIZE;
    tsplay_data->rbuf_buf = (D_U8*)d_mem_alloc(0, NETTS_PLAY_RBUF_SIZE);
    hidrv_rbuf_init(&(tsplay_data->rbuf), (const void * )tsplay_data->rbuf_buf, (int)tsplay_data->rbuf_size);
    hidrv_rbuf_set_wp(&(tsplay_data->rbuf), 0);
    hidrv_rbuf_set_rp(&(tsplay_data->rbuf), 0);

    D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
    return D_OK;
}

static D_Result tsplay_start(void) D_FUNCPOSTFIT
{
    D_PvrRepDev repdev = {0};
    D_PvrRepAttr attr = {0};

    //tsplay_data->notify = d_sem_create(NULL);
    tsplay_data->running = D_TRUE;
    D_DUMP("########tsplay_start######## \n");
    repdev.param.repbuf_baseaddr        = (D_U32)tsplay_data->rep_buf_phys;
    repdev.param.repbuf_size            = NETTS_PVR_REP_BUFFER_SIZE;
    repdev.param.min_rep_len            = NETTS_MIN_REP_LENGTH;
    repdev.param.min_acd_space          = NETTS_MIN_ACD_SPACE;
    repdev.param.min_vcd_space          = NETTS_MIN_VCD_SPACE;
    repdev.param.TV_num                 = tsplay_data->dev_id;
    repdev.param.rep_interrupt_state    = 0;

    d_pvr_porting_open();
    d_pvr_porting_rep_open();
    tsplay_data->hPvr = d_pvr_porting_rep_create(attr, &repdev);
    if(tsplay_data->hPvr == D_INVALID_HANDLE)
    {
        D_ERROR("Cannot create porting replay\n");
        return D_ERR;
    }

    tsplay_av_evt_handle = d_cbman_subscribe(PL_AV_CALLBACK, D_INVALID_HANDLE, _NetTsAvDrvEventCallback, (D_Ptr)tsplay_data);
    tsplay_pvr_rep_int_handle = d_cbman_subscribe(PL_INTERRUPT_PVR, D_INVALID_HANDLE, _NetTsRepIntCallback, (D_Ptr)tsplay_data);

    d_pvr_porting_rep_restart(tsplay_data->hPvr);
    d_pvr_porting_rep_start(tsplay_data->hPvr, &tsplay_data->ts_parm);
    tsplay_data->pause = D_FALSE;
    //d_pvr_porting_rep_pause(tsplay_data->hPvr);
    //tsplay_data->pause = D_TRUE;

    D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
    return D_OK;
}

static D_Result tsplay_close(void) D_FUNCPOSTFIT
{
     D_DUMP("########tsplay_close######## \n");
   if(tsplay_data == NULL)
    {
        return D_OK;
    }
    __tsplay_lock();
    net_tsplay_open = D_FALSE;
    tsplay_data->running = D_FALSE;
    if(tsplay_data->notify != D_INVALID_HANDLE)
    {
        d_sem_destroy(tsplay_data->notify);
    }

    if(tsplay_data->hPvr != D_INVALID_HANDLE )
    {
        d_pvr_porting_rep_stop(tsplay_data->hPvr);
        d_pvr_porting_rep_destroy(tsplay_data->hPvr);
        tsplay_data->hPvr = D_INVALID_HANDLE;
    }

    d_pvr_porting_rep_close();
    if(tsplay_pvr_rep_int_handle != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(tsplay_pvr_rep_int_handle);
    }
    tsplay_pvr_rep_int_handle = D_INVALID_HANDLE;
    if(tsplay_av_evt_handle != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(tsplay_av_evt_handle);
    }
    tsplay_av_evt_handle = D_INVALID_HANDLE;
    if(tsplay_data->rep_buf_phys)
        d_sys_unmap_address(tsplay_data->rep_buf_phys);
    if(tsplay_data->rep_buf)
        d_sys_unmap_address(tsplay_data->rep_buf);
    if(tsplay_data->rep_buf_nc)
        d_sys_free_dev_mem(tsplay_data->rep_buf_nc);

    if(tsplay_data->rbuf_buf)
        d_mem_free(tsplay_data->rbuf_buf);

    if(tsplay_data)
        d_mem_free(tsplay_data);

    tsplay_data = NULL;

    __tsplay_unlock();

    D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
    return D_OK;
}

static D_Result tsplay_add_pid_info(int mode, D_U16 pid, D_U16 type)
{
    int i;

    if(tsplay_data)
    {
        if(mode == 0)
        {
            i = 0;
        }
        else if(mode == 1)
        {
            i = 1;
        }
        else
        {
            for(i = 2; i < 5; i++)
            {
                if(tsplay_data->pidinfo[i].pid == 0 || tsplay_data->pidinfo[i].pid == 0x1FFF)
                    break;
            }
        }

        if(i < 5)
        {
            tsplay_data->pidinfo[i].type = type;
            tsplay_data->pidinfo[i].pid = pid;
        }
    }
    return D_OK;
}

static D_Result tsplay_get_avpid_avtype(D_U8* pData, unsigned int dataLen)
{
    unsigned char tsh[188] = {0,};
    unsigned int pid = 0;
    int adaptation_length = 0;
    unsigned char adaptation_field_control;
    int section_length = 0;
    int program_num = 0;
    int program_info_length = 0;
    int ES_info_length = 0;
    int space, ret_len, offset;
    int dat_size;
    D_U8 *p = NULL;
    D_U8 *temp = NULL;
    D_U8 *sibuf = NULL;

    sibuf = tsplay_data->rbuf_buf;
    tsplay_data->si_data_size = NETTS_PLAY_RBUF_SIZE;
    offset = 0;
    while(dataLen && tsplay_data->find_pmt == 0)
    {
        /* ѡ�����ݴ��ڻ�������*/
        space = (tsplay_data->si_data_wp >= tsplay_data->si_data_rp) ? (tsplay_data->si_data_size - tsplay_data->si_data_wp) : (tsplay_data->si_data_rp - tsplay_data->si_data_wp);
        if(space != 0)
        {
            ret_len = D_MIN(dataLen, space);
            memcpy((sibuf + tsplay_data->si_data_wp), (pData + offset), dataLen);
            tsplay_data->si_data_wp = (tsplay_data->si_data_wp + ret_len) % tsplay_data->si_data_size;
            tsplay_data->si_data_total_size += ret_len;
            dataLen -= ret_len;
            offset += ret_len;
        }

        dat_size = (tsplay_data->si_data_wp >= tsplay_data->si_data_rp) ? (tsplay_data->si_data_wp - tsplay_data->si_data_rp) : (tsplay_data->si_data_size - tsplay_data->si_data_rp + tsplay_data->si_data_wp);
        while(dat_size >= (188 * 2 + 1) && tsplay_data->find_pmt == 0)
        {
            int idx, idx1;

            /* read ts packet*/
            idx = tsplay_data->si_data_rp;
            idx1 = (tsplay_data->si_data_rp + 188) % tsplay_data->si_data_size;

            while(dat_size > (188 + 1))
            {
                if(sibuf[idx] == 0x47 && sibuf[idx1] == 0x47)
                {
                    break;
                }
                dat_size -= 1;
                idx = (idx + 1) % tsplay_data->si_data_size;
                idx1 = (idx1 + 1) % tsplay_data->si_data_size;
            }

            tsplay_data->si_data_rp = idx;
            if(dat_size <= (188 + 1))
            {
                continue;
            }

            idx = D_MIN(188, (tsplay_data->si_data_size - tsplay_data->si_data_rp));
            idx1 = 188 - idx;
            memcpy(tsh, (sibuf + tsplay_data->si_data_rp), idx);
            if(idx1)
            {
                memcpy(tsh + idx, sibuf, idx1);
            }
            dat_size -= 188;
            tsplay_data->si_data_rp = (tsplay_data->si_data_rp + 188) % tsplay_data->si_data_size;

            temp = tsh;
            pid = (tsh[1] << 8 | tsh[2]) & 0x1fff;
            if(pid == 0x1FFF)
            {
                continue;
            }

            if(pid == PID_PAT)
            {
                if(tsplay_data->pmt_pid == 0x1FFF)
                {
                    adaptation_field_control = tsh[3] & 0x30;
                    if(adaptation_field_control == 0x10)
                    {
                        temp = tsh + 4 + 1;
                    }
                    else if(adaptation_field_control == 0x30)
                    {
                        adaptation_length = tsh[4];
                        temp = tsh + 4 + 1 + adaptation_length + 1;

                    }
                    else
                    {
                        temp = tsh + 4 + 1;
                    }
                    section_length = (temp[1] & 0x0f) << 8 | temp[2];

                    p = temp + 1 + section_length;
                    temp = temp + 8;

                    while(temp < p - 4)
                    {
                        program_num = (temp[0] << 8) | temp[1];
                        if(program_num != 0)
                        {
                            tsplay_data->pmt_pid = (temp[2] & 0x1f) << 8 | temp[3];
                            D_DUMP("pmt_pid 0x%04x\n", tsplay_data->pmt_pid);
                            break;
                        }
                        temp = temp + 4;
                    }
                }
                continue;
            }

            if(pid == tsplay_data->pmt_pid)
            {
                tsplay_data->find_pmt = 1;
                adaptation_field_control = tsh[3] & 0x30;

                if(adaptation_field_control == 0x10)
                {
                    temp = tsh + 4 + 1;
                }
                else if(adaptation_field_control == 0x30)
                {
                    adaptation_length = tsh[4];
                    temp = tsh + 4 + 1 + adaptation_length + 1;
                }
                else
                {
                    temp = tsh + 4 + 1;
                }

                section_length = (temp[1] & 0x0f) << 8 | temp[2];
                p = temp + 1 + section_length;

                /*pcr pid*/
                pid = (temp[8] << 8 | temp[9]) & 0x1fff;
                tsplay_add_pid_info(0, pid, 0);
                D_DUMP("pcr pid pid 0x%04x\n", pid);

                program_info_length = (temp[10] & 0xf) << 8 | temp[11];
                temp = temp + 12 + program_info_length;

                for(; temp < p - 4;)
                {
                    pid = (temp[1] << 8 | temp[2]) & 0x1fff;
                    D_DUMP("ES info type 0x%02x pid 0x%04x\n", temp[0], pid);
                    ES_info_length = (temp[3] & 0x0f) << 8 | temp[4];

                    switch(temp[0])
                    {
                        case 0x01:
                        case 0x02:
                            tsplay_add_pid_info(1, pid, D_VID_CODEC_MPEG2);
                            break;
                        case 0x1b:
                            tsplay_add_pid_info(1, pid, D_VID_CODEC_H264);
                            break;
                        case 0x10:
                            tsplay_add_pid_info(1, pid, D_VID_CODEC_MPEG4);
                            break;
                        case 0x42:
                        case 0x43:
                            tsplay_add_pid_info(1, pid, D_VID_CODEC_AVS);
                            break;
                        case 0xEA:
                            tsplay_add_pid_info(1, pid, D_VID_CODEC_VC1);
                            break;
                        case 0x03:
                        case 0x04:
                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_MPEG2);
                            break;
                        case 0x0f:
                        case 0x11:
                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_AAC);
                            break;
                        case 0x81:
                        case 0x87:
                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_AC3);
                            break;
                        case 0x82:
                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_DTS);
                            break;
                        case 0x06:
                            if(ES_info_length)
                            {
                                int info_len = ES_info_length;
                                int des_len;
                                p = &temp[5];
                                while(info_len > 0)
                                {
                                    des_len = p[1];
                                    switch(p[0])
                                    {
                                        case DESCR_AC3:
                                        case DESCR_EAC3:
                                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_AC3);
                                            break;
                                        case DESCR_AAC:
                                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_AAC);
                                            break;
                                        case DESCR_DTS:
                                            tsplay_add_pid_info(2, pid, D_AUD_CODEC_DTS);
                                            break;
                                        case DESCR_REGISTRATION:
                                        {
                                            D_U32 format_identifier;
                                            format_identifier = (((D_U32)p[2]) << 24) | (((D_U32)p[3]) << 16) | (((D_U32)p[4]) << 8) | ((D_U32)p[5]) ;
                                            if(format_identifier == 0x44524131)/*DRA1*/
                                            {
                                                tsplay_add_pid_info(2, pid, D_AUD_CODEC_DRA);
                                            }
                                            else if(format_identifier == 0x44545331)/*DTS1*/
                                            {
                                                tsplay_add_pid_info(2, pid, D_AUD_CODEC_DTS);
                                            }
                                        }
                                        break;
                                        default:
                                            break;
                                    }

                                    info_len -= (2 + des_len);
                                }
                            }
                            break;
                        default:
                            break;
                    };

                    temp = temp + 4 + ES_info_length + 1;
                }

                break;
            }
        }
    }

    if(tsplay_data->find_pmt)
    {
        return D_OK;
    }

    return D_ERR;
}

static void tsplay_check_buf(void)
{
    D_U32 length_vcd = 0, length_acd = 0; 
    D_U32 size_vcd = 0, size_acd = 0;
    D_U32 t, toff;

    if(tsplay_data->get_ts_play_param == D_FALSE || tsplay_data->video_ok == D_FALSE)
    {
        return ;
    }

    /* ����100ms ���һ��*/
    t = d_sys_get_time();
    toff = t - tsplay_data->last_check_time;
    if(toff >= 200)
    {
        tsplay_data->last_check_time = t;
    }
    else
    {
        return ;
    }
	if(is_change_channel == D_TRUE) {
		is_change_channel = D_FALSE;
		is_loading = D_FALSE;
		MSG("is_loading hide  %d  \n", is_loading);
		D_DUMP("########is_loading######## \n");
	}
    
    /* ����������������йػ�������*/
    length_acd = d_pvr_porting_get_repavcd_data_len(tsplay_data->hPvr, 0, &size_acd);
    length_vcd = d_pvr_porting_get_repavcd_data_len(tsplay_data->hPvr, 1, &size_vcd);
    D_DUMP("####data length  acd %x, vcd %x\n", length_acd, length_vcd);

    if((length_vcd >= NETTS_PLAY_DATA_SIZE)  || (length_vcd >= (size_vcd - NETTS_MIN_VCD_SPACE)) || (length_acd >= (size_acd - NETTS_MIN_ACD_SPACE)))
    {
        if(tsplay_data->pause)
        {
 		is_loading = D_FALSE;
 		MSG("is_loading hide  %d  \n", is_loading);
          tsplay_data->pause = D_FALSE;
            tsplay_data->wait_progress = 100;
            d_pvr_porting_rep_resume(tsplay_data->hPvr);
            D_DUMP("########resume########  %d\n", is_loading);
        }
    }
    else if(length_vcd < NETTS_WAIT_DATA_SIZE)
    {
        if(tsplay_data->pause == D_FALSE)
        {
            tsplay_data->pause = D_TRUE;
            tsplay_data->wait_progress = 0;
            d_pvr_porting_rep_pause(tsplay_data->hPvr);
			is_loading = D_TRUE;
            D_DUMP("########pause########  %d\n", is_loading);
 			MSG("is_loading hide  %d  \n", is_loading);
       }
    }
    else
    {
        if(tsplay_data->pause)
        {
            tsplay_data->wait_progress = (100 * length_vcd / NETTS_PLAY_DATA_SIZE);
        }
    }
}

int tsplay_fill_rbuf(D_U8* pData, unsigned int dataLen)
{
    int ret_len = 0;
    __tsplay_lock();
    if(tsplay_data)
    {
        ret_len = hidrv_rbuf_space(&(tsplay_data->rbuf));
        if(ret_len != 0)
        {
            ret_len = hidrv_rbuf_write(&(tsplay_data->rbuf), pData, dataLen);
        }
    }
    __tsplay_unlock();
    return ret_len;
}

int tsplay_fill_pvrbuf(void)
{
    D_U32 length = 0;
    D_U32 size = 0, read_size = 0;
    D_U32 rep_buff_wp;
    D_U8 *rep_buff_virt;
    MSG("\n");
    __tsplay_lock();
    /* get pvr replay circle buffer's address and size ,µÃµœ»ºŽæÇø¿ÉÐŽµÄÖžÕëŒ°ŽóÐ¡*/
    d_pvr_porting_get_repbuf_data(tsplay_data->hPvr, &rep_buff_wp, &length, REP_BUF, FORWARD_1PIX);
    if(length == 0)
    {
        MSG("length = 0 !!!!!\n");

		if(tsplay_data->pause)
        {
			tsplay_data->pause = D_FALSE;
			tsplay_data->wait_progress = 100;
			d_pvr_porting_rep_resume(tsplay_data->hPvr);
			D_DUMP("########resume######## \n");
        }
    }
    else
    {
        rep_buff_virt = tsplay_data->rep_buf + (rep_buff_wp - (D_U32)tsplay_data->rep_buf_phys);
        size = hidrv_rbuf_length(&(tsplay_data->rbuf)) & (~0x1f); //ÅÐ¶Ï»º³åÓÐ¶àÉÙ¿ÉÒÔ¶ÁÈ¡
        size = MIN(size, length);
        if(size)
        {
            read_size = hidrv_rbuf_read(&(tsplay_data->rbuf), rep_buff_virt, size);
            if(read_size != size)
            {
                MSG("read_size(%x)  != size(%x) !!!!!\n", read_size, size);
            }
            d_sys_cache_flush_range((D_Ptr)rep_buff_virt, read_size);
            d_pvr_porting_set_repwp(tsplay_data->hPvr, read_size);
        }
    }
   __tsplay_unlock();
    return D_OK;
}


unsigned int tsplay_recv_packet(void* pData, unsigned int dataLen)
{
    unsigned int read_len = 0;

    __tsplay_lock();

    if(net_tsplay_open && tsplay_data  && dataLen )
    {
        tsplay_data->recv_packet_cnt++;
        /* Ã»È¡µÃpidÐÅÏ¢Ê±£¬ÏÈœâÎö»ñÈ¡pidÐÅÏ¢*/
        if(tsplay_data->get_ts_play_param == D_FALSE)
        {
            if(D_OK == tsplay_get_avpid_avtype((D_U8*)pData, dataLen))
            {
                /* È¡µÃpidÐÅÏ¢ºóÆô¶¯²¥·Å*/
                tsplay_data->get_ts_play_param = D_TRUE;
                tsplay_data->ts_parm.pid.pcr_pid = tsplay_data->pidinfo[0].pid;
                tsplay_data->ts_parm.pid.v_pid = tsplay_data->pidinfo[1].pid;
                tsplay_data->ts_parm.video_decode_type = tsplay_data->pidinfo[1].type;
                tsplay_data->ts_parm.pid.a_pid = tsplay_data->pidinfo[2].pid;
                tsplay_data->ts_parm.audio_decode_type = tsplay_data->pidinfo[2].type;
                tsplay_data->ts_parm.scramble_flag = 0;
                tsplay_data->ts_parm.type = D_AV_SYNC_APTS;

                tsplay_start();  /* ¿ªÊŒ²¥·ÅÀïpause£¬ÊýŸÝ×ã¹»resume*/
                D_DUMP("####tsplay_data->si_data_total_size  %x\n", tsplay_data->si_data_total_size);
            }
            __tsplay_unlock();
            return dataLen;
        }

        if(tsplay_data->PvrReplayIntStatus & D_PvrInt_RepDataOverflow)
        {
            /* deal with pvr replay overflow */
            d_pvr_porting_rep_restart(tsplay_data->hPvr);
            D_ERROR("replay overflow and restart \n");
            d_pvr_porting_reset_rep_int_status(tsplay_data->hPvr, (D_PvrIntMask)D_PvrInt_RepDataOverflow);
            tsplay_data->PvrReplayIntStatus &= ~D_PvrInt_RepDataRequest;
            tsplay_data->pause = D_TRUE;
            tsplay_data->wait_progress = 0;
            d_pvr_porting_rep_pause(tsplay_data->hPvr);
        }

        read_len = tsplay_fill_rbuf((D_U8*)pData, dataLen);
		MSG("read_len: %d\n", read_len);
        tsplay_fill_pvrbuf();
    __check_data:
        tsplay_check_buf();
    }
    else
    	{
    	MSG("read_len = 000000 !\n");
		read_len = dataLen;
    	}
    __tsplay_unlock();
    return read_len;
}

D_Result tsplay_callback(D_Msg * msg) D_FUNCPOSTFIT
{
    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            d_app_set_timeout(d_app_self(), 200);
            break;
        case D_MSG_APP_TIMEOUT:
            if(tsplay_data->get_ts_play_param)
            {
                if(tsplay_data->last_recv_packet_cnt == tsplay_data->recv_packet_cnt)
                {
                    __tsplay_lock();
                    tsplay_fill_pvrbuf();
                    tsplay_check_buf();
                    __tsplay_unlock();
                }
                else
                {
                    tsplay_data->last_recv_packet_cnt = tsplay_data->recv_packet_cnt;
                }
            }
            break;
        default:
            break;
    }
    return D_OK;
}

/**@brief ²¥·Å ÍøÂçtsÎÄŒþ
*@param[in] path:²¥·ÅÊÓÆµÎÄŒþµÄŸø¶ÔÂ·Ÿ¶
*@param[in] id:Ö±²¥œÚÄ¿list id
*@param[in] x,y,w,h:²¥·ÅÊÓÆµµÄŽ°¿ÚŽóÐ¡Î»ÖÃ
*@param[in] type: ²¥·ÅÊÓÆµÀàÐÍ (µçÓ°ÔÝÊ±ÎŽÓÃ £¬ ts µÚŒžÂ·œÚÄ¿)
*@param[in] vis:²¥·ÅÊÓÆµÎÄŒþÈç¹ûÓÐ×ÖÄ»ÎÄŒþµÄ»°£¬ÕâžöÔòÊÇÏÔÊŸ×ÖÄ»µÄ¿ØŒþÖžÕë
*@retval ³É¹Š·µ»ØD_OK,Ê§°Ü·µ»ØD_ERR
*/
D_Result d_media_netts_play(D_Char* path, D_U32 id, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_S8 type, D_Visual *vis)D_FUNCPOSTFIT
{
    D_Result ret;
	
	d_av_set_aud_mute(0, D_TRUE);
	d_av_set_vid_input(0, D_VID_IUTPUT_DTV);
    
	ret = tsplay_open();
    
	if(D_OK != ret)
    {
        tsplay_close();
    }
    else
    {
        net_tsplay_open = D_TRUE;
        d_av_stop(0);
        d_av_set_vid_window(0, x, y, w, h);
        d_av_set_vid_blank(0, D_TRUE);

        tsplay_data->hnetts_play = d_app_create ("NetTsPlay", D_PVR_REPLAY_TASK_PRIO, D_PVR_REPLAY_TASK_STACK_SIZE, D_PVR_REPLAY_QUEUE_SIZE, tsplay_callback, (D_Ptr)tsplay_data);
        if (tsplay_data->hnetts_play == D_INVALID_HANDLE)
        {
            tsplay_close();
            return D_ERR;
        }
        else
        {
            d_app_sync (tsplay_data->hnetts_play);
            // add read packet task
			_iptv_start_play(id);
        }
    }
    D_DUMP("%s:%d-----ret = %d\n", __FUNCTION__, __LINE__, ret);
    is_change_channel = D_TRUE;
    return D_OK;
}

/**@brief Í£Ö¹ÍøÂçtsÎÄŒþ²¥·Å
*@retval ³É¹Š·µ»ØD_OK,Ê§°Ü·µ»ØD_ERR
*/
D_Result d_media_netts_stop(void)D_FUNCPOSTFIT
{
    D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
    // stop recv data task
	_iptv_stop_play();
    if(tsplay_data && net_tsplay_open)
    {
        net_tsplay_open = D_FALSE;
        if (tsplay_data->hnetts_play != D_INVALID_HANDLE)
        {
    		D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
            d_app_destroy (tsplay_data->hnetts_play);
            tsplay_data->hnetts_play = D_INVALID_HANDLE;
        }

    	D_DUMP("%s:%d-----\n", __FUNCTION__, __LINE__);
        tsplay_close();
        d_task_wait(1000);
        d_av_set_vid_blank(0, D_TRUE);
    }
    return D_OK;
}


/**@brief »ñÈ¡ÍøÂçtsÎÄŒþ²¥·Å×ŽÌ¬
*@retval ·µ»ØÊÓÆµÃ¶ŸÙœá¹¹ÌåD_MovieStatusÖÐµÄÖµ
*/
D_MovieStatus d_media_netts_get_status(void) D_FUNCPOSTFIT
{
    return MOVIE_STATUS_PLAY;
}

/**@brief »ñÈ¡µ±Ç°²¥·ÅÊ±Œä
*@retval ·µ»ØÖµÎªD_DoubleÀàÐÍµÄµ±Ç°²¥·ÅÊ±ŒäÖµ
*/
D_Double d_media_netts_get_curtime(void) D_FUNCPOSTFIT
{
    D_Double ctime = 0;
    D_Time  stime;

    if(tsplay_data)
    {
        if(tsplay_data->pause)
        {
            ctime = (D_Double)(tsplay_data->last_play_duration);
        }
        else
        {
            stime = d_sys_get_time();
            stime = (stime >= tsplay_data->last_play_duration) ? (stime - tsplay_data->last_play_duration) : (stime - (0xFFFFFFFF - tsplay_data->last_play_duration));
            stime /= 1000;
            ctime = (D_Double)(tsplay_data->last_play_duration + stime);
        }
    }
    return ctime;
}

