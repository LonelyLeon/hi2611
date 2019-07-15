/** @file
* @brief 搜索结果排序模块
* @author 覃宜
* @date 2013-7-22 覃宜: 建立文件
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dDBase.h"
#include "dScan.h"
#include "dConfigFile.h"
#include "pStbScan.h"
#include "pCustomConfig.h"
#include "pDBaseDefault.h"

static D_ScanSortMode sort_all_mode;
static D_ID *sort_dbtsid_list = NULL;
static D_U32 sort_dbtsid_list_cnt = 0;

/** @brief 对数组进行冒泡排序法*/
static void haier_sort(void*base, D_U32 num, D_U32 width, int(*compare)(const void*, const void*))
{
    D_U32 i, j;
    int flag = 1;
    void*node_a, *node_b, *tmp;

    if((!base) || num == 0 || width == 0 || compare == NULL)
    {
        return ;
    }

    tmp = d_mem_alloc(0, width);
    if(tmp == NULL)
    {
        return ;
    }

    for (i = 0; (i < (num - 1) && flag); i++)
    {
        flag = 0;
        for (j = 0; j < (num - 1 - i); j++)
        {
            node_a = (void*)(((D_U8*)base) + width * j);
            node_b = (void*)(((D_U8*)base) + width * (j + 1));
            if (compare(node_a, node_b) > 0)
            {
                memcpy(tmp, node_a, width);
                memcpy(node_a, node_b, width);
                memcpy(node_b, tmp, width);
                flag = 1;
            }
        }
    }

    d_mem_free(tmp);
}


/*交换数值*/
static __inline__ void  swap_val(D_ScanSrvInfoNode*a, D_ScanSrvInfoNode*b)
{
    D_ScanSrvInfoNode    c;

    memcpy(&c, a, sizeof(D_ScanSrvInfoNode));
    memcpy(a, b, sizeof(D_ScanSrvInfoNode));
    a->list = c.list;
    c.list = b->list;
    memcpy(b, &c, sizeof(D_ScanSrvInfoNode));
}


/*比较数值*/
static D_Bool cmp_val(D_ScanSrvInfoNode*a, D_ScanSrvInfoNode*b, D_ScanSortMode mode)
{
    D_Bool ret = D_FALSE;

    switch(mode)
    {
        case D_SCAN_SORT_MODE_LCN:
            if(a->srvinfo.chan_lcn > b->srvinfo.chan_lcn)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_LCN_CONTRARY:
            if(a->srvinfo.chan_lcn < b->srvinfo.chan_lcn)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_SRVID:
            if(a->srvinfo.srv_id > b->srvinfo.srv_id)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_SRVID_CONTRARY:
            if(a->srvinfo.srv_id < b->srvinfo.srv_id)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_FREECA:
            if(a->srvinfo.ca_mask > b->srvinfo.ca_mask)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_FREECA_CONTRARY:
            if(a->srvinfo.ca_mask < b->srvinfo.ca_mask)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_NAME:
            if( strcmp( a->srvinfo.name, b->srvinfo.name) > 0)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_NAME_CONTRARY:
            if( strcmp( a->srvinfo.name, b->srvinfo.name) < 0)
            {
                ret = D_TRUE;
            }
            break;
        case D_SCAN_SORT_MODE_TS:
        case D_SCAN_SORT_MODE_TS_CONTRARY:
            if(sort_dbtsid_list && sort_dbtsid_list_cnt && (a->ts_no < sort_dbtsid_list_cnt) && (b->ts_no < sort_dbtsid_list_cnt))
            {
                D_ID dbtsid_a, dbtsid_b;

                dbtsid_a = sort_dbtsid_list[a->ts_no];
                dbtsid_b = sort_dbtsid_list[b->ts_no];

                if(dbtsid_a != dbtsid_b)
                {
                    D_DBTSInfo tsinfo_a, tsinfo_b;
                    D_Result ret_a, ret_b;

                    ret_a = d_dbase_get_ts_info(dbtsid_a, &tsinfo_a);
                    ret_b = d_dbase_get_ts_info(dbtsid_b, &tsinfo_b);

                    if(ret_a == D_OK && ret_b == D_OK)
                    {
                        if(mode == D_SCAN_SORT_MODE_TS && tsinfo_a.param.freq > tsinfo_b.param.freq)
                        {
                            ret = D_TRUE;
                        }
                        else if(mode == D_SCAN_SORT_MODE_TS_CONTRARY && tsinfo_a.param.freq < tsinfo_b.param.freq)
                        {
                            ret = D_TRUE;
                        }
                    }
                }
            }
            break;

        case D_SCAN_SORT_MODE_TSID:
            if(sort_dbtsid_list && sort_dbtsid_list_cnt && (a->ts_no < sort_dbtsid_list_cnt) && (b->ts_no < sort_dbtsid_list_cnt))
            {
                D_ID dbtsid_a, dbtsid_b;

                dbtsid_a = sort_dbtsid_list[a->ts_no];
                dbtsid_b = sort_dbtsid_list[b->ts_no];

                if(dbtsid_a != dbtsid_b)
                {
                    D_DBTSInfo tsinfo_a, tsinfo_b;
                    D_Result ret_a, ret_b;

                    ret_a = d_dbase_get_ts_info(dbtsid_a, &tsinfo_a);
                    ret_b = d_dbase_get_ts_info(dbtsid_b, &tsinfo_b);

                    if(ret_a == D_OK && ret_b == D_OK)
                    {
                        if(tsinfo_a.ts_id > tsinfo_b.ts_id)
                        {
                            ret = D_TRUE;
                        }
                        else if(tsinfo_a.ts_id == tsinfo_b.ts_id)
                        {
                            if(tsinfo_a.param.freq > tsinfo_b.param.freq)
                            {
                                ret = D_TRUE;
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
    }

    return ret;
}

/** @brief 搜索后排序所用的dbtsid列表*/
D_Result p_scan_sort_srv_set_dbtsid_list(D_ID *list, D_U32 cnt)D_FUNCPOSTFIT
{
    sort_dbtsid_list = list;
    sort_dbtsid_list_cnt = cnt;
    return D_OK;
}

/** @brief 对搜索的结果进行排序，冒泡排序法
* @param [in][out] srvlist 业务链表
* @param [in] mode 排序方式
* @return 成功D_OK, 失败D_ERR
*/
static D_Result scan_sort_srv(D_ScanSrvInfoNode*srvlist, D_ScanSortMode mode)D_FUNCPOSTFIT
{
    D_ScanSrvInfoNode * srvnode,  *end = NULL, *e = NULL;
    D_Bool flag = D_TRUE;

    if(mode > D_SCAN_SORT_MODE_NOT)
    {
        while(flag)
        {
            flag = D_FALSE;
            srvnode = srvlist;
            while((srvnode != end) && srvlist != (D_ScanSrvInfoNode*)(srvnode->list.next))
            {
                if(cmp_val(srvnode, (D_ScanSrvInfoNode*)(srvnode->list.next), mode))
                {
                    swap_val(srvnode, (D_ScanSrvInfoNode*)(srvnode->list.next));
                    flag = D_TRUE;
                }
                e = srvnode;
                srvnode = (D_ScanSrvInfoNode*)(srvnode->list.next);
            }
            end = e;
        }
    }

    return D_OK;
}


/** @brief 对搜索的结果进行排序，冒泡排序法
* @param [in][out] srvlist 业务链表
* @param [in] mode 排序方式
* @return 成功D_OK, 失败D_ERR
*/
D_Result p_scan_sort_srv(D_ScanSrvInfoNode*srvlist, D_ScanSortMode mode)D_FUNCPOSTFIT
{
    D_ID i;
    D_ScanSortMode mode_list[4] = {0};
    D_U32 mode_list_cnt = 0;

    if(mode == D_SCAN_SORT_MODE_TSID_SRVID)
    {
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_SRVID;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_TSID;
    }
    else if(mode == D_SCAN_SORT_MODE_CAFREE_TS_SRVID)
    {
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_SRVID;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_TS;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_FREECA_CONTRARY;
    }
    else
    {
        mode_list[mode_list_cnt++] = mode;
    }

    if(mode == 0 || mode_list_cnt == 0)
    {
        return D_OK;
    }

    for(i = 0; i < mode_list_cnt; i++)
    {
        scan_sort_srv(srvlist, mode_list[i]);
    }
    
    return D_OK;
}

/** @brief 与用户软件配置里的频点屏蔽列表比较，判断频点是否有效
* @return 有效D_TRUE, 无效D_FALSE
*/
D_Bool p_scan_judge_freq_valid(D_U32 freq)D_FUNCPOSTFIT
{
    static D_U16 disable_freq[16][2];
    static D_U32 disable_cnt = 0xFF, i;

    if(disable_cnt == 0xFF)
    {
        D_U8 *payload;
        D_U16 len, temp;

        disable_cnt = 0;
        payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_SCAN_DISABLE_FREQ_LIST, &len);
        while(payload && len >= 4)
        {
            temp = payload[0] << 8;
            temp |= payload[1];
            disable_freq[disable_cnt][0] = temp;
            temp = payload[2] << 8;
            temp |= payload[3];
            disable_freq[disable_cnt][1] = temp;
            disable_cnt++;
            payload += 4;
            len -= 4;
        }
    }

    for(i = 0; i < disable_cnt; i++)
    {
        if(disable_freq[i][0] <= freq && freq <= disable_freq[i][1])
        {
            return D_FALSE;
        }
    }

    return D_TRUE;
}

static int cmp_val_all(const void*a, const void*b)
{
    int ret = 0, c;
    D_DBSrvInfo ainfo, binfo;

    p_dbase_get_srv_info(*((D_ID*)a), &ainfo);
    p_dbase_get_srv_info(*((D_ID*)b), &binfo);

    switch(sort_all_mode)
    {
        case D_SCAN_SORT_MODE_LCN:
            if(ainfo.chan_lcn > binfo.chan_lcn)
            {
                ret = 1;
            }
            else if(ainfo.chan_lcn < binfo.chan_lcn)
            {
                ret = -1;
            }

            break;
        case D_SCAN_SORT_MODE_LCN_CONTRARY:
            if(ainfo.chan_lcn < binfo.chan_lcn)
            {
                ret = 1;
            }
            else if(ainfo.chan_lcn > binfo.chan_lcn)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_SRVID:
            if(ainfo.srv_id > binfo.srv_id)
            {
                ret = 1;
            }
            else if(ainfo.srv_id < binfo.srv_id)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_SRVID_CONTRARY:
            if(ainfo.srv_id < binfo.srv_id)
            {
                ret = 1;
            }
            else if(ainfo.srv_id > binfo.srv_id)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_FREECA:
            if(ainfo.ca_flag > binfo.ca_flag)
            {
                ret = 1;
            }
            else if(ainfo.ca_flag < binfo.ca_flag)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_FREECA_CONTRARY:
            if(ainfo.ca_flag < binfo.ca_flag)
            {
                ret = 1;
            }
            else if(ainfo.ca_flag > binfo.ca_flag)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_NAME:
            c = strcmp( ainfo.name, binfo.name);
            if( c > 0)
            {
                ret = 1;
            }
            else if(c < 0)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_NAME_CONTRARY:
            c = strcmp( ainfo.name, binfo.name);
            if( c < 0)
            {
                ret = 1;
            }
            else if(c > 0)
            {
                ret = -1;
            }
            break;
        case D_SCAN_SORT_MODE_TS:
        case D_SCAN_SORT_MODE_TS_CONTRARY:
            if(ainfo.db_ts_id != binfo.db_ts_id)
            {
                D_DBTSInfo tsinfo_a, tsinfo_b;
                D_Result ret_a, ret_b;

                ret_a = d_dbase_get_ts_info(ainfo.db_ts_id, &tsinfo_a);
                ret_b = d_dbase_get_ts_info(binfo.db_ts_id, &tsinfo_b);

                if(ret_a == D_OK && ret_b == D_OK)
                {
                    if(tsinfo_a.param.freq > tsinfo_b.param.freq)
                    {
                        ret = (sort_all_mode == D_SCAN_SORT_MODE_TS) ? 1 : (-1);
                    }
                    else if(tsinfo_a.param.freq < tsinfo_b.param.freq)
                    {
                        ret = (sort_all_mode == D_SCAN_SORT_MODE_TS_CONTRARY) ? 1 : (-1);
                    }
                }
            }
            break;
        case D_SCAN_SORT_MODE_TSID:
            if(ainfo.db_ts_id != binfo.db_ts_id)
            {
                D_DBTSInfo tsinfo_a, tsinfo_b;
                D_Result ret_a, ret_b;

                ret_a = d_dbase_get_ts_info(ainfo.db_ts_id, &tsinfo_a);
                ret_b = d_dbase_get_ts_info(binfo.db_ts_id, &tsinfo_b);

                if(ret_a == D_OK && ret_b == D_OK)
                {
                    if(tsinfo_a.ts_id > tsinfo_b.ts_id)
                    {
                        ret = 1;
                    }
                    else if(tsinfo_a.ts_id == tsinfo_b.ts_id)
                    {
                        if(tsinfo_a.param.freq > tsinfo_b.param.freq)
                        {
                            ret = 1;
                        }
                    }
                    else
                    {
                        ret = -1;
                    }
                }
            }
            break;
        default:
            break;
    }

    return ret;
}

/** @brief 对数据库的结果进行排序，冒泡排序法
* @param [in] type 电视广播
* @param [in] mode 排序方式
* @param [in] reset_num 是否重新设置频道号
* @return 成功D_OK, 失败D_ERR
*/
D_Result p_scan_sort_all_srv(D_DBSrvType type, D_ScanSortMode mode, D_Bool reset_num)D_FUNCPOSTFIT
{
    D_Bool flag = D_TRUE;
    D_DBRecset rset;
    D_ID i, max, *dbids = NULL;
    D_U16 *num = NULL;
    D_Result ret = D_OK;
    D_ScanSortMode mode_list[4] = {0};
    D_U32 mode_list_cnt = 0;

    
    if(mode == D_SCAN_SORT_MODE_TSID_SRVID)
    {
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_SRVID;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_TSID;
    }
    else if(mode == D_SCAN_SORT_MODE_CAFREE_TS_SRVID)
    {
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_SRVID;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_TS;
        mode_list[mode_list_cnt++] = D_SCAN_SORT_MODE_FREECA_CONTRARY;
    }
    else
    {
        mode_list[mode_list_cnt++] = mode;
    }

    if(mode == 0 || mode_list_cnt == 0 || type > D_DB_SRV_RADIO)
    {
        return D_OK;
    }
    max = d_dbase_get_srvs_cnt(D_FALSE, type);
    if(0 == max)
    {
        return D_OK;
    }

    dbids = (D_ID*)d_mem_alloc(0, sizeof(D_ID) * max);
    if(!dbids)
    {
        ret = D_ERR;
        goto _SORT_END;
    }

    d_dbase_rset_init(&rset, max, dbids);
    d_dbase_get_srvs_by_type_ex(&rset, D_FALSE, type, D_FALSE, 0);
    if(rset.cnt == 0)
    {
        ret = D_ERR;
        goto _SORT_END;
    }

    if(!reset_num)
    {
        D_DBSrvInfo info;
        num = (D_U16*)d_mem_alloc(0, sizeof(D_U16) * rset.cnt);
        if(!num)
        {
            ret = D_ERR;
            goto _SORT_END;
        }
        for(i = 0; i < rset.cnt; i++)
        {
            p_dbase_get_srv_info(rset.ids[i], &info);
            num[i] = info.chan_num;
        }
    }

    for(i = 0; i < mode_list_cnt; i++)
    {
        sort_all_mode = mode_list[i];
        haier_sort(rset.ids, rset.cnt, sizeof(D_ID), cmp_val_all);
    }

    for(i = 0; i < rset.cnt; i++)
    {
        if(!reset_num)
        {
            d_dbase_update_srv_num(rset.ids[i], num[i]);
        }
        else
        {
            d_dbase_update_srv_num(rset.ids[i], i + 1);
        }
    }

_SORT_END:
    if(dbids)
    {
        d_mem_free(dbids);
    }
    if(num)
    {
        d_mem_free(num);
    }
    return ret;
}


