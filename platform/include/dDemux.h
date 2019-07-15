/** @file
* @brief �⸴���豸����
* @author ����
* @date 2005-5-18 ����: �����ļ�
*/

#ifndef _D_DEMUX_H_
#define _D_DEMUX_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDemux.h"
#include "dTask.h"
#include "dQueue.h"
#include "dMutex.h"
#include "dMem.h"
#include "dMsg.h"
#include "dResource.h"
#include <stdio.h>
#include "dDebug.h"


#define DEMUX_DEFAULT_BUFFERSIZE              (4 * 1024)  
#define PES_SIZE 0x300000

/** @brief �⸴���豸���*/
typedef D_Handle	D_HDemux;

/** @brief �⸴���豸����*/
typedef enum {
	D_DEMUX_SEC,					/**< Section demux*/
	D_DEMUX_TS,						/**< TS packet demux*/
	D_DEMUX_PES						/**< PES demux*/
} D_DemuxType;

/** @brief crcģʽ*/
typedef enum
{
	D_DMX_CRC_AUTO = 0,
	D_DMX_CRC_DISABLE,
	D_DMX_CRC_ENABLE,
}D_DemuxCrcType;

/** @brief  �⸴��pvr/pesͨ����pes_outģʽ*/
typedef enum
{
    D_DMX_PES_OUT_ES_OF_PES = 0,         /* es of pes (pusi��Ч)*/
    D_DMX_PES_OUT_TELETEXT_PES,           /* ͼ��pes (pusi��Ч)*/        
    D_DMX_PES_OUT_PID_TS,                     /* Ts_pidָ����ts ��*/
    D_DMX_PES_OUT_PES,                            /* pes (pusi��Ч)*/
    D_DMX_PES_OUT_ALL_TS,                        /* ���е�ts��*/
    D_DMX_PES_OUT_PES_NO_HEAD,            /* ȥ��pesͷ6���ֽ� (pusi��Ч)*/
    D_DMX_PES_OUT_PAYLOAD,                    /* payload (pusi��Ч)*/
}D_DemuxPesOutMode;

/** @brief �⸴���豸����*/
typedef struct {
	D_ID				id;				/**< Demux�豸ID*/
	D_DemuxType	type;			/**< �⸴���豸����*/
	D_Size			buf_size;	/**< �⸴���豸��������С*/
	D_ID				fend_id;	/**< ��Ӧǰ���豸ID*/
	D_DemuxCrcType  crc_type;	/**< crcУ�����*/
	D_S8                   *TaskName;
} D_DemuxAttr;

/** @brief ��ȱʡֵ��ʼ���⸴���豸����*/
#define D_DEMUX_ATTR_INIT(_a)\
D_MACRO_BEGIN\
(_a)->type = D_DEMUX_SEC;\
(_a)->buf_size = DEMUX_DEFAULT_BUFFERSIZE;\
(_a)->fend_id = d_demux_get_default_dev();\
(_a)->id = (_a)->fend_id;\
(_a)->crc_type = D_DMX_CRC_AUTO;\
(_a)->TaskName = "Task";\
D_MACRO_END

/** @brief �⸴���豸�¼�*/
typedef enum {
	D_DEMUX_EVT_DATA,			/**< �⸴���豸�������ݿɶ�*/
	D_DEMUX_EVT_OVERFLOW,	/**< �⸴���豸���������*/
	D_DEMUX_EVT_ERROR			/**< �⸴���豸����*/
} D_DemuxEvent;

/** @brief �⸴���豸�¼��ص�
*
*	���⸴���豸��ʼ���к�����⸴���豸�������ݣ�����
* �豸����ʱ��ͨ���ص�����֪ͨӦ�á�
*/
typedef D_Result (*D_DemuxCallback) (D_HDemux hdemux, D_Handle handle, D_DemuxEvent evt) D_FUNCPOSTFIT;
//typedef D_Result (*D_DemuxPesCallback)(D_HDemux hdemux, D_Handle handle, D_DemuxEvent evt) D_FUNCPOSTFIT;
//typedef D_Result (*D_DemuxPvrCallback) () D_FUNCPOSTFIT;

/** @brief �⸴�ù�����*/
typedef union {
	D_U16				pid;			/**< PID*/
	/** @brief Section ������
	*
	*	���ݹ�������Ϊ,pidֵ���,section�����߼���maskֵ���filter�߼���maskֵ
	*	����ȫ��ͬ����section�����߼���positiveֵ���filter�߼���positiveֵ��
	* ����1λ��ͬ��
	*/
	struct {
		D_U16			pid;				/**< PID*/
		D_Size		buf_size;	/**< ��������С*/
		D_U8			length;			/**< Section filter����*/
		D_U8			filter[16];	/**< ������*/
		D_U8			mask[16];		/**< ����������λ*/
		D_U8			positive[16];/**< ��������������λ*/
	} sec;
	struct {
		D_U16			pid;			/**< PID*/
		D_Size		buf_size;	/**< ��������С*/
	} pes;								/**< PES ������*/
	struct {
		D_U16			pid;			/**< PID*/
		D_Size		buf_size;	/**< ��������С*/
	} ts;									/**< TS ������*/
} D_DemuxFilter;

/** @brief Demuxϵͳ��ʼ��
*
*	�ڵ���Demux��������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_demux_open (void) D_FUNCPOSTFIT;
/** @brief Demuxϵͳ��ֹ
*
* �������ʱ���ͷ�Demuxϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_demux_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��Demux�豸
* @param attr	Demux�豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(type=D_DEMUX_SEC,buf_size=4096,fend_id=0)
* @param handle ���ûص�ʱ���صĲ������
* @return �ɹ�ʱ����Demux�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HDemux	d_demux_create (D_DemuxAttr *attr, D_Handle handle) D_FUNCPOSTFIT;

/** @brief ����һ��Demux�豸
* @param hdemux Demux�豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_demux_destroy (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief �趨�⸴���豸������
* @param hdemux	�⸴���豸���
* @param filter	����������
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	filter������Ч
*/
D_Result	d_demux_set_filter (D_HDemux hdemux, D_DemuxFilter *filter) D_FUNCPOSTFIT;
D_Result d_demux_confine_length (D_HDemux hdemux,D_U8  length) D_FUNCPOSTFIT;

/** @brief �����⸴���豸
* @param hdemux	�⸴���豸���
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�豸�����Ч
* @retval D_ERR_FAULT	�޷���������
* @retval	D_ERR_ALREADY_DONE	�豸�Ѿ�����
*/
D_Result	d_demux_start (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief ֹͣ�⸴���豸
* @param hdemux	�⸴���豸���
* @retval D_OK	�����ɹ�
* @retval D_ERR_INVALID_HANDLE	�豸�����Ч
* @retval D_ERR_FAULT	�޷�����ֹͣ
* @retval D_ERR_ALREADY_DONE	�豸�Ѿ�ֹͣ
*/
D_Result	d_demux_stop (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief �ӽ⸴���豸�ж�ȡ�豸
*
*	����⸴���豸��û�����ݣ�����D_ERR_EMPTY��
* ����⸴���豸��������,����section filter,ÿ�ζ�ȡ
* һ��section������,����������ռ䲻��������һ��section,
* ����D_ERR_OVERFLOW.һ�㽫��������Ϊ4096�ֽڴ�С��
* @param hdemux	�⸴���豸���
* @param pd		��Ŷ�ȡ�Ļ�����
* @param size	��������С
* @return	�ɹ�ʱ����ʵ�ʶ�ȡ���ֽ�����ʧ��ʱ���ظ���
* @retval D_ERR_INVALID_HANDLE	�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_OVERFLOW	������С���޷���������
* @retval D_ERR_EMPTY	������û������
*/
D_Size d_demux_read (D_HDemux hdemux, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief ע��⸴���¼��ص�����
*
*	�������Ľ⸴���豸���յ����ݻ���ִ���ʱ��ϵͳ����
* �ص�����֪ͨӦ�ó���
* @param callback	�ص�����ָ��
* @param old �����NULL,���ؾɵĻص�����ָ��
* @return �����ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_demux_register_callback (D_DemuxCallback callback,D_DemuxCallback *old,D_U8 dev) D_FUNCPOSTFIT;


D_HDemux d_demux_createpes(D_DemuxAttr *attr, D_Handle handle);
D_Result d_demux_destroypes (D_HDemux hdemux);
D_Result d_demux_setpespara (D_HDemux hdemux, D_DemuxFilter *filter);
D_Result d_demux_startpes (D_HDemux hdemux);
D_Result d_demux_stoppes (D_HDemux hdemux);
D_Size d_demux_readpes (D_HDemux hdemux, D_U8 *data, D_Size size);


D_HDemux d_demux_createpvr(D_DemuxAttr *attr, D_Handle handle);
D_Result d_demux_destroypvr(D_HDemux hdemux);
D_Result d_demux_setpvrpara(D_HDemux hdemux, D_U16 *wPid, D_U32 pid_cnt, D_DemuxPesOutMode out_mode);
D_Result d_demux_setpvrbuffer(D_HDemux hdemux, D_U32 address, D_Size size);
D_Result d_demux_stoppvr (D_HDemux hdemux);
D_Result d_demux_startpvr (D_HDemux hdemux);
D_Result d_demux_getpvr_info (D_HDemux hdemux, D_U32 *buf_base, D_U32 *buf_size, D_U32 *wp, D_U32 *rp);
D_Result d_demux_setpvr_rp (D_HDemux hdemux, D_U32 rp);
D_Size d_demux_readpvr(D_HDemux hdemux, D_U8 *data, D_Size size);


/* ȡ�÷��䵽��������handle ,����D_ARCH == D_HI2035*/
D_Char d_demux_get_lowlevel_handler(D_HDemux hdemux);

D_Result d_demux_set_default_dev(D_U8 dev);
D_U8 d_demux_get_default_dev(void);

D_U8 d_demux_set_ts_selector(D_U8 tv,D_U8 Ts_selector);
D_U8 d_demux_chip_demod(D_U8 ts_sel);
D_U8 d_demux_set_ts_ctrl(D_U8 ts_ctrl);
D_U8 d_demux_get_sysFlag(D_U8 ts_sys);
void d_demux_chip_reset(void);
void d_demux_filter_reset(void);
#ifdef  __cplusplus
}
#endif

#endif
