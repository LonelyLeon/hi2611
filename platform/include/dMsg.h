/** @file
* @brief ͨ����Ϣ����
* @author ����
* @date 2005-6-4  ����: �����ļ�
* @date 2005-5-18 ��ѫ: �޸��ļ�
������ϢD_MSG_LAODER_UPDATE
* @date 2013-04-25 lc: ͳһƽ̨, ��������
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


/** @brief ��Ϣ����*/
typedef enum
{
    D_MSG_NULL = -1,

    D_MSG_TIMER = 0,            /**< ��ʱ����Ϣ*/
    D_MSG_DEMUX_DATA,           /**< �⸴���豸���յ�����*/
    D_MSG_DEMUX_OVERFLOW,       /**< �⸴���豸���������*/
    D_MSG_DEMUX_ERROR,          /**< �⸴���豸����*/
    D_MSG_APP_CREATE,           /**< ��Ӧ�ô���*/
    D_MSG_APP_DESTROY,          /**< Ӧ�ý���*/
    D_MSG_APP_SYNC_REQ,         /**< Ӧ��ͬ������*/
    D_MSG_APP_TIMEOUT,          /**< Ӧ�ý�����Ϣ��ʱ*/

    D_MSG_FEND_SET_PARAM,       /**< �趨ǰ�˲���*/
    D_MSG_FEND_SET_PARAM_TRACK, /**< �趨ǰ�˲����������źű仯*/
    D_MSG_FEND_GET_LOCKED_REQ,  /**< ȡǰ����״̬����*/
    D_MSG_FEND_GET_LOCKED_REPLY,/**< ȡǰ����״̬Ӧ��*/
    D_MSG_FEND_GET_STATUS_REQ,  /**< ȡǰ���豸״̬����*/
    D_MSG_FEND_GET_STATUS_REPLY,/**< ȡǰ���豸״̬Ӧ��*/
    D_MSG_FEND_SET_LOCKED_DETECTOR,/**< �趨ǰ����״̬������*/
    // 2013-3-18 ������by wy
    D_MSG_FEND_SET_DISEQC,          /**< ����diseqc���豸*/
    D_MSG_FEND_SET_DISEQC_REPLY,
    D_MSG_FEND_BLIND_SCAN,          /**< äɨ*/
    D_MSG_FEND_BLIND_SCAN_REPLY,
    D_MSG_FEND_SET_LNB_POWER_ENABLE, /**< �趨lnb�����Ƿ��*/
    D_MSG_FEND_SET_STANDBY_POWER,/**< �趨�����ر�tuner��Դ�����͹���ģʽ*/
    D_MSG_FEND_SET_NORMAL_POWER,/**< �趨��tuner�͹���ģʽ��������ģʽ*/
    D_MSG_KEY_PRESSED,          /**< ������*/
    D_MSG_KEY_RELEASE,          /**< ��̧��*/

    D_MSG_SCAN_OK,              /**< �������*/
    D_MSG_SCAN_FEND_STATUS,     /**< �������޷���סƵ��*/
    D_MSG_SCAN_FREQ,            /**< ��ʼ����Ƶ��*/
    D_MSG_SCAN_FREQ_END,        /**< ��������Ƶ��*/
    D_MSG_SCAN_SI,              /**< ��ʼ����Ƶ��si ��Ϣ*/
    D_MSG_SCAN_DATA,            /**< ����������*/
    D_MSG_SCAN_PROGRESS,        /**< ��������*/
    D_MSG_SCAN_TRY_LOCK,        /**< ����ȥ����Ƶ��*/
    D_MSG_SCAN_GROUP_START,     /**< ��ʼ����һ������*/
    D_MSG_SCAN_GROUP_END,       /**< ����һ������*/

    D_MSG_PROG_SCAN_START_TS,   /**< ��ʼ����һ��TS��*/
    D_MSG_PROG_SCAN_STOP_TS,    /**< ֹͣ����һ��TS��*/
    D_MSG_PROG_SCAN_START_SRV,  /**< ��ʼ����һ��������Ϣ*/
    D_MSG_PROG_SCAN_STOP_SRV,   /**< ֹͣ����һ���������Ϣ*/
    D_MSG_CA_START_TS,          /**< ��ʼ����һ��TS���Ĺ�����Ϣ*/
    D_MSG_CA_STOP_TS,           /**< ֹͣ����һ��TS���Ĺ�����Ϣ*/
    D_MSG_CA_START_SRV,         /**< ��ʼ����һ������Ŀ�����Ϣ*/
    D_MSG_CA_STOP_SRV,          /**< ֹͣ����һ������Ŀ�����Ϣ*/
    D_MSG_CA_EVT,               /**< CA�¼�*/
    D_MSG_SI_GET_TDT,           /**< ������SI���µ�ʱ����Ϣ*/
    D_MSG_SI_GET_EIT,           /**< ������SI���µ�EIT��Ϣ*/
    D_MSG_SI_GET_CAT,           /**< ������SI���µ�CAT��Ϣ*/
    D_MSG_SI_GET_PMT,           /**< ������SI���µ�PMT��Ϣ*/
    D_MSG_SUB_START,            /**< Ԥ����Ŀ����*/

    D_MSG_SUBTITLE_REDRAW,      /**< ���»�����Ļ��Ϣ*/
    D_MSG_SUBTITLE_SHOW,        /**< ��ʾ��Ļ��Ϣ*/
    D_MSG_SUBTITLE_HIDE,        /**< ������Ļ��Ϣ*/

    D_MSG_TELETEXT_ERROR,       /**< Teletext��Ϣ����ʧ��*/
    D_MSG_TELETEXT_SHOW,        /**< ��ʾTeletext��Ϣ*/
    D_MSG_TELETEXT_HIDE,        /**< ����Teletext��Ϣ*/
    D_MSG_TELETEXT_REDRAW,      /**< ���»���Teletext��Ϣ*/

    D_MSG_PVR_DISK_QUERY,       /**< ���̿ռ��ѯ*/
    D_MSG_PVR_DISK_VALID,       /**< ����״̬����*/
    D_MSG_PVR_DISK_FULL,        /**< ���̿ռ䲻��*/
    D_MSG_PVR_SET_MONITOR_QUEUE,/**< ����PVR״̬������*/

    D_MSG_MEDIA_PLAY,       /**< ��ʼ���Ŷ�ý��*/
    D_MSG_MEDIA_STOP,       /**< ֹͣ���Ŷ�ý��*/
    D_MSG_MEDIA_PAUSE,      /**< ��ͣ��ý���ļ�����*/
    D_MSG_MEDIA_RESUME,     /**< �ָ���ý�岥��*/
    D_MSG_MEDIA_SEEK,       /**< ��λ��ĳ��λ�ÿ�ʼ����*/
    D_MSG_MEDIA_GET_STATUS, /**< ��ȡ��ý�岥��״̬*/
    D_MSG_MEDIA_SET_STATUS, /**< ���ö�ý�岥��״̬*/

    D_MSG_TV_PLAY_SRV,          /**< ��ʼ���ŷ���*/
    D_MSG_TV_PLAY_SRV_BY_IDS,   /**< ͨ��ID���ò���*/
    D_MSG_TV_PLAY_SRV_BY_PIDS,  /**< ͨ��PID���ò���*/
    D_MSG_TV_SCAN_SI,           /**< �趨SI����ģʽ*/
    D_MSG_TV_NEED_TABLE_VERSION,    /**< ��ر�汾����*/
    D_MSG_TV_DISPLAY_PIC_I,     /**< ��ʼ��ʾI֡*/
    D_MSG_TV_DISPLAY_PIC_I_EXT, /**< ��ʼ��ʾ�ⲿI֡*/
    D_MSG_TV_STOP,              /**< ֹͣ���ŵ�ǰ��Ŀ*/
    D_MSG_TV_SET_AUD_MUTE,      /**< ����*/
    D_MSG_TV_SET_AUD_ACC,       /**< �л�����*/
    D_MSG_TV_SET_AUD_TRACK,     /**< �趨����*/
    D_MSG_TV_SET_VID_WINDOW,    /**< �趨��ʾ����*/
    D_MSG_TV_SET_VID_FORMAT,    /**< �趨��ʾ��ʽ*/
    D_MSG_TV_SET_VID_OUTPUT,    /**< �趨��Ƶ���*/
    D_MSG_TV_SET_VID_BLANK,     /**< �趨����*/
    D_MSG_TV_CLEAR_VID,         /**< �����Ƶ*/
    D_MSG_TV_SET_VOL,           /**< �趨����*/
    D_MSG_TV_SUSPEND,           /**< ���𲥷ź�����*/
    D_MSG_TV_STANDBY,           /**< ���𲢼��һ��Ƶ��*/
    D_MSG_TV_VID_FMT_CHANGED,   /**< ��Ƶ��ʽ�ı�*/
    D_MSG_TV_NEW_PIC_START,     /**< �»��濪ʼ����*/
    D_MSG_TV_NEW_AUD_START,     /**< ����Ƶ��ʼ����*/
    D_MSG_SI_SW_UPDATE,         /**< �ҵ������������*/
    D_MSG_SI_CHAN_UPDATE,       /**< ��Ŀsi��Ϣ�仯*/
    D_MSG_TV_CAT_CHANGED,       /**< CAT��Ϣ�仯*/
    D_MSG_TV_PMT_CHANGED,       /**< PMT��Ϣ�仯*/
    D_MSG_TV_SET_PIC_PARAM,     /**< ����ͼ�����*/
    D_MSG_TV_SET_PIC_RATIO,     /**< ����ͼ���߱�*/
    D_MSG_TV_SET_FMAN,          /**< �趨TV��Ӧǰ���豸*/
    D_MSG_TV_SET_QUEUE,         /**< �趨TV��Ӧ����Ϣ����*/
    D_MSG_TV_SET_CHANGE_CHAN_MODE, /**< �趨��̨��֡����ģʽ*/
    D_MSG_TV_RESET_CAT,         /**< ���½���CAT ��*/
    D_MSG_TV_POWER_ON_CHECK,    /**< �������SI�������Ϣ*/
    D_MSG_TV_SET_PLAY_LOCK,     /**< ����TV, Ƥʱ���ܲ��Ž�Ŀ*/

    D_MSG_GUI_VID_WIN_MSG,  /**< ��ƵС������ʾ��Ϣ*/
    D_MSG_HOTPLUG_MSG,      /**< �Ȳ����Ϣ */
    D_MSG_USER,                                 /**< �û��Զ�����Ϣ��ʼ*/
    D_MSG_USER1,            /**< �û���Ϣ1*/
    D_MSG_USER2,            /**< �û���Ϣ2*/
    D_MSG_USER3,            /**< �û���Ϣ3*/
    D_MSG_EIT_CONTROL,      /**< ����EIT����*/
    D_MSG_EIT_SCAN_MODE,    /**< EIT����ģʽ*/
    D_MSG_EIT_FILTER_MODE,  /**< EIT������������*/
    D_MSG_EIT_FILTER_SET,   /**< EIT��������*/
    D_MSG_PIP_SET_QUEUE,

    /*add by yulz for pvr replay*/
    D_MSG_PVR_REPLAY_START,         /**< PVR REPLAY ������Ϣ*/
    D_MSG_PVR_REPLAY_STOP,          /**< PVR REPLAY ֹͣ��Ϣ*/
    D_MSG_PVR_REPLAY_PAUSE,         /**< PVR REPLAY ��ͣ��Ϣ*/
    D_MSG_PVR_REPLAY_RESUME,        /**< PVR REPLAY �ָ���Ϣ*/
    D_MSG_PVR_REPLAY_RESTART,       /**< PVR REPLAY ����������Ϣ*/
    D_MSG_PVR_REPLAY_FORWARD,       /**< PVR REPLAY �����Ϣ*/
    D_MSG_PVR_REPLAY_BACKWARD,      /**< PVR REPLAY ������Ϣ*/
    D_MSG_PVR_REPLAY_JUMP,          /**< PVR REPLAY ��ת��Ϣ*/
    D_MSG_PVR_REPLAY_SET_PARAM,     /**< PVR REPLAY ���ò�����Ϣ*/

    /* add by caig for pvr record */
    D_MSG_PVR_REC_CREAT,
    D_MSG_PVR_REC_START,        /**< ¼��ʹ�ܴ�  ������Բ���Ҫ*/
    D_MSG_PVR_REC_PAUSE,        /**< ¼����ͣ*/
    D_MSG_PVR_REC_RESUME,       /**< ¼��ָ�*/
    D_MSG_PVR_REC_STOP,         /**< ֹͣ¼��*/
    /*add by hegx for tv*/
    D_MSG_TV_SET_VID_INPUT,     /**< �趨��Ƶ����*/
    D_MSG_TV_SET_VOLBALANCE,    /**< �趨����ƽ��*/
    /* reserved*/
    /* ...... */
    /* reserved*/

    /* 0x1000��ֵ��ʼΪ��Ŀ����չֵ��������platform��ص��¹�����Ϣ���ͣ�
    ����ʹ��D_MSG_USERx�����������ӵ����ļ����ƽ̨����ظ�����ȷ�ϣ�
    project���¹���������Ŀ��ͳһ������0x1000��ʼ���ж������*/
    D_MSG_PROJECT_EXT = 0x1000,
    /* reserved*/
    /* ...... */
    /* reserved*/
    D_MSG_DEADLINE = 0xFFFF
} D_MsgType;

/** @brief ͨ����Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
} D_GeneralMsg;

/** @brief ��ʱ����Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    htimer; /**< ��ʱ�����*/
} D_TimerMsg;

/** @brief �⸴���豸��Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    hdemux; /**< �⸴���豸���*/
} D_DemuxMsg;

/** @brief Ӧ����Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    happ;   /**< Ӧ�þ��*/
    D_Handle    handle; /**< �������*/
    D_Ptr       arg;    /**< Ӧ�ò���*/
} D_AppMsg;

/** @brief ǰ����Ϣ*/
typedef struct
{
    D_MsgType       type;       /**< ��Ϣ����*/
    D_Handle        hfman;      /**< ǰ�˹����豸���*/
    D_FEndType      fendtype;   /**��Ŀ���� ����S C T���ź�*/
    D_FEndParam     param;      /**< ǰ���豸����*/
    D_FEndStatus    status;     /**< ǰ��״̬*/
    D_FEndDiSEqC    diseqc;     /**< diseqc����*/
    D_Handle        hq;         /**< ��Ϣ���о��*/
    D_FEndBlindScanType scantype;
    D_FEndBlindCmd  blindcmd;
    D_FEndFreq      startfreq;  /**<��ʼƵ��HZ*/
    D_FEndBandWitch bandwidth;  /**<����MHZ*/
    D_FEndLnbInfo   lnbinfo;
    D_Ptr           ptr;        /**<����*/
    D_U32           reserved;   /**<����*/
    D_FEndBlindResult result;   /**<äɨ���>*/
} D_FEndMsg;

/** @brief �û��Զ�����Ϣ*/
typedef struct
{
    D_MsgType   type;       /**< ��Ϣ����*/
    D_Handle    handle;     /**< ��Ϣ��ؾ��*/
    D_U32       param1;     /**< ����1*/
    D_U32       param2;     /**< ����2*/
    D_U32       param3;     /**< ����3*/
    D_U32       param4;     /**< ����4*/
} D_UserMsg;

/** @brief ������Ϣ*/
typedef struct
{
    D_MsgType       type;       /**< ��Ϣ����*/
    D_Handle        hscan;      /**< �������*/
    D_FEndType      fendtype;   /**< ǰ������*/
    D_FEndParam     fendparam;  /**< ����Ƶ��*/
    D_FEndStatus    fendstatus; /**< ǰ��״̬*/

    D_U16       freq_cnt;   /**< ��������Ƶ�����*/
    D_U16       prog_cnt;   /**< �������Ľ�Ŀ��*/

    D_U16       tv_cnt;     /**< �������ĵ�����Ŀ*/
    D_U16       radio_cnt;  /**< �������Ĺ㲥��Ŀ*/
    D_U16       other_cnt;  /**< ������������ҵ����Ŀ*/

    D_U16       tv_cnt_1;   /**< �������ĵ�����Ŀ*/
    D_U16       radio_cnt_1;/**< �������Ĺ㲥��Ŀ*/
    D_U16       other_cnt_1;    /**< ������������ҵ����Ŀ*/

    D_U8        progress;   /**< ��������*/

    D_U32       param;      /**< ������Ϣ�����������ȡ��Ƿ�������*/
    D_Ptr       ptr;        /**< ������Ϣָ�룬�����ڽ�Ŀ����*/
    D_DBSrvInfo srvinfo;
} D_ScanMsg;

/** @brief ��Ŀ������Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    hscan;  /**< �������*/
    D_ID        ts_id;  /**< ����TS������ID*/
    D_ID        srv_id; /**< ������Ŀ������ID*/
} D_ProgScanMsg;

/** @brief CA������Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_ID        fend_id;/**< ����ID*/
    D_ID        rec_id; /**< ����ID*/
    D_U32       param1; /**< CA����*/
    D_U32       param2; /**< CA����*/
} D_CAMsg;
/** @brief CA������Ϣ*/

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

/** @brief SI��Ϣ*/
typedef struct
{
    D_MsgType       type;   /**< ��Ϣ����*/
    D_Handle        hscan;  /**< �������*/
    D_SiMonParam    param;  /**<si��Ϣ���²���*/
} D_SIMsg;

/** @brief EIT������Ϣ*/
typedef struct
{
    D_MsgType   type;       /**< ��Ϣ����*/
    D_U32       param;
} D_EITMsg;

/** @brief Ԥ����Ŀ��Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_ID        sub_id; /**< Ԥ���¼���¼��ID*/
} D_SubMsg;


/** @brief ��Ļ��Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    hsubt;  /**< ��Ļ���������*/
} D_SubtitleMsg;


typedef struct
{
    D_MsgType   type;   /**<��Ϣ����*/
    D_Handle    httxt;  /**<Teletext���������*/
} D_TeletextMsg;

/** @brief PVR��Ϣ*/
typedef struct
{
    D_MsgType   type;   /**< ��Ϣ����*/
    D_Handle    handle; /**< �������*/
    D_U32       jump_value;
    D_U32       param;
} D_PvrMsg;

/** @brief Media��Ϣ*/
typedef struct
{
    D_MsgType   type;   /**<��Ϣ����>*/
    D_Handle    handle; /**<Media�豸���>*/
    union
    {
        struct
        {
            D_S32   x;  /**<��ʾλ��*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
            D_S8    type;   /**<ͼƬ����*/
            D_U8    rotate_flag;    /**<��ת��־0--0; 1--90; 2--180; 3--270*/
        } pic;
        struct
        {
            D_S8    type;   /**<��������*/
            D_Ptr   pdata;  /*����ؼ�ָ��*/
        } music;
        struct
        {
            D_S32   x;      /**<���Ŵ��ڴ�С*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
            D_S8    type;   /**<��Ƶ����*/
            D_U32   rate;   /**<��������*/
            D_U32   pos;    /**<����λ��*/
            D_Ptr   pdata;  /*����ؼ�ָ��*/
        } movie;
        struct
        {
            D_S32   x;      /**<���Ŵ��ڴ�С*/
            D_S32   y;
            D_S32   w;
            D_S32   h;
        } ebk;
    } param;
} D_MediaMsg;

/** @brief TV������Ϣ*/
typedef struct
{
    D_MsgType   type;       /**< ��Ϣ����*/
    D_Handle    htv;        /**< TV�豸���*/
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
    D_MsgType type; /**< ��Ϣ����*/
    D_Bool show;    /**<��ʾ�������*/
    D_Char *msg;    /**< ��Ϣ�ַ���*/
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
