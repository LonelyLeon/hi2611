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
#include "image_setting_window.c"

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 backlight, vip_on;
    D_S16 cm_on;
    D_VidInput input;
    D_BLDIM_SET param;
    D_VE_SET vip_param;
    D_CM_SET cm_param;
    D_Char backlight_buf[4];
} D_ImageDate;

static D_ImageDate *image_data;

static D_Result
set_of_param(void) D_FUNCPOSTFIT
{
    image_data->vip_param.ve_on = image_data->vip_on;
    image_data->cm_param.cm_on = image_data->cm_on;
    if(p_tvconf_get_bldim_set_param(&image_data->param, p_vip_get_dbinput(image_data->input)) == D_OK)
    {
        d_vip_setBldim((D_U8*)&image_data->param, image_data->backlight);
    }
    d_vip_Set_VE((D_U8*)&image_data->vip_param);
    d_vip_Set_CM((D_U8*)&image_data->cm_param);

    return D_OK;
}

static D_Result
save_of_param(void) D_FUNCPOSTFIT
{
    p_tvconf_set_bldim_backlight(&image_data->backlight, p_vip_get_dbinput(image_data->input));
    p_tvconf_set_veset_param(&image_data->vip_param, p_vip_get_dbinput(image_data->input));
    p_tvconf_set_cmset_param(&image_data->cm_param, p_vip_get_dbinput(image_data->input));
    return D_OK;
}

static D_Result
get_set_of_image(void) D_FUNCPOSTFIT
{
    p_tvconf_get_bldim_backlight(&image_data->backlight, p_vip_get_dbinput(image_data->input)) ;

    if(p_tvconf_get_veset_param(&image_data->vip_param, p_vip_get_dbinput(image_data->input)) == D_OK)
    {
        image_data->vip_on = image_data->vip_param.ve_on;
    }
    if(p_tvconf_get_cmset_param(&image_data->cm_param, p_vip_get_dbinput(image_data->input)) == D_OK)
    {
        image_data->cm_on = image_data->cm_param.cm_on;
    }
    sprintf(image_data->backlight_buf, "%d", image_data->backlight);

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
set_image_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual * vis, *vis_label;

    switch(id)
    {
        case ID_IMAGE_BUTTON_1:
            if(flag)
            {
                image_data->backlight = (image_data->backlight + 1) % 101;
            }
            else
            {
                image_data->backlight = (image_data->backlight + 101 - 1) % 101;
            }
            vis = d_frame_get_control(frm, ID_IMAGE_LABEL_1);
            {
                sprintf(image_data->backlight_buf, "%d", image_data->backlight);
                d_label_set_text(vis, image_data->backlight_buf);
            }
            break;
        case ID_IMAGE_BUTTON_11:
            vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_11);
            image_data->vip_on = ( image_data->vip_on + 1) & 0x01;
            d_label_set_text(vis_label, d_gui_get_text(( image_data->vip_on) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_IMAGE_BUTTON_10:
            vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_10);
            image_data->cm_on = ( image_data->cm_on + 1) & 0x01;
            d_label_set_text(vis_label, d_gui_get_text(( image_data->cm_on) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        default:
            break;
    }
    set_of_param();
    return D_OK;
}


static D_Result
backlight_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_image_data(id, D_TRUE);
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
wb_adjust_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_wb_adjust_show();
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
pq_nonlilnear_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_pq_nonlilnear_show();
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
bl_dim_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_bl_dim_show();
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
nr_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_nr_set_show();
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
de_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_de_set_show();
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
dce_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_dce_show();
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
colorsetting_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_colorset_show();
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
gamma_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_9);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_gamma_show();
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
vip_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_11);
    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
	     set_image_data(id, D_TRUE);
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
cm_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_IMAGE_LABEL_10);
    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
	     set_image_data(id, D_TRUE);
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
image_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_1);
    d_vis_set_handler(vis, backlight_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_2);
    d_vis_set_handler(vis, wb_adjust_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_3);
    d_vis_set_handler(vis, pq_nonlilnear_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_4);
    d_button_set_text(vis, "BL_DIM");
    d_vis_set_handler(vis, bl_dim_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_5);
    d_button_set_text(vis, "NR");
    d_vis_set_handler(vis, nr_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_6);
    d_button_set_text(vis, "DE");
    d_vis_set_handler(vis, de_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_7);
    d_button_set_text(vis, "COLORSETTING");
    d_vis_set_handler(vis, colorsetting_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_8);
    d_button_set_text(vis, "DCE");
    d_vis_set_handler(vis, dce_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_9);
    d_button_set_text(vis, "GAMMA");
    d_vis_set_handler(vis, gamma_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_10);
    d_button_set_text(vis, "CM");
    d_vis_set_handler(vis, cm_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_BUTTON_11);
    d_button_set_text(vis, "VIP");
    d_vis_set_handler(vis, vip_set_handler);

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_1);
    d_label_set_text(vis, image_data->backlight_buf);

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_4);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_5);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_6);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_7);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_8);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_9);
    d_label_set_text(vis, ">>>");

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_11);
    d_label_set_text(vis, d_gui_get_text((image_data->vip_on) ? atv_IDS_ON : atv_IDS_OFF));

    vis = d_frame_get_control(frm, ID_IMAGE_LABEL_10);
    d_label_set_text(vis, d_gui_get_text((image_data->cm_on) ? atv_IDS_ON : atv_IDS_OFF));
    return D_OK;
}



static D_Result
image_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &image_setting_window;
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
                    set_image_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_image_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_of_param();
            if(image_data)
            {
                PROJECT_FREE(image_data);
                image_data = NULL;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
image_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    image_data = (D_ImageDate*)PROJECT_ALLOC(sizeof(D_ImageDate));
    if(!image_data)
    {
        return D_ERR;
    }
    memset(image_data, 0, sizeof(D_ImageDate));
    image_data->input = p_conf_get_vid_input();

    get_set_of_image();
    image_vis_set();

    vis = d_frame_get_control(frm, ID_IMAGE_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, image_setting_window_handler);
    }

    return D_OK;
}

/** @brief  声音模式菜单*/
D_Result
p_atv_image_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&image_setting_window, D_TRUE);
}

