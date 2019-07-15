#ifndef _GUI_RESOURCE_FILE_
#define	_GUI_RESOURCE_FILE_


#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGUI.h"
#include "lanresource.h"
#include "ImageResource.h"
#include "palletes.h"



#define ID_COLOUR_RED 96


D_Result p_gui_stb_resource_init(void);
D_Result p_gui_stb_lang_set(D_U8 lang);
D_Result p_gui_stb_resource_open(void);

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_RESOURCE_FILE_

