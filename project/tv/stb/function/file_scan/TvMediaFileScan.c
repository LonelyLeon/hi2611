/** @file
* @brief tv ��ý���ļ�ȫ·��ɨ��洢
* @author
* @date 2018-01-16: �����ļ�
*/
#include "pFile_scan.h"
#include "dDebug.h"
#include "dMMan.h"
#include "dFileSystem.h"

#define TV_MEDIA_FILE_NAME_MEM_SIZE (2*512*1024)        /** �ڴ�������ռ��С*/
#define TV_MEDIA_ALL_FILE_MAX 4000                /**�ļ�������*/
#define TV_MEDIA_FILE_TYPE_NUM  4                   /** ��ý�����͸���*/

/**��ý���ļ������������*/
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

/**�ڴ������handle����*/
static D_HMMan tv_media_scan_mman = D_INVALID_HANDLE;

/**�����ڴ���������ڴ�handle*/
static D_Ptr tv_media_scan_mem = NULL;

/** @brief ��λ������*/
static TV_FILE_RSET_INFO *  free_area_ptr;


/**@brief �ڴ������ȫ���ռ����*/
static void tv_media_mman_clear(void)D_FUNCPOSTFIT
{
    if(tv_media_scan_mman != D_INVALID_HANDLE)
    {
        d_mman_clear(tv_media_scan_mman);
    }
}

/**@brief �����ڴ������*/
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

/**@brief �����ڴ������*/
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

/**@brief ��¼��λ�����������ͷ��ļ���λ��
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


/**@brief �����ڴ������*/
D_Result p_tv_media_mman_open(void)D_FUNCPOSTFIT
{
    return tv_media_mman_creat();
}
/**@brief �����ڴ������*/
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

/**@brief ����Ƿ�����
*@return 0 ��ʾû������1��ʾ�Ѿ�����
*/
static D_U8 tv_MediaCheckAFsFull(void)D_FUNCPOSTFIT
{
    if(free_area_ptr->next != NULL)
    {
        return 0;// is not full
    }
    return 1; // full
}


/**@brief ɨ����������
*@param[in] fd ɨ�赽���ļ�����Ŀ¼����
*@param[in] arg ɨ�����洢������Ϣ
*@param[in] find_para ��Ҫƥ����ļ�����
*@return ����ֵû�����壬���ܷ��غ�ֵ����һֱ����ɨ����ȥ
*/
static D_Bool tv_MediaDeepReadDirProc(D_FileFindData *fd, D_Ptr arg, D_Ptr find_para)D_FUNCPOSTFIT
{
    TV_MEDIA_D_ProcFSData  *fsd = (TV_MEDIA_D_ProcFSData*)arg;
    D_Bool  match_flag = D_FALSE;
    D_FILE_TYPE  filetype;

    /**ɨ���ն˱�ǣ�Ϊ1��ʾ�ⲿ��Ҫ�ն�ɨ�裬���˳�ɨ��*/
    if(fsd->stop_ctrl && (*(fsd->stop_ctrl)))
    {
        return D_OK;
    }

    /**ɨ�赽����һ��Ŀ¼���������Ŀ¼*/
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
        
        /**����ɨ�赽���ļ�����¼����*/
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

            tv_file_rset_info[cur_area].path = d_mman_alloc(tv_media_scan_mman, file_name_len + 1); //�����ļ�·�������ȷ����С
            if(tv_file_rset_info[cur_area].path  == NULL)
            {
                return D_ERR;
            }
            /**���ļ����Ա��浽��¼���У���������ز���*/
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

/**@brief ��ʼɨ��Ľӿں���
*@param[in] path Ҫɨ���·��
*@param[in] stop_ctrl ֹͣɨ�����
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
    find_para.step = 10;    // ��Ҫƥ����ļ����͸�����ע���ֵ�������fsd.num
    file_fmt_to_unicode(fsd.subfix, fsd.num, find_para.filetype, &find_para.num); // �ļ����͸�ʽת����unicode
    d_fsm_readdir_ext(path, tv_MediaDeepReadDirProc, (D_Ptr)&fsd, (D_Ptr)&find_para); //���ɨ��ӿ�
    return D_OK;
}


/**@brief ͨ���̷���ָ���ļ�����ȡ����Ӧu��������������ļ�
*@param[in] volumes �̷�
*@param[in] file_rset ���������ļ���
*@param[in] area_rset �ļ��ڼ�¼����λ������
*@param[in] fileclass �ļ�����
*@return[in] ���ظ��ļ��ܸ���
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



