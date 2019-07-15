/**@defgroup dbase 数据库
*@{*/
/** @file
* @brief 数据库管理模块
* @author 龚克
* @date 2005-6-17 龚克: 建立文件
	@date 2006-8-2 shanzs: 
		修改D_DBSrvInfo结构
		增加d_dbase_get_srvs_by_type_ex函数
		增加d_dbase_get_srvs_by_bouq_ex函数
		增加d_dbase_update_srv_skip函数
* @date 2013-03-19 lc: 统一平台, 代码整理
	@date 2013-4-17 Liuwf: 
		增加天线、卫星数据库部分；整理之前的函数，通过宏来决定是否编译
* @date 2013-04-22 lwf,sunzy: 统一平台, 代码整理
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


/* 暂时定义保留字节不大于128B */
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

/** @brief 数据类型*/
typedef enum {
	D_DB_DATA_CA,	/**< CA相关数据*/
	D_DB_DATA_DB	/**< 数据广播相关数据*/
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
	D_DB_SRV_ATV, /*模拟电视*/
	
	/* 直播星推送业务*/
	D_DB_SRV_PUSHVOD,

    //...
    //...    
    
    /*以下类型只用于接口操作*/
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
	D_U8	aud_acc;		/*伴音*/
	D_Bool	favor0;
	D_Bool	favor1;
	D_Bool	favor2;
	D_Bool	favor3;
	D_Bool	favor4;
	D_Bool	favor5;
	D_Bool	favor6;
	D_Bool	favor7;

	D_Bool	lock;	
	D_Bool	skip;				/*跳过 added by shanzs@06/08/02*/
	D_Bool	ca_flag;		/*加扰标记*/
	D_S8		volume;
	D_U8		aud_track;	/*声道*/
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
	D_U8	sd_hd_flag;/*高标清标志*/
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
	D_S16	longitude;	/*卫星经度(-18000 ~ 18000) 东为正，两位小数*/
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
/** @brief 取得音频PID*/
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
/** @brief 取得音频PID*/
#define D_DB_GET_SRV_AUD(_s)\
		((_s)->aud_acc ?\
				(((_s)->aud2_pid==D_INVALID_PID_VALUE)?(_s)->aud1_pid:(_s)->aud2_pid) :\
				(((_s)->aud1_pid==D_INVALID_PID_VALUE)?(_s)->aud2_pid:(_s)->aud1_pid))

/** @brief 取得音频编码类型*/
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

/** @brief 取记录集内的记录数目*/
#define d_dbase_rset_cnt(_r)	((_r)->cnt)

/** @brief 取记录集指定记录ID*/
#define d_dbase_rset_get(_r,_i)	((_r)->ids[_i])

/** @brief table id与dbase里的table数组对应, 不能更改 */
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

/** @brief 表配置结构 */
typedef struct
{
    D_U32 max_cnt; /**< 表最大记录数 */
    D_U32 store_cnt; /**< 表存储记录数 */
    D_ID part_id; /* 表存储分区id */
    D_U8 reserved_field_size; /* 保留域大小,0不保存 */
}D_DBTabInfo;

/** @brief 数据库初始化结构 */
typedef struct
{
    D_U16 table_valid_flag; /**< 表有效标志 */
    D_DBTabInfo tab_info[D_DBASE_MAX_TAB_ID]; /**< 表初始化属性 */
    D_U32 var_string_cnt; /**< var_string个数 */
    D_U16 config_blk_size; /**< config block大小, 不超过64K */
    D_U16 data_blk_size; /**< 根据需要定义数据块大小, 单独占一个分区, 0将不存储 */
}D_DBOpenParam;

/************************************************dDBase.c**********************************************************************/
/** @brief 初始化全部数据库
* @param[in] param 数据库初始化结构指针
* @retval D_OK	加载数据库正确
* @retval D_ERR_NO_SPACE	分配内存空间出错
* @retval D_ERR	数据库中的数据无效
*/
D_Result	d_dbase_open (D_DBOpenParam *param) D_FUNCPOSTFIT;

/** @brief 关闭全部数据库*/
D_Result	d_dbase_close (void) D_FUNCPOSTFIT;

/** @brief 将数据库中改动数据保存到Flash中
* @param[in] sync   是否同步刷新
* @retval D_OK
*/
D_Result d_dbase_flush_ex(D_Bool sync) D_FUNCPOSTFIT;

/** @brief 将数据库中改动数据同步保存到Flash中*/
#define d_dbase_flush()           d_dbase_flush_ex(D_TRUE)

/** @brief 将数据库中改动数据异步保存到Flash中*/
#define d_dbase_async_flush()     d_dbase_flush_ex(D_FALSE)

/** @brief 检查数据库是否需要更新
* @retval D_TRUE 需要刷新
* @retval D_FALSE 不需要刷新
*/
D_Bool		d_dbase_need_flush (void) D_FUNCPOSTFIT;

/** @brief 记录集初始化
* @param[out] set	记录集指针
* @param[in] max	记录集可容纳的最大记录数目
* @param[in] buf	ID存放缓冲区
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_rset_init (D_DBRecset *set, D_U16 max, D_ID *buf) D_FUNCPOSTFIT;

/** @brief 记录集空间释放
* @param[out] set	记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_rset_deinit (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 清空记录集内的记录
* @param[out] set	记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_rset_empty (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 向记录集中增加记录
* @param[out] set	记录集指针
* @param[in] id		增加的记录ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_rset_add (D_DBRecset *set, D_ID id) D_FUNCPOSTFIT;

/** @brief 对记录集内记录排序
* @param[out] set	记录集指针
* @param[in] func	比较函数
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_rset_sort (D_DBRecset *set, D_CmpFunc func) D_FUNCPOSTFIT;

/** @brief 保存buf数据到flash中
* @param[in] part_id	flash分区ID
* @param[in] offset	偏移地址
* @param[in] szie	写入的数据大小
* @param[in] buf	数据缓冲区指针
* @retval 成功返回写入的数据大小
* @retval 失败返回D_ERR
*/
D_Size    d_dbase_nvram_store_data (D_ID part_id, D_U32 offset, D_U32 size, D_U8 *buf) D_FUNCPOSTFIT;

/** @brief 读flash数据到buf中
* @param[in] part_id	flash分区ID
* @param[in] offset	偏移地址
* @param[in] szie	读取的数据大小
* @param[out] buf	数据缓冲区指针
* @retval 成功返回读取的数据大小
* @retval 失败返回D_ERR
*/
D_Size    d_dbase_nvram_read_data (D_ID part_id, D_U32 offset, D_U32 size, D_U8 *buf) D_FUNCPOSTFIT;

/** @brief 获得flash记录集开关
* @retval rset_en 记录集开关值，记录集开启 1, 记录集关闭 0
*/
D_Result   d_dbase_get_rset_en(void)D_FUNCPOSTFIT;

/** @brief 设置flash记录集开关
* @param[in] en	记录集开关值，0：关闭；1：打开
*/
void  d_dbase_set_rset_en(D_U8 en)D_FUNCPOSTFIT;

/** @brief 擦除flash记录集*/
void 
d_dbase_erase_flash_record(void)D_FUNCPOSTFIT;

#ifdef D_SUPPORT_EEPROM
/** @brief 打开EEPROM*/
D_Result	d_dbase_open_eeprom (void) D_FUNCPOSTFIT;

/** @brief 加载EEPROM数据*/
D_Result	d_dbase_load_eeprom (void) D_FUNCPOSTFIT;

/** @brief 数据库读取eeprom
* @param[out] dat	数据buffer指针
* @param[in] size	读取的数据大小
* @retval 成功返回读取的数据大小
* @retval 失败返回负值
*/
D_Size	d_dbase_read_eeprom (D_U8 *dat, D_Size size) D_FUNCPOSTFIT;

/** @brief 数据库写eeprom
* @param[in] dat	数据buffer指针
* @param[in] size	写入的数据大小
* @retval 成功返回写入的数据大小
* @retval 失败返回负值
*/
D_Size d_dbase_write_eeprom (D_U8 *dat, D_Size size) D_FUNCPOSTFIT;

#endif

/************************************************end**********************************************************************/

/************************************************dAnteTable.c**********************************************************************/
/** @brief 清空天线表
* @retval 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_dbase_clear_ante (void) D_FUNCPOSTFIT;

/** @brief 插入一条天线信息，常用于恢复出厂设置时
* @param[in] info	存放天线信息的数据缓冲区指针
* @return 成功返回天线ID,失败返回-1
*/
D_DBTSID d_dbase_insert_ante (D_DBAnteInfo *info) D_FUNCPOSTFIT;

/** @brief 获取天线信息
* @param[in] id	天线记录ID
* @param[in] info	存放天线信息的数据缓冲区指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_get_ante_info (D_DBAnteID id, D_DBAnteInfo *info) D_FUNCPOSTFIT;

/** @brief 获取所有天线列表
* @param[out] rset 天线记录集指针
* @retval D_OK 获取成功
* @retval D_ERR 获取失败
*/
D_Result  d_dbase_get_antes (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 更新天线信息
* @param[in] id 天线记录ID
* @param[in] anteinfo 存放天线信息的数据缓冲区指针
* @param[in] dirty 是否将更改写到flash中，TRUE：写；FALSE：不写
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_update_ante_param (D_DBAnteID id, D_DBAnteInfo * anteinfo, D_Bool dirty) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dSateTable.c**********************************************************************/
/** @brief 清空卫星表
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_dbase_clear_sat (void) D_FUNCPOSTFIT;

/** @brief 插入一条卫星记录
* @param[in] info	存放卫星信息的数据缓冲区指针
* @return 成功返回天线ID,失败返回-1
*/
D_DBSATID d_dbase_insert_sat_ex (D_DBSateInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 删除一条卫星记录
* @param[in] id	卫星记录的ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_dbase_delete_sat (D_DBSATID id) D_FUNCPOSTFIT;

/** @brief 获取卫星信息
* @param[in] id	卫星记录ID
* @param[in] info	存放卫星信息的数据缓冲区指针
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_get_sat_info (D_DBSATID id, D_DBSateInfo *info) D_FUNCPOSTFIT;

/** @brief 获取所有卫星列表
* @param[out] rset 卫星记录集指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result  d_dbase_get_sates (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 取得指定卫星逻辑号的卫星DID，注意一定要对返回的结果进行判断，-1为无效的ID，切勿直接使用返回值
* @param[in] num 卫星号
* @retval 成功返回卫星记录ID
* @retval 失败返回-1
*/
D_DBSATID
d_dbase_get_sat_did_by_num (D_S16 num) D_FUNCPOSTFIT;

/** @brief 更新卫星信息
* @param[in] id 卫星记录ID
* @param[in] satinfo 存放卫星信息的数据缓冲区指针
* @param dirty 是否将更改写到flash中，TRUE：写；FALSE：不写
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_update_sat_param (D_DBSATID id, D_DBSateInfo * satinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief 取得卫星列表
* @param rset 记录集指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result d_dbase_get_sates_selected (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 修改卫星的选中状态
* @param id 卫星记录ID
* @param sel 是否选中
* @retval 修改成功返回D_OK
* @retval 修改失败返回D_ERR
*/
D_Result d_dbase_update_sat_selected (D_DBSATID id, D_Bool sel) D_FUNCPOSTFIT;

/** @brief 取得一个空闲的卫星号
* @retval -1 获取失败; num 获取成功
*/
D_S16
d_dbase_get_free_sate_num (void) D_FUNCPOSTFIT;

/** @brief 修改卫星的天线位置号
* @param id 卫星记录ID
* @param pos 卫星位置号
* @retval 修改成功返回D_OK
* @retval 修改失败返回D_ERR
*/
D_Result d_dbase_update_sat_diseqc_pos (D_DBSATID id, D_U8 pos) D_FUNCPOSTFIT;


/** @brief 修改卫星的DisEqC类型
* @param id 卫星记录ID
* @param type 卫星DisEqc类型
* @retval 修改成功返回D_OK
* @retval 修改失败返回D_ERR
*/
D_Result d_dbase_update_sat_diseqc_type (D_DBSATID id, D_U8 type) D_FUNCPOSTFIT;

/** @brief 修改卫星的DisEqC端口
* @param id 卫星记录ID
* @param port 卫星DisEqc端口
* @retval 修改成功返回D_OK
* @retval 修改失败返回D_ERR
*/
D_Result d_dbase_update_sat_diseqc_port (D_DBSATID id, D_U8 port) D_FUNCPOSTFIT;

/** @brief 修改卫星的DisEqC 22K开关
* @param id 卫星记录ID
* @param diseqc12v 卫星diseqc22K开关
* @retval 修改成功返回D_OK
* @retval 修改失败返回D_ERR
*/
D_Result d_dbase_update_sat_diseqc_22k (D_DBSATID id, D_U8 diseqc22k) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dNetTable.c**********************************************************************/
/** @brief 清空网络表*/
D_Result	d_dbase_clear_net (void) D_FUNCPOSTFIT;

/** @brief 向网络表中加入一条记录
* @param[in] info	网络信息指针
* @retval 成功返回网络ID
* @retval 失败返回-1
*/
D_DBNetID	d_dbase_insert_net (D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @brief 删除一条记录
* @param[in] id	网络记录ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_delete_net (D_DBNetID id) D_FUNCPOSTFIT;

/** @brief 取出一个网络相关信息
* @param[in] id	网络记录ID
* @param[in] info	网络信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_net_info (D_DBNetID id, D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @brief 取出数据库内的全部网络列表
* @param[out] rset	网络记录记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_nets (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 更新网络信息
* @param[in] id 网络记录ID
* @param[in] netinfo 存放网络信息的数据缓冲区指针
* @param[in] dirty 是否将更改写到flash中，TRUE：写；FALSE：不写
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_dbase_update_net_param (D_DBNetID id, D_DBNetInfo * netinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief 根据卫星经度获取卫星相关信息
* @param longitude 卫星经度
* @param info 卫星信息指针
* @retval 读取成功返回D_OK
* @retval 读取失败返回D_ERR
*/
D_Result
d_dbase_get_sat_info_by_longitude(D_S16 longitude, D_DBSateInfo *info) D_FUNCPOSTFIT;

/** @brief 根据卫星经度获取卫星id
* @param longitude 卫星经度
* @retval 读取成功返回D_OK
* @retval 读取失败返回D_ERR
*/
D_ID
d_dbase_get_sat_id_by_longitude(D_S16 longitude) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dTSTable.c**********************************************************************/
/** @brief 清空TS表*/
D_Result	d_dbase_clear_ts (void) D_FUNCPOSTFIT;
D_Result d_dbase_clear_ts_ex (D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 向TS表中插入一个记录
* @param[in] info TS信息
* @param[in] tmp 临时标志
* @retval id TS ID
* @retval -1 插入失败
*/
D_DBTSID	d_dbase_insert_ts_ex (D_DBTSInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 向TS表中插入一个记录*/
#define d_dbase_insert_ts(_i)	d_dbase_insert_ts_ex(_i,D_FALSE)

/** @brief 向TS表中插入一个临时记录*/
#define d_dbase_insert_temp_ts(_i)	d_dbase_insert_ts_ex(_i,D_TRUE)

/** @brief 删除TS表中的一个记录
* @param[in] id TS记录 ID
* @retval 删除成功返回D_OK
* @retval 删除失败返回D_ERR
*/
D_Result	d_dbase_delete_ts (D_DBTSID id) D_FUNCPOSTFIT;

/** @brief 删除指定前端类型的全部转发器 
* @param[in] type 前端类型
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_delete_ts_by_type (D_FEndType type) D_FUNCPOSTFIT;

/** @brief 检查Ts记录有效性*/
D_Bool d_dbase_check_ts_valid (D_DBTSID id) D_FUNCPOSTFIT;

/** @brief 取得TS相关信息
* @param[in] id TS记录 ID
* @param[in] info TS信息区指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result	d_dbase_get_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief 取得TS列表
* @param[out] rset 记录集指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result	d_dbase_get_tses (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 取得对应网络的TS列表
* @param[in] net_id 网络ID
* @param[out] rset 记录集指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result	d_dbase_get_tses_by_net (D_DBNetID net_id, D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 取得指定频点参数的TS记录
* @param[in] db_net_id 网络ID
* @param[in] type 前段搜索类型
* @param[in] param TS参数
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBTSID	d_dbase_get_ts_by_param (D_DBNetID db_net_id, D_FEndType type, D_DBTSParam *param) D_FUNCPOSTFIT;

/** @brief 取得指定频点参数的TS记录
* @param[in] freq 主频点
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBTSID
d_dbase_get_ts_by_main_freq (D_FEndFreq freq) D_FUNCPOSTFIT;

/** @brief 取得指定频点参数的TS记录
* @param[in] db_sat_id 卫星ID
* @param[in] type 前段搜索类型
* @param[in] param TS参数
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBTSID
d_dbase_get_ts_by_param_ex (D_DBNetID db_sat_id, D_FEndType type, D_DBTSParam *param) D_FUNCPOSTFIT;


/** @brief 取得指定TS ID的TS记录
* @param[in] db_net_id 网络ID
* @param[in] ts_id TS ID
* @param[in] org_net_id 原始网络ID
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBTSID	d_dbase_get_ts_by_id (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id) D_FUNCPOSTFIT;
D_DBTSID	d_dbase_get_ts_by_id_new (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id,D_U16 srv_id) D_FUNCPOSTFIT;

D_DBTSID    d_dbase_get_ts_by_id_ex (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_FEndType fendtype) D_FUNCPOSTFIT;
D_DBTSID    d_dbase_get_dbtsid_by_tsid (D_U16 ts_id) D_FUNCPOSTFIT;
/** @brief 删除指定网络的全部TS流
* @param[in] db_net_id 网络ID
* @retval 删除成功返回D_OK
* @retval 删除失败返回D_ERR
*/
D_Result	d_dbase_delete_tses_of_net (D_DBNetID db_net_id) D_FUNCPOSTFIT;

/** @brief 删除指定网络的全部事件
* @param[in] db_net_id 网络ID
* @retval 删除成功返回D_OK
* @retval 删除失败返回D_ERR
*/
D_Result	d_dbase_delete_evts_of_net (D_DBNetID db_net_id) D_FUNCPOSTFIT;

/** @brief 查找当前转发器总数 added by shulh 20090714
* @retval 转发器总数
*/
D_U16 d_dbase_get_ts_total_num (void) D_FUNCPOSTFIT;

/** @brief 查找相同的ts信息
* @param[in] info TS信息指针
* @param[in] type 前段搜索类型
* @retval 有相同的返回记录ID
* @retval 无相同的返回-1
*/
D_DBTSID d_dbase_get_same_ts_num (D_DBTSInfo *info,  D_FEndType type) D_FUNCPOSTFIT;


/** @brief 设定频率与符号率偏差范围，
对DVBS工程，盲扫时检查是否是相同的TS
* @param[in] freq_range 频率范围
* @param[in] baud_range 符号率范围
* @retval 相同返回D_OK
* @retval 不同返回D_ERR
*/
D_Result
d_dbase_set_dvbs_freq_baud_range(D_FEndFreq freq_range, D_FEndBaud baud_range) D_FUNCPOSTFIT;

/** @brief 对DVBS工程，盲扫时检查是否是相同的TS
* @param[in] p1 TS1指针
* @param[in] p2 TS2指针
* @retval 相同返回D_OK
* @retval 不同返回D_ERR
*/
D_Result
d_dbase_check_ts_dvbs(D_FEndParam *p1, D_FEndParam *p2) D_FUNCPOSTFIT;

/** @brief 查找DVBS卫星下相同的转发器，一般用于盲扫时
* @param[in] info	存放TS信息的数据缓冲区指针
* @param[in] type	前端搜台类型
* @return 成功返回TS记录的ID,失败返回-1
*/
D_DBTSID d_dbase_get_same_ts_num_dvbs (D_DBTSInfo *info, D_FEndType type) D_FUNCPOSTFIT;

/** @判断频点是否属于某卫星
* @param[in] db_sat_id 卫星 ID
* @param[in] db_ts_id  TS id
* @retval 属于返回D_TRUE， 不属于返回D_FALSE
*/
D_Bool 
d_dbase_check_ts_in_sat(D_DBSATID db_sat_id, D_DBTSID db_ts_id)D_FUNCPOSTFIT;

/** @brief 删除卫星下的转发器
* @param[in] db_sat_id	卫星记录的ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_delete_ts_of_sat(D_DBSATID db_sat_id) D_FUNCPOSTFIT;

/** @brief 获取卫星下的转发器
* @param[out] set	存放TS ID的记录集指针
* @param[in] id	卫星记录ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_get_ts_by_sat (D_DBRecset *set, D_DBSATID id) D_FUNCPOSTFIT;

/** @brief 更新TS信息
* @param[in] id TS记录ID
* @param[in] tsinfo 存放TS信息的数据缓冲区指针
* @param[in] dirty 是否将更改写到flash中，TRUE：写；FALSE：不写
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result  d_dbase_update_ts_param (D_DBTSID id, D_DBTSInfo * tsinfo, D_Bool dirty) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dSrvTable.c**********************************************************************/
/** @brief 清空服务表*/
D_Result d_dbase_clear_srv (void) D_FUNCPOSTFIT;
D_Result d_dbase_clear_srv_ex (D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 清除指定类型的所有服务*/
D_Result d_dbase_clear_srv_by_type (D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 向服务表中加入一条记录
* @param[in] info	服务信息
* @param[in] tmp 临时标志
* @retval id 服务ID
* @retval -1 插入失败
*/
D_DBSrvID	d_dbase_insert_srv_ex (D_DBSrvInfo *info, D_Bool tmp) D_FUNCPOSTFIT;

/** @brief 向服务表中加入一条记录*/
#define d_dbase_insert_srv(_i)	d_dbase_insert_srv_ex(_i, D_FALSE)

/** @brief 向服务表中加入一条临时记录*/
#define d_dbase_insert_temp_srv(_i)	d_dbase_insert_srv_ex(_i, D_TRUE)

/** @brief 删除一条记录
* @param[in] id 服务ID
* @retval D_OK 删除成功
* @retval D_ERR 删除失败
*/
D_Result	d_dbase_delete_srv (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief 检查业务记录有效性*/
D_Bool d_dbase_check_srv_valid (D_DBSrvID id) D_FUNCPOSTFIT;

/** @brief 取得指定类型的服务数量
* @param[in] all_flag 是否取全部业务数量
* @param[in] type 服务类型(all_flag为D_FALSE时有效)
* @retval 服务数量
*/
D_U32 d_dbase_get_srvs_cnt (D_Bool all_flag, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 取出一个服务相关信息
* @param[in] id 服务ID
* @param[in] info 服务信息
* @retval D_OK 获得成功
* @retval D_ERR 获取失败
*/
D_Result	d_dbase_get_srv_info (D_DBSrvID id, D_DBSrvInfo *info) D_FUNCPOSTFIT;

/** @brief 取得指定service id的服务 @added by qiny 15/09/14
* @param[out] set 记录集
* @param[in]  service_id service_id
* @retval  D_OK 获取成功
* @retval  D_ERR 获取失败
*/
D_Result
d_dbase_get_srvs_by_srvid (D_DBRecset *set, D_U16 service_id) D_FUNCPOSTFIT;

/** @brief 取得指定类型的服务
* @param[out] rset 记录集
* @param[in] type 服务类型
* @param[in] favor 是否获取喜爱节目。TRUE：是；FALSE：否
* @param[in] fav_type 喜爱类型，获取哪种类型的喜爱列表，该参数只有在favor设为TRUE时有效
* @retval D_OK 获得成功
* @retval D_ERR 获取失败
*/
D_Result	d_dbase_get_srvs_by_type (D_DBRecset *set, D_DBSrvType type, D_Bool favor, D_U8 fav_type) D_FUNCPOSTFIT;

/** @brief 取得指定类型的服务 added by shanzs@06/08/04
* @param[out] set 记录集
* @param[in] skip 跳过标志
* @param[in] type 服务类型
* @param[in] favor 是否获取喜爱节目。TRUE：是；FALSE：否
* @param[in] fav_type 喜爱类型，获取哪种类型的喜爱列表，该参数只有在favor设为TRUE时有效
* @retval D_OK 获得成功
* @retval D_ERR 获取失败
*/
D_Result	d_dbase_get_srvs_by_type_ex (D_DBRecset *set, D_Bool skip, D_DBSrvType type, D_Bool favor, D_U8 fav_type) D_FUNCPOSTFIT;

/** @brief 取得指定频道号的服务ID
* @param[in] num 频道号
* @param[in] type 服务类型
* @retval id 记录ID
* @retval -1 获取失败
*/
D_DBSrvID	d_dbase_get_srv_by_num (D_S16 num, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 根据service id取得服务
* @param[in] db_ts_id TS表记录ID
* @param[in] srv_id 服务ID
* @retval id 记录ID
* @retval -1 获取失败
*/
D_DBSrvID	d_dbase_get_srv_by_id (D_DBTSID db_ts_id, D_U16 srv_id) D_FUNCPOSTFIT;

/** @brief 取得指定PID的服务
* @param[in] db_ts_id TS表记录ID
* @param[in] pid 节目PID
* @retval id 记录ID
* @retval -1 获取失败
*/
D_DBSrvID	d_dbase_get_srv_by_pid (D_DBTSID db_ts_id, D_U16 pid) D_FUNCPOSTFIT;

/** @brief 取得指定PID的服务
* @param[in] db_ts_id TS表记录ID,  (-1时不比较)
* @param[in] vpid 节目视频PID
* @param[in] apid 节目音频PID
* @param[in] pcrpid 节目PCR PID
* @retval id 记录ID
* @retval -1 获取失败
*/
D_DBSrvID
d_dbase_get_srv_by_pids (D_DBTSID db_ts_id, D_U16 vpid, D_U16 apid, D_U16 pcrpid) D_FUNCPOSTFIT;


/** @brief 取得一个空闲的频道号
* @param[in] type 服务类型
* @retval num 频道号
* @retval -1 获取失败
*/
D_S16	    d_dbase_get_free_chan_num (D_DBSrvType type) D_FUNCPOSTFIT;
D_S16		d_dbase_get_free_chan_num_ex (D_DBSrvType srvtype, D_FEndType ftype) D_FUNCPOSTFIT;

/** @brief 从一个起始频道号开始向后分配一个空闲的频道号
* @param[in] type 服务类型
* @retval[in] num 起始频道号
* @retval -1 获取失败
*/
D_S16 d_dbase_get_free_chan_num_from (D_DBSrvType type, D_S16 start_num) D_FUNCPOSTFIT;
/** @brief 从一个起始频道号开始向前或向后分配一个空闲的频道号
* @param[in] type 服务类型
* @retval[in] num 起始频道号
* @retval[in] dir 0为向后，1为向前
* @retval -1 获取失败
*/
D_S16
d_dbase_get_free_chan_num_from_ex (D_DBSrvType type, D_S16 start_num, D_U8 dir) D_FUNCPOSTFIT;

/** @brief 查找下一个相邻的频道号  
* @param[in] start 当前频道号
* @param[in] srvtype 服务类型
* @param[in] ltob 查找方向(true向上,false向下)
* @param[in] favor 喜爱标志
* @retval num 频道号
* @retval -1 获取失败
*/
D_S16		d_dbase_get_next_chan_num (D_S16 num, D_DBSrvType type, D_Bool ltob, D_Bool favor) D_FUNCPOSTFIT;

/** @brief 根据节目号获取该位置的节目DID。注意一定要对获取的结果进行检测，-1为无效的DID，千万不能直接使用
* @param[in] type 服务类型
* @param[in] num 节目号
* @retval -1 无效的节目DID
* @retval 节目DID
*/
D_S16
d_dbase_get_srv_did_by_num (D_DBSrvType type, D_U16 num) D_FUNCPOSTFIT;

/** @brief 删除指定TS流的全部服务
* @param[in] db_ts_id ts记录ID
* @retval  D_OK 删除成功
* @retval  D_ERR 删除失败
*/
D_Result	d_dbase_delete_srvs_of_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief 删除指定卫星的全部服务
* @param db_sat_id 卫星记录ID
* @retval  D_OK 删除成功
* @retval  D_ERR 删除失败
*/
D_Result d_dbase_delete_srvs_of_sat (D_DBSATID db_sat_id) D_FUNCPOSTFIT;

/** @brief 删除指定前端类型的全部服务
* @param fendtype 前端类型
* @retval  D_OK 删除成功
* @retval  D_ERR 删除失败
*/
D_Result
d_dbase_delete_srvs_of_fendtype (D_FEndType fendtype) D_FUNCPOSTFIT;

/** @brief 检查数据库中是否有指定类型的服务
* @param[in] type 服务类型
* @retval  D_TRUE 有
* @retval  D_FALSE 无
*/
D_Bool		d_dbase_has_any_srv (D_DBSrvType type) D_FUNCPOSTFIT;
D_Bool    d_dbase_has_any_srv_ex (D_FEndType fendtype, D_DBSrvType type, D_DBTSID *db_ts_id) D_FUNCPOSTFIT;

/** @brief 取出数据库内的全部业务列表
* @param[in][out] rset 业务记录集
* @retval D_OK 获取成功
* @retval D_ERR 获取失败
*/
D_Result
d_dbase_get_srvs (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 获取TS下的服务列表
* @param[out] set 存放服务的记录集指针
* @param[in] ID TS记录ID
* @param[in] type 服务类型
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_get_srvs_by_ts (D_DBRecset *set, D_DBTSID id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 获取卫星下的服务列表
* @param[out] set 存放服务的记录集指针
* @param[in] ID 卫星记录ID
* @param[in] type 服务类型
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_get_srvs_by_sat (D_DBRecset *set, D_DBSATID id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief 删除指定TS流的全部事件
* @param[in] db_ts_id ts记录ID
* @retval  D_OK 删除成功
*/
D_Result d_dbase_delete_evts_of_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief 更新服务信息
* @param[in] id 服务记录ID
* @param[in] srvinfo 存放服务信息的数据缓冲区
* @param[in] dirty 是否将更改写到flash中，TRUE：写；FALSE：不写
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_dbase_update_srv_param (D_DBSrvID id, D_DBSrvInfo * srvinfo, D_Bool dirty) D_FUNCPOSTFIT;

/** @brief 移动或排序节目后，更改相应的节目号。移动或排序节目是在一个封闭的范围内对节目号进行逐一重置，所以直接更改即可。
* @param[in] id 服务记录ID
* @param[in] num 频道号
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result
d_dbase_update_chan_num_for_sort_move(D_DBSrvID id, D_S16 num) D_FUNCPOSTFIT;

/** @brief 取得指定类型的喜爱服务总数
* @param[in] type 服务类型
* @param[in] skip 是否去除已经设置为跳过的节目。D_TRUE:是；D_FALSE：否。
* @retval 服务总数
*/
D_U16
d_dbase_get_fav_srvs_cnt (D_DBSrvType srvtype, D_Bool skip) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dEvtTable.c**********************************************************************/

/** @brief 清空事件表*/
D_Result	d_dbase_clear_evt (void) D_FUNCPOSTFIT;

/** @brief 向事件表中加入一条记录
* @param[in] info	插入的事件信息
* @retval 成功返回事件ID
* @retval 失败返回-1
*/
D_DBEvtID	d_dbase_insert_evt (D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief 删除一条记录*/
D_Result	d_dbase_delete_evt (D_DBEvtID id) D_FUNCPOSTFIT;

/** @brief 删除所有过期事件
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_clear_out_time_evt (void) D_FUNCPOSTFIT;

/** @brief 取出一个网络相关信息
* @param[in] id	事件的ID
* @param[in] info 事件信息区指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_evt_info (D_DBEvtID id, D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief 取得一个服务的当前事件
* @param[in] srv_id	服务ID
* @param[in] now 当前时间
* @retval 成功返回事件ID
* @retval 失败返回-1
*/
D_DBEvtID	d_dbase_get_present_evt (D_DBSrvID srv_id, D_Time now) D_FUNCPOSTFIT;

/** @brief 取得一个服务的下一个事件
* @param[in] srv_id	服务ID
* @param[in] now 当前时间
* @retval 成功返回事件ID
* @retval 失败返回第一个事件的ID
*/
D_DBEvtID d_dbase_get_following_evt (D_DBSrvID srv_id, D_Time now) D_FUNCPOSTFIT;

/** @brief 取得指定的事件列表
* @param[in] srv_id	服务ID
* @param[in] begin 开始时间
* @param[in] end 结束时间
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_evts (D_DBSrvID srv_id, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得指定类型的事件
* @param[in] type	事件类型
* @param[in] begin 事件起始时间
* @param[in] end 事件结束时间
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_evts_by_type (D_U8 type, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得指定事件ID的事件
* @param[in] srv_id	服务ID
* @param[in] evt_id 事件ID
* @param[in] start	服务起始时间
* @param[in] duration 事件持续时间
* @retval 成功返回时间ID
* @retval 失败返回-1
*/
D_DBEvtID d_dbase_get_evt_by_id (D_DBSrvID srv_id, D_U16 evt_id,D_Time start, D_Time duration) D_FUNCPOSTFIT;

/** @brief 预定或取消预定一个节目
* @param[in] evt	事件ID
* @param[in] sub 预定或取消标记
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_subscribe_evt (D_DBEvtID id, D_Bool subscribe) D_FUNCPOSTFIT;

/** @brief 设定一个事件的描述信息
* @param[in] id	事件ID
* @param[in] descr 描述信息指针
* @param[in] size 信息长度
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_set_evt_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief 设定一个事件的扩展描述信息
* @param[in] id	事件ID
* @param[in] descr 扩展描述信息指针
* @param[in] size 信息长度
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_set_evt_ext_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief 取得一个事件的描述信息
* @param[in] id	事件ID
* @param[in] descr 描述信息指针
* @param[in] size 信息长度
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Size		d_dbase_get_evt_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief 取得一个事件的扩展描述信息
* @param[in] id	事件ID
* @param[in] descr 扩展描述信息指针
* @param[in] size 信息长度
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Size		d_dbase_get_evt_ext_descr (D_DBEvtID id, D_Char *descr, D_Size size) D_FUNCPOSTFIT;

/** @brief 删除指定服务的全部事件
* @param[in] db_srv_id	服务ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_delete_evts_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dNVODTable.c**********************************************************************/
#ifdef D_SUPPORT_NOVD

/** @brief 清空NVOD数据库*/
D_Result	d_dbase_clear_nvod (void) D_FUNCPOSTFIT;

/** @brief 插入一个NVOD节目
* @retval 成功插入返回插入节目的ID
* @retval 插入失败返回-1
*/
D_DBNVodID	d_dbase_insert_nvod (void) D_FUNCPOSTFIT;

/** @brief 删除一个NVOD节目
* @param[in] nvod	NVOD节目ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_delete_nvod (D_DBNVodID nvod) D_FUNCPOSTFIT;

/** @brief 增加参考服务
* @param[in] nvod	NVOD节目ID
* @param[in] ref 增加的参考服务ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_add_ref_srv (D_DBNVodID nvod, D_DBSrvID ref) D_FUNCPOSTFIT;

/** @brief 删除参考服务
* @param[in] nvod	NVOD节目ID
* @param[in] ref 参考服务ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_del_ref_srv (D_DBNVodID nvod, D_DBSrvID ref) D_FUNCPOSTFIT;

/** @brief 增加时移服务
* @param[in] nvod	NVOD节目ID
* @param[in] ref 参考服务ID
* @param[in] shift	增加的时移服务ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_add_shifted_srv (D_DBNVodID nvod, D_DBSrvID ref, D_DBSrvID shift) D_FUNCPOSTFIT;

/** @brief 取得NVod服务列表
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_nvods (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得NVOD中的参考服务
* @param[in] nvod_id	NVOD节目ID
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_ref_srvs (D_DBNVodID nvod, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得参考事件列表
* @param[in] nvod_id	NVOD节目ID
* @param[in] begin	起始时间
* @param[in] end	结束时间	
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_ref_evts (D_DBNVodID nvod, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得指定参考事件的时移事件列表
* @param[in] nvod_id	NVOD节目ID
* @param[in] ref 参考事件ID
* @param[in] now	当前时间
* @param[in] p	
* @param[in] f	
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_pf_shifted_evts (D_DBNVodID nvod_id, D_DBEvtID ref, D_Time now, D_Bool p, D_Bool f, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得指定参考事件的时移事件列表
* @param[in] nvod_id	NVOD节目ID
* @param[in] ref 参考事件ID
* @param[in] begin	起始时间
* @param[in] end	结束时间	
* @param[out] set 记录集指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_shifted_evts (D_DBNVodID nvod, D_DBEvtID ref, D_Time begin, D_Time end, D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 删除含有指定服务的NVOD记录
* @param[in] db_srv_id	服务ID
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_delete_nvods_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 取得含有指定服务的NVOD记录
* @param[in] db_srv_id	服务ID
* @retval 成功返回NVOD ID
* @retval 失败返回-1
*/
D_DBNVodID	d_dbase_get_nvod_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 取得NVOD相关信息
* @param[in] nvod	NVOD节目ID
* @param[in] info 服务信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result	d_dbase_get_nvod_info (D_DBNVodID nvod, D_DBSrvInfo *info) D_FUNCPOSTFIT;

/** @brief 取得一个时移业务的参考业务
* @param[in] db_srv_id	服务ID
* @retval 成功返回参考业务ID
* @retval 失败返回-1
*/
D_DBSrvID	d_dbase_get_ref_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 取得一个时移事件的参考事件
* @param[in] db_evt_id	时移事件ID
* @retval 成功返回参考事件ID
* @retval 失败返回-1
*/
D_DBEvtID	d_dbase_get_ref_of_evt (D_DBEvtID db_evt_id) D_FUNCPOSTFIT;

#endif

/************************************************end**********************************************************************/

/************************************************dSubTable.c**********************************************************************/

/** @brief 清空预订节目表*/
D_Result	d_dbase_clear_subscribe (void) D_FUNCPOSTFIT;

/** @brief 加入预订节目记录
* @param[in] info 预约信息指针
* @retval 插入成功返回记录ID
* @retval 插入失败返回-1
*/
D_DBSubID	d_dbase_insert_subscribe (D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief 删除一个预订节目记录
* @param[in] id 记录ID
* @retval 删除成功返回D_OK
* @retval 删除失败返回D_ERR
*/
D_Result	d_dbase_delete_subscribe (D_DBSubID id) D_FUNCPOSTFIT;

/** @brief 取得一个预订节目记录ID
* @param[in] srv 服务ID
* @param[in] evt_id 事件ID
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBSubID	d_dbase_get_subscribe (D_DBSrvID srv, D_U16 evt_id) D_FUNCPOSTFIT;

/** @brief 取得一个特定时间段内预订节目的ID
* @param[in] begin 起始时间
* @param[in] end 结束时间
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBSubID	d_dbase_get_subscribe_by_time (D_Time begin, D_Time end) D_FUNCPOSTFIT;

/** @brief 取得一个特定开始时间点的预订节目的ID
* @param[in] begin 起始时间
* @param[in] end 结束时间
* @retval 获取成功返回记录ID
* @retval 获取失败返回-1
*/
D_DBSubID d_dbase_get_subscribe_overlap (D_Time begin, D_Time end) D_FUNCPOSTFIT;

/** @brief 取得预定节目列表
* @param[out] set 记录集指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result	d_dbase_get_subscribes (D_DBRecset *set) D_FUNCPOSTFIT;

/** @brief 取得一个预订节目记录信息
* @param[in] id 预约记录ID
* @param[in] info 预约事件信息指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result	d_dbase_get_subscribe_info (D_DBSubID id, D_DBEvtInfo *info) D_FUNCPOSTFIT;

/** @brief 删除指定服务的全部预订事件
* @param[in] db_srv_id 服务ID
* @retval 删除成功返回D_OK
* @retval 删除失败返回D_ERR
*/
D_Result	d_dbase_delete_subscribes_of_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief 预订函数检查:删除已结束预订节目,检查是否有节目到期
* @param[in] del	是否删除过期节目
* @param[in] sub_callback	到期节目回调
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_dbase_check_subscribe (D_Bool del, D_Time advance_time, D_Result (*sub_callback) (D_DBSubID sub) D_FUNCPOSTFIT) D_FUNCPOSTFIT;

/** @brief 加入预订服务记录
* @param[in] info 预约信息指针
* @retval 插入成功返回预约记录ID
* @retval 插入失败返回-1
*/
D_DBSubID
d_dbase_insert_srv_subscribe (D_DBSubInfo *info) D_FUNCPOSTFIT;

/** @brief 取得一个预订服务的信息
* @param[in] id 预约服务ID
* @param[in] info 预约服务信息指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result
d_dbase_get_srv_sub_info (D_DBSubID id, D_DBSubInfo *info) D_FUNCPOSTFIT;

/** @brief 取得一个预订服务的信息
* @param[in] id 预约服务ID
* @param[in] info 预约服务信息指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result
d_dbase_get_srv_sub_info (D_DBSubID id, D_DBSubInfo *info) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/

/************************************************dBouqTable.c**********************************************************************/
/** @brief 清空业务群表*/
D_Result	d_dbase_clear_bouq (void) D_FUNCPOSTFIT;

/** @brief 向业务群表中加入一条记录
* @param[in] info 插入的业务群记录信息
* @retval id 插入成功，返回记录ID
* @retval -1 插入失败
*/
D_DBNetID	d_dbase_insert_bouq (D_DBBouqInfo *info) D_FUNCPOSTFIT;

/** @brief 删除一条业务群记录
* @param[in] id 业务群ID
* @retval D_OK 删除成功
* @retval D_ERR 删除失败
*/
D_Result	d_dbase_delete_bouq (D_DBBouqID id) D_FUNCPOSTFIT;

/** @brief 取出一个业务群相关信息
* @param[in] id 业务群ID
* @param[in] info 读取后业务群信息存放区指针
* @retval D_OK 读取成功
* @retval D_ERR 读取失败
*/
D_Result	d_dbase_get_bouq_info (D_DBBouqID id, D_DBBouqInfo *info) D_FUNCPOSTFIT;

/** @brief 取出数据库内的全部业务群列表
* @param[out] rset 业务群记录集
* @retval D_OK 获取成功
* @retval D_ERR 获取失败
*/
D_Result	d_dbase_get_bouqs (D_DBRecset *rset) D_FUNCPOSTFIT;

/** @brief 取得指定名字的业务群
* @param[in] name 业务群名称
* @retval id 获取成功，返回业务群ID
* @retval -1 获取失败
*/
D_DBBouqID d_dbase_get_bouqs_by_name(const D_Char *bouq_name) D_FUNCPOSTFIT;

/************************************************end**********************************************************************/


/************************以下函数有待整理以确定是否保留******************************************************************/

/** @brief 取得TS相关信息
* @param[in] id TS ID
* @param[in] info TS信息指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result d_dbase_get_ts_info_by_num(D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief 取得TS相关信息,并取得对应的db_ts_id
* @param[in] id 记录集序号
* @param[in] info TS信息指针
* @param[in] db_ts_id TS ID
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
/*id 为记录集里序号id*/
D_Result d_dbase_get_ts_info_by_num_ex(D_ID id, D_DBTSInfo *info, D_DBTSID *db_ts_id) D_FUNCPOSTFIT;

//按搜索类型清除数据库有关的节目记录
D_Result 	d_dbase_delete_srvs_bytype(D_FEndType type)D_FUNCPOSTFIT;

/** @brief 通过ts id, original network id, service id 取得服务
*** @brief 先找频点，再在频点下找服务(频道)
* @param[in] db_net_id	网络ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	原始网络ID
* @param[in] srv_id	服务ID
* @retval 成功返回记录ID
* @retval 失败返回-1
*/
D_DBSrvID	d_dbase_get_srv_by_ids (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id) D_FUNCPOSTFIT;
D_DBSrvID   d_dbase_get_srv_by_ids_ex (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_FEndType fendtype,D_U16 srv_id) D_FUNCPOSTFIT;

/** @brief 通过ts id, original network id, service id 取得服务
*** @brief 遍历节目数据库里所有的服务(频道)，直到找到符合的。
* @param[in] db_net_id	网络ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	原始网络ID
* @param[in] srv_id	服务ID
* @retval 成功返回记录ID
* @retval 失败返回-1
*/
D_DBSrvID
d_dbase_get_srv_by_ids_new (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id) D_FUNCPOSTFIT;

#if 0
/** @brief 通过ts id, original network id, service id, event id 取得服务
* @param[in] db_net_id	网络ID
* @param[in] ts_id	TS ID
* @param[in] org_net_id	原始网络ID
* @param[in] srv_id	服务ID
* @param[in] evt_id	事件ID
* @retval 成功返回事件ID
* @retval 失败返回-1
*/
D_DBEvtID	d_dbase_get_evt_by_ids (D_DBNetID db_net_id, D_U16 ts_id, D_U16 org_net_id, D_U16 srv_id, D_U16 evt_id) D_FUNCPOSTFIT;
#endif
/** @brief 更新网络相关信息
* @param[in] id	网络记录ID
* @param[in] info	网络信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_updata_net_info (D_DBNetID id, D_DBNetInfo *info) D_FUNCPOSTFIT;

/** @更新某个ts信息
* @param[in] id TS ID
* @param[in] info TS信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_updata_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT;

/** @brief 修改service的频道号，只用于更新全部同类型节目的频道号  
* @param[in] id 服务记录ID
* @param[in] num 频道号
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_num (D_DBSrvID id, D_S16 num) D_FUNCPOSTFIT;

/** @brief 修改service的名字
* @param[in] id 服务记录ID
* @param[in] name 节目名
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result
d_dbase_update_srv_name (D_DBSrvID id, D_Char *name) D_FUNCPOSTFIT;

/** @brief 修改service的加锁标志
* @param[in] id 服务记录ID
* @param[in] lock 加锁标志
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_lock (D_DBSrvID id, D_Bool lock) D_FUNCPOSTFIT;

/** @brief 修改service的跳过标志
* @param[in] id 服务记录ID
* @param[in] skip 跳过标志
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_skip (D_DBSrvID id, D_Bool skip) D_FUNCPOSTFIT;

/** @brief 修改service的音量设置
* @param[in] id 服务记录ID
* @param[in] vol 音量
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_volume (D_DBSrvID id, D_U8 vol) D_FUNCPOSTFIT;

/** @brief 修改service的声道设置
* @param[in] id 服务记录ID
* @param[in] track 声道
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_aud_track (D_DBSrvID id, D_AudTrack track) D_FUNCPOSTFIT;

/** @brief 修改service的伴音设置
* @param[in] id 服务记录ID
* @param[in] acc 伴音
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_aud_acc (D_DBSrvID id, D_U8 acc) D_FUNCPOSTFIT;

/** @brief 修改service的PMT设置
* @param[in] id 服务记录ID
* @param[in] v_pid 视频PID
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result	d_dbase_update_srv_pmt (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec) D_FUNCPOSTFIT;
		
/** @brief 修改service的PMT设置,包含PMT_PID*/
D_Result	d_dbase_update_srv_pmt_ex (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec,
		D_U16 pcr_pid, D_U16 pmt_pid) D_FUNCPOSTFIT;
D_Result d_dbase_update_srv_pmt_ex2 (D_DBSrvID id, D_U16 v_pid, D_VidCodecType v_codec, D_U16 a1_pid, D_AudCodecType a1_codec, D_U16 a2_pid, D_AudCodecType a2_codec, 
                D_U16 a3_pid, D_AudCodecType a3_codec, D_U16 a4_pid, D_AudCodecType a4_codec, D_U16 pcr_pid, D_U16 pmt_pid) D_FUNCPOSTFIT;

/** @brief 修改service的喜爱标志 add by bianxy 2006-8-17  
* @param[in] id 服务记录ID
* @param[in] favor_type 八个喜爱之一
* @param[in] favor 喜爱标志
* @retval D_OK 更新成功
* @retval D_ERR 更新失败
*/
D_Result d_dbase_update_srv_favor_ex (D_DBSrvID id, D_U8 favor_type, D_Bool favor) D_FUNCPOSTFIT;

/** @brief 开机加载flash记录集中的数据到对应的memory缓冲区中
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_load_flash_ex(void)D_FUNCPOSTFIT;

/** @brief 表数据有改动时，将改动数据写入到记录集中
* @param[in] T_id	table ID
* @param[in] F_id	field ID
* @param[in] D_id	记录ID
* @param[in] length	更改的数据长度
* @param[in] data	数据缓冲区指针
* @param[in] dirty	是否刷新到flash的标记
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_record_flash_flush_tbl(D_U8 T_id,D_S8 F_id,D_U16 D_id,D_U16 length,D_U8*data,D_Bool dirty)D_FUNCPOSTFIT;

/** @brief block数据有改动时，将改动数据写入到记录集中 liuwf
* @param[in] B_id	block ID
* @param[in] offset	偏移地址
* @param[in] size	更改的数据大小
* @param[in] data	数据缓冲区指针
* @param[in] dirty	是否刷新到flash的标记
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result d_dbase_record_flash_flush_blk(D_U8 B_id, D_U16 offset, D_U16 size, D_U8*data, D_Bool dirty)D_FUNCPOSTFIT;

/************************end*************************************************************************************************/


#ifdef  __cplusplus
}
#endif

#endif
/*EOF*/
/**@}*/
