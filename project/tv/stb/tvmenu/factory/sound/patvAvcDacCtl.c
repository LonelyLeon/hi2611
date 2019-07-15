#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "avc_dac_ctl_window.c"

#define AVC_LEVEL_NUM (D_AVC_DAC_CTL_LEVEL_NUM)
#define BUF_LINE 8


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 avc_dac_value_1,avc_dac_value_2,cur_avc_dac;
    D_VidInput input;
    D_Char avc_dac_value_1_buf[BUF_LINE];
    D_Char avc_dac_value_2_buf[BUF_LINE];
    D_Char cur_avc_dac_buf[BUF_LINE];
    D_AVC_SET avc[TV_AVC_INPUT_NUM];
    D_Avc_Param avc_param;
	D_U8 dbid;

} D_AvcDacCtlDate;

static D_AvcDacCtlDate *avc_dac_ctl_data;
static D_U8 avc_ctrl_type = 0;


static D_Char *show_title_text[2] = {"DAC CTL", "DAC CTL"};
static D_Char *show_button_text[4][2] =
{
    {"CUR_LEVEL", "CUR_LEVEL"},
    {"DAC_VALUE", "DAC_VALUE"},
    {"DAC_LEVEL", "DAC_LEVEL"},
};


/** @brief  判断焦点位置
* @param    vis 控件指针
* @return   控件ID号
*/
static D_ID
get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

static D_Result
set_label_focus_attribute(D_Visual *vis, D_Bool flag) D_FUNCPOSTFIT
{
    D_Ptr pattr;

    if(flag)
    {
        pattr = (D_Ptr)&GUID_label_focus;
        d_vis_set_attribute(vis, pattr);
    }
    else
    {
        pattr = (D_Ptr)&GUID_label_normal;
        d_vis_set_attribute(vis, pattr);
    }

    return D_OK;
}

static D_Result
set_param_of_avc_dac_ctl(void) D_FUNCPOSTFIT
{
	avc_dac_ctl_data->avc_param.base_avc = avc_dac_ctl_data->avc_dac_value_1;
	avc_dac_ctl_data->avc_param.base_level = avc_dac_ctl_data->avc_dac_value_2;
	d_av_audio_avc_base_set(avc_dac_ctl_data->avc_param ,avc_dac_ctl_data->dbid);
	
    return D_OK;
}

static D_Result
save_param_of_avc_dac_ctl(void) D_FUNCPOSTFIT
{
	D_U8 dbid;
    D_Avc_Param avc_param;	
	dbid = avc_dac_ctl_data->dbid;
	avc_dac_ctl_data->avc_param.base_avc = avc_dac_ctl_data->avc_dac_value_1;
	avc_dac_ctl_data->avc_param.base_level = avc_dac_ctl_data->avc_dac_value_2;
	
	avc_dac_ctl_data->avc[dbid].base_avc = avc_dac_ctl_data->avc_param.base_avc ;
	avc_dac_ctl_data->avc[dbid].base_level = avc_dac_ctl_data->avc_param.base_level ;

	p_tvconf_set_avc(avc_dac_ctl_data->avc);
    return D_OK;
}



static D_S16
set_avc_dac_level_ctl_value(D_S16 value, D_Bool flag)
{
    if(avc_ctrl_type == 1)
    {
        if(flag)
        {
            value = (value + 1);
            value = (value > 100) ? (-100) : value;
        }
        else
        {
            value = (value - 1);
            value = (value < (-100)) ? 100 : value;
        }
    }
    else
    {
        if(flag)
        {
            value = (value + 1) % 41;
        }
        else
        {
            value = (value + 41 - 1) % 41;
        }
    }

    return value;
}


static D_S16
set_avc_dac_ctl_value(D_S16 value, D_Bool flag)
{
    if(avc_ctrl_type == 1)
    {
        if(flag)
        {
            value = (value + 1);
            value = (value > 100) ? (-100) : value;
        }
        else
        {
            value = (value - 1);
            value = (value < (-100)) ? 100 : value;
        }
    }
    else
    {
        if(flag)
        {
            value = (value + 1) % 268;
        }
        else
        {
            value = (value + 268 - 1) % 268;
        }
    }

    return value;
}


static D_Result
set_avc_dac_ctl_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &avc_dac_ctl_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_AVC_DAC_CTL_BUTTON_2:
            avc_dac_ctl_data->avc_dac_value_1 = set_avc_dac_ctl_value(avc_dac_ctl_data->avc_dac_value_1, flag);

            vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_2);
            {
                sprintf(avc_dac_ctl_data->avc_dac_value_1_buf, "%d", avc_dac_ctl_data->avc_dac_value_1);
                d_label_set_text(vis, avc_dac_ctl_data->avc_dac_value_1_buf);
            }
            break;
            
        case ID_AVC_DAC_CTL_BUTTON_3:
            avc_dac_ctl_data->avc_dac_value_2 = set_avc_dac_level_ctl_value(avc_dac_ctl_data->avc_dac_value_2, flag);

            vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_3);
            {
                sprintf(avc_dac_ctl_data->avc_dac_value_2_buf, "%d", avc_dac_ctl_data->avc_dac_value_2);
                d_label_set_text(vis, avc_dac_ctl_data->avc_dac_value_2_buf);
            }
            break;
            
        default:
            break;
    }

    set_param_of_avc_dac_ctl();
    return D_OK;
}

static D_Result
avc_dac_ctl_1_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &avc_dac_ctl_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_avc_dac_ctl_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
avc_dac_ctl_2_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &avc_dac_ctl_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_avc_dac_ctl_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
avc_dac_ctl_3_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &avc_dac_ctl_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_avc_dac_ctl_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
get_set_of_avc_dac_ctl(void) D_FUNCPOSTFIT
{
	D_U8 dbid;
    D_Avc_Param avc_param;	
    p_tvconf_get_avc(avc_dac_ctl_data->avc);
	avc_dac_ctl_data->dbid = get_avc_db_idx(avc_dac_ctl_data->input);
	dbid = avc_dac_ctl_data->dbid;
	avc_dac_ctl_data->avc_param.base_level = avc_dac_ctl_data->avc[dbid].base_level;
	avc_dac_ctl_data->avc_param.base_avc = avc_dac_ctl_data->avc[dbid].base_avc;
	avc_dac_ctl_data->avc_param.level_step = avc_dac_ctl_data->avc[dbid].level_step;
	avc_dac_ctl_data->avc_param.now_level_offset = avc_dac_ctl_data->avc[dbid].now_level_offset;
	avc_dac_ctl_data->avc_param.now_close_avc = avc_dac_ctl_data->avc[dbid].now_close_avc;
	avc_dac_ctl_data->avc_param.now_open_avc = avc_dac_ctl_data->avc[dbid].now_open_avc;

    avc_dac_ctl_data->avc_dac_value_1 = avc_dac_ctl_data->avc_param.base_avc;
    avc_dac_ctl_data->avc_dac_value_2 = avc_dac_ctl_data->avc_param.base_level;
    
    avc_dac_ctl_data->cur_avc_dac = d_av_get_cur_vdac_ctrl();
    sprintf(avc_dac_ctl_data->cur_avc_dac_buf, "%d", avc_dac_ctl_data->cur_avc_dac);
    sprintf(avc_dac_ctl_data->avc_dac_value_1_buf, "%d", avc_dac_ctl_data->avc_dac_value_1);
    sprintf(avc_dac_ctl_data->avc_dac_value_2_buf, "%d", avc_dac_ctl_data->avc_dac_value_2);

    return D_OK;
}

static D_Result
avc_dac_ctl_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &avc_dac_ctl_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_AVC_DAC_CTL);
    d_label_set_text(vis, show_title_text[avc_ctrl_type]);

    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_BUTTON_1);
    d_button_set_text(vis, show_button_text[0][avc_ctrl_type]);
    d_vis_set_handler(vis, avc_dac_ctl_1_handler);
    d_vis_enable(vis, D_FALSE);
    
    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_BUTTON_2);
    d_button_set_text(vis, show_button_text[1][avc_ctrl_type]);
    d_vis_set_handler(vis, avc_dac_ctl_2_handler);
    d_vis_set_focus(vis);
    
    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_BUTTON_3);
    d_button_set_text(vis, show_button_text[2][avc_ctrl_type]);
    d_vis_set_handler(vis, avc_dac_ctl_3_handler);

    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_1);
    d_label_set_text(vis, avc_dac_ctl_data->cur_avc_dac_buf);
    
    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_2);
    d_label_set_text(vis, avc_dac_ctl_data->avc_dac_value_1_buf);

    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_LABEL_3);
    d_label_set_text(vis, avc_dac_ctl_data->avc_dac_value_2_buf);
   
    return D_OK;
}


static D_Result
avc_dac_ctl_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &avc_dac_ctl_window;
    D_ID id;

    id = get_focus_control_id(frm);

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    set_avc_dac_ctl_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_avc_dac_ctl_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                //case D_KEY_BACK:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_avc_dac_ctl();
            if(avc_dac_ctl_data)
            {
                PROJECT_FREE(avc_dac_ctl_data);
                avc_dac_ctl_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
avc_dac_ctl_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    avc_dac_ctl_data = (D_AvcDacCtlDate*)PROJECT_ALLOC(sizeof(D_AvcDacCtlDate));
    if(!avc_dac_ctl_data)
    {
        return D_ERR;
    }
    memset(avc_dac_ctl_data, 0, sizeof(D_AvcDacCtlDate));

    avc_dac_ctl_data->input = p_conf_get_vid_input();
    get_set_of_avc_dac_ctl();
    avc_dac_ctl_vis_set();

    vis = d_frame_get_control(frm, ID_AVC_DAC_CTL_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, avc_dac_ctl_window_handler);
    }

    return D_OK;
}

/** @brief  avc dac ctl菜单*/
D_Result
p_atv_avc_dac_ctl_show (D_U32 param) D_FUNCPOSTFIT
{
    avc_ctrl_type = D_MIN(param, 2);
    return d_gui_enter_menu (&avc_dac_ctl_window, D_TRUE);
}

