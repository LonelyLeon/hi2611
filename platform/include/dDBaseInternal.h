/**@defgroup dbase 数据库
*@{*/
/** @file
* @brief 数据库管理模块
* @author 龚克
* @date 2005-6-17 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
* @date 2013-04-22 lwf,sunzy: 统一平台, 代码整理
*/

#ifndef _D_DBASE_INTERNAL_H_
#define _D_DBASE_INTERNAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDBase.h"
#include "dNVPart.h"
#include "dVarString.h"
#include "dResource.h"
#include "dMem.h"
#include "dMutex.h"
#include <string.h>

#define D_DB_NVRAM_ID		(0)
#define D_DB_EEPROM_ID		(0)

/** @brief 数据库域值类型*/
typedef enum {
	D_DB_FIELD_BIT, 
	D_DB_FIELD_U8,
	D_DB_FIELD_U16,
	D_DB_FIELD_U32,
	D_DB_FIELD_ARRAY,
	D_DB_FIELD_STRING,
	D_DB_FIELD_VAR_STRING,
	D_DB_FIELD_RESERVED,
        D_DB_FIELD_2BIT,
        D_DB_FIELD_4BIT,
	D_DB_FIELD_NONE
} D_DBFieldType;

/** @brief 域*/
typedef struct {
	D_DBFieldType	 type;
	D_U8					 size;
	D_U8					*buf;
	D_Bool				 store;
	D_Bool				 dirty;
	D_ID					 part_id;
} D_DBField;

/** @brief 表*/
typedef struct {
	D_U32			max;
	D_U32			store_cnt;
	D_U8			*mask;
	D_DBField		*fields;
	D_Bool			store;
	D_Bool			dirty;
	D_ID			part_id;
	D_Result		(*init) (D_Bool init) D_FUNCPOSTFIT;
	D_Result		(*deinit) (void) D_FUNCPOSTFIT;
	D_U16			last_rec;
	D_U8			rec_id;
} D_DBTable;

/** @brief 数据区*/
typedef struct {
	D_Size			size;
	D_U8			*buf;
	D_Bool			store;
	D_Bool			dirty;
	D_ID			part_id;
	D_Result		(*init) (D_Bool init) D_FUNCPOSTFIT;
	D_Result		(*deinit) (void) D_FUNCPOSTFIT;
	D_U8			rec_id;
} D_DBBlock;

/** @brief 当part_id为D_DB_EEPROM_PART_ID时,数据保存到EEPROM中*/
#define D_DB_EEPROM_PART_ID	(0xF000)

#define D_ALIGN_U8(_n)	(_n) /*(((_n)+1) & 0xFFFFFFFE)*/
#define D_ALIGN_U16(_n)	(_n)
#define D_ALIGN_U32(_n)	(_n)

/** @brief 定义域存储区
* 因为部分数据区要存储到Flash中，Flash的访问是字对齐的(SPI无此问题)，
* 所以存储区定义成2字节对齐的。
*/
#define D_DEF_FIELD_BIT(_n,_c)
#define D_DEF_FIELD_2BIT(_n,_c)
#define D_DEF_FIELD_4BIT(_n,_c)
#define D_DEF_FIELD_U8(_n,_c)
#define D_DEF_FIELD_U16(_n,_c)
#define D_DEF_FIELD_U32(_n,_c)
#define D_DEF_FIELD_ARRAY(_n,_s,_c)
#define D_DEF_FIELD_STRING(_n,_s,_c)
#define D_DEF_FIELD_VAR_STRING(_n,_c)
#define D_DEF_FIELD_RESERVED(_n,_s,_c)

/** @brief 定义域*/
#define D_ADD_FIELD_BIT(_n,_s,_p)		{D_DB_FIELD_BIT,1,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_2BIT(_n,_s,_p)		{D_DB_FIELD_2BIT,1,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_4BIT(_n,_s,_p)		{D_DB_FIELD_4BIT,1,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_U8(_n,_s,_p)		{D_DB_FIELD_U8,1,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_U16(_n,_s,_p)		{D_DB_FIELD_U16,2,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_U32(_n,_s,_p)		{D_DB_FIELD_U32,4,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_ARRAY(_n,_l,_s,_p)		{D_DB_FIELD_ARRAY,D_ALIGN_U8(_l),NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_STRING(_n,_l,_s,_p)		{D_DB_FIELD_STRING,D_ALIGN_U8(_l),NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_VAR_STRING(_n,_s,_p)	{D_DB_FIELD_VAR_STRING,0,NULL,_s,D_FALSE,_p},
#define D_ADD_FIELD_RESERVED(_n,_s,_p)	{D_DB_FIELD_RESERVED,0,NULL,_s,D_FALSE,_p},
#define D_FIELD_END()								{D_DB_FIELD_NONE},
#define D_FIELD(_t,_f)	((_t)->fields+(_f))

#define D_BLOCK_DIRTY(_b)\
		((_b)->dirty = D_TRUE)

/** @brief 设置域*/
#define D_SET_FIELD_BIT(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			((_v)?D_SET_MASK(D_FIELD(_t,_f)->buf,_i):D_CLEAR_MASK(D_FIELD(_t,_f)->buf,_i));\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U8 _tmp = (D_U8)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 1, &_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END

#define D_SET_FIELD_2BIT(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			D_SET_2BIT(D_FIELD(_t,_f)->buf, _i, _v);\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U8 _tmp = (D_U8)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 1, &_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END
		
#define D_SET_FIELD_4BIT(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			D_SET_4BIT(D_FIELD(_t,_f)->buf, _i, _v);\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U8 _tmp = (D_U8)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 1, &_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END

#define D_SET_FIELD_U8(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			(D_FIELD(_t,_f)->buf[_i]=(_v));\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U8 _tmp = (D_U8)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 1, &_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END
#define D_SET_FIELD_U16(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			(((D_U16*)D_FIELD(_t,_f)->buf)[_i]=(_v));\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U16 _tmp = (D_U16)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 2, (D_U8*)&_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END
#define D_SET_FIELD_U32(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			(((D_U32*)D_FIELD(_t,_f)->buf)[_i]=(_v));\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					D_U32 _tmp = (D_U32)(_v);\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), 4, (D_U8*)&_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END
#define D_SET_FIELD_ARRAY(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			memcpy(D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size,_v,D_FIELD(_t,_f)->size);\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), D_FIELD(_t,_f)->size, (D_U8*)(_v), D_TRUE);\
				}\
			}\
		D_MACRO_END
#define D_SET_FIELD_STRING(_t,_f,_i,_v)\
		D_MACRO_BEGIN\
			strncpy((D_Char*)(D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size),_v,(D_Size)D_FIELD(_t,_f)->size-1);\
			if (((_i)<(_t)->store_cnt) && (_t)->store && D_FIELD(_t,_f)->store) {\
				D_FIELD(_t,_f)->dirty = D_TRUE;\
				{\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, (_f), (_i), D_FIELD(_t,_f)->size - 1, (D_U8*)(_v), D_TRUE);\
				}\
			}\
		D_MACRO_END
#define D_SET_FIELD_VAR_STRING(_t,_f,_i,_v,_s)\
		D_MACRO_BEGIN\
			if (((D_VarString**)D_FIELD(_t,_f)->buf)[_i])\
				d_var_string_del (((D_VarString**)D_FIELD(_t,_f)->buf)[_i]);\
			((D_VarString**)D_FIELD(_t,_f)->buf)[_i] = d_var_string_set (_v,_s);\
		D_MACRO_END

#define D_SET_FIELD_RESERVED(_t,_f,_i,_v)\
        D_MACRO_BEGIN\
            if(D_FIELD(_t,_f)->buf)\
                D_SET_FIELD_ARRAY(_t, _f, _i, _v);\
        D_MACRO_END
        
/** @brief 取域值*/
#define D_GET_FIELD_BIT(_t,_f,_i,_v)		((_v)=(D_ISSET_MASK(D_FIELD(_t,_f)->buf,_i))? 1 : 0)
#define D_GET_FIELD_2BIT(_t,_f,_i,_v)		((_v)=D_GET_2BIT(D_FIELD(_t,_f)->buf, _i))
#define D_GET_FIELD_4BIT(_t,_f,_i,_v)		((_v)=D_GET_4BIT(D_FIELD(_t,_f)->buf, _i))
#define D_GET_FIELD_U8(_t,_f,_i,_v)		        ((_v)=D_FIELD(_t,_f)->buf[_i])
#define D_GET_FIELD_U16(_t,_f,_i,_v)		((_v)=((D_U16*)D_FIELD(_t,_f)->buf)[_i])
#define D_GET_FIELD_U32(_t,_f,_i,_v)		((_v)=((D_U32*)D_FIELD(_t,_f)->buf)[_i])
#define D_GET_FIELD_ARRAY(_t,_f,_i,_v)		memcpy((_v),D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size,D_FIELD(_t,_f)->size)
#define D_GET_FIELD_STRING(_t,_f,_i,_v)	strncpy((_v),(D_Char*)D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size,(D_Size)D_FIELD(_t,_f)->size-1)
#define D_GET_FIELD_VAR_STRING(_t,_f,_i,_v,_s)\
		d_var_string_get (((D_VarString**)D_FIELD(_t,_f)->buf)[_i],_v,_s)
#define D_GET_FIELD_RESERVED(_t,_f,_i,_v)\
        D_MACRO_BEGIN\
            if(D_FIELD(_t,_f)->buf)\
                D_GET_FIELD_ARRAY(_t, _f, _i, _v);\
        D_MACRO_END

#define D_INIT_FIELD_VAR_STRING(_t,_f,_i)\
		(((D_VarString**)D_FIELD(_t,_f)->buf)[_i]=NULL)
#define D_DEL_FIELD_VAR_STRING(_t,_f,_i)\
		D_MACRO_BEGIN\
			d_var_string_del (((D_VarString**)D_FIELD(_t,_f)->buf)[_i]);\
			((D_VarString**)D_FIELD(_t,_f)->buf)[_i]=NULL;\
		D_MACRO_END

#define D_FIELD_BIT(_t,_f,_i)					(D_ISSET_MASK(D_FIELD(_t,_f)->buf,_i))
#define D_FIELD_2BIT(_t,_f,_i)					(D_GET_2BIT(D_FIELD(_t,_f)->buf, _i))
#define D_FIELD_4BIT(_t,_f,_i)					(D_GET_4BIT(D_FIELD(_t,_f)->buf, _i))
#define D_FIELD_U8(_t,_f,_i)					(D_FIELD(_t,_f)->buf[_i])
#define D_FIELD_U16(_t,_f,_i)					(((D_U16*)D_FIELD(_t,_f)->buf)[_i])
#define D_FIELD_U32(_t,_f,_i)					(((D_U32*)D_FIELD(_t,_f)->buf)[_i])
#define D_FIELD_ARRAY(_t,_f,_i)				(D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size)
#define D_FIELD_STRING(_t,_f,_i)			(D_FIELD(_t,_f)->buf+(_i)*D_FIELD(_t,_f)->size)
#define D_FIELD_RESERVED                    D_FIELD_ARRAY  //不安全使用

/*ID型数据域*/
#define D_FIELD_ID				D_FIELD_U32
#define D_GET_FIELD_ID		D_GET_FIELD_U32
#define D_SET_FIELD_ID		D_SET_FIELD_U32
#define D_ADD_FIELD_ID		D_ADD_FIELD_U32
#define D_DEF_FIELD_ID		D_DEF_FIELD_U32
#define D_DB_FIELD_ID			D_DB_FIELD_U32
#define D_ALIGN_ID				D_ALIGN_U32

/** @brief 定义表*/
#define D_DEF_TABLE(_n,_m,_f,_s,_p,_init,_deinit)\
		D_DBTable	_n = {_m,_m,NULL,_f,_s,D_FALSE,_p,_init,_deinit,0,0};

/** @brief 定义表(增加了需要保存记录的数目)*/
#define D_DEF_TABLE_EX(_n,_m,_sn,_f,_s,_p,_init,_deinit)\
		D_DBTable	_n = {_m,_sn,NULL,_f,_s,D_FALSE,_p,_init,_deinit,0,0};

/** @brief 定义数据块*/
#define D_DEF_BLOCK(_n,_m,_b,_s,_p,_init,_deinit)\
		D_DBBlock 	_n = {_m,(D_U8*)_b,_s,D_FALSE,_p,_init,_deinit,0};

extern D_HMutex	dbase_lock;

/** @brief 加锁*/
#define D_DB_LOCK()		d_mutex_lock(dbase_lock)

/** @brief 解锁*/
#define D_DB_UNLOCK()	d_mutex_unlock(dbase_lock)
			
/** @brief 记录是否已经分配*/
#define D_REC_VALID(_t,_i)		D_ISSET_MASK((_t)->mask, _i)

/** @brief 记录是否在范围内*/
#define D_REC_IN_RANGE(_t,_i)	(((_i)>=0)&&((_i)<(_t)->max))

/** @brief 检查记录有效性*/
#define D_REC_CHECK(_t,_i)	(D_REC_IN_RANGE(_t,_i) && D_REC_VALID(_t,_i))

/** @brief 分配一个空闲记录*/
#define D_ALLOC_REC(_t,_ret)\
		D_MACRO_BEGIN\
			D_ID	_i;\
			_ret = -1;\
			for (_i = (_t)->last_rec+1; _i < (_t)->store_cnt; _i++) {\
				if (! D_REC_VALID(_t,_i)) {\
					_ret = _i;\
					(_t)->last_rec = _i;\
					D_SET_MASK ((_t)->mask, _i);\
					if ((_i)<(_t)->store_cnt) {\
						(_t)->dirty = D_TRUE;\
					}\
					break;\
				}\
			}\
			if (_ret == -1 && (_t)->store_cnt) {\
				for (_i = 0; _i <= (_t)->last_rec; _i++) {\
					if (! D_REC_VALID(_t,_i)) {\
						_ret = _i;\
						(_t)->last_rec = _i;\
						D_SET_MASK ((_t)->mask, _i);\
						if ((_i)<(_t)->store_cnt) {\
							(_t)->dirty = D_TRUE;\
						}\
						break;\
					}\
				}\
			}\
			if((_ret != -1) && (_t)->store)\
			{\
				D_U8 _tmp = 1;\
				d_dbase_record_flash_flush_tbl((_t)->rec_id, -1, _ret, 1, &_tmp, D_TRUE);\
			}\
		D_MACRO_END

/** @brief 分配一个空闲的临时记录*/
#define D_ALLOC_TEMP_REC(_t,_ret)\
		D_MACRO_BEGIN\
			D_ID	_i;\
			_ret = -1;\
			for (_i = (_t)->store_cnt; _i < (_t)->max; _i++) {\
				if (! D_REC_VALID(_t,_i)) {\
					_ret = _i;\
					D_SET_MASK ((_t)->mask, _i);\
					break;\
				}\
			}\
		D_MACRO_END

/** @brief 删除一个记录*/
#define D_DEL_REC(_t,_i)\
		D_MACRO_BEGIN\
			D_CLEAR_MASK((_t)->mask, _i);\
			if ((_i)<(_t)->store_cnt) {\
				(_t)->dirty = D_TRUE;\
				if((_t)->store)\
				{\
					D_U8 _tmp = 0;\
					d_dbase_record_flash_flush_tbl((_t)->rec_id, -1, (_i), 1, &_tmp, D_TRUE);\
				}\
			}\
		D_MACRO_END

/** @brief 清空表*/
#define D_DB_CLEAR(_t)\
		D_MACRO_BEGIN\
		    if((_t)->store)\
			{\
				D_ID _i;\
				D_U8 _tmp = 0;\
				for(_i = 0;_i < (_t)->store_cnt;_i ++)\
				{\
					if(D_REC_VALID(_t,_i))\
						d_dbase_record_flash_flush_tbl((_t)->rec_id, -1, _i, 1, &_tmp, D_TRUE);\
				}\
			}\
			memset ((_t)->mask, 0, ((D_U32)(_t)->max+7)>>3);\
			(_t)->last_rec = 0;\
			(_t)->dirty = D_TRUE;\
		D_MACRO_END
		
/** @brief 遍历一个表*/
#define D_DB_FOR_EACH(_t,_j)\
		D_MACRO_BEGIN\
			D_ID _i;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					_j(_i);\
				}\
			}\
		D_MACRO_END

/** @brief 查找记录*/
#define D_DB_SELECT(_t,_cmp,_set)\
		D_MACRO_BEGIN\
			D_ID _i;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					if (_cmp (_i)) {\
						if (d_dbase_rset_add (_set,_i) < 0) {\
							break;\
						}\
					}\
				}\
			}\
		D_MACRO_END

/** @brief 查找一个记录*/
#define D_DB_SELECT1(_t,_cmp,_ret)\
		D_MACRO_BEGIN\
			D_ID _i;\
			_ret=-1;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					if (_cmp (_i)) {\
						_ret = _i;\
						break;\
					}\
				}\
			}\
		D_MACRO_END

/** @brief 删除记录*/
#define D_DB_DELETE(_t,_cmp,_j)\
		D_MACRO_BEGIN\
			D_ID _i;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					if (_cmp (_i)) {\
						_j (_i);\
						D_DEL_REC (_t,_i);\
						if ((_i)<(_t)->store_cnt) {\
							(_t)->dirty = D_TRUE;\
						}\
					}\
				}\
			}\
		D_MACRO_END

/** @brief 删除一个记录*/
#define D_DB_DELETE1(_t,_cmp,_j)\
		D_MACRO_BEGIN\
			D_ID _i;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					if (_cmp (_i)) {\
						_j (_i);\
						D_DEL_REC (_t,_i);\
						if ((_i)<(_t)->store_cnt) {\
							(_t)->dirty = D_TRUE;\
						}\
						break;\
					}\
				}\
			}\
		D_MACRO_END

/** @brief 获取table ID
* @param[in] table 数据表指针	
*/
static __inline__ D_ID d_dbase_get_table_id (D_DBTable* table) D_FUNCPOSTFIT
{   
	return (D_ID)(table->rec_id);
}

/** @brief 获取block ID
* @param[in] block 数据块指针	
*/
static __inline__ D_ID d_dbase_get_block_id (D_DBBlock* block) D_FUNCPOSTFIT
{   
	return (D_ID)(block->rec_id);
}

/** @brief 取得服务的第一个事件
* @param[in] srv 服务ID
* @retval evt 事件记录ID
* @retval -1 获取失败
*/
D_DBEvtID	dbase_get_srv_first_evt (D_DBSrvID srv) D_FUNCPOSTFIT;

/** @brief 设置服务的第一个事件
* @param[in] srv 服务ID
* @param[in] evt 事件记录ID
* @retval  D_OK 更新成功
* @retval  D_ERR更新失败
*/
D_Result	dbase_set_srv_first_evt (D_DBSrvID srv, D_DBEvtID evt) D_FUNCPOSTFIT;

/** @brief 清除全部服务的第一个事件
* @retval D_OK 清除成功
*/
D_Result	dbase_clear_srv_first_evt (void) D_FUNCPOSTFIT;

/** @brief 取得指定事件的时移事件
* @param[in] srv_id	服务ID
* @param[in] ref 事件ID
* @param[in] begin	起始时间
* @param[in] end	结束时间
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	dbase_get_shifted_evts (D_DBSrvID srv_id, D_DBEvtID ref, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得指定事件的时移事件
* @param[in] srv_id	服务ID
* @param[in] ref 事件ID
* @param[in] now	当前时间
* @param[in] p	
* @param[in] f	
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	dbase_get_pf_shifted_evts (D_DBSrvID srv_id, D_DBEvtID ref, D_Time now, D_Bool p, D_Bool f, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 检查服务是否是参考服务
* @param[in] id 服务记录ID
* @retval D_TRUE 是
* @retval D_FALSE 不是
*/
D_Bool		d_dbase_is_ref_srv (D_DBSrvID id) D_FUNCPOSTFIT;

#ifdef D_SUPPORT_EEPROM
/** @brief 保存域值到EEPROM中
* @param[in] table	数据库表指针
* @param[in] fid	数据域ID
* @param[in] rid	记录的DID
* @retval 成功返回写入的数据大小
* @retval 失败返回D_ERR
*/
D_Result		d_dbase_eeprom_store_field (D_DBTable *table, D_ID fid, D_DBID rid) D_FUNCPOSTFIT;

/** @brief 保存数据块数据到EEPROM中
* @param blk	数据块指针
* @param offset	偏移地址
* @param size	写入数据的大小
* @retval 成功返回写入的数据大小
* @retval 失败返回D_ERR
*/
D_Size			d_dbase_eeprom_store_data (D_DBBlock *blk, D_Size offset, D_Size size) D_FUNCPOSTFIT;

/** @brief 从EEPROM中读取数据
* @param[in] blk	数据块指针
* @param[in] offset	偏移地址
* @param[in] size	读取的数据大小
* @retval 成功返回读取数据的大小
* @retval 失败返回D_ERR
*/
D_Size			d_dbase_eeprom_read_data (D_DBBlock *blk, D_Size offset, D_Size size) D_FUNCPOSTFIT;
#endif

#ifdef  __cplusplus
}
#endif

#endif
/*EOF*/
/**@}*/

