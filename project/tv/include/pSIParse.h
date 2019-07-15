/** @file
* @brief SI˽�б�˽������������ģ��
* @author ����
* @date 2013-08-30 ����: �����ļ�
*/

#ifndef _D_PROJECT_SI_PARSE_H_
#define _D_PROJECT_SI_PARSE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dMMan.h"
#include "dTypes.h"
#include "dFEnd.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"



/* ˽��tag ����*/
#define P_DESCR_LOADER_TAG		0x85    /*Haier ic ����������*/
#define P_YONGXIN_DESCR_LOADER_TAG 0xa1 /*��������������*/
#ifdef D_CA_SUPPORT_XGCA                
#define DESCR_CDXG_SERVICE_UPDATE			 0x86
#define CDXG_DESCR_LEN	10
#endif
#define P_DESCR_ABV_LCN_TAG		0x83    /*LCN �߼�Ƶ����������*/

#define P_DESCR_DSAD_TAG		0xA6    /*�������������*/
#define P_DESCR_MGAD_TAG		0xFE    /*���޹��������*/
#define P_DESCR_DIVIAD_TAG			0x84    /*����ͨ���������*/
#define P_DESCR_DVTAD_TAG			0xAF //0x89    /*������Ѷ���������*/


#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
#ifndef P_DESCR_HAIER_PROGRAM_VERSION_TAG
#define P_DESCR_HAIER_PROGRAM_VERSION_TAG 0xC5    /*Haier��Ŀ�汾��������*/
#endif
#endif

/*˽�����������ȶ���*/
#define ABV_LCN_DESCR_BODY_LEN	 		(4)





/** @brief Haier ic �����������ڲ���������*/
typedef struct 
{
	D_List						list;
	D_U8						download_table_id; 
	D_U16						download_pid;
	D_U32						download_info_len;
	D_U32						hardware_version;
	D_U32						software_version;
	D_U32						stb_sn_start;
	D_U32						stb_sn_end;
	D_U8						upgrade_mode;
	D_Descr						*delivery; /*�ڲ�����ϵͳ����-c \ -t \ -s*/
}D_Loader_Descr;

/** @brief Haier ic ����������tag:0x85*/
typedef struct 
{
	D_List	 list;
	D_U8		 tag;
	D_U16						manufacturer_code;
	D_Loader_Descr	*loader_list;
}D_Loader;


#ifdef D_CA_SUPPORT_XGCA                
/** @brief �ɶ��¹��Ŀ����������*/
typedef struct {
	D_List	 list;
	D_U8		 tag;
	D_U8		 update_flag;
	D_U8		 version_number;
	D_U16      fm_pid;
} D_CDXGDescr;
#endif

/** @brief LCN�߼�Ƶ����������*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    srv_id;
    D_U16       lcn;
    D_U32   reserved;
} D_LCNDescr;

/** @brief �������������*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    datapid;
    D_U32   reserved;
} D_DSADDescr;

/** @brief���޹��������*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U16	    picpid;
    D_U16	    txtpid;
    D_U16	    corpid;
} D_MGADDescr;

/** @briefͨ����������
�û��Լ�����private_dat�������*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U8	    len;
    D_U8        *dat;
} D_NormalDescr;

/** @brief ��Ŀ�汾������*/
typedef struct {
    D_List	    list;
    D_U8	    tag;
    D_U8	    force;    
    D_U8	    version;
    D_U8        match;
    D_U16	    match_code;
} D_HrProgramVersionDescr;


/** @brief ��si˽����������������(ע��˽�н�������)
* @param ��
* @return ��
*/
void p_private_si_parse_open (void) D_FUNCPOSTFIT;


/** @brief �ر�si˽����������������(��ע��˽�н�������)
* @param ��
* @return ��
*/
void p_private_si_parse_close (void) D_FUNCPOSTFIT;



/** @brief ����һ��xxx section
* @param [in] buf	��������ַ
* @param [in]length	��������С
* @param [in]hmm		�ڴ���������,����ͨ���˾�������ڴ�
* @return �ɹ�����PAT�ṹ����,ʧ�ܷ���NULL
*/
D_List*	p_si_parse_xxx (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT;






#ifdef  __cplusplus
}
#endif

#endif
