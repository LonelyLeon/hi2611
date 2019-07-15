////////////////////////////////////////////////////////////////
#ifndef EBOOKPARSE_H_
#define EBOOKPARSE_H_

#include "dTypes.h"


#define STR_LENGTH          20

#define E_CONTROL_PIC       1
#define E_CONTROL_TXT       2
#define E_CONTROL_EDIT      3
#define E_CONTROL_SLIDER    4
#define E_CONTROL_LYRIC     5

#define E_KEY_UP            1
#define E_KEY_DOWN         	2
#define E_KEY_LEFT          3
#define E_KEY_RIGHT         4
#define E_KEY_OK			5

#define E_LINK_EXIT         0
#define E_LINK_ETM          1
#define E_LINK_MP3          2

#define E_NODE_NUM          40

#define E_DIF               8

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} CRect;

typedef struct
{
    CRect rect;
    unsigned char ctrFlag;

    int picID;
    char picType;
    int picMouseDownID;
    char picMouseDownType;
    int picFocusID;
    char picFocusType;

    int linkID;
    char linkType;

    /*
     char picName[STR_LENGTH];
     //  char picMouseDownName[STR_LENGTH];
     char picFocus[STR_LENGTH];

     char linkName[STR_LENGTH];
     */

    /*
     INT showFlag;

     INT charFont;
     INT charStyle;
     INT charHeight;

     INT charColor;
     INT charColorF;
     INT charColorD;
     */
} EBookNode;

void HREBK_getLabel(D_U8* pStr);
void HREBK_getParaValue(D_U8* pStr);
void HREBK_parseString(D_U8* pStr);

void HREBK_keyEvent(D_U8 keyFlag);
void HREBK_screenEvent(D_U32 pos);

void HREBK_showEBook(void);

void HREBK_bookInit(void);
D_S8 HREBK_bookCompare(D_U32 x0, D_U32 x1);

void HREBK_showFocusItem(void);
D_U32 HREBK_getNextFocusItem(D_U8 flag);
D_S32 HREBK_getFocusItem(D_U32 x, D_U32 y);

#endif

