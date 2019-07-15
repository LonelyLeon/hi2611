/** @file
* @brief 窗口模块
* @author  jx
* @date 2014-05-20 : jx 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "pMem.h"
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dFEnd.h"
#include "dGUI.h"
#include "dTask.h"
#include "dFMan.h"
#include "pStbMenus.h"
#include "pGuiResource.h"
#include "pPlayer.h"
#include "dTypes.h"
#include "channel_spectrum_window.c"
#include "scatter_and_demo_info_window.c"
#include "channel_impulse_window.c"
#include "channel_demo_detial_window.c"
#include "channel_carrier_freq_window.c"

#define D_DRAW_DUMP  D_DUMP   ///<调试打印信息

//解调基本信息位置
#define FRAME_INFO_X    10
#define FRAME_INFO_Y    30
#define FRAME_INFO_W    150
#define FRAME_INFO_H    256

//解调详细信息位置
#define  FRAME_DEMO_INFO_X1   50
#define  FRAME_DEMO_INFO_X2   310
#define  FRAME_DEMO_INFO_Y     25

#define FRAME_INFO_String_W 45  //用于控制显示字的偏移
#define FRAME_INFO_String_H 28

#define FRAME_IMSPLUSE_H    33
#define FRAME_IMSPLUSE_LEN   7 //刻度线长度

#define FRAME_HN420_X    88//420时写数字的x偏移
#define FRAME_HN595_X    0 //595时写数字的x偏移
#define FRAME_HN945_X    63//945时写数字的x偏移

#define FRAME_HN420_START  148 //画刻度时的起始位置
#define FRAME_HN595_START  48
#define FRAME_HN945_START  98

#define FLUSH_TIME_IMPLUSE          (3000)
#define FLUSH_TIME_SCATT         (500)
#define FLUSH_TIME_SPECTRUM     (1700)
#define FLUSH_TIME_DEMO_DETIAL  (500)
#define FLUSH_TIME_CARRIER_FREQ      (1200)

#define OSD_SCATT   1  //星座图
#define OSD_HN      0  //信道冲击响应
#define OSD_FREQ    2  //频谱图

#define DRAW_COLOR_CNT  (5)

//引导头定义
#define OSD_PN420   1
#define OSD_PN595   2
#define OSD_PN945   3

//用于记录当前的HI3308C的引导头部分，便于区别对待OSD
static D_U8 OSD_PN = 3;

/*星座图界面参数 */
typedef struct
{
    D_U8        scatt[64][2];        /*星座图x,y点*/
    D_U16       C;        /* 单/多载波模式 */
    D_U8        QAM;     /* 调制QAM数 */
    D_U8            FEC;     /* 前向纠错码率 */
    D_U16       PN;     /* 帧头模式 */
    D_U16       INTL;       /* 交织深度 */
    D_U8        Mod;       /* 接收方式：固定、移动、自动选择 */
    D_U8        AGC;       /* 中频信号强度 */
    float           CN;       /* 信噪比 */
    D_U8        BER;       /* 误码率 */
    D_U16   N_pre;              /* 信道前径长度指示 */
    D_U16       N_post;          /* 信道后径长度指示 */
    D_U8        Dly_len_equ;        /*信道均衡使用最大延时长度 */
    D_U8        Dly_len_est;         /* 信道估计得到的最大延时长度 */
    float           diff_sum;         /* 信道变化速度指示 */
    float           FF_thrld;         /* 移动信道门限值 */
    D_U8        Lock;         /* 同步锁定指示 */
    D_U8        PN_Phase;         /*PN相位变化指示信号 */
} ScattDemoInfomation;


/*解调详细参数 */
typedef struct
{
    float       CFO_Khz;        /*载波频率偏差*/
    float           SFO_ppm;        /* 采样频率偏差 */
    D_U8        LDPC_Iter;     /* LDPC译码器迭代次数 */
    D_U8        NULL_Ratio;     /*TS流中的空包比率 */
    D_U16       Pth_max_idx;     /* 信道冲击响应最大值 */
    D_U16       Win_opn_idx;       /* 信道开窗位置指示 */
    D_U8        Equ_smooth_factor;       /* 均衡平滑系数 */
    D_U8        Est_smooth_factor;       /* 估计平滑系数 */
    float           Mod_diff_sum;       /* 信道变化量指示 */
    float           Mod_FF_thrld;       /* 移动信道门限值 */
    D_U16       Hn_equ_sum_num;    /* 信道均衡用于统计噪声的点数 */
    float           Hn_equ_sum_all;  /* 信道均衡统计噪声之和 */
    D_U16       Hn_est_sum_num;        /*信道估计用于统计噪声的点数 */
    float           Hn_est_sum_all;         /* 信道估计统计噪声之和 */
    float           CPE_phase;         /*  CPE相位值 */
    D_U8        Mul_factor_est;         /* 信道估计乘积系数 */
    D_U8        Mul_factor_equ;         /* 信道均衡乘积系数 */
    float           LLR_mean;         /*软信息均值 */
    D_U8        Datacast_flag;         /*多业务指示信号 */
    float           Thres_low;         /*多业务判断低门限 */
    D_U16       Thres_high;         /*多业务判断高门限 */
} DemoDetilInfomation;

typedef struct
{
    float   CFO_Khz; /*载波频率偏差*/
    float   SFO_ppm; /* 采样频率偏差 */
    D_U8    LDPC_Iter; /* LDPC译码器迭代次数 */
    D_U8     NULL_Ratio; /*TS流中的空包比率 */
//D_U16     Pth_max_idx; /* 信道冲击响应最大值 */
    D_U16   Win_opn_idx; /* 信道开窗位置指示 */
    D_U8    PNF_smooth_factor; /* 均衡平滑系数 */
    D_U8     HD_smooth_factor; /* 估计平滑系数 */
    float   Mod_diff_sum; /* 信道变化量指示 */
    float   Mod_HD_1_to_0_SC; /* 移动信道门限值 */
    float       Mod_HD_0_to_X_SC; /* 信道均衡用于统计噪声的点数 */
    float   Mod_PNF_2_to_1_SC;  /* 信道均衡统计噪声之和 */
    float   Mod_HD_1_to_0_MC; /*信道估计用于统计噪声的点数 */
    float   Mod_HD_0_to_X_MC; /* 信道估计统计噪声之和 */
    float   Mod_PNF_2_to_1_MC; /* CPE相位值 */
    float   Mod_PNF_1_to_7_ALL; /* 信道估计乘积系数 */
//D_U8  Mul_factor_equ; /* 信道均衡乘积系数 */
//float     LLR_mean; /*软信息均值 */
    D_U8    Datacast_flag; /*多业务指示信号 */
    float   Thres_low; /*多业务判断低门限 */
    D_U16   Thres_high; /*多业务判断高门限 */
} DemoDetilInfomation_E;

/*信道冲击响应*/
typedef struct
{
    D_U16   PN;     /* 帧头模式 */
    D_U32  Hn[1890];
} DemoHnInfomation;
/*信道载波频谱*/
typedef struct
{
    D_U16   C;     /* 帧头模式 */
    float  Freq[600];
} DemocarrierfreqInfomation;
/*信道频谱*/
typedef struct
{
    D_U16   C;     /* 帧头模式 */
    float  Freq[600];
} DemofreqInfomation;

/** @brief 定时器*/
static D_HTimer htimer ;

typedef enum
{
    DRAW_BG,
    DRAW_RED,
    DRAW_GREEN,
    DRAW_YELLOW,
    DRAW_BLUE,
    DRAW_WHITE,
    DRAW_BORDER
} DrawColor;

static D_Color const D_FAR draw_color[] =
{
    D_RGB(0, 0, 0),
    D_RGB(255, 0, 0),
    D_RGB(0, 255, 0),
    D_RGB(255, 255, 0),
    D_RGB(52, 114, 188),
    D_RGB(255, 255, 255),
    D_RGB(200, 200, 200),
};

static D_Pixel  draw_pixel[DRAW_COLOR_CNT + 2];

typedef struct
{
    D_FEndadvanceStatus impulse_str;
    D_FEndadvanceStatus scatter_and_demo_str;
    D_FEndadvanceStatus spectrum_str;
    D_FEndadvanceStatus demo_detial_str;
    D_FEndadvanceStatus carrier_freq_str;

    DemoHnInfomation Hninfo;
    ScattDemoInfomation scattinfo;
    DemofreqInfomation  freqinfo;
    DemoDetilInfomation demo_detial_info;
    DemoDetilInfomation_E demo_detial_e_info;
    DemocarrierfreqInfomation carrier_freq_info;

    D_U8 Hn[8000];
    D_U8  scatt[200];
    D_U8 Freq[2500];
    D_U8 demo_detial[100];
    D_U8 carrier_freq[2500];
} D_SignalInfoDat;
static D_SignalInfoDat *signal_info = NULL;
static D_Image *image_spectru = NULL;
/** @brief 计算字符串长度*/
static D_Size
d_strlen (D_Char *str) D_FUNCPOSTFIT
{
	return strlen (str);
}

static D_Result signal_test_memory(D_Bool alloc_flag)
{
    if(alloc_flag)
    {
        if(signal_info == NULL)
        {
            signal_info = (D_SignalInfoDat*)PROJECT_ALLOC(sizeof(D_SignalInfoDat));
        }
        if(signal_info)
        {
            memset(signal_info, 0x00, sizeof(D_SignalInfoDat));
        }
    }
    else
    {
        if(signal_info)
        {
            PROJECT_FREE(signal_info);
            signal_info = NULL;
        }
    }

    return D_OK;
}


static D_Result signal_draw_text(D_Visual *vis, D_Coord x, D_Coord y, D_Char *text, D_Size cnt, D_Pixel pix) D_FUNCPOSTFIT
{
    if(!vis || !text || !cnt)
        return D_ERR;

    /* 字符绘制只能用alpha叠加, 否则会有透明底框 */
    d_vis_set_mode(D_GSURF_DRAW_MODE_ALPHABLEND);

    d_vis_set_fg (pix);
    d_vis_draw_text (vis, x, y, text, cnt);

    /* 恢复原来的绘图模式 */
    d_vis_set_mode((vis->flags & D_VIS_FL_TRANSPARENT \
    ? D_GSURF_DRAW_MODE_ALPHABLEND : D_GSURF_DRAW_MODE_NORMAL) | D_GSURF_DRAW_MODE_TILE);

    return D_OK;
}

/** @brief 更新信道冲击响应画图区*/
static void
update_impulse_draw (void) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_impulse_window;
    D_Visual    *vis;
    D_U32 time1;

    memset(&(signal_info->impulse_str), 0, sizeof(signal_info->impulse_str));
    signal_info->impulse_str.type = D_FEND_DTMB_HN_INFO;
    signal_info->impulse_str.Statusinfo = &signal_info->Hn[0];

    d_fman_get_advance_status_direct(d_fman_get_handle_by_type(D_FEND_DTMB, 0), &signal_info->impulse_str);
    memcpy(&(signal_info->Hninfo.PN), (D_U16*) & (signal_info->Hn[0]), sizeof(signal_info->Hninfo.PN));
    memcpy(&(signal_info->Hninfo.Hn), (D_U32*) & (signal_info->Hn[4]), sizeof(signal_info->Hninfo.Hn));

    if(signal_info->Hninfo.PN == 420)
    {
        OSD_PN = OSD_PN420;
    }
    else if(signal_info->Hninfo.PN == 595)
    {
        OSD_PN = OSD_PN595;
    }
    else if(signal_info->Hninfo.PN == 945)
    {
        OSD_PN = OSD_PN945;
    }
    vis = d_frame_get_control (frm, ID_IMPULSE_DRAW_BACK);
    if (vis)
    {
        /*更新重新绘制一个控件*/
        d_vis_update (vis, NULL);
    }
}

/** @brief 用于画信道冲击响应*/
static void DrawHnn(D_Visual *vis) D_FUNCPOSTFIT
{
    D_U32  i, j, start_count, countmax, max_i, max_j;
    D_S16 position;
    D_U16 hnStart1, hnEnd1, hnStart2, hnEnd2, hnStep;
    D_U32 datamax, maxdata;
    if(OSD_PN == OSD_PN945)
    {
        hnStart1 = 0;
        hnEnd1   = 1890;
        hnStep  = 4;
    }
    else if(OSD_PN == OSD_PN595)
    {
        hnStart1 = 0;
        hnEnd1   = 1190;
        hnStep  = 2;
    }
    else if(OSD_PN == OSD_PN420)
    {
        hnStart1 = 0;
        hnEnd1   = 840;
        hnStep  = 2;
    }
    datamax = 0;
    maxdata = 0;
    start_count = 0;
    countmax = 0;
    max_i = 0;
    max_j = 0;
    for(i = hnStart1; i < (hnEnd1 - hnStart1) / hnStep; i++)
    {
        for(j = 0; j < hnStep; j++)
        {
            if(signal_info->Hninfo.Hn[i * hnStep + j] > datamax)
            {
                datamax = signal_info->Hninfo.Hn[i * hnStep + j];
                max_j = j;
            }

        }
        if(datamax > 0)
        {
            start_count = 1;
            if(datamax > maxdata)
                maxdata = datamax;
            if(datamax > countmax)
            {
                countmax = datamax;
                max_i = i;
            }

            if(OSD_PN == OSD_PN420)
            {
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  FRAME_HN420_X + i,  vis->rect.h - 5 - FRAME_INFO_String_H,  FRAME_HN420_X + i,  vis->rect.h - 5 - datamax - FRAME_INFO_String_H);
            }
            else if(OSD_PN == OSD_PN595)
            {
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  FRAME_HN595_X + i,  vis->rect.h - 5 - FRAME_INFO_String_H,  FRAME_HN595_X + i,  vis->rect.h - 5 - datamax - FRAME_INFO_String_H);
            }
            else if(OSD_PN == OSD_PN945)
            {
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  FRAME_HN945_X + i,  vis->rect.h - 5 - FRAME_INFO_String_H,  FRAME_HN945_X + i,  vis->rect.h - 5 - datamax - FRAME_INFO_String_H);
            }
        }
        if((start_count == 1) && (datamax == 0))
        {
            start_count = 0;

            if(OSD_PN == OSD_PN420)
            {
                position = (max_i * hnStep + max_j) - 420;
            }
            else if(OSD_PN == OSD_PN595)
            {
                position = (max_i * hnStep + max_j) - 595;
            }
            else if(OSD_PN == OSD_PN945)
            {
                position = (max_i * hnStep + max_j) - 945;
            }
            D_DRAW_DUMP("position: %d maxdata: %d\n", position, countmax);
            countmax = 0;
        }
        datamax = 0;

    }

}

/** @brief 信道冲击响应事件处理*/
static D_Result
channel_impulse_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &channel_impulse_window;
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU:
                    signal_test_memory(D_FALSE);
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    signal_test_memory(D_FALSE);
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return d_gui_replace_menu (&scatter_and_demo_info_window);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    return d_gui_replace_menu (&channel_carrier_freq_window);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            update_impulse_draw ();
            break;

        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 信道冲击响应事件处理*/
static D_Result
channel_impulse_draw_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U16 i = 0;
    D_Rect  rect = {0};
    D_Char  str_num[10] = {0};

    switch (evt->type)
    {
        case D_EVT_DRAW:
            if(OSD_PN == OSD_PN420)
            {
                /*画背景*/
                d_vis_set_fg (draw_pixel[DRAW_BLUE]);
                d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
                d_vis_draw_fill_rect (vis, &rect);

                /*画直线*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  1,  vis->rect.h - FRAME_IMSPLUSE_H,  vis->rect.w - 1,  vis->rect.h - FRAME_IMSPLUSE_H);

                sprintf (str_num, "-420");
                signal_draw_text (vis, FRAME_HN420_X - 40, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "0");
                signal_draw_text (vis, (vis->rect.w) / 2 - 5, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                //sprintf (str_num,"200");
                //signal_draw_text (vis, (vis->rect.w)/2+85, vis->rect.h-5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "420(55us)");
                signal_draw_text (vis, (vis->rect.w - FRAME_HN420_X - 5), vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);

                /*画刻度*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis, vis->rect.w - FRAME_HN420_X,  vis->rect.h - FRAME_IMSPLUSE_H, vis->rect.w - FRAME_HN420_X,  vis->rect.h - FRAME_IMSPLUSE_H + 7);
                d_vis_draw_line(vis,  FRAME_HN420_X,  vis->rect.h - FRAME_IMSPLUSE_H, FRAME_HN420_X,  vis->rect.h - FRAME_IMSPLUSE_H + 7);
                d_vis_draw_line(vis,  vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H, vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H + 7);
#if 0
                for(i = 0; i < 7; i++)
                {
                    d_vis_draw_line(vis, FRAME_HN420_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H, FRAME_HN420_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H + FRAME_IMSPLUSE_LEN);
                }
#endif

            }
            else if(OSD_PN == OSD_PN595)
            {
                /*画背景*/
                d_vis_set_fg (draw_pixel[DRAW_BLUE]);
                d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
                d_vis_draw_fill_rect (vis, &rect);

                /*画直线*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  1,  vis->rect.h - FRAME_IMSPLUSE_H,  vis->rect.w - 1,  vis->rect.h - FRAME_IMSPLUSE_H);

                sprintf (str_num, "-595");
                signal_draw_text (vis, FRAME_HN595_X, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "0");
                signal_draw_text (vis, (vis->rect.w) / 2 - 5, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                //sprintf (str_num,"38us");
                //signal_draw_text (vis, (vis->rect.w)/2+85, vis->rect.h-5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "595(79us)");
                signal_draw_text (vis, (vis->rect.w - FRAME_HN595_X - 92), vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);

                /*画刻度*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H, vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H + 7);
#if 0
                for(i = 0; i <= 10; i++)
                {
                    d_vis_draw_line(vis, FRAME_HN595_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H, FRAME_HN595_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H + FRAME_IMSPLUSE_LEN );
                }
#endif
            }
            else if(OSD_PN == OSD_PN945)//945
            {
                /*画背景*/
                d_vis_set_fg (draw_pixel[DRAW_BLUE]);
                d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
                d_vis_draw_fill_rect (vis, &rect);

                /*画直线*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis,  1,  vis->rect.h - 5 - FRAME_INFO_String_H,  vis->rect.w - 1,  vis->rect.h - 5 - FRAME_INFO_String_H);

                sprintf (str_num, "-945");
                signal_draw_text (vis, FRAME_HN945_X - 40, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "0");
                signal_draw_text (vis, (vis->rect.w) / 2 - 5, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
                sprintf (str_num, "945(125us)");
                signal_draw_text (vis, (vis->rect.w - 105), vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);

                /*画刻度*/
                d_vis_set_fg (draw_pixel[DRAW_WHITE]);
                d_vis_draw_line(vis, vis->rect.w - FRAME_HN945_X,  vis->rect.h - FRAME_IMSPLUSE_H, vis->rect.w - FRAME_HN945_X,  vis->rect.h - FRAME_IMSPLUSE_H + FRAME_IMSPLUSE_LEN);
                d_vis_draw_line(vis,  FRAME_HN945_X,  vis->rect.h - FRAME_IMSPLUSE_H, FRAME_HN945_X,  vis->rect.h - FRAME_IMSPLUSE_H + FRAME_IMSPLUSE_LEN);
                d_vis_draw_line(vis,  vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H, vis->rect.w / 2,  vis->rect.h - FRAME_IMSPLUSE_H + 7);
#if 0
                for(i = 0; i <= 8; i++)
                {
                    d_vis_draw_line(vis, FRAME_HN945_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H, FRAME_HN945_START + (i * 50),  vis->rect.h - FRAME_IMSPLUSE_H + FRAME_IMSPLUSE_LEN);
                }
#endif
            }
            DrawHnn(vis);
            break;
        default:
            break;
    }
    return D_OK;
}




/** @brief 信道冲击窗口初始化*/
D_Result
channel_impulse_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Int   i;
    D_Ptr priv;
    D_HFMan fm;

    fm = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
    priv = d_task_priv_get(d_app_get_task_handle(fm));
    d_task_priv_set(d_task_self(), priv);

    /*取指定颜色*/
    for (i = 0; i < DRAW_COLOR_CNT + 2; i++)
    {
        draw_pixel[i] = d_vis_map_color (draw_color[i]);
    }

    htimer = d_timer_create (NULL, FLUSH_TIME_IMPLUSE, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, channel_impulse_window_handler);
    }

    vis = d_frame_get_control (frm, ID_IMPULSE_DRAW_BACK);
    if(vis)
    {
        d_vis_set_handler (vis, channel_impulse_draw_handler);
    }

    return D_OK;
}

/** @brief 更新画图区*/
static void
update_scatter_demo_draw(void) D_FUNCPOSTFIT
{
    D_Frame     *frm = &scatter_and_demo_info_window;
    D_Visual    *vis;
    D_U32 time1;

    memset(&signal_info->scatter_and_demo_str, 0, sizeof(signal_info->scatter_and_demo_str));
    signal_info->scatter_and_demo_str.type = D_FEND_DTMB_INFO;
    signal_info->scatter_and_demo_str.Statusinfo = &(signal_info->scatt[0]);

    d_fman_get_advance_status_direct(d_fman_get_handle_by_type(D_FEND_DTMB, 0), &(signal_info->scatter_and_demo_str));
    memcpy(&signal_info->scattinfo, &(signal_info->scatt[0]), sizeof(signal_info->scattinfo));

    vis = d_frame_get_control (frm, ID_SCATT_DRAW_PIC);
    if (vis)
    {
        d_vis_update (vis, NULL);
    }

    vis = d_frame_get_control (frm, ID_SCATT_INFO);
    if (vis)
    {
        d_vis_update (vis, NULL);
    }
}

static void image_spectrum_draw(D_U32 init) D_FUNCPOSTFIT
{
    D_GSurface *gui_surface;
    D_GSurface temp_surf;
    D_Rect dr;
    D_U8 i;

    if(image_spectru == NULL)
    {
        return ;
    }
    gui_surface = d_gui_get_surface();
    d_g_mem_surface_init(&temp_surf, D_GDEV_MODE_32BPP, \
    image_spectru->buf.buf, NULL, image_spectru->buf.width, image_spectru->buf.height, image_spectru->buf.pitch, D_TRUE);

    d_g_lock(gui_surface);

    if(init)
    {
        d_g_set_fg (&temp_surf, d_g_map_color(&temp_surf, 0));
        d_rect_set(&dr, 0, 0, image_spectru->buf.width, image_spectru->buf.height);
        d_g_fill_rect (&temp_surf, &dr);
    }
    else
    {
        for(i = 0; i < 64; i++)
        {
            d_g_set_fg(&temp_surf, draw_pixel[DRAW_WHITE]);
            d_g_point (&temp_surf, 2 + signal_info->scattinfo.scatt[i][0], 2 + (255 - signal_info->scattinfo.scatt[i][1]));
        }
    }

    d_g_unlock(gui_surface);
    d_g_surface_deinit(&temp_surf);
}
/** @brief 画星座图*/
static void DrawScatt(D_Visual *vis) D_FUNCPOSTFIT
{
    D_Rect sr, dr;

    if(signal_info->scatter_and_demo_str.Statusinfolength)
    {
        if(image_spectru == NULL)
        {
            return ;
        }
        image_spectrum_draw(D_FALSE);
        d_rect_set (&dr, (vis->rect.w - image_spectru->buf.width) >> 1, (vis->rect.h - image_spectru->buf.height) >> 1, image_spectru->buf.width, image_spectru->buf.height);
        d_rect_set (&sr, 0, 0, image_spectru->buf.width, image_spectru->buf.height);
        d_vis_set_mode(D_GSURF_DRAW_MODE_ALPHABLEND);
        d_vis_draw_image(vis, &dr, image_spectru, &sr);
    }
}

#if 0
//实时刷新星座图
static void DrawScatt(D_Visual *vis) D_FUNCPOSTFIT
{

    D_U8 i;

    for(i = 0; i < 64; i++)
    {
        d_vis_set_fg (draw_pixel[DRAW_WHITE]);
        d_vis_draw_point(vis,  scattinfo.scatt[i][0], vis->rect.h - scattinfo.scatt[i][1]);
    }

}
#endif
/** @brief 更新解调基本信息数据*/
static void flush_scatt_info(D_Visual* vis)D_FUNCPOSTFIT
{
    D_Char str[20] = {0};

    /*画背景*/
#if 0
    d_vis_set_fg (draw_pixel[DRAW_BLUE]);
    d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
    d_vis_draw_fill_rect (vis, &rect);
#endif

    sprintf(str, "N_pre: %d", signal_info->scattinfo.N_pre);
    signal_draw_text(vis, FRAME_INFO_W, FRAME_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "N_post: %d", signal_info->scattinfo.N_post);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Dly_len_equ: %d", signal_info->scattinfo.Dly_len_equ);
    signal_draw_text(vis, FRAME_INFO_W, FRAME_INFO_Y + 2 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Dly_len_est: %d", signal_info->scattinfo.Dly_len_est);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + 3 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "dif_sum: %.4f", signal_info->scattinfo.diff_sum);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + 4 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "FF_thrld: %.4f", signal_info->scattinfo.FF_thrld);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + 5 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Lock: 0x%x", signal_info->scattinfo.Lock);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + 6 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "PN_Phase: %d", signal_info->scattinfo.PN_Phase);
    signal_draw_text(vis,  FRAME_INFO_W, FRAME_INFO_Y + 7 * FRAME_INFO_String_H, str, d_strlen(str), draw_pixel[DRAW_WHITE]);


    if(signal_info->scattinfo.C == 3780 )
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y  , "C     : 3780 ", d_strlen("C     : 3780 "), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y  , "C     : 1  ", d_strlen("C     : 1  "), draw_pixel[DRAW_WHITE]);
    }

    if(signal_info->scattinfo.QAM == 4)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + FRAME_INFO_String_H , "QAM: 4    ", d_strlen("QAM: 4    "), draw_pixel[DRAW_WHITE]);
    }
    else if(signal_info->scattinfo.QAM == 16)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + FRAME_INFO_String_H , "QAM: 16   ", d_strlen("QAM: 16   "), draw_pixel[DRAW_WHITE]);
    }
    else if(signal_info->scattinfo.QAM == 32)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + FRAME_INFO_String_H , "QAM: 32   ", d_strlen("QAM: 32   "), draw_pixel[DRAW_WHITE]);
    }
    else if(signal_info->scattinfo.QAM == 64)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + FRAME_INFO_String_H , "QAM: 64   ", d_strlen("QAM: 64   "), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + FRAME_INFO_String_H , "QAM: 4-NR ", d_strlen("QAM: 4-NR "), draw_pixel[DRAW_WHITE]);
    }

    if(signal_info->scattinfo.FEC == 2)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + 2 * FRAME_INFO_String_H , "FEC  : 0.8 ", d_strlen("FEC  : 0.8 "), draw_pixel[DRAW_WHITE]);
    }
    else if(signal_info->scattinfo.FEC == 1)
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + 2 * FRAME_INFO_String_H , "FEC  : 0.6 ", d_strlen("FEC  : 0.6 "), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + 2 * FRAME_INFO_String_H , "FEC  : 0.4 ", d_strlen("FEC  : 0.4 "), draw_pixel[DRAW_WHITE]);
    }


    if(signal_info->scattinfo.PN == 945)
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 3 * FRAME_INFO_String_H , "PN   : 945 ", d_strlen("PN   : 945 "), draw_pixel[DRAW_WHITE]);
    }
    else if(signal_info->scattinfo.PN == 595)
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 3 * FRAME_INFO_String_H , "PN   : 595 ", d_strlen("PN   : 595 "), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 3 * FRAME_INFO_String_H , "PN   : 420 ", d_strlen("PN   : 420 "), draw_pixel[DRAW_WHITE]);
    }

    if(signal_info->scattinfo.INTL == 720)
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 4 * FRAME_INFO_String_H , "INTL : 720  ", d_strlen("INTL : 720  "), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 4 * FRAME_INFO_String_H , "INTL : 240  ", d_strlen("INTL : 240  "), draw_pixel[DRAW_WHITE]);
    }

    if(signal_info->scattinfo.Mod == 1)
    {
        signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 5 * FRAME_INFO_String_H , "Mod : Mobile", d_strlen("Mod : Mobile"), draw_pixel[DRAW_WHITE]);
    }
    else
    {
        signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + 5 * FRAME_INFO_String_H , "Mod : Fixed ", d_strlen("Mod : Fixed "), draw_pixel[DRAW_WHITE]);
    }

    sprintf(str, "Agc  : %3d ", (D_U16)signal_info->scattinfo.AGC);
    signal_draw_text(vis,  FRAME_INFO_X, FRAME_INFO_Y + 6 * FRAME_INFO_String_H , str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "C/N  :%2.1fdB", signal_info->scattinfo.CN);
    signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 7 * FRAME_INFO_String_H  , str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "BER  :%3dE-05", (D_U16)signal_info->scattinfo.BER);
    signal_draw_text(vis, FRAME_INFO_X, FRAME_INFO_Y + 8 * FRAME_INFO_String_H  , str, d_strlen(str), draw_pixel[DRAW_WHITE]);
}

/** @brief 事件处理*/
static D_Result
scatter_and_demo_info_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU:
                    signal_test_memory(D_FALSE);
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    signal_test_memory(D_FALSE);
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return d_gui_replace_menu (&channel_spectrum_window);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    return d_gui_replace_menu (&channel_impulse_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    //d_timer_reset(htimer, FLUSH_TIME_SPECTRUM);
                    //update_scatter_demo_draw();
                    return D_OK;
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            update_scatter_demo_draw();
            break;

        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(image_spectru)
            {
                d_image_free(image_spectru);
                image_spectru = NULL;
            }
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 星座和解调事件处理*/
static D_Result
channel_scatter_demo_draw_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_DRAW:
            DrawScatt(vis);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 星座和解调事件处理*/
static D_Result
channel_scatter_demo_info_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch (evt->type)
    {
        case D_EVT_DRAW:
            flush_scatt_info(vis);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 星座图窗口初始化*/
D_Result
scatter_and_demo_info_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual    *vis;
    D_Int i;

    /*取指定颜色*/
    for (i = 0; i < DRAW_COLOR_CNT + 2; i++)
    {
        draw_pixel[i] = d_vis_map_color (draw_color[i]);
    }

    /*临时图片，保存星座图*/
    image_spectru = d_image_new(D_GDEV_MODE_32BPP, 260, 260);
    if(image_spectru == NULL)
    {
        return D_OK;
    }
    image_spectrum_draw(D_TRUE);

    htimer = d_timer_create (NULL, FLUSH_TIME_SCATT, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, scatter_and_demo_info_window_handler);
    }

    vis = d_frame_get_control (frm, ID_SCATT_DRAW_PIC);
    if(vis)
    {
        d_vis_set_handler (vis, channel_scatter_demo_draw_handler);
    }

    vis = d_frame_get_control (frm, ID_SCATT_INFO);
    if(vis)
    {
        d_vis_set_handler (vis, channel_scatter_demo_info_handler);
    }

    return D_OK;
}

/** @brief 更新频谱画图区*/
static void
update_spectrum_draw (void) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_spectrum_window;
    D_Visual    *vis;
    D_U32   time1;
    memset(&signal_info->spectrum_str, 0, sizeof(signal_info->spectrum_str));
    signal_info->spectrum_str.type = D_FEND_DTMB_FREQ_INFO;
    signal_info->spectrum_str.Statusinfo = &(signal_info->Freq[0]);


    d_fman_get_advance_status_direct(d_fman_get_handle_by_type(D_FEND_DTMB, 0), &signal_info->spectrum_str);
    memcpy(&(signal_info->freqinfo.C), (D_U16*) & (signal_info->Freq[0]), sizeof(signal_info->freqinfo.C));
    memcpy(&(signal_info->freqinfo.Freq), (float*) & (signal_info->Freq[4]), sizeof(signal_info->freqinfo.Freq));

    vis = d_frame_get_control (frm, ID_SPECTRUM_DRAW_BACK);
    if (vis)
    {
        d_vis_update (vis, NULL);
    }
}

/** @brief 用于画频谱曲线*/
static void drawfreq(D_Visual *vis)D_FUNCPOSTFIT
{

    D_U32  i, prev = 0, cur = 0;

    d_vis_set_fg (draw_pixel[DRAW_WHITE]);
    d_vis_draw_line(vis,  1,  vis->rect.h - 5 - FRAME_INFO_String_H,  vis->rect.w - 1,  vis->rect.h - 5 - FRAME_INFO_String_H);

    for(i = 0; i < 541; i++)
    {
        cur = signal_info->freqinfo.Freq[i];
        d_vis_draw_line(vis,  i,  vis->rect.h - 5 - prev - FRAME_INFO_String_H,  i,  vis->rect.h - 5 - cur - FRAME_INFO_String_H);
        prev = cur;
    }

}

/** @brief 频谱事件处理*/
static D_Result
channel_spectrum_draw_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i = 0;
    D_Rect  rect = {0};
    switch (evt->type)
    {

        case D_EVT_DRAW:
            /*画背景*/
            d_vis_set_fg (draw_pixel[DRAW_BLUE]);
            d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
            d_vis_draw_fill_rect (vis, &rect);
#if 0
            for(i = 0; i < 20; i++)
            {
                D_DRAW_DUMP("freq[%d] =%f\n", i, freqinfo.Freq[i]);
            }
#endif
            drawfreq(vis);
            break;
#if 0
        case D_EVT_TIMER:
            D_DRAW_DUMP("spectrum_draw time---\n");
            update_spectrum_draw ();
            break;
#endif
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
channel_spectrum_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU:
                    signal_test_memory(D_FALSE);
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    signal_test_memory(D_FALSE);
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return d_gui_replace_menu (&channel_demo_detial_window);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    return d_gui_replace_menu (&scatter_and_demo_info_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            update_spectrum_draw();
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 频谱窗口初始化*/
D_Result
channel_spectrum_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual    *vis;
    D_Int    i;

    /*取指定颜色*/
    for (i = 0; i < DRAW_COLOR_CNT + 2; i++)
    {
        /*取得色彩对应的像素值*/
        draw_pixel[i] = d_vis_map_color (draw_color[i]);
    }

    htimer = d_timer_create (NULL, FLUSH_TIME_SPECTRUM, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, channel_spectrum_window_handler);
    }

    vis = d_frame_get_control (frm, ID_SPECTRUM_DRAW_BACK);
    if(vis)
    {
        d_vis_set_handler (vis, channel_spectrum_draw_handler);
    }

    return D_OK;
}

/** @brief 更新解调详细信息数据*/
static void
update_demo_detial_draw (void) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_demo_detial_window;
    D_Visual    *vis;
    D_U32   time1;
    D_FEndAttr attr;
    D_HFMan hfm;

    hfm = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
    memset(&signal_info->demo_detial_str, 0, sizeof(signal_info->demo_detial_str));
    signal_info->demo_detial_str.type = D_FEND_DTMB_DETAIL_INFO;
    signal_info->demo_detial_str.Statusinfo = &(signal_info->demo_detial[0]);

    d_fman_get_advance_status_direct(hfm, &signal_info->demo_detial_str);

    d_fman_get_dev_attr (hfm, &attr);
    if(attr.demod == demod_3308E_inside)
    {
        memcpy(&signal_info->demo_detial_e_info, &(signal_info->demo_detial[0]), sizeof(signal_info->demo_detial_e_info));
    }
    else
    {
    memcpy(&signal_info->demo_detial_info, &(signal_info->demo_detial[0]), sizeof(signal_info->demo_detial_info));
    }

    vis = d_frame_get_control (frm, ID_DEMO_DETIAL_DRAW_BACK);
    if (vis)
    {
        d_vis_update (vis, NULL);
    }
}


/**@brief显示解调详细信息*/
static D_Result
display_demo_detial_info(D_Visual* vis) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_demo_detial_window;
    D_Char str[40] = {0};
    vis = d_frame_get_control (frm, ID_DEMO_DETIAL_DRAW_BACK);

    sprintf(str, "CFO_Khz: %.3f", signal_info->demo_detial_info.CFO_Khz);
    signal_draw_text(vis, FRAME_DEMO_INFO_X1, FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "SFO(ppm): %.4f", signal_info->demo_detial_info.SFO_ppm);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 2 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "LDPC Iter: %d", signal_info->demo_detial_info.LDPC_Iter);
    signal_draw_text(vis, FRAME_DEMO_INFO_X1,  3 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "NULL Ratio: %2d%%", signal_info->demo_detial_info.NULL_Ratio);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 4 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Pth_max_idx: %d", signal_info->demo_detial_info.Pth_max_idx);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1,  5 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Win_opn_idx: %d", signal_info->demo_detial_info.Win_opn_idx);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1,  6 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Equ_smooth_factor: %d", signal_info->demo_detial_info.Equ_smooth_factor);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 7 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Est_smooth_factor: %d", signal_info->demo_detial_info.Est_smooth_factor);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 8 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_diff_sum: %.4f", signal_info->demo_detial_info.Mod_diff_sum);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 9 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_FF_thrld: %.4f", signal_info->demo_detial_info.Mod_FF_thrld);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 10 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Hn_equ_sum_num: %d", signal_info->demo_detial_info.Hn_equ_sum_num);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 11 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    /*右边*/
    sprintf(str, "Hn_equ_sum_all: %.4f", signal_info->demo_detial_info.Hn_equ_sum_all);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Hn_est_sum_num: %d", signal_info->demo_detial_info.Hn_est_sum_num);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 2 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Hn_est_sum_all: %.4f", signal_info->demo_detial_info.Hn_est_sum_all);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 3 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "CPE_phase: %.4f", signal_info->demo_detial_info.CPE_phase);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 4 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mul_factor_est: %d", signal_info->demo_detial_info.Mul_factor_est);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 5 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mul_factor_equ: %d", signal_info->demo_detial_info.Mul_factor_equ);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 6 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "LLR mean: %.4f", signal_info->demo_detial_info.LLR_mean);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 7 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Datacast_flag: %d", signal_info->demo_detial_info.Datacast_flag);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 8 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Thres_low: %.4f", signal_info->demo_detial_info.Thres_low);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 9 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Thres_high: %d", signal_info->demo_detial_info.Thres_high);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 10 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

}

/**@brief显示解调详细信息*/
static D_Result
display_demo_detial_e_info(D_Visual* vis) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_demo_detial_window;
    D_Char str[40] = {0};
    vis = d_frame_get_control (frm, ID_DEMO_DETIAL_DRAW_BACK);

    sprintf(str, "CFO_Khz: %.3f", signal_info->demo_detial_e_info.CFO_Khz);
    signal_draw_text(vis, FRAME_DEMO_INFO_X1, FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "SFO(ppm): %.4f", signal_info->demo_detial_e_info.SFO_ppm);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 2 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "LDPC Iter: %d", signal_info->demo_detial_e_info.LDPC_Iter);
    signal_draw_text(vis, FRAME_DEMO_INFO_X1,  3 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "NULL Ratio: %2d%%", signal_info->demo_detial_e_info.NULL_Ratio);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 4 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Win_opn_idx: %d", signal_info->demo_detial_e_info.Win_opn_idx);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1,  5 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "PHF_smooth_factor: %d", signal_info->demo_detial_e_info.PNF_smooth_factor);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 6 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "HD_smooth_factor: %d", signal_info->demo_detial_e_info.HD_smooth_factor);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 7 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_diff_sum: %.4f", signal_info->demo_detial_e_info.Mod_diff_sum);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 8 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_HD_1_to_0_SC: %.4f", signal_info->demo_detial_e_info.Mod_HD_1_to_0_SC);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 9 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_HD_1_to_X_SC: %.4f", signal_info->demo_detial_e_info.Mod_HD_0_to_X_SC);
    signal_draw_text(vis,  FRAME_DEMO_INFO_X1, 10 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);
    /*右边*/
    sprintf(str, "Mod_PNF_2_to_1_SC: %.4f", signal_info->demo_detial_e_info.Mod_PNF_2_to_1_SC);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 1 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_HD_1_to_0_MC: %.4f", signal_info->demo_detial_e_info.Mod_HD_1_to_0_MC);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 2 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_HD_1_to_X_MC: %.4f", signal_info->demo_detial_e_info.Mod_HD_0_to_X_MC);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 3 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_PNF_2_to_1_MC: %.4f", signal_info->demo_detial_e_info.Mod_PNF_2_to_1_MC);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 4 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Mod_PNF_1_to_7_ALL: %.4f", signal_info->demo_detial_e_info.Mod_PNF_1_to_7_ALL);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 5 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Datacast_flag: %d", signal_info->demo_detial_e_info.Datacast_flag);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 6 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Thres_low: %.4f", signal_info->demo_detial_e_info.Thres_low);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 7 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

    sprintf(str, "Thres_high: %d", signal_info->demo_detial_e_info.Thres_high);
    signal_draw_text(vis, FRAME_DEMO_INFO_X2, 8 * FRAME_DEMO_INFO_Y, str, d_strlen(str), draw_pixel[DRAW_WHITE]);

}
/** @brief 解调信息事件处理*/
static D_Result
channel_demo_detial_draw_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i = 0;
    D_Rect  rect = {0};
    D_FEndAttr attr;
    switch (evt->type)
    {

        case D_EVT_DRAW:
            /*画背景*/
            d_vis_set_fg (draw_pixel[DRAW_BLUE]);
            d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
            d_vis_draw_fill_rect (vis, &rect);
            d_fman_get_dev_attr (d_fman_get_handle_by_type(D_FEND_DTMB, 0), &attr);
            if(attr.demod == demod_3308E_inside)
            {
                display_demo_detial_e_info(vis);
            }
            else
            {
            display_demo_detial_info(vis);
            }
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 解调信息事件处理*/
static D_Result
channel_demo_detial_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &channel_demo_detial_window;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU://前面板menu键
                    signal_test_memory(D_FALSE);
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    signal_test_memory(D_FALSE);
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return d_gui_replace_menu (&channel_carrier_freq_window);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    return d_gui_replace_menu (&channel_spectrum_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    return D_OK;
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            update_demo_detial_draw();
            break;

        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/**@brief解调详细信息初始化*/
D_Result
channel_demo_detial_window_init(D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_Int            i;

    /*取指定颜色*/
    for (i = 0; i < DRAW_COLOR_CNT + 2; i++)
    {
        /*取得色彩对应的像素值*/
        draw_pixel[i] = d_vis_map_color (draw_color[i]);
    }

    htimer = d_timer_create (NULL, FLUSH_TIME_DEMO_DETIAL, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, channel_demo_detial_window_handler);
    }

    vis = d_frame_get_control (frm, ID_DEMO_DETIAL_DRAW_BACK);
    if(vis)
    {
        d_vis_set_handler (vis, channel_demo_detial_draw_handler);
    }

}

/** @brief 更新频谱画图区*/
static void
update_carrier_freq_draw (void) D_FUNCPOSTFIT
{
    D_Frame     *frm = &channel_carrier_freq_window;
    D_Visual    *vis;
    D_U32   time1;

    memset(&signal_info->carrier_freq_str, 0, sizeof(signal_info->carrier_freq_str));
    signal_info->carrier_freq_str.type = D_FEND_DTMB_CARRIER_FREQ_INFO;
    signal_info->carrier_freq_str.Statusinfo = &(signal_info->carrier_freq[0]);

    d_fman_get_advance_status_direct(d_fman_get_handle_by_type(D_FEND_DTMB, 0), &signal_info->carrier_freq_str);
    memcpy(&(signal_info->carrier_freq_info.C), (D_U16*) & (signal_info->carrier_freq[0]), sizeof(signal_info->carrier_freq_info.C));
    memcpy(&(signal_info->carrier_freq_info.Freq), (float*) & (signal_info->carrier_freq[4]), sizeof(signal_info->carrier_freq_info.Freq));

    vis = d_frame_get_control (frm, ID_CARRIER_FREQ_DRAW_BACK);
    if (vis)
    {
        d_vis_update (vis, NULL);
    }
}

/** @brief 画信道载波频谱*/
static void Draw_Carrier_Freq(D_Visual *vis) D_FUNCPOSTFIT
{

    D_U32  i, prev = 0, cur = 0;
    d_vis_set_fg (draw_pixel[DRAW_WHITE]);
    for(i = 0; i < 555; i++)
    {
        //D_DRAW_DUMP("freq[%d]= %d\n",i,(D_S16)carrier_freq_info.Freq[i]);
        if(signal_info->carrier_freq_info.Freq[i] > 180)
            signal_info->carrier_freq_info.Freq[i] = 180;
        if(signal_info->carrier_freq_info.Freq[i] < -180)
            signal_info->carrier_freq_info.Freq[i] = -180;

        cur = signal_info->carrier_freq_info.Freq[i];
        d_vis_draw_line(vis,  i + 40,  vis->rect.h - prev - 180,  i + 40,  vis->rect.h - cur - 180);
        prev = cur;
    }
}

/** @brief 载波频谱事件处理*/
static D_Result
channel_carrier_freq_draw_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8    i = 0;
    D_Rect  rect = {0};
    D_Char  str_num[10] = {0};
    switch (evt->type)
    {

        case D_EVT_DRAW:
            /*画背景*/
            d_vis_set_fg (draw_pixel[DRAW_BLUE]);
            d_rect_set (&rect, 0, 0, vis->rect.w, vis->rect.h);
            d_vis_draw_fill_rect (vis, &rect);
            d_vis_set_fg (draw_pixel[DRAW_WHITE]);
            d_vis_draw_line(vis,  40,  vis->rect.h - 3,  vis->rect.w,  vis->rect.h - 3);
            d_vis_draw_line(vis,  40,  vis->rect.h - 3,  40,  vis->rect.h - 360);

            sprintf (str_num, "180");
            signal_draw_text (vis, 5, vis->rect.h - 340, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
            sprintf (str_num, "0");
            signal_draw_text (vis, 25, vis->rect.h / 2, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);
            sprintf (str_num, "-180");
            signal_draw_text (vis, 0, vis->rect.h - 5, str_num, d_strlen(str_num), draw_pixel[DRAW_WHITE]);

            /*画信道载波频谱*/
            Draw_Carrier_Freq(vis);
            break;
        default:
            break;
    }

    return D_OK;
}


/** @brief 载波频谱事件处理*/
static D_Result
channel_carrier_freq_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &channel_carrier_freq_window;
    D_Visual    *draw_vis;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU://前面板menu键
                    signal_test_memory(D_FALSE);
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    signal_test_memory(D_FALSE);
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return d_gui_replace_menu (&channel_impulse_window);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    return d_gui_replace_menu (&channel_demo_detial_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    return D_OK;
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            update_carrier_freq_draw();
            break;

        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/**@brief载波频率初始化*/
D_Result
channel_carrier_freq_window_init(D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_Int             i;

    /*取指定颜色*/
    for (i = 0; i < DRAW_COLOR_CNT + 2; i++)
    {
        /*取得色彩对应的像素值*/
        draw_pixel[i] = d_vis_map_color (draw_color[i]);
    }

    htimer = d_timer_create (NULL, FLUSH_TIME_CARRIER_FREQ, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, channel_carrier_freq_window_handler);
    }

    vis = d_frame_get_control (frm, ID_CARRIER_FREQ_DRAW_BACK);
    if(vis)
    {
        d_vis_set_handler (vis, channel_carrier_freq_draw_handler);
    }

}

/** @breif 显示信道冲击响应信息*/
D_Result
p_atv_chan_impulse_show (void) D_FUNCPOSTFIT
{
    signal_test_memory(D_TRUE);
    if(signal_info == NULL)
    {
        return D_ERR;
    }
    return d_gui_enter_menu (&channel_impulse_window, D_TRUE);
}

