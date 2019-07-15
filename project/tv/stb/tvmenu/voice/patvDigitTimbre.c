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
#include "digit_timbre_window.c"

#define BUF_LINE 16

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

D_Bool  mode_flag;
typedef struct
{
    D_S16 nfft;
    D_Float user_50, user_75, user_100, user_300, user_1k, user_3k, user_5k, user_10k, user_15k;
    D_VidInput input;
    D_U8 mode;//声音模式
    D_AUDIO_Peq param[9];

    D_Char user_50_buf[BUF_LINE];
    D_Char user_75_buf[BUF_LINE];
    D_Char user_100_buf[BUF_LINE];
    D_Char user_300_buf[BUF_LINE];
    D_Char user_1k_buf[BUF_LINE];
    D_Char user_3k_buf[BUF_LINE];
    D_Char user_5k_buf[BUF_LINE];
    D_Char user_10k_buf[BUF_LINE];
    D_Char user_15k_buf[BUF_LINE];
    D_Char nfft_buf[BUF_LINE];

    D_Char button_1[BUF_LINE];
    D_Char button_2[BUF_LINE];
    D_Char button_3[BUF_LINE];
    D_Char button_4[BUF_LINE];
    D_Char button_5[BUF_LINE];
    D_Char button_6[BUF_LINE];
    D_Char button_7[BUF_LINE];
    D_Char button_8[BUF_LINE];
    D_Char button_9[BUF_LINE];

} D_DigitTimbreDate;

static D_DigitTimbreDate *digit_timbre_data;

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
save_param_of_digit_timbre(void) D_FUNCPOSTFIT
{
    D_U8 i;
    for(i = 0; i < 9; i ++)
    {

        p_tvconf_set_audio_peq_set_param(&digit_timbre_data->param[i], p_vip_get_dbinput(digit_timbre_data->input),digit_timbre_data->mode, i);
    }
    p_tvconf_set_cur_t_ffft(&digit_timbre_data->nfft, p_vip_get_dbinput(digit_timbre_data->input),digit_timbre_data->mode);
    return D_OK;
}

static D_Result
set_param_of_digit_timbre(void) D_FUNCPOSTFIT
{
    digit_timbre_data->param[0].gain = digit_timbre_data->user_50;
    digit_timbre_data->param[1].gain = digit_timbre_data->user_75;
    digit_timbre_data->param[2].gain = digit_timbre_data->user_100;
    digit_timbre_data->param[3].gain = digit_timbre_data->user_300;
    digit_timbre_data->param[4].gain = digit_timbre_data->user_1k;
    digit_timbre_data->param[5].gain = digit_timbre_data->user_3k;
    digit_timbre_data->param[6].gain = digit_timbre_data->user_5k;
    digit_timbre_data->param[7].gain = digit_timbre_data->user_10k;
    digit_timbre_data->param[8].gain = digit_timbre_data->user_15k;

    d_av_Audio_PEQ(0, digit_timbre_data->param, 9, digit_timbre_data->nfft, D_Digital_Audio);

    return D_OK;
}
#if 0
static D_Float
set_digit_timbre_value(D_Float value, D_Bool flag)
{
    if(flag)
    {
        if(value >= 5.9f)
            value = -6.0f;
        else
            value = value + 0.1f;
    }
    else
    {
        if(value <= -5.9f)
            value = 6.0f;
        else
            value = value - 0.1f;
    }

    return value;
}
#else
static D_Float
set_digit_timbre_value(D_Float value, D_Bool flag)
{

    if(flag)
    {
        if(value >= 12.0f)
            value = -12.0f;
        else
        {
            //value = value + 0.1f;
            value = value + 1.0f;
        }
    }
    else
    {
        if(value <= -12.0f)
            value = 12.0f;
        else
        {
            //value = value - 0.1f;
            value = value - 1.0f;
        }
    }

    return value;
}

#endif

static D_Result
set_digit_timbre_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_DIGIT_TIMBRE_BUTTON_1:
            digit_timbre_data->user_50 = set_digit_timbre_value(digit_timbre_data->user_50, flag);
            sprintf(digit_timbre_data->user_50_buf, "%.1f", digit_timbre_data->user_50);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_1);
            {
                d_label_set_text(vis, digit_timbre_data->user_50_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_2:
            digit_timbre_data->user_75 = set_digit_timbre_value(digit_timbre_data->user_75, flag);
            sprintf(digit_timbre_data->user_75_buf, "%.1f", digit_timbre_data->user_75);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_2);
            {
                d_label_set_text(vis, digit_timbre_data->user_75_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_3:
            digit_timbre_data->user_100 = set_digit_timbre_value(digit_timbre_data->user_100, flag);
            sprintf(digit_timbre_data->user_100_buf, "%.1f", digit_timbre_data->user_100);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_3);
            {
                d_label_set_text(vis, digit_timbre_data->user_100_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_4:
            digit_timbre_data->user_300 = set_digit_timbre_value(digit_timbre_data->user_300, flag);
            sprintf(digit_timbre_data->user_300_buf, "%.1f", digit_timbre_data->user_300);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_4);
            {
                d_label_set_text(vis, digit_timbre_data->user_300_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_5:
            digit_timbre_data->user_1k = set_digit_timbre_value(digit_timbre_data->user_1k, flag);
            sprintf(digit_timbre_data->user_1k_buf, "%.1f", digit_timbre_data->user_1k);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_5);
            {
                d_label_set_text(vis, digit_timbre_data->user_1k_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_6:
            digit_timbre_data->user_3k = set_digit_timbre_value(digit_timbre_data->user_3k, flag);
            sprintf(digit_timbre_data->user_3k_buf, "%.1f", digit_timbre_data->user_3k);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_6);
            {
                d_label_set_text(vis, digit_timbre_data->user_3k_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_7:
            digit_timbre_data->user_5k = set_digit_timbre_value(digit_timbre_data->user_5k, flag);
            sprintf(digit_timbre_data->user_5k_buf, "%.1f", digit_timbre_data->user_5k);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_7);
            {
                d_label_set_text(vis, digit_timbre_data->user_5k_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_8:
            digit_timbre_data->user_10k = set_digit_timbre_value(digit_timbre_data->user_10k, flag);
            sprintf(digit_timbre_data->user_10k_buf, "%.1f", digit_timbre_data->user_10k);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_8);
            {
                d_label_set_text(vis, digit_timbre_data->user_10k_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_9:
            digit_timbre_data->user_15k = set_digit_timbre_value(digit_timbre_data->user_15k, flag);
            sprintf(digit_timbre_data->user_15k_buf, "%.1f", digit_timbre_data->user_15k);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_9);
            {
                d_label_set_text(vis, digit_timbre_data->user_15k_buf);
            }
            break;
        case ID_DIGIT_TIMBRE_BUTTON_10:
            if(flag)
            {
#ifdef D_TV_IAMGE_SOURCE
                if(digit_timbre_data->nfft == 2048)
#else
               if(digit_timbre_data->nfft == 1024)
#endif
                    digit_timbre_data->nfft = 64;
                else
                    digit_timbre_data->nfft  = digit_timbre_data->nfft * 2;
            }
            else
            {
                if(digit_timbre_data->nfft == 64)
#ifdef D_TV_IAMGE_SOURCE
                    digit_timbre_data->nfft = 2048;
#else
                    digit_timbre_data->nfft = 1024;
#endif
                else
                    digit_timbre_data->nfft  = digit_timbre_data->nfft / 2;
            }
            sprintf(digit_timbre_data->nfft_buf, "%d", digit_timbre_data->nfft);

            vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_10);
            d_label_set_text(vis, digit_timbre_data->nfft_buf);
            break;

        default:
            break;
    }
    set_param_of_digit_timbre();

    return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_9);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_10);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_digit_timbre_data(id, D_TRUE);
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
get_set_of_digit_timbre(void) D_FUNCPOSTFIT
{
    p_tvconf_get_cur_t_ffft(&digit_timbre_data->nfft, p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode);


    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[0], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 0);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[1], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 1);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[2], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 2);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[3], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 3);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[4], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 4);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[5], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 5);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[6], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 6);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[7], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 7);
    p_tvconf_get_audio_peq_set_param(&digit_timbre_data->param[8], p_vip_get_dbinput(digit_timbre_data->input), digit_timbre_data->mode, 8);

    digit_timbre_data->user_50 =  digit_timbre_data->param[0].gain;
    digit_timbre_data->user_75 = digit_timbre_data->param[1].gain;
    digit_timbre_data->user_100 = digit_timbre_data->param[2].gain;
    digit_timbre_data->user_300 = digit_timbre_data->param[3].gain; 
    digit_timbre_data->user_1k = digit_timbre_data->param[4].gain;
    digit_timbre_data->user_3k = digit_timbre_data->param[5].gain;
    digit_timbre_data->user_5k = digit_timbre_data->param[6].gain;
    digit_timbre_data->user_10k = digit_timbre_data->param[7].gain;
    digit_timbre_data->user_15k = digit_timbre_data->param[8].gain;

    sprintf(digit_timbre_data->user_50_buf, "%.1f", digit_timbre_data->user_50);
    sprintf(digit_timbre_data->user_75_buf, "%.1f", digit_timbre_data->user_75);
    sprintf(digit_timbre_data->user_100_buf, "%.1f", digit_timbre_data->user_100);
    sprintf(digit_timbre_data->user_300_buf, "%.1f", digit_timbre_data->user_300);
    sprintf(digit_timbre_data->user_1k_buf, "%.1f", digit_timbre_data->user_1k);
    sprintf(digit_timbre_data->user_3k_buf, "%.1f", digit_timbre_data->user_3k);
    sprintf(digit_timbre_data->user_5k_buf, "%.1f", digit_timbre_data->user_5k);
    sprintf(digit_timbre_data->user_10k_buf, "%.1f", digit_timbre_data->user_10k);
    sprintf(digit_timbre_data->user_15k_buf, "%.1f", digit_timbre_data->user_15k);
    sprintf(digit_timbre_data->nfft_buf, "%d", digit_timbre_data->nfft);

    return D_OK;
}

static D_Result
digit_timbre_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis;
    D_ID i;

#ifdef D_TV_IAMGE_SOURCE
   digit_timbre_data->param[0].freq = 62;
    digit_timbre_data->param[1].freq = 125;
    digit_timbre_data->param[2].freq = 250;
    digit_timbre_data->param[3].freq = 500;
    digit_timbre_data->param[4].freq = 1000;
    digit_timbre_data->param[5].freq = 2000;
    digit_timbre_data->param[6].freq = 4000;
    digit_timbre_data->param[7].freq = 8000;
    digit_timbre_data->param[8].freq = 16000;

    digit_timbre_data->param[0].bw = 44;
    digit_timbre_data->param[1].bw = 90;
    digit_timbre_data->param[2].bw = 178;
    digit_timbre_data->param[3].bw = 357;
    digit_timbre_data->param[4].bw = 714;
    digit_timbre_data->param[5].bw = 1428;
    digit_timbre_data->param[6].bw = 2857;
    digit_timbre_data->param[7].bw = 5174;
    digit_timbre_data->param[8].bw = 11428;
#else
    digit_timbre_data->param[0].freq = 80;
    digit_timbre_data->param[1].freq = 350;
    digit_timbre_data->param[2].freq = 650;
    digit_timbre_data->param[3].freq = 1000;
    digit_timbre_data->param[4].freq = 2000;
    digit_timbre_data->param[5].freq = 4000;
    digit_timbre_data->param[6].freq = 6000;
    digit_timbre_data->param[7].freq = 8000;
    digit_timbre_data->param[8].freq = 12000;

    digit_timbre_data->param[0].bw = 60;
    digit_timbre_data->param[1].bw = 100;
    digit_timbre_data->param[2].bw = 200;
    digit_timbre_data->param[3].bw = 500;
    digit_timbre_data->param[4].bw = 800;
    digit_timbre_data->param[5].bw = 1000;
    digit_timbre_data->param[6].bw = 1400;
    digit_timbre_data->param[7].bw = 2000;
    digit_timbre_data->param[8].bw = 4000;

#endif
    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_1);

    sprintf(digit_timbre_data->button_1, "%.0f/%.0f", digit_timbre_data->param[0].freq, digit_timbre_data->param[0].bw);
    d_label_set_text(vis, digit_timbre_data->button_1);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_2);
    sprintf(digit_timbre_data->button_2, "%.0f/%.0f", digit_timbre_data->param[1].freq, digit_timbre_data->param[1].bw);
    d_label_set_text(vis, digit_timbre_data->button_2);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_3);
    sprintf(digit_timbre_data->button_3, "%.0f/%.0f", digit_timbre_data->param[2].freq, digit_timbre_data->param[2].bw);
    d_label_set_text(vis, digit_timbre_data->button_3);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_4);
    sprintf(digit_timbre_data->button_4, "%.0f/%.0f", digit_timbre_data->param[3].freq, digit_timbre_data->param[3].bw);
    d_label_set_text(vis, digit_timbre_data->button_4);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_5);
    sprintf(digit_timbre_data->button_5, "%.0f/%.0f", digit_timbre_data->param[4].freq, digit_timbre_data->param[4].bw);
    d_label_set_text(vis, digit_timbre_data->button_5);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_6);
    sprintf(digit_timbre_data->button_6, "%.0f/%.0f", digit_timbre_data->param[5].freq, digit_timbre_data->param[5].bw);
    d_label_set_text(vis, digit_timbre_data->button_6);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_7);
    sprintf(digit_timbre_data->button_7, "%.0f/%.0f", digit_timbre_data->param[6].freq, digit_timbre_data->param[6].bw);
    d_label_set_text(vis, digit_timbre_data->button_7);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_8);
    sprintf(digit_timbre_data->button_8, "%.0f/%.0f", digit_timbre_data->param[7].freq, digit_timbre_data->param[7].bw);
    d_label_set_text(vis, digit_timbre_data->button_8);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_9);
    sprintf(digit_timbre_data->button_9, "%.0f/%.0f", digit_timbre_data->param[8].freq, digit_timbre_data->param[8].bw);
    d_label_set_text(vis, digit_timbre_data->button_9);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_10);
    d_label_set_text(vis, "Nfft");

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_1);
    d_label_set_text(vis, digit_timbre_data->user_50_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_2);
    d_label_set_text(vis, digit_timbre_data->user_75_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_3);
    d_label_set_text(vis, digit_timbre_data->user_100_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_4);
    d_label_set_text(vis, digit_timbre_data->user_300_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_5);
    d_label_set_text(vis, digit_timbre_data->user_1k_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_6);
    d_label_set_text(vis, digit_timbre_data->user_3k_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_7);
    d_label_set_text(vis, digit_timbre_data->user_5k_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_8);
    d_label_set_text(vis, digit_timbre_data->user_10k_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_9);
    d_label_set_text(vis, digit_timbre_data->user_15k_buf);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_LABEL_10);
    d_label_set_text(vis, digit_timbre_data->nfft_buf);

    return D_OK;
}

static D_Result
digit_timbre_set_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &digit_timbre_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_1);
    d_vis_set_handler(vis, button_1_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_2);
    d_vis_set_handler(vis, button_2_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_3);
    d_vis_set_handler(vis, button_3_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_4);
    d_vis_set_handler(vis, button_4_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_5);
    d_vis_set_handler(vis, button_5_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_6);
    d_vis_set_handler(vis, button_6_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_7);
    d_vis_set_handler(vis, button_7_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_8);
    d_vis_set_handler(vis, button_8_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_9);
    d_vis_set_handler(vis, button_9_set_handler);

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_10);
    d_vis_set_handler(vis, button_10_set_handler);

    return D_OK;
}

static D_Result
digit_timbre_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &digit_timbre_window;
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
                    set_digit_timbre_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_digit_timbre_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                case D_KEY_BACK:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_digit_timbre();

            if(digit_timbre_data)
            {
                PROJECT_FREE(digit_timbre_data);
                digit_timbre_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
digit_timbre_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    digit_timbre_data = (D_DigitTimbreDate*)PROJECT_ALLOC(sizeof(D_DigitTimbreDate));
    if(!digit_timbre_data)
    {
        return D_ERR;
    }
    memset(digit_timbre_data, 0, sizeof(D_DigitTimbreDate));
    digit_timbre_data->input = p_conf_get_vid_input();

    p_tvconf_get_cur_audiomode(&digit_timbre_data->mode, p_vip_get_dbinput(digit_timbre_data->input));

    get_set_of_digit_timbre();
    digit_timbre_label_show();
    digit_timbre_set_vis_handler();

    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, digit_timbre_window_handler);
    }

    return D_OK;
}

/** @brief  DIGIT_TIMBRE菜单*/
D_Result
p_atv_digit_timbre_show (D_Bool flag) D_FUNCPOSTFIT
{
    mode_flag = flag;
    return d_gui_enter_menu (&digit_timbre_window, D_FALSE);
}

