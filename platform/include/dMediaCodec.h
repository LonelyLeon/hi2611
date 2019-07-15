/** @file
*@brief 硬解码设备
*@author houwb
*@date 2013-11-5 houwb 建立文件
*/
#ifndef DMEDIACODEC_H_
#define DMEDIACODEC_H_
#ifdef __cplusplus
extern "C"{
#endif

#include "dTypes.h"
#include "dAV.h"

typedef enum {
    D_MEDIACODEC_TYPE_AUDIO = 0,
    D_MEDIACODEC_TYPE_VIDEO,
    D_MEDIACODEC_TYPE_JPEG,
} D_MediaCodecType;

typedef D_Handle D_MediaCodecHandle;

typedef struct
{
    // set decoder param with docoder stopped
    D_Result (*setParam)(D_MediaCodecHandle handle, D_Ptr param) D_FUNCPOSTFIT;
    // get decoder param
    D_Result (*getParam)(D_MediaCodecHandle handle, D_Ptr param) D_FUNCPOSTFIT;
    // start decode
    void (*start)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // stop decode
    void (*stop)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // write data to decoder
    D_U32 (*writeData)(D_MediaCodecHandle handle, const void *buffer, D_U32 len) D_FUNCPOSTFIT;
    // notify decoder data ready
    void (*dataReady)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get decoder status
    D_U8 (*getStatus)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
} D_MediaCodecOps;

/*
 * JPEG CODEC
 */
typedef struct _D_MdeiaCodecJpegParamIn {
    void *out_wnd_buffer;                       // output window buffer addr
    D_U16 out_wnd_width, out_wnd_height;        // output window width & height
    D_U16 out_x, out_y, out_width, out_height;  // output image pos
    D_U16 pic_width, pic_height;                // jpeg picture width & height
    D_U8 jpeg_type;                             // base line or progressive
    D_U8 data_mode;                             // 0--yuv444 or 1--yuv411
    D_U8 pingpang_mode;                         // 0--single output window or 1--double output window
    D_U8 decode_type;                           // 0--scaler or 1--noscaler or 2--partial
    D_U8 preview_mode;                          // 0--normal or 1--decode thumbnail
} D_MdeiaCodecJpegParamIn;

typedef struct _D_MdeiaCodecJpegParamOut {
    void *out_wnd_buffer;                       // output window buffer addr
    D_U16 out_wnd_width, out_wnd_height;        // output window width & height
    D_U16 out_x, out_y, out_width, out_height;  // output image pos
    D_U16 pic_width, pic_height;                // jpeg picture width & height
    D_U8 jpeg_type;                             // base line or progressive
    D_U8 data_mode;                             // 0--yuv444 or 1--yuv411
    D_U8 pingpang_mode;                         // 0--single output window or 1--double output window
    D_U8 decode_type;                           // 0--scaler or 1--noscaler or 2--partial
} D_MdeiaCodecJpegParamOut;

typedef enum
{
    JpuScalerSrcType_YUV444 = 0,
    JpuScalerSrcType_BGR888,
}D_MediaCodecJpuScalerSrcType;

/** @breif jpu scaler参数 */
typedef struct
{
    D_MediaCodecJpuScalerSrcType src_type;
    D_Ptr src_buf;  /**< 源地址 */
    D_U32 src_ddr_line;  /**< 源数据行宽 */
    D_U16 src_orig_height;  /**< 源数据高 */
    D_U16 src_width;  /**< 源数据输入宽 */
    D_U16 src_height;  /**< 源数据输入高 */
    D_Ptr dst_buf;  /**< 目标地址 */
    D_U32 dst_ddr_line;  /**< 目标数据行宽 */
    D_U16 dst_orig_height;  /**< 目标数据高 */
    D_U16 dst_width;  /**< 目标输出宽 */
    D_U16 dst_height;  /**< 目标输出高 */
}D_MediaCodecJpuScalerParam;

typedef enum
{
	JpuRotateType_90		= 1,
	JpuRotateType_180		= 2,
	JpuRotateType_270		= 3,
}D_MediaCodecJpuRotateType;
/** @breif jpu rotate参数 */
typedef struct
{
    D_MediaCodecJpuRotateType rotate_type;	//旋转/镜像方向
    D_Ptr src_buf;  				//源数据地址
    D_Ptr dst_buf;					//旋转后数据存储地址
    D_U16 src_width;  				// 源图像宽
    D_U16 src_height;  			//源图像高
    D_U16 src_x;					//源图像起始横坐标
    D_U16 src_y;					//源图像起始纵坐标
    D_U16 src_store_width;  		//源数据存储宽度
    D_U16 src_store_height;  		//源数据存储高度
    D_U16 dst_store_width;  		//旋转后数据存储宽
    D_U16 dst_store_height;  		//旋转后数据存储高
}D_MediaCodecJpuRotateParam;

typedef enum
{
    D_JpuStatus_Idle = 0x00,
    D_JpuStatus_WaitData = 0x01,
    D_JpuStatus_HeaderReady = 0x02,
    D_JpuStatus_End = 0x04,
    D_JpuStatus_Error = 0x08,
}D_MediaCodecJpuStatus;

typedef struct _D_MediaCodecJpegOps {
    // set decoder param with docoder stopped
    D_Result (*setParam)(D_MediaCodecHandle handle, D_MdeiaCodecJpegParamIn *param) D_FUNCPOSTFIT;
    // get decoder param
    D_Result (*getParam)(D_MediaCodecHandle handle, D_MdeiaCodecJpegParamOut *param) D_FUNCPOSTFIT;
    // start decode
    void (*start)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // stop decode
    void (*stop)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // write data to decoder
    D_U32 (*writeData)(D_MediaCodecHandle handle, const void *buffer, D_U32 len,D_U8 jpg_file_end) D_FUNCPOSTFIT;
    // notify decoder data ready
    void (*dataReady)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get decoder status
    D_MediaCodecJpuStatus (*getStatus)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get ready frame index
    D_U32 (*getReadyFrame)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // used for progressive
    void (*setProgressiveAlpha)(D_MediaCodecHandle handle, D_U8 alpha, D_U8 mode) D_FUNCPOSTFIT;
    void (*setProgressiveType)(D_MediaCodecHandle handle, D_U8 type) D_FUNCPOSTFIT;
    // process after decoding
    void (*postProcess)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    D_Result (*scaler)(D_MediaCodecHandle handle, D_MediaCodecJpuScalerParam *param) D_FUNCPOSTFIT;  /**< jpu scaler方法 */
#if (defined(D_ARCH_HI2610E))
    D_Result (*rotate)( D_MediaCodecJpuRotateParam *param)D_FUNCPOSTFIT;/**< jpu rotate方法 */
#endif
} D_MediaCodecJpegOps;

/*
 * AUDIO CODEC
 */

typedef struct _D_MdeiaCodecAudioParamIn {
    void *out_buffer;       // output pcm buffer
    D_U32 out_buffer_len;   // output pcm buffer length
    //D_U8 pcm_format;        // pcm format
    D_U32 sample_rate;      // sample rate
    D_U8 channels;          // channel count
    D_AudCodecType codec_id;          // codec id
} D_MdeiaCodecAudioParamIn;

typedef struct _D_MdeiaCodecAudioParamOut {
    void *out_buffer;       // output pcm buffer
    D_U32 out_buffer_len;   // output pcm buffer length
    //D_U8 pcm_format;        // pcm format
    D_U32 sample_rate;      // sample rate
    D_U8 channels;          // channel count
    D_AudCodecType codec_id;          // codec id
} D_MdeiaCodecAudioParamOut;

typedef enum
{
    D_ApuStatus_Nul = 0x00,
    D_ApuStatus_StreamReq = 0x01,
}D_MediaCodecApuStatus;

typedef struct _D_MediaCodecAudioOps {
    // set decoder param with docoder stopped
    D_Result (*setParam)(D_MediaCodecHandle handle, D_MdeiaCodecAudioParamIn *param) D_FUNCPOSTFIT;
    // get decoder param
    D_Result (*getParam)(D_MediaCodecHandle handle, D_MdeiaCodecAudioParamOut *param) D_FUNCPOSTFIT;
    // start decode
    void (*start)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // stop decode
    void (*stop)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // write data to decoder
    D_U32 (*writeData)(D_MediaCodecHandle handle, const void *buffer, D_U32 len) D_FUNCPOSTFIT;
    // notify decoder data ready
    void (*dataReady)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get decoder status
    D_MediaCodecApuStatus (*getStatus)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get sample count already played
    D_U32 (*getPlayedSamples)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get sample count not played yet
    D_U32 (*getCachedSamples)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // pause decode
    void (*pause)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
} D_MediaCodecAudioOps;

/* 配置H264解码重启后第一个序列的前四个参考帧是否丢掉*/
#define D_MC_VideoFirst4FrameDiscard_Enable (0xfd15cafd)
#define D_MC_VideoFirst4FrameDiscard_Disable (0x0d15cafd)

/*
 * VIDEO CODEC
 */
typedef struct _D_MdeiaCodecVideoParamIn {
    void *out_buffer;               // video output buffer
    D_U32 out_buffer_len;           // video output buffer length
    D_U16 pic_width, pic_height;    // video picture width & height
    D_VidCodecType codec_id;                  // video codec id
    D_U8 error_deal_mode;           // 0 -- normal; 1 -- skip error b-frame
    D_U32 discard_first_4frame;           // D_MC_VideoFirst4FrameDiscard_Enable/Disable or other
} D_MdeiaCodecVideoParamIn;

typedef struct _D_MdeiaCodecVideoParamOut {
    void *out_buffer;               // video output buffer
    D_U32 out_buffer_len;           // video output buffer length
    D_U16 pic_width, pic_height;    // video picture width & height
    D_VidCodecType codec_id;                  // video codec id
} D_MdeiaCodecVideoParamOut;

typedef struct _D_VideoStreamInfo {
    D_Bool stream_valid;
    D_U16 pic_width;
    D_U16 pic_height;
} D_VideoStreamInfo;

typedef enum
{
    D_VpuStatus_Nul = 0x00,
    D_VpuStatus_StreamReq = 0x01,
    D_VpuStatus_PlayIdle = 0x02,
    D_VpuStatus_FrameReady = 0x04,
}D_MediaCodecVpuStatus;

typedef struct _D_MediaCodecVideoOps {
    // set decoder param with docoder stopped
    D_Result (*setParam)(D_MediaCodecHandle handle, D_MdeiaCodecVideoParamIn *param) D_FUNCPOSTFIT;
    // get decoder param
    D_Result (*getParam)(D_MediaCodecHandle handle, D_MdeiaCodecVideoParamOut *param) D_FUNCPOSTFIT;
    // start decode
    void (*start)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // stop decode
    void (*stop)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // write data to decoder
    D_U32 (*writeData)(D_MediaCodecHandle handle, const void *buffer, D_U32 len) D_FUNCPOSTFIT;
    // notify decoder data ready
    void (*dataReady)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get decoder status
    D_MediaCodecVpuStatus (*getStatus)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get ready frame index
    D_U32 (*getReadyFrame)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get frame count not played yet
    D_U32 (*getCachedFrames)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    // get stream info
    D_Result (*getStreamInfo)(D_MediaCodecHandle handle, D_VideoStreamInfo *info) D_FUNCPOSTFIT;
    // notify decoder frame played
    void (*framePlayed)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
    D_U32 (*getReadyFramePTS)(D_MediaCodecHandle handle) D_FUNCPOSTFIT;
} D_MediaCodecVideoOps;

D_Result d_mediacodec_open(void);
D_Result d_mediacodec_close(void);
D_MediaCodecHandle d_mediacodec_create(D_ID id, D_MediaCodecType type);
D_Result d_mediacodec_destroy(D_MediaCodecHandle handle);
D_Result d_mediacodec_get_op_funs(D_MediaCodecHandle handle, D_MediaCodecOps const **ops);

#ifdef __cplusplus
}
#endif
#endif /* DMEDIACODEC_H_ */
