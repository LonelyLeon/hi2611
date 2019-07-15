#include "pvr.h"
#include "_helper.h"
#include <fcntl.h>

#define PVR_REP_BUFFER_SIZE     (2*M)
#define PVR_REP_BUFFER_ALIGN    (1*K)
#define MIN_REP_LENGTH          (128*K) //replay buff wp limit size,for interrupting 
#define MIN_VCD_SPACE           (256*K) //0x60000 1024byte对齐
#define MIN_ACD_SPACE           (4*K)   //0x800 1024byte对齐

static PVRDATA *pvr_data = NULL;
static D_Bool pvr_porting_already_open = D_FALSE;
static D_Handle pvr_rep_int_handle = D_INVALID_HANDLE;
static D_Handle av_evt_handle = D_INVALID_HANDLE;
static D_U8 * rbuf_buf = NULL;
static int buf_len = 0x20000;

PVRDATA * get_default_pvrdata(void)
{
    return pvr_data;
}

D_Result pvr_rep_fill_buf(void)
{
    D_U32 length = 0;
    D_U32 size = 0;
    D_U32 rep_buff_wp;
    D_U8 *rep_buff_virt;

    /* get pvr replay circle buffer's address and size ,得到缓存区可写的指针及大小*/
    d_pvr_porting_get_repbuf_data(pvr_data->hPvr, &rep_buff_wp, &length, REP_BUF, FORWARD_1PIX);
    if(length == 0)
    {
        MSG("length = 0 !!!!!\n");
        return D_OK;
    }

    rep_buff_virt = pvr_data->rep_buf + (rep_buff_wp - (D_U32)pvr_data->rep_buf_phys);

    size = hidrv_rbuf_length(&(pvr_data->rbuf)) & (~0x1f); //判断缓冲有多少可以读取
    size = MIN(size, length);
    if(size)
    {
        size = hidrv_rbuf_read(&(pvr_data->rbuf), rep_buff_virt, size);
        d_sys_cache_flush_range((D_Ptr)rep_buff_virt, size);
        d_pvr_porting_set_repwp(pvr_data->hPvr, size);
    }

    return D_OK;
}

void d_pvr_fill_buf(void)
{
    //D_U32 length = 0;
    //D_U32 rep_buff_wp;

    if(pvr_data->PvrReplayIntStatus & D_PvrInt_RepDataOverflow)
    {
        /* deal with pvr replay overflow */
        d_pvr_porting_rep_restart(pvr_data->hPvr);
        D_ERROR("replay overflow and restart \n");
        d_pvr_porting_reset_rep_int_status(pvr_data->hPvr, (D_PvrIntMask)D_PvrInt_RepDataOverflow);
    }

    pvr_rep_fill_buf();
    //d_pvr_porting_get_repbuf_data(pvr_data->hPvr, &rep_buff_wp, &length, REP_BUF, FORWARD_1PIX);
    pvr_data->PvrReplayIntStatus &= ~D_PvrInt_RepDataRequest;
}

static void _PvrRepIntCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_PvrIntReason reason = (D_PvrIntReason)obj_data;

    if(pvr_data && (reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow)))
    {
        MSG("\n");
        pvr_data->PvrReplayIntStatus = (D_PvrIntMask)(reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow));
    }
}

static void _PvrAvDrvEventCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_AVEventParam *param = (D_AVEventParam*)obj_data;
    SEE("%d", param->evt);
    if(param->evt == D_AV_EVT_NEW_PIC_START)
    {
        p_atv_zhilian_tv_window_show_enable(0);
        d_av_set_vid_blank(0, D_FALSE);
        //p_stb_player_set_vol(0, 10);
    }
    else if(param->evt == D_AV_EVT_NEW_AUD_START)
    {
    }
}

D_Result p_pvr_open(void) D_FUNCPOSTFIT
{
    D_PvrRepDev repdev = {0};
    D_PvrRepAttr attr = {0};

    if(pvr_porting_already_open == D_FALSE)
    {
        /* 只能open一次 */
        d_pvr_porting_open();
        pvr_porting_already_open = D_TRUE;
    }

    pvr_data = (PVRDATA*)d_mem_alloc(0, sizeof(PVRDATA));
    if(!pvr_data)
        return D_ERR_NO_SPACE;

    memset(pvr_data, 0x00, sizeof(PVRDATA));
    pvr_rep_int_handle = D_INVALID_HANDLE;
    av_evt_handle = D_INVALID_HANDLE;
    pvr_data->notify = D_INVALID_HANDLE;
    pvr_data->hPvr = D_INVALID_HANDLE;
    pvr_data->dev_id = 0;

    pvr_data->rep_buf_nc = (D_U8*)d_sys_alloc_dev_mem(PVR_REP_BUFFER_SIZE, PVR_REP_BUFFER_ALIGN);
    if(!pvr_data->rep_buf_nc)
    {
        d_mem_free(pvr_data);
        pvr_data = NULL;
        D_ERROR("Cannot alloc rep_buf_nc\n");
        return D_ERR_NO_SPACE;
    }

    pvr_data->rep_buf = (D_U8*)d_sys_map_address(D_SysAddr_Cached, pvr_data->rep_buf_nc, PVR_REP_BUFFER_SIZE);
    pvr_data->rep_buf_phys = (D_U8*)d_sys_map_address(D_SysAddr_Phys, pvr_data->rep_buf_nc, PVR_REP_BUFFER_SIZE);

    memset(&(pvr_data->ts_parm), 0, sizeof(D_PvrRepTsParm));
    /* 根据实际情况设值 */
    pvr_data->ts_parm.pid.v_pid = 0x1011;
    pvr_data->ts_parm.pid.a_pid = 0x1100;
    pvr_data->ts_parm.pid.pcr_pid = 0x1000;
    pvr_data->ts_parm.video_decode_type = D_VID_CODEC_H264;
    pvr_data->ts_parm.audio_decode_type = D_AUD_CODEC_AAC;
    pvr_data->ts_parm.type = D_AV_SYNC_VPTS; /* 2610e的pcr同步方式有问题，所以使用vpts同步*/

    //pvr_data->notify = d_sem_create(NULL);
    pvr_data->running = D_TRUE;
    pvr_data->rbuf.ops = hidrv_rbuf_default_ops;
    rbuf_buf = (D_U8*)d_mem_alloc(0, (D_Size)buf_len);
    hidrv_rbuf_init(&(pvr_data->rbuf), (const void * )rbuf_buf, (int)buf_len);
    hidrv_rbuf_set_wp(&(pvr_data->rbuf), 0);
    hidrv_rbuf_set_rp(&(pvr_data->rbuf), 0);

    repdev.param.repbuf_baseaddr        = (D_U32)pvr_data->rep_buf_phys;
    repdev.param.repbuf_size            = PVR_REP_BUFFER_SIZE;
    repdev.param.min_rep_len            = MIN_REP_LENGTH;
    repdev.param.min_acd_space          = MIN_ACD_SPACE;
    repdev.param.min_vcd_space          = MIN_VCD_SPACE;
    repdev.param.TV_num                 = pvr_data->dev_id;
    repdev.param.rep_interrupt_state    = 0;

    d_pvr_porting_rep_open();
    pvr_data->hPvr = d_pvr_porting_rep_create(attr, &repdev);
    if(pvr_data->hPvr == D_INVALID_HANDLE)
    {
        D_ERROR("Cannot create porting replay\n");
        return D_ERR;
    }

    av_evt_handle = d_cbman_subscribe(PL_AV_CALLBACK, D_INVALID_HANDLE, _PvrAvDrvEventCallback, (D_Ptr)pvr_data);
    pvr_rep_int_handle = d_cbman_subscribe(PL_INTERRUPT_PVR, D_INVALID_HANDLE, _PvrRepIntCallback, (D_Ptr)pvr_data);

    d_av_screen_push_en(1);

    d_pvr_porting_rep_restart(pvr_data->hPvr);
    d_pvr_porting_rep_start(pvr_data->hPvr, &pvr_data->ts_parm);
    d_av_vdac_ctrl(1);

    return D_OK;
}

D_Result p_pvr_close(void) D_FUNCPOSTFIT
{
    if(pvr_data == NULL)
    {
        return D_OK;
    }

    if(rbuf_buf)
        d_mem_free(rbuf_buf);

    pvr_data->running = D_FALSE;
    if(pvr_data->notify != D_INVALID_HANDLE)
    {
        d_sem_destroy(pvr_data->notify);
    }

    if(pvr_data->hPvr != D_INVALID_HANDLE )
    {
        d_pvr_porting_rep_stop(pvr_data->hPvr);
        d_pvr_porting_rep_destroy(pvr_data->hPvr);
        pvr_data->hPvr = D_INVALID_HANDLE;
    }

    d_pvr_porting_rep_close();
    if(pvr_rep_int_handle != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(pvr_rep_int_handle);
    }
    pvr_rep_int_handle = D_INVALID_HANDLE;
    if(av_evt_handle != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(av_evt_handle);
    }
    av_evt_handle = D_INVALID_HANDLE;
    if(pvr_data->rep_buf_phys)
        d_sys_unmap_address(pvr_data->rep_buf_phys);
    if(pvr_data->rep_buf)
        d_sys_unmap_address(pvr_data->rep_buf);
    if(pvr_data->rep_buf_nc)
        d_sys_free_dev_mem(pvr_data->rep_buf_nc);
    if(pvr_data)
        d_mem_free(pvr_data);

    rbuf_buf = NULL;
    pvr_data = NULL;
    d_av_screen_push_en(0);
    D_DUMP("p_pvr_close end\n");
    return D_OK;
}
