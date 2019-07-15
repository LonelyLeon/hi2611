
#ifndef	HRCA_FUNCPOSTFIX
#define	HRCA_FUNCPOSTFIX  
#endif

#ifdef  __cplusplus
extern "C" {
#endif
/*
功能：3DES加密
参数：
out:		输出的密文
in:			输入的明文
datalen:	输入的数据长度
key:		密钥－16字节
说明:In＝Out,此时加/解密后将覆盖输入缓冲区(In)的内容
*/

void TripleDes_Encrypt(unsigned char *Out,unsigned char *In,long datalen,unsigned char *Key)HRCA_FUNCPOSTFIX;
/*
功能：3DES解密
参数：
out:		输出的明文
in:			输入的密文
datalen:	输入的数据长度
key:		密钥－16字节
说明:In＝Out,此时加/解密后将覆盖输入缓冲区(In)的内容
*/
void TripleDes_Decrypt(unsigned char *Out,unsigned char *In,long datalen,unsigned char *Key)HRCA_FUNCPOSTFIX;
#ifdef  __cplusplus
}
#endif
