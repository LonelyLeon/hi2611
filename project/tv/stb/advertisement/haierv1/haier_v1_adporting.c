/** @file
* @brief 广告模块支撑接口
* @author liuwf
* @date 2014-03-11 liuwf: 建立文件
*/
#include <string.h>
#include "stdio.h"
#include <stdarg.h>
#include "dTypes.h"
#include "dNVPart.h"
#include "dDebug.h"
#include "dGUI.h"
#include "dDBaseInternal.h"
#include "dMMan.h"
#include "dMem.h"
#include "dApp.h"
#include "dMutex.h"
#include "dSem.h"
#include "dQueue.h"
#include "dadporting.h"
#include "dSys.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dCrc.h"



/** @brief  支持的图片显示应用需求*/
typedef enum
{
    logAdvType_PowerOn = (1 << 0),
    logAdvType_RadioBackGround = (1 << 1),
    logAdvType_Nosignal = (1 << 2),
    logAdvType_ProgramBanner = (1 << 3),
    logAdvType_AudioVolume = (1 << 4),
    logAdvType_MainMenu = (1 << 5),
    logAdvType_NoProgram = (1 << 6),
    logAdvType_ProgramList = (1 << 7),
    logAdvType_EPG = (1 << 8),

} P_Log_Advertisement;

/** @brief  LOGO中的图片信息头描述*/
typedef struct
{
    D_U32 crc;
    D_U32 length;
    D_U32 count;
} P_Logo_Header;

/** @brief  LOGO中的图片信息描述*/
typedef struct
{
    D_U32 advType;      // 图片应用类型
    D_ImageType imgType;// 图片类型
    D_Size off_ptr;     // img数据在数组中的偏移
    D_Size img_size;    // img数据大小
    D_U16 times;        // img显示时间 100ms
    D_U16 left;                     // img显示相对坐标
    D_Int top;                      // img显示相对坐标
    D_Int width;                        // img显示宽度
    D_Int height;                       // img显示高度
    D_U32 crc;

} Logo_Item;

/** @brief  LOGO中的图片信息解析之后给应用的数据信息*/
typedef struct logo_info_s
{
    Logo_Item item;     /// 图片信息
    D_U32 picid;
    D_U8 *buffer;      ///数据的指针
    struct logo_info_s *next;
} logo_info_t;


/***************************************stb提供给ad的函数******************************************/
/******************************************广告模块提供给stb调用的函数****************************************************/

/*----------------------------------------------------------------------------------------*/
// content of logo sample code
/*----------------------------------------------------------------------------------------*/
#define BYTE_PTR(ptr, byte_off)     (((D_U8*)(ptr))+(byte_off))
#define U32_BYTE(ptr)       ((D_U32)*BYTE_PTR(ptr, 0))
#define U32_BE16(ptr)       ((U32_BYTE(ptr)<<8)|U32_BYTE(BYTE_PTR(ptr, 1)))
#define U32_BE32(ptr)       ((U32_BE16(ptr)<<16)|U32_BE16(BYTE_PTR(ptr, 2)))
#define U32_BYTE_OFF(ptr, byte_off)     U32_BYTE(BYTE_PTR(ptr, byte_off))
#define U32_BE16_OFF(ptr, byte_off)     U32_BE16(BYTE_PTR(ptr, byte_off))
#define U32_BE32_OFF(ptr, byte_off)     U32_BE32(BYTE_PTR(ptr, byte_off))

static  logo_info_t *logolist = NULL; ///保存图片信息的链表

static  D_HNVPart hnvp = D_INVALID_HANDLE;


/** @brief logo模块内存申请
* @param  size 申请的大小
* @return NULL -- 无效 D_Ptr -- 申请到的地址
*/
D_Ptr logo_mem_alloc(D_Size size)
{
    D_Ptr buf;

    buf = d_mem_alloc(0, size);
    D_DUMP("[advalloc]buf [0x%lx] size[0x%lx]\n", buf , size);

    return  buf;
}

/** @brief logo模块内存释放
* @param  p 要释放的内存地址
* @return
*/
void logo_mem_free(D_Ptr p)
{
    D_DUMP("[advallocfree]buf [0x%lx]\n", p);
    d_mem_free (p);
}

/** @brief CRC32位校验
* @param  ptr_data 数据地址
* @param  data_length 数据长度
* @param  ucrc_verify 校验值
* @return D_OK:校验成功  ; D_ERR:校验失败
*/
static D_Result logo_crc32_check(const void *ptr_data, D_Size data_length, D_U32 ucrc_verify) D_FUNCPOSTFIT
{
    unsigned long ccrc;

    ccrc = d_crc_compute_32((unsigned char*)ptr_data, data_length);
    return ccrc == ucrc_verify ? D_OK : D_ERR;
}

/** @brief 取得img描述信息
* @param [in]ptr    img数据描述信息首地址
* @param [out]dli   img数据信息结构化描述
* @return
*/
static void logo_GetLogInfo(const void *ptr, Logo_Item *dli) D_FUNCPOSTFIT
{
    D_Int off = 0;
    D_U32 temp = 0;

    dli->advType = (P_Log_Advertisement)U32_BE32_OFF(ptr, off);
    off += 4;
    dli->imgType = (D_ImageType)U32_BE32_OFF(ptr, off);
    off += 4;
    dli->off_ptr = U32_BE32_OFF(ptr, off);
    off += 4;
    dli->img_size = U32_BE32_OFF(ptr, off);
    off += 4;
    temp = U32_BE32_OFF(ptr, off);
    dli->times = (D_U16)(temp >> 16); //100ms
    dli->left = (D_U16)((temp << 16) >> 16);
    off += 4;
    dli->top = U32_BE32_OFF(ptr, off);
    off += 4;
    dli->width = U32_BE32_OFF(ptr, off);
    off += 4;
    dli->height = U32_BE32_OFF(ptr, off);
    off += 4;
    dli->crc = U32_BE32_OFF(ptr, off);
}

/** @brief 检查logo信息是否有效
* @param [in]logo_data  logo数据首地址
* @return D_OK  logo有效D_ERR   logo数据无效
*/
static D_Result logo_verify_data(const void *logo_data) D_FUNCPOSTFIT
{
    D_Int i;
    D_U32  ucrc_logo = U32_BE32(logo_data);
    D_Size size_logo = U32_BE32_OFF(logo_data, 4);
    D_Int  count = U32_BE32_OFF(logo_data, 8);
    D_Size size = 4;
    D_Int  off = 12;
    Logo_Item item;

    if(D_OK != logo_crc32_check(BYTE_PTR(logo_data, 4), size_logo + 4, ucrc_logo))
        return D_ERR;
    for(i = 0; i < count; i++)
    {
        Logo_Item *dli = (Logo_Item*)BYTE_PTR(logo_data, off);
        logo_GetLogInfo(dli, &item);
        size += item.img_size + sizeof(Logo_Item );
        off += sizeof(Logo_Item );
    }
    if(size != size_logo)
        return D_ERR;
    return D_OK;
}

/** @brief 获得logo可能的长度
* @param [in]logo_data_partial logo数据前面部分，至少包含32字节
* @return  logo数据可能的长度
*/
D_Size logo_peek_size(const void *logo_data_partial) D_FUNCPOSTFIT
{
    D_Size size_logo = U32_BE32_OFF(logo_data_partial, 4);
    return size_logo + 8;
}

/** @brief 获得logo可能的数量
* @param [in]logo_data_partial      logo数据前面部分，至少包含32字节
* @return logo数据可能的数量
*/
D_Int logo_get_count(const void *logo_data_partial) D_FUNCPOSTFIT
{
    D_Int  count = U32_BE32_OFF(logo_data_partial, 8);
    return count;
}

/** @brief 获取logo中指定位置的img描述信息
* @pram [in]logo_data       logo数据首地址
* @pram [in]no          指定的img的位置，0代表第一个，以此类推
* @pram [out]logo_item  logo数据中指定img的描述信息输出缓冲区首地址
* @return D_OK          成功，logo_item可用
* @return D_ERR         失败，logo_item不可用
*/
D_Result logo_get_img_info(const void *logo_data, Logo_Item *logo_item, D_Int no) D_FUNCPOSTFIT
{
    D_Size size_logo = U32_BE32_OFF(logo_data, 4);
    D_Int  count = U32_BE32_OFF(logo_data, 8);
    D_Int  off = 12;
    Logo_Item *dli;

    if((no >= 0) && (no < count))
    {
        off += (sizeof(Logo_Item) * no);

        dli = (Logo_Item*)BYTE_PTR(logo_data, off);

        logo_GetLogInfo(dli, logo_item);

        if(D_OK != logo_crc32_check(BYTE_PTR(logo_data, logo_item->off_ptr), logo_item->img_size, logo_item->crc))
            return D_ERR;

        if(logo_item->off_ptr + logo_item->img_size <= size_logo + 8)
        {
            return D_OK;
        }
    }
    return D_ERR;
}

/** @brief 链表中添加一个图片的信息
* @param list   基本链表
* @param type   图片的应用类型
* @param no     第几个
* @return 找到的图片链表 NULL --无效
*/
static logo_info_t* logo_get_list_type(logo_info_t *list, P_Log_Advertisement type, D_U8 no)
{
    logo_info_t *nextlist;
    D_U8 find = 0;

    if(list == NULL)
    {
        D_ERROR("[adv]adv_get_count_type error!\n");
        return NULL;
    }
    else
    {
        nextlist = list;
        if((list->item.advType & type) == type)
        {
            if(find == no)
            {
                return list;
            }
            else
            {
                find ++;
            }

        }
        while(nextlist->next)
        {
            nextlist = nextlist->next;
            if((nextlist->item.advType & type) == type)
            {
                if(find == no)
                {
                    return nextlist;
                }
                else
                {
                    find ++;
                }
            }
        }
    }
    return NULL;

}

/** @brief 链表中添加一个图片的信息
* @param list   基本链表
* @param type   图片的应用类型
* @return 找到的图片数量
*/
static D_U8 logo_get_count_type(logo_info_t *list, P_Log_Advertisement type)
{
    logo_info_t *nextlist;
    D_U8 no = 0;

    if(list == NULL)
    {
        D_ERROR("[adv]adv_get_count_type error!\n");
    }
    else
    {
        nextlist = list;
        if((list->item.advType & type) == type)
        {
            no ++;
        }
        while(nextlist->next)
        {
            nextlist = nextlist->next;
            if((nextlist->item.advType & type) == type)
            {
                no ++;
            }
        }
    }
    return no;

}

/** @brief 链表中添加一个图片的信息
* @param list   基本链表
* @param newlist    新的图片数据信息
* @return NULL
*/
static void logo_add_list(logo_info_t **list, logo_info_t *newlist)
{
    logo_info_t *nextlist;
    D_U32 picid;

    picid = 0;

    if(*list == NULL)
    {
        newlist->picid = 0;
        *list = newlist;
    }
    else
    {
        nextlist = *list;

        while(nextlist->next)
        {
            nextlist = nextlist->next;
        }
        picid = nextlist->picid;
        nextlist->next = newlist;
        nextlist = nextlist->next;

        nextlist->picid = (picid + 1);
    }

}

/** @brief 释放某个图片
* @param img_data   图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   内部使用的接口
*/
D_Result logo_release_img_data(logo_info_t *img_data)D_FUNCPOSTFIT
{
    if(img_data->buffer != NULL)
    {
        switch(img_data->item.imgType)
        {
            case    D_IMAGE_JPEG:
            case    D_IMAGE_PNG:
            case    D_IMAGE_GIF:
            case    D_IMAGE_BMP:
            {
                d_image_free((D_Image *)img_data->buffer);
                img_data->buffer = NULL;
                break;
            }
            case    D_IMAGE_MPEG2_FRAME_I:
            {
                logo_mem_free(img_data->buffer);
                img_data->buffer = NULL;
                break;
            }
            default:
            {
                D_ERROR("[adv]logo_item.imgType error!\n");
                break;
            }
        }

    }
    return D_OK;
}

/** @brief 释放链表及所有的内存，在p_adv_destroy时候使用
* @param list   基本链表
* @return NULL
*/
static void logo_del_list(logo_info_t **list)
{
    logo_info_t *templist;

    templist = *list;

    while(templist != NULL)
    {
        *list = templist->next;
        if(templist->buffer != NULL)
        {
            logo_release_img_data(templist);
            templist->buffer = NULL;
        }
        logo_mem_free(templist);
        templist = *list;
    }
    *list = NULL;
}

/** @brief 打开logo模块
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result logo_open (void) D_FUNCPOSTFIT
{
    D_U8 buf[sizeof(P_Logo_Header) + 1];
    D_NVPartInfo info;
    D_Size ret;
    D_U8 * tempbuf;
    D_U8 i;
    D_U8  count;
    Logo_Item logo_item ;
    logo_info_t * templogoitem;

    hnvp = d_nvpart_create(D_DB_NVRAM_ID, D_NV_PART_ADVERTISE);
    if(hnvp == D_INVALID_HANDLE)
    {
        D_ERROR("[adv]d_nvpart_create error!\n");
        return D_ERR;
    }
    if(d_nvpart_get_info (hnvp, &info) != D_OK)
    {
        D_ERROR("[adv]d_nvpart_get_info error!\n");
        return D_ERR;
    }
    if(info.nv_size == 0)
    {
        D_ERROR("[adv]info.nv_size error!\n");
        return D_ERR;
    }

    ret = d_nvpart_read(hnvp, 0, buf, (D_Size)sizeof(P_Logo_Header));   ///头信息
    if(ret < sizeof(P_Logo_Header))
    {
        D_ERROR("[adv]d_nvpart_read error!\n");
        return D_ERR;
    }
    ret = logo_peek_size(buf);
    if((ret <= 8) || (ret > info.nv_size))
    {
        D_ERROR("[adv]d_logo_peek_size error!\n");
        return D_ERR;
    }
    tempbuf = (D_U8*)logo_mem_alloc(ret + 1);
    if(tempbuf == NULL)
    {
        D_ERROR("[adv]logo_mem_alloc error!\n");
        return D_ERR;
    }
    ret = d_nvpart_read(hnvp, 0, tempbuf, (D_Size)ret); ///整块数据
    if(ret < ret)
    {
        D_ERROR("[adv]d_nvpart_read error!\n");
        return D_ERR;
    }
    if(logo_verify_data(tempbuf) != D_OK)
    {
        D_ERROR("[adv]logo_verify_data error!\n");
        logo_mem_free(tempbuf);
        return D_ERR;
    }
    count = logo_get_count(tempbuf);
    for(i = 0; i <  count; i++)
    {
        if(logo_get_img_info(tempbuf, &logo_item , i) != D_OK)
        {
            D_ERROR("[adv]logo_get_img_info error!\n");
            logo_mem_free(tempbuf);
            return D_ERR;
        }
        templogoitem = (logo_info_t*)logo_mem_alloc(sizeof(logo_info_t));
        memcpy((D_U8 *)templogoitem, (D_U8 *)(&logo_item), sizeof(Logo_Item));
        templogoitem ->next = NULL;
        templogoitem ->buffer = NULL;
        logo_add_list(&logolist, templogoitem);
    }
    logo_mem_free(tempbuf);
    return D_OK;
}
/** @brief 关闭logo模块
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result
logo_destroy (void) D_FUNCPOSTFIT
{
    if(hnvp != D_INVALID_HANDLE)
    {
        d_nvpart_destroy(hnvp);
    }
    hnvp = D_INVALID_HANDLE;

    logo_del_list(&logolist);

    return D_OK;

}

/** @brief 获取某种应用的图片数量
* @param  type 图片应用类型
* @return 返回这种应用的图片的数量
*/
D_U8 d_logo_get_img_count (P_Log_Advertisement type) D_FUNCPOSTFIT
{
    return logo_get_count_type(logolist, type);
}

/** @brief 获取某种应用的图片数据和信息
* @param  type 图片应用类型
* @param  no 第几个这个类型的图片
* @return 返回图片信息的指针
*/
logo_info_t * d_logo_load_img_data(P_Log_Advertisement type, D_U8 no)D_FUNCPOSTFIT
{
    logo_info_t* info;
    D_U8 *buf = NULL;
    D_U8 *imgbuf = NULL;
    D_Size ret;

    info = logo_get_list_type(logolist, type, no);
    if(info == NULL || (info->item.img_size == 0))
    {
        return NULL;
    }
    if(info ->buffer != NULL)
    {
        return info;
    }
    buf = (D_U8*)logo_mem_alloc(info->item.img_size);
    if(buf == NULL)
    {
        D_ERROR("[adv]logo_mem_alloc error:%d\n", info->item.img_size);
        return NULL;
    }
    ret = d_nvpart_read(hnvp, info->item.off_ptr, buf, (D_Size)info->item.img_size);    ///头信息
    if(ret < info->item.img_size)
    {
        D_ERROR("[adv]d_nvpart_read error!\n");
        logo_mem_free(buf);
        return NULL;
    }
    switch(info->item.imgType)
    {
        case    D_IMAGE_JPEG:
        case    D_IMAGE_PNG:
        case    D_IMAGE_GIF:
        case    D_IMAGE_BMP:
        {
            imgbuf = (D_U8*)d_g_load_image (d_gui_get_surface(), D_IMAGE_AUTO, (D_U8*)buf, (D_Size)info->item.img_size);
            if (imgbuf == NULL)
            {
                D_ERROR("[adv]Eng Image load error:%d\n", info->item.img_size);
                logo_mem_free(buf);
                return NULL;
            }
            logo_mem_free(buf);
            info->buffer = imgbuf;
            return info;
        }
        case    D_IMAGE_MPEG2_FRAME_I:
        {
            imgbuf = (D_U8*)logo_mem_alloc((D_Size)info->item.img_size);
            if (imgbuf == NULL)
            {
                D_ERROR("[adv]Eng Image load error:%d\n", info->item.img_size);
                logo_mem_free(buf);
                return NULL;
            }
            memcpy(imgbuf , (D_U8*)buf, (D_Size)info->item.img_size);
            logo_mem_free(buf);
            info->buffer = imgbuf;
            return info;
        }
        default:
        {
            D_ERROR("[adv]logo_item.imgType error!\n");
            return NULL;
        }
    }
}

/** @brief 释放某个图片
* @param img_data   图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   给外部使用的接口
*/
D_Result d_logo_release_img_data(logo_info_t *img_data)D_FUNCPOSTFIT
{
    return logo_release_img_data(img_data);
}

/////////////////外部函数////////////
static D_Result d_hv1ad_Init(D_Ad_Init_Param *cfg)D_FUNCPOSTFIT
{
    return logo_open();
}

static D_Result d_hv1ad_exit(void)D_FUNCPOSTFIT
{
    logo_destroy();
    return D_OK;
}
static D_Result d_hv1ad_CheckApp(D_Ad_Pos_Type type, D_Ad_Service_Param* chan_param)D_FUNCPOSTFIT
{
    D_U8 temp = 0;
    P_Log_Advertisement hitype;

    switch(type)
    {
        case    DAD_STB_VOLUME:      /*音量广告*/
        {
            hitype = logAdvType_AudioVolume;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case    DAD_STB_MENU:        /*主菜单广告*/
        {
            hitype = logAdvType_MainMenu;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case    DAD_STB_BANNER:          /*节目信息条广告*/
        {
            hitype = logAdvType_ProgramBanner;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case DAD_STB_ProgramList: /*节目浏览广告*/
        {
            hitype = logAdvType_ProgramList;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case DAD_STB_EPG: /*节目浏览广告*/
        {
            hitype = logAdvType_EPG;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        default:
            return D_ERR;
    }
    if(temp == 0)
        return D_ERR;
    else
        return D_OK;
}


/** @brief  退出广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result d_hv1ad_get_img(D_Ad_Service_Param *chan_param, D_Ad_Pos_Type type, D_U8 idx, D_U8* info)D_FUNCPOSTFIT
{
    D_U8 count;
    P_Log_Advertisement dstype;
    logo_info_t *logo_info = NULL;
    D_Ad_Image_Param* pic = (D_Ad_Image_Param*)info;

    pic->left = 0;    /*坐标    */
    pic->top = 0;      /*坐标   */

    switch(type)
    {
        case DAD_STB_MENU: //DAD_STB_LOG:       //开机广告
        {
            dstype = logAdvType_MainMenu;
            count = d_logo_get_img_count(dstype);
            if(idx >= count)
                return D_ERR;

            logo_info = d_logo_load_img_data(dstype, idx);
            if(!logo_info)
            {
                return D_ERR;
            }
            if(logo_info->item.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                pic->data_type = DAD_M2V_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->id = 0;
            }
            else
            {

                pic->uctotal = count;
                pic->id = 0;
                pic->data_type = DAD_PIC_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->times = (D_U32)logo_info->item.times * 100;
                pic->image = (D_Image *)(logo_info->buffer);
                pic->left = 666;    /*坐标   */
                pic->top = 448; /*坐标   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_EPG: //DAD_STB_LOG:        //开机广告
        {
            dstype = logAdvType_EPG;
            count = d_logo_get_img_count(dstype);
            if(idx >= count)
                return D_ERR;

            logo_info = d_logo_load_img_data(dstype, idx);
            if(!logo_info)
            {
                return D_ERR;
            }
            if(logo_info->item.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                pic->data_type = DAD_M2V_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->id = 0;
            }
            else
            {

                pic->uctotal = count;
                pic->id = 0;
                pic->data_type = DAD_PIC_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->times = (D_U32)logo_info->item.times * 100;
                pic->image = (D_Image *)(logo_info->buffer);
                pic->left = 666;    /*坐标   */
                pic->top = 448; /*坐标   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_VOLUME: //DAD_STB_LOG:     //开机广告
        {
            dstype = logAdvType_AudioVolume;
            count = d_logo_get_img_count(dstype);
            if(idx >= count)
                return D_ERR;

            logo_info = d_logo_load_img_data(dstype, idx);
            if(!logo_info)
            {
                return D_ERR;
            }
            if(logo_info->item.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                pic->data_type = DAD_M2V_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->id = 0;
            }
            else
            {

                pic->uctotal = count;
                pic->id = 0;
                pic->data_type = DAD_PIC_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->times = (D_U32)logo_info->item.times * 100;
                pic->image = (D_Image *)(logo_info->buffer);
                pic->left = 668;    /*坐标   */
                pic->top = 546; /*坐标   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_BANNER: //DAD_STB_LOG:     //开机广告
        {
            dstype = logAdvType_ProgramBanner;
            count = d_logo_get_img_count(dstype);
            if(idx >= count)
                return D_ERR;

            logo_info = d_logo_load_img_data(dstype, idx);
            if(!logo_info)
            {
                return D_ERR;
            }
            if(logo_info->item.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                pic->data_type = DAD_M2V_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->id = 0;
            }
            else
            {

                pic->uctotal = count;
                pic->id = 0;
                pic->data_type = DAD_PIC_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->times = (D_U32)logo_info->item.times * 100;
                pic->image = (D_Image *)(logo_info->buffer);

                pic->left = 668;    /*坐标   */
                pic->top = 546; /*坐标   */
                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_ProgramList:
        {
            dstype = logAdvType_ProgramList;;
            count = d_logo_get_img_count(dstype);
            if(idx >= count)
                return D_ERR;
            logo_info = d_logo_load_img_data(dstype, idx);
            if(!logo_info)
            {
                return D_ERR;
            }
            if(logo_info->item.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                pic->data_type = DAD_M2V_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->id = 0;
            }
            else
            {
                pic->uctotal = count;
                pic->id = 0;
                pic->data_type = DAD_PIC_DATA;
                pic->data_rsc_ptr = (D_Ptr)(logo_info);
                pic->if_erase = 0;
                pic->times = (D_U32)logo_info->item.times * 100;
                pic->image = (D_Image *)(logo_info->buffer);

                pic->left = 349;    /*坐标   */
                pic->top = 594; /*坐标   */
                return D_OK;
            }
            return D_ERR;
        }
        default:
            break;
    }
    return D_ERR;

}

/** @brief  释放资源
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result d_hv1ad_release_img(D_Ad_Pos_Type type, D_U8* image)D_FUNCPOSTFIT
{
    logo_info_t *logo_info = (logo_info_t *)(image);
    type = type;
    return logo_release_img_data(logo_info);
}
/**以下几个函数是直接取保存的数据，用来给上层自己显示的时候使用*/
static D_U8 d_hv1ad_get_img_count_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    P_Log_Advertisement tmptype;

    switch(type)
    {
        case DAD_STB_LOG:        /*开机广告*/
        {
            tmptype = logAdvType_PowerOn;
            break;
        }
        case DAD_STB_RadioBackGround:
        {
            tmptype = logAdvType_RadioBackGround;
            break;
        }
        case DAD_STB_Nosignal:
        {
            tmptype = logAdvType_Nosignal;
            break;
        }
        case DAD_STB_NoProgram:
        {
            tmptype = logAdvType_NoProgram;
            break;
        }
        default:
            return 0;
    }
    return d_logo_get_img_count(tmptype);

}
static D_Result d_hv1ad_load_img_data_ex(D_Ad_Pos_Type type, D_U8 no, d_ad_pict_info *info)D_FUNCPOSTFIT
{
    P_Log_Advertisement tmptype;
    logo_info_t *param = NULL;

    switch(type)
    {
        case DAD_STB_LOG:        /*开机广告*/
        {
            tmptype = logAdvType_PowerOn;
            break;
        }
        case DAD_STB_RadioBackGround:
        {
            tmptype = logAdvType_RadioBackGround;
            break;
        }
        case DAD_STB_Nosignal:
        {
            tmptype = logAdvType_Nosignal;
            break;
        }
        case DAD_STB_NoProgram:
        {
            tmptype = logAdvType_NoProgram;
            break;
        }
        default:
            return D_ERR;
    }
    param =  d_logo_load_img_data(tmptype, no);
    if(param == NULL)
    {
        return D_ERR;
    }
    info->advType = param->item.advType;
    info->imgType = param->item.imgType;
    info->id = param->picid;
    info->buffer = param->buffer;
    info->img_size = param->item.img_size;
    info->times = (D_U32)param->item.times * 100;
    info->left = param->item.left;
    info->top = param->item.top;
    info->width = param->item.width;
    info->height = param->item.height;
    info->hand = (D_U8*)param;

    return D_OK;
}
static D_Result d_hv1ad_release_img_data_ex(d_ad_pict_info *img_data)D_FUNCPOSTFIT
{
    return d_logo_release_img_data((logo_info_t *)img_data->hand);
}

const D_Ad_Op dhaierv1ad_op =
{
    NULL,
    d_hv1ad_Init,
    d_hv1ad_exit,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    d_hv1ad_get_img,
    d_hv1ad_release_img,
    NULL,
    NULL,
    d_hv1ad_CheckApp,
    NULL,
    NULL,
    NULL,
    NULL,
    d_hv1ad_get_img_count_ex,
    d_hv1ad_load_img_data_ex,
    d_hv1ad_release_img_data_ex,
};
D_U8 * d_dad_getop(void)D_FUNCPOSTFIT
{
    return (D_U8*)(&dhaierv1ad_op);
}

