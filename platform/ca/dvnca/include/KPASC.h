#ifndef __ASC_20150110_H__
#define __ASC_20150110_H__

U16  KPAPPCA_SetKeyLayer(U8 layer);
U16  KPAPPCA_SetKeyAlg(U8 u8index);
U16  KPAPPCA_SetKeyMode(U8 u8index);

U16  KPAPPCA_SetDCK2(U8 *buf, U8 len, U8 *iv);
U16  KPAPPCA_SetDCK1(U8 *buf, U8 len, U8 *iv);
U16  KPAPPCA_SetECW(U16 ecmpid, U8 *buf, U8 len, U8 *iv);

//@ªÒ»° Licence id + Chip id, buf need 8 bytes
U16  KPAPPCA_GetLicenceId(U8 *buf);
U16  KPAPPCA_GetChipId(U8 *buf);

#endif
