/**@defgroup logo信息存储模块
*@{*/

/** @file
* @brief logo信息存储
* @author liuwf
* @date 2014-04-01 liuwf: 创建文件
*/
#include "stdio.h"
#include <string.h>
#include "dTypes.h"
#include "dNVPart.h"
#include "dDebug.h"
#include "dad_data_store.h"
#include "dadporting.h"
#include "dGUI.h"
#include "dDBaseInternal.h"
#include "dCrc.h"
#include "dNVPart_def.h"
//#include "logo_data.c"


/** @brief 图片信息头描述*/
typedef struct
{
    D_U32 crc_header;
    D_U32 length;
    D_U32 count;    
}Ad_Data_Header;


#define  D_AD_BUFFER_SIZE 0x10000
#define  D_AD_HEADER_MAX_SIZE 0x2800//0x10000
#define  D_AD_MAX_CNT ((D_AD_HEADER_MAX_SIZE - sizeof(Ad_Data_Header))/sizeof(D_Ad_Pict_Param))


static D_HNVPart hnvp = D_INVALID_HANDLE;
static D_NVPartInfo ad_part_info;
static D_Bool valid_flag = D_FALSE;
static D_U8 *header_buf = NULL;
static D_U8 *temp_buf = NULL;
static  Ad_Data_Info *adlogolist = NULL; ///保存图片信息的链表
static  D_HSem		sem;	

/** @brief 检查广告信息是否有效
* @param [in]ad_data	广告数据头地址
* @return D_OK	广告数据有效；D_ERR	广告数据无效
*/
static D_Result verify_data(D_U8 *ad_data) D_FUNCPOSTFIT
{
	D_U16 i;
	Ad_Data_Header tmp_ad_header;
	D_Ad_Pict_Param tmp_pict_param;
	D_U32 crc_header;
	D_Size size_h;
	D_U16 offset = 0;

	memcpy(&tmp_ad_header, ad_data, sizeof(Ad_Data_Header));	
	if(tmp_ad_header.count > D_AD_MAX_CNT)
	{
		return D_ERR;
	}
	size_h = sizeof(Ad_Data_Header) + (tmp_ad_header.count)*sizeof(D_Ad_Pict_Param) - 4;
	crc_header = d_crc_compute_32_ex((D_U32)-1, (ad_data + 4), size_h);
	if(crc_header != tmp_ad_header.crc_header)
	{
		return D_ERR;
	}
	offset = sizeof(Ad_Data_Header);
	for(i = 0; i < tmp_ad_header.count; ++i)
	{
		memcpy(&tmp_pict_param, (ad_data + offset), sizeof(D_Ad_Pict_Param));
		if(tmp_pict_param.img_size <= 0)
		{
			return D_ERR;
		}
		if((D_U32)(tmp_pict_param.offset + tmp_pict_param.img_size) > (ad_part_info.nv_size - 8))
		{
			return D_ERR;
		}
#if 0	//加载数据时，不需要对每张图片的CRC做校验
		crc_pict = (D_U32)(-1);
		cnt = (tmp_pict_param.img_size + 0xFFFF)/0x10000;
		for(j = 1; j <= cnt; ++j)
		{
			memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
			if(j == cnt)
			{
				size_tmp = tmp_pict_param.img_size - (j - 1)*0x10000;
			}
			else
			{
				size_tmp = 0x10000;
			}
			ret = d_nvpart_read(hnvp, (tmp_pict_param.offset + (j - 1)*0x10000), temp_buf, size_tmp);
			if(ret < size_tmp)
			{
				return D_ERR;
			}
			crc_pict = d_crc_compute_32_ex(crc_pict, temp_buf, size_tmp);
		}
		if(crc_pict != tmp_pict_param.crc)
		{
			return D_ERR;
		}
#endif
		offset += sizeof(D_Ad_Pict_Param);
		size_h += tmp_pict_param.img_size;
	}
	if((size_h + 4) != tmp_ad_header.length)
	{
		return D_ERR;
	}
	return D_OK;
}

/** @brief 删除某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	删除成功；D_ERR	删除成功
*/
static D_Result delete_by_type(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
	D_U16 i = 0, j = 0;
	Ad_Data_Header header_info, tmp_header_info;
	D_Ad_Pict_Param tmp_pict_param, pict_param;
	D_U8 *buf = NULL;
	D_Bool if_delete = D_FALSE;
	D_U32 offset = 0, erase_size = 0;
	D_U32 new_offset = 0;
	D_U32 read_offset = 0;
	D_Size size1, size2, data_len;
	D_U8 cnt = 0;
	D_Size ret;

	if(!valid_flag)
	{
		return D_ERR;
	}

	buf = (D_U8*)d_mem_alloc (0, D_AD_BUFFER_SIZE);
	if(!buf)
	{
		return D_ERR;
	}
	memset(buf, 0xFF, D_AD_BUFFER_SIZE);
	memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	memset(&tmp_header_info, 0, sizeof(Ad_Data_Header));

	offset = sizeof(Ad_Data_Header);
	new_offset = D_AD_HEADER_MAX_SIZE;
	data_len = sizeof(Ad_Data_Header);
	for(i = 0; i < header_info.count; ++i)
	{
		memcpy(&pict_param, (header_buf + offset), sizeof(D_Ad_Pict_Param));
		if(pict_param.advType == type)
		{
			if_delete = D_TRUE;
			size1 = pict_param.offset % 0x10000;
			size2 = 0x10000 - size1;
			if(pict_param.img_size <= size2)
			{
				cnt = 1;
			}
			else
			{
				cnt = (D_U8)(1 + (pict_param.img_size - size2 + 0xFFFF)/0x10000);
			}
			read_offset = (pict_param.offset/0x10000)*0x10000;
			for(j = 0; j < cnt; ++j)
			{
				memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
				if(j == 0)
				{
					ret = d_nvpart_read(hnvp, read_offset, temp_buf, 0x10000);
					if(ret < 0x10000)
					{
						d_mem_free(buf);
						return D_ERR;
					}
					d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
					if(pict_param.img_size <= size2)
					{
						erase_size = (D_U16)pict_param.img_size;
					}
					else
					{
						erase_size = size2;
					}
					memset((temp_buf + pict_param.offset - read_offset), 0xFF, erase_size);
					if((read_offset + 0x10000) >= ad_part_info.nv_size)
					{
						d_nvpart_write (hnvp, read_offset, temp_buf, 0x10000 - sizeof (D_NVPartTail));
					}
					else
					{
						d_nvpart_write (hnvp, read_offset, temp_buf, 0x10000);
					}
				}
				else if(j == (cnt - 1))
				{
					read_offset += 0x10000;
					ret = d_nvpart_read(hnvp, read_offset, temp_buf, 0x10000);
					if(ret < 0x10000)
					{
						d_mem_free(buf);
						return D_ERR;
					}
					d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
					erase_size = pict_param.offset + pict_param.img_size - read_offset;
					memset(temp_buf, 0xFF, erase_size);
					if((read_offset + 0x10000) >= ad_part_info.nv_size)
					{
						d_nvpart_write (hnvp, read_offset, temp_buf, 0x10000 - sizeof (D_NVPartTail));
					}
					else
					{
						d_nvpart_write (hnvp, read_offset, temp_buf, 0x10000);
					}
				}
				else
				{
					read_offset += 0x10000;
					d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
				}
			}
		}
		else
		{
			memcpy(&tmp_pict_param, &pict_param, sizeof(D_Ad_Pict_Param));
			data_len += (sizeof(D_Ad_Pict_Param) + pict_param.img_size);
			if(new_offset == pict_param.offset)
			{
				new_offset += pict_param.img_size;
			}
			else
			{
				if((D_U32)pict_param.offset < new_offset)
				{
					d_mem_free(buf);
					return D_ERR;
				}
				tmp_pict_param.offset = new_offset;

				size1 = pict_param.offset % 0x10000;
				size2 = 0x10000 - size1;
				if(pict_param.img_size <= size2)
				{
					cnt = 1;
				}
				else
				{
					cnt =(D_U8)( 1 + (pict_param.img_size - size2 + 0xFFFF)/0x10000);
				}
				read_offset = (pict_param.offset/0x10000)*0x10000;
				for(j = 0; j < cnt; ++j)
				{
					memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
					if(j == 0)
					{
						ret = d_nvpart_read(hnvp, read_offset, temp_buf, 0x10000);
						if(ret < 0x10000)
						{
							d_mem_free(buf);
							return D_ERR;
						}
						d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
						if(pict_param.img_size <= size2)
						{
							erase_size = pict_param.img_size;
						}
						else
						{
							erase_size = size2;
						}
						d_nvpart_write (hnvp, new_offset, (temp_buf + pict_param.offset - read_offset), erase_size);
						new_offset += erase_size;
					}
					else if(j == (cnt - 1))
					{
						read_offset += 0x10000;
						ret = d_nvpart_read(hnvp, read_offset, temp_buf, 0x10000);
						if(ret < 0x10000)
						{
							d_mem_free(buf);
							return D_ERR;
						}
						d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
						erase_size = pict_param.offset + pict_param.img_size - read_offset;
						d_nvpart_write (hnvp, new_offset, temp_buf, erase_size);
						new_offset += erase_size;
					}
					else
					{
						read_offset += 0x10000;
						ret = d_nvpart_read(hnvp, read_offset, temp_buf, 0x10000);
						if(ret < 0x10000)
						{
							d_mem_free(buf);
							return D_ERR;
						}
						d_nvpart_erase_flash(0, (ad_part_info.nv_offset + read_offset), 0x10000);
						if(new_offset + 0x10000 >= ad_part_info.nv_size)
						{
							d_nvpart_write (hnvp, new_offset, temp_buf, 0x10000 - sizeof (D_NVPartTail));
						}
						else
						{
							d_nvpart_write (hnvp, new_offset, temp_buf, 0x10000);
						}
						new_offset += 0x10000;
					}
				}
			}
			memcpy((buf + sizeof(Ad_Data_Header) + tmp_header_info.count * sizeof(D_Ad_Pict_Param)), &tmp_pict_param, sizeof(D_Ad_Pict_Param));
			++(tmp_header_info.count);
		}
		offset += sizeof(D_Ad_Pict_Param);
	}
	if(if_delete)
	{
		tmp_header_info.length = data_len;
		memcpy(buf, &tmp_header_info, sizeof(Ad_Data_Header));	
		tmp_header_info.crc_header = d_crc_compute_32_ex((D_U32)-1, (buf + 4), sizeof(Ad_Data_Header) + tmp_header_info.count * sizeof(D_Ad_Pict_Param) -4 );
		memcpy(buf, &(tmp_header_info.crc_header), 4);

		memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
		ret = d_nvpart_read(hnvp, 0, temp_buf, 0x10000);
		if(ret < 0x10000)
		{
			d_mem_free(buf);
			return D_ERR;
		}
		memset(temp_buf, 0xFF, D_AD_HEADER_MAX_SIZE);
		memcpy(temp_buf, buf, sizeof(Ad_Data_Header) + tmp_header_info.count * sizeof(D_Ad_Pict_Param));
		d_nvpart_erase_flash(0, ad_part_info.nv_offset, 0x10000);
		if(ad_part_info.nv_size <= 0x10000)
		{
			d_nvpart_write (hnvp, 0, temp_buf, 0x10000 - sizeof (D_NVPartTail));
		}
		else
		{
			d_nvpart_write (hnvp, 0, temp_buf, 0x10000);
		}
		memset(header_buf,0xFF,D_AD_BUFFER_SIZE);
		memcpy(header_buf, buf, sizeof(Ad_Data_Header) + tmp_header_info.count * sizeof(D_Ad_Pict_Param));
	}	

	d_mem_free(buf);

	return D_OK;
}

/** @brief 添加某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	添加成功；D_ERR	添加失败
*/
static D_Result insert_by_type(D_Ad_Pos_Type type, D_Ad_Img_Param *img_param)D_FUNCPOSTFIT
{
	D_Size ret;
	Ad_Data_Header header_info;
	D_Ad_Pict_Param tmp_pict_param, pict_param;

	if(!valid_flag)
	{
		return D_ERR;
	}

	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	if(header_info.count >= D_AD_MAX_CNT)
	{
		return D_ERR;
	}
	pict_param.advType = type;
	pict_param.imgType = img_param->imgType;
	pict_param.id = img_param->id;
	pict_param.img_size = img_param->img_size;
	pict_param.times = img_param->times;
	pict_param.left = img_param->left;
	pict_param.top = img_param->top;
	pict_param.width = img_param->width;
	pict_param.height = img_param->height;
	if(header_info.count == 0)
	{
		pict_param.offset = D_AD_HEADER_MAX_SIZE;
		header_info.length = sizeof(Ad_Data_Header);
	}
	else
	{
		memcpy(&tmp_pict_param, (header_buf + sizeof(Ad_Data_Header) + (header_info.count - 1) * sizeof(D_Ad_Pict_Param)), sizeof(D_Ad_Pict_Param));
		pict_param.offset = tmp_pict_param.offset + tmp_pict_param.img_size;
	}
	if((D_U32)(pict_param.offset + pict_param.img_size) > (ad_part_info.nv_size - sizeof(D_NVPartTail)))
	{
		return D_ERR;
	}
	pict_param.crc = d_crc_compute_32_ex((D_U32)-1, img_param->buf, img_param->img_size);
	memcpy((header_buf + sizeof(Ad_Data_Header) + (header_info.count) * sizeof(D_Ad_Pict_Param)), &pict_param, sizeof(D_Ad_Pict_Param));
	++(header_info.count);
	header_info.length += (img_param->img_size + sizeof(D_Ad_Pict_Param));
	memcpy(header_buf, &header_info, sizeof(Ad_Data_Header));
	header_info.crc_header = d_crc_compute_32_ex((D_U32)-1, (header_buf + 4), sizeof(Ad_Data_Header) + header_info.count * sizeof(D_Ad_Pict_Param) -4 );
	memcpy(header_buf, &(header_info.crc_header), 4);

	memset(temp_buf, 0xFF, D_AD_BUFFER_SIZE);
	ret = d_nvpart_read(hnvp, 0, temp_buf, 0x10000);
	if(ret < 0x10000)
	{
		return D_ERR;
	}
	memset(temp_buf, 0xFF, D_AD_HEADER_MAX_SIZE);
	memcpy(temp_buf, header_buf, sizeof(Ad_Data_Header) + header_info.count * sizeof(D_Ad_Pict_Param));
	d_nvpart_erase_flash(0, ad_part_info.nv_offset, 0x10000);
	if(ad_part_info.nv_size <= 0x10000)
	{
		d_nvpart_write (hnvp, 0, temp_buf, 0x10000 - sizeof(D_NVPartTail));
	}
	else
	{
		d_nvpart_write (hnvp, 0, temp_buf, 0x10000);
	}
	d_nvpart_write (hnvp, pict_param.offset, img_param->buf, pict_param.img_size);

	return D_OK;
}
/** @brief 检查链表的有效性，数据更新之后，之前的链表无效，所以需要释放
* @param list	基本链表
* @return NULL
*/
static D_Result check_list_valid(Ad_Data_Info *list,Ad_Data_Info *img_data)D_FUNCPOSTFIT
{
	Ad_Data_Info *templist;

    if(img_data == NULL)
    {
		return D_ERR;
    }

	templist = list;

	while(templist!=NULL)
	{
	 	list = templist->next;
		if(templist == img_data)
        {
			return D_OK;
        }
		templist = list;
	}		
	return D_ERR;        
}

/** @brief 释放某个图片
* @param img_data	图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   给外部使用的接口
*/
static D_Result release_img_data(Ad_Data_Info *img_data)D_FUNCPOSTFIT
{
	if(img_data->buffer != NULL)
	{
		switch(img_data->item.imgType)
		{
			case	D_IMAGE_JPEG: 
			case	D_IMAGE_PNG: 
			case	D_IMAGE_GIF: 
			case	D_IMAGE_BMP: 
				{
					d_image_free((D_Image *)img_data->buffer);
					img_data->buffer = NULL;
					break;
				}
			case	D_IMAGE_MPEG2_FRAME_I: 
				{
					d_mem_free(img_data->buffer);	 
					img_data->buffer = NULL;	 
					break;
				}
			default:
				{
					D_ERROR("[adv]logo_item.imgType error!\n"); 		
					break;
				}				
		}

	}
	return D_OK;	
}

/** @brief 获得所有图片总数
* @return 图片数量；-1 获取失败
*/
static D_S32 get_all_pict_cnt(void)D_FUNCPOSTFIT
{
	Ad_Data_Header header_info;

	if(!valid_flag)
	{
		return -1;
	}
	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	if(header_info.count > D_AD_MAX_CNT)
	{
		return -1;
	}
	return header_info.count;
}

/** @brief 获得某种应用的图片数量
* @param  type 图片应用类型
* @return 图片数量；-1 获取失败
*/
static D_S32 get_pict_cnt_by_type(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
	D_Size cnt = 0;	
	Ad_Data_Header header_info;
	D_Ad_Pict_Param pict_param;
	D_U16 i = 0;
	D_U16 offset = 0;

	if(!valid_flag)
	{
		return -1;
	}
	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	if(header_info.count > D_AD_MAX_CNT)
	{
		return -1;
	}
	offset = sizeof(Ad_Data_Header);
	for(i = 0; i < header_info.count; ++i)
	{
		memcpy(&pict_param, (header_buf + offset), sizeof(D_Ad_Pict_Param));
		if(pict_param.advType == type)
		{
			++cnt;
		}
		offset += sizeof(D_Ad_Pict_Param);
	}
	return cnt;
}
#if 0
/** @brief 获得某种应用的图片头信息
* @param  type 图片应用类型
* @param  num 图片号,从0开始
* @param  param 图片头信息存放指针
* @return D_OK	获取成功；D_ERR	获取失败
*/
static D_Result get_pict_param(D_Ad_Pos_Type type, D_U16 num, D_Ad_Pict_Param * param)D_FUNCPOSTFIT
{
	D_Size cnt = 0;	
	Ad_Data_Header header_info;
	D_Ad_Pict_Param pict_param;
	D_U16 i = 0;
	D_U16 offset = 0;

	if(!param)
	{
		return D_ERR;
	}
	if(!valid_flag)
	{
		return D_ERR;
	}
	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	if(header_info.count > D_AD_MAX_CNT)
	{
		return D_ERR;
	}
	offset = sizeof(Ad_Data_Header);
	for(i = 0; i < header_info.count; ++i)
	{
		memcpy(&pict_param, (header_buf + offset), sizeof(D_Ad_Pict_Param));
		if(pict_param.advType == type)
		{
			if(cnt == num)
			{
				memcpy(param, &pict_param, sizeof(D_Ad_Pict_Param));
				return D_OK;
			}
			++cnt;
		}
		offset += sizeof(D_Ad_Pict_Param);
	}
	return D_ERR;
}
#endif
/** @brief 获得图片数据
* @param  buf 图片数据存放区指针
* @param  flash_offset 图片数据在flash中存放区的偏移
* @param  data_size 图片数据的大小
* @param  crc 图片数据的crc
* @return D_OK	获取成功；D_ERR	获取失败
*/
static D_Result get_pict_data(D_U8 *buf, D_U32 flash_offset, D_U32 data_size, D_U32 crc)D_FUNCPOSTFIT
{
	D_Size ret;
	D_U32 crc_tmp;
	if(!buf)
	{
		return D_ERR;
	}
	if(!valid_flag)
	{
		return D_ERR;
	}
	if((flash_offset + data_size) > (ad_part_info.nv_size - 8))
	{
		return D_ERR;
	}
	ret = d_nvpart_read(hnvp, flash_offset, buf, data_size);
	if((D_U32)ret < data_size)
	{
		return D_ERR;
	}
	crc_tmp = d_crc_compute_32_ex((D_U32)-1, buf, data_size);
	if(crc_tmp != crc)
	{
		return D_ERR;
	}
	return D_OK;
}
/** @brief 获得某种应用的图片头信息
* @param  num 图片号,从0开始
* @param  param 图片头信息存放指针
* @return D_OK	获取成功；D_ERR	获取失败
*/
static D_Result get_pict_param_ex(D_U16 num, D_Ad_Pict_Param * param)D_FUNCPOSTFIT
{
	D_Size cnt = 0;	
	Ad_Data_Header header_info;
	D_Ad_Pict_Param pict_param;
	D_U16 i = 0;
	D_U16 offset = 0;

	if(!param)
	{
		return D_ERR;
	}
	if(!valid_flag)
	{
		return D_ERR;
	}
	memcpy(&header_info, header_buf, sizeof(Ad_Data_Header));
	if(header_info.count > D_AD_MAX_CNT)
	{
		return D_ERR;
	}
	offset = sizeof(Ad_Data_Header);
	for(i = 0; i < header_info.count; ++i)
	{
		memcpy(&pict_param, (header_buf + offset), sizeof(D_Ad_Pict_Param));
		if(cnt == num)
		{
			memcpy(param, &pict_param, sizeof(D_Ad_Pict_Param));
			return D_OK;
		}
		offset += sizeof(D_Ad_Pict_Param);
		++cnt;
	}
	return D_ERR;
}

/** @brief 链表中添加一个图片的信息
* @param list	基本链表
* @param type	图片的应用类型
* @param no	    第几个
* @return 找到的图片链表 NULL --无效
*/
static Ad_Data_Info* get_list_type(Ad_Data_Info *list,D_Ad_Pos_Type type,D_U8 no)D_FUNCPOSTFIT
{
    Ad_Data_Info *nextlist;
    D_U8 find = 0;

    if(list == NULL)
    {
		D_ERROR("[adv]adv_get_count_type error!\n");
    	return NULL;
    }
    else
    {
        nextlist = list;
        if((list->item.advType) == type)
        {
            if(find == no)
            {
                return list;
            }
            else
            {
                find ++;
            }

        } 
	    while(nextlist->next)
        {
            nextlist = nextlist->next;      
			if((nextlist->item.advType) == type)
            {
                if(find == no)
                {
                    return nextlist;
                }
                else
                {
                    find ++;
                } 
            }
        }          
    }
   	return NULL;

}

/** @brief 链表中添加一个图片的信息
* @param list	基本链表
* @param newlist	新的图片数据信息
* @return NULL
*/
static void add_list(Ad_Data_Info **list,Ad_Data_Info *newlist)D_FUNCPOSTFIT
{
    Ad_Data_Info *nextlist;
    D_U32 picid;

	picid = 0;

    if(*list == NULL)
    {
    	newlist->picid = 0;
        *list = newlist;
    }
    else
    {
        nextlist = *list;

	    while(nextlist->next)
        {
			nextlist = nextlist->next;      
        }
		picid = nextlist->picid;
        nextlist->next = newlist;
        nextlist = nextlist->next;

		nextlist->picid = (picid+1);
    }

}

/** @brief 更新的时候更新链表信息
* @param list	基本链表
* @return NULL
*/
static void update_list(Ad_Data_Info **list)D_FUNCPOSTFIT
{
    Ad_Data_Info *templist;
	D_S32 ret;
	D_U8 i;		
    D_S32  count;
	Ad_Data_Info * templogoitem;
	D_Ad_Pict_Param param;

	templist = *list;

	while(templist!=NULL)
	{
	 	*list = templist->next;
		if(templist->buffer == NULL)//释放上层未使用的链表信息
        {
			d_mem_free(templist);			 
        }
        templist = *list;
	}	
	*list = NULL;	

	//重新添加链表

	ret = d_nvpart_read(hnvp, 0, header_buf, D_AD_BUFFER_SIZE);	///头信息区数据
	if(ret < D_AD_BUFFER_SIZE)
	{
		D_ERROR("[adv]d_nvpart_read update_list error!\n");
		d_mem_free(temp_buf);
		d_mem_free(header_buf);
		temp_buf = NULL;
		header_buf = NULL;
		valid_flag = D_FALSE;
		return ;
	}
	if(verify_data(header_buf) != D_OK)
	{
		D_ERROR("[adv]logo_verify_data error!\n");
		d_nvpart_erase (hnvp);
		memset(header_buf, 0, D_AD_BUFFER_SIZE);
	}
	valid_flag = D_TRUE;
    count = get_all_pict_cnt();
	if(count == -1 )
	{
		return ;
	}
    for(i = 0; i <  count;i++)
    {
		if(get_pict_param_ex(i,&param)==D_OK) 
		{
			templogoitem = (Ad_Data_Info*)d_mem_alloc(0,sizeof(Ad_Data_Info));
			if(templogoitem != NULL)
			{
				memcpy((D_U8 *)templogoitem,(D_U8 *)(&param),sizeof(Ad_Data_Info));  	
		        templogoitem ->next = NULL;
		        templogoitem ->buffer = NULL;
		        add_list(list,templogoitem); 
			}
		}
    } 		
}

/** @brief 释放链表及所有的内存，在p_ad_close时候使用
* @param list	基本链表
* @return NULL
*/
static void del_list(Ad_Data_Info **list)D_FUNCPOSTFIT
{
	Ad_Data_Info *templist;

	templist = *list;

	while(templist!=NULL)
	{
	 	*list = templist->next;
		if(templist->buffer != NULL)
		{
			release_img_data(templist);
			templist->buffer = NULL;
		}
		d_mem_free(templist);		 
		templist = *list;
	}	
	*list = NULL;	
}

/**以下几个函数外部函数***************************/
/** @brief 打开广告模块，申请资源
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_store_open (void) D_FUNCPOSTFIT
{
	D_S32 ret;
	D_U8 i;
  D_S32  count;
	Ad_Data_Info * templogoitem;
	D_Ad_Pict_Param param;
	D_SemAttr attr;


	hnvp = d_nvpart_create(D_DB_NVRAM_ID, D_NV_PART_ADVERTISE);
	if(hnvp == D_INVALID_HANDLE)
	{
		D_ERROR("[adv]d_nvpart_create error!\n");
		valid_flag = D_FALSE;
		return D_ERR;
	}
	if(d_nvpart_get_info (hnvp, &ad_part_info)!=D_OK)
	{
		D_ERROR("[adv]d_nvpart_get_info error!\n");
		valid_flag = D_FALSE;
		return D_ERR;				
	}
	if(ad_part_info.nv_size == 0)
	{
		D_ERROR("[adv]ad_part_info.nv_size error!\n");
		valid_flag = D_FALSE;
		return D_ERR;					
	}
	header_buf = (D_U8*)d_mem_alloc (0, D_AD_BUFFER_SIZE);
    if(header_buf == NULL)
    {
		D_ERROR("[adv]logo_mem_alloc error!\n");
		valid_flag = D_FALSE;
        return D_ERR;
    }								
	memset(header_buf, 0xFF, D_AD_BUFFER_SIZE);

	temp_buf = (D_U8*)d_mem_alloc (0, D_AD_BUFFER_SIZE);
    if(temp_buf == NULL)
    {
		D_ERROR("[adv]logo_mem_alloc error!\n");
		d_mem_free(header_buf);
		header_buf = NULL;
		valid_flag = D_FALSE;
        return D_ERR;
    }								

	ret = d_nvpart_read(hnvp, 0, header_buf, D_AD_BUFFER_SIZE);	///头信息区数据
	if(ret < D_AD_BUFFER_SIZE)
	{
		D_ERROR("[adv]d_nvpart_read open error!\n");
		d_mem_free(temp_buf);
		d_mem_free(header_buf);
		temp_buf = NULL;
		header_buf = NULL;
		valid_flag = D_FALSE;
		return D_ERR;
	}
	if(verify_data(header_buf) != D_OK)
	{
		D_ERROR("[adv]logo_verify_data error!\n");
		d_nvpart_erase (hnvp);
		memset(header_buf, 0, D_AD_BUFFER_SIZE);
	}
	valid_flag = D_TRUE;
    count = get_all_pict_cnt();
	if(count == -1 )
	{
		return D_ERR;
	}
    for(i = 0; i <  count;i++)
    {
		if(get_pict_param_ex(i,&param)==D_OK) 
		{
			templogoitem = (Ad_Data_Info*)d_mem_alloc(0,sizeof(Ad_Data_Info));
			if(templogoitem != NULL)
			{
				memcpy((D_U8 *)templogoitem,(D_U8 *)(&param),sizeof(Ad_Data_Info));  	
		        templogoitem ->next = NULL;
		        templogoitem ->buffer = NULL;
		        add_list(&adlogolist,templogoitem); 
			}
		}
    } 

	sem = D_INVALID_HANDLE;
	D_SEM_ATTR_INIT (&attr);	
	sem = d_sem_create (&attr);
	d_sem_post(sem);

	return D_OK;
}

/** @brief 关闭logo模块，释放资源
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_store_close (void) D_FUNCPOSTFIT
{
	if(hnvp != D_INVALID_HANDLE)
    {   
	    d_nvpart_destroy(hnvp);
    }
    hnvp = D_INVALID_HANDLE;
	memset(&ad_part_info, 0, sizeof(D_NVPartInfo));

	del_list(&adlogolist);

	d_mem_free(temp_buf);
	d_mem_free(header_buf);
	temp_buf = NULL;
	header_buf = NULL;
	valid_flag = D_FALSE;

	if(sem != D_INVALID_HANDLE)
	{
		d_sem_destroy (sem);
		sem = D_INVALID_HANDLE;
	}

	return D_OK;
}

/** @brief 获取某种应用的图片数量
* @param  type 图片应用类型
* @return 返回这种应用的图片的数量
*/
D_U8 d_ad_store_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT
{
	D_Size num;
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}	

	num = get_pict_cnt_by_type(type);
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_post(sem);
	}

	if(num <= 0 )
		return 0;
	else
		return (D_U8)num;
}

/** @brief 获取某种应用的图片数据和信息
* @param  type 图片应用类型
* @param  no 第几个这个类型的图片
* @return 返回图片信息的指针
*/
Ad_Data_Info * d_ad_store_load_img_data(D_Ad_Pos_Type type, D_U8 no)D_FUNCPOSTFIT
{
    Ad_Data_Info* info;
    D_U8 *buf =NULL;
    D_U8 *imgbuf =NULL;
	D_Result ret;

 	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}
	info = get_list_type(adlogolist,type,no);
    if(info == NULL || (info->item.img_size==0))
    {
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}
		return NULL;
    }
    if(info ->buffer != NULL)
    {
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}
        return info;
    }
    buf = (D_U8*)(D_U8*)d_mem_alloc (0, info->item.img_size);	
    if(buf == NULL)
    {
		D_ERROR("[adv]logo_mem_alloc error:%d\n",info->item.img_size);
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}

        return NULL;
    }    
	ret = get_pict_data(buf,(D_U32)info->item.offset,(D_U32)info->item.img_size,(D_U32)info->item.crc);	///头信息
 	if(ret != D_OK)
	{
		D_ERROR("[adv]d_nvpart_read load image error!\n");
	    d_mem_free(buf);	
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}

        return NULL;
	}   
	switch(info->item.imgType)
	{
		case	D_IMAGE_JPEG: 
		case 	D_IMAGE_PNG: 
		case 	D_IMAGE_GIF: 
		case 	D_IMAGE_BMP: 
			{
				imgbuf = (D_U8*)d_g_load_image (d_gui_get_surface(), D_IMAGE_AUTO,(D_U8*)buf, (D_Size)info->item.img_size);						
				if (imgbuf == NULL)
				{
					D_ERROR("[adv]Eng Image load error:%d\n",info->item.img_size);
					d_mem_free(buf);	
					if(sem != D_INVALID_HANDLE)
					{
						d_sem_post(sem);
					}

					return NULL;
				}
				d_mem_free(buf);	
				info->buffer = imgbuf;
				if(sem != D_INVALID_HANDLE)
				{
					d_sem_post(sem);
				}

				return info;
			}
		case 	D_IMAGE_MPEG2_FRAME_I: 
			{
				imgbuf = (D_U8*)d_mem_alloc (0, (D_Size)info->item.img_size);	
				if (imgbuf == NULL)
				{
					D_ERROR("[adv]Eng Image load error:%d\n",info->item.img_size);
					d_mem_free(buf);	
					if(sem != D_INVALID_HANDLE)
					{
						d_sem_post(sem);
					}

					return NULL;
				}
				memcpy(imgbuf ,(D_U8*)buf,(D_Size)info->item.img_size);
				d_mem_free(buf);	
				info->buffer = imgbuf;
				if(sem != D_INVALID_HANDLE)
				{
					d_sem_post(sem);
				}

				return info;
			}
        default:
			{
    	        D_ERROR("[adv]logo_item.imgType error!\n");			
				if(sem != D_INVALID_HANDLE)
				{
					d_sem_post(sem);
				}

				return NULL;
			}
	}
}

/** @brief 释放某个图片
* @param img_data	图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   给外部使用的接口
*/
D_Result d_ad_store_release_img_data(Ad_Data_Info *img_data)D_FUNCPOSTFIT
{
	D_Result ret;
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}

	ret = release_img_data(img_data);	
	if(check_list_valid(adlogolist,img_data) == D_ERR)
	{
  		d_mem_free(img_data);            	
	}
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_post(sem);
	}

	return ret;
}
/** @brief 删除某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	删除成功；D_ERR	删除成功
*/
D_Result d_ad_store_delete_by_type(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
	D_Result ret;
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}

	ret = delete_by_type(type);
	update_list(&adlogolist);
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_post(sem);
	}

	return ret;
}

/** @brief 添加某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	添加成功；D_ERR	添加失败
*/
D_Result d_ad_store_insert_by_type(D_Ad_Pos_Type type, D_Ad_Img_Param *img_param)D_FUNCPOSTFIT
{	
	D_Result ret;
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}

	ret = insert_by_type(type,img_param);
	update_list(&adlogolist);
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_post(sem);
	}

	return ret;
}
/** @brief 获取某种应用的图片数据和信息
* @param  type 图片应用类型
* @param  no 第几个这个类型的图片
* @return 返回图片信息的指针
*/
Ad_Data_Info * d_ad_store_get_by_type(D_Ad_Pos_Type type, D_U8 no)D_FUNCPOSTFIT
{
    Ad_Data_Info* info,*picinfo = NULL;
    D_U8 *buf =NULL;
    D_U8 *imgbuf =NULL;
	D_Result ret;

 	if(sem != D_INVALID_HANDLE)
	{
		d_sem_wait (sem);
	}
	info = get_list_type(adlogolist,type,no);
    if(info == NULL || (info->item.img_size==0))
    {
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}
		return NULL;
    }
    buf = (D_U8*)(D_U8*)d_mem_alloc (0, info->item.img_size);	
    if(buf == NULL)
    {
		D_ERROR("[adv]logo_mem_alloc error:%d\n",info->item.img_size);
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}

        return NULL;
    }    
	ret = get_pict_data(buf,(D_U32)info->item.offset,(D_U32)info->item.img_size,(D_U32)info->item.crc);	///头信息
 	if(ret != D_OK)
	{
		D_ERROR("[adv]d_nvpart_read load image error!\n");
	    d_mem_free(buf);	
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}

        return NULL;
	}   
	imgbuf = (D_U8*)d_mem_alloc (0, (D_Size)info->item.img_size);	
	if (imgbuf == NULL)
	{
		D_ERROR("[adv]Eng Image load error:%d\n",info->item.img_size);
		d_mem_free(buf);	
		if(sem != D_INVALID_HANDLE)
		{
			d_sem_post(sem);
		}

		return NULL;
	}
	memcpy(imgbuf ,(D_U8*)buf,(D_Size)info->item.img_size);
	d_mem_free(buf);	
	if(sem != D_INVALID_HANDLE)
	{
		d_sem_post(sem);
	}
    picinfo = (D_U8*)d_mem_alloc (0, sizeof(Ad_Data_Info));	
    if(picinfo != NULL)
    {
		memcpy((D_U8*)picinfo ,(D_U8*)info,sizeof(Ad_Data_Info));    	
		picinfo->buffer = imgbuf;
		picinfo->next = NULL;
    } 
	return picinfo;
}
/** @brief 释放获取图片时所申请的内存
* @param  Ad_Data_Info *img_data
* @return 返回图片信息的指针
*/
void d_ad_store_free_mem(Ad_Data_Info *img_data)D_FUNCPOSTFIT
{
	if(img_data == NULL)
		return;
	if(img_data->buffer != NULL)
	{
		d_mem_free(img_data->buffer);	 
		img_data->buffer = NULL;	 
	}
	return;	
}
/* @}*/



