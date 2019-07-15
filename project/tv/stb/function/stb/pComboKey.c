/**@defgroup stb 组合键功能 
*@{*/
/** @file
* @brief 组合键功能
* @author 刘伟峰
* @date 2013-09-06 刘伟峰: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include "dSys.h"
#include "pMem.h"
#include "pComboKey.h"

static D_U32 last_time = 0;	//记录上次按键时间
static D_U32 current_time = 0; //记录当前按键时间
static D_U8* buf = NULL;	//组合键序列缓存
static D_U8 num = 0;		//组合键的数目
static D_U8* combo_seq = NULL;	//保存用户设定的组合键序列键值
static D_U8 key_pos = 0;	//按键所存放的位置

static D_U32 last_time1 = 0;	//记录上次按键时间
static D_U32 current_time1 = 0; //记录当前按键时间
static D_U8* buf1 = NULL;	//组合键序列缓存
static D_U8 num1 = 0;		//组合键的数目
static D_U8* combo_seq1 = NULL;	//保存用户设定的组合键序列键值
static D_U8 key_pos1 = 0;	//按键所存放的位置

static D_U32 last_time2 = 0;	//记录上次按键时间
static D_U32 current_time2 = 0; //记录当前按键时间
static D_U8* buf2 = NULL;	//组合键序列缓存
static D_U8 num2 = 0;		//组合键的数目
static D_U8* combo_seq2 = NULL;	//保存用户设定的组合键序列键值
static D_U8 key_pos2 = 0;	//按键所存放的位置

/** @brief 设置组合键数目、序列键值及初始化组合键缓存
* @param[in] key_seq 组合键序列键值的指针
* @param[in] len 组合键数目
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_combo_key_seq_init(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT
{
	if(len == 0)	//组合键个数不能为0
	{
		return D_ERR;
	}
	num = len;
	combo_seq =	(D_U8*)PROJECT_ALLOC(num*sizeof(D_U8));
	if(combo_seq == NULL)	//内存申请失败
	{
		num = 0;
		return D_ERR;
	}
	buf = (D_U8*)PROJECT_ALLOC(num*sizeof(D_U8));
	if(buf == NULL)	//内存申请失败
	{
		num = 0;
		return D_ERR;
	}
	memcpy(combo_seq, key_seq, num);
	current_time = 0;
	last_time = 0;
	key_pos = 0;
	return D_OK;
}

D_Result p_combo_key_seq_init1(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT
{
	if(len == 0)	//组合键个数不能为0
	{
		return D_ERR;
	}
	num1 = len;
	combo_seq1 =	(D_U8*)PROJECT_ALLOC(num1*sizeof(D_U8));
	if(combo_seq1 == NULL)	//内存申请失败
	{
		num1 = 0;
		return D_ERR;
	}
	buf1 = (D_U8*)PROJECT_ALLOC(num1*sizeof(D_U8));
	if(buf1 == NULL)	//内存申请失败
	{
		num1 = 0;
		return D_ERR;
	}
	memcpy(combo_seq1, key_seq, num1);
	current_time1 = 0;
	last_time1 = 0;
	key_pos1 = 0;
	return D_OK;
}

D_Result p_combo_key_seq_init2(D_U8 *key_seq, D_U8 len) D_FUNCPOSTFIT
{
	if(len == 0)	//组合键个数不能为0
	{
		return D_ERR;
	}
	num2 = len;
	combo_seq2 =	(D_U8*)PROJECT_ALLOC(num2*sizeof(D_U8));
	if(combo_seq2 == NULL)	//内存申请失败
	{
		num2 = 0;
		return D_ERR;
	}
	buf2 = (D_U8*)PROJECT_ALLOC(num2*sizeof(D_U8));
	if(buf2 == NULL)	//内存申请失败
	{
		num2 = 0;
		return D_ERR;
	}
	memcpy(combo_seq2, key_seq, num2);
	current_time2 = 0;
	last_time2 = 0;
	key_pos2 = 0;
	return D_OK;
}


/** @brief 注销组合键所申请的资源
*/
void p_combo_key_seq_dinit(void) D_FUNCPOSTFIT
{
	PROJECT_FREE(buf);
	PROJECT_FREE(combo_seq);
	num = 0;
	current_time = 0;
	last_time = 0;
	key_pos = 0;
}

void p_combo_key_seq_dinit1(void) D_FUNCPOSTFIT
{
	PROJECT_FREE(buf1);
	PROJECT_FREE(combo_seq1);
	num1 = 0;
	current_time1 = 0;
	last_time1 = 0;
	key_pos1 = 0;
}

void p_combo_key_seq_dinit2(void) D_FUNCPOSTFIT
{
	PROJECT_FREE(buf2);
	PROJECT_FREE(combo_seq2);
	num2 = 0;
	current_time2 = 0;
	last_time2 = 0;
	key_pos2 = 0;
}

/** @brief 输入组合键
* @param[in] key 组合键按键枚举值
* @retval 成功返回D_OK
* @retval 失败返回D_ERR
*/
D_Result p_combo_key_input(D_U8 key) D_FUNCPOSTFIT
{
	D_U32 dif_time = 0;
	D_U8 i = 0;
	
	if(num == 0) //设定组合键个数不对
	{
		return D_ERR;
	}
	else if(combo_seq == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else if(buf == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else
	{
		current_time = d_sys_get_time();
		dif_time = current_time - last_time;
//		D_DUMP("time difference is %d\n", dif_time);
		if((last_time != 0) && (dif_time <= 5000))
		{
			buf[key_pos] = key;
			last_time = current_time;
			key_pos++;
		}
		else
		{
			memset(buf, 0, num);
			buf[0] = key;
			last_time = current_time;
			key_pos = 1;
		}
		if(key_pos >= num)
		{
			last_time = 0;
			for(i = 0; i < num; i++)
			{
				if(buf[i] != combo_seq[i])
				{
					return D_ERR;
				}
			}
			return D_OK;
		}
	}
	return D_ERR;
}

D_Result p_combo_key_input1(D_U8 key) D_FUNCPOSTFIT
{
	D_U32 dif_time = 0;
	D_U8 i = 0;
	
	if(num1 == 0) //设定组合键个数不对
	{
		return D_ERR;
	}
	else if(combo_seq1 == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else if(buf1 == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else
	{
		current_time1 = d_sys_get_time();
		dif_time = current_time1 - last_time1;
//		D_DUMP("time difference is %d\n", dif_time);
		if((last_time1 != 0) && (dif_time <= 5000))
		{
			buf1[key_pos1] = key;
			last_time1 = current_time1;
			key_pos1++;
		}
		else
		{
			memset(buf1, 0, num1);
			buf1[0] = key;
			last_time1 = current_time1;
			key_pos1 = 1;
		}
		if(key_pos1 >= num1)
		{
			last_time1 = 0;
			for(i = 0; i < num1; i++)
			{
				if(buf1[i] != combo_seq1[i])
				{
					return D_ERR;
				}
			}
			return D_OK;
		}
	}
	return D_ERR;
}

D_Result p_combo_key_input2(D_U8 key) D_FUNCPOSTFIT
{
	D_U32 dif_time = 0;
	D_U8 i = 0;
	
	if(num2 == 0) //设定组合键个数不对
	{
		return D_ERR;
	}
	else if(combo_seq2 == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else if(buf2 == NULL) //内存申请失败
	{
		return D_ERR;
	}
	else
	{
		current_time2 = d_sys_get_time();
		dif_time = current_time2 - last_time2;
//		D_DUMP("time difference is %d\n", dif_time);
		if((last_time2 != 0) && (dif_time <= 5000))
		{
			buf2[key_pos2] = key;
			last_time2 = current_time2;
			key_pos2++;
		}
		else
		{
			memset(buf2, 0, num2);
			buf2[0] = key;
			last_time2 = current_time2;
			key_pos2 = 1;
		}
		if(key_pos2 >= num2)
		{
			last_time2 = 0;
			for(i = 0; i < num2; i++)
			{
				if(buf2[i] != combo_seq2[i])
				{
					return D_ERR;
				}
			}
			return D_OK;
		}
	}
	return D_ERR;
}


/**@}*/
