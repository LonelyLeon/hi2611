#include	"atvImageResource.h"
#include	"atvlanresource.h"

#define macro_w (vis->rect.w) 
#define macro_h (vis->rect.h) 

static D_Result _atv_IMG_ID_FS_Signal_HDMI_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_HDMI02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_HDMI_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_HDMI01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Tv_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_tv_signal02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Tv_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_tv_signal01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Av1_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_video02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Av1_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_video01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Component_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_component02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Component_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_component01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Computer_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_computer02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Computer_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_computer01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Usb_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background02, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_usb02, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Signal_Usb_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_signal_background01, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_usb01, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Move(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 100, 36, atv_IMG_ID_hint_button, 0, 0, 100, 36);
	gui_tool_draw_image(vis, 35, 3, 30, 30, atv_IMG_ID_hint_direction, 0, 0, 30, 30);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_audio_tune_bg(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 40, 160, atv_IMG_ID_tune_adjust_background2, 0, 0, 40, 160);
	gui_tool_draw_image(vis, 15, 7, 22, 146, atv_IMG_ID_tune_adjust_bar, 0, 0, 22, 146);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_movie(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_movie, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Music(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_music, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Picture(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_picture, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Setting(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_setting, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Movie_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_movie_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Music_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_music_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Picture_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_picture_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Setting_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_setting_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Floder1_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_up_level, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder1_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_up_level_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_disk_normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_disk_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_disk_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_disk_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_media_play, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Pause_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_media_pause, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Last_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_last, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Next_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_next, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_LeftRotate_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_rotate_left, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_RightRotate_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 110, 50, atv_IMG_ID_picture_menu_button, 0, 0, 110, 50);
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_rotate_right, 0, 0, 110, 50);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_media_play, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Pause(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_media_pause, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Last(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_last, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Next(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_next, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_LeftRotate(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_rotate_left, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_RightRotate(D_Visual *vis)
{
	gui_tool_draw_image(vis, 31, 0, 48, 48, atv_IMG_ID_picture_menu_rotate_right, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_ebook_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_ebook_icon_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_ebook_normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_ebook_icon_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PVR_FOCUS(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_media_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_pvr_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Normal(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_background, 0, 0, 152, 112);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_pvr_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Stop_Focus(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, 48, 48, 0xffff9900);
	gui_tool_draw_image(vis, 0, 0, 48, 48, atv_IMG_ID_media_pause, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Last_Focus(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, 48, 48, 0xffff9900);
	gui_tool_draw_image(vis, 0, 0, 48, 48, atv_IMG_ID_picture_menu_last, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Next_focus(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, 48, 48, 0xffff9900);
	gui_tool_draw_image(vis, 0, 0, 48, 48, atv_IMG_ID_picture_menu_next, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Pause_Focus(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, 48, 48, 0xffff9900);
	gui_tool_draw_image(vis, 0, 0, 48, 48, atv_IMG_ID_media_play, 0, 0, 48, 48);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Window_black_bg(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff3b454f);
	gui_tool_draw_fill_rect(vis, 4, 4, macro_w-8, macro_h-8, 0xff0d0d0d);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Select_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 3, (macro_h-12)/2, 12, 12, atv_IMG_ID_search_right, 0, 0, 12, 12);
	gui_tool_draw_fill_rect(vis, 18, 0, macro_w-36, macro_h, 0xfff1a81b);
	gui_tool_draw_image(vis, macro_w-15, (macro_h-12)/2, 12, 12, atv_IMG_ID_search_left, 0, 0, 12, 12);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static PREFIXCONST fGuiTool POSTCONST free_shape_entry[]={
	_atv_IMG_ID_FS_Signal_HDMI_Focus,
	_atv_IMG_ID_FS_Signal_HDMI_Normal,
	_atv_IMG_ID_FS_Signal_Tv_Focus,
	_atv_IMG_ID_FS_Signal_Tv_Normal,
	_atv_IMG_ID_FS_Signal_Av1_Focus,
	_atv_IMG_ID_FS_Signal_Av1_Normal,
	_atv_IMG_ID_FS_Signal_Component_Focus,
	_atv_IMG_ID_FS_Signal_Component_Normal,
	_atv_IMG_ID_FS_Signal_Computer_Focus,
	_atv_IMG_ID_FS_Signal_Computer_Normal,
	_atv_IMG_ID_FS_Signal_Usb_Focus,
	_atv_IMG_ID_FS_Signal_Usb_Normal,
	_atv_IMG_ID_FS_Move,
	_atv_IMG_ID_FS_audio_tune_bg,
	_atv_IMG_ID_FS_Media_movie,
	_atv_IMG_ID_FS_Media_Music,
	_atv_IMG_ID_FS_Media_Picture,
	_atv_IMG_ID_FS_Media_Setting,
	_atv_IMG_ID_FS_Media_Movie_Focus,
	_atv_IMG_ID_FS_Media_Music_Focus,
	_atv_IMG_ID_FS_Media_Picture_Focus,
	_atv_IMG_ID_FS_Media_Setting_Focus,
	_atv_IMG_ID_FS_Media_Folder_Normal,
	_atv_IMG_ID_FS_Media_Folder_Focus,
	_atv_IMG_ID_FS_Media_Floder1_Normal,
	_atv_IMG_ID_FS_Media_Folder1_Focus,
	_atv_IMG_ID_FS_Media_disk_normal,
	_atv_IMG_ID_FS_Media_disk_focus,
	_atv_IMG_ID_FS_Media_PictureMenu_Play_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_Pause_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_Last_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_Next_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_LeftRotate_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_RightRotate_Focus,
	_atv_IMG_ID_FS_Media_PictureMenu_Play,
	_atv_IMG_ID_FS_Media_PictureMenu_Pause,
	_atv_IMG_ID_FS_Media_PictureMenu_Last,
	_atv_IMG_ID_FS_Media_PictureMenu_Next,
	_atv_IMG_ID_FS_Media_PictureMenu_LeftRotate,
	_atv_IMG_ID_FS_Media_PictureMenu_RightRotate,
	_atv_IMG_ID_FS_Media_ebook_focus,
	_atv_IMG_ID_FS_Media_ebook_normal,
	_atv_IMG_ID_FS_Media_PVR_FOCUS,
	_atv_IMG_ID_FS_Media_Normal,
	_atv_IMG_ID_FS_Media_Stop_Focus,
	_atv_IMG_ID_FS_Media_Last_Focus,
	_atv_IMG_ID_FS_Media_Next_focus,
	_atv_IMG_ID_FS_Media_Pause_Focus,
	_atv_IMG_ID_FS_Window_black_bg,
	_atv_IMG_ID_FS_Select_focus,
};
fGuiTool atv_LoadFreeShape(int id, int lanid)
{
	if(id<atv_IMG_ID_FS_START||id>=atv_IMG_ID_FS_ENUM_MAX)
		return NULL;
	id-=atv_IMG_ID_FS_START;
	if(id>=sizeof(free_shape_entry)/sizeof(free_shape_entry[0]))
		return NULL;
	return free_shape_entry[id];
}
