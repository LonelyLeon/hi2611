/**@defgroup db 数据库测试
*@{*/
/** @file
* @brief 数据库模块测试
* @author 龚克
* @date 2005-6-27 龚克: 建立文件
*/

#include "dDBase.h"
#include "pConfig.h"
#include "dNVPart.h"
#include "dPort.h"
#include "pDBaseDefault.h"
#include "dDebug.h"

 
void
print_srv_tables(int count)D_FUNCPOSTFIT;
void
print_ante_tables(int count)D_FUNCPOSTFIT;
void
print_sat_tables(int count)D_FUNCPOSTFIT;
void
print_ts_tables(int count)D_FUNCPOSTFIT;
int
srv_insert_test ()D_FUNCPOSTFIT;


/** @brief 产生随机字符串*/
char*
generate_random_string(int length)D_FUNCPOSTFIT
{
	static char string[101];
	int i = 0, j = 0;
	
	memset((void*)&string, 0, 101);
	if(length > 100)
	{
		length %= 100;
//		return 0;
	}
	for(i = 0; i < length; i++)
	{
		j = rand();
		if((j%2) == 0)
		{
			string[i] = 'a' + j%26;
		}
		else
		{
			string[i] = 'A' + j%26;
		}
	}
	string[length] = 0;
	return &string;
}

/** @brief 测试天线表*/
int
ante_test(void)D_FUNCPOSTFIT
{
	D_DBAnteInfo info;
	D_DBRecset	rset;
	D_DBID		ids[256], ante;
	D_Int		i;
	D_Bool dirty = D_TRUE;
	print_ante_tables(10);//////////////////////////////////////////
	info.lnb_power = D_TRUE;
	info.lnb_type = 2;
	info.freq1 = 9750;
	info.freq2 = 10600;
	info.diseqc_22k_tone = 0;	
	i=d_dbase_insert_ante (&info);	
	printf("\n malloc id = %d\n",i);
	info.lnb_power = D_TRUE;
	info.lnb_type = 1;
	info.freq1 = 5750;
	info.freq2 = 5150;
	info.diseqc_22k_tone = 0;	
	i=d_dbase_insert_ante (&info);
	printf("\n malloc id = %d\n",i);
	
	d_dbase_rset_init (&rset, 256, ids);
	
	d_dbase_get_antes (&rset);
	
	for (i = 0; i < rset.cnt; i++) 
	{
		d_dbase_get_ante_info (rset.ids[i], &info);
		printf ("\nget d_id=%d; ",rset.ids[i]);
		printf ("\nFRE1:     %d\n", info.freq1);
		printf ("\nFRE2:     %d\n", info.freq2);
	}
	return 0;
}

/** @brief 测试卫星表*/
int
sat_test(void)D_FUNCPOSTFIT
{
	D_DBSateInfo info;
	D_DBRecset	rset;
	D_DBID		ids[256], sat;
	D_Int		i;
	D_Bool dirty = D_TRUE;
	print_sat_tables(10);//////////////////////////////////////////
	info.antenna_slot = 1;
	info.longitude = 120;
	strcpy (info.sate_name, "sat1");
	info.diseqc_pos = 1;
	info.sate_no = 1;
	info.diseqc_type = 4;	
	info.diseqc_port = 1;	
	info.diseqc_12v = 1;	
	i=d_dbase_insert_sat_ex (&info, D_FALSE);	
	printf("\n malloc id = %d\n",i);
	info.antenna_slot = 2;
	info.longitude = 240;
	strcpy (info.sate_name, "sat2");
	info.diseqc_pos = 2;
	info.sate_no = 2;
	info.diseqc_type = 4;	
	info.diseqc_port = 2;	
	info.diseqc_12v = 1;	
	i=d_dbase_insert_sat_ex (&info, D_FALSE);
	printf("\n malloc id = %d\n",i);
	
	d_dbase_rset_init (&rset, 256, ids);
	
	d_dbase_get_sates (&rset);
	
	for (i = 0; i < rset.cnt; i++) 
	{
		d_dbase_get_sat_info (rset.ids[i], &info);
		printf ("\nget d_id=%d; ",rset.ids[i]);
		printf ("\nSAT:     %s\n", info.sate_name);
		printf ("\nantenna_slot:     %d\n", info.antenna_slot);
		printf ("\nlongitude:     %d\n", info.longitude);
		printf ("\nsate_no:     %d\n", info.sate_no);
		printf ("\ndiseqc_12v:     %d\n", info.diseqc_12v);
	}
	return 0;
}

/** @brief 测试TS表*/
int
ts_test(void)D_FUNCPOSTFIT
{
	D_DBTSInfo info;
	D_DBRecset	rset;
	D_DBID		ids[256], sat;
	D_Int		i;
	D_Bool dirty = D_TRUE;
	print_ts_tables(10);//////////////////////////////////////////
#ifdef D_DBASE_DVBS
	info.param.dvbs.freq = 12020;
//	info.param.dvbs.baud = 28800;
//	info.param.dvbs.pol = 0;
	info.db_net_id = 1;
	info.ts_id = 1;
	info.tuner_type = 0;
	info.db_sat_id = 1;
#else
	info.param.abs.freq = 12020;
	info.param.abs.baud = 28800;
	info.param.abs.pol = 0;
	info.db_net_id = 1;
	info.ts_id = 1;
	info.tuner_type = 0;
	info.db_sat_id = 1;
#endif	
	i=d_dbase_insert_ts_ex(&info, D_FALSE);	
	printf("\n malloc id = %d\n",i);
#ifdef D_DBASE_DVBS
	info.param.dvbs.freq = 12340;
//	info.param.dvbs.baud = 27500;
//	info.param.dvbs.pol = 1;
	info.db_net_id = 2;
	info.ts_id = 2;
	info.tuner_type = 1;
	info.db_sat_id = 2;
#else
	info.param.abs.freq = 12340;
	info.param.abs.baud = 27500;
	info.param.abs.pol = 1;
	info.db_net_id = 2;
	info.ts_id = 2;
	info.tuner_type = 1;
	info.db_sat_id = 2;
#endif	
	i=d_dbase_insert_ts_ex(&info, D_FALSE);
	printf("\n malloc id = %d\n",i);
	
	d_dbase_rset_init (&rset, 256, ids);
	
	d_dbase_get_tses(&rset);
	
	for (i = 0; i < rset.cnt; i++) 
	{
		d_dbase_get_ts_info(rset.ids[i], &info);
		printf ("\nget d_id=%d; ",rset.ids[i]);
#ifdef D_DBASE_DVBS		
		printf ("\nfreq:     %d\n", info.param.dvbs.freq);
//		printf ("\nbaud:     %d\n", info.param.dvbs.baud);
//		printf ("\npol:     %d\n", info.param.dvbs.pol);
#else
		printf ("\nfreq:     %d\n", info.param.abs.freq);
		printf ("\nbaud:     %d\n", info.param.abs.baud);
		printf ("\npol:     %d\n", info.param.abs.pol);
#endif
		printf ("\ndb_net_id:     %d\n", info.db_net_id);
		printf ("\nts_id:     %d\n", info.ts_id);
		printf ("\ntuner_type:     %d\n", info.tuner_type);
		printf ("\ndb_sat_id:     %d\n", info.db_sat_id);		
	}
	return 0;
}

/** @brief 测试服务表*/
int
srv_test(void)D_FUNCPOSTFIT
{
	D_DBSrvInfo	info;
	D_DBRecset	rset;
	D_DBID			ids[256], srv;
	D_Int				i;
	D_Bool dirty = D_TRUE;
	print_srv_tables(10);//////////////////////////////////////////
	strcpy (info.name, "cctv5");
	info.srv_type = D_DB_SRV_TV;
	info.favor0 = D_TRUE;
	info.chan_num = 6;
	i=d_dbase_insert_srv (&info);
	printf("\n malloc id = %d\n",i);
	strcpy (info.name, "cctv6");
	info.srv_type = D_DB_SRV_TV;
	info.favor0 = D_TRUE;
	info.chan_num = 8;
	i=d_dbase_insert_srv (&info);
	printf("\n malloc id = %d\n",i);
	
	d_dbase_rset_init (&rset, 256, ids);
	if (d_dbase_has_any_srv (D_DB_SRV_TV)) 
	{
		printf ("\nHAVE TV\n");
		d_dbase_get_srvs_by_type (&rset, D_DB_SRV_TV, D_TRUE, 0);
		for (i = 0; i < rset.cnt; i++) 
		{
			d_dbase_get_srv_info (rset.ids[i], &info);
			printf ("\nget d_id=%d; ",rset.ids[i]);
			printf ("SRV:     %s\n", info.name);
		}
	}
	srv = d_dbase_get_srv_by_num (0, D_DB_SRV_TV);
	if (srv != -1) 
	{
		d_dbase_get_srv_info (srv, &info);
		printf ("\nSRV NUM: %s %ld\n", info.name, (D_U32)info.chan_num);
	}
	printf ("\nFREE NUM %ld\n", (D_U32)d_dbase_get_free_chan_num (D_DB_SRV_TV));
	printf ("\nNEXT NUM %ld\n", (D_U32)d_dbase_get_next_chan_num (-1, D_DB_SRV_TV, D_TRUE, D_FALSE));
	return 0;
}

/** @brief 插入多个节目记录*/
int
srv_insert_test(void)D_FUNCPOSTFIT
{
	D_DBSrvInfo	info;
	D_DBRecset	rset,rset2;
	D_DBID		ids[256], ids2[256], srv;
	D_Int		i,j,len;
	D_Bool dirty = D_TRUE;
//	print_srv_tables(10);//////////////////////////////////////////
	d_dbase_set_rset_en(0);
	for(j = 0; j < 1020; j++)
	{
//		d_strcpy (info.name, "cctv");
//		memset(info.name, 0, sizeof(info.name));
		memset(&info, 0, sizeof(D_DBSrvInfo));
		strncpy(info.name, generate_random_string(8), sizeof(info.name));
		len = strlen(info.name);
		info.srv_type = D_DB_SRV_TV; //rand() % 2; //D_DB_SRV_TV;
		info.chan_num = d_dbase_get_free_chan_num(info.srv_type/*D_DB_SRV_TV*/);
		printf ("\nchan_num=%d; ",info.chan_num);
/*		info.name[len] = (j + 1)/100 + 0x30;
		info.name[len + 1] = ((j + 1)%100)/10 + 0x30;
		info.name[len + 2] = (((j + 1)%100)%10) + 0x30;
		info.name[len + 3] = 0;		*/	
		info.name[len] = info.chan_num/1000 + 0x30;
		info.name[len + 1] = (info.chan_num%1000)/100 + 0x30;
		info.name[len + 2] = (info.chan_num%100)/10 + 0x30;
		info.name[len + 3] = (info.chan_num%10) + 0x30;
		info.name[len + 4] = 0;
		info.favor0 = rand() % 2; //D_TRUE;
		info.srv_id = rand();		
		info.ca_flag = rand() % 2; //D_TRUE;
		info.db_ts_id = j/25 + 1;
		i=d_dbase_insert_srv (&info);
                printf("\n srv type is %d\n",info.srv_type);
		printf("\n malloc id = %d\n",i);
		printf("\n service id = %d\n",info.srv_id);
	}	
	d_dbase_flush();
	d_dbase_set_rset_en(1);			
/*	d_dbase_rset_init (&rset, 256, ids);
	d_dbase_rset_init (&rset2, 256, ids2);
	if (d_dbase_has_any_srv (D_DB_SRV_TV)) 
	{
		printf ("\nHAVE TV\n");
		d_dbase_get_srvs_by_type (&rset, D_DB_SRV_TV, D_FALSE, 0);
		d_dbase_program_sort(&rset, 5, 0, D_FALSE);
		d_dbase_program_move(&rset, 5, 10);
		for (i = 0; i < rset.cnt; i++) 
		{
			d_dbase_get_srv_info (rset.ids[i], &info);
			printf ("\nget d_id=%d; ",rset.ids[i]);
			printf ("\nget service_id=%d; ",info.srv_id);
			printf ("SRV:     %s\n", info.name);
		}
		d_dbase_program_sort(&rset, 0, 0, D_FALSE);
		for (i = 0; i < rset.cnt; i++) 
		{
			d_dbase_get_srv_info (rset.ids[i], &info);
			printf ("\nget d_id=%d; ",rset.ids[i]);
			printf ("\nget service_id=%d; ",info.srv_id);
			printf ("SRV:     %s\n", info.name);
		}
		d_dbase_find_program_by_name(&rset, &rset2, "z");
//		d_dbase_get_srvs_by_ts (&rset2, 1, D_DB_SRV_TV);
		printf ("\nTV with name including z:\n");
		for (i = 0; i < rset2.cnt; i++) 
		{
			d_dbase_get_srv_info (rset2.ids[i], &info);
			printf ("\nget d_id=%d; ",rset2.ids[i]);
			printf ("\nget service_id=%d; ",info.srv_id);
			printf ("SRV:     %s\n", info.name);
		}		
	}	*/
	for(i = 0; i < 7280; i++)
	{
		d_dbase_get_srv_info (1, &info);
		info.favor0 = !info.favor0;
		d_dbase_update_srv_param (1, &info, D_TRUE);
	}
	return 0;
}

/** @brief 测试bouquet表*/
int
bouquet_test(void)D_FUNCPOSTFIT
{
	D_DBBouqInfo	info;
	D_DBRecset	rset;
	D_DBID			ids[256];
	D_Int				i;
	strcpy (info.name, "bouquet5");
	info.bouq_id = 1132;
	i=d_dbase_insert_bouq (&info);
	printf("\n malloc id = %d\n",i);
	strcpy (info.name, "bouquet2");
	info.bouq_id = 1212;
	i=d_dbase_insert_bouq (&info);
	printf("\n malloc id = %d\n",i);
	d_dbase_rset_init (&rset, 256, ids);
	d_dbase_get_bouqs (&rset);
	for (i = 0; i < rset.cnt; i++) 
	{
		d_dbase_get_bouq_info (rset.ids[i], &info);
		printf ("\nget d_id=%d; ",rset.ids[i]);
		printf ("bouquet:   %s\n", info.name);
		printf ("bouquet id:   %d\n", info.bouq_id);
	}
	return 0;
}
/** @brief 测试sub表*/
int
sub_test(void)D_FUNCPOSTFIT
{
	D_DBEvtInfo	info;
	D_DBRecset	rset;
	D_DBID			ids[256];
	int				i;
	strcpy (info.name, "sub1");
	info.db_srv_id = 1111;
	i=d_dbase_insert_subscribe (&info);
	printf("\n malloc id = %d\n",i);
	strcpy (info.name, "sub2");
	info.db_srv_id = 1212;
	i=d_dbase_insert_subscribe (&info);
	printf("\n malloc id = %d\n",i);
	d_dbase_rset_init (&rset, 256, ids);
	d_dbase_get_subscribes (&rset);
	for (i = 0; i < rset.cnt; i++) 
	{
		d_dbase_get_subscribe_info (rset.ids[i], &info);
		printf ("\nget d_id=%d; ",rset.ids[i]);
		printf ("bouquet:   %s\n", info.name);
		printf ("bouquet id:   %d\n", info.db_srv_id);
	}
	return 0;
}
/** @brief 打印节目信息
* @param id 指定打印目标
*/
int
print_srv_table(int id)D_FUNCPOSTFIT
{
	static D_DBSrvInfo	infochange;
	d_dbase_get_srv_info (id, &infochange);
	printf ("\nchan_name: %s \n", infochange.name);
	printf ("\nchan_type: %d \n", infochange.srv_type);
	printf ("\nchan_fav0: %d \n", infochange.favor0);
	printf ("\nchan_num: %ld \n", (D_U32)infochange.chan_num);
	return 0;
}

/** @brief 打印天线信息
* @param id 指定打印目标
*/
int
print_ante_table(int id)D_FUNCPOSTFIT
{
	static D_DBAnteInfo	infochange;
	d_dbase_get_ante_info (id, &infochange);
	printf ("\nlnb_type: %d \n", infochange.lnb_type);
	printf ("\nfreq1: %d \n", infochange.freq1);
	printf ("\nfreq2: %d \n", infochange.freq2);
	return 0;
}

/** @brief 打印卫星信息
* @param id 指定打印目标
*/
int
print_sat_table(int id)D_FUNCPOSTFIT
{
	static D_DBSateInfo	infochange;
	d_dbase_get_sat_info(id, &infochange);
	printf ("\nsat_name: %s \n", infochange.sate_name);
	printf ("\nnantenna_slot: %d \n", infochange.antenna_slot);
	printf ("\nlongitude: %d \n", infochange.longitude);
	printf ("\nsate_no: %d \n", infochange.sate_no);
	return 0;
}

/** @brief 打印转发器信息
* @param id 指定打印目标
*/
int
print_ts_table(int id)D_FUNCPOSTFIT
{
	static D_DBTSInfo	infochange;
	d_dbase_get_ts_info(id, &infochange);
#ifdef D_DBASE_DVBS		
	printf ("\nfreq:     %d\n", infochange.param.dvbs.freq);
//	printf ("\nbaud:     %d\n", infochange.param.dvbs.baud);
//	printf ("\npol:     %d\n", infochange.param.dvbs.pol);
#else
	printf ("\nfreq:     %d\n", infochange.param.abs.freq);
	printf ("\nbaud:     %d\n", infochange.param.abs.baud);
	printf ("\npol:     %d\n", infochange.param.abs.pol);
#endif
	printf ("\ndb_net_id:     %d\n", infochange.db_net_id);
	printf ("\nts_id:     %d\n", infochange.ts_id);
	printf ("\ntuner_type:     %d\n", infochange.tuner_type);
	printf ("\ndb_sat_id:     %d\n", infochange.db_sat_id);		
	return 0;
}

/** @brief 打印节目信息
* @param id 打印总数
*/
void
print_srv_tables(int count)D_FUNCPOSTFIT
{
	int k;
	for(k = 1 ; k < count;k++)
	print_srv_table(k);
}

/** @brief 打印天线信息
* @param id 打印总数
*/
void
print_ante_tables(int count)D_FUNCPOSTFIT
{
	int k;
	for(k = 1 ; k < count;k++)
	print_ante_table(k);
}

/** @brief 打印卫星信息
* @param id 打印总数
*/
void
print_sat_tables(int count)D_FUNCPOSTFIT
{
	int k;
	for(k = 1 ; k < count;k++)
	print_sat_table(k);
}

/** @brief 打印转发器信息
* @param id 打印总数
*/
void
print_ts_tables(int count)D_FUNCPOSTFIT
{
	int k;
	for(k = 1 ; k < count;k++)
	print_ts_table(k);
}

/** @brief 测试记录集中的插入与删除
* @param num	插入个数
*/
void 
test_mask(int num)D_FUNCPOSTFIT
{
	D_DBSrvInfo	info;
	D_DBID      srv;
	D_Int		j;
	
	info.srv_type = D_DB_SRV_TV;
	info.favor0 = D_TRUE;
	printf("\ntest_mask start\n");
	
	d_dbase_delete_srv(8);
	
	for(j = 1;j < num;j++)
	{
		strcpy (info.name, "cctv5");
		info.chan_num = j;
		srv=d_dbase_insert_srv (&info);
		printf("\n malloc id =%d\n",srv);
	}
	
	d_dbase_delete_srv(2);
	print_srv_tables(10);
	printf("\ntest_mask end\n");
}


D_Result
testconfig()D_FUNCPOSTFIT
{
	D_AudTrack	t;
	t = p_conf_get_volume();
	printf("\n############# %d ###########\n",t);
	p_conf_set_volume(30);
	p_conf_set_volume(28);
	return D_OK;
}

/** @brief 测试记录集极限
* @param changes	改变次数
*/
D_Result
change_flash_record(int changes)D_FUNCPOSTFIT
{
	static D_DBSrvInfo	info;
	D_Bool dirty = D_TRUE;
	D_DBID id = 2;
 	int i=0;
	char str[10]={0};
	for(i = 0;i<changes;i++)
	{
		sprintf(str,"cctv%d",i);
		d_dbase_record_flash_flush_tbl(2,0,id,strlen(str),str,1);
	} 
	
	print_srv_tables(10);
	testconfig();
	return 0;
}
/*
int
main (int argc, char **argv)
{		
	printf("hello dasetest\n");
	d_port_open ();
	d_nvpart_open ();
	d_dbase_open ();		
	d_dbase_load_flash_ex();//放在ddbase_open函数中。
	
	ante_test ();
	sat_test ();
	ts_test ();
//	srv_test ();
	srv_insert_test();
	bouquet_test();
	sub_test();
	//change_flash_record(10000);
	//testconfig();
	//test_mask(500);
	//dbase_refresh_flash();
	d_dbase_close ();
	d_nvpart_close ();
	d_port_close ();
	printf("goodbye dasetest\n");
	return 0;
}
*/

/**@}*/
