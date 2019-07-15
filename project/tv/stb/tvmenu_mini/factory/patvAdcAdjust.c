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
#include "adc_adjust_window.c"

#define BUF_LINE 8

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 r_gain, g_gain, b_gain, power_ref, r_offset, g_offset, b_offset;
    D_S16 mode;
    D_ADC_SET param;
    D_U8 hdflag;
    D_COMP_SET comp_param;
    D_COMP_SET hdcomp_param;
    D_COMP_SET temp_comp_param;
    D_VidInput input;
    D_Char auto_adjust_buf[BUF_LINE];
    D_Char r_gain_buf[BUF_LINE];
    D_Char g_gain_buf[BUF_LINE];
    D_Char b_gain_buf[BUF_LINE];
    D_Char r_offset_buf[BUF_LINE];
    D_Char g_offset_buf[BUF_LINE];
    D_Char b_offset_buf[BUF_LINE];
} D_ADCAdjustDate;

static D_ADCAdjustDate *adc_adjust_data;

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

static D_S16
set_adc_set_value_gain(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        if(value == 511)
            value = 0;
        else
            value ++;
    }
    else
    {
        if(value == 0)
            value = 511;
        else
            value --;
    }

    return value;
}

static D_Bool set_adc_set_auto_adc(void)
{
    if(adc_adjust_data->input != D_VID_IUTPUT_YPBPR)
        return D_FALSE;
    if(d_vip_AutoADC(&adc_adjust_data->param, &adc_adjust_data->temp_comp_param) == D_TRUE)
    {
        p_tvconf_set_hdadc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
        p_tvconf_set_adc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));

        adc_adjust_data->comp_param.comp_gain_r = adc_adjust_data->temp_comp_param.comp_gain_r;
        adc_adjust_data->comp_param.comp_gain_g = adc_adjust_data->temp_comp_param.comp_gain_g;
        adc_adjust_data->comp_param.comp_gain_b = adc_adjust_data->temp_comp_param.comp_gain_b;
        adc_adjust_data->comp_param.comp_vclamplevel_r = adc_adjust_data->temp_comp_param.comp_vclamplevel_r;
        adc_adjust_data->comp_param.comp_vclamplevel_g = adc_adjust_data->temp_comp_param.comp_vclamplevel_g;
        adc_adjust_data->comp_param.comp_vclamplevel_b = adc_adjust_data->temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_comp_set_param(&adc_adjust_data->comp_param, p_vip_get_dbinput(adc_adjust_data->input));

        adc_adjust_data->hdcomp_param.comp_gain_r = adc_adjust_data->temp_comp_param.comp_gain_r;
        adc_adjust_data->hdcomp_param.comp_gain_g = adc_adjust_data->temp_comp_param.comp_gain_g;
        adc_adjust_data->hdcomp_param.comp_gain_b = adc_adjust_data->temp_comp_param.comp_gain_b;
        adc_adjust_data->hdcomp_param.comp_vclamplevel_r = adc_adjust_data->temp_comp_param.comp_vclamplevel_r;
        adc_adjust_data->hdcomp_param.comp_vclamplevel_g = adc_adjust_data->temp_comp_param.comp_vclamplevel_g;
        adc_adjust_data->hdcomp_param.comp_vclamplevel_b = adc_adjust_data->temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_hdcomb_set_param(&adc_adjust_data->hdcomp_param, p_vip_get_dbinput(adc_adjust_data->input));

        if(adc_adjust_data->hdflag)
        {
            p_tvconf_get_hdadc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
        }
        else
        {
            p_tvconf_get_adc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
        }

        adc_adjust_data->r_gain = adc_adjust_data->param.r_gain;
        adc_adjust_data->g_gain = adc_adjust_data->param.g_gain;
        adc_adjust_data->b_gain = adc_adjust_data->param.b_gain;
        adc_adjust_data->r_offset = adc_adjust_data->param.r_offset;
        adc_adjust_data->g_offset = adc_adjust_data->param.g_offset;
        adc_adjust_data->b_offset = adc_adjust_data->param.b_offset;

        sprintf(adc_adjust_data->r_gain_buf, "%d", adc_adjust_data->r_gain);
        sprintf(adc_adjust_data->g_gain_buf, "%d", adc_adjust_data->g_gain);
        sprintf(adc_adjust_data->b_gain_buf, "%d", adc_adjust_data->b_gain);
        sprintf(adc_adjust_data->r_offset_buf, "%d", adc_adjust_data->r_offset);
        sprintf(adc_adjust_data->g_offset_buf, "%d", adc_adjust_data->g_offset);
        sprintf(adc_adjust_data->b_offset_buf, "%d", adc_adjust_data->b_offset);
        return D_TRUE;
    }
    else
    {
        return D_FALSE;
    }

}
static D_S16
set_adc_set_value_offset(D_S16 value, D_Bool flag)
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
set_mode_vis_show(D_S16 flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_ADC_LABEL_2);

    switch(flag)
    {
        case 0:
            adc_adjust_data->input = D_VID_IUTPUT_TV;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_TV));
            break;
        case 1:
            adc_adjust_data->input = D_VID_IUTPUT_DTV;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_DTV));
            break;
        case 2:
            adc_adjust_data->input = D_VID_IUTPUT_AV1;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_AV));
            break;
        case 3:
            adc_adjust_data->input = D_VID_IUTPUT_YPBPR;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_YPBPR));
            break;
        case 4:
            adc_adjust_data->input = D_VID_IUTPUT_HDMI1;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI1));
            break;
        case 5:
            adc_adjust_data->input = D_VID_IUTPUT_HDMI2;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI2));
            break;
        case 6:
            adc_adjust_data->input = D_VID_IUTPUT_VGA;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_PC));
            break;
        case 7:
            adc_adjust_data->input = D_VID_IUTPUT_USB1;
            d_label_set_text(vis, d_gui_get_text(atv_IDS_USB));
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
set_of_adc_adjust(void) D_FUNCPOSTFIT
{
    adc_adjust_data->param.r_gain = adc_adjust_data->r_gain;
    adc_adjust_data->param.g_gain = adc_adjust_data->g_gain;
    adc_adjust_data->param.b_gain = adc_adjust_data->b_gain;
    adc_adjust_data->param.r_offset = adc_adjust_data->r_offset;
    adc_adjust_data->param.g_offset = adc_adjust_data->g_offset;
    adc_adjust_data->param.b_offset = adc_adjust_data->b_offset;

    d_vip_setAdc((D_U8*)&adc_adjust_data->param);
    return D_OK;
}

static D_Result
save_of_adc_adjust(void) D_FUNCPOSTFIT
{
    if(adc_adjust_data->hdflag)
    {
        p_tvconf_set_hdadc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
    }
    else
    {
        p_tvconf_set_adc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
    }

    return D_OK;
}

static D_Result
get_set_of_adc_adjust(void) D_FUNCPOSTFIT
{
    if(adc_adjust_data->hdflag)
    {
        p_tvconf_get_hdcomb_set_param(&adc_adjust_data->hdcomp_param, p_vip_get_dbinput(adc_adjust_data->input));
        p_tvconf_get_hdadc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));

    }
    else
    {
        p_tvconf_get_comp_set_param(&adc_adjust_data->comp_param, p_vip_get_dbinput(adc_adjust_data->input));
        p_tvconf_get_adc_set_param(&adc_adjust_data->param, p_vip_get_dbinput(adc_adjust_data->input));
    }

    adc_adjust_data->r_gain = adc_adjust_data->param.r_gain;
    adc_adjust_data->g_gain = adc_adjust_data->param.g_gain;
    adc_adjust_data->b_gain = adc_adjust_data->param.b_gain;
    adc_adjust_data->r_offset = adc_adjust_data->param.r_offset;
    adc_adjust_data->g_offset = adc_adjust_data->param.g_offset;
    adc_adjust_data->b_offset = adc_adjust_data->param.b_offset;

    sprintf(adc_adjust_data->auto_adjust_buf, "%s", "->");
    sprintf(adc_adjust_data->r_gain_buf, "%d", adc_adjust_data->r_gain);
    sprintf(adc_adjust_data->g_gain_buf, "%d", adc_adjust_data->g_gain);
    sprintf(adc_adjust_data->b_gain_buf, "%d", adc_adjust_data->b_gain);
    sprintf(adc_adjust_data->r_offset_buf, "%d", adc_adjust_data->r_offset);
    sprintf(adc_adjust_data->g_offset_buf, "%d", adc_adjust_data->g_offset);
    sprintf(adc_adjust_data->b_offset_buf, "%d", adc_adjust_data->b_offset);

    return D_OK;
}

static D_Result
set_adc_adjust_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_ADC_BUTTON_1:
            vis = d_frame_get_control(frm, ID_ADC_LABEL_1);
            {
                D_Bool ret;

                sprintf(adc_adjust_data->auto_adjust_buf, "%s", "校正中...");
                d_label_set_text(vis, adc_adjust_data->auto_adjust_buf);
                d_gui_update();

                ret = set_adc_set_auto_adc();
                d_task_wait(50);
                sprintf(adc_adjust_data->auto_adjust_buf, "%s", ((ret) ? "成功" : "失败"));
                d_label_set_text(vis, adc_adjust_data->auto_adjust_buf);

                if(ret)
                {
                    vis = d_frame_get_control(frm, ID_ADC_GROUP);
                    d_vis_update(vis, NULL);
                }
            }
            break;
        case ID_ADC_BUTTON_2:
            if(flag)
            {
                if(adc_adjust_data->mode == 7)
                    adc_adjust_data->mode = 0;
                else
                    adc_adjust_data->mode++;
            }
            else
            {
                if(adc_adjust_data->mode == 0)
                    adc_adjust_data->mode = 7;
                else
                    adc_adjust_data->mode --;
            }
            set_mode_vis_show(adc_adjust_data->mode);
            break;
        case ID_ADC_BUTTON_3:
            adc_adjust_data->r_gain = set_adc_set_value_gain(adc_adjust_data->r_gain, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_3);
            {
                sprintf(adc_adjust_data->r_gain_buf, "%d", adc_adjust_data->r_gain);
                d_label_set_text(vis, adc_adjust_data->r_gain_buf);
            }
            break;
        case ID_ADC_BUTTON_4:
            adc_adjust_data->g_gain = set_adc_set_value_gain(adc_adjust_data->g_gain, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_4);
            {
                sprintf(adc_adjust_data->g_gain_buf, "%d", adc_adjust_data->g_gain);
                d_label_set_text(vis, adc_adjust_data->g_gain_buf);
            }

            break;

        case ID_ADC_BUTTON_5:
            adc_adjust_data->b_gain = set_adc_set_value_gain(adc_adjust_data->b_gain, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_5);
            {
                sprintf(adc_adjust_data->b_gain_buf, "%d", adc_adjust_data->b_gain);
                d_label_set_text(vis, adc_adjust_data->b_gain_buf);
            }
            break;

        case ID_ADC_BUTTON_6:
            adc_adjust_data->r_offset = set_adc_set_value_offset(adc_adjust_data->r_offset, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_6);
            {
                sprintf(adc_adjust_data->r_offset_buf, "%d", adc_adjust_data->r_offset);
                d_label_set_text(vis, adc_adjust_data->r_offset_buf);
            }
            break;
        case ID_ADC_BUTTON_7:
            adc_adjust_data->g_offset = set_adc_set_value_offset(adc_adjust_data->g_offset, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_7);
            {
                sprintf(adc_adjust_data->g_offset_buf, "%d", adc_adjust_data->g_offset);
                d_label_set_text(vis, adc_adjust_data->g_offset_buf);
            }
            break;
        case ID_ADC_BUTTON_8:
            adc_adjust_data->b_offset = set_adc_set_value_offset(adc_adjust_data->b_offset, flag);

            vis = d_frame_get_control(frm, ID_ADC_LABEL_8);
            {
                sprintf(adc_adjust_data->b_offset_buf, "%d", adc_adjust_data->b_offset);
                d_label_set_text(vis, adc_adjust_data->b_offset_buf);
            }
            break;
        default:
            break;
    }
    set_of_adc_adjust();

    return D_OK;
}

static D_Result
auto_adjust_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
source_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
r_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
g_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
b_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
r_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
g_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
b_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_ADC_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_adc_adjust_data(id, D_TRUE);
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
adc_adjust_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_ADC_LABEL_ADC);
    if(vis)
    {
        d_label_set_text(vis, "ADC Adjust");
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_1);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->auto_adjust_buf);
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_2);
    if(vis)
    {
        if(adc_adjust_data->input == D_VID_IUTPUT_TV)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_TV));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_DTV)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_DTV));
        }
        else if((adc_adjust_data->input == D_VID_IUTPUT_AV1) || (adc_adjust_data->input == D_VID_IUTPUT_AV2))
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_AV));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_YPBPR)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_YPBPR));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_HDMI1)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI1));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_USB1)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_USB));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_HDMI2)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI2));
        }
        else if(adc_adjust_data->input == D_VID_IUTPUT_VGA)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_PC));
        }
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_3);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->r_gain_buf);
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_4);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->g_gain_buf);
    }
    vis = d_frame_get_control(frm, ID_ADC_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->b_gain_buf);
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_6);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->r_offset_buf);
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_7);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->g_offset_buf);
    }

    vis = d_frame_get_control(frm, ID_ADC_LABEL_8);
    if(vis)
    {
        d_label_set_text(vis, adc_adjust_data->b_offset_buf);
    }

    return D_OK;
}

static D_Result
adc_adjust_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &adc_adjust_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_1);
    if(vis)
    {
        d_button_set_text(vis, "Auto Adjust");
        d_vis_set_handler(vis, auto_adjust_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_2);
    if(vis)
    {
        d_button_set_text(vis, "Source");
        d_vis_set_handler(vis, source_set_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_3);
    if(vis)
    {
        d_button_set_text(vis, "R-Gain");
        d_vis_set_handler(vis, r_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_4);
    if(vis)
    {
        d_button_set_text(vis, "G-Gain");
        d_vis_set_handler(vis, g_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_5);
    if(vis)
    {
        d_button_set_text(vis, "B-Gain");
        d_vis_set_handler(vis, b_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_6);
    if(vis)
    {
        d_button_set_text(vis, "R-Offset");
        d_vis_set_handler(vis, r_offset_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_7);
    if(vis)
    {
        d_button_set_text(vis, "G-Offset");
        d_vis_set_handler(vis, g_offset_handler);
    }

    vis = d_frame_get_control(frm, ID_ADC_BUTTON_8);
    if(vis)
    {
        d_button_set_text(vis, "B-Offset");
        d_vis_set_handler(vis, b_offset_handler);
    }

    return D_OK;
}

static D_Result
adc_adjust_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &adc_adjust_window;
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
                case D_KEY_OK:
                    if(id != ID_ADC_BUTTON_1)
                    {
                        set_adc_adjust_data(id, D_TRUE);
                    }
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(id != ID_ADC_BUTTON_1)
                    {
                        set_adc_adjust_data(id, D_FALSE);
                    }
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_of_adc_adjust();
            if(adc_adjust_data)
            {
                PROJECT_FREE(adc_adjust_data);
                adc_adjust_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
adc_adjust_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    adc_adjust_data = (D_ADCAdjustDate*)PROJECT_ALLOC(sizeof(D_ADCAdjustDate));
    if(!adc_adjust_data)
    {
        return D_ERR;
    }
    memset(adc_adjust_data, 0, sizeof(D_ADCAdjustDate));

    adc_adjust_data->input = p_conf_get_vid_input();
    if(adc_adjust_data->input == D_VID_IUTPUT_AV1 || adc_adjust_data->input == D_VID_IUTPUT_AV2 || adc_adjust_data->input == D_VID_IUTPUT_TV)
    {
        adc_adjust_data->hdflag = p_vip_get_ntscflag();
    }
    else
    {
        adc_adjust_data->hdflag = p_vip_get_hdflag();
    }
    get_set_of_adc_adjust();
    adc_adjust_label_show();
    adc_adjust_vis_handler();

    vis = d_frame_get_control(frm, ID_ADC_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, adc_adjust_window_handler);
    }

    return D_OK;
}

/** @brief adc adjust菜单*/
D_Result
p_atv_adc_adjust_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&adc_adjust_window, D_TRUE);
}

