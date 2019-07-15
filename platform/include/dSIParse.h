/** @file
* @brief SI分析模块
* @author 龚克
* @date 2005-6-14 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_SI_PARSE_H_
#define _D_SI_PARSE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dMMan.h"
#include "dTypes.h"
#include "dFEnd.h"

#define D_SI_RECORD_SEC_INFO	0

/** @brief 遍历链表中的元素*/
#define D_SI_FOR_EACH_BEGIN(_t,_l,_d)\
		if (_l) {\
			_d = (_t*) (_l);\
			do {\

#define D_SI_FOR_EACH_END(_t,_l,_d)\
			} while (((_d) = (_t*) ((D_List*)(_d))->next) != (_t*) (_l));\
		}

/** @brief 在链表中加入一个元素或链表   (注:在结尾加入)*/
#define D_SI_LIST_ADD(_l,_d)\
		D_MACRO_BEGIN\
			if (_l) {\
				D_List	*t1, *t2;\
				t1 = ((D_List*)(_l))->prev;\
				t2 = ((D_List*)(_d))->prev;\
				t1->next = (D_List*)(_d);\
				t2->next = (D_List*)(_l);\
				((D_List*)(_l))->prev = t2;\
				((D_List*)(_d))->prev = t1;\
			} else {\
				(_l) = (D_List*)(_d);\
			}\
		D_MACRO_END
		
/** @brief 在链表中一个元素后加入一个元素或链表*/
#define D_SI_LIST_ADD_NODE(_c,_d)\
		D_MACRO_BEGIN\
			if ((_c) && (_d)) {\
				D_List	*t1, *t2;\
				t1 = ((D_List*)(_c))->next;\
				t2 = ((D_List*)(_d))->prev;\
				t2->next = t1;\
				t1->prev = t2;\
				((D_List*)(_c))->next = (D_List*)(_d);\
				((D_List*)(_d))->prev = ((D_List*)(_c));\
			} else if(_d){\
				(_c) = (D_List*) (_d);\
			}\
		D_MACRO_END
		
/** @brief 在链表中移出一个元素*/
#define D_SI_LIST_REMOVE(_l,_d)\
		D_MACRO_BEGIN\
			if ((_l)&& (_d)) {\
                if(((D_List*)(_l) == (D_List*)(_d)) && (((D_List*)(_d))->next == (D_List*)(_d))){\
                    (_l) = NULL;\
                }else{\
    				D_List	*t1, *t2;\
    				t1 = ((D_List*)(_d))->prev;\
    				t2 = ((D_List*)(_d))->next;\
    				t1->next = t2;\
    				t2->prev = t1;\
    				if((D_List*)(_l) == (D_List*)(_d)){\
                        (_l)= t2;\
                    }\
                }\
                ((D_List*)(_d))->prev = (D_List*)(_d);\
                ((D_List*)(_d))->next = (D_List*)(_d);\
			}\
		D_MACRO_END
		
/** @brief 分配一个链表元素*/
#define D_SI_ALLOC(_m,_d)\
		D_MACRO_BEGIN\
			_d = d_mman_alloc (_m, sizeof (*(_d)));\
			if (_d) {\
				memset (_d, 0, sizeof (*(_d)));\
				((D_List*)(_d))->prev = (D_List*)(_d);\
				((D_List*)(_d))->next = (D_List*)(_d);\
			} else {\
				D_ERROR ("SI cannot allocate memory %d bytes %s %d\n", sizeof (*(_d)), __FILE__,__LINE__);\
			}\
		D_MACRO_END

/** @brief 释放一个链表元素*/
//#define D_SI_FREE(_m,_d) if(_d){d_mman_free (_m, (_d));}

		
/** @brief 链表*/
typedef struct _D_List D_List;
struct _D_List{
	D_List	*prev;
	D_List	*next;
};

/** @brief 描述符*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_Descr;

/** @brief Registration描述符*/
typedef struct {
	D_List  list;
	D_U8    tag;
	D_U32   format_identifier;
} D_RegistrationDescr;

/** @brief CA描述符*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ca_sys_id;
	D_U16		 ca_pid;
} D_CADescr;

/** @brief ISO639 Language元素*/
typedef struct {
	D_List	 list;
	D_U8     country[3];
	D_U8     audiotype;
} D_ISO639LanguageDescrItem;

/** @brief ISO639 Language描述符*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_ISO639LanguageDescr;



/** @brief 业务群名称描述符tag:0x47*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	*name;
} D_BouquetNameDescr;

/** @brief CA identifier descriptor tag:0x53*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ca_system_id;
} D_CAIdentifierDescr;

/** @brief Component描述符tag:0x50*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 content;
	D_U8		 type;
	D_U8		 comp_tag;
	D_Char	 lang[3];
	D_Char	*name;
} D_ComponentDescr;

/** @brief 内容描述符0x:54*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 content;
} D_ContentDescr;

/** @brief cuntry code list*/
typedef struct {
	D_List	 list;
	D_Char	 country_code[3];	
} D_CountryItem;

/** @brief Country availability descriptor tag:0x49*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	avail_flag;
	D_List	*countrys;
} D_CountryAvailabilityDescr;

/** @brief Data broadcast descriptor tag:0x64*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	comp_tag;
	D_U16	db_id;		
	D_U8    selector_len;
	D_U8	*selector;
	D_U8	 lang[3];
	D_Char	*name;
} D_DataBroadcastDescr;

/** @brief Data broadcast id descriptor tag:0x66*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U16	db_id;		
} D_DataBroadcastIdDescr;

/** @brief 有线网络传输描述符 tag:0x44*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		fec_outer;
	D_U8		fec_inner;
	D_FEndFreq	freq;	/*单位100Hz*/
	D_FEndBaud	baud;	/*单位100symbol/s*/
	D_FEndMod	mod;	
} D_CableDeliverySystemDescr;

/** @brief 卫星网络传输描述符tag:0x43*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_FEndFreq	freq;	/*单位MHz*/
	D_FEndBaud	baud;	/*单位ksymbol/s*/
	D_U16		position;/*单位0.1degrees*/
	D_U8				pol;
	D_Bool			west;
	D_U8		mod;    /*0x01:QPSK,  other reserved*/
	D_U8		fec_inner;
} D_SatelliteDeliverySystemDescr;

/** @brief 地面网络传输描述符tag:0x5A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_FEndFreq	freq;	/*单位10Hz*/
	D_U8		band;	/*0x00 :8MHz,  0x01:7MHz,  other reserved*/
	D_U8				constellation;
	D_U8				hierarchy_inf;
	D_U8				code_rate_HP_stream;
	D_U8				code_rate_LP_stream;
	D_U8				guard_interval;
	D_U8				transmission_mode;
	D_U8				other_frequency_flag;
}D_TerrestrialDeliverySystemDescr;

/** @brief 扩展事件描述符元素*/
typedef struct {
	D_List	 list;
	D_Char	*tag;
	D_Char	*text;
} D_ExtendedEventDescrItem;

/** @brief 扩展事件描述符tag:0x4E*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	 lang[3];
	D_List	*items;
	D_U8		 descr_num;
	D_U8		 last_descr_num;
	D_Char	*text;
} D_ExtendedEventDescr;


/** @brief Frequency list descriptor item*/
typedef struct {
	D_List	 list;	
	D_U32		centre_freq;
} D_FrequencyListDescrItem;
/** @brief Frequency list descriptor tag:0x62*/
typedef struct {
	D_List	 list;
	D_U8	 tag;
	D_U8	 type;
	D_List	*freq_list;
} D_FrequencyListDescr;

/** @brief Linkage descriptor tag:0x4A*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	type;
	D_U16	ts_id;
	D_U16	org_net_id;
	D_U16	srv_id;	
	D_U8	private_dat_len;
	D_U8	*private_dat;	
} D_LinkageDescr;

/** @brief 本地事件偏移描述符tag:0x58*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	 country[3];
	D_U8		 region_id;
	D_S8	 	 polar;
	D_Time	 offset;
	D_Time	 time_change;
	D_Time	 next_time_offset;
} D_LocalTimeOffsetDescr;

/** @brief 马赛克元素*/
typedef struct {
	D_List	 list;
/*	D_U8			tag;*/
	D_U8		 log_cell_id;
	D_U8		 presentation;
	D_U8		 cell_ids[8];
	D_U8		 link_type;
	union {
		D_U16	 bouq_id;
		struct {
			D_U16	org_net_id;
			D_U16	ts_id;
			D_U16	srv_id;
		} srv;
		struct {
			D_U16	org_net_id;
			D_U16	ts_id;
			D_U16	srv_id;
		} mosaic;
		struct {
			D_U16	org_net_id;
			D_U16	ts_id;
			D_U16	srv_id;
			D_U16	evt_id;
		} evt;
	} link;
} D_MosaicDescrItem;

/** @brief 马赛克描述符tag:0x51*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Bool	 entry;
	D_U8		 rows;
	D_U8		 cols;
	D_List	*multi_text;
} D_MosaicDescr;

/** @brief 算通定义私有数据*/
/** 逻辑屏幕*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U16	start_x;
	D_U16	start_y;
	D_U16	end_x;
	D_U16	end_y;
} D_MosaicLogicScreenDescr;

/** @brief 多语言文字*/
typedef struct {
	D_List	 list;
	D_Char	 country[3];
	D_Char	*text;
} D_MultilingualText;

typedef struct {
	D_List	 list;
	D_Char	 country[3];
	D_Char	*prov_name;
    D_Char	*srv_name;
} D_MultilingualSrvText;

/** @brief 多语言业务群名描述符tag:0x5C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualBouquetNameDescr;

/** @brief 多语言元素描述符tag:0x5E*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualComponentDescr;

/** @brief 多语言网络名描述符tag:0x5B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualNetworkNameDescr;

/** @brief 多语言服务名描述符tag:0x5D*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualServiceNameDescr;

/** @brief NVOD参考业务描述符tag:0x4B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ts_id;
	D_U16		 org_net_id;
	D_U16		 srv_id;
} D_NVODReferenceDescr;

/** @brief 网络名描述符Network name descriptor tag:0x40*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	*name;
} D_NetworkNameDescr;

/** @brief 父母收看等级描述符tag:0x55  add by liux 2006-8-23*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	 country[3];
	D_U8		 rating;
} D_ParentalRatingDescr;

/** @brief Private data specifier descriptor tag:0x5F*/
typedef struct {
	D_List	 list;
	D_U8		 tag;	
	D_U32		 private_dat_spec;
} D_PrivateDataSpecifierDescr;

/** @brief Short smoothing buffer descriptor tag:0x61*/
typedef struct {
	D_List	 list;
	D_U8		 tag;	
	D_U8		size;
	D_U8		leak_rate;
	D_U8		*reserved;
} D_ShortSmoothingBufferDescr;

/** @brief 服务描述符Service descriptor tag:0x48*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 type;
	D_Char	*prov_name;
	D_Char	*srv_name;
} D_ServiceDescr;

/** @brief 服务列表描述符Service list descriptor tag:0x41*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 type;
	D_U16		 srv_id;
} D_ServiceListDescr;

/** @brief 服务转移描述符tag:0x60*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 org_net_id;
	D_U16		 ts_id;
	D_U16		 srv_id;
} D_ServiceMoveDescr;

/** @brief 短事件描述符tag:0x4D*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	 lang[3];
	D_Char	*name;
	D_Char	*descr;
} D_ShortEventDescr;

/** @brief 流标记描述符tag:0x52*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 comp_tag;
} D_StreamIdentifierDescr;

/** @brief Stuffing descriptor tag:0x42*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	*stuffing_byte;	
} D_StuffingDescr;

/** @brief Subtitling descriptor tag:0x59*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	lang[3];
	D_U8	type;	
	D_U16	com_page_id;
	D_U16	anc_page_id;
} D_SubtitlingDescr;

/** @brief Telephone descriptor tag:0x57*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 oreign_avail;
	D_U8		 type;
	D_U8		 country_prefix_len;
	D_U8		 international_area_code_len;
	D_U8		 operator_code_len;
	D_U8		 national_area_code_len;
	D_U8		 core_number_len;
	D_U8		*country_prefix;
	D_U8		*international_area_code;
	D_U8		*operator_code;
	D_U8		*national_area_code;
	D_U8		*core_number;
} D_TelephoneDescr;

/** @brief Teletext descriptor tag:0x56*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U8	lang[3];
	D_U8	type;	
	D_U8	magazine_number;
	D_U8	page_number;
} D_TeletextDescr;

/** @brief 时移事件描述符tag:0x4F*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ref_srv_id;
	D_U16		 ref_evt_id;
} D_TimeShiftedEventDescr;

/** @brief 时移业务描述符tag:0x4C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ref_srv_id;
} D_TimeShiftedServiceDescr;


/** @brief AC3 描述符tag:0x6A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_AC3Descr;

/** @brief EAC3 描述符tag:0x7A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_EAC3Descr;

/** @brief DTS 描述符tag:0x7B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_DTSDescr;

/** @brief AAC 描述符tag:0x7C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_AACDescr;



/** @brief Section 信息*/
typedef struct {
	D_U8		 tab_id;
	D_U8		 version;
	D_U16		 ext_tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 seg_last_sec_num;
	D_U8		 last_tab_id;
} D_SectionInfo;

/** @brief 基础流*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 pid;
	D_U8		 type;
} D_ElementStream;

/** @brief PMT表*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_List	*eses;
	D_U16		 prog_num;
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
	D_U16		 pcr_pid;
} D_Pmt;

/** @brief PAT表*/
typedef struct {
	D_List	 list;
	D_U16		 ts_id;
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
	D_U16		 pid;
	D_U16		 prog_num;
} D_Pat;

/** @brief CAT表*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
} D_Cat;

/** @brief NIT表中的TS数据*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 ts_id;
	D_U16		 org_net_id;
} D_NitTS;

/** @brief BAT表中的TS数据*/
typedef D_NitTS	D_BatTS;
typedef struct {
	D_List	 list;
	D_List	*tses;
	D_List	*descrs;
	D_U16		 net_id;
	D_Bool	 is_act;
#if 1//D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
} D_Nit;

/** @brief BAT表*/
typedef struct {
	D_List	 list;
	D_List	*tses;
	D_List	*descrs;
	D_U16		 bouq_id;
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
} D_Bat;

/** @brief SDT表*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 ts_id;
	D_U16		 org_net_id;
	D_Bool	 is_act;
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 version;
#endif
	D_U16		 srv_id;
	D_Bool	 pf_flag;
	D_Bool	 sch_flag;
	D_Bool	 ca;
	D_U8		 status;
} D_Sdt;

/** @brief EIT表*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 srv_id;
	D_U16		 ts_id;
	D_U16		 org_net_id;
	D_U16		 evt_id;
	D_U8     rating;            /* liux 观看等级 */
#if D_SI_RECORD_SEC_INFO
	D_U8		 tab_id;
	D_U8		 last_tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 seg_last_sec_num;
	D_U8		 version;
#endif
	D_Time	 start;
	D_Time	 duration;
	D_Bool	 ca;
	D_U8		 status;
} D_Eit;

/** @brief TDT表*/
typedef struct {
	D_List	 list;
	D_Time	 utc;
	D_U8		 tab_id;
} D_Tdt;

/** @brief TOT表*/
typedef struct {
	D_List	 list;
	D_Time	 utc;
	D_U8		 tab_id;
	D_List	*descrs;
} D_Tot;

/** @brief SI分析描述子前钩子 */
typedef struct
{
	D_U8 *buf;
	D_HMMan hmm;
	D_List **dds;
	D_Result *ret;
}D_SIParseHookPre;

/** @brief SI分析描述子后钩子 */
typedef struct
{
	D_U8 *buf;
	D_HMMan hmm;
	D_List **dds;
}D_SIParseHookRet;

/** @brief 分析secion 通用信息
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param info	返回section通用信息
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_si_parse_section (D_U8 *buf, D_S16 length, D_SectionInfo *info) D_FUNCPOSTFIT;

/** @brief 分析一个描述符
* @param buf    缓冲区地址
* @param hmm    内存管理器句柄
* @return   成功返回描述符指针,失败返回NULL
*/
D_List* d_si_parse_descr (D_U8 *buf, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析指定缓冲区内的所有描述符
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回描述符结构链表,失败返回NULL
*/
D_List*	d_si_parse_descrs (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个PAT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回PAT结构链表,失败返回NULL
*/
D_List*	d_si_parse_pat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个PMT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回PMT结构链表,失败返回NULL
*/
D_List*	d_si_parse_pmt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个CAT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回CAT结构链表,失败返回NULL
*/
D_List*	d_si_parse_cat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个NIT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回NIT结构链表,失败返回NULL
*/
D_List*	d_si_parse_nit (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个SDT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回SDT结构链表,失败返回NULL
*/
D_List*	d_si_parse_sdt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个BAT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回BAT结构链表,失败返回NULL
*/
D_List*	d_si_parse_bat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个EIT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回EIT结构链表,失败返回NULL
*/
D_List*	d_si_parse_eit (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个TDT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回TDT结构链表,失败返回NULL
*/
D_List*	d_si_parse_tdt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief 分析一个TOT section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回描述符结构链表,失败返回NULL
*/
D_List*	d_si_parse_tot (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
