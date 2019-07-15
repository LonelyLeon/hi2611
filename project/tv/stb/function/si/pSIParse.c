/** @file
* @brief SI私有表、私有描述符分析模块
* @author 覃宜
* @date 2013-08-30 覃宜: 建立文件
*/
#include "dConvCode.h"
#include "dMem.h"
#include "dDebug.h"
#include "dCBMan.h"
#include "pSIParse.h"
#include <string.h>

static D_Handle si_hcbm = D_INVALID_HANDLE;



/** @brief 分析一个字符串
* @param src	输入缓冲区地址
* @param len 	输入缓冲区的大小
* @param hmm	内存管理器句柄
* @return 成功返回字符串指针,失败返回NULL
*/
static D_Char*
si_parse_text (D_U8 *src, D_Size len, D_HMMan hmm) D_FUNCPOSTFIT
{
	D_Char	*str = NULL;
	D_Char	*tmp;
	D_Int		 i;

	if (! src || ! len)
		return NULL;

	if (src[0] == 0x05 || (src[0] >= 0x20))
	{
		str = (D_Char*) d_mman_alloc (hmm, len + 1);
		if (! str)
			return NULL;

		tmp = str;
		for (i = 0; i < len; i++)
		{
			if (*src == 0) break;
#if 0
			if ((*src >= ' ' && *src <= '~') ||
					(*src >= 0xa0))
				*tmp++ = *src++;
			else src++;
#else
			*tmp++ = *src++; /* 不要跳过不能识别的编码, 否则可能导致后面的字符编码都是错误的 */
#endif
		}
		*tmp = '\0';
	}
	else if (src[0] == 0x11)
	{
		/*UTF-16*/
#ifdef D_SI_SUPPORT_UNICODE
        D_Size   glen, ulen, ret, temp;
        D_U8 now1, now2;
        D_U16 tempunicode;

        len --;
        src ++;

        glen = len;
        ulen = len;

        str = (D_Char*) d_mman_alloc (hmm, glen + 1);
        if (! str)
            return NULL;
        tmp = str;

        ret = 0;
        while ((glen > 0) && (ulen > 1))
        {
            now1 = (*(D_U8  *)(D_U32)(src++));
            now2 = (*(D_U8  *)(D_U32)(src++));
            tempunicode = ((D_U16)now1 << 8) + (D_U16)now2;
            temp = d_cc_utf16_to_sys ((D_U8*)tmp, glen, (D_U8*)&tempunicode, 2);
            tmp += temp;
            ret += temp;
            glen -= temp;
            ulen -= 2;
        }
        if (ret >= 0)
        {
            str[ret] = 0;
        }
        else
        {
            d_mman_free (hmm, str);
            str = NULL;
        }
#endif
	}
	else
	{
		/*GB2312*/
		str = (D_Char*) d_mman_alloc (hmm, len);
		if (! str)
			return NULL;

		src ++;
		len --;
		memcpy (str, src, len);
		str[len] = 0;
	}

	return str;
}

/** @brief 获取一段字节数据
* @param src	输入缓冲区地址
* @param len 	输入缓冲区的大小
* @param hmm	内存管理器句柄
* @return 成功返回数据指针,失败返回NULL
*/
static D_U8*
si_get_bytes (D_U8 *src, D_Size len, D_HMMan hmm) D_FUNCPOSTFIT
{
	D_U8	*str = NULL;	

	if (! src || ! len)
		return NULL;	

	str = (D_U8*) d_mman_alloc (hmm, len);
	if (! str)
		return NULL;	

	memcpy (str, src, len);	
	return str;
}





/** @brief 分析一个私有描述符
* @param buf	缓冲区地址
* @param hmm	内存管理器句柄
* @return	成功返回描述符指针,失败返回NULL
*/
static void
p_si_parse_descr (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
	D_SIParseHookPre *HookPre = (D_SIParseHookPre *)obj_data;
	D_U8 *buf;
	D_HMMan hmm;
	D_U8		 tag;
	D_List	*dds = NULL;
	D_U16		 len;
	D_Result ret = D_ERR;


	if (! HookPre || !HookPre->buf)
		return ;

	hmm = HookPre->hmm;
	buf = HookPre->buf;


	tag = buf[0];
	len = buf[1] + 2;

	switch (tag)
	{
		case P_DESCR_LOADER_TAG:   			
			{
				D_Loader_Descr		*dLoader_Descriptor;
				D_Loader				*dLoader_List;
				D_U16		 		des_len;

				if (len < 31)
				{
					D_ERROR ("Descriptor length error\n");
					break;
				}

				D_SI_ALLOC (hmm, dLoader_List);

				if (dLoader_List)
				{
					D_SI_LIST_ADD (dds, dLoader_List);

					dLoader_List->tag = buf[0];
					dLoader_List->manufacturer_code = D_SI_HILO(buf[2], buf[3]);
					dLoader_List->loader_list = NULL;
					len -= 4; //NIT 升级描述子的总长度
					buf += 4; //指针向下指4个位置到d_si_parse_descr里

					while( len > 26 )
					{
					       /*判断是否是卫星、有线、地面系统描述符，不是则数据有误*/
						if(buf[0] != DESCR_SAT_DEL_SYS && buf[0] != DESCR_CABLE_DEL_SYS && buf[0] != DESCR_TERR_DEL_SYS)
						{
							break;
						}

						D_SI_ALLOC(hmm, dLoader_Descriptor);

						if( !dLoader_Descriptor )
							break;

						dLoader_Descriptor->delivery = (D_Descr*)d_si_parse_descr(buf, hmm);
						des_len = buf[1] +  2; //d_si_parse_descr描述的总长度,13byte

						dLoader_Descriptor->download_table_id = buf[des_len];	
						dLoader_Descriptor->download_pid = (((buf[des_len + 1]<<8)|(buf[des_len + 2]))&0xfff8)>>3;
						dLoader_Descriptor->upgrade_mode = ((buf[des_len + 1]<<8)|(buf[des_len + 2]))&0x7;
						dLoader_Descriptor->hardware_version = (buf[des_len + 4]<<24)|(buf[des_len + 5]<<16)|(buf[des_len + 6]<<8)|(buf[des_len + 7]);
						dLoader_Descriptor->software_version = (buf[des_len + 8]<<24)|(buf[des_len + 9]<<16)|(buf[des_len + 10]<<8)|(buf[des_len + 11]);

						D_SI_LIST_ADD(dLoader_List->loader_list, dLoader_Descriptor);

						des_len += buf[des_len + 12] + 12 + 2; //nit 升级描述的总长度

						len = len - des_len;
						buf = buf + des_len; //指针+ 总长度的偏移，如果有另外一张nit描述用
					}

					ret = D_OK;
				}
			}                 
			break;
#ifdef D_CA_SUPPORT_XGCA                
		case DESCR_CDXG_SERVICE_UPDATE:
			/*成都新光节目更新描述符*/
			{
				D_CDXGDescr *cdxg;

				if (len < CDXG_DESCR_LEN)
				{
					D_ERROR ("Descriptor length error\n");
					break;
				}

				D_SI_ALLOC (hmm, cdxg);

				if (cdxg)
				{
					D_SI_LIST_ADD (dds, cdxg);
					cdxg->tag = DESCR_CDXG_SERVICE_UPDATE;
					cdxg->update_flag = buf[2];
					cdxg->version_number = buf[3];
					cdxg->fm_pid =  D_SI_HILO(buf[4], buf[5]);
				}
			}
			break;
#endif  
#ifdef D_CA_SUPPORT_CDCA
		case P_YONGXIN_DESCR_LOADER_TAG:
			{
				D_Loader_Descr		*dLoader_Descriptor;
				D_Loader				*dLoader_List;
				D_U16		 		des_len;

				if (len < 6)
				{
					D_ERROR ("Descriptor length error\n");
					break;
				}

				D_SI_ALLOC (hmm, dLoader_List);

				if (dLoader_List)
				{
					D_SI_LIST_ADD (dds, dLoader_List);

					dLoader_List->tag = buf[0];
					dLoader_List->manufacturer_code = D_SI_HILO(buf[2], buf[3]);
					dLoader_List->loader_list = NULL;
					len -= 4; //NIT 升级描述子的总长度
					buf += 4; //指针向下指4个位置到d_si_parse_descr里

					while( len > 0 )
					{
						D_SI_ALLOC(hmm, dLoader_Descriptor);

						if( !dLoader_Descriptor )
							break;

						dLoader_Descriptor->delivery = (D_Descr*)d_si_parse_descr(buf, hmm);
//20150427 add if for fix upgrade 
						if(dLoader_Descriptor->delivery->tag ==DESCR_TERR_DEL_SYS)
						{
                                                D_TerrestrialDeliverySystemDescr *tempfre =(D_TerrestrialDeliverySystemDescr *)dLoader_Descriptor->delivery;

                                                tempfre->freq = D_SI_BCD(buf[2])*1000000 +
                                                D_SI_BCD(buf[3])*10000 +
                                                D_SI_BCD(buf[4])*100+
                                                D_SI_BCD(buf[5])*1;
    
						}
						
						
						des_len = buf[1] +  2; //d_si_parse_descr描述的总长度

						dLoader_Descriptor->download_table_id = 0x83;	
						dLoader_Descriptor->download_pid = (((buf[des_len]<<8)|(buf[des_len + 1]))&0xfff8)>>3;
						dLoader_Descriptor->upgrade_mode = ((buf[des_len]<<8)|(buf[des_len + 1]))&0x7;
						dLoader_Descriptor->download_info_len = buf[des_len+2];
						dLoader_Descriptor->hardware_version = (buf[des_len + 3]<<24)|(buf[des_len + 4]<<16)|(buf[des_len + 5]<<8)|(buf[des_len + 6]);
						dLoader_Descriptor->software_version = (buf[des_len + 7]<<24)|(buf[des_len + 8]<<16)|(buf[des_len + 9]<<8)|(buf[des_len + 10]);
						dLoader_Descriptor->stb_sn_start = (buf[des_len + 11]<<24)|(buf[des_len + 12]<<16)|(buf[des_len + 13]<<8)|(buf[des_len + 14]);
						dLoader_Descriptor->stb_sn_end = (buf[des_len + 15]<<24)|(buf[des_len + 16]<<16)|(buf[des_len + 17]<<8)|(buf[des_len + 18]);
						D_SI_LIST_ADD(dLoader_List->loader_list, dLoader_Descriptor);

						des_len += buf[des_len + 2] + 3; //nit 升级描述的总长度

						len = len - des_len;
						buf = buf + des_len; //指针+ 总长度的偏移，如果有另外一张nit描述用
					}

					ret = D_OK;
				}			
			}
			break;
#endif
#ifdef D_CA_SUPPORT_DSCA
		case P_DESCR_ABV_LCN_TAG:
			/*联广视讯LCN 逻辑频道号描述符*/
			{
				D_LCNDescr *dLCN;
				D_U8	*ptr;				

				if (len < 3)
				{
					D_ERROR ("Descriptor length error\n");
					break;
				}
				ptr = buf + 2;
				len -= 2;

				while (len >= ABV_LCN_DESCR_BODY_LEN) 
				{
					dLCN = NULL;
					D_SI_ALLOC (hmm, dLCN);	
					if(dLCN)
					{
						D_SI_LIST_ADD (dds, dLCN);
						dLCN->tag = P_DESCR_ABV_LCN_TAG;
						dLCN->srv_id= D_SI_HILO(ptr[0], ptr[1]);
						dLCN->lcn= D_SI_HILO(D_SI_BIT(ptr[2], 6, 2), ptr[3]);	                                   
					}
					ptr += ABV_LCN_DESCR_BODY_LEN;
					len -= ABV_LCN_DESCR_BODY_LEN;					
				}
				ret = D_OK;
			} 
			break;
#endif
#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
        case P_DESCR_HAIER_PROGRAM_VERSION_TAG:
        {
            D_HrProgramVersionDescr *puDescr = NULL;
            D_U8    *ptr;

            if (len < 4)
            {
                D_ERROR ("Descriptor 0x%02x length error\n", tag);
                break;
            }
            ptr = buf + 2;
            len -= 2;

            D_SI_ALLOC (hmm, puDescr);
            if(puDescr)
            {
                D_SI_LIST_ADD (dds, puDescr);
                puDescr->tag = P_DESCR_HAIER_PROGRAM_VERSION_TAG;
                puDescr->force = ptr[0];
                puDescr->version = ptr[1];
                if(len > 2)
                {
                    puDescr->match = ptr[2];
                }
                if(len > 4)
                {
                    puDescr->match_code = D_SI_HILO(ptr[3], ptr[4]);
                }
                ret = D_OK;
            }
        }
        break;
#endif
		case P_DESCR_DSAD_TAG:
			/*德赛广告描述符*/
			{
				D_DSADDescr *dDSAD;
				D_U8	*ptr;				

				if (len < 3)
				{
					D_ERROR ("Descriptor length error\n");
					break;
				}
				ptr = buf + 2;
				len -= 2;

				if(len >= 2) 
				{
				    dDSAD = NULL;
					D_SI_ALLOC (hmm, dDSAD);	
					if(dDSAD)
					{
						D_SI_LIST_ADD (dds, dDSAD);
						dDSAD->tag = P_DESCR_DSAD_TAG;
						dDSAD->datapid= D_SI_HILO(ptr[0], ptr[1]);
					}
					ptr += 2;
					len -= 2;					
				}
				ret = D_OK;
			} 
			break;
			case P_DESCR_MGAD_TAG:
				/*三洲广告描述符*/
				{
					D_MGADDescr *MGAD;
					D_U8	*ptr;				
			
					if (len < 18)
					{
						D_ERROR ("Descriptor length error\n");
						break;
					}
					ptr = buf + 4;
					len -= 4;
			
					if(len >= 16) 
					{
						MGAD = NULL;
						D_SI_ALLOC (hmm, MGAD);	
						if(MGAD)
						{
							D_SI_LIST_ADD (dds, MGAD);
							MGAD->tag = P_DESCR_MGAD_TAG;
							MGAD->picpid= D_SI_HILO(ptr[0], ptr[1]);
							MGAD->txtpid= D_SI_HILO(ptr[4], ptr[5]);
							MGAD->corpid= D_SI_HILO(ptr[8], ptr[9]);
						}
						ptr += 16;
						len -= 16;					
					}
					ret = D_OK;
				} 
				break;

		default:
			break;
	}

	*(HookPre->ret) = ret;
	*(HookPre->dds) = dds;
}




/** @brief 打开si私有描述符解析功能(注册私有解析函数)
* @param 无
* @return 无
*/
void p_private_si_parse_open (void) D_FUNCPOSTFIT
{
    si_hcbm = d_cbman_subscribe(PL_SI_PARSE_DESC_PRE, D_INVALID_HANDLE, p_si_parse_descr, NULL);

}

/** @brief 关闭si私有描述符解析功能(反注册私有解析函数)
* @param 无
* @return 无
*/
void p_private_si_parse_close (void) D_FUNCPOSTFIT
{
    d_cbman_unsubscribe(si_hcbm);
}





/** @brief 分析XXX 表的一个section
* @param buf	缓冲区地址
* @param length	缓冲区大小
* @param hmm		内存管理器句柄,函数通过此句柄分配内存
* @return 成功返回PAT结构链表,失败返回NULL
*/
D_List*
p_si_parse_xxx (D_U8 *buf, D_S16 length, D_HMMan hmm) D_FUNCPOSTFIT
{
	D_U8	*ptr;
	D_S16	 len;
	D_Cat	*dcat;
	D_List	*dcats = NULL;

	if (! buf) {
#ifdef D_DEBUG
		D_ERROR ("Buffer is NULL\n");
#endif
		return NULL;
	}

	if (length < 3) {
#ifdef D_DEBUG
		D_ERROR ("Section size < 3 bytes\n");
#endif
		return dcats;
	}

	ptr = buf;
	len = D_SI_HILO (D_SI_BIT(ptr[1], 4, 4),ptr[2]) + 3 - 4;

	if ((len > length) || (len < CAT_LEN)) {
#ifdef D_DEBUG
		D_ERROR ("Sction length error\n");
#endif
		return dcats;
	}

	D_SI_ALLOC (hmm, dcat);
	if (! dcat) {
#ifdef D_DEBUG
		D_ERROR ("Cannot allocate memory\n");
#endif
		return dcats;
	}

	D_SI_LIST_ADD (dcats, dcat);

#if D_SI_RECORD_SEC_INFO
	dcat->tab_id = ptr[0];
	dcat->version = D_SI_BIT(ptr[5], 2, 5);
	dcat->sec_num = ptr[6];
	dcat->last_sec_num = ptr[7];
#endif

	/*分析描述符*/
	ptr += CAT_LEN;
	len -= CAT_LEN;

	if (len > 0) {
		dcat->descrs = d_si_parse_descrs (ptr, len, hmm);
	}

	return dcats;
}









