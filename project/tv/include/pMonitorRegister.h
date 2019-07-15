/**@defgroup MonitorTable SI����
*@{*/
/** @file
* @brief ��Ŀ���ģ��
* @author sunzy
* @date 2013-06-03 sunzy: �����ļ�
* @date 2013-06-05 sunzy: �ƶ�ԭģ����ش���
* @date 2013-07-25 hegx: ����Ҫ��ʵ��ע�ắ��
*/
#ifndef _D_MONITORREGISTER_H_
#define _D_MONITORREGISTER_H_

#ifdef  __cplusplus

extern "C"
{
#endif

#include "pSIParse.h"

typedef enum {
	D_MSG_MON_NULL = -1,	
	D_MSG_MON_SW_UPDATE,				/**< �ҵ������������*/
	D_MSG_MON_SW_UPDATE_MUST,			/**< �ҵ������������, ǿ������*/
	D_MSG_MON_UMT_UPDATE,				/**< �ҵ�UMT �����������*/
	D_MSG_MON_UMT_UPDATE_FORCE,		/**< �ҵ�UMT �����������, ǿ������*/
	D_MSG_MON_CA_UPDATE,				/**< �ҵ����� �����������*/
	D_MSG_MON_CA_UPDATE_FORCE,		/**< �ҵ����� �����������, ǿ������*/
	D_MSG_MON_CHAN_UPDATE,				/**< Ƶ����Ҫ��������*/
	D_MSG_MON_CHAN_CHANGE,				/**< ��Ƶ���Ŀ�仯*/
	D_MSG_MON_CHAN_UPDATE_MUST,		/**< Ƶ����Ҫ��������*/
	D_MSG_MON_CAT_CHANGED,				/**< CAT��Ϣ�仯*/
	D_MSG_MON_PMT_CHANGED,				/**< PMT��Ϣ�仯*/
	D_MSG_MON_SDT_CHANGED,				/**< SDT��Ϣ�仯*/
	D_MSG_MON_NETWORK_ID_CHANGED,		/**< network id�仯*/
	D_MSG_MON_NETWORK_NAME_CHANGED,	/**< network name �仯*/	
} D_MONMsgType;


#define NET_NAME_MAX_LEN (32)

typedef struct
{
    D_U8 nit_version;
    D_U16 currNetworkId;
    D_Char currNetworkName[NET_NAME_MAX_LEN + 1];
    D_Loader_Descr  Loader_Descr;
    D_U8	delivery[64];
}D_PMonitorData;

typedef struct
{
	D_U8	download_table_id; 
	D_U16	download_pid;
	D_U8	upgrade_mode;
	D_U16	manufacturer_code;
	D_U32	software_version;
	D_U32	hardware_version;
	D_FEndFreq	freq;	/*��λ100Hz*/
	D_FEndBaud	baud;	/*��λ100symbol/s*/
	D_FEndMod	mod;	
	D_U8		download_flag;
	D_U8		 tag;
}D_CA_Loaderinfo;

/** @brief ���س�ʼ��
*@return D_ERR ��ʼ��ʧ�� D_OK ��ʼ���ɹ�
*/
D_Result p_monitor_init()D_FUNCPOSTFIT;
/** @brief ��������ͨ��ʱ��ص���ҵ�ͨ��
*@return D_ERR ��ʼ��ʧ�� D_OK ��ʼ���ɹ�
*/
D_Result p_monitor_close(void)D_FUNCPOSTFIT;

/** @brief ���¿������ͨ��
*@return D_ERR ��ʼ��ʧ�� D_OK ��ʼ���ɹ�
*/
D_Result p_monitor_restart(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
/* @}*/

