#include "dFP.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "pMem.h"
#include "pFile_Scan.h"
#include "dTxt.h"
#include "dMedia.h"
#include "pConvCode.h"
#include "pStbAtvMenus.h"

#include "atv_media_txt_full_window.c"


/*������ȫ��ʱ��λ��*/
#define TXT_X_ZOOM_LOCATION		105
#define TXT_Y_ZOOM_LOCATION		95
#define TXT_W_ZOOM_LOCATION	739
#define TXT_H_ZOOM_LOCATION		293

typedef struct
{
	D_Char	mediaTxtPathName[D_PATH_LENGTH];	/*�ļ���*/
	D_Char	mediaTxtDisplayName[D_PATH_LENGTH]; /*ת����ŵ�λ��*/
	D_U32 	mediaTxtKeyFlag;	/*��¼�Ƿ������ϻ�������1: ���Ϸ�ҳ 2: ���·�ҳ*/
	D_Coord x;			/*����ֵ*/
	D_Coord y;
	D_Coord w;
	D_Coord h; 
	D_U32 TotalPage;// 1 2 3...
	D_U32 CurPage;//0 1 2...
}MediaTxtData;

static MediaTxtData* media_txt_data = NULL;

/*
* @brief ����������������¼���handler
* @param[in] vis: ����ָ��
* @param[in] evt : �¼�ָ��
*/
static D_Result
media_txt_full_event(D_Visual *vis, D_Event *evt)D_FUNCPOSTFIT
{
	if(evt->type != D_EVT_DRAW)
		return D_ERR;
	
	if (media_txt_data->mediaTxtKeyFlag == 1)
		d_txt_show(TXT_PAGE_UP, vis);
	else if (media_txt_data->mediaTxtKeyFlag == 2)
		d_txt_show(TXT_PAGE_DOWN, vis);
	else
		d_txt_show(0,vis);
	media_txt_data->mediaTxtKeyFlag = 0;
	return D_OK;	
}

#if 0
/*
* @brief ���õ��������Ϣ
*/
static D_Result
media_txt_set_show_info(void) D_FUNCPOSTFIT
{
	D_Visual* vis;
	char *file_name = NULL;

	vis = d_frame_get_control(&atv_media_txt_full_window, ID_TXT_FILE_NAME);
	if(vis)
	{	
		file_name = strrchr(media_txt_data->mediaTxtPathName, '/');
		if(file_name)
			file_name++;
		else
			return D_ERR;
	
#ifndef D_SYSTEM_WIN32
            p_cc_utf8_to_sys((D_U8*)media_txt_data->mediaTxtDisplayName, D_PATH_LENGTH, (D_U8*)file_name, strlen(file_name));
#else
            /*pc���治��Ҫת��*/
            strcpy(media_txt_data->mediaTxtDisplayName, file_name);
#endif
		d_label_set_text(vis, media_txt_data->mediaTxtDisplayName);		
	}
	return D_OK;
}
#endif

/*
* @brief ���������������handler
* @param[in] vis: ����ָ��
* @param[in] evt : �¼�ָ��
*/
static D_Result
media_txt_full_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_S32  device_state = 0;
	D_Visual *area_vis = d_frame_get_control(&atv_media_txt_full_window,  ID_TXT_DRAW_AREA);
	D_Visual *scoll_vis = d_frame_get_control(&atv_media_txt_full_window,  ID_EBOOK_SCROLL);
	
	switch(evt->type)
	{
		case D_EVT_FP:
			{
				switch(evt->fp.key)
				{
					case D_KEY_UP:
					case D_KEY_PNL_U:
					case D_KEY_LEFT:
					case D_KEY_PNL_L:
					case D_KEY_PGUP:
						if(media_txt_data->CurPage == 0)
							return D_OK;
						media_txt_data->mediaTxtKeyFlag = 1;
						d_vis_update(area_vis, NULL);
						media_txt_data->CurPage--;
						d_scroll_bar_set_val(scoll_vis,  (media_txt_data->CurPage * 100) / (media_txt_data->TotalPage - 1));
						return D_OK;
						break;
					case D_KEY_DOWN:
					case D_KEY_PNL_D:
					case D_KEY_RIGHT:
					case D_KEY_PNL_R:
					case D_KEY_PGDOWN:
						if(media_txt_data->CurPage == (media_txt_data->TotalPage - 1))
							return D_OK;
						media_txt_data->mediaTxtKeyFlag = 2;
						d_vis_update(area_vis, NULL);
						media_txt_data->CurPage++;
						d_scroll_bar_set_val(scoll_vis,  (media_txt_data->CurPage * 100) / (media_txt_data->TotalPage - 1));
						return D_OK;
						break;
					case D_KEY_BACK:
					case D_KEY_ESC:
						d_txt_close();
						d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
						return D_OK;
					default:
						//Txt_show(0,area_vis);
						break;
				}
			}
			break;
		case D_EVT_DESTROY:
			d_vis_unsubscribe_evt(vis);
			AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_TXT_FULLSCREEN;
			if(media_txt_data)
			{
				PROJECT_FREE(media_txt_data);
				media_txt_data = NULL;
			}
			break;
		default:
			break;
	}

	return D_ERR;
}


/*
* @brief ������ȫ���˵���ʼ��
* @param[in] frm: ���������ָ��
*/
D_Result
atv_media_txt_full_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual * vis;

	//media_txt_set_show_info();

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, media_txt_full_window_handler);
	}

	vis = d_frame_get_control(frm, ID_TXT_DRAW_AREA);
	if(vis)
	{
		d_vis_set_handler(vis, media_txt_full_event);
	}

	media_txt_data->mediaTxtKeyFlag = 0;

	if(D_OK != d_txt_content_init(media_txt_data->mediaTxtPathName, media_txt_data->x, media_txt_data->y, media_txt_data->w, media_txt_data->h, 0xffffffff,24,0,0xff0151ab))
	{
		d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                           "�ļ���ʧ��", 3000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
	}
	
	AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_TXT_FULLSCREEN;
	d_txt_get_num(&media_txt_data->TotalPage);

	return D_OK;
}


D_Result
p_media_txt_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT
{

	media_txt_data = (MediaTxtData*)PROJECT_ALLOC(sizeof(MediaTxtData));
	if(!media_txt_data)
	{
		return D_ERR;
	}

	memset(media_txt_data, 0x00, sizeof(MediaTxtData));

	strncpy(media_txt_data->mediaTxtPathName, path_name, sizeof(media_txt_data->mediaTxtPathName));

	media_txt_data->x = TXT_X_ZOOM_LOCATION;
	media_txt_data->y = TXT_Y_ZOOM_LOCATION;
	media_txt_data->w = TXT_W_ZOOM_LOCATION;
	media_txt_data->h = TXT_H_ZOOM_LOCATION;
	
	return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_txt_full_window, D_CLEAR_NONE);
}

D_Result
p_media_txt_full_screen_window_hide() D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_media_txt_full_window))
    {
        /*ֹͣ����*/
        d_txt_close();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_OK;
}


