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
#include "setting_window.c"


#define BUF_LINE 4

typedef enum
{
    CONTRAST,
    BRIGHTNESS,
    SATURATION,
    SHARPNESS,
    HUE
} PICTURE;


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 video_mode;
    D_VidInput input;
	D_U8 hdflag;
    D_PMODE_SET tparam;
    D_PCURVE_SET param;

    D_S16 osd_0, osd_1, osd_25, osd_50, osd_75, osd_100;

    D_Char osd_0_buf[BUF_LINE];
    D_Char osd_1_buf[BUF_LINE];
    D_Char osd_25_buf[BUF_LINE];
    D_Char osd_50_buf[BUF_LINE];
    D_Char osd_75_buf[BUF_LINE];
    D_Char osd_100_buf[BUF_LINE];
} D_SettingDate;

static D_S16 pic_set;
static D_SettingDate *setting_data;
static D_Result set_set_of_setting(void) D_FUNCPOSTFIT;

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
set_setting_value(D_S16 value, D_Bool flag)
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

static D_S16
set_setting_value1(D_S16 value, D_Bool flag)
{
    if(flag)
    {
        if(value == 63)
            value = 0;
        else
            value ++;
    }
    else
    {
        if(value == 0)
            value = 63;
        else
            value --;
    }

    return value;
}

static D_Result
set_setting_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_SETTING_BUTTON_1:
			if(pic_set == HUE)
			{
				setting_data->osd_0 = set_setting_value1(setting_data->osd_0, flag);
			}
			else
			{
            	setting_data->osd_0 = set_setting_value(setting_data->osd_0, flag);
			}
            vis = d_frame_get_control(frm, ID_SETTING_LABEL_1);
            {
                sprintf(setting_data->osd_0_buf, "%d", setting_data->osd_0);
                d_label_set_text(vis, setting_data->osd_0_buf);
            }
            break;
        case ID_SETTING_BUTTON_2:
			if(pic_set == HUE)
			{
            	setting_data->osd_1 = set_setting_value1(setting_data->osd_1, flag);
			}
			else
			{
            	setting_data->osd_1 = set_setting_value(setting_data->osd_1, flag);
			}

            vis = d_frame_get_control(frm, ID_SETTING_LABEL_2);
            {
                sprintf(setting_data->osd_1_buf, "%d", setting_data->osd_1);
                d_label_set_text(vis, setting_data->osd_1_buf);
            }
            break;
        case ID_SETTING_BUTTON_3:
			if(pic_set == HUE)
			{
            	setting_data->osd_25 = set_setting_value1(setting_data->osd_25, flag);
			}
			else
			{
            	setting_data->osd_25 = set_setting_value(setting_data->osd_25, flag);
			}
            vis = d_frame_get_control(frm, ID_SETTING_LABEL_3);
            {
                sprintf(setting_data->osd_25_buf, "%d", setting_data->osd_25);
                d_label_set_text(vis, setting_data->osd_25_buf);
            }
            break;
        case ID_SETTING_BUTTON_4:
			if(pic_set == HUE)
			{
            	setting_data->osd_50 = set_setting_value1(setting_data->osd_50, flag);
			}
			else
			{
            	setting_data->osd_50 = set_setting_value(setting_data->osd_50, flag);
			}

            vis = d_frame_get_control(frm, ID_SETTING_LABEL_4);
            {
                sprintf(setting_data->osd_50_buf, "%d", setting_data->osd_50);
                d_label_set_text(vis, setting_data->osd_50_buf);
            }
            break;
        case ID_SETTING_BUTTON_5:
			if(pic_set == HUE)
			{
            	setting_data->osd_75 = set_setting_value1(setting_data->osd_75, flag);
			}
			else
			{
            	setting_data->osd_75 = set_setting_value(setting_data->osd_75, flag);
			}

            vis = d_frame_get_control(frm, ID_SETTING_LABEL_5);
            {
                sprintf(setting_data->osd_75_buf, "%d", setting_data->osd_75);
                d_label_set_text(vis, setting_data->osd_75_buf);
            }
            break;
        case ID_SETTING_BUTTON_6:
			if(pic_set == HUE)
			{
            	setting_data->osd_100 = set_setting_value1(setting_data->osd_100, flag);
			}
			else
			{
            	setting_data->osd_100 = set_setting_value(setting_data->osd_100, flag);
			}

            vis = d_frame_get_control(frm, ID_SETTING_LABEL_6);
            {
                sprintf(setting_data->osd_100_buf, "%d", setting_data->osd_100);
                d_label_set_text(vis, setting_data->osd_100_buf);
            }
            break;
        default:
            break;
    }
    set_set_of_setting();

    return D_OK;
}

static D_Result
osd_0_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
osd_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
osd_25_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
osd_50_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
osd_75_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
osd_100_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SETTING_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_setting_data(id, D_TRUE);
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
get_set_of_setting(void) D_FUNCPOSTFIT
{
    if(pic_set == CONTRAST)
    {
    	if(setting_data->hdflag)
	    {
	        p_tvconf_get_hdpcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 1);
	    }
	    else
	    {
	        p_tvconf_get_pcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 1);
	    }
    }
    else if(pic_set == BRIGHTNESS)
    {
        if(setting_data->hdflag)
	    {
	        p_tvconf_get_hdpcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 0);
	    }
	    else
	    {
	        p_tvconf_get_pcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 0);
	    }
    }
    else if(pic_set == SATURATION)
    {
        if(setting_data->hdflag)
	    {
	        p_tvconf_get_hdpcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 2);
	    }
	    else
	    {
	        p_tvconf_get_pcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 2);
	    }
    }
    else if(pic_set == SHARPNESS)
    {
        if(setting_data->hdflag)
	    {
	        p_tvconf_get_hdpcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 4);
	    }
	    else
	    {
	        p_tvconf_get_pcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 4);
	    }
    }
    else if(pic_set == HUE)
    {
        if(setting_data->hdflag)
	    {
	        p_tvconf_get_hdpcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 3);
	    }
	    else
	    {
	        p_tvconf_get_pcurve_param(&setting_data->param, p_vip_get_dbinput(setting_data->input), 3);
	    }
    }

	setting_data->osd_0 = setting_data->param.osd_0;
    setting_data->osd_1 = setting_data->param.osd_1;
    setting_data->osd_25 = setting_data->param.osd_25;
    setting_data->osd_50 = setting_data->param.osd_50;
    setting_data->osd_75 = setting_data->param.osd_75;
    setting_data->osd_100 = setting_data->param.osd_100;
	
    sprintf(setting_data->osd_0_buf, "%d", setting_data->osd_0);
    sprintf(setting_data->osd_1_buf, "%d", setting_data->osd_1);
    sprintf(setting_data->osd_25_buf, "%d", setting_data->osd_25);
    sprintf(setting_data->osd_50_buf, "%d", setting_data->osd_50);
    sprintf(setting_data->osd_75_buf, "%d", setting_data->osd_75);
    sprintf(setting_data->osd_100_buf, "%d", setting_data->osd_100);

    return D_OK;
}
static D_Result
set_set_of_setting(void) D_FUNCPOSTFIT
{
    setting_data->param.osd_0 = setting_data->osd_0;
    setting_data->param.osd_1 = setting_data->osd_1;
    setting_data->param.osd_25 = setting_data->osd_25;
    setting_data->param.osd_50 = setting_data->osd_50;
    setting_data->param.osd_75 = setting_data->osd_75;
    setting_data->param.osd_100 = setting_data->osd_100;

    if(pic_set == CONTRAST)
    {
        d_vip_setConstrast(setting_data->tparam.contrast, (D_U8*)&setting_data->param);
    }
    else if(pic_set == BRIGHTNESS)
    {
        d_vip_setBrightness(setting_data->tparam.brightness, (D_U8*)&setting_data->param);

    }
    else if(pic_set == SATURATION)
    {
        d_vip_setSaturation(setting_data->tparam.color, (D_U8*)&setting_data->param);

    }
    else if(pic_set == SHARPNESS)
    {
        d_vip_setSharpness(setting_data->tparam.sharpness, (D_U8*)&setting_data->param);
    }
    else if(pic_set == HUE)
    {
        //tint

    }

    return D_OK;
}
static D_Result
save_set_of_setting(void) D_FUNCPOSTFIT
{
    setting_data->param.osd_0 = setting_data->osd_0;
    setting_data->param.osd_1 = setting_data->osd_1;
    setting_data->param.osd_25 = setting_data->osd_25;
    setting_data->param.osd_50 = setting_data->osd_50;
    setting_data->param.osd_75 = setting_data->osd_75;
    setting_data->param.osd_100 = setting_data->osd_100;


    if(pic_set == CONTRAST)
    {
    	if(setting_data->hdflag)
	    {
        p_tvconf_set_hdpcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 1);
	    }
	    else
	    {
        	p_tvconf_set_pcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 1);
	    }
    }
    else if(pic_set == BRIGHTNESS)
    {
        if(setting_data->hdflag)
	    {
        	p_tvconf_set_hdpcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 0);
	    }
	    else
	    {
        	p_tvconf_set_pcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 0);
	    }
    }
    else if(pic_set == SATURATION)
    {
        if(setting_data->hdflag)
	    {
        	p_tvconf_set_hdpcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 2);
	    }
	    else
	    {
        	p_tvconf_set_pcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 2);
	    }
    }
    else if(pic_set == SHARPNESS)
    {
        if(setting_data->hdflag)
	    {
        	p_tvconf_set_hdpcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 4);
	    }
	    else
	    {
        	p_tvconf_set_pcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 4);
	    }
    }
    else if(pic_set == HUE)
    {
        if(setting_data->hdflag)
	    {
        	p_tvconf_set_hdpcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 3);
	    }
	    else
	    {
        	p_tvconf_set_pcurve_param  (&setting_data->param, p_vip_get_dbinput(setting_data->input), 3);
	    }
    }

    return D_OK;
}

static D_Result
setting_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_1);
    d_label_set_text(vis, "OSD_0");
    d_vis_set_handler(vis, osd_0_set_handler);

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_2);
    d_label_set_text(vis, "OSD_1");
    d_vis_set_handler(vis, osd_1_set_handler);

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_3);
    d_label_set_text(vis, "OSD_25");
    d_vis_set_handler(vis, osd_25_handler);

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_4);
    d_label_set_text(vis, "OSD_50");
    d_vis_set_handler(vis, osd_50_handler);

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_5);
    d_label_set_text(vis, "OSD_75");
    d_vis_set_handler(vis, osd_75_handler);

    vis = d_frame_get_control(frm, ID_SETTING_BUTTON_6);
    d_label_set_text(vis, "OSD_100");
    d_vis_set_handler(vis, osd_100_handler);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_SETTING);
    if(pic_set == CONTRAST)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_CONTRAST));
    }
    else if(pic_set == BRIGHTNESS)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_BRIGHTNESS));
    }
    else if(pic_set == SATURATION)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_SATURATION));
    }
    else if(pic_set == SHARPNESS)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_SHARPNESS));
    }
    else if(pic_set == HUE)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_TINT));
    }

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_1);
    d_label_set_text(vis, setting_data->osd_0_buf);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_2);
    d_label_set_text(vis, setting_data->osd_1_buf);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_3);
    d_label_set_text(vis, setting_data->osd_25_buf);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_4);
    d_label_set_text(vis, setting_data->osd_50_buf);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_5);
    d_label_set_text(vis, setting_data->osd_75_buf);

    vis = d_frame_get_control(frm, ID_SETTING_LABEL_6);
    d_label_set_text(vis, setting_data->osd_100_buf);

    return D_OK;
}


static D_Result
setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &setting_window;
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

                    set_setting_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_setting_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            save_set_of_setting();
            d_vis_unsubscribe_evt (vis);
            if(setting_data)
            {
                PROJECT_FREE(setting_data);
                setting_data = NULL;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    setting_data = (D_SettingDate*)PROJECT_ALLOC(sizeof(D_SettingDate));
    if(!setting_data)
    {
        return D_ERR;
    }
    memset(setting_data, 0, sizeof(D_SettingDate));
    setting_data->input = p_conf_get_vid_input();
	if(setting_data->input == D_VID_IUTPUT_AV1 || setting_data->input == D_VID_IUTPUT_AV2|| setting_data->input == D_VID_IUTPUT_TV)
	{
		setting_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		setting_data->hdflag = p_vip_get_hdflag();
	}
    p_tvconf_get_cur_imagemode(&setting_data->video_mode, p_vip_get_dbinput(setting_data->input));

    if(p_tvconf_get_pmodeset_param(&setting_data->tparam, p_vip_get_dbinput(setting_data->input), setting_data->video_mode) == D_OK)
    {
        D_DUMP("p_tvconf_get_pmodeset_param ok\n");
    }

    get_set_of_setting();
    setting_vis_set();

    vis = d_frame_get_control(frm, ID_SETTING_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, setting_window_handler);
    }

    return D_OK;
}

/** @brief  图像调整菜单*/
D_Result
p_atv_setting_show (D_S16 flag) D_FUNCPOSTFIT
{
    pic_set = flag;
    return d_gui_enter_menu (&setting_window, D_TRUE);
}

