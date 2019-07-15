/** @file
* @brief tv 多媒体文件全路径扫描存储
* @author
* @date 2018-01-16: 建立文件
*/
#include "pFile_scan.h"
#include "dDebug.h"
#include "dMMan.h"
#include "dFileSystem.h"

#define TV_MEDIA_FILE_NAME_MEM_SIZE (2*512*1024)        /** 内存管理器空间大小*/
#define TV_MEDIA_ALL_FILE_MAX 4000                /**文件最大个数*/
#define TV_MEDIA_FILE_TYPE_NUM  4                   /** 多媒体类型个数*/

/**多媒体文件类型数组变量*/
static D_FILE_TYPE tv_media_file_type[] =
{
    D_FILE_TYPE_JPG,
    D_FILE_TYPE_BMP,
 //D_FILE_TYPE_GIF,
 //D_FILE_TYPE_PNG,
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
 //D_FILE_TYPE_RMVB,
 //D_FILE_TYPE_TXT,
 //D_FILE_TYPE_LRC,
 //D_FILE_TYPE_SRT,
 //D_FILE_TYPE_EBK,
    D_FILE_TYPE_TS,
 //D_FILE_TYPE_HTS,
};


static TV_FILE_RSET_INFO tv_file_rset_info[TV_MEDIA_ALL_FILE_MAX] = {0};

/**内存管理器handle变量*/
static D_HMMan tv_media_scan_mman = D_INVALID_HANDLE;

/**分配内存管理器的内存handle*/
static D_Ptr tv_media_scan_mem = NULL;

/** @brief 空位置链表*/
static TV_FILE_RSET_INFO *  free_area_ptr;


/**@brief 内存管理器全部空间清除*/
static void tv_media_mman_clear(void)D_FUNCPOSTFIT
{
    if(tv_media_scan_mman != D_INVALID_HANDLE)
    {
        d_mman_clear(tv_media_scan_mman);
    }
}

/**@brief 销毁内存管理器*/
static void tv_media_mman_destroy(void)D_FUNCPOSTFIT
{
    if(tv_media_scan_mman != D_INVALID_HANDLE)
    {
        d_mman_destroy(tv_media_scan_mman);
        tv_media_scan_mman = D_INVALID_HANDLE;
    }
    if(tv_media_scan_mem != NULL)
    {
        d_mem_free(tv_media_scan_mem);
        tv_media_scan_mem = NULL;
    }
}

/**@brief 创建内存管理器*/
static D_Result tv_media_mman_creat(void)D_FUNCPOSTFIT
{
    if(tv_media_scan_mman != D_INVALID_HANDLE && tv_media_scan_mem != NULL)
    {
        return D_OK;
    }
    tv_media_scan_mem = d_mem_alloc(0, TV_MEDIA_FILE_NAME_MEM_SIZE);
    if(tv_media_scan_mem == NULL)
    {
        return D_ERR;
    }
    tv_media_scan_mman = d_mman_create(tv_media_scan_mem, TV_MEDIA_FILE_NAME_MEM_SIZE , D_MMAN_HEAP);
    if(D_INVALID_HANDLE == tv_media_scan_mman)
    {
        d_mem_free(tv_media_scan_mem);
        return D_ERR;
    }

    tv_media_mman_clear();
    media_file_scan_open_file();
    return D_OK;
}

/**@brief 记录空位置链表增加释放文件的位置
*@param[in]
*@return
*/
static D_Result media_file_scan_free_file(TV_FILE_RSET_INFO *new_free_area)
{
    new_free_area->next = free_area_ptr;
    free_area_ptr = new_free_area;
    return D_OK;
}

/**@brief
*@param[in]
*@return
*/
static D_S16 media_file_scan_malloc_file(void)
{
    D_S16 cur_area;
    if(free_area_ptr->next == NULL)
    {
        return -1;
    }
    cur_area = free_area_ptr->local_num;
    free_area_ptr = free_area_ptr->next;
    return cur_area;
}

/**@brief
*@param[in]
*@return
*/
static D_Result media_file_scan_open_file(void)
{
    D_U16 i;
    for (i = 0; i < (TV_MEDIA_ALL_FILE_MAX - 1) ; i++)
    {
        tv_file_rset_info[i].local_num = i;
        tv_file_rset_info[i].next = &tv_file_rset_info[i + 1];
    }

    tv_file_rset_info[i].next = NULL;
    free_area_ptr = tv_file_rset_info;
    return D_OK;
}


/**@brief 创建内存管理器*/
D_Result p_tv_media_mman_open(void)D_FUNCPOSTFIT
{
    return tv_media_mman_creat();
}
/**@brief 销毁内存管理器*/
void p_tv_media_mman_close(void)D_FUNCPOSTFIT
{
    tv_media_mman_destroy();
}

D_Result p_tv_delete_volumes_data( D_U32 volumes, D_Bool plug)D_FUNCPOSTFIT
{
    D_U16 i;
    if(!plug)
    {
        for (i = 0; i < TV_MEDIA_ALL_FILE_MAX ; i++)
        {
            if((tv_file_rset_info[i].used == 1) && ( tv_file_rset_info[i].volumes == volumes))
            {
                media_file_scan_free_file(&tv_file_rset_info[i]);
                d_mman_free(tv_media_scan_mman, tv_file_rset_info[i].path);
                tv_file_rset_info[i].used = 0;
                tv_file_rset_info[i].file_type = 0;
                tv_file_rset_info[i].volumes = 0;
            }
        }
        return D_OK;
    }
    return D_ERR;
}

/**@brief 检查是否已满
*@return 0 表示没有满，1表示已经满了
*/
static D_U8 tv_MediaCheckAFsFull(void)D_FUNCPOSTFIT
{
    if(free_area_ptr->next != NULL)
    {
        return 0;// is not full
    }
    return 1; // full
}


/**@brief 扫描结果处理函数
*@param[in] fd 扫描到的文件或者目录属性
*@param[in] arg 扫描结果存储属性信息
*@param[in] find_para 需要匹配的文件属性
*@return 返回值没有意义，不管返回何值还会一直继续扫描下去
*/
static D_Bool tv_MediaDeepReadDirProc(D_FileFindData *fd, D_Ptr arg, D_Ptr find_para)D_FUNCPOSTFIT
{
    TV_MEDIA_D_ProcFSData  *fsd = (TV_MEDIA_D_ProcFSData*)arg;
    D_Bool  match_flag = D_FALSE;
    D_FILE_TYPE  filetype;

    /**扫描终端标记，为1表示外部需要终端扫描，则退出扫描*/
    if(fsd->stop_ctrl && (*(fsd->stop_ctrl)))
    {
        return D_OK;
    }

    /**扫描到的是一个目录，则继续该目录*/
    if((fd->attribute == 0) && (strcmp(fd->filename, ".")) && (strcmp(fd->filename, "..")))
    {
        if(d_fsm_readdir_ext(fd->full_path, tv_MediaDeepReadDirProc, (D_Ptr)fsd, find_para) == D_ERR)
        {
             
        }
        return D_OK;
    }
    else if(fd->attribute == 1)
    {
        if(fsd->mode == D_FILE_MATCH_MODE_FILETYPE)
        {
            filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);
            if(find_file_type(filetype, (D_FILE_TYPE *)fsd->subfix, fsd->num) == D_TRUE)
            {
                match_flag = D_TRUE;
            }
        }
        
        /**保存扫描到的文件到记录集中*/
        if(match_flag == D_TRUE && !tv_MediaCheckAFsFull())
        {
            D_U8 file_name_len = 0;
            D_U16 cur_area;

            cur_area = media_file_scan_malloc_file();

            file_name_len = strlen(fd->full_path);
            if(file_name_len >= D_PATH_LENGTH)
            {
                file_name_len = D_PATH_LENGTH - 1;
            }

            tv_file_rset_info[cur_area].path = d_mman_alloc(tv_media_scan_mman, file_name_len + 1); //根据文件路径名长度分配大小
            if(tv_file_rset_info[cur_area].path  == NULL)
            {
                return D_ERR;
            }
            /**将文件属性保存到记录集中，并更新相关参数*/
            memset(tv_file_rset_info[cur_area].path , 0, file_name_len + 1);
            strncpy(tv_file_rset_info[cur_area].path , fd->full_path, file_name_len);

            tv_file_rset_info[cur_area].file_type = filetype;
            tv_file_rset_info[cur_area].class_type = p_file_scan_get_class_type_by_type(filetype);
            tv_file_rset_info[cur_area].used = 1;
            tv_file_rset_info[cur_area].volumes = fsd->volumes;
        }
    }
    return D_ERR;
}

/**@brief 开始扫描的接口函数
*@param[in] path 要扫描的路径
*@param[in] stop_ctrl 停止扫描参数
*/
D_Result p_tv_file_scan_get_files_by_type_ex(D_Char *path, D_U32 volumes, D_U32 *stop_ctrl)D_FUNCPOSTFIT
{
    TV_MEDIA_D_ProcFSData fsd = {0};
    D_FileFindPara find_para;
    if (!path )
    {
        return D_ERR;
    }
    fsd.volumes = volumes;
    fsd.mode = D_FILE_MATCH_MODE_FILETYPE;
    fsd.num = sizeof(tv_media_file_type) / sizeof(tv_media_file_type[0]);
    fsd.subfix = (D_Ptr)tv_media_file_type;
    fsd.stop_ctrl = stop_ctrl;
    find_para.flag = 0;
    find_para.step = 10;    // 需要匹配的文件类型个数，注意该值必须大于fsd.num
    file_fmt_to_unicode(fsd.subfix, fsd.num, find_para.filetype, &find_para.num); // 文件类型格式转换到unicode
    d_fsm_readdir_ext(path, tv_MediaDeepReadDirProc, (D_Ptr)&fsd, (D_Ptr)&find_para); //深度扫描接口
    return D_OK;
}


/**@brief 通过盘符和指定文件类型取得相应u盘里该类型所有文件
*@param[in] volumes 盘符
*@param[in] file_rset 返回所有文件集
*@param[in] area_rset 文件在记录集的位置数组
*@param[in] fileclass 文件类型
*@return[in] 返回该文件总个数
*/
D_U16 p_tv_file_scan_get_typefile_by_volumes(D_U32 volumes, TV_FILE_RSET_INFO **file_rset, D_U16 *area_rset, D_FILESCAN_TYPE fileclass)
{
    D_U16 i;
    D_U16 cnt = 0;
    D_FILESCAN_TYPE fileclass2 = 0;

    if(D_FILE_SCAN_FMT_Movie == fileclass)
    {
        fileclass2 = D_FILE_SCAN_FMT_TS;
    }

    *file_rset = &tv_file_rset_info[0];
    for(i = 0; i < TV_MEDIA_ALL_FILE_MAX ; i++)
    {
        if((tv_file_rset_info[i].volumes == volumes) && ((tv_file_rset_info[i].class_type == fileclass) ||(tv_file_rset_info[i].class_type == fileclass2)) && (tv_file_rset_info[i].used == 1) )
        {
            area_rset[cnt] = i;
            cnt++;
        }
    }
    return cnt;
}



