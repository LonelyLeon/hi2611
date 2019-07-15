/** @file
* @brief 屏参处理相关设置
* @author 刘爽
* @date 2017-01-22 lius: 建立文件
*/

#include "dTypes.h"

/** @brief d_panel_Set_LvdsVcc
* @param en[0:1]
* @return 成功返回D_OK,失败返回D_ERR
*/
void d_panel_Set_LvdsVcc(D_U8 en)D_FUNCPOSTFIT;

/** @brief d_panel_Set_LvdsData
* @param en[0:1]
* @return 成功返回D_OK,失败返回D_ERR
*/
void d_panel_Set_LvdsData(D_U8 en)D_FUNCPOSTFIT;

/** @brief d_panel_Set_LvdsBacklight
* @param en[0:1]
* @return 成功返回D_OK,失败返回D_ERR
*/
void d_panel_Set_LvdsBacklight(D_U8 en)D_FUNCPOSTFIT;

/** @brief d_panel_init
* @param en[0:1]
* @return 
*/
void d_panel_init(void)D_FUNCPOSTFIT;


/** @brief d_panel_Set_exchange
* @param val
1'b0: exchange 
1'b1: no exchange
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_exchange(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_map
* @param 
1'b0: JEIDA standard
1'b1: VESA standard
* @return 成功返回D_OK,失败返回D_ERR
*/
void d_panel_Set_map(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_split
* @param val
1'b0: single channel output
1'b1: dual channel output
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_split(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_PLL
* @param param1
INPUT DIVIDER VALUE
* @param param2
FEEDBACK DIVIDER VALUE
* @param param3
VCO BAND SELECT[0:1]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_PLL(D_U8 param1, D_U8 param2, D_U8 param3)D_FUNCPOSTFIT;

/** @brief d_panel_Set_tx_amp_ctrl
* @param mode[0:1]
when mode was 0,Vod=350mv
* @param level--Vod level when mode was 1;
level[0,1,2...7]---Vod[150mv,200mv,250mv...600mv]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_tx_amp_ctrl(D_U8 mode, D_U8 level)D_FUNCPOSTFIT;

/** @brief d_panel_Set_pnsel
* @param lpn --Left P N exchange
* @param rpn --Right P N exchange
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_pnsel(D_U8 lpn, D_U8 rpn)D_FUNCPOSTFIT;

/** @brief d_panel_Set_de_mode
* @param val
1'b0: vs/hs/de in output sync
1'b1: only de in output sync
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_de_mode(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_sync_mode
* @param val
1'b0: reset in every frame
1'b1: reset in every line
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_sync_mode(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_ser_mode
* @param val
2'b00: 6bit P2S
2'b01: 7bit P2S
2'b10: 8bit P2S
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_ser_mode(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_sequence
* @param val
BIT[0] 1'b0:reverse 1'b1:normal
BIT[1] 1'b0: Pairs 0 and 2
exchange
      1'b1: normal
BIT[2] 1'b0: P N exchange for all
           pairs
       1'b1: normal
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_sequence(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_scnt
* @param  val
HCNT RESET VALUE
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_scnt(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_sync_adj
* @param val
VCNT RESET VALUE
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_sync_adj(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_de_adj
* @param val
RESET POSITION AFTER DE START
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_de_adj(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_hsync_end
* @param val
HORIZONTAL DE END AFTER SPLIT 
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_hsync_end(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_hde_start
* @param val
HORIZONTAL DE START AFTER SPLIT 
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_hde_start(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_hde_end
* @param val
HORIZONTAL DE END AFTER SPLIT  
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_hde_end(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_htotal
* @param val
HORIZONTAL TOTAL AFTER SPLIT 
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_htotal(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_de_width
* @param val
DE WIDTH BEFORE SPLIT 
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_de_width(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_vtotal
* @param val
VERTICAL TOTAL
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_vtotal(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_vsync_end
* @param val
VERTICAL SYNC END
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_vsync_end(D_U8 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_vde_start
* @param val
VERTICAL DE START
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_vde_start(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_vde_end
* @param val
VERTICAL DE END
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_panel_Set_vde_end(D_U16 val)D_FUNCPOSTFIT;

/** @brief d_panel_Set_Lvds_vtotal
* @param val
* @return NULL
*/
void d_panel_Set_Lvds_vtotal(D_U16 val)D_FUNCPOSTFIT;
/** @brief d_panel_Set_Lvds_vtotal
* @param val
* @return NULL
*/
void d_panel_Set_LVDS_TXCTRL(D_U8 txlval,D_U8 txrval)D_FUNCPOSTFIT;

void d_panel_Set_LVDS_DA_CLK(D_U8 dat,D_U8 clk)D_FUNCPOSTFIT;
