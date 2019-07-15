#ifndef 	_ATV_GUI_RESOURCE_FILE_
#define	_ATV_GUI_RESOURCE_FILE_


#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGUI.h"
#include "atvFormat.h"
#include "atvlanresource.h"
#include "atvImageResource.h"
#include "atvpalletes.h"

D_Result p_gui_atv_resource_init(void);
D_Result p_gui_atv_lang_set(D_U8 lang);
D_Result p_gui_atv_resource_open(void);

/* 2610���ӻ���Ŀ�������ݲ����ý���ͼƬ, 
���ǵ�����ͼ �� �ͷŽӿڣ�������ý��ʱ���ã�@qiny 2015.12.11*/
D_Result p_gui_atv_media_resource_init(void);
D_Result p_gui_atv_media_resource_deinit(void);

D_Result p_gui_atv_zhilian_resource_init(void);
D_Result p_gui_atv_zhilian_resource_deinit(void);

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_RESOURCE_FILE_
