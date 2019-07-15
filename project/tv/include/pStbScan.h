/** @file
* @brief ����������ؽӿ������ݶ���
* @author ����
* @date 2013-7-05 ����: �����ļ�
*/

#ifndef _D_STB_SCAN_H_
#define _D_STB_SCAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dScan.h"


extern D_AutoScanOp DVBC_AutoScan_Op;
extern D_ManualScanOp DVBC_ManualScan_Op;

extern D_AutoScanOp DVBT_AutoScan_Op;
extern D_ManualScanOp DVBT_ManualScan_Op;

extern D_AtvManualScanOp ATV_ManualScan_Op;
extern D_AtvAutoScanOp ATV_AutoScan_Op;

extern D_AutoScanOp DVBS_AutoScan_Op;
extern D_ManualScanOp DVBS_ManualScan_Op;

/** @brief �����������ʽ*/
typedef enum {
	D_SCAN_SORT_MODE_NOT 	= 0,    /*������*/
	D_SCAN_SORT_MODE_TS		= 1,    /*Ƶ��,��Ƶ��*/
	D_SCAN_SORT_MODE_SRVID 	= 2,    /*service id*/
	D_SCAN_SORT_MODE_LCN 	= 3,    /*�߼�Ƶ����*/
	D_SCAN_SORT_MODE_FREECA = 4,    /*���/����*/
	D_SCAN_SORT_MODE_NAME 	= 5,    /*��Ŀ��*/
	D_SCAN_SORT_MODE_TSID   = 6,    /*TSID����, TSID��ͬ����freq��*/
	D_SCAN_SORT_MODE_TSID_SRVID = 7,  /*��ͬƵ�㰴��TSID�ţ�ͬƵ���ڵĽ�Ŀ����serviceID����, TSID��ͬ����freq��*/
	D_SCAN_SORT_MODE_CAFREE_TS_SRVID = 8,  /*�Ȱ�����/����ų����Σ����ڲ�ͬƵ�㰴��Ƶ���ţ�Ƶ���ڵĽ�Ŀ����serviceID����*/
	
	D_SCAN_SORT_MODE_TS_CONTRARY,                /*Ƶ�㵹��*/
	D_SCAN_SORT_MODE_SRVID_CONTRARY,         /*service id ����*/
	D_SCAN_SORT_MODE_LCN_CONTRARY,           /*�߼�Ƶ���ŵ���*/
	D_SCAN_SORT_MODE_FREECA_CONTRARY,        /*���/���ŵ���*/
	D_SCAN_SORT_MODE_NAME_CONTRARY,          /*��Ŀ������*/	
	
	D_SCAN_SORT_MODE_OTHERS	
}D_ScanSortMode;

/*��������*/
typedef enum
{
	STB_SCAN_TYPE_MANUAL = 0,/*�ֶ�����*/
	STB_SCAN_TYPE_AUTO = 1,/*�Զ�����*/
	STB_SCAN_TYPE_FULL = 2,/*ȫƵ������*/
	STB_SCAN_TYPE_LIST = 3,/*Ԥ������*/
	STB_SCAN_TYPE_TP = 4,/*ת��������*/
	STB_SCAN_TYPE_SINGLE_SATELLITE = 5,/*����������*/
	STB_SCAN_TYPE_OTHERS
}D_StbScanType;

/*����ģʽ*/
typedef enum
{
	STB_SCAN_MODE_BLIND = 0,      /*äɨ*/
	STB_SCAN_MODE_PRESET = 1,              /*Ԥ������*/
	STB_SCAN_MODE_OTHERS
}P_StbScanMode;

/*������Ŀ����*/
typedef enum
{
	STB_SCAN_PROG_TYPE_TV_RADIO = 0, /*����+�㲥*/
	STB_SCAN_PROG_TYPE_TV = 1,          /*����*/
	STB_SCAN_PROG_TYPE_RADIO = 2,  /*�㲥*/
	STB_SCAN_PROG_OTHERS
}P_StbScanProgType;

/*Ӧ����������*/
typedef struct
{
    D_Bool  valid;
    D_StbScanType   type;
    D_U32 satelliteNo;
    D_FEndParam	fendparam;	/**< Ƶ����Ϣ*/
    D_FEndType   fendtype;		/**< ǰ������*/	    
    D_U32   freeFlag;
    P_StbScanProgType progType; 
    P_StbScanMode mode;
    D_Bool  netFlag;
}P_ScanConfig;

#define CA_FLAG_IN_PMT 0x01
#define CA_FLAG_IN_SDT 0x02


/**/
typedef struct
{
	D_FEndFreq start_freq;
	D_FEndFreq end_freq;
	D_FEndBandWitch band;
}D_WaveBand;

/** @brief �������������õ�dbtsid�б�*/
D_Result p_scan_sort_srv_set_dbtsid_list(D_ID *list, D_U32 cnt)D_FUNCPOSTFIT;

/** @brief �������Ľ����������ð������
* @param [in][out] srvlist ҵ������
* @param [in] mode ����ʽ
* @return �ɹ�D_OK, ʧ��D_ERR
*/
D_Result p_scan_sort_srv(D_ScanSrvInfoNode*srvlist, D_ScanSortMode mode)D_FUNCPOSTFIT;

/** @brief ���û�����������Ƶ�������б�Ƚϣ��ж�Ƶ���Ƿ���Ч
* @return ��ЧD_TRUE, ��ЧD_FALSE
*/
D_Bool p_scan_judge_freq_valid(D_U32 freq)D_FUNCPOSTFIT;

/** @brief �����ݿ�Ľ����������
* @param [in] type ���ӹ㲥
* @param [in] mode ����ʽ
* @param [in] reset_num �Ƿ���������Ƶ����
* @return �ɹ�D_OK, ʧ��D_ERR
*/
D_Result p_scan_sort_all_srv(D_DBSrvType type, D_ScanSortMode mode, D_Bool reset_num)D_FUNCPOSTFIT;

/** @brief ��ʼ�ֶ�����
* @param config ��������
* @return �ɹ������������, ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan p_atv_manual_scan_create (D_ScanTaskConfig config) D_FUNCPOSTFIT;

/** @brief �����ֶ�����
* @param hscan  �������
* @param store  �Ƿ�洢�������
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result p_atv_manual_scan_destroy (D_HScan hscan, D_Bool store) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

