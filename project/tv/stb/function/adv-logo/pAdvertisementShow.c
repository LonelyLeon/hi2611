/** @file
* @brief ÂπøÂëäÊ®°ÂùóÊòæÁ§∫Êé•Âè£
* @author liuwf
* @date 2014-03-07 liuwf: Âª∫Á´ãÊñá‰ª∂
*/
#include "dDebug.h"
#include <string.h>
#include "dTypes.h"
#include "dGUI.h"
#include "dCBMan.h"
#include "dGraph.h"
#include "pAdvertisementShow.h"
#include "dadporting.h"
#include "dVisual.h"
#include "dScroll.h"


#define MAX_AD_PICT_NUM 5
#define MAX_AD_SCROLL_NUM 2

#define MAX_SCROLL_W  (D_SCREEN_HOR_RESOLUTION-20)
#define MAX_SCROLL_H  (D_SCREEN_VER_RESOLUTION-20)

typedef struct
{
    D_Visual *parent_vis;
    D_U16 parent_pos_x;
    D_U16 parent_pos_y;
    D_U16 parent_width;
    D_U16 parent_height;
    D_Ad_Pos_Type pos_type;
    D_Handle hcbm;
} menu_win_param;

typedef struct
{
    D_Visual *child_vis;
    D_Ptr  img;
    D_U32  id;
    D_Bool valid;
    D_Handle scroll_hdl[MAX_AD_SCROLL_NUM];
} img_param;

typedef struct
{
    D_U32 state;
    D_U8  childtype;
    menu_win_param menu_info;
    img_param img_info[MAX_AD_PICT_NUM];
    D_HSem      hsem;
} ad_show_param;

static ad_show_param ad_info[DAD_STB_POS_UNKNOWN];
static D_Bool init_flag = D_FALSE;
static D_Ad_Service_Param curr_chan_param;
static D_DBSrvID curr_DBSrvID = -1;

/** @brief  p_ad_find_id
* @param[in] D_U8 type   ◊¢ Õ
* @param[in] D_U32 ID    ◊¢ Õ
* @param[in] D_U8* idx   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result p_ad_find_id(D_U8 type, D_U32 ID, D_U8* idx)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < MAX_AD_PICT_NUM ; i++)
    {
        if(ad_info[type - 1].img_info[i].valid == D_TRUE && ad_info[type - 1].img_info[i].id == ID)
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}
/** @brief  p_ad_find_idle
* @param[in] D_U8 type   ◊¢ Õ
* @param[in] D_U8* idx   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result p_ad_find_idle(D_U8 type, D_U8* idx)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < MAX_AD_PICT_NUM ; i++)
    {
        if(ad_info[type - 1].img_info[i].valid == D_FALSE)
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}
/** @brief  p_ad_clean_one
* @param[in] D_U8 type   ◊¢ Õ
* @param[in] D_U8 idx    ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static void p_ad_clean_one(D_U8 type, D_U8 idx)D_FUNCPOSTFIT
{
    D_U8 i;
    if(ad_info[type - 1].img_info[idx].valid == D_TRUE)
    {
        for(i = 0 ; i < MAX_AD_SCROLL_NUM ; i++)
        {
            if(ad_info[type - 1].img_info[idx].scroll_hdl[i] != D_INVALID_HANDLE)
            {
                d_scroll_clear(ad_info[type - 1].img_info[idx].scroll_hdl[i]);
                d_scroll_destory(ad_info[type - 1].img_info[idx].scroll_hdl[i]);
                ad_info[type - 1].img_info[idx].scroll_hdl[i] = D_INVALID_HANDLE;
            }
        }
        if(ad_info[type - 1].img_info[idx].child_vis != NULL)
        {
            d_vis_free(ad_info[type - 1].img_info[idx].child_vis);
            ad_info[type - 1].img_info[idx].child_vis = NULL;
        }
        if((ad_info[type - 1].img_info[idx].img))
        {
            d_ad_release_img_ex(type, (D_U8 *)(ad_info[type - 1].img_info[idx].img));
            ad_info[type - 1].img_info[idx].img = NULL;
        }
        ad_info[type - 1].img_info[idx].valid = D_FALSE;
    }
    return;
}
/** @brief  p_ad_clean_all
* @param[in] D_U8 type   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static void p_ad_clean_all(D_U8 type)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < MAX_AD_PICT_NUM ; i++)
    {
        p_ad_clean_one(type, i);
    }
    return;
}

/** @brief  ad_param_init
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_param_init(D_Ad_Pos_Type pos_type)D_FUNCPOSTFIT
{
    D_U8 i = 0;
    D_U8 j = 0;

    if((pos_type < 1) || (pos_type >= DAD_STB_POS_UNKNOWN))
    {
        return D_ERR;
    }
    ad_info[pos_type - 1].menu_info.parent_vis = NULL;
    ad_info[pos_type - 1].menu_info.parent_pos_x = 0;
    ad_info[pos_type - 1].menu_info.parent_pos_y = 0;
    ad_info[pos_type - 1].menu_info.parent_width = 0;
    ad_info[pos_type - 1].menu_info.parent_height = 0;
    ad_info[pos_type - 1].menu_info.pos_type = 0;
    ad_info[pos_type - 1].menu_info.hcbm = D_INVALID_HANDLE;
    ad_info[pos_type - 1].hsem = D_INVALID_HANDLE;

    for(i = 0; i < MAX_AD_PICT_NUM; i++)
    {
        ad_info[pos_type - 1].img_info[i].child_vis = NULL;
        ad_info[pos_type - 1].img_info[i].img = NULL;
        ad_info[pos_type - 1].img_info[i].valid = D_FALSE;
        ad_info[pos_type - 1].img_info[i].id = 0;
        for(j = 0 ; j < MAX_AD_SCROLL_NUM ; j++)
        {
            ad_info[pos_type - 1].img_info[i].scroll_hdl[j] = D_INVALID_HANDLE;
        }
    }
    return D_OK;
}

/** @brief  osd_scroll_callback
* @param[in] D_HScroll handle         ◊¢ Õ
* @param[in] D_ScrollUsrParas paras   ◊¢ Õ
* @param[in] D_ScrollState state      ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result osd_scroll_callback(D_HScroll handle, D_ScrollUsrParas paras, D_ScrollState state)D_FUNCPOSTFIT
{
    D_U8 i, j, found;
    if(state == SCROLL_DONE)
    {
        if(ad_info[DAD_STB_OSD - 1].hsem != D_INVALID_HANDLE)
        {
            d_sem_wait (ad_info[DAD_STB_OSD - 1].hsem);
        }
        for(i = 0 ; i < MAX_AD_PICT_NUM ; i++)
        {
            found = 0;

            for(j = 0 ; j < MAX_AD_SCROLL_NUM ; j++)
            {
                if(ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j] != D_INVALID_HANDLE)
                {
                    if(ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j] == handle)
                    {
                        found = 1;
                    }
                }
            }
            if(found == 1)
            {
                for(j = 0 ; j < MAX_AD_SCROLL_NUM ; j++)
                {
                    if(ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j] != D_INVALID_HANDLE)
                    {
                        d_scroll_clear(ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j]);
                        d_scroll_destory(ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j]);
                        ad_info[DAD_STB_OSD - 1].img_info[i].scroll_hdl[j] = D_INVALID_HANDLE;
                    }
                }
            }
            if(ad_info[DAD_STB_OSD - 1].img_info[i].valid != D_FALSE)
            {
                if(ad_info[DAD_STB_OSD - 1].img_info[i].img != NULL)
                {
                    D_Ad_Osd_Param *type = (D_Ad_Osd_Param *)ad_info[DAD_STB_OSD - 1].img_info[i].img;

                    d_ad_scroll_callback(type->idx, type->uctotal);
                    d_ad_release_img_ex(DAD_STB_OSD, (D_U8 *)(ad_info[DAD_STB_OSD - 1].img_info[i].img));
                    ad_info[DAD_STB_OSD - 1].img_info[i].img = NULL;
                }
                ad_info[DAD_STB_OSD - 1].img_info[i].valid = D_FALSE;
            }
        }
        if(ad_info[DAD_STB_OSD - 1].hsem != D_INVALID_HANDLE)
        {
            d_sem_post (ad_info[DAD_STB_OSD - 1].hsem);
        }
    }
    return D_OK;
}
/** @brief  p_ad_clear_when_chan_change
* @param[in] void   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result p_ad_clear_when_chan_change(void)D_FUNCPOSTFIT
{
    D_U8 i, j, k;

    for(i = 1; i < DAD_STB_POS_UNKNOWN; i++)
    {
        if(i != DAD_STB_OSD&& ad_info[i - 1].state == 1 )
        {
            for(j = 0; j < MAX_AD_PICT_NUM; j++)
            {
                for(k = 0; k < MAX_AD_SCROLL_NUM; k++)
                {
                    if(ad_info[i - 1].img_info[j].scroll_hdl[k] != D_INVALID_HANDLE)
                    {
                        d_scroll_clear(ad_info[i - 1].img_info[j].scroll_hdl[k]);
                        d_scroll_destory(ad_info[i - 1].img_info[j].scroll_hdl[k]);
                        ad_info[i - 1].img_info[j].scroll_hdl[k] = D_INVALID_HANDLE;
                    }
                }
                if(ad_info[i - 1].img_info[j].child_vis != NULL)
                {
                    d_vis_free(ad_info[i - 1].img_info[j].child_vis);
                    ad_info[i - 1].img_info[j].child_vis = NULL;
                }
                if((ad_info[i - 1].img_info[j].img))
                {
                    d_ad_release_img_ex(i, (D_U8 *)(ad_info[i - 1].img_info[j].img));
                    ad_info[i - 1].img_info[j].img = NULL;
                }
                ad_info[i - 1].img_info[j].valid = D_FALSE;
            }
        }
    }
    return D_OK;
}

/** @brief  ad_get_data
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8* idx                ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_U8* ad_get_data(D_Ad_Pos_Type pos_type, D_U8* idx)D_FUNCPOSTFIT
{
    D_Ad_Image_Param * type;
    D_Ad_Osd_Param *type2;
    D_U8 num;

    if(pos_type == DAD_STB_OSD)
    {
        if(ad_info[pos_type - 1].hsem != D_INVALID_HANDLE)
        {
            d_sem_wait (ad_info[pos_type - 1].hsem);
        }
        type2 = (D_Ad_Osd_Param *)d_ad_get_img_ex(pos_type);
        if(ad_info[pos_type - 1].hsem != D_INVALID_HANDLE)
        {
            d_sem_post (ad_info[pos_type - 1].hsem);
        }

        if(type2 == NULL)
            return NULL;
        if(type2->if_erase == 1)//≤¡≥˝∂‘”¶id
        {
            if(p_ad_find_id(pos_type, type2->id, &num) == D_OK)
            {
                p_ad_clean_one(pos_type, num);
            }
            d_ad_release_img_ex(pos_type, (D_U8 *)type2);
            return NULL;
        }
        else if(type2->if_erase == 0xff)//≤¡≥˝À˘”–µƒÕº∆¨
        {
            p_ad_clean_all(pos_type);
            d_ad_release_img_ex(pos_type, (D_U8 *)type2);
            return NULL;
        }
        if(p_ad_find_id(pos_type, type2->id, &num) == D_OK)
        {
            d_ad_release_img_ex(pos_type, (D_U8 *)type2);
            return NULL;
//              p_ad_clean_one(pos_type, num);
        }
        /*
                    if(p_ad_find_idle(pos_type, &num) == D_ERR)
                    {
                        p_ad_clean_all(pos_type);
                    }
        */
        p_ad_clean_all(pos_type);
        if(p_ad_find_idle(pos_type, &num) == D_ERR)
        {
            d_ad_release_img_ex(pos_type, (D_U8 *)type2);
            return NULL;
        }
        *idx = num;
        return (D_U8*)type2;
    }
    else
    {
        type = (D_Ad_Image_Param *)d_ad_get_img_ex(pos_type);
        if(type == NULL)
            return NULL;
        if(type->if_erase == 1)//≤¡≥˝∂‘”¶idµƒÕº∆¨
        {
            if(p_ad_find_id(pos_type, type->id, &num) == D_OK)
            {
                p_ad_clean_one(pos_type, num);
            }
            d_ad_release_img_ex(pos_type, (D_U8 *)type);
            return NULL;
        }
        else if(type->if_erase == 0xff)//≤¡≥˝À˘”–µƒÕº∆¨
        {
            p_ad_clean_all(pos_type);
            d_ad_release_img_ex(pos_type, (D_U8 *)type);
            return NULL;
        }
        if(p_ad_find_id(pos_type, type->id, &num) == D_OK)
        {
            p_ad_clean_one(pos_type, num);
        }
        if(p_ad_find_idle(pos_type, &num) == D_ERR)
        {
            p_ad_clean_all(pos_type);
        }
        if(p_ad_find_idle(pos_type, &num) == D_ERR)
        {
            d_ad_release_img_ex(pos_type, (D_U8 *)type);
            return NULL;
        }
        *idx = num;
        return (D_U8*)type;

    }
}

/** @brief  ad_get_coordinate
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 idx                 ◊¢ Õ
* @param[in] D_U8 data                ◊¢ Õ
* @param[in] D_Rect* rect             ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_get_piccoordinate(D_Ad_Pos_Type pos_type, D_U8 idx, D_U8* data, D_Rect* rect)D_FUNCPOSTFIT
{
    D_Ad_Image_Param * type;
    D_Image *tmp_img = NULL;
    if(pos_type > DAD_STB_POS_UNKNOWN)
        return D_ERR;

    switch(pos_type)
    {
        case DAD_STB_PICOSD:
            type = (D_Ad_Image_Param *)data;
            tmp_img = type->image;

            rect->x = type->left;
            rect->y = type->top;
            rect->w = tmp_img->buf.width;
            rect->h = tmp_img->buf.height;
            return D_OK;
        default:
            type = (D_Ad_Image_Param *)data;
            tmp_img = type->image;

            rect->x = type->left;
            rect->y = type->top;
            rect->w = tmp_img->logical_width;
            rect->h = tmp_img->logical_height;
            return D_OK;
    }
    return D_ERR;

}
/** @brief  ad_get_osdcoordinate
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 idx                 ◊¢ Õ
* @param[in] D_U8* data               ◊¢ Õ
* @param[in] D_Rect* rect             ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_get_osdcoordinate(D_Ad_Pos_Type pos_type, D_U8 idx, D_U8* data, D_Rect* rect, D_ScrollDirection* direction, D_ScrollType *scrolltype)D_FUNCPOSTFIT
{
    D_Ad_Osd_Param *type2 = (D_Ad_Osd_Param *)data;

    switch(pos_type)
    {
        case DAD_STB_OSD:
            if(type2->enDisplayPos == LOCAL_HORIZONTAL)
            {
                if(type2->ucstartposx > type2->ucendposx)
                {
                    rect->x = type2->ucendposx;
                    rect->y = type2->ucstartposy;
                    rect->w = type2->ucstartposx - type2->ucendposx;
                    rect->w = (rect->w > MAX_SCROLL_W) ? MAX_SCROLL_W : rect->w;
                    rect->h = 30;
                    *scrolltype = H_SCROLL_RIGHT_TO_LEFT;
                    *direction = H_SCROLL_HORIZONTAL;
                    return D_OK;
                }
                else
                {
                    rect->x = type2->ucstartposx;
                    rect->y = type2->ucstartposy;
                    rect->w = type2->ucendposx - type2->ucstartposx;
                    rect->w = (rect->w > MAX_SCROLL_W) ? MAX_SCROLL_W : rect->w;
                    rect->h = 30;
                    *scrolltype = H_SCROLL_LEFT_TO_RIGHT;
                    *direction = H_SCROLL_HORIZONTAL;
                    return D_OK;
                }
            }
            else if(type2->enDisplayPos == LOCAL_VERTICAL)
            {
                if(type2->ucstartposy > type2->ucendposy)
                {
                    rect->x = type2->ucendposx;
                    rect->y = type2->ucendposy;
                    rect->w = 30;
                    rect->h = type2->ucstartposy - type2->ucendposy;
                    rect->h = (rect->h > MAX_SCROLL_H) ? MAX_SCROLL_H : rect->h;

                    *scrolltype = V_SCROLL_BOTTOM_TO_TOP;
                    *direction = H_SCROLL_VERTICAL;
                    return D_OK;
                }
                else
                {
                    rect->x = type2->ucstartposx;
                    rect->y = type2->ucstartposy;
                    rect->w = 30;
                    rect->h = type2->ucendposy - type2->ucstartposy;
                    rect->h = (rect->h > MAX_SCROLL_H) ? MAX_SCROLL_H : rect->h;

                    *scrolltype = V_SCROLL_TOP_TO_BOTTOM;
                    *direction = H_SCROLL_VERTICAL;
                    return D_OK;
                }
            }
            else if(type2->enDisplayPos == TOP_BOTTOM)
            {
                *scrolltype = H_SCROLL_RIGHT_TO_LEFT;
                *direction = H_SCROLL_HORIZONTAL;
                return D_OK;
            }
            else if(type2->enDisplayPos == LEFT_RIGHT)
            {
                *scrolltype = V_SCROLL_BOTTOM_TO_TOP;
                *direction = H_SCROLL_VERTICAL;
                return D_OK;
            }
            return D_ERR;
        default:
            break;
    }
    return D_ERR;

}
/** @brief  ad_set_pic
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 idx                 ◊¢ Õ
* @param[in] D_U8* data               ◊¢ Õ
* @param[in] D_Rect* rect             ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_set_pic(D_Ad_Pos_Type pos_type, D_U8 idx, D_U8* data, D_Rect* rect)D_FUNCPOSTFIT
{
    D_Ad_Image_Param * type;

    D_Coord     x = rect->x;
    D_Coord     y = rect->y;
    D_Coord     w = rect->w;
    D_Coord     h = rect->h;
    type = (D_Ad_Image_Param *)data;

    if(pos_type > DAD_STB_POS_UNKNOWN)
        return D_ERR;

    switch(pos_type)
    {
        case DAD_STB_EPG:
        case DAD_STB_MENU_UP:
        case DAD_STB_MENU_DOWN:
            ad_info[pos_type - 1].childtype = 1;
            break;
        default:
            ad_info[pos_type - 1].childtype = 1;
            break;
    }
    if(type->data_type == DAD_PIC_DATA)
    {
        if(!(ad_info[pos_type - 1].img_info[idx].child_vis))
        {
            ad_info[pos_type - 1].img_info[idx].child_vis = d_control_new(D_CTRL_IMAGE);
            if(!(ad_info[pos_type - 1].img_info[idx].child_vis))
            {
                return D_ERR;
            }
            ad_info[pos_type - 1].img_info[idx].child_vis->flags |= D_VIS_FL_TRANSPARENT;
        }
        d_vis_show(ad_info[pos_type - 1].img_info[idx].child_vis, D_TRUE);
        d_vis_set_pos(ad_info[pos_type - 1].img_info[idx].child_vis, x, y, w, h);
        d_image_box_set_image (ad_info[pos_type - 1].img_info[idx].child_vis, type->image);
        if(ad_info[pos_type - 1].childtype == 0)
            d_vis_append_child(ad_info[pos_type - 1].menu_info.parent_vis, ad_info[pos_type - 1].img_info[idx].child_vis);
        else
            d_vis_prepend_child(ad_info[pos_type - 1].menu_info.parent_vis, ad_info[pos_type - 1].img_info[idx].child_vis);

        ad_info[pos_type - 1].img_info[idx].id = type->id;
        ad_info[pos_type - 1].img_info[idx].valid = D_TRUE;
        d_vis_update (ad_info[pos_type - 1].img_info[idx].child_vis, NULL);
        ad_info[pos_type - 1].img_info[idx].img = data;

        return D_OK;
    }
    return D_ERR;
}
/** @brief  ad_set_osd
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 idx                 ◊¢ Õ
* @param[in] D_U8* data               ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_set_osd(D_Ad_Pos_Type pos_type, D_U8 idx, D_U8* data, D_Rect* rect, D_ScrollDirection direction, D_ScrollType scrolltype)D_FUNCPOSTFIT
{
    D_Ad_Osd_Param *type2 = (D_Ad_Osd_Param *)data;
    D_Coord     x = rect->x;
    D_Coord     y = rect->y;
    D_Coord     w = rect->w;
    D_Coord     h = rect->h;

    if(pos_type != DAD_STB_OSD)
        return D_ERR;

    p_ad_clean_one(pos_type, idx);

    if(type2->enDisplayPos == LOCAL_HORIZONTAL || type2->enDisplayPos == LOCAL_VERTICAL)
    {
        if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
        {
            ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] = d_scroll_create (w, h, direction);
            if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
        d_scroll_start(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0], w, h, scrolltype, x, y , type2->pucDisplayBuffer, type2->aucBackgroundColor, type2->aucDisplayColor, type2->ucFontSize, type2->txtSpeed, type2->ucShowTimes, 0xFFFFFFFF, D_FALSE, osd_scroll_callback);
    }
    else if(type2->enDisplayPos == TOP_BOTTOM)
    {
        x = type2->ucstartposx;
        y = type2->ucstartposy;
        w = MAX_SCROLL_W;
        h = 30;

        if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
        {
            ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] = d_scroll_create (w, h, direction);
            if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
        d_scroll_start(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0], w, h, scrolltype, x, y , type2->pucDisplayBuffer, type2->aucBackgroundColor, type2->aucDisplayColor, type2->ucFontSize, type2->txtSpeed, type2->ucShowTimes, 0xFFFFFFFF, D_FALSE, osd_scroll_callback);
        x = type2->ucendposx;
        y = type2->ucendposy;
        w = MAX_SCROLL_W;
        h = 30;
        if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] == D_INVALID_HANDLE)
        {
            ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] = d_scroll_create (w, h, direction);
            if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
        d_scroll_start(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1], w, h, scrolltype, x, y , type2->pucDisplayBuffer, type2->aucBackgroundColor, type2->aucDisplayColor, type2->ucFontSize, type2->txtSpeed, type2->ucShowTimes, 0xFFFFFFFF, D_FALSE, osd_scroll_callback);
    }
    else if(type2->enDisplayPos == LEFT_RIGHT)
    {
        x = type2->ucstartposx;
        y = type2->ucstartposy;
        w = 30;
        h = MAX_SCROLL_H;

        if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
        {
            ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] = d_scroll_create (w, h, direction);
            if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0] == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
        d_scroll_start(ad_info[pos_type - 1].img_info[idx].scroll_hdl[0], w, h, scrolltype, x, y , type2->pucDisplayBuffer, type2->aucBackgroundColor, type2->aucDisplayColor, type2->ucFontSize, type2->txtSpeed, type2->ucShowTimes, 0xFFFFFFFF, D_FALSE, osd_scroll_callback);

        x = type2->ucendposx;
        y = type2->ucendposy;
        w = 30;
        h = MAX_SCROLL_H;
        if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] == D_INVALID_HANDLE)
        {
            ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] = d_scroll_create (w, h, direction);
            if(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1] == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
        d_scroll_start(ad_info[pos_type - 1].img_info[idx].scroll_hdl[1], w, h, scrolltype, x, y , type2->pucDisplayBuffer, type2->aucBackgroundColor, type2->aucDisplayColor, type2->ucFontSize, type2->txtSpeed, type2->ucShowTimes, 0xFFFFFFFF, D_FALSE, osd_scroll_callback);
    }
    else
    {
        return D_ERR;
    }
    ad_info[pos_type - 1].img_info[idx].img = type2;
    ad_info[pos_type - 1].img_info[idx].id = type2->id;
    ad_info[pos_type - 1].img_info[idx].valid = D_TRUE;
	
    return D_OK;
}
/** @brief  ad_deal_data
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 idx                 ◊¢ Õ
* @param[in] D_U8 data                ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result ad_deal_data(D_Ad_Pos_Type pos_type, D_U8 idx, D_U8* data)D_FUNCPOSTFIT
{
    if(pos_type == DAD_STB_OSD)
    {
        D_ScrollType scrolltype;
        D_ScrollDirection direction;
        D_Rect rect;
        if(ad_get_osdcoordinate(pos_type, idx, data, &rect, &direction, &scrolltype) == D_OK)
        {
            return ad_set_osd(pos_type, idx, data, &rect, direction, scrolltype);
        }
    }
    else
    {
        D_Rect rect;
        if(ad_get_piccoordinate(pos_type, idx, data, &rect) == D_OK)
        {
            return ad_set_pic(pos_type, idx, data, &rect);
        }
    }
    return D_ERR;
}
/** @brief  ad_check_chaninfo
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
void ad_check_chaninfo(D_Ad_Pos_Type pos_type, D_Ad_Service_Param* chan_param)D_FUNCPOSTFIT
{
    D_ID id = -1;
    D_DBSrvInfo srv_info;
    D_DBTSInfo ts_info;

    memset(chan_param, 0, sizeof(D_Ad_Service_Param));
    id = p_stb_player_get_curr_srv (0);
    if(curr_DBSrvID != id)
    {
        if((id > 0) && (id <= P_DB_MAX_SRV_CNT))
        {
            if(d_dbase_get_srv_info (id, &srv_info) == D_OK)
            {
                if(p_dbase_get_ts_info (srv_info.db_ts_id, &ts_info) == D_OK)
                {
                    memset(chan_param, 0, sizeof(D_Ad_Service_Param));
                    chan_param->usNetworkId = ts_info.org_net_id;
                    chan_param->usTsId = ts_info.ts_id;
                    chan_param->usServiceId = srv_info.srv_id;
                    curr_DBSrvID = id;
                }
            }
        }
        else
        {
            memset(chan_param, 0, sizeof(D_Ad_Service_Param));
            curr_DBSrvID = -1;
        }
        if(memcmp(&curr_chan_param, chan_param, sizeof(D_Ad_Service_Param)) != 0)
        {
            memcpy(&curr_chan_param, chan_param, sizeof(D_Ad_Service_Param));
            p_ad_clear_when_chan_change();
            d_ad_set_chan_ex(chan_param);
        }
    }
	else if((id > 0) && (id <= P_DB_MAX_SRV_CNT))
	{
		memcpy( chan_param,&curr_chan_param, sizeof(D_Ad_Service_Param));	
	}
}

/** @brief  p_ad_show
* @param[in] D_U32 cb_id      ◊¢ Õ
* @param[in] D_Handle obj     ◊¢ Õ
* @param[in] D_Ptr obj_data   ◊¢ Õ
* @param[in] D_Ptr cb_data    ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
static D_Result p_ad_show(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_Ad_Service_Param chan_param;
    D_U8 *tmp_str = NULL;
    D_U32 size = 0;
    menu_win_param *menu_info = (menu_win_param *)cb_data;
	
    D_Ad_Pos_Type pos_type = menu_info->pos_type;
    D_U8 idx = 0;

    if((pos_type < 1) || (pos_type >= DAD_STB_POS_UNKNOWN))
    {
        return D_ERR;
    }

    ad_check_chaninfo(pos_type, &chan_param);

    tmp_str = ad_get_data(pos_type, &idx);
    if(tmp_str == NULL)
        return D_ERR;

    if(ad_deal_data(pos_type, idx, tmp_str) == D_ERR)
    {
        d_ad_release_img_ex(pos_type, tmp_str);
        return D_ERR;
    }
    return D_OK;
}

/** @brief  p_ad_show_destroy
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
D_Result p_ad_show_destroy(D_Ad_Pos_Type pos_type)D_FUNCPOSTFIT
{
    D_U8 i, j;
    if(!init_flag)
    {
        return D_ERR;
    }
    if((pos_type < 1) || (pos_type >= DAD_STB_POS_UNKNOWN))
    {
        return D_ERR;
    }
    for(i = 0; i < MAX_AD_PICT_NUM; ++i)
    {
        for(j = 0; j < MAX_AD_SCROLL_NUM; j++)
        {
            if(ad_info[pos_type - 1].img_info[i].scroll_hdl[j] != D_INVALID_HANDLE)
            {
                d_scroll_clear(ad_info[pos_type - 1].img_info[i].scroll_hdl[j]);
                d_scroll_destory(ad_info[pos_type - 1].img_info[i].scroll_hdl[j]);
                ad_info[pos_type - 1].img_info[i].scroll_hdl[j] = D_INVALID_HANDLE;
            }
        }
        if(ad_info[pos_type - 1].img_info[i].child_vis != NULL)
        {
            d_vis_free(ad_info[pos_type - 1].img_info[i].child_vis);
            ad_info[pos_type - 1].img_info[i].child_vis = NULL;
        }
        if((ad_info[pos_type - 1].img_info[i].img))
        {
            d_ad_release_img_ex(pos_type, (D_U8 *)(ad_info[pos_type - 1].img_info[i].img));
            ad_info[pos_type - 1].img_info[i].img = NULL;
        }
        ad_info[pos_type - 1].img_info[i].valid = D_FALSE;
    }
    if(ad_info[pos_type - 1].menu_info.hcbm != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(ad_info[pos_type - 1].menu_info.hcbm);
    }
    d_ad_exit_menu_ex(pos_type);
    ad_info[pos_type - 1].state = 0;
    if(ad_info[pos_type - 1].hsem != D_INVALID_HANDLE)
    {
        d_sem_destroy (ad_info[pos_type - 1].hsem);
        ad_info[pos_type - 1].hsem = D_INVALID_HANDLE;
    }

    return ad_param_init(pos_type);
}


/** @brief  p_ad_show_open
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_Visual *vis            ◊¢ Õ
* @param[in] D_U16 x                  ◊¢ Õ
* @param[in] D_U16 y                  ◊¢ Õ
* @param[in] D_U16 width              ◊¢ Õ
* @param[in] D_U16 height             ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
D_Result p_ad_show_open(D_Ad_Pos_Type pos_type, D_Visual *vis, D_U16 x, D_U16 y, D_U16 width, D_U16 height)D_FUNCPOSTFIT
{
    D_U8 i = 0;
    D_HSem  hsem;
    D_SemAttr attr;
    D_Ad_Service_Param chan_param;
    D_ID id = -1;
    D_DBSrvInfo srv_info;
    D_DBTSInfo ts_info;

    if((!vis) || (pos_type < 1) || (pos_type >= DAD_STB_POS_UNKNOWN))
    {
        return D_ERR;
    }
    ad_check_chaninfo(pos_type, &chan_param);

    if(d_ad_Check_App(pos_type, &chan_param) != D_OK)
    {
        return D_ERR;
    }
    if(!init_flag)
    {
        for(i = 1; i < DAD_STB_POS_UNKNOWN; ++i)
        {
            ad_param_init(i);
        }
        init_flag = D_TRUE;
    }
    if(ad_info[pos_type - 1].state == 1)
    {
        p_ad_show_destroy(pos_type);
    }
    ad_info[pos_type - 1].menu_info.parent_vis = vis;
    ad_info[pos_type - 1].menu_info.parent_pos_x = x;
    ad_info[pos_type - 1].menu_info.parent_pos_y = y;
    ad_info[pos_type - 1].menu_info.parent_width = width;
    ad_info[pos_type - 1].menu_info.parent_height = height;

    ad_info[pos_type - 1].menu_info.pos_type = pos_type;
    ad_info[pos_type - 1].menu_info.hcbm = d_cbman_subscribe(PL_GUI_IDLE, D_INVALID_HANDLE, p_ad_show, &(ad_info[pos_type - 1].menu_info));
    if(ad_info[pos_type - 1].menu_info.hcbm == D_INVALID_HANDLE)
    {
        ad_param_init(pos_type);
        return D_ERR;
    }
    if(ad_info[pos_type - 1].hsem != D_INVALID_HANDLE)
    {
        d_sem_destroy (ad_info[pos_type - 1].hsem);
        ad_info[pos_type - 1].hsem = D_INVALID_HANDLE;
    }
    D_SEM_ATTR_INIT (&attr);
    ad_info[pos_type - 1].hsem = d_sem_create (&attr);
    d_sem_post (ad_info[pos_type - 1].hsem);

    ad_info[pos_type - 1].state = 1;
    d_ad_enter_menu_ex(pos_type, &chan_param);
    return D_OK;
}
/** @brief  p_ad_check_fpkey
* @param[in] D_Ad_Pos_Type pos_type   ◊¢ Õ
* @param[in] D_U8 key                 ◊¢ Õ
* @retval D_OK  ≥…π¶
* @retval D_ERR   ß∞‹
* @note ◊¢Ω‚
*/
D_Result p_ad_check_fpkey(D_Ad_Pos_Type pos_type, D_U8 key)D_FUNCPOSTFIT
{
    if((pos_type >= DAD_STB_LOG) && (pos_type < DAD_STB_POS_UNKNOWN))
    {
        d_ad_check_fpkey_ex(pos_type, key);
    }
}

