
#ifndef	HRCA_FUNCPOSTFIX
#define	HRCA_FUNCPOSTFIX  
#endif

#ifdef  __cplusplus
extern "C" {
#endif
/*
���ܣ�3DES����
������
out:		���������
in:			���������
datalen:	��������ݳ���
key:		��Կ��16�ֽ�
˵��:In��Out,��ʱ��/���ܺ󽫸������뻺����(In)������
*/

void TripleDes_Encrypt(unsigned char *Out,unsigned char *In,long datalen,unsigned char *Key)HRCA_FUNCPOSTFIX;
/*
���ܣ�3DES����
������
out:		���������
in:			���������
datalen:	��������ݳ���
key:		��Կ��16�ֽ�
˵��:In��Out,��ʱ��/���ܺ󽫸������뻺����(In)������
*/
void TripleDes_Decrypt(unsigned char *Out,unsigned char *In,long datalen,unsigned char *Key)HRCA_FUNCPOSTFIX;
#ifdef  __cplusplus
}
#endif
