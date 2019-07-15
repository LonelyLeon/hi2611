/*
*********************************************************************************************************
*
*                                              ---HI1018---
*                        (c) Copyright Since 2001, 北京海尔集成电路设计有限公司
*                                           All Rights Reserved
*
*                                       HIC-S0-XX-00-V1.0.1(9001)
*
*********************************************************************************************************
*/

#ifndef _EBOOK_INTERFACE_H
#define _EBOOK_INTERFACE_H

#include "dTypes.h"

int HREBK_parseFile(D_U32 fileID);
void HREBK_showPic(D_U32 picID, D_U32 x, D_U32 y, D_U32 w, D_U32 h, D_U8 type);
//void HREBK_showPic(D_U32 picID, D_U32 x, D_U32 y, D_U8 type);
void HREBK_playMp3(D_U32 mp3ID);
void HREBK_exit(void);

#endif  // _EBOOK_INTERFACE_H


