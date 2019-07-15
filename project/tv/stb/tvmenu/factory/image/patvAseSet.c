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
#include "ase_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 ase_gain, ase_stl, ase_ssl, ase_on, ase_stu, ase_ssu, ase_ftg_gain;
    D_VidInput input;
    D_U8 hdflag;
    D_ASE_SET param;

    D_Char ase_gain_buf[BUF_LINE];
    D_Char ase_stl_buf[BUF_LINE];
    D_Char ase_ssl_buf[BUF_LINE];
    D_Char ase_stu_buf[BUF_LINE];
    D_Char ase_ssu_buf[BUF_LINE];
    D_Char ase_ftg_gain_buf[BUF_LINE];
} D_AseSetDate;

static D_AseSetDate *ase_set_data;

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
vis_switch_init(D_S16 value, D_Visual *vis)
{
    if(value == 0)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
    }
    else if(value == 1)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
    }

    return D_OK;
}


static D_Result
save_param_of_ase(void) D_FUNCPOSTFIT
{
    if(ase_set_data->hdflag)
    {
        p_tvconf_set_hdase_set_param(&ase_set_data->param, p_vip_get_dbinput(ase_set_data->input));
    }
    else
    {
        p_tvconf_set_ase_set_param(&ase_set_data->param, p_vip_get_dbinput(ase_set_data->input));
    }

    return D_OK;
}

static D_Result
set_param_of_ase(void) D_FUNCPOSTFIT
{
    ase_set_data->param.ase_gain = ase_set_data->ase_gain;
    ase_set_data->param.ase_stl = ase_set_data->ase_stl;
    ase_set_data->param.ase_ssl = ase_set_data->ase_ssl;
    ase_set_data->param.ase_on = ase_set_data->ase_on;
    ase_set_data->param.ase_ftg_gain = ase_set_data->ase_ftg_gain;
    ase_set_data->param.ase_stu = ase_set_data->ase_stu;
    ase_set_data->param.ase_ssu = ase_set_data->ase_ssu;

    d_vip_setAse(&ase_set_data->param);
    return D_OK;
}

static D_S16
set_ase_value(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        if(value == 255)
            value = 0;
        else
            value ++;
    }
    else
    {
        if(value == 0)
            value = 255;
        else
            value --;
    }

    return value;
}


static D_Result
set_ase_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_ASE_BUTTON_1:

            vis = d_frame_get_control(frm, ID_ASE_LABEL_1);

            if(ase_set_data->ase_on == 0)
            {
                d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
                ase_set_data->ase_on = 1;
            }
            else if(ase_set_data->ase_on == 1)
            {
                d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
                ase_set_data->ase_on = 0;
            }
            break;
        case ID_ASE_BUTTON_2:
            if(flag)
            {
                if(ase_set_data->ase_gain == 63)
                    ase_set_data->ase_gain = 0;
                else
                    ase_set_data->ase_gain ++;
            }
            else
            {
                if(ase_set_data->ase_gain == 0)
                    ase_set_data->ase_gain = 63;
                else
                    ase_set_data->ase_gain --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_2);
            {
                sprintf(ase_set_data->ase_gain_buf, "%d", ase_set_data->ase_gain);
                d_label_set_text(vis, ase_set_data->ase_gain_buf);
            }
            break;
        case ID_ASE_BUTTON_3:
            if(flag)
            {
                if(ase_set_data->ase_stl == 63)
                    ase_set_data->ase_stl = 0;
                else
                    ase_set_data->ase_stl ++;
            }
            else
            {
                if(ase_set_data->ase_stl == 0)
                    ase_set_data->ase_stl = 63;
                else
                    ase_set_data->ase_stl --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_3);
            {
                sprintf(ase_set_data->ase_stl_buf, "%d", ase_set_data->ase_stl);
                d_label_set_text(vis, ase_set_data->ase_stl_buf);
            }
            break;
        case ID_ASE_BUTTON_4:
            if(flag)
            {
                if(ase_set_data->ase_ssl == 255)
                    ase_set_data->ase_ssl = 0;
                else
                    ase_set_data->ase_ssl ++;
            }
            else
            {
                if(ase_set_data->ase_ssl == 0)
                    ase_set_data->ase_ssl = 255;
                else
                    ase_set_data->ase_ssl --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_4);
            {
                sprintf(ase_set_data->ase_ssl_buf, "%d", ase_set_data->ase_ssl);
                d_label_set_text(vis, ase_set_data->ase_ssl_buf);
            }
            break;
        case ID_ASE_BUTTON_5:
            if(flag)
            {
                if(ase_set_data->ase_stu == 127)
                    ase_set_data->ase_stu = 0;
                else
                    ase_set_data->ase_stu ++;
            }
            else
            {
                if(ase_set_data->ase_stu == 0)
                    ase_set_data->ase_stu = 127;
                else
                    ase_set_data->ase_stu --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_5);
            {
                sprintf(ase_set_data->ase_stu_buf, "%d", ase_set_data->ase_stu);
                d_label_set_text(vis, ase_set_data->ase_stu_buf);
            }
            break;
        case ID_ASE_BUTTON_6:
            if(flag)
            {
                if(ase_set_data->ase_ssu == 255)
                    ase_set_data->ase_ssu = 0;
                else
                    ase_set_data->ase_ssu ++;
            }
            else
            {
                if(ase_set_data->ase_ssu == 0)
                    ase_set_data->ase_ssu = 255;
                else
                    ase_set_data->ase_ssu --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_6);
            {
                sprintf(ase_set_data->ase_ssu_buf, "%d", ase_set_data->ase_ssu);
                d_label_set_text(vis, ase_set_data->ase_ssu_buf);
            }
            break;
        case ID_ASE_BUTTON_7:
            if(flag)
            {
                if(ase_set_data->ase_ftg_gain == 31)
                    ase_set_data->ase_ftg_gain = 0;
                else
                    ase_set_data->ase_ftg_gain ++;
            }
            else
            {
                if(ase_set_data->ase_ftg_gain == 0)
                    ase_set_data->ase_ftg_gain = 31;
                else
                    ase_set_data->ase_ftg_gain --;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_7);
            {
                sprintf(ase_set_data->ase_ftg_gain_buf, "%d", ase_set_data->ase_ftg_gain);
                d_label_set_text(vis, ase_set_data->ase_ftg_gain_buf);
            }
            break;
        default:
            break;
    }
    set_param_of_ase();
    return D_OK;
}


static D_Result
ase_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_stl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_ssl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_ftg_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_stu_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
ase_ssu_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_ase_set_data(id, D_TRUE);
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
get_set_of_ase(void) D_FUNCPOSTFIT
{
    if(ase_set_data->hdflag)
    {
        p_tvconf_get_hdase_set_param(&ase_set_data->param, p_vip_get_dbinput(ase_set_data->input));
    }
    else
    {
        p_tvconf_get_ase_set_param(&ase_set_data->param, p_vip_get_dbinput(ase_set_data->input));
    }

    ase_set_data->ase_gain = ase_set_data->param.ase_gain;
    ase_set_data->ase_stl = ase_set_data->param.ase_stl;
    ase_set_data->ase_ssl = ase_set_data->param.ase_ssl;
    ase_set_data->ase_on = ase_set_data->param.ase_on;
    ase_set_data->ase_ftg_gain = ase_set_data->param.ase_ftg_gain;
    ase_set_data->ase_stu = ase_set_data->param.ase_stu;
    ase_set_data->ase_ssu = ase_set_data->param.ase_ssu;

    sprintf(ase_set_data->ase_gain_buf, "%d", ase_set_data->ase_gain);
    sprintf(ase_set_data->ase_stl_buf, "%d", ase_set_data->ase_stl);
    sprintf(ase_set_data->ase_ssl_buf, "%d", ase_set_data->ase_ssl);
    sprintf(ase_set_data->ase_stu_buf, "%d", ase_set_data->ase_stu);
    sprintf(ase_set_data->ase_ssu_buf, "%d", ase_set_data->ase_ssu);
    sprintf(ase_set_data->ase_ftg_gain_buf, "%d", ase_set_data->ase_ftg_gain);

    return D_OK;
}

static D_Result
ase_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &ase_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_1);
    d_label_set_text(vis, "Ase On");
    d_vis_set_handler(vis, ase_on_handler);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_ASE);
    d_label_set_text(vis, "ASE");

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_2);
    d_label_set_text(vis, "Ase Gain");
    d_vis_set_handler(vis, ase_gain_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_3);
    d_label_set_text(vis, "Ase Stl");
    d_vis_set_handler(vis, ase_stl_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_4);
    d_label_set_text(vis, "Ase Ssl");
    d_vis_set_handler(vis, ase_ssl_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_5);
    d_label_set_text(vis, "Ase Stu");
    d_vis_set_handler(vis, ase_stu_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_6);
    d_label_set_text(vis, "Ase Ssu");
    d_vis_set_handler(vis, ase_ssu_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_7);
    d_label_set_text(vis, "Ase Ftg Gain");
    d_vis_set_handler(vis, ase_ftg_gain_handler);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_2);
    d_label_set_text(vis, ase_set_data->ase_gain_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_3);
    d_label_set_text(vis, ase_set_data->ase_stl_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_4);
    d_label_set_text(vis, ase_set_data->ase_ssl_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_1);
    vis_switch_init(ase_set_data->ase_on, vis);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_5);
    d_label_set_text(vis, ase_set_data->ase_stu_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_6);
    d_label_set_text(vis, ase_set_data->ase_ssu_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_7);
    d_label_set_text(vis, ase_set_data->ase_ftg_gain_buf);

    return D_OK;
}


static D_Result
ase_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &ase_window;
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

                    set_ase_set_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_ase_set_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_ase();
            if(ase_set_data)
            {
                PROJECT_FREE(ase_set_data);
                ase_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
ase_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    ase_set_data = (D_AseSetDate*)PROJECT_ALLOC(sizeof(D_AseSetDate));
    if(!ase_set_data)
    {
        return D_ERR;
    }
    memset(ase_set_data, 0, sizeof(D_AseSetDate));
    ase_set_data->input = p_conf_get_vid_input();
	if(ase_set_data->input == D_VID_IUTPUT_AV1 || ase_set_data->input == D_VID_IUTPUT_AV2|| ase_set_data->input == D_VID_IUTPUT_TV)
	{
		ase_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		ase_set_data->hdflag = p_vip_get_hdflag();
	}
    get_set_of_ase();
    ase_vis_set();

    vis = d_frame_get_control(frm, ID_ASE_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, ase_window_handler);
    }

    return D_OK;
}

/** @brief ase菜单*/
D_Result
p_atv_ase_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&ase_window, D_TRUE);
}

