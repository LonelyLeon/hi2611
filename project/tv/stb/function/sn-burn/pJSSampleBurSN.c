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
//#include "Hrca_dmux.h"
#include "dDsc.h"
#include "dCrc.h"
#include "pBurnSerialNumber.h"


#define SCAN_REPEAT_CNT	30
#define SERIAL_BUF_LENGTH 60

#if (SERIAL_BUF_LENGTH < D_CONF_DEF_STB_ID_LEN)
	#undef SERIAL_BUF_LENGTH
	#define SERIAL_BUF_LENGTH D_CONF_DEF_STB_ID_LEN
#endif

#define RECEIVE_DATA_SERIAL_NUM_SIZE	18//22//D_CONF_DEF_STB_ID_LEN
#define SEND_DATA_CHIP_ID_SIZE			(8 + 4)
#define SEND_DATA_CA_ID_SIZE			(16 + 4)
#define UART_CMD_LENGTH  				1
#define READ_TIMEOUT_TICK			100
/*�����в����������*/
#define CMD_SEND_CHIPID		0x01
#define CMD_GET_STB			0x05
#define CMD_SEND_CAID		0x06

#define RESULT_OK	0x11
#define RESULT_CMD_FAIL	0x12
#define RESULT_TIMEOUT	0x15
#define RET_OK			0x3C
#define RET_FAIL		0x3D
#define DATA_PACKET_END	0x55AA
#define HEADER_TAIL_LEN (4 + 4 + 2)

typedef struct
{
	D_U8* buf_rciv;	//���ڴӴ��ڽ������ݵ�buffer
	D_U8* buf_bkup;	//���ڴ������ݵı���buffer
	D_U32 buf_len;	//buffer�ĳ���
	D_LoaderParam loaderparam; //�����кŴ����loader������ʱʹ��
}SerialParam;

static SerialParam *serial_data = NULL;	//������ʱʹ�õ�buffer


#ifdef D_BURN_SN_MODE_B
/** @brief ��ʼ����д���к�����Ҫ����Դ
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result sn_burn_init(void) D_FUNCPOSTFIT
{
	D_U8 i = 0;
	D_Size sn_len = 0;

	serial_data = (SerialParam*)PROJECT_ALLOC(sizeof(SerialParam));
	if(!serial_data)
	{
		return D_ERR;
	}
	memset(serial_data, 0, sizeof(SerialParam));
	serial_data->buf_len = (SERIAL_BUF_LENGTH + HEADER_TAIL_LEN);
	
	serial_data->buf_rciv = (D_U8*)PROJECT_ALLOC(serial_data->buf_len);
	if(!serial_data->buf_rciv)
	{
		PROJECT_FREE(serial_data);
		return D_ERR;
	}
	d_dbg_set_io_func(NULL, NULL); //�رմ���
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
	if(p_serial_check_if_bur_when_start_up ())
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

static char iibuf[30]={0};

/** @brief �Ӵ��ڽ������ݲ���д���к�
* @param[in] sl_hdl�����ھ��
* @retval �ɹ�����D_OK
* @retval ʧ�ܷ���D_ERR
*/
static D_Result sn_burn_handle(D_HSerial sl_hdl) D_FUNCPOSTFIT
{
	D_U32 valid_len = 0, rcv_len = 0;
	D_U16 end_flag = 0;
	D_U32 i = 0;
	D_U32 crc = 0, tmp_crc = 0;
	D_U8 ret;
	D_U32  serial_1;
	D_U32  serial_2;
	D_U8 *ptr_c;
	
	memset(serial_data->buf_rciv, 0, serial_data->buf_len);
	rcv_len = d_serial_read(sl_hdl, serial_data->buf_rciv, serial_data->buf_len);
	if(/*d_serial_read(sl_hdl, serial_data->buf_rciv, serial_data->buf_len)*/rcv_len > 0)	//�Ӵ����н��յ�����
	{
		memset(serial_data->buf_bkup, 0, serial_data->buf_len);	
		crc = ((D_U32)((serial_data->buf_rciv[0]) << 24))|((D_U32)((serial_data->buf_rciv[1]) << 16))|((D_U32)((serial_data->buf_rciv[2]) << 8))|((D_U32)(serial_data->buf_rciv[3]));
		valid_len = ((D_U32)((serial_data->buf_rciv[4]) << 24))|((D_U32)((serial_data->buf_rciv[5]) << 16))|((D_U32)((serial_data->buf_rciv[6]) << 8))|((D_U32)(serial_data->buf_rciv[7]));
		if(((valid_len + HEADER_TAIL_LEN) > serial_data->buf_len)||(valid_len > 29))
		{
			serial_data->buf_bkup[0] = RET_FAIL;
			d_serial_flush(sl_hdl);
			d_serial_write (sl_hdl, serial_data->buf_bkup, UART_CMD_LENGTH);
			return D_ERR;
		}
		end_flag = ((D_U16)((serial_data->buf_rciv[valid_len+8]) << 8))|((D_U16)(serial_data->buf_rciv[valid_len+9]));
		if(end_flag != DATA_PACKET_END)
		{
			serial_data->buf_bkup[0] = RET_FAIL;
			d_serial_flush(sl_hdl);
			d_serial_write (sl_hdl, serial_data->buf_bkup, UART_CMD_LENGTH);
			return D_ERR;
		}
		tmp_crc = d_crc_compute_32(&(serial_data->buf_rciv[4]), (valid_len - 4 + HEADER_TAIL_LEN));
		if(tmp_crc != crc)
		{
			serial_data->buf_bkup[0] = RET_FAIL;
			d_serial_flush(sl_hdl);
			d_serial_write (sl_hdl, serial_data->buf_bkup, UART_CMD_LENGTH);
			return D_ERR;
		}
		ptr_c = &serial_data->buf_rciv[8];
		memset(iibuf,0,30);
		memcpy(iibuf, ptr_c, 8); 
		serial_1 = strtoul((D_Char*)iibuf, NULL, 16);
		
		memset(iibuf,0,30);
		memcpy(iibuf, ptr_c+8, 8); 
		serial_2 = strtoul((D_Char*)iibuf, NULL, 16);
		
		serial_data->loaderparam.lnbfreq1 = serial_1;
		serial_data->loaderparam.lnbfreq2 = serial_2;
		
		memset(serial_data->loaderparam.stb_param_copy.stb_id, 0, D_CONF_DEF_STB_ID_LEN);
		memcpy(serial_data->loaderparam.stb_param_copy.stb_id, ptr_c+16,13);
		p_conf_set_loader_param ((D_LoaderParam*)&(serial_data->loaderparam));		//�Ѵ������кŵ�loader����д�뵽flash��

		serial_data->buf_bkup[0] = RET_OK;
		d_serial_flush(sl_hdl);	//��մ�������
		d_serial_write (sl_hdl, serial_data->buf_bkup, UART_CMD_LENGTH);

		return D_OK;
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
D_Result p_js_bur_sn_handle(D_HSerial sl_hdl, OPERATE_TYPE type) D_FUNCPOSTFIT
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

#endif

/**@}*/
