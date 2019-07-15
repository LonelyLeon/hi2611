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
#include "set_register_window.c"

#define BUF_LINE 40

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_U32 address, value, new_value;
    D_Char title_buf[36];
    D_Char address_buf[BUF_LINE];
    D_Char value_buf[BUF_LINE];
    D_Char new_value_buf[BUF_LINE];
} D_SerRegisterDate;

static D_SerRegisterDate *set_register_data;
static D_U32 base_addr = 0;

/** @brief HDMI输入模式结束*/
extern D_U8 hrvip_test_getreg(D_U32 baseaddr,D_U8 addr);

/** @brief HDMI输入模式结束*/
extern void hrvip_test_setreg(D_U32 baseaddr,D_U16 addr,D_U8 val);

/** @brief HDMI输入模式结束*/
extern void HRHdmi_test_init(D_U8 val);
extern	D_U32 getPixYUV_avg(D_U16 x, D_U16 y);
extern D_U16 H_D_VIP_Get_GAMMA_Table(D_U8 nChannel, D_U8 addr);
extern void  H_D_VIP_Set_GAMMA_Table(D_U8 nChannel, D_U8 addr, D_U16 val);

void hraudio_test_setreg(D_U32 val);
D_U32 hraudio_test_getreg(void);


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
set_of_register_setting(void) D_FUNCPOSTFIT
{
	if(base_addr == 0xffffffff)
	{
		set_register_data->value = getPixYUV_avg(set_register_data->new_value,set_register_data->address);
	}
	else if(base_addr == 0xfffffff0)
	{
		//H_D_VIP_Set_GAMMA_Table(1, set_register_data->address,set_register_data->new_value);
		set_register_data->value = set_register_data->new_value;
	}
	else if(base_addr == 0xffffff00)
	{
		//hraudio_test_setreg(set_register_data->new_value);
		set_register_data->value = set_register_data->new_value;
	}	
	else
	{
		//hrvip_test_setreg(base_addr,set_register_data->address,set_register_data->new_value);
	}		
	return D_OK;
}

static D_Result
save_of_register_setting(void) D_FUNCPOSTFIT
{
	
    return D_OK;
}

static D_Result
get_set_of_register_setting(void) D_FUNCPOSTFIT
{
	set_register_data->address = 000;
	set_register_data->new_value= 0;
	if(base_addr == 0xffffffff)
	{
	    sprintf(set_register_data->address_buf, "%03d", set_register_data->address);

		set_register_data->value = getPixYUV_avg(set_register_data->new_value,set_register_data->address);
	    sprintf(set_register_data->value_buf, "0x%08x", set_register_data->value);	

	    sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);

	}
	else if(base_addr == 0xfffffff0)
	{
	    sprintf(set_register_data->address_buf, "%03d", set_register_data->address);
		//set_register_data->value = H_D_VIP_Get_GAMMA_Table(1, set_register_data->address);
	    sprintf(set_register_data->value_buf, "%04d", set_register_data->value);	
		set_register_data->new_value = set_register_data->value;
	    sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);

	}
	else if(base_addr == 0xffffff00)
	{
	    sprintf(set_register_data->address_buf, "%03d", set_register_data->address);
		//set_register_data->value = hraudio_test_getreg();
	    sprintf(set_register_data->value_buf, "%04d", set_register_data->value);	
		set_register_data->new_value = set_register_data->value;
	    sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);

	}	
	else
	{
		//set_register_data->value = hrvip_test_getreg(base_addr,set_register_data->address );
		//set_register_data->new_value = hrvip_test_getreg(base_addr,set_register_data->address );
    	sprintf(set_register_data->value_buf, "%03d", set_register_data->value);
	    sprintf(set_register_data->address_buf, "%03d", set_register_data->address);
	    sprintf(set_register_data->new_value_buf, "%03d", set_register_data->new_value);

	}

    return D_OK;
}

static D_Result
resigter_input_3_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_register_window;
    D_Visual *vis_label, *vis_show;

    vis_label = d_frame_get_control(frm, ID_REGISTER_LABEL_3);
    vis_show = d_frame_get_control(frm, ID_REGISTER_LABEL_SHOW_VALUE);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
			set_register_data->new_value = (D_S16)d_input_box_get_num(vis);
        	set_of_register_setting();
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
resigter_input_1_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_register_window;
    D_Visual *vis_label, *vis_show, *vis_new_value;

    vis_label = d_frame_get_control(frm, ID_REGISTER_LABEL_1);
    vis_show = d_frame_get_control(frm, ID_REGISTER_LABEL_SHOW_VALUE);
	vis_new_value = d_frame_get_control(frm, ID_REGISTER_INPUT_3);
	

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_DATA_CHANGED:
        	set_register_data->address = (D_S16)d_input_box_get_num(vis);
			if(base_addr == 0xffffffff)
			{
	        	sprintf(set_register_data->address_buf, "%03d", set_register_data->address);

				set_register_data->value = getPixYUV_avg(set_register_data->new_value,set_register_data->address);
			    sprintf(set_register_data->value_buf, "0x%08x", set_register_data->value);	
	        	d_label_set_text(vis_show, set_register_data->value_buf);

	    		sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);	        	
				d_input_box_set_text(vis_new_value,set_register_data->new_value_buf,4);
			}
			else if(base_addr == 0xfffffff0)
			{
	        	sprintf(set_register_data->address_buf, "%03d", set_register_data->address);

				//set_register_data->value = H_D_VIP_Get_GAMMA_Table(1, set_register_data->address);
			    sprintf(set_register_data->value_buf, "%4d", set_register_data->value);	
				set_register_data->new_value = set_register_data->value;

	    		sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);
	        	
	        	d_label_set_text(vis_show, set_register_data->value_buf);
				d_input_box_set_text(vis_new_value,set_register_data->new_value_buf,4);

			}
			else if(base_addr == 0xffffff00)
			{
	        	sprintf(set_register_data->address_buf, "%03d", set_register_data->address);

				//set_register_data->value = hraudio_test_getreg();
			    sprintf(set_register_data->value_buf, "%4d", set_register_data->value);	
				set_register_data->new_value = set_register_data->value;

	    		sprintf(set_register_data->new_value_buf, "%04d", set_register_data->new_value);
	        	
	        	d_label_set_text(vis_show, set_register_data->value_buf);
				d_input_box_set_text(vis_new_value,set_register_data->new_value_buf,4);
			}			
			else
			{
				//set_register_data->value = hrvip_test_getreg(base_addr,set_register_data->address );
				//set_register_data->new_value = hrvip_test_getreg(base_addr,set_register_data->address );
		    	sprintf(set_register_data->value_buf, "%03d", set_register_data->value);

	    		sprintf(set_register_data->new_value_buf, "%03d", set_register_data->new_value);
	        	sprintf(set_register_data->address_buf, "%03d", set_register_data->address);
	        	
	        	d_label_set_text(vis_show, set_register_data->value_buf);
				d_input_box_set_text(vis_new_value,set_register_data->new_value_buf,3);

			}			
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
set_register_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_register_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_REGISTER_LABEL_REGISTER);
    if(vis)
    {
    	sprintf(set_register_data->title_buf, "0x%x", base_addr);
		d_label_set_text(vis, set_register_data->title_buf);
    }
	
    vis = d_frame_get_control(frm, ID_REGISTER_LABEL_2);
    if(vis)
    {
        d_label_set_text(vis, "Value");
    }

     vis = d_frame_get_control(frm, ID_REGISTER_LABEL_SHOW_VALUE);
    if(vis)
    {
        d_label_set_text(vis, set_register_data->value_buf);
    }

    vis = d_frame_get_control(frm, ID_REGISTER_LABEL_3);
    if(vis)
    {
        d_label_set_text(vis, "Input New Value");
    }

    vis = d_frame_get_control(frm, ID_REGISTER_LABEL_1);
    if(vis)
    {
    	d_label_set_text(vis, "Input Address");
        
    }
    return D_OK;
}

static D_Result
set_register_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_register_window;
    D_Visual *vis;
	
    vis = d_frame_get_control(frm, ID_REGISTER_INPUT_1);
    if(vis)
    {
        d_input_box_set_text(vis, set_register_data->address_buf,3);
		d_vis_set_handler(vis, resigter_input_1_handler);
    }

    vis = d_frame_get_control(frm, ID_REGISTER_INPUT_3);
    if(vis)
    {
        d_input_box_set_text(vis,set_register_data->new_value_buf,4);
        d_vis_set_handler(vis, resigter_input_3_handler);
    }

    return D_OK;
}

static D_Result
set_register_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &set_register_window;
	D_Visual *vis_show, *vis_input_3;
	
    vis_show = d_frame_get_control(frm, ID_REGISTER_LABEL_SHOW_VALUE);
	vis_input_3 = d_frame_get_control(frm, ID_REGISTER_INPUT_3);
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_MENU:
                case D_KEY_BACK:
                    return d_gui_upper_menu();
				case D_KEY_OK:
					if(base_addr == 0xffffffff)
					{
						set_register_data->new_value = (D_S16)d_input_box_get_num(vis_input_3);
	        			set_of_register_setting();
						sprintf(set_register_data->value_buf, "0x%08x", set_register_data->value);
						d_label_set_text(vis_show, set_register_data->value_buf);

					}
					else if(base_addr == 0xfffffff0)
					{
						set_register_data->new_value = (D_S16)d_input_box_get_num(vis_input_3);
	        			set_of_register_setting();
						sprintf(set_register_data->value_buf, "%04d", set_register_data->new_value);
						d_label_set_text(vis_show, set_register_data->value_buf);
					}
					else if(base_addr == 0xffffff00)
					{
						set_register_data->new_value = (D_S16)d_input_box_get_num(vis_input_3);
	        			set_of_register_setting();
						sprintf(set_register_data->value_buf, "%04d", set_register_data->new_value);
						d_label_set_text(vis_show, set_register_data->value_buf);
					}					
					else
					{
						set_register_data->new_value = (D_S16)d_input_box_get_num(vis_input_3);
	        			set_of_register_setting();
						sprintf(set_register_data->value_buf, "%03d", set_register_data->new_value);
						d_label_set_text(vis_show, set_register_data->value_buf);
					}					
					break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
	//		HRHdmi_test_init(0);
            d_vis_unsubscribe_evt (vis);
            save_of_register_setting();
            if(set_register_data)
            {
                PROJECT_FREE(set_register_data);
                set_register_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
set_register_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    set_register_data = (D_SerRegisterDate*)PROJECT_ALLOC(sizeof(D_SerRegisterDate));
    if(!set_register_data)
    {
        return D_ERR;
    }
    memset(set_register_data, 0, sizeof(D_SerRegisterDate));
//	HRHdmi_test_init(1);

    get_set_of_register_setting();
    set_register_label_show();
    set_register_vis_handler();

	vis = d_frame_get_control(frm, ID_REGISTER_GROUP_2);
    if(vis)
    {
       d_vis_enable(vis, D_FALSE);
    }
	
    vis = d_frame_get_control(frm, ID_REGISTER_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, set_register_window_handler);
    }
    return D_OK;
}

/** @brief set register菜单*/
D_Result
p_atv_set_register_show (D_U8 val) D_FUNCPOSTFIT
{
	switch(val)
	{
		case 0:
		base_addr = 0xbd501d00;
		break;
		case 1:
		base_addr = 0xbd500600;
		break;
		case 2:
		base_addr = 0xbd501300;
		break;
		case 3:
		base_addr = 0xbd501500;
		break;
		case 4:
		base_addr = 0xbd501400;
		break;
		case 5:
		base_addr = 0xbd500c00;
		break;
		case 6:
		base_addr = 0xbd501C00;
		break;
		case 7:
		base_addr = 0xffffffff;
		break;
		case 8:
		base_addr = 0xffffff00;
		break;	
		default:
		base_addr = 0xbd501C00;
		break;
	}

    return d_gui_enter_menu (&set_register_window, D_TRUE);
}

