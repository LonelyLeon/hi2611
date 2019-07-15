#include <stdio.h>
#include <string.h>
#include "pMem.h"
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pStbAtvMenus.h"
#include "dadporting.h"
#include "patvGuiResource.h"
#include "pPlayer.h"
#include "iptv_list_window.c"
#include "iptv_player_window.c"
#include "auth.h"
#include "dNetTsPlay.h"
#include "dAV.h"
#include "iptv_channel_info_window.c"


#define BUFFER_LEN  64

#define CHAN_LIST_ROW_CNT       11///16   目前显示列表的行数为6 
#define CHAN_NUM_BUF_LEN        4
#define CHAN_NAME_BUF_LEN       64
#define MAX_CHAN_CNT            1000

#define IPTV_LIST_SHOW_TIME  30000

static D_HTimer	delay_timer = D_INVALID_HANDLE;

volatile int status_running;
volatile D_U8 is_loading = D_FALSE; 

D_TaskAttr	taskAttr;
D_HTask        iptvHandle = D_INVALID_HANDLE;

D_TaskAttr	taskAttr1;
D_HTask		hTask_auth = D_INVALID_HANDLE;

typedef struct
{
	D_Char          type_name[CHAN_LIST_ROW_CNT][CHAN_NAME_BUF_LEN];
	D_Char          type_total[BUFFER_LEN];
	D_DBRecset   rset;
	D_ID            type_ids[MAX_CHAN_CNT];
} ChanListType;

typedef struct
{
	D_Char          date_num[CHAN_LIST_ROW_CNT][CHAN_NUM_BUF_LEN];
	D_Char          data_name[CHAN_LIST_ROW_CNT][CHAN_NAME_BUF_LEN];
	D_Char          data_total[BUFFER_LEN];
	D_DBRecset      rset;
	D_ID            data_ids[MAX_CHAN_CNT];
}ChanListData;

extern D_Frame iptv_login_window;
extern void p_iptv_info_show( );

static D_U8 focus_flag; //0: left list 1:right list
static ChanListData  *list_data = NULL;
static ChanListType *list_type = NULL;
static D_U8 menu_lang;

static D_ID curr_ch_typeid = -1;
static D_ID curr_ch_id = -1;
static D_U8 in_iptv = 0;
static D_U8 is_up_down = 0;  //Whether to switch channels with press the up and down keys
static D_U8 is_first_key = 0;  //first change channel, react immediatly
static D_U16  _resend = 0;
static D_ID curr_ch_cnt = 0; //The current program number to be played
static D_U8 is_display = 0; //Whether the prompt message is being displayed
static int type_count = 0;

D_Char char_buff[CHAN_NAME_BUF_LEN];
D_U8 curmenu = 0;  // 0: play window  1: list window


void * iptv_run(void *d);

static D_Result getTypeReset( D_DBRecset *rset )
{
	int i = 0;

	type_count = 0;
	
	Authenticator * auth;
	auth = OTT_get_default_auth();

	GList * tmp = NULL;
	ProgramCategory *elem = NULL;
	
	SEE("%d\n", auth->authReply.code);
	
	for(tmp = auth->authReply.category_list; tmp; tmp = g_slist_next(tmp))
	{
		elem = tmp->data;
		//printf("tag: %s, title: %s, parentId: %d, type: %d, parentOrder:%d, categoryId:%d, order:%d\n", elem->tag, elem->title, elem->parentId, elem->type, elem->parentOrder, elem->categoryId, elem->order);
		//if(elem->type == 0 || elem->type == 4 || elem->type == 8 || elem->type == 9)
		
		//live：0，vod：1， live recommendation:4,vod recommendation:6, series:7, adult live:8, adult live:9
		//目前只显示 live 0 直播 
		if(elem->type == 0)
		{
			d_dbase_rset_add(rset, i);
			type_count++ ;
		}
		i++;
	}
	
	rset->cnt = type_count;
	
	return D_OK;
}

static D_Result getDateReset( D_DBRecset *rset )
{
	int i = 0;
	
	Authenticator * auth;
	auth = OTT_get_default_auth();

	GList * tmp = NULL;
	ProgramUrl *elem = NULL;
	
	for(tmp = auth->authReply.program_list; tmp; tmp = g_slist_next(tmp))
	{
		elem = tmp->data;
	//	printf("name: %s\n url: %s\n", elem->name, elem->url); 
	
		d_dbase_rset_add(rset, i);
		i++;
	}
	
	SEE("%d\n\n\n", i);
	rset->cnt = i;

	return D_OK;
}

D_Result get_iptv_type_info (D_DBSrvID id, ProgramCategory *info) D_FUNCPOSTFIT
{
	Authenticator * auth;
	auth = OTT_get_default_auth();
	
	ProgramCategory *elem = NULL;
	
	elem = g_slist_nth_data(auth->authReply.category_list, id);

	if(info->tag)
		g_free(info->tag);	
	info->tag = g_strdup(elem->tag);

	if(info->title)
		g_free(info->title);
	info->title = g_strdup(elem->title);

	info->parentId = elem->parentId;

	if(info->icon)
		g_free(info->icon);
	info->icon = g_strdup(elem->icon);

	info->type = elem->type;

	info->parentName = strdup(elem->parentName);

	info->parentOrder = elem->parentOrder;

	info->categoryId = elem->categoryId;

	info->order = elem->order;
	
	return D_OK;
}

D_Result get_iptv_date_info (D_DBSrvID id, ProgramUrl *info) D_FUNCPOSTFIT
{
	Authenticator * auth;
	auth = OTT_get_default_auth();
	
	ProgramUrl *elem = NULL;
	
	elem = g_slist_nth_data(auth->authReply.program_list, id);

	if(info->name)
		g_free(info->name);	
	info->name = g_strdup(elem->name);

	if(info->url)
		g_free(info->url);
	info->url = g_strdup(elem->url);
	
	return D_OK;
}

static D_Result set_select_type_title()
{
	D_Frame *frm = &iptv_list_window;
	D_Visual    *label_vis, *list_vis;
	D_ID        focus;

	label_vis = d_frame_get_control(frm, ID_CHANNEL_LIST_LABEL_LIST);
	list_vis = d_frame_get_control(frm, ID_CHANNEL_LIST_TYPE);
	
	focus = d_list_get_focus (list_vis, NULL, NULL);
	focus = focus % CHAN_LIST_ROW_CNT;
	MSG("focus: %d\n", focus);	
	d_label_set_text(label_vis, list_type->type_name[focus]);
	
	return D_OK;
}


/** @brief获取IPTV节目列表数据*/
static D_Result get_list_data(D_Visual *vis)
{
	D_DBSrvID srv_id;
	D_U16 col = 0;
	D_StbPlayer *player;
	player = p_stb_get_player (0);

	D_Visual	*rightList;
	D_Frame *frm = &iptv_list_window;
	
	rightList = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);

	d_dbase_rset_empty(&list_data->rset);///如果rset为空将没有节目显示出来。

	getDateReset(&list_data->rset);
	if(list_data->rset.cnt==0){
		D_DUMP ("NO DATA IPTV\n");
	}

	d_vis_set_focus(rightList);    
	focus_flag = 1;   

	MSG("list data cnt: %d\n", list_data->rset.cnt);

	d_list_set_max_row (vis, list_data->rset.cnt);///设置列表最大行数

	if(curr_ch_id == -1)
	{
		curr_ch_id = 0;
	}
	
	if( curr_ch_id >=0 &&  curr_ch_id <list_data->rset.cnt)
	{
		d_list_set_focus(vis, curr_ch_id, 0); ///第一行聚焦
	}
	else
	{
		curr_ch_id = 0;
		d_list_set_focus(vis, 0, 0); ///第一行聚焦
	}
	
	return D_OK;
}

/** @brief获取iptvTYPE列表数据*/
static D_Result get_list_type(D_Visual *vis)
{
	D_DBSrvID srv_id;
	D_U16 col = 0;
	D_StbPlayer *player;
	player = p_stb_get_player (0);

	d_dbase_rset_empty(&list_type->rset);///如果rset为空将没有节目显示出来。

	getTypeReset(&list_type->rset);
	
	if(list_type->rset.cnt==0){
		D_DUMP ("NO TYPE IPTV\n");
	}


	d_list_set_max_row (vis, list_type->rset.cnt);///设置列表最大行数

	MSG("type: %d\n", curr_ch_typeid);
	if(curr_ch_typeid == -1)
	{
		curr_ch_typeid = 0;
	}

	if( curr_ch_typeid >=0 &&  curr_ch_typeid <list_type->rset.cnt)
	{
		d_list_set_focus(vis, curr_ch_typeid, 0); ///第一行聚焦
	}
	else
	{
		d_list_set_focus(vis, 0, 0); ///第一行聚焦
	}

	return D_OK;
}

/** @brief 更新IPTV TYPE列表显示*/
static D_Result
iptvlist_update_type (D_Visual *vis) D_FUNCPOSTFIT
{
	D_ID                start, i;
	ProgramCategory ptinfo;
	D_DBSrvID   srv = -1;
	D_Image     *img;
	D_Frame *frm = &iptv_list_window;

	memset(&ptinfo, 0, sizeof(ptinfo));

	start = d_list_get_first_line_id (vis);
	for (i = start; i < start + CHAN_LIST_ROW_CNT; i++)
	{
		if (i >= list_type->rset.cnt)
		{
			/*清空显示*/
			d_list_set_text (vis, i, 0, NULL);
			d_list_set_text (vis, i, 1, NULL);
			if(i == 0) ///无节目，显示无节目。
			{
				if( menu_lang == D_LANG_ENG )
					strncpy (list_type->type_name[0], "No IPTV TYPE", sizeof (list_type->type_name[0]) - 1);
				else
					strncpy (list_type->type_name[0], "没有任何IPTV", sizeof (list_type->type_name[0]) - 1);

				d_list_set_text (vis, i, 1, list_type->type_name[0]);
			}
		}
		else
		{
			D_ID    row = i - start;

			srv = list_type->rset.ids[i];
			 if (get_iptv_type_info (srv, &ptinfo) >= 0)
			{
				sprintf(list_type->type_name[row], "%s", ptinfo.title);
				d_list_set_text (vis, i, 0, list_type->type_name[row]);
			}
		}
	}
	
	g_free(ptinfo.tag);	
	g_free(ptinfo.title);
	g_free(ptinfo.icon);
	
	return D_OK;
}



/** @brief 更新列表显示*/
static D_Result
iptvlist_update_list (D_Visual *vis) D_FUNCPOSTFIT
{
	D_ID                start, i;
	ProgramUrl	pinfo;
	D_DBSrvID   srv = -1;
	D_Image     *img;
	D_Frame *frm = &iptv_list_window;

	start = d_list_get_first_line_id (vis);

	MSG("%d\n", start);
	for (i = start; i < start + CHAN_LIST_ROW_CNT; i++)
	{
		if (i >= list_data->rset.cnt)
		{
			/*清空显示*/

			d_list_set_text (vis, i, 0, NULL);
			d_list_set_text (vis, i, 1, NULL);
			
			if(i == 0) ///无节目，显示无节目。
			{
				if( menu_lang == D_LANG_ENG )
					strncpy (list_data->data_name[0], "No IPTV Program", sizeof (list_data->data_name[0]) - 1);
				else
					strncpy (list_data->data_name[0], "没有IPTV节目", sizeof (list_data->data_name[0]) - 1);

				d_list_set_text (vis, i, 1, list_data->data_name[0]);
			}

		}
		else
		{
			D_ID    row = i - start;

			srv = list_data->rset.ids[i];
			
			memset(&pinfo, 0, sizeof(pinfo)); 
			MSG("\n");
	
			if (get_iptv_date_info (srv, &pinfo) >= 0)
			{
				MSG("i:%d name:%s\n", i, pinfo.name);
				/*显示IPTV节目号*/
				sprintf (list_data->date_num[row],  "%03d",i+1 );
				d_list_set_text (vis, i, 0, list_data->date_num[row]);

				/*舷允綢PTV节目名*/
				if (strlen (pinfo.name))
				{
					sprintf(list_data->data_name[row], pinfo.name);
				}
				
				d_list_set_text (vis, i, 1, list_data->data_name[row]);
			}
		}
	}

	return D_OK;
}


/** @brie列表控件回调函数*/
static D_Result
program_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	if (delay_timer != D_INVALID_HANDLE)
	{
		d_timer_reset(delay_timer, IPTV_LIST_SHOW_TIME);
	}

	switch (evt->type)
	{
		case D_EVT_DATA_CHANGED:
			D_DUMP("\n");
			return iptvlist_update_list(vis);
			break;
		case D_EVT_SELECTED:
			return D_OK;
			break;
		default:
			break;
	}
	return D_ERR;
}

/** @brie列表控件回调函数*/
static D_Result
program_list_type_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	if (delay_timer != D_INVALID_HANDLE)
	{
		d_timer_reset(delay_timer, IPTV_LIST_SHOW_TIME);
	}
	switch (evt->type)
	{
		case D_EVT_DATA_CHANGED:
			return iptvlist_update_type(vis);
			break;
		case D_EVT_SELECTED:
			return D_OK;
			break;
		default:
			break;
	}
	return D_ERR;
}


/** @brie列表控件回调函数*/
static D_Result
set_list_focus (void) D_FUNCPOSTFIT
{
	D_Frame *frm = &iptv_list_window;
	D_Visual *leftList, *rightList;
	D_ID focus;
	
	leftList = d_frame_get_control (frm, ID_CHANNEL_LIST_TYPE);
	rightList = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);

	focus_flag = !focus_flag;
	
	if(focus_flag == 0)
	{
		d_vis_set_focus(leftList);
	}
	else
	{
		focus = d_list_get_focus (leftList, NULL, NULL);

		if(focus != curr_ch_typeid)
		{
			if ((focus >= 0) && (focus < list_type->rset.cnt))
			{
				curr_ch_typeid = focus;
				MSG("type: %d\n", curr_ch_typeid);
				curr_ch_id = 0;
				d_list_set_focus(rightList, curr_ch_id, 0);
				set_select_type_title();

				d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
					D_GUI_LAYER_MESSAGE,
					D_POP_MSG_MSG,   "TIPS", "Loading the program,Please wait...",
					0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
				OTT_auth_get_cur_epg(list_type->type_ids[focus]);

				if(iptvHandle != D_INVALID_HANDLE)
				{
					status_running = 0;
					d_task_wait(300);
					//d_task_kill(iptvHandle);
					d_task_join(iptvHandle);
					iptvHandle = D_INVALID_HANDLE;
				}
				status_running = 1;
				iptvHandle= d_task_create(&taskAttr, (D_TaskEntry)iptv_run, NULL);
			}
		}
		else
		{
			d_vis_set_focus(rightList);    
		}
	}
	
	d_vis_update( leftList, NULL);
	d_vis_update( rightList, NULL);
	
	return D_OK;
}

/** @brief 事件处理*/
static D_Result
iptv_list_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &iptv_list_window;
	D_Visual    *list;
	D_ID focus, srv;

	Authenticator * auth;
	ProgramUrl *elem = NULL;

	switch (evt->type)
	{
			//	MSG("\n");
		case D_EVT_FP:

				MSG("\n");
			if (delay_timer != D_INVALID_HANDLE)
			{
				MSG("\n");
				d_timer_reset(delay_timer, IPTV_LIST_SHOW_TIME);
			}
			switch (evt->fp.key)
			{
				case D_KEY_SOURCE:
				case D_KEY_PNL_SOURCE:

	//				p_atv_signal_select_show();
					return D_OK;
					break;
				case D_KEY_ESC:
				case D_KEY_MENU:
				case D_KEY_PNL_MENU:
				case D_KEY_BACK:
					MSG("D_KEY_BACK !\n");
					p_stb_exit_iptv();
					return D_OK;
					break;

				case D_KEY_LEFT:
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
				case D_KEY_PNL_L:

					set_list_focus();

					return D_OK;
					break;

				case D_KEY_OK:
				case D_KEY_PNL_OK:

					MSG("D_KEY_OK !\n");
					if(!focus_flag)
					{
						list = d_frame_get_control (frm, ID_CHANNEL_LIST_TYPE);
						
						focus = d_list_get_focus (list, NULL, NULL);

						if ((focus >= 0) && (focus < list_type->rset.cnt))
						{
							curr_ch_typeid = focus;
							set_select_type_title();
							d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
									D_GUI_LAYER_MESSAGE,
									D_POP_MSG_MSG,   "TIPS", "Loading the program,Please wait...",
									0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
							OTT_auth_get_cur_epg(list_type->type_ids[focus]);
							
							if(iptvHandle !=D_INVALID_HANDLE)
							{
								status_running = 0;
								d_task_wait(300);
								//d_task_kill(iptvHandle);
								d_task_join(iptvHandle);
								iptvHandle = D_INVALID_HANDLE;
							}
							status_running = 1;
							curr_ch_id = 0;
							list = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
							d_list_set_focus(list, curr_ch_id, 0);
							iptvHandle= d_task_create(&taskAttr, (D_TaskEntry)iptv_run, NULL);
						}
						if ((focus >= 0) && (focus < list_data->rset.cnt))
						{
							curr_ch_typeid = focus;
						}

						return D_OK;
					}

					list = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
					focus = d_list_get_focus (list, NULL, NULL);
					curr_ch_cnt = list_data->rset.cnt;

					if ((focus >= 0) && (focus < list_data->rset.cnt))
					{
						srv = list_data->data_ids[focus];
						{
							MSG("id: %d\n", srv);

							is_up_down = 0;
							d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
							d_media_netts_stop();
							d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
									D_GUI_LAYER_MESSAGE,
									D_POP_MSG_MSG,   "TIPS", "Loading the program,Please wait...",
									0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
							d_media_netts_play(NULL, srv, 0, 0, 0, 0, 0, NULL);
							curr_ch_id = focus;
							d_gui_upper_menu ();
							// 节目已经在播放退出。
							p_iptv_info_show();
							is_display = 1;
							is_loading = D_TRUE;
							MSG("is_loading hide  %d  %d\n", is_loading,is_display);
							//p_atv_tv_iptv_playwin_show();
						}
					}

					MSG("\n");
					return D_OK;
					break;

				default:
					break;
			}

			break;
	      
		case D_EVT_USER:
			
			if( evt->user.param1 == USER_MSG_PARAM1_IPTV_TIPSHOW )
			{
				D_DUMP("iptv_list_window_handler receive the massage USER_MSG_PARAM1_IPTV_PASSCODE, the tips is %s\n", (D_Char *)(evt->user.param2));
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
				d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
						D_GUI_LAYER_MESSAGE,
						D_POP_MSG_MSG,   "TIPS", (D_Char *)(evt->user.param2),
						0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
			}
			else if( evt->user.param1 == USER_MSG_PARAM1_IPTV_TIPHIDE )
			{
				D_DUMP("iptv_list_window_handler receive the massage USER_MSG_PARAM1_IPTV_TIPHIDE\n");
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
			}
			else if( evt->user.param1 == USER_MSG_PARAM1_IPTV_LISTDATE)
			{
				D_DUMP("iptv_list_window_handler receive the massage USER_MSG_PARAM1_IPTV_LISTDATE\n");
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);

				list = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
				vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LABEL_TOTAL_LIST);

				get_list_data(list);    

				iptvlist_update_list(list);

				if( menu_lang == D_LANG_ENG)
				{
					sprintf(list_data->data_total, "total: %d", list_data->rset.cnt );
					d_label_set_text(vis, list_data->data_total ); 
				}
				else
				{
					sprintf(list_data->data_total, "总数:%d",  list_data->rset.cnt );
					d_label_set_text(vis, list_data->data_total ); 
				}
			}
			return D_OK;
			break;

		case D_EVT_TIMER:
			MSG("TIMER----!\n");
			if (delay_timer != D_INVALID_HANDLE)
			{
				d_gui_upper_menu ();
			}
			break;

		case D_EVT_DESTROY:
			MSG("D_KEY_DESTROY !\n");
			if (delay_timer != D_INVALID_HANDLE)
			{
				d_timer_destroy (delay_timer);
				delay_timer = D_INVALID_HANDLE;
			}
			d_vis_unsubscribe_evt (vis);
			PROJECT_FREE(list_type);
			PROJECT_FREE(list_data);
			list_type = NULL;
			list_data = NULL;

			break;

		default:

			break;
	}

	return D_ERR;
}

/** @brief 窗口初始化*/
D_Result
iptv_list_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual        *vis;
	D_Result ad_check = D_ERR;

	type_count = 0;
	list_data = (ChanListData*) PROJECT_ALLOC (sizeof (ChanListData));
	list_type = (ChanListType*) PROJECT_ALLOC (sizeof (ChanListType));
	memset(list_data, 0x00, sizeof(ChanListData));
	memset(list_type, 0x00, sizeof(ChanListType));
	menu_lang = p_conf_get_lang();
	curmenu = 1;


	d_dbase_rset_init (&list_type->rset, MAX_CHAN_CNT, list_type->type_ids);
	d_dbase_rset_init (&list_data->rset, MAX_CHAN_CNT, list_data->data_ids);

	vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
	if (vis)
	{
		d_vis_set_focus(vis);    
		get_list_data(vis);    
		iptvlist_update_list(vis);
		d_vis_set_handler(vis, program_list_handler);        
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
	}

	vis = d_frame_get_control (frm, ID_CHANNEL_LIST_TYPE);
	if (vis)
	{
		get_list_type(vis);    
		iptvlist_update_type(vis);
		d_vis_set_handler(vis, program_list_type_handler);     
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
		set_select_type_title();
	}
	
	focus_flag = 1;   
	D_DUMP ("iptv_list_window_init 2\n");

	vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LABEL_TOTAL_TYPE);
	if( menu_lang == D_LANG_ENG)
	{
		sprintf(list_type->type_total, "total: %d",  list_type->rset.cnt );
		d_label_set_text(vis, list_type->type_total ); 
	}
	else
	{
		sprintf(list_type->type_total, "总数: %d",list_type->rset.cnt );
		d_label_set_text(vis, list_type->type_total ); 
	}
	vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LABEL_TOTAL_LIST);
	if( menu_lang == D_LANG_ENG)
	{
		sprintf(list_data->data_total, "total: %d", list_data->rset.cnt );
		d_label_set_text(vis, list_data->data_total ); 
	}
	else
	{
		sprintf(list_data->data_total, "总数:%d",  list_data->rset.cnt );
		d_label_set_text(vis, list_data->data_total ); 
	}

	vis = d_frame_get_control (frm, 0);
	if (vis)
	{
		/*设定窗口事件回调*/
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
		d_vis_subscribe_evt (vis, D_EVT_USER_MASK , D_INVALID_HANDLE);
	
		d_vis_set_handler (vis, iptv_list_window_handler);
	      /*创建前端定期检查定时器*/
//	        delay_timer = d_timer_create (NULL,IPTV_LIST_SHOW_TIME, d_gui_get_queue ());
	        if(delay_timer != D_INVALID_HANDLE)
	        {
			d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, delay_timer);
	        }
	}

	return D_OK;
}

/** @breif 显示窗口*/
D_Result
p_atv_tv_iptv_list_show (void) D_FUNCPOSTFIT
{
	return d_gui_enter_menu (&iptv_list_window, D_TRUE);
}

/** @breif 显示窗口*/
D_Result
p_atv_tv_iptv_playwin_show (void) D_FUNCPOSTFIT
{
	return d_gui_enter_menu (&iptv_list_window, D_TRUE);
}

D_Result iptv_play_window_msg( D_Handle handle,  D_U32 param1, D_U32 param2) {
	D_UserMsg msg;
	if(handle==D_INVALID_HANDLE)
	{
		if(curmenu==0){
		msg.handle = (D_Handle)(&iptv_player_window);
		}else if(curmenu==1){
			msg.handle = (D_Handle)(&iptv_list_window);
		}else{
			return D_OK;
		}
	}else{
		msg.handle = handle;
	}
	msg.type   = D_MSG_USER;
	msg.param1 = param1;
	msg.param2 = param2;
	msg.param3 = (D_U32)0;
	d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
	return D_OK;
}

/** @brief 事件处理*/
static D_Result
iptv_player_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &iptv_player_window;
	D_Visual    *list;
	D_ID focus, srv;

	D_DUMP("iptv_player_window_handler, evt->type is %d\n",evt->type );
	switch (evt->type)
	{
		case D_EVT_FP:
			switch (evt->fp.key)
			{
				case D_KEY_SOURCE:
				case D_KEY_PNL_SOURCE:
					
//					p_atv_signal_select_show();
					break;
	                case D_KEY_HOME :
				case D_KEY_BACK:
	                    {
					D_DUMP ("p_atv_tv_iptv_list_show()\n");
					if(type_count > 0)
					{
						MSG("D_KEY_BACK");
						d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
						//d_media_netts_stop();
						p_atv_tv_iptv_list_show();
					}
					else
					{
						MSG("D_KEY_BACK");
							 p_stb_exit_iptv();
//						usleep(200 * 1000);
//						p_atv_zhilian_main_menu_window_show();
	                    }
				}
	                    break;				
				case D_KEY_OK:
				case D_KEY_PNL_OK:
					
					D_DUMP ("p_atv_tv_iptv_list_show()\n");
					if(curr_ch_typeid != -1 && curr_ch_id != -1)
					{
						if (delay_timer != D_INVALID_HANDLE)
						{
							d_gui_close_frame (&iptv_channel_info_window);
							d_timer_destroy (delay_timer);
							delay_timer == D_INVALID_HANDLE;
						}
						MSG("D_KEY_OK");
						d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
						//d_media_netts_stop();
						p_atv_tv_iptv_list_show();
					}

					return D_OK;
			
				case D_KEY_PNL_L:
				case D_KEY_PNL_R:
				case D_KEY_VOLUME_PLUS:
				case D_KEY_VOLUME_MINUS:
					
					if(list_type->rset.cnt > 0 && list_data->rset.cnt > 0)
					{					
						p_atv_voice_show();
					}
					return D_OK;
				case D_KEY_UP:
				case D_KEY_PNL_U:
					MSG("curr_ch_id U= %d\n",curr_ch_id);
					if(!is_first_key)
						_resend = 18;
					is_up_down = 1;
					if(curr_ch_id<curr_ch_cnt-1)
						curr_ch_id += 1;
					else if(curr_ch_id==curr_ch_cnt-1)
						curr_ch_id = 0;
						//d_media_netts_stop();
 					p_iptv_info_show();
                    //d_media_netts_play(NULL, curr_ch_id, 0, 0, 0, 0, 0, NULL);
					MSG("_resend %d\n",_resend);
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					MSG("curr_ch_id D= %d\n",curr_ch_id);
					if(!is_first_key)
						_resend = 18;
					is_up_down = 1;
					if(curr_ch_id > 0)
						curr_ch_id -= 1;
					else if((curr_ch_id == 0) && (curr_ch_cnt >0))
						curr_ch_id = curr_ch_cnt-1;
						//d_media_netts_stop();
					if(curr_ch_id >= 0)
					p_iptv_info_show();
                    //d_media_netts_play(NULL, curr_ch_id, 0, 0, 0, 0, 0, NULL);
					MSG("_resend %d\n",_resend);
					break;
				default:
		                        if ((evt->fp.key >= D_KEY_0) && (evt->fp.key <= D_KEY_9))
		                        {
		                            /*显示频道号输入窗口*/
		                            p_atv_chan_input_window_show(0, evt->fp.key);
		                        }
					break;
			}
			break;
	      case D_EVT_USER:
			if( evt->user.param1 == USER_MSG_PARAM1_IPTV_PASSCODE )
			{
				D_DUMP("iptv_player_window_handler receive the massage USER_MSG_PARAM1_IPTV_PASSCODE\n");
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
				p_atv_iptv_login_show(1);
			}
			else if( evt->user.param1 == USER_MSG_PARAM1_IPTV_TVLIST )
			{
				D_DUMP("iptv_player_window_handler receive the massage USER_MSG_PARAM1_IPTV_TVLIST\n");
				curr_ch_typeid = 0;
				curr_ch_id = 0;
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);

				p_atv_tv_iptv_list_show();
			}
			else if( evt->user.param1 == USER_MSG_PARAM1_IPTV_TIPSHOW )
			{
				D_DUMP("iptv_player_window_handler receive the massage USER_MSG_PARAM1_IPTV_TIPSHOW. the tips is %s \n", (D_Char *)(evt->user.param2));
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
			        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
			                           D_GUI_LAYER_MESSAGE,
			                           D_POP_MSG_MSG,   "TIPS", (D_Char *)(evt->user.param2),
			                           0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
			}
			else if( evt->user.param1 == USER_MSG_PARAM1_IPTV_TIPHIDE )
			{
				D_DUMP("iptv_player_window_handler receive the massage USER_MSG_PARAM1_IPTV_TIPHIDE\n");
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
			}
			return D_OK;
			break;
		case D_EVT_DESTROY:
			d_vis_unsubscribe_evt (vis);
			break;
		default:
			break;
	}

	return D_ERR;
}

void * iptv_run(void *d)
{
	D_DUMP("iptv_run\n");
	static D_U8 show_flag =1;

	int count = 0;
	Authenticator * auth;
	
	D_Frame *frm = &iptv_list_window;

	D_Visual    *list;
	D_Visual    *label_list_total;
	D_Visual    *channel_list;
	
	while(status_running)
	{
		usleep(200 * 1000);
		auth = OTT_get_default_auth();

		MSG("%d\n", auth->status);
		switch(auth->status)
		{
			case WIFI_ERROR: 
				htk_main_quit();
				sprintf(char_buff, "%s", "Please set wifi connect ! !" );
				iptv_play_window_msg(D_INVALID_HANDLE, USER_MSG_PARAM1_IPTV_TIPSHOW, (D_U32)char_buff) ;
				return;
				
			case DATA_ERROR:
				
				htk_main_quit();
				sprintf(char_buff, "%s", "Data Error!!!"  );
				iptv_play_window_msg(D_INVALID_HANDLE, USER_MSG_PARAM1_IPTV_TIPSHOW, (D_U32)char_buff) ;
				return;

			case BACK_USER_FAILED:
			
				htk_main_quit();
				
				auth->status = STATUS_DEFAULT;	
				//OTT_auth_uninit();
				
				//get user info, if failed try three times	
				if(count < 3)
				{
					count++;
					//hTask_auth = d_task_create(&taskAttr1, OTT_auth_init, NULL);
				}

				return;
			
			case BACK_USER_FAILED_NEED_ACTIVE:
			case LOGIN_GET_EPG_EXPIRED:
					
				htk_main_quit();
				
				auth->status = STATUS_DEFAULT;	
				//sprintf(char_buff, "%s","Loading the program,Please wait..." );
				iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_PASSCODE, 0 ) ;				
				return;

			case REGISTER_REQUEST_RENEW_OR_REPLACE:
			case REGISTER_THIRED_REGISTERED_SUCCESS:

				MSG("register success\n");	
				auth->status = REGISTER_SUCESS_READY_FOR_LOGIN;
				sprintf(char_buff, "%s","register success");
				iptv_play_window_msg(&iptv_login_window, USER_MSG_PARAM1_IPTV_LOGLABLE, (D_U32)char_buff) ;			
				return;

			case REGISTER_ONE_PARAM_ERROR:
			case REGISTER_ONE_SNID_NOT_EXIST:
			case REGISTER_ONE_SUB_ID_NOT_EXIST:
			case REGISTER_ONE_SUB_ID_EXPIRED:
			case REGISTER_ONE_SUB_ID_CANNOT_USE:
			case REGISTER_ONE_ACTIVE_CODE_NOT_EXIST:
			case REGISTER_ONE_ACTIVE_CODE_USED:
			case REGISTER_ONE_OTHER_ERROR:
			case REGISTER_ONE_ACTIVE_CODE_NOT_MATCH:
			case REGISTER_ONE_CLIENT_INFO_ERROR:
			case REGISTER_ONE_AUT_ERROR:

			case REGISTER_SECOND_PARAM_ERROR:
			case REGISTER_SECOND_OTHER_ERROR:
			case REGISTER_SECOND_SN_INVALID:
			case REGISTER_SECOND_SN_REGISTERED:
			case REGISTER_SECOND_AUT_ERROR:

			case REGISTER_THIRED_PARAM_ERROR:
			case REGISTER_THIRED_SN_INVALID:
			case REGISTER_THIRED_SN_REGISTERED:
			case REGISTER_THIRED_ACTIVE_CODE_USED:
			case REGISTER_THIRED_ACTIVE_CODE_INVALID:
			case REGISTER_THIRED_HID_EXIST:
			case REGISTER_THIRED_NOT_MATCH:
			case REGISTER_THIRED_CLIENT_INFO_ERROR:
			case REGISTER_THIRED_AUT_ERROR:
			case REGISTER_ERROR:

				if(auth->status == REGISTER_THIRED_ACTIVE_CODE_USED)
				{
					sprintf(char_buff, "%s","active code used" );
				}
				else if(auth->status == REGISTER_THIRED_ACTIVE_CODE_INVALID)
				{
					sprintf(char_buff, "%s","active code invalid");
				}	
				else if(auth->status == REGISTER_THIRED_AUT_ERROR)
				{
					sprintf(char_buff, "%s","aut error" );
				}	
				else if(auth->status == REGISTER_THIRED_HID_EXIST)
				{
					sprintf(char_buff, "%s","hid exist" );
				}	
				else 
				{
					sprintf(char_buff, "register error %d", auth->status );
				}	
				
				iptv_play_window_msg(&iptv_login_window, USER_MSG_PARAM1_IPTV_LOGLABLE, (D_U32)char_buff) ;			
				
				return;


			case LOGIN_GET_EPG_PROGRAM_SUCCESS:
			
				htk_main_quit();
			
				auth->status = STATUS_DEFAULT;	
				count = 0;	
				
				MSG("LOGIN_GET_EPG_PROGRAM_SUCCESS %d\n", auth->cur_api);
				if(auth->cur_api == REQUEST_EPG) 
				{
					MSG("USER_MSG_PARAM1_IPTV_LISTDATE\n");
					iptv_play_window_msg(&iptv_list_window, USER_MSG_PARAM1_IPTV_LISTDATE, 0) ;
				}
				else if(auth->cur_api == REQUEST_LOGIN)
				{
					iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TVLIST, 0) ;
				}
				else
				{
					iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TVLIST, 0) ;
				}

				return;
				
			case LOGIN_GET_EPG_FAILED:
				auth->status = STATUS_DEFAULT;	
				return;
			
			case LOGIN_GET_EPG_PROGRAM_FAILED:
				auth->status = STATUS_DEFAULT;	
				return;
		
			default:
				MSG("\n");	
				break;
		}
	}
}


D_Result
iptv_player_window_init (void) D_FUNCPOSTFIT
{
	D_Visual        *vis;
	 
	MSG("\n");
	vis = d_frame_get_control (&iptv_player_window, 0);
	
	if (vis)
	{
		D_DUMP("iptv_player_window_init\n");
		curmenu = 0;
		/*设定窗口事件回调*/
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
		d_vis_subscribe_evt (vis, D_EVT_USER_MASK , D_INVALID_HANDLE);
		d_vis_set_handler (vis, iptv_player_window_handler);
	}

	return D_OK;
}

void p_iptv_info_show( )
{
	if(curr_ch_cnt<=0)
		return ;
	return d_gui_open_frame(&iptv_channel_info_window, D_GUI_LAYER_USER );
}

void p_iptv_info_close( )
{
	return d_gui_close_frame (&iptv_channel_info_window);
}
D_U8 getIptvRunFlag( void )
{
	return in_iptv;
}

void try_play_new_iptvchan(  D_U16 chno )
{
	if(chno<1)
		return ;
	if(chno <= curr_ch_cnt)
	{
		curr_ch_id = chno - 1 ;
		d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
		d_media_netts_stop();
		p_iptv_info_show();
		d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
				D_GUI_LAYER_MESSAGE,
				D_POP_MSG_MSG,   "", "Program Loading...",
				0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
		d_media_netts_play(NULL, curr_ch_id, 0, 0, 0, 0, 0, NULL);
		is_up_down = 0;
		is_display = 1;
		is_loading = D_TRUE;
	}
}

/** @brief 事件处理*/
static D_Result
iptv_channel_info_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch(evt->type)
	{
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_SCREEN:
				case D_KEY_BACK:
					MSG("\n");
                    return d_gui_close_frame (&iptv_channel_info_window);
                default:
                    break;
			}
            break;
        case D_EVT_TIMER:
            /*隐藏窗口*/
			is_first_key = 0;
            return d_gui_close_frame (&iptv_channel_info_window);
            break;
            break;
        case D_EVT_DESTROY:
                if (delay_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy (delay_timer);
                   delay_timer == D_INVALID_HANDLE;
                }
                d_vis_unsubscribe_evt (vis);
               break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
iptv_channel_info_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual *vis;
	ProgramUrl	pinfo;
	MSG("\n");
	vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_INFO);
	if(vis)
	{
		MSG("\n");
		memset(&pinfo, 0, sizeof(pinfo)); 
		if (get_iptv_date_info (curr_ch_id, &pinfo) >= 0){
			MSG("\n");
			sprintf(char_buff, "%03d  %s", curr_ch_id+1,  pinfo.name  );
			d_label_set_text(vis, char_buff);
			MSG("\n");
		}
	}

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
           /*创建隐藏定时器*/
        delay_timer = d_timer_create (NULL, 5000, d_gui_get_queue());
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK,delay_timer);

         /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

        /*注册事件回调*/
        d_vis_set_handler (vis, iptv_channel_info_window_handler);
    }
    /*清除音量条*/
    p_atv_volume_window_hide();
	MSG("\n");
	return D_OK;
}

void * _iptv_channel_change(void* arg){
    while(in_iptv)
    {
		if((is_loading == D_FALSE) && (is_display == 1))
		{
			is_display = 0;
			 MSG("is_loading hide  %d  %d\n", is_loading, is_display);
			iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TIPHIDE, 0) ;
		}
		else if((is_loading == D_TRUE ) &&(is_display == 0))
		{
			is_display = 1;
			 MSG("is_loading show  %d  %d\n", is_loading, is_display);
			sprintf(char_buff, "%s", "Program Loading..."  );
			iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TIPSHOW, char_buff) ;
		}
     		 if((_resend == 20) && is_up_down && (curr_ch_cnt>0))
 		 {
			MSG("_iptv_channel_change !!\n");
			iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TIPHIDE, 0) ;
			d_media_netts_stop();
			sprintf(char_buff, "%s", "Program Loading..."  );
			iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TIPSHOW, char_buff) ;
			d_media_netts_play(NULL, curr_ch_id, 0, 0, 0, 0, 0, NULL);
			_resend = 0;
			is_up_down = 0;
			is_first_key = 1;
			is_display = 1;
			is_loading = D_TRUE;
			MSG("is_loading hide  %d  %d\n", is_loading,is_display);
   		 }
		 if(_resend > 300){
			 //MSG("is_loading  %d  %d\n", is_loading, is_display);
			if(is_loading == D_FALSE || is_display == 1){
				//is_display = 0;
			//	iptv_play_window_msg(&iptv_player_window, USER_MSG_PARAM1_IPTV_TIPHIDE, 0) ;
			}
			 _resend = 0;
		 }
		 usleep(10*1000);
	     _resend ++; 
    }   
    MSG("_iptv_channel_change !!! \n");
}
/** @breif 播放IPYV服务*/
	D_Result
p_stb_enter_iptv(void)
{
	int ret;
    	pthread_t  thread_t;

	type_count = 0;

	p_av_set_vid_background(0, D_VID_BackGround_BLack, D_FALSE);
	
	D_DUMP("d_gui_enter_menu\n");
	d_gui_enter_menu (&iptv_player_window, D_TRUE);

	taskAttr1.name = "IptvAuth";
	taskAttr1.priority = D_MAIN_TASK_PRIO + 1;
	taskAttr1.stack_size = 16 * 1024;
	taskAttr1.priority   = 4;
	
	d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
		D_GUI_LAYER_MESSAGE,
		D_POP_MSG_MSG,   "TIPS", "Loading the program,Please wait...",
		0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
	hTask_auth = d_task_create(&taskAttr1, OTT_auth_init, NULL);

	d_task_wait(300);
	taskAttr.id         = 0;
	taskAttr.stack_size = 8 * 1024;
	taskAttr.name       = "iptv task";
       taskAttr.priority   = 1;
	D_DUMP("d_task_create\n");
	status_running = 1;
	iptvHandle= d_task_create(&taskAttr, (D_TaskEntry)iptv_run, NULL);
	D_DUMP("iptv_run d_task_create end\n");

	in_iptv = 1;
	ret = pthread_create(&thread_t, NULL, _iptv_channel_change, NULL);
	
	if(0 != ret)
	{
	    perror("Thread_t Create");
	}

	D_DUMP("p_stb_enter_iptv end\n");

	return D_OK;	
}


D_Result endIptv_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
	if(sel)
	{
		in_iptv = 0;
		MSG("end iptv\n");
		d_media_netts_stop();

		if( iptvHandle!=D_INVALID_HANDLE ){
			status_running = 0;
			d_task_wait(300);
			//d_task_kill(iptvHandle);
			MSG("iptvHandle\n");
			d_task_join(iptvHandle);		
			iptvHandle = D_INVALID_HANDLE;
			D_DUMP("===================d_gui_exit iptv task=========================\n");
		}
		if(hTask_auth!=D_INVALID_HANDLE ) {
			MSG("hTask_auth\n");
			//d_task_join(hTask_auth);
			//hTask_auth=D_INVALID_HANDLE;
			//if(param != 1)
			//	OTT_auth_uninit(); //hanjf 0422
		}
		MSG("\n");
	d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
		MSG("\n");
		d_gui_clear_menu();
		//d_gui_clear_menu_ext(0);
		D_DUMP("===================d_gui_exit_menu=========================\n");
		
		p_av_set_vid_background(0, p_sys_get_user_background_color(), D_FALSE);
			usleep(200 * 1000);
			p_atv_zhilian_main_menu_window_show();

	}
}

D_Result
p_stb_exit_iptv(void)
{
	//d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
	d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE, NULL,
	                      "Exit IPTV or  Not ?", 0, D_FALSE, endIptv_callback, 0) ;
	
	return D_OK;	
}
