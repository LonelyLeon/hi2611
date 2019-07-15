/** @file
* @brief TTX控制
* @author 和光雄
* @date 2013-10-12 和光雄: 建立文件
*/

//该模块目前需要动态分配的空间为2.3M左右

#ifndef __D_TTX_H
#define __D_TTX_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dScan.h"
#include "dGDev.h"


#define TTX_MAGAZINE_NO								8
#define TTX_MAGAZINE_PAGENO							100
#define TTX_PAGE_NO_MAX   							(TTX_MAGAZINE_NO*TTX_MAGAZINE_PAGENO)

#define TTX_PACKET_COUNT							36
#define TTX_PACKET_BYTES							46
#define TTX_PAGE_SIZE    							(TTX_PACKET_COUNT*TTX_PACKET_BYTES)

#define TTX_PACKET26_COUNT							16
#define TTX_PAGE26_SIZE    							(TTX_PACKET26_COUNT*TTX_PACKET_BYTES)

#define SubPage_MAX_INDEX  80

// 错误类型
typedef enum
{
	P_TTX_PMT_ERROR,
	P_TTX_PES_ERROR,
	P_TTX_UNKNOW_ERROR		
}D_Ttx_Error_Type;


/** @brief 图形操作*/
typedef struct {
	D_Result (*fill_rect) (D_Rect *rect,D_U8 textColor) D_FUNCPOSTFIT;
	D_Result (*show_Character) (D_U8 * charLib, D_U8 txt, D_U16 PosX, D_U16 PosY, D_U8 pix_W, D_U8 pix_H, D_U8 color,D_U8 SizeMode)D_FUNCPOSTFIT;
	D_Result (*show_StringInMid) (D_Rect *rect,char * textP, D_U8 color)D_FUNCPOSTFIT;
}D_TTXSurOp;


/** @brief */
typedef struct
{
	D_U32 ttx_black;
	D_U32 ttx_white;
	D_U32 ttx_red;
	D_U32 ttx_green;
	D_U32 ttx_blue;
	D_U32 ttx_yellow;
	D_U32 ttx_gray;
}D_TtxRegionConfig;

/** @brief */
typedef struct
{
	D_HQueue hqueue;			/*注册任务消息队列*/
	D_S8 	 priority;
	D_U8* 	lang;
	D_U16 	pid;
	D_U8	type;	
	D_U8	magazine_number;
	D_U8	page_number;

} D_TtxTaskConfig;
/** @brief */
typedef struct
{
	D_TTXSurOp* op;
	D_TtxRegionConfig * regionop;
} D_TtxConfig;


/** @brief创建TTX搜索任务
* @param[in] priority 任务优先级
* @return 成功返回设备句柄,失败返回D_INVALID_HANDLE
*/
D_HScan d_ttx_scan_create(D_TtxTaskConfig taskconfig,D_TtxConfig *cfg)D_FUNCPOSTFIT ;

D_Result d_ttx_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT;

void dTTX_DealData(D_U8  *TtxBuf)D_FUNCPOSTFIT;
D_Result dTTX_Open(D_TtxConfig* cfg,D_U8 type,D_U8 cmap,D_U8 cpage,D_U8  *lang)D_FUNCPOSTFIT;
D_Result dTTX_Close(void)D_FUNCPOSTFIT;
void dTTX_SetMP(D_U8 bMagazine,D_U8 bPage)D_FUNCPOSTFIT;
void HRTTX_OSD_DrawOneRow(D_U8 *RowData,D_U8 RowNo)D_FUNCPOSTFIT;
void HRTTX_ShowSearch(D_U16  sSearchPage,D_U16 sSearchMag)D_FUNCPOSTFIT;

D_Result dTTX_Switch(D_U16  inProgfo)D_FUNCPOSTFIT;
D_U8 dTTX_KeyRespond( D_U8 key )D_FUNCPOSTFIT;
D_Result  dTTX_CheckUpgrade(D_U8 flag,D_Rect* rect)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
