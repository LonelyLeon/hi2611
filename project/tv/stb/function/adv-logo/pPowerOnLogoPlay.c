/**@defgroup plogo logo和广告模块
*@{*/

/** @file
* @brief 开机logo播放任务
* @author qiny
* @date 2014-02-26 qiny: 创建文件
*/
#include "dTypes.h"
#include "dResource.h"
#include "dDebug.h"
#include "dTask.h"
#include "pSdk.h"
#include "pStb.h"
#include "pPowerOnLogoPlay.h"
#include "dadporting.h"



#define PLAY_MIN_TIME (1000)
#define PLAY_MAX_TIME (60000)

static D_Time  play_def_time;
static D_U8     logo_count;
static D_HTask hTask_logo = D_INVALID_HANDLE;
static D_HSem hsync_logo = D_INVALID_HANDLE;
static PLOGO_CALLBACK  Logocallback = NULL;

/** @brief 显示logo之后的回调函数，用于打开屏等
* @param happ 应用句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
void p_power_on_logo_cb(PLOGO_CALLBACK cb)D_FUNCPOSTFIT
{
    Logocallback = cb;
}

/** @brief 和一个应用进行消息同步
* @param happ 应用句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_logo_sync (D_HApp happ) D_FUNCPOSTFIT
{
	D_AppMsg			amsg;
	D_Result			ret;
    D_Bool              force_exit = D_FALSE;
	
		
	/*发送同步请求消息*/
	amsg.happ = happ;
	amsg.type = D_MSG_APP_SYNC_REQ;
	amsg.handle = hsync_logo;
	
	if ((ret = d_app_send (happ, (D_U8*)&amsg, sizeof(amsg))) < 0) {
#ifdef D_DEBUG
		D_ERROR ("Send message error\n");
#endif
		return ret;
	}
	
	/*等待信号量*/
    while(d_sem_wait_timeout(hsync_logo, 500) != D_OK)
    {
        if(force_exit)
        {
            return D_ERR_TIMEOUT;
        }
    }
    
	return D_OK;
}


/** @brief 开机logo播放函数
* @return 错误代码
*/
static void logo_play_proc(D_Ptr p) D_FUNCPOSTFIT
{
    d_ad_pict_info imginfo;
    D_U8 i;
    D_GSurface* gsurface;
    D_GSurface* psurface; 
    D_Time delay_time;

    gsurface = d_gui_get_surface();
    psurface = p_gui_get_dev_surface();

	if(logo_count > 0)
	{
		for(i = 0; i < logo_count; i++)
		{
			D_Pixel pix;
			D_Rect dr,sr;

			dr.x = 0;
			dr.y = 0;
			dr.w = gsurface->buf.width;
			dr.h= gsurface->buf.height;

			pix = d_g_map_color (p_gui_get_dev_surface(), D_RGBA (0x00, 0x00, 0x00, 0x00));

			if(d_ad_load_img_data(DAD_STB_LOG,i,&imginfo) != D_OK)
			{
				continue;
			}

			delay_time = imginfo.times;
			delay_time = (delay_time < PLAY_MIN_TIME) ? D_MAX(PLAY_MIN_TIME, play_def_time) : D_MIN(PLAY_MAX_TIME, delay_time);
			D_DUMP("[hegx]logoplayer\n");

			if(imginfo.imgType == D_IMAGE_MPEG2_FRAME_I)
			{		
				d_tv_display_pic_I (g_htv, imginfo.id, (D_U8*)imginfo.buffer,imginfo.img_size);
				d_logo_sync(g_htv);
				if(Logocallback)Logocallback(i);
				d_task_wait(delay_time);
			}				
			else
			{		
				d_g_lock(gsurface);
				sr.x = 0;
				sr.y = 0;
				sr.w = psurface->buf.width;
				sr.h = psurface->buf.height;
				
				d_g_set_fg(gsurface,pix);
				d_g_fill_rect(gsurface,&dr);		
				d_g_copy(psurface, &sr,gsurface, &dr);					

				sr.x = 0;
				sr.y = 0;
				sr.w =imginfo.width;
				sr.h = imginfo.height;

				d_gdev_set_enable(p_gui_get_hgdev(), D_TRUE);
				d_gdev_enable_hw_antiflicker(p_gui_get_hgdev(), D_TRUE);

				d_g_copy_image (gsurface,&dr,(D_Image *)imginfo.buffer,&sr);	

				d_gdev_enable_hw_antiflicker(p_gui_get_hgdev(), D_FALSE);

				sr.x = imginfo.left;
				sr.y = imginfo.top;
				sr.w = psurface->buf.width;
				sr.h = psurface->buf.height;
				
				d_g_copy(psurface, &sr,gsurface, &dr);
				if(Logocallback)Logocallback(i);
				d_task_wait(delay_time);
				d_g_unlock(gsurface);
			}				
			d_ad_release_img_data(&imginfo );	

		}	
	}

}


/** @brief 启动开机logo播放任务函数
* @return def_time 默认一帧播放时间
* @return 错误代码
*/
D_Result 
p_power_on_logo_play_start(D_Time def_time)D_FUNCPOSTFIT
{
    D_TaskAttr TaskAttr;
	D_U8 logo_enable = 1;
		
    play_def_time = def_time;
		
	p_tvconf_get_logomode (&logo_enable);
	if(logo_enable)
		logo_count =  d_ad_get_img_count (DAD_STB_LOG);	
	else
		logo_count = 0;	
	
    if(logo_count > 0)
    {
        D_TASK_ATTR_INIT(&TaskAttr);
        TaskAttr.name = "Playlogo";
        TaskAttr.priority = D_MAIN_TASK_PRIO + 1;
        TaskAttr.stack_size = 4096;
		hsync_logo = d_sem_create (NULL);

        hTask_logo = d_task_create(&TaskAttr, logo_play_proc, NULL);
        if(hTask_logo == D_INVALID_HANDLE)
        {
            D_ERROR("Playlogo task create failed!\n");
            return D_ERR;
        }
    }
    return D_OK;
}

/** @brief 线束logo播放任务函数
* @return 错误代码
*/
D_Result 
p_power_on_logo_play_end(void)D_FUNCPOSTFIT
{
    if(hTask_logo != D_INVALID_HANDLE)
    {
        d_task_join(hTask_logo);
    }
    if(hsync_logo != D_INVALID_HANDLE)
    {
        d_sem_destroy(hsync_logo);
    }	
	
    hTask_logo = D_INVALID_HANDLE;
    hsync_logo = D_INVALID_HANDLE;

    return D_OK;
}

/* @}*/



