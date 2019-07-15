/**@defgroup dbase ���ݿ�
*@{*/
/** @file
* @brief ���ݿ����ģ��
* @author ����
* @date 2005-6-17 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
* @date 2013-04-22 lwf,sunzy: ͳһƽ̨, ��������
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

/** @brief ���ݿ���ֵ����*/
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

/** @brief ��*/
typedef struct {
	D_DBFieldType	 type;
	D_U8					 size;
	D_U8					*buf;
	D_Bool				 store;
	D_Bool				 dirty;
	D_ID					 part_id;
} D_DBField;

/** @brief ��*/
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

/** @brief ������*/
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

/** @brief ��part_idΪD_DB_EEPROM_PART_IDʱ,���ݱ��浽EEPROM��*/
#define D_DB_EEPROM_PART_ID	(0xF000)

#define D_ALIGN_U8(_n)	(_n) /*(((_n)+1) & 0xFFFFFFFE)*/
#define D_ALIGN_U16(_n)	(_n)
#define D_ALIGN_U32(_n)	(_n)

/** @brief ������洢��
* ��Ϊ����������Ҫ�洢��Flash�У�Flash�ķ������ֶ����(SPI�޴�����)��
* ���Դ洢�������2�ֽڶ���ġ�
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

/** @brief ������*/
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

/** @brief ������*/
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
        
/** @brief ȡ��ֵ*/
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
#define D_FIELD_RESERVED                    D_FIELD_ARRAY  //����ȫʹ��

/*ID��������*/
#define D_FIELD_ID				D_FIELD_U32
#define D_GET_FIELD_ID		D_GET_FIELD_U32
#define D_SET_FIELD_ID		D_SET_FIELD_U32
#define D_ADD_FIELD_ID		D_ADD_FIELD_U32
#define D_DEF_FIELD_ID		D_DEF_FIELD_U32
#define D_DB_FIELD_ID			D_DB_FIELD_U32
#define D_ALIGN_ID				D_ALIGN_U32

/** @brief �����*/
#define D_DEF_TABLE(_n,_m,_f,_s,_p,_init,_deinit)\
		D_DBTable	_n = {_m,_m,NULL,_f,_s,D_FALSE,_p,_init,_deinit,0,0};

/** @brief �����(��������Ҫ�����¼����Ŀ)*/
#define D_DEF_TABLE_EX(_n,_m,_sn,_f,_s,_p,_init,_deinit)\
		D_DBTable	_n = {_m,_sn,NULL,_f,_s,D_FALSE,_p,_init,_deinit,0,0};

/** @brief �������ݿ�*/
#define D_DEF_BLOCK(_n,_m,_b,_s,_p,_init,_deinit)\
		D_DBBlock 	_n = {_m,(D_U8*)_b,_s,D_FALSE,_p,_init,_deinit,0};

extern D_HMutex	dbase_lock;

/** @brief ����*/
#define D_DB_LOCK()		d_mutex_lock(dbase_lock)

/** @brief ����*/
#define D_DB_UNLOCK()	d_mutex_unlock(dbase_lock)
			
/** @brief ��¼�Ƿ��Ѿ�����*/
#define D_REC_VALID(_t,_i)		D_ISSET_MASK((_t)->mask, _i)

/** @brief ��¼�Ƿ��ڷ�Χ��*/
#define D_REC_IN_RANGE(_t,_i)	(((_i)>=0)&&((_i)<(_t)->max))

/** @brief ����¼��Ч��*/
#define D_REC_CHECK(_t,_i)	(D_REC_IN_RANGE(_t,_i) && D_REC_VALID(_t,_i))

/** @brief ����һ�����м�¼*/
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

/** @brief ����һ�����е���ʱ��¼*/
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

/** @brief ɾ��һ����¼*/
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

/** @brief ��ձ�*/
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
		
/** @brief ����һ����*/
#define D_DB_FOR_EACH(_t,_j)\
		D_MACRO_BEGIN\
			D_ID _i;\
			for (_i = 0; _i < (_t)->max; _i++) {\
				if (D_REC_VALID(_t, _i)) {\
					_j(_i);\
				}\
			}\
		D_MACRO_END

/** @brief ���Ҽ�¼*/
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

/** @brief ����һ����¼*/
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

/** @brief ɾ����¼*/
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

/** @brief ɾ��һ����¼*/
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

/** @brief ��ȡtable ID
* @param[in] table ���ݱ�ָ��	
*/
static __inline__ D_ID d_dbase_get_table_id (D_DBTable* table) D_FUNCPOSTFIT
{   
	return (D_ID)(table->rec_id);
}

/** @brief ��ȡblock ID
* @param[in] block ���ݿ�ָ��	
*/
static __inline__ D_ID d_dbase_get_block_id (D_DBBlock* block) D_FUNCPOSTFIT
{   
	return (D_ID)(block->rec_id);
}

/** @brief ȡ�÷���ĵ�һ���¼�
* @param[in] srv ����ID
* @retval evt �¼���¼ID
* @retval -1 ��ȡʧ��
*/
D_DBEvtID	dbase_get_srv_first_evt (D_DBSrvID srv) D_FUNCPOSTFIT;

/** @brief ���÷���ĵ�һ���¼�
* @param[in] srv ����ID
* @param[in] evt �¼���¼ID
* @retval  D_OK ���³ɹ�
* @retval  D_ERR����ʧ��
*/
D_Result	dbase_set_srv_first_evt (D_DBSrvID srv, D_DBEvtID evt) D_FUNCPOSTFIT;

/** @brief ���ȫ������ĵ�һ���¼�
* @retval D_OK ����ɹ�
*/
D_Result	dbase_clear_srv_first_evt (void) D_FUNCPOSTFIT;

/** @brief ȡ��ָ���¼���ʱ���¼�
* @param[in] srv_id	����ID
* @param[in] ref �¼�ID
* @param[in] begin	��ʼʱ��
* @param[in] end	����ʱ��
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	dbase_get_shifted_evts (D_DBSrvID srv_id, D_DBEvtID ref, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��ָ���¼���ʱ���¼�
* @param[in] srv_id	����ID
* @param[in] ref �¼�ID
* @param[in] now	��ǰʱ��
* @param[in] p	
* @param[in] f	
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	dbase_get_pf_shifted_evts (D_DBSrvID srv_id, D_DBEvtID ref, D_Time now, D_Bool p, D_Bool f, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief �������Ƿ��ǲο�����
* @param[in] id �����¼ID
* @retval D_TRUE ��
* @retval D_FALSE ����
*/
D_Bool		d_dbase_is_ref_srv (D_DBSrvID id) D_FUNCPOSTFIT;

#ifdef D_SUPPORT_EEPROM
/** @brief ������ֵ��EEPROM��
* @param[in] table	���ݿ��ָ��
* @param[in] fid	������ID
* @param[in] rid	��¼��DID
* @retval �ɹ�����д������ݴ�С
* @retval ʧ�ܷ���D_ERR
*/
D_Result		d_dbase_eeprom_store_field (D_DBTable *table, D_ID fid, D_DBID rid) D_FUNCPOSTFIT;

/** @brief �������ݿ����ݵ�EEPROM��
* @param blk	���ݿ�ָ��
* @param offset	ƫ�Ƶ�ַ
* @param size	д�����ݵĴ�С
* @retval �ɹ�����д������ݴ�С
* @retval ʧ�ܷ���D_ERR
*/
D_Size			d_dbase_eeprom_store_data (D_DBBlock *blk, D_Size offset, D_Size size) D_FUNCPOSTFIT;

/** @brief ��EEPROM�ж�ȡ����
* @param[in] blk	���ݿ�ָ��
* @param[in] offset	ƫ�Ƶ�ַ
* @param[in] size	��ȡ�����ݴ�С
* @retval �ɹ����ض�ȡ���ݵĴ�С
* @retval ʧ�ܷ���D_ERR
*/
D_Size			d_dbase_eeprom_read_data (D_DBBlock *blk, D_Size offset, D_Size size) D_FUNCPOSTFIT;
#endif

#ifdef  __cplusplus
}
#endif

#endif
/*EOF*/
/**@}*/

