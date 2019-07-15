/** @file
* @brief 多音频模块
* @author 
* @date 2014-06-12 :  建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDate.h"
#include "dDebug.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pMem.h"
#include "dDBase.h"
#include "pPlayer.h"
#include "pStbMenus.h"
#include "dFileSystem.h"
#include "dMedia.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dPvrReplay.h"
#include "atv_media_movie_info_window.c"



#define MEDIA_PROG_NUM (32)
#define MEDIA_AUDIO_NUM (8)
#define TEXT_MAX_LEN (32)

typedef struct
{
    D_Char str_name[256];
    D_Char str_size[TEXT_MAX_LEN];
    D_Char str_wh[TEXT_MAX_LEN];
	D_U16 audio_cnt;   /*多路音频*/
	D_U16 audio_val;
    D_Char str_audio[MEDIA_AUDIO_NUM][TEXT_MAX_LEN];
    D_Char *str_audio_content[MEDIA_AUDIO_NUM];
    D_MovieAudioInfo audio_info[MEDIA_AUDIO_NUM];
    
	D_PvrProgramInfo ts_prog_info;    
    D_Char str_prog[MEDIA_PROG_NUM][TEXT_MAX_LEN];
    D_Char *str_prog_content[MEDIA_PROG_NUM];
    D_U16 prog_cnt;   /*多路音频*/
    D_U16 prog_val;
    
    D_Visual *vis_name, *vis_size, *vis_wh;
	D_Visual *vis_audio, *vis_prog;
}D_MovieInfoMenuData;

static D_MovieInfoMenuData *movie_info_menu = NULL;
static D_Bool param_set_enable = D_FALSE;
static D_Char *curr_file_name = NULL;
static D_MovieInfo curr_movie_info = {0};
static D_Bool movie_info_valid = D_FALSE;
extern D_U32 movie_audio_select;



/** @brief 取得音频相关信息*/
static D_Result
media_movie_update_info(void)D_FUNCPOSTFIT
{
    D_U32 i;

    sprintf(movie_info_menu->str_name, "%s", curr_file_name);
    p_unit_converter((D_Double)curr_movie_info.filesize, movie_info_menu->str_size);
    if(curr_movie_info.width && curr_movie_info.height && movie_info_valid)
    {
        sprintf(movie_info_menu->str_wh, "%d x %d", curr_movie_info.width, curr_movie_info.height);
    }
    else
    {
        sprintf(movie_info_menu->str_wh, "--");
    }	

    movie_info_menu->audio_cnt = d_media_movie_get_audio_info(movie_info_menu->audio_info, MEDIA_AUDIO_NUM);    
	movie_info_menu->audio_cnt = D_MIN(MEDIA_AUDIO_NUM, movie_info_menu->audio_cnt);
	movie_info_menu->audio_cnt = (movie_info_valid)? movie_info_menu->audio_cnt: 0;
    movie_info_menu->audio_val = 0;
    if(movie_info_menu->audio_cnt)
    {
        movie_info_menu->audio_val = D_MIN(movie_audio_select, (movie_info_menu->audio_cnt - 1));
    }
    movie_info_menu->audio_val = (movie_info_valid)? movie_info_menu->audio_val: 0;
    
	for(i = 0; i < MEDIA_AUDIO_NUM; i++)
	{
	    if(i < movie_info_menu->audio_cnt)
	    {
            sprintf(movie_info_menu->str_audio[i], "%d/%d", (i+1), movie_info_menu->audio_cnt);
        }
        else
        {
            sprintf(movie_info_menu->str_audio[i], (movie_info_valid)? "1/1" : "--");
        }
        movie_info_menu->str_audio_content[i] = movie_info_menu->str_audio[i];
	}
	memset((D_U8*)(&movie_info_menu->ts_prog_info),0,sizeof(D_PvrProgramInfo));
    d_media_movie_get_ts_progs_info((D_Ptr)(&movie_info_menu->ts_prog_info));
    movie_info_menu->ts_prog_info.prog_cnt = D_MIN(movie_info_menu->ts_prog_info.prog_cnt, MEDIA_PROG_NUM);
	movie_info_menu->prog_cnt = D_MIN(MEDIA_PROG_NUM, movie_info_menu->ts_prog_info.prog_cnt);
    movie_info_menu->prog_cnt = (movie_info_valid)? movie_info_menu->prog_cnt: 0;
    movie_info_menu->prog_val = 0;
    if(movie_info_menu->prog_cnt)
    {
        movie_info_menu->prog_val = D_MIN((movie_info_menu->prog_cnt - 1), movie_info_menu->ts_prog_info.play_idx);
    }
	movie_info_menu->prog_val = (movie_info_valid)? movie_info_menu->prog_val: 0;
	
	for(i = 0; i < MEDIA_PROG_NUM; i++)
	{
	    if(i < movie_info_menu->prog_cnt)
	    {
            sprintf(movie_info_menu->str_prog[i], "%d/%d", (i+1), movie_info_menu->prog_cnt);
        }
        else
        {
            sprintf(movie_info_menu->str_prog[i], (movie_info_valid)? "1/1" : "--");
        }
        movie_info_menu->str_prog_content[i] = movie_info_menu->str_prog[i];
	}

    d_label_set_text(movie_info_menu->vis_name, movie_info_menu->str_name);
    d_label_set_text(movie_info_menu->vis_size, movie_info_menu->str_size);
    d_label_set_text(movie_info_menu->vis_wh, movie_info_menu->str_wh);
	d_select_box_set_content(movie_info_menu->vis_audio, movie_info_menu->str_audio_content, movie_info_menu->audio_cnt);
	d_select_box_set_val(movie_info_menu->vis_audio, movie_info_menu->audio_val);
	d_select_box_set_content(movie_info_menu->vis_prog, movie_info_menu->str_prog_content, movie_info_menu->prog_cnt);
	d_select_box_set_val(movie_info_menu->vis_prog, movie_info_menu->prog_val);

	return D_OK;
}

/** @brief 设置音频选择*/
static D_Result
media_movie_info_set_audio(D_U16 audio)D_FUNCPOSTFIT
{
    audio = D_MIN((MEDIA_AUDIO_NUM - 1), audio);
    
    if(movie_info_menu->audio_val != audio && param_set_enable)
    {
        d_media_movie_select_audio((D_Int)movie_info_menu->audio_info[audio].audio_index);
        movie_info_menu->audio_val = audio;
        movie_audio_select = audio;
    }    
	return D_OK;
}

/** @brief 设置节目选择*/
static D_Result
media_movie_info_set_prog(D_U16 prog)D_FUNCPOSTFIT
{
    prog = D_MIN((MEDIA_PROG_NUM - 1), prog);
    
    if(movie_info_menu->prog_val != prog && param_set_enable)
    {
        movie_info_menu->prog_val = prog;
        p_media_movie_full_screen_play_ts_prog(prog);
    }

	return D_OK;
}

/** @brief 事件处理回调*/
static D_Result
media_audio_select_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)  
    {	
        case D_EVT_SELECTED:
            media_movie_info_set_audio(d_select_box_get_val(vis));
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理回调*/
static D_Result
media_prog_select_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)  
    {	
        case D_EVT_SELECTED:
            media_movie_info_set_prog(d_select_box_get_val(vis));
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理回调*/
static D_Result
media_menu_esc_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)  
    {	
        case D_EVT_PRESSED:
            p_atv_media_movie_info_window_hide();
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理回调*/
static D_Result
atv_media_movie_info_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Visual *select;
	
	switch (evt->type) 
	{
		case D_EVT_FP:
			switch (evt->fp.key)
			{
				case D_KEY_ESC:
				case D_KEY_PNL_ESC:
				case D_KEY_BACK:
					p_atv_media_movie_info_window_hide();
					break;
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                case D_KEY_MUTE:
                    return D_ERR;
                    break;
				default:
					break;
			}
			return D_OK;
			break;
		case D_EVT_DESTROY:
			d_vis_unsubscribe_evt (vis);		
			if(movie_info_menu)
			{
				PROJECT_FREE(movie_info_menu);
				movie_info_menu = NULL;
			}
			break;
		default:
			break;
	}

	return D_ERR;
}

/** @brief 窗口初始化*/
D_Result
atv_media_movie_info_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual	*vis;	

	/*分配内存*/
	movie_info_menu = (D_MovieInfoMenuData*)PROJECT_ALLOC(sizeof (D_MovieInfoMenuData));
	if (! movie_info_menu)
		return D_ERR;
		
	memset(movie_info_menu, 0, sizeof (D_MovieInfoMenuData));
    param_set_enable = D_FALSE;
	movie_info_menu->vis_name = d_frame_get_control(frm, ID_MOVIEINFO_LABEL_FILE_NAME);
	movie_info_menu->vis_size = d_frame_get_control(frm, ID_MOVIEINFO_LABEL_SIZE);
	movie_info_menu->vis_wh = d_frame_get_control(frm, ID_MOVIEINFO_LABEL_WH);
	movie_info_menu->vis_audio = d_frame_get_control(frm, ID_MOVIEINFO_SELECT_AUDIO);
    movie_info_menu->vis_prog = d_frame_get_control(frm, ID_MOVIEINFO_SELECT_PROG);

    d_vis_set_handler(movie_info_menu->vis_audio, media_audio_select_handler);
	d_vis_set_handler(movie_info_menu->vis_prog, media_prog_select_handler);

	/*暂时不允许选择音频*/
	d_vis_set_focus(movie_info_menu->vis_prog);
	d_vis_enable(movie_info_menu->vis_audio, D_FALSE);
	
    vis = d_frame_get_control(frm, ID_MOVIEINFO_BUTTON_ESC);
    if(vis)
    {
        d_vis_set_handler(vis, media_menu_esc_handler);
    }
	
    media_movie_update_info();

	vis = d_frame_get_control (frm, 0);
	if (vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler (vis, atv_media_movie_info_window_handler);
	}
	param_set_enable = D_TRUE;
	return D_OK;   
}  

/** @brief 显示电影信息窗口*/
D_Result
p_atv_media_movie_info_window_show (D_Char *filename, D_MovieInfo *info, D_Bool valid, D_Coord x, D_Coord y) D_FUNCPOSTFIT
{
    D_FrameControlDescr *descr;
    
    d_gui_close_frame (&atv_media_movie_info_window);
    descr = (D_FrameControlDescr *)(atv_media_movie_info_window.ctrl_descrs);
    descr->x = x;
    descr->paly = y;
    descr->ntscy = y;
    curr_movie_info = *info;
    curr_file_name = filename;
    movie_info_valid = valid;
    return d_gui_open_frame(&atv_media_movie_info_window, D_GUI_LAYER_IME);
}

/** @brief 显示电影信息窗口*/
D_Result
p_atv_media_movie_info_window_update (D_Char *filename, D_MovieInfo *info, D_Bool valid) D_FUNCPOSTFIT
{
    if(d_frame_is_loaded(&atv_media_movie_info_window))
    {
        param_set_enable = D_FALSE;
        curr_movie_info = *info;
        curr_file_name = filename;
        movie_info_valid = valid;
        media_movie_update_info();
        param_set_enable = D_TRUE;
    }
	return D_OK;	
}

/** @brief 显示电影信息窗口*/
D_Result
p_atv_media_movie_info_window_update_wh (D_MovieInfo *info) D_FUNCPOSTFIT
{
    if(d_frame_is_loaded(&atv_media_movie_info_window))
    {
        if(curr_movie_info.width != info->width || curr_movie_info.height != info->height)
        {
            curr_movie_info.width = info->width;
            curr_movie_info.height = info->height;
            if(curr_movie_info.width && curr_movie_info.height && movie_info_valid)
            {
                sprintf(movie_info_menu->str_wh, "%d x %d", curr_movie_info.width, curr_movie_info.height);
            }
            else
            {
                sprintf(movie_info_menu->str_wh, "--");
            }
            d_label_set_text(movie_info_menu->vis_wh, movie_info_menu->str_wh);
        }
    }
	return D_OK;	
}

/** @brief 清除信息窗口*/
D_Result
p_atv_media_movie_info_window_hide (void) D_FUNCPOSTFIT
{
	return d_gui_close_frame (&atv_media_movie_info_window);
}

