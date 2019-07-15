/** @file
* @brief Auxi
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#include "dResource.h"
#include "dApp.h"
#include "dNVPart.h"
#include "pNVPartApp.h"
#include "dDBase.h"
#include "dFMan.h"
#include "dVarString.h"
#include "pConfig.h"
#include "ptvConfig.h"
#include "pSdk.h"

static D_U32 aux_var_string_cnt;

D_Result p_auxi_init(void) D_FUNCPOSTFIT
{
    D_DBOpenParam dbase_open_param;

	d_app_open(D_TRUE, D_MAIN_QUEUE_SIZE);

    d_nvpart_set_tail_flag(P_NVPART_TAIL_FLAG);
	d_nvpart_open();
    app_nvpart_init();

   aux_var_string_cnt = 0x400040 / 36; // sizeof(D_VarString) = 36
    /* 保证至少占位4M内存, 这样在多媒体里, 可以分配到4M的大块内存 */
    aux_var_string_cnt = D_MAX(aux_var_string_cnt, P_DB_MAX_EVT_CNT * 3);
    
    dbase_open_param.table_valid_flag = \
        D_DBASE_NET_TAB_VALID | D_DBASE_TS_TAB_VALID | D_DBASE_SRV_TAB_VALID \
        | D_DBASE_EVT_TAB_VALID | D_DBASE_SUB_TAB_VALID;
    
#ifdef HI_SOFT_TYPE_DVBS
    dbase_open_param.table_valid_flag |= (D_DBASE_ANTE_TAB_VALID|D_DBASE_SATE_TAB_VALID);
#endif
    
    dbase_open_param.tab_info[D_DBASE_ANTE_TAB_ID].max_cnt = \
        dbase_open_param.tab_info[D_DBASE_ANTE_TAB_ID].store_cnt = P_DB_MAX_ANTE_CNT;
    dbase_open_param.tab_info[D_DBASE_ANTE_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_ANTE_TAB_ID].reserved_field_size = 0;
    
    dbase_open_param.tab_info[D_DBASE_SATE_TAB_ID].max_cnt = \
        dbase_open_param.tab_info[D_DBASE_SATE_TAB_ID].store_cnt = P_DB_MAX_SAT_CNT;
    dbase_open_param.tab_info[D_DBASE_SATE_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_SATE_TAB_ID].reserved_field_size = 0;
    
    dbase_open_param.tab_info[D_DBASE_NET_TAB_ID].max_cnt = \
        dbase_open_param.tab_info[D_DBASE_NET_TAB_ID].store_cnt = P_DB_MAX_NET_CNT;
    dbase_open_param.tab_info[D_DBASE_NET_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_NET_TAB_ID].reserved_field_size = 0;
    
    dbase_open_param.tab_info[D_DBASE_TS_TAB_ID].max_cnt = P_DB_MAX_TS_CNT;
    dbase_open_param.tab_info[D_DBASE_TS_TAB_ID].store_cnt = P_DB_MAX_TS_CNT - P_DB_TEMP_TS_CNT;
    dbase_open_param.tab_info[D_DBASE_TS_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_TS_TAB_ID].reserved_field_size = 8;
    
    dbase_open_param.tab_info[D_DBASE_SRV_TAB_ID].max_cnt = P_DB_MAX_SRV_CNT;
    dbase_open_param.tab_info[D_DBASE_SRV_TAB_ID].store_cnt = P_DB_MAX_SRV_CNT - P_DB_TEMP_SRV_CNT;
    dbase_open_param.tab_info[D_DBASE_SRV_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_SRV_TAB_ID].reserved_field_size = 8;
    
    dbase_open_param.tab_info[D_DBASE_SUB_TAB_ID].max_cnt = \
        dbase_open_param.tab_info[D_DBASE_SUB_TAB_ID].store_cnt = P_DB_MAX_SUB_CNT;
    dbase_open_param.tab_info[D_DBASE_SUB_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_SUB_TAB_ID].reserved_field_size = 0;
    
    dbase_open_param.tab_info[D_DBASE_EVT_TAB_ID].max_cnt = P_DB_MAX_EVT_CNT;
    dbase_open_param.tab_info[D_DBASE_EVT_TAB_ID].store_cnt = 0;
    dbase_open_param.tab_info[D_DBASE_EVT_TAB_ID].part_id = -1;
    dbase_open_param.tab_info[D_DBASE_EVT_TAB_ID].reserved_field_size = 0;
    
    dbase_open_param.tab_info[D_DBASE_BOUQ_TAB_ID].max_cnt = \
        dbase_open_param.tab_info[D_DBASE_BOUQ_TAB_ID].store_cnt = P_DB_MAX_BOUQ_CNT;
    dbase_open_param.tab_info[D_DBASE_BOUQ_TAB_ID].part_id = D_NV_PART_PARAM;
    dbase_open_param.tab_info[D_DBASE_BOUQ_TAB_ID].reserved_field_size = 0;

#if HI_P_MUTIMEDIA_EN
    dbase_open_param.var_string_cnt = aux_var_string_cnt;
#else
    aux_var_string_cnt = P_DB_MAX_EVT_CNT * 3;
    dbase_open_param.var_string_cnt = aux_var_string_cnt;
#endif
    dbase_open_param.config_blk_size = P_CONFIG_BLOCK_SIZE;
    dbase_open_param.data_blk_size = 0;
    
	d_dbase_open(&dbase_open_param);

    d_fman_open();
	p_conf_init();
    p_tvconf_init();
#if defined(D_DDR_SIZE_64M) || defined(D_TV_LIULINK_SOURCE)
	{
		D_VideoMemParam video_mem;
		
		video_mem.pic_en = 1;
		video_mem.pic_size = (8160*384*7);
		video_mem.pic_size_media = (8160*384*7);
		video_mem.work_en = 1;
		video_mem.work_size = (0x24800 + ((8160*84+1023)/1024)*1024*7);
		video_mem.work_size_media = (0x24800 + ((8160*84+1023)/1024)*1024*7);
		video_mem.switch_en = 1;
		video_mem.switch_size = 0;
		video_mem.pa_od_en = 1;
		video_mem.pa_od_size = 0;

		d_av_mem_set(&video_mem);
		d_av_unref_frames(0);	
		d_av_set_switch_mode(D_Black_Screen);
	}

               {
        		D_VideoMemParam video_mem;
		

		video_mem.switch_en = 1;
		video_mem.switch_size = 0;
		video_mem.pa_od_en = 1;
		video_mem.pa_od_size = 0;

		d_av_mem_set(&video_mem);
	
		d_av_set_switch_mode(D_Black_Screen);
		}
#endif
	d_av_unref_frames(0);	//使用精简方案
	p_tven_lvds_init();	
	return D_OK;
}

D_Result p_auxi_free_varstring(void) D_FUNCPOSTFIT
{
    d_dbase_clear_evt();
    d_var_string_close();
    return D_OK;
}


D_Result p_auxi_reopen_varstring(void) D_FUNCPOSTFIT
{
    d_var_string_open(aux_var_string_cnt);
    return D_OK;
}
