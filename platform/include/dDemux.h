/** @file
* @brief 解复用设备操作
* @author 龚克
* @date 2005-5-18 龚克: 建立文件
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

/** @brief 解复用设备句柄*/
typedef D_Handle	D_HDemux;

/** @brief 解复用设备类型*/
typedef enum {
	D_DEMUX_SEC,					/**< Section demux*/
	D_DEMUX_TS,						/**< TS packet demux*/
	D_DEMUX_PES						/**< PES demux*/
} D_DemuxType;

/** @brief crc模式*/
typedef enum
{
	D_DMX_CRC_AUTO = 0,
	D_DMX_CRC_DISABLE,
	D_DMX_CRC_ENABLE,
}D_DemuxCrcType;

/** @brief  解复用pvr/pes通道的pes_out模式*/
typedef enum
{
    D_DMX_PES_OUT_ES_OF_PES = 0,         /* es of pes (pusi有效)*/
    D_DMX_PES_OUT_TELETEXT_PES,           /* 图文pes (pusi有效)*/        
    D_DMX_PES_OUT_PID_TS,                     /* Ts_pid指定的ts 流*/
    D_DMX_PES_OUT_PES,                            /* pes (pusi有效)*/
    D_DMX_PES_OUT_ALL_TS,                        /* 所有的ts流*/
    D_DMX_PES_OUT_PES_NO_HEAD,            /* 去掉pes头6个字节 (pusi有效)*/
    D_DMX_PES_OUT_PAYLOAD,                    /* payload (pusi无效)*/
}D_DemuxPesOutMode;

/** @brief 解复用设备属性*/
typedef struct {
	D_ID				id;				/**< Demux设备ID*/
	D_DemuxType	type;			/**< 解复用设备类型*/
	D_Size			buf_size;	/**< 解复用设备缓冲区大小*/
	D_ID				fend_id;	/**< 对应前端设备ID*/
	D_DemuxCrcType  crc_type;	/**< crc校验策略*/
	D_S8                   *TaskName;
} D_DemuxAttr;

/** @brief 按缺省值初始化解复用设备属性*/
#define D_DEMUX_ATTR_INIT(_a)\
D_MACRO_BEGIN\
(_a)->type = D_DEMUX_SEC;\
(_a)->buf_size = DEMUX_DEFAULT_BUFFERSIZE;\
(_a)->fend_id = d_demux_get_default_dev();\
(_a)->id = (_a)->fend_id;\
(_a)->crc_type = D_DMX_CRC_AUTO;\
(_a)->TaskName = "Task";\
D_MACRO_END

/** @brief 解复用设备事件*/
typedef enum {
	D_DEMUX_EVT_DATA,			/**< 解复用设备中有数据可读*/
	D_DEMUX_EVT_OVERFLOW,	/**< 解复用设备缓冲区溢出*/
	D_DEMUX_EVT_ERROR			/**< 解复用设备出错*/
} D_DemuxEvent;

/** @brief 解复用设备事件回调
*
*	当解复用设备开始运行后，如果解复用设备中有数据，或者
* 设备出错时，通过回调函数通知应用。
*/
typedef D_Result (*D_DemuxCallback) (D_HDemux hdemux, D_Handle handle, D_DemuxEvent evt) D_FUNCPOSTFIT;
//typedef D_Result (*D_DemuxPesCallback)(D_HDemux hdemux, D_Handle handle, D_DemuxEvent evt) D_FUNCPOSTFIT;
//typedef D_Result (*D_DemuxPvrCallback) () D_FUNCPOSTFIT;

/** @brief 解复用过滤器*/
typedef union {
	D_U16				pid;			/**< PID*/
	/** @brief Section 过滤器
	*
	*	数据过滤条件为,pid值相等,section数据逻辑与mask值后和filter逻辑与mask值
	*	后完全相同。且section数据逻辑与positive值后和filter逻辑与positive值后
	* 至少1位不同。
	*/
	struct {
		D_U16			pid;				/**< PID*/
		D_Size		buf_size;	/**< 缓冲区大小*/
		D_U8			length;			/**< Section filter长度*/
		D_U8			filter[16];	/**< 过滤器*/
		D_U8			mask[16];		/**< 过滤器屏蔽位*/
		D_U8			positive[16];/**< 过滤器反向屏蔽位*/
	} sec;
	struct {
		D_U16			pid;			/**< PID*/
		D_Size		buf_size;	/**< 缓冲区大小*/
	} pes;								/**< PES 过滤器*/
	struct {
		D_U16			pid;			/**< PID*/
		D_Size		buf_size;	/**< 缓冲区大小*/
	} ts;									/**< TS 过滤器*/
} D_DemuxFilter;

/** @brief Demux系统初始化
*
*	在调用Demux操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_demux_open (void) D_FUNCPOSTFIT;
/** @brief Demux系统中止
*
* 程序结束时，释放Demux系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_demux_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个Demux设备
* @param attr	Demux设备属性结构指针，为NULL时使用缺省值(type=D_DEMUX_SEC,buf_size=4096,fend_id=0)
* @param handle 调用回调时返回的参数句柄
* @return 成功时返回Demux设备句柄，失败返回D_INVALID_HANDLE
*/
D_HDemux	d_demux_create (D_DemuxAttr *attr, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 销毁一个Demux设备
* @param hdemux Demux设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_demux_destroy (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief 设定解复用设备过滤器
* @param hdemux	解复用设备句柄
* @param filter	过滤器参数
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	filter参数无效
*/
D_Result	d_demux_set_filter (D_HDemux hdemux, D_DemuxFilter *filter) D_FUNCPOSTFIT;
D_Result d_demux_confine_length (D_HDemux hdemux,D_U8  length) D_FUNCPOSTFIT;

/** @brief 启动解复用设备
* @param hdemux	解复用设备句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	设备句柄无效
* @retval D_ERR_FAULT	无法正常启动
* @retval	D_ERR_ALREADY_DONE	设备已经启动
*/
D_Result	d_demux_start (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief 停止解复用设备
* @param hdemux	解复用设备句柄
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	设备句柄无效
* @retval D_ERR_FAULT	无法正常停止
* @retval D_ERR_ALREADY_DONE	设备已经停止
*/
D_Result	d_demux_stop (D_HDemux hdemux) D_FUNCPOSTFIT;

/** @brief 从解复用设备中读取设备
*
*	如果解复用设备中没有数据，返回D_ERR_EMPTY。
* 如果解复用设备中有数据,对于section filter,每次读取
* 一个section的数据,如果缓冲区空间不足以容纳一个section,
* 返回D_ERR_OVERFLOW.一般将缓冲区设为4096字节大小。
* @param hdemux	解复用设备句柄
* @param pd		存放读取的缓冲区
* @param size	缓冲区大小
* @return	成功时返回实际读取的字节数，失败时返回负数
* @retval D_ERR_INVALID_HANDLE	句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_OVERFLOW	缓冲区小，无法容纳数据
* @retval D_ERR_EMPTY	缓冲区没有数据
*/
D_Size d_demux_read (D_HDemux hdemux, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief 注册解复用事件回调函数
*
*	当启动的解复用设备接收到数据或出现错误时，系统调用
* 回调函数通知应用程序。
* @param callback	回调函数指针
* @param old 如果非NULL,返回旧的回调函数指针
* @return 操作成功返回D_OK,失败返回D_ERR
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


/* 取得分配到的驱动的handle ,兼容D_ARCH == D_HI2035*/
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
