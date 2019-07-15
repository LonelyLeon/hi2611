#include	"tImageResource_tv.h"
enum{
	_internal_use_only_IID_HOR=0,
	_internal_use_only_IID_VER=1,
	_internal_use_only_IID_MAT=2,
	_internal_use_only_IID_USER=3,
};
static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_Tv_msg_box[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Tv_Pop_Info_left, 
	tv_IMG_ID_Tv_Pop_Info_middle, 
	tv_IMG_ID_Tv_Pop_Info_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_search[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Pop_Box_left, 
	tv_IMG_ID_Pop_Box_middle, 
	tv_IMG_ID_Pop_Box_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_and_video[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Tv_Video_left, 
	tv_IMG_ID_Tv_Video_middle, 
	tv_IMG_ID_Tv_Video_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_list1[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Channel_List_left1, 
	tv_IMG_ID_Channel_List_middle1, 
	tv_IMG_ID_Channel_List_right1,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_list2[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Channel_List_left2, 
	tv_IMG_ID_Channel_List_middle2, 
	tv_IMG_ID_Channel_List_right2,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_list_bottom[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Bottom_list_left, 
	tv_IMG_ID_Bottom_list_middle, 
	-1,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_list_video_bottom[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_video_list_left, 
	tv_IMG_ID_video_list_middle, 
	-1,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_music_group[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_music_bottom_left, 
	tv_IMG_ID_music_bottom_middle, 
	tv_IMG_ID_music_bottom_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_progrss_music[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_music_progress_left, 
	tv_IMG_ID_music_progress_middle, 
	tv_IMG_ID_music_progress_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_progress_red[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_progress_red_left, 
	tv_IMG_ID_progress_red_middle, 
	tv_IMG_ID_progress_red_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_and_video_Progress[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_tv_progress_white_left, 
	tv_IMG_ID_tv_progress_white_middle, 
	tv_IMG_ID_tv_progress_white_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_tv_and_video_red_Progress[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_tv_progress_red_left, 
	tv_IMG_ID_tv_progress_red_middle, 
	tv_IMG_ID_tv_progress_red_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_fm_name_bottom[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_Fm_bottom_left, 
	tv_IMG_ID_Fm_bottom_middle, 
	tv_IMG_ID_Fm_bottom_right,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_file_manage[]={
	_internal_use_only_IID_HOR, 
	-1, 
	tv_IMG_ID_music_bottom_middle, 
	-1,
};

static PREFIXCONST short POSTCONST _tv_IMG_ID_COMB_pvr_image[]={
	_internal_use_only_IID_HOR, 
	tv_IMG_ID_pvr_image_left, 
	tv_IMG_ID_pvr_image_middle, 
	tv_IMG_ID_pvr_image_right,
};

static PREFIXCONST short *POSTCONST img_type_entries[]={
	_tv_IMG_ID_COMB_Tv_msg_box,
	_tv_IMG_ID_COMB_tv_search,
	_tv_IMG_ID_COMB_tv_and_video,
	_tv_IMG_ID_COMB_tv_list1,
	_tv_IMG_ID_COMB_tv_list2,
	_tv_IMG_ID_COMB_list_bottom,
	_tv_IMG_ID_COMB_list_video_bottom,
	_tv_IMG_ID_COMB_music_group,
	_tv_IMG_ID_COMB_progrss_music,
	_tv_IMG_ID_COMB_progress_red,
	_tv_IMG_ID_COMB_tv_and_video_Progress,
	_tv_IMG_ID_COMB_tv_and_video_red_Progress,
	_tv_IMG_ID_COMB_fm_name_bottom,
	_tv_IMG_ID_COMB_file_manage,
	_tv_IMG_ID_COMB_pvr_image,

};
const short* tv_LoadCombineImageData(int ids)
{
	if(ids<tv_IMG_ID_COMB_START||ids>=tv_COMB_ID_ENUM_MAX)
		return 0;
	ids-=(tv_IMG_ID_COMB_START);
	return img_type_entries[ids];
}
