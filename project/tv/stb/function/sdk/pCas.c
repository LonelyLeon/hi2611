/** @file
* @brief Cas
*
* @author �
* @date 2013-07-10 �: �����ļ�
*/
#include <stdlib.h>
#include "dMsg.h"
#include "dQueue.h"
#include "dCBMan.h"
#include "dCA.h"
#include "dGUI.h"
#include "pSdk.h"
#include "dDebug.h"
#include "pConfig.h"
#include "pStbCaMenus.h"

/* @brief �����������ӿ�*/
extern D_Result 
p_stb_ca_scroll_action(D_Handle handle, D_U32 action, D_CasScrollParam *param)D_FUNCPOSTFIT;

#if   D_CA_SUPPORT_DEF   
static void cas_get_curr_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U32 *curr_ca = (D_U32*)obj_data;

    *curr_ca = p_conf_get_curr_ca();
}

static void cas_set_curr_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U32 *curr_ca = (D_U32*)obj_data;

    p_conf_set_curr_ca(*curr_ca);
}

static void cas_get_lan_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U8 *lan = (D_U8*)obj_data;

    *lan = p_conf_get_lang();
}

static void cas_get_stb_id_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U32 *stb_id = (D_U32*)obj_data;
    D_LoaderParam loader_param;

    p_conf_get_loader_param(&loader_param);

    *stb_id = strtoul(loader_param.stb_param_copy.stb_id, NULL, 0);
}

static void cas_get_stb_id_string_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U8 *cainfo = (D_U8*)obj_data;
    D_LoaderParam loader_param;

    p_conf_get_loader_param(&loader_param);
    
    memcpy(cainfo, loader_param.stb_param_copy.stb_id, D_CONF_DEF_STB_ID_LEN);
}

static void cas_get_stb_id_abv_string_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U8 *cainfo = (D_U8*)obj_data;
    D_LoaderParam loader_param = {0};

    p_conf_get_loader_param(&loader_param);
    
    sprintf((char *)cainfo, "%08x", loader_param.lnbfreq1);
	sprintf((char *)(cainfo + 8), "%08x", loader_param.lnbfreq2);
    memcpy((cainfo + 16), loader_param.stb_param_copy.stb_id, D_CONF_DEF_STB_ID_LEN);
}

static void cas_get_ca_private_info_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U8 *cainfo = (D_U8*)obj_data;
    
    p_conf_get_ca_related_info(cainfo);  //p_conf_get_ca_related_info�ӿ�ʵ�ֺ󣬴򿪴����    
}

static void cas_set_ca_private_info_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_U8 *cainfo = (D_U8*)obj_data;

    p_conf_set_ca_related_info(cainfo); //p_conf_set_ca_related_info�ӿ�ʵ�ֺ󣬴򿪴����
}
#endif

#ifdef D_CA_SUPPORT_COS
/* @brief scmode�����ӿ�*/
static D_Result 
p_stb_ca_scmode_action(void)D_FUNCPOSTFIT
{
    return D_OK;
}
#endif


#ifdef D_SYS_SUPPORT_CA
/** @brief CA�ص�����*/
static D_Result stb_ca_event_cb(D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT
{
	D_CAMsg	msg;
	
	msg.type = D_MSG_CA_EVT;
	msg.param1 = (D_U32) type;
	msg.param2 = (D_U32) param;
	
	return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}
#endif

D_Result p_cas_init(void) D_FUNCPOSTFIT
{
#if   D_CA_SUPPORT_DEF   
    d_cbman_subscribe(CA_GET_CUR_CAS, D_INVALID_HANDLE, cas_get_curr_cb, NULL);
    d_cbman_subscribe(CA_SET_CUR_CAS, D_INVALID_HANDLE, cas_set_curr_cb, NULL);
    d_cbman_subscribe(CA_GET_CUR_LAN, D_INVALID_HANDLE, cas_get_lan_cb, NULL);
    d_cbman_subscribe(CA_GET_CUR_STB_SERIALNO, D_INVALID_HANDLE, cas_get_stb_id_cb, NULL);
    d_cbman_subscribe(CA_GET_CA_PRIVATE_INFO, D_INVALID_HANDLE, cas_get_ca_private_info_cb, NULL);
    d_cbman_subscribe(CA_SET_CA_PRIVATE_INFO, D_INVALID_HANDLE, cas_set_ca_private_info_cb, NULL);
    d_cbman_subscribe(CA_GET_STB_SERIAL_STRING, D_INVALID_HANDLE, cas_get_stb_id_string_cb, NULL);    
#ifdef D_JIANGSU_BURNER_SERIAL_NUM
    d_cbman_subscribe(CA_GET_STB_SERIAL_ABV_STRING, D_INVALID_HANDLE, cas_get_stb_id_abv_string_cb, NULL);
#endif

	//d_ca_register_comp_callback(complie_cas_handler,NULL); //���ӻ�û�б���camenu����ʱע��
	
    /*ע��ca�����������ӿ�*/
    d_ca_register_scroll_callback(p_stb_ca_scroll_action, NULL); 
    
    /*ע��scmode�����ӿ�, ���ӻ���Ŀscmode�̶�Ϊ2*/
		/*ע��scmode�����ӿ�, ���ӻ���Ŀscmode�̶�Ϊ2*/
		/*(1)�޿�CA(D_CA_SUPPORT_COS��������); (2)ͬ����ѶCA; (3)����޿�CA*/
#if (defined(D_CA_SUPPORT_COS) || defined(D_CA_SUPPORT_THTFCA) || defined(D_CA_SUPPORT_DVNCA_COS))
//#ifdef D_CA_SUPPORT_COS
    d_ca_register_scmode_callback(p_stb_ca_scmode_action, NULL); 
#endif    
#if defined(D_CA_SUPPORT_ABVCA)  
    /*ע��ca��д���л����ݲ����ӿ�,Ŀǰֻ������CA�õ��˽ӿ�*/
    d_ca_register_burn_callback(p_ABVCa_send_msg_from_ca_to_otherstb, NULL); 
#endif

	d_ca_register_callback(stb_ca_event_cb, NULL);
#endif
    d_ca_open();

	D_DUMP("p_cas_Init Ok.\n");

	return D_OK;
}

