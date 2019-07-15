#include "dDebug.h"
#include "pConfig.h"
#include "patvGuiResource.h"

#include "dSys.h"


#define _IMAGE_ID_START 		atv_IMG_ID_START
#define _IMAGE_ID_SINGLE_MAX 	atv_IMG_ID_ENUM_MAX
#define _IMAGE_ID_COMB_MAX 	atv_COMB_ID_ENUM_MAX
#define _IMAGE_ID_FREE_MAX	atv_IMG_ID_FS_ENUM_MAX

#define _IMAGE_ID_MEDIA_START atv_IMG_ID_media_folder_file


#define _LAN_ENG 	atv_LANCOUNTRY_English
#define _LAN_CHN 	atv_LANCOUNTRY_Chinese

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
				sys_images[idx].image[img_lang].buffer = atv_LoadImageData(id, img_lang, &(sys_images[idx].image[img_lang].size));
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
			pdata = (D_U32)atv_LoadCombineImageData(id);
		}

		else if(id < _IMAGE_ID_FREE_MAX)
		{
			pimg = NULL;
			type = D_IMAGE_ID_RES_TYPE_FREE_SHAPE;
			pdata = (D_U32)atv_LoadFreeShape(id, 0);
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
	return atv_LoadIdsRes(id, language);
}

static D_Color get_resource_colour(int id)
{
	return (D_Color)atv_GetColorData(id);
}


D_Result p_gui_atv_lang_set(D_U8 lang)
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


D_Result p_gui_atv_resource_init(void)
{
	int i, idx, endidx;
	D_U32 t1, t2;

	t1 = d_sys_get_time();

	gui_surf = d_gui_get_surface();
	
    /*2610电视机项目，开机暂不解多媒体的图片, @qiny 2015.12.11*/
    endidx = _IMAGE_ID_MEDIA_START; //_IMAGE_ID_SINGLE_MAX;
    
	for (i = _IMAGE_ID_START; i < endidx; i++)
	{
		idx = i - _IMAGE_ID_START;
		sys_images[idx].image[_LAN_ENG].buffer = atv_LoadImageData(i, _LAN_ENG, &(sys_images[idx].image[_LAN_ENG].size));
		sys_images[idx].image[_LAN_CHN].buffer = atv_LoadImageData(i, _LAN_CHN, &(sys_images[idx].image[_LAN_CHN].size));
		
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
	D_INFO("Gui load tv %d Pictures cost %lu ms\n", (endidx - _IMAGE_ID_START), t2 - t1);

	return D_OK;
}

/* 2610电视机项目，开机暂不解多媒体的图片, 
这是单独解图接口，进入多媒体时调用，@qiny 2015.12.11*/
D_Result p_gui_atv_media_resource_init(void)
{
	int i, idx;
	D_U32 t1, t2;

	t1 = d_sys_get_time();

	gui_surf = d_gui_get_surface();

	for (i = _IMAGE_ID_MEDIA_START; i < _IMAGE_ID_SINGLE_MAX; i++)
	{
		idx = i - _IMAGE_ID_START;
		sys_images[idx].image[_LAN_ENG].buffer = atv_LoadImageData(i, _LAN_ENG, &(sys_images[idx].image[_LAN_ENG].size));
		sys_images[idx].image[_LAN_CHN].buffer = atv_LoadImageData(i, _LAN_CHN, &(sys_images[idx].image[_LAN_CHN].size));

        if(sys_images[idx].image[_LAN_ENG].img == NULL)
        {
    		sys_images[idx].image[_LAN_ENG].img = d_g_load_image (gui_surf, D_IMAGE_AUTO, 
    				(D_U8*)sys_images[idx].image[_LAN_ENG].buffer, sys_images[idx].image[_LAN_ENG].size);
	
    		if (sys_images[idx].image[_LAN_ENG].img == NULL)
    		{
    			D_DUMP("tv Eng Image load error:%d\n",i);
    			return D_ERR;
    		}   
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
	D_INFO("Gui load media %d Pictures cost %lu ms\n", (_IMAGE_ID_SINGLE_MAX - _IMAGE_ID_MEDIA_START), t2 - t1);

	return D_OK;
}

/* 2610电视机项目，开机暂不解多媒体的图片, 
这是单独释放图接口，退出多媒体时调用，@qiny 2015.12.11*/
D_Result p_gui_atv_media_resource_deinit(void)
{
	int i, idx;
	D_U32 t1, t2;

	t1 = d_sys_get_time();

	for (i = _IMAGE_ID_MEDIA_START; i < _IMAGE_ID_SINGLE_MAX; i++)
	{
		idx = i - _IMAGE_ID_START;
        
        /*中英文图片相同*/
        if(sys_images[idx].image[_LAN_CHN].img != sys_images[idx].image[_LAN_ENG].img)
        {
            if(sys_images[idx].image[_LAN_CHN].img)
            {
                d_image_free(sys_images[idx].image[_LAN_CHN].img);
            }
        }

        if(sys_images[idx].image[_LAN_ENG].img)
        {
            d_image_free(sys_images[idx].image[_LAN_ENG].img);
        }

		sys_images[idx].image[_LAN_ENG].buffer = NULL;
        sys_images[idx].image[_LAN_ENG].size = 0;
        sys_images[idx].image[_LAN_ENG].img = NULL;        
		sys_images[idx].image[_LAN_CHN].buffer = NULL;
        sys_images[idx].image[_LAN_CHN].size = 0;
        sys_images[idx].image[_LAN_CHN].img = NULL;
	}
	
	t2 = d_sys_get_time();
	D_INFO("Gui free media %d Pictures cost %lu ms\n", (_IMAGE_ID_SINGLE_MAX - _IMAGE_ID_MEDIA_START), t2 - t1);

	return D_OK;
}

/* 2610电视机项目，开机暂不解zhilian的图片,
这是单独解图接口，进入zhilian时调用，@qiny 2015.12.11*/
D_Result p_gui_atv_zhilian_resource_init(void)
{
#if 1
    int j, i, idx;
    D_U32 t1, t2;
    int img_id[] = {
        atv_IMG_ID_media_pause,  
            atv_IMG_ID_media_play, 
            atv_IMG_ID_pos,
	atv_IMG_ID_music_select_left, 
	atv_IMG_ID_music_select_middle, 
	atv_IMG_ID_music_select_right,
	atv_IMG_ID_music_select_focus_left, 
	atv_IMG_ID_music_select_focus_middle, 
	atv_IMG_ID_music_select_focus_right,
            };
    int img_cnt = sizeof(img_id)/sizeof(img_id[0]);
    
    t1 = d_sys_get_time();

    gui_surf = d_gui_get_surface();

    for (j = 0; j < img_cnt; j++)
    {
        i = img_id[j];
        idx = i - _IMAGE_ID_START;
        sys_images[idx].image[_LAN_ENG].buffer = atv_LoadImageData(i, _LAN_ENG, &(sys_images[idx].image[_LAN_ENG].size));
        sys_images[idx].image[_LAN_CHN].buffer = atv_LoadImageData(i, _LAN_CHN, &(sys_images[idx].image[_LAN_CHN].size));

        if(sys_images[idx].image[_LAN_ENG].img == NULL)
        {
            if(sys_images[idx].image[_LAN_ENG].buffer && sys_images[idx].image[_LAN_ENG].size)
            {
                sys_images[idx].image[_LAN_ENG].img = d_g_load_image (gui_surf, D_IMAGE_AUTO,
                                                      (D_U8*)sys_images[idx].image[_LAN_ENG].buffer, sys_images[idx].image[_LAN_ENG].size);

                if (sys_images[idx].image[_LAN_ENG].img == NULL)
                {
                    D_DUMP("tv Eng Image load error:%d\n", i);
                    return D_ERR;
                }
            }
        }
        /*中英文图片相同*/
        if(sys_images[idx].image[_LAN_ENG].buffer == sys_images[idx].image[_LAN_CHN].buffer)
        {
            sys_images[idx].image[_LAN_CHN].img = sys_images[idx].image[_LAN_ENG].img;
        }
        else
        {
            if(sys_images[idx].image[_LAN_CHN].buffer && sys_images[idx].image[_LAN_CHN].size)
            {
                sys_images[idx].image[_LAN_CHN].img = d_g_load_image (gui_surf, D_IMAGE_AUTO,
                                                      (D_U8*)sys_images[idx].image[_LAN_CHN].buffer, sys_images[idx].image[_LAN_CHN].size);

                if (sys_images[idx].image[_LAN_CHN].img == NULL)
                {
                    D_DUMP("tv Chn Image load error:%d\n", i);
                    return D_ERR;
                }
            }
        }
    }

    t2 = d_sys_get_time();
    D_INFO("Gui load zhilian %d Pictures cost %lu ms\n", img_cnt, t2 - t1);
#endif
    return D_OK;
}

/* 2610电视机项目，开机暂不解zhilian的图片,
这是单独释放图接口，退出zhilian时调用，@qiny 2015.12.11*/
D_Result p_gui_atv_zhilian_resource_deinit(void)
{
#if 1
    int j, i, idx;
    D_U32 t1, t2;
    int img_id[] = {
        atv_IMG_ID_media_pause,  
            atv_IMG_ID_media_play, 
            atv_IMG_ID_pos,
	atv_IMG_ID_music_select_left, 
	atv_IMG_ID_music_select_middle, 
	atv_IMG_ID_music_select_right,
	atv_IMG_ID_music_select_focus_left, 
	atv_IMG_ID_music_select_focus_middle, 
	atv_IMG_ID_music_select_focus_right,
            };
    int img_cnt = sizeof(img_id)/sizeof(img_id[0]);

    t1 = d_sys_get_time();

    for (j = 0; j < img_cnt; j++)
    {
        i = img_id[j];
        idx = i - _IMAGE_ID_START;

        /*中英文图片相同*/
        if(sys_images[idx].image[_LAN_CHN].img != sys_images[idx].image[_LAN_ENG].img)
        {
            if(sys_images[idx].image[_LAN_CHN].img)
            {
                d_image_free(sys_images[idx].image[_LAN_CHN].img);
            }
        }

        if(sys_images[idx].image[_LAN_ENG].img)
        {
            d_image_free(sys_images[idx].image[_LAN_ENG].img);
        }

        sys_images[idx].image[_LAN_ENG].buffer = NULL;
        sys_images[idx].image[_LAN_ENG].size = 0;
        sys_images[idx].image[_LAN_ENG].img = NULL;
        sys_images[idx].image[_LAN_CHN].buffer = NULL;
        sys_images[idx].image[_LAN_CHN].size = 0;
        sys_images[idx].image[_LAN_CHN].img = NULL;
    }

    t2 = d_sys_get_time();
    D_INFO("Gui free zhilian %d Pictures cost %lu ms\n", img_cnt, t2 - t1);
#endif
    return D_OK;
}



static D_GuiResourceOp atvResourceOp = 
{
	D_TRUE,
	4,
	0x4000,
	0x4fff,
	p_gui_atv_resource_init,/*如果资源想单独初始化，这里可以放空NULL*/
	p_gui_atv_lang_set,
	get_resource_text,
	get_resource_colour,
	get_resource_image,
};


D_Result p_gui_atv_resource_open(void)
{	
	d_gui_register_callback((D_Ptr)(&atvResourceOp), GUI_RESOURCE_OP);
	return D_OK;
}

