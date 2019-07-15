 /**@file pbat.c
*@brief bat �������洢bat�������Ϣ
*��ϸ����
*@author wansb
*@copyright Haier-IC
*@date 2014-04-01  
*/

#include <stdio.h>
#include <string.h>

#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pMonitorRegister.h"
#include "dMsg.h"
#include "pBat.h"
#include "pConfig.h"
#include "dCBMan.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"

#include "dTypes.h"
#include "dDBaseInternal.h"
#include "pDBaseDefault.h"
#include "dadporting.h"


#define P_BAT_PARSE_DUMP(_x_)  D_DUMP _x_   ///<���Դ�ӡ��Ϣ
#define P_BAT_PARSE_DERR(_x_)  D_ERROR _x_  ///<�����ӡ��Ϣ

static D_MonitorHandle g_bat_monitor_handle = -1;
static D_BatScan *Batps = NULL;


/** @brief	����bat��
* @param[in] TVData *tv    ��������
* @param[in] D_U8 *buf	   bat ����ָ��
* @param[in] D_Size size   ��ʱû�õ�
* @retval D_OK	�ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result
get_bat_data(TVData *tv, D_U8 *buf, D_Size length)D_FUNCPOSTFIT
{
	D_Size	 cnt;
	D_List	*bats;
	D_SectionInfo sec;
	D_Bat	   *bat;
	D_Descr *descr;

	if (length > 0)
	{
		if (d_si_parse_section (buf, length, &sec) < 0)
		{
			P_BAT_PARSE_DERR (("[pBat.c] BAT section error\n"));
			return D_ERR;
		}		
		if (Batps->version != sec.version)
		{
			Batps->version = sec.version;
			d_tab_mask_clear (Batps->bat_mask);
		}
		if (d_tab_mask_is_set (Batps->bat_mask, sec.ext_tab_id, sec.version, sec.sec_num)) {
			P_BAT_PARSE_DUMP (("BAT section duplicated\n"));
			return D_OK;
		} 		
		d_tab_mask_add (Batps->bat_mask, 0, sec.version, sec.sec_num, sec.last_sec_num);
		bats = d_si_parse_bat (buf, length, tv->ps->hsi_mm);
		if (bats) 
		{
			D_SI_FOR_EACH_BEGIN (D_Bat, bats, bat)
				D_SI_FOR_EACH_BEGIN (D_Descr, bat->descrs, descr)
				if (descr->tag == P_DESCR_MGAD_TAG) 
				{
					D_MGADDescr*mgaddescr = (D_MGADDescr*)descr;
					d_ad_SetDescr(mgaddescr,AD_STB_MG);		 
				}
			D_SI_FOR_EACH_END (D_Descr, bat->descrs, descr)  
				D_SI_FOR_EACH_END (D_Bat,bats, bat)

				D_SI_LIST_ADD (Batps->Bat, bats);//�����������֪������?
			if (d_tab_mask_full (Batps->bat_mask)) 
			{
				bat_monitor_stop();			 
			}	 
			 /*����ڴ������*/
			d_mman_clear (tv->ps->hsi_mm);
			return D_OK;
		}
		/*����ڴ������*/
		d_mman_clear (tv->ps->hsi_mm);		

	}	
	return D_ERR;
}


/** @brief  �ڼ���ﴴ��bat
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result
bat_monitor_create(void)D_FUNCPOSTFIT
{ 	
	D_TimerAttr ta;
	D_U32 time_out;

    ta.id =0;	
    ta.one_shot = D_TRUE;
    time_out = 1000*30;

	g_bat_monitor_handle = d_monitor_create(get_bat_data,ta,time_out);
	if(g_bat_monitor_handle!=-1)
	{
		D_U8	*buf;
		D_HMMan  hmm;
		D_Bat    *head;
		/*�ڴ����*/
		buf = (D_U8*) d_mem_alloc (0, 4096*8);
		if (! buf) {
			P_BAT_PARSE_DERR (("Cannot allocate memory for bat scan\n"));
			return D_ERR;
		}

		hmm = d_mman_create (buf, 4096*6, D_MMAN_SIMPLE);
		if (hmm == D_INVALID_HANDLE) {
			P_BAT_PARSE_DERR (("Cannot create mman for prog scan\n"));
			d_mem_free (buf);
			return D_ERR;
		}

		Batps = d_mman_alloc (hmm, sizeof (D_BatScan));
		if (! Batps) {
			d_mman_destroy (hmm);
			d_mem_free (buf);
			return D_ERR;
		}
		memset(Batps, 0x00, sizeof (D_BatScan));
		Batps->buf = buf;
		Batps->hmm = hmm;

		/*���������*/
		Batps->bat_mask = d_tab_mask_new (Batps->hmm, 1);
		if (!Batps->bat_mask)
		{
			d_mman_destroy (hmm);
			d_mem_free (buf);
			return D_ERR;
		}
	}	


	return D_OK;
}


 /** @brief  ����bat ��ع���
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result
bat_monitor_start(void)D_FUNCPOSTFIT
{
	if(g_bat_monitor_handle!=-1)
	{
		if (! Batps->bat_mask||! Batps) 
		{
			return D_ERR;
		}
		d_tab_mask_clear (Batps->bat_mask);	
		return d_monitor_start(g_bat_monitor_handle);
	}
	return D_ERR;
}


 /** @brief  ֹͣbat ��ع���
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
D_Result
bat_monitor_stop(void)D_FUNCPOSTFIT
{
	if(g_bat_monitor_handle!=-1)
	{
		return d_monitor_stop(g_bat_monitor_handle);
	}
	return D_ERR;
}


/** @brief  ���ù���bat��Ĺ�������
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result
bat_set_param(void)D_FUNCPOSTFIT
{
	D_DemuxFilter filter;

	memset(&filter,0,sizeof(D_DemuxFilter));//��ʼ��

	filter.pid = PID_BAT;//����pid
	filter.sec.length   = 16; //����bat��section header����
	filter.sec.filter[0]= TID_BAT; //����bat���table id
	filter.sec.mask[0]  = 0xff;

	if(g_bat_monitor_handle!=-1)
	{
		return d_monitor_set_param(g_bat_monitor_handle,filter);
	}
	return D_ERR;
}

 /** @brief  �ͷ�bat ���
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result
bat_set_destory(void)D_FUNCPOSTFIT
{
	if(g_bat_monitor_handle!=-1)
	{
		d_monitor_destory(g_bat_monitor_handle);
        g_bat_monitor_handle  = -1;               
	}
	if (Batps)
	{
		if (Batps->hmm != D_INVALID_HANDLE) 
		{
			d_mman_destroy (Batps->hmm);
			Batps->hmm = D_INVALID_HANDLE;
		}	
		if (Batps->buf) 
		{
			d_mem_free (Batps->buf);
			Batps->buf = NULL;
		}
		Batps = NULL;
	}

	return D_OK;
}


 /** @brief  bat ������Ϣ
* @param[in] D_MsgType type       ��Ϣ����
* @param[in] D_SiMonParam param   ��Ϣ��Ϣ
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
*/ 
static D_Result 
bat_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT
{
	D_SIMsg	msg;

	msg.type = type;
	msg.hscan = d_app_self ();
	msg.param = param;

	return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}

 /** @brief  bat ��ʼ������ں���
* @param[in] void   ע��
* @retval ��
*/ 
void p_bat_start(void)D_FUNCPOSTFIT
{
	bat_monitor_create();
	bat_set_param();
	bat_monitor_start();

	return;
}


 /** @brief  bat ע�����պ���
* @param[in] void   ע��
* @retval ��
*/ 
void p_bat_stop(void)D_FUNCPOSTFIT
{
    bat_monitor_stop();
	bat_set_destory();
	return;
}


