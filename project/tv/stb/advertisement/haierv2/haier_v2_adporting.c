/** @file
* @brief  haier广告2.0版本
* @author huangq
* @date 2014-06-16 huangq:实现2.0版本haier广告功能，包括开机LOGO和信息条广告
*/
#include "dMMan.h"
#include "dMem.h"
#include "dMsg.h"
#include "dResource.h"
#include "dTimer.h"
#include "dDebug.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dApp.h"
#include "dDate.h"
#include "dDBase.h"
#include "dProgScan.h"
#include <string.h>
#include <stdarg.h>
#include "dTV.h"
#include "pPlayer.h"
#include "dNVPart.h"
#include "dDBaseInternal.h"
#include "pMonitorRegister.h"
#include "dCBMan.h"
#include "pConfig.h"
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pSIParse.h"
#include "dSem.h"
#include "dSys.h"
#include "dEvent.h"
#include "dDemux.h"
#include "dNVRam.h"
#include "dGDev.h"
#include "dTypes.h"
#include "dadporting.h"
#include "dad_data_store.h"
#include "dTask.h"
#include "dScan.h"
#include "dQueue.h"
#include "dCrc.h"
#include "haier_v2_ad_api.h"

#define HIV2AD_PRINT_EN 1

#if HIV2AD_PRINT_EN
#define HIV2AD_DUMP D_DUMP
#define HIV2AD_ERROR D_ERROR
#else
#define HIV2AD_DUMP(_s,...)
#define HIV2AD_ERROR(_s,...)
#endif

/**  Definitions *************************************************************/

/** @brief AD搜索资源*/
typedef struct
{
    D_HMMan     hmm;            /**@brief < 为搜索分配的内存创建的内存管理器句柄*/
    D_HSem      hsem;
    D_U8           *buf;            /**@brief < 为搜索分配的内存地址*/
    D_hiv2_fullscan   fullscan[DAD_PIC_TOTAL_TYPE];/**@brief < 显示挂角的状态*/
    D_U8            dataflag[DAD_STB_POS_UNKNOWN][DAD_PIC_TOTAL_TYPE];/**@brief < 记录状态*/
    D_U32           osd_id;        /**@brief < 记录上次显示的osd的序号*/
    D_U8            osd_idx;        /**@brief < 记录上次显示的osd的序号*/
    D_Ad_Service_Param chan_param;  /**@brief < 记录节目参数*/
} d_hiv2ad_esdata;

#define  D_HIV2AD_PMEM_SIZE    (0x10000+sizeof(d_hiv2ad_esdata))
static d_hiv2ad_esdata *hiv2ades = NULL ;   /**@brief 广告指针*/
/***************************************完成******************************************/
/** @brief  查找指定ID的推送广告
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result hiv2ad_find_id(D_U32 ID, D_U8* idx)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < DAD_PIC_TOTAL_TYPE ; i++)
    {
        if(hiv2ades->fullscan[i].data_ptr != NULL && hiv2ades->fullscan[i].id == ID)
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}

/** @brief 查找推送广告一个可用ID
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result hiv2ad_find_idle(D_U8* idx)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < DAD_PIC_TOTAL_TYPE ; i++)
    {
        if((hiv2ades->fullscan[i].data_ptr == NULL) && (hiv2ades->fullscan[i].erase == 0))
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}

/** @brief  清除所有推送广告信息*/
static void hiv2ad_clean_all(void)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0 ; i < DAD_PIC_TOTAL_TYPE ; i++)
    {
        hiv2ades->fullscan[i].data_type = DAD_PIC_DATA;
        hiv2ades->fullscan[i].data_ptr = NULL;
        hiv2ades->fullscan[i].erase = 0;
        hiv2ades->fullscan[i].id = 0;
    }
    return ;
}

/** @brief 查找下一个滚条 */
static D_Result hiv2ad_find_nextosd(hiv2ad_osd_prog_show_info* info, D_U8 num, D_U8 times, D_U8* idx)D_FUNCPOSTFIT
{
    D_U8 i;
    for(i = num; i < info->ucOsdNum; i++)
    {
        if((info->stTextShow[i].scrollend == 0) || (info->stTextShow[i].ucShowTimes == 0))
        {
            *idx = i;
            return D_OK;
        }
    }
    for(i = 0; i < num; i++)
    {
        if((info->stTextShow[i].scrollend == 0) || (info->stTextShow[i].ucShowTimes == 0))
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}


/** @brief  初始化广告数据
* @param[in]    要初始化的指针数据
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_init(D_Ad_Init_Param *cfg)D_FUNCPOSTFIT
{
    d_hiv2ad_esdata  *es;
    D_U8        *buf;
    D_HMMan hmm;
    D_HSem  hsem;
    D_SemAttr attr;

    d_ad_store_open();
    buf = (D_U8*) d_mem_alloc(0, D_HIV2AD_PMEM_SIZE);

    if(! buf)
    {
        HIV2AD_ERROR ("Cannot allocate hiv2ad scan memory\n");
        return NULL;
    }
    hmm = d_mman_create((D_Ptr)buf, (D_Size)D_HIV2AD_PMEM_SIZE, (D_MManType)D_MMAN_HEAP); //创建一个内存管理器
    HIV2AD_DUMP("[ad]ad_start[buf:0x%x][hmm:0x%x][size:0x%x]\n", buf, hmm, D_HIV2AD_PMEM_SIZE);

    if(D_INVALID_HANDLE == hmm)
    {
        HIV2AD_ERROR ("Cannot create hiv2ad memory manager\n");
        d_mem_free (buf);
        return NULL;
    }

    es = (d_hiv2ad_esdata*) d_mman_alloc((D_HMMan)hmm, sizeof (d_hiv2ad_esdata)); //通过内存管理器分配一块内存
    if(! es)
    {
        HIV2AD_ERROR ("Cannot allocate hiv2ad scan data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(es, 0, sizeof (d_hiv2ad_esdata));
    es->hmm = hmm;
    es->buf = buf;
    hiv2ades = es;
    es->hsem = D_INVALID_HANDLE;
    D_SEM_ATTR_INIT (&attr);
    hsem = d_sem_create (&attr);
    es->hsem = hsem;
    d_sem_post (es->hsem);
    hiv2ad_open(cfg->ucPriority, cfg->cb);
    return D_OK;
}


/** @brief  退出广告应用
* @param[in]
* @return
* @note
*/
static D_Result d_hiv2ad_exit(void)D_FUNCPOSTFIT
{
    d_ad_store_close();
    if(D_INVALID_HANDLE  != hiv2ades->hmm)
    {
        HIV2AD_DUMP("[ad]d_mman_destroy[ es->hmm:0x%x]\n", hiv2ades->hmm);
        d_mman_destroy (hiv2ades->hmm);                                     /*释放一个内存管理器*/
        hiv2ades->hmm = D_INVALID_HANDLE;
    }
    if(D_INVALID_HANDLE  != hiv2ades->hsem)
    {
        d_sem_destroy (hiv2ades->hsem);                                     /*释放一个内存管理器*/
        hiv2ades->hsem = D_INVALID_HANDLE;
    }
    if(hiv2ades->buf)
    {
        HIV2AD_DUMP("[ad]d_mem_free[buf:0x%x]\n", hiv2ades->buf);
        d_mem_free (hiv2ades->buf);                                                     /*释放分配的内存*/
        hiv2ades->buf = NULL;
    }
    hiv2ad_Close();
    return D_OK;
}


/** @brief  重新打开广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_reset(void)D_FUNCPOSTFIT
{
//重新组织数据
    D_U8 i, j;

    for(i = 0 ; i < DAD_STB_POS_UNKNOWN ; i++)
    {
        for(j = 0 ; j < DAD_PIC_TOTAL_TYPE ; j++)
        {
            hiv2ades->dataflag[i][j] = 0 ;
        }
    }
    return D_OK;
}

/** @brief  打开广告菜单
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_enter_menu(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    D_U8 j;
    if(type >= DAD_STB_POS_UNKNOWN)
    {
        return D_ERR;
    }
    for(j = 0 ; j < DAD_PIC_TOTAL_TYPE ; j++)
    {
        hiv2ades->dataflag[type][j] = 0 ;
    }

    return D_OK;
}

/** @brief  退出广告菜单
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_exit_menu(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    //作废之前的数据
    D_U8 j;
    if(type >= DAD_STB_POS_UNKNOWN)
        return D_ERR;

    for(j = 0 ; j < DAD_PIC_TOTAL_TYPE ; j++)
    {
        hiv2ades->dataflag[type][j] = 0 ;
    }

    return D_OK;
}

/** @brief  设置广告应用的PID
* @param[in] descr广告标签  id三洲广告
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_SetDescr(D_U8 * descr, D_U32 id)D_FUNCPOSTFIT
{
    return D_OK;
}

/** @brief  设置广告应用标签
* @param[in] ttag广告应用标签，id三洲广告
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_SetTag(D_U8 ttag, D_U32 id)D_FUNCPOSTFIT
{
    return D_OK;
}

/** @brief  检查广告数据
* @param[in]    type类型
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_CheckApp(D_Ad_Pos_Type type, D_Ad_Service_Param* chan_param)D_FUNCPOSTFIT
{
    switch(type)
    {
        case  DAD_STB_VOLUME:         /*音量广告*/
        case  DAD_STB_MENU:           /*主菜单广告*/
        case  DAD_STB_BANNER:         /*节目信息条广告*/
        case  DAD_STB_FULLSCREEN:     /*挂角广告*/
        case  DAD_STB_OSD:            /*滚动字幕广告*/
        case  DAD_STB_ProgramList:    /*节目列表广告*/
        case  DAD_STB_EPG:            /*EPG广告*/
        case  DAD_STB_RadioBackGround:/*广播背景广告*/
        case  DAD_STB_Nosignal:       /*无信号广告*/
        case  DAD_STB_NoProgram:      /*无节目广告*/
            break;
        default:
            return D_ERR;
    }
    return D_OK;
}

D_Result d_hiv2ad_chan_change(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT
{
    hiv2ad_chan_change(chan_param);
    return D_OK;
}
/** @brief  需要主动显示的广告
* @param[in]    ucMessageType显示类型 pucMessage数据
* @return NULL
* @note
*/
void d_hiv2ad_ShowMessage(D_U8 ucMessageType, D_U8* pucMessage)D_FUNCPOSTFIT
{
//    D_Ad_Img_Param img_param;
    D_hiv2_fullscan  pucmsg;

    switch(ucMessageType)
    {
        case HIV2AD_MSEEAGE_SHOWFULLSRCEEN_TYPE:      //显示挂角广告
			{
				if(pucMessage == NULL)
					return ;
				memcpy((D_U8*)(&pucmsg), (D_U8*)(pucMessage), sizeof(D_hiv2_fullscan));

				if(pucmsg.data_type == DAD_PIC_DATA)
				{
					D_U8 idx;
					D_U32 element_id;

					element_id = pucmsg.id;

					d_sem_wait(hiv2ades->hsem);
					if(hiv2ad_find_id(element_id, &idx) == D_OK)
					{
					}
					else
					{
						if(hiv2ad_find_idle(&idx) == D_ERR)
						{
							d_sem_post (hiv2ades->hsem);
							return;
						}
					}
					hiv2ades->fullscan[idx].left  = pucmsg.left;
					hiv2ades->fullscan[idx].top   = pucmsg.top;
					hiv2ades->fullscan[idx].data_type = DAD_PIC_DATA;
					hiv2ades->fullscan[idx].data_ptr  = pucmsg.data_ptr;
					hiv2ades->fullscan[idx].data_len  = pucmsg.data_len;
					hiv2ades->fullscan[idx].erase = 0;
					hiv2ades->fullscan[idx].id    = element_id;
					hiv2ades->fullscan[idx].duration    = pucmsg.duration;
					hiv2ades->dataflag[DAD_STB_FULLSCREEN][idx] = 0;
					d_sem_post (hiv2ades->hsem);
				}
				break;
			}
        case HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE:          //隐藏挂角广告
			{
				d_sem_wait(hiv2ades->hsem);
				if(pucMessage == NULL)
				{
					hiv2ad_clean_all();
					hiv2ades->fullscan[0].data_type = DAD_PIC_DATA;
					hiv2ades->fullscan[0].data_ptr = NULL;
					hiv2ades->fullscan[0].erase = 0xff;
					hiv2ades->fullscan[0].id = 0;
					hiv2ades->dataflag[DAD_STB_FULLSCREEN][0] = 0;
					d_sem_post (hiv2ades->hsem);
					break;
				}
				else
				{
					D_U8 idx;
					D_U32 element_id;
					memcpy((D_U8*)(&pucmsg), (D_U8*)(pucMessage), sizeof(D_hiv2_fullscan));

					element_id = pucmsg.id;
					if(hiv2ad_find_id(element_id, &idx) == D_OK)
					{
						hiv2ades->fullscan[idx].data_type = DAD_PIC_DATA;
						hiv2ades->fullscan[idx].data_ptr = NULL;
						hiv2ades->fullscan[idx].erase = 1;
						hiv2ades->fullscan[idx].id = element_id;
						hiv2ades->dataflag[DAD_STB_FULLSCREEN][idx] = 0;
					}
					d_sem_post (hiv2ades->hsem);
				}
				break;
			}

        default:
            break;
    }
}

/** @brief  获取保存的图片
* @param[in]chan_param 节目参数；type 广告类型；idx 指定的id；info 广告参数
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_get_img(D_Ad_Service_Param* chan_param, D_Ad_Pos_Type type, D_U8 idx, D_U8* info)D_FUNCPOSTFIT
{
#if 1
    D_U8 ret;
    hiv2ad_program_para ProgramPara;
//    HIV2_Ad_Pos_Type mgtype;
    D_Image* image = NULL;
    D_Ad_Image_Param* pic = (D_Ad_Image_Param*)info;
    D_Ad_Osd_Param* osd = (D_Ad_Osd_Param*)info;
//    Ad_Data_Info *ad_data_info;
//    logo_info_mg *rsc_ptr;
    D_U8 totalnum = 1;
    HIV2_Ad_Pos_Type hiv2_adtype;
    D_U8 uctotal = 0;
    D_U16 show_left = 0;
    D_U16 show_top = 0;
    D_U32 show_times = 0x0;

    idx = idx;
    ProgramPara.usServiceId = chan_param->usServiceId;


    pic->left = 0;    /*坐标    */
    pic->top = 0;     /*坐标   */

    switch(type)
    {
        case DAD_STB_FULLSCREEN:    //推送广告
			{
				D_U8 i;

				d_sem_wait(hiv2ades->hsem);
				for(i = 0 ; i < DAD_PIC_TOTAL_TYPE ; i++)
				{
					if(hiv2ades->dataflag[DAD_STB_FULLSCREEN][i] == 0)
					{
						if(hiv2ades->fullscan[i].erase != 0)
						{
							pic->data_type = hiv2ades->fullscan[i].data_type;
							pic->data_rsc_ptr = NULL;
							pic->if_erase = hiv2ades->fullscan[i].erase;
							pic->id = hiv2ades->fullscan[i].id;
							pic->image = NULL;
							pic->left = hiv2ades->fullscan[i].left;
							pic->top = hiv2ades->fullscan[i].top;
							pic->uctotal = 1;
							hiv2ades->fullscan[i].erase = 0;
							hiv2ades->dataflag[DAD_STB_FULLSCREEN][i] = 1;

							d_sem_post (hiv2ades->hsem);
							return D_OK;
						}
						if(hiv2ades->fullscan[i].data_ptr != NULL)
						{
							image = (D_Image*)d_g_load_image (d_gui_get_surface(), D_IMAGE_AUTO, (D_U8*)(hiv2ades->fullscan[i].data_ptr), (D_Size)(hiv2ades->fullscan[i].data_len));
							if (image == NULL)
							{
								HIV2AD_DUMP("[ad]d_mg_load_cor_image error:%d\n", hiv2ades->fullscan[i].data_len);
								d_sem_post (hiv2ades->hsem);
								return D_ERR;
							}
							pic->data_type = hiv2ades->fullscan[i].data_type;
							pic->data_rsc_ptr = (D_Ptr)(image);
							pic->if_erase = hiv2ades->fullscan[i].erase;
							pic->id = hiv2ades->fullscan[i].id;
							pic->image = image;
							pic->left = hiv2ades->fullscan[i].left;
							pic->top = hiv2ades->fullscan[i].top;
							pic->uctotal = 1;
							hiv2ades->dataflag[DAD_STB_FULLSCREEN][i] = 1;

							HIV2AD_DUMP("d_MGad_get_img3cor[ptr:0x%x]\n", pic->image);

							d_sem_post (hiv2ades->hsem);
							return D_OK;
						}
					}
				}
				d_sem_post (hiv2ades->hsem);
				return D_ERR;
			}
        case DAD_STB_OSD:           //滚动字幕广告
			{
				D_U8 chanflag = 0;
				hiv2ad_osd_prog_show_info *OsdPShow;
				ProgramPara.usNetworkId = chan_param->usNetworkId;
				ProgramPara.usTsId = chan_param->usTsId;
				ProgramPara.usServiceId = chan_param->usServiceId;
				if(memcmp(&hiv2ades->chan_param, chan_param, sizeof(D_Ad_Service_Param)) != 0)
				{
					memcpy(&hiv2ades->chan_param, chan_param, sizeof(D_Ad_Service_Param));
					chanflag = 1;
					hiv2ades->dataflag[DAD_STB_OSD][0] = 0;
				}
				OsdPShow = (hiv2ad_osd_prog_show_info*) d_mman_alloc(hiv2ades->hmm, sizeof(hiv2ad_osd_prog_show_info)); //通过内存管理器分配一块内存
				if(OsdPShow == NULL)
				{
					return D_ERR;
				}
				ret = hiv2ad_ProgramGetOSD(ProgramPara, OsdPShow);
				if(ret == D_OK && OsdPShow->ucOsdNum)
				{
					D_U8 num;
					if(hiv2ades->osd_idx >= OsdPShow->ucOsdNum)
					{
						hiv2ades->osd_idx = 0;
					}
					if(hiv2ad_find_nextosd(OsdPShow, hiv2ades->osd_idx, 0, &num) == D_OK)
					{
						if((hiv2ades->osd_id == OsdPShow->stTextShow[num].txtId) && (hiv2ades->dataflag[DAD_STB_OSD][0] == 1))
						{
							d_mman_free (hiv2ades->hmm, OsdPShow);
							return D_ERR;
						}
						osd->pucDisplayBuffer = (D_U8 *) d_mman_alloc (hiv2ades->hmm, OsdPShow->stTextShow[num].usContentSize + 1);
						if (osd->pucDisplayBuffer)
						{
							D_DUMP("d_mgad_get_img4[ptr:0x%x]id[%d]\n", osd->pucDisplayBuffer, OsdPShow->stTextShow[num].txtId);
							memset((D_U8 *)osd->pucDisplayBuffer, 0, OsdPShow->stTextShow[num].usContentSize + 1);
							memcpy((D_U8 *)osd->pucDisplayBuffer, (D_U8 *)OsdPShow->stTextShow[num].pucDisplayBuffer, OsdPShow->stTextShow[num].usContentSize);
							osd->data_rsc_ptr = osd->pucDisplayBuffer;

							osd->ucstartposx = OsdPShow->stTextShow[num].ucstartposx;              //显示次数
							osd->ucstartposy = OsdPShow->stTextShow[num].ucstartposy;              //显示次数
							osd->ucendposx = OsdPShow->stTextShow[num].ucendposx;              //显示次数
							osd->ucendposy = OsdPShow->stTextShow[num].ucendposy;              //显示次数

							osd->aucBackgroundColor = OsdPShow->stTextShow[num].aucBackgroundColor; //背景颜色

							osd->aucDisplayColor = OsdPShow->stTextShow[num].aucDisplayColor; //背景颜色
							osd->usContentSize = OsdPShow->stTextShow[num].usContentSize;      //osd内容长度
							osd->ucFontType = OsdPShow->stTextShow[num].ucFontType;                //字体类型
							osd->ucFontSize = OsdPShow->stTextShow[num].ucFontSize;                //字体大小
							osd->ucShowTimes = 1;            //显示次数
							osd->id = OsdPShow->stTextShow[num].txtId;           //id
							osd->uctotal = OsdPShow->ucOsdNum;             //总数
							osd->idx = num;              //总数
							switch(OsdPShow->stTextShow[num].txtSpeed)
							{
								case        1:
									osd->txtSpeed = 1;
									break;
								case        2:
									osd->txtSpeed = 7;
									break;
								default:
									osd->txtSpeed = 4;
									break;
							}
							if(osd->ucendposx == osd->ucstartposx)
								osd->enDisplayPos = LOCAL_VERTICAL;
							else
								osd->enDisplayPos = LOCAL_HORIZONTAL;

							osd->if_erase = 0;
							hiv2ades->osd_id = OsdPShow->stTextShow[num].txtId;
							hiv2ades->dataflag[DAD_STB_OSD][0] = 1;
							d_mman_free (hiv2ades->hmm, OsdPShow);
							return D_OK;
						}
					}
				}
				if(chanflag == 1)//如果换台了，查不到滚动条的话就擦除之前显示的
				{
					osd->pucDisplayBuffer = NULL;
					osd->data_rsc_ptr = NULL;
					osd->if_erase = 0xff;
					d_mman_free (hiv2ades->hmm, OsdPShow);
					return D_OK;
				}
				d_mman_free (hiv2ades->hmm, OsdPShow);
				return D_ERR;
			}

        case DAD_STB_EPG:           //节目指南广告
			{
				hiv2_adtype = HIV2AD_STB_EPG;
				image = hiv2ad_get_image_by_idx(hiv2_adtype, &ProgramPara, idx, &uctotal, &show_left, &show_top, &show_times);
				if(image != NULL)
				{
					pic->image = (D_Ptr)image;
					pic->uctotal = uctotal;
					pic->data_type = DAD_PIC_DATA;
					pic->id = 0;
					pic->data_rsc_ptr = (D_Ptr)image;
					if(show_left == 0 && show_top == 0)
					{
						pic->left = 360;    //坐标
						pic->top = 320;     //坐标
					}
					else
					{
						pic->left = show_left;  //坐标
						pic->top = show_top;    //坐标
					}
					if(show_times == 0x0 || show_times > 5000)
					{
						pic->times = 5000;
					}
					else
					{
						pic->times = show_times;
					}
					return D_OK;
				}
				return D_ERR;
			}
        case    DAD_STB_ProgramList:    //节目列表广告
			{
				hiv2_adtype = HIV2AD_STB_PROGRAM_LIST;  //节目列表广告

				image = hiv2ad_get_image_by_idx(hiv2_adtype, &ProgramPara, idx, &uctotal, &show_left, &show_top, &show_times);
				if(image != NULL)
				{
					pic->image = (D_Ptr)image;
					pic->uctotal = uctotal;
					pic->data_type = DAD_PIC_DATA;
					pic->id = 0;
					pic->data_rsc_ptr = (D_Ptr)image;
					if(show_left == 0 && show_top == 0)
					{
						pic->left = 210;    //坐标
						pic->top = 427;     //坐标
					}
					else
					{
						pic->left = show_left;  //坐标
						pic->top = show_top;    //坐标
					}
					if(show_times == 0x0 || show_times > 5000)
					{
						pic->times = 5000;
					}
					else
					{
						pic->times = show_times;
					}

					return D_OK;
				}
				return D_ERR;
			}
        case DAD_STB_VOLUME:        //音量条广告
			{
				hiv2_adtype = HIV2AD_STB_VOLUME;

				image = hiv2ad_get_image_by_idx(hiv2_adtype, &ProgramPara, idx, &uctotal, &show_left, &show_top, &show_times);
				if(image != NULL)
				{
					pic->image = (D_Ptr)image;
					pic->uctotal = uctotal;
					pic->data_type = DAD_PIC_DATA;
					pic->id = 0;
					pic->data_rsc_ptr = (D_Ptr)image;
					if(show_left == 0 && show_top == 0)
					{
						pic->left = 386;    //坐标
						pic->top = 438;     //坐标
					}
					else
					{
						pic->left = show_left;  //坐标
						pic->top = show_top;    //坐标
					}
					if((show_times == 0x0) || (show_times >= 5))
					{
						pic->times = 5000 / pic->uctotal;
					}
					else
					{
						pic->times = show_times;
					}

					return D_OK;
				}
				return D_ERR;
			}
        case DAD_STB_BANNER:    //换台条广告
			{
				hiv2_adtype = HIV2AD_STB_BANNER;

				image = hiv2ad_get_image_by_idx( hiv2_adtype, &ProgramPara, idx, &uctotal, &show_left, &show_top, &show_times);
				if(image != NULL)
				{
					pic->image = (D_Ptr)image;
					pic->uctotal = uctotal;
					pic->data_type = DAD_PIC_DATA;
					pic->id = 0;
					pic->data_rsc_ptr = (D_Ptr)image;
					if(show_left == 0 && show_top == 0)
					{
						pic->left = 386;    //坐标
						pic->top = 438;     //坐标
					}
					else
					{
						pic->left = show_left;  //坐标
						pic->top = show_top;    //坐标
					}
					if((show_times == 0x0) || (show_times >= 5))
					{
						pic->times = 5000 / pic->uctotal;
					}
					else
					{
						pic->times = show_times;
					}

					return D_OK;
				}
				return D_ERR;
			}
        case DAD_STB_MENU:      //主菜单广告
			{
				hiv2_adtype = HIV2AD_STB_MENU;

				image = hiv2ad_get_image_by_idx(hiv2_adtype, &ProgramPara, idx, &uctotal, &show_left, &show_top, &show_times);
				if(image != NULL)
				{
					pic->image = (D_Ptr)image;
					pic->uctotal = uctotal;
					pic->data_type = DAD_PIC_DATA;
					pic->id = 0;
					pic->data_rsc_ptr = (D_Ptr)image;
					if(show_left == 0 && show_top == 0)
					{
						pic->left = 348;    //坐标
						pic->top = 328;     //坐标
					}
					else
					{
						pic->left = show_left;  //坐标
						pic->top = show_top;    //坐标
					}
					if(show_times == 0x0 || show_times > 5000)
					{
						pic->times = 5000;
					}
					else
					{
						pic->times = show_times;
					}

					return D_OK;
				}
				return D_ERR;
			}
        case DAD_STB_UNAUTHORIZED:      //未授权节目广告
			{
				return D_ERR;
			}
        case DAD_STB_POS_UNKNOWN:
            return D_ERR;
    }
#endif
    return D_ERR;
}

/** @brief  释放资源
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_start(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT
{
    hiv2ad_SetDataPid();
    return D_OK;
}

/**********以下几个函数是直接取保存的数据，用来给上层自己显示的时候使用**********/
/** @brief  获取开机logo和广播背景，无节目和无信号时播放开机logo
* @param[in] type 广告图片类型
* @return
* @note
*/
static D_U8 d_hiv2ad_get_img_count_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    switch(type)
    {
        case DAD_STB_LOG:         /*开机广告*/
        case DAD_STB_NoProgram:   /*无节目背景*/
        case DAD_STB_Nosignal:    /*无信号背景*/
			{
				return d_ad_store_get_img_count(DAD_STB_LOG);
			}
        case DAD_STB_RadioBackGround:
			{
				return d_ad_store_get_img_count(type);
			}
        default:
            return 0;
    }
}

/** @brief  滚屏回调
* @param[in] idx 指定的id；total 总数
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_scroll_callback(D_U8 idx, D_U8 total)D_FUNCPOSTFIT
{
    if(hiv2ades)
    {
        hiv2ad_CallBackOSD(hiv2ades->osd_id);
        hiv2ades->osd_idx += 1;
        if(idx + 1 >= total)
        {
            hiv2ades->osd_idx = 0;
        }
        hiv2ades->dataflag[DAD_STB_OSD][0] = 0;

    }
    return D_ERR;
}

/** @brief   获取图片数据
* @param[in] type 广告图片类型；info 图片信息解析之后给应用的数据信息
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result d_hiv2ad_load_img_data_ex(D_Ad_Pos_Type type, D_U8 no, d_ad_pict_info* info)D_FUNCPOSTFIT
{
    Ad_Data_Info *param = NULL;
    D_Ad_Pos_Type type2;

    switch(type)
    {
        case DAD_STB_LOG:           /*开机广告*/
			{
				type2 = type;
				break;
			}
        case DAD_STB_NoProgram:     /*无节目背景*/
			{
				type2 = type;
				break;
			}
        case DAD_STB_Nosignal:      /*无信号背景*/
			{
				type2 = type;
				break;
			}
        case DAD_STB_RadioBackGround:/*广播背景*/
			{
				type2 = type;
				break;
			}
        default:
            return D_ERR;
    }
    param = d_ad_store_load_img_data(type2, no);
    if((D_U8*)param == NULL)
    {
        HIV2AD_DUMP("[hiv2ad] cannot load image,type=%d\n", type);
        return D_ERR;
    }
    info->advType = param->item.advType;
    info->imgType = param->item.imgType;
    info->id = param->picid;
    info->buffer = param->buffer;
    info->img_size = param->item.img_size;
    info->times = param->item.times;
    info->left = param->item.left;
    info->top = param->item.top;
    info->width = param->item.width;
    info->height = param->item.height;
    info->hand = (D_U8*)param;

    return D_OK;
}

/** @brief  释放图片数据资源
* @param[in]  数据指针
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_release_img_data_ex(d_ad_pict_info *img_data)D_FUNCPOSTFIT
{
    if(img_data == NULL)
        return D_ERR;

    return d_ad_store_release_img_data((Ad_Data_Info *)(img_data->hand));
}

/** @brief  释放图片内存资源
* @param[in] type 广告图片类型；image 图片信息解析之后给应用的数据信息
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_hiv2ad_release_img(D_Ad_Pos_Type type, D_U8* image)D_FUNCPOSTFIT
{
    if(image == NULL)
        return D_OK;
    if(type == DAD_STB_OSD)
    {
        d_mman_free(hiv2ades->hmm, image);
        return D_OK;
    }
    else
    {
        HIV2AD_DUMP("d_hiv2ad_release_img2[ptr:0x%x]\n", image);
        return d_image_free((D_Image *)image);
    }
}

const D_Ad_Op d_hiv2ad_op =
	{
		NULL,
		d_hiv2ad_init,
		d_hiv2ad_exit,
		d_hiv2ad_start,
		d_hiv2ad_reset,
		NULL,
		d_hiv2ad_enter_menu,
		d_hiv2ad_exit_menu,
		d_hiv2ad_get_img,
		d_hiv2ad_release_img,
		d_hiv2ad_SetDescr,
		d_hiv2ad_SetTag,
		d_hiv2ad_CheckApp,
		NULL,
		NULL,
		d_hiv2ad_scroll_callback,
		d_hiv2ad_chan_change,
		d_hiv2ad_get_img_count_ex,
		d_hiv2ad_load_img_data_ex,
		d_hiv2ad_release_img_data_ex,
	};

D_U8 * d_dad_getop(void)D_FUNCPOSTFIT
{
    return (D_U8*)(&d_hiv2ad_op);
}
