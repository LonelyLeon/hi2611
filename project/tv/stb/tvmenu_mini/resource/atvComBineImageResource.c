#include    "atvImageResource.h"
enum
{
    _internal_use_only_IID_HOR = 0,
    _internal_use_only_IID_VER = 1,
    _internal_use_only_IID_MAT = 2,
    _internal_use_only_IID_USER = 3,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_button_menu[] =
{
    _internal_use_only_IID_HOR,
    atv_IMG_ID_menu_button_left,
    atv_IMG_ID_menu_button_normal,
    atv_IMG_ID_menu_button_right,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_button_menu_focus[] =
{
    _internal_use_only_IID_HOR,
    atv_IMG_ID_menu_button_left_focus,
    atv_IMG_ID_menu_button_normal_focus,
    atv_IMG_ID_menu_button_right_focus,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_scroll_no_focus[] =
{
    _internal_use_only_IID_HOR,
    atv_IMG_ID_scroll_left_no_focus,
    atv_IMG_ID_scroll_normal_no_focus,
    atv_IMG_ID_scroll_right_no_focus,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_scroll_focus[] =
{
    _internal_use_only_IID_HOR,
    atv_IMG_ID_scroll_left_focus,
    atv_IMG_ID_scroll_normal_focus,
    atv_IMG_ID_scroll_right_focus,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_scroll_enable[] =
{
    _internal_use_only_IID_HOR,
    atv_IMG_ID_scroll_left_enable,
    atv_IMG_ID_scroll_normal_enable,
    atv_IMG_ID_scroll_right_enable,
};

static PREFIXCONST short POSTCONST _atv_IMB_ID_COMB_white_background[]={
	_internal_use_only_IID_MAT, 
	atv_IMG_ID_white_background_lu, 
	atv_IMG_ID_white_background_mu, 
	atv_IMG_ID_white_background_ru, 
	atv_IMG_ID_white_background_lm, 
	atv_IMG_ID_white_background_middle, 
	atv_IMG_ID_white_background_rm, 
	atv_IMG_ID_white_background_ld, 
	atv_IMG_ID_white_background_md, 
	atv_IMG_ID_white_background_rd, 
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_music_select[]={
	_internal_use_only_IID_HOR, 
	atv_IMG_ID_music_select_left, 
	atv_IMG_ID_music_select_middle, 
	atv_IMG_ID_music_select_right,
};

static PREFIXCONST short POSTCONST _atv_IMG_ID_COMB_music_select_focus[]={
	_internal_use_only_IID_HOR, 
	atv_IMG_ID_music_select_focus_left, 
	atv_IMG_ID_music_select_focus_middle, 
	atv_IMG_ID_music_select_focus_right,
};

static PREFIXCONST short POSTCONST _atv_IMB_ID_COMB_zhilian_main_focse[]={
	_internal_use_only_IID_MAT, 
	atv_IMG_ID_main_zhilian_focse_1, 
	atv_IMG_ID_main_zhilian_focse_2, 
	atv_IMG_ID_main_zhilian_focse_3, 
	atv_IMG_ID_main_zhilian_focse_4, 
	NULL, 
	atv_IMG_ID_main_zhilian_focse_5, 
	atv_IMG_ID_main_zhilian_focse_6, 
	atv_IMG_ID_main_zhilian_focse_7, 
	atv_IMG_ID_main_zhilian_focse_8, 
};

static PREFIXCONST short *POSTCONST img_type_entries[] =
{
    _atv_IMG_ID_COMB_button_menu,
    _atv_IMG_ID_COMB_button_menu_focus,
    _atv_IMG_ID_COMB_scroll_no_focus,
    _atv_IMG_ID_COMB_scroll_focus,
    _atv_IMG_ID_COMB_scroll_enable,
    _atv_IMB_ID_COMB_white_background,
    _atv_IMG_ID_COMB_music_select,
    _atv_IMG_ID_COMB_music_select_focus,
_atv_IMB_ID_COMB_zhilian_main_focse,
};

const short* atv_LoadCombineImageData(int ids)
{
    if(ids < atv_IMG_ID_COMB_START || ids >= atv_COMB_ID_ENUM_MAX)
        return 0;
    ids -= (atv_IMG_ID_COMB_START);
    return img_type_entries[ids];
}
