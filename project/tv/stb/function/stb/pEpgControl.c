/** @file
* @brief EPG控制api
* @author 李臣
* @date 2013-08-09 李臣: 建立文件
*/
#include "dDebug.h"
#include "dScan.h"
#include "pEpgControl.h"

static D_HScan local_epgscan_handle = D_INVALID_HANDLE;

/** @brief 后台启动EPG
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_epg_start(D_U32 param) D_FUNCPOSTFIT
{
#if defined(P_AD_USE_EPG_MEM)	
#else
    if(local_epgscan_handle == D_INVALID_HANDLE)
    {
        D_EPGScanMode mode = D_SCAN_MODE_ALL_EPG;
#ifdef D_DDR_SIZE_64M
		mode =D_SCAN_MODE_PF_EPG;
#endif
        if(param == 1)
        {
            mode |= D_SCAN_MODE_TDT_TOT_EPG;
        }
        local_epgscan_handle = d_epg_scan_create(1, mode, D_FALSE, 30000, 30000,EPG_FIND_SERVICE_ID_NORMAL);
        if(local_epgscan_handle == D_INVALID_HANDLE)
        {
            D_ERROR("Can not start EPG scan!\n");
            return D_ERR;
        }
    }
#endif
    return D_OK;
}

/** @brief 关闭后台EPG
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_epg_stop(void) D_FUNCPOSTFIT
{
#if defined(P_AD_USE_EPG_MEM)	
#else
    if(local_epgscan_handle != D_INVALID_HANDLE)
    {
        d_epg_scan_destroy(local_epgscan_handle);
        local_epgscan_handle = D_INVALID_HANDLE;
    }
#endif
    return D_OK;
}
