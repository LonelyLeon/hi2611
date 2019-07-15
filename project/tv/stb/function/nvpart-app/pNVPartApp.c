#include "dNVPart.h"
#include "pNVPartApp.h"
#include "dNVRam.h"
#include "dMem.h"
#include "dMutex.h"
#include "dSys.h"
#include "dDebug.h"

#define NUM_Logo  16
#define D_LOGO_ID 0
#ifndef D_LOAD_LOGO_TO_MEM
/** @brief 得到指定logo  信息
* @param logo_id 需要得到信息的Logo ID
* @param logo_info 得到信息
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result
d_nvpart_get_logo_info(D_ID logo_id, D_LogoPartInfo *logo_info)
{
	D_Int		i;
	D_HNVPart		hnvp;
	D_HNVRam		hnvram;
	D_NVDev			*dev;
	D_NVRamAttr  attr;
	D_NVPartInfo info;
	D_LogoPartInfo logo_tables[NUM_Logo];
	D_Size offset = 0;

	dev = get_nv (D_LOGO_ID);
	hnvram = dev->hnv;
	d_nvram_get_attr(hnvram, &attr);
	
	hnvp = d_nvpart_create(D_LOGO_ID, D_NV_PART_LOGO);
	
	if (hnvp == D_INVALID_HANDLE) {
		#ifdef D_DEBUG
		D_DUMP ("Cannot get part D_NV_PART_LOGO");
		#endif
		return D_ERR;
	}
	d_nvpart_get_info (hnvp, &info);
	
	for(i = 0; i<NUM_Logo; i++)	{
		
		d_nvpart_read(hnvp, offset, (D_U8*)&logo_tables[i], sizeof(D_LogoPartInfo));
		
/*		printf("table[%d]>> id:%d, type:%d, add:0x%x, size:%d\n",
			i, logo_tables[i].id, logo_tables[i].type, logo_tables[i].address, logo_tables[i].size);*/
		
		offset += sizeof (D_LogoPartInfo);
	}
	
	d_nvpart_destroy (hnvp);


	for (i=0; i<NUM_Logo; i++){
		if ( logo_id ==  logo_tables[i].id ) {
			logo_info->id = logo_tables[i].id;
			logo_info->type = logo_tables[i].type;
			logo_info->address= logo_tables[i].address + info.nv_offset + attr.address;
			logo_info->size = logo_tables[i].size;
			return D_OK;
		}
		
	}
	return D_ERR;
}
#else
/** @brief 得到指定logo  信息
* @param logo_id 需要得到信息的Logo ID
* @param logo_info 得到信息
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result
d_nvpart_get_logo_info(D_ID logo_id, D_LogoPartInfo *logo_info)
{
	D_Int		i;
	D_HNVPart		hnvp;
	D_HNVRam		hnvram;
	D_NVDev			*dev;
	D_NVRamAttr  attr;
	D_NVPartInfo info;
	D_LogoPartInfo *logo_tables;
	D_Size offset = 0;
	
	static D_Bool loaded;
	static D_U8  *buf;
	
	if (loaded && ! buf)
		return D_ERR;
	
	if (! loaded) {
		/*Load data to memory*/
		dev = get_nv (D_LOGO_ID);
		hnvram = dev->hnv;
		d_nvram_get_attr(hnvram, &attr);
		
		hnvp = d_nvpart_create(D_LOGO_ID, D_NV_PART_LOGO);
		
		if (hnvp == D_INVALID_HANDLE) {
			D_DUMP ("Cannot get part D_NV_PART_LOGO");
			return D_ERR;
		}
		
		d_nvpart_get_info (hnvp, &info);
		
		buf = d_mem_alloc (0, info.data_size);
		if (! buf) {
			D_DUMP ("Cannot allocate memory for logo.");
			d_nvpart_destroy (hnvp);
			return D_ERR;
		}
		
		d_nvpart_read(hnvp, 0, buf, info.data_size);
		loaded = D_TRUE;
		d_sys_cache_flush ();
	}
	
	/*Search in the logo table*/
	logo_tables = (D_LogoPartInfo*) buf;
	
	for (i=0; i<NUM_Logo; i++){
		if ( logo_id ==  logo_tables[i].id ) {
			logo_info->id = logo_tables[i].id;
			logo_info->type = logo_tables[i].type;
			logo_info->address= (D_U32)buf + logo_tables[i].address;
			logo_info->size = logo_tables[i].size;
			return D_OK;
		}
		
	}
	return D_ERR;
}
#endif

#define D_AD_ID 0

/** @brief 得到指定广告图片 信息
* @param ad_id 需要得到信息的Logo ID
* @param ad_info 得到信息
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result
d_nvpart_get_advertise_file_info(D_ID ad_id, D_ADPartInfo *ad_info)D_FUNCPOSTFIT
{
	D_Int		i;
	D_HNVPart		hnvp;
	D_HNVRam		hnvram;
	D_NVDev			*dev;
	D_NVRamAttr  attr;
	D_NVPartInfo info;
	D_ADPartInfo ad_tables[NUM_AD];
	D_Size readlen;
	

	dev = get_nv (D_AD_ID);
	hnvram = dev->hnv;
	d_nvram_get_attr(hnvram, &attr);
	
	hnvp = d_nvpart_create(D_LOGO_ID, D_NV_PART_ADVERTISE);
	
	if (hnvp == D_INVALID_HANDLE) {
		D_DUMP ("Cannot get part D_NV_PART_ADVERTISE");
		return D_ERR;
	}

	if(D_FALSE == d_nvpart_is_available(hnvp, NULL, NULL))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}

	readlen = NUM_AD * sizeof(D_ADPartInfo);
	d_nvpart_get_info (hnvp, &info);		
	if(readlen != d_nvpart_read(hnvp, 0, (D_U8*)&ad_tables[0], readlen))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	d_nvpart_destroy (hnvp);

	
	for (i=0; i<NUM_AD; i++){
		if ( ad_id ==  ad_tables[i].id  && ad_tables[i].size != 0) {
			ad_info->id = ad_tables[i].id;
			ad_info->adtype = ad_tables[i].adtype;
			ad_info->filetype = ad_tables[i].filetype;
			ad_info->pos_x = ad_tables[i].pos_x;
			ad_info->pos_y = ad_tables[i].pos_y;	
			ad_info->width = ad_tables[i].width;
			ad_info->heigth = ad_tables[i].heigth;
			ad_info->duration_time = ad_tables[i].duration_time;
			ad_info->address= ad_tables[i].address + info.nv_offset + attr.address;
			ad_info->size = ad_tables[i].size;

			//目前只用于开机广告与音频广告，相关参数固定
			if(ad_tables[i].adtype == D_AD_TYPE_BOOTLOGO || ad_tables[i].adtype == D_AD_TYPE_AUDIOBG)
			{
				if(ad_tables[i].filetype == 0 && ad_tables[i].pos_x == 0 && ad_tables[i].pos_y == 0)
				/*&& ad_tables[i].width == 720 && ad_tables[i].heigth == 576*/
			return D_OK;
		}
		}
		
	}
	return D_ERR;
}

/** @brief 得到全部广告文件 信息表
* @param ad_info 信息表数组
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_nvpart_get_advertise_table_info(D_ADPartInfo ad_info[NUM_AD])D_FUNCPOSTFIT
{
	D_HNVPart		hnvp;
	D_HNVRam		hnvram;
	D_NVDev			*dev;
	D_NVRamAttr  attr;
	//D_NVPartInfo info;
	D_Size readlen;
	

	dev = get_nv (D_AD_ID);
	hnvram = dev->hnv;
	d_nvram_get_attr(hnvram, &attr);
	
	hnvp = d_nvpart_create(D_LOGO_ID, D_NV_PART_ADVERTISE);
	
	if (hnvp == D_INVALID_HANDLE) {
		D_DUMP ("Cannot get part D_NV_PART_ADVERTISE");
		return D_ERR;
	}

	if(D_FALSE == d_nvpart_is_available(hnvp, NULL, NULL))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	
	readlen = NUM_AD * sizeof(D_ADPartInfo);
	//d_nvpart_get_info (hnvp, &info);		
	if(readlen != d_nvpart_read(hnvp, 0, (D_U8*)&ad_info[0], readlen))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	d_nvpart_destroy (hnvp);

	return D_OK;

}

/** @brief 得到指定广告类型的广告文件 信息表
* @param adtype 广告类型
* @param ad_info 信息表数组
* @param filenum 此类型广告文件的数量
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_nvpart_get_advertise_tables_info_by_type(D_AdType adtype, D_ADPartInfo ad_info[NUM_AD], D_U8 *filenum)D_FUNCPOSTFIT
{
	D_U8 idx, i = 0 ;
	D_ADPartInfo ad_tables[NUM_AD];
	
	if(ad_info == NULL || filenum == NULL)
		return D_ERR;
	
	*filenum = 0;

		
	if(D_ERR == d_nvpart_get_advertise_table_info(ad_tables))
		return D_ERR;

	for(idx = 0; idx < NUM_AD; idx++)
	{
		if(ad_tables[idx].adtype == adtype)
			ad_info[i++] = ad_tables[idx];
	}

	*filenum = i;

	return D_OK;
}
/** @brief 得到指定广告图片数据
* @param id 需要得到数据的文件id
* @param buf 存储文件数据的缓冲区
* @param size 缓冲区大小
* @return 成功返回文件长度，失败返回D_ERR
*/
D_Size d_nvpart_load_advertise_file(D_U8 id,D_U8 *buf,D_Size size)D_FUNCPOSTFIT
{
	D_HNVPart				hnvp;
	D_ADPartInfo 	info[NUM_AD];
	D_U8             i;
	//D_Size offset = 0;
	D_Size readlen;
	
	hnvp = d_nvpart_create(D_AD_ID, D_NV_PART_ADVERTISE);
	
	if (hnvp == D_INVALID_HANDLE) {
		#ifdef D_DEBUG
		D_DUMP ("Cannot get part D_NV_PART_ADVERTISE");
		#endif
		return D_ERR;
	}
	
	if(D_FALSE == d_nvpart_is_available(hnvp, NULL, NULL))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	
	/*读取头信息*/	
	readlen = NUM_AD * sizeof(D_ADPartInfo);
	
	if(readlen != d_nvpart_read(hnvp, 0, (D_U8*)&info[0], readlen))
	{
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}	
	
	for(i=0;i<NUM_AD;i++)
	{		
		if(info[i].id == id)
			break;
	}
	
	if(i == NUM_AD){
		#ifdef D_DEBUG
		D_DUMP("Cannot find ad info by id:%d\n",id);
		#endif
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	
	readlen = info[i].size;
	if(readlen%2 == 1)readlen++;
	if(readlen > size)
	{
		#ifdef D_DEBUG
		D_DUMP("Buffer size is too small");
		#endif
		d_nvpart_destroy (hnvp);
		return D_ERR;
	}
	
	if( d_nvpart_read(hnvp,info[i].address,buf,readlen) != readlen){
		#ifdef D_DEBUG
		D_DUMP("Error in Loading ad file id:%d\n", id);		
		#endif
		d_nvpart_destroy (hnvp);	
		return D_ERR;
	}
	d_nvpart_destroy (hnvp);	
	
	return info[i].size;
}

/** @brief 保存单个广告图片数据,别的文件数据不变*/
D_Result d_nvpart_save_one_advertise_file(D_ADPartInfo ad_info) D_FUNCPOSTFIT
{
	D_HNVPart				hnvp;

	D_ADPartInfo 	ad_tables[NUM_AD] = {0xff};
	D_NVPartInfo 		info;
	D_Size offset = 0;
	D_Size head_size = 0;
	D_Size total_size = 0;
	D_S8            allocated_id=-1;
	D_U8            *cache;
	D_U8             *idx;
	D_ADPartInfo  *ptr;
	D_U8             i;
	
	if(ad_info.size%2 == 1)
{
		//保证文件数据都为双数字节的，
		//即保证文件数据在flash里的起始地址是双字节对齐的。
		ad_info.size += 1 ;
	}
	
	hnvp = d_nvpart_create(D_AD_ID, D_NV_PART_ADVERTISE);
	
	if (hnvp == D_INVALID_HANDLE) {
		#ifdef D_DEBUG
		D_DUMP ("Cannot get part D_NV_PART_ADVERTISE");
		#endif
		return D_ERR;
	}
	
	d_nvpart_get_info (hnvp, &info);

	/*分配整个D_NV_PART_LOGO分区大小*/
	cache = (D_U8*)d_mem_alloc(0,info.nv_size);
	
	if(cache == NULL){
		D_ERROR("Insufficient Memory");
		d_nvpart_destroy (hnvp);	
		return D_ERR;
	}

	memset(cache, 0x0, info.nv_size);
	
	/*预留头信息长度*/
	head_size = NUM_AD*sizeof(D_ADPartInfo) ;
	idx = cache+head_size;
	
	/*处理每个logo结构体*/
	for(i=0;i<NUM_AD;i++){
		ptr = &ad_tables[i];
		d_nvpart_read(hnvp, offset, (D_U8*)ptr, sizeof(D_ADPartInfo));
		offset += sizeof (D_ADPartInfo);
		
		/*未分配的id 初始值都为-1*/
		if(ptr->id != (D_U32)-1){
			if( (ptr->id == ad_info.id)){
				/*更新此logo结构信息*/

				ptr->id      = ad_info.id;
				ptr->adtype = ad_info.adtype;
				ptr->filetype = ad_info.filetype;
				ptr->pos_x = ad_info.pos_x;
				ptr->pos_y = ad_info.pos_y;	
				ptr->width = ad_info.width;
				ptr->heigth = ad_info.heigth;
				ptr->duration_time = ad_info.duration_time;	
				ptr->size    = ad_info.size;
				ptr->address = idx-cache;
				
				memcpy(idx,(void*)ad_info.address,ad_info.size);
				idx += ad_info.size;
				
				/*NUM_Logo表示已经找到匹配id的广告图片*/
				allocated_id = NUM_AD;
			}
			else{
				d_nvpart_read(hnvp,ptr->address,idx,ptr->size);
				ptr->address = idx-cache;
				idx += ptr->size;
			}
		}
		else{
			
			if(allocated_id == -1){
				/*分配一个最小的闲置的id号*/
				allocated_id=i;
			}
		}
	}
	
	total_size = idx - cache;
	
	/*仍然没有分配，表示id已经全部占用*/
	if(allocated_id == -1){
		#ifdef D_DEBUG
		D_DUMP("advertise partition is full:%d\n",NUM_AD);
		#endif
		d_mem_free(cache);
		d_nvpart_destroy (hnvp);	
		return D_ERR;
	}else if(allocated_id != NUM_AD){
	
		/*空间不足以存放此logo*/
		if ( (info.nv_size - total_size)<ad_info.size){
			D_ERROR("Data overflows in adding new advertise file\n");
			d_mem_free(cache);
			d_nvpart_destroy (hnvp);	
			return D_ERR;
		}
		
		ptr = &ad_tables[allocated_id];
		
		ptr->id      = ad_info.id;
		ptr->adtype = ad_info.adtype;
		ptr->filetype = ad_info.filetype;
		ptr->pos_x = ad_info.pos_x;
		ptr->pos_y = ad_info.pos_y;	
		ptr->width = ad_info.width;
		ptr->heigth = ad_info.heigth;
		ptr->duration_time = ad_info.duration_time;	
		ptr->size    = ad_info.size;
		ptr->address = idx-cache;

			
		memcpy(idx,(void*)ad_info.address,ad_info.size);
		idx += ad_info.size;
		total_size = idx - cache;
	}
	
	/*FLASH写入需要2字节对齐*/
	if(total_size % 2 != 0) total_size++;
	
	if( total_size > info.nv_size){
		D_ERROR("Data overflows in advertise partition\n");
		d_mem_free(cache);
		d_nvpart_destroy (hnvp);	
		return D_ERR;
	}

	/*将头信息写入到cache*/
	memcpy(cache,&ad_tables[0],head_size);

	if(d_nvpart_erase(hnvp) != D_ERR){
		d_nvpart_write(hnvp,0,cache,total_size);
	}else{
		D_ERROR("Cannot erase FLASH device: advertise data partition\n");
	}
	d_mem_free(cache);
	d_nvpart_write_tail(hnvp);
	d_nvpart_destroy(hnvp);
		
	
	return D_OK;
}
/** @brief 保存多个广告图片数据*/
D_Result d_nvpart_save_advertise_files(D_ADPartInfo ad_info[], D_U8 save_file_num) D_FUNCPOSTFIT
{
	D_HNVPart				hnvp;

	D_ADPartInfo 	ad_tables[NUM_AD] = {0xff};
	D_NVPartInfo 		info;
	D_Size head_size = 0;
	D_Size total_size = 0;
	D_U8            *cache;
	D_U8             *idx;
	D_U8             i;

	if(save_file_num > NUM_AD)
		save_file_num = NUM_AD;
	
	hnvp = d_nvpart_create(D_AD_ID, D_NV_PART_ADVERTISE);
	
	if (hnvp == D_INVALID_HANDLE) {
		#ifdef D_DEBUG
		D_DUMP ("Cannot get part D_NV_PART_ADVERTISE");
		#endif
		return D_ERR;
	}
	
	d_nvpart_get_info (hnvp, &info);

	/*分配整个D_NV_PART_LOGO分区大小*/
	cache = (D_U8*)d_mem_alloc(0,info.nv_size);
	
	if(cache == NULL){
		D_ERROR("Insufficient Memory");
		d_nvpart_destroy (hnvp);	
		return D_ERR;
}

	memset(cache, 0x0, info.nv_size);
	
	/*预留头信息长度*/
	head_size = NUM_AD*sizeof(D_ADPartInfo) ;
	idx = cache+head_size;	
	total_size = head_size;
	
	for(i = 0; i < save_file_num; i++)
	{
		if(ad_info[i].size%2 == 1)
{
			//保证文件数据都为双数字节的，
			//即保证文件数据在flash里的起始地址是双字节对齐的。
			ad_info[i].size += 1 ;
		}
		
		total_size += ad_info[i].size;
		if(total_size > info.nv_size)
			break;
		//复制文件数据

		ad_tables[i] = ad_info[i];
		ad_tables[i].address = idx - cache;
		memcpy(idx,(void*)ad_info[i].address,ad_info[i].size);
		idx += ad_info[i].size;	
	}
		
	memcpy(cache,(void*)(&ad_tables[0]), head_size);
	
	total_size = idx - cache;
	
	/*FLASH写入需要2字节对齐*/
	if(total_size % 2 != 0) total_size++;
	
	if( total_size > info.nv_size){
		D_ERROR("Data overflows in advertise partition\n");
		d_mem_free(cache);
		d_nvpart_destroy (hnvp);	
		return D_ERR;
	}
	
	if(d_nvpart_erase(hnvp) != D_ERR){
		d_nvpart_write(hnvp, 0, cache, total_size);
	}else{
		D_ERROR("Cannot erase FLASH device: advertise data partition\n");
	}
	d_mem_free(cache);
	d_nvpart_write_tail(hnvp);
	d_nvpart_destroy(hnvp);
		
	return D_OK;	

}

