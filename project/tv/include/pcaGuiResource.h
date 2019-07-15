#ifndef _CA_GUI_RESOURCE_FILE_
#define	_CA_GUI_RESOURCE_FILE_


#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGUI.h"
#include "mlanresource_ca.h"
#include "mImageResource_ca.h"
#include "mpalletes_ca.h"

D_Result p_gui_ca_resource_init(void);
D_Result p_gui_ca_lang_set(D_U8 lang);
D_Result p_gui_ca_resource_open(void);

#ifdef  __cplusplus
}
#endif

#endif	//_GUI_RESOURCE_FILE_

