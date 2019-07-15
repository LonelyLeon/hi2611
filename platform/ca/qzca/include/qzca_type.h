#ifndef QZCA_TYPE_H_
#define QZCA_TYPE_H_

//�����
#define GS_CLA                            0xE5
//#define HR_CONST HR_BYTE PACK_TYPE_DATE   0x05 //������Ȩ����ʱ��

//ָ����
#define INS_GET_CA_SYSTEM_ID			  0x22
#define INS_GET_SMARTCARD_ID			  0x24
#define INS_GET_CARD_NO					  0x26
#define INS_GET_CARD_ID					  0x28
#define INS_GET_AREA_CODE				  0x2A
#define INS_CHECK_SMART					  0x7C
#define INS_PROCESS_ECM					  0x7E
#define INS_PROCESS_EMM					  0x36
#define INS_GET_STB_SN				      0x38
#define INS_GET_VERSION_INFO			  0x3A
#define INS_GET_SUBSCRIBER_INFO			  0x3C
#define INS_GET_EXPIRE_DATE 			  0x2C
#define INS_GET_CHILD_AUTH_INFO           0x46
#define INS_SET_CHILD_AUTH_INFO           0x48
#define INS_READ_CHILD_AUTH_INFO          0x4a
#define INS_GET_CARD_TYPE                 0x4c
//������
#define PARA_DEFAULT                      0

//����ֵ
/*û��״̬��*/
#define NO_SW1SW2                         0x0000
/*״̬��ȷ*/
#define SW1SW2_OK                         0x9000
/*���ܿ��ڴ����*/
#define SW1SW2_MEMORY_ERROR               0x6581
/*APDU�����(lc)����*/
#define SW1SW2_WRONG_LC_LENGTH            0x6700
/*���ݴ��� ͨ����CRC����*/
#define SW1SW2_INCORRECT_DATA             0x6A80
/*APDU��������*/
#define SW1SW2_INCORRECT_PARA             0x6A86
/*APDU �����ֽڳ��ȣ�le������*/
#define SW1SW2_WRONG_LE_LENGTH            0x6C00
/*APDU���֧��*/
#define SW1SW2_INS_NOT_SUPPORTED          0x6D00
/*APDU �����벻֧��*/
#define SW1SW2_CLA_NOT_SUPPORTED          0x6E00
/*δ֪���ʹ���һ����ͨѶ����*/
#define SW1SW2_GENERAL_ERROR              0x6F00
/*��Ȩ����*/
#define SW1SW2_EXPIRED                    0x6FA0
/*���������*/
#define SW1SW2_STB_SN_NOT_MATCH           0x7000
/*���ܿ�δ��ʼ��*/
#define SW1SW2_CARD_NOT_INIT              0x7001
/*�����SUPER_CAS_ID*/
#define SW1SW2_INCORRECT_SUPER_CAS_ID     0x7002
/*��������ܿ��ţ� ���˵����ݲ������ſ���*/
#define SW1SW2_INCORRECT_SMARTCARD_ID     0x7003
/*PPV����*/
#define SW1SW2_PPV_EXCEED                 0x7004
/*���ܿ�û������Ϊ�������*/
#define SW1SW2_NOT_PAIRED                 0x7005
/*Ƶ��δ��Ȩ*/
#define SW1SW2_ECM_NOT_AUTHORIZED         0x7006
/*�����޲�*/
#define SW1SW2_LIMIT_AREA                 0x7007
/*���޲�*/
#define SW1SW2_LIMIT_CARD                 0x7008
/*���ܿ�û������Ϊ�ӿ�ģʽ*/
#define SW1SW2_NOT_CHILD_MODE             0x7009
/*û���ӿ���Ȩ*/
#define SW1SW2_NO_CHILD_AUTH              0x700a
/*�ӿ�δ��Ȩ*/
#define SW1SW2_CHILD_NOT_AUTHORIZED       0x700b
/*�����ӿ���Ȩ��ʱ*/
#define SW1SW2_CHILD_AUTH_TIMEOUT         0x700c
/*�ӿ���Ȩ����*/
#define SW1SW2_CHILD_AUTH_EXPIRED         0x700d


/* ������ */
#define  ERR_OK  						  0x19
#define  ERR_CRC   						  0x1a
#define  ERR_NOT_INI  					  0x1b//��δ��ʼ��

#endif
