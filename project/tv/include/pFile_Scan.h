/** @file
* @brief �ļ����ģ��
* @author ������
* @date ������2013-11-21: �����ļ�
*/
#ifndef _P_S2_FILE_SCAN_H_
#define _P_S2_FILE_SCAN_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "dTypes.h"
#include "dDisk.h"
#include "dFileSystem.h"

#define D_PATH_LENGTH	(256)   /*�ļ�·�� ���ȴ�128��Ϊ256 ��ΪĿǰ128�ĳ����Ѿ����㲻������һЩ�������ļ�·�����ᾭ������һ���쳣����*/
#define FILE_FORMAT_STRING_LENGTH		(4)	//MP3 BMP JPEG.....
#define FILE_FORMAT_MAX_NUM		(20)		/*�ݶ��ļ����ͺ�׺���ָ������Ϊ20����������������*/
#define D_DEVICE_PARTITION_MAX	(24)

/*�ļ����ͷ���˵����ļ��������Ͱ������ʽ��ʾ����ֵ����Ӵ�С��������*/
typedef enum
{	
	D_FILE_SCAN_FMT_None = 0,
	D_FILE_SCAN_FMT_BIN,
	D_FILE_SCAN_FMT_Lrc_Title,/*���ָ��*/
	D_FILE_SCAN_FMT_Srt_Title, /*��Ƶ��Ļ*/
	D_FILE_SCAN_FMT_Txt,
	D_FILE_SCAN_FMT_Pvr,
	D_FILE_SCAN_FMT_EBK,
	D_FILE_SCAN_FMT_Photo,	
	D_FILE_SCAN_FMT_Music,
	D_FILE_SCAN_FMT_TS,
	D_FILE_SCAN_FMT_Movie,
	D_FILE_SCAN_FMT_Dir,
	D_FILE_SCAN_FMT_UpDir,/*������һ��Ŀ¼��: '..'*/
	D_FILE_SCAN_FMT_Device,	/*��һ����ļ������ȡ���Ǵ��̸��̷�*/
}D_FILESCAN_TYPE;

/*�ļ���ϸ���ͷ���*/
typedef enum
{	
	D_FILE_TYPE_None = 0,
	D_FILE_TYPE_DEVICE, /*����*/
	D_FILE_TYPE_UPDIR,   /*�ϼ�Ŀ¼*/
	D_FILE_TYPE_DIR,    /*Ŀ¼*/
	 /*�ļ�����*/
	D_FILE_TYPE_JPG,
	D_FILE_TYPE_BMP,
	D_FILE_TYPE_GIF,
	D_FILE_TYPE_PNG,	
	D_FILE_TYPE_MP3,
	D_FILE_TYPE_WMA,
	D_FILE_TYPE_WAV,
	D_FILE_TYPE_AAC,
	D_FILE_TYPE_AMR,
	D_FILE_TYPE_MP4,	
	D_FILE_TYPE_AVI,	
	D_FILE_TYPE_MOV,
	D_FILE_TYPE_MPG,
	D_FILE_TYPE_3GP,	
	D_FILE_TYPE_DAT,	
	D_FILE_TYPE_VOB,	
	D_FILE_TYPE_FLV,	
	D_FILE_TYPE_MKV,	
	D_FILE_TYPE_RMVB,	
	D_FILE_TYPE_TXT,	
	D_FILE_TYPE_LRC,	
	D_FILE_TYPE_SRT,	
	D_FILE_TYPE_EBK,	
	D_FILE_TYPE_TS,	
	D_FILE_TYPE_HTS,	
	D_FILE_TYPE_BIN,
	D_FILE_TYPE_AC3,
}D_FILE_TYPE;

/* �ļ�����ʱƥ�䷽ʽ*/
typedef enum
{	
	D_FILE_MATCH_MODE_ALL = 0,  /*����*/
	D_FILE_MATCH_MODE_POSTFIX,	/*��׺��ƥ��*/
	D_FILE_MATCH_MODE_FILETYPE,	/*�ļ�(��)����ƥ��*/
	D_FILE_MATCH_MODE_OTHERS,	/*����*/
}D_FILEMATCH_MODE;

/* �ļ�������Լ�*/
typedef struct
{
	union
	{
		char fullpath[D_PATH_LENGTH];/*�ļ���ȫ·��*/
		char filename[D_PATH_LENGTH];/*�ļ�����*/
	}path;
	D_U8	type;/*0:Ŀ¼ 1:�ļ�*/
	D_U8	class_type;	/*�ļ���������(����/��Ӱ/Ŀ¼/��Ƭ...)*/
	D_U8	file_type;	/*�ļ�����(gif/bmp/jpg/mkv/rmvb/ts...)*/
       D_U8       dev_type;    /* ������豸�����ڱ�ʶu�̻���sd��*/
}D_FSAttr;

/*�ļ�����ṹ������*/
typedef struct 
{
	D_FSAttr *ids;
	D_U16	max;/*��¼����������*/
	D_U16	cnt;
}D_FileScan;

#ifdef D_MUTIMEDIA_NOCATALOG
typedef struct _TV_FILE_RSET_INFO    TV_FILE_RSET_INFO;

/**@brief ��ý���ļ����Խṹ��*/
struct _TV_FILE_RSET_INFO
{
    D_U8 used;     /**ʹ����Ч��ǣ������¼�������ݣ�����Ϊ1 */
    D_U8 volumes;  /**��ǰ��¼������USB����SD�ı��*/
    D_Char *path; /**��ý���ļ�·��*/
    D_U8    class_type; /**�ļ���������(����/��Ӱ/Ŀ¼/��Ƭ...)*/
    D_U8    file_type;  /**�ļ�����(gif/bmp/jpg/mkv/rmvb/ts...)*/
    TV_FILE_RSET_INFO * next;
    D_U16 local_num;
};
#endif

typedef struct
{
	D_FileScan fs;
    D_Ptr subfix;   /*ƥ��������*/
    D_U8 num;       /*����Ԫ������*/
    D_U8 mode;       /*ƥ�䷽ʽ*/
}D_ProcFSData;

#ifdef D_MUTIMEDIA_NOCATALOG
typedef struct
{
    D_Ptr subfix;   /*ƥ��������*/
    D_U8 num;       /*����Ԫ������*/
    D_U8 mode;       /*ƥ�䷽ʽ*/
    D_U32 *stop_ctrl;     /*��ѯ���̽�������*/
    D_U8   volumes; /**�̷�*/
} TV_MEDIA_D_ProcFSData;
#endif

/*�ж��ļ�(��)���ͺ궨��*/
#define Judge_Up_Folder(_fsattr) ((_fsattr)->type == 0 && (_fsattr)->class_type == D_FILE_SCAN_FMT_UpDir)
#define Judge_Dir_Folder(_fsattr) ((_fsattr)->type == 0 && ((_fsattr)->class_type == D_FILE_SCAN_FMT_Device || (_fsattr)->class_type == D_FILE_SCAN_FMT_Dir))
#define Judge_Movie_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Movie)
#define Judge_TS_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_TS)
#define Judge_Music_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Music)
#define Judge_Photo_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Photo)
#define Judge_PVR_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Pvr)
#define Judge_EBK_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_EBK)
#define Judge_TXT_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Txt)

/**@brief �ַ�������ֱ���ַ�c����
*@param[out] dst : Ŀ���ַ���
*@param[in] src: Դ�ַ���
*@param[in] c: ��Ҫ���ҵ��ַ�
*@param[in] count: �ܵ��ַ�����
*/
void * my_memccpy(void *dst,const void *src,int c,int count)D_FUNCPOSTFIT;

/** @brief �����ִ�Сд���Ƚ��ַ���
*/
int strcasecmp(const char *s1, const char *s2)D_FUNCPOSTFIT;


/**@brief���ҵ�ǰĿ¼�µ������ļ����ļ���
**@brief ��array��num���������ʱ�ǲ��ҵ�ǰĿ¼�µ������ļ����ļ���,�в���ʱ˵��ֻ��Ҫ��ǰĿ¼�¿�ʶ����ļ�
*@param[in] path :Ҫ���ҵ�Ŀ¼·��
*@param[out] fs_set:���ز��ҵ��������ļ���¼��
*@param[in] postfix:�ַ���ָ���ַ���������Ҫƥ����ļ���׺��
*@param[in] numb:�ַ����ַ����ĸ���
*@return D_OK:���سɹ���D_ERR:����ʧ��
*/
D_Result p_file_scan_get_current_dir(D_Char *path, D_FileScan *fs_set,  D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE match_mode)D_FUNCPOSTFIT;

/**@brief�ӵ�ǰĿ¼��ʼ��������subfix�������е������ļ�
*@param[in] path :Ҫ���ҵ�Ŀ¼·��
*@param[out] fs_set:���ز��ҵ��������ļ���¼��
*@param[in] postfix:�ַ���ָ���ַ���������Ҫƥ����ļ���׺��
*@param[in] numb:�ַ����ַ����ĸ���
*return D_OK:���سɹ���D_ERR:����ʧ��
*/
D_Result p_file_scan_get_files_by_type(D_Char *path, D_FileScan *fs_set,  D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE match_mode)D_FUNCPOSTFIT;

/**@brief ���ݷ��������������Ϊ��ý���б������������
*@param[out] fs_set:���̼�¼�����ݽṹ��
*@param[in] vol_index:��������������
*@param[in] numb:���̷�������
*@retval �ɹ�����D_OK, ʧ�ܷ���D_ERR;
*/
D_Result p_file_scan_get_all_partitons(D_FileScan *fs_set, D_U8 vol_index[], D_U8 numb)D_FUNCPOSTFIT;

/**@brief �����ļ�(��)��ȡ������(gif/jpg/flv/rmvb/mkv...)
*param: attribute ����(0 Ŀ¼��1 �ļ�)
*param: path �ļ�(��)����
*ret	 �ɹ������ļ�����
*/
D_FILE_TYPE p_file_scan_parse_file_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT;

/**@brief �����ļ�����(gif/jpg/rmvb/flv...)ȡ�÷�����Ϣ(Ŀ¼/��Ӱ/����...)*/
D_FILESCAN_TYPE p_file_scan_get_class_type_by_type(D_FILE_TYPE filetype)D_FUNCPOSTFIT;

/**@brief �����ļ�(��)��ȡ�÷�����Ϣ(Ŀ¼/��Ӱ/����...)
*param: attribute ����(0 Ŀ¼��1 �ļ�)
*param: path �ļ�(��)����
*ret	 �ɹ������ļ�����D_FILESCAN_TYPE_***, ʧ�ܷ���D_FILE_SCAN_FMT_None;
*/
D_FILESCAN_TYPE p_file_scan_get_file_class_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT;


/**@brief�����ļ����ͽ�������
*@param[in/out] fs_set:�ź���Ĵ��̼�¼�����ݽṹ��
*@param[in] func:������
*return D_OK:���سɹ���D_ERR:����ʧ��
*/
D_Result p_file_scan_sort_by_type(D_FileScan *fs_set, D_CmpFunc func)D_FUNCPOSTFIT;


/**@brief ���Ҹ���·���ļ��ڵ�ǰ�ļ���¼���е����
*@param[in] path :Ҫ���ҵ�Ŀ¼·��
*@param[in] fs_set:���ز��ҵ��������ļ���¼��
*@return �ɹ��������D_ERR:����ʧ��
*/
D_Result p_file_scan_get_index(D_Char *path, D_FileScan *fs_set)D_FUNCPOSTFIT;

#ifdef __cplusplus
}
#endif

#endif
