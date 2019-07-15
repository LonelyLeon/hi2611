/** @file dMedia.h
* @brief Mediaģ��
* @author wangyq
* @date 2013-10-10 wangyq: �����ļ�
* @date 2014-05-04 wangyq: �������ע��
*/

#ifndef _D_Media_H_
#define _D_Media_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"
#include "dControl.h"


/** @brief �û��������Ϣ��Ĳ���*/
#define D_MSG_USER_PARAM1_MEDIA_INFO        0xff5a0100

/*��Ը�����ӽ�����Ƶ�߿����*/
#define D_Media_Movie_Codec_Width_Max	(1920)
#define D_Media_Movie_Codec_Height_Max	(1088)

#define D_Media_Movie_Codec_Width_Limit		(256)
#define D_Media_Movie_Codec_Height_LImit	(192)

/**@brief  ͼƬ����*/
typedef enum 
{
	IMGTYPE_JPEG = 0, /**< JPEG��ʽͼƬ*/
	IMGTYPE_BMP,      /**< BMP��ʽͼƬ */
	IMGTYPE_GIF,      /**< GIF��ʽͼƬ*/
	IMGTYPE_PNG,      /**< PNG��ʽͼƬ */
	IMGTPYE_MAX
}D_PictureType;

/**@breif ͼƬ����ģʽ*/
typedef enum
{
	PICTURE_PLAY_SINGLE_ONE=0,
	PICTUREC_PLAY_SINGLE_REAPEAT,	
	PICTURE_PLAY_ALL_ONE,
	PICTURE_PLAY_ALL_REAPEAT
}D_PictureCycleMode;

/**@brief ͼƬ����״̬*/
typedef enum 
{
	PICTURE_STATUS_STOP = 0,//����
	PICTURE_STATUS_RUN,//������
	PICTURE_STATUS_PAUSE //��ͣ
}D_PictureStatus;

/**@brief ͼƬ�򿪷�ʽ��dfpģ���Ӧ����*/
typedef enum 
{
    PICTURE_OPEN_MODE_NORMAL = 0,
    PICTURE_OPEN_MODE_PREVIEW,
} D_PictureOpenMode;

/**@brief ���ֲ���ģʽ*/
typedef enum
{
	MUSIC_PLAY_SINGLE_ONE=0,
	MUSIC_PLAY_SINGLE_REPEAT,	
	MUSIC_PLAY_ALL_ONE,
	MUSIC_PLAY_ALL_REPEAT
}D_MusicCycleMode;

/**@brief ���ֲ���״̬*/
typedef enum 
{
	MUSIC_STATUS_STOP = 0,//����
	MUSIC_STATUS_RUN,//������
	MUSIC_STATUS_PAUSE //��ͣ��
}D_MusicStatus;

/**@brief ebk����״̬*/
typedef enum {
    EBK_STATUS_STOP = 0,
    EBK_STATUS_RUN,
    EBK_STATUS_PAUSE,
}D_EbkStatus;

/**@brief ��Ƶffmpeg�汾*/
typedef enum
{
	MOVIE_FFMPEG_VER_OLD=0,  /* �ɰ汾����֧�����粥��*/
	MOVIE_FFMPEG_VER_NEW_V34, /* 3.4�汾��֧�����粥��*/
}D_MovieFFmepgVersion;

/**@brief ��Ƶ����ģʽ*/
typedef enum
{
	MOVIE_PLAY_SINGLE_ONE=0,
	MOVIE_PLAY_SINGLE_REAPEAT,	
	MOVIE_PLAY_ALL_ONE,
	MOVIE_PLAY_ALL_REAPEAT
}D_MovieCycleMode;

/**@brief ��Ƶ����״̬*/
typedef enum 
{
	MOVIE_STATUS_STOP = 0,//��ͣ
	MOVIE_STATUS_PLAY,//������
	MOVIE_STATUS_PAUSE,//��ͣ��
	MOVIE_STATUS_SEEK,
	MOVIE_STATUS_WAITING, //������
}D_MovieStatus;

/** @brief������ʾ����*/
typedef struct
{
	D_U32 offset_x;//ˮƽƫ��	
	D_U32 offset_y;//��ֱƫ��
	
	D_U32 out_width;//	��ʾ���	
	D_U32 out_height;//��ʾ�߶�
}D_ShowRect;

/**@brief ͼƬ��Ϣ*/
typedef struct
{
	D_U16 file_type;//// 0:jpeg.  1:bmp
	D_U16 jpeg_type;
	D_U32 width;//ԭʼ��
	D_U32 height;//ԭʼ��
	D_S64 filesize;//�ļ���С���ֽ�
}D_PictureInfo;

typedef struct
{
    D_U16 pic_x;
    D_U16 pic_y;
    D_U16 pic_w;
    D_U16 pic_h;
    D_U16 win_w;
    D_U16 win_h;
    D_Ptr dst_addr;
}D_Bmp_Data;

/**@brief ͼƬ��Ϣ*/
typedef struct
{
	/*callback ���˵���ʾ��Ϣʹ��*/
	D_U8 pic_decode_ret;/*ͼƬ������Ϣ  0: ����ʧ�� 1:�ڴ治��*/
	D_Char path[256];
        D_Bmp_Data bmp_data;
}D_Pic_Cb;


/**@brief ������Ϣ*/
typedef struct
{
	
	D_U32 codec_id;//��Ƶ�����ʽ�����ϲ����֧�ֵĲ��Ÿ�ʽ
	D_U8 channel;//ͨ����
	D_U32 BitsPerSec;//������
	D_U32 sample_rate;//������
	D_S64 filesize;//�ļ���С���ֽ�
	D_Double totaltime;//��ʱ������
       D_Char title[32];
	D_Char artist[32];
	D_Char album[32];
    D_Char year[32];
	D_U8 tag_encoding_type; // 0--ansi(mp3); 1--utf8(mp3); 2--utf16(wma)
}D_MusicInfo;

/**@brief ��Ƶ��Ϣ*/
typedef struct
{
	D_U32 width;//ԭʼ��
	D_U32 height;//ԭʼ��
	D_Double totaltime;//��ʱ��
	D_Double  frame_rate; //֡��
	D_S64 filesize;//�ļ���С���ֽ�
	D_U32 sample_rate;
	D_U32 channels;
}D_MovieInfo;

typedef enum
{
    D_MoviePlayRate_1X = 0,
    D_MoviePlayRate_2X,
    D_MoviePlayRate_4X,
    D_MoviePlayRate_8X,
    D_MoviePlayRate_16X,
    D_MoviePlayRate_32X,
}D_MoviePlayRate;

#define MOVIE_AUDIO_LANGUAGE_LENGTH 4

/**@brief ��Ƶ��Ϣ */
typedef struct
{
    D_Int audio_index;  /**< ���ڴ��ݸ�����ѡ�������ֵ */
    D_U32 sample_rate;
    D_U32 channels;
    D_Char language[MOVIE_AUDIO_LANGUAGE_LENGTH];
	D_U32 codec_id;
}D_MovieAudioInfo;

#define MEDIA_SUBTITLE_LINE_CNT (3)
#define MEDIA_SUBTITLE_LINE_SIZE (512)
/**@brief ��Ļ��Ϣ*/
typedef struct
{
	D_U32 sub_id;
	D_U32 line_cnt;
    D_Char sub_text[MEDIA_SUBTITLE_LINE_CNT][MEDIA_SUBTITLE_LINE_SIZE];
}D_SubtitleInfo;



/**@brief ͼƬ��ؽӿ�����*/

/** @brief Media ͼƬģ���ʼ��
*@retval ��Ч����ֵ:D_OK  ��Ч����ֵ:D_ERR_FAULT
*/
D_Result	d_media_picture_open (void) D_FUNCPOSTFIT;

/** @brief Media ͼƬģ���ͷ�
*@retval ����ֵ:D_OK
*/
D_Result	d_media_picture_close (void) D_FUNCPOSTFIT;

/** @brief Media ͼƬģ���趨ͼƬ��ʾ���ڵ�gui��
gifͼ����osd�ϴ����ؼ���ʾ�ģ�����Ҫָ����ʾ��
һ����d_media_picture_open�����һ��
*@retval ����ֵ:D_OK
*/
D_Result d_media_picture_set_layer (D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief ��ȡ ͼƬ��Ϣ
*@param[in] path �ļ���ȫ·����Ϣ
*@param[out] info ����ͼƬ��Ϣ�ṹ��
*@retval �ɹ�����D_OK; ʧ�ܷ���D_ERR_NOT_SUPPORT
*/
D_Result d_media_picture_get_info (D_Char* path, D_PictureInfo* info) D_FUNCPOSTFIT;

/** @brief ����һ��ͼƬ
*@param[in] path: �ļ�����·��
*@param[in] x,y,w,h:���Ŵ��ڴ�С
*@param[in] type:�ļ�����
*@param[in] rotate_flag:ͼƬ������ת�Ƕ�0--0; 1--90; 2--180; 3--270
*@param[in] codec_flag:ͼƬ���뷽ʽ0:�������� 1:Ԥ����ʽ����
*@retval �ɹ�����D_OK  ʧ�ܷ���D_ERR_FAULT
*/
D_Result d_media_picture_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_S8 type,D_U8 rotate_flag, D_U8 codec_flag) D_FUNCPOSTFIT;

/** @brief ֹͣ����MediaͼƬ
*@retval �ɹ�����D_OK ʧ�ܷ���D_ERR
*/
D_Result	d_media_picture_stop (void) D_FUNCPOSTFIT;

/** @brief ��ȡMediaͼƬ����״̬
*@retval ���ص�ǰͼƬ״̬D_PictureStatus ö��ֵ
*/
D_PictureStatus d_media_picture_get_status(void)D_FUNCPOSTFIT;

/** @brief ��תYUV����
*@x,y,w,h:���Ŵ��ڴ�С
*@rotate_flag:ͼƬ������ת�Ƕ�0--0; 1--90; 2--180; 3--270
*/
D_Result d_media_picture_sw_rotate(D_Char* srcbuf, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_U16 src_store_w,D_U16 src_store_h,D_U8 rotate_flag) D_FUNCPOSTFIT;

/**@brief ������ؽӿ�����*/
/**@brief ��ʼ������״̬��media����
*@retval ��Ч����ֵ:D_OK  ��Ч����ֵ:D_ERR
*/
D_Result d_media_music_open(void) D_FUNCPOSTFIT;

/**@brief ��ԭ���Ӳ������ú�����
*@retval ����ֵΪD_OK
*/
D_Result d_media_music_close(void) D_FUNCPOSTFIT;

/**@brief ֹͣ���ֲ���
*@ retval �ɹ�����D_OK ʧ�ܷ���D_ERR
*/
D_Result d_media_music_stop(void) D_FUNCPOSTFIT;

/**@brief ��������
*@param[in] path:Ҫ�������ֵľ���·��
*@param[in] type: �������� ��ʱδ�ã�û��ʵ������
*@param[in] vis ���ֲ���ʱ�����������Ļ�Ļ�����ʾ��Ļ�Ŀؼ�ָ��
*@retval �ɹ�����D_OK  ʧ�ܷ���D_ERR
*/
D_Result d_media_music_play(D_Char* path, D_U8 type, D_Visual *vis) D_FUNCPOSTFIT;

/**@breif ������ͣ����
*@retval �ɹ�����D_OK  ʧ�ܷ���D_ERR
*/
D_Result d_media_music_pause(void) D_FUNCPOSTFIT;

/**@breif ������������
*@retval �ɹ�����D_OK  ʧ�ܷ���D_ERR
*/
D_Result d_media_music_resume(void) D_FUNCPOSTFIT;

/**@breif ��ȡ��ǰ����״̬
*@retval ����ֵΪ�ṹ����D_MusicStatus��ö��ֵ
*/
D_U8 d_media_music_get_status(void) D_FUNCPOSTFIT;

/**@brief ��ȡ��ǰ���ֲ���ʱ��
*@retval ����ֵΪfloat���͵ĵ�ǰʱ��ֵ
*/
float d_media_music_get_curtime(void) D_FUNCPOSTFIT;

/**@brief ��ȡ������Ϣ������ʾ��UI��
*@param[in] path:Ҫ��ȡ���ֵľ���·��
*@param[out] info:����������Ϣ�ṹ��D_MusicInfo�е��������
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_music_get_info(D_Char* path, D_MusicInfo* info) D_FUNCPOSTFIT;

/**@brief ��ʼ�����ֲ��Ż�����ͼ����״������ÿ�еĿ���
*@param[in] block:ÿһ�е���״����
*@param[in] column��UI����Ҫ������״����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*ע��:�ú����ڻ�ÿ�������ļ�����ͼʱֻ�����һ�μ���
*/
D_Result d_media_music_init_sound_param(D_U16 *block, D_U16 *column) D_FUNCPOSTFIT;

/**@brief ��ȡ���ֲ�������ͼ��������UI��
*@param[out] size:�������ݸ���
*@param[out] histogram:����������Ϣͼ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_music_get_sound_param(D_U16 histogram[]) D_FUNCPOSTFIT;

/**@brief ��Ƶ��ؽӿ�����*/

/**@brief ����ʹ��ffmpeg�İ汾������d_media_movie_open֮ǰ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_set_version(D_MovieFFmepgVersion version) D_FUNCPOSTFIT;

/**@brief ��ʼ����Ƶ�ļ�����״̬��������Ƶ��������ͽ�������
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_open(void) D_FUNCPOSTFIT;

/**@brief ��ԭ���Ӳ������ú�ֹͣ��Ƶ��������
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_close(void) D_FUNCPOSTFIT;

/**@brief ֹͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_stop(void) D_FUNCPOSTFIT;

/**@brief ������Ƶ�ļ�
*@param[in] path:������Ƶ�ļ��ľ���·��
*@param[in] x,y,w,h:������Ƶ�Ĵ��ڴ�Сλ��
*@param[in] type: ������Ƶ���� (��Ӱ��ʱδ�� �� ts �ڼ�·��Ŀ)
*@param[in] vis:������Ƶ�ļ��������Ļ�ļ��Ļ������������ʾ��Ļ�Ŀؼ�ָ��
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_S8 type, D_Visual *vis) D_FUNCPOSTFIT;

/**@brief ��ͣ��Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_pause(void) D_FUNCPOSTFIT;

/**@brief �ָ���Ƶ����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_resume(void) D_FUNCPOSTFIT;

/**@brief �Բ�ͬ���ٶȲ�����Ƶ����
*@note ������ʱδʹ�ã���ʵ��
*/
D_Result d_media_movie_slow(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief �Բ�ͬ���ٶȲ�����Ƶ�첥
*@note ������ʱδʹ�ã���ʵ��
*/
D_Result d_media_movie_forward(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief �Բ�ͬ���ٶȻ��˲�����Ƶ
*@note ������ʱδʹ�ã���ʵ��
*/
D_Result d_media_movie_rewind(D_MoviePlayRate rate) D_FUNCPOSTFIT;

/**@brief��Ƶ��ת��һ��ָ����ʱ��㿪ʼ��������
*@param[in] pos:Ҫseek���ŵ�ʱ���
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_seek(D_U64 pos) D_FUNCPOSTFIT;

/**@brief ��ȡ����״̬
*@D_MovieStatus ������Ƶö�ٽṹ��D_MovieStatus�е�ֵ
*/
D_MovieStatus d_media_movie_get_status(void) D_FUNCPOSTFIT;

/**@brief ��ȡ��ǰ����ʱ��
*@retval ����ֵΪD_Double���͵ĵ�ǰ����ʱ��ֵ
*/
D_Double d_media_movie_get_curtime(void) D_FUNCPOSTFIT;

/**@brief ��ȡ��Ƶ�ļ���Ϣ������ʾ��UI��
*@param[in] path:Ҫ��ȡ����Ƶ�ļ�����·��
*@param[in] x,y,w,h:��Ҫ��ʾ��Ƶ�Ĵ��ڴ�С
*@param[in] type: ������Ƶ���� (��Ӱ��ʱδ�� �� ts �ڼ�·��Ŀ)
*@param[out] info:Ҫ���ص���Ƶ�ļ���Ϣ�ṹ������D_MovieInfo
*@retval �ɹ�����D_OK ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_get_info_ex (D_Char* path, D_MovieInfo* info, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_S8 type) D_FUNCPOSTFIT;
#define d_media_movie_get_info(path, info, x, y, w, h) d_media_movie_get_info_ex (path, info, x, y, w, h, 0)

/**@brief ��ƵԤ��������ʾ��Ƶ�еĵ�һ֡ͼƬ��Ϣ
*@param[in] path:ҪԤ������Ƶ�ļ�����·��
*@param[in] x,y,w,h:Ԥ����ʾ��Ƶ֡�Ĵ��ڴ�С
*@retval �ɹ�����D_OK ʧ�ܷ���D_ERR
*/
D_Result d_media_movie_preview(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h) D_FUNCPOSTFIT;

/**@brief �豸��Ƶ����λ��
*@param[in] x,y,w,h:��Ҫ��ʾ��Ƶ�Ĵ��ڴ�С
*@param[in] mode: 0 -- full screen; 1 -- window mode
*@retval �ɹ�����D_OK ʧ�ܷ���D_ERR
*@note ������ʱδ�õ�
*/
D_Result d_media_movie_set_video_location(D_U32 x, D_U32 y, D_U32 w, D_U32 h,D_U8 mode)D_FUNCPOSTFIT;

/**@brief �ر���ƵVO����ʾ
*@retval �ɹ�����D_OK 
*/
D_Result d_media_movie_hide_screen(void) D_FUNCPOSTFIT;

/**@brief ����ƵVO����ʾһ���ں���d_movie_set_param()������d_media_movie_hide_screen()�����
*@retval �ɹ�����D_OK 
*/
D_Result d_media_movie_show_screen(void) D_FUNCPOSTFIT;


/**@brief ������Ƶ���ŵ�״̬
*@param[in] status:Ҫ���õ���Ƶ״̬������Ϊö��ֵD_MovieStatus�еĳ�Ա����
*@retval �ɹ�����D_OK 
*/
D_Result d_media_movie_set_status(D_MovieStatus status) D_FUNCPOSTFIT;

/**@brief ��ȡ��ǰ�����ļ�����ʱ�䳤��
*@retval ����ֵΪ��ǰ������Ƶ�ļ�����ʱ��
*/
D_Double d_media_movie_get_play_file_total_time(void) D_FUNCPOSTFIT;

/** @brief ���ý���ļ������Ƶ��Ϣ
*@param[out] ��Ƶ��Ϣ�ṹ����
*@param[in]  ����Ľṹ���鳤��
@retval ʵ�ʻ����Ƶ��Ϣ������, ʧ�ܷ���С��0
*/
D_Result d_media_movie_get_audio_info(D_MovieAudioInfo *info, D_Size info_array_count) D_FUNCPOSTFIT;

/**@brief ѡ������
*@param[in] ����Ƶ��Ϣ���õ���Ƶ����ֵ
*@retval �ɹ�����D_OK, ����ʧ��
*/
D_Result d_media_movie_select_audio(D_Int audio_index) D_FUNCPOSTFIT;

/**@brief ��ȡ��Ƶ����״̬
*@retval �ɹ�����D_OK, ����ʧ��
*/
D_Result d_media_movie_get_video_smooth(void) D_FUNCPOSTFIT;

/** @brief ���ý��ts�ļ���Ķ�Ƶ����Ϣ
*@param[in/out] info D_PvrProgramInfo�ṹָ��
*@retval �ɹ�����D_OK, ����ʧ��
*/
D_Result d_media_movie_get_ts_progs_info(D_Ptr info) D_FUNCPOSTFIT;

/**@brief EBK��ؽӿ�����*/

/**@brief ��ʼ������״̬��ebk����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_ebk_open(void) D_FUNCPOSTFIT;

/**@brief����ebk��������
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_ebk_close(void) D_FUNCPOSTFIT;

/**@brief ebk�ļ�����
*@param[in] path:Ҫ���ŵ�ebk�ļ��ľ���·��
*@param[in] x,y,w,h:����ebkͼƬ�Ĵ���λ�ô�С
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_ebk_play(D_Char* path, D_U32 x, D_U32 y, D_U32 w, D_U32 h) D_FUNCPOSTFIT;

/**@brief ֹͣebk����
*@retval �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_media_ebk_stop(void) D_FUNCPOSTFIT;

/**@breif ��ȡebk��ǰ״̬
*@retval ����ֵΪ�ṹ��ö��ֵD_EbkStatus�еĳ�Ա����
*/
D_U8 d_media_ebk_get_status(void) D_FUNCPOSTFIT;

/**@breif ����ebk��������
*@param[in] key:��ҳ���ϴ������İ���ֵ���õ�ebk�����ļ���ȥ
*@retval �ɹ�����D_OK
*/
D_Result d_media_ebk_set_key(D_U8 key) D_FUNCPOSTFIT;

/**@brief ȡ����Ļ��Ϣ
* @param[in/out]  sub_text  ������Ļ�ı�
* @param[in]  cnt  sub_text�ռ����ֵ
*@retval ��Ч����ֵ:-1 ʧ��  0 ���ϴ���ͬ 1 �ɹ�
*/
int d_media_get_curr_subtitle(D_SubtitleInfo* sub) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif

