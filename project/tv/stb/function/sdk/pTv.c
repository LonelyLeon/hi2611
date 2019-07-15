/** @file
* @brief Tv
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#include "dResource.h"
#include "dGUI.h"
#include "dTV.h"
#include "pSdk.h"
#include "pCustomConfig.h"

D_HTV g_htv = D_INVALID_HANDLE;

D_Result p_tv_init(void) D_FUNCPOSTFIT
{
	D_AVAttr aa;
	
	d_tv_open();

	aa.id = 0;
	aa.fend_id = 0;
    aa.decodetype = g_custom_config.decode_switch.decodetype;   
    aa.wait_sync_type = g_custom_config.switch_play.wait_sync_type;
	g_htv = d_tv_create(D_TV_TASK_PRIO, &aa, d_gui_get_queue());

	D_DUMP("p_tv_init Ok.\n");

	return D_OK;
}

