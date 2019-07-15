/**@defgroup font 字库
*@{*/
/** @file
* @brief 外部固定点阵字体
* @author 覃宜
* @date 2014-2-20 覃宜: 建立文件
*/

#include "dFont.h"
#include "dCharset.h"
#include "dDebug.h"
#include "dCBMan.h"
#include "pFontOther.h"
#include "fixed_gbk_24_fnt.c"


#define TOTAL_OTHER_CHARS P_GBK_CHAR_CNT

#define D_IS_GBK(_ptr) (((_ptr[0] >= 0x81) && (_ptr[0] < 0xa1) && (_ptr[1] >= 0x40) && (_ptr[1] < 0xff)) || \
                        ((_ptr[0] >= 0xaa) && (_ptr[0] < 0xff) && (_ptr[1] >= 0x40) && (_ptr[1] < 0xa1)))
        
typedef struct
{
    D_U8        FontMaxHeight;
    D_U8        FontMaxWidth;
    D_U8        FontWidthBytes;
    D_U8        FontLineSpace;
    D_U8        CharBitmaps[4];
} GBKFontHeaders;

static D_Result gbk_font_init (D_Font *fnt, D_FontDesc *fnt_desc) D_FUNCPOSTFIT
{
    GBKFontHeaders *hdr = (GBKFontHeaders*)fnt_desc->font_data;

    if(fnt_desc->cset != D_CHARSET_GBK)
    {
        D_ERROR("ext font engine do not support %d cset!\n", fnt_desc->cset);
        return D_ERR;
    }

    fnt->cset = fnt_desc->cset;
    fnt->size = hdr->FontMaxHeight;
    fnt->obj = (D_Ptr)fnt_desc->font_data;

    return D_OK;
}

static D_Result gbk_font_deinit (D_Font *fnt) D_FUNCPOSTFIT
{
    return D_OK;
}

/** @brief 计算字体大小
* @param[in] fnt 字库指针
* @param[in] chr    显示字符指针
* @param[out] w     返回字符宽度
* @param[out] h     返回字符高度
* @param[out] b     返回字符基线位置
* @return 成功返回D_OK，失败返回D_ERR
*/
static D_Result
gbk_font_char_size (D_Font *fnt, D_Char *chr, D_Coord *w, D_Coord *h, D_Coord *b) D_FUNCPOSTFIT
{
    GBKFontHeaders *hdr = (GBKFontHeaders*) fnt->obj;

    if (w)
    {
        *w = hdr->FontMaxWidth;
    }
    if (h)
    {
        *h = hdr->FontMaxHeight;
    }
    if (b)
    {
        *b = hdr->FontMaxHeight;
    }
    return D_OK;
}

/** @brief 显示一个字模
* @param[in] fnt 字库指针
* @param[in] chr    显示字符指针
* @param[in] mask   显示字模指针
* @return 成功返回D_OK，失败返回D_ERR
*/
static D_Result
gbk_font_get_char (D_Font *fnt, D_Char *chr, D_FontCharMask *mask) D_FUNCPOSTFIT
{
    GBKFontHeaders *hdr = (GBKFontHeaders*) fnt->obj;
    D_U16 idx, chbcnt;
    D_U8 *pb = (D_U8*)chr;

    /*取字模*/

    if (pb[0] >= 0xaa)
    {
        idx = (pb[0] - 0xaa) * (0xa1 - 0x40) + (pb[1] - 0x40);
        idx = idx + (0xff - 0x40) * (0xa1 - 0x81);
    }
    else
    {
        idx = (pb[0] - 0x81) * (0xff - 0x40) + (pb[1] - 0x40);
    }
    chbcnt = hdr->FontWidthBytes * hdr->FontMaxHeight;

    mask->left = 0;
    mask->top = 0;
    mask->width = hdr->FontMaxWidth;
    mask->height = hdr->FontMaxHeight;
    mask->pitch = hdr->FontWidthBytes;
    mask->bpp = 1;
    mask->mask = hdr->CharBitmaps + idx * chbcnt;

    return D_OK;
}

/** @brief   字体操作*/
const D_FontOp gbk_font_dianzhen_font_ops =
{
    gbk_font_init,
    gbk_font_deinit,
    gbk_font_char_size,
    gbk_font_get_char,
    NULL,
};


static void font_op_next_char_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_CCNextCharHookParam *nextChar = (D_CCNextCharHookParam *)obj_data;
    D_U8 *ptr = (D_U8*)nextChar->str;
    D_Result ret = D_ERR;
    D_Charset cs = D_CHARSET_UNKNOWN;

    if(D_IS_GBK(ptr))
    {
        ptr += 2;
        cs = D_CHARSET_GBK;
        ret = D_OK;
    }

    nextChar->str = (D_Char*)ptr;
    *(nextChar->ret) = ret;
    *(nextChar->cs) = cs;
}

static void font_op_next_word_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_CCNextWordHookParam *nextWord = (D_CCNextWordHookParam *)obj_data;
    D_U8 *ptr = (D_U8*)nextWord->str;
    D_Result ret = D_ERR;

    if(D_IS_GBK(ptr))
    {
        ptr += 2;
        ret = D_OK;
    }

    nextWord->str = (D_Char*)ptr;
    *(nextWord->ret) = ret;
}

/*外部字库初始化，即创建与注册*/
void p_gbk_font_init(void) D_FUNCPOSTFIT
{
    D_Font *gbk_fnt;
    D_FontDesc fnt_desc;

    fnt_desc.font_type = D_FONT_DIANZHEN_OTHER;
    fnt_desc.cset = D_CHARSET_GBK;
    fnt_desc.size = 24;
    fnt_desc.font_op = (D_Ptr)&gbk_font_dianzhen_font_ops;
    fnt_desc.font_data = (D_U8*)fixed_gbk_char_fnt_buf;
    fnt_desc.font_data_size = sizeof(fixed_gbk_char_fnt_buf);
    gbk_fnt = d_font_create(&fnt_desc);
    d_cbman_subscribe(PL_CC_NEXT_CHAR, D_INVALID_HANDLE, font_op_next_char_cb, NULL);
    d_cbman_subscribe(PL_CC_NEXT_WORD, D_INVALID_HANDLE, font_op_next_word_cb, NULL);
    d_font_set(gbk_fnt, 24);
}


/**@}*/
