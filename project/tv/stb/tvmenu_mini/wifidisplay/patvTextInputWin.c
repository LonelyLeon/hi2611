/** @file
* @brief 语言设置菜单窗口模块
* @author 覃宜:
* @date 2017-10-18 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

/* 困系统总共最多只能使用256个控件，输入法菜单控件太多，
为避免影响系统其它菜单，可以使用area方式自定义绘制*/
#define MENU_USE_AREA_CONTROL (1)

#if MENU_USE_AREA_CONTROL
#include "atv_text_input_ex_window.c"
#else
#include "atv_text_input_window.c"
#endif

#define P_NAME_LEN (32)

#define P_DIRECTIONT_LEFT (0)
#define P_DIRECTIONT_RIGHT (1)
#define P_DIRECTIONT_UP     (2)
#define P_DIRECTIONT_DOWN (3)

#define P_TABLE_ROW_NUM (5)
#define P_TABLE_COL_NUM (11)
#define P_TABLE_BUTTON_CNT (P_TABLE_ROW_NUM * P_TABLE_COL_NUM)

typedef struct
{
    D_Char *str_normal;
    D_Char *str_caps;
    D_Char *str_normal_show_eng;
    D_Char *str_caps_show_eng;
    D_Char *str_normal_show_chn;
    D_Char *str_caps_show_chn;
} D_KeyTextInfo;



typedef struct
{
    D_U8   menu_lang;
    D_Bool  caps_flag;

    D_S16  char_cnt;
    D_S16  char_byte[P_NAME_LEN];

    D_S16  name_len;
    D_Char  strName[P_NAME_LEN + 4];

    D_Result (*handler) (D_Char *text, D_U32 param, D_U32 action) D_FUNCPOSTFIT;
    D_U32   param;
    D_Frame *frm;
    D_Char strtitle[64];
    D_Char strdef[P_NAME_LEN];
    D_U32 min_len;
    D_U32 max_len;
    D_Bool ok_enable;
#if MENU_USE_AREA_CONTROL
    D_ID  focus;
    D_Visual *vis_area;
#endif
} D_TextInputData;

static D_TextInputData    *textinput_data = NULL;

static D_KeyTextInfo key_text[] =
{
    {"a", "A"}, {"b", "B"}, {"c", "C"}, {"d", "D"}, {"e", "E"}, {"f", "F"}, {"g", "G"}, {"h", "H"}, {"i", "I"}, {"j", "J"}, {"A-a", "A-a"},
    {"k", "K"}, {"l", "L"}, {"m", "M"}, {"n", "N"}, {"o", "O"}, {"p", "P"}, {"q", "Q"}, {"r", "R"}, {"s", "S"}, {"t", "T"}, {"", "", "Del", "Del", "删除", "删除"},
    {"u", "U"}, {"v", "V"}, {"w", "W"}, {"x", "X"}, {"y", "Y"}, {"z", "Z"}, {"+", "+"}, {"=", "="}, {"-", "-"}, {"_", "_"}, {" ", " ", "Space", "Space", "空格", "空格"},
    {"1", "!"}, {"2", "@"}, {"3", "#"}, {"4", "$"}, {"5", "%"}, {"6", "^"}, {"7", "&"}, {"8", "*"}, {"9", "("}, {"0", ")"}, {"", "", "Esc", "Esc",  "退出", "退出"},
    {"[", "{"}, {"]", "}"}, {",", "<"}, {".", ">"}, {"/", "?"}, {";", ":"}, {"'", "\""}, {"\\", "|"}, {"`", "~"}, {"@", "|"}, {"", "", "OK", "OK", "确认", "确认"},
};


/** @brief通知用户编辑结果*/
static D_Result
text_input_inform_user(D_U32 action) D_FUNCPOSTFIT
{
    D_U32        param;
    D_Result (*handler) (D_Char * text, D_U32 param, D_U32 action) D_FUNCPOSTFIT;

    param = textinput_data->param;
    handler = textinput_data->handler;

    if (handler)
    {
        handler(textinput_data->strName, param, action);
    }

    return D_OK;
}

#if MENU_USE_AREA_CONTROL == 0
static D_Result
text_input_show_key_text (void) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_ID     id;
    D_Char *strtext = NULL;

    for(id = 0; id < P_TABLE_BUTTON_CNT; id++)
    {
        vis = d_frame_get_control(textinput_data->frm, (id + ID_TEXTINPUT_BUTTON_00));
        if(vis)
        {
            strtext = NULL;
            if(textinput_data->caps_flag == D_FALSE)
            {
                if(textinput_data->menu_lang == D_LANG_ENG && key_text[i].str_normal_show_eng)
                {
                    strtext = key_text[i].str_normal_show_eng;
                }
                else if(textinput_data->menu_lang == D_LANG_CHN && key_text[i].str_normal_show_chn)
                {
                    strtext = key_text[i].str_normal_show_chn;
                }
                if(strtext == NULL)
                {
                    strtext = key_text[i].str_normal;
                }
            }
            else
            {
                if(textinput_data->menu_lang == D_LANG_ENG && key_text[i].str_caps_show_eng)
                {
                    strtext = key_text[i].str_caps_show_eng;
                }
                else if(textinput_data->menu_lang == D_LANG_CHN && key_text[i].str_caps_show_chn)
                {
                    strtext = key_text[i].str_caps_show_chn;
                }
                if(strtext == NULL)
                {
                    strtext = key_text[i].str_caps;
                }
            }

            d_button_set_text(vis, strtext);
        }
    }
    return D_OK;
}

static D_Result
text_input_change_focus(D_U32 direction) D_FUNCPOSTFIT
{
    D_Visual    * win, *vis;
    D_ID     id, off;

    win = d_frame_get_control(textinput_data->frm, 0);
    vis = d_vis_get_focus(win);
    id = d_frame_get_control_id(textinput_data->frm, vis);
    id = id - ID_TEXTINPUT_BUTTON_00;

    if(direction == P_DIRECTIONT_LEFT)
    {
        if(id % P_TABLE_COL_NUM)
        {
            id = id - 1;
        }
        else
        {
            id = id + (P_TABLE_COL_NUM - 1);
        }
    }
    else if(direction == P_DIRECTIONT_RIGHT)
    {
        if((id % P_TABLE_COL_NUM) != (P_TABLE_COL_NUM - 1))
        {
            id = id + 1;
        }
        else
        {
            id = id - (P_TABLE_COL_NUM - 1);
        }
    }
    else if(direction == P_DIRECTIONT_UP)
    {
        if(id < P_TABLE_COL_NUM)
        {
            id = id + (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1));
        }
        else
        {
            id = id - P_TABLE_COL_NUM;
        }
    }
    else if(direction == P_DIRECTIONT_DOWN)
    {
        if(id < (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1)))
        {
            id = id + P_TABLE_COL_NUM;
        }
        else
        {
            id = id - (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1));
        }
    }

    id = id + ID_TEXTINPUT_BUTTON_00;
    vis = d_frame_get_control(textinput_data->frm, id);
    {
        d_vis_set_focus(vis);
    }

    return D_OK;
}

static D_Result
text_input_show_text(void) D_FUNCPOSTFIT
{
    D_Visual *vis;

    vis = d_frame_get_control(textinput_data->frm, ID_TEXTINPUT_LABEL_TEXT);
    if(vis)
    {
        d_label_set_text(vis, textinput_data->strName);
    }

    return D_OK;
}

static D_Result
text_input_add_char(D_Visual *vis, D_Char ch) D_FUNCPOSTFIT
{
    D_ID     id;
    D_U16  len;
    D_Char *strc = NULL;
    D_Char strchar[8] = {0};

    if(vis)
    {
        id = d_frame_get_control_id(textinput_data->frm, vis);
        id = id - ID_TEXTINPUT_BUTTON_00;

        if(textinput_data->caps_flag == D_FALSE)
        {
            strc = key_text[id].str_normal;
        }
        else
        {
            strc = key_text[id].str_caps;
        }
    }
    else if(ch >= 0x20 && ch <= 0x80)
    {
        strchar[0] = ch;
        strc = strchar;
    }

    if(strc && textinput_data->name_len < textinput_data->max_len)
    {
        len = strlen(strc);
        if(textinput_data->name_len + len <= textinput_data->max_len)
        {
            strcat(textinput_data->strName, strc);
            textinput_data->char_byte[textinput_data->char_cnt++] = len;
            textinput_data->name_len = textinput_data->name_len + len;
            if(textinput_data->name_len >= textinput_data->min_len && textinput_data->ok_enable == D_FALSE)
            {
                textinput_data->ok_enable = D_TRUE;
            }
            else if(textinput_data->name_len < textinput_data->min_len && textinput_data->ok_enable == D_TRUE)
            {
                textinput_data->ok_enable = D_FALSE;
            }
            text_input_show_text();
        }
    }

    return D_OK;
}

static D_Result
text_input_del_char(void) D_FUNCPOSTFIT
{
    D_S16  len;

    if(textinput_data->name_len)
    {
        len = textinput_data->char_byte[textinput_data->char_cnt - 1];
        textinput_data->name_len = D_MAX(0, textinput_data->name_len - len);
        if(textinput_data->name_len >= textinput_data->min_len && textinput_data->ok_enable == D_FALSE)
        {
            textinput_data->ok_enable = D_TRUE;
        }
        else if(textinput_data->name_len < textinput_data->min_len && textinput_data->ok_enable == D_TRUE)
        {
            textinput_data->ok_enable = D_FALSE;
        }
        textinput_data->strName[textinput_data->name_len] = '\0';
        textinput_data->strName[textinput_data->name_len + 1] = '\0';
        textinput_data->char_byte[textinput_data->char_cnt - 1] = 0;
        textinput_data->char_cnt--;
        text_input_show_text();
    }

    return D_OK;
}

static D_Result
text_input_clear_input(void) D_FUNCPOSTFIT
{
    if(textinput_data->name_len)
    {
        memset(textinput_data->char_byte, 0x00, sizeof(textinput_data->char_byte));
        memset(textinput_data->strName, 0x00, sizeof(textinput_data->strName));
        textinput_data->name_len = 0;
        textinput_data->char_cnt = 0;
        if(textinput_data->name_len < textinput_data->min_len)
        {
            textinput_data->ok_enable = D_FALSE;
        }
        text_input_show_text();
    }

    return D_OK;
}

static D_Result
text_input_save_input(void) D_FUNCPOSTFIT
{
    if(textinput_data->name_len)
    {
        memset(textinput_data->char_byte, 0x00, sizeof(textinput_data->char_byte));
        memset(textinput_data->strName, 0x00, sizeof(textinput_data->strName));
        textinput_data->name_len = 0;
        textinput_data->char_cnt = 0;
        text_input_show_text();
    }

    return D_OK;
}

static D_Result
text_input_esc_input(void) D_FUNCPOSTFIT
{
    if(textinput_data->name_len)
    {
        memset(textinput_data->char_byte, 0x00, sizeof(textinput_data->char_byte));
        memset(textinput_data->strName, 0x00, sizeof(textinput_data->strName));
        textinput_data->name_len = 0;
        textinput_data->char_cnt = 0;
        text_input_show_text();
    }

    return D_OK;
}

/** @brief 字符key 用户回调*/
static D_Result
char_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            return text_input_add_char(vis, 0);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief caps key 用户回调*/
static D_Result
caps_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            textinput_data->caps_flag = !textinput_data->caps_flag;
            return text_input_show_key_text();
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief del key 用户回调*/
static D_Result
del_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            return text_input_del_char();
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief esc key 用户回调*/
static D_Result
esc_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            text_input_inform_user(0);
            p_atv_textinput_window_colse();
            return D_OK;
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief ok key 用户回调*/
static D_Result
ok_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            if(textinput_data->ok_enable)
            {
                text_input_inform_user(1);
                p_atv_textinput_window_colse();
            }
            return D_OK;
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
text_input_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    text_input_inform_user(0);
                    p_atv_textinput_window_colse();
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    text_input_change_focus(P_DIRECTIONT_LEFT);
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    text_input_change_focus(P_DIRECTIONT_RIGHT);
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    text_input_change_focus(P_DIRECTIONT_UP);
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    text_input_change_focus(P_DIRECTIONT_DOWN);
                    break;
                    break;
                default:
                    if ((evt->fp.key >= D_KEY_0) && (evt->fp.key <= D_KEY_9))
                    {
                        /* 数字键时，直接添加对应的数字字符*/
                        return text_input_add_char(NULL, ('0' + (evt->fp.key - D_KEY_0)));
                    }
                    break;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(textinput_data)
            {
                PROJECT_FREE(textinput_data);
                textinput_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_text_input_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_ID     id;

    textinput_data->frm = frm;
    textinput_data->menu_lang = p_conf_get_lang();
    vis = d_frame_get_control(frm, ID_TEXTINPUT_LABEL_TITLE);
    if(vis)
    {
        d_label_set_text(vis, textinput_data->strtitle);
    }

    for(id = 0; id < P_TABLE_BUTTON_CNT; id++)
    {
        vis = d_frame_get_control(frm, (id + ID_TEXTINPUT_BUTTON_00));
        if(vis)
        {
            d_vis_set_handler (vis, char_button_handler);
        }
    }

    vis = d_frame_get_control(frm, (ID_TEXTINPUT_BUTTON_00 + P_TABLE_COL_NUM - 1));
    if(vis)
    {
        d_vis_set_handler (vis, caps_button_handler);
    }

    vis = d_frame_get_control(frm, (ID_TEXTINPUT_BUTTON_00 + P_TABLE_COL_NUM * 2 - 1));
    if(vis)
    {
        d_vis_set_handler (vis, del_button_handler);
    }

    vis = d_frame_get_control(frm, (ID_TEXTINPUT_BUTTON_00 + P_TABLE_COL_NUM * 4 - 1));
    if(vis)
    {
        d_vis_set_handler (vis, esc_button_handler);
    }

    vis = d_frame_get_control(frm, (ID_TEXTINPUT_BUTTON_00 + P_TABLE_COL_NUM * 5 - 1));
    if(vis)
    {
        d_vis_set_handler (vis, ok_button_handler);
    }

    text_input_show_key_text();
    if(textinput_data->strdef[0])
    {
        D_U32 len;
        len = strlen(textinput_data->strdef);
        if(textinput_data->name_len + len <= textinput_data->max_len)
        {
            strcat(textinput_data->strName, textinput_data->strdef);
            textinput_data->name_len = textinput_data->name_len + len;
            textinput_data->char_cnt = textinput_data->name_len;
            if(textinput_data->name_len >= textinput_data->min_len)
            {
                textinput_data->ok_enable = D_TRUE;
            }
            for(len = 0; len < textinput_data->char_cnt; len++)
            {
                textinput_data->char_byte[len] = 1;
            }
            text_input_show_text();
        }
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, text_input_window_handler);
    }

    return D_OK;
}

#else


static D_Result
text_input_change_focus(D_U32 direction) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID     id;

    id = textinput_data->focus;

    if(direction == P_DIRECTIONT_LEFT)
    {
        if(id % P_TABLE_COL_NUM)
        {
            id = id - 1;
        }
        else
        {
            id = id + (P_TABLE_COL_NUM - 1);
        }
    }
    else if(direction == P_DIRECTIONT_RIGHT)
    {
        if((id % P_TABLE_COL_NUM) != (P_TABLE_COL_NUM - 1))
        {
            id = id + 1;
        }
        else
        {
            id = id - (P_TABLE_COL_NUM - 1);
        }
    }
    else if(direction == P_DIRECTIONT_UP)
    {
        if(id < P_TABLE_COL_NUM)
        {
            id = id + (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1));
        }
        else
        {
            id = id - P_TABLE_COL_NUM;
        }
    }
    else if(direction == P_DIRECTIONT_DOWN)
    {
        if(id < (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1)))
        {
            id = id + P_TABLE_COL_NUM;
        }
        else
        {
            id = id - (P_TABLE_COL_NUM * (P_TABLE_ROW_NUM - 1));
        }
    }

    textinput_data->focus = id;
    d_vis_update(textinput_data->vis_area, NULL);

    return D_OK;
}

static D_Result
text_input_show_text(void) D_FUNCPOSTFIT
{
    D_Visual *vis;

    vis = d_frame_get_control(textinput_data->frm, ID_TEXTINPUT_LABEL_TEXT);
    if(vis)
    {
        d_label_set_text(vis, textinput_data->strName);
    }

    return D_OK;
}

static D_Result
text_input_add_char(D_Visual *vis, D_Char ch) D_FUNCPOSTFIT
{
    D_ID     id;
    D_U16  len;
    D_Char *strc = NULL;
    D_Char strchar[8] = {0};

    if(vis)
    {
        id = textinput_data->focus;

        if(textinput_data->caps_flag == D_FALSE)
        {
            strc = key_text[id].str_normal;
        }
        else
        {
            strc = key_text[id].str_caps;
        }
    }
    else if(ch >= 0x20 && ch <= 0x80)
    {
        strchar[0] = ch;
        strc = strchar;
    }

    if(strc && textinput_data->name_len < textinput_data->max_len)
    {
        len = strlen(strc);
        if(textinput_data->name_len + len <= textinput_data->max_len)
        {
            strcat(textinput_data->strName, strc);
            textinput_data->char_byte[textinput_data->char_cnt++] = len;
            textinput_data->name_len = textinput_data->name_len + len;
            if(textinput_data->name_len >= textinput_data->min_len && textinput_data->ok_enable == D_FALSE)
            {
                textinput_data->ok_enable = D_TRUE;
                d_vis_update(textinput_data->vis_area, NULL);
            }
            else if(textinput_data->name_len < textinput_data->min_len && textinput_data->ok_enable == D_TRUE)
            {
                textinput_data->ok_enable = D_FALSE;
                d_vis_update(textinput_data->vis_area, NULL);
            }
            text_input_show_text();
        }
    }

    return D_OK;
}

static D_Result
text_input_del_char(void) D_FUNCPOSTFIT
{
    D_S16  len;

    if(textinput_data->name_len)
    {
        len = textinput_data->char_byte[textinput_data->char_cnt - 1];
        textinput_data->name_len = D_MAX(0, textinput_data->name_len - len);
        textinput_data->strName[textinput_data->name_len] = '\0';
        textinput_data->strName[textinput_data->name_len + 1] = '\0';
        textinput_data->char_byte[textinput_data->char_cnt - 1] = 0;
        textinput_data->char_cnt--;
        if(textinput_data->name_len >= textinput_data->min_len && textinput_data->ok_enable == D_FALSE)
        {
            textinput_data->ok_enable = D_TRUE;
            d_vis_update(textinput_data->vis_area, NULL);
        }
        else if(textinput_data->name_len < textinput_data->min_len && textinput_data->ok_enable == D_TRUE)
        {
            textinput_data->ok_enable = D_FALSE;
            d_vis_update(textinput_data->vis_area, NULL);
        }
        text_input_show_text();
    }

    return D_OK;
}

static D_Result
text_input_clear_char(void) D_FUNCPOSTFIT
{
    if(textinput_data->name_len)
    {
        memset(textinput_data->char_byte, 0x00, sizeof(textinput_data->char_byte));
        memset(textinput_data->strName, 0x00, sizeof(textinput_data->strName));
        textinput_data->name_len = 0;
        textinput_data->char_cnt = 0;
        if(textinput_data->name_len < textinput_data->min_len && textinput_data->ok_enable == D_TRUE)
        {
            textinput_data->ok_enable = D_FALSE;
            d_vis_update(textinput_data->vis_area, NULL);
        }
        text_input_show_text();
    }

    return D_OK;
}


#define POS_X_START (20)
#define POS_Y_START (10)
#define POS_BUTTON_W (32)
#define POS_BUTTON_WL (60)
#define POS_BUTTON_H (34)
#define POS_X_OFFSET (7)
#define POS_Y_OFFSET (8)

/** @brief del/ cancel key 用户回调*/
static D_Result
text_input_area_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    if(evt->type == D_EVT_DRAW)
    {
        D_ID i, vis_id;
        D_Coord x, y, w, h;
        D_Rect r;
        D_FontAttribute font;
        D_TextFormat form;
        D_Char *strtext = NULL;

        d_vis_set_mode((vis->flags & D_VIS_FL_TRANSPARENT \
        ? D_GSURF_DRAW_MODE_ALPHABLEND : D_GSURF_DRAW_MODE_NORMAL) | D_GSURF_DRAW_MODE_TILE);

        memset(&font, 0x00, sizeof(D_FontAttribute));
        memset(&form, 0x00, sizeof(D_TextFormat));

        for(i = 0; i < P_TABLE_BUTTON_CNT; i++)
        {
            x = POS_X_START + (i % P_TABLE_COL_NUM) * (POS_BUTTON_W + POS_X_OFFSET);
            y = POS_Y_START + (i / P_TABLE_COL_NUM) * (POS_BUTTON_H + POS_Y_OFFSET);
            w = ((i % P_TABLE_COL_NUM) == (P_TABLE_COL_NUM - 1)) ? POS_BUTTON_WL : POS_BUTTON_W;
            h = POS_BUTTON_H;
            d_rect_set (&r, x, y, w, h);

            //d_draw_image (vis, &r, bgImageId, (D_ALIGN_CENTER | D_ALIGN_MIDDLE));
            gui_tool_draw_fill_round_rect(vis, r.x, r.y, r.w, r.h, 4, ((i == textinput_data->focus) ? 0xfff1a81b : 0xffa7a7a8));
            font.fontSize = (D_U16)24;
            font.fontType = (D_U16)D_FONT_DOT_MATRIX;
            font.fontColor = (D_Color)0xFF000000;
            form.align = (D_U16)(D_ALIGN_CENTER | D_ALIGN_MIDDLE);
            form.valid = D_TRUE;

            strtext = NULL;
            if(textinput_data->caps_flag == D_FALSE)
            {
                if(textinput_data->menu_lang == D_LANG_ENG && key_text[i].str_normal_show_eng)
                {
                    strtext = key_text[i].str_normal_show_eng;
                }
                else if(textinput_data->menu_lang == D_LANG_CHN && key_text[i].str_normal_show_chn)
                {
                    strtext = key_text[i].str_normal_show_chn;
                }
                if(strtext == NULL)
                {
                    strtext = key_text[i].str_normal;
                }
            }
            else
            {
                if(textinput_data->menu_lang == D_LANG_ENG && key_text[i].str_caps_show_eng)
                {
                    strtext = key_text[i].str_caps_show_eng;
                }
                else if(textinput_data->menu_lang == D_LANG_CHN && key_text[i].str_caps_show_chn)
                {
                    strtext = key_text[i].str_caps_show_chn;
                }
                if(strtext == NULL)
                {
                    strtext = key_text[i].str_caps;
                }
            }

            if(textinput_data->ok_enable == D_FALSE && i == (P_TABLE_BUTTON_CNT - 1)) /*最后一项是确认*/
            {
                font.fontColor = (D_Color)0xff7f7f7f;
            }

            d_draw_text(vis, &r, strtext, strlen(strtext), &font, &form);
        }
    }
    return D_OK;
}

/** @brief del/ cancel key 用户回调*/
static D_Result
text_input_ok_action (D_Visual * vis) D_FUNCPOSTFIT
{
    if(textinput_data->focus == (P_TABLE_COL_NUM - 1))
    {
        textinput_data->caps_flag = !textinput_data->caps_flag;
        d_vis_update(textinput_data->vis_area, NULL);
    }
    else if(textinput_data->focus == (P_TABLE_COL_NUM * 2 - 1))
    {
        text_input_del_char();
    }
    else if(textinput_data->focus == (P_TABLE_COL_NUM * 4 - 1))
    {
        text_input_inform_user(0);
        p_atv_textinput_window_colse();
    }
    else if(textinput_data->focus == (P_TABLE_COL_NUM * 5 - 1))
    {
        if(textinput_data->ok_enable)
        {
            text_input_inform_user(1);
            p_atv_textinput_window_colse();
        }
    }
    else
    {
        text_input_add_char(vis, 0);
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
text_input_window_handler (D_Visual * vis, D_Event * evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    text_input_inform_user(0);
                    p_atv_textinput_window_colse();
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    text_input_ok_action(vis);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    text_input_change_focus(P_DIRECTIONT_LEFT);
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    text_input_change_focus(P_DIRECTIONT_RIGHT);
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    text_input_change_focus(P_DIRECTIONT_UP);
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    text_input_change_focus(P_DIRECTIONT_DOWN);
                    break;
                case D_KEY_RED:
                    text_input_del_char();
                    break;
                case D_KEY_BLUE:
                    textinput_data->caps_flag = !textinput_data->caps_flag;
                    d_vis_update(textinput_data->vis_area, NULL);
                    break;
                case D_KEY_GREEN:
                    if(textinput_data->ok_enable)
                    {
                        text_input_inform_user(1);
                        p_atv_textinput_window_colse();
                    }
                    break;
                default:
                    if ((evt->fp.key >= D_KEY_0) && (evt->fp.key <= D_KEY_9))
                    {
                        /* 数字键时，直接添加对应的数字字符*/
                        return text_input_add_char(NULL, ('0' + (evt->fp.key - D_KEY_0)));
                    }
                    break;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(textinput_data)
            {
                PROJECT_FREE(textinput_data);
                textinput_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_text_input_window_init (D_Frame * frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;

    textinput_data->frm = frm;
    textinput_data->menu_lang = p_conf_get_lang();

    vis = d_frame_get_control(frm, ID_TEXTINPUT_LABEL_TITLE);
    if(vis)
    {
        d_label_set_text(vis, textinput_data->strtitle);
    }

    vis = d_frame_get_control(frm, ID_TEXTINPUT_AREA);
    if(vis)
    {
        textinput_data->vis_area = vis;
        d_vis_set_handler (vis, text_input_area_handler);
    }

    if(textinput_data->strdef[0])
    {
        D_U32 len;
        len = strlen(textinput_data->strdef);
        if(textinput_data->name_len + len <= textinput_data->max_len)
        {
            strcat(textinput_data->strName, textinput_data->strdef);
            textinput_data->name_len = textinput_data->name_len + len;
            textinput_data->char_cnt = textinput_data->name_len;
            if(textinput_data->name_len >= textinput_data->min_len)
            {
                textinput_data->ok_enable = D_TRUE;
            }
            for(len = 0; len < textinput_data->char_cnt; len++)
            {
                textinput_data->char_byte[len] = 1;
            }
            text_input_show_text();
        }

        /* 已有内容，焦点定于确定键上*/
        if(textinput_data->ok_enable && textinput_data->name_len)
        {
            textinput_data->focus = (P_TABLE_COL_NUM * 5 - 1);
        }
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, text_input_window_handler);
    }

    return D_OK;
}

#endif

/** @brief 文本输入 窗口显示(只支持英文数字与符号)
* @param strtitle           要显示的标题文本
* @param strdef         默认文本(只支持英文数字与符号)
* @param handler        用户确认后调用的函数指针
* @param param          传给用户回调的参数
*/
D_Result
p_atv_textinput_window_show(D_Char *strtitle, D_Char *strdef,  D_U32 min_len, D_U32 max_len, D_Result (*handler) (D_Char *text, D_U32 param, D_U32 action) D_FUNCPOSTFIT, D_U32 param )D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;

    if(D_FALSE == d_frame_is_loaded(&atv_text_input_window))
    {
        D_FrameControlDescr *pcdescr;

        textinput_data = (D_TextInputData*)PROJECT_ALLOC(sizeof(D_TextInputData));
        if(!textinput_data)
        {
            return D_ERR;
        }
        memset(textinput_data, 0x00, sizeof(D_TextInputData));
        textinput_data->min_len = D_MAX(0, min_len);
        textinput_data->max_len = D_MIN(max_len, P_NAME_LEN);
        textinput_data->param = param;
        textinput_data->handler = handler;
        if(strtitle)
        {
            strncpy(textinput_data->strtitle, strtitle,  sizeof(textinput_data->strtitle));
            textinput_data->strtitle[sizeof(textinput_data->strtitle) - 1] = '\0';
        }
        if(strdef)
        {
            strncpy(textinput_data->strdef, strdef,  sizeof(textinput_data->strdef));
            textinput_data->strdef[sizeof(textinput_data->strdef) - 1] = '\0';
        }

        pcdescr = (D_FrameControlDescr *)atv_text_input_window.ctrl_descrs;
        pcdescr[0].x = pcdescr[0].x;
        pcdescr[0].paly = pcdescr[0].paly;
        ret = d_gui_open_frame(&atv_text_input_window, D_GUI_LAYER_USER);
        if(ret != D_OK && textinput_data)
        {
            PROJECT_FREE(textinput_data);
            textinput_data = NULL;
        }
    }
    return ret;
}

/** @brief rename 文本输入窗口关闭*/
D_Result
p_atv_textinput_window_colse(void)D_FUNCPOSTFIT
{
    if(d_frame_is_loaded(&atv_text_input_window))
    {
        d_gui_close_frame(&atv_text_input_window);
    }
    return D_OK;
}
