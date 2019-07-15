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
#include "nr_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 focus, snr_y, snr_c, tnr_y, tnr_c, mode;
    D_U16          value;
    D_VidInput input;
    D_U8 hdflag;
    D_NR_SET param;

    //D_Char tnr_dynrnd_buf[BUF_LINE];
} D_NrSetDate;

static D_NrSetDate *nr_set_data;
static D_Char * strmode[] = {"high", "middle", "low", "off"};
static D_Result
save_param_of_nr(void) D_FUNCPOSTFIT
{
    if(nr_set_data->hdflag)
    {
        //p_tvconf_set_hdnr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->value);
    }
    else
    {
        p_tvconf_set_cur_nrmode((D_U8*)&nr_set_data->mode, p_vip_get_dbinput(nr_set_data->input));
        p_tvconf_set_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), (D_U8)nr_set_data->mode);
    }
    return D_OK;
}

static D_Result
get_set_of_nr_set(void) D_FUNCPOSTFIT
{
    p_tvconf_get_cur_nrmode(&nr_set_data->mode, p_vip_get_dbinput(nr_set_data->input));
    p_tvconf_get_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->mode);

    nr_set_data->snr_y = nr_set_data->param.luma_snr_on;
    nr_set_data->snr_c = nr_set_data->param.chroma_snr_on;
    nr_set_data->tnr_y = nr_set_data->param.luma_tnr_on;
    nr_set_data->tnr_c = nr_set_data->param.chroma_tnr_on;

    return D_OK;
}

static D_Result
set_param_of_nr(void) D_FUNCPOSTFIT
{
    nr_set_data->param.luma_snr_on = nr_set_data->snr_y;
    nr_set_data->param.chroma_snr_on = nr_set_data->snr_c;
    nr_set_data->param.luma_tnr_on = nr_set_data->tnr_y;
    nr_set_data->param.chroma_tnr_on = nr_set_data->tnr_c;
    d_vip_setNr((D_U8*)&nr_set_data->param);
    return D_OK;
}


static D_Result
set_nr_mode_show(D_S16 flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis;
    D_Char * str_on, *str_off;

    flag = D_MIN(3, flag);
    vis = d_frame_get_control(frm, ID_NR_LABEL_1);
    d_label_set_text(vis, strmode[flag]);

    //根据不同的模式取得不同的设置
    if(p_tvconf_get_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->mode) == D_OK)
    {
        nr_set_data->snr_y = nr_set_data->param.luma_snr_on;
        nr_set_data->snr_c = nr_set_data->param.chroma_snr_on;
        nr_set_data->tnr_y = nr_set_data->param.luma_tnr_on;
        nr_set_data->tnr_c = nr_set_data->param.chroma_tnr_on;
    }
    d_vip_setNr((D_U8*)&nr_set_data->param);

    str_on = d_gui_get_text(atv_IDS_ON);
    str_off =  d_gui_get_text(atv_IDS_OFF);

    vis = d_frame_get_control(frm, ID_NR_LABEL_2);
    d_label_set_text(vis, nr_set_data->snr_y == 1 ?  str_on : str_off);

    vis = d_frame_get_control(frm, ID_NR_LABEL_3);
    d_label_set_text(vis, nr_set_data->snr_c == 1 ? str_on : str_off);

    vis = d_frame_get_control(frm, ID_NR_LABEL_4);
    d_label_set_text(vis, nr_set_data->tnr_y == 1 ? str_on : str_off);

    vis = d_frame_get_control(frm, ID_NR_LABEL_5);
    d_label_set_text(vis, nr_set_data->tnr_c == 1 ? str_on : str_off);
    return D_OK;
}

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
    d_label_set_text(vis, d_gui_get_text((value) ? atv_IDS_ON : atv_IDS_OFF));
    return D_OK;
}

static D_Result
set_nr_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_NR_BUTTON_2:
            vis = d_frame_get_control(frm, ID_NR_LABEL_2);
            nr_set_data->snr_y = (nr_set_data->snr_y + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((nr_set_data->snr_y) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_NR_BUTTON_3:
            vis = d_frame_get_control(frm, ID_NR_LABEL_3);
            nr_set_data->snr_c = (nr_set_data->snr_c + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((nr_set_data->snr_c) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_NR_BUTTON_4:
            vis = d_frame_get_control(frm, ID_NR_LABEL_4);
            nr_set_data->tnr_y = (nr_set_data->tnr_y + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((nr_set_data->tnr_y) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_NR_BUTTON_5:
            vis = d_frame_get_control(frm, ID_NR_LABEL_5);
            nr_set_data->tnr_c = (nr_set_data->tnr_c + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((nr_set_data->tnr_c) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_NR_BUTTON_1:
            p_tvconf_set_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->mode);
            if(flag)
            {
                nr_set_data->mode = (nr_set_data->mode + 1) % 4;
            }
            else
            {
                nr_set_data->mode = (nr_set_data->mode + 4 - 1) % 4;
            }
            set_nr_mode_show(nr_set_data->mode);
            break;
        default:
            break;
    }
    set_param_of_nr();

    return D_OK;
}

static D_Result
button_2_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_NR_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_nr_set_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    d_gui_update();
    return D_OK;
}

static D_Result
button_3_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_NR_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_nr_set_data(id, D_TRUE);
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
button_4_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_NR_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_nr_set_data(id, D_TRUE);
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
button_5_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_NR_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_nr_set_data(id, D_TRUE);
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
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_NR_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_nr_set_data(id, D_TRUE);
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
set_page_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis;
    D_ID i;

    set_nr_mode_show(nr_set_data->mode);

    vis = d_frame_get_control(frm, ID_NR_LABEL_NR);
    d_label_set_text(vis, "NR");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_1);
    d_button_set_text(vis, "NR MODE");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_2);
    d_button_set_text(vis, "SNR Y");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_3);
    d_button_set_text(vis, "SNR C");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_4);
    d_button_set_text(vis, "SNR Y");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_5);
    d_button_set_text(vis, "SNR C");

    /*
        vis = d_frame_get_control(frm, ID_NR_LABEL_2);
        vis_switch_init(nr_set_data->snr_y,vis);

        vis = d_frame_get_control(frm, ID_NR_LABEL_3);
        vis_switch_init(nr_set_data->snr_c,vis);

        vis = d_frame_get_control(frm, ID_NR_LABEL_4);
        vis_switch_init(nr_set_data->tnr_y,vis);

        vis = d_frame_get_control(frm, ID_NR_LABEL_5);
        vis_switch_init(nr_set_data->tnr_c,vis);

        vis = d_frame_get_control(frm, ID_NR_LABEL_1);
        set_nr_mode_show(nr_set_data->mode);
    */
    return D_OK;
}

static D_Result
nr_set_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &nr_set_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_NR_LABEL_NR);
    d_label_set_text(vis, "NR");

    vis = d_frame_get_control(frm, ID_NR_BUTTON_2);
    d_vis_set_handler(vis, button_2_set_handler);

    vis = d_frame_get_control(frm, ID_NR_BUTTON_3);
    d_vis_set_handler(vis, button_3_set_handler);

    vis = d_frame_get_control(frm, ID_NR_BUTTON_4);
    d_vis_set_handler(vis, button_4_set_handler);

    vis = d_frame_get_control(frm, ID_NR_BUTTON_5);
    d_vis_set_handler(vis, button_5_set_handler);

    vis = d_frame_get_control(frm, ID_NR_BUTTON_1);
    d_vis_set_handler(vis, button_1_set_handler);
    return D_OK;
}


static D_Result
nr_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &nr_set_window;
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
                    set_nr_set_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_nr_set_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_nr();

            if(nr_set_data)
            {
                PROJECT_FREE(nr_set_data);
                nr_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
nr_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_U8 val;

    nr_set_data = (D_NrSetDate*)PROJECT_ALLOC(sizeof(D_NrSetDate));
    if(!nr_set_data)
    {
        return D_ERR;
    }
    memset(nr_set_data, 0, sizeof(D_NrSetDate));
    nr_set_data->input = p_conf_get_vid_input();
    if(p_tvconf_get_cur_nrmode(&val, p_vip_get_dbinput(nr_set_data->input)) == D_OK )
    {
        nr_set_data->mode = val;
    }
    if(nr_set_data->input == D_VID_IUTPUT_AV1 || nr_set_data->input == D_VID_IUTPUT_AV2 || nr_set_data->input == D_VID_IUTPUT_TV)
    {
        nr_set_data->hdflag = p_vip_get_ntscflag();
    }
    else
    {
        nr_set_data->hdflag = p_vip_get_hdflag();
    }
    nr_set_data->focus = ID_NR_BUTTON_1;
    get_set_of_nr_set();
    set_page_show();
    nr_set_vis_handler();

    vis = d_frame_get_control(frm, ID_NR_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, nr_set_window_handler);
    }

    return D_OK;
}

/** @brief  NR菜单*/
D_Result
p_atv_nr_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&nr_set_window, D_TRUE);
}
