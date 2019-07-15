#include "dDebug.h"
#include "pConfig.h"
#include "ptvGuiResource.h"

#include "dSys.h"


#define _IMAGE_ID_START 		tv_IMG_ID_START
#define _IMAGE_ID_SINGLE_MAX 	tv_IMG_ID_ENUM_MAX
#define _IMAGE_ID_COMB_MAX 	tv_COMB_ID_ENUM_MAX
#define _IMAGE_ID_FREE_MAX	tv_IMG_ID_FS_ENUM_MAX

#define _LAN_ENG 	tv_LANCOUNTRY_English
#define _LAN_CHN 	tv_LANCOUNTRY_Chinese

#define _IMG_ENG 	0
#define _IMG_CHN 	1


#define _IMAGE_NUM	(_IMAGE_ID_SINGLE_MAX - _IMAGE_ID_START)


static D_U8 language = _LAN_ENG;
static D_U8 img_lang = _IMG_ENG;
static D_SysImage sys_images[_IMAGE_NUM] = {0};
static D_GSurface* gui_surf;



static D_Image *get_resource_image(int id, D_U32 *res_type, D_U32 *pRes_addr)
{
	D_S32 idx;
	D_U32 type = D_IMAGE_ID_RES_TYPE_INVALID;
	D_Image*  pimg = NULL;
	D_U32  pdata = 0;
	
    	if((id >= _IMAGE_ID_START) && (id != _IMAGE_ID_SINGLE_MAX) && (id != _IMAGE_ID_COMB_MAX))
    	{
  		if(id < _IMAGE_ID_SINGLE_MAX)
  		{
			idx = id - _IMAGE_ID_START;

			/* 检查是否需要现加载图片 */
			if(sys_images[idx].image[img_lang].img == NULL)
			{
				sys_images[idx].image[img_lang].buffer = tv_LoadImageData(id, img_lang, &(sys_images[idx].image[img_lang].size));
				sys_images[idx].image[img_lang].img = d_g_load_image (gui_surf, D_IMAGE_AUTO, 
						(D_U8*)sys_images[idx].image[img_lang].buffer, sys_images[idx].image[img_lang].size);
				if (sys_images[idx].image[img_lang].img == NULL)
				{
					D_DUMP("tv GUI load_res error:%d\n",id);
					return NULL;
				}
			}
			
			type = D_IMAGE_ID_RES_TYPE_SINGLE_IMAGE;
			pimg = sys_images[idx].image[img_lang].img;
  		}
		
		else if(id < _IMAGE_ID_COMB_MAX)
		{
			pimg = NULL;
			type = D_IMAGE_ID_RES_TYPE_COMB_IMAGES;
			pdata = (D_U32)tv_LoadCombineImageData(id);
		}

		else if(id < _IMAGE_ID_FREE_MAX)
		{
			pimg = NULL;
			type = D_IMAGE_ID_RES_TYPE_FREE_SHAPE;
			pdata = (D_U32)tv_LoadFreeShape(id, 0);
		}
    	}

	if(res_type)
	{
		*res_type = type;
	}
	
	if(pRes_addr)
	{
		*pRes_addr = (D_U32)pdata;
	}

	return pimg;
}


static D_Char *get_resource_text(int id)
{
	return tv_LoadIdsRes(id, language);
}

static D_Color get_resource_colour(int id)
{
	return (D_Color)tv_GetColorData(id);
}


D_Result p_gui_tv_lang_set(D_U8 lang)
{
	switch(lang)
	{
		case D_LANG_ENG:
			language = _LAN_ENG;
			img_lang = _IMG_ENG;
			break;			
		case D_LANG_CHN:
		default:
			language = _LAN_CHN;
			img_lang = _IMG_CHN;
			break;
	}

	return D_OK;
}


D_Result p_gui_tv_resource_init(void)
{
	int i, idx;
	D_U32 t1, t2;

	t1 = d_sys_get_time();

	gui_surf = d_gui_get_surface();
	
	for (i = _IMAGE_ID_START; i < _IMAGE_ID_SINGLE_MAX; i++)
	{
		idx = i - _IMAGE_ID_START;
		sys_images[idx].image[_LAN_ENG].buffer = tv_LoadImageData(i, _LAN_ENG, &(sys_images[idx].image[_LAN_ENG].size));
		sys_images[idx].image[_LAN_CHN].buffer = tv_LoadImageData(i, _LAN_CHN, &(sys_images[idx].image[_LAN_CHN].size));
		
		sys_images[idx].image[_LAN_ENG].img = d_g_load_image (gui_surf, D_IMAGE_AUTO, 
				(D_U8*)sys_images[idx].image[_LAN_ENG].buffer, sys_images[idx].image[_LAN_ENG].size);
		
		if (sys_images[idx].image[_LAN_ENG].img == NULL)
		{
			D_DUMP("tv Eng Image load error:%d\n",i);
			return D_ERR;
		}

		/*中英文图片相同*/
		if(sys_images[idx].image[_LAN_ENG].buffer == sys_images[idx].image[_LAN_CHN].buffer)
		{
			sys_images[idx].image[_LAN_CHN].img = sys_images[idx].image[_LAN_ENG].img;
		}
		else
		{
			sys_images[idx].image[_LAN_CHN].img = d_g_load_image (gui_surf, D_IMAGE_AUTO, 
					(D_U8*)sys_images[idx].image[_LAN_CHN].buffer, sys_images[idx].image[_LAN_CHN].size);
			
			if (sys_images[idx].image[_LAN_CHN].img == NULL)
			{
				D_DUMP("tv Chn Image load error:%d\n",i);
				return D_ERR;
			}
		}		
	}
	
	t2 = d_sys_get_time();
	D_INFO("Gui load tv %d Pictures cost %lu ms\n", _IMAGE_NUM, t2 - t1);

	return D_OK;
}


static D_GuiResourceOp tvResourceOp = 
{
	D_TRUE,
	4,
	0x4000,
	0x4fff,
	p_gui_tv_resource_init,/*如果资源想单独初始化，这里可以放空NULL*/
	p_gui_tv_lang_set,
	get_resource_text,
	get_resource_colour,
	get_resource_image,
};


D_Result p_gui_tv_resource_open(void)
{	
	d_gui_register_callback((D_Ptr)(&tvResourceOp), GUI_RESOURCE_OP);
	return D_OK;
}

