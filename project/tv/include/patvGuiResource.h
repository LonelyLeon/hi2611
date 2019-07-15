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

/* 2610电视机项目，开机暂不解多媒体的图片, 
这是单独解图 与 释放接口，进出多媒体时调用，@qiny 2015.12.11*/
D_Result p_gui_atv_media_resource_init(void);
D_Result p_gui_atv_media_resource_deinit(void);

D_Result p_gui_atv_zhilian_resource_init(void);
D_Result p_gui_atv_zhilian_resource_deinit(void);

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_RESOURCE_FILE_
