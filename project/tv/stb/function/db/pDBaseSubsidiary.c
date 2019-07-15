/**@defgroup db 数据库定制应用
*@{*/
/** @file
* @brief 数据库一些辅助功能函数
* @author 刘伟峰
* @date 2013-04-25 刘伟峰: 建立文件
*/

#include <ctype.h>
#include <string.h>
#include "dVarString.h"
#include "pMem.h"
#include "dMMan.h"
#include "dDBase.h"
#include "dDebug.h"
#include "dSys.h"
#include "pDBaseDefault.h"

/** @brief 字母不分大小写进行比较 
* @param[in] str1 字符串1
* @param[in] str2 字符串2
* @retval 0 相等
* @retval 1 str1大于str2
* @retval -1 str1小于str2
*/
static D_Result
d_dbase_strcmp(D_Char* str1, D_Char* str2)
{
	if((str1 == NULL)||(str2 == NULL))
	{
		return 0;
	}
	for(; str1[0] != 0; ++str1, ++str2)
	{
		if(toupper(str1[0]) > toupper(str2[0]))
		{
			return 1;
		}
		else if(toupper(str1[0]) < toupper(str2[0]))
		{
			return -1;
		}
	}
	return 0;
}

/** @brief 判断节目名是否为阿拉伯文 
* @param[in] str 字符串
* @retval 0 English
* @retval 1 Arab
*/
static D_Result
d_dbase_judge_string_language( D_Char * str )
{
	if( (str[0] >= 0x87) && (str[0] <= 0x88) )
	{
		return 1;
	}
	else if( str[0] == ' ' )  
	{  
		D_U8 i = 0;    
		while( i < strlen(str) )   
		{   
			if((D_Char)str[i] != ' ')   
			{     
			   break;   
			}   
			i++;    
		}
		if( i == strlen(str) )
		{
			return 0;
		}
		else if( (str[i] >= 0x87) && (str[i] <= 0x88) )
		{
			return 1;
		}
	}
	    return 0;
}

/** @brief 按节目在表中的DID对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_did(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_S16 flag = 0;
	D_U16 did1 = 0, did2 = 0;
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			did1 = rset->ids[j];
			i = j - h;
			did2 = rset->ids[i];
			if(order == 0)	/*从小到大*/
			{
				flag = (did2 > did1);
			}
			else			/*从大到小*/
			{
				flag = (did2 < did1);
			}
			while((i >= 0)&&(flag != 0))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					did2 = rset->ids[i];
					if(order == 0)	/*从小到大*/
					{
						flag = (did2 > did1);
					}
					else			/*从大到小*/
					{
						flag = (did2 < did1);
					}
				}	
			}
		}
		h = h/2;
	}
	return D_OK;
}

/** @brief 按节目名称字母对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_letter(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_S16 flag = 0;
	D_DBSrvInfo info1, info2; 
	D_Char str1[D_DB_SERVICE_NAME_LEN + 1], str2[D_DB_SERVICE_NAME_LEN + 1];
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			ret = d_dbase_get_srv_info (rset->ids[j], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			strncpy(str1, (const char *)&(info1.name), D_DB_SERVICE_NAME_LEN);
			str1[D_DB_SERVICE_NAME_LEN] = 0;
			if( d_dbase_judge_string_language(info1.name) != 0)
			{
				str1[0] = (((order == 0)||(order == 2)) ? 0 : 128);
			}			
			i = j - h;
			ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
			if(ret == D_ERR)
			{
				return ret;
			}
			strncpy(str2, (const char *)&(info2.name), D_DB_SERVICE_NAME_LEN);
			str2[D_DB_SERVICE_NAME_LEN] = 0;
			if( d_dbase_judge_string_language(info2.name) != 0)
			{
				str2[0] = (((order == 0)||(order == 2)) ? 0 : 128);
			}			
			if(order == 0 )
			{
				flag = d_dbase_strcmp( str2, str1 );
			}
			else if(order == 1)
			{
				flag = d_dbase_strcmp( str1, str2 );			
			}
			else if(order == 2)
			{
				flag = strcmp( str2, str1 );
			}
			else 
			{
				flag = strcmp( str1, str2 );			
			}
			while((i >= 0)&&(flag > 0))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
					if(ret == D_ERR)
					{
						return ret;
					}
					strncpy(str2, (const char *)&(info2.name), D_DB_SERVICE_NAME_LEN);
					str2[D_DB_SERVICE_NAME_LEN] = 0;
					if( d_dbase_judge_string_language(info2.name) != 0)
					{
						str2[0] = (((order == 0)||(order == 2)) ? 0 : 128);
					}			
					if(order == 0 )
					{
						flag = d_dbase_strcmp( str2, str1 );
					}
					else if(order == 1)
					{
						flag = d_dbase_strcmp( str1, str2 );			
					}
					else if(order == 2)
					{
						flag = strcmp( str2, str1 );
					}
					else 
					{
						flag = strcmp( str1, str2 );			
					}
				}
			}
		}
		h = h/2;
	}
	return ret;
}

/** @brief 按service id对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_service_id(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_Bool flag = 0;
	D_DBSrvInfo info1, info2; 
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			ret = d_dbase_get_srv_info (rset->ids[j], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			i = j - h;
			ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
			if(ret == D_ERR)
			{
				return ret;
			}
			if(order == 0)	/*从小到大*/
			{
				flag = (info2.srv_id > info1.srv_id);
			}
			else			/*从大到小*/
			{
				flag = (info2.srv_id < info1.srv_id);
			}
			while((i >= 0)&&(flag))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
					if(ret == D_ERR)
					{
						return ret;
					}
					if(order == 0)	/*从小到大*/
					{
						flag = (info2.srv_id > info1.srv_id);
					}
					else			/*从大到小*/
					{
						flag = (info2.srv_id < info1.srv_id);
					}
				}
			}
		}
		h = h/2;
	}
	return ret;
}

/** @brief 按逻辑频道号对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_logic_num(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_Bool flag = 0;
	D_DBSrvInfo info1, info2; 
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			ret = d_dbase_get_srv_info (rset->ids[j], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			i = j - h;
			ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
			if(ret == D_ERR)
			{
				return ret;
			}
			if(order == 0)	/*从小到大*/
			{
				flag = (info2.chan_num > info1.chan_num);
			}
			else			/*从大到小*/
			{
				flag = (info2.chan_num < info1.chan_num);
			}
			while((i >= 0)&&(flag))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
					if(ret == D_ERR)
					{
						return ret;
					}
					if(order == 0)	/*从小到大*/
					{
						flag = (info2.chan_num > info1.chan_num);
					}
					else			/*从大到小*/
					{
						flag = (info2.chan_num < info1.chan_num);
					}
				}
			}
		}
		h = h/2;
	}
	return ret;
}

/** @brief 按TS频点对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_ts(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_Bool flag = 0;
	D_DBSrvInfo info1, info2; 
	D_DBTSInfo tsinfo1, tsinfo2;
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			ret = d_dbase_get_srv_info (rset->ids[j], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_ts_info(info1.db_ts_id, &tsinfo1);
			if(ret == D_ERR)
			{
				return ret;
			}
			i = j - h;
			ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_ts_info(info2.db_ts_id, &tsinfo2);
			if(ret == D_ERR)
			{
				return ret;
			}					
			if(order == 0)	/*从小到大*/
			{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
				flag = (tsinfo2.param.dvbs.freq > tsinfo1.param.dvbs.freq);
#else
				flag = (tsinfo2.param.dtmb.freq > tsinfo1.param.dtmb.freq);
#endif
			}
			else			/*从大到小*/
			{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
				flag = (tsinfo2.param.dvbs.freq < tsinfo1.param.dvbs.freq);
#else
				flag = (tsinfo2.param.dtmb.freq < tsinfo1.param.dtmb.freq);
#endif
			}
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
			if(tsinfo2.param.dvbs.freq == tsinfo1.param.dvbs.freq)
			{
				if(order == 0)
				{
					flag = (info2.srv_id > info1.srv_id);
				}
				else
				{
					flag = (info2.srv_id < info1.srv_id);
				}
			}
#else
			if(tsinfo2.param.dtmb.freq == tsinfo1.param.dtmb.freq)
			{
				if(order == 0)
				{
					flag = (info2.srv_id > info1.srv_id);
				}
				else
				{
					flag = (info2.srv_id < info1.srv_id);
				}
			}
#endif
			while((i >= 0)&&(flag))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
					if(ret == D_ERR)
					{
						return ret;
					}
					ret = d_dbase_get_ts_info(info2.db_ts_id, &tsinfo2);
					if(ret == D_ERR)
					{
						return ret;
					}					
					if(order == 0)	/*从小到大*/
					{
#ifdef	P_DBASE_DVBS				/*关于abs的情况尚未做处理，应用时要注意*/
						flag = (tsinfo2.param.dvbs.freq > tsinfo1.param.dvbs.freq);
#else
						flag = (tsinfo2.param.dtmb.freq > tsinfo1.param.dtmb.freq);
#endif
					}
					else			/*从大到小*/
					{
#ifdef	P_DBASE_DVBS				/*关于abs的情况尚未做处理，应用时要注意*/
						flag = (tsinfo2.param.dvbs.freq < tsinfo1.param.dvbs.freq);
#else
						flag = (tsinfo2.param.dtmb.freq < tsinfo1.param.dtmb.freq);
#endif
					}
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
					if(tsinfo2.param.dvbs.freq == tsinfo1.param.dvbs.freq)
					{
						if(order == 0)
						{
							flag = (info2.srv_id > info1.srv_id);
						}
						else
						{
							flag = (info2.srv_id < info1.srv_id);
						}
					}
#else
					if(tsinfo2.param.dtmb.freq == tsinfo1.param.dtmb.freq)
					{
						if(order == 0)
						{
							flag = (info2.srv_id > info1.srv_id);
						}
						else
						{
							flag = (info2.srv_id < info1.srv_id);
						}
					}
#endif
				}
			}				
		}
		h = h/2;
	}
	return ret;
}

/** @brief 按卫星对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_sat(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_S32 h = 0;
	D_S32 i = 0, j = 0;
	D_U16 total = 0;
	D_U16 temp;
	D_Bool flag = 0;
	D_DBSrvInfo info1, info2; 
	D_DBTSInfo tsinfo1, tsinfo2;
	D_DBSateInfo satinfo1, satinfo2;
	
	total = rset->cnt;
	h = total/2;
	
	while(h > 0)
	{
		for(j = h; j < total; j++)
		{
			ret = d_dbase_get_srv_info (rset->ids[j], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_ts_info(info1.db_ts_id, &tsinfo1);
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_sat_info (tsinfo1.db_sat_id, &satinfo1);
			if(ret == D_ERR)
			{
				return ret;
			}
			i = j - h;
			ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_ts_info(info2.db_ts_id, &tsinfo2);
			if(ret == D_ERR)
			{
				return ret;
			}
			ret = d_dbase_get_sat_info (tsinfo2.db_sat_id, &satinfo2);
			if(ret == D_ERR)
			{
				return ret;
			}
			if(order == 0)	/*从小到大*/
			{
				flag = (satinfo2.sate_no > satinfo1.sate_no);
			}
			else			/*从大到小*/
			{
				flag = (satinfo2.sate_no < satinfo1.sate_no);
			}
			if(satinfo2.sate_no == satinfo1.sate_no)
			{
				if(order == 0)	/*从小到大*/
				{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
					flag = (tsinfo2.param.dvbs.freq > tsinfo1.param.dvbs.freq);
#else
					flag = (tsinfo2.param.dtmb.freq > tsinfo1.param.dtmb.freq);
#endif
				}
				else			/*从大到小*/
				{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
					flag = (tsinfo2.param.dvbs.freq < tsinfo1.param.dvbs.freq);
#else
					flag = (tsinfo2.param.dtmb.freq < tsinfo1.param.dtmb.freq);
#endif
				}
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
				if(tsinfo2.param.dvbs.freq == tsinfo1.param.dvbs.freq)
				{
					if(order == 0)
					{
						flag = (info2.srv_id > info1.srv_id);
					}
					else
					{
						flag = (info2.srv_id < info1.srv_id);
					}
				}
#else
				if(tsinfo2.param.dtmb.freq == tsinfo1.param.dtmb.freq)
				{
					if(order == 0)
					{
						flag = (info2.srv_id > info1.srv_id);
					}
					else
					{
						flag = (info2.srv_id < info1.srv_id);
					}
				}
#endif
			}
			while((i >= 0)&&(flag))
			{
				temp = rset->ids[i];
				rset->ids[i] = rset->ids[i + h];
				rset->ids[i + h] = temp;
				i = i - h;
				if(i >= 0)
				{
					ret = d_dbase_get_srv_info (rset->ids[i], &info2); 					
					if(ret == D_ERR)
					{
						return ret;
					}
					ret = d_dbase_get_ts_info(info2.db_ts_id, &tsinfo2);
					if(ret == D_ERR)
					{
						return ret;
					}
					ret = d_dbase_get_sat_info (tsinfo2.db_sat_id, &satinfo2);
					if(ret == D_ERR)
					{
						return ret;
					}
					if(order == 0)	/*从小到大*/
					{
						flag = (satinfo2.sate_no > satinfo1.sate_no);
					}
					else			/*从大到小*/
					{
						flag = (satinfo2.sate_no < satinfo1.sate_no);
					}
					if(satinfo2.sate_no == satinfo1.sate_no)
					{
						if(order == 0)	/*从小到大*/
						{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
							flag = (tsinfo2.param.dvbs.freq > tsinfo1.param.dvbs.freq);
#else
							flag = (tsinfo2.param.dtmb.freq > tsinfo1.param.dtmb.freq);
#endif
						}
						else			/*从大到小*/
						{
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
							flag = (tsinfo2.param.dvbs.freq < tsinfo1.param.dvbs.freq);
#else
							flag = (tsinfo2.param.dtmb.freq < tsinfo1.param.dtmb.freq);
#endif
						}
#ifdef	P_DBASE_DVBS		/*关于abs的情况尚未做处理，应用时要注意*/
						if(tsinfo2.param.dvbs.freq == tsinfo1.param.dvbs.freq)
						{
							if(order == 0)
							{
								flag = (info2.srv_id > info1.srv_id);
							}
							else
							{
								flag = (info2.srv_id < info1.srv_id);
							}
						}
#else
						if(tsinfo2.param.dtmb.freq == tsinfo1.param.dtmb.freq)
						{
							if(order == 0)
							{
								flag = (info2.srv_id > info1.srv_id);
							}
							else
							{
								flag = (info2.srv_id < info1.srv_id);
							}
						}
#endif
					}
				}
			}				
		}
		h = h/2;
	}
	return ret;
}

/** @brief 按加密标记对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_ca(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Int	i, j;
	D_ID	temp;
	D_DBSrvInfo info1, info2; 
	D_Result ret = D_OK;
	D_ID * buf = NULL;
	D_Int m = 0, n = 0;
	
	if ((! rset) || (rset->cnt < 1)) 
	{
		return D_ERR;
	}
#if 0 //规模较大时冒泡排序明显速度较慢，好处是不用额外申请较大内存。不采用此法，留作参考
	/*冒泡排序*/
	for (i = 0; i < rset->cnt - 1; i ++) 
	{
		if(order == 0)	/*从小到大*/
		{
			for(j = 0; j < rset->cnt - i - 1; j++)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j + 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.ca_flag == 0)&&(info1.ca_flag != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j + 1];
					rset->ids[j + 1] = temp;
				}
			}
		}
		else	/*从大到小*/
		{
			for(j = rset->cnt - 1; j > i; j--)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j - 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.ca_flag == 0)&&(info1.ca_flag != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j - 1];
					rset->ids[j - 1] = temp;
				}
			}
		}
	}
#else	//此种排序方法需额外申请内存，占用更多空间，好处是时间更快。	
	buf = (D_ID *)PROJECT_ALLOC(rset->cnt * sizeof(D_ID));
	if(buf == NULL)
	{
		return D_ERR;
	}
	n = rset->cnt - 1;
	if(order == 0)	/*从小到大*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.ca_flag != 0)
			{
				buf[n] = rset->ids[i];
				n--;
			}
			else
			{
				buf[m] = rset->ids[i];
				m++;
			}
		}
	}
	else	/*从大到小*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.ca_flag != 0)
			{
				buf[m] = rset->ids[i];
				m++;
			}
			else
			{
				buf[n] = rset->ids[i];
				n--;
			}
		}
	}
	for(i = (n + 1), j = rset->cnt - 1; i < j; i++, j-- )
	{
		temp = buf[i];
		buf[i] = buf[j];
		buf[j] = temp;
	}
	memcpy(rset->ids, buf, (rset->cnt * sizeof(D_ID)));
	PROJECT_FREE(buf);
#endif
	return D_OK;
}

/** @brief 按喜爱标记对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_fav(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Int	i, j;
	D_ID	temp;
	D_DBSrvInfo info1, info2; 
	D_Result ret = D_OK;
	D_ID * buf = NULL;
	D_Int m = 0, n = 0;

	if ((! rset) || (rset->cnt < 1)) 
	{
		return D_ERR;
	}
#if 0 //规模较大时冒泡排序明显速度较慢，好处是不用额外申请较大内存。不采用此法，留作参考
	/*冒泡排序*/
	for (i = 0; i < rset->cnt - 1; i ++) 
	{
		if(order == 1)	/*从小到大*/
		{
			for(j = 0; j < rset->cnt - i - 1; j++)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j + 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if(((info2.favor0 == 0 )&&(info1.favor0 != 0))||((info2.favor1 == 0 )&&(info1.favor1 != 0))||\
						((info2.favor2 == 0 )&&(info1.favor2 != 0))||((info2.favor3 == 0 )&&(info1.favor3 != 0))||\
						((info2.favor4 == 0 )&&(info1.favor4 != 0))||((info2.favor5 == 0 )&&(info1.favor5 != 0))||\
						((info2.favor6 == 0 )&&(info1.favor6 != 0))||((info2.favor7 == 0 )&&(info1.favor7 != 0)))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j + 1];
					rset->ids[j + 1] = temp;
				}
			}
		}
		else	/*从大到小*/
		{
			for(j = rset->cnt - 1; j > i; j--)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j - 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if(((info2.favor0 == 0 )&&(info1.favor0 != 0))||((info2.favor1 == 0 )&&(info1.favor1 != 0))||\
						((info2.favor2 == 0 )&&(info1.favor2 != 0))||((info2.favor3 == 0 )&&(info1.favor3 != 0))||\
						((info2.favor4 == 0 )&&(info1.favor4 != 0))||((info2.favor5 == 0 )&&(info1.favor5 != 0))||\
						((info2.favor6 == 0 )&&(info1.favor6 != 0))||((info2.favor7 == 0 )&&(info1.favor7 != 0)))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j - 1];
					rset->ids[j - 1] = temp;
				}
			}
		}
	}
#else	//此种排序方法需额外申请内存，占用更多空间，好处是时间更快。
	buf = (D_ID *)PROJECT_ALLOC(rset->cnt * sizeof(D_ID));
	if(buf == NULL)
	{
		return D_ERR;
	}
	n = rset->cnt - 1;
	if(order == 0)	/*从小到大*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if((info1.favor0 != 0)||(info1.favor1 != 0)||\
				(info1.favor2 != 0)||(info1.favor3 != 0)||\
				(info1.favor4 != 0)||(info1.favor5 != 0)||\
				(info1.favor6 != 0)||(info1.favor7 != 0))
			{
				buf[m] = rset->ids[i];
				m++;
			}
			else
			{
				buf[n] = rset->ids[i];
				n--;
			}
		}
	}
	else	/*从大到小*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if((info1.favor0 != 0)||(info1.favor1 != 0)||\
				(info1.favor2 != 0)||(info1.favor3 != 0)||\
				(info1.favor4 != 0)||(info1.favor5 != 0)||\
				(info1.favor6 != 0)||(info1.favor7 != 0))
			{
				buf[n] = rset->ids[i];
				n--;
			}
			else
			{
				buf[m] = rset->ids[i];
				m++;
			}
		}
	}
	for(i = (n + 1), j = rset->cnt - 1; i < j; i++, j-- )
	{
		temp = buf[i];
		buf[i] = buf[j];
		buf[j] = temp;
	}
	memcpy(rset->ids, buf, (rset->cnt * sizeof(D_ID)));
	PROJECT_FREE(buf);
#endif
	return D_OK;
}

/** @brief 按跳过标记对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_skip(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Int	i, j;
	D_ID	temp;
	D_DBSrvInfo info1, info2; 
	D_Result ret = D_OK;
	D_ID * buf = NULL;
	D_Int m = 0, n = 0;

	if ((! rset) || (rset->cnt < 1)) 
	{
		return D_ERR;
	}
#if 0//规模较大时冒泡排序明显速度较慢，好处是不用额外申请较大内存。不采用此法，留作参考
	/*冒泡排序*/
	for (i = 0; i < rset->cnt - 1; i ++) 
	{
		if(order == 0)	/*从小到大*/
		{
			for(j = 0; j < rset->cnt - i - 1; j++)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j + 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.skip == 0)&&(info1.skip != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j + 1];
					rset->ids[j + 1] = temp;
				}
			}
		}
		else	/*从大到小*/
		{
			for(j = rset->cnt - 1; j > i; j--)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j - 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.skip == 0)&&(info1.skip != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j - 1];
					rset->ids[j - 1] = temp;
				}
			}
		}
	}
#else	//此种排序方法需额外申请内存，占用更多空间，好处是时间更快。
	buf = (D_ID *)PROJECT_ALLOC(rset->cnt * sizeof(D_ID));
	if(buf == NULL)
	{
		return D_ERR;
	}
	n = rset->cnt - 1;
	if(order == 0)	/*从小到大*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.skip != 0)
			{
				buf[n] = rset->ids[i];
				n--;
			}
			else
			{
				buf[m] = rset->ids[i];
				m++;
			}
		}
	}
	else	/*从大到小*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.skip != 0)
			{
				buf[m] = rset->ids[i];
				m++;
			}
			else
			{
				buf[n] = rset->ids[i];
				n--;
			}
		}
	}
	for(i = (n + 1), j = rset->cnt - 1; i < j; i++, j-- )
	{
		temp = buf[i];
		buf[i] = buf[j];
		buf[j] = temp;
	}
	memcpy(rset->ids, buf, (rset->cnt * sizeof(D_ID)));
	PROJECT_FREE(buf);
#endif
	return D_OK;
}

/** @brief 按加锁标记对节目记录集进行排序
* @param[in] rset 需要进行排序的记录集
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
static D_Result
d_dbase_program_sort_by_lock(D_DBRecset *rset, D_Bool order) D_FUNCPOSTFIT
{
	D_Int	i, j;
	D_ID	temp;
	D_DBSrvInfo info1, info2; 
	D_Result ret = D_OK;
	D_ID * buf = NULL;
	D_Int m = 0, n = 0;

	if ((! rset) || (rset->cnt < 1)) 
	{
		return D_ERR;
	}
#if 0//规模较大时冒泡排序明显速度较慢，好处是不用额外申请较大内存。不采用此法，留作参考
	/*冒泡排序*/
	for (i = 0; i < rset->cnt - 1; i ++) 
	{
		if(order == 0)	/*从小到大*/
		{
			for(j = 0; j < rset->cnt - i - 1; j++)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j + 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.lock == 0)&&(info1.lock != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j + 1];
					rset->ids[j + 1] = temp;
				}
			}
		}
		else	/*从大到小*/
		{
			for(j = rset->cnt - 1; j > i; j--)
			{
				ret = d_dbase_get_srv_info(rset->ids[j], &info1); 
				if(ret == D_ERR)
				{
					return ret;
				}
				ret = d_dbase_get_srv_info(rset->ids[j - 1], &info2); 					
				if(ret == D_ERR)
				{
					return ret;
				}
				if((info2.lock == 0)&&(info1.lock != 0))
				{
					temp = rset->ids[j];
					rset->ids[j] = rset->ids[j - 1];
					rset->ids[j - 1] = temp;
				}
			}
		}
	}
#else	//此种排序方法需额外申请内存，占用更多空间，好处是时间更快。
	buf = (D_ID *)PROJECT_ALLOC(rset->cnt * sizeof(D_ID));
	if(buf == NULL)
	{
		return D_ERR;
	}
	n = rset->cnt - 1;
	if(order == 0)	/*从小到大*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.lock != 0)
			{
				buf[n] = rset->ids[i];
				n--;
			}
			else
			{
				buf[m] = rset->ids[i];
				m++;
			}
		}
	}
	else	/*从大到小*/
	{
		for(i = 0; i < rset->cnt; i++)
		{
			ret = d_dbase_get_srv_info(rset->ids[i], &info1); 
			if(ret == D_ERR)
			{
				return ret;
			}
			if(info1.lock != 0)
			{
				buf[m] = rset->ids[i];
				m++;
			}
			else
			{
				buf[n] = rset->ids[i];
				n--;
			}
		}
	}
	for(i = (n + 1), j = rset->cnt - 1; i < j; i++, j-- )
	{
		temp = buf[i];
		buf[i] = buf[j];
		buf[j] = temp;
	}
	memcpy(rset->ids, buf, (rset->cnt * sizeof(D_ID)));
	PROJECT_FREE(buf);
#endif
	return D_OK;
}

/** @brief 查找节目记录集中节目记录的频道号
* @param[in] rset 记录集
* @param[out] pos 存放频道号的缓冲区
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result
d_dbase_program_chnum_in_rset(D_DBRecset *rset, D_S16 *pos) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_U16 i = 0;
	D_DBSrvInfo info;
	for(i = 0; i < rset->cnt; i++)
	{
		ret = d_dbase_get_srv_info (rset->ids[i], &info);
		if(ret == D_ERR)
		{
			return ret;
		}
		pos[i] = info.chan_num;
	}
	return ret;
}

/** @brief 对节目记录进行按多方式进行排序 
* @param[in] rset 需要进行排序的记录集
* @param[in] type 排序方式
* @param[in] order 对一般的排序方式，order为0代表从小到大排序，为1代表从大到小排序；
			   对字母排序，0代表不区分大小写且从小到大，1代表不区分大小写且从大到小，2代表区分大小写且从小到大，3代表区分大小写且从大到小。
* @param[in] rearrange 排序后是否把节目号重置为从1开始。TRUE：是；FALSE：否。
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result
d_dbase_program_sort(D_DBRecset *rset, D_DBProgramArrayType type, D_U8 order, D_Bool rearrange) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_U16 i = 0;
	D_S16 *position = NULL;
	D_ID *old_ids = NULL;
	D_U32 t1 = 0, t2 = 0;
	
	position = (D_S16 *)PROJECT_ALLOC(rset->cnt * sizeof(D_S16));
	if(!position)
	{
		return D_ERR;	
	}
	old_ids = (D_ID *)PROJECT_ALLOC(rset->cnt * sizeof(D_ID));
	if(!old_ids)
	{
		return D_ERR;	
	}
	
	memset((void *)position, 0, (rset->cnt * sizeof(D_S16)));
	ret = d_dbase_program_chnum_in_rset(rset, position);	
	if(ret == D_ERR)
	{
		PROJECT_FREE(position);
		return ret;
	}
	memcpy((void *)old_ids, rset->ids, (rset->cnt * sizeof(D_ID)));
	t1 = d_sys_get_time();
	switch (type) 
	{
		case ONID_ARRAY:
			ret = d_dbase_program_sort_by_did(rset, order);
			break;
		case SERVICE_ID_ARRAY:
			ret = d_dbase_program_sort_by_service_id(rset, order);
			break;
		case TS_ARRAY:
			ret = d_dbase_program_sort_by_ts(rset, order);
			break;
		case SAT_ARRAY:
			ret = d_dbase_program_sort_by_sat(rset, order);
			break;
		case LCN_ARRAY:
			ret = d_dbase_program_sort_by_logic_num(rset, order);
			break;
		case LETTER_ARRAY:
			ret = d_dbase_program_sort_by_letter(rset, order);
			break;
		case CA_ARRAY:
			ret = d_dbase_program_sort_by_ca(rset, order);
			break;
		case FAV_ARRAY:
			ret = d_dbase_program_sort_by_fav(rset, order);
			break;
		case SKIP_ARRAY:
			ret = d_dbase_program_sort_by_skip(rset, order);
			break;
		case LOCK_ARRAY:
			ret = d_dbase_program_sort_by_lock(rset, order);
			break;
		default:
			break;
	}
	t2 = d_sys_get_time();
	D_DUMP("sorting cost %u ms\n", t2 - t1);
	if(ret == D_OK)
	{
		if(memcmp(old_ids, rset->ids, (rset->cnt * sizeof(D_ID))) != 0)
		{
			d_dbase_set_rset_en(0);	//排序时关闭记录集
			if(rearrange == D_TRUE)
			{
				for(i = 0; i < rset->cnt; i++)
				{
					d_dbase_update_srv_num(rset->ids[i], i);	/*排序结束，更新频道号,这种方法会更改以前的节目号区段，占用更大的flash记录集空间*/
				}
			}
			else
			{
				for(i = 0; i < rset->cnt; i++)
				{
					d_dbase_update_srv_num(rset->ids[i], position[i]);	/*排序结束，更新频道号*/
				}
			}
		}
	}
	
	PROJECT_FREE(position);
	PROJECT_FREE(old_ids);
	return ret;
}

/** @brief 对节目记录进行移动
* @param[in] rset 记录集指针
* @param[in] lastchpos 移动前的位置
* @param[in] nextchpos 移动后的位置
* @retval D_OK 排序成功
* @retval D_ERR 排序失败
*/
D_Result
d_dbase_program_move(D_DBRecset *rset, D_U16 lastchpos,D_U16 nextchpos) D_FUNCPOSTFIT
{
	D_Result ret = D_OK;
	D_U16 i = 0, j =0, temp;
	
	if(ret == D_ERR)
	{
		return ret;
	}
	if((lastchpos >= rset->cnt)||(nextchpos >= rset->cnt))
	{
		return D_ERR;
	}
	if(lastchpos < nextchpos)
	{
		temp = rset->ids[lastchpos];
		for(i = 0; i < (nextchpos - lastchpos); i++)
		{
			rset->ids[lastchpos + i] = rset->ids[lastchpos + i + 1];
		}
		rset->ids[nextchpos] = temp;
	}
	else if(lastchpos > nextchpos)
	{
		temp = rset->ids[lastchpos];
		for(i = 0; i < (lastchpos - nextchpos); i++)
		{
			rset->ids[lastchpos - i] = rset->ids[lastchpos - i - 1];
		}
		rset->ids[nextchpos] = temp;
	}
	else
	{
		return ret;
	}
	return ret;
}

/** @brief 按节目名称查找节目
* @param[in] src_rset 查询的节目所在的最初记录集
* @param[in] dst_rset 筛选出的节目组成的记录集
* @param[in] str 输入的字符串
* @retval D_OK 存在符合条件的节目
* @retval D_ERR 不存在符合条件的节目
*/
D_Result
d_dbase_find_program_by_name(D_DBRecset *src_rset, D_DBRecset *dst_rset, D_Char str[])
{
	D_Result ret = D_OK;
	D_U16 i = 0, j = 0;
	D_DBSrvInfo info;	

	for(i = 0; i < src_rset->cnt; i++)
	{
		ret = d_dbase_get_srv_info(src_rset->ids[i], &info);
		if(ret == D_ERR)
		{
			return ret;
		}
		for(j = 0; j < strlen(str); j++)
		{
			if( toupper(str[j]) != toupper(info.name[j]) )
			{
				break;
			}
		}
		if(j == strlen(str))
		{
			d_dbase_rset_add (dst_rset, src_rset->ids[i]);
		}
	}
	return ret;
}


/** @更新某个ts信息
* @param[in] id TS ID
* @param[in] info TS信息指针
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result
p_dbase_updata_ts_info(D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT
{
	info->ts_reserved[0] =  (D_U8)(info->org_net_id>>8);
	info->ts_reserved[1] =  (D_U8)(info->org_net_id);
	return d_dbase_updata_ts_info(id,info);
}

/** @brief 向TS表中插入一个记录
* @param[in] info TS信息
* @retval id TS ID
* @retval -1 插入失败
*/
D_DBTSID
p_dbase_insert_ts (D_DBTSInfo *info) D_FUNCPOSTFIT
{
	info->ts_reserved[0] =  (D_U8)(info->org_net_id>>8);
	info->ts_reserved[1] =  (D_U8)(info->org_net_id);

	return d_dbase_insert_ts(info);
}


/** @brief 取得TS相关信息
* @param[in] id TS记录 ID
* @param[in] info TS信息区指针
* @retval 获取成功返回D_OK
* @retval 获取失败返回D_ERR
*/
D_Result
p_dbase_get_ts_info (D_DBTSID id, D_DBTSInfo *info) D_FUNCPOSTFIT
{
	D_Result	ret = D_ERR;

	ret = d_dbase_get_ts_info(id,info);
	info->org_net_id =  (D_U16)info->ts_reserved[0];
	info->org_net_id =  (D_U16)(info->org_net_id << 8)|(info->ts_reserved[1]);

	return ret;
}

/** @brief 取出一个服务相关信息
* @param[in] id 服务ID
* @param[in] info 服务信息
* @retval D_OK 获得成功
* @retval D_ERR 获取失败
*/
D_Result
p_dbase_get_srv_info(D_DBSrvID id, D_DBSrvInfo * info) D_FUNCPOSTFIT
{    
    if(D_OK != d_dbase_get_srv_info(id, info))
    {
        return D_ERR;
    }

    info->chan_lcn = d_make_u16(info->srv_reserved[0], info->srv_reserved[1]);

    return D_OK;
}

/** @brief 向服务表中加入一条记录
* @param[in] info 服务信息
* @param[in] tmp 临时标志
* @retval id 服务ID
* @retval -1 插入失败
*/
D_DBSrvID
p_dbase_insert_srv_ex(D_DBSrvInfo *info, D_Bool tmp) D_FUNCPOSTFIT
{  
    info->srv_reserved[0] = (D_U8)(info->chan_lcn >> 8);
    info->srv_reserved[1] = (D_U8)(info->chan_lcn);
       
    return d_dbase_insert_srv_ex(info, tmp);
}

/**@}*/

