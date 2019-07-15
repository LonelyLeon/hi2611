/**@defgroup sn-burn 序列号烧写模块
*@{*/
/** @file
* @brief 序列号烧写模块
* @author 刘伟峰
* @date 2013-08-20 刘伟峰: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include "dSerial.h"
#include "pConfig.h"
#include "pMem.h"
#include "dGraph.h"
#include "dGDev.h"
#include "dSys.h"
#include "dTask.h"
#include "dApp.h"
#include "dMsg.h"
#include "dTimer.h"
#include "dResource.h"
#include "dDebug.h"
#include "pPopMsg.h"
//#include "Hrca_dmux.h"
#include "dDsc.h"
#include "pBurnSerialNumber.h"
#include "pStbFunctions.h"
#include "pPlayer.h"
#include "ptvConfig.h"
#include "pFp.h"
#include "pStb.h"
#include "dDisk.h"


#define SCAN_REPEAT_CNT 30
#define SERIAL_BUF_LENGTH 60

#if (SERIAL_BUF_LENGTH < D_CONF_DEF_STB_ID_LEN)
#undef SERIAL_BUF_LENGTH
#define SERIAL_BUF_LENGTH D_CONF_DEF_STB_ID_LEN
#endif

#define RECEIVE_DATA_SERIAL_NUM_SIZE    18//22//D_CONF_DEF_STB_ID_LEN
#define SEND_DATA_CHIP_ID_SIZE          (8 + 4)
#define SEND_DATA_CA_ID_SIZE            (16 + 4)
#define UART_CMD_LENGTH                 1
#define READ_TIMEOUT_TICK           100
/*机顶盒操作结果定义*/
#define CMD_SEND_CHIPID     0x01
#define CMD_GET_STB         0x05
#define CMD_SEND_CAID       0x06

#define RESULT_OK   0x11
#define RESULT_CMD_FAIL 0x12
#define RESULT_TIMEOUT  0x15
//#define WYG_GAMMA_SET         //added by wangyg on 2015-09-03

typedef enum
{
    SEND_CHIPID,
    SEND_CAID,
    CMD_GET_STB_SN,
    GET_STB_SN_DATA,
} SnBurnStep;

typedef struct
{
    D_U8* buf_rciv; //用于从串口接收数据的buffer
    D_U8* buf_bkup; //用于处理数据的备份buffer
    D_U32 buf_len;  //buffer的长度
    //D_LoaderParam loaderparam; //当序列号存放在loader参数中时使用
    SnBurnStep step;    //记录通信进行的步骤
    D_U8 rev_cnt;
} SerialParam;

#define COMMAND_HEAD    0x55
#define COMMAND_TAIL    0xfe
#define FACTORY_API_OK 0
#define FACTORY_API_Error -1
#define FACTORY_API_NoSupport -3

typedef enum
{
    SET_WB_MODE = 0x1,
    SET_COLOR_TEMP, // 0x2
    GET_COLOR_TEMP,     // 0x3

    SET_USR_R_OFF,      // 0x4
    SET_USR_G_OFF,      // 0x5
    SET_USR_B_OFF,      // 0x6

    GET_USR_R_OFF,      // 0x7
    GET_USR_G_OFF,      // 0x8
    GET_USR_B_OFF,      // 0x9

    SET_USR_R_GAN,      //0xa
    SET_USR_G_GAN,      //0xb
    SET_USR_B_GAN,      //0xc

    GET_USR_R_GAN,      //0xd
    GET_USR_G_GAN,  //0xe
    GET_USR_B_GAN,      //0xf
    COPY_ALL = 0x16,
    SET_AUTO_ADC = 0x17,
    SET_RCU_KEY = 0x1d,
    DO_TST_USB_PORT = 0x22,
    SET_SCREEN_WHITE = 0x23,
    FACTORY_RESET_BOE = 0x25,
    FACTORY_RESET_CTV = 0x26,
    FACTORY_RESET_OK = 0x27,
    GET_SYS_FW_VER = 0x29,
    SET_INPUT_SRC = 0x2e,
    GET_INPUT_SRC = 0x2f,
    SET_PICTUREMODE = 0x35,
    GET_PICTUREMODE = 0x36,
    SET_BRGHTNSS = 0x37,
    GET_BRGHTNSS = 0x38,
    SET_CONTRAST = 0x39,
    GET_CONTRAST = 0x3a,
    SET_BACKLIGHT = 0x3b,
    GET_BACKLIGHT = 0x3c,
    SET_VOLUME = 0x49,
    SET_MUTE = 0x4b,
    SET_CHANNEL = 0x4c,
    SET_DISPLAYMODE = 0x59,
    GET_DISPLAYMODE = 0x5a,
    GET_IP_ADDRESS = 0x79,
    FAC_PERSET_CHANNEL = 0x8e,
    SET_KEY_LOCK = 0xcb,
    SET_MAC_ADDRESS = 0xd7,
    GET_MAC_ADDRESS = 0xd8,
    GET_KEYPAD_ADC = 0xdb,
#ifdef WYG_GAMMA_SET
    SET_USR_GAMMA_R = 0xd9,
    SET_USR_GAMMA_G = 0xda,
    SET_USR_GAMMA_B = 0xdb,

    GET_USR_GAMMA_R = 0xdc,
    GET_USR_GAMMA_G = 0xdd,
    GET_USR_GAMMA_B = 0xde,
#endif

} Command_Type;

static SerialParam *serial_data = NULL; //处理串口时使用的buffer
static D_U8 gCommand_buf[SERIAL_BUF_LENGTH];
static D_U8 gCom_crc = 0x00;
static D_U8 gSet_type;
static D_HSerial Serial_Handle;

static D_U8 uart_ack_buf[26];
static D_U8 OK_ack[] = { 0x55, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xFE,};
static D_U8 Error_ack[] = { 0x55, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0xFE,};
static D_U8 ChecksumError_ack[] = { 0x55, 0xB1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F, 0xFE,};
static D_U8 ColorTemp[] = { 0x55, 0xB2, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE,};
static D_U8 ACK[] = { 0x55, 0xB2, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,};
static D_U8 GAMMA_R[] = { 0x55, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,};
static D_U8 GAMMA_G[] = { 0x55, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,};
static D_U8 GAMMA_B[] = { 0x55, 0xDE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,};
static D_U8 IRKEY[] = { 0x55, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xFE,};

#ifdef D_BURN_SN_MODE_B

static D_Result
ctv_reset_factory_setting(void) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_LoaderParam loader_param;
    D_VidInput input;
    D_U8 debug_en, logo_mode;

    player = p_stb_get_player(0);
    input = p_conf_get_vid_input();
    if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
    {
        /*停止所有播放*/
        d_stb_stop_play ();
    }

    d_sys_stand_by();

    /*关闭窗体*/
    d_gui_clear_menu ();
    d_gui_clear_layer (D_GUI_LAYER_VIDEO_OSD);
    d_gui_clear_layer (D_GUI_LAYER_MESSAGE);

    /*关闭GUI显示*/
    d_gui_show (D_FALSE);
    /*停止所有播放*/
    d_stb_stop_play ();

    d_dbase_set_rset_en(0);
    d_dbase_clear_srv ();
    d_dbase_clear_evt ();
    d_dbase_clear_ts ();
    d_dbase_clear_net ();
    //d_dbase_clear_nvod ();
    d_dbase_clear_bouq ();
    d_dbase_clear_subscribe ();
    //d_dbase_rset_add_ts();

    p_conf_restore(D_FALSE);
    p_tvconf_restore(D_FALSE);

    /*刷新数据库*/
    d_dbase_flush();

    //powermode模式恢复为开
    if(p_conf_get_loader_param(&loader_param) == D_OK)
    {
        loader_param.reserved2 = 1;
        p_conf_set_loader_param(&loader_param);
    }
    /* 工厂复位时，将调试模式关闭*/
    debug_en = 1;
    p_tvconf_set_debug_en(debug_en);
    logo_mode = 0;
    p_tvconf_set_logomode (&logo_mode);

    p_precast_program(0);//预制BOE的节目
    return D_OK;
}

static D_Result
boe_reset_factory_setting(void) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_LoaderParam loader_param;
    D_VidInput input;
    D_U8 debug_en, logo_mode;

    player = p_stb_get_player(0);
    input = p_conf_get_vid_input();
    if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
    {
        /*停止所有播放*/
        d_stb_stop_play ();
    }

    d_sys_stand_by();

    /*关闭窗体*/
    d_gui_clear_menu ();
    d_gui_clear_layer (D_GUI_LAYER_VIDEO_OSD);
    d_gui_clear_layer (D_GUI_LAYER_MESSAGE);

    /*关闭GUI显示*/
    d_gui_show (D_FALSE);
    /*停止所有播放*/
    d_stb_stop_play ();

    d_dbase_set_rset_en(0);
    d_dbase_clear_srv ();
    d_dbase_clear_evt ();
    d_dbase_clear_ts ();
    d_dbase_clear_net ();
    //d_dbase_clear_nvod ();
    d_dbase_clear_bouq ();
    d_dbase_clear_subscribe ();
    //d_dbase_rset_add_ts();

    p_conf_restore(D_FALSE);
    p_tvconf_restore(D_FALSE);

    /*刷新数据库*/
    d_dbase_flush();

    //powermode模式恢复为开
    if(p_conf_get_loader_param(&loader_param) == D_OK)
    {
        loader_param.reserved2 = 0;
        p_conf_set_loader_param(&loader_param);
    }
    /* 工厂复位时，将调试模式关闭*/
    debug_en = 0;
    p_tvconf_set_debug_en(debug_en);
    logo_mode = 1;
    p_tvconf_set_logomode (&logo_mode);

    return D_OK;
}

static D_U8 GetCurSourceType(void)D_FUNCPOSTFIT
{
    D_VidInput input;
    D_U8 ret = 0xff;
    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_TV:
            ret = 0x1;
            break;
        case D_VID_IUTPUT_DTV:
            ret = 0x2;
            break;
        case D_VID_IUTPUT_AV1:
            ret = 0x3;
            break;
        case D_VID_IUTPUT_AV2:
            ret = 0x4;
            break;
        case D_VID_IUTPUT_YPBPR:
            ret = 0x9;
            break;
        case D_VID_IUTPUT_HDMI1:
            ret = 0x7;
            break;
        case D_VID_IUTPUT_HDMI2:
            ret = 0x8;
            break;

#ifdef D_TV_LIULINK_SOURCE
        case D_VID_IUTPUT_LIULINK:
#endif
        case D_VID_IUTPUT_USB1:
            ret = 0xa;
            break;
        default:
            ret = 0xff;
            break;
    }
    return ret;
}

/** @brief 初始化烧写序列号所需要的资源
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
static D_Result sn_burn_init(void) D_FUNCPOSTFIT
{
    serial_data = (SerialParam*)PROJECT_ALLOC(sizeof(SerialParam));
    if(!serial_data)
    {
        return D_ERR;
    }
    memset(serial_data, 0, sizeof(SerialParam));
    serial_data->buf_len = SERIAL_BUF_LENGTH;

    serial_data->buf_rciv = (D_U8*)PROJECT_ALLOC(serial_data->buf_len);
    if(!serial_data->buf_rciv)
    {
        PROJECT_FREE(serial_data);
        return D_ERR;
    }

    serial_data->buf_bkup = (D_U8*)PROJECT_ALLOC(serial_data->buf_len);
    if(!serial_data->buf_bkup)
    {
        PROJECT_FREE(serial_data->buf_rciv);
        PROJECT_FREE(serial_data);
        return D_ERR;
    }
    d_dbg_set_io_func(NULL, NULL);
    serial_data->step = SEND_CHIPID;

    return D_OK;
}

static void return_result2tools_set(D_Result ret)
{
    if(ret == FACTORY_API_OK)
    {
        d_serial_flush(Serial_Handle);
        d_serial_write(Serial_Handle, OK_ack, 12);
    }
    else if(ret == FACTORY_API_Error)
    {
        d_serial_flush(Serial_Handle);
        d_serial_write(Serial_Handle, Error_ack, 12);
    }
    else //(ret == FACTORY_API_NoSupport)
    {
        d_serial_flush(Serial_Handle);
        d_serial_write(Serial_Handle, Error_ack, 12);
    }
}

static void return_result2tools_get(D_U8* pData)
{
    D_U8 i;
    D_U8 checksum = 0;

    uart_ack_buf[0] = pData[0];
    for(i = 1; i < 10; i++)
    {
        uart_ack_buf[i] = pData[i];
        checksum += uart_ack_buf[i];
    }
    checksum ^= 0xFF;
    checksum += 0x01;
    uart_ack_buf[10] = checksum;
    uart_ack_buf[11] = 0xFE;//pData[11];
    d_serial_flush(Serial_Handle);
    d_serial_write(Serial_Handle, uart_ack_buf, 12);
}

D_S32 SetWB_GammaMode(D_S32 nValue)
{
#if 0
    switch(nValue)
    {
        case 0:
            break;
        case 2:
            break;
        case 6:
        case 9:
            break;
        default:
            return FACTORY_API_Error;
    }

#endif
    return FACTORY_API_Error;

}

D_S32 SetColorTemp(D_S32 nValue)
{
    D_U8 color_mode;
    D_U8 hdflag;
    D_VidInput input = p_conf_get_vid_input();

    if(nValue > 3)
        return FACTORY_API_Error;
    switch(nValue)
    {
        case 1:
            color_mode = 1;
            break;
        case 2:
            color_mode = 0;
            break;
        case 3:
            color_mode = 2;
            break;
    }
    hdflag = p_vip_get_ntscflag();
    if(hdflag)
    {
        p_vip_set_Temperature(input, color_mode, 1);
    }
    else
    {
        p_vip_set_Temperature(input, color_mode, 0);
    }
    p_tvconf_set_cur_colormode(&color_mode, p_vip_get_dbinput(input));

    return FACTORY_API_OK;

}

D_S32 GetColorTemp(D_S32 *nValue)
{
    D_U8 color_mode;
    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&color_mode, p_vip_get_dbinput(input));
    switch(color_mode)
    {
        case 0:
            *nValue = 2;
            return FACTORY_API_OK;
        case 1:
            *nValue = 1;
            return FACTORY_API_OK;
        case 2:
            *nValue = 3;
            return FACTORY_API_OK;
    }
    return FACTORY_API_Error;
}

D_S32 SetRedOffset(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.roffset = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 SetRGBOffset(D_S32 nR, D_S32 nG, D_S32 nB)
{

    return FACTORY_API_Error;

}

D_S32 SetGreenOffset(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.goffset = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 SetBlueOffset(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.boffset = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);

            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 GetRedOffset(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.roffset;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}
D_S32 GetGreenOffset(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.goffset;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}
D_S32 GetBlueOffset(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.boffset;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}

D_S32 SetRedGain(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.rgain = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 SetGreenGain(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.ggain = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);

            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 SetBlueGain(D_S32 nValue)
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_S16 temperature;
    D_U8 hdflag;

    D_VidInput input = p_conf_get_vid_input();
    hdflag = p_vip_get_ntscflag();

    if(nValue >= 0 && nValue <= 255)
    {
        p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

        if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
        {
            tparam.bgain = nValue;
            if(hdflag)
            {
                if(p_tvconf_get_hdcsc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            else
            {
                if(p_tvconf_get_csc_set_param(&cscparam, p_vip_get_dbinput(input)) == D_OK)
                {
                    d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
                }
            }
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;

}

D_S32 SetRGBGain(D_S32 nR, D_S32 nG, D_S32 nB)
{
    return FACTORY_API_Error;
}

D_S32 SetKeyLock(D_U8 lock)
{
    if(lock)
        p_fp_set_enable(D_FALSE);
    else
        p_fp_set_enable(D_TRUE);

    return FACTORY_API_OK;
}

D_S32 GetRedGain(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.rgain;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}
D_S32 GetGreenGain(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.ggain;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}
D_S32 GetBlueGain(D_S32 *nValue)
{
    D_CTEMP_SET tparam;
    D_U8 temperature;

    D_VidInput input = p_conf_get_vid_input();

    p_tvconf_get_cur_colormode(&temperature, p_vip_get_dbinput(input));

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), temperature) == D_OK)
    {
        *nValue = tparam.bgain;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;

}

D_S32 Set_copy_all(void)
{
    D_CTEMP_SET tparam;
    D_U8 i;
    D_VidInput input = p_conf_get_vid_input();

    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), 0) == D_OK)
    {
        for(i = 0; i < D_VID_IUTPUT_MAX; i++)
        {
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(i), 0);
        }
    }
    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), 1) == D_OK)
    {
        for(i = 0; i < D_VID_IUTPUT_MAX; i++)
        {
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(i), 1);
        }
    }
    if(p_tvconf_get_ctemp_param(&tparam, p_vip_get_dbinput(input), 2) == D_OK)
    {
        for(i = 0; i < D_VID_IUTPUT_MAX; i++)
        {
            p_tvconf_set_ctemp_param(&tparam, p_vip_get_dbinput(i), 2);
        }
    }

    return FACTORY_API_OK;
}

static D_S32 Set_auto_adc(void)
{
    D_ADC_SET param;
    D_U8 hdflag;
    D_COMP_SET comp_param;
    D_COMP_SET hdcomp_param;
    D_COMP_SET temp_comp_param;
    D_VidInput input = p_conf_get_vid_input();

    if(input != D_VID_IUTPUT_YPBPR)
        return FACTORY_API_Error;
    p_tvconf_get_comp_set_param(&comp_param, p_vip_get_dbinput(input));
    p_tvconf_get_hdcomb_set_param(&hdcomp_param, p_vip_get_dbinput(input));
    if(d_vip_AutoADC(&param, &temp_comp_param) == D_TRUE)
    {
        p_tvconf_set_hdadc_set_param(&param, p_vip_get_dbinput(input));
        p_tvconf_set_adc_set_param(&param, p_vip_get_dbinput(input));

        comp_param.comp_gain_r = temp_comp_param.comp_gain_r;
        comp_param.comp_gain_g = temp_comp_param.comp_gain_g;
        comp_param.comp_gain_b = temp_comp_param.comp_gain_b;
        comp_param.comp_vclamplevel_r = temp_comp_param.comp_vclamplevel_r;
        comp_param.comp_vclamplevel_g = temp_comp_param.comp_vclamplevel_g;
        comp_param.comp_vclamplevel_b = temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_comp_set_param(&comp_param, p_vip_get_dbinput(input));

        hdcomp_param.comp_gain_r = temp_comp_param.comp_gain_r;
        hdcomp_param.comp_gain_g = temp_comp_param.comp_gain_g;
        hdcomp_param.comp_gain_b = temp_comp_param.comp_gain_b;
        hdcomp_param.comp_vclamplevel_r = temp_comp_param.comp_vclamplevel_r;
        hdcomp_param.comp_vclamplevel_g = temp_comp_param.comp_vclamplevel_g;
        hdcomp_param.comp_vclamplevel_b = temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_hdcomb_set_param(&hdcomp_param, p_vip_get_dbinput(input));
        return FACTORY_API_OK;
    }
    else
    {
        return FACTORY_API_Error;
    }
}

D_S32 SetRCU_Key(D_S32 nValue)
{
    return FACTORY_API_NoSupport;
}

#ifdef WYG_GAMMA_SET        // added by wangyg on 2015-09-03

D_S32 SetRedGamma(D_U8 nIdx, D_U16 nValue)
{
    if(nValue >= 0 && nValue <= 1023)
    {
        d_vip_setGamma_Table(0, nIdx, nValue);

        return FACTORY_API_OK;
    }
    else
        return FACTORY_API_Error;
}

D_S32 SetGreenGamma(D_U8 nIdx, D_U16 nValue)
{
    if(nValue >= 0 && nValue <= 1023)
    {
        d_vip_setGamma_Table(1, nIdx, nValue);

        return FACTORY_API_OK;
    }
    else
        return FACTORY_API_Error;
}

D_S32 SetBlueGamma(D_U8 nIdx, D_U16 nValue)
{
    if(nValue >= 0 && nValue <= 1023)
    {
        d_vip_setGamma_Table(2, nIdx, nValue);

        return FACTORY_API_OK;
    }
    else
        return FACTORY_API_Error;
}

D_S32 GetRedGamma(D_U8 nIdx, D_U16 *nValue)
{
    *nValue = d_vip_getGamma_Table(0, nIdx);

    return FACTORY_API_OK;
}

D_S32 GetGreenGamma(D_U8 nIdx, D_U16 *nValue)
{
    *nValue = d_vip_getGamma_Table(1, nIdx);

    return FACTORY_API_OK;
}

D_S32 GetBlueGamma(D_U8 nIdx, D_U16 *nValue)
{
    *nValue = d_vip_getGamma_Table(2, nIdx);

    return FACTORY_API_OK;
}
#endif
D_S32 DoUsbTest(D_S32 nValue1, D_S32 *nValue2)
{
    D_S32 status;
#if 0
    int entries = 0;
    char path[20];
    struct dirent **namelist;
    snprintf(path, 20, "%s%c%d", "/mnt/udisk/sd", 'a' + nValue1, 1);
//  printf("USB Test:    %s=\n", path);
    if((entries = scandir(path, &namelist, 0, alphasort)) < 0)
    {
//      printf("USB Test Fail:port %d no connected USB\n", nValue1);
        *nValue2 = 0;
    }
    else
        *nValue2 = 1;
#endif
    status = d_disk_check_connect();
    *nValue2 = status;
    return FACTORY_API_OK;
}

D_S32 SetSrceenWhite(D_S32 nValue)
{
    return FACTORY_API_NoSupport;
}

D_S32 GetFirmwareVersion(D_U8 *szValue)
{
#if 0
    char *sTmp;//[260];
    //write(fd, sTmp, 13);
    //SetupFunctions::getInstance()->getSystemVersion(sTmp);
    //sTmp = GetApVersion();
    sTmp = GetSvnVersionWis(); //
    //write(fd, sTmp, 20);
    /*if(strncmp(sTmp, "Revision: ", 10) == 0)
        {memcpy(szValue, sTmp + 10, (strlen(sTmp) - 10));write(fd, sTmp, 17);}
    else
        {return FACTORY_API_Error;write(fd, sTmp, 17);}*/
    int i = 10, j = 3, len = 1;
    while(sTmp[i])
    {
        szValue[j++] = sTmp[i++];
        szValue[2] = len++;
    }
#endif
    return FACTORY_API_NoSupport;
}

static void send_msg_to_gui(D_U8 temp) D_FUNCPOSTFIT
{
    D_UserMsg msg;
    msg.type = D_MSG_USER1;
    msg.handle = -1;
    msg.param1 = USER_MSG_PARAM1_RS232_CHANGEINPUT;
    msg.param2 = temp;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}
/***************************************************************
*userInput:
*   0->SOURCE_ATV1      1->SOURCE_AV1       2->SOURCE_AV2       3->SOURCE_YPP1
*   4->SOURCE_VGA1      5->SOURCE_HDMI1 6->SOURCE_DTV1
*
*Transform
*   SOURCE_ATV1->1      SOURCE_AV1->5       SOURCE_AV2->6       SOURCE_YPP1->10
*   SOURCE_VGA1->14 SOURCE_HDMI1->16    SOURCE_DTV1->3
*
*SOURCE-IDTV1->27  :
*   SOURCE-IDTV1 include SOURCE_ATV1 and SOURCE_DTV1, so it need to set subSource.
*
****************************************************************/
D_S32 SetInputSource(D_S32 nValue)
{
    switch(nValue)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 9:
        case 7:
        case 8:
        case 10:
        {
            send_msg_to_gui(nValue);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;
}

D_S32 SetBrghtnss(D_S32 nValue)
{
    D_PCURVE_SET param;
    D_U8 video_mode;
    D_PMODE_SET tparam;

    D_VidInput input = p_conf_get_vid_input();
    if(nValue >= 0 && nValue <= 255)
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input))  == D_OK)
        {
            if(p_tvconf_get_pmodeset_param(&tparam,  p_vip_get_dbinput(input), video_mode) == D_OK)
            {
                tparam.brightness = nValue;
                if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 0) == D_OK)
                {
                    d_vip_setBrightness(tparam.brightness, (D_U8*)&param);
                }
                p_tvconf_set_pmodeset_param(&tparam,  p_vip_get_dbinput(input), video_mode);
                return FACTORY_API_OK;
            }
        }
    }
    return FACTORY_API_Error;
}

D_S32 GetBrghtnss(D_S32 *nValue)
{
    D_U8 video_mode;
    D_PMODE_SET tparam;

    D_VidInput input = p_conf_get_vid_input();
    if(p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input))  == D_OK)
    {
        if(p_tvconf_get_pmodeset_param(&tparam, p_vip_get_dbinput(input), video_mode) == D_OK)
        {
            *nValue = tparam.brightness;
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;
}

D_S32 SetContrast(D_S32 nValue)
{
    D_PCURVE_SET param;
    D_U8 video_mode;
    D_PMODE_SET tparam;

    D_VidInput input = p_conf_get_vid_input();
    if(nValue >= 0 && nValue <= 255)
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input))  == D_OK)
        {
            if(p_tvconf_get_pmodeset_param(&tparam,  p_vip_get_dbinput(input), video_mode) == D_OK)
            {
                tparam.contrast = nValue;
                if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 1) == D_OK)
                {
                    d_vip_setConstrast(tparam.contrast, (D_U8*)&param);
                }
                p_tvconf_set_pmodeset_param(&tparam,  p_vip_get_dbinput(input), video_mode);
                return FACTORY_API_OK;
            }
        }
    }
    return FACTORY_API_Error;
}

D_S32 GetContrast(D_S32 *nValue)
{
    D_U8 video_mode;
    D_PMODE_SET tparam;

    D_VidInput input = p_conf_get_vid_input();
    if(nValue >= 0 && nValue <= 255)
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input))  == D_OK)
        {
            if(p_tvconf_get_pmodeset_param(&tparam, p_vip_get_dbinput(input), video_mode) == D_OK)
            {
                *nValue = tparam.contrast;
                return FACTORY_API_OK;
            }
        }
    }
    return FACTORY_API_Error;
}

D_S32 SetBacklight(D_S32 nValue)
{
    D_U8 backlight;
    D_BLDIM_SET param;
    D_VidInput input = p_conf_get_vid_input();
    if(nValue >= 0 && nValue <= 100)
    {
        p_tvconf_get_bldim_set_param(&param, p_vip_get_dbinput(input));
        d_vip_setBldim(&param, nValue);

        return FACTORY_API_OK;
    }

    return FACTORY_API_Error;
}

D_S32 GetBacklight(D_S32 *nValue)
{
    D_U8 backlight;
    D_VidInput input = p_conf_get_vid_input();

    if(p_tvconf_get_bldim_backlight(&backlight, p_vip_get_dbinput(input)) == D_OK)
    {
        *nValue = backlight;
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;
}

D_S32 SetPictureMode(D_S32 nValue)
{
    D_U8 video_mode;
    D_PMODE_SET tparam;
    D_U8 ntscflag;

    D_VidInput input = p_conf_get_vid_input();
    ntscflag = p_vip_get_ntscflag();
    if(nValue >= 0 && nValue <= TV_IMAGE_MODE_MAX)
    {
        switch(nValue)
        {
            case 0:
            {
                video_mode = 0;
                break;
            }
            case 1:
            {
                video_mode = 3;
                break;
            }
            case 2:
            {
                video_mode = 1;
                break;
            }
            case 3:
            {
                video_mode = 2;
                break;
            }
            default:
            {
                return FACTORY_API_Error;
            }
        }
        if(p_tvconf_get_pmodeset_param(&tparam, p_vip_get_dbinput(input), video_mode) == D_OK)
        {
            D_PCURVE_SET  param;
            if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 0) == D_OK)
            {
                d_vip_setBrightness(tparam.brightness, (D_U8*)&param);
            }
            if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 1) == D_OK)
            {
                d_vip_setConstrast(tparam.contrast, (D_U8*)&param);
            }
            if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 2) == D_OK)
            {
                d_vip_setSaturation(tparam.color, (D_U8*)&param);
            }
            if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 3) == D_OK)
            {
                if(ntscflag)
                {
                    d_vip_setHue(tparam.tint, (D_U8*)&param);
                }
                else
                {
                    d_vip_setHue(50, (D_U8*)&param);
                }
            }
            if(p_tvconf_get_pcurve_param(&param, p_vip_get_dbinput(input), 4) == D_OK)
            {
                d_vip_setSharpness(tparam.sharpness, (D_U8*)&param);
            }
            p_tvconf_set_pmodeset_param(&tparam, p_vip_get_dbinput(input), video_mode);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;
}

D_S32 GetPictureMode(D_S32 *nValue)
{
    D_U8 video_mode;
    D_VidInput input = p_conf_get_vid_input();

    if(p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input))  == D_OK)
    {
        switch(video_mode)
        {
            case 0:
            {
                *nValue = 0;
                break;
            }
            case 1:
            {
                *nValue = 3;
                break;
            }
            case 2:
            {
                *nValue = 1;
                break;
            }
            case 3:
            {
                *nValue = 2;
                break;
            }
            default:
            {
                return FACTORY_API_Error;
            }
        }
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;
}

D_S32 SetMute(D_S32 nValue)
{
    if(nValue <= 1)
    {
        d_av_set_aud_mute (0, nValue);
        p_conf_set_aud_mute (nValue);
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;
}

D_S32 FactoryReset_boe(D_S32 nValue)
{
    boe_reset_factory_setting();
    return FACTORY_API_OK;
}
D_S32 FactoryReset(D_S32 nValue)
{
    ctv_reset_factory_setting();
    return FACTORY_API_OK;
}

D_S32 GetInputSource(D_S32 *nValue)
{
    D_U8 ret;
    //*nValue = GetCurSourceType();//SetupClass::GetInstance()->GetSource();
    ret = GetCurSourceType();
    *nValue = ret;
    return FACTORY_API_OK;
}

D_S32 SetSoundVolume(D_S32 nValue)
{
    //SetupClass::GetInstance()->SetVolume(nValue);
    //SetAudioVolume(nValue);
    if(nValue <= 100)
    {
        p_conf_set_volume((D_U8)nValue);
        d_av_set_volume (0, (D_U8)nValue);
    }
    return FACTORY_API_OK;
}

D_S32 SetTVChannel(D_S32 nValue1, D_S32 nValue2)
{
    D_S16   num = 0;
    D_DBSrvID db_srv_id = -1;
    D_StbPlayer  *player;
    D_VidInput input;

    input = p_conf_get_vid_input ();
    if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
    {
        num = nValue1 * 10 + nValue2;

        player = p_stb_get_player (0);
        if (! player)
        {
            return FACTORY_API_Error;
        }

        if (player->play_srv)
        {
            db_srv_id = d_dbase_get_srv_by_num(num, D_DB_SRV_TV);
        }
        else if (player->play_atv)
        {
            db_srv_id = d_dbase_get_srv_by_num(num, D_DB_SRV_ATV);
        }
        else if (! player->play_radio)
        {
            db_srv_id = d_dbase_get_srv_by_num(num, D_DB_SRV_TV);
        }
        else
        {
            db_srv_id = d_dbase_get_srv_by_num(num, D_DB_SRV_RADIO);
        }

        if (db_srv_id != -1)
        {
            p_stb_player_play_srv(0, db_srv_id);
            return FACTORY_API_OK;
        }
    }
    return FACTORY_API_Error;
}

D_S32 SetFacPersetCH(D_S32 nValue)
{
    D_VidInput input;
    if(nValue < 2)
    {
        p_precast_program(nValue);

        input = p_conf_get_vid_input ();
        if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
        {
            p_stb_player_play_valid (0);
        }
        return FACTORY_API_OK;
    }
    return FACTORY_API_Error;
}

D_S32 GetFacPersetCH(D_S32 *nValue)
{
    return FACTORY_API_Error;
}

D_S32 Set_DisplayMode(D_S32 nValue)
{
    return FACTORY_API_Error;
}

D_S32 Get_DisplayMode(D_S32 *nValue)
{
    return FACTORY_API_Error;
}

D_S32 Get_IRKEY(D_U8 *nValue)
{
    D_KeyCode temp;
    *nValue = 0;
    temp = p_fp_get_curr_key(0);
    switch(temp)
    {
        case D_KEY_PNL_MENU:
            *nValue = 1;
            break;

        case D_KEY_PNL_D:
            *nValue = 2;
            break;
        case D_KEY_PNL_U:
            *nValue = 3;
            break;
        case D_KEY_PNL_L:
            *nValue = 4;
            break;
        case D_KEY_PNL_R:
            *nValue = 5;
            break;
        case D_KEY_PNL_SOURCE:
        case D_KEY_PNL_POWER:
            *nValue = 6;
            break;

    }
    return FACTORY_API_OK;
}

static void set_tv_parameter(D_U8 *cmd_buf)
{
    D_Result ret;

    switch(cmd_buf[1])
    {
        case SET_WB_MODE:
        {
            return_result2tools_set(SetWB_GammaMode(cmd_buf[3]));
        }
        break;

        case SET_COLOR_TEMP:
        {
            return_result2tools_set(SetColorTemp(cmd_buf[3]));
        }
        break;

        case GET_COLOR_TEMP:
        {
#if 0
            D_S32 color_temp;
            GetColorTemp(&color_temp);
            ColorTemp[3] = (char)(color_temp);
            return_result2tools_get(ColorTemp);
#else
            D_S32 color_temp;
            GetColorTemp(&color_temp);
            ColorTemp[2] = 0x01;
            ColorTemp[3] = (char)color_temp;
            return_result2tools_get(ColorTemp);
#endif
        }
        break;

        case SET_USR_R_OFF:
        {
            D_S32   input_R, input_G, input_B;
            if( cmd_buf[2] == 0x06 ) //SET_USR_RGB_GAIN_OFFSET
            {
                input_R = ((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4];
                input_G = ((D_U16)(cmd_buf[5]) << 8) | cmd_buf[6];
                input_B =  ((D_U16)(cmd_buf[7]) << 8) | cmd_buf[8];
                return_result2tools_set(SetRGBOffset(input_R, input_G, input_B));
            }
            else
                return_result2tools_set(SetRedOffset(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case SET_USR_G_OFF:
        {
            return_result2tools_set(SetGreenOffset(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case SET_USR_B_OFF:
        {
            return_result2tools_set(SetBlueOffset(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case GET_USR_R_OFF:
        {
            D_S32 r_offset;
            GetRedOffset(&r_offset);
            ACK[2] = 0x02;
            ACK[3] = (r_offset & 0xff00) >> 8;
            ACK[4] = (r_offset & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case GET_USR_G_OFF:
        {
            D_S32 r_offset;
            GetGreenOffset(&r_offset);
            ACK[2] = 0x02;
            ACK[3] = (r_offset & 0xff00) >> 8;
            ACK[4] = (r_offset & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case GET_USR_B_OFF:
        {
            D_S32 r_offset;
            GetBlueOffset(&r_offset);
            ACK[2] = 0x02;
            ACK[3] = (r_offset & 0xff00) >> 8;
            ACK[4] = (r_offset & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case SET_USR_R_GAN:
        {
            D_S32   input_R, input_G, input_B;
            if( cmd_buf[2] == 0x06 ) //SET_USR_RGB_GAN
            {
                input_R = ((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4];
                input_G = ((D_U16)(cmd_buf[5]) << 8) | cmd_buf[6];
                input_B =  ((D_U16)(cmd_buf[7]) << 8) | cmd_buf[8];
                return_result2tools_set(SetRGBGain(input_R, input_G, input_B));
            }
            else
                return_result2tools_set(SetRedGain(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case SET_USR_G_GAN:
        {
            return_result2tools_set(SetGreenGain(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case SET_USR_B_GAN:
        {
            return_result2tools_set(SetBlueGain(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case GET_USR_R_GAN:
        {
            D_S32 r_gain;
            GetRedGain(&r_gain);
            ACK[2] = 0x02;
            ACK[3] = (r_gain & 0xff00) >> 8;
            ACK[4] = (r_gain & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case GET_USR_G_GAN:
        {
            D_S32 g_gain;
            GetGreenGain(&g_gain);
            ACK[2] = 0x02;
            ACK[3] = (g_gain & 0xff00) >> 8;
            ACK[4] = (g_gain & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case GET_USR_B_GAN:
        {
            D_S32 b_gain;
            GetBlueGain(&b_gain);
            ACK[2] = 0x02;
            ACK[3] = (b_gain & 0xff00) >> 8;
            ACK[4] = (b_gain & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case COPY_ALL:
        {
            return_result2tools_set(Set_copy_all());
        }
        break;
        case SET_AUTO_ADC:
        {
            return_result2tools_set(Set_auto_adc());
        }
        break;

        case SET_RCU_KEY:
        {
            return_result2tools_set(SetRCU_Key(cmd_buf[3]));
        }
        break;

        case DO_TST_USB_PORT:
        {
            D_S32 udisk;
            DoUsbTest((cmd_buf[3]), &udisk);
            ACK[2] = 0x01;
            ACK[3] = (char)udisk;
            return_result2tools_get(ACK);
        }
        break;

        case SET_SCREEN_WHITE:
        {
            return_result2tools_set(SetSrceenWhite(cmd_buf[3]));
        }
        break;

        case GET_SYS_FW_VER:
        {
            GetFirmwareVersion(ACK);
            return_result2tools_get(ACK);
        }
        break;

        case SET_INPUT_SRC:
        {
            return_result2tools_set(SetInputSource(cmd_buf[3]));
        }
        break;

        case GET_INPUT_SRC:
        {
            D_S32 input_src;
            GetInputSource(&input_src);
            ACK[2] = 0x01;
            ACK[3] = input_src;
            return_result2tools_get(ACK);
        }
        break;

        case SET_BRGHTNSS:
        {
            return_result2tools_set(SetBrghtnss(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case GET_BRGHTNSS:
        {
            D_S32 brghtnss;
            GetBrghtnss(&brghtnss);
            ACK[2] = 0x02;
            ACK[3] = (brghtnss & 0xff00) >> 8;
            ACK[4] = (brghtnss & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case SET_CONTRAST:
        {
            return_result2tools_set(SetContrast(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case GET_CONTRAST:
        {
            D_S32 contrast;
            GetContrast(&contrast);
            ACK[2] = 0x02;
            ACK[3] = (contrast & 0xff00) >> 8;
            ACK[4] = (contrast & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case SET_BACKLIGHT:
        {
            return_result2tools_set(SetBacklight(((D_U16)(cmd_buf[3]) << 8) | cmd_buf[4]));
        }
        break;

        case GET_BACKLIGHT:
        {
            D_S32 backlight;
            GetBacklight(&backlight);
            ACK[2] = 0x02;
            ACK[3] = (backlight & 0xff00) >> 8;
            ACK[4] = (backlight & 0x00ff);
            return_result2tools_get(ACK);
        }
        break;

        case SET_PICTUREMODE:
        {
            return_result2tools_set(SetPictureMode(cmd_buf[3]));
        }
        break;

        case GET_PICTUREMODE:
        {
            D_S32 pic_mode;
            GetPictureMode(&pic_mode);
            ACK[2] = 0x01;
            ACK[3] = pic_mode;
            return_result2tools_get(ACK);
        }
        break;

        case SET_MUTE:
        {
            return_result2tools_set(SetMute(cmd_buf[3]));
        }
        break;

        case SET_VOLUME:
        {
            return_result2tools_set(SetSoundVolume(cmd_buf[3]));
        }
        break;
        case FACTORY_RESET_BOE:
        {
            return_result2tools_set(FactoryReset_boe(cmd_buf[3]));
        }
        break;
        case FACTORY_RESET_CTV:
        {
            return_result2tools_set(FactoryReset(cmd_buf[3]));
        }
        break;

        case SET_CHANNEL:
        {
            return_result2tools_set(SetTVChannel(cmd_buf[3], cmd_buf[4]));
        }
        break;

        case GET_IP_ADDRESS:
        {
            return_result2tools_set(FACTORY_API_NoSupport);
        }
        break;

        case FAC_PERSET_CHANNEL:
        {
            return_result2tools_set(SetFacPersetCH(cmd_buf[3]));
        }
        break;

        case SET_DISPLAYMODE:
        {
            return_result2tools_set(Set_DisplayMode(cmd_buf[3]));
        }
        break;

        case GET_DISPLAYMODE:
        {
            D_S32 display_mode;
            Get_DisplayMode(&display_mode);
            ACK[2] = 0x01;
            ACK[3] = display_mode;
            return_result2tools_get(ACK);
        }
        break;
        case SET_MAC_ADDRESS:
        {
            return_result2tools_set(FACTORY_API_NoSupport);
        }
        break;

        case GET_MAC_ADDRESS:
        {
            return_result2tools_set(FACTORY_API_NoSupport);
        }
        break;
        case SET_KEY_LOCK:
        {
            if( cmd_buf[2] == 0x01 ) //SET_KEY_LOCK SET_KEY_UNLOCK
            {
                return_result2tools_set(SetKeyLock(cmd_buf[3]));
            }
            else
            {
                return_result2tools_set(FACTORY_API_NoSupport);
            }
        }
        break;
        case GET_KEYPAD_ADC:
        {
            D_U8 key;
            Get_IRKEY(&key);
            IRKEY[2] = 0x00;
            IRKEY[3] = key;
            return_result2tools_get(IRKEY);
        }
        break;
#ifdef WYG_GAMMA_SET        // added by wangyg on 2015-09-03

        case SET_USR_GAMMA_R:
        {
            return_result2tools_set(SetRedGamma(cmd_buf[3], cmd_buf[4]));
        }
        break;
        case SET_USR_GAMMA_G:
        {
            return_result2tools_set(SetGreenGamma(cmd_buf[3], cmd_buf[4]));
        }
        break;
        case SET_USR_GAMMA_B:
        {
            return_result2tools_set(SetBlueGamma(cmd_buf[3], cmd_buf[4]));
        }
        break;
        case GET_USR_GAMMA_R:
        {
            D_U8 idx = cmd_buf[2];
            D_U16 val;
            GetRedGamma(idx, &val);
            GAMMA_R[2] = idx;
            GAMMA_R[3] = (val >> 8) & 0xff;
            GAMMA_R[4] = val & 0xff;
            return_result2tools_get(GAMMA_R);
        }
        break;
        case GET_USR_GAMMA_G:
        {
            D_U8 idx = cmd_buf[2];
            D_U16 val;
            GetGreenGamma(idx, &val);
            GAMMA_G[2] = idx;
            GAMMA_G[3] = (val >> 8) & 0xff;
            GAMMA_G[4] = val & 0xff;
            return_result2tools_get(GAMMA_G);
        }
        break;
        case GET_USR_GAMMA_B:
        {
            D_U8 idx = cmd_buf[2];
            D_U16 val;
            GetBlueGamma(idx, &val);
            GAMMA_B[2] = idx;
            GAMMA_B[3] = (val >> 8) & 0xff;
            GAMMA_B[4] = val & 0xff;
            return_result2tools_get(GAMMA_B);
        }
        break;
#endif
        default:
        {
            return_result2tools_set(FACTORY_API_NoSupport);
            break;
        }
    }
    return;
}

static D_Result rev_command_func(D_U8 *buf_rciv)
{
    static D_U8 offset = 0;

    if(buf_rciv[0] == COMMAND_HEAD)
    {
        gCom_crc = 0x00;
        offset = 0;
        gCommand_buf[offset] = buf_rciv[0];

    }
    else
    {
        gCommand_buf[++offset] = buf_rciv[0];

        if( gCommand_buf[11] == COMMAND_TAIL )
        {
            set_tv_parameter(gCommand_buf);
            offset = 0;
            gCom_crc = 0x00;
            memset(gCommand_buf, 0, SERIAL_BUF_LENGTH);
        }

        if(offset < 10)
        {
            gCom_crc += buf_rciv[0];
        }
        else
        {
            gCom_crc ^= 0xFF;
            gCom_crc += 0x01;
            if(gCom_crc != gCommand_buf[10])
            {
                memset(gCommand_buf, 0, SERIAL_BUF_LENGTH);
                offset = 0;
                gCom_crc = 0x00;
                return D_ERR;
            }
        }
    }

    return D_OK;
}

/** @brief 从串口接收数据并烧写序列号
* @param[in] sl_hdl：串口句柄
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
static D_Result sn_burn_handle(D_HSerial sl_hdl) D_FUNCPOSTFIT
{
    D_U16 real_len = 0;
    D_Result ret;

    Serial_Handle = sl_hdl;

    switch(serial_data->step)
    {
        case SEND_CHIPID:
        {
            memset(serial_data->buf_rciv, 0, serial_data->buf_len);
            memset(serial_data->buf_bkup, 0, serial_data->buf_len);
            real_len = d_serial_read(sl_hdl, serial_data->buf_rciv, UART_CMD_LENGTH);
            if(real_len > 0)    //从串口中接收到数据
            {
                ret = rev_command_func(serial_data->buf_rciv);
                if(ret != D_OK)
                {
                    serial_data->rev_cnt++;
                    //return D_OK;
                    break;
                }
            }
        }
        break;

        default:
            break;
    }
    if(real_len == 0)
    {
        D_ERROR("Read serial interface error!\n");
        //serial_data->buf_bkup[0] = RESULT_TIMEOUT;
        d_serial_flush(sl_hdl);
        //d_serial_write (sl_hdl, serial_data->buf_bkup, UART_CMD_LENGTH);
    }
    if(serial_data->rev_cnt > SCAN_REPEAT_CNT)
    {
        serial_data->rev_cnt = 0;
        serial_data->step = SEND_CHIPID;
    }
    return D_ERR;
}

/** @brief 序列号烧写结束，释放资源
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
static D_Result sn_burn_end(void) D_FUNCPOSTFIT
{
    PROJECT_FREE(serial_data->buf_bkup);
    PROJECT_FREE(serial_data->buf_rciv);
    PROJECT_FREE(serial_data);
    serial_data = NULL;

    return D_OK;
}

/** @brief 烧写序列号
* @param[in] sl_hdl：串口句柄
* @param[in] type：操作类型
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_tv_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT
{
    switch (type)
    {
        case INITIALIZE:
            if(sn_burn_init() != D_OK)
            {
                return D_ERR;
            }
            break;
        case HANDLE:
            if(sn_burn_handle(sl_hdl) != D_OK)
            {
                return D_ERR;
            }
            break;
        case DESTROY:
            sn_burn_end();
            break;
        default:
            break;
    }
    return D_OK;
}

#endif

/**@}*/
