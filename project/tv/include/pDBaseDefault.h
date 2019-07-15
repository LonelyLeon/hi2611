/**@defgroup db 数据库定制应用
*@{*/
/** @file
* @brief 数据库定制应用模块
* @author 刘伟峰
* @date 2013-04-25 刘伟峰: 建立文件
*/

#ifndef _D_DBASEDEFAULT_H_
#define _D_DBASEDEFAULT_H_

#ifdef  __cplusplus
extern "C"
{
#endif


#include "dDBase.h"


typedef enum {
	ALL,
	SAT,
	FAV,
	BAT,
	LETTER,
} D_DBProgramListType;

typedef enum
{
	LETTER_ARRAY,
	SERVICE_ID_ARRAY,
	CA_ARRAY,
	ONID_ARRAY,
	FAV_ARRAY,
	LOCK_ARRAY,
	LCN_ARRAY,
	TS_ARRAY,
	SAT_ARRAY,
	SKIP_ARRAY,
} D_DBProgramArrayType;



/** @brief 数据库恢复出厂设置
* @retval D_OK
*/
D_Result
d_dbase_factory_set(void) D_FUNCPOSTFIT;

/** @brief 查找节目记录集中节目记录的频道号
* @param[in] rset 记录集
* @param[out] pos 存放频道号的缓冲区
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result d_dbase_program_chnum_in_rset(D_DBRecset *rset, D_S16 *pos) D_FUNCPOSTFIT;

/** @brief 对节目记录进行按多方式进行排序 
* @param[in] rset 需要进行排序的记录集
* @param[in] type 排序方式
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @param[in] rearrange 排序后是否把节目号重置为从1开始。TRUE：是；FALSE：否。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result d_dbase_program_sort(D_DBRecset *rset, D_DBProgramArrayType type, D_U8 order, D_Bool rearrange) D_FUNCPOSTFIT;

/** @brief 对节目记录进行移动
* @param[in] rset 记录集指针
* @param[in] lastchpos 移动前的位置
* @param[in] nextchpos 移动后的位置
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result d_dbase_program_move(D_DBRecset *rset, D_U16 lastchpos,D_U16 nextchpos) D_FUNCPOSTFIT;

/** @brief 按节目名称查找节目
* @param[in] src_rset 查询的节目所在的最初记录集
* @param[in] dst_rset 筛选出的节目组成的记录集
* @param[in] str 输入的字符串
* @retval D_OK 存在符合条件的节目
* @retval D_ERR 不存在符合条件的节目
*/
D_Result d_dbase_find_program_by_name(D_DBRecset *src_rset, D_DBRecset *dst_rset, D_Char str[]);

/** @更新某个ts信息
* @param[in] id TS ID
* @param[in] info TS信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_dbase_updata_ts_info(D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;
/** @brief 向TS表中插入一个记录
* @param[in] info TS信息
* @retval id TS ID
* @retval -1 插入失败
*/
D_DBTSID p_dbase_insert_ts (D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief 取得TS相关信息
* @param[in] id TS记录 ID
* @param[in] info TS信息区指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result p_dbase_get_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief 取出一个服务相关信息
* @param[in] id 服务ID
* @param[in] info 服务信息
* @retval D_OK 获得成功
* @retval D_ERR 获取失败
*/
D_Result
p_dbase_get_srv_info(D_DBSrvID id, D_DBSrvInfo * info) D_FUNCPOSTFIT;


/** @brief 向服务表中加入一条记录
* @param[in] info 服务信息
* @param[in] tmp 临时标志
* @retval id 服务ID
* @retval -1 插入失败
*/
D_DBSrvID
p_dbase_insert_srv_ex(D_DBSrvInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 向服务表中加入一条记录*/
#define p_dbase_insert_srv(_i)	p_dbase_insert_srv_ex(_i, D_FALSE)

D_Result p_precast_program(D_U32 param) D_FUNCPOSTFIT;


/** @brief 恢复出厂设置时添加预制数据*/
D_Result
d_dbase_add_default_data_dvbs(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
