/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-11-02      lim            created              ---
1.1		   2013-03-06	   lim			  modify               ---

*************************************************************************************************/

#ifndef XGCA_TYPE_H_
#define XGCA_TYPE_H_

/*�����*/
#define CLA_GENERAL				0x00	  //ͨ������
#define CLA_SPECIAL				0x80	  

/*ָ����*/
//ͨ������ ָ��
#define INS_GET_RESPONSE		0xc0	  //Get Response

//������������ ָ��
#define INS_TS_PACKAGE			0x33	  //����TS���ݰ�
#define INS_IPPV				0x35	  //�Ƿ��տ�IPPV

//������Ϣ���� ָ��
#define INS_CAS_LIST			0x40	  //���֧�ֵ�CAS�б�
#define INS_ECM_FILTER			0x41	  //���ECM���˲���
#define INS_EMM_FILTER			0x41	  //���EMM���˲���
#define INS_GET_CARD_INFO		0x56	  //��ȡ����Ϣ
#define INS_GET_PPC				0x43	  //���PPC��Ȩ����б�
#define INS_ZONE_LIMI			0x45	  //��ȡ�������������
										  
//����������� ָ��
#define INS_VERIFY_MATCH		0x8d	  //У��������
#define INS_BOUND				0x8d	  //����󶨿�Ƭ
										  
//��ĸ������ ָ��
#define INS_GET_FEED_DATA		0x63	  //��ȡι������
#define INS_FEED_CARD			0x61	  //ι��
#define INS_GET_MAIN_SUB_CARD	0x62	  //��ȡ������ĸ����Ϣ


/*����ֵ��sw1 sw2��*/

//����Ӧ��
#define SUCCESS_XGCA			0x9000	  //�ɹ�
#define INVALID_INSTRUCTION		0x6000	  //�Ƿ�����
#define GET_RESPONSE			0x61	  //(0x61��sw1��ֵ)Ҫ���ն��豸����Get Response ������ȡ�û���������. sw2��ֵ�ǻ��������ݳ��ȡ�
#define WRONG_LENGTH			0x6700	  //�򳤶ȴ���
#define CARD_FORMAT1_FAIL		0x6868	  //��Ƭδ����ʽ��
#define CARD_FORMAT2_FAIL		0x68fc	  //��Ƭδ���Ӧ�ø�ʽ��
#define WRONG_P1_P2				0x6a86	  //p1��p2��������
#define INVALID_NOT_SUPPORT		0x6a81	  //���֧��
#define INS_WRONG_LENGTH		0x6c	  //(0x6c��sw1��ֵ)���������峤�ȴ���Ӧ��Ϊsw2��ֵ��

//Get Response ����
#define NO_DATA					0x6401	  //�����ݿ�ȡ

//����TS���ݰ�
#define TABLE_FORMAT_NOT_SUPP	0x6203	  //��֧�ֵİ���ʽ�汾
#define CA_NOT_SUPPORT			0x6204	  //��֧�ֵ�CA�汾
#define NET_NOT_SUPPORT			0x6205	  //��֧�ֵ�����ϵͳ
#define WRONG_FILTER			0x6206	  //����Ĺ��˹���
#define OPERATE_FAIL			0x6207	  //����ʧ��
#define START_SER_SUCCESS		0x6208	  //�������ò����ɹ�
#define STOP_SER_SUCCESS		0x6209	  //���񶳽�����ɹ�
#define NEED_MATCH				0x620a	  //��Ҫ�������
#define BALANCE_NOT_ENOUGH		0x620b	  //Ǯ������
#define NEED_FEED_CARD			0x620c	  //�ӿ����ڣ���Ҫι��
#define NIT_ZONE_FAIL			0x620d	  //NIT��������֤ʧ��
#define NEED_CORRECT_NIT		0x620e	  //��δͨ��������֤����Ҫ��ȷ��NIT
#define SER_STOPED				0x6244	  //���񱻶���
#define CARD_DELETED			0x62aa	  //����ɾ��
#define FILE_SYS_WRONG			0x6884	  //�ļ�ϵͳ����
#define LEVEL_LIMITED			0x6885	  //�����տ��Ľ�Ŀ����
#define DECRYPT_FAIL			0x6897	  //���ܴ���
#define NO_AUTHORIZATION		0x6899	  //����Ȩ
#define TABLE_FORMAT_WRONG		0x6a82	  //����İ���ʽ

//�տ�IPPV
#define PAY_IPP_FAIL			0x689a	  //����ִ��ʧ��

//���֧�ֵ�CAS�б�
#define P1_P2_NOT_ZERO			0x6a86	  //p1��p2������0
#define NO_VALID_INFO			0x6200	  //�޿��õ���Ϣ

//���ָ��CAS��ECM\EMM���˲���
#define CARD_INIT_FAIL			0x6200	  //��Ƭδ���Ӧ�ó�ʼ��
#define INVALID_CAID			0x6204	  //δ֪��CAID

//��ȡ��Ƭ��Ϣ
#define CARD_NOT_INIT			0x6801	  //��Ƭδ��ɳ�ʼ��

//���PPC��Ȩ����б�
/*
#define INVALID_CAID			0x6204	  //δ֪��CAID
#define FILE_SYS_WRONG			0x6884	  //�ļ�ϵͳ����
*/

//��ȡ��Ƭ�����������
/*
#define CARD_NOT_INIT			0x6801	  //��Ƭδ��ɳ�ʼ��
*/

//У��������
#define CARD_NOT_MATCH_STB		0x6301	  //��δ���κ�STB���
#define VERIFY_FAIL				0x6303	  //У��ʧ��
#define VERIFY_UNEXPECTED_WRONG	0x6304	  //У��ɹ��������ؿ�Ƭ����������������
#define CARD_NOT_REGISTER		0x6305	  //��δע��

//����󶨿�Ƭ
#define CARD_ALREADY_MATCH		0x6302	  //���Ѿ���ĳһSTB���
#define BOUND_FAIL				0x6303	  //��ʧ��
#define BOUND_UNEXPECTED_WRONG	0x6304	  //�󶨳ɹ��������ؿ�Ƭ����������������
/*
#define CARD_NOT_REGISTER		0x6305	  //��δע��
*/

//��ȡι������
#define GET_FEED_FAIL			0x6280	  //��Ϊ�ӿ����޷���ȡι������
#define UNKNOWN_TIME			0x6281	  //δ֪�ĵ�ǰʱ�䣬����Ҫ�Ȼ�ȡECM����
/*
#define INVALID_CAID			0x6204	  //δ֪��CAID
*/

//ι��
#define DONOT_NEED_FEED			0x6282	  //��δĸ��������Ҫι������
#define WRONG_FEED_DATA			0x6285	  //�����ι������						

//��ȡ��Ƭ����ĸ����Ϣ
#define NO_EXPIRE_TIME			0x6286	  //����ĸ�������ӿ�����ʱ��
/*
#define CARD_NOT_INIT			0x6801	  //��Ƭδ��ɳ�ʼ��
*/

#endif //end XGCA_TYPE_H_
