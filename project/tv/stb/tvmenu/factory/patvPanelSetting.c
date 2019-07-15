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
#include "ppanel.h"
#include "ppanelset.h"
#include "panel_setting_window.c"

#define BIT_MODE_STEP 6

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_U8  rp;
    D_U8  model;
    D_U8  TiMode, BitMode, SwapMode, DualPort, PanelSwingDa, PanelSwingClk;
    D_U16 Mirror;
    D_Char PanelSwingBufDa[5];
    D_Char PanelSwingBufClk[5];
} D_PanelSettingDate;
static D_PanelSettingDate *panel_setting_data;

static D_Char* rp_param[5] = {"无效", "1024x600", "1280x800", "1366x768", "1920x1080"};
static D_Char* model_param[5][8] =
{
    {"无效", "", "", "", "", "", "", ""},//无效
    {"BOE_32_768P_50", "", "", "", "", "", "", ""},//1024x600
    {"PB082WX1-100", "", "", "", "", "", "", ""},//1280x800
    {"BOE_32_768P_50", "BOE_32_768P_60", "LC390TU1A", "TLB315DF39-09", "LM185WH1_768P_50", "v320BJ6-q01", "", ""},//1366x768
    {"BOE_40_1080P_50", "BOE_40_1080P_60", "SANYO_46_1080P_50", "SANYO_46_1080P_60", "M236HGE-L20", "HV320FHB-N00", "LSC320HN05", ""},//1920x1080
};
static D_Char* TiMode_param[2] = {"JEDIA", "VESA"};
static D_Char* BitMode_param[3] = {"6 BIT", "7 BIT", "8 BIT"};
static D_Char* SwapMode_param[2] = {"no exchange", "exchange"};
static D_Char* DualPort_param[2] = {"signal channel", "dual channel"};
static D_Char* mirror_param[4] = {"close", "h_invert", "v_invert", "hv_invert"};

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
save_param_of_panel(void) D_FUNCPOSTFIT
{
    D_PanelParam panel_param;
    D_PartPanelParam part_panel_param;
    p_conf_get_panel_param(&panel_param);
    if(panel_setting_data->rp != 0)
    {
        get_part_panel_param(&part_panel_param, panel_setting_data->rp, panel_setting_data->model);
        parse_partpanel_to_panel(&panel_param, &part_panel_param);
    }
    panel_param.spmodel_param.rp = panel_setting_data->rp;
    panel_param.spmodel_param.model = panel_setting_data->model;
    panel_param.lvds_init_param.lvds_foramt = panel_setting_data->TiMode;
    panel_param.lvds_init_param.lvds_exchange_mode = panel_setting_data->SwapMode;
    panel_param.lvds_init_param.lvds_channel_mode = panel_setting_data->DualPort;
    panel_param.lvds_init_param.lvds_da_tx_pds = panel_setting_data->PanelSwingDa;
    panel_param.lvds_init_param.lvds_clk_tx_pds = panel_setting_data->PanelSwingClk;
    panel_param.tven_para.display_invert = panel_setting_data->Mirror;

    p_conf_set_panel_param(&panel_param);
    return D_OK;
}

static D_Result
set_panel_setting_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis;
    D_LoaderParam loader_param;

    switch(id)
    {
        case ID_GENERAL_BUTTON_1:
            if(flag)
            {
                if(panel_setting_data->rp < 4)
                    panel_setting_data->rp++;
                else
                    panel_setting_data->rp = 0;
            }
            else
            {
                if(panel_setting_data->rp > 0)
                    panel_setting_data->rp--;
                else
                    panel_setting_data->rp = 4;
            }
            panel_setting_data->model = 0;
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_1);
            if(vis)
            {
                d_label_set_text(vis, rp_param[panel_setting_data->rp]);
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_2);
            if(vis)
            {
                d_label_set_text(vis, model_param[panel_setting_data->rp][panel_setting_data->model]);
            }
            break;
        case ID_GENERAL_BUTTON_2:
            switch(panel_setting_data->rp)
            {
                case 3:
                    if(flag)
                    {
                        if(panel_setting_data->model < 5)
                            panel_setting_data->model++;
                        else
                            panel_setting_data->model = 0;
                    }
                    else
                    {
                        if(panel_setting_data->model > 0)
                            panel_setting_data->model--;
                        else
                            panel_setting_data->model = 5;
                    }
                    break;
                case 4:
                    if(flag)
                    {
                        if(panel_setting_data->model < 6)
                            panel_setting_data->model++;
                        else
                            panel_setting_data->model = 0;
                    }
                    else
                    {
                        if(panel_setting_data->model > 0)
                            panel_setting_data->model--;
                        else
                            panel_setting_data->model = 6;
                    }
                    break;
                default:
                    break;
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_2);
            if(vis)
            {
                d_label_set_text(vis, model_param[panel_setting_data->rp][panel_setting_data->model]);
            }
            //p_tvconf_set_logomode (&panel_setting_data->logo_mode);
            break;
        case ID_GENERAL_BUTTON_3:
        {
            panel_setting_data->TiMode = !panel_setting_data->TiMode;
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_3);
            if(vis)
            {
                d_label_set_text(vis, TiMode_param[panel_setting_data->TiMode]);
            }
            d_panel_Set_map(panel_setting_data->TiMode);
        }
        break;
        case ID_GENERAL_BUTTON_4:
        {
            if(flag)
            {
                if(panel_setting_data->BitMode < 8)
                    panel_setting_data->BitMode++;
                else
                    panel_setting_data->BitMode = 6;
            }
            else
            {
                if(panel_setting_data->BitMode > 6)
                    panel_setting_data->BitMode--;
                else
                    panel_setting_data->BitMode = 8;
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_4);
            if(vis)
            {
                d_label_set_text(vis, BitMode_param[panel_setting_data->BitMode - BIT_MODE_STEP]);
            }
        }
        break;
        case ID_GENERAL_BUTTON_5:
        {
            panel_setting_data->SwapMode = !panel_setting_data->SwapMode;
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_5);
            if(vis)
            {
                d_label_set_text(vis, SwapMode_param[panel_setting_data->SwapMode]);
            }
            d_panel_Set_exchange(panel_setting_data->SwapMode);
        }
        break;
        case ID_GENERAL_BUTTON_6:
        {
            panel_setting_data->DualPort = !panel_setting_data->DualPort;
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_6);
            if(vis)
            {
                d_label_set_text(vis, DualPort_param[panel_setting_data->DualPort]);
            }
            d_panel_Set_split(panel_setting_data->DualPort);
        }
        break;
        case ID_GENERAL_BUTTON_7:
        {
            if(flag)
            {
                if(panel_setting_data->PanelSwingDa < 7)
                    panel_setting_data->PanelSwingDa++;
                else
                    panel_setting_data->PanelSwingDa = 0;
            }
            else
            {
                if(panel_setting_data->PanelSwingDa > 0)
                    panel_setting_data->PanelSwingDa--;
                else
                    panel_setting_data->PanelSwingDa = 7;
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_7);
            if(vis)
            {
                sprintf(panel_setting_data->PanelSwingBufDa, "%d", panel_setting_data->PanelSwingDa);
                d_label_set_text(vis, panel_setting_data->PanelSwingBufDa);
            }
            d_panel_Set_LVDS_DA_CLK(panel_setting_data->PanelSwingDa, panel_setting_data->PanelSwingClk);
        }
        break;
        case ID_GENERAL_BUTTON_8:
        {
            if(flag)
            {
                if(panel_setting_data->PanelSwingClk < 7)
                    panel_setting_data->PanelSwingClk++;
                else
                    panel_setting_data->PanelSwingClk = 0;
            }
            else
            {
                if(panel_setting_data->PanelSwingClk > 0)
                    panel_setting_data->PanelSwingClk--;
                else
                    panel_setting_data->PanelSwingClk = 7;
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_8);
            if(vis)
            {
                sprintf(panel_setting_data->PanelSwingBufClk, "%d", panel_setting_data->PanelSwingClk);
                d_label_set_text(vis, panel_setting_data->PanelSwingBufClk);
            }
            d_panel_Set_LVDS_DA_CLK(panel_setting_data->PanelSwingDa, panel_setting_data->PanelSwingClk);
        }
        break;
        case ID_GENERAL_BUTTON_9:
        {
            if(flag)
            {
                if(panel_setting_data->Mirror < 3)
                    panel_setting_data->Mirror++;
                else
                    panel_setting_data->Mirror = 0;
            }
            else
            {
                if(panel_setting_data->Mirror > 0)
                    panel_setting_data->Mirror--;
                else
                    panel_setting_data->Mirror = 3;
            }
            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_9);
            if(vis)
            {
                d_label_set_text(vis, mirror_param[panel_setting_data->Mirror]);
            }
            d_av_display_invert(panel_setting_data->Mirror);
        }
        break;
        default:
            break;
    }

    return D_OK;
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
rp_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
model_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
TiMode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
BitMode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
SwapMode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
DualPort_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
PanelSwingDa_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_7);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
PanelSwingClk_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
Mirror_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_9);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_panel_setting_data(id, D_TRUE);
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
get_set_of_panel_setting(void) D_FUNCPOSTFIT
{
    D_PanelParam panel_param;
    p_conf_get_panel_param(&panel_param);
    panel_setting_data->rp = panel_param.spmodel_param.rp;
    panel_setting_data->model = panel_param.spmodel_param.model;
    panel_setting_data->TiMode = panel_param.lvds_init_param.lvds_foramt;
    panel_setting_data->BitMode = 8;//暂时放空,默认为8
    panel_setting_data->SwapMode = panel_param.lvds_init_param.lvds_exchange_mode;
    panel_setting_data->DualPort = panel_param.lvds_init_param.lvds_channel_mode;
    panel_setting_data->PanelSwingDa = panel_param.lvds_init_param.lvds_da_tx_pds;
    panel_setting_data->PanelSwingClk = panel_param.lvds_init_param.lvds_clk_tx_pds;
    panel_setting_data->Mirror = panel_param.tven_para.display_invert;
    return D_OK;
}

static D_Result
panel_setting_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_PANEL_LABEL_PANEL_SETTING);
    if(vis)
    {
        d_label_set_text(vis, "Panel");
    }

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_1);
    if(vis)
    {
        d_label_set_text(vis, "分辨率");
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_2);
    if(vis)
    {
        d_label_set_text(vis, "屏型号");
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_3);
    if(vis)
    {
        d_label_set_text(vis, "TiMode");
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_4);
    if(vis)
    {
        d_label_set_text(vis, "BitMode");
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_5);
    if(vis)
    {
        d_label_set_text(vis, "SwapMode");
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_6);
    if(vis)
    {
        d_label_set_text(vis, "DualPort");
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_7);
    if(vis)
    {
        d_label_set_text(vis, "Panel Swing Da");
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_8);
    if(vis)
    {
        d_label_set_text(vis, "Panel Swing Clk");
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_9);
    if(vis)
    {
        d_label_set_text(vis, "Mirror");
    }

    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_1);
    if(vis)
    {
        d_label_set_text(vis, rp_param[panel_setting_data->rp]);
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_2);
    if(vis)
    {
        d_label_set_text(vis, model_param[panel_setting_data->rp][panel_setting_data->model]);
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_3);
    if(vis)
    {
        d_label_set_text(vis, TiMode_param[panel_setting_data->TiMode]);
		set_label_focus_attribute(vis, D_TRUE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_4);
    if(vis)
    {
        d_label_set_text(vis, BitMode_param[panel_setting_data->BitMode - BIT_MODE_STEP]);
        d_vis_enable(vis, D_FALSE);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, SwapMode_param[panel_setting_data->SwapMode]);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_6);
    if(vis)
    {
        d_label_set_text(vis, DualPort_param[panel_setting_data->DualPort]);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_7);
    if(vis)
    {
        sprintf(panel_setting_data->PanelSwingBufDa, "%d", panel_setting_data->PanelSwingDa);
        d_label_set_text(vis, panel_setting_data->PanelSwingBufDa);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_8);
    if(vis)
    {
        sprintf(panel_setting_data->PanelSwingBufClk, "%d", panel_setting_data->PanelSwingClk);
        d_label_set_text(vis, panel_setting_data->PanelSwingBufClk);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_9);
    if(vis)
    {
        d_label_set_text(vis, mirror_param[panel_setting_data->Mirror]);
    }

    return D_OK;
}

static D_Result
panel_setting_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &panel_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_1);
    if(vis)
    {
        d_vis_set_handler(vis, rp_handler);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_2);
    if(vis)
    {
        d_vis_set_handler(vis, model_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_3);
    if(vis)
    {
        d_vis_set_handler(vis, TiMode_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_4);
    if(vis)
    {
        d_vis_set_handler(vis, BitMode_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_5);
    if(vis)
    {
        d_vis_set_handler(vis, SwapMode_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_6);
    if(vis)
    {
        d_vis_set_handler(vis, DualPort_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_7);
    if(vis)
    {
        d_vis_set_handler(vis, PanelSwingDa_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_8);
    if(vis)
    {
        d_vis_set_handler(vis, PanelSwingClk_handler);
    }
    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_9);
    if(vis)
    {
        d_vis_set_handler(vis, Mirror_handler);
    }

    return D_OK;
}

static D_Result
panel_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &panel_setting_window;
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
                    set_panel_setting_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_panel_setting_data(id, D_FALSE);
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
            save_param_of_panel();
            if(panel_setting_data)
            {
                PROJECT_FREE(panel_setting_data);
                panel_setting_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
panel_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    panel_setting_data = (D_PanelSettingDate*)PROJECT_ALLOC(sizeof(D_PanelSettingDate));
    if(!panel_setting_data)
    {
        return D_ERR;
    }
    memset(panel_setting_data, 0, sizeof(D_PanelSettingDate));

    get_set_of_panel_setting();
    panel_setting_label_show();
    panel_setting_vis_handler();

    vis = d_frame_get_control(frm, ID_GENERAL_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, panel_setting_window_handler);
    }

    return D_OK;
}

/** @brief 通用设置菜单*/
D_Result
p_atv_panel_setting_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&panel_setting_window, D_TRUE);
}

