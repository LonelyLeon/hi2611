/**@defgroup sn-burn 序列号烧写模块
*@{*/
/** @file
* @brief 序列号烧写模块
* @author 刘伟峰
* @date 2013-08-20 刘伟峰: 建立文件
*/

#include <stdio.h>
#include <stdlib.h>
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
#include "dDsc.h"
#include "pBurnSerialNumber.h"
#include "ptvConfig.h"

#define SERIAL_BUF_LENGTH       4096
#define UART_CMD_LENGTH         1
#define RESULT_OK               0x11
#define RESULT_CMD_FAIL     0x12

#define CMD_HEAD    0x55
#define CMD_TAIL    0xfe
#define HEAD_BYTE       (1)
#define CMD_BYTE        (2)
#define TAIL_BYTE           (1)
#define LEN_BYTE        (2)
#define CRC_BYTE            (4)
#define GROUP_CNT_BYTE      (2)

static D_U32 gCmd_offset = 0;
static D_U8 gCmd_flag = 0;
static D_U32 gCmd_crc = 0;

typedef enum
{
    SN_GREG_VAL = 0xa4,
    SN_SETREG_VAL = 0xa5,
    SN_SETMODE_VAL = 0xa6,
    SN_GET_CNTREG_VAL = 0xa7,
    SN_GET_GAMMA_VAL = 0xa9,
    SN_SET_GAMMA_VAL = 0xaa,
    SN_SET_DATA_VAL = 0xab,
    SN_GET_DATA_VAL = 0xac,
    SN_SET_SOUND_VAL = 0xad,
    SN_GET_SOUND_VAL = 0xae,
} SN_CMD_TYPE;

typedef struct
{
    D_U8* buf_rciv; //用于从串口接收数据的buffer
    D_U8* buf_bkup; //用于处理数据的备份buffer
    D_U8* cmd_buff;
    D_U32 buf_len;  //buffer的长度
} SerialParam;

static SerialParam *serial_data = NULL; //处理串口时使用的buffer

static D_U8 Uart_lock_flag = 0;

D_U8  *input_mode_buf;
D_U8  *input_data_buf;

#ifdef D_BURN_SN_MODE_E
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

    serial_data->cmd_buff = (D_U8*)PROJECT_ALLOC(SERIAL_BUF_LENGTH);
    if(!serial_data->cmd_buff)
    {
        PROJECT_FREE(serial_data->buf_bkup);
        PROJECT_FREE(serial_data->buf_rciv);
        PROJECT_FREE(serial_data);
        return D_ERR;
    }
    memset( serial_data->cmd_buff, 0 , SERIAL_BUF_LENGTH);
    return D_OK;
}

static D_Result Data2SNCMD(D_HSerial sl_hdl, D_U16 cmd_type, D_U8 *data_buff, D_Size data_len )
{
    D_S32 i = 0, j = 0;
    D_U16 cmd_len = 0, sn_len = 0;
    D_U32   sn_crc = 0;
    D_U8    *sn_buf;
    D_Size  data_len_t;

    data_len_t = data_len;
    cmd_len = HEAD_BYTE + LEN_BYTE + CMD_BYTE + data_len_t + CRC_BYTE + TAIL_BYTE;
    sn_len = cmd_len - (HEAD_BYTE + LEN_BYTE + TAIL_BYTE);
    //hex_len = inttohex(sn_len);

    sn_buf = (D_U8*)PROJECT_ALLOC(cmd_len);
    if(!sn_buf)
    {
        return D_ERR;
    }
    memset(sn_buf, 0, cmd_len);

    for(i = 0; i < cmd_len; i++)
    {
        if(i == 0)
        {
            sn_buf[i] = 0x55;
        }
        else if(i == 1)
        {
            sn_buf[i] = (D_U8)(sn_len >> 8);
        }
        else if(i == 2)
        {
            sn_buf[i] = (D_U8)sn_len;
        }
        else if(i == 3)
        {
            sn_buf[i] = cmd_type >> 8;
            sn_crc += sn_buf[i];
        }
        else if(i == 4)
        {
            sn_buf[i] = cmd_type;
            sn_crc += sn_buf[i];
        }
        else if( i == (cmd_len - CRC_BYTE - TAIL_BYTE))
        {
            if(data_len_t == 0 )
            {
                sn_crc ^= 0xFF;
                sn_crc += 0x01;
            }
            else
            {
                return D_ERR;
            }
            sn_buf[i] = sn_crc >> 24;
        }
        else if( i == (cmd_len - CRC_BYTE - TAIL_BYTE + 1))
        {
            sn_buf[i] = sn_crc >> 16;
        }
        else if( i == (cmd_len - CRC_BYTE - TAIL_BYTE + 2))
        {
            sn_buf[i] = sn_crc >> 8;
        }
        else if( i == (cmd_len - CRC_BYTE - TAIL_BYTE + 3))
        {
            sn_buf[i] = sn_crc;
        }
        else if(i == (cmd_len - 1))
        {
            sn_buf[i] = 0xfe;
            memcpy(serial_data->buf_rciv, sn_buf, cmd_len);
            serial_data->buf_len = cmd_len;
            PROJECT_FREE(sn_buf);
            sn_buf = NULL;
            return D_OK;
        }
        else
        {
            sn_buf[i] = data_buff[j];
            sn_crc += sn_buf[i];
            j ++;
            data_len_t--;
        }

    }
    return D_OK;

}

static D_Result get_cntreg_val(D_U32 addr, D_U16 reg_cnt, D_U8 *send_reg_date)
{
    D_U32 i;
    D_U32 set_reg_addr = 0;
    D_U8 get_reg_val = 0;

    if(addr == 0 || reg_cnt == 0 )
        return D_ERR;

    send_reg_date[0] = (reg_cnt >> 8) & 0xff;
    send_reg_date[1] = reg_cnt;
    send_reg_date[2] = (addr >> 24) & 0xff;
    send_reg_date[3] = (addr >> 16) & 0xff;
    send_reg_date[4] = (addr >> 8) & 0xff;
    send_reg_date[5] = (addr) & 0xff;

    for( i = 0; i < reg_cnt; i++)
    {
        set_reg_addr = addr + i;
        get_reg_val = d_sys_get_reg(set_reg_addr);
        send_reg_date[6 + i] = get_reg_val;
    }
    return D_OK;
}

static D_Result get_reg_val(D_U8 *input_reg_date, D_U16 reg_cnt, D_U8 *send_reg_date)
{
    D_U32 i;
    D_U32 set_reg_addr = 0;
    D_U32 input_offset = 0, send_offset = 0;
    D_U8 reg_val = 0;

    for( i = 0; i < reg_cnt; i++)
    {
        if( input_reg_date[input_offset] == 0 || input_reg_date == NULL )
            return D_ERR;

        set_reg_addr = input_reg_date[input_offset] << 24\
                       | input_reg_date[input_offset + 1] << 16 \
                       | input_reg_date[input_offset + 2] << 8\
                       | input_reg_date[input_offset + 3];

        reg_val = d_sys_get_reg(set_reg_addr);

        send_reg_date[0] = (reg_cnt & 0xff00) >> 8;
        send_reg_date[1] = reg_cnt & 0xff;

        memcpy(&send_reg_date[send_offset + 2], &input_reg_date[input_offset], 4);
        input_offset += 4;
        send_offset += 4;
        send_reg_date[2 + send_offset] = reg_val;
        send_offset += 1;

    }

    return D_OK;
}
static D_Result get_gamma_val(D_U8 *input_reg_date, D_U8 val1, D_U16 cnt1, D_U16 cnt2, D_U8 *send_reg_date)
{
    D_U32 i, j;
    D_U32 wr_reg_addr = 0, set_reg_addr = 0;
    D_U8 reg_mask;
    D_U32 input_offset = 0, send_offset = 0;
    D_U8 reg_val = 0;

    wr_reg_addr = input_reg_date[0] << 24\
                  | input_reg_date[0 + 1] << 16 \
                  | input_reg_date[0 + 2] << 8\
                  | input_reg_date[0 + 3];
    reg_mask = input_reg_date[0 + 4];
    send_reg_date[0] = cnt1 >> 8;
    send_reg_date[1] = cnt1;
    send_reg_date[2] = cnt2 >> 8;
    send_reg_date[3] = cnt2;
    send_offset = 4;
    input_offset = 7;
    for( i = 0; i < cnt2; i++)
    {
        memcpy(&send_reg_date[send_offset], &input_reg_date[input_offset], 4);
        input_offset += 4;
        send_offset += 4;
    }
    input_offset = 7;
    for( i = 0; i < cnt1; i++)
    {
        d_sys_set_reg(wr_reg_addr, val1 + i, reg_mask);
        d_task_wait(10);
        for( j = 0; j < cnt2; j++)
        {
            set_reg_addr = input_reg_date[input_offset + 4 * j] << 24\
                           | input_reg_date[input_offset + 4 * j + 1] << 16 \
                           | input_reg_date[input_offset + 4 * j + 2] << 8\
                           | input_reg_date[input_offset + 4 * j + 3];
            reg_val = d_sys_get_reg(set_reg_addr);
            send_reg_date[send_offset] = reg_val;
            send_offset += 1;
        }
    }

    return D_OK;
}
static D_Result set_gamma_val(D_U8 *input_reg_date, D_U8 val1, D_U16 cnt1, D_U16 cnt2)
{
    D_U32 i, j;
    D_U32 wr_reg_addr = 0, set_reg_addr = 0;
    D_U8 reg_mask, reg_mask1;
    D_U32 input_offset = 0;
    D_U32 data_offset = 0;

    wr_reg_addr = input_reg_date[0] << 24\
                  | input_reg_date[0 + 1] << 16 \
                  | input_reg_date[0 + 2] << 8\
                  | input_reg_date[0 + 3];
    reg_mask = input_reg_date[0 + 4];
    input_offset = 7;
    data_offset = input_offset + cnt2 * 5;
    for( i = 0; i < cnt1; i++)
    {
        d_sys_set_reg(wr_reg_addr, val1 + i, reg_mask);
        d_task_wait(10);
        for( j = 0; j < cnt2; j++)
        {
            set_reg_addr = input_reg_date[input_offset + 5 * j] << 24\
                           | input_reg_date[input_offset + 5 * j + 1] << 16 \
                           | input_reg_date[input_offset + 5 * j + 2] << 8\
                           | input_reg_date[input_offset + 5 * j + 3];
            reg_mask1 = input_reg_date[input_offset + 5 * j + 4];
            d_sys_set_reg(set_reg_addr, input_reg_date[data_offset], reg_mask1);
            data_offset++;
        }
    }

    return D_OK;
}

D_Result set_reg_val(D_U8 *input_reg_date, D_U16 reg_cnt)
{
    D_U32   i;
    D_U32   set_reg_addr = 0;
    D_U32   input_offset = 0;
    D_U8    reg_data = 0, reg_mask = 0;
    D_Result    ret = D_ERR;

    for( i = 0; i < reg_cnt; i++ )
    {
        if( input_reg_date[input_offset] == 0 || input_reg_date == NULL )
            return D_ERR;

        set_reg_addr = input_reg_date[input_offset] << 24\
                       | input_reg_date[input_offset + 1] << 16 \
                       | input_reg_date[input_offset + 2] << 8\
                       | input_reg_date[input_offset + 3];
        reg_data = input_reg_date[input_offset + 4];
        reg_mask = input_reg_date[input_offset + 5];
        ret = d_sys_set_reg(set_reg_addr, reg_data, reg_mask);
        if( ret != D_OK )
        {
            return D_ERR;
        }
        input_offset += 6;
    }
    return D_OK;
}

static D_Result parse_reg_cmd(D_U8 *cmd_buf , D_HSerial sl_hdl)
{
    D_U16   Cmd_Type = 0;
    D_Size  Cmd_Len = 0;
    D_U16   Reg_cnt = 0;
    D_U16   mode = 0, type = 0;
    D_U8    *send_reg_buff, *input_reg_buf;
    D_Size  date_len = 0;
    D_U32   width = 0, high = 0, color = 0, vcom_startpix = 0, vcom_width = 0, vcom_height = 0, vcom_en = 0 , test_en = 0;
    D_AVC_SET avc[TV_AVC_INPUT_NUM];
    D_Avc_Param avc_param;
    Cmd_Len = (cmd_buf[1] << 8) | cmd_buf[2];
    Cmd_Type = (cmd_buf[3] << 8) | cmd_buf[4];
    Reg_cnt = cmd_buf[5] << 8 | cmd_buf[6];
    mode = cmd_buf[7] << 8 | cmd_buf[8];

    switch(Cmd_Type)
    {
        case SN_GREG_VAL:
        {
            D_Result ret = D_ERR;
            D_U8   err = 0x02;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;

            if( date_len / 4 != Reg_cnt )
                return D_ERR;

            input_reg_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_reg_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_reg_buf, 0, date_len);

            send_reg_buff = (D_U8*)PROJECT_ALLOC(GROUP_CNT_BYTE + date_len + Reg_cnt);
            if(send_reg_buff == NULL)
            {
                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                return D_ERR;
            }
            memset(send_reg_buff, 0, GROUP_CNT_BYTE + date_len + Reg_cnt);

            memcpy(input_reg_buf, &cmd_buf[7], date_len);
            ret = get_reg_val( input_reg_buf, Reg_cnt, send_reg_buff);
            if( ret != D_OK )
            {
                Data2SNCMD(sl_hdl, SN_GREG_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                PROJECT_FREE(send_reg_buff);
                send_reg_buff = NULL;

                return D_ERR;
            }
            Data2SNCMD(sl_hdl, SN_GREG_VAL, send_reg_buff, GROUP_CNT_BYTE + Reg_cnt + date_len);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(input_reg_buf);
            input_reg_buf = NULL;
            PROJECT_FREE(send_reg_buff);
            send_reg_buff = NULL;
        }
        break;

        case SN_SETREG_VAL:
        {
            D_Result ret = D_ERR;
            D_U8    suc = 0x00, err = 0x02;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;

            if( date_len / 6 != Reg_cnt )
                return D_ERR;

            input_reg_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_reg_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_reg_buf, 0, date_len);

            memcpy(input_reg_buf, &cmd_buf[7], date_len);
            ret = set_reg_val( input_reg_buf, Reg_cnt);
            if( ret != D_OK )
            {
                Data2SNCMD(sl_hdl, SN_SETREG_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;

                return D_ERR;
            }
            Data2SNCMD(sl_hdl, SN_SETREG_VAL, &suc, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
            PROJECT_FREE(input_reg_buf);
            input_reg_buf = NULL;
        }
        break;

        case SN_SETMODE_VAL:
        {
            D_U8    suc = 0x00;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;//vcom:16

            if( date_len != Reg_cnt )/*Reg_cnt:2BYTE数据长度; date_len:数据总的字节数;*/
                return D_ERR;

            input_mode_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_mode_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_mode_buf, 0, date_len);

            memcpy(input_mode_buf, &cmd_buf[7], date_len);
            type = (input_mode_buf[0] << 8) | input_mode_buf[1];
//VCOM
            if(type == 0)
            {
                vcom_en = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                vcom_startpix = (input_mode_buf[6] << 24) | (input_mode_buf[7] << 16) | (input_mode_buf[8] << 8) | (input_mode_buf[9] << 0);
                vcom_width = (input_mode_buf[10] << 24) | (input_mode_buf[11] << 16) | (input_mode_buf[12] << 8) | (input_mode_buf[13] << 0);
                vcom_height = (input_mode_buf[14] << 24) | (input_mode_buf[15] << 16) | (input_mode_buf[16] << 8) | (input_mode_buf[17] << 0);
                VCOM_testparten((D_U8)vcom_en , (D_U16)vcom_startpix , (D_U16)vcom_width, (D_U16)vcom_height);
            }
//OSD
            else if(type == 1)
            {
                width = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                high = (input_mode_buf[6] << 24) | (input_mode_buf[7] << 16) | (input_mode_buf[8] << 8) | (input_mode_buf[9] << 0);
                color = input_mode_buf[10];
                HI_OSD_test_pattern(width, high, color);
            }
//SP
            else if(type == 2)
            {
                width = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                high = (input_mode_buf[6] << 24) | (input_mode_buf[7] << 16) | (input_mode_buf[8] << 8) | (input_mode_buf[9] << 0);
                HI_SP_test_pattern(width, high);
            }
//VO
            else if(type == 3)
            {
                width = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                high = (input_mode_buf[6] << 24) | (input_mode_buf[7] << 16) | (input_mode_buf[8] << 8) | (input_mode_buf[9] << 0);
                HI_VO_test_pattern(width, high);
            }
//VCOM_EN
            else if(type == 4)
            {
                test_en = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                (test_en == 0) ? (d_av_set_vid_blank(0, D_TRUE)) : (d_av_set_vid_blank(0, D_FALSE));
            }
//OSD_EN
            else if(type == 5)
            {
                test_en = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                (test_en == 0) ? (d_gdev_set_enable(p_gui_get_hgdev(), D_FALSE)) : (d_gdev_set_enable(p_gui_get_hgdev(), D_TRUE));
            }
//SP_EN
            else if(type == 6)
            {
                test_en = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                (test_en == 0) ? (VIDEO_Set_Close_VideoWin(1)) : (VIDEO_Set_Resume_VideoWin(1));
            }
//VO_EN
            else
            {
                test_en = (input_mode_buf[2] << 24) | (input_mode_buf[3] << 16) | (input_mode_buf[4] << 8) | (input_mode_buf[5] << 0);
                (test_en == 0) ? (VIDEO_Set_Close_VideoWin(0)) : (VIDEO_Set_Resume_VideoWin(0));
            }

            Data2SNCMD(sl_hdl, SN_SETMODE_VAL, &suc, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
            PROJECT_FREE(input_mode_buf);
            input_mode_buf = NULL;
        }
        break;
        case SN_GET_CNTREG_VAL:
        {
            D_Result ret = D_ERR;
            D_U8     err = 0x02;
            D_U32 regbase = 0;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;

            if( date_len < 4 )
                return D_ERR;

            regbase = (cmd_buf[7] << 24) | cmd_buf[8] << 16 | cmd_buf[9] << 8 | cmd_buf[0xa];

            send_reg_buff = (D_U8*)PROJECT_ALLOC(2 + 4 + Reg_cnt);
            if(send_reg_buff == NULL)
            {
                return D_ERR;
            }
            memset(send_reg_buff, 0, GROUP_CNT_BYTE + date_len + Reg_cnt);

            ret = get_cntreg_val( regbase, Reg_cnt, send_reg_buff);
            if( ret != D_OK )
            {
                Data2SNCMD(sl_hdl, SN_GET_CNTREG_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

                PROJECT_FREE(send_reg_buff);
                send_reg_buff = NULL;

                return D_ERR;
            }
            Data2SNCMD(sl_hdl, SN_GET_CNTREG_VAL, send_reg_buff, 2 + 4 + Reg_cnt);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(send_reg_buff);
            send_reg_buff = NULL;
        }
        break;
        case SN_GET_GAMMA_VAL:
        {
            D_Result ret = D_ERR;
            D_U8     err = 0x02;
            D_U32 ret_data_len;
            D_U16 cnt1, cnt2;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;
            input_reg_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_reg_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_reg_buf, 0, date_len);
            memcpy(input_reg_buf, &cmd_buf[7], date_len);
            cnt1 = cmd_buf[6] - cmd_buf[5] + 1;
            cnt2 = cmd_buf[12] << 8 | cmd_buf[13];
            ret_data_len = 4 + cnt2 * 4 + cnt1 * cnt2;

            send_reg_buff = (D_U8*)PROJECT_ALLOC(ret_data_len);
            if(send_reg_buff == NULL)
            {
                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                return D_ERR;
            }
            memset(send_reg_buff, 0, ret_data_len);

            ret = get_gamma_val( input_reg_buf, cmd_buf[5], cnt1, cnt2, send_reg_buff);
            if( ret != D_OK )
            {
                Data2SNCMD(sl_hdl, SN_GET_GAMMA_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                PROJECT_FREE(send_reg_buff);
                send_reg_buff = NULL;

                return D_ERR;
            }
            Data2SNCMD(sl_hdl, SN_GET_GAMMA_VAL, send_reg_buff, ret_data_len);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(input_reg_buf);
            input_reg_buf = NULL;
            PROJECT_FREE(send_reg_buff);
            send_reg_buff = NULL;
        }
        break;
        case SN_SET_GAMMA_VAL:
        {
            D_Result ret = D_ERR;
            D_U8    suc = 0x00, err = 0x02;
            D_U16 cnt1, cnt2;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE - GROUP_CNT_BYTE;
            input_reg_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_reg_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_reg_buf, 0, date_len);
            memcpy(input_reg_buf, &cmd_buf[7], date_len);
            cnt1 = cmd_buf[6] - cmd_buf[5] + 1;
            cnt2 = cmd_buf[12] << 8 | cmd_buf[13];
            ret = set_gamma_val( input_reg_buf, cmd_buf[5], cnt1, cnt2);
            if( ret != D_OK )
            {
                Data2SNCMD(sl_hdl, SN_SET_GAMMA_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                return D_ERR;
            }
            Data2SNCMD(sl_hdl, SN_SET_GAMMA_VAL, &suc, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(input_reg_buf);
            input_reg_buf = NULL;
        }
        break;
        case SN_SET_DATA_VAL:
        {
            D_U8   suc = 0x00 , GDflag;
            D_U16 cnt1, cnt2 , cnt2_total , rgb_type_data , current_position;

            cnt1 = cmd_buf[5] << 8 | cmd_buf[6];
            rgb_type_data = cmd_buf[7] << 8 | cmd_buf[8];
            cnt2_total = cmd_buf[9]  << 8 | cmd_buf[10];
            current_position = cmd_buf[11]  << 8 | cmd_buf[12];
            GDflag = cmd_buf[13];

            cnt2 = cmd_buf[7 + cnt1] << 8 | cmd_buf[7 + cnt1 + 1];
            date_len = cnt2_total;

            if(current_position == 0)
            {
                input_data_buf = (D_U8*)PROJECT_ALLOC(date_len);
                if(input_data_buf == NULL)
                {
                    return D_ERR;
                }
                memset(input_data_buf, 0, date_len);
            }
            memcpy(&input_data_buf[current_position] , &cmd_buf[7 + cnt1 + 2] , cnt2);

            if((current_position + cnt2) == cnt2_total)
            {
                if(GDflag == 0)
                {
                    PQ_CM_setLUT_UGM((D_U8)rgb_type_data, input_data_buf);
                }
                else if(GDflag == 1)
                {
                    PQ_PA_setLUT_OD((D_U8)rgb_type_data, input_data_buf);
                }
                else if(GDflag == 2)
                {
                    PQ_PA_setLUT_LD(input_data_buf);
                }
                else if(GDflag == 3)
                {
                    PQ_CM_setVal_WBA(input_data_buf);
                }
                else if(GDflag == 4)
                {
                    PQ_CVBS_setVal_COMB(input_data_buf);
                }               
                else if(GDflag == 5)
                {
                    PQ_VO_setVal_CSP(input_data_buf);
                }
                else if(GDflag == 6) // ICM
                {
                    PQ_VE_setVal_ICM((D_U8)rgb_type_data, input_data_buf);
                }
                else if(GDflag == 7) // FCC
                {
                    PQ_VE_setVal_FCC((D_U8)rgb_type_data, input_data_buf);
                }
                else if(GDflag == 8)
                {
                    PQ_VE_setLUT_CE_STATIC(input_data_buf);
                }


                PROJECT_FREE(input_data_buf);
                input_data_buf = NULL;
            }
            Data2SNCMD(sl_hdl, SN_SET_DATA_VAL, &suc, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
        }
        break;

        case SN_GET_DATA_VAL:
        {
            D_U8     err = 0x02 , ret_data_len , mode , hdflag;
            D_U16 channel;
            D_U8 start_addr, len , GDflag , mode_idx , sdhd_idx;
            D_VidInput input;
            D_DBTvMode tinput;
            D_NR_SET nr_param;

            date_len = Cmd_Len - CMD_BYTE - CRC_BYTE;
            input_reg_buf = (D_U8*)PROJECT_ALLOC(date_len);
            if(input_reg_buf == NULL)
            {
                return D_ERR;
            }
            memset(input_reg_buf, 0, date_len);
            memcpy(input_reg_buf, &cmd_buf[5], date_len);
            channel = input_reg_buf[1];
            start_addr = input_reg_buf[2];
            len = input_reg_buf[3];
            GDflag = input_reg_buf[4];

            ret_data_len = 2 * len;
            send_reg_buff = (D_U8*)PROJECT_ALLOC(ret_data_len);
            if(send_reg_buff == NULL)
            {
                PROJECT_FREE(input_reg_buf);
                input_reg_buf = NULL;
                return D_ERR;
            }
            memset(send_reg_buff, 0, ret_data_len);

            if(GDflag == 0)
            {
                PQ_CM_getLUT_UGM(channel, start_addr, len, send_reg_buff);
            }
            else if(GDflag == 1)
            {
                PQ_PA_getLUT_OD(channel, start_addr, len, send_reg_buff);
            }
            else if(GDflag == 2)
            {
                PQ_PA_getLUT_LD(start_addr , len , send_reg_buff);
            }
            else if(GDflag == 3)
            {
                PQ_CM_getVal_WBA(send_reg_buff);
            }
            else if(GDflag == 4)
            {
                PQ_CVBS_getVal_COMB(send_reg_buff);
            }
            else if(GDflag == 5)
            {
                PQ_VO_getVal_CSP(send_reg_buff);
            }
            else if(GDflag == 6) // ICM
            {
                PQ_VE_getVal_ICM(send_reg_buff);
            }	
            else if(GDflag == 7) // FCC
            {
                PQ_VE_getVal_FCC(channel, send_reg_buff);
            }				
            else if(GDflag == 8)
            {
                PQ_VE_getLUT_CE_STATIC(start_addr , len , send_reg_buff);
            }
            else if(GDflag == 9)
            {
                PQ_VE_getLUT_CE_DYNAMIC(start_addr , len , send_reg_buff);
            }
            else if(GDflag == 10)
            {
                PQ_VE_getLUT_CE_HIST(start_addr , len , send_reg_buff);
            }
            else if(GDflag == 11) // NR: tinput hdflag mode
            {
                input = p_conf_get_vid_input();
                if(input == D_VID_IUTPUT_AV1 || input == D_VID_IUTPUT_AV2 || input == D_VID_IUTPUT_TV)
                {
                    hdflag = p_vip_get_ntscflag();
                }
                else
                {
                    hdflag = p_vip_get_hdflag();
                }
                tinput = p_vip_get_dbinput(input);
                p_tvconf_get_cur_nrmode(&mode, tinput);
                if(channel == 1)//首次读取
                {
                    if(start_addr == 0)
                    {
                        send_reg_buff[0] = tinput;
                        send_reg_buff[1] = mode;
                        send_reg_buff[2] = hdflag;
                    }
                    else
                    {
                        for(mode_idx = 0; mode_idx < 4; mode_idx ++)
                        {
                            p_tvconf_get_nr_set_param(&nr_param, start_addr - 1 , mode_idx);
                            memcpy(&send_reg_buff[mode_idx * 2 * sizeof(nr_param)] , &nr_param , sizeof(nr_param));
                            p_tvconf_get_hdnr_set_param(&nr_param, start_addr - 1 , mode_idx);
                            memcpy(&send_reg_buff[(mode_idx * 2 + 1) * sizeof(nr_param)] , &nr_param , sizeof(nr_param));
                        }
                    }
                }
                else//非首次读取只需读写三字节当前状态
                {
                    send_reg_buff[0] = tinput;
                    send_reg_buff[1] = mode;
                    send_reg_buff[2] = hdflag;
                }
            }


            Data2SNCMD(sl_hdl, SN_GET_DATA_VAL, send_reg_buff, ret_data_len);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(input_reg_buf);
            input_reg_buf = NULL;
            PROJECT_FREE(send_reg_buff);
            send_reg_buff = NULL;
        }
        break;
        case SN_SET_SOUND_VAL:
        {
            D_U8   suc = 0x00 , SPflag, en , i , j , pattern;
            D_U16 vol_diff = 0 , vol[TV_VOL_WAVE] , audio_factor[101];
            D_S16 nfft , freq , gain , bw;
            D_SRS_SET srs;
            D_AUDIO_Peq param[9];
            D_VidInput input;
            D_DisplayParam dis_param ;
            D_PanelParam panel_param;

            SPflag = cmd_buf[5];
            switch(SPflag)
            {
                case 0://srs_enable
                    en = cmd_buf[6];
                    (en == 0) ? (d_av_audio_srs(0, D_Surround_close)) : (d_av_audio_srs(0, D_Surround_open));
                    break;
                case 1://srs_data
                    srs.srs_time = cmd_buf[9]  << 24 | cmd_buf[8] << 16 | cmd_buf[7]  << 8 | cmd_buf[6];
                    srs.weight_coefficient = cmd_buf[13]  << 24 | cmd_buf[12] << 16 | cmd_buf[11]  << 8 | cmd_buf[10];
                    d_av_audio_srs_param_set(srs.srs_time , srs.weight_coefficient);
                    p_tvconf_set_srs(&srs);
                    break;
                case 2://peq_enable
                    en = cmd_buf[6];
                    d_av_peq_ctrl(0, en);
                    p_tvconf_set_avc_peq_en(en);
                    break;
                case 3://peq_data
                    input_reg_buf = (D_U8*)PROJECT_ALLOC(80);
                    if(input_reg_buf == NULL)
                    {
                        return D_ERR;
                    }
                    memset(input_reg_buf, 0, 80);
                    memcpy(input_reg_buf, &cmd_buf[6], 80);
                    for(i = 0; i < 9; i++)
                    {
                        memcpy(&freq , &input_reg_buf[6 * i], 2);
                        memcpy(&gain , &input_reg_buf[6 * i + 2], 2);
                        memcpy(&bw, &input_reg_buf[6 * i + 4], 2);
                        param[i].freq = freq;
                        param[i].gain = gain / 10.0;
                        param[i].bw = bw;
                    }
                    input_reg_buf += 54;
                    pattern = input_reg_buf[0];
                    if(input_reg_buf[1] == 0)
                        nfft = 64;
                    else if(input_reg_buf[1] == 1)
                        nfft = 128;
                    else if(input_reg_buf[1] == 2)
                        nfft = 256;
                    else if(input_reg_buf[1] == 3)
                        nfft = 512;
                    else if(input_reg_buf[1] == 4)
                        nfft = 1024;
                    else
                        nfft = 2048;
                    input_reg_buf -= 54;
                    d_av_Audio_PEQ(0, param, 9, nfft, D_PEQ);
                    input = p_conf_get_vid_input();

                    for(i = 0; i < 9; i++)
                    {
                        p_tvconf_set_audio_peq_set_param(&param[i], p_vip_get_dbinput(input), pattern, i);
                    }
                    p_tvconf_set_cur_t_ffft(&nfft, p_vip_get_dbinput(input), pattern);

                    PROJECT_FREE(input_reg_buf);
                    input_reg_buf = NULL;
                    break;
                case 4://vcom
                    p_conf_get_panel_param(&panel_param);
                    dis_param = panel_param.screenparam;
					dis_param.VCOM_StartPix = cmd_buf[7]  << 8 | cmd_buf[6];
                    dis_param.VCOM_StartLine = cmd_buf[9]  << 8 | cmd_buf[8];
                    dis_param.VCOM_DE_start_pix = cmd_buf[11]  << 8 | cmd_buf[10];
                    dis_param.VCOM_DE_start_line = cmd_buf[13]  << 8 | cmd_buf[12];
                    d_av_display_para_init(&dis_param);
                    panel_param.screenparam = dis_param;
                    p_conf_set_panel_param(&panel_param);					
                    break;
                case 5://vo
                    p_conf_get_panel_param(&panel_param);
                    dis_param = panel_param.screenparam;
                    dis_param.VO_feeder_vsync_line = cmd_buf[7]  << 8 | cmd_buf[6];
                    dis_param.VO_hs_vsync_pix = cmd_buf[9]  << 8 | cmd_buf[8];
                    dis_param.VO_hs_vsync_line = cmd_buf[11]  << 8 | cmd_buf[10];
                    dis_param.VO_set_pix_to_VeBypass = cmd_buf[13]  << 8 | cmd_buf[12];
                    dis_param.VO_set_pix_to_VeEnable = cmd_buf[15]  << 8 | cmd_buf[14];
                    d_av_display_para_init(&dis_param);
                    panel_param.screenparam = dis_param;
                    p_conf_set_panel_param(&panel_param);
                    break;
                case 6://sp
                    p_conf_get_panel_param(&panel_param);
                    dis_param = panel_param.screenparam;					
                    dis_param.SP_StartPix = cmd_buf[7]  << 8 | cmd_buf[6];
                    dis_param.SP_StartLine = cmd_buf[9]  << 8 | cmd_buf[8];
                    d_av_display_para_init(&dis_param);
                    panel_param.screenparam = dis_param;
                    p_conf_set_panel_param(&panel_param);					
                    break;
                case 7://osd
                    p_conf_get_panel_param(&panel_param);
                    dis_param = panel_param.screenparam;					
                    dis_param.OSD_set_pix_to = cmd_buf[7]  << 8 | cmd_buf[6];
                    dis_param.OSD_set_line_to_top = cmd_buf[9]  << 8 | cmd_buf[8];
                    d_av_display_para_init(&dis_param);
                    panel_param.screenparam = dis_param;
                    p_conf_set_panel_param(&panel_param);					
                    break;
                case 8://vol
                    input = p_conf_get_vid_input();
                    switch(input)
                    {
                        case D_VID_IUTPUT_TV:
                            p_tvconf_set_vol(&cmd_buf[6] , 0);
                            break;
                        case D_VID_IUTPUT_AV1:
                        case D_VID_IUTPUT_AV2:
                            p_tvconf_set_vol(&cmd_buf[6] , 1);
                            break;
                        case D_VID_IUTPUT_DTV:
                        case D_VID_IUTPUT_USB1:
                        case D_VID_IUTPUT_USB2:
                            p_tvconf_set_vol(&cmd_buf[6] , 2);
                            break;
                        case D_VID_IUTPUT_HDMI1:
                        case D_VID_IUTPUT_HDMI2:
                            p_tvconf_set_vol(&cmd_buf[6] , 3);
                            break;
                        default:
                            break;
                    }
                    memcpy(vol , &cmd_buf[6] , sizeof(vol));
                    memset(audio_factor , 0 , sizeof(audio_factor));

                    for(i = 0; i < TV_VOL_WAVE; i++)
                    {
                        (i == 0) ? (vol_diff = vol[i] / 5) : (vol_diff = (vol[i] - vol[i - 1]) / 5);
                        for(j = 1; j < 5; j++)
                        {
                            (i == 0) ? (audio_factor[5 * i + j] = j * vol_diff) : (audio_factor[5 * i + j] = vol[i - 1] + j * vol_diff);
                        }
                        audio_factor[5 * (i + 1)] = vol[i];
                    }
                    d_av_audio_factor_set(0 , audio_factor , 1 , input);
                    d_av_set_volume(0 , p_conf_get_volume());
                    break;
                case 9://avc
                    memcpy(&avc[0] , &cmd_buf[6] , sizeof(avc));
                    p_tvconf_set_avc(&avc[0]);
                    for(i = 0; i < 6; i++)
                    {
                        memset(&avc_param , 0 , sizeof(avc_param));
                        avc_param.base_level = avc[i].base_level;
                        avc_param.base_avc = avc[i].base_avc;
                        avc_param.level_step = avc[i].level_step;
                        avc_param.now_level_offset = avc[i].now_level_offset;
                        avc_param.now_close_avc = avc[i].now_close_avc;
                        avc_param.now_open_avc = avc[i].now_open_avc;
                        d_av_audio_avc_base_set(avc_param , i);
                    }
                    break;
                default:
                    break;
            }
            Data2SNCMD(sl_hdl, SN_SET_SOUND_VAL, &suc, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
        }
        break;
        case SN_GET_SOUND_VAL:
        {
            D_U8  SPflag , pattern , i , enable;
            D_SRS_SET srs;
            D_S16 nfft , freq , gain , bw;
            D_AUDIO_Peq param[9];
            D_VidInput input;
            D_DisplayParam dis_param , *p_dis_param;
            D_PanelParam panel_param;
            D_AVC_SET avc[TV_AVC_INPUT_NUM];

            send_reg_buff = (D_U8*)PROJECT_ALLOC(120);
            if(send_reg_buff == NULL)
            {
                return D_ERR;
            }
            memset(send_reg_buff, 0, 120);

            SPflag = cmd_buf[5];
            switch(SPflag)
            {
                case 0://srs_enable
                    break;
                case 1://srs_data
                    p_tvconf_get_srs(&srs);
                    memcpy(&send_reg_buff[0], &srs.srs_time, sizeof(D_U32));
                    memcpy(&send_reg_buff[4], &srs.weight_coefficient, sizeof(D_U32));
                    break;
                case 2://peq_enable
                    break;
                case 3://peq_data
                    pattern = cmd_buf[6];
                    input = p_conf_get_vid_input();
                    for(i = 0; i < 9; i++)
                    {
                        p_tvconf_get_audio_peq_set_param(&param[i], p_vip_get_dbinput(input), pattern, i);
                        freq = param[i].freq;
                        gain = param[i].gain * 10;
                        bw = param[i].bw;

                        memcpy(&send_reg_buff[6 * i] , &freq, 2);
                        memcpy(&send_reg_buff[6 * i + 2] , &gain, 2);
                        memcpy(&send_reg_buff[6 * i + 4], &bw , 2);
                    }
                    send_reg_buff += 54;
                    p_tvconf_get_cur_t_ffft(&nfft, p_vip_get_dbinput(input), pattern);
                    if(nfft == 64)
                        send_reg_buff[0] = 0;
                    else if(nfft == 128)
                        send_reg_buff[0] = 1;
                    else if(nfft == 256)
                        send_reg_buff[0] = 2;
                    else if(nfft == 512)
                        send_reg_buff[0] = 3;
                    else if(nfft == 1024)
                        send_reg_buff[0] = 4;
                    else
                        send_reg_buff[0] = 5;
                    send_reg_buff   -= 54;
                    break;
                case 4://screen
                    p_conf_get_panel_param(&panel_param);
                    p_dis_param = &dis_param;
                    memset(p_dis_param, 0, sizeof(D_DisplayParam));
                    dis_param = panel_param.screenparam;
                    send_reg_buff[0] = dis_param.VCOM_StartPix;
                    send_reg_buff[1] = dis_param.VCOM_StartPix >> 8;
                    send_reg_buff[2] = dis_param.VCOM_StartLine;
                    send_reg_buff[3] = dis_param.VCOM_StartLine >> 8;
                    send_reg_buff[4] = dis_param.VCOM_DE_start_pix;
                    send_reg_buff[5] = dis_param.VCOM_DE_start_pix >> 8;
                    send_reg_buff[6] = dis_param.VCOM_DE_start_line;
                    send_reg_buff[7] = dis_param.VCOM_DE_start_line >> 8;
                    send_reg_buff += 8;

                    send_reg_buff[0] = dis_param.VO_feeder_vsync_line;
                    send_reg_buff[1] = dis_param.VO_feeder_vsync_line >> 8;
                    send_reg_buff[2] = dis_param.VO_hs_vsync_pix;
                    send_reg_buff[3] = dis_param.VO_hs_vsync_pix >> 8;
                    send_reg_buff[4] = dis_param.VO_hs_vsync_line;
                    send_reg_buff[5] = dis_param.VO_hs_vsync_line >> 8;
                    send_reg_buff[6] = dis_param.VO_set_pix_to_VeBypass;
                    send_reg_buff[7] = dis_param.VO_set_pix_to_VeBypass >> 8;
                    send_reg_buff[8] = dis_param.VO_set_pix_to_VeEnable;
                    send_reg_buff[9] = dis_param.VO_set_pix_to_VeEnable >> 8;
                    send_reg_buff += 10;

                    send_reg_buff[0] = dis_param.SP_StartPix;
                    send_reg_buff[1] = dis_param.SP_StartPix >> 8;
                    send_reg_buff[2] = dis_param.SP_StartLine;
                    send_reg_buff[3] = dis_param.SP_StartLine >> 8;
                    send_reg_buff += 4;

                    send_reg_buff[0] = dis_param.OSD_set_pix_to;
                    send_reg_buff[1] = dis_param.OSD_set_pix_to >> 8;
                    send_reg_buff[2] = dis_param.OSD_set_line_to_top;
                    send_reg_buff[3] = dis_param.OSD_set_line_to_top >> 8;
                    send_reg_buff += 4;

                    send_reg_buff -= 26;
                    break;
                case 5://vol
                    input = p_conf_get_vid_input();
                    switch(input)
                    {
                        case D_VID_IUTPUT_TV:
                            p_tvconf_get_vol(send_reg_buff, 0);
                            break;
                        case D_VID_IUTPUT_AV1:
                        case D_VID_IUTPUT_AV2:
                            p_tvconf_get_vol(send_reg_buff, 1);
                            break;
                        case D_VID_IUTPUT_DTV:
                        case D_VID_IUTPUT_USB1:
                        case D_VID_IUTPUT_USB2:
                            p_tvconf_get_vol(send_reg_buff, 2);
                            break;
                        case D_VID_IUTPUT_HDMI1:
                        case D_VID_IUTPUT_HDMI2:
                            p_tvconf_get_vol(send_reg_buff, 3);
                            break;
                        default:
                            break;
                    }
                    break;
                case 6://avc
                    p_tvconf_get_avc(&avc[0]);		
                    memcpy(send_reg_buff , &avc[0] , sizeof(avc));
                    break;
                default:
                    break;
            }
            Data2SNCMD(sl_hdl, SN_GET_SOUND_VAL, send_reg_buff, 120);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);

            PROJECT_FREE(send_reg_buff);
            send_reg_buff = NULL;
        }
        break;
        default:
            break;
    }

    return D_OK;
}

static D_Result rev_command_func(D_U8 *buf_rciv, D_HSerial sl_hdl)
{
    D_Result ret = D_ERR;

    if((buf_rciv[0] == CMD_HEAD) && (gCmd_offset == 0))
    {
        serial_data->cmd_buff[gCmd_offset] = buf_rciv[0];
        gCmd_crc = 0x00;
        gCmd_flag = 1;
    }
    else
    {
        serial_data->cmd_buff[++gCmd_offset] = buf_rciv[0];

        if( gCmd_offset > 2 ) //接收过2个字节的 length后，再解析
        {
            D_U16 SnLength = 0;

            SnLength = (serial_data->cmd_buff[1] << 8) | serial_data->cmd_buff[2] ;

            if( SnLength == 0 || SnLength > SERIAL_BUF_LENGTH )
            {
                return D_ERR;
            }

            if(gCmd_offset < HEAD_BYTE + LEN_BYTE + SnLength - CRC_BYTE) // 数据头+2字节的length+length-4字节的CRC
            {
                gCmd_crc += buf_rciv[0];
            }
            else
            {
                if( gCmd_offset == HEAD_BYTE + LEN_BYTE + SnLength - TAIL_BYTE ) //接收到所有SN数据，除尾以外
                {
                    D_U32 SnCrc;

                    //解析发送端的CRC
                    SnCrc = (serial_data->cmd_buff[HEAD_BYTE + LEN_BYTE + SnLength - CRC_BYTE] << 24)
                            | (serial_data->cmd_buff[HEAD_BYTE + LEN_BYTE + SnLength - CRC_BYTE + 1] << 16)
                            | (serial_data->cmd_buff[HEAD_BYTE + LEN_BYTE + SnLength - CRC_BYTE + 2] << 8)
                            | serial_data->cmd_buff[HEAD_BYTE + LEN_BYTE + SnLength - CRC_BYTE + 3];

                    gCmd_crc ^= 0xFF; //异或
                    gCmd_crc += 0x01;

                    if(gCmd_crc != SnCrc)
                    {
                        return D_ERR;
                    }
                }
            }

            if( serial_data->cmd_buff[HEAD_BYTE + LEN_BYTE + SnLength] == CMD_TAIL )
            {
                ret = parse_reg_cmd(serial_data->cmd_buff, sl_hdl);
                if( ret != D_OK )
                {
                    return D_ERR;
                }
                gCmd_offset = 0;
                gCmd_crc = 0x00;
                memset(serial_data->cmd_buff, 0, SERIAL_BUF_LENGTH);
                gCmd_flag = 0;
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
    D_Size real_len = 0;
    D_U8    err = 0x02;

    memset(serial_data->buf_rciv, 0, serial_data->buf_len);
    real_len = d_serial_read(sl_hdl, serial_data->buf_rciv, UART_CMD_LENGTH);

    if(real_len > 0)
    {
        if(Uart_lock_flag == 0)
        {
            d_dbg_set_io_func(NULL, NULL);
            Uart_lock_flag = 1;
        }

        if(rev_command_func(serial_data->buf_rciv, sl_hdl) != D_OK)
        {
            if(gCmd_flag == 1)
            {
                gCmd_offset = 0;
                gCmd_flag = 0;
                memset(serial_data->cmd_buff, 0, SERIAL_BUF_LENGTH);
                Data2SNCMD(sl_hdl, SN_GREG_VAL, &err, 1);
                d_serial_flush(sl_hdl);
                d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
            }
        }
    }
    if(real_len == 0)
    {
        if(gCmd_flag == 1)
        {
            gCmd_offset = 0;
            gCmd_flag = 0;
            memset(serial_data->cmd_buff, 0, SERIAL_BUF_LENGTH);
            Data2SNCMD(sl_hdl, SN_GREG_VAL, &err, 1);
            d_serial_flush(sl_hdl);
            d_serial_write(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
        }

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
    PROJECT_FREE(serial_data->cmd_buff);
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
D_Result p_es_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT
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
