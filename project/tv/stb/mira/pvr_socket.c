#include "pvr.h"
#include "_helper.h"
#include <fcntl.h>

//#define READ_FROME_FILE

#define PVR_REP_BUFFER_SIZE     (2*M)
#define PVR_REP_BUFFER_ALIGN    (1*K)
#define MIN_REP_LENGTH          (128*K) //replay buff wp limit size,for interrupting 
#define MIN_VCD_SPACE           (256*K) //0x60000 1024byte对齐
#define MIN_ACD_SPACE           (4*K)   //0x800 1024byte对齐

static PVRDATA *pvr_data;
static D_Bool pvr_porting_already_open = D_FALSE;
static D_Handle pvr_rep_int_handle;
static D_Handle av_evt_handle;

#ifdef READ_FROME_FILE
static int fd = 0;
#endif
static char * rbuf_buf = NULL;
static int buf_len = 64 * 1024;
static D_Bool first_packet = D_TRUE;
static int cliend_fd = 0;

PVRDATA * get_default_pvrdata(void)
{
    return pvr_data;
}

static void _PvrRepIntCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_PvrIntReason reason = (D_PvrIntReason)obj_data;

    if(reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow))
    {
        PVRDATA *pThis = (PVRDATA*)cb_data;

        pThis->PvrReplayIntStatus = (D_PvrIntMask)(reason & (D_PvrInt_RepDataRequest | D_PvrInt_RepDataOverflow));
//        d_sem_post(pThis->notify);
    }
}

static void _PvrAvDrvEventCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_AVEventParam *param = (D_AVEventParam*)obj_data;
    if(param->evt == D_AV_EVT_NEW_PIC_START)
    {
        d_av_set_vid_blank(pvr_data->dev_id, D_FALSE);
    }
    else if(param->evt == D_AV_EVT_NEW_AUD_START)
    {
    }
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
        return D_OK;
    }

    rep_buff_virt = pvr_data->rep_buf + (rep_buff_wp - (D_U32)pvr_data->rep_buf_phys);

    size = hidrv_rbuf_length(&(pvr_data->rbuf)) & ~0x1f; //判断缓冲有多少可以读取
    size = MIN(size, length);
    size = hidrv_rbuf_read(&(pvr_data->rbuf), rep_buff_virt, size);

    d_sys_cache_flush_range((D_Ptr)rep_buff_virt, size);

    if(size)
    {
        /* set the pvr replay buffer write_point, 刷新缓冲区可写指针*/
        d_pvr_porting_set_repwp(pvr_data->hPvr, size);
    }

    return D_OK;
}

void d_pvr_fill_buf(void)
{
    PVRDATA *pThis = pvr_data;
    D_U32 length = 0;
    D_U32 rep_buff_wp;

    if(first_packet)
    {
        VCOM_SetDisable_video(0); //开屏幕
        first_packet = D_FALSE;
    }

//  hidrv_rbuf_write(&(pvr_data->rbuf), data, data_len);

    if(pThis->PvrReplayIntStatus & D_PvrInt_RepDataRequest)
    {
        if(pThis->PvrReplayIntStatus & D_PvrInt_RepDataOverflow)
        {
            /* deal with pvr replay overflow */
            d_pvr_porting_rep_restart(pvr_data->hPvr);
            D_ERROR("replay overflow and restart \n");
        }
        d_pvr_porting_reset_rep_int_status(pvr_data->hPvr, (D_PvrIntMask)D_PvrInt_RepDataOverflow);

        pvr_rep_fill_buf();
    }

    d_pvr_porting_get_repbuf_data(pvr_data->hPvr, &rep_buff_wp, &length, REP_BUF, FORWARD_1PIX);
    if(length < 0x40000)
    {
        pThis->PvrReplayIntStatus &= ~D_PvrInt_RepDataRequest;
        d_pvr_porting_reset_rep_int_status(pvr_data->hPvr, (D_PvrIntMask)(D_PvrInt_RepDataRequest));
    }
}
void setSockNonBlock(int sock)
{
    int flags;
    flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
    {
        perror("fcntl(F_GETFL) failed");
        exit(EXIT_FAILURE);
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl(F_SETFL) failed");
        exit(EXIT_FAILURE);
    }
}

static void _create_socket(void)
{
    struct sockaddr_in * address = &pvr_data->address;
    bzero(address, sizeof(pvr_data->address));
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = inet_addr("127.0.0.1");
    address->sin_port = htons(pvr_data->port);

    pvr_data->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setSockNonBlock(pvr_data->sockfd);
    if(pvr_data->sockfd < 0)
        MSG("socket create error !!! %s\n", strerror(errno));
    bind(pvr_data->sockfd, (struct sockaddr *)address, sizeof(pvr_data->address));
    listen(pvr_data->sockfd, 1);
}

static void pvr_task(D_Ptr p) D_FUNCPOSTFIT
{
    PVRDATA *pThis = (PVRDATA*)p;
    int read_bytes = 0;
    unsigned char * tmp_buf = NULL;
    int space = 0;
    int res = 0;
    socklen_t sin_len = sizeof(struct sockaddr_in);
    fd_set readfds;
    struct timeval timeout;
    int i = 0;

    tmp_buf = malloc(buf_len);
    p_mira_open("keting");

    while(pThis->running)
    {
        if(cliend_fd <= 0)
        {
            FD_ZERO(&readfds);
            FD_SET(pvr_data->sockfd, &readfds);
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            res = select(pvr_data->sockfd + 1, &readfds, NULL, NULL, &timeout);
            if(res == 0)
                continue;
            else if (res < 0)
            {
                MSG(" select error %s!!!\n", strerror(errno));
            }
            else
            {
                for(i = 0; i < pvr_data->sockfd + 1; ++i)
                {
                    if(!FD_ISSET(i, &readfds))
                        continue;
                    if(i == pvr_data->sockfd)
                        cliend_fd = accept(pvr_data->sockfd, (struct sockaddr*)NULL, NULL);
                }
            }

            SEE(" !!!!! %d", cliend_fd);
            p_atv_zhilian_tv_window_show_enable(0);
        }
        else
        {
            space = hidrv_rbuf_space(&(pvr_data->rbuf)) & ~0x1f;
            if(space != 0)
            {
                read_bytes = MIN(space, buf_len);
#if 1
                if(read_bytes > 0)
                {
                    read_bytes = recv(cliend_fd, tmp_buf, read_bytes, 0);
                    if(read_bytes <= 0)
                    {
                        MSG("recv %d !!! %s\n", read_bytes, strerror(errno));
                        close(cliend_fd);
                        cliend_fd = 0;
                        p_atv_zhilian_tv_window_show_enable(1);
                    }
                }
#else
                if(read_bytes > 0)
                {
                    read_bytes = read(fd, tmp_buf, read_bytes);
                    (read_bytes == 0)
                    {
                        MSG("file read done !!!\n");
                        break;
                    }
                }
#endif
            }
            hidrv_rbuf_write(&(pvr_data->rbuf), tmp_buf, read_bytes);
            d_pvr_fill_buf();
        }
    }
}

D_Result p_pvr_open(void) D_FUNCPOSTFIT
{
    D_PvrRepDev repdev;
    D_PvrRepAttr attr = {0};
    D_TaskAttr ta;

    if(pvr_porting_already_open == D_FALSE)
    {
        /* 只能open一次 */
        d_pvr_porting_open();
        pvr_porting_already_open = D_TRUE;
    }

    pvr_data = (PVRDATA*)d_mem_alloc(0, sizeof(PVRDATA));
    if(!pvr_data)
        return D_ERR_NO_SPACE;

    pvr_data->dev_id = 0;
    pvr_data->rep_buf_nc = (D_U8*)d_sys_alloc_dev_mem(PVR_REP_BUFFER_SIZE, PVR_REP_BUFFER_ALIGN);
    if(!pvr_data->rep_buf_nc)
    {
        d_mem_free(pvr_data);
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

    pvr_data->notify = d_sem_create(NULL);
    pvr_data->running = D_TRUE;
    pvr_data->task = 0;
    pvr_data->port = 6789;
    pvr_data->sockfd = 0;
    pvr_data->rbuf.ops = hidrv_rbuf_default_ops;
    hidrv_rbuf_set_wp(&(pvr_data->rbuf), 0);
    hidrv_rbuf_set_rp(&(pvr_data->rbuf), 0);
    rbuf_buf = (char*)d_mem_alloc(0, buf_len);
    hidrv_rbuf_init(&(pvr_data->rbuf), (void *)rbuf_buf, buf_len);

    ta.id = 0;
    ta.stack_size = 8192;
    ta.name = "pvr";
    ta.priority = 15;


    repdev.param.repbuf_baseaddr        = (D_U32)pvr_data->rep_buf_phys;
    repdev.param.repbuf_size            = PVR_REP_BUFFER_SIZE;
    repdev.param.min_rep_len            = MIN_REP_LENGTH;
    repdev.param.min_acd_space          = MIN_ACD_SPACE;
    repdev.param.min_vcd_space          = MIN_VCD_SPACE;
    repdev.param.TV_num                 = pvr_data->dev_id;
    repdev.param.rep_interrupt_state    = 0;

    pvr_data->hPvr = d_pvr_porting_rep_create(attr, &repdev);
    if(pvr_data->hPvr == D_INVALID_HANDLE)
    {
        D_ERROR("Cannot create porting replay\n");
        return D_ERR;
    }


    _create_socket();

#ifdef READ_FROME_FILE
    fd = open("/root/video/bian5.ts", O_RDWR);
    SEE("%d", fd);
    if(fd < 0)
    {
        MSG("file open error !\n");
        return -1;
    }
#endif

    av_evt_handle = d_cbman_subscribe(PL_AV_CALLBACK, D_INVALID_HANDLE, _PvrAvDrvEventCallback, (D_Ptr)pvr_data);
    pvr_rep_int_handle = d_cbman_subscribe(PL_INTERRUPT_PVR, D_INVALID_HANDLE, _PvrRepIntCallback, (D_Ptr)pvr_data);
    d_pvr_porting_rep_open();

    pvr_data->task = d_task_create(&ta, pvr_task, (void*)pvr_data);

    d_pvr_porting_rep_restart(pvr_data->hPvr);
    d_pvr_porting_rep_start(pvr_data->hPvr, &pvr_data->ts_parm);
    d_av_vdac_ctrl(1);
    return D_OK;
}

D_Result p_pvr_close(void) D_FUNCPOSTFIT
{
    p_mira_close();

    pvr_data->running = D_FALSE;
    if(pvr_data->task != D_INVALID_HANDLE)
    {
        d_task_join(pvr_data->task);
    }
    pvr_data->task = D_INVALID_HANDLE;
    if(cliend_fd)
    {
        close(cliend_fd);
    }
    cliend_fd = 0;
    if(pvr_data->sockfd)
    {
        close(pvr_data->sockfd);
    }
    pvr_data->sockfd = 0;
    d_mem_free(pvr_data->rbuf.head);
    d_sem_destroy(pvr_data->notify);
    d_pvr_porting_rep_stop(pvr_data->hPvr);
    d_pvr_porting_rep_destroy(pvr_data->hPvr);
    d_pvr_porting_rep_close();
    d_cbman_unsubscribe(pvr_rep_int_handle);
    d_sys_unmap_address(pvr_data->rep_buf_phys);
    d_sys_unmap_address(pvr_data->rep_buf);
    d_sys_free_dev_mem(pvr_data->rep_buf_nc);
    d_mem_free(pvr_data);
    rbuf_buf = NULL;
    pvr_data = NULL;
    return D_OK;
}
