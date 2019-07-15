/** @file
* @brief ���ģ��֧�Žӿ�
* @author liuwf
* @date 2014-03-11 liuwf: �����ļ�
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



/** @brief  ֧�ֵ�ͼƬ��ʾӦ������*/
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

/** @brief  LOGO�е�ͼƬ��Ϣͷ����*/
typedef struct
{
    D_U32 crc;
    D_U32 length;
    D_U32 count;
} P_Logo_Header;

/** @brief  LOGO�е�ͼƬ��Ϣ����*/
typedef struct
{
    D_U32 advType;      // ͼƬӦ������
    D_ImageType imgType;// ͼƬ����
    D_Size off_ptr;     // img�����������е�ƫ��
    D_Size img_size;    // img���ݴ�С
    D_U16 times;        // img��ʾʱ�� 100ms
    D_U16 left;                     // img��ʾ�������
    D_Int top;                      // img��ʾ�������
    D_Int width;                        // img��ʾ���
    D_Int height;                       // img��ʾ�߶�
    D_U32 crc;

} Logo_Item;

/** @brief  LOGO�е�ͼƬ��Ϣ����֮���Ӧ�õ�������Ϣ*/
typedef struct logo_info_s
{
    Logo_Item item;     /// ͼƬ��Ϣ
    D_U32 picid;
    D_U8 *buffer;      ///���ݵ�ָ��
    struct logo_info_s *next;
} logo_info_t;


/***************************************stb�ṩ��ad�ĺ���******************************************/
/******************************************���ģ���ṩ��stb���õĺ���****************************************************/

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

static  logo_info_t *logolist = NULL; ///����ͼƬ��Ϣ������

static  D_HNVPart hnvp = D_INVALID_HANDLE;


/** @brief logoģ���ڴ�����
* @param  size ����Ĵ�С
* @return NULL -- ��Ч D_Ptr -- ���뵽�ĵ�ַ
*/
D_Ptr logo_mem_alloc(D_Size size)
{
    D_Ptr buf;

    buf = d_mem_alloc(0, size);
    D_DUMP("[advalloc]buf [0x%lx] size[0x%lx]\n", buf , size);

    return  buf;
}

/** @brief logoģ���ڴ��ͷ�
* @param  p Ҫ�ͷŵ��ڴ��ַ
* @return
*/
void logo_mem_free(D_Ptr p)
{
    D_DUMP("[advallocfree]buf [0x%lx]\n", p);
    d_mem_free (p);
}

/** @brief CRC32λУ��
* @param  ptr_data ���ݵ�ַ
* @param  data_length ���ݳ���
* @param  ucrc_verify У��ֵ
* @return D_OK:У��ɹ�  ; D_ERR:У��ʧ��
*/
static D_Result logo_crc32_check(const void *ptr_data, D_Size data_length, D_U32 ucrc_verify) D_FUNCPOSTFIT
{
    unsigned long ccrc;

    ccrc = d_crc_compute_32((unsigned char*)ptr_data, data_length);
    return ccrc == ucrc_verify ? D_OK : D_ERR;
}

/** @brief ȡ��img������Ϣ
* @param [in]ptr    img����������Ϣ�׵�ַ
* @param [out]dli   img������Ϣ�ṹ������
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

/** @brief ���logo��Ϣ�Ƿ���Ч
* @param [in]logo_data  logo�����׵�ַ
* @return D_OK  logo��ЧD_ERR   logo������Ч
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

/** @brief ���logo���ܵĳ���
* @param [in]logo_data_partial logo����ǰ�沿�֣����ٰ���32�ֽ�
* @return  logo���ݿ��ܵĳ���
*/
D_Size logo_peek_size(const void *logo_data_partial) D_FUNCPOSTFIT
{
    D_Size size_logo = U32_BE32_OFF(logo_data_partial, 4);
    return size_logo + 8;
}

/** @brief ���logo���ܵ�����
* @param [in]logo_data_partial      logo����ǰ�沿�֣����ٰ���32�ֽ�
* @return logo���ݿ��ܵ�����
*/
D_Int logo_get_count(const void *logo_data_partial) D_FUNCPOSTFIT
{
    D_Int  count = U32_BE32_OFF(logo_data_partial, 8);
    return count;
}

/** @brief ��ȡlogo��ָ��λ�õ�img������Ϣ
* @pram [in]logo_data       logo�����׵�ַ
* @pram [in]no          ָ����img��λ�ã�0�����һ�����Դ�����
* @pram [out]logo_item  logo������ָ��img��������Ϣ����������׵�ַ
* @return D_OK          �ɹ���logo_item����
* @return D_ERR         ʧ�ܣ�logo_item������
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

/** @brief ���������һ��ͼƬ����Ϣ
* @param list   ��������
* @param type   ͼƬ��Ӧ������
* @param no     �ڼ���
* @return �ҵ���ͼƬ���� NULL --��Ч
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

/** @brief ���������һ��ͼƬ����Ϣ
* @param list   ��������
* @param type   ͼƬ��Ӧ������
* @return �ҵ���ͼƬ����
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

/** @brief ���������һ��ͼƬ����Ϣ
* @param list   ��������
* @param newlist    �µ�ͼƬ������Ϣ
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

/** @brief �ͷ�ĳ��ͼƬ
* @param img_data   ͼƬ��Ϣ��ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
* @note   �ڲ�ʹ�õĽӿ�
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

/** @brief �ͷ��������е��ڴ棬��p_adv_destroyʱ��ʹ��
* @param list   ��������
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

/** @brief ��logoģ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

    ret = d_nvpart_read(hnvp, 0, buf, (D_Size)sizeof(P_Logo_Header));   ///ͷ��Ϣ
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
    ret = d_nvpart_read(hnvp, 0, tempbuf, (D_Size)ret); ///��������
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
/** @brief �ر�logoģ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ��ȡĳ��Ӧ�õ�ͼƬ����
* @param  type ͼƬӦ������
* @return ��������Ӧ�õ�ͼƬ������
*/
D_U8 d_logo_get_img_count (P_Log_Advertisement type) D_FUNCPOSTFIT
{
    return logo_get_count_type(logolist, type);
}

/** @brief ��ȡĳ��Ӧ�õ�ͼƬ���ݺ���Ϣ
* @param  type ͼƬӦ������
* @param  no �ڼ���������͵�ͼƬ
* @return ����ͼƬ��Ϣ��ָ��
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
    ret = d_nvpart_read(hnvp, info->item.off_ptr, buf, (D_Size)info->item.img_size);    ///ͷ��Ϣ
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

/** @brief �ͷ�ĳ��ͼƬ
* @param img_data   ͼƬ��Ϣ��ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
* @note   ���ⲿʹ�õĽӿ�
*/
D_Result d_logo_release_img_data(logo_info_t *img_data)D_FUNCPOSTFIT
{
    return logo_release_img_data(img_data);
}

/////////////////�ⲿ����////////////
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
        case    DAD_STB_VOLUME:      /*�������*/
        {
            hitype = logAdvType_AudioVolume;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case    DAD_STB_MENU:        /*���˵����*/
        {
            hitype = logAdvType_MainMenu;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case    DAD_STB_BANNER:          /*��Ŀ��Ϣ�����*/
        {
            hitype = logAdvType_ProgramBanner;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case DAD_STB_ProgramList: /*��Ŀ������*/
        {
            hitype = logAdvType_ProgramList;
            temp = d_logo_get_img_count (hitype);
            break;
        }
        case DAD_STB_EPG: /*��Ŀ������*/
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


/** @brief  �˳����Ӧ��
* @param[in]
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result d_hv1ad_get_img(D_Ad_Service_Param *chan_param, D_Ad_Pos_Type type, D_U8 idx, D_U8* info)D_FUNCPOSTFIT
{
    D_U8 count;
    P_Log_Advertisement dstype;
    logo_info_t *logo_info = NULL;
    D_Ad_Image_Param* pic = (D_Ad_Image_Param*)info;

    pic->left = 0;    /*����    */
    pic->top = 0;      /*����   */

    switch(type)
    {
        case DAD_STB_MENU: //DAD_STB_LOG:       //�������
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
                pic->left = 666;    /*����   */
                pic->top = 448; /*����   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_EPG: //DAD_STB_LOG:        //�������
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
                pic->left = 666;    /*����   */
                pic->top = 448; /*����   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_VOLUME: //DAD_STB_LOG:     //�������
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
                pic->left = 668;    /*����   */
                pic->top = 546; /*����   */

                return D_OK;
            }
            return D_ERR;
        }
        case DAD_STB_BANNER: //DAD_STB_LOG:     //�������
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

                pic->left = 668;    /*����   */
                pic->top = 546; /*����   */
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

                pic->left = 349;    /*����   */
                pic->top = 594; /*����   */
                return D_OK;
            }
            return D_ERR;
        }
        default:
            break;
    }
    return D_ERR;

}

/** @brief  �ͷ���Դ
* @param[in]
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result d_hv1ad_release_img(D_Ad_Pos_Type type, D_U8* image)D_FUNCPOSTFIT
{
    logo_info_t *logo_info = (logo_info_t *)(image);
    type = type;
    return logo_release_img_data(logo_info);
}
/**���¼���������ֱ��ȡ��������ݣ��������ϲ��Լ���ʾ��ʱ��ʹ��*/
static D_U8 d_hv1ad_get_img_count_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    P_Log_Advertisement tmptype;

    switch(type)
    {
        case DAD_STB_LOG:        /*�������*/
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
        case DAD_STB_LOG:        /*�������*/
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

