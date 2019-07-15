/**@defgroup dbase ���ݿ�
*@{*/
/** @file
* @brief ���ݿ����ģ��
* @author ����
* @date 2005-6-17 ����: �����ļ�
	@date 2006-8-2 shanzs: 
		�޸�D_DBSrvInfo�ṹ
		����d_dbase_get_srvs_by_type_ex����
		����d_dbase_get_srvs_by_bouq_ex����
		����d_dbase_update_srv_skip����
* @date 2013-03-19 lc: ͳһƽ̨, ��������
	@date 2013-4-17 Liuwf: 
		�������ߡ��������ݿⲿ�֣�����֮ǰ�ĺ�����ͨ�����������Ƿ����
* @date 2013-04-22 lwf,sunzy: ͳһƽ̨, ��������
*/

#ifndef _D_DBASE_H_
#define _D_DBASE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFEnd.h"
#include "dEEPRom.h"
#include "dAV.h"


/* ��ʱ���屣���ֽڲ�����128B */
#define D_DB_MAX_RESERVED_LENGTH        (16)

typedef D_ID	D_DBID;
typedef D_DBID	D_DBNetID;
typedef D_DBID	D_DBTSID;
typedef D_DBID	D_DBSrvID;
typedef D_DBID	D_DBEvtID;
typedef D_DBID	D_DBSubID;
typedef D_DBID	D_DBBouqID;
typedef D_DBID	D_DBNVodID;
typedef D_DBID	D_DBSATID;
typedef D_DBID	D_DBAnteID;
typedef D_S16	D_DBChanNum;

#define D_DB_DEF_NET_ID	(0)

/** @brief ��������*/
typedef enum {
	D_DB_DATA_CA,	/**< CA�������*/
	D_DB_DATA_DB	/**< ���ݹ㲥�������*/
} D_DBDataType;

typedef struct {
	D_Char				name[D_DB_NETWORK_NAME_LEN];
	D_U16				network_id;
} D_DBNetInfo;

typedef D_FEndParam	D_DBTSParam;

typedef struct {
	D_DBTSParam	param;
	D_U8		db_net_id;
	D_U16				ts_id;
	D_U16				org_net_id;
	D_U8	      tuner_type;
	D_U8		db_sat_id;
	D_U8             ts_reserved[D_DB_MAX_RESERVED_LENGTH];
} D_DBTSInfo;

typedef enum {
	D_DB_SRV_TV,
	D_DB_SRV_RADIO,
	D_DB_SRV_NVOD_REF,
	D_DB_SRV_NVOD_SHIFTED,
	D_DB_SRV_DB,
	D_DB_SRV_DATA,
	D_DB_SRV_MOSAIC,
	D_DB_SRV_MOSAIC_ROOT,
	D_DB_SRV_TELETEXT,
	D_DB_SRV_FM,
	D_DB_SRV_ATV, /*ģ�����*/
	
	/* ֱ��������ҵ��*/
	D_DB_SRV_PUSHVOD,

    //...
    //...    
    
    /*��������ֻ���ڽӿڲ���*/
	D_DB_SRV_ACTION = 0x20,
	D_DB_SRV_ACTION_TV = (D_DB_SRV_ACTION << 1),
	D_DB_SRV_ACTION_RADIO = (D_DB_SRV_ACTION << 2),
	D_DB_SRV_ACTION_FM = (D_DB_SRV_ACTION << 3),
	D_DB_SRV_ACTION_ATV = (D_DB_SRV_ACTION << 4),
	D_DB_SRV_ACTION_ALL = D_DB_SRV_ACTION_TV | D_DB_SRV_ACTION_RADIO | D_DB_SRV_ACTION_FM | D_DB_SRV_ACTION_ATV,
} D_DBSrvType;

typedef struct {
	D_Char	name[D_DB_SERVICE_NAME_LEN];
	D_U8	srv_type;
	D_U8	aud_acc;		/*����*/
	D_Bool	favor0;
	D_Bool	favor1;
	D_Bool	favor2;
	D_Bool	favor3;
	D_Bool	favor4;
	D_Bool	favor5;
	D_Bool	favor6;
	D_Bool	favor7;

	D_Bool	lock;	
	D_Bool	skip;				/*���� added by shanzs@06/08/02*/
	D_Bool	ca_flag;		/*���ű��*/
	D_S8		volume;
	D_U8		aud_track;	/*����*/
	D_U16		srv_id;
	D_U16		pcr_pid;
	D_U16		vid_pid;
	D_VidCodecType vid_codec;
	D_U16		aud1_pid;
	D_AudCodecType aud1_codec;
	D_U16		aud2_pid;
	D_AudCodecType aud2_codec;
#ifdef D_DB_SRV_SUPPORT_4AUDIO
    	D_U16		aud3_pid;
	D_AudCodecType aud3_codec;
	D_U16		aud4_pid;
	D_AudCodecType aud4_codec;
#endif
	D_DBTSID		db_ts_id;
	D_S8	db_bouq_id;
	D_U8	sd_hd_flag;/*�߱����־*/
	D_DBChanNum	chan_num;
	D_U16	        chan_lcn;    
	D_U16 		pmt_pid;
       D_U64 db_bouq_mask; 
	D_U8  srv_reserved[D_DB_MAX_RESERVED_LENGTH];
} D_DBSrvInfo;

typedef struct {
	D_Char	name[D_DB_BOUQUET_NAME_LEN];
	D_U16		bouq_id;
} D_DBBouqInfo;

typedef enum {
    SINGLE,
    C_DOUBLE,
    KU_DOUBLE,
    MID_FRE
} D_DBLnbType;

typedef enum {
    DISEQC_NONE,
    DISEQC1_0,
    DISEQC1_1,
    DISEQC1_2,
    DISEQC1_3,
    DISEQC_USALS = DISEQC1_3,
    DISEQC2_0,
    DISEQC2_1,	
    DISEQC2_2,
    DISEQC2_3,	
} D_DBDiSEqCType;

typedef enum {
    PORT_OFF = 0,
#if defined(D_SYSTEM_HROS)
    PORT_NONE = 0,
#endif    
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_01 = PORT_A,
    PORT_02 = PORT_B,
    PORT_03 = PORT_C,
    PORT_04 = PORT_D,
    PORT_05 = PORT_E,	
    PORT_06 = PORT_F,
    PORT_07,
    PORT_08,
    PORT_09,
    PORT_10,
    PORT_11,
    PORT_12,
    PORT_13,
    PORT_14,
    PORT_15,
    PORT_16,
    PORT_OTHERS,
} D_DBDiSEqCPort;

typedef enum {
    OFF_22K,
    ON_22K,
    AUTO_22K
} D_DB22KTone;

typedef enum {
    OFF_12V,
    ON_12V,
    AUTO_12V
} D_DBDiSEqC_12V;

typedef struct {
	D_Bool	lnb_power;
	D_U8	lnb_type;
	D_U16	freq1;	
	D_U16	freq2;
} D_DBAnteInfo;

typedef struct {
	D_U8	antenna_slot;
	D_S16	longitude;	/*���Ǿ���(-18000 ~ 18000) ��Ϊ������λС��*/
	D_Char	sate_name[D_DB_SATE_NAME_LEN];
	D_U8	diseqc_pos;
	D_U8	sate_no;
	D_U8	diseqc_type;
	D_U8	diseqc_port;
	D_Bool	diseqc_12v;
	D_U8	 diseqc_22k;  
       D_Bool   selected;
} D_DBSateInfo;

#ifdef D_DB_SRV_SUPPORT_4AUDIO
/** @brief ȡ����ƵPID*/
#define D_DB_GET_SRV_AUD(_s) \
                (((_s)->aud_acc == 0) ? (_s)->aud1_pid : \
                                ((_s)->aud_acc == 1 && (_s)->aud2_pid !=D_INVALID_PID_VALUE) ? (_s)->aud2_pid : \
                                ((_s)->aud_acc == 2 && (_s)->aud3_pid !=D_INVALID_PID_VALUE) ? (_s)->aud3_pid : \
                                ((_s)->aud_acc == 3 && (_s)->aud4_pid !=D_INVALID_PID_VALUE) ? (_s)->aud4_pid : (_s)->aud1_pid)
                
#define D_DB_GET_SRV_AUD_CODEC(_s) \
                (((_s)->aud_acc == 0) ? (_s)->aud1_codec : \
                                ((_s)->aud_acc == 1 && (_s)->aud2_pid !=D_INVALID_PID_VALUE) ? (_s)->aud2_codec : \
                                ((_s)->aud_acc == 2 && (_s)->aud3_pid !=D_INVALID_PID_VALUE) ? (_s)->aud3_codec : \
                                ((_s)->aud_acc == 3 && (_s)->aud4_pid !=D_INVALID_PID_VALUE) ? (_s)->aud4_codec : (_s)->aud1_codec)

#else
/** @brief ȡ����ƵPID*/
#define D_DB_GET_SRV_AUD(_s)\
		((_s)->aud_acc ?\
				(((_s)->aud2_pid==D_INVALID_PID_VALUE)?(_s)->aud1_pid:(_s)->aud2_pid) :\
				(((_s)->aud1_pid==D_INVALID_PID_VALUE)?(_s)->aud2_pid:(_s)->aud1_pid))

/** @brief ȡ����Ƶ��������*/
#define D_DB_GET_SRV_AUD_CODEC(_s)\
		((_s)->aud_acc ?\
				(((_s)->aud2_pid==D_INVALID_PID_VALUE)?(_s)->aud1_codec:(_s)->aud2_codec) :\
				(((_s)->aud1_pid==D_INVALID_PID_VALUE)?(_s)->aud2_codec:(_s)->aud1_codec))
#endif

#define D_DB_TS_INFO_INIT(_t)\
		D_MACRO_BEGIN\
			memset(&((_t)->param), 0, sizeof((_t)->param));\
			(_t)->db_net_id = (D_U8)(-1);\
			(_t)->ts_id = 0xFFFF;\
			(_t)->org_net_id = 0xFFFF;\
			(_t)->db_sat_id = (D_U8)(-1);\
			(_t)->tuner_type = 0;\
			memset((_t)->ts_reserved, 0, sizeof((_t)->ts_reserved));\
		D_MACRO_END

#define D_DB_BOUQ_INIT(_b)\
		D_MACRO_BEGIN\
			(_b)->name[0] = '\0';\
			(_b)->bouq_id = 0xFFFF;\
		D_MACRO_END

#ifdef D_DB_SRV_SUPPORT_4AUDIO		
#define D_DB_SRV_INFO_INIT(_s)\
		D_MACRO_BEGIN\
			(_s)->name[0] = '\0';\
			(_s)->srv_type = (D_U8)D_DB_SRV_TV;\
			(_s)->aud_acc=0;\
			(_s)->favor0=D_FALSE;\
			(_s)->favor1=D_FALSE;\
			(_s)->favor2=D_FALSE;\
			(_s)->favor3=D_FALSE;\
			(_s)->favor4=D_FALSE;\
			(_s)->favor5=D_FALSE;\
			(_s)->favor6=D_FALSE;\
			(_s)->favor7=D_FALSE;\
			(_s)->lock=D_FALSE;\
			(_s)->skip=D_FALSE;\
			(_s)->ca_flag = D_FALSE;\
			(_s)->volume=0;\
			(_s)->aud_track = (D_U8)D_AUD_STEREO;\
			(_s)->srv_id=0;\
			(_s)->pcr_pid=D_INVALID_PID_VALUE;\
			(_s)->vid_pid=D_INVALID_PID_VALUE;\
			(_s)->vid_codec=D_VID_CODEC_MAX;\
			(_s)->aud1_pid=D_INVALID_PID_VALUE;\
			(_s)->aud1_codec=D_AUD_CODEC_MAX;\
			(_s)->aud2_pid=D_INVALID_PID_VALUE;\
			(_s)->aud2_codec=D_AUD_CODEC_MAX;\
			(_s)->aud3_pid=D_INVALID_PID_VALUE;\
			(_s)->aud3_codec=D_AUD_CODEC_MAX;\
			(_s)->aud4_pid=D_INVALID_PID_VALUE;\
			(_s)->aud4_codec=D_AUD_CODEC_MAX;\
			(_s)->db_ts_id=-1;\
			(_s)->db_bouq_id=-1;\
			(_s)->sd_hd_flag = 0;\
			(_s)->chan_num=-1;\
			(_s)->chan_lcn = (D_U16)(-1);\
			(_s)->pmt_pid = D_INVALID_PID_VALUE;\
			(_s)->db_bouq_mask = 0;\
			memset((_s)->srv_reserved, 0, sizeof((_s)->srv_reserved));\
		D_MACRO_END
#else
#define D_DB_SRV_INFO_INIT(_s)\
		D_MACRO_BEGIN\
			(_s)->name[0] = '\0';\
			(_s)->srv_type = (D_U8)D_DB_SRV_TV;\
			(_s)->aud_acc=0;\
			(_s)->favor0=D_FALSE;\
			(_s)->favor1=D_FALSE;\
			(_s)->favor2=D_FALSE;\
			(_s)->favor3=D_FALSE;\
			(_s)->favor4=D_FALSE;\
			(_s)->favor5=D_FALSE;\
			(_s)->favor6=D_FALSE;\
			(_s)->favor7=D_FALSE;\
			(_s)->lock=D_FALSE;\
			(_s)->skip=D_FALSE;\
			(_s)->ca_flag = D_FALSE;\
			(_s)->volume=0;\
			(_s)->aud_track = (D_U8)D_AUD_STEREO;\
			(_s)->srv_id=0;\
			(_s)->pcr_pid=D_INVALID_PID_VALUE;\
			(_s)->vid_pid=D_INVALID_PID_VALUE;\
			(_s)->vid_codec=D_VID_CODEC_MAX;\
			(_s)->aud1_pid=D_INVALID_PID_VALUE;\
			(_s)->aud1_codec=D_AUD_CODEC_MAX;\
			(_s)->aud2_pid=D_INVALID_PID_VALUE;\
			(_s)->aud2_codec=D_AUD_CODEC_MAX;\
			(_s)->db_ts_id=-1;\
			(_s)->db_bouq_id=-1;\
			(_s)->sd_hd_flag = 0;\
			(_s)->chan_num=-1;\
			(_s)->chan_lcn = (D_U16)(-1);\
			(_s)->pmt_pid = D_INVALID_PID_VALUE;\
			(_s)->db_bouq_mask = 0;\
			memset((_s)->srv_reserved, 0, sizeof((_s)->srv_reserved));\
                D_MACRO_END     
#endif	
#define D_DB_ANTE_INFO_INIT(_a)\
		D_MACRO_BEGIN\
			(_a)->lnb_power=0;\
			(_a)->lnb_type=SINGLE;\
			(_a)->freq1=0;\
			(_a)->freq2=0;\
		D_MACRO_END
		
#define D_DB_SAT_INFO_INIT(_s)\
		D_MACRO_BEGIN\
			(_s)->antenna_slot=(D_U8)(-1);\
			(_s)->longitude=0;\
			(_s)->sate_name[0]=0;\
			(_s)->diseqc_pos=0;\
			(_s)->sate_no=1;\
			(_s)->diseqc_type=DISEQC1_0;\
			(_s)->diseqc_port=PORT_OFF;\
			(_s)->diseqc_12v=OFF_12V;\
			(_s)->diseqc_22k=OFF_22K;\
			(_s)->selected = D_FALSE;\
		D_MACRO_END

typedef struct {
	D_Bool	is_shifted;
	D_Char	name[D_DB_EVENT_NAME_LEN];
	D_Time	start;
	D_Time	duration;
	D_DBSrvID	db_srv_id;
	D_U16		ref_evt_id;
	D_U16		evt_id;
	D_U8		type;
	D_U8    rating;
	D_Bool	subscribe;
} D_DBEvtInfo;

typedef struct {
	D_Char	name[D_DB_EVENT_NAME_LEN];
	D_Time	start;
	D_Time	duration;
	D_DBSrvID	db_srv_id;
	D_U16		evt_id;
	D_U8		sub_modu;
	D_U8		timer_type;
} D_DBSubInfo;

typedef struct {
	D_Size	 size;
	D_Size	 cnt;
	D_ID		*ids;
} D_DBRecset;

typedef D_Handle	D_HDBTable;

/** @brief ȡ��¼���ڵļ�¼��Ŀ*/
#define d_dbase_rset_cnt(_r)	((_r)->cnt)

/** @brief ȡ��¼��ָ����¼ID*/
#define d_dbase_rset_get(_r,_i)	((_r)->ids[_i])

/** @brief table id��dbase���table�����Ӧ, ���ܸ��� */
#define D_DBASE_ANTE_TAB_ID         0
#define D_DBASE_SATE_TAB_ID         1
#define D_DBASE_NET_TAB_ID          2
#define D_DBASE_TS_TAB_ID           3
#define D_DBASE_SRV_TAB_ID          4
#define D_DBASE_SUB_TAB_ID          5
#define D_DBASE_BOUQ_TAB_ID         6
#define D_DBASE_EVT_TAB_ID          7
#define D_DBASE_MAX_TAB_ID          8

#define D_DBASE_ANTE_TAB_VALID      (1 << D_DBASE_ANTE_TAB_ID)
#define D_DBASE_SATE_TAB_VALID      (1 << D_DBASE_SATE_TAB_ID)
#define D_DBASE_NET_TAB_VALID       (1 << D_DBASE_NET_TAB_ID)
#define D_DBASE_TS_TAB_VALID        (1 << D_DBASE_TS_TAB_ID)
#define D_DBASE_SRV_TAB_VALID       (1 << D_DBASE_SRV_TAB_ID)
#define D_DBASE_SUB_TAB_VALID       (1 << D_DBASE_SUB_TAB_ID)
#define D_DBASE_EVT_TAB_VALID       (1 << D_DBASE_EVT_TAB_ID)
#define D_DBASE_BOUQ_TAB_VALID      (1 << D_DBASE_BOUQ_TAB_ID)

/** @brief �����ýṹ */
typedef struct
{
    D_U32 max_cnt; /**< ������¼�� */
    D_U32 store_cnt; /**< ��洢��¼�� */
    D_ID part_id; /* ��洢����id */
    D_U8 reserved_field_size; /* �������С,0������ */
}D_DBTabInfo;

/** @brief ���ݿ��ʼ���ṹ */
typedef struct
{
    D_U16 table_valid_flag; /**< ����Ч��־ */
    D_DBTabInfo tab_info[D_DBASE_MAX_TAB_ID]; /**< ���ʼ������ */
    D_U32 var_string_cnt; /**< var_string���� */
    D_U16 config_blk_size; /**< config block��С, ������64K */
    D_U16 data_blk_size; /**< ������Ҫ�������ݿ��С, ����ռһ������, 0�����洢 */
}D_DBOpenParam;

/************************************************dDBase.c**********************************************************************/
/** @brief ��ʼ��ȫ�����ݿ�
* @param[in] param ���ݿ��ʼ���ṹָ��
* @retval D_OK	�������ݿ���ȷ
* @retval D_ERR_NO_SPACE	�����ڴ�ռ����
* @retval D_ERR	���ݿ��е�������Ч
*/
D_Result	d_dbase_open (D_DBOpenParam *param) D_FUNCPOSTFIT;

/** @brief �ر�ȫ�����ݿ�*/
D_Result	d_dbase_close (void) D_FUNCPOSTFIT;

/** @brief �����ݿ��иĶ����ݱ��浽Flash��
* @param[in] sync   �Ƿ�ͬ��ˢ��
* @retval D_OK
*/
D_Result d_dbase_flush_ex(D_Bool sync) D_FUNCPOSTFIT;

/** @brief �����ݿ��иĶ�����ͬ�����浽Flash��*/
#define d_dbase_flush()           d_dbase_flush_ex(D_TRUE)

/** @brief �����ݿ��иĶ������첽���浽Flash��*/
#define d_dbase_async_flush()     d_dbase_flush_ex(D_FALSE)

/** @brief ������ݿ��Ƿ���Ҫ����
* @retval D_TRUE ��Ҫˢ��
* @retval D_FALSE ����Ҫˢ��
*/
D_Bool		d_dbase_need_flush (void) D_FUNCPOSTFIT;

/** @brief ��¼����ʼ��
* @param[out] set	��¼��ָ��
* @param[in] max	��¼�������ɵ�����¼��Ŀ
* @param[in] buf	ID��Ż�����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_rset_init (D_DBRecset *set, D_U16 max, D_ID *buf) D_FUNCPOSTFIT;

/** @brief ��¼���ռ��ͷ�
* @param[out] set	��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_rset_deinit (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ��ռ�¼���ڵļ�¼
* @param[out] set	��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_rset_empty (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ���¼�������Ӽ�¼
* @param[out] set	��¼��ָ��
* @param[in] id		���ӵļ�¼ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_rset_add (D_DBRecset *set, D_ID id) D_FUNCPOSTFIT;

/** @brief �Լ�¼���ڼ�¼����
* @param[out] set	��¼��ָ��
* @param[in] func	�ȽϺ���
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_rset_sort (D_DBRecset *set, D_CmpFunc func) D_FUNCPOSTFIT;

/** @brief ����buf���ݵ�flash��
* @param[in] part_id	flash����ID
* @param[in] offset	ƫ�Ƶ�ַ
* @param[in] szie	д������ݴ�С
* @param[in] buf	���ݻ�����ָ��
* @retval �ɹ�����д������ݴ�С
* @retval ʧ�ܷ���D_ERR
*/
D_Size    d_dbase_nvram_store_data (D_ID part_id, D_U32 offset, D_U32 size, D_U8 *buf) D_FUNCPOSTFIT;

/** @brief ��flash���ݵ�buf��
* @param[in] part_id	flash����ID
* @param[in] offset	ƫ�Ƶ�ַ
* @param[in] szie	��ȡ�����ݴ�С
* @param[out] buf	���ݻ�����ָ��
* @retval �ɹ����ض�ȡ�����ݴ�С
* @retval ʧ�ܷ���D_ERR
*/
D_Size    d_dbase_nvram_read_data (D_ID part_id, D_U32 offset, D_U32 size, D_U8 *buf) D_FUNCPOSTFIT;

/** @brief ���flash��¼������
* @retval rset_en ��¼������ֵ����¼������ 1, ��¼���ر� 0
*/
D_Result   d_dbase_get_rset_en(void)D_FUNCPOSTFIT;

/** @brief ����flash��¼������
* @param[in] en	��¼������ֵ��0���رգ�1����
*/
void  d_dbase_set_rset_en(D_U8 en)D_FUNCPOSTFIT;

/** @brief ����flash��¼��*/
void 
d_dbase_erase_flash_record(void)D_FUNCPOSTFIT;

#ifdef D_SUPPORT_EEPROM
/** @brief ��EEPROM*/
D_Result	d_dbase_open_eeprom (void) D_FUNCPOSTFIT;

/** @brief ����EEPROM����*/
D_Result	d_dbase_load_eeprom (void) D_FUNCPOSTFIT;

/** @brief ���ݿ��ȡeeprom
* @param[out] dat	����bufferָ��
* @param[in] size	��ȡ�����ݴ�С
* @retval �ɹ����ض�ȡ�����ݴ�С
* @retval ʧ�ܷ��ظ�ֵ
*/
D_Size	d_dbase_read_eeprom (D_U8 *dat, D_Size size) D_FUNCPOSTFIT;

/** @brief ���ݿ�дeeprom
* @param[in] dat	����bufferָ��
* @param[in] size	д������ݴ�С
* @retval �ɹ�����д������ݴ�С
* @retval ʧ�ܷ��ظ�ֵ
*/
D_Size d_dbase_write_eeprom (D_U8 *dat, D_Size size) D_FUNCPOSTFIT;

#endif

/************************************************end**********************************************************************/

/************************************************dAnteTable.c**********************************************************************/
/** @brief ������߱�
* @retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_dbase_clear_ante (void) D_FUNCPOSTFIT;

/** @brief ����һ��������Ϣ�������ڻָ���������ʱ
* @param[in] info	���������Ϣ�����ݻ�����ָ��
* @return �ɹ���������ID,ʧ�ܷ���-1
*/
D_DBTSID d_dbase_insert_ante (D_DBAnteInfo *info) D_FUNCPOSTFIT;

/** @brief ��ȡ������Ϣ
* @param[in] id	���߼�¼ID
* @param[in] info	���������Ϣ�����ݻ�����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_ante_info (D_DBAnteID id, D_DBAnteInfo *info) D_FUNCPOSTFIT;

/** @brief ��ȡ���������б�
* @param[out] rset ���߼�¼��ָ��
* @retval D_OK ��ȡ�ɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result  d_dbase_get_antes (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ����������Ϣ
* @param[in] id ���߼�¼ID
* @param[in] anteinfo ���������Ϣ�����ݻ�����ָ��
* @param[in] dirty �Ƿ񽫸���д��flash�У�TRUE��д��FALSE����д
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_ante_param (D_DBAnteID id, D_DBAnteInfo * anteinfo, D_Bool dirty) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dSateTable.c**********************************************************************/
/** @brief ������Ǳ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_dbase_clear_sat (void) D_FUNCPOSTFIT;

/** @brief ����һ�����Ǽ�¼
* @param[in] info	���������Ϣ�����ݻ�����ָ��
* @return �ɹ���������ID,ʧ�ܷ���-1
*/
D_DBSATID d_dbase_insert_sat_ex (D_DBSateInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief ɾ��һ�����Ǽ�¼
* @param[in] id	���Ǽ�¼��ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_dbase_delete_sat (D_DBSATID id) D_FUNCPOSTFIT;

/** @brief ��ȡ������Ϣ
* @param[in] id	���Ǽ�¼ID
* @param[in] info	���������Ϣ�����ݻ�����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_sat_info (D_DBSATID id, D_DBSateInfo *info) D_FUNCPOSTFIT;

/** @brief ��ȡ���������б�
* @param[out] rset ���Ǽ�¼��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result  d_dbase_get_sates (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�������߼��ŵ�����DID��ע��һ��Ҫ�Է��صĽ�������жϣ�-1Ϊ��Ч��ID������ֱ��ʹ�÷���ֵ
* @param[in] num ���Ǻ�
* @retval �ɹ��������Ǽ�¼ID
* @retval ʧ�ܷ���-1
*/
D_DBSATID
d_dbase_get_sat_did_by_num (D_S16 num) D_FUNCPOSTFIT;

/** @brief ����������Ϣ
* @param[in] id ���Ǽ�¼ID
* @param[in] satinfo ���������Ϣ�����ݻ�����ָ��
* @param dirty �Ƿ񽫸���д��flash�У�TRUE��д��FALSE����д
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_param (D_DBSATID id, D_DBSateInfo * satinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief ȡ�������б�
* @param rset ��¼��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_sates_selected (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief �޸����ǵ�ѡ��״̬
* @param id ���Ǽ�¼ID
* @param sel �Ƿ�ѡ��
* @retval �޸ĳɹ�����D_OK
* @retval �޸�ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_selected (D_DBSATID id, D_Bool sel) D_FUNCPOSTFIT;

/** @brief ȡ��һ�����е����Ǻ�
* @retval -1 ��ȡʧ��; num ��ȡ�ɹ�
*/
D_S16
d_dbase_get_free_sate_num (void) D_FUNCPOSTFIT;

/** @brief �޸����ǵ�����λ�ú�
* @param id ���Ǽ�¼ID
* @param pos ����λ�ú�
* @retval �޸ĳɹ�����D_OK
* @retval �޸�ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_diseqc_pos (D_DBSATID id, D_U8 pos) D_FUNCPOSTFIT;


/** @brief �޸����ǵ�DisEqC����
* @param id ���Ǽ�¼ID
* @param type ����DisEqc����
* @retval �޸ĳɹ�����D_OK
* @retval �޸�ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_diseqc_type (D_DBSATID id, D_U8 type) D_FUNCPOSTFIT;

/** @brief �޸����ǵ�DisEqC�˿�
* @param id ���Ǽ�¼ID
* @param port ����DisEqc�˿�
* @retval �޸ĳɹ�����D_OK
* @retval �޸�ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_diseqc_port (D_DBSATID id, D_U8 port) D_FUNCPOSTFIT;

/** @brief �޸����ǵ�DisEqC 22K����
* @param id ���Ǽ�¼ID
* @param diseqc12v ����diseqc22K����
* @retval �޸ĳɹ�����D_OK
* @retval �޸�ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_sat_diseqc_22k (D_DBSATID id, D_U8 diseqc22k) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dNetTable.c**********************************************************************/
/** @brief ��������*/
D_Result	d_dbase_clear_net (void) D_FUNCPOSTFIT;

/** @brief ��������м���һ����¼
* @param[in] info	������Ϣָ��
* @retval �ɹ���������ID
* @retval ʧ�ܷ���-1
*/
D_DBNetID	d_dbase_insert_net (D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @brief ɾ��һ����¼
* @param[in] id	�����¼ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_net (D_DBNetID id) D_FUNCPOSTFIT;

/** @brief ȡ��һ�����������Ϣ
* @param[in] id	�����¼ID
* @param[in] info	������Ϣָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_net_info (D_DBNetID id, D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ�����ݿ��ڵ�ȫ�������б�
* @param[out] rset	�����¼��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_nets (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ����������Ϣ
* @param[in] id �����¼ID
* @param[in] netinfo ���������Ϣ�����ݻ�����ָ��
* @param[in] dirty �Ƿ񽫸���д��flash�У�TRUE��д��FALSE����д
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_dbase_update_net_param (D_DBNetID id, D_DBNetInfo * netinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief �������Ǿ��Ȼ�ȡ���������Ϣ
* @param longitude ���Ǿ���
* @param info ������Ϣָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result
d_dbase_get_sat_info_by_longitude(D_S16 longitude, D_DBSateInfo *info) D_FUNCPOSTFIT;

/** @brief �������Ǿ��Ȼ�ȡ����id
* @param longitude ���Ǿ���
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_ID
d_dbase_get_sat_id_by_longitude(D_S16 longitude) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dTSTable.c**********************************************************************/
/** @brief ���TS��*/
D_Result	d_dbase_clear_ts (void) D_FUNCPOSTFIT;
D_Result d_dbase_clear_ts_ex (D_Bool tmp) D_FUNCPOSTFIT;

/** @brief ��TS���в���һ����¼
* @param[in] info TS��Ϣ
* @param[in] tmp ��ʱ��־
* @retval id TS ID
* @retval -1 ����ʧ��
*/
D_DBTSID	d_dbase_insert_ts_ex (D_DBTSInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief ��TS���в���һ����¼*/
#define d_dbase_insert_ts(_i)	d_dbase_insert_ts_ex(_i,D_FALSE)

/** @brief ��TS���в���һ����ʱ��¼*/
#define d_dbase_insert_temp_ts(_i)	d_dbase_insert_ts_ex(_i,D_TRUE)

/** @brief ɾ��TS���е�һ����¼
* @param[in] id TS��¼ ID
* @retval ɾ���ɹ�����D_OK
* @retval ɾ��ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_ts (D_DBTSID id) D_FUNCPOSTFIT;

/** @brief ɾ��ָ��ǰ�����͵�ȫ��ת���� 
* @param[in] type ǰ������
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_delete_ts_by_type (D_FEndType type) D_FUNCPOSTFIT;

/** @brief ���Ts��¼��Ч��*/
D_Bool d_dbase_check_ts_valid (D_DBTSID id) D_FUNCPOSTFIT;

/** @brief ȡ��TS�����Ϣ
* @param[in] id TS��¼ ID
* @param[in] info TS��Ϣ��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��TS�б�
* @param[out] rset ��¼��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_tses (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ȡ�ö�Ӧ�����TS�б�
* @param[in] net_id ����ID
* @param[out] rset ��¼��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_tses_by_net (D_DBNetID net_id, D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��Ƶ�������TS��¼
* @param[in] db_net_id ����ID
* @param[in] type ǰ����������
* @param[in] param TS����
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBTSID	d_dbase_get_ts_by_param (D_DBNetID db_net_id, D_FEndType type, D_DBTSParam *param) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��Ƶ�������TS��¼
* @param[in] freq ��Ƶ��
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBTSID
d_dbase_get_ts_by_main_freq (D_FEndFreq freq) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��Ƶ�������TS��¼
* @param[in] db_sat_id ����ID
* @param[in] type ǰ����������
* @param[in] param TS����
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBTSID
d_dbase_get_ts_by_param_ex (D_DBNetID db_sat_id, D_FEndType type, D_DBTSParam *param) D_FUNCPOSTFIT;


/** @brief ȡ��ָ��TS ID��TS��¼
* @param[in] db_net_id ����ID
* @param[in] ts_id TS ID
* @param[in] org_net_id ԭʼ����ID
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBTSID	d_dbase_get_ts_by_id (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id) D_FUNCPOSTFIT;
D_DBTSID	d_dbase_get_ts_by_id_new (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id,D_U16 srv_id) D_FUNCPOSTFIT;

D_DBTSID    d_dbase_get_ts_by_id_ex (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_FEndType fendtype) D_FUNCPOSTFIT;
D_DBTSID    d_dbase_get_dbtsid_by_tsid (D_U16 ts_id) D_FUNCPOSTFIT;
/** @brief ɾ��ָ�������ȫ��TS��
* @param[in] db_net_id ����ID
* @retval ɾ���ɹ�����D_OK
* @retval ɾ��ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_tses_of_net (D_DBNetID db_net_id) D_FUNCPOSTFIT;

/** @brief ɾ��ָ�������ȫ���¼�
* @param[in] db_net_id ����ID
* @retval ɾ���ɹ�����D_OK
* @retval ɾ��ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_evts_of_net (D_DBNetID db_net_id) D_FUNCPOSTFIT;

/** @brief ���ҵ�ǰת�������� added by shulh 20090714
* @retval ת��������
*/
D_U16 d_dbase_get_ts_total_num (void) D_FUNCPOSTFIT;

/** @brief ������ͬ��ts��Ϣ
* @param[in] info TS��Ϣָ��
* @param[in] type ǰ����������
* @retval ����ͬ�ķ��ؼ�¼ID
* @retval ����ͬ�ķ���-1
*/
D_DBTSID d_dbase_get_same_ts_num (D_DBTSInfo *info,  D_FEndType type) D_FUNCPOSTFIT;


/** @brief �趨Ƶ���������ƫ�Χ��
��DVBS���̣�äɨʱ����Ƿ�����ͬ��TS
* @param[in] freq_range Ƶ�ʷ�Χ
* @param[in] baud_range �����ʷ�Χ
* @retval ��ͬ����D_OK
* @retval ��ͬ����D_ERR
*/
D_Result
d_dbase_set_dvbs_freq_baud_range(D_FEndFreq freq_range, D_FEndBaud baud_range) D_FUNCPOSTFIT;

/** @brief ��DVBS���̣�äɨʱ����Ƿ�����ͬ��TS
* @param[in] p1 TS1ָ��
* @param[in] p2 TS2ָ��
* @retval ��ͬ����D_OK
* @retval ��ͬ����D_ERR
*/
D_Result
d_dbase_check_ts_dvbs(D_FEndParam *p1, D_FEndParam *p2) D_FUNCPOSTFIT;

/** @brief ����DVBS��������ͬ��ת������һ������äɨʱ
* @param[in] info	���TS��Ϣ�����ݻ�����ָ��
* @param[in] type	ǰ����̨����
* @return �ɹ�����TS��¼��ID,ʧ�ܷ���-1
*/
D_DBTSID d_dbase_get_same_ts_num_dvbs (D_DBTSInfo *info, D_FEndType type) D_FUNCPOSTFIT;

/** @�ж�Ƶ���Ƿ�����ĳ����
* @param[in] db_sat_id ���� ID
* @param[in] db_ts_id  TS id
* @retval ���ڷ���D_TRUE�� �����ڷ���D_FALSE
*/
D_Bool 
d_dbase_check_ts_in_sat(D_DBSATID db_sat_id, D_DBTSID db_ts_id)D_FUNCPOSTFIT;

/** @brief ɾ�������µ�ת����
* @param[in] db_sat_id	���Ǽ�¼��ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_delete_ts_of_sat(D_DBSATID db_sat_id) D_FUNCPOSTFIT;

/** @brief ��ȡ�����µ�ת����
* @param[out] set	���TS ID�ļ�¼��ָ��
* @param[in] id	���Ǽ�¼ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_ts_by_sat (D_DBRecset *set, D_DBSATID id) D_FUNCPOSTFIT;

/** @brief ����TS��Ϣ
* @param[in] id TS��¼ID
* @param[in] tsinfo ���TS��Ϣ�����ݻ�����ָ��
* @param[in] dirty �Ƿ񽫸���д��flash�У�TRUE��д��FALSE����д
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result  d_dbase_update_ts_param (D_DBTSID id, D_DBTSInfo * tsinfo, D_Bool dirty) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dSrvTable.c**********************************************************************/
/** @brief ��շ����*/
D_Result d_dbase_clear_srv (void) D_FUNCPOSTFIT;
D_Result d_dbase_clear_srv_ex (D_Bool tmp) D_FUNCPOSTFIT;

/** @brief ���ָ�����͵����з���*/
D_Result d_dbase_clear_srv_by_type (D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief �������м���һ����¼
* @param[in] info	������Ϣ
* @param[in] tmp ��ʱ��־
* @retval id ����ID
* @retval -1 ����ʧ��
*/
D_DBSrvID	d_dbase_insert_srv_ex (D_DBSrvInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief �������м���һ����¼*/
#define d_dbase_insert_srv(_i)	d_dbase_insert_srv_ex(_i, D_FALSE)

/** @brief �������м���һ����ʱ��¼*/
#define d_dbase_insert_temp_srv(_i)	d_dbase_insert_srv_ex(_i, D_TRUE)

/** @brief ɾ��һ����¼
* @param[in] id ����ID
* @retval D_OK ɾ���ɹ�
* @retval D_ERR ɾ��ʧ��
*/
D_Result	d_dbase_delete_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief ���ҵ���¼��Ч��*/
D_Bool d_dbase_check_srv_valid (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����͵ķ�������
* @param[in] all_flag �Ƿ�ȡȫ��ҵ������
* @param[in] type ��������(all_flagΪD_FALSEʱ��Ч)
* @retval ��������
*/
D_U32 d_dbase_get_srvs_cnt (D_Bool all_flag, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief ȡ��һ�����������Ϣ
* @param[in] id ����ID
* @param[in] info ������Ϣ
* @retval D_OK ��óɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result	d_dbase_get_srv_info (D_DBSrvID id, D_DBSrvInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��service id�ķ��� @added by qiny 15/09/14
* @param[out] set ��¼��
* @param[in]  service_id service_id
* @retval  D_OK ��ȡ�ɹ�
* @retval  D_ERR ��ȡʧ��
*/
D_Result
d_dbase_get_srvs_by_srvid (D_DBRecset *set, D_U16 service_id) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����͵ķ���
* @param[out] rset ��¼��
* @param[in] type ��������
* @param[in] favor �Ƿ��ȡϲ����Ŀ��TRUE���ǣ�FALSE����
* @param[in] fav_type ϲ�����ͣ���ȡ�������͵�ϲ���б��ò���ֻ����favor��ΪTRUEʱ��Ч
* @retval D_OK ��óɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result	d_dbase_get_srvs_by_type (D_DBRecset *set, D_DBSrvType type, D_Bool favor, D_U8 fav_type) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����͵ķ��� added by shanzs@06/08/04
* @param[out] set ��¼��
* @param[in] skip ������־
* @param[in] type ��������
* @param[in] favor �Ƿ��ȡϲ����Ŀ��TRUE���ǣ�FALSE����
* @param[in] fav_type ϲ�����ͣ���ȡ�������͵�ϲ���б��ò���ֻ����favor��ΪTRUEʱ��Ч
* @retval D_OK ��óɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result	d_dbase_get_srvs_by_type_ex (D_DBRecset *set, D_Bool skip, D_DBSrvType type, D_Bool favor, D_U8 fav_type) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��Ƶ���ŵķ���ID
* @param[in] num Ƶ����
* @param[in] type ��������
* @retval id ��¼ID
* @retval -1 ��ȡʧ��
*/
D_DBSrvID	d_dbase_get_srv_by_num (D_S16 num, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief ����service idȡ�÷���
* @param[in] db_ts_id TS���¼ID
* @param[in] srv_id ����ID
* @retval id ��¼ID
* @retval -1 ��ȡʧ��
*/
D_DBSrvID	d_dbase_get_srv_by_id (D_DBTSID db_ts_id, D_U16 srv_id) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��PID�ķ���
* @param[in] db_ts_id TS���¼ID
* @param[in] pid ��ĿPID
* @retval id ��¼ID
* @retval -1 ��ȡʧ��
*/
D_DBSrvID	d_dbase_get_srv_by_pid (D_DBTSID db_ts_id, D_U16 pid) D_FUNCPOSTFIT;

/** @brief ȡ��ָ��PID�ķ���
* @param[in] db_ts_id TS���¼ID,  (-1ʱ���Ƚ�)
* @param[in] vpid ��Ŀ��ƵPID
* @param[in] apid ��Ŀ��ƵPID
* @param[in] pcrpid ��ĿPCR PID
* @retval id ��¼ID
* @retval -1 ��ȡʧ��
*/
D_DBSrvID
d_dbase_get_srv_by_pids (D_DBTSID db_ts_id, D_U16 vpid, D_U16 apid, D_U16 pcrpid) D_FUNCPOSTFIT;


/** @brief ȡ��һ�����е�Ƶ����
* @param[in] type ��������
* @retval num Ƶ����
* @retval -1 ��ȡʧ��
*/
D_S16	    d_dbase_get_free_chan_num (D_DBSrvType type) D_FUNCPOSTFIT;
D_S16		d_dbase_get_free_chan_num_ex (D_DBSrvType srvtype, D_FEndType ftype) D_FUNCPOSTFIT;

/** @brief ��һ����ʼƵ���ſ�ʼ������һ�����е�Ƶ����
* @param[in] type ��������
* @retval[in] num ��ʼƵ����
* @retval -1 ��ȡʧ��
*/
D_S16 d_dbase_get_free_chan_num_from (D_DBSrvType type, D_S16 start_num) D_FUNCPOSTFIT;
/** @brief ��һ����ʼƵ���ſ�ʼ��ǰ��������һ�����е�Ƶ����
* @param[in] type ��������
* @retval[in] num ��ʼƵ����
* @retval[in] dir 0Ϊ���1Ϊ��ǰ
* @retval -1 ��ȡʧ��
*/
D_S16
d_dbase_get_free_chan_num_from_ex (D_DBSrvType type, D_S16 start_num, D_U8 dir) D_FUNCPOSTFIT;

/** @brief ������һ�����ڵ�Ƶ����  
* @param[in] start ��ǰƵ����
* @param[in] srvtype ��������
* @param[in] ltob ���ҷ���(true����,false����)
* @param[in] favor ϲ����־
* @retval num Ƶ����
* @retval -1 ��ȡʧ��
*/
D_S16		d_dbase_get_next_chan_num (D_S16 num, D_DBSrvType type, D_Bool ltob, D_Bool favor) D_FUNCPOSTFIT;

/** @brief ���ݽ�Ŀ�Ż�ȡ��λ�õĽ�ĿDID��ע��һ��Ҫ�Ի�ȡ�Ľ�����м�⣬-1Ϊ��Ч��DID��ǧ����ֱ��ʹ��
* @param[in] type ��������
* @param[in] num ��Ŀ��
* @retval -1 ��Ч�Ľ�ĿDID
* @retval ��ĿDID
*/
D_S16
d_dbase_get_srv_did_by_num (D_DBSrvType type, D_U16 num) D_FUNCPOSTFIT;

/** @brief ɾ��ָ��TS����ȫ������
* @param[in] db_ts_id ts��¼ID
* @retval  D_OK ɾ���ɹ�
* @retval  D_ERR ɾ��ʧ��
*/
D_Result	d_dbase_delete_srvs_of_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief ɾ��ָ�����ǵ�ȫ������
* @param db_sat_id ���Ǽ�¼ID
* @retval  D_OK ɾ���ɹ�
* @retval  D_ERR ɾ��ʧ��
*/
D_Result d_dbase_delete_srvs_of_sat (D_DBSATID db_sat_id) D_FUNCPOSTFIT;

/** @brief ɾ��ָ��ǰ�����͵�ȫ������
* @param fendtype ǰ������
* @retval  D_OK ɾ���ɹ�
* @retval  D_ERR ɾ��ʧ��
*/
D_Result
d_dbase_delete_srvs_of_fendtype (D_FEndType fendtype) D_FUNCPOSTFIT;

/** @brief ������ݿ����Ƿ���ָ�����͵ķ���
* @param[in] type ��������
* @retval  D_TRUE ��
* @retval  D_FALSE ��
*/
D_Bool		d_dbase_has_any_srv (D_DBSrvType type) D_FUNCPOSTFIT;
D_Bool    d_dbase_has_any_srv_ex (D_FEndType fendtype, D_DBSrvType type, D_DBTSID *db_ts_id) D_FUNCPOSTFIT;

/** @brief ȡ�����ݿ��ڵ�ȫ��ҵ���б�
* @param[in][out] rset ҵ���¼��
* @retval D_OK ��ȡ�ɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result
d_dbase_get_srvs (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ��ȡTS�µķ����б�
* @param[out] set ��ŷ���ļ�¼��ָ��
* @param[in] ID TS��¼ID
* @param[in] type ��������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_srvs_by_ts (D_DBRecset *set, D_DBTSID id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief ��ȡ�����µķ����б�
* @param[out] set ��ŷ���ļ�¼��ָ��
* @param[in] ID ���Ǽ�¼ID
* @param[in] type ��������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_srvs_by_sat (D_DBRecset *set, D_DBSATID id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief ɾ��ָ��TS����ȫ���¼�
* @param[in] db_ts_id ts��¼ID
* @retval  D_OK ɾ���ɹ�
*/
D_Result d_dbase_delete_evts_of_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief ���·�����Ϣ
* @param[in] id �����¼ID
* @param[in] srvinfo ��ŷ�����Ϣ�����ݻ�����
* @param[in] dirty �Ƿ񽫸���д��flash�У�TRUE��д��FALSE����д
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_dbase_update_srv_param (D_DBSrvID id, D_DBSrvInfo * srvinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief �ƶ��������Ŀ�󣬸�����Ӧ�Ľ�Ŀ�š��ƶ��������Ŀ����һ����յķ�Χ�ڶԽ�Ŀ�Ž�����һ���ã�����ֱ�Ӹ��ļ��ɡ�
* @param[in] id �����¼ID
* @param[in] num Ƶ����
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result
d_dbase_update_chan_num_for_sort_move(D_DBSrvID id, D_S16 num) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����͵�ϲ����������
* @param[in] type ��������
* @param[in] skip �Ƿ�ȥ���Ѿ�����Ϊ�����Ľ�Ŀ��D_TRUE:�ǣ�D_FALSE����
* @retval ��������
*/
D_U16
d_dbase_get_fav_srvs_cnt (D_DBSrvType srvtype, D_Bool skip) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dEvtTable.c**********************************************************************/

/** @brief ����¼���*/
D_Result	d_dbase_clear_evt (void) D_FUNCPOSTFIT;

/** @brief ���¼����м���һ����¼
* @param[in] info	������¼���Ϣ
* @retval �ɹ������¼�ID
* @retval ʧ�ܷ���-1
*/
D_DBEvtID	d_dbase_insert_evt (D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief ɾ��һ����¼*/
D_Result	d_dbase_delete_evt (D_DBEvtID id) D_FUNCPOSTFIT;

/** @brief ɾ�����й����¼�
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_clear_out_time_evt (void) D_FUNCPOSTFIT;

/** @brief ȡ��һ�����������Ϣ
* @param[in] id	�¼���ID
* @param[in] info �¼���Ϣ��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_evt_info (D_DBEvtID id, D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��һ������ĵ�ǰ�¼�
* @param[in] srv_id	����ID
* @param[in] now ��ǰʱ��
* @retval �ɹ������¼�ID
* @retval ʧ�ܷ���-1
*/
D_DBEvtID	d_dbase_get_present_evt (D_DBSrvID srv_id, D_Time now) D_FUNCPOSTFIT;

/** @brief ȡ��һ���������һ���¼�
* @param[in] srv_id	����ID
* @param[in] now ��ǰʱ��
* @retval �ɹ������¼�ID
* @retval ʧ�ܷ��ص�һ���¼���ID
*/
D_DBEvtID d_dbase_get_following_evt (D_DBSrvID srv_id, D_Time now) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����¼��б�
* @param[in] srv_id	����ID
* @param[in] begin ��ʼʱ��
* @param[in] end ����ʱ��
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_evts (D_DBSrvID srv_id, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����͵��¼�
* @param[in] type	�¼�����
* @param[in] begin �¼���ʼʱ��
* @param[in] end �¼�����ʱ��
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_evts_by_type (D_U8 type, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��ָ���¼�ID���¼�
* @param[in] srv_id	����ID
* @param[in] evt_id �¼�ID
* @param[in] start	������ʼʱ��
* @param[in] duration �¼�����ʱ��
* @retval �ɹ�����ʱ��ID
* @retval ʧ�ܷ���-1
*/
D_DBEvtID d_dbase_get_evt_by_id (D_DBSrvID srv_id, D_U16 evt_id,D_Time start, D_Time duration) D_FUNCPOSTFIT;

/** @brief Ԥ����ȡ��Ԥ��һ����Ŀ
* @param[in] evt	�¼�ID
* @param[in] sub Ԥ����ȡ�����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_subscribe_evt (D_DBEvtID id, D_Bool subscribe) D_FUNCPOSTFIT;

/** @brief �趨һ���¼���������Ϣ
* @param[in] id	�¼�ID
* @param[in] descr ������Ϣָ��
* @param[in] size ��Ϣ����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_set_evt_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief �趨һ���¼�����չ������Ϣ
* @param[in] id	�¼�ID
* @param[in] descr ��չ������Ϣָ��
* @param[in] size ��Ϣ����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_set_evt_ext_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief ȡ��һ���¼���������Ϣ
* @param[in] id	�¼�ID
* @param[in] descr ������Ϣָ��
* @param[in] size ��Ϣ����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Size		d_dbase_get_evt_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief ȡ��һ���¼�����չ������Ϣ
* @param[in] id	�¼�ID
* @param[in] descr ��չ������Ϣָ��
* @param[in] size ��Ϣ����
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Size		d_dbase_get_evt_ext_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief ɾ��ָ�������ȫ���¼�
* @param[in] db_srv_id	����ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_evts_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dNVODTable.c**********************************************************************/
#ifdef D_SUPPORT_NOVD

/** @brief ���NVOD���ݿ�*/
D_Result	d_dbase_clear_nvod (void) D_FUNCPOSTFIT;

/** @brief ����һ��NVOD��Ŀ
* @retval �ɹ����뷵�ز����Ŀ��ID
* @retval ����ʧ�ܷ���-1
*/
D_DBNVodID	d_dbase_insert_nvod (void) D_FUNCPOSTFIT;

/** @brief ɾ��һ��NVOD��Ŀ
* @param[in] nvod	NVOD��ĿID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_nvod (D_DBNVodID nvod) D_FUNCPOSTFIT;

/** @brief ���Ӳο�����
* @param[in] nvod	NVOD��ĿID
* @param[in] ref ���ӵĲο�����ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_add_ref_srv (D_DBNVodID nvod, D_DBSrvID ref) D_FUNCPOSTFIT;

/** @brief ɾ���ο�����
* @param[in] nvod	NVOD��ĿID
* @param[in] ref �ο�����ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_del_ref_srv (D_DBNVodID nvod, D_DBSrvID ref) D_FUNCPOSTFIT;

/** @brief ����ʱ�Ʒ���
* @param[in] nvod	NVOD��ĿID
* @param[in] ref �ο�����ID
* @param[in] shift	���ӵ�ʱ�Ʒ���ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_add_shifted_srv (D_DBNVodID nvod, D_DBSrvID ref, D_DBSrvID shift) D_FUNCPOSTFIT;

/** @brief ȡ��NVod�����б�
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_nvods (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��NVOD�еĲο�����
* @param[in] nvod_id	NVOD��ĿID
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_ref_srvs (D_DBNVodID nvod, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ�òο��¼��б�
* @param[in] nvod_id	NVOD��ĿID
* @param[in] begin	��ʼʱ��
* @param[in] end	����ʱ��	
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_ref_evts (D_DBNVodID nvod, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��ָ���ο��¼���ʱ���¼��б�
* @param[in] nvod_id	NVOD��ĿID
* @param[in] ref �ο��¼�ID
* @param[in] now	��ǰʱ��
* @param[in] p	
* @param[in] f	
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_pf_shifted_evts (D_DBNVodID nvod_id, D_DBEvtID ref, D_Time now, D_Bool p, D_Bool f, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��ָ���ο��¼���ʱ���¼��б�
* @param[in] nvod_id	NVOD��ĿID
* @param[in] ref �ο��¼�ID
* @param[in] begin	��ʼʱ��
* @param[in] end	����ʱ��	
* @param[out] set ��¼��ָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_shifted_evts (D_DBNVodID nvod, D_DBEvtID ref, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ɾ������ָ�������NVOD��¼
* @param[in] db_srv_id	����ID
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_nvods_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief ȡ�ú���ָ�������NVOD��¼
* @param[in] db_srv_id	����ID
* @retval �ɹ�����NVOD ID
* @retval ʧ�ܷ���-1
*/
D_DBNVodID	d_dbase_get_nvod_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief ȡ��NVOD�����Ϣ
* @param[in] nvod	NVOD��ĿID
* @param[in] info ������Ϣָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_nvod_info (D_DBNVodID nvod, D_DBSrvInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ʱ��ҵ��Ĳο�ҵ��
* @param[in] db_srv_id	����ID
* @retval �ɹ����زο�ҵ��ID
* @retval ʧ�ܷ���-1
*/
D_DBSrvID	d_dbase_get_ref_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ʱ���¼��Ĳο��¼�
* @param[in] db_evt_id	ʱ���¼�ID
* @retval �ɹ����زο��¼�ID
* @retval ʧ�ܷ���-1
*/
D_DBEvtID	d_dbase_get_ref_of_evt (D_DBEvtID db_evt_id) D_FUNCPOSTFIT;

#endif

/************************************************end**********************************************************************/

/************************************************dSubTable.c**********************************************************************/

/** @brief ���Ԥ����Ŀ��*/
D_Result	d_dbase_clear_subscribe (void) D_FUNCPOSTFIT;

/** @brief ����Ԥ����Ŀ��¼
* @param[in] info ԤԼ��Ϣָ��
* @retval ����ɹ����ؼ�¼ID
* @retval ����ʧ�ܷ���-1
*/
D_DBSubID	d_dbase_insert_subscribe (D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief ɾ��һ��Ԥ����Ŀ��¼
* @param[in] id ��¼ID
* @retval ɾ���ɹ�����D_OK
* @retval ɾ��ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_subscribe (D_DBSubID id) D_FUNCPOSTFIT;

/** @brief ȡ��һ��Ԥ����Ŀ��¼ID
* @param[in] srv ����ID
* @param[in] evt_id �¼�ID
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBSubID	d_dbase_get_subscribe (D_DBSrvID srv, D_U16 evt_id) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ض�ʱ�����Ԥ����Ŀ��ID
* @param[in] begin ��ʼʱ��
* @param[in] end ����ʱ��
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBSubID	d_dbase_get_subscribe_by_time (D_Time begin, D_Time end) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ض���ʼʱ����Ԥ����Ŀ��ID
* @param[in] begin ��ʼʱ��
* @param[in] end ����ʱ��
* @retval ��ȡ�ɹ����ؼ�¼ID
* @retval ��ȡʧ�ܷ���-1
*/
D_DBSubID d_dbase_get_subscribe_overlap (D_Time begin, D_Time end) D_FUNCPOSTFIT;

/** @brief ȡ��Ԥ����Ŀ�б�
* @param[out] set ��¼��ָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_subscribes (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief ȡ��һ��Ԥ����Ŀ��¼��Ϣ
* @param[in] id ԤԼ��¼ID
* @param[in] info ԤԼ�¼���Ϣָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result	d_dbase_get_subscribe_info (D_DBSubID id, D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief ɾ��ָ�������ȫ��Ԥ���¼�
* @param[in] db_srv_id ����ID
* @retval ɾ���ɹ�����D_OK
* @retval ɾ��ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_delete_subscribes_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief Ԥ���������:ɾ���ѽ���Ԥ����Ŀ,����Ƿ��н�Ŀ����
* @param[in] del	�Ƿ�ɾ�����ڽ�Ŀ
* @param[in] sub_callback	���ڽ�Ŀ�ص�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_dbase_check_subscribe (D_Bool del, D_Time advance_time, D_Result (*sub_callback) (D_DBSubID sub) D_FUNCPOSTFIT) D_FUNCPOSTFIT;

/** @brief ����Ԥ�������¼
* @param[in] info ԤԼ��Ϣָ��
* @retval ����ɹ�����ԤԼ��¼ID
* @retval ����ʧ�ܷ���-1
*/
D_DBSubID
d_dbase_insert_srv_subscribe (D_DBSubInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��һ��Ԥ���������Ϣ
* @param[in] id ԤԼ����ID
* @param[in] info ԤԼ������Ϣָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result
d_dbase_get_srv_sub_info (D_DBSubID id, D_DBSubInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��һ��Ԥ���������Ϣ
* @param[in] id ԤԼ����ID
* @param[in] info ԤԼ������Ϣָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result
d_dbase_get_srv_sub_info (D_DBSubID id, D_DBSubInfo *info) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dBouqTable.c**********************************************************************/
/** @brief ���ҵ��Ⱥ��*/
D_Result	d_dbase_clear_bouq (void) D_FUNCPOSTFIT;

/** @brief ��ҵ��Ⱥ���м���һ����¼
* @param[in] info �����ҵ��Ⱥ��¼��Ϣ
* @retval id ����ɹ������ؼ�¼ID
* @retval -1 ����ʧ��
*/
D_DBNetID	d_dbase_insert_bouq (D_DBBouqInfo *info) D_FUNCPOSTFIT;

/** @brief ɾ��һ��ҵ��Ⱥ��¼
* @param[in] id ҵ��ȺID
* @retval D_OK ɾ���ɹ�
* @retval D_ERR ɾ��ʧ��
*/
D_Result	d_dbase_delete_bouq (D_DBBouqID id) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ҵ��Ⱥ�����Ϣ
* @param[in] id ҵ��ȺID
* @param[in] info ��ȡ��ҵ��Ⱥ��Ϣ�����ָ��
* @retval D_OK ��ȡ�ɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result	d_dbase_get_bouq_info (D_DBBouqID id, D_DBBouqInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ�����ݿ��ڵ�ȫ��ҵ��Ⱥ�б�
* @param[out] rset ҵ��Ⱥ��¼��
* @retval D_OK ��ȡ�ɹ�
* @retval D_ERR ��ȡʧ��
*/
D_Result	d_dbase_get_bouqs (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief ȡ��ָ�����ֵ�ҵ��Ⱥ
* @param[in] name ҵ��Ⱥ����
* @retval id ��ȡ�ɹ�������ҵ��ȺID
* @retval -1 ��ȡʧ��
*/
D_DBBouqID d_dbase_get_bouqs_by_name(const D_Char *bouq_name) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/


/************************���º����д�������ȷ���Ƿ���******************************************************************/

/** @brief ȡ��TS�����Ϣ
* @param[in] id TS ID
* @param[in] info TS��Ϣָ��
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
D_Result d_dbase_get_ts_info_by_num(D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief ȡ��TS�����Ϣ,��ȡ�ö�Ӧ��db_ts_id
* @param[in] id ��¼�����
* @param[in] info TS��Ϣָ��
* @param[in] db_ts_id TS ID
* @retval ��ȡ�ɹ�����D_OK
* @retval ��ȡʧ�ܷ���D_ERR
*/
/*id Ϊ��¼�������id*/
D_Result d_dbase_get_ts_info_by_num_ex(D_ID id, D_DBTSInfo *info, D_DBTSID *db_ts_id) D_FUNCPOSTFIT;

//����������������ݿ��йصĽ�Ŀ��¼
D_Result 	d_dbase_delete_srvs_bytype(D_FEndType type)D_FUNCPOSTFIT;

/** @brief ͨ��ts id, original network id, service id ȡ�÷���
*** @brief ����Ƶ�㣬����Ƶ�����ҷ���(Ƶ��)
* @param[in] db_net_id	����ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	ԭʼ����ID
* @param[in] srv_id	����ID
* @retval �ɹ����ؼ�¼ID
* @retval ʧ�ܷ���-1
*/
D_DBSrvID	d_dbase_get_srv_by_ids (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id) D_FUNCPOSTFIT;
D_DBSrvID   d_dbase_get_srv_by_ids_ex (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_FEndType fendtype,D_U16 srv_id) D_FUNCPOSTFIT;

/** @brief ͨ��ts id, original network id, service id ȡ�÷���
*** @brief ������Ŀ���ݿ������еķ���(Ƶ��)��ֱ���ҵ����ϵġ�
* @param[in] db_net_id	����ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	ԭʼ����ID
* @param[in] srv_id	����ID
* @retval �ɹ����ؼ�¼ID
* @retval ʧ�ܷ���-1
*/
D_DBSrvID
d_dbase_get_srv_by_ids_new (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id) D_FUNCPOSTFIT;

#if 0
/** @brief ͨ��ts id, original network id, service id, event id ȡ�÷���
* @param[in] db_net_id	����ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	ԭʼ����ID
* @param[in] srv_id	����ID
* @param[in] evt_id	�¼�ID
* @retval �ɹ������¼�ID
* @retval ʧ�ܷ���-1
*/
D_DBEvtID	d_dbase_get_evt_by_ids (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id, D_U16 evt_id) D_FUNCPOSTFIT;
#endif
/** @brief �������������Ϣ
* @param[in] id	�����¼ID
* @param[in] info	������Ϣָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_updata_net_info (D_DBNetID id, D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @����ĳ��ts��Ϣ
* @param[in] id TS ID
* @param[in] info TS��Ϣָ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_updata_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief �޸�service��Ƶ���ţ�ֻ���ڸ���ȫ��ͬ���ͽ�Ŀ��Ƶ����  
* @param[in] id �����¼ID
* @param[in] num Ƶ����
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_num (D_DBSrvID id, D_S16 num) D_FUNCPOSTFIT;

/** @brief �޸�service������
* @param[in] id �����¼ID
* @param[in] name ��Ŀ��
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result
d_dbase_update_srv_name (D_DBSrvID id, D_Char *name) D_FUNCPOSTFIT;

/** @brief �޸�service�ļ�����־
* @param[in] id �����¼ID
* @param[in] lock ������־
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_lock (D_DBSrvID id, D_Bool lock) D_FUNCPOSTFIT;

/** @brief �޸�service��������־
* @param[in] id �����¼ID
* @param[in] skip ������־
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_skip (D_DBSrvID id, D_Bool skip) D_FUNCPOSTFIT;

/** @brief �޸�service����������
* @param[in] id �����¼ID
* @param[in] vol ����
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_volume (D_DBSrvID id, D_U8 vol) D_FUNCPOSTFIT;

/** @brief �޸�service����������
* @param[in] id �����¼ID
* @param[in] track ����
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_aud_track (D_DBSrvID id, D_AudTrack track) D_FUNCPOSTFIT;

/** @brief �޸�service�İ�������
* @param[in] id �����¼ID
* @param[in] acc ����
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_aud_acc (D_DBSrvID id, D_U8 acc) D_FUNCPOSTFIT;

/** @brief �޸�service��PMT����
* @param[in] id �����¼ID
* @param[in] v_pid ��ƵPID
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result	d_dbase_update_srv_pmt (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec) D_FUNCPOSTFIT;
		
/** @brief �޸�service��PMT����,����PMT_PID*/
D_Result	d_dbase_update_srv_pmt_ex (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec,
		D_U16 pcr_pid, D_U16 pmt_pid) D_FUNCPOSTFIT;
D_Result d_dbase_update_srv_pmt_ex2 (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec, 
                D_U16 a3_pid, D_AudCodecType a3_codec, D_U16 a4_pid, D_AudCodecType a4_codec, D_U16 pcr_pid, D_U16 pmt_pid) D_FUNCPOSTFIT;

/** @brief �޸�service��ϲ����־ add by bianxy 2006-8-17  
* @param[in] id �����¼ID
* @param[in] favor_type �˸�ϲ��֮һ
* @param[in] favor ϲ����־
* @retval D_OK ���³ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result d_dbase_update_srv_favor_ex (D_DBSrvID id, D_U8 favor_type, D_Bool favor) D_FUNCPOSTFIT;

/** @brief ��������flash��¼���е����ݵ���Ӧ��memory��������
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_load_flash_ex(void)D_FUNCPOSTFIT;

/** @brief �������иĶ�ʱ�����Ķ�����д�뵽��¼����
* @param[in] T_id	table ID
* @param[in] F_id	field ID
* @param[in] D_id	��¼ID
* @param[in] length	���ĵ����ݳ���
* @param[in] data	���ݻ�����ָ��
* @param[in] dirty	�Ƿ�ˢ�µ�flash�ı��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_record_flash_flush_tbl(D_U8 T_id,D_S8 F_id,D_U16 D_id,D_U16 length,D_U8*data,D_Bool dirty)D_FUNCPOSTFIT;

/** @brief block�����иĶ�ʱ�����Ķ�����д�뵽��¼���� liuwf
* @param[in] B_id	block ID
* @param[in] offset	ƫ�Ƶ�ַ
* @param[in] size	���ĵ����ݴ�С
* @param[in] data	���ݻ�����ָ��
* @param[in] dirty	�Ƿ�ˢ�µ�flash�ı��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result d_dbase_record_flash_flush_blk(D_U8 B_id, D_U16 offset, D_U16 size, D_U8*data, D_Bool dirty)D_FUNCPOSTFIT;

/************************end*************************************************************************************************/


#ifdef  __cplusplus
}
#endif

#endif
/*EOF*/
/**@}*/
