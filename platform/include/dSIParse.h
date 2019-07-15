/** @file
* @brief SI����ģ��
* @author ����
* @date 2005-6-14 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
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

/** @brief ���������е�Ԫ��*/
#define D_SI_FOR_EACH_BEGIN(_t,_l,_d)\
		if (_l) {\
			_d = (_t*) (_l);\
			do {\

#define D_SI_FOR_EACH_END(_t,_l,_d)\
			} while (((_d) = (_t*) ((D_List*)(_d))->next) != (_t*) (_l));\
		}

/** @brief �������м���һ��Ԫ�ػ�����   (ע:�ڽ�β����)*/
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
		
/** @brief ��������һ��Ԫ�غ����һ��Ԫ�ػ�����*/
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
		
/** @brief ���������Ƴ�һ��Ԫ��*/
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
		
/** @brief ����һ������Ԫ��*/
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

/** @brief �ͷ�һ������Ԫ��*/
//#define D_SI_FREE(_m,_d) if(_d){d_mman_free (_m, (_d));}

		
/** @brief ����*/
typedef struct _D_List D_List;
struct _D_List{
	D_List	*prev;
	D_List	*next;
};

/** @brief ������*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_Descr;

/** @brief Registration������*/
typedef struct {
	D_List  list;
	D_U8    tag;
	D_U32   format_identifier;
} D_RegistrationDescr;

/** @brief CA������*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ca_sys_id;
	D_U16		 ca_pid;
} D_CADescr;

/** @brief ISO639 LanguageԪ��*/
typedef struct {
	D_List	 list;
	D_U8     country[3];
	D_U8     audiotype;
} D_ISO639LanguageDescrItem;

/** @brief ISO639 Language������*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_ISO639LanguageDescr;



/** @brief ҵ��Ⱥ����������tag:0x47*/
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

/** @brief Component������tag:0x50*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 content;
	D_U8		 type;
	D_U8		 comp_tag;
	D_Char	 lang[3];
	D_Char	*name;
} D_ComponentDescr;

/** @brief ����������0x:54*/
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

/** @brief �������紫�������� tag:0x44*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		fec_outer;
	D_U8		fec_inner;
	D_FEndFreq	freq;	/*��λ100Hz*/
	D_FEndBaud	baud;	/*��λ100symbol/s*/
	D_FEndMod	mod;	
} D_CableDeliverySystemDescr;

/** @brief �������紫��������tag:0x43*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_FEndFreq	freq;	/*��λMHz*/
	D_FEndBaud	baud;	/*��λksymbol/s*/
	D_U16		position;/*��λ0.1degrees*/
	D_U8				pol;
	D_Bool			west;
	D_U8		mod;    /*0x01:QPSK,  other reserved*/
	D_U8		fec_inner;
} D_SatelliteDeliverySystemDescr;

/** @brief �������紫��������tag:0x5A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_FEndFreq	freq;	/*��λ10Hz*/
	D_U8		band;	/*0x00 :8MHz,  0x01:7MHz,  other reserved*/
	D_U8				constellation;
	D_U8				hierarchy_inf;
	D_U8				code_rate_HP_stream;
	D_U8				code_rate_LP_stream;
	D_U8				guard_interval;
	D_U8				transmission_mode;
	D_U8				other_frequency_flag;
}D_TerrestrialDeliverySystemDescr;

/** @brief ��չ�¼�������Ԫ��*/
typedef struct {
	D_List	 list;
	D_Char	*tag;
	D_Char	*text;
} D_ExtendedEventDescrItem;

/** @brief ��չ�¼�������tag:0x4E*/
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

/** @brief �����¼�ƫ��������tag:0x58*/
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

/** @brief ������Ԫ��*/
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

/** @brief ������������tag:0x51*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Bool	 entry;
	D_U8		 rows;
	D_U8		 cols;
	D_List	*multi_text;
} D_MosaicDescr;

/** @brief ��ͨ����˽������*/
/** �߼���Ļ*/
typedef struct {
	D_List	list;
	D_U8	tag;
	D_U16	start_x;
	D_U16	start_y;
	D_U16	end_x;
	D_U16	end_y;
} D_MosaicLogicScreenDescr;

/** @brief ����������*/
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

/** @brief ������ҵ��Ⱥ��������tag:0x5C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualBouquetNameDescr;

/** @brief ������Ԫ��������tag:0x5E*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualComponentDescr;

/** @brief ������������������tag:0x5B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualNetworkNameDescr;

/** @brief �����Է�����������tag:0x5D*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_List	*multi_text;
} D_MultilingualServiceNameDescr;

/** @brief NVOD�ο�ҵ��������tag:0x4B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ts_id;
	D_U16		 org_net_id;
	D_U16		 srv_id;
} D_NVODReferenceDescr;

/** @brief ������������Network name descriptor tag:0x40*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	*name;
} D_NetworkNameDescr;

/** @brief ��ĸ�տ��ȼ�������tag:0x55  add by liux 2006-8-23*/
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

/** @brief ����������Service descriptor tag:0x48*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 type;
	D_Char	*prov_name;
	D_Char	*srv_name;
} D_ServiceDescr;

/** @brief �����б�������Service list descriptor tag:0x41*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 type;
	D_U16		 srv_id;
} D_ServiceListDescr;

/** @brief ����ת��������tag:0x60*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 org_net_id;
	D_U16		 ts_id;
	D_U16		 srv_id;
} D_ServiceMoveDescr;

/** @brief ���¼�������tag:0x4D*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_Char	 lang[3];
	D_Char	*name;
	D_Char	*descr;
} D_ShortEventDescr;

/** @brief �����������tag:0x52*/
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

/** @brief ʱ���¼�������tag:0x4F*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ref_srv_id;
	D_U16		 ref_evt_id;
} D_TimeShiftedEventDescr;

/** @brief ʱ��ҵ��������tag:0x4C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U16		 ref_srv_id;
} D_TimeShiftedServiceDescr;


/** @brief AC3 ������tag:0x6A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_AC3Descr;

/** @brief EAC3 ������tag:0x7A*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_EAC3Descr;

/** @brief DTS ������tag:0x7B*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_DTSDescr;

/** @brief AAC ������tag:0x7C*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
} D_AACDescr;



/** @brief Section ��Ϣ*/
typedef struct {
	D_U8		 tab_id;
	D_U8		 version;
	D_U16		 ext_tab_id;
	D_U8		 sec_num;
	D_U8		 last_sec_num;
	D_U8		 seg_last_sec_num;
	D_U8		 last_tab_id;
} D_SectionInfo;

/** @brief ������*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 pid;
	D_U8		 type;
} D_ElementStream;

/** @brief PMT��*/
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

/** @brief PAT��*/
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

/** @brief CAT��*/
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

/** @brief NIT���е�TS����*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 ts_id;
	D_U16		 org_net_id;
} D_NitTS;

/** @brief BAT���е�TS����*/
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

/** @brief BAT��*/
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

/** @brief SDT��*/
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

/** @brief EIT��*/
typedef struct {
	D_List	 list;
	D_List	*descrs;
	D_U16		 srv_id;
	D_U16		 ts_id;
	D_U16		 org_net_id;
	D_U16		 evt_id;
	D_U8     rating;            /* liux �ۿ��ȼ� */
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

/** @brief TDT��*/
typedef struct {
	D_List	 list;
	D_Time	 utc;
	D_U8		 tab_id;
} D_Tdt;

/** @brief TOT��*/
typedef struct {
	D_List	 list;
	D_Time	 utc;
	D_U8		 tab_id;
	D_List	*descrs;
} D_Tot;

/** @brief SI����������ǰ���� */
typedef struct
{
	D_U8 *buf;
	D_HMMan hmm;
	D_List **dds;
	D_Result *ret;
}D_SIParseHookPre;

/** @brief SI���������Ӻ��� */
typedef struct
{
	D_U8 *buf;
	D_HMMan hmm;
	D_List **dds;
}D_SIParseHookRet;

/** @brief ����secion ͨ����Ϣ
* @param buf	��������ַ
* @param length	��������С
* @param info	����sectionͨ����Ϣ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_si_parse_section (D_U8 *buf, D_S16 length, D_SectionInfo *info) D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param buf    ��������ַ
* @param hmm    �ڴ���������
* @return   �ɹ�����������ָ��,ʧ�ܷ���NULL
*/
D_List* d_si_parse_descr (D_U8 *buf, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����ָ���������ڵ�����������
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ������������ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_descrs (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��PAT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����PAT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_pat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��PMT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����PMT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_pmt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��CAT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����CAT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_cat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��NIT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����NIT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_nit (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��SDT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����SDT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_sdt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��BAT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����BAT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_bat (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��EIT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����EIT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_eit (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��TDT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����TDT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_tdt (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

/** @brief ����һ��TOT section
* @param buf	��������ַ
* @param length	��������С
* @param hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ������������ṹ����,ʧ�ܷ���NULL
*/
D_List*	d_si_parse_tot (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
