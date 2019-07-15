/** @file
* @brief 文件系统
* @author
* @date 
*/
#include "dDebug.h"
#include "dTask.h"
#include "dGUI.h"
#include "pStb.h"

static D_Bool hp_plug_in_flag;
static D_HTask hp_probe_task_handle;
static D_Bool hp_probe_running;

static void send_msg_to_gui(D_U8 temp) D_FUNCPOSTFIT
{
    D_UserMsg msg;
    msg.type = D_MSG_USER1;
    msg.handle = -1;
    msg.param1 = USER_MSG_PARAM1_HP_STATUS;
    msg.param2 = (D_VidInputFormat)temp;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}

static void head_phone_probe_task(void *p) D_FUNCPOSTFIT
{
    D_Result r;
    D_Bool plug_in;

    while(hp_probe_running == D_TRUE)
    {
        /* 检测是否有磁盘插入 */
        r = d_av_get_earphone_status(0);
		if(r == D_ERR_INVALID_HANDLE)
		{
			d_task_wait(5000);
			continue;
		}
        plug_in = ((r == D_OK) ? D_TRUE : D_FALSE);

				if(hp_plug_in_flag != plug_in)		
		    {
		    	D_INFO("hp plug %s\n",plug_in ? "IN" : "OUT");
		    	hp_plug_in_flag = plug_in;
		    	send_msg_to_gui(plug_in);			    		
		    }
        d_task_wait(100);
    }

}

D_Result d_head_phone_open(void) D_FUNCPOSTFIT
{
    D_TaskAttr ta;

    if(hp_probe_running)
        return D_OK;

		hp_plug_in_flag = D_FALSE;
    hp_probe_running = D_TRUE;
    
    ta.id = 0;
    ta.name = "HPProbe";
    ta.priority = 3;
    ta.stack_size = 1024;
    hp_probe_task_handle = d_task_create(&ta, head_phone_probe_task, NULL);
    if(hp_probe_task_handle == D_INVALID_HANDLE)
    {
        D_ERROR("Can not create hpProbe task!\n");
        return D_ERR;
    }
    return D_OK;
}

D_Result d_head_phone_close(void) D_FUNCPOSTFIT
{
    hp_probe_running = D_FALSE;
    d_task_join(hp_probe_task_handle);

    return D_OK;
}
