#ifndef _GS_CA_PROCESS_H_
#define _GS_CA_PROCESS_H_
/* �����ͳ��� */
#define PACK_TYPE_CHECK       0x01    /* ����� */
#define PACK_TYPE_EMM         0x03    /* EMM���� */
#define PACK_TYPE_ECM         0x04    /* ECM���� */
#define PACK_TYPE_DATE        0x05    /* ���� */

/* ������ */
#define ERR_OK                0x00    //����
#define ERR_INVALID_ADDRESS   0x01    //���ܿ���Ŵ���
#define ERR_CRC               0x02    //CRC����
#define ERR_NOT_INI           0x03    //��δ��ʼ��
#define ERR_INVALID_TYPE      0x04    //��������ݰ�����
#define ERR_UNKNOWN           0x06    //δ֪�Ĵ���
#define ERR_COMM              0x80    //ͨѶ����

#endif
