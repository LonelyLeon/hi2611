/** @file
* @brief 文件浏览模块
* @author 王玉芹
* @date 王玉芹2013-11-21: 建立文件
* @date wangyq 2014-05-05 整理代码注释说明
* @date 覃宜 2014-08-06 整理并修改代码
*/
#include <stdlib.h>
#include <string.h>
#include "dDebug.h"
#include "pMem.h"
#include "pFile_Scan.h"
#include "dFileSystem.h"
#include "dCharset.h"

static D_Char *device_content[] =
{
	"C:", "D:", "E:", "F:",
	"G:", "H:", "I:", "J:",
	"K:", "L:", "M:", "N:",
	"O:", "P:", "Q:", "R:",
	"S:", "T:", "U:", "V:",
	"W:", "X:", "Y:", "Z:",
};

/**@brief 字符串拷贝直到字符c出现
*@param[out] dst : 目的字符串
*@param[in] src: 源字符串
*@param[in] c: 需要查找的字符
*@param[in] count: 总的字符个数
*/
void * my_memccpy(void *dst,const void *src,int c,int count)D_FUNCPOSTFIT
{
   while (count)
   {
      *(char *)dst = *(char *)src;
      dst = (char *)dst + 1;
      if(*(char *)src == (char) c)
        break;
      src = (char *)src + 1;
      count--;
   }
   return(count ? dst : NULL);
}

/** @brief 不区分大小写来比较字符串
*/
int strcasecmp(const char *s1, const char *s2)D_FUNCPOSTFIT
{
    int ii;
    int res = -1;

    if (!s1) {
        if (!s2)  return 0;
        return (-1);
    }
    if (!s2)
        return (1);

    for (ii = 0; *s1 && *s2; ii++, s1++, s2++)
    {
        res = (int) (D_TO_LOWER(*s1) - D_TO_LOWER(*s2));
        if (res != 0) break;
    }

    if (! *s1) {
        if (! *s2)  return 0;
        return (-1);
    }
    if (! *s2)
        return (1);

    return (res);
}

/** @brief 查找指定文件名的后缀是否在给定的后缀名数组中
* @param filename		文件名
* @param postfix 		后缀名数组
* @param num	后缀名数组的个数
* @retval D_TRUE:查找成功，D_FALSE:查找失败没找到
*/
D_Bool find_file_postfix(D_Char *filename, D_Char **postfix,D_U8 num)
{
	D_U8 i = 0;
	char * file_fmt_prv = NULL;

    if(!postfix)
        return D_FALSE;

#ifdef NEVER
	for(i ;i < num; i ++)
	{
		D_DUMP("subfix[%d]:%s \n",i, postfix[i]);
	}
	D_DUMP("\n");
#endif /* NEVER */

	
	file_fmt_prv = strrchr(filename, '.');
	if (file_fmt_prv)
	{
		file_fmt_prv++;
		for(i = 0; i < num; i++)
		{
			if (strcasecmp(file_fmt_prv,postfix[i]) == 0)
				return D_TRUE;
		}

	}
	else
	{
		//如果为文件夹时
		file_fmt_prv = "dir";
		for(i = 0; i < num; i++)
		{
			if (strcasecmp(file_fmt_prv,postfix[i]) == 0)
				return D_TRUE;
		}
		return D_FALSE;
	}
	
	if (i >= num)
		return D_FALSE;
	
}

D_Bool find_file_type(D_FILE_TYPE filetype, D_FILE_TYPE *ptype, D_U8 num)
{
    D_U8 i;
    D_Bool ret = D_FALSE;

    if(ptype)
    {
        for(i = 0; i < num; i++)
        {
            if(filetype == ptype[i])
            {
                ret = D_TRUE;
                break;
            }
        }
    }

    return ret;	
}


/** @brief 查找当前文件夹内的所有文件
* @param fd	回调函数返回的文件信息结构体
* @param arg	传给回调函数的指针参数
* @retval D_FALSE:处理成功后返回
*/
static D_Bool LSReadDirProc(D_FileFindData *fd, D_Ptr arg) D_FUNCPOSTFIT
{
	D_ProcFSData		*fsd = (D_ProcFSData*)arg;
	
	//D_DUMP("\t%s%s\t\t%llu\n",  fd->attribute ? "   " : "[D]",  fd->filename, fd->file_size);
	if( strcmp(fd->filename, ".") /*&& strcmp(fd->filename, "..")*/)
	{
		if (fsd->fs.cnt < fsd->fs.max)
		{
			strncpy(fsd->fs.ids[fsd->fs.cnt].path.filename ,fd->filename,sizeof(fsd->fs.ids[fsd->fs.cnt].path.filename)-1);
			fsd->fs.ids[fsd->fs.cnt].type = fd->attribute;
			fsd->fs.ids[fsd->fs.cnt].file_type = p_file_scan_parse_file_type(fd->attribute, fd->filename);
			fsd->fs.ids[fsd->fs.cnt].class_type = p_file_scan_get_class_type_by_type(fsd->fs.ids[fsd->fs.cnt].file_type);
			fsd->fs.ids[fsd->fs.cnt].dev_type = 0;
			fsd->fs.cnt++;
		}
		return D_FALSE;	
	}
	return D_FALSE;
}


/** @brief 查找当前文件夹内的指定文件后缀名的文件
* @param fd	回调函数返回的文件信息结构体
* @param arg	传给回调函数的指针参数
* @retval D_FALSE:处理成功后返回
*/
static D_Bool LSReadDirProcFilter(D_FileFindData *fd, D_Ptr arg) D_FUNCPOSTFIT
{
    D_ProcFSData		*fsd = (D_ProcFSData*)arg;
    D_Bool  match_flag = D_FALSE;
    D_FILE_TYPE  filetype;

    //D_DUMP("\t%s%s\t\t%llu\n",  fd->attribute ? "   " : "[D]",  fd->filename, fd->file_size);
    if( strcmp(fd->filename, ".") && fsd && (fsd->fs.cnt < fsd->fs.max))
    {   
        if(fsd->mode == D_FILE_MATCH_MODE_POSTFIX)
        {
            if(find_file_postfix(fd->filename, (D_Char **)fsd->subfix, fsd->num) == D_TRUE)
            {
                filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);     
                match_flag = D_TRUE;
            }
        }
        else if(fsd->mode == D_FILE_MATCH_MODE_FILETYPE)
        {
            filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);
            if(find_file_type(filetype, (D_FILE_TYPE *)fsd->subfix, fsd->num) == D_TRUE)
            {
                match_flag = D_TRUE;
            }   
        }

        if(match_flag == D_TRUE &&  fsd->fs.cnt < fsd->fs.max)
        {
            strncpy(fsd->fs.ids[fsd->fs.cnt].path.fullpath, fd->filename, sizeof(fsd->fs.ids[fsd->fs.cnt].path.fullpath)-1);
            fsd->fs.ids[fsd->fs.cnt].type = fd->attribute;
            fsd->fs.ids[fsd->fs.cnt].file_type = filetype;
            fsd->fs.ids[fsd->fs.cnt].class_type = p_file_scan_get_class_type_by_type(filetype);
            fsd->fs.ids[fsd->fs.cnt].dev_type = 0;
            fsd->fs.cnt++;
        }
    }
    return D_FALSE;
}

/** @brief 从当前文件夹开始深度遍历所有文件
* @param fd	回调函数返回的文件信息结构体
* @param arg	传给回调函数的指针参数
* @retval D_FALSE:处理成功后返回
*/
static D_Bool DeepReadDirProc(D_FileFindData *fd, D_Ptr arg) D_FUNCPOSTFIT
{
    D_ProcFSData		*fsd = (D_ProcFSData*)arg;
    D_Bool  match_flag = D_FALSE;
    D_FILE_TYPE  filetype;
    
    //D_DUMP("\t%s%s\t\t%llu\n",  fd->attribute ? "   " : "[D]",  fd->filename, fd->file_size);

    if((fd->attribute == 0) && strcmp(fd->filename, ".") && strcmp(fd->filename, ".."))
    {
        if(fsd->fs.cnt < fsd->fs.max)
        {
            if(d_fsm_readdir(fd->full_path, DeepReadDirProc, (D_Ptr)fsd) != D_OK)
            {
                D_DUMP("Read dir '%s' complete !\n", fd->full_path);
            }
        }
        return D_OK;
    }
    else if(fd->attribute)
    {
        if(fsd->mode == D_FILE_MATCH_MODE_ALL)
        {
            filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);   
            match_flag = D_TRUE;
        }
        else if(fsd->mode == D_FILE_MATCH_MODE_POSTFIX)
        {
            if(find_file_postfix(fd->filename, (D_Char **)fsd->subfix, fsd->num) == D_TRUE)
            {
                filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);     
                match_flag = D_TRUE;
            }
        }
        else if(fsd->mode == D_FILE_MATCH_MODE_FILETYPE)
        {
            filetype = p_file_scan_parse_file_type(fd->attribute, fd->filename);
            if(find_file_type(filetype, (D_FILE_TYPE *)fsd->subfix, fsd->num) == D_TRUE)
            {
                match_flag = D_TRUE;
            }   
        }

        if(match_flag == D_TRUE && fsd->fs.cnt < fsd->fs.max)
        {
            strncpy(fsd->fs.ids[fsd->fs.cnt].path.fullpath, fd->full_path, sizeof(fsd->fs.ids[fsd->fs.cnt].path.fullpath)-1);
            fsd->fs.ids[fsd->fs.cnt].type = fd->attribute;
            fsd->fs.ids[fsd->fs.cnt].file_type = filetype;
            fsd->fs.ids[fsd->fs.cnt].class_type = p_file_scan_get_class_type_by_type(filetype);
            fsd->fs.ids[fsd->fs.cnt].dev_type = 0;
            fsd->fs.cnt++;
        }
    }

    return D_FALSE;
}

/** @brief 比较两个文件的类型大小
* @param p1	事件1指针
* @param p2 事件2指针
* @retval 返回两文件类型的大小差
*/
static int sort_cmp_class_type(const D_Ptr*a, const D_Ptr*b)
{
    return (int)(((D_FSAttr*)b)->class_type) - (int)(((D_FSAttr*)a)->class_type);
}


/**@brief查找当前目录下的所有匹配的文件及文件夹
**@brief 当subfix和num不传入参数时是查找当前目录下的所有文件及文件夹,有参数按照方式与条件进行查找文件
*@param[in] path :要查找的目录路径
*@param[out] fs_set:返回查找到的所有文件记录集
*@param[in] postfix:查找时匹配项数组，如文件后缀名数组，类型数组等
*@param[in] numb:匹配项数组元素个数
*@param[in] mode:匹配方式
*@return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_get_current_dir(D_Char *path, D_FileScan *fs_set, D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE mode)D_FUNCPOSTFIT
{
    void *fp;
    D_ProcFSData		fsd = {0};
    int i = 0,result;
    D_Bool check_updir = D_FALSE;

    if(!path || !fs_set )
    {
        return D_ERR;
    }

    fsd.fs = *fs_set;
    
    /*当array 和num为空时搜索所有文件及文件夹*/
    if((!subfix) || (!numb) || (mode == D_FILE_MATCH_MODE_ALL))
    {
        mode = D_FILE_MATCH_MODE_ALL;
        check_updir = D_TRUE;
        if(d_fsm_readdir(path, LSReadDirProc, (D_Ptr)&fsd) != D_TRUE)
        {
            D_DUMP("Read dir '%s' read complete. total files: %d\n", path,fsd.fs.cnt);
            fs_set->cnt = fsd.fs.cnt;
        }
    }
    else
    {
        fsd.mode = mode;
        fsd.num = numb;
        fsd.subfix = subfix;

        if(mode == D_FILE_MATCH_MODE_POSTFIX)
        {
            if(find_file_postfix("..", (D_Char **)subfix, numb))
            {
                check_updir = D_TRUE;
            }
        }
        else if(mode == D_FILE_MATCH_MODE_FILETYPE)
        {
            if(find_file_type(D_FILE_TYPE_UPDIR, (D_FILE_TYPE *)subfix, numb))
            {
                check_updir = D_TRUE;
            }
        }

        if(d_fsm_readdir(path, LSReadDirProcFilter, (D_Ptr)&fsd) != D_TRUE)
        {
            D_DUMP("Read dir '%s' read complete. total files: %d\n", path,fsd.fs.cnt);
            fs_set->cnt = fsd.fs.cnt;
        }
    }

    /*文件记录集添加上级目录'..'的记录*/
    if(fs_set->cnt == 0)
    {
        strcpy(fs_set->ids[fs_set->cnt].path.filename, "..");
        fs_set->ids[fs_set->cnt].type = 0;
        fs_set->ids[fs_set->cnt].file_type = D_FILE_TYPE_UPDIR;
        fs_set->ids[fs_set->cnt].class_type = D_FILE_SCAN_FMT_UpDir;
        fs_set->ids[fs_set->cnt].dev_type = 0;
        fs_set->cnt++;
    } 
    else if(check_updir)
    {
        for(i = 0; i < fs_set->cnt; i++)
        {
            if(fs_set->ids[i].type == 0 && fs_set->ids[i].class_type == D_FILE_SCAN_FMT_UpDir)
                break;
        }
       
        if (i >= fs_set->cnt)	/*如果是达到了最大文件个数，加在最后一个*/
        {
            i = D_MIN(i, (fs_set->max - 1));
            memset(fs_set->ids[i].path.filename, 0x00, sizeof(fs_set->ids[i].path.filename));
            strcpy(fs_set->ids[i].path.filename, "..");
            fs_set->ids[i].type = 0;
            fs_set->ids[i].file_type = D_FILE_TYPE_UPDIR;
            fs_set->ids[i].class_type = D_FILE_SCAN_FMT_UpDir;
            fs_set->ids[i].dev_type = 0;
            fs_set->cnt = i+1;
        }
    }  

    //调用按文件类型排序的函数
    if(fs_set->cnt > 1)
    {
        p_file_scan_sort_by_type(fs_set, sort_cmp_class_type);
    }
    
    return D_OK;
}

/**@brief从当前目录开始遍历查找subfix数组所列的所有文件
*@param[in] path :要查找的目录路径
*@param[out] fs_set:返回查找到的所有文件记录集
*@param[in] postfix:查找时匹配项数组，如文件后缀名数组，类型数组等
*@param[in] numb:匹配项数组元素个数
*@param[in] mode:匹配方式
*@return D_OK:返回成功，D_ERR:返回失败
*return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_get_files_by_type(D_Char *path, D_FileScan *fs_set, D_Ptr subfix, D_U8 numb, D_FILEMATCH_MODE mode)D_FUNCPOSTFIT
{
    D_ProcFSData		fsd;
    D_U8 i = 0;
    D_Bool check_updir = D_FALSE;
    
    if (!path || !fs_set)
    {
        return D_ERR;
    }
    
    if((!subfix || !numb) || mode == D_FILE_MATCH_MODE_ALL)
    {
         subfix = NULL;
         numb = 0;
         mode = D_FILE_MATCH_MODE_ALL;
         check_updir = D_TRUE;
    }
    
    if(mode == D_FILE_MATCH_MODE_POSTFIX)
    {
        if(find_file_postfix("..", (D_Char **)subfix, numb))
        {
            check_updir = D_TRUE;
        }
    }
    else if(mode == D_FILE_MATCH_MODE_FILETYPE)
    {
        if(find_file_type(D_FILE_TYPE_UPDIR, (D_FILE_TYPE *)subfix, numb))
        {
            check_updir = D_TRUE;
        }
    }  
    
    fsd.fs = *fs_set;
    fsd.mode = mode;
    fsd.num = numb;
    fsd.subfix = subfix;
 
    if(d_fsm_readdir(path, DeepReadDirProc, (D_Ptr)&fsd) != D_TRUE)
    {
        D_DUMP("Read dir '%s' read complete. total files: %d\n", path,fsd.fs.cnt);
        fs_set->cnt = fsd.fs.cnt;
    }
    
    /*文件记录集添加上级目录'..'的记录*/
    if(fs_set->cnt == 0)
    {
        strcpy(fs_set->ids[fs_set->cnt].path.filename, "..");
        fs_set->ids[fs_set->cnt].type = 0;
        fs_set->ids[fs_set->cnt].file_type = D_FILE_TYPE_UPDIR;
        fs_set->ids[fs_set->cnt].class_type = D_FILE_SCAN_FMT_UpDir;
        fs_set->ids[fs_set->cnt].dev_type = 0;
        fs_set->cnt++;
    }
    else if(check_updir)
    {
        for(i = 0; i < fs_set->cnt; i++)
        {
            if(fs_set->ids[i].type == 0 && fs_set->ids[i].class_type == D_FILE_SCAN_FMT_UpDir)
                break;
        }
       
        if (i >= fs_set->cnt)	/*如果是达到了最大文件个数，加在最后一个*/
        {
            i = D_MIN(i, (fs_set->max - 1));
            memset(fs_set->ids[i].path.filename, 0x00, sizeof(fs_set->ids[i].path.filename));
            strcpy(fs_set->ids[i].path.filename, "..");
            fs_set->ids[i].type = 0;
            fs_set->ids[i].file_type = D_FILE_TYPE_UPDIR;
            fs_set->ids[i].class_type = D_FILE_SCAN_FMT_UpDir;
            fs_set->ids[i].dev_type = 0;
            fs_set->cnt = i+1;
        }
    }

    //调用按文件类型排序的函数
    if(fs_set->cnt > 1)
    {
        p_file_scan_sort_by_type(fs_set, sort_cmp_class_type);
    }

    return D_OK;
}

/**@brief 根据分区索引号与个数为多媒体列表数据填充内容
*@param[out] fs_set:磁盘记录集数据结构体
*@param[in] vol_index:分区索引号数组
*@param[in] numb:磁盘分区个数
*@retval 成功返回D_OK, 失败返回D_ERR;
*/
D_Result p_file_scan_get_all_partitons(D_FileScan *fs_set, D_U8 vol_index[], D_U8 numb)D_FUNCPOSTFIT
{
    D_ID	i = 0;
    D_U32 size;

    size = sizeof(fs_set->ids[i].path.fullpath);

	for(i; i < numb; i++)
	{
		if (fs_set->cnt < fs_set->max)
		{
			strncpy(fs_set->ids[i].path.fullpath, device_content[vol_index[i]], size);
			fs_set->ids[i].type = 0;/*磁盘都默认为为目录*/
			fs_set->ids[i].file_type = D_FILE_TYPE_DEVICE;
			fs_set->ids[i].class_type = D_FILE_SCAN_FMT_Device;
			fs_set->ids[i].dev_type = (D_U8)d_fsm_get_volume_type(vol_index[i]);
			fs_set->cnt++;
		}
	}

	if (i >= numb)
		return D_ERR;
	
	return D_OK;
}

/**@brief 根据文件(夹)名取得格式类型(gif/jpg/flv/rmvb/mkv...)
*param: attribute 属性(0 目录，1 文件)
*param: path 文件(夹)名称
*ret	 成功返回文件类型
*/
D_FILE_TYPE p_file_scan_parse_file_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT
{
    char * file_fmt_prv = NULL, ch;
    D_FILE_TYPE type = D_FILE_TYPE_None;

    if(NULL == fname)
    {
        return D_FILE_TYPE_None;
    }

    if(attribute == 0)
    {   
        if (!strcmp((fname), ".."))
        {
            type = D_FILE_TYPE_UPDIR;
        }
        else
        {
            type = D_FILE_TYPE_DIR;
        }
        return type;
    }
    
    file_fmt_prv = strrchr(fname, '.');
    if (file_fmt_prv)
    {
        file_fmt_prv ++;
        ch = D_TO_UPPER(*file_fmt_prv);
        switch(ch)
        {
            case 'A':
                if(strcasecmp(file_fmt_prv, "AAC") == 0)
                {
                    type = D_FILE_TYPE_AAC;
                }
                else if(strcasecmp(file_fmt_prv, "AMR") == 0)
                {
                    type = D_FILE_TYPE_AMR;
                }
                else if(strcasecmp(file_fmt_prv, "AVI") == 0)
                {
                    type = D_FILE_TYPE_AVI;
                }
                if(strcasecmp(file_fmt_prv, "AC3") == 0)
                {
                    type = D_FILE_TYPE_AC3;
                }
                break;
            case 'B':
                if(strcasecmp(file_fmt_prv, "BIN") == 0)
                {
                    type = D_FILE_TYPE_BIN;
                }
                else if(strcasecmp(file_fmt_prv, "BMP") == 0)
                {
                    type = D_FILE_TYPE_BMP;
                }
                break;         
            case 'C':
                break;    
            case 'D':
                if(strcasecmp(file_fmt_prv, "DAT") == 0)
                {
                    type = D_FILE_TYPE_DAT;
                }
                break;   
            case 'E':
                if(strcasecmp(file_fmt_prv, "EBK") == 0)
                {
                    type = D_FILE_TYPE_EBK;
                }
                else if(strcasecmp(file_fmt_prv, "EAC3") == 0)
                {
                    type = D_FILE_TYPE_AC3;
                }
                break;    
            case 'F':
                if(strcasecmp(file_fmt_prv, "FLV") == 0)
                {
                    type = D_FILE_TYPE_FLV;
                }
                else if(strcasecmp(file_fmt_prv, "F4V") == 0)
                {
                    type = D_FILE_TYPE_MP4;
                }
                break;    
            case 'G':
                if(strcasecmp(file_fmt_prv, "GIF") == 0)
                {
                    type = D_FILE_TYPE_GIF;
                }
                break;  
            case 'H':
                if(strcasecmp(file_fmt_prv, "HTS") == 0)
                {
                    type = D_FILE_TYPE_HTS;
                }
                break;  
            case 'I':
                break;  
            case 'J':
                if(strcasecmp(file_fmt_prv, "JPG") == 0)
                {
                    type = D_FILE_TYPE_JPG;
                }
                else if(strcasecmp(file_fmt_prv, "JPEG") == 0)
                {
                    type = D_FILE_TYPE_JPG;
                }
                break;
            case 'K':
                break;  
            case 'L':
                if(strcasecmp(file_fmt_prv, "LRC") == 0)
                {
                    type = D_FILE_TYPE_LRC;
                }
                break;   
            case 'M':
                if(strcasecmp(file_fmt_prv, "MP3") == 0)
                {
                    type = D_FILE_TYPE_MP3;
                }
                else if(strcasecmp(file_fmt_prv, "MP4") == 0)
                {
                    type = D_FILE_TYPE_MP4;
                }
                else if(strcasecmp(file_fmt_prv, "M4V") == 0)
                {
                    type = D_FILE_TYPE_MP4;
                }
                else if(strcasecmp(file_fmt_prv, "MPG") == 0)
                {
                    type = D_FILE_TYPE_MPG;
                }
                else if(strcasecmp(file_fmt_prv, "MPEG") == 0)
                {
                    type = D_FILE_TYPE_MPG;
                }
                else if(strcasecmp(file_fmt_prv, "MOV") == 0)
                {
                    type = D_FILE_TYPE_MOV;
                }
                else if(strcasecmp(file_fmt_prv, "MKV") == 0)
                {
                    type = D_FILE_TYPE_MKV;
                }
#if 0	//去掉M2T和M2TS格式的支持			
                else if(strcasecmp(file_fmt_prv, "M2T") == 0)
                {
                    type = D_FILE_TYPE_TS;
                }
                else if(strcasecmp(file_fmt_prv, "M2TS") == 0)
                {
                    type = D_FILE_TYPE_TS;
                }
#endif
                break;
            case 'N':
            case 'O':
                break; 
            case 'P':
                if(strcasecmp(file_fmt_prv, "PNG") == 0)
                {
                    type = D_FILE_TYPE_PNG;
                }
                break;   
            case 'Q':
                break; 
            case 'R':
                if(strcasecmp(file_fmt_prv, "RMVB") == 0)
                {
                    type = D_FILE_TYPE_RMVB;
                }
                break;   
            case 'S':
                if(strcasecmp(file_fmt_prv, "SRT") == 0)
                {
                    type = D_FILE_TYPE_SRT;
                }
                break;   
            case 'T':
                if(strcasecmp(file_fmt_prv, "TS") == 0)
                {
                    type = D_FILE_TYPE_TS;
                }
                else if(strcasecmp(file_fmt_prv, "TP") == 0)
                {
                    type = D_FILE_TYPE_TS;
                }				
                else if(strcasecmp(file_fmt_prv, "TRP") == 0)
                {
                    type = D_FILE_TYPE_TS;
                }
#if 1								
                else if(strcasecmp(file_fmt_prv, "TXT") == 0)
                {
                    type = D_FILE_TYPE_TXT;
                }
#endif								
                break;   
            case 'U':
                break; 
            case 'V':
                if(strcasecmp(file_fmt_prv, "VOB") == 0)
                {
                    type = D_FILE_TYPE_VOB;
                }
                break;
            case 'W':
                if(strcasecmp(file_fmt_prv, "WMA") == 0)
                {
                    type = D_FILE_TYPE_WMA;
                }
                else if(strcasecmp(file_fmt_prv, "WAV") == 0)
                {
                    type = D_FILE_TYPE_WAV;
                }
                break;  
            case 'X':
            case 'Y':
            case 'Z':
                break;   
            case '3':
                if(strcasecmp(file_fmt_prv, "3GP") == 0)
                {
                    type = D_FILE_TYPE_3GP;
                }
                break;
           default:
            break;
        }
    }
                            
    return type;
}

/**@brief 根据文件格式类型(gif/jpg/rmvb/flv...)取得分类信息(目录/电影/音乐...)*/
D_U32 p_file_type_to_unicode(D_FILE_TYPE filetype)D_FUNCPOSTFIT
{
    D_U32 unicode = 0;;

    switch(filetype)
    {

        case D_FILE_TYPE_3GP:
            unicode = 0x334750;
            break;
        case D_FILE_TYPE_MKV:
            unicode = 0x4d4b56;
            break;
        case D_FILE_TYPE_MP4:
            unicode = 0x4d5034;
            break;
        case D_FILE_TYPE_MPG:
            unicode = 0x4d5047;
            break;
        case D_FILE_TYPE_MOV:
            unicode = 0x4d4f56;
            break;

        case D_FILE_TYPE_RMVB:
            unicode = 0x524d56;
            break;

        case D_FILE_TYPE_FLV:
            unicode = 0x464c56;
            break;

        case D_FILE_TYPE_VOB:
            unicode = 0x564f42;
            break;

        case D_FILE_TYPE_AVI:
            unicode = 0x415649;
            break;

        case D_FILE_TYPE_DAT:
            unicode = 0x444154;
            break;

        case D_FILE_TYPE_MP3:
            unicode = 0x4d5033;
            break;

        case D_FILE_TYPE_AAC:
            unicode = 0x414143;
            break;

        case D_FILE_TYPE_AMR:
            unicode = 0x414d52;
            break;

        case D_FILE_TYPE_WAV:
            unicode = 0x574156;
            break;

        case D_FILE_TYPE_WMA:
            unicode = 0x574d41;
            break;

        case D_FILE_TYPE_BMP:
            unicode = 0x424d50;
            break;

        case D_FILE_TYPE_GIF:
            unicode = 0x474946;
            break;

        case D_FILE_TYPE_JPG:
            unicode = 0x4a5047;
            break;

        case D_FILE_TYPE_PNG:
            unicode = 0x504e47;
            break;

        case D_FILE_TYPE_EBK:
            unicode = 0x45424b;
            break;

        case D_FILE_TYPE_TS:
            unicode = 0x545320;
            break;
        case D_FILE_TYPE_HTS:
            unicode = 0x485453;
            break;

        case D_FILE_TYPE_TXT:
            unicode = 0x545854;
            break;

        case D_FILE_TYPE_LRC:
            unicode = 0x4c5243;
            break;

        case D_FILE_TYPE_SRT:
            unicode = 0x535254;
            break;
        case D_FILE_TYPE_BIN:
            unicode = 0x42494e;
            break;

        default:
            break;
    }
    return unicode;
}

void file_fmt_to_unicode(D_FILE_TYPE *ptype, D_U8 num, D_U32 *unicode, D_U8 *unicode_num)
{
    int i;
    if (num > FILE_TYPE_NUM)
    {
        *unicode_num = FILE_TYPE_NUM;
    }
    else
    {
        *unicode_num = num;
    }
    for(i = 0; i < *unicode_num; i++)
    {
        unicode[i] = p_file_type_to_unicode(ptype[i]);
    }
}

/**@brief 根据文件格式类型(gif/jpg/rmvb/flv...)取得分类信息(目录/电影/音乐...)*/
D_FILESCAN_TYPE p_file_scan_get_class_type_by_type(D_FILE_TYPE filetype)D_FUNCPOSTFIT
{
    D_FILESCAN_TYPE type = D_FILE_SCAN_FMT_None;

    switch(filetype)
    {
        case D_FILE_TYPE_None:
            type = D_FILE_SCAN_FMT_None;
            break;
        case D_FILE_TYPE_DEVICE:
            type = D_FILE_SCAN_FMT_Device;
            break; 
        case D_FILE_TYPE_UPDIR:
            type = D_FILE_SCAN_FMT_UpDir;
            break; 
        case D_FILE_TYPE_DIR:
            type = D_FILE_SCAN_FMT_Dir;
            break;  
        case D_FILE_TYPE_3GP:
        case D_FILE_TYPE_MKV:
        case D_FILE_TYPE_MP4:
        case D_FILE_TYPE_MPG:    
        case D_FILE_TYPE_MOV:           
        case D_FILE_TYPE_RMVB:    
        case D_FILE_TYPE_FLV:
        case D_FILE_TYPE_VOB:
        case D_FILE_TYPE_AVI:
        case D_FILE_TYPE_DAT: 
            type = D_FILE_SCAN_FMT_Movie;
            break;
        case D_FILE_TYPE_MP3:
        case D_FILE_TYPE_AAC:
        case D_FILE_TYPE_AMR:
        case D_FILE_TYPE_WAV:    
        case D_FILE_TYPE_WMA:           
        case D_FILE_TYPE_AC3:
            type = D_FILE_SCAN_FMT_Music;
            break;
        case D_FILE_TYPE_BMP:
        case D_FILE_TYPE_GIF:
        case D_FILE_TYPE_JPG:
        case D_FILE_TYPE_PNG:              
            type = D_FILE_SCAN_FMT_Photo;
            break;
        case D_FILE_TYPE_EBK:
            type = D_FILE_SCAN_FMT_EBK;
            break; 
        case D_FILE_TYPE_TS:
            type = D_FILE_SCAN_FMT_TS;
            break; 
        case D_FILE_TYPE_HTS:
            type = D_FILE_SCAN_FMT_Pvr;
            break;
        case D_FILE_TYPE_TXT:
            type = D_FILE_SCAN_FMT_Txt;
            break;
        case D_FILE_TYPE_LRC:
            type = D_FILE_SCAN_FMT_Lrc_Title;
            break;
        case D_FILE_TYPE_SRT:
            type = D_FILE_SCAN_FMT_Srt_Title;
            break;
        case D_FILE_TYPE_BIN:
            type = D_FILE_SCAN_FMT_BIN;
            break;
        default:
            break;
    }
                     
    return type;
}


/**@brief 根据文件(夹)名取得分类信息(目录/电影/音乐...)
*@param[in] attribute 属性(0 目录，1 文件)
*@param[in] path 文件(夹)名称
*@return 成功返回文件类型D_FILESCAN_TYPE_***, 失败返回D_FILE_SCAN_FMT_None;
*/
D_FILESCAN_TYPE p_file_scan_get_file_class_type(D_U8 attribute, D_Char *fname)D_FUNCPOSTFIT
{
    D_FILE_TYPE filetype;
    filetype = p_file_scan_parse_file_type(attribute, fname);               
    return p_file_scan_get_class_type_by_type(filetype);
}

/**@brief根据文件类型进行排序
*@param[in/out] fs_set:排好序的磁盘记录集数据结构体
*@param[in] func:排序函数
*return D_OK:返回成功，D_ERR:返回失败
*/
D_Result p_file_scan_sort_by_type(D_FileScan *fs_set, D_CmpFunc func)D_FUNCPOSTFIT
{
    if (! fs_set || ! func) 
    {
        return D_ERR;
    }

    qsort(fs_set->ids, fs_set->cnt, sizeof(D_FSAttr), func);

    return D_OK;
}

/**@brief 查找给定路径文件在当前文件记录集中的序号
*@param[in] path :要查找的目录路径
*@param[in] fs_set:返回查找到的所有文件记录集
*@return 成功返回序号D_ERR:返回失败
*/
D_Result p_file_scan_get_index(D_Char *path, D_FileScan *fs_set)D_FUNCPOSTFIT
{
	D_ID	i,max = fs_set->cnt;
	for(i = 0; i < max; i++)
	{
		if (!strcmp(fs_set->ids[i].path.fullpath, path))
			break;
	}

	/*没找到path对应序号则返回失败*/
	if (i <0 || i >= max)
	{
		return D_ERR; 
	}

	return i;
}

//pFile_Scan.c end

