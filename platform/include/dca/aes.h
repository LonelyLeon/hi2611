
#ifndef _AES_H_
#define _AES_H_

#ifdef AES_EXPORTS
#define AES_API __declspec(dllexport)
#else
#define AES_API //__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define xdata 
#define ENCRYPT 1
#define DECRYPT 0

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef unsigned char	u_char;


void AES_API aes_cbc(
             u8      SL_OpeVal, /* ENCRYPT or DECRYPT */
             void      *SL_Src,
             int     SL_Len,
             void    *SL_Key1,/*key1*/
             void      *SL_Key2,/*key2*/
             void      *SL_Dest 
             );

void AES_API aes_ecb(
             u8      SL_OpeVal, /* ENCRYPT or DECRYPT */
             void      *SL_Src,
             int     SL_Len,
             void    *SL_Key1,/*key1*/
             void      *SL_Dest
             );





#ifdef __cplusplus
}
#endif

#endif

