/** @file
* @brief DVBS ����ʱ�ĵ�һЩע�ắ��
* @author ����
* @date 2013-4-4 ����: �����ļ�
*/
#include "dDBase.h"
#include "dMem.h"
#include "dSys.h"
#include "dDebug.h"
#include "dScan.h"


static D_ASGroupOp Analog_AutoScanGroup_Op;




/*˽�г�ʼ��, �Ը�����з��䲢��ʼ������Ҫ�趨����������Ƶ���б�*/
static D_Result analog_auto_scan_init (D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
	D_ASGroup*scan_group = NULL;
	D_U32	group_id = 0;
	D_FEndParam 	*fendp;
	D_FEndFreq		freq;

	/*��������*/	
	scan_group = (D_ASGroup*) d_mman_alloc (hmm, sizeof (D_ASGroup));
	if(!scan_group)
	{
		D_ERROR ("[AutoScan] Cannot allocate group\n");
		return D_ERR;
	}
	
	group[group_id++] = scan_group;
	
	memset(scan_group, 0x00, sizeof (D_ASGroup));	
	scan_group->type = D_SCAN_TYPE_ANALOG;
	scan_group->scan_mode = D_AUTO_SCAN_MODE_ANALOG;
	scan_group->fend_type = D_FEND_ANALOG;
	scan_group->hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
	scan_group->groupOp = &Analog_AutoScanGroup_Op;

	if(as_config->startfreq && (as_config->startfreq <= as_config->endfreq) && as_config->bandwitch)
	{
		freq = as_config->startfreq;

		while(freq < as_config->endfreq  && scan_group->scanFendParamList_cnt < D_SCAN_GROUP_MAX_TP_CNT)
		{
			fendp = (D_FEndParam *)d_mman_alloc(hmm, sizeof (D_FEndParam));
			memset(fendp, 0x00, sizeof(D_FEndParam));
			if(fendp)
			{
				fendp->freq = freq;				
				scan_group->fend_param_list[scan_group->scanFendParamList_cnt++] = fendp;
			}

			freq += as_config->bandwitch;
		}
	}

	/*��¼����*/
	*group_cnt = group_id;

	return D_OK;
}


/** @brief������������������ݿ⡣*/
static D_Result analog_auto_scan_store(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{
	D_U16 groupid, idx;
	D_ASGroup	*scan_group;

	if(!group)
	{
		return D_ERR;
	}

	/*��ÿ�������������б���*/
	for(groupid = 0; groupid < group_cnt; groupid++)
	{
		scan_group = group[groupid];		

		if(scan_group)
		{
			/*�洢Ƶ����Ϣ(Ƶ����Ϣ)*/
			for(idx = 0; idx < scan_group->scanResult.scan_tsinfo_cnt; idx++)
			{			
				if(scan_group->scanResult.tsinfo[idx])
				{
					//Ƶ����Ϣ����param.freq
					//scan_group->scanResult.tsinfo[idx]->param.freq
				}
			}
		}
	}

	return D_OK;
}

static D_Result analog_auto_scan_destroy (D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{	
	D_U16 groupid;
	D_ASGroup	*scan_group;

	for(groupid = 0; groupid < group_cnt; groupid++)
	{
		scan_group = group[groupid];
		//��������	
	}
	
	return D_OK;
}


D_AutoScanOp Analog_AutoScan_Op = 
{
	analog_auto_scan_init,
	analog_auto_scan_store,
	analog_auto_scan_destroy
};





/*˽�г�ʼ��*/
static D_Result analog_group_start (D_ASGroup *scan_group)
{
	return D_OK;
}

/*˽�з���ʼ��*/
static D_Result analog_group_end(D_ASGroup *scan_group)
{
	return D_OK;
}


/*DVBS�Զ���������*/
static D_ASGroupOp Analog_AutoScanGroup_Op = 
{
	analog_group_start,
	analog_group_end,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};


