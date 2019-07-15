/** @file
* @brief 窗口模块
* @author覃宜
* @date 2013-7-1 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "pStbAtvMenus.h"
#include "dSem.h"
#include "prog_scan_menu_window.c"




static D_Ptr AutoScan_Op = (D_Ptr)(&DVBS_AutoScan_Op);
static D_Ptr ManualScan_Op = (D_Ptr)(&DVBS_ManualScan_Op);



#define MSG_BUFFER_LEN		(256)
#define SRV_NAME_MAX_LEN	(36)
#define LABEL_BUFF_SIZE		(16)
#define D_SHOW_PROG_CNT 	(5)
#define SAT_NAME_MAX_LEN	(36)
#define D_SHOW_FREQ_CNT 	(5)


/* @brief 菜单内部数据*/
typedef struct 
{
    D_StbPlayer	*player; 
	D_U32   		menu_type;
	D_HScan		hscan;								/**< 搜索句柄*/	
    D_HFMan hfman;
    D_FDiSEqCType diseqc_type;
    
	D_U16		prog_num_tv;
	D_U8 		prog_ca_tv[D_SHOW_PROG_CNT];
	D_Char		prog_name_tv[D_SHOW_PROG_CNT][SRV_NAME_MAX_LEN];	/**< 存储节目名*/
	
	D_U16		prog_num_radio;
	D_U8 		prog_ca_radio[D_SHOW_PROG_CNT];
	D_Char		prog_name_radio[D_SHOW_PROG_CNT][SRV_NAME_MAX_LEN];	/**< 存储节目名*/

	D_U16		tp_cnt;
	D_Char 		freq_num[D_SHOW_FREQ_CNT][8]; /**< 序号*/
	D_Char		satellite_name[D_SHOW_FREQ_CNT][SAT_NAME_MAX_LEN];	/**<卫星名*/    
	D_Char 		freq_label[D_SHOW_FREQ_CNT][LABEL_BUFF_SIZE]; /**< 频率*/
	D_Char 		baud_label[D_SHOW_FREQ_CNT][LABEL_BUFF_SIZE]; /**< 符号率*/
	D_FEndPol      polarize[D_SHOW_FREQ_CNT]; /**< 极化方式水平垂直*/
	D_U32          ret_flag[D_SHOW_FREQ_CNT]; /**< 搜索结果*/      
    
	D_Char		progress_lab[LABEL_BUFF_SIZE];		/**< 进度值显示*/	
    
       D_Char		tv_lab[LABEL_BUFF_SIZE];		/**< 电视节目数显示*/
       D_Char		radio_lab[LABEL_BUFF_SIZE];	/**< 广播节目数显示*/
       
	D_Bool		scanning_flag;
	D_Bool		save_flag;
	D_Bool		got_srv_flag;
	D_Char		msg[MSG_BUFFER_LEN];				/**< 显示信息存储区*/	
} D_ScanMenuData;


/** @brief 菜单内部数据指针*/
static D_ScanMenuData	*prog_data = NULL;
static P_ScanConfig PScanConfig = {0};
static D_Bool power_scan = D_FALSE;
static D_ID  title_text_id;

static D_Char *HVstring[] = {"H", "V", NULL};
static D_Char *Resultstring[] = {"...failed", "...ok", "..."};
static D_Char *CaFlagstring[] = {"", "$", NULL};

/** @brief 设置搜索进度*/
static D_Result show_title_text (void) D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;
    D_ID  text_id;
  
    if(PScanConfig.type == STB_SCAN_TYPE_TP)
    {
        text_id = atv_IDS_TP_SCAN;
    }
    else if(PScanConfig.mode == STB_SCAN_MODE_BLIND)
    {
        text_id = atv_IDS_SATE_SCAN;
    }
    
    /*设定进度条*/
    vis = d_frame_get_control (frm, ID_SCAN_LABEL_TITLE);
    if (vis) 
    {
        d_label_set_text (vis, d_gui_get_text(text_id));
    }
	
    return D_OK;
}

/** @brief 设置搜索进度*/
static D_Result set_scan_progress (D_U16 prog) D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;

    /*设定进度条*/
    vis = d_frame_get_control (frm, ID_SCAN_PROGRESS);
    if (vis) 
    {
        d_progress_bar_set_val (vis, prog);
    }

    vis = d_frame_get_control (frm, ID_SCAN_LABEL_PROGRESS);
    if (vis) 
    {
        sprintf(prog_data->progress_lab, "%d%%", prog);       
        d_label_set_text(vis, prog_data->progress_lab);
    }		
	return D_OK;
}


/** @brief 增加节目显示*/
static D_Result add_prog_name(D_Char *pname, D_U32 type, D_U8 ca_flag) D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;
    D_Int	idx;
    D_Char name[SRV_NAME_MAX_LEN] = "no name";

    if ((! name) || (type != D_DB_SRV_TV && type != D_DB_SRV_RADIO) || prog_data->hscan == D_INVALID_HANDLE)
        return D_OK;

    if(pname[0] != '\0')
    {
        memcpy(name, pname, SRV_NAME_MAX_LEN);
    }
    
    prog_data->got_srv_flag = D_TRUE;
    
    if(type == D_DB_SRV_TV)
    {    
        vis = d_frame_get_control (frm, ID_SCAN_LIST_TV);
        if (vis)
        {
            /*存储节目名*/
            if (prog_data->prog_num_tv < D_SHOW_PROG_CNT) 
            {			
                memcpy(prog_data->prog_name_tv[prog_data->prog_num_tv], name, SRV_NAME_MAX_LEN);
                prog_data->prog_ca_tv[prog_data->prog_num_tv] = D_MIN(ca_flag, 1);
                /*刷新显示*/
                
                d_list_set_text (vis, prog_data->prog_num_tv, 0, (ca_flag)? CaFlagstring[1] : CaFlagstring[0]);
                d_list_set_text (vis, prog_data->prog_num_tv, 1, prog_data->prog_name_tv[prog_data->prog_num_tv]);
                prog_data->prog_num_tv++;
            }
            else 
            {	
                memmove (prog_data->prog_ca_tv, prog_data->prog_ca_tv + 1, (D_SHOW_PROG_CNT - 1));
                memmove (prog_data->prog_name_tv, prog_data->prog_name_tv+1, (D_SHOW_PROG_CNT - 1) * SRV_NAME_MAX_LEN);
                memcpy(prog_data->prog_name_tv[D_SHOW_PROG_CNT-1], name, SRV_NAME_MAX_LEN);
                prog_data->prog_ca_tv[D_SHOW_PROG_CNT-1] = D_MIN(ca_flag, 1);
                
                /*刷新显示*/
                for (idx = 0; idx < D_SHOW_PROG_CNT; idx++) 
                {
                    d_list_set_text (vis, idx, 0, (prog_data->prog_ca_tv[idx])? CaFlagstring[1] : CaFlagstring[0]);
                    d_list_set_text (vis, idx, 1, prog_data->prog_name_tv[idx]);
                }
                prog_data->prog_num_tv++;
            }
        }
        
        vis = d_frame_get_control (frm, ID_SCAN_LABEL_TV_NUM);
        if (vis)
        {        
            sprintf(prog_data->tv_lab, "%d", prog_data->prog_num_tv);
            d_label_set_text(vis, prog_data->tv_lab);
        }
    }

    if(type == D_DB_SRV_RADIO)
    {
        vis = d_frame_get_control (frm, ID_SCAN_LIST_RADIO);
        if (vis)
        {
        /*存储节目名*/
            if (prog_data->prog_num_radio < D_SHOW_PROG_CNT) 
            {			
                memcpy(prog_data->prog_name_radio[prog_data->prog_num_radio], name, SRV_NAME_MAX_LEN);
                prog_data->prog_ca_radio[prog_data->prog_num_radio] = D_MIN(ca_flag, 1);
                /*刷新显示*/
                d_list_set_text (vis, prog_data->prog_num_radio, 0, (ca_flag)? CaFlagstring[1] : CaFlagstring[0]);
                d_list_set_text (vis, prog_data->prog_num_radio, 1, prog_data->prog_name_radio[prog_data->prog_num_radio]);
                prog_data->prog_num_radio++;
            }
            else 
            {	
                memmove (prog_data->prog_ca_radio, prog_data->prog_ca_radio + 1, (D_SHOW_PROG_CNT - 1));
                memmove (prog_data->prog_name_radio, prog_data->prog_name_radio+1, (D_SHOW_PROG_CNT - 1) * SRV_NAME_MAX_LEN);
                memcpy(prog_data->prog_name_radio[D_SHOW_PROG_CNT-1], name, SRV_NAME_MAX_LEN);
                prog_data->prog_ca_radio[D_SHOW_PROG_CNT-1] = D_MIN(ca_flag, 1);

                /*刷新显示*/
                for (idx = 0; idx < D_SHOW_PROG_CNT; idx++) 
                {
                    d_list_set_text (vis, idx, 0, (prog_data->prog_ca_radio[idx])? CaFlagstring[1] : CaFlagstring[0]);
                    d_list_set_text (vis, idx, 1, prog_data->prog_name_radio[idx]);
                }
                prog_data->prog_num_radio++;
            }
        }
        
        vis = d_frame_get_control (frm, ID_SCAN_LABEL_RADIO_NUM);
        if (vis)
        {        
            sprintf(prog_data->radio_lab, "%d", prog_data->prog_num_radio);
            d_label_set_text(vis, prog_data->radio_lab);
        }        
    }
    return D_OK;
}

/** @brief 增加转发器条目*/
static D_Result add_tp_info(D_ScanEvent *scan_evt) D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;
    D_Int	idx;
    D_DBTSInfo tsinfo = {0};
    D_DBSateInfo    satinfo = {0};

    if((!scan_evt) || prog_data->hscan == D_INVALID_HANDLE)
    {
        return D_ERR;
    }
    
    if(scan_evt->ptr)
    {
        memcpy(&satinfo, scan_evt->ptr, sizeof(D_DBSateInfo));
        
        vis = d_frame_get_control (frm, ID_SCAN_LIST_RESULT);
        if (vis)
        {
            /*存储节目名*/
            if (prog_data->tp_cnt < D_SHOW_FREQ_CNT) 
            {			
                memcpy(prog_data->satellite_name[prog_data->tp_cnt], satinfo.sate_name, SAT_NAME_MAX_LEN);
                prog_data->ret_flag[prog_data->tp_cnt] = 2;
                prog_data->polarize[prog_data->tp_cnt] = scan_evt->fendparam.dvbs.pol;
                sprintf(prog_data->freq_label[prog_data->tp_cnt], "%d", scan_evt->fendparam.freq);                
                sprintf(prog_data->baud_label[prog_data->tp_cnt], "%d", scan_evt->fendparam.dvbs.baud);                
                sprintf(prog_data->freq_num[prog_data->tp_cnt], "%d", prog_data->tp_cnt + 1);

                /*刷新显示*/
                d_list_set_text (vis, prog_data->tp_cnt, 0, prog_data->freq_num[prog_data->tp_cnt]);
                d_list_set_text (vis, prog_data->tp_cnt, 1, prog_data->satellite_name[prog_data->tp_cnt]);
                d_list_set_text (vis, prog_data->tp_cnt, 2, prog_data->freq_label[prog_data->tp_cnt]);
                d_list_set_text (vis, prog_data->tp_cnt, 3, ((prog_data->polarize[prog_data->tp_cnt] == D_FEND_HOR_POL) ? HVstring[0] : HVstring[1])); 
                d_list_set_text (vis, prog_data->tp_cnt, 4, prog_data->baud_label[prog_data->tp_cnt]);
                d_list_set_text (vis, prog_data->tp_cnt, 5, Resultstring[prog_data->ret_flag[prog_data->tp_cnt]]);
            }
            else 
            {	
                memmove (prog_data->satellite_name, prog_data->satellite_name+1, (D_SHOW_FREQ_CNT - 1) * SAT_NAME_MAX_LEN);
                memmove (prog_data->freq_label, prog_data->freq_label+1, (D_SHOW_FREQ_CNT - 1) * LABEL_BUFF_SIZE);                
                memmove (prog_data->baud_label, prog_data->baud_label+1, (D_SHOW_FREQ_CNT - 1) * LABEL_BUFF_SIZE);
                memmove (prog_data->polarize, prog_data->polarize+1, (D_SHOW_FREQ_CNT - 1) * sizeof(D_FEndPol));
                memmove (prog_data->ret_flag, prog_data->ret_flag+1, (D_SHOW_FREQ_CNT - 1) * sizeof(D_U32));

                memcpy(prog_data->satellite_name[D_SHOW_FREQ_CNT-1], satinfo.sate_name, SAT_NAME_MAX_LEN);
                prog_data->ret_flag[D_SHOW_FREQ_CNT-1] = 2;
                prog_data->polarize[D_SHOW_FREQ_CNT-1] = scan_evt->fendparam.dvbs.pol;
                sprintf(prog_data->freq_label[D_SHOW_FREQ_CNT-1], "%d", scan_evt->fendparam.freq);        
                sprintf(prog_data->baud_label[D_SHOW_FREQ_CNT-1], "%d", scan_evt->fendparam.dvbs.baud);
                
                /*刷新显示*/
                for (idx = 0; idx < D_SHOW_FREQ_CNT; idx++) 
                {
                    sprintf(prog_data->freq_num[idx], "%d", (prog_data->tp_cnt - D_SHOW_FREQ_CNT + 2 + idx));                    
                    d_list_set_text (vis, idx, 0, prog_data->freq_num[idx]);
                    d_list_set_text (vis, idx, 1, prog_data->satellite_name[idx]);
                    d_list_set_text (vis, idx, 2, prog_data->freq_label[idx]);
                    d_list_set_text (vis, idx, 3, ((prog_data->polarize[idx] == D_FEND_HOR_POL) ? HVstring[0] : HVstring[1])); 
                    d_list_set_text (vis, idx, 4, prog_data->baud_label[idx]);
                    d_list_set_text (vis, idx, 5, Resultstring[prog_data->ret_flag[idx]]);                   
                }
            }
        }
    }

    return D_OK;
}

/** @brief 增加转发器条目*/
static D_Result add_tp_scan_result(D_ScanEvent *scan_evt, D_Bool scanning) D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;
    D_Int	idx;
    D_DBTSInfo tsinfo = {0};
    D_DBSateInfo    satinfo = {0};

    if((!scan_evt) || prog_data->hscan == D_INVALID_HANDLE)
    {
        return D_ERR;
    }
            
    vis = d_frame_get_control (frm, ID_SCAN_LIST_RESULT);
    if (vis)
    {
        if(scanning)
        {
            /*存储节目名*/
            if (prog_data->tp_cnt < D_SHOW_FREQ_CNT) 
            {			
                prog_data->ret_flag[prog_data->tp_cnt] = (scan_evt->param) ? 1 : 0;
                /*预制频点搜索时，当前频点搜索结束与下一个频点搜索开始之间时间较短，如果这里直接显示当前频点的搜索结果，
                在视觉上会感觉界面文字闪一下，因此当前频点结果暂不显示，下一频点搜索开始时才显示。@qiny 2013-12-20*/
                if (PScanConfig.mode != STB_SCAN_MODE_PRESET || prog_data->tp_cnt < (D_SHOW_FREQ_CNT - 1))
                {
                    d_list_set_text (vis, (prog_data->tp_cnt), 5, Resultstring[prog_data->ret_flag[prog_data->tp_cnt]]);
                }
                prog_data->tp_cnt++;
            }
            else 
            {	
                prog_data->ret_flag[D_SHOW_FREQ_CNT - 1] = (scan_evt->param) ? 1 : 0;
                /*预制频点搜索时，当前频点搜索结束与下一个频点搜索开始之间时间较短，如果这里直接显示当前频点的搜索结果，
                在视觉上会感觉界面文字闪一下，因此当前频点结果暂不显示，下一频点搜索开始时才显示。@qiny 2013-12-20*/
                if (PScanConfig.mode != STB_SCAN_MODE_PRESET)
                {
                    d_list_set_text (vis, (D_SHOW_FREQ_CNT - 1), 5, Resultstring[prog_data->ret_flag[D_SHOW_FREQ_CNT - 1]]);
                }
                prog_data->tp_cnt++;
            }
        }
        else
        {
            /*显示最后一个频点的搜索结果。@qiny 2013-12-20*/
            if (PScanConfig.mode == STB_SCAN_MODE_PRESET && prog_data->tp_cnt >= D_SHOW_FREQ_CNT) 
            {
                d_list_set_text (vis, (D_SHOW_FREQ_CNT - 1), 5, Resultstring[prog_data->ret_flag[D_SHOW_FREQ_CNT - 1]]);
            }
        }
    }

    return D_OK;
}


/*开始节目自动搜索*/
static D_Result
start_prog_scan(D_U32 param)D_FUNCPOSTFIT
{
    D_Frame		*frm = &scan_menu_window;
    D_Visual	*vis;
    D_ScanTaskConfig config = {0};
    D_ID ante_dbid;
    
    D_DUMP("start_prog_scan()\n");

    vis = d_frame_get_control (frm, 0);
    
    prog_data->scanning_flag = D_FALSE;
    prog_data->prog_num_tv = 0;
    prog_data->prog_num_radio = 0;
    prog_data->tp_cnt = 0;
    prog_data->save_flag = D_FALSE;
    prog_data->got_srv_flag = D_FALSE;

    config.pReserved = (D_Ptr)(&PScanConfig);
    config.sdt_srv_type_en = D_FALSE;
    
    if(prog_data->menu_type == STB_SCAN_TYPE_TP)
    {
        config.buf_size = 96 * 1024;
        config.hqueue = d_gui_get_queue();
        config.priority = D_MANUAL_SCAN_TASK_PRIO;
        config.scan_type = prog_data->menu_type;
        config.fend_type = PScanConfig.fendtype;
        config.fend_param = PScanConfig.fendparam;
        config.srv_name_en = D_TRUE;
        config.hfman = d_fman_get_handle_by_type(config.fend_type, 0);
        config.pScanOp = ManualScan_Op;
        config.db_sat_id = PScanConfig.satelliteNo;
        if(D_OK != d_dbase_get_sat_info(PScanConfig.satelliteNo, &(config.SateInfo)))
        {
            D_ERROR("Error : get sateinfo error.  %s:%d \n", __FUNCTION__, __LINE__);
            return D_ERR;
        }
        
        //if(prog_data->diseqc_type != D_DISEQC_TYPE_10)
        //{
            //ante_dbid = (D_DBAnteID)p_conf_get_db_ante_id();
        //}
        //else
        {
            ante_dbid = config.SateInfo.antenna_slot;
        }
        
        if(D_OK != d_dbase_get_ante_info(ante_dbid, &(config.AnteInfo)))
        {
            D_ERROR("Error : get anteinfo error.  %s:%d \n", __FUNCTION__, __LINE__);
            return D_ERR;
        }  

        prog_data->hscan = d_manual_scan_create(config);	
        if (prog_data->hscan != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_SCAN_MASK, prog_data->hscan);
            /*处理用户事件*/
		    d_vis_subscribe_evt (vis, D_EVT_USER_MASK, prog_data->hscan);
            prog_data->scanning_flag = D_TRUE;
        }		
    }
    else
    {
        config.buf_size = 384 * 1024;
        config.hqueue = d_gui_get_queue();
        config.parse_mode = D_SCAN_PARSE_TP;
        config.priority = D_AUTO_SCAN_TASK_PRIO;
        config.scan_type = prog_data->menu_type;
        config.fend_type = PScanConfig.fendtype;        
        config.srv_name_en = D_TRUE;
        config.group_end_save = D_TRUE;
        config.hfman = d_fman_get_handle_by_type(config.fend_type, 0);
        config.pScanOp = AutoScan_Op;

        prog_data->hscan = d_auto_scan_create(config);	
        if (prog_data->hscan != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_SCAN_MASK, prog_data->hscan);
            /*处理用户事件*/
		    d_vis_subscribe_evt (vis, D_EVT_USER_MASK, prog_data->hscan);
            prog_data->scanning_flag = D_TRUE;
        }
    }
    
    return D_OK;
}

/*搜素默认播放第一个电视节目*/
static D_Result
update_play_prog(void)D_FUNCPOSTFIT
{	
	D_DUMP("pScanwin update prog num!\n");
	return D_OK;
}

/** @brief 结束搜索过程*/
static D_Result scan_prog_end (D_U32 save)
{	
    D_Bool save_flag;
    
	prog_data->scanning_flag = D_FALSE;
	save_flag = save ? D_TRUE : D_FALSE;

	/*保存搜索的节目*/
	if (prog_data->hscan != D_INVALID_HANDLE) 
	{	
		if(prog_data->menu_type == STB_SCAN_TYPE_TP)
		{	
			d_manual_scan_destroy (prog_data->hscan, save_flag);
		}
		else
		{
			d_auto_scan_destroy (prog_data->hscan, save_flag);
		}
		
		prog_data->hscan = D_INVALID_HANDLE;
	}

	if(save_flag && prog_data->got_srv_flag)
	{
		/*搜索结束后默认播放第一个电视节目*/
		update_play_prog();
	}

	return D_OK;
}

static D_Result 
scan_end_handler(D_Bool sel,  D_U32 param)
{
    /*确认或退出都保存已经搜索到的节目*/
    if(prog_data->save_flag/* && sel*/)
    {
        d_pop_msg_show (D_POP_MSG_PRIO_MSG_2, 
            D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
            NULL, "saving..."/*d_gui_get_text(IDS_SAVE_DATA)*/,
            0, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, NULL, 0);
       d_gui_update();
       scan_prog_end((D_U32)D_TRUE);
       d_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
    }
    else
    {
	    scan_prog_end((D_U32)D_FALSE);	
    }
	d_gui_clear_menu();
	return D_OK;
}


/** @brief 显示搜索结果*/
static D_Result show_scan_result (D_Visual *vis, D_U16 prog_cnt, D_U16 tv_cnt, D_U16 radio_cnt)
{
    D_MSec timeout = 0;
    D_Result ret = D_ERR;

    D_DUMP("scan_result : tv %d, radio %d\n", tv_cnt, radio_cnt);	

    if (prog_data->hscan != D_INVALID_HANDLE) 
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_SCAN_MASK, prog_data->hscan);
    }

    /*显示搜索结束信息*/
    if((tv_cnt + radio_cnt) == 0)
    {
        prog_data->got_srv_flag = D_FALSE;
        if(PScanConfig.type != STB_SCAN_TYPE_TP && PScanConfig.mode == STB_SCAN_MODE_BLIND && prog_data->tp_cnt)
        {
            prog_data->save_flag = D_TRUE;
        }
        else
        {
            prog_data->save_flag = D_FALSE;
        }
        sprintf(prog_data->msg, "%s", d_gui_get_text(atv_IDS_NO_PROGRAM));              
    }
    else
    {	
        prog_data->got_srv_flag = D_TRUE;
        prog_data->save_flag = D_TRUE;
        sprintf(prog_data->msg, "%s  %d\n%s  %d", d_gui_get_text(atv_IDS_DIGI_RADIO), tv_cnt, d_gui_get_text(atv_IDS_DIGI_TV), radio_cnt);
    }

    ret = d_pop_select_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, "info", prog_data->msg, timeout, D_TRUE, scan_end_handler, 0);

    /*因界面上可能还有别的显示而使提示框显示失败，
    这时要退出搜索，以免死机。*/
    if(ret != D_OK)
    {
        scan_prog_end((prog_data->save_flag || prog_data->got_srv_flag) ? ((D_U32)D_TRUE) : (D_U32)D_FALSE);
    }		
    return D_OK;
}

/** @brief 中止搜索过程*/
static D_Result esc_prog_scan (D_U32 save)
{
    /*搜索到节目则保存*/
    if(prog_data->got_srv_flag ||
    (PScanConfig.type != STB_SCAN_TYPE_TP && PScanConfig.mode == STB_SCAN_MODE_BLIND && prog_data->tp_cnt))
	{
        d_pop_msg_show (D_POP_MSG_PRIO_MSG_2, 
            D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
            NULL, "Saving..."/*d_gui_get_text(IDS_SAVE_DATA)*/,
            0, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, NULL, 0);
       d_gui_update();
       scan_prog_end((D_U32)D_TRUE);
       d_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
    }
    else
    {
	    scan_prog_end((D_U32)D_FALSE);	
    }

	return D_OK;
}

static D_Result
move_diseqc_handler(D_U32 param)D_FUNCPOSTFIT
{
    D_HSem hsem;

    hsem = (D_HSem )param;
    if(hsem != D_INVALID_HANDLE)
    {
        d_sem_post(hsem);
    }
    return D_OK;
}

/*移动diseqc*/
static D_Result
show_move_diseqc(D_U32 param)
{
#if 0
    D_Rect del_rect = {240,204,240,68};  
  
    d_pop_msg_show_rect (D_POP_MSG_PRIO_MSG_2, 
        D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
        NULL, d_gui_get_text(IDS_MOVING_DISEQC),
        15000, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, move_diseqc_handler, param, &del_rect);
#endif
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
scan_menu_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
    switch (evt->type) 
    {					
        case D_EVT_FP:
            switch (evt->fp.key) 
            {
                case D_KEY_ESC:
                case D_KEY_BACK:                    
                    if(prog_data->scanning_flag == D_TRUE && prog_data->menu_type != STB_SCAN_TYPE_TP)
                    {
                        esc_prog_scan((D_U32)D_TRUE);
                    }
                    d_gui_upper_menu();
                    break;				
						
                default:
                    break;
            }

            return D_OK;
            break;
        case D_EVT_USER1:
            return show_move_diseqc(evt->user.param1);
            break;
        /*更新搜索进度*/
        case D_EVT_SCAN_PROGRESS:  
            return set_scan_progress (evt->scan.progress);
        /*搜索完毕*/
        case D_EVT_SCAN_OK:	
            add_tp_scan_result (evt, D_FALSE);/*显示最后一个频点的搜索结果 ok/faild*/
            return show_scan_result(vis, evt->scan.prog_cnt, evt->scan.tv_cnt, evt->scan.radio_cnt);
            break;
        case D_EVT_SCAN_DATA:
            return add_prog_name ((D_Char*)evt->scan.srvinfo.name, evt->scan.srvinfo.srv_type, evt->scan.srvinfo.ca_flag);
        case D_EVT_SCAN_FREQ:
            return add_tp_info (evt);
            break;
        case D_EVT_SCAN_FREQ_END:
            return add_tp_scan_result (evt, D_TRUE);
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            d_fp_set_led (0, "0000");
            if(prog_data)
            {
                scan_prog_end(0);
                
                /*恢复fman空闲时频点监控*/
                d_fman_set_monitor_mode(prog_data->hfman, D_TRUE);
                /*恢复表监控*/
                d_tv_scan_si(prog_data->player->htv, D_TV_SCAN_ALL);            
                PROJECT_FREE(prog_data);
                prog_data = NULL;
            }
            power_scan = D_FALSE;
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
scan_menu_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual		*vis;

    prog_data = (D_ScanMenuData*)PROJECT_ALLOC(sizeof(D_ScanMenuData));
    if(!prog_data)
    {
        return D_ERR;
    }

    memset(prog_data, 0x00, sizeof(D_ScanMenuData));
    prog_data->hscan = D_INVALID_HANDLE;
    prog_data->menu_type = (D_U32)(PScanConfig.type);
    prog_data->diseqc_type = D_DISEQC_TYPE_10;
    prog_data->hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0); 
    prog_data->player = p_stb_get_player (0);
    if (! (prog_data->player))
    {
        PROJECT_FREE(prog_data);
        prog_data = NULL;	
        return D_ERR;
    }
#if 0
    if(p_conf_get_lnb())
    {
        if(p_conf_get_motortype())
        {
            prog_data->diseqc_type = D_DISEQC_TYPE_USALS;
        }
        else
        {
            prog_data->diseqc_type = D_DISEQC_TYPE_12;
        }
    }
#endif
    /*因为有信号的锁定，要停播*/
    d_stb_stop_play();
    /*清除残留视频帧*/
    p_stb_player_clear_vid(0);

    /*停止表监控*/
    d_tv_scan_si(prog_data->player->htv, 0);

    /*停止fman空闲时频点监控*/
    d_fman_set_monitor_mode(prog_data->hfman, D_FALSE);
    
    show_title_text();
    set_scan_progress(0);

    vis = d_frame_get_control (frm, 0);
    if (vis) 
    {		
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK ,D_INVALID_HANDLE);		
        d_vis_set_handler (vis, scan_menu_window_handler);
        start_prog_scan(0);
    }
    d_fp_set_led (0, "scan");
    return D_OK;
}

/** @breif 显示DVBS搜索界面*/
D_Result
p_atv_dvbs_scan_window_show (P_ScanConfig *pScanConf) D_FUNCPOSTFIT
{
	if(pScanConf && pScanConf->valid)
	{
		if(pScanConf)
		{
			PScanConfig = *pScanConf;
		}

		return d_gui_enter_menu (&scan_menu_window, D_CLEAR_ALL);
	}
	
	return D_ERR;
}

