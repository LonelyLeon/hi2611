/**@defgroup db ���ݿⶨ��Ӧ��
*@{*/
/** @file
* @brief ���ݿⶨ��Ӧ��ģ��
* @author ��ΰ��
* @date 2013-04-25 ��ΰ��: �����ļ�
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



/** @brief ���ݿ�ָ���������
* @retval D_OK
*/
D_Result
d_dbase_factory_set(void) D_FUNCPOSTFIT;

/** @brief ���ҽ�Ŀ��¼���н�Ŀ��¼��Ƶ����
* @param[in] rset ��¼��
* @param[out] pos ���Ƶ���ŵĻ�����
* @retval D_OK ����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_dbase_program_chnum_in_rset(D_DBRecset *rset, D_S16 *pos) D_FUNCPOSTFIT;

/** @brief �Խ�Ŀ��¼���а��෽ʽ�������� 
* @param[in] rset ��Ҫ��������ļ�¼��
* @param[in] type ����ʽ
* @param[in] order ��һ�������ʽ��orderΪ0�����С��������Ϊ1����Ӵ�С����
			   ����ĸ����0�������ִ�Сд�Ҵ�С����1�������ִ�Сд�ҴӴ�С��2�������ִ�Сд�Ҵ�С����3�������ִ�Сд�ҴӴ�С��
* @param[in] rearrange ������Ƿ�ѽ�Ŀ������Ϊ��1��ʼ��TRUE���ǣ�FALSE����
* @retval D_OK ����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_dbase_program_sort(D_DBRecset *rset, D_DBProgramArrayType type, D_U8 order, D_Bool rearrange) D_FUNCPOSTFIT;

/** @brief �Խ�Ŀ��¼�����ƶ�
* @param[in] rset ��¼��ָ��
* @param[in] lastchpos �ƶ�ǰ��λ��
* @param[in] nextchpos �ƶ����λ��
* @retval D_OK ����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_dbase_program_move(D_DBRecset *rset, D_U16 lastchpos,D_U16 nextchpos) D_FUNCPOSTFIT;

/** @brief ����Ŀ���Ʋ��ҽ�Ŀ
* @param[in] src_rset ��ѯ�Ľ�Ŀ���ڵ������¼��
* @param[in] dst_rset ɸѡ���Ľ�Ŀ��ɵļ�¼��
* @param[in] str ������ַ���
* @retval D_OK ���ڷ��������Ľ�Ŀ
* @retval D_ERR �����ڷ��������Ľ�Ŀ
*/
D_Result d_dbase_find_program_by_name(D_DBRecset *src_rset, D_DBRecset *dst_rset, D_Char str[]);

/** @����ĳ��ts��Ϣ
* @param[in] id TS ID
* @param[in] info TS��Ϣָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_dbase_updata_ts_info(D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;
/** @brief ��TS���в���һ����¼
* @param[in] info TS��Ϣ
* @retval id TS ID
* @retval -1 ����ʧ��
*/
D_DBTSID p_dbase_insert_ts (D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��TS�����Ϣ
* @param[in] id TS��¼ ID
* @param[in] info TS��Ϣ��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result p_dbase_get_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��һ�����������Ϣ
* @param[in] id ����ID
* @param[in] info ������Ϣ
* @retval D_OK ��óɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result
p_dbase_get_srv_info(D_DBSrvID id, D_DBSrvInfo * info) D_FUNCPOSTFIT;


/** @brief �������м���һ����¼
* @param[in] info ������Ϣ
* @param[in] tmp ��ʱ��־
* @retval id ����ID
* @retval -1 ����ʧ��
*/
D_DBSrvID
p_dbase_insert_srv_ex(D_DBSrvInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief �������м���һ����¼*/
#define p_dbase_insert_srv(_i)	p_dbase_insert_srv_ex(_i, D_FALSE)

D_Result p_precast_program(D_U32 param) D_FUNCPOSTFIT;


/** @brief �ָ���������ʱ���Ԥ������*/
D_Result
d_dbase_add_default_data_dvbs(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
