#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pMonitorRegister.h"
#include "pConfig.h"
#include "dCBMan.h"
#include "pFm.h"
#include "dSerial.h"

#define P_FM_PARSE_DUMP(_x_)  D_DUMP _x_   ///<调试打印信息
#define P_FM_PARSE_DERR(_x_)  D_ERROR _x_  ///<错误打印信息

D_fmScan *fmps;

static D_MonitorHandle g_fm_monitor_handle = -1;
static D_HSerial fm_hs = D_INVALID_HANDLE;;

static D_Result
serial_interface_scanner_open (D_HSerial* srl_hdl)D_FUNCPOSTFIT 
{
	D_SerialAttr com;
	D_SerialMode mode;
	
	if(d_serial_open() != D_OK)	//打开串口失败
	{
		return D_ERR;
	}
	com.id = 0;
	*srl_hdl = d_serial_create(&com);
	if((*srl_hdl) == D_INVALID_HANDLE)	//创建串口失败
	{
		return D_ERR;
	}
	d_serial_flush(*srl_hdl);
	
	return D_OK;
}

static D_Result 
p_fm_parse_table(TVData *tv, D_U8 *buf, D_Size length)D_FUNCPOSTFIT
{
	D_U8	*ptr;
	D_S16	len;
	D_U8	tab_id;
	D_HMMan hmm;
	D_U8 section_syntax_indicator;
	D_U16 actuallywritten;

	if (!buf) 
	{
		P_FM_PARSE_DERR (("Buffer is NULL\n"));
		return D_ERR;
	}
	
	if (length < 3) 
	{
		P_FM_PARSE_DERR (("Section size < 3 bytes\n"));
		return D_ERR;
	}

	ptr = buf;
	len = D_SI_HILO (D_SI_BIT(ptr[1], 4, 4),ptr[2]);
	section_syntax_indicator = D_SI_BIT(ptr[1], 0, 1);
	
	if(len > length) 
	{
		P_FM_PARSE_DERR (("Sction length error\n"));
		return D_ERR;
	}

	tab_id = ptr[0];
	  
	if(section_syntax_indicator == 0)
	{
		actuallywritten = d_serial_write(fm_hs, ptr+3, len);
		d_serial_flush(fm_hs);
	}
	
	return D_ERR;
		
}
 /** @brief  在监控里创建fm
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/ 
D_Result
p_fm_monitor_create(void)D_FUNCPOSTFIT
{ 	
	D_TimerAttr ta;
	D_U32 time_out;
	
	ta.id =0;	
	ta.one_shot = D_TRUE;
	time_out = 10000;
	
	g_fm_monitor_handle = d_monitor_create_ex(p_fm_parse_table,ta,time_out, D_TRUE);
	
	if(g_fm_monitor_handle!=-1)
	{
		D_U8	*buf;
		D_HMMan  hmm;

		/*内存分配*/
		buf = (D_U8*) d_mem_alloc (0, 4096);
		if (! buf)
		{
			P_FM_PARSE_DERR (("Cannot allocate memory for fm scan\n"));
			return D_ERR;
		}

		hmm = d_mman_create (buf, 4096, D_MMAN_SIMPLE);
		if (hmm == D_INVALID_HANDLE)
		{
			P_FM_PARSE_DERR (("Cannot create mman for prog scan\n"));
			d_mem_free (buf);
			return D_ERR;
		}

		fmps = d_mman_alloc (hmm, sizeof (D_fmScan));
		if (! fmps)
		{
			d_mman_destroy (hmm);
			d_mem_free (buf);
			return D_ERR;
		}

		memset(fmps, 0x00, sizeof (D_fmScan));
		fmps->buf = buf;
		fmps->hmm = hmm;

		/*分配表屏蔽*/
		fmps->fm_mask = d_tab_mask_new (hmm, 1);
		if (! fmps->fm_mask) 
		{
			d_mman_destroy (hmm);
			d_mem_free (buf);
			return D_ERR;
		}
	}	

	return D_OK;
}

 /** @brief  开启fm 监控过滤
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/ 
D_Result
p_fm_monitor_start(void)D_FUNCPOSTFIT
{
	if(g_fm_monitor_handle!=-1)
	{
		if (! fmps->fm_mask||! fmps) 
		{
			return D_ERR;
		}
		d_tab_mask_clear (fmps->fm_mask);	
		return d_monitor_start(g_fm_monitor_handle);
	}
	return D_ERR;
}

 /** @brief  停止fm 监控过滤
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/ 
D_Result
p_fm_monitor_stop(void)D_FUNCPOSTFIT
{
	if(g_fm_monitor_handle!=-1)
	{
		return d_monitor_stop(g_fm_monitor_handle);
	}
	return D_ERR;
}
 
 /** @brief  设置过滤fm表的过滤条件
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/ 
D_Result
p_fm_set_param(void)D_FUNCPOSTFIT
{
	D_DemuxFilter filter;
	D_SIParam si_param;
#ifdef D_CA_SUPPORT_XGCA                    

	memset(&filter,0,sizeof(D_DemuxFilter));//初始化
	p_conf_get_si_param (&si_param);/// 取得SI设置

	filter.pid=si_param.cdxg_desc_pid;//设置pid
	filter.sec.length=16;
	filter.sec.filter[0]=0xFD;//设置tbid
	filter.sec.mask[0]=0xff;

	if(g_fm_monitor_handle!=-1)
	{
		return d_monitor_set_param(g_fm_monitor_handle,filter);
	}
	#endif
	return D_ERR;
}

 /** @brief  释放fm 监控
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/ 
D_Result
p_fm_set_destory(void)D_FUNCPOSTFIT
{
	if (! fmps)
		return D_ERR;
	
    if (fmps->hmm != D_INVALID_HANDLE)
    {
		d_mman_destroy (fmps->hmm);
		fmps->hmm = NULL;
	}

    if (fmps->buf)
    {
		d_mem_free (fmps->buf);
	}
	
	if(g_fm_monitor_handle!=-1)
	{
		d_monitor_destory(g_fm_monitor_handle);
              g_fm_monitor_handle  = -1;               
	}
	fmps = NULL;
	
	return D_OK;
}


 /** @brief  fM 开始接收入口函数
* @param[in] void   注释
* @retval 无
*/ 
void p_fm_start( void)D_FUNCPOSTFIT
{
	p_fm_monitor_create();
	p_fm_set_param();
	p_fm_monitor_start();
	serial_interface_scanner_open(&fm_hs);

	return;
}
 
 /** @brief  fm 注销接收函数
* @param[in] void   注释
* @retval 无
*/ 
void p_fm_stop(void)D_FUNCPOSTFIT
{
       p_fm_monitor_stop();
	p_fm_set_destory();
	
	return;
}
 
