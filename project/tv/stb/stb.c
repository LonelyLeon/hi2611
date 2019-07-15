/** @file
* @brief 项目入口
*
* @author 李臣
* @date 2013-05-15 李臣: 建立文件
*/
#include "dResource.h"
#include "dDebug.h"
#include "dTask.h"
#include "dTime.h"
#include "dGUI.h"
#include "pSdk.h"
#include "pStb.h"
#include "pConfig.h"

static void stb_init(void) D_FUNCPOSTFIT
{
	d_stb_open();
	d_stb_power_on(D_TRUE);
}

#ifdef D_TV_LIULINK_SOURCE
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
extern D_Result liulinkclient_test(void);
#endif
#endif

static void stb_main(D_Ptr p) D_FUNCPOSTFIT
{
	p_auxi_init();
	p_gui_init();
#if   D_CA_SUPPORT_DEF
	p_cas_init();
#endif
	p_tv_init();
	p_fp_init();
	stb_init();


#ifdef D_TV_LIULINK_SOURCE
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    liulinkclient_test();
#endif
#endif


	D_DUMP("GUI enter main.\n");

	d_gui_main();

	D_DUMP("GUI leave main.\n");
}

/** @brief stb库入口函数
* @param[in] argc 参数个数
* @param[in] argv 参数指针
* @return 错误代码
*/
int project_main(int argn, char *argv[]) D_FUNCPOSTFIT
{
	D_HTask hMainTask;
	D_TaskAttr MainTaskAttr;

	if(p_port_init() != D_OK)
	{
		return -1;
	}

	D_TASK_ATTR_INIT(&MainTaskAttr);
	MainTaskAttr.name = "Main";
	MainTaskAttr.priority = D_MAIN_TASK_PRIO;
	MainTaskAttr.stack_size = D_MAIN_TASK_STACK_SIZE;

	hMainTask = d_task_create(&MainTaskAttr, stb_main, NULL);
	if(hMainTask == D_INVALID_HANDLE)
	{
		D_ERROR("Main task create failed!\n");
		return -1;
	}

	d_task_join(hMainTask);

	return 0;
}

