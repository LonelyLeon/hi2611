/** @file
* @brief Gui
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#include "dResource.h"
#include "dApp.h"
#include "dGUI.h"
#include "dControl.h"
#include "dFont.h"
#include "dCBMan.h"
#include "dGDev.h"
#include "dGraph.h"
#include "dRect.h"
#include "dCharset.h"
#include "dConvCode.h"
#include "dDebug.h"
#include "pGuiResource.h"
#include "pConfig.h"
#include "pSdk.h"
#include "dAV.h"
#include "dMsg.h"
#include "dConfigFile.h"
#include "pConvCode.h"
#include "pBurnSerialNumber.h"
#include "pFontOther.h"
#include "dChpll.h"

#ifdef D_GUI_SUPPORT_FREETYPE
#include "../../tvmenu/resource/fixed_decker.c"
#elif defined(D_TV_UI_STYLE_MINI)
#include "../../tvmenu_mini/resource/fixed_iso8859_16_fnt.c"
#else
#include "../../tvmenu/resource/fixed_iso8859_16_fnt.c"
#endif

#ifdef D_TV_UI_STYLE_MINI
#include "../../tvmenu_mini/resource/fixed_gb2312_24_fnt.c"
#else
#include "../../tvmenu/resource/fixed_gb2312_24_fnt.c"
#endif
#include "pStbCaMenus.h"
#include "ver.h"

static D_HGDev g_hgdev;
static D_GSurface g_surface;
#ifdef D_USE_BACK_BUFFER
static D_GSurface g_back_surface;

#ifdef D_TV_LIULINK_OSD_PORTRAIT
static D_GSurface g_back_portrait_surface;
#endif

#endif
static D_U32 vis_count = 0;
static D_Bool ntsc_mode = 0;
static D_U32 vis_count_min = 2;

static D_VidBackGroundColor_t sysBackGround = D_VID_BackGround_Blue;
static D_VidBackGroundColor_t userBackGround = D_VID_BackGround_Blue;

#ifdef D_USE_BACK_BUFFER
#if 0
// 向右旋转90度
int d_sw_argb_rotate_right_90(unsigned char* argb_dst, 
                              unsigned char* argb_src,
                              unsigned int src_width, 
                              unsigned int src_height)
{
    int src_pos = 0;
    for (int i=0; i < src_height; i++)
    {
        src_pos = (src_height-1-i) * src_width;
        for (int j=0; j < src_width; j++)
        {
            *((D_U32*)argb_dst + j*src_height + i) = *((D_U32*)argb_src + src_pos + j);
        }
    }
    return 0;
}

// 向左旋转90度
int d_sw_argb_rotate_left_90(unsigned char* argb_dst, 
                             unsigned char* argb_src,
                             unsigned int src_width, 
                             unsigned int src_height)
{
    int src_pos = 0;
    int dst_pos = 0;

    for (int i=0; i < src_height; i++)
    {
        src_pos = i * src_width;
        for (int j=0; j < src_width; j++)
        {
            dst_pos = (src_width - j - 1) * src_height;
            *((D_U32*)argb_dst + dst_pos + i) = *((D_U32*)argb_src + src_pos + j);
        }
    }
    return 0;
}
#endif

// 向右旋转90度
int d_sw_argb_rotate_right_90_ex(unsigned char* argb_dst, 

                             unsigned char* argb_src,
                             unsigned int src_width,      //源图片宽
                             D_Rect *       src_rect,     //源图片中需要旋转的部分

                             unsigned int dst_x,          // 目标中x
                             unsigned int dst_y,          // 目标中y
                             unsigned int dst_width       // 目标图片宽度
                             )
{
    int src_pos = 0;
    int dst_pos = 0;
	int i;
	int j;

    
    for ( i=0; i < src_rect->h; i++)
    {
        src_pos = src_width * (src_rect->y + src_rect->h - 1 - i) + src_rect->x;



        for ( j=0; j < src_rect->w; j++)
        {
            dst_pos = dst_width * (dst_y +  j)  + dst_x ;



            *((D_U32*)argb_dst + dst_pos + i) = *((D_U32*)argb_src + src_pos + j);
        }
    }
    return 0;
}



// 向左旋转90度
int d_sw_argb_rotate_left_90_ex(unsigned char* argb_dst, 

                             unsigned char* argb_src,
                             unsigned int src_width,      //源图片宽
                             D_Rect *       src_rect,     //源图片中需要旋转的部分

                             unsigned int dst_x,          // 目标中x
                             unsigned int dst_y,          // 目标中y
                             unsigned int dst_width       // 目标图片宽度
                             )
{
    int src_pos = 0;
    int dst_pos = 0;
	int i;
	int j;





    for (i=0; i < src_rect->h; i++) {
        
        src_pos    = src_width * (src_rect->y + i) + src_rect->x;



        for (j=0; j < src_rect->w; j++) {
            dst_pos    = dst_width * (dst_y + src_rect->w - j - 1) + dst_x;

            *((D_U32*)argb_dst + dst_pos + i) = *((D_U32*)argb_src + src_pos + j);
        }
    }
    return 0;
}


static void gui_new_frame_ready_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_Rect *r = (D_Rect*)obj_data;
    D_Rect *rc = r;

#ifdef D_ARCH_HI2309
    /*
        Hi2309防抖和锯齿问题,先做一次防抖PDMA,源到源,
        再关掉防抖,做一次源到显存的抗齿PDMA
    */
    d_gdev_enable_hw_antiflicker(g_hgdev, D_TRUE);

    ((D_GSurface*)obj)->draw_mode = D_GSURF_DRAW_MODE_NORMAL;

    d_g_copy((D_GSurface*)obj, r, (D_GSurface*)obj, r);

    d_gdev_enable_hw_antiflicker(g_hgdev, D_FALSE);

    if(ntsc_mode)
    {
#if 0
        d_rect_set(r, 0, 0, ((D_GSurface*)obj)->buf.width, ((D_GSurface*)obj)->buf.height);
#else
        /* 局部刷新, 纵坐标和高度运算, 和ppu实际可能有一个像素误差 */
        D_Coord x, y, w, h;
        D_Rect dst;
        D_Double radio = (D_Double)g_surface.buf.height / (D_Double)((D_GSurface*)obj)->buf.height;

        x = r->x;
        y = (D_Coord)((D_Double)r->y * radio + 0.5);
        w = r->w;
        h = (D_Coord)((D_Double)r->h * radio + 0.5);

        d_rect_set(&dst, x, y, w, h);

        rc = &dst;
#endif
    }
#endif

#ifdef D_TV_LIULINK_OSD_PORTRAIT
    D_GSurface* srcSurf = (D_GSurface*)obj;
    D_Rect src_rect     = {0, 0, srcSurf->buf.width, srcSurf->buf.height};


//    int start = 0LL;
//    start = d_sys_get_time();
#ifdef D_TV_LIULINK_OSD_LEFT
    d_sw_argb_rotate_left_90_ex(g_back_portrait_surface.buf.buf, 
                                srcSurf->buf.buf,
                                srcSurf->buf.width,
                                &src_rect,
                                g_back_portrait_surface.buf.width  - src_rect.h - src_rect.y,
                                src_rect.x,
                                g_back_portrait_surface.buf.width);
#else
    d_sw_argb_rotate_right_90_ex(g_back_portrait_surface.buf.buf, 
                                srcSurf->buf.buf,
                                srcSurf->buf.width,
                                &src_rect,
                                g_back_portrait_surface.buf.width  - src_rect.h - src_rect.y,
                                src_rect.x,
                                g_back_portrait_surface.buf.width);
#endif
//    D_ERROR(">>>>>>>>>>>>rotate time=%d\n", d_sys_get_time()-start);
    D_Rect rotate_90_src = {0,0,D_SCREEN_HOR_RESOLUTION, D_SCREEN_VER_RESOLUTION};
    d_g_copy(&g_surface, &rotate_90_src, (D_GSurface*)&g_back_portrait_surface, &rotate_90_src);
#else
    d_g_copy(&g_surface, rc, (D_GSurface*)obj, r);
#endif
    d_gdev_flip_screen(g_hgdev, r);

    /*osd重绘完成时设置视频背景色(黑屏、蓝屏等), 这样肉眼就看不到过程，@qiny 20190527*/
    if(sysBackGround != userBackGround)
    {
        sysBackGround = userBackGround;
        d_av_set_vid_background(0, sysBackGround);
    }
}

#ifdef D_ARCH_HI2309
static void gui_vis_update_rect_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
//#ifdef D_ARCH_HI2309
    D_VisUpdateRectHook *vis_update_rect_hook = (D_VisUpdateRectHook*)obj_data;
    D_Rect *r = vis_update_rect_hook->update_rect;
    D_Coord x, y, w, h;

#define ANTI_FLICK_PATCH_ENLARGE_SIZE       (3)
    /* 防抖刷新补丁 */
    /*
        配合刷新屏幕前的防抖PDMA操作,由于是源到源,
        后备缓冲区的数据被防抖算法破坏, 所以必须
        在下次计算刷新区域时扩大一点,否则会有上次
        绘制残留在边缘上
    */
    x = (r->x >= ANTI_FLICK_PATCH_ENLARGE_SIZE) ? (r->x - ANTI_FLICK_PATCH_ENLARGE_SIZE) : 0;
    y = (r->y >= ANTI_FLICK_PATCH_ENLARGE_SIZE) ? (r->y - ANTI_FLICK_PATCH_ENLARGE_SIZE) : 0;
    w = ((r->w + ANTI_FLICK_PATCH_ENLARGE_SIZE * 2 + x) <= D_SCREEN_HOR_RESOLUTION) \
    ? (r->w + ANTI_FLICK_PATCH_ENLARGE_SIZE * 2) : (D_SCREEN_HOR_RESOLUTION - x);
    h = ((r->h + ANTI_FLICK_PATCH_ENLARGE_SIZE * 2 + y) <= D_SCREEN_VER_RESOLUTION) \
    ? (r->h + ANTI_FLICK_PATCH_ENLARGE_SIZE * 2) : (D_SCREEN_VER_RESOLUTION - y);
#undef ANTI_FLICK_PATCH_ENLARGE_SIZE

    d_rect_set(r, x, y, w, h);
//#endif
}

static void gui_control_new_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_ControlCallbackParam *ctrl_new_cb = (D_ControlCallbackParam*)obj_data;

    if((ctrl_new_cb->type != D_CTRL_DESKTOP) \
    && (ctrl_new_cb->type != D_CTRL_WINDOW) \
    && (ctrl_new_cb->type != D_CTRL_LABEL) \
    && (ctrl_new_cb->type != D_CTRL_DRAW_AREA))
    {
        ctrl_new_cb->vis->flags |= D_VIS_FL_TRANSPARENT;
    }
}
#endif
#endif

static D_U32  c_ddr_freq =1066;
void gui_set_ddr_freq(D_U32 freq) D_FUNCPOSTFIT
{	
#if defined(D_SYSTEM_HROS)
	if(freq == 1020)
	{
		if(c_ddr_freq == 1020)return;
		D_DUMP("hrpllapi(960) start ***********************************.\n");
		//hrpllapi(1020);
		d_pll_set_ddrfreq(1020);
		D_DUMP("hrpllapi(960) end ***********************************.\n");
		c_ddr_freq =1020;
	}
	else 
	{
		if(c_ddr_freq == 1066)return;
		D_DUMP("hrpllapi(1056)start ***********************************.\n");
		d_pll_set_ddrfreq(1066);
		//hrpllapi(1066);
		D_DUMP("hrpllapi(1056)end ***********************************.\n");
		c_ddr_freq =1066;
	}
#endif	
}

static void gui_vis_pll_jam_patch_cb(DemodType_t tuner_type, D_FEndFreq freq) D_FUNCPOSTFIT
{
    D_PllParam pllparam;
    D_U8 flag = 0;
    if((tuner_type ==demod_3308E_inside ) ||(tuner_type == demod_3701))
    {
    /**********************ddr切频率处理*************************/
         if(tuner_type  == demod_3701)
        {
            if(((freq / 1000 % 264) >= 256) ||((freq /1000 % 264)  <= 8) )
            {
                    flag = 1;
            }
        }
        if(tuner_type  ==demod_3308E_inside)
        {
            if(((freq % 264) >= 256) ||((freq % 264)  <= 8) )
            {
                    flag = 1;
            }
        }   
        if( flag ==1)
        {
			gui_set_ddr_freq(1020);
        }
        else if(c_ddr_freq == 1020 && flag == 0)
        {
			gui_set_ddr_freq(1066);
        }
		/**********************pll4切频率处理*************************/
    }
    if(tuner_type == demod_3701)
    {
    	if((freq == 152250) ||(freq == 160250)||(freq == 224250)||(freq == 232250)||(freq == 304250)||(freq == 312250)\
			||(freq == 384250)||(freq == 456250)||(freq == 464250)||(freq == 535250)||(freq == 547250)||(freq == 607250)||(freq == 615250)\
			||(freq == 687250)||(freq == 695250)||(freq == 767250)||(freq == 839250)||(freq == 847250))
    	{
			p_vip_set_panel_param(1);	
    	}
		else
		{
			p_vip_set_panel_param(0);			
		}
    }	
    else if(tuner_type ==demod_3308E_inside )
    {
    	if((freq == 538) ||(freq == 610)||(freq == 618)||(freq == 690)||(freq == 762)||(freq == 770)||(freq == 842)||(freq == 850))
	{
		p_vip_set_panel_param(1);	
	}
	else
	{
		p_vip_set_panel_param(0);			
	}    
    }
}

//add hegx
static void gui_vis_palntsc_cb(D_U8 temp) D_FUNCPOSTFIT
{
    D_Msg msg;

    //d_gdev_set_enable(g_hgdev, D_FALSE);
    msg.type = D_MSG_TV_VID_FMT_CHANGED;
    msg.tv.htv = g_htv;
#ifdef D_ARCH_HI2309
    msg.tv.param.vid_format = temp ? D_VID_FMT_NTSC : D_VID_FMT_PAL;
    if(temp == D_VID_FMT_PAL)
    {
        d_gdev_set_param (g_hgdev, D_SCREEN_VER_RESOLUTION);
    }
    else if(temp == D_VID_FMT_NTSC)
    {
        d_gdev_set_param (g_hgdev,  480);
    }
#else
    msg.tv.param.vid_format = (D_VidFormat)temp;
    //d_gdev_set_param(g_hgdev, 0);
#endif

    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_Msg));
}
static void gui_vis_input_cb(D_U8 temp) D_FUNCPOSTFIT
{
    D_UserMsg msg;
    msg.type = D_MSG_USER1;
    msg.handle = g_htv;
    msg.param1 = USER_MSG_PARAM1_INPUTFMT_CHANGE;
    msg.param2 = (D_VidInputFormat)temp;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}

static void gui_vis_unlock_cb(D_U8 temp) D_FUNCPOSTFIT
{
    D_UserMsg msg;
    msg.type = D_MSG_USER1;
    msg.handle = g_htv;
    msg.param1 = USER_MSG_PARAM1_INPUT_STATUS;
    msg.param2 = temp;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));

}
void p_gui_set_vis_count(D_U32 num) D_FUNCPOSTFIT
{
    if(vis_count > vis_count_min)//原来是开osd
    {
        if(vis_count <= num)
        {
            d_gdev_set_enable(g_hgdev, D_FALSE);
        }
    }
    else
    {
        if(vis_count >  num)
        {
            d_gdev_set_enable(g_hgdev, D_TRUE);
        }
    }
    vis_count_min = num;
}
void p_gui_reset_vis_count(void) D_FUNCPOSTFIT
{
    if(vis_count > vis_count_min)//原来是开osd
    {
        if(vis_count <= 2)
        {
            d_gdev_set_enable(g_hgdev, D_FALSE);
        }
    }
    else
    {
        if(vis_count >  2)
        {
            d_gdev_set_enable(g_hgdev, D_TRUE);
        }
    }
    vis_count_min = 2;
}
static void gui_vis_new_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    if(vis_count ++ == vis_count_min)
        d_gdev_set_enable(g_hgdev, D_TRUE);
    //D_ERROR("vis_count %d/%d\n", vis_count, vis_count_min);
}

static void gui_vis_free_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{

    if(-- vis_count == vis_count_min)
        d_gdev_set_enable(g_hgdev, D_FALSE);
    //D_ERROR("vis_count %d/%d\n", vis_count, vis_count_min);
}

#ifdef D_GUI_SUPPORT_FREETYPE
static void font_op_char_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_Char **chr_p = (D_Char**)obj_data;
    D_Char *chr = *chr_p;
    static D_U16 utf16;
    D_Font *fnt = (D_Font*)obj;

    /* freetype字库, 需要转码成unicode */
    if(D_IS_ASCII((D_Char)*chr))
    {
        utf16 = (D_U16)((D_U8) * chr);
    }
    else
    {
        utf16 = '*';
    }

    *((D_Char**)obj_data) = (D_Char*)&utf16;
}
#endif
/*根据当前制式自动匹配小窗口坐标*/
D_Result
p_gui_auto_match_window_format(D_Coord* x, D_Coord* y, D_Coord* w, D_Coord* h)D_FUNCPOSTFIT
{
    D_VidFormat fmt;
    D_Coord output_width = 1920;
    D_Coord output_height = 1080;
	D_U8 *payload;
	D_U16 len;
	
	payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_PANEL_CONFIG, &len);
	if(payload)
	{
		output_width = ((D_U16)payload[2]<<8 )|payload[3];
		output_height = ((D_U16)payload[4]<<8 )|payload[5];
	}
	else
	{
	    fmt = p_conf_get_vid_fmt();
	    switch(fmt)
	    {
	        case D_VID_FMT_480I_60:
	        case D_VID_FMT_480P_60:
	            output_width = 720;
	            output_height = 480;
	            break;
	        case D_VID_FMT_576I_50:
	        case D_VID_FMT_576P_50:
	            output_width = 720;
	            output_height = 576;
	            break;
	        case D_VID_FMT_720P_50:
	        case D_VID_FMT_720P_60:
	            output_width = 1280;
	            output_height = 720;
	            break;
	        case D_VID_FMT_1080I_50:
	        case D_VID_FMT_1080P_50:
	        case D_VID_FMT_1080I_60:
	        case D_VID_FMT_1080P_60:
	            output_width = 1920;
	            output_height = 1080;
	            break;
	        case D_VID_FMT_768P_50:
	        case D_VID_FMT_768P_60:
	            output_width = 1366;
	            output_height = 768;
	            break;
	        case D_VID_FMT_1440_900:
	            output_width = 1440;
	            output_height = 900;
	            break;
	        default:
	            break;
	    }
	}
    (*x) = (*x) * output_width / D_SCREEN_HOR_RESOLUTION;
    (*w) = (*w) * output_width / D_SCREEN_HOR_RESOLUTION;
    (*y) = (*y) * output_height / D_SCREEN_VER_RESOLUTION;
    (*h) = (*h) * output_height / D_SCREEN_VER_RESOLUTION;
    return D_OK;
}

static void font_init(void) D_FUNCPOSTFIT
{
    D_Font * ascii_fnt, *gb2312_fnt;
    D_FontDesc fnt_desc;

    d_font_open();

#ifdef D_GUI_SUPPORT_FREETYPE
    fnt_desc.font_type = D_FONT_FREETYPE;
    fnt_desc.cset = D_CHARSET_ISO8859;
    fnt_desc.size = 20;
    fnt_desc.font_data = (D_U8*)fixed_decker_buf;
    fnt_desc.font_data_size = sizeof(fixed_decker_buf);
    ascii_fnt = d_font_create(&fnt_desc);

    d_cbman_subscribe(PL_FONT_OP_CHAR, (D_Handle)ascii_fnt, font_op_char_cb, NULL);
#else
    fnt_desc.font_type = D_FONT_DIANZHEN_ASCII;
    fnt_desc.cset = D_CHARSET_ISO8859;
    fnt_desc.size = 24;
    fnt_desc.font_data = (D_U8*)fixed_iso8859_16_fnt_buf;
    fnt_desc.font_data_size = sizeof(fixed_iso8859_16_fnt_buf);
#endif
    ascii_fnt = d_font_create(&fnt_desc);
#ifdef D_TV_UI_STYLE_MINI
    fnt_desc.font_type = D_FONT_DIANZHEN_HANZI;
    fnt_desc.cset = D_CHARSET_GB2312;
    fnt_desc.size = 24;
    fnt_desc.font_data = (D_U8*)fixed_gb2312_24_fnt_buf;
    fnt_desc.font_data_size = sizeof(fixed_gb2312_24_fnt_buf);
    gb2312_fnt = d_font_create(&fnt_desc);

    d_font_set(gb2312_fnt, 24);
#else
    fnt_desc.font_type = D_FONT_DIANZHEN_HANZI;
    fnt_desc.cset = D_CHARSET_GB2312;
    fnt_desc.size = 24;
    fnt_desc.font_data = (D_U8*)fixed_gb2312_24_fnt_buf;
    fnt_desc.font_data_size = sizeof(fixed_gb2312_24_fnt_buf);
    gb2312_fnt = d_font_create(&fnt_desc);

    d_font_set(gb2312_fnt, 24);
#endif

#ifdef D_GUI_SUPPORT_GBK
    p_gbk_font_init();
#endif
    p_cc_open();
}

D_Result p_gui_init(void) D_FUNCPOSTFIT
{
    D_Result ret;
    D_GDevAttr dev_attr;
    D_GDevMode mode;
    D_GSurface *surf;
    D_GUIOpenParam gui_open_param;
#ifdef D_USE_BACK_BUFFER
    D_Image *back_image;
#endif

    font_init();

    ret = d_gdev_open();
    if(ret != D_OK)
    {
        D_ERROR("d_gdev_open() failed! Err = %d\n", ret);
        return D_ERR;
    }

    D_GDEV_ATTR_INIT(&dev_attr);
    g_hgdev = d_gdev_create(&dev_attr);
    if(g_hgdev == D_INVALID_HANDLE)
    {
        D_ERROR("d_gdev_create() failed!\n");
        d_gdev_close();
        return D_ERR;
    }

    switch(D_SCREEN_COLOR_BITS)
    {
        case 8:
            mode = D_GDEV_MODE_8BPP;
            break;
        case 24:
            mode = D_GDEV_MODE_24BPP;
            break;
        case 32:
            mode = D_GDEV_MODE_32BPP;
            break;
        case 16:
        default:
            mode = D_GDEV_MODE_16BPP;
            break;
    }

    ret = d_g_dev_surface_init(&g_surface, D_GDEV_MODE_32BPP, g_hgdev, NULL, D_SCREEN_HOR_RESOLUTION, D_SCREEN_VER_RESOLUTION);
    if(ret != D_OK)
    {
        D_ERROR("d_g_dev_surface_init() failed! Err = %d\n", ret);
        d_gdev_destroy(g_hgdev);
        d_gdev_close();
        return D_ERR;
    }
    /*不需要画矩形，由下面d_gui_update()清屏  qiny*/
    //d_g_set_fg(&g_surface, d_g_map_pixel(&g_surface, D_RGBA(0, 0, 0, 0)));
    //d_g_fill_rect(&g_surface, &g_surface.clip);
    //d_gdev_set_enable(g_hgdev, D_TRUE);
#ifdef D_SUPPORT_USB_SERIAL
	d_serial_open_usb();
#endif  
#if defined(D_SYSTEM_WIN32)

#else
#ifdef D_BURNER_SERIAL_NUM
#ifdef D_BURN_SN_MODE_A
    /*先清一下屏，在打开osd，不然烧写序列号界面显示不出来*/
    d_g_set_fg(&g_surface, d_g_map_pixel(&g_surface, D_RGBA(0, 0, 0, 0)));
    d_g_fill_rect(&g_surface, &g_surface.clip);
    d_gdev_set_enable(g_hgdev, D_TRUE);
    d_gdev_set_global_alpha(g_hgdev, 0x80);
    p_burn_serial_number(1, &g_surface);    //开机烧写序列号
#endif
#ifdef D_BURN_SN_MODE_B
#ifdef D_COLOUR_SERIAL_EN
    /* 判断是否使用debug模式，是否启动串口命令任务 @qiny 20150913*/
    if(p_tvconf_get_debug_en())     // if(p_stb_ca_burn_serial_number() != D_OK)
    {
        D_CRIT("start test [version]%s[end]", REVISION); //打印svn版本号
        p_serial_monitor_create(1, p_tv_bur_sn_handle, 0xffffffff, D_TRUE);
    }
#else
	 if(p_tvconf_get_debug_en())     //
        {
#ifdef D_JIANGSU_BURNER_SERIAL_NUM
            p_serial_monitor_create(1, p_js_bur_sn_handle, 0xffffffff, D_TRUE);
#else
            p_stb_ca_burn_serial_number();
#endif
        }
#endif
#endif
    #ifdef D_BURN_SN_MODE_E
/*    	d_dbg_set_io_func(NULL, NULL);*/
    	p_serial_monitor_create(14, p_es_bur_sn_handle, 0xffffffff, D_TRUE);
    #endif
#endif
#endif
    surf = &g_surface;

#ifdef D_USE_BACK_BUFFER
    back_image = d_image_new(mode,D_VIRTUAL_SCREEN_W, D_VIRTUAL_SCREEN_H);
    if(back_image)
    {
        d_g_mem_surface_init(&g_back_surface, mode, back_image->buf.buf, \
        back_image->palettes, back_image->buf.width, back_image->buf.height, \
        back_image->buf.pitch, D_TRUE);

        surf = &g_back_surface;

        d_cbman_subscribe(PL_GUI_NEW_FRAME_READY, (D_Handle)surf, gui_new_frame_ready_cb, (D_Ptr)&g_surface);
#ifdef D_ARCH_HI2309
        d_cbman_subscribe(PL_GUI_VIS_UPDATE_RECT, D_INVALID_HANDLE, gui_vis_update_rect_cb, NULL);
        d_cbman_subscribe(PL_GUI_CONTROL_NEW, D_INVALID_HANDLE, gui_control_new_cb, NULL);
#endif
    }
    else
    {
        D_INFO("No mem to allocate back buffer!\n");
    }

#ifdef D_TV_LIULINK_OSD_PORTRAIT
    D_Image *back_portrait_image = NULL;
    back_portrait_image = d_image_new(mode,D_SCREEN_HOR_RESOLUTION, D_SCREEN_VER_RESOLUTION);
    if(back_portrait_image)
    {
        d_g_mem_surface_init(&g_back_portrait_surface, mode, back_portrait_image->buf.buf, \
        back_portrait_image->palettes, back_portrait_image->buf.width, back_portrait_image->buf.height, \
        back_portrait_image->buf.pitch, D_TRUE);
    }
#endif


#endif

    d_cbman_subscribe(PL_GUI_VIS_NEW, D_INVALID_HANDLE, gui_vis_new_cb, NULL);
    d_cbman_subscribe(PL_GUI_VIS_FREE, D_INVALID_HANDLE, gui_vis_free_cb, NULL);

    gui_open_param.draw_surf = surf;
    gui_open_param.queue = d_app_get_queue(d_app_self());
    gui_open_param.poll_time = 20;

    d_gui_open(&gui_open_param);
#if 0  /*调整到p_stb_open里 qiny*/
    p_gui_stb_resource_open();
    p_gui_ca_resource_open();
    d_gui_resource_open();
    d_gui_lang_set(p_conf_get_lang());
#endif
    d_theme_open();
    d_gui_update();  /* 引起一次刷新, 清osd缓冲区 */
    d_gdev_set_enable(g_hgdev, D_TRUE);
    d_av_setguicb((DAVGUICALLBACK)gui_vis_palntsc_cb);
    d_av_setinputcb((DAVGUICALLBACK)gui_vis_input_cb);
    d_av_setunlockcb((DAVGUICALLBACK) gui_vis_unlock_cb);
#if defined(D_SYSTEM_HROS)
    d_pll_jam_patchcb((DFENDPLLCALLBACK)gui_vis_pll_jam_patch_cb);
#endif
    D_DUMP("p_gui_init Ok.\n");

    return D_OK;
}

D_HGDev p_gui_get_hgdev(void) D_FUNCPOSTFIT
{
    return g_hgdev;
}

D_Result p_gui_set_format(D_VidFormat fmt) D_FUNCPOSTFIT
{
    D_U8 transp;
    D_U8 transparency[] = {128, 115, 90, 64, 38};

    transp = p_conf_get_transp();
    transp = (transp > 4) ? 0 : transp;

    d_gdev_set_global_alpha(g_hgdev, transparency[transp]);

#ifdef D_ARCH_HI2309
    if(fmt == D_VID_FMT_PAL)
    {
//      d_gdev_set_param (g_hgdev, D_SCREEN_VER_RESOLUTION);

        g_surface.draw_mode &= ~D_GSURF_DRAW_MODE_STRETCH;
        g_surface.buf.height = D_SCREEN_VER_RESOLUTION;
        ntsc_mode = 0;
    }
    else if(fmt == D_VID_FMT_NTSC)
    {
//      d_gdev_set_param (g_hgdev,  480);

        g_surface.draw_mode |= D_GSURF_DRAW_MODE_STRETCH;
        g_surface.buf.height = 480;
        ntsc_mode = 1;
    }

    d_vis_update(NULL, NULL);
#endif

    //if(vis_count >= 3)
    d_gdev_set_enable(g_hgdev, D_TRUE);

    return D_OK;
}

D_GSurface *p_gui_get_dev_surface(void) D_FUNCPOSTFIT
{
    return &g_surface;
}



/** @brief 取得当前osd的显示信息，宽高模式以及当前截屏数据*/
D_Result p_gui_get_osd_image_info(D_U32 *width, D_U32 *height, D_U32 *pitch, D_GDevMode *mode, D_U8*buf) D_FUNCPOSTFIT
{
    D_GSurface *gui_surface, *surf;
    D_U32 len;

    gui_surface = d_gui_get_surface();
    d_g_lock(gui_surface);
    surf = &g_surface;
#ifdef D_USE_BACK_BUFFER
    surf = &g_back_surface;  /* 有缓冲区就给缓冲区*/
#endif
    len = (D_U32)(surf->buf.height * surf->buf.pitch);
    if(buf)
    {
        memcpy(buf, surf->buf.buf, len);
    }

    if(width)*width = (D_U32)surf->buf.width;
    if(height)*height = (D_U32)surf->buf.height;
    if(pitch)*pitch = (D_U32)surf->buf.pitch;
    if(mode)*mode = (D_GDevMode)surf->buf.mode;
    d_g_unlock(gui_surface);
    return D_OK;
}

/** @brief 设置视频背景色（黑屏、蓝屏等），project封装为解决视觉亮暗现象
direct 立即起作用，还是跟随osd重新绘制时起作用
*/
D_Result p_av_set_vid_background(D_HAV hav, D_VidBackGroundColor_t BackGround, D_Bool direct)D_FUNCPOSTFIT
{
    userBackGround = BackGround;
    if(direct)
    {
        sysBackGround = userBackGround;
        d_av_set_vid_background(hav, BackGround);
    }

    return D_OK;
}


