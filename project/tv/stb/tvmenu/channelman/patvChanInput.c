/** @file
* @brief 频道号输入窗口模块
* @author 覃宜
* @date 2013-07-13 覃宜: 建立文件
*/
#include <stdio.h>
#include "dDBase.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

#include "atv_chan_input_window.c"


#define D_CHAN_NUM_LEN	(3)
#define D_SHOW_TIMEOUT	(3000)			/*菜单显示时间*/
#define D_SHOW_CHANGED_TIMEOUT	(2000)	/*频道切换后菜单显示时间*/
#define MAX_CHAN_CNT (1000)


static D_ID		curr_player_id;
static D_HTimer	delay_timer;
static D_U8     key_input[D_CHAN_NUM_LEN];

/*是否已经换台的标志   */
static D_Bool	change_chan = D_FALSE; 

/*统计输入数字个数*/
static D_U8    count = 0;


static D_ID VisNumId[D_CHAN_NUM_LEN] = {ID_IMG_NUM_100, ID_IMG_NUM_10, ID_IMG_NUM_1};
static D_ImageID NumImgId[10] = {atv_IMG_ID_num_0, atv_IMG_ID_num_1, atv_IMG_ID_num_2, atv_IMG_ID_num_3, atv_IMG_ID_num_4,atv_IMG_ID_num_5, 
								atv_IMG_ID_num_6, atv_IMG_ID_num_7, atv_IMG_ID_num_8, atv_IMG_ID_num_9};


/**@brief 判断输入频道的有效性*/
static D_DBSrvID 
get_db_srv_id_by_num(D_S16 chan_num)D_FUNCPOSTFIT
{
	D_DBSrvID srv_id = -1;
	D_StbPlayer	*player;

	if (! (player = p_stb_get_player (curr_player_id)))
	{
		return D_ERR;
	}
  /*取当前频道号*/
  if (player->play_atv)
  {
		srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_ATV);		
	}	
	else if (!player->play_radio)
	{
		srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_TV);		
		if (srv_id == -1)
		{
			//srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_RADIO);
		}
	}
	else
	{
		srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_RADIO);		
		if (srv_id == -1)
		{
			//srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_TV);
		}
	}
	
	return srv_id;;
}

/*贴图显示当前频道号*/
static D_Result
update_chan_num(D_U8 show_cnt)
{
	D_Frame *frm = &atv_chan_input_window;
	D_U8 idx, start;
	D_Image *img;
	D_Visual *vis;
	
	show_cnt = D_MIN(show_cnt, D_CHAN_NUM_LEN);
	start = D_CHAN_NUM_LEN - show_cnt;
	
	for(idx = 0; idx < D_CHAN_NUM_LEN; idx++)
	{
		img = (idx < start) ? NULL : d_gui_get_image(NumImgId[key_input[idx]]);
		vis = d_frame_get_control(frm, VisNumId[idx]);
		{
			d_image_box_set_image(vis, img);
		}
	}

	return D_OK;
}


static D_Result 
try_play_new_chan(void)
{
	D_U8 i;
	D_S16	num = 0;	
	D_DBSrvID db_srv_id;
	
	for (i = 0; i < D_CHAN_NUM_LEN; i++) 
	{
		num = num * 10 + key_input[i];			
	}
#ifdef D_TV_SUPPORT_IPTV
 	if( getIptvRunFlag() )
	{
	  	try_play_new_iptvchan(  num );
	}
	else
#endif
	{
	db_srv_id =get_db_srv_id_by_num(num);
	
	if (db_srv_id != -1)
	{
		p_stb_player_play_srv(curr_player_id, db_srv_id);
	}
	else
	{
/*		d_pop_msg_show (D_POP_MSG_PRIO_MSG_3, 
			D_GUI_LAYER_VIDEO_MESSAGE, D_POP_MSG_MSG,
			NULL, d_gui_get_text(IDS_INVALID_CHAN_NUM),
			2000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL,0);	*/
	}
	}
	return D_OK;
}


/** @brief 事件处理回调*/
static D_Result
chan_input_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type) 
	{
		case D_EVT_TIMER:
			if(!change_chan)
			{	
				/*3秒超时切换节目*/	
				update_chan_num(D_CHAN_NUM_LEN);	
				try_play_new_chan();
				change_chan = D_TRUE;
				
				if (delay_timer != D_INVALID_HANDLE)
				{
					d_timer_reset(delay_timer, D_SHOW_CHANGED_TIMEOUT);
				}
				return D_OK;
			}				
			else
			{					
				return p_atv_chan_input_window_hide();
			}
			break;
		case D_EVT_FP:
			if ((evt->fp.key >= D_KEY_0) && (evt->fp.key <= D_KEY_9))
			{				
				/*已经进行换台操作，或是输入数目超过，不再响应*/
				if (change_chan  || (count >= D_CHAN_NUM_LEN))
				{
					return D_OK;
				}
				
				memmove(key_input, &key_input[1], (sizeof(D_U8) * (D_CHAN_NUM_LEN - 1)));
				key_input[D_CHAN_NUM_LEN - 1] = evt->fp.key - D_KEY_0;
				count++;

				update_chan_num(count);
				
				/*输入三个数字切换节目*/
				if(count == D_CHAN_NUM_LEN)
				{
					change_chan = D_TRUE;
					
					try_play_new_chan();
					
					/*切换后一定时间后清除频道号显示*/
					if (delay_timer != D_INVALID_HANDLE)
					{
						d_timer_reset(delay_timer, D_SHOW_CHANGED_TIMEOUT);
					}
				}
			}
			switch (evt->fp.key)
			{
				case D_KEY_OK:
                            case D_KEY_PNL_OK:
					/*按确定键切换节目*/
					if (!change_chan)
					{
						update_chan_num(D_CHAN_NUM_LEN);	
						try_play_new_chan();
						change_chan = D_TRUE;
						
						/*切换后2秒清除显示*/
						if (delay_timer != D_INVALID_HANDLE)
						{
							d_timer_reset(delay_timer, D_SHOW_CHANGED_TIMEOUT);
						}
					}
					return D_OK;
				case D_KEY_ESC:
					return p_atv_chan_input_window_hide();
				case D_KEY_LEFT:
				case D_KEY_RIGHT:
				case D_KEY_MUTE:
				case D_KEY_INFO:
				case D_KEY_TV_RADIO:
				case D_KEY_BACK:
				case D_KEY_UP:
				case D_KEY_DOWN:
					p_atv_chan_input_window_hide();
					return D_ERR;
				default:
					break;
			}
			return D_OK;
		case D_EVT_DESTROY:
			if (delay_timer != D_INVALID_HANDLE)
			{
				d_timer_destroy (delay_timer);
				delay_timer = D_INVALID_HANDLE;
			}
			d_vis_unsubscribe_evt (vis);
			break;
		default:
			break;
	}

	return D_ERR;
}

/** @brief 频道号输入窗口初始化*/
D_Result
atv_chan_input_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual	*vis;
	D_MSec   ms;	

	update_chan_num(count);
		
	vis = d_frame_get_control (frm, 0);
	if (vis)
	{
		delay_timer = d_timer_create (NULL, D_SHOW_TIMEOUT, d_gui_get_queue ());
		d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, delay_timer);
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK|D_EVT_AUDIO_KEY_MASK |
								D_EVT_TV_MASK, D_INVALID_HANDLE);
		d_vis_set_handler (vis, chan_input_handler);
	}
		
	return D_OK;
}

/** @brief 显示频道号输入窗*/
D_Result
p_atv_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT
{
	D_U8       i;
	
	for(i=0; i<D_CHAN_NUM_LEN; i++)
	{
		key_input[i] = 0;
	}
	
	change_chan = D_FALSE;
			
	count = 1;
	key_input[D_CHAN_NUM_LEN - 1] = key - D_KEY_0;
	
	curr_player_id = player_id;
#ifdef D_TV_SUPPORT_IPTV
 	if( getIptvRunFlag() )
	{
	  	p_iptv_info_close();
	}
	else
#endif
	{
    p_atv_tv_chan_info_window_hide();
	}
	d_gui_open_frame (&atv_chan_input_window, D_GUI_LAYER_IME);
		
	return D_OK;
}


/** @brief 清除频道号输入窗*/
D_Result
p_atv_chan_input_window_hide (void) D_FUNCPOSTFIT
{
	d_gui_close_frame (&atv_chan_input_window);		
	return D_OK;
}

