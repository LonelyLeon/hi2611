/** @file
* @brief Smart���ӿ��豸����
* @author ���
* @date 2005-8-18 ���: �����ļ�
*/

#ifndef _D_SCI_H_
#define _D_SCI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

#define  D_SMART_MAX_HISTORY     15
#define  D_SMART_MAX_ATR         30

/**	@brief ���ܿ��ӿ��豸���*/
typedef D_Handle	D_HSCI;

typedef struct
{
    D_GPIO_PortBit detect;
    D_GPIO_PortBit reset;
    D_GPIO_PortBit vcc_cmd;
    D_Bool open_close;
    D_U8 uart_no;
    D_U8 pwm_sel;
    D_GPIO_PortBit sw_3_5v;
    D_U8 sc_mode;//0С�� 1��
}D_SCOpenParam;

/** @brief ���ݴ��䷽��*/
typedef enum {
	D_SCI_DIR_READ,		/**< ������*/
	D_SCI_DIR_WRITE		/**< д����*/
} D_SCIDirection;

/**< @brief ���ܿ�����Э��*/
typedef enum {
	D_SCI_PROTOCOL_T0,/**< T0����Э��*/
	D_SCI_PROTOCOL_T1	/**< T1����Э��*/
} D_SCIProtocol;

/** @brief ���ܿ��ӿ��豸����*/
typedef struct {
	D_ID		id;		/**< ���豸ID*/
} D_SCIAttr;

/** @brief ��ȱʡֵ��ʼ��SCI����*/
#define D_SCI_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ���ܿ�״̬*/
typedef struct {
	D_Bool	inserted;	/**< ���ܿ��Ѿ�����*/
} D_SCIStatus;

/** @brief ֹͣλ���� */
typedef enum StopBits
{
    STOPBITS__0_5 = 0,
    STOPBITS__1_0 = 1,
    STOPBITS__1_5 = 2,
    STOPBITS__2_0 = 3
} D_StopBits;

/** @brief SCI communication parameters */
typedef struct _D_SCIParam
{
    D_U32  baud;
		D_U32	 wwt;
		D_U32	 guard_time;
    D_StopBits      	StopBits;

} D_SCIParam;

/** @brief ���ܿ��ӿ�ϵͳ��ʼ��
*
*	�ڵ������ܿ���������ʱ���ȵ��ô˺���
* @param param  ��ʼ���ṹ
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_sci_open (D_SCOpenParam *param) D_FUNCPOSTFIT;

/** @brief ���ܿ��ӿ�ϵͳ��ʼ����ǿ��
*
*	�ڵ������ܿ���������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_sci_open_ex (void) D_FUNCPOSTFIT;

/** @brief ���ܿ��ӿ�ϵͳ��ֹ
*
* �������ʱ���ͷ����ܿ��ӿ�ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_sci_close (void) D_FUNCPOSTFIT;

/** @brief ����һ�����ܿ��ӿ��豸
* @param attr	���ܿ��ӿ��豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return       �ɹ�ʱ�������ܿ��ӿ��豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HSCI		d_sci_create (D_SCIAttr	*attr) D_FUNCPOSTFIT;

/**	@brief ���豸����
* @param  hsci										���ܿ����
* @retval D_OK										�����ɹ�
* @ertval D_ERR_INVALID_HANDLE		�豸�����Ч		
*/
D_Result	d_sci_lock(D_HSCI hsci) D_FUNCPOSTFIT;

/**	@brief ���豸����
* @param  hsci										���ܿ����
* @retval D_OK										�����ɹ�
* @ertval D_ERR_INVALID_HANDLE		�豸�����Ч		
*/
D_Result	d_sci_unlock(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief ����һ�����ܿ��ӿ��豸
* @param hsci	                    	�豸���
* @retval D_OK	                    �ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE			�����Ч
*/
D_Result	d_sci_destroy (D_HSCI hsci) D_FUNCPOSTFIT;


/** @brief ȡ���ܿ�״̬
* @param hsci		                	���ܿ����
* @param status	                  ���ܿ�״̬
* @retval D_OK	                  �����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
* @retval D_ERR_IO								����IO����
*/
D_Result	d_sci_get_status (D_HSCI hsci, D_SCIStatus *status) D_FUNCPOSTFIT;

/** @brief �趨���ܿ��ӿڲ���
* @param hsci		                	���ܿ����
* @param param	                  SCI����
* @retval D_OK	                  �����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
* @retval D_ERR_NO_DEV						û�п�����
* @retval D_ERR_IO								����IO����
*/
D_Result	d_sci_set_param (D_HSCI hsci, D_SCIParam *param) D_FUNCPOSTFIT;

/** @Э������ѡ��
* @param hsci                     ���ܿ����
* @param pts_bytes_p              Э������ѡ������
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_NO_DEV						û�п�����
* @retval D_ERR_IO								����IO����
* @retval D_OK										�����ɹ�
* @retval D_ERR_INVALID_ARGUMENT	������Ч
*/
D_Result    d_sci_pts(D_HSCI hsci, D_U8 *pts_bytes_p) D_FUNCPOSTFIT;

/** @brief ���ܿ���λ
* @param hsci											���ܿ����
* @param atr											���ATR���ݵĻ�����
* @param len											ATR���ݻ������Ĵ�С
* @retval D_OK										�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
* @retval D_ERR_NO_DEV						û�п�����
* @retval D_ERR_IO								����IO����
*/
D_Result	d_sci_reset (D_HSCI hsci, D_U8 *atr, D_Size *len) D_FUNCPOSTFIT;

/** @brief ���ܿ�T0Э�����ݴ���
* @param hsci											���ܿ����
* @param capdu										�������
* @param clen											���������С
* @param rapdu										���ջ�����
* @param rlen											���ջ�������С
* @retval D_OK										�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
* @retval D_ERR_NO_DEV						û�п�����
* @retval D_ERR_IO								����IO����
*/
D_Result	d_sci_t0_command (D_HSCI hsci, D_U8 *capdu, D_Size clen, D_U8 *rapdu, D_Size *rlen) D_FUNCPOSTFIT;

/** @brief ���ܿ�T1Э�����ݴ���
* @param hsci											���ܿ����
* @param capdu										�������
* @param clen											���������С
* @param rapdu										���ջ�����
* @param rlen											���ջ�������С
* @retval D_OK										�����ɹ�
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	������Ч
* @retval D_ERR_NO_DEV						û�п�����
* @retval D_ERR_IO								����IO����
*/
D_Result	d_sci_t1_command (D_HSCI hsci, D_U8 *capdu, D_Size clen, D_U8 *rapdu, D_Size *rlen) D_FUNCPOSTFIT;


/** @brief ������ܿ��Ĳ���
* @param hsci                   ���ܿ���� 
* @@retval D_OK	                �����ɹ�
* @retval D_ERR_INVALID_HANDLE	�����Ч 
*/
D_Result	d_sci_deactivate(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief ���ܿ�����
* @param hsci                       �豸���
* @retval D_OK                      �����ɹ�
* @retval D_ERR_INVALID_HANDLE			�豸�����Ч
*/      

D_Result	d_sci_hw_reset(D_HSCI hsci) D_FUNCPOSTFIT;

/** @brief �ӽӿڶ����ݵ����ܿ���
* @param hsci		                	���ܿ����
* @param buf	                    ��Ŷ������ݵĻ�����
* @param size											�������ݵĴ�С
* @retval                         ����ʵ�ʶ�����ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_FAULT	            ����ʧ��
*/
D_Size	d_sci_hw_read (D_HSCI hsci,  D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief �����ܿ�д��ӿ�
* @param hsci		                	���ܿ����
* @param buf	                    д���ݵĻ�����
* @param size                     д�����ݵĴ�С
* @retval 0	                  ����ʵ��д����ֽ���,��������ظ���
* @retval D_ERR_INVALID_HANDLE		�豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT	dataΪNULL
* @retval D_ERR_FAULT	            ����ʧ��
*/
D_Size	d_sci_hw_write (D_HSCI hsci, D_U8 *buf,  D_Size size) D_FUNCPOSTFIT;

/** @brief ��ȡ��ʷ�ֽ�
* @param history											������ʷ�ֽ�
* @param historylength_p									������ʷ�ֽڴ�С

*/
D_Result
d_sci_gethistory (D_U8 *history, D_U8 *historylength_p) D_FUNCPOSTFIT;

/** @brief �趨���ܿ��ӿڲ�������ʹ��*/
D_Result
d_sci_set_param_ex (D_HSCI hsci, D_SCIParam *param) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
