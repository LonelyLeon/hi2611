#include	"atvImageResource.h"
#include	"atvlanresource.h"

#define macro_w (vis->rect.w) 
#define macro_h (vis->rect.h) 

static D_Result _atv_IMG_ID_FS_Move(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 100, 36, atv_IMG_ID_hint_button, 0, 0, 100, 36);
	gui_tool_draw_image(vis, 35, 3, 30, 30, atv_IMG_ID_hint_direction, 0, 0, 30, 30);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_movie(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_movie, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Music(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_music, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Picture(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_picture, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Setting(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_setting, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Movie_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_movie_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Music_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_music_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Picture_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_picture_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Setting_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_setting_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder_Normal(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffcacaca);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Floder1_Normal(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_up_level, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Folder1_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_icon_file_up_level_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_disk_normal(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_disk_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_disk_focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
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
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_ebook_icon_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_ebook_normal(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffcacaca);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_ebook_icon_focus, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PVR_FOCUS(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffb8000);
	gui_tool_draw_image(vis, 0, 0, 152, 112, atv_IMG_ID_pvr_normal, 0, 0, 152, 112);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Normal(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffffffff);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xffd7d7d7);
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
static D_Result _atv_IMG_ID_FS_Window_white_bg(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffc7c8c7);
	gui_tool_draw_fill_rect(vis, 4, 4, macro_w-8, macro_h-8, 0xfff0f0f0);
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
static D_Result _atv_IMG_ID_FS_SIGNAL_BACKGROUND(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffe6e6e6);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffc8c8c8);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, 12, macro_h, 0xfffaba00);
	gui_tool_draw_fill_rect(vis, 12, 0, macro_w - 12, macro_h, 0xff282828);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_NORMAL(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffc8c8c8);
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, 3, 0xffc8c8c8);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_FOCSE(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffaba00);
	gui_tool_draw_fill_round_rect(vis, 12, 0, macro_w - 12, macro_h, 3, 0xff282828);
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, 3, 0xfffaba00);
	gui_tool_draw_fill_rect(vis, 12, 0, 3, macro_h, 0xff282828);
	gui_tool_draw_fill_rect(vis, 12, 0, macro_w, 3, 0xff282828);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Wifi_password_bg(D_Visual *vis)
{
       gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h,4, 0xff005998);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Wifi_pwkey_normal(D_Visual *vis)
{
       gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h,4, 0xffa7a7a8);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Wifi_pw_title(D_Visual *vis)
{
       gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h,4, 0xfff1a81b);
       gui_tool_draw_fill_round_rect(vis, 2, 2, macro_w-4, macro_h-4,4, 0xffffffff);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Wifi_pwkey_focse(D_Visual *vis)
{
       gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h,4, 0xfff1a81b);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_select_focus_ex(D_Visual *vis)
{
	gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffff9900);
	gui_tool_draw_image(vis, 5, (macro_h-12)/2, 12, 12, atv_IMG_ID_search_right, 0, 0, 12, 12);
	gui_tool_draw_image(vis, macro_w-17, (macro_h-12)/2, 12, 12, atv_IMG_ID_search_left, 0, 0, 12, 12);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_White_Round_bg(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfff9f9f9);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Mira(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff48823);
        gui_tool_draw_image(vis, (macro_w-100)/2, 8, 100, 83, atv_IMG_ID_zhilian_main_mira_pic, 0, 0, 100, 83);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Dlna(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff46c554);
        gui_tool_draw_image(vis, (macro_w-82)/2, 8, 82, 83, atv_IMG_ID_zhilian_main_dlna_pic, 0, 0, 82, 83);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Tsnet(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff9746d);
        gui_tool_draw_image(vis, (macro_w-100)/2, 8, 100, 77, atv_IMG_ID_zhilian_main_tsnet_pic, 0, 0, 100, 77);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_Zhilian_AirPlay(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff9746d);
        gui_tool_draw_image(vis, (macro_w-100)/2, 8, 100, 77, atv_IMG_ID_mini_airplay, 0, 0, 100, 77);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_Zhilian_Source(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff1375e4);
        gui_tool_draw_image(vis, (macro_w-263)/2, macro_h - 60, 263, 44, atv_IMG_ID_zhilian_main_source_pic, 0, 0, 263, 44);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Setting(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff00c289);
        gui_tool_draw_image(vis, (macro_w-145)/2, macro_h - 82, 145, 82, atv_IMG_ID_zhilian_main_setting_pic, 0, 0, 145, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Iptv(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff8557d3);
        gui_tool_draw_image(vis, (macro_w-92)/2, 40, 92, 99, atv_IMG_ID_zhilian_main_iptv_pic, 0, 0, 92, 99);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Zhilian_Media(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xffef4a5a);
        gui_tool_draw_image(vis, (macro_w-90)/2, (macro_h-83)/2, 90, 83, atv_IMG_ID_zhilian_main_media_pic, 0, 0, 90, 83);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_pop_bg(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff8c8c8c);
    gui_tool_draw_fill_rect(vis, 3, 3, macro_w - 6, macro_h - 6, 0xffd7d7d7);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_picture_menu_bg(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xfff0f0f0);
    gui_tool_draw_fill_rect(vis, 3, 3, macro_w - 6, macro_h - 6, 0xffc0c0c0);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_no_signal_backgroud(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xfff404040);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xff080808);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_program_info_backplane(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 5, 0xffe1e1e1);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_music_select_bg(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 18, 0xffe1e1e1);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_music_select_focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 18, 0xffff9900);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_main_zhilian_mode_bg(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xff2c4be1);
    gui_tool_draw_fill_round_rect(vis, 1, 1, macro_w - 2, macro_h - 2, 3, 0xff170862);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_Zhilian_tv(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff8557d3);
        gui_tool_draw_image(vis, (macro_w-100)/2, 60, 100, 78, atv_IMG_ID_main_zhilian_souce_tv, 0, 0, 100, 78);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static PREFIXCONST fGuiTool POSTCONST free_shape_entry[]={
	_atv_IMG_ID_FS_Move,
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
	_atv_IMG_ID_FS_Window_white_bg,
	_atv_IMG_ID_FS_Select_focus,
	_atv_IMG_ID_FS_SIGNAL_BACKGROUND,
	_atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL,
	_atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE,
	_atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_NORMAL,
	_atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_FOCSE,
	_atv_IMG_ID_FS_Wifi_password_bg,
	_atv_IMG_ID_FS_Wifi_pwkey_normal,
	_atv_IMG_ID_FS_Wifi_pwkey_focse,
	_atv_IMG_ID_FS_Wifi_pw_title,
	_atv_IMG_ID_FS_select_focus_ex,
	_atv_IMG_ID_FS_White_Round_bg,
	_atv_IMG_ID_FS_Zhilian_Mira,
	_atv_IMG_ID_FS_Zhilian_Dlna,
	_atv_IMG_ID_FS_Zhilian_Tsnet,
	_atv_IMG_ID_FS_Zhilian_AirPlay,
	_atv_IMG_ID_FS_Zhilian_Source,
	_atv_IMG_ID_FS_Zhilian_Iptv,
	_atv_IMG_ID_FS_Zhilian_Setting,
	_atv_IMG_ID_FS_Zhilian_Media,
	_atv_IMG_ID_FS_pop_bg,
	_atv_IMG_ID_FS_picture_menu_bg,
	_atv_IMG_ID_FS_no_signal_backgroud,
	_atv_IMG_ID_FS_program_info_backplane,
	_atv_IMG_ID_FS_music_select_bg,
	_atv_IMG_ID_FS_music_select_focus,
	_atv_IMG_ID_FS_main_zhilian_mode_bg,
	_atv_IMG_ID_FS_Zhilian_tv,
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
