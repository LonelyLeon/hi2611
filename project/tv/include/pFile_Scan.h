/** @file
* @brief 文件浏览模块
* @author 王玉芹
* @date 王玉芹2013-11-21: 建立文件
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

#define D_PATH_LENGTH	(256)   /*文件路径 长度从128改为256 因为目前128的长度已经满足不了现在一些常见的文件路径，会经常出现一样异常问题*/
#define FILE_FORMAT_STRING_LENGTH		(4)	//MP3 BMP JPEG.....
#define FILE_FORMAT_MAX_NUM		(20)		/*暂定文件类型后缀名字个数最多为20个，后续可以增大*/
#define D_DEVICE_PARTITION_MAX	(24)

/*文件类型分类菜单上文件排序类型按这个方式显示，按值代表从大到小依次排序*/
typedef enum
{	
	D_FILE_SCAN_FMT_None = 0,
	D_FILE_SCAN_FMT_BIN,
	D_FILE_SCAN_FMT_Lrc_Title,/*音乐歌词*/
	D_FILE_SCAN_FMT_Srt_Title, /*视频字幕*/
	D_FILE_SCAN_FMT_Txt,
	D_FILE_SCAN_FMT_Pvr,
	D_FILE_SCAN_FMT_EBK,
	D_FILE_SCAN_FMT_Photo,	
	D_FILE_SCAN_FMT_Music,
	D_FILE_SCAN_FMT_TS,
	D_FILE_SCAN_FMT_Movie,
	D_FILE_SCAN_FMT_Dir,
	D_FILE_SCAN_FMT_UpDir,/*代表上一层目录即: '..'*/
	D_FILE_SCAN_FMT_Device,	/*这一类的文件代表获取的是磁盘各盘符*/
}D_FILESCAN_TYPE;

/*文件详细类型分类*/
typedef enum
{	
	D_FILE_TYPE_None = 0,
	D_FILE_TYPE_DEVICE, /*磁盘*/
	D_FILE_TYPE_UPDIR,   /*上级目录*/
	D_FILE_TYPE_DIR,    /*目录*/
	 /*文件类型*/
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

/* 文件查找时匹配方式*/
typedef enum
{	
	D_FILE_MATCH_MODE_ALL = 0,  /*所有*/
	D_FILE_MATCH_MODE_POSTFIX,	/*后缀名匹配*/
	D_FILE_MATCH_MODE_FILETYPE,	/*文件(夹)类型匹配*/
	D_FILE_MATCH_MODE_OTHERS,	/*其它*/
}D_FILEMATCH_MODE;

/* 文件浏览属性集*/
typedef struct
{
	union
	{
		char fullpath[D_PATH_LENGTH];/*文件的全路径*/
		char filename[D_PATH_LENGTH];/*文件名称*/
	}path;
	D_U8	type;/*0:目录 1:文件*/
	D_U8	class_type;	/*文件所属种类(音乐/电影/目录/相片...)*/
	D_U8	file_type;	/*文件类型(gif/bmp/jpg/mkv/rmvb/ts...)*/
       D_U8       dev_type;    /* 如果是设备，用于标识u盘还是sd卡*/
}D_FSAttr;

/*文件浏览结构体属性*/
typedef struct 
{
	D_FSAttr *ids;
	D_U16	max;/*记录集的最大个数*/
	D_U16	cnt;
}D_FileScan;

#ifdef D_MUTIMEDIA_NOCATALOG
typedef struct _TV_FILE_RSET_INFO    TV_FILE_RSET_INFO;

/**@brief 多媒体文件属性结构体*/
struct _TV_FILE_RSET_INFO
{
    D_U8 used;     /**使用有效标记，如果记录集有数据，则置为1 */
    D_U8 volumes;  /**当前记录集属于USB或者SD的标记*/
    D_Char *path; /**多媒体文件路径*/
    D_U8    class_type; /**文件所属种类(音乐/电影/目录/相片...)*/
    D_U8    file_type;  /**文件类型(gif/bmp/jpg/mkv/rmvb/ts...)*/
    TV_FILE_RSET_INFO * next;
    D_U16 local_num;
};
#endif

typedef struct
{
	D_FileScan fs;
    D_Ptr subfix;   /*匹配项数组*/
    D_U8 num;       /*数组元素数量*/
    D_U8 mode;       /*匹配方式*/
}D_ProcFSData;

#ifdef D_MUTIMEDIA_NOCATALOG
typedef struct
{
    D_Ptr subfix;   /*匹配项数组*/
    D_U8 num;       /*数组元素数量*/
    D_U8 mode;       /*匹配方式*/
    D_U32 *stop_ctrl;     /*查询过程结束控制*/
    D_U8   volumes; /**盘符*/
} TV_MEDIA_D_ProcFSData;
#endif

/*判断文件(夹)类型宏定义*/
#define Judge_Up_Folder(_fsattr) ((_fsattr)->type == 0 && (_fsattr)->class_type == D_FILE_SCAN_FMT_UpDir)
#define Judge_Dir_Folder(_fsattr) ((_fsattr)->type == 0 && ((_fsattr)->class_type == D_FILE_SCAN_FMT_Device || (_fsattr)->class_type == D_FILE_SCAN_FMT_Dir))
#define Judge_Movie_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Movie)
#define Judge_TS_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_TS)
#define Judge_Music_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Music)
#define Judge_Photo_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Photo)
#define Judge_PVR_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Pvr)
#define Judge_EBK_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_EBK)
#define Judge_TXT_File(_fsattr) ((_fsattr)->type == 1 && (_fsattr)->class_type == D_FILE_SCAN_FMT_Txt)

/**@brief 字符串拷贝直到字符c出现
*@param[out] dst : 目的字符串
*@param[in] src: 源字符串
*@param[in] c: 需要查找的字符
*@param[in] count: 总的字符个数
*/
void * my_memccpy(void *dst,const void *src,int c,int count)D_FUNCPOSTFIT;

/** @brief 不区分大小写来比较字符串
*/
int strcasecmp(const char *s1, const char *s2)D_FUNCPOSTFIT;


/**@brief查找当前目录下的所有文件及文件夹
**@brief 当array和num不传入参数时是查找当前目录下的所有文件及文件夹,有参数时说明只需要当前目录下可识别的文件
*@param[in] path :要查找的目录路径
*@param[out] fs_set:返回查找到的所有文件记录集
*@param[in] postfix:字符串指针字符集，查找要匹配的文件后缀名
*@param[in] numb:字符串字符集的个数
*@return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_get_current_dir(D_Char *path, D_FileScan *fs_set,  D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE match_mode)D_FUNCPOSTFIT;

/**@brief从当前目录开始遍历查找subfix数组所列的所有文件
*@param[in] path :要查找的目录路径
*@param[out] fs_set:返回查找到的所有文件记录集
*@param[in] postfix:字符串指针字符集，查找要匹配的文件后缀名
*@param[in] numb:字符串字符集的个数
*return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_get_files_by_type(D_Char *path, D_FileScan *fs_set,  D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE match_mode)D_FUNCPOSTFIT;

/**@brief 根据分区索引号与个数为多媒体列表数据填充内容
*@param[out] fs_set:磁盘记录集数据结构体
*@param[in] vol_index:分区索引号数组
*@param[in] numb:磁盘分区个数
*@retval 成功返回D_OK, 失败返回D_ERR;
*/
D_Result p_file_scan_get_all_partitons(D_FileScan *fs_set, D_U8 vol_index[], D_U8 numb)D_FUNCPOSTFIT;

/**@brief 根据文件(夹)名取得类型(gif/jpg/flv/rmvb/mkv...)
*param: attribute 属性(0 目录，1 文件)
*param: path 文件(夹)名称
*ret	 成功返回文件类型
*/
D_FILE_TYPE p_file_scan_parse_file_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT;

/**@brief 根据文件类型(gif/jpg/rmvb/flv...)取得分类信息(目录/电影/音乐...)*/
D_FILESCAN_TYPE p_file_scan_get_class_type_by_type(D_FILE_TYPE filetype)D_FUNCPOSTFIT;

/**@brief 根据文件(夹)名取得分类信息(目录/电影/音乐...)
*param: attribute 属性(0 目录，1 文件)
*param: path 文件(夹)名称
*ret	 成功返回文件类型D_FILESCAN_TYPE_***, 失败返回D_FILE_SCAN_FMT_None;
*/
D_FILESCAN_TYPE p_file_scan_get_file_class_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT;


/**@brief根据文件类型进行排序
*@param[in/out] fs_set:排好序的磁盘记录集数据结构体
*@param[in] func:排序函数
*return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_sort_by_type(D_FileScan *fs_set, D_CmpFunc func)D_FUNCPOSTFIT;


/**@brief 查找给定路径文件在当前文件记录集中的序号
*@param[in] path :要查找的目录路径
*@param[in] fs_set:返回查找到的所有文件记录集
*@return 成功返回序号D_ERR:返回失败
*/
D_Result p_file_scan_get_index(D_Char *path, D_FileScan *fs_set)D_FUNCPOSTFIT;

#ifdef __cplusplus
}
#endif

#endif
