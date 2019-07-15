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
#include "emc_setting_window.c"

#define BUF_LINE 16

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16  lvds_en, miu_en, lvds_mode, miu_mode;
    D_Float miu_span, miu_step, lvds_span, lvds_step;
    D_VidInput input;

    D_Char miu_span_buf[BUF_LINE];
    D_Char miu_step_buf[BUF_LINE];
    D_Char lvds_en_buf[BUF_LINE];
    D_Char lvds_span_buf[BUF_LINE];
    D_Char lvds_step_buf[BUF_LINE];
    D_Char miu_en_buf[BUF_LINE];
    D_Char lvds_mode_buf[BUF_LINE];
    D_Char miu_mode_buf[BUF_LINE];
} D_EmcSettingDate;

static D_EmcSettingDate *emc_setting_data;

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
save_param_of_emc(void) D_FUNCPOSTFIT
{
    D_LVDSSSCG_SET lvds;
    D_MIUSSCG_SET   miu;

    lvds.enable = emc_setting_data->lvds_en;
    lvds.mode = emc_setting_data->lvds_mode;

    lvds.ssc_span = emc_setting_data->lvds_span;
    lvds.ssc_step = emc_setting_data->lvds_step;
    p_tvconf_set_lvds_sscg (&lvds);

    miu.enable = emc_setting_data->miu_en;
    miu.mode = emc_setting_data->miu_mode;

    miu.ssc_span = emc_setting_data->miu_span;
    miu.ssc_step = emc_setting_data->miu_step;
    p_tvconf_set_miu_sscg (&miu);

    return D_OK;
}

static D_Result
set_param_of_emc(void) D_FUNCPOSTFIT
{
    d_lvds_Set_Sscg(emc_setting_data->lvds_en, emc_setting_data->lvds_mode, emc_setting_data->lvds_span, emc_setting_data->lvds_step);
    d_miu_Set_Sscg(emc_setting_data->miu_en, emc_setting_data->miu_mode, emc_setting_data->miu_span, emc_setting_data->miu_step);
    return D_OK;
}

static D_Result
set_emc_setting_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_EMC_BUTTON_1:

            vis = d_frame_get_control(frm, ID_EMC_LABEL_1);

            if(emc_setting_data->miu_en == 0)
            {
                emc_setting_data->miu_en = 1;
            }
            else if(emc_setting_data->miu_en == 1)
            {
                emc_setting_data->miu_en = 0;
            }

            sprintf(emc_setting_data->miu_en_buf, "%d", emc_setting_data->miu_en);
            d_label_set_text(vis, emc_setting_data->miu_en_buf);
            break;
        case ID_EMC_BUTTON_2:

            vis = d_frame_get_control(frm, ID_EMC_LABEL_2);

            if(emc_setting_data->miu_mode == 0)
            {
                emc_setting_data->miu_mode = 1;
            }
            else if(emc_setting_data->miu_mode == 1)
            {
                emc_setting_data->miu_mode = 0;
            }

            sprintf(emc_setting_data->miu_mode_buf, "%d", emc_setting_data->miu_mode);
            d_label_set_text(vis, emc_setting_data->miu_mode_buf);
            break;
        case ID_EMC_BUTTON_3:
            if(flag)
            {
                if(emc_setting_data->miu_span > 32.9f)
                    emc_setting_data->miu_span = 30.0;
                else
                    emc_setting_data->miu_span = emc_setting_data->miu_span + 0.1f;
            }
            else
            {
                if(emc_setting_data->miu_span <= 30.09f)
                    emc_setting_data->miu_span = 33.0;
                else
                    emc_setting_data->miu_span = emc_setting_data->miu_span - 0.1f;
            }
            vis = d_frame_get_control(frm, ID_EMC_LABEL_3);
            {
                sprintf(emc_setting_data->miu_span_buf, "%.1f KHz", emc_setting_data->miu_span);
                d_label_set_text(vis, emc_setting_data->miu_span_buf);
            }
            break;
        case ID_EMC_BUTTON_4:
#ifdef D_TV_IAMGE_SOURCE 
            if(flag)
            {
                if(emc_setting_data->miu_step > 3.09f)
                    emc_setting_data->miu_step = 0.00;
                else
                    emc_setting_data->miu_step = emc_setting_data->miu_step + 0.1f;
            }
            else
            {
                if(emc_setting_data->miu_step <= 0.0f)
                    emc_setting_data->miu_step = 3.10;
                else
                    emc_setting_data->miu_step = emc_setting_data->miu_step - 0.1f;
            }
            vis = d_frame_get_control(frm, ID_EMC_LABEL_4);
            {
                sprintf(emc_setting_data->miu_step_buf, "%.1f %%", emc_setting_data->miu_step);
                d_label_set_text(vis, emc_setting_data->miu_step_buf);
            }
#else
            if(flag)
            {
                if(emc_setting_data->miu_step > 9.99f)
                    emc_setting_data->miu_step = 0.1;
                else
                    emc_setting_data->miu_step = emc_setting_data->miu_step + 0.1f;
            }
            else
            {
                if(emc_setting_data->miu_step <= 0.11f)
                    emc_setting_data->miu_step = 10.0;
                else
                    emc_setting_data->miu_step = emc_setting_data->miu_step - 0.1f;
            }
            vis = d_frame_get_control(frm, ID_EMC_LABEL_4);
            {
                sprintf(emc_setting_data->miu_step_buf, "%.1f %%", emc_setting_data->miu_step);
                d_label_set_text(vis, emc_setting_data->miu_step_buf);
            }
#endif
            break;
        case ID_EMC_BUTTON_5:
            if(emc_setting_data->lvds_en == 1)
                emc_setting_data->lvds_en = 0;
            else if(emc_setting_data->lvds_en == 0)
                emc_setting_data->lvds_en = 1;
            vis = d_frame_get_control(frm, ID_EMC_LABEL_5);
            {
                sprintf(emc_setting_data->lvds_en_buf, "%d", emc_setting_data->lvds_en);
                d_label_set_text(vis, emc_setting_data->lvds_en_buf);
            }
            break;
        case ID_EMC_BUTTON_6:
            if(emc_setting_data->lvds_mode == 1)
                emc_setting_data->lvds_mode = 0;
            else if(emc_setting_data->lvds_mode == 0)
                emc_setting_data->lvds_mode = 1;
            vis = d_frame_get_control(frm, ID_EMC_LABEL_6);
            {
                sprintf(emc_setting_data->lvds_mode_buf, "%d", emc_setting_data->lvds_mode);
                d_label_set_text(vis, emc_setting_data->lvds_mode_buf);
            }
            break;
        case ID_EMC_BUTTON_7:
            if(flag)
            {
                if(emc_setting_data->lvds_span > 32.9f)
                    emc_setting_data->lvds_span = 30.0;
                else
                    emc_setting_data->lvds_span = emc_setting_data->lvds_span + 0.1f;
            }
            else
            {
                if(emc_setting_data->lvds_span <= 30.09f)
                    emc_setting_data->lvds_span = 33.0;
                else
                    emc_setting_data->lvds_span = emc_setting_data->lvds_span - 0.1f;
            }

            vis = d_frame_get_control(frm, ID_EMC_LABEL_7);
            {
                sprintf(emc_setting_data->lvds_span_buf, "%.1f KHz", emc_setting_data->lvds_span);
                d_label_set_text(vis, emc_setting_data->lvds_span_buf);
            }
            break;
        case ID_EMC_BUTTON_8:
#ifdef D_TV_IAMGE_SOURCE 
            if(flag)
            {
                if(emc_setting_data->lvds_step > 3.09f)
                    emc_setting_data->lvds_step = 0.00;
                else
                    emc_setting_data->lvds_step = emc_setting_data->lvds_step + 0.1f;
            }
            else
            {
                if(emc_setting_data->lvds_step <= 0.0f)
                    emc_setting_data->lvds_step = 3.10;
                else
                    emc_setting_data->lvds_step = emc_setting_data->lvds_step - 0.1f;
            }

            vis = d_frame_get_control(frm, ID_EMC_LABEL_8);
            {
                sprintf(emc_setting_data->lvds_step_buf, "%.1f %%", emc_setting_data->lvds_step);
                d_label_set_text(vis, emc_setting_data->lvds_step_buf);
            }
#else
            if(flag)
            {
                if(emc_setting_data->lvds_step > 9.99f)
                    emc_setting_data->lvds_step = 0.5;
                else
                    emc_setting_data->lvds_step = emc_setting_data->lvds_step + 0.1f;
            }
            else
            {
                if(emc_setting_data->lvds_step <= 0.51f)
                    emc_setting_data->lvds_step = 10.0;
                else
                    emc_setting_data->lvds_step = emc_setting_data->lvds_step - 0.1f;
            }

            vis = d_frame_get_control(frm, ID_EMC_LABEL_8);
            {
                sprintf(emc_setting_data->lvds_step_buf, "%.1f %%", emc_setting_data->lvds_step);
                d_label_set_text(vis, emc_setting_data->lvds_step_buf);
            }
#endif
            break;
        default:
            break;
    }
    set_param_of_emc();
    return D_OK;
}

static D_Result
miu_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
miu_span_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
miu_step_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
lvds_en_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
lvds_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
miu_en_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
lvds_span_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
lvds_step_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_EMC_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_emc_setting_data(id, D_TRUE);
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
get_set_of_emc(void) D_FUNCPOSTFIT
{
    D_LVDSSSCG_SET lvds;
    D_MIUSSCG_SET miu;

    p_tvconf_get_lvds_sscg (&lvds);
    emc_setting_data->lvds_en = lvds.enable;
    emc_setting_data->lvds_mode = lvds.mode;

    emc_setting_data->lvds_span = lvds.ssc_span;
    emc_setting_data->lvds_step = lvds.ssc_step;

    p_tvconf_get_miu_sscg (&miu);
    emc_setting_data->miu_en = miu.enable;
    emc_setting_data->miu_mode = miu.mode;

    emc_setting_data->miu_span = miu.ssc_span;
    emc_setting_data->miu_step = miu.ssc_step;

    sprintf(emc_setting_data->miu_en_buf, "%d", emc_setting_data->miu_en);
    sprintf(emc_setting_data->miu_span_buf, "%.1f KHz", emc_setting_data->miu_span);
    sprintf(emc_setting_data->miu_step_buf, "%.1f %%", emc_setting_data->miu_step);
    sprintf(emc_setting_data->lvds_en_buf, "%d", emc_setting_data->lvds_en);
    sprintf(emc_setting_data->lvds_span_buf, "%.1f KHz", emc_setting_data->lvds_span);
    sprintf(emc_setting_data->lvds_step_buf, "%.1f %%", emc_setting_data->lvds_step);

    sprintf(emc_setting_data->miu_mode_buf, "%d", emc_setting_data->miu_mode);
    sprintf(emc_setting_data->lvds_mode_buf, "%d", emc_setting_data->lvds_mode);

    return D_OK;
}

static D_Result
emc_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &emc_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_1);
    d_label_set_text(vis, "MIU SSC En");
    d_vis_set_handler(vis, miu_en_handler);

    vis = d_frame_get_control(frm, ID_EMC_LABEL_EMC);
    d_label_set_text(vis, "EMC");

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_2);
    d_label_set_text(vis, "MIU SSC Mode");
    d_vis_set_handler(vis, miu_mode_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_3);
    d_label_set_text(vis, "MIU SSC Span");
    d_vis_set_handler(vis, miu_span_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_4);
    d_label_set_text(vis, "MIU SSC Step");
    d_vis_set_handler(vis, miu_step_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_5);
    d_label_set_text(vis, "LVDS SSC En");
    d_vis_set_handler(vis, lvds_en_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_6);
    d_label_set_text(vis, "LVDS SSC Mode");
    d_vis_set_handler(vis, lvds_mode_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_7);
    d_label_set_text(vis, "LVDS SSC Span");
    d_vis_set_handler(vis, lvds_span_handler);

    vis = d_frame_get_control(frm, ID_EMC_BUTTON_8);
    d_label_set_text(vis, "LVDS SSC Step");
    d_vis_set_handler(vis, lvds_step_handler);

	vis = d_frame_get_control(frm, ID_EMC_LABEL_1);
    d_label_set_text(vis, emc_setting_data->miu_en_buf);

	vis = d_frame_get_control(frm, ID_EMC_LABEL_2);
    d_label_set_text(vis, emc_setting_data->miu_mode_buf);
	
    vis = d_frame_get_control(frm, ID_EMC_LABEL_3);
    d_label_set_text(vis, emc_setting_data->miu_span_buf);

    vis = d_frame_get_control(frm, ID_EMC_LABEL_4);
    d_label_set_text(vis, emc_setting_data->miu_step_buf);

    vis = d_frame_get_control(frm, ID_EMC_LABEL_5);
    d_label_set_text(vis, emc_setting_data->lvds_en_buf);

   vis = d_frame_get_control(frm, ID_EMC_LABEL_6);
    d_label_set_text(vis, emc_setting_data->lvds_mode_buf);

    vis = d_frame_get_control(frm, ID_EMC_LABEL_7);
    d_label_set_text(vis, emc_setting_data->lvds_span_buf);

    vis = d_frame_get_control(frm, ID_EMC_LABEL_8);
    d_label_set_text(vis, emc_setting_data->lvds_step_buf);

    return D_OK;
}


static D_Result
emc_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &emc_setting_window;
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
                    set_emc_setting_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_emc_setting_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_emc();
            if(emc_setting_data)
            {
                PROJECT_FREE(emc_setting_data);
                emc_setting_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
emc_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    emc_setting_data = (D_EmcSettingDate*)PROJECT_ALLOC(sizeof(D_EmcSettingDate));
    if(!emc_setting_data)
    {
        return D_ERR;
    }
    memset(emc_setting_data, 0, sizeof(D_EmcSettingDate));
    emc_setting_data->input = p_conf_get_vid_input();

    get_set_of_emc();
    emc_vis_set();

    vis = d_frame_get_control(frm, ID_EMC_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }
#ifdef D_TV_IAMGE_SOURCE 
    vis = d_frame_get_control(frm, ID_EMC_BUTTON_3);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);

    }
    vis = d_frame_get_control(frm, ID_EMC_LABEL_3);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        
    }
#endif
    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, emc_setting_window_handler);
    }

    return D_OK;
}

/** @brief emc菜单*/
D_Result
p_atv_emc_setting_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&emc_setting_window, D_TRUE);
}

