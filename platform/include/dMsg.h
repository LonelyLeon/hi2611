/** @file
* @brief 通用消息定义
* @author 龚克
* @date 2005-6-4  龚克: 建立文件
* @date 2005-5-18 刘勋: 修改文件
加入消息D_MSG_LAODER_UPDATE
* @date 2013-04-25 lc: 统一平台, 代码整理
*/

#ifndef _D_MSG_H_
#define _D_MSG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFEnd.h"
#include "dAV.h"
#include "dSem.h"
#include "dDBase.h"


/** @brief 消息类型*/
typedef enum
{
    D_MSG_NULL = -1,

    D_MSG_TIMER = 0,            /**< 定时器消息*/
    D_MSG_DEMUX_DATA,           /**< 解复用设备接收到数据*/
    D_MSG_DEMUX_OVERFLOW,       /**< 解复用设备缓冲区溢出*/
    D_MSG_DEMUX_ERROR,          /**< 解复用设备出错*/
    D_MSG_APP_CREATE,           /**< 新应用创建*/
    D_MSG_APP_DESTROY,          /**< 应用结束*/
    D_MSG_APP_SYNC_REQ,         /**< 应用同步请求*/
    D_MSG_APP_TIMEOUT,          /**< 应用接收消息超时*/

    D_MSG_FEND_SET_PARAM,       /**< 设定前端参数*/
    D_MSG_FEND_SET_PARAM_TRACK, /**< 设定前端参数并跟踪信号变化*/
    D_MSG_FEND_GET_LOCKED_REQ,  /**< 取前端锁状态请求*/
    D_MSG_FEND_GET_LOCKED_REPLY,/**< 取前端锁状态应答*/
    D_MSG_FEND_GET_STATUS_REQ,  /**< 取前端设备状态请求*/
    D_MSG_FEND_GET_STATUS_REPLY,/**< 取前端设备状态应答*/
    D_MSG_FEND_SET_LOCKED_DETECTOR,/**< 设定前端锁状态监测队列*/
    // 2013-3-18 添加命令。by wy
    D_MSG_FEND_SET_DISEQC,          /**< 控制diseqc等设备*/
    D_MSG_FEND_SET_DISEQC_REPLY,
    D_MSG_FEND_BLIND_SCAN,          /**< 盲扫*/
    D_MSG_FEND_BLIND_SCAN_REPLY,
    D_MSG_FEND_SET_LNB_POWER_ENABLE, /**< 设定lnb供电是否打开*/
    D_MSG_FEND_SET_STANDBY_POWER,/**< 设定待机关闭tuner电源或进入低功耗模式*/
    D_MSG_FEND_SET_NORMAL_POWER,/**< 设定从tuner低功耗模式进入正常模式*/
    D_MSG_KEY_PRESSED,          /**< 键按下*/
    D_MSG_KEY_RELEASE,          /**< 键抬起*/

    D_MSG_SCAN_OK,              /**< 搜索完毕*/
    D_MSG_SCAN_FEND_STATUS,     /**< 搜索中无法锁住频点*/
    D_MSG_SCAN_FREQ,            /**< 开始搜索频点*/
    D_MSG_SCAN_FREQ_END,        /**< 结束搜索频点*/
    D_MSG_SCAN_SI,              /**< 开始搜索频点si 信息*/
    D_MSG_SCAN_DATA,            /**< 搜索到数据*/
    D_MSG_SCAN_PROGRESS,        /**< 搜索进度*/
    D_MSG_SCAN_TRY_LOCK,        /**< 搜索去锁定频点*/
    D_MSG_SCAN_GROUP_START,     /**< 开始启动一组搜索*/
    D_MSG_SCAN_GROUP_END,       /**< 结束一组搜索*/

    D_MSG_PROG_SCAN_START_TS,   /**< 开始搜索一个TS流*/
    D_MSG_PROG_SCAN_STOP_TS,    /**< 停止搜索一个TS流*/
    D_MSG_PROG_SCAN_START_SRV,  /**< 开始搜索一个服务信息*/
    D_MSG_PROG_SCAN_STOP_SRV,   /**< 停止搜索一个服务的信息*/
    D_MSG_CA_START_TS,          /**< 开始分析一个TS流的管理信息*/
    D_MSG_CA_STOP_TS,           /**< 停止分析一个TS流的管理信息*/
    D_MSG_CA_START_SRV,         /**< 开始分析一个服务的控制信息*/
    D_MSG_CA_STOP_SRV,          /**< 停止分析一个服务的控制信息*/
    D_MSG_CA_EVT,               /**< CA事件*/
    D_MSG_SI_GET_TDT,           /**< 搜索到SI中新的时间信息*/
    D_MSG_SI_GET_EIT,           /**< 搜索到SI中新的EIT信息*/
    D_MSG_SI_GET_CAT,           /**< 搜索到SI中新的CAT信息*/
    D_MSG_SI_GET_PMT,           /**< 搜索到SI中新的PMT信息*/
    D_MSG_SUB_START,            /**< 预订节目到期*/

    D_MSG_SUBTITLE_REDRAW,      /**< 重新绘制字幕信息*/
    D_MSG_SUBTITLE_SHOW,        /**< 显示字幕信息*/
    D_MSG_SUBTITLE_HIDE,        /**< 隐藏字幕信息*/

    D_MSG_TELETEXT_ERROR,       /**< Teletext信息搜索失败*/
    D_MSG_TELETEXT_SHOW,        /**< 显示Teletext信息*/
    D_MSG_TELETEXT_HIDE,        /**< 隐藏Teletext信息*/
    D_MSG_TELETEXT_REDRAW,      /**< 重新绘制Teletext信息*/

    D_MSG_PVR_DISK_QUERY,       /**< 磁盘空间查询*/
    D_MSG_PVR_DISK_VALID,       /**< 磁盘状态正常*/
    D_MSG_PVR_DISK_FULL,        /**< 磁盘空间不足*/
    D_MSG_PVR_SET_MONITOR_QUEUE,/**< 设置PVR状态检测队列*/

    D_MSG_MEDIA_PLAY,       /**< 开始播放多媒体*/
    D_MSG_MEDIA_STOP,       /**< 停止播放多媒体*/
    D_MSG_MEDIA_PAUSE,      /**< 暂停多媒体文件播放*/
    D_MSG_MEDIA_RESUME,     /**< 恢复多媒体播放*/
    D_MSG_MEDIA_SEEK,       /**< 定位到某个位置开始播放*/
    D_MSG_MEDIA_GET_STATUS, /**< 获取多媒体播放状态*/
    D_MSG_MEDIA_SET_STATUS, /**< 设置多媒体播放状态*/

    D_MSG_TV_PLAY_SRV,          /**< 开始播放服务*/
    D_MSG_TV_PLAY_SRV_BY_IDS,   /**< 通过ID设置播放*/
    D_MSG_TV_PLAY_SRV_BY_PIDS,  /**< 通过PID设置播放*/
    D_MSG_TV_SCAN_SI,           /**< 设定SI分析模式*/
    D_MSG_TV_NEED_TABLE_VERSION,    /**< 监控表版本控制*/
    D_MSG_TV_DISPLAY_PIC_I,     /**< 开始显示I帧*/
    D_MSG_TV_DISPLAY_PIC_I_EXT, /**< 开始显示外部I帧*/
    D_MSG_TV_STOP,              /**< 停止播放当前节目*/
    D_MSG_TV_SET_AUD_MUTE,      /**< 静音*/
    D_MSG_TV_SET_AUD_ACC,       /**< 切换伴音*/
    D_MSG_TV_SET_AUD_TRACK,     /**< 设定声道*/
    D_MSG_TV_SET_VID_WINDOW,    /**< 设定显示窗口*/
    D_MSG_TV_SET_VID_FORMAT,    /**< 设定显示制式*/
    D_MSG_TV_SET_VID_OUTPUT,    /**< 设定视频输出*/
    D_MSG_TV_SET_VID_BLANK,     /**< 设定黑屏*/
    D_MSG_TV_CLEAR_VID,         /**< 清除视频*/
    D_MSG_TV_SET_VOL,           /**< 设定音量*/
    D_MSG_TV_SUSPEND,           /**< 挂起播放和搜索*/
    D_MSG_TV_STANDBY,           /**< 挂起并监控一个频点*/
    D_MSG_TV_VID_FMT_CHANGED,   /**< 视频制式改变*/
    D_MSG_TV_NEW_PIC_START,     /**< 新画面开始播放*/
    D_MSG_TV_NEW_AUD_START,     /**< 新音频开始播放*/
    D_MSG_SI_SW_UPDATE,         /**< 找到软件升级数据*/
    D_MSG_SI_CHAN_UPDATE,       /**< 节目si信息变化*/
    D_MSG_TV_CAT_CHANGED,       /**< CAT信息变化*/
    D_MSG_TV_PMT_CHANGED,       /**< PMT信息变化*/
    D_MSG_TV_SET_PIC_PARAM,     /**< 设置图像参数*/
    D_MSG_TV_SET_PIC_RATIO,     /**< 设置图像宽高比*/
    D_MSG_TV_SET_FMAN,          /**< 设定TV对应前端设备*/
    D_MSG_TV_SET_QUEUE,         /**< 设定TV对应的消息队列*/
    D_MSG_TV_SET_CHANGE_CHAN_MODE, /**< 设定换台静帧黑屏模式*/
    D_MSG_TV_RESET_CAT,         /**< 重新接收CAT 表*/
    D_MSG_TV_POWER_ON_CHECK,    /**< 开机检查SI里相关信息*/
    D_MSG_TV_SET_PLAY_LOCK,     /**< 锁定TV, 皮时不能播放节目*/

    D_MSG_GUI_VID_WIN_MSG,  /**< 视频小窗口提示信息*/
    D_MSG_HOTPLUG_MSG,      /**< 热插拔消息 */
    D_MSG_USER,                                 /**< 用户自定义消息开始*/
    D_MSG_USER1,            /**< 用户消息1*/
    D_MSG_USER2,            /**< 用户消息2*/
    D_MSG_USER3,            /**< 用户消息3*/
    D_MSG_EIT_CONTROL,      /**< 控制EIT搜索*/
    D_MSG_EIT_SCAN_MODE,    /**< EIT搜索模式*/
    D_MSG_EIT_FILTER_MODE,  /**< EIT过滤条件设置*/
    D_MSG_EIT_FILTER_SET,   /**< EIT过滤设置*/
    D_MSG_PIP_SET_QUEUE,

    /*add by yulz for pvr replay*/
    D_MSG_PVR_REPLAY_START,         /**< PVR REPLAY 启动消息*/
    D_MSG_PVR_REPLAY_STOP,          /**< PVR REPLAY 停止消息*/
    D_MSG_PVR_REPLAY_PAUSE,         /**< PVR REPLAY 暂停消息*/
    D_MSG_PVR_REPLAY_RESUME,        /**< PVR REPLAY 恢复消息*/
    D_MSG_PVR_REPLAY_RESTART,       /**< PVR REPLAY 重新启动消息*/
    D_MSG_PVR_REPLAY_FORWARD,       /**< PVR REPLAY 快进消息*/
    D_MSG_PVR_REPLAY_BACKWARD,      /**< PVR REPLAY 回退消息*/
    D_MSG_PVR_REPLAY_JUMP,          /**< PVR REPLAY 跳转消息*/
    D_MSG_PVR_REPLAY_SET_PARAM,     /**< PVR REPLAY 设置参数消息*/

    /* add by caig for pvr record */
    D_MSG_PVR_REC_CREAT,
    D_MSG_PVR_REC_START,        /**< 录像使能打开  这个可以不需要*/
    D_MSG_PVR_REC_PAUSE,        /**< 录像暂停*/
    D_MSG_PVR_REC_RESUME,       /**< 录像恢复*/
    D_MSG_PVR_REC_STOP,         /**< 停止录像*/
    /*add by hegx for tv*/
    D_MSG_TV_SET_VID_INPUT,     /**< 设定视频输入*/
    D_MSG_TV_SET_VOLBALANCE,    /**< 设定音量平衡*/
    /* reserved*/
    /* ...... */
    /* reserved*/

    /* 0x1000此值开始为项目层扩展值，开发与platform相关的新功能消息类型，
    尽量使用D_MSG_USERx解决，如需添加到此文件须和平台层相关负责人确认，
    project里新功能请在项目里统一管理并从0x1000开始自行定义添加*/
    D_MSG_PROJECT_EXT = 0x1000,
    /* reserved*/
    /* ...... */
    /* reserved*/
    D_MSG_DEADLINE = 0xFFFF
} D_MsgType;

/** @brief 通用消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
} D_GeneralMsg;

/** @brief 定时器消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    htimer; /**< 定时器句柄*/
} D_TimerMsg;

/** @brief 解复用设备消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    hdemux; /**< 解复用设备句柄*/
} D_DemuxMsg;

/** @brief 应用消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    happ;   /**< 应用句柄*/
    D_Handle    handle; /**< 参数句柄*/
    D_Ptr       arg;    /**< 应用参数*/
} D_AppMsg;

/** @brief 前端消息*/
typedef struct
{
    D_MsgType       type;       /**< 消息类型*/
    D_Handle        hfman;      /**< 前端管理设备句柄*/
    D_FEndType      fendtype;   /**节目类型 区分S C T的信号*/
    D_FEndParam     param;      /**< 前端设备参数*/
    D_FEndStatus    status;     /**< 前端状态*/
    D_FEndDiSEqC    diseqc;     /**< diseqc命令*/
    D_Handle        hq;         /**< 消息队列句柄*/
    D_FEndBlindScanType scantype;
    D_FEndBlindCmd  blindcmd;
    D_FEndFreq      startfreq;  /**<起始频率HZ*/
    D_FEndBandWitch bandwidth;  /**<带宽MHZ*/
    D_FEndLnbInfo   lnbinfo;
    D_Ptr           ptr;        /**<备用*/
    D_U32           reserved;   /**<备用*/
    D_FEndBlindResult result;   /**<盲扫结果>*/
} D_FEndMsg;

/** @brief 用户自定义消息*/
typedef struct
{
    D_MsgType   type;       /**< 消息类型*/
    D_Handle    handle;     /**< 消息相关句柄*/
    D_U32       param1;     /**< 参数1*/
    D_U32       param2;     /**< 参数2*/
    D_U32       param3;     /**< 参数3*/
    D_U32       param4;     /**< 参数4*/
} D_UserMsg;

/** @brief 搜索消息*/
typedef struct
{
    D_MsgType       type;       /**< 消息类型*/
    D_Handle        hscan;      /**< 搜索句柄*/
    D_FEndType      fendtype;   /**< 前端类型*/
    D_FEndParam     fendparam;  /**< 搜索频率*/
    D_FEndStatus    fendstatus; /**< 前端状态*/

    D_U16       freq_cnt;   /**< 搜索到的频点个数*/
    D_U16       prog_cnt;   /**< 搜索到的节目数*/

    D_U16       tv_cnt;     /**< 搜索到的电视数目*/
    D_U16       radio_cnt;  /**< 搜索到的广播数目*/
    D_U16       other_cnt;  /**< 搜索到的其它业务数目*/

    D_U16       tv_cnt_1;   /**< 搜索到的电视数目*/
    D_U16       radio_cnt_1;/**< 搜索到的广播数目*/
    D_U16       other_cnt_1;    /**< 搜索到的其它业务数目*/

    D_U8        progress;   /**< 搜索进度*/

    D_U32       param;      /**< 其它信息，如搜索进度、是否锁定等*/
    D_Ptr       ptr;        /**< 其它信息指针，可用于节目名等*/
    D_DBSrvInfo srvinfo;
} D_ScanMsg;

/** @brief 节目搜索消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    hscan;  /**< 搜索句柄*/
    D_ID        ts_id;  /**< 搜索TS流数据ID*/
    D_ID        srv_id; /**< 搜索节目的数据ID*/
} D_ProgScanMsg;

/** @brief CA控制信息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_ID        fend_id;/**< 参数ID*/
    D_ID        rec_id; /**< 参数ID*/
    D_U32       param1; /**< CA参数*/
    D_U32       param2; /**< CA参数*/
} D_CAMsg;
/** @brief CA控制信息*/

typedef  union
{
    struct
    {
        D_U32   type;
        D_U8    version;
        D_Ptr   pdata;
    } swparam;
    struct
    {
        D_U32   type;
        D_U8    version;
        D_Ptr   pdata;
    } siparam;
} D_SiMonParam;

/** @brief SI信息*/
typedef struct
{
    D_MsgType       type;   /**< 消息类型*/
    D_Handle        hscan;  /**< 搜索句柄*/
    D_SiMonParam    param;  /**<si信息更新参数*/
} D_SIMsg;

/** @brief EIT搜索消息*/
typedef struct
{
    D_MsgType   type;       /**< 消息类型*/
    D_U32       param;
} D_EITMsg;

/** @brief 预订节目消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_ID        sub_id; /**< 预订事件记录的ID*/
} D_SubMsg;


/** @brief 字幕消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    hsubt;  /**< 字幕处理器句柄*/
} D_SubtitleMsg;


typedef struct
{
    D_MsgType   type;   /**<消息类型*/
    D_Handle    httxt;  /**<Teletext处理器句柄*/
} D_TeletextMsg;

/** @brief PVR消息*/
typedef struct
{
    D_MsgType   type;   /**< 消息类型*/
    D_Handle    handle; /**< 搜索句柄*/
    D_U32       jump_value;
    D_U32       param;
} D_PvrMsg;

/** @brief Media消息*/
typedef struct
{
    D_MsgType   type;   /**<消息类型>*/
    D_Handle    handle; /**<Media设备句柄>*/
    union
    {
        struct
        {
            D_S32   x;  /**<显示位置*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
            D_S8    type;   /**<图片类型*/
            D_U8    rotate_flag;    /**<旋转标志0--0; 1--90; 2--180; 3--270*/
        } pic;
        struct
        {
            D_S8    type;   /**<音乐类型*/
            D_Ptr   pdata;  /*传输控件指针*/
        } music;
        struct
        {
            D_S32   x;      /**<播放窗口大小*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
            D_S8    type;   /**<视频类型*/
            D_U32   rate;   /**<播放速率*/
            D_U32   pos;    /**<播放位置*/
            D_Ptr   pdata;  /*传输控件指针*/
        } movie;
        struct
        {
            D_S32   x;      /**<播放窗口大小*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
        } ebk;
    } param;
} D_MediaMsg;

/** @brief TV播放消息*/
typedef struct
{
    D_MsgType   type;       /**< 消息类型*/
    D_Handle    htv;        /**< TV设备句柄*/
    union
    {
        D_ID        db_srv_id;
        D_ID        db_ts_id;
        D_ID        pic_I_id;
        D_U8        vol;
        D_S8        balance;
        D_Bool      vid_blank;
        D_Bool      aud_mute;
        D_U8        aud_acc;
        D_AudTrack  aud_track;
        D_VidFormat vid_format;
        D_VidOutput vid_output;
        D_VidInput  vid_input;
        D_VidPicParam pic_param;
        D_VidPicRatio   pic_ratio;
        D_U32       si_mode;
        D_U32       version_mode;
        D_Bool      flag;
        D_U32       timer;
        D_Handle    hq;
        struct
        {
            D_ID pic_I_id;
            D_U8* buf;
            D_U32 size;
        } i_ext;
        struct
        {
            D_S32   x;
            D_S32   y;
            D_S32   w;
            D_S32   h;
        } vid_window;
        struct
        {
            D_Bool      start;
            D_ID        db_ts_id;
            D_DBTSInfo  ts_info;
            D_U32       scan_mode;
        } power_on_check;
    } param;
} D_TVMsg;

typedef struct
{
    D_MsgType type; /**< 消息类型*/
    D_Bool show;    /**<显示还是清除*/
    D_Char *msg;    /**< 消息字符串*/
} D_GUIVidWinMsg;

typedef struct
{
    D_MsgType type;
    D_Bool plug;
    D_Ptr arg;
} D_HotplugMsg;

#define D_DEF_MSG_STRUCT\
        D_MsgType       type;\
        D_GeneralMsg    general;\
        D_TimerMsg      timer;\
        D_DemuxMsg      demux;\
        D_AppMsg        app;\
        D_FEndMsg       fend;\
        D_ScanMsg       scan;\
        D_ProgScanMsg   prog_scan;\
        D_CAMsg         ca;\
        D_SIMsg         si;\
        D_SubMsg        sub;\
        D_SubtitleMsg   subtitle;\
        D_TeletextMsg   teletext;\
        D_PvrMsg        pvr; \
        D_MediaMsg      media; \
        D_TVMsg         tv;\
        D_GUIVidWinMsg  vid_win;\
        D_HotplugMsg    hotplug;\
        D_UserMsg       user;\
        D_EITMsg        eit;

typedef union
{
    D_DEF_MSG_STRUCT
} D_Msg;

#ifdef  __cplusplus
}
#endif

#endif
