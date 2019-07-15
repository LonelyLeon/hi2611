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
#include "peq_set_window.c"

#define PEQ_PARAGRAPH 18

#define BUF_LINE 16
#define CHAN_LIST_ROW_CNT   16
#define AUDIO_STANDARD_MODE_ID 1//标准模式在数据库中的序号

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };


typedef struct
{
    D_S16 focus,
          fo1_coarse, fo2_coarse, fo3_coarse, fo4_coarse, fo5_coarse, fo6_coarse, fo7_coarse, fo8_coarse, fo9_coarse,
          fo10_coarse, fo11_coarse, fo12_coarse, fo13_coarse, fo14_coarse, fo15_coarse, fo16_coarse, fo17_coarse, fo18_coarse,
          nfft;
    D_Float gain1, gain2, gain3, gain4, gain5, gain6, gain7, gain8, gain9, gain10, gain11, gain12, gain13, gain14, gain15, gain16, gain17, gain18;

    D_VidInput input;
    D_AUDIO_Peq param[PEQ_PARAGRAPH];

    D_U32 enable;
    D_Char enable_buf[BUF_LINE];
    D_U8 mode;
    D_Char fo1_coarse_buf[BUF_LINE];
    D_Char fo2_coarse_buf[BUF_LINE];
    D_Char fo3_coarse_buf[BUF_LINE];
    D_Char fo4_coarse_buf[BUF_LINE];
    D_Char fo5_coarse_buf[BUF_LINE];
    D_Char fo6_coarse_buf[BUF_LINE];
    D_Char fo7_coarse_buf[BUF_LINE];
    D_Char fo8_coarse_buf[BUF_LINE];
    D_Char fo9_coarse_buf[BUF_LINE];
    D_Char fo10_coarse_buf[BUF_LINE];
    D_Char fo11_coarse_buf[BUF_LINE];
    D_Char fo12_coarse_buf[BUF_LINE];
    D_Char fo13_coarse_buf[BUF_LINE];
    D_Char fo14_coarse_buf[BUF_LINE];
    D_Char fo15_coarse_buf[BUF_LINE];
    D_Char fo16_coarse_buf[BUF_LINE];
    D_Char fo17_coarse_buf[BUF_LINE];
    D_Char fo18_coarse_buf[BUF_LINE];
    D_Char nfft_buf[BUF_LINE];

    D_Char gain1_buf[BUF_LINE];
    D_Char gain2_buf[BUF_LINE];
    D_Char gain3_buf[BUF_LINE];
    D_Char gain4_buf[BUF_LINE];
    D_Char gain5_buf[BUF_LINE];
    D_Char gain6_buf[BUF_LINE];
    D_Char gain7_buf[BUF_LINE];
    D_Char gain8_buf[BUF_LINE];
    D_Char gain9_buf[BUF_LINE];
    D_Char gain10_buf[BUF_LINE];
    D_Char gain11_buf[BUF_LINE];
    D_Char gain12_buf[BUF_LINE];
    D_Char gain13_buf[BUF_LINE];
    D_Char gain14_buf[BUF_LINE];
    D_Char gain15_buf[BUF_LINE];
    D_Char gain16_buf[BUF_LINE];
    D_Char gain17_buf[BUF_LINE];
    D_Char gain18_buf[BUF_LINE];

} D_PeqSetDate;

static D_PeqSetDate *peq_set_data;
static D_Bool first_flag = D_TRUE;
static D_Bool second_flag = D_FALSE;
static D_Bool third_flag = D_FALSE;
static D_Bool fourth_flag = D_FALSE;

static D_Float gain_max = 6;
static D_Float gain_min = -6;
static D_Float gain_step = 0.5;


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
set_param_of_peq(void) D_FUNCPOSTFIT
{
    D_U8 i;
	
    peq_set_data->param[0].freq = peq_set_data->fo1_coarse;
    peq_set_data->param[1].freq = peq_set_data->fo2_coarse;
    peq_set_data->param[2].freq = peq_set_data->fo3_coarse;
    peq_set_data->param[3].freq = peq_set_data->fo4_coarse;
    peq_set_data->param[4].freq = peq_set_data->fo5_coarse;
    peq_set_data->param[5].freq = peq_set_data->fo6_coarse;
    peq_set_data->param[6].freq = peq_set_data->fo7_coarse;
    peq_set_data->param[7].freq = peq_set_data->fo8_coarse;
    peq_set_data->param[8].freq = peq_set_data->fo9_coarse;
    peq_set_data->param[9].freq = peq_set_data->fo10_coarse;
    peq_set_data->param[10].freq = peq_set_data->fo11_coarse;
    peq_set_data->param[11].freq = peq_set_data->fo12_coarse;
    peq_set_data->param[12].freq = peq_set_data->fo13_coarse;
    peq_set_data->param[13].freq = peq_set_data->fo14_coarse;
    peq_set_data->param[14].freq = peq_set_data->fo15_coarse;
    peq_set_data->param[15].freq = peq_set_data->fo16_coarse;
    peq_set_data->param[16].freq = peq_set_data->fo17_coarse;
    peq_set_data->param[17].freq = peq_set_data->fo18_coarse;

    peq_set_data->param[0].gain = peq_set_data->gain1;
    peq_set_data->param[1].gain = peq_set_data->gain2;
    peq_set_data->param[2].gain = peq_set_data->gain3;
    peq_set_data->param[3].gain = peq_set_data->gain4;
    peq_set_data->param[4].gain = peq_set_data->gain5;
    peq_set_data->param[5].gain = peq_set_data->gain6;
    peq_set_data->param[6].gain = peq_set_data->gain7;
    peq_set_data->param[7].gain = peq_set_data->gain8;
    peq_set_data->param[8].gain = peq_set_data->gain9;
    peq_set_data->param[9].gain = peq_set_data->gain10;
    peq_set_data->param[10].gain = peq_set_data->gain11;
    peq_set_data->param[11].gain = peq_set_data->gain12;
    peq_set_data->param[12].gain = peq_set_data->gain13;
    peq_set_data->param[13].gain = peq_set_data->gain14;
    peq_set_data->param[14].gain = peq_set_data->gain15;
    peq_set_data->param[15].gain = peq_set_data->gain16;
    peq_set_data->param[16].gain = peq_set_data->gain17;
    peq_set_data->param[17].gain = peq_set_data->gain18;

    for(i = 0; i < PEQ_PARAGRAPH; i++)
    {
        D_DUMP("freq:%f bw:%f gain:%f \n", peq_set_data->param[i].freq, peq_set_data->param[i].bw, peq_set_data->param[i].gain);
    }
    //d_av_Audio_PEQ(0, NULL, 0, 0, D_Surround_close);
    d_av_Audio_PEQ(0, peq_set_data->param, PEQ_PARAGRAPH, peq_set_data->nfft, D_PEQ);
    return D_OK;
}

static D_Result
save_param_of_peq(void) D_FUNCPOSTFIT
{
    D_U8 i;
    for(i = 0; i < PEQ_PARAGRAPH; i ++)
    {
        p_tvconf_set_audio_peq_set_param(&peq_set_data->param[i], p_vip_get_dbinput(peq_set_data->input), peq_set_data->mode, i);
    }

    p_tvconf_set_cur_t_ffft(&peq_set_data->nfft, p_vip_get_dbinput(peq_set_data->input), peq_set_data->mode);
    return D_OK;
}


static D_S16
set_icm_set_fo_coarse_value(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        value = value + 100;
        if(value > 20000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 100)
            value = 0;
        else if(value == 0)
            value = 20000;
        else
            value = value - 100;
    }
    return value;
}

static D_S16
set_icm_set_fo_fine_value(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        value = value + 5;
        if(value > 20000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 5)
            value = 0;
        else if(value == 0)
            value = 20000;
        else
            value = value - 5;
    }
    return value;
}

static D_S16
set_icm_set_bw_coarse_value(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        value = value + 100;
        if(value > 10000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 100)
            value = 0;
        else if(value == 0)
            value = 10000;
        else
            value = value - 100;
    }
    return value;
}

static D_S16
set_icm_set_bw_fine_value(D_S16 value, D_Bool flag)
{
    if(flag)
    {
        value = value + 10;
        if(value > 10000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 10)
            value = 0;
        else if(value == 0)
            value = 10000;
        else
            value = value - 10;
    }
    return value;
}

static D_S16
set_icm_set_bw9_coarse_value(D_S16 value, D_Bool flag)
{
    if(flag)
    {
        value = value + 100;
        if(value > 12000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 100)
            value = 0;
        else if(value == 0)
            value = 12000;
        else
            value = value - 100;
    }
    return value;
}

static D_S16
set_icm_set_bw9_fine_value(D_S16 value, D_Bool flag)
{
    if(flag)
    {
        value = value + 10;
        if(value > 12000)
            value = 0;
    }
    else
    {
        if(value > 0 && value < 10)
            value = 0;
        else if(value == 0)
            value = 12000;
        else
            value = value - 10;
    }
    return value;
}

static D_Float
set_icm_set_gain_value(D_Float value, D_Bool flag)
{

    if(flag)
    {
        if((value + gain_step) <= gain_max)
            value = value + gain_step;
    }
    else
    {
        if((value - gain_step) >= gain_min)
            value = value - gain_step;
    }
    return value;
}

static D_Result
set_peq_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_PEQ_BUTTON_1:
            if(first_flag)
            {
                peq_set_data->enable = (peq_set_data->enable + 1) % 2;
                sprintf(peq_set_data->enable_buf, "%d", peq_set_data->enable);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
                d_label_set_text(vis, peq_set_data->enable_buf);
                d_av_peq_ctrl(0, peq_set_data->enable);
                p_tvconf_set_avc_peq_en(peq_set_data->enable);
                return D_OK;
            }
            else if(second_flag)
            {
                peq_set_data->fo8_coarse = set_icm_set_fo_fine_value(peq_set_data->fo8_coarse, flag);
                sprintf(peq_set_data->fo8_coarse_buf, "%d", peq_set_data->fo8_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
                d_label_set_text(vis, peq_set_data->fo8_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->fo16_coarse = set_icm_set_fo_fine_value(peq_set_data->fo16_coarse, flag);
                sprintf(peq_set_data->fo16_coarse_buf, "%d", peq_set_data->fo16_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
                d_label_set_text(vis, peq_set_data->fo16_coarse_buf);
            }
            else
            {
                peq_set_data->gain12 = set_icm_set_gain_value(peq_set_data->gain12, flag);
                sprintf(peq_set_data->gain12_buf, "%.1f", peq_set_data->gain12);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
                d_label_set_text(vis, peq_set_data->gain12_buf);
            }
            break;
        case ID_PEQ_BUTTON_2:
            if(first_flag)
            {
                peq_set_data->fo1_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo1_coarse, flag);
                sprintf(peq_set_data->fo1_coarse_buf, "%d", peq_set_data->fo1_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo1_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo1_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo9_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo9_coarse, flag);
                sprintf(peq_set_data->fo9_coarse_buf, "%d", peq_set_data->fo9_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo9_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo9_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->fo17_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo17_coarse, flag);
                sprintf(peq_set_data->fo17_coarse_buf, "%d", peq_set_data->fo17_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo17_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo17_coarse_buf);
            }
            else
            {
                peq_set_data->gain13 = set_icm_set_gain_value(peq_set_data->gain13, flag);
                sprintf(peq_set_data->gain13_buf, "%.1f", peq_set_data->gain13);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->gain13_buf);
            }
            break;
        case ID_PEQ_BUTTON_3:
            if(first_flag)
            {
                peq_set_data->fo1_coarse = set_icm_set_fo_fine_value(peq_set_data->fo1_coarse, flag);
                sprintf(peq_set_data->fo1_coarse_buf, "%d", peq_set_data->fo1_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo1_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo1_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo9_coarse = set_icm_set_fo_fine_value(peq_set_data->fo9_coarse, flag);
                sprintf(peq_set_data->fo9_coarse_buf, "%d", peq_set_data->fo9_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo9_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo9_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->fo17_coarse = set_icm_set_fo_fine_value(peq_set_data->fo17_coarse, flag);
                sprintf(peq_set_data->fo17_coarse_buf, "%d", peq_set_data->fo17_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
                d_label_set_text(vis, peq_set_data->fo17_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->fo17_coarse_buf);
            }
            else
            {
                peq_set_data->gain14 = set_icm_set_gain_value(peq_set_data->gain14, flag);
                sprintf(peq_set_data->gain14_buf, "%.1f", peq_set_data->gain14);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
                d_label_set_text(vis, peq_set_data->gain14_buf);
            }
            break;
        case ID_PEQ_BUTTON_4:
            if(first_flag)
            {
                peq_set_data->fo2_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo2_coarse, flag);
                sprintf(peq_set_data->fo2_coarse_buf, "%d", peq_set_data->fo2_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo2_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo2_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo10_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo10_coarse, flag);
                sprintf(peq_set_data->fo10_coarse_buf, "%d", peq_set_data->fo10_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo10_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo10_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->fo18_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo18_coarse, flag);
                sprintf(peq_set_data->fo18_coarse_buf, "%d", peq_set_data->fo18_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo18_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo18_coarse_buf);
            }
            else
            {
                peq_set_data->gain15 = set_icm_set_gain_value(peq_set_data->gain15, flag);
                sprintf(peq_set_data->gain15_buf, "%.1f", peq_set_data->gain15);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->gain15_buf);
            }
            break;
        case ID_PEQ_BUTTON_5:
            if(first_flag)
            {
                peq_set_data->fo2_coarse = set_icm_set_fo_fine_value(peq_set_data->fo2_coarse, flag);
                sprintf(peq_set_data->fo2_coarse_buf, "%d", peq_set_data->fo2_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo2_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo2_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo10_coarse = set_icm_set_fo_fine_value(peq_set_data->fo10_coarse, flag);
                sprintf(peq_set_data->fo10_coarse_buf, "%d", peq_set_data->fo10_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo10_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo10_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->fo18_coarse = set_icm_set_fo_fine_value(peq_set_data->fo18_coarse, flag);
                sprintf(peq_set_data->fo18_coarse_buf, "%d", peq_set_data->fo18_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
                d_label_set_text(vis, peq_set_data->fo18_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->fo18_coarse_buf);
            }
            else
            {
                peq_set_data->gain16 = set_icm_set_gain_value(peq_set_data->gain16, flag);
                sprintf(peq_set_data->gain16_buf, "%.1f", peq_set_data->gain16);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
                d_label_set_text(vis, peq_set_data->gain16_buf);
            }

            break;
        case ID_PEQ_BUTTON_6:
            if(first_flag)
            {
                peq_set_data->fo3_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo3_coarse, flag);
                sprintf(peq_set_data->fo3_coarse_buf, "%d", peq_set_data->fo3_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->fo3_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->fo3_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo11_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo11_coarse, flag);
                sprintf(peq_set_data->fo11_coarse_buf, "%d", peq_set_data->fo11_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->fo11_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->fo11_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain1 = set_icm_set_gain_value(peq_set_data->gain1, flag);
                sprintf(peq_set_data->gain1_buf, "%.1f", peq_set_data->gain1);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->gain1_buf);
            }
            else
            {
                peq_set_data->gain17 = set_icm_set_gain_value(peq_set_data->gain17, flag);
                sprintf(peq_set_data->gain17_buf, "%.1f", peq_set_data->gain17);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->gain17_buf);
            }
            break;
        case ID_PEQ_BUTTON_7:
            if(first_flag)
            {
                peq_set_data->fo3_coarse = set_icm_set_fo_fine_value(peq_set_data->fo3_coarse, flag);
                sprintf(peq_set_data->fo3_coarse_buf, "%d", peq_set_data->fo3_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->fo3_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->fo3_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo11_coarse = set_icm_set_fo_fine_value(peq_set_data->fo11_coarse, flag);
                sprintf(peq_set_data->fo11_coarse_buf, "%d", peq_set_data->fo11_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
                d_label_set_text(vis, peq_set_data->fo11_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->fo11_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain2 = set_icm_set_gain_value(peq_set_data->gain2, flag);
                sprintf(peq_set_data->gain2_buf, "%.1f", peq_set_data->gain2);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->gain2_buf);
            }
            else
            {
                peq_set_data->gain18 = set_icm_set_gain_value(peq_set_data->gain18, flag);
                sprintf(peq_set_data->gain18_buf, "%.1f", peq_set_data->gain18);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
                d_label_set_text(vis, peq_set_data->gain18_buf);
            }
            break;
        case ID_PEQ_BUTTON_8:
            if(first_flag)
            {
                peq_set_data->fo4_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo4_coarse, flag);
                sprintf(peq_set_data->fo4_coarse_buf, "%d", peq_set_data->fo4_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->fo4_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
                d_label_set_text(vis, peq_set_data->fo4_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo12_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo12_coarse, flag);
                sprintf(peq_set_data->fo12_coarse_buf, "%d", peq_set_data->fo12_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->fo12_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
                d_label_set_text(vis, peq_set_data->fo12_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain3 = set_icm_set_gain_value(peq_set_data->gain3, flag);
                sprintf(peq_set_data->gain3_buf, "%.1f", peq_set_data->gain3);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->gain3_buf);
            }
            else
            {
                if(flag)
                {
                    if(peq_set_data->nfft == 2048)
                        peq_set_data->nfft = 64;
                    else
                        peq_set_data->nfft = peq_set_data->nfft * 2;
                }
                else
                {
                    if(peq_set_data->nfft == 64)
                        peq_set_data->nfft = 2048;
                    else
                        peq_set_data->nfft = peq_set_data->nfft / 2;
                }
                sprintf(peq_set_data->nfft_buf, "%d", peq_set_data->nfft);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->nfft_buf);
            }
            break;
        case ID_PEQ_BUTTON_9:

            if(first_flag)
            {
                peq_set_data->fo4_coarse = set_icm_set_fo_fine_value(peq_set_data->fo4_coarse, flag);
                sprintf(peq_set_data->fo4_coarse_buf, "%d", peq_set_data->fo4_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->fo4_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
                d_label_set_text(vis, peq_set_data->fo4_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo12_coarse = set_icm_set_fo_fine_value(peq_set_data->fo12_coarse, flag);
                sprintf(peq_set_data->fo12_coarse_buf, "%d", peq_set_data->fo12_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
                d_label_set_text(vis, peq_set_data->fo12_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
                d_label_set_text(vis, peq_set_data->fo12_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain4 = set_icm_set_gain_value(peq_set_data->gain4, flag);
                sprintf(peq_set_data->gain4_buf, "%.1f", peq_set_data->gain4);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
                d_label_set_text(vis, peq_set_data->gain4_buf);
            }
            break;
        case ID_PEQ_BUTTON_10:
            if(first_flag)
            {
                peq_set_data->fo5_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo5_coarse, flag);
                sprintf(peq_set_data->fo5_coarse_buf, "%d", peq_set_data->fo5_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
                d_label_set_text(vis, peq_set_data->fo5_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
                d_label_set_text(vis, peq_set_data->fo5_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo13_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo13_coarse, flag);
                sprintf(peq_set_data->fo13_coarse_buf, "%d", peq_set_data->fo13_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
                d_label_set_text(vis, peq_set_data->fo13_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
                d_label_set_text(vis, peq_set_data->fo13_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain5 = set_icm_set_gain_value(peq_set_data->gain5, flag);
                sprintf(peq_set_data->gain5_buf, "%.1f", peq_set_data->gain5);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
                d_label_set_text(vis, peq_set_data->gain5_buf);
            }
            break;
        case ID_PEQ_BUTTON_11:
            if(first_flag)
            {
                peq_set_data->fo5_coarse = set_icm_set_fo_fine_value(peq_set_data->fo5_coarse, flag);
                sprintf(peq_set_data->fo5_coarse_buf, "%d", peq_set_data->fo5_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
                d_label_set_text(vis, peq_set_data->fo5_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
                d_label_set_text(vis, peq_set_data->fo5_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo13_coarse = set_icm_set_fo_fine_value(peq_set_data->fo13_coarse, flag);
                sprintf(peq_set_data->fo13_coarse_buf, "%d", peq_set_data->fo13_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
                d_label_set_text(vis, peq_set_data->fo13_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
                d_label_set_text(vis, peq_set_data->fo13_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain6 = set_icm_set_gain_value(peq_set_data->gain6, flag);
                sprintf(peq_set_data->gain6_buf, "%.1f", peq_set_data->gain6);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
                d_label_set_text(vis, peq_set_data->gain6_buf);
            }
            break;
        case ID_PEQ_BUTTON_12:
            if(first_flag)
            {
                peq_set_data->fo6_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo6_coarse, flag);
                sprintf(peq_set_data->fo6_coarse_buf, "%d", peq_set_data->fo6_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
                d_label_set_text(vis, peq_set_data->fo6_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
                d_label_set_text(vis, peq_set_data->fo6_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo14_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo14_coarse, flag);
                sprintf(peq_set_data->fo14_coarse_buf, "%d", peq_set_data->fo14_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
                d_label_set_text(vis, peq_set_data->fo14_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
                d_label_set_text(vis, peq_set_data->fo14_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain7 = set_icm_set_gain_value(peq_set_data->gain7, flag);
                sprintf(peq_set_data->gain7_buf, "%.1f", peq_set_data->gain7);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
                d_label_set_text(vis, peq_set_data->gain7_buf);
            }
            break;
        case ID_PEQ_BUTTON_13:
            if(first_flag)
            {
                peq_set_data->fo6_coarse = set_icm_set_fo_fine_value(peq_set_data->fo6_coarse, flag);
                sprintf(peq_set_data->fo6_coarse_buf, "%d", peq_set_data->fo6_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
                d_label_set_text(vis, peq_set_data->fo6_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
                d_label_set_text(vis, peq_set_data->fo6_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo14_coarse = set_icm_set_fo_fine_value(peq_set_data->fo14_coarse, flag);
                sprintf(peq_set_data->fo14_coarse_buf, "%d", peq_set_data->fo14_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
                d_label_set_text(vis, peq_set_data->fo14_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
                d_label_set_text(vis, peq_set_data->fo14_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain8 = set_icm_set_gain_value(peq_set_data->gain8, flag);
                sprintf(peq_set_data->gain8_buf, "%.1f", peq_set_data->gain8);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
                d_label_set_text(vis, peq_set_data->gain8_buf);
            }
            break;
        case ID_PEQ_BUTTON_14:
            if(first_flag)
            {
                peq_set_data->fo7_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo7_coarse, flag);
                sprintf(peq_set_data->fo7_coarse_buf, "%d", peq_set_data->fo7_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
                d_label_set_text(vis, peq_set_data->fo7_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
                d_label_set_text(vis, peq_set_data->fo7_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo15_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo15_coarse, flag);
                sprintf(peq_set_data->fo15_coarse_buf, "%d", peq_set_data->fo15_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
                d_label_set_text(vis, peq_set_data->fo15_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
                d_label_set_text(vis, peq_set_data->fo15_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain9 = set_icm_set_gain_value(peq_set_data->gain9, flag);
                sprintf(peq_set_data->gain9_buf, "%.1f", peq_set_data->gain9);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
                d_label_set_text(vis, peq_set_data->gain9_buf);
            }
            break;
        case ID_PEQ_BUTTON_15:
            if(first_flag)
            {
                peq_set_data->fo7_coarse = set_icm_set_fo_fine_value(peq_set_data->fo7_coarse, flag);
                sprintf(peq_set_data->fo7_coarse_buf, "%d", peq_set_data->fo7_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
                d_label_set_text(vis, peq_set_data->fo7_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
                d_label_set_text(vis, peq_set_data->fo7_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo15_coarse = set_icm_set_fo_fine_value(peq_set_data->fo15_coarse, flag);
                sprintf(peq_set_data->fo15_coarse_buf, "%d", peq_set_data->fo15_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
                d_label_set_text(vis, peq_set_data->fo15_coarse_buf);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
                d_label_set_text(vis, peq_set_data->fo15_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain10 = set_icm_set_gain_value(peq_set_data->gain10, flag);
                sprintf(peq_set_data->gain10_buf, "%.1f", peq_set_data->gain10);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
                d_label_set_text(vis, peq_set_data->gain10_buf);
            }
            break;
        case ID_PEQ_BUTTON_16:
            if(first_flag)
            {
                peq_set_data->fo8_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo8_coarse, flag);
                sprintf(peq_set_data->fo8_coarse_buf, "%d", peq_set_data->fo8_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
                d_label_set_text(vis, peq_set_data->fo8_coarse_buf);
            }
            else if(second_flag)
            {
                peq_set_data->fo16_coarse = set_icm_set_fo_coarse_value(peq_set_data->fo16_coarse, flag);
                sprintf(peq_set_data->fo16_coarse_buf, "%d", peq_set_data->fo16_coarse);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
                d_label_set_text(vis, peq_set_data->fo16_coarse_buf);
            }
            else if(third_flag)
            {
                peq_set_data->gain11 = set_icm_set_gain_value(peq_set_data->gain11, flag);
                sprintf(peq_set_data->gain11_buf, "%.1f", peq_set_data->gain11);
                vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
                d_label_set_text(vis, peq_set_data->gain11_buf);
            }
            break;
        default:
            break;
    }
    set_param_of_peq();

    return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_2_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_3_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_6_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_7_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_8_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_9_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_9);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_10_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_10);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_11_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_11);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
} static D_Result
button_12_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_12);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_13_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_13);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_14_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_14);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_15_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_15);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
button_16_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_PEQ_LABEL_16);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_peq_set_data(id, D_TRUE);
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
get_set_of_peq_set(void)
{
    D_U8 i = 0;
    p_tvconf_get_cur_audiomode(&peq_set_data->mode, p_vip_get_dbinput(peq_set_data->input));
    p_tvconf_get_cur_t_ffft(&peq_set_data->nfft, p_vip_get_dbinput(peq_set_data->input), peq_set_data->mode);

    for(i = 0; i < PEQ_PARAGRAPH; i++)
        p_tvconf_get_audio_peq_set_param(&peq_set_data->param[i], p_vip_get_dbinput(peq_set_data->input), peq_set_data->mode, i);

    peq_set_data->enable = p_tvconf_get_avc_peq_en();
    peq_set_data->enable = D_MIN(peq_set_data->enable, 1);

    peq_set_data->fo1_coarse = peq_set_data->param[0].freq;
    peq_set_data->fo2_coarse = peq_set_data->param[1].freq;
    peq_set_data->fo3_coarse = peq_set_data->param[2].freq;
    peq_set_data->fo4_coarse = peq_set_data->param[3].freq;
    peq_set_data->fo5_coarse = peq_set_data->param[4].freq;
    peq_set_data->fo6_coarse = peq_set_data->param[5].freq;
    peq_set_data->fo7_coarse = peq_set_data->param[6].freq;
    peq_set_data->fo8_coarse = peq_set_data->param[7].freq;
    peq_set_data->fo9_coarse = peq_set_data->param[8].freq;
    peq_set_data->fo10_coarse = peq_set_data->param[9].freq;
    peq_set_data->fo11_coarse = peq_set_data->param[10].freq;
    peq_set_data->fo12_coarse = peq_set_data->param[11].freq;
    peq_set_data->fo13_coarse = peq_set_data->param[12].freq;
    peq_set_data->fo14_coarse = peq_set_data->param[13].freq;
    peq_set_data->fo15_coarse = peq_set_data->param[14].freq;
    peq_set_data->fo16_coarse = peq_set_data->param[15].freq;
    peq_set_data->fo17_coarse = peq_set_data->param[16].freq;
    peq_set_data->fo18_coarse = peq_set_data->param[17].freq;

    peq_set_data->gain1 = peq_set_data->param[0].gain;
    peq_set_data->gain2 = peq_set_data->param[1].gain;
    peq_set_data->gain3 = peq_set_data->param[2].gain;
    peq_set_data->gain4 = peq_set_data->param[3].gain;
    peq_set_data->gain5 = peq_set_data->param[4].gain;
    peq_set_data->gain6 = peq_set_data->param[5].gain;
    peq_set_data->gain7 = peq_set_data->param[6].gain;
    peq_set_data->gain8 = peq_set_data->param[7].gain;
    peq_set_data->gain9 = peq_set_data->param[8].gain;
    peq_set_data->gain10 = peq_set_data->param[9].gain;
    peq_set_data->gain11 = peq_set_data->param[10].gain;
    peq_set_data->gain12 = peq_set_data->param[11].gain;
    peq_set_data->gain13 = peq_set_data->param[12].gain;
    peq_set_data->gain14 = peq_set_data->param[13].gain;
    peq_set_data->gain15 = peq_set_data->param[14].gain;
    peq_set_data->gain16 = peq_set_data->param[15].gain;
    peq_set_data->gain17 = peq_set_data->param[16].gain;
    peq_set_data->gain18 = peq_set_data->param[17].gain;

    sprintf(peq_set_data->fo1_coarse_buf, "%d", peq_set_data->fo1_coarse);
    sprintf(peq_set_data->fo2_coarse_buf, "%d", peq_set_data->fo2_coarse);
    sprintf(peq_set_data->fo3_coarse_buf, "%d", peq_set_data->fo3_coarse);
    sprintf(peq_set_data->fo4_coarse_buf, "%d", peq_set_data->fo4_coarse);
    sprintf(peq_set_data->fo5_coarse_buf, "%d", peq_set_data->fo5_coarse);
    sprintf(peq_set_data->fo6_coarse_buf, "%d", peq_set_data->fo6_coarse);
    sprintf(peq_set_data->fo7_coarse_buf, "%d", peq_set_data->fo7_coarse);
    sprintf(peq_set_data->fo8_coarse_buf, "%d", peq_set_data->fo8_coarse);
    sprintf(peq_set_data->fo9_coarse_buf, "%d", peq_set_data->fo9_coarse);
    sprintf(peq_set_data->fo10_coarse_buf, "%d", peq_set_data->fo10_coarse);
    sprintf(peq_set_data->fo11_coarse_buf, "%d", peq_set_data->fo11_coarse);
    sprintf(peq_set_data->fo12_coarse_buf, "%d", peq_set_data->fo12_coarse);
    sprintf(peq_set_data->fo13_coarse_buf, "%d", peq_set_data->fo13_coarse);
    sprintf(peq_set_data->fo14_coarse_buf, "%d", peq_set_data->fo14_coarse);
    sprintf(peq_set_data->fo15_coarse_buf, "%d", peq_set_data->fo15_coarse);
    sprintf(peq_set_data->fo16_coarse_buf, "%d", peq_set_data->fo16_coarse);
    sprintf(peq_set_data->fo17_coarse_buf, "%d", peq_set_data->fo17_coarse);
    sprintf(peq_set_data->fo18_coarse_buf, "%d", peq_set_data->fo18_coarse);

    sprintf(peq_set_data->gain1_buf, "%.1f", peq_set_data->gain1);
    sprintf(peq_set_data->gain2_buf, "%.1f", peq_set_data->gain2);
    sprintf(peq_set_data->gain3_buf, "%.1f", peq_set_data->gain3);
    sprintf(peq_set_data->gain4_buf, "%.1f", peq_set_data->gain4);
    sprintf(peq_set_data->gain5_buf, "%.1f", peq_set_data->gain5);
    sprintf(peq_set_data->gain6_buf, "%.1f", peq_set_data->gain6);
    sprintf(peq_set_data->gain7_buf, "%.1f", peq_set_data->gain7);
    sprintf(peq_set_data->gain8_buf, "%.1f", peq_set_data->gain8);
    sprintf(peq_set_data->gain9_buf, "%.1f", peq_set_data->gain9);
    sprintf(peq_set_data->gain10_buf, "%.1f", peq_set_data->gain10);
    sprintf(peq_set_data->gain11_buf, "%.1f", peq_set_data->gain11);
    sprintf(peq_set_data->gain12_buf, "%.1f", peq_set_data->gain12);
    sprintf(peq_set_data->gain13_buf, "%.1f", peq_set_data->gain13);
    sprintf(peq_set_data->gain14_buf, "%.1f", peq_set_data->gain14);
    sprintf(peq_set_data->gain15_buf, "%.1f", peq_set_data->gain15);
    sprintf(peq_set_data->gain16_buf, "%.1f", peq_set_data->gain16);
    sprintf(peq_set_data->gain17_buf, "%.1f", peq_set_data->gain17);
    sprintf(peq_set_data->gain18_buf, "%.1f", peq_set_data->gain18);

    sprintf(peq_set_data->nfft_buf, "%d", peq_set_data->nfft);
    sprintf(peq_set_data->enable_buf, "%d", peq_set_data->enable);

    return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;
    D_ID i;

    first_flag = D_TRUE;
    second_flag = D_FALSE;
    third_flag = D_FALSE;
    fourth_flag = D_FALSE;

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_1);
    d_label_set_text(vis, "PEG ENABLE");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_2);
    d_label_set_text(vis, "FO1-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_3);
    d_label_set_text(vis, "FO1-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_4);
    d_label_set_text(vis, "FO2-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_5);
    d_label_set_text(vis, "FO2-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_6);
    d_label_set_text(vis, "FO3-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_7);
    d_label_set_text(vis, "FO3-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_8);
    d_label_set_text(vis, "FO4-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_label_set_text(vis, "FO4-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_label_set_text(vis, "FO5-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_label_set_text(vis, "FO5-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_label_set_text(vis, "FO6-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_label_set_text(vis, "FO6-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_label_set_text(vis, "FO7-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_label_set_text(vis, "FO7-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_label_set_text(vis, "FO8-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
    d_label_set_text(vis, peq_set_data->enable_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
    d_label_set_text(vis, peq_set_data->fo1_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
    d_label_set_text(vis, peq_set_data->fo1_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
    d_label_set_text(vis, peq_set_data->fo2_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
    d_label_set_text(vis, peq_set_data->fo2_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
    d_label_set_text(vis, peq_set_data->fo3_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
    d_label_set_text(vis, peq_set_data->fo3_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
    d_label_set_text(vis, peq_set_data->fo4_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
    d_label_set_text(vis, peq_set_data->fo4_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
    d_label_set_text(vis, peq_set_data->fo5_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
    d_label_set_text(vis, peq_set_data->fo5_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
    d_label_set_text(vis, peq_set_data->fo6_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
    d_label_set_text(vis, peq_set_data->fo6_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
    d_label_set_text(vis, peq_set_data->fo7_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
    d_label_set_text(vis, peq_set_data->fo7_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
    d_label_set_text(vis, peq_set_data->fo8_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_9);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_10);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_11);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_12);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_13);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_14);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_15);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_16);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_vis_set_focusable(vis, D_TRUE);

    return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;
    D_ID i;

    first_flag = D_FALSE;
    second_flag = D_TRUE;
    third_flag = D_FALSE;
    fourth_flag = D_FALSE;

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_1);
    d_label_set_text(vis, "FO8-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_2);
    d_label_set_text(vis, "FO9-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_3);
    d_label_set_text(vis, "FO9-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_4);
    d_label_set_text(vis, "FO10-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_5);
    d_label_set_text(vis, "FO10-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_6);
    d_label_set_text(vis, "FO11-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_7);
    d_label_set_text(vis, "FO11-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_8);
    d_label_set_text(vis, "FO12-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_label_set_text(vis, "FO12-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_label_set_text(vis, "FO13-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_label_set_text(vis, "FO13-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_label_set_text(vis, "FO14-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_label_set_text(vis, "FO14-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_label_set_text(vis, "FO15-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_label_set_text(vis, "FO15-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_label_set_text(vis, "FO16-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
    d_label_set_text(vis, peq_set_data->fo8_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
    d_label_set_text(vis, peq_set_data->fo9_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
    d_label_set_text(vis, peq_set_data->fo9_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
    d_label_set_text(vis, peq_set_data->fo10_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
    d_label_set_text(vis, peq_set_data->fo10_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
    d_label_set_text(vis, peq_set_data->fo11_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
    d_label_set_text(vis, peq_set_data->fo11_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
    d_label_set_text(vis, peq_set_data->fo12_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
    d_label_set_text(vis, peq_set_data->fo12_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
    d_label_set_text(vis, peq_set_data->fo13_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
    d_label_set_text(vis, peq_set_data->fo13_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
    d_label_set_text(vis, peq_set_data->fo14_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
    d_label_set_text(vis, peq_set_data->fo14_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
    d_label_set_text(vis, peq_set_data->fo15_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
    d_label_set_text(vis, peq_set_data->fo15_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
    d_label_set_text(vis, peq_set_data->fo16_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_9);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_10);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_11);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_12);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_13);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_14);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_15);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_16);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_vis_set_focusable(vis, D_TRUE);

    return D_OK;
}

static D_Result
set_third_page_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;
    D_ID i;

    first_flag = D_FALSE;
    second_flag = D_FALSE;
    third_flag = D_TRUE;
    fourth_flag = D_FALSE;

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_1);
    d_label_set_text(vis, "FO16-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_2);
    d_label_set_text(vis, "FO17-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_3);
    d_label_set_text(vis, "FO17-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_4);
    d_label_set_text(vis, "FO18-Coarse Hz");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_5);
    d_label_set_text(vis, "FO18-Fine");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_6);
    d_label_set_text(vis, "Gain 1 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_7);
    d_label_set_text(vis, "Gain 2 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_8);
    d_label_set_text(vis, "Gain 3 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_label_set_text(vis, "Gain 4 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_label_set_text(vis, "Gain 5 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_label_set_text(vis, "Gain 6 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_label_set_text(vis, "Gain 7 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_label_set_text(vis, "Gain 8 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_label_set_text(vis, "Gain 9 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_label_set_text(vis, "Gain 10 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_label_set_text(vis, "Gain 11 db");

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
    d_label_set_text(vis, peq_set_data->fo16_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
    d_label_set_text(vis, peq_set_data->fo17_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
    d_label_set_text(vis, peq_set_data->fo17_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
    d_label_set_text(vis, peq_set_data->fo18_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
    d_label_set_text(vis, peq_set_data->fo18_coarse_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
    d_label_set_text(vis, peq_set_data->gain1_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
    d_label_set_text(vis, peq_set_data->gain2_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
    d_label_set_text(vis, peq_set_data->gain3_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
    d_label_set_text(vis, peq_set_data->gain4_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
    d_label_set_text(vis, peq_set_data->gain5_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
    d_label_set_text(vis, peq_set_data->gain6_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
    d_label_set_text(vis, peq_set_data->gain7_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
    d_label_set_text(vis, peq_set_data->gain8_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
    d_label_set_text(vis, peq_set_data->gain9_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
    d_label_set_text(vis, peq_set_data->gain10_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
    d_label_set_text(vis, peq_set_data->gain11_buf);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_9);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_10);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_11);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_12);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_13);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_14);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_15);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_vis_set_focusable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_16);
    d_vis_enable(vis, D_TRUE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_vis_set_focusable(vis, D_TRUE);

    return D_OK;
}

static D_Result
set_fourth_page_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;
    D_ID i;

    first_flag = D_FALSE;
    second_flag = D_FALSE;
    third_flag = D_FALSE;
    fourth_flag = D_TRUE;

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_1);
    d_label_set_text(vis, "Gain 12 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_2);
    d_label_set_text(vis, "Gain 13 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_3);
    d_label_set_text(vis, "Gain 14 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_4);
    d_label_set_text(vis, "Gain 15 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_5);
    d_label_set_text(vis, "Gain 16 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_6);
    d_label_set_text(vis, "Gain 17 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_7);
    d_label_set_text(vis, "Gain 18 db");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_8);
    d_label_set_text(vis, "Nfft");

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_1);
    d_label_set_text(vis, peq_set_data->gain12_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_2);
    d_label_set_text(vis, peq_set_data->gain13_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_3);
    d_label_set_text(vis, peq_set_data->gain14_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_4);
    d_label_set_text(vis, peq_set_data->gain15_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_5);
    d_label_set_text(vis, peq_set_data->gain16_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_6);
    d_label_set_text(vis, peq_set_data->gain17_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_7);
    d_label_set_text(vis, peq_set_data->gain18_buf);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_8);
    d_label_set_text(vis, peq_set_data->nfft_buf);


    vis = d_frame_get_control(frm, ID_PEQ_GROUP_9);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_9);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_10);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_10);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_11);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_11);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_12);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_12);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_13);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_13);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_14);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_14);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_15);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_15);
    d_label_set_text(vis, NULL);

    vis = d_frame_get_control(frm, ID_PEQ_GROUP_16);
    d_vis_enable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_label_set_text(vis, NULL);
    d_vis_set_focusable(vis, D_FALSE);

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_16);
    d_label_set_text(vis, NULL);

    return D_OK;
}


static D_Result
peq_set_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &peq_set_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_PEQ_LABEL_PEQ);
    d_label_set_text(vis, "PEQ");

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_1);
    d_vis_set_handler(vis, button_1_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_2);
    d_vis_set_handler(vis, button_2_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_3);
    d_vis_set_handler(vis, button_3_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_4);
    d_vis_set_handler(vis, button_4_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_5);
    d_vis_set_handler(vis, button_5_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_6);
    d_vis_set_handler(vis, button_6_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_7);
    d_vis_set_handler(vis, button_7_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_8);
    d_vis_set_handler(vis, button_8_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_9);
    d_vis_set_handler(vis, button_9_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_10);
    d_vis_set_handler(vis, button_10_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_11);
    d_vis_set_handler(vis, button_11_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_12);
    d_vis_set_handler(vis, button_12_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_13);
    d_vis_set_handler(vis, button_13_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_14);
    d_vis_set_handler(vis, button_14_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_15);
    d_vis_set_handler(vis, button_15_set_handler);

    vis = d_frame_get_control(frm, ID_PEQ_BUTTON_16);
    d_vis_set_handler(vis, button_16_set_handler);

    return D_OK;
}


static D_Result
peq_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &peq_set_window;
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
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    if(peq_set_data->focus == ID_PEQ_BUTTON_1 && first_flag)
                    {
                        set_fourth_page_show();
                        peq_set_data->focus = ID_PEQ_BUTTON_8;
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_1 && second_flag)
                    {
                        set_first_page_show();
                        peq_set_data->focus = ID_PEQ_BUTTON_16;
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_1 && third_flag)
                    {
                        set_second_page_show();
                        peq_set_data->focus = ID_PEQ_BUTTON_16;
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_1 && fourth_flag)
                    {
                        set_third_page_show();
                        peq_set_data->focus = ID_PEQ_BUTTON_16;
                    }
					else
                    {
                        peq_set_data->focus--;
                    }
                    d_vis_set_focus(d_frame_get_control(frm, peq_set_data->focus));
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(peq_set_data->focus == ID_PEQ_BUTTON_16 && first_flag)
                    {
                        peq_set_data->focus = ID_PEQ_BUTTON_1;
                        set_second_page_show();
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_16 && second_flag)
                    {
                        set_third_page_show();
                        peq_set_data->focus = ID_PEQ_BUTTON_1;
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_16 && third_flag)
                    {
                        peq_set_data->focus = ID_PEQ_BUTTON_1;
                        set_fourth_page_show();
                    }
                    else if(peq_set_data->focus == ID_PEQ_BUTTON_8 && fourth_flag)
                    {
                        peq_set_data->focus = ID_PEQ_BUTTON_1;
                        set_first_page_show();
                    }                    
					else
                    {
                        peq_set_data->focus++;
                    }
                    d_vis_set_focus(d_frame_get_control(frm, peq_set_data->focus));
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    set_peq_set_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_peq_set_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_peq();
            if(peq_set_data)
            {
                PROJECT_FREE(peq_set_data);
                peq_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}
D_Result
peq_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    peq_set_data = (D_PeqSetDate*)PROJECT_ALLOC(sizeof(D_PeqSetDate));
    if(!peq_set_data)
    {
        return D_ERR;
    }
    memset(peq_set_data, 0, sizeof(D_PeqSetDate));
    peq_set_data->input = p_conf_get_vid_input();

    gain_max = 20;
    gain_min = -20;
    gain_step = 0.1;

    get_set_of_peq_set();
    set_first_page_show();
    peq_set_vis_handler();

    peq_set_data->focus = ID_PEQ_BUTTON_1;

    vis = d_frame_get_control(frm, ID_PEQ_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }


    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, peq_set_window_handler);
    }

    return D_OK;
}

/** @brief peq菜单*/
D_Result
p_atv_peq_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&peq_set_window, D_TRUE);
}
