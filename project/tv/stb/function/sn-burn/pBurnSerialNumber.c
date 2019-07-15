/**@defgroup sn-burn ���к���дģ�� 
*@{*/
/** @file
* @brief ���к���дģ��
* @author ��ΰ��
* @date 2013-08-20 ��ΰ��: �����ļ�
*/

#include <stdio.h>
#include <string.h>
#include "dSerial.h"
#include "pConfig.h"
#include "pMem.h"
#include "dGraph.h"
#include "dGDev.h"
#include "dSys.h"
#include "dTask.h"
#include "dApp.h"
#include "dMsg.h"
#include "dTimer.h"
#include "dResource.h"
#include "dDebug.h"
#include "pPopMsg.h"
#include "pBurnSerialNumber.h"
#include "dFileSystem.h"
#include "pStbCaMenus.h"

#define SERIAL_MONI_PRIORITY 1
#define SERIAL_MONI_SNGL_SCAN_TIME 20
#define SERIAL_MONI_TOTAL_SCAN_TIME 600000
#define SERIAL_BUF_LENGTH 60

#if (SERIAL_BUF_LENGTH < D_CONF_DEF_STB_ID_LEN)
	#undef SERIAL_BUF_LENGTH
	#define SERIAL_BUF_LENGTH D_CONF_DEF_STB_ID_LEN
#endif


/** @brief ���崮�ڼ�ع��ܵĸ������ṹ*/
typedef struct
{
	D_HTask htask;				//������
	D_HQueue hq;				//��Ϣ����
	D_HSerial serial_hdl;		//���ھ��
	FUNCTION function;			//�����ⲿע������ĺ���ָ��
	D_Bool if_start_up;			//�Ƿ񿪻�ʱ��д
	D_U32 total_scan_time;		//���ڼ����ʱ��
	D_U32 task_start_time;		//���񴴽�ʱ��
	D_U32 curr_time;			//��ǰʱ��
}SerialMoniTask;

typedef struct
{
	D_U8* buf_rciv;	//���ڴӴ��ڽ������ݵ�buffer
	D_U8* buf_bkup;	//���ڴ������ݵı���buffer
	D_U32 buf_len;	//buffer�ĳ���
	D_LoaderParam loaderparam; //�����кŴ����loader������ʱʹ��
}SerialDataBuf;

SerialMoniTask *serial_tsk_param = NULL; //���ڼ�ع���ʹ�õĸ�����
SerialDataBuf *serial_data = NULL;	//������ʱʹ�õ�buffer


#ifdef D_BURN_SN_MODE_A       
/** @brief ��д���к�
* @param[in] flag 1�������������е�ĳʱ����д���кţ�0�����뱾����Ϣ������д���к�
	���뱾����Ϣ������д�Ƿ�ֹ����ʱ��д���ɹ��������ڽ������ʱ��дһ�Σ�������ʱ����д�ɹ����������ʱ�����ظ���д��
* @param[in] surf ͼ�α������������軭��ʾ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
D_Result p_burn_serial_number(D_U8 flag, D_GSurface * surf) D_FUNCPOSTFIT
{
	D_Char buf[D_CONF_DEF_STB_ID_LEN + 1];
	D_U8 retry = 10, i = 0;
	D_LoaderParam loaderparam;
	D_SerialAttr com;
	D_HSerial hs;
	D_SerialMode mode;
	D_Size sn_len = 0;
	D_Rect rect;
	
	if(p_conf_get_loader_param ((D_LoaderParam*)&loaderparam) != D_OK)	//��ȡloader����ʧ��
	{
		return D_ERR;
	}
	if(flag == 1)	//ֻ�п�����д���к�ʱ��Ҫ�ж��Ƿ�������кš�����ĳ�˵�ʱ��д����Ҫ���Ա��ڽ���ĳ�˵�ʱ�������к�
	{
		for(i = 0; i < D_CONF_DEF_STB_ID_LEN; i++)
		{
			if(loaderparam.stb_param_copy.stb_id[i] != -1)	//�Ѿ�д�����кţ��˳�
			{
				sn_len = strlen(loaderparam.stb_param_copy.stb_id);
//				D_DUMP("SN is %s\n", loaderparam.stb_param_copy.stb_id);
				return D_ERR;
			}
		}
	}
	if(d_serial_open() != D_OK)	//�򿪴���ʧ��
	{
		return D_ERR;
	}
	com.id = 0;
	hs = d_serial_create(&com);
	if(hs == D_INVALID_HANDLE)	//��������ʧ��
	{
		return D_ERR;
	}
	mode.baud = 115200;
	mode.data_bits = D_SERIAL_8_DATABITS;
	mode.stop_bits = D_SERIAL_1_STOPBITS;
	mode.parity = D_SERIAL_NO_PARITY;
	if(d_serial_set_mode(hs, &mode) != D_OK)	//���ô���ģʽʧ��
	{
		return D_ERR;
	}
	d_serial_flush(hs);
	if(flag == 1)	//��ʾ�ȴ�ɨ�����к�����
	{
		if(surf != NULL)
		{
			rect.x = 0;
			rect.y = 0;
			rect.w = 720;
			rect.h = 576;
			d_g_fill_rect(surf, &rect);
			d_g_set_fg (surf, d_g_map_color(surf, D_RGBA(0xFF,0xFF,0xFF,0xFF)));
			d_g_text(surf, 210, 280, "�ȴ�ɨ�����к�����...", strlen("�ȴ�ɨ�����к�����..."));
		}
	}
	while(retry--)	//�ȴ�����ɨ��ǹ���봮�ڵ�����
	{
		sn_len = D_CONF_DEF_STB_ID_LEN;
		memset(buf, 0, D_CONF_DEF_STB_ID_LEN + 1);
		if(d_serial_read(hs, &buf, sn_len) != 0)	//�Ӵ����н��յ�����
		{
			for(i = 0; i < sn_len; i++)
			{
				if(buf[i] == 0x0D)	//���һس���
				{
					break;
				}
			}
			for(; i < sn_len; i++)	//�س������������
			{
				buf[i] = 0;
			}
			memcpy(loaderparam.stb_param_copy.stb_id, (D_U8*)buf, sn_len);
			p_conf_set_loader_param ((D_LoaderParam*)&loaderparam);		//�Ѵ������кŵ�loader����д�뵽flash��
			if(flag == 1)	//��ʾ��д���кŽ���
			{
				if(surf != NULL)
				{
					d_g_set_fg (surf, d_g_map_color(surf, D_RGBA(0,0,0,0)));
					rect.x = 0;
					rect.y = 0;
					rect.w = 720;
					rect.h = 576;
					d_g_fill_rect(surf, &rect);
					d_g_set_fg (surf, d_g_map_color(surf, D_RGBA(0xFF,0xFF,0xFF,0xFF)));
					d_g_text(surf, 210, 280, "��д���кŽ���!", strlen("��д���кŽ���!"));
					d_task_wait(5000);
				}
			}
			d_serial_flush (hs);	//��մ�������
			d_serial_destroy(hs);	//ע������
			d_serial_close();		//�رմ���
//			D_DUMP("SN is %s\n", loaderparam.stb_param_copy.stb_id);
			return D_OK;	
		}
		d_serial_flush (hs);
	}
	if(flag == 1)	//��ʾ�ȴ���ʱ����д���к�ʧ��
	{
		if(surf != NULL)
		{
			d_g_set_fg (surf, d_g_map_color(surf, D_RGBA(0,0,0,0)));
			rect.x = 0;
			rect.y = 0;
			rect.w = 720;
			rect.h = 576;
			d_g_fill_rect(surf, &rect);
			d_g_set_fg (surf, d_g_map_color(surf, D_RGBA(0xFF,0xFF,0xFF,0xFF)));
			d_g_text(surf, 210, 280, "�ȴ���ʱ����д���к�ʧ�ܣ�", strlen("�ȴ���ʱ����д���к�ʧ�ܣ�"));
			d_task_wait(5000);
		}
	}
	d_serial_destroy(hs);
	d_serial_close();
	return D_ERR;
}
#endif

#if defined(D_BURN_SN_MODE_B)||defined(D_BURN_SN_MODE_E)

/** @brief Ϊ���ڼ�ط����ڴ���Դ
* @return �ɹ����ط������Դָ�룬ʧ�ܷ���NULL
*/
static SerialMoniTask* serial_monitor_start (void)D_FUNCPOSTFIT 
{
	D_U32 tmp_len = 0;
	
	serial_tsk_param = (SerialMoniTask*) PROJECT_ALLOC(sizeof (SerialMoniTask));
	if(!serial_tsk_param)
	{
		return NULL;
	}
	memset(serial_tsk_param, 0, sizeof(SerialMoniTask));
	serial_tsk_param->htask = D_INVALID_HANDLE;
	serial_tsk_param->hq = D_INVALID_HANDLE;
	
	return serial_tsk_param;
}

/** @brief  ����Ϊ���ڼ�ط�����ڴ���Դ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result serial_monitor_stop (void)D_FUNCPOSTFIT 
{
	if(!serial_tsk_param)
	{
		return D_ERR;
	}
	d_queue_destroy (serial_tsk_param->hq);
	
	serial_tsk_param->hq = D_INVALID_HANDLE;
	serial_tsk_param->htask = D_INVALID_HANDLE;
	PROJECT_FREE(serial_tsk_param);
	serial_tsk_param = NULL;
	
	return D_OK;
}

/** @brief ���ڳ�ʼ��
* @param[out] srl_hdl�����ھ��
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
static D_Result serial_interface_open (D_HSerial* srl_hdl)D_FUNCPOSTFIT 
{
	D_SerialAttr com;
	D_SerialMode mode;
	
	if(d_serial_open() != D_OK)	//�򿪴���ʧ��
	{
		return D_ERR;
	}
	com.id = 1;
	*srl_hdl = d_serial_create(&com);
	if((*srl_hdl) == D_INVALID_HANDLE)	//��������ʧ��
	{
		return D_ERR;
	}
	mode.baud = 115200;
	mode.data_bits = D_SERIAL_8_DATABITS;
	mode.stop_bits = D_SERIAL_1_STOPBITS;
	mode.parity = D_SERIAL_EVEN_PARITY;
	if(d_serial_set_mode(*srl_hdl, &mode) != D_OK)	//���ô���ģʽʧ��
	{
		return D_ERR;
	}
	d_serial_flush(*srl_hdl);
	
	return D_OK;
}

/** @brief �رմ���
* @param[in] srl_hdl�����ھ��
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
static D_Result serial_interface_close (D_HSerial srl_hdl)D_FUNCPOSTFIT 
{
	d_serial_destroy(srl_hdl);
	d_serial_close();
	
	return D_OK;
}

/** @brief ��ʼ����д���к�����Ҫ����Դ
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result sn_burn_init(void) D_FUNCPOSTFIT
{
	D_U8 i = 0;
	D_Size sn_len = 0;

	serial_data = (SerialDataBuf*)PROJECT_ALLOC(sizeof(SerialDataBuf));
	if(!serial_data)
	{
		return D_ERR;
	}
	memset(serial_data, 0, sizeof(SerialDataBuf));
	serial_data->buf_len = SERIAL_BUF_LENGTH;
	
	serial_data->buf_rciv = (D_U8*)PROJECT_ALLOC(serial_data->buf_len);
	if(!serial_data->buf_rciv)
	{
		PROJECT_FREE(serial_data);
		return D_ERR;
	}
	
	serial_data->buf_bkup = (D_U8*)PROJECT_ALLOC(serial_data->buf_len);
	if(!serial_data->buf_bkup)
	{
		PROJECT_FREE(serial_data->buf_rciv);
		PROJECT_FREE(serial_data);
		return D_ERR;
	}
	if(p_conf_get_loader_param (&(serial_data->loaderparam)) != D_OK) //��ȡloader����ʧ��
	{
		PROJECT_FREE(serial_data->buf_bkup);
		PROJECT_FREE(serial_data->buf_rciv);
		PROJECT_FREE(serial_data);
		return D_ERR;	
	}
	if(serial_tsk_param->if_start_up)
	{
/*		for(i = 0; i < D_CONF_DEF_STB_ID_LEN; i++)
		{
			if(serial_data->loaderparam.stb_param_copy.stb_id[i] != -1)	//�Ѿ�д�����кţ��˳�
			{
				sn_len = strlen(serial_data->loaderparam.stb_param_copy.stb_id);
//				D_DUMP("SN is %s\n", loaderparam.stb_param_copy.stb_id);

				PROJECT_FREE(serial_data->buf_bkup);
				PROJECT_FREE(serial_data->buf_rciv);
				PROJECT_FREE(serial_data);
				return D_ERR;
			}
		}*/
	}
	return D_OK;
}

/** @brief �Ӵ��ڽ������ݲ���д���к�
* @param[in] sl_hdl�����ھ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result sn_burn_handle(D_HSerial sl_hdl) D_FUNCPOSTFIT
{
	D_U32 valid_len = 0;
	D_U32 i = 0;
	D_Char start_str[] = "[satus]";
	D_Char end_str[] = "[finis]";
	D_U8 start_len = 0, end_len = 0;
	D_Char tmp_str_s[] = "0000007";
	D_Char tmp_str_e[] = "0000007";
	D_Bool start = D_FALSE;
	D_Char start_char = '[';
	
	start_len = strlen(start_str);
	end_len = strlen(end_str);
	
	memset(serial_data->buf_rciv, 0, serial_data->buf_len);
	if(d_serial_read(sl_hdl, serial_data->buf_rciv, serial_data->buf_len) != 0)	//�Ӵ����н��յ�����
	{
		memset(serial_data->buf_bkup, 0, serial_data->buf_len);		
		for(i = 0; i < serial_data->buf_len;)
		{
			if((D_Char)serial_data->buf_rciv[i] == start_char)	
			{
				memcpy(tmp_str_s, &serial_data->buf_rciv[i], start_len);
				memcpy(tmp_str_e, &serial_data->buf_rciv[i], end_len);
				if(strncmp(tmp_str_s, start_str, start_len) == 0)
				{
					i += start_len;
					if(i >= serial_data->buf_len)
					{
						 break;
					}
					start = D_TRUE;
				}
				else if(strncmp(tmp_str_e, end_str, end_len) == 0)
				{
//					start = D_FALSE;
//					i += start_len;
					break;
				}
				else
				{
					start = D_FALSE;
					memset(serial_data->buf_bkup, 0, serial_data->buf_len);
					valid_len = 0;
				}
			}
			if(start)
			{
				serial_data->buf_bkup[valid_len] = serial_data->buf_rciv[i];
				valid_len++;
			}
			i++;
		}
		d_serial_flush (sl_hdl);	//��մ�������
		
		if(valid_len > 0)
		{
			memcpy(serial_data->loaderparam.stb_param_copy.stb_id, serial_data->buf_bkup, D_CONF_DEF_STB_ID_LEN);
			p_conf_set_loader_param ((D_LoaderParam*)&(serial_data->loaderparam));		//�Ѵ������кŵ�loader����д�뵽flash��
			return D_OK;
		}
	}
	return D_ERR;
}

/** @brief ���к���д�������ͷ���Դ
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result sn_burn_end(void) D_FUNCPOSTFIT
{
	PROJECT_FREE(serial_data->buf_bkup);
	PROJECT_FREE(serial_data->buf_rciv);
	PROJECT_FREE(serial_data);
	serial_data = NULL;
	
	return D_OK;
}

/** @brief ��д���к�
* @param[in] sl_hdl�����ھ��
* @param[in] type����������
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result burn_serial_number(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT
{
    switch (type) 
    {
		case INITIALIZE:
			if(sn_burn_init() != D_OK)
			{
				return D_ERR;
			}
			break;
		case HANDLE:
			if(sn_burn_handle(sl_hdl) != D_OK)
			{
				return D_ERR;
			}
			break;
		case DESTROY:
			sn_burn_end();
			break;
		default:
			break;
	}
	return D_OK;
}

/** @brief ���ڼ�ز���
* @param[in] type��Ӧ�����ͣ����ݲ�ͬ����������ͬ�Ĳ���
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result serial_monitor_operator(OPERATE_TYPE type) D_FUNCPOSTFIT
{
    switch (type) 
    {
		case INITIALIZE:
			if(serial_interface_open (&(serial_tsk_param->serial_hdl)) != D_OK)
			{
				return D_ERR;
			}
			if(serial_tsk_param->function(serial_tsk_param->serial_hdl, INITIALIZE) != D_OK)
			{
				return D_ERR;
			}
			break;
		case HANDLE:
			if(serial_tsk_param->function(serial_tsk_param->serial_hdl, HANDLE) != D_OK)
			{
				return D_ERR;
			}
			break;
 		case DESTROY:
			serial_tsk_param->function(serial_tsk_param->serial_hdl, DESTROY);
			serial_interface_close (serial_tsk_param->serial_hdl);
			serial_monitor_stop ();
			break;
		default:
			break;
   }
    return D_OK;
}

/** @brief ���ڼ����������
* @param[in] arg ���
*/
static void
serial_moni_task_entry (D_Ptr arg) D_FUNCPOSTFIT
{
	D_Result	ret;
	D_U32 delta_time = 0xFFFFFFFF;
	D_Msg msg;

	if(!serial_tsk_param)
	{
#ifdef D_DEBUG
		D_ERROR ("Task resource error\n");
#endif
		d_task_exit ();
	}
	
	ret = serial_monitor_operator(INITIALIZE);
	
	if (ret != D_OK) 
	{
#ifdef D_DEBUG
		D_ERROR ("Create task error\n");
#endif
		serial_monitor_stop ();
		d_task_exit ();
	} 
	else 
	{
		serial_tsk_param->curr_time = d_sys_get_time();
		delta_time = serial_tsk_param->curr_time - serial_tsk_param->task_start_time;
		
		while (delta_time <= serial_tsk_param->total_scan_time) 
		{
			ret = d_queue_timed_recv (serial_tsk_param->hq, (D_U8*)&msg, sizeof (msg), SERIAL_MONI_SNGL_SCAN_TIME);
			if (ret == D_ERR_EMPTY) 
			{
				if(serial_monitor_operator(HANDLE) == D_OK)
				{
					break;
				}
			} 
			else if (ret < 0) 
			{
				#ifdef D_DEBUG
				D_ERROR ("Cannot receive message\n");
				#endif
				serial_tsk_param->curr_time = d_sys_get_time();
				delta_time = serial_tsk_param->curr_time - serial_tsk_param->task_start_time;
				continue;
			}
			if (DESTROY == msg.type) 
			{
				break;
			}
			serial_tsk_param->curr_time = d_sys_get_time();
			delta_time = serial_tsk_param->curr_time - serial_tsk_param->task_start_time;
		}
	}
	serial_monitor_operator(DESTROY);
	d_task_exit ();
}

/** @brief  ����Ƿ��ǿ���ʱ��д���к�
* @return ��д��ʽ���
*/
D_Bool p_serial_check_if_bur_when_start_up (void)D_FUNCPOSTFIT 
{
	return serial_tsk_param->if_start_up;
}

/** @brief �������ڼ������
* @param[in] priority �������ȼ�
* @param[in] func ע����ⲿ����ָ��
* @param[in] total_time ���ڼ�ص���ʱ��
* @param[in] if_strt_up �Ƿ񿪻�ʱ��д���кţ�D_TRUE���ǣ�D_FALSE����
* @return �ɹ�����������,ʧ�ܷ���D_INVALID_HANDLE
*/
D_HTask p_serial_monitor_create(D_S8 priority, FUNCTION func, D_U32 total_time, D_Bool if_strt_up)D_FUNCPOSTFIT 
{
	D_TaskAttr	tattr;
	D_QueueAttr	qattr;
	D_U32 tmp_tot_time = 0;

	/*����ռ�*/
	serial_tsk_param = serial_monitor_start();
	if(! serial_tsk_param) 
	{
		D_ERROR ("Cannot allocate serial interface data\n");
		return D_INVALID_HANDLE;
	}
	if(!func)
	{
		serial_monitor_stop ();
		return D_INVALID_HANDLE;
//		serial_tsk_param->function = burn_serial_number;
	}
	else
	{
		serial_tsk_param->function = func;
	}
	
	if(total_time <= SERIAL_MONI_SNGL_SCAN_TIME)
	{
		tmp_tot_time = SERIAL_MONI_TOTAL_SCAN_TIME;
	}
	else
	{
		tmp_tot_time = total_time;
	}	
	serial_tsk_param->total_scan_time = tmp_tot_time;
	serial_tsk_param->if_start_up = if_strt_up;
	
	D_TASK_ATTR_INIT (&tattr);
	D_QUEUE_ATTR_INIT (&qattr);
	
	tattr.priority = priority;	//SERIAL_MONI_PRIORITY;
	tattr.stack_size = D_SERIAL_MONI_TASK_STACK_SIZE;	
	tattr.name = "COMMoni";
	qattr.size = D_SERIAL_MONI_QUEUE_SIZE;
	
	serial_tsk_param->hq = d_queue_create (&qattr);
	if (serial_tsk_param->hq == D_INVALID_HANDLE) 
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot create serial monitor resource\n");
#endif
		serial_monitor_stop ();
		return D_INVALID_HANDLE;
	}
	
	serial_tsk_param->htask = d_task_create (&tattr, serial_moni_task_entry, (D_Ptr)(serial_tsk_param));
	if (serial_tsk_param->htask == D_INVALID_HANDLE) 
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot create serial monitor task\n");
#endif
		serial_monitor_stop ();
		return D_INVALID_HANDLE;
	}
	
#ifdef D_DEBUG
	D_DUMP ("Create serial monitor task 0x%x, %s\n", serial_tsk_param->htask, tattr.name);
#endif
	
	serial_tsk_param->task_start_time = d_sys_get_time();
	
	return serial_tsk_param->htask;
}

/** @brief  ��ô��ڼ��������
* @return ������
*/
D_HTask p_serial_monitor_get_task_hdl (void)D_FUNCPOSTFIT 
{
	if(!serial_tsk_param)
	{
		return D_INVALID_HANDLE;
	}
	return serial_tsk_param->htask;
}

/** @brief  �������ڼ������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_serial_monitor_destroy (void)D_FUNCPOSTFIT 
{
	D_AppMsg			msg;
	D_Result			ret;
		
	/*����Ӧ�ý�����Ϣ*/
	msg.type = DESTROY;
	
	if ((ret = d_queue_send (serial_tsk_param->hq, (D_U8*)&msg, sizeof(msg))) < 0) 
	{
#ifdef D_DEBUG
		D_ERROR ("Send message error\n");
#endif
		return ret;
	}	
	
        d_task_join (serial_tsk_param->htask);
	
	return D_OK;
}
#endif

#ifdef D_BURN_OTP_MODE_B

#define OTP_USB_FILE_DIR                 "c:/OTP"

/** @brief ������дOTP ��Ϣ����*/
void p_otp_monitor_usb(void)D_FUNCPOSTFIT 
{
    D_S32 ret_sys;
    D_FsVolumeInfo VolumeInfo;
	D_U32 timeout = 10;

	if(p_stb_ca_get_chipid_info() == D_OK)
	{	
		D_ERROR ("OTP data has burned!\n");
		return;
	}
    
    D_DUMP("[p_otp_monitor_usb] d_disk_check_connect:%d\n", d_disk_check_connect());
    if(!d_disk_check_connect())
        return;
    
#if HI_P_MUTIMEDIA_EN
//
#else
	d_file_system_open();
#ifdef D_SYSTEM_WIN32
	d_fs_win32_open();
#else
	d_fs_fat_open();
#endif
#endif	
	while(timeout--)
	{
	    ret_sys = d_fsm_volume_get_info(OTP_USB_FILE_DIR, &VolumeInfo);
	    if(ret_sys != D_OK)
	    {
	        D_ERROR ("[p_otp_monitor_usb] d_fsm_volume_get_info fail!\n");
			d_task_wait(1000);
	    }
	    else
	    {
	        D_ERROR ("[p_otp_monitor_usb] d_fsm_volume_get_info ok! %d\n", timeout);
	    	break;
	    }
	}    

	p_stb_ca_burn_otp_info_by_usb();
}
#endif

/**@}*/
