#include    "atvImageResource.h"
#include    "atvlanresource.h"

#define macro_w (vis->rect.w)
#define macro_h (vis->rect.h)

static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Play_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_movie_play, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Pause_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_movie_pause, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Last_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_pic_last, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Next_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_pic_next, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_LeftRotate_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_rotate_l, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_RightRotate_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, 35, 35, 3, 0xffff9900);
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_rotate_r, 0, 0, 110, 50);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Play(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_movie_play, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Pause(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_movie_pause, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Last(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_pic_last, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_Next(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_pic_next, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_LeftRotate(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_rotate_l, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_PictureMenu_RightRotate(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, 3, 30, 30, atv_IMG_ID_media_rotate_r, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_Media_Stop_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 30, 30, 0xffff9900);
    gui_tool_draw_image(vis, 0, 0, 30, 30, atv_IMG_ID_media_movie_pause, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Last_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 30, 30, 0xffff9900);
    gui_tool_draw_image(vis, 0, 0, 30, 30, atv_IMG_ID_media_pic_last, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Next_focus(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 30, 30, 0xffff9900);
    gui_tool_draw_image(vis, 0, 0, 30, 30, atv_IMG_ID_media_pic_next, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}
static D_Result _atv_IMG_ID_FS_Media_Pause_Focus(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 30, 30, 0xffff9900);
    gui_tool_draw_image(vis, 0, 0, 30, 30, atv_IMG_ID_media_movie_play, 0, 0, 30, 30);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_Select_focus(D_Visual *vis)
{
    gui_tool_draw_image(vis, 3, (macro_h - 18) / 2, 10, 18, atv_IMG_ID_sub_menu_direc_left, 0, 0, 10, 18);
    gui_tool_draw_fill_rect(vis, 18, 0, macro_w - 36, macro_h, 0xfff1a81b);
    gui_tool_draw_image(vis, macro_w - 13, (macro_h - 18) / 2, 10, 18, atv_IMG_ID_sub_menu_direc_right, 0, 0, 10, 18);
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
    gui_tool_draw_fill_rect(vis, 0, 0, 10, macro_h, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 10, 0, macro_w - 10, macro_h, 0xff282828);
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
    gui_tool_draw_fill_round_rect(vis, 10, 0, macro_w - 10, macro_h, 3, 0xff282828);
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, 3, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 10, 0, 3, macro_h, 0xff282828);
    gui_tool_draw_fill_rect(vis, 10, 0, macro_w, 3, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_MAIN_BUTTON_FOCSE(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, 64, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 64, macro_w, macro_h - 64, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_MAIN_MENU_BUTTON_FOCSE(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, 100, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 100, macro_w, macro_h-100, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_SUBMENU_BUTTON_NORMAL(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffc8c8c8);
    gui_tool_draw_fill_rect(vis, 0, 35, macro_w, macro_h - 35, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_SUBMENU_BUTTON_FOCSE(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffc8c8c8);
    gui_tool_draw_fill_rect(vis, 0, 33, macro_w, macro_h - 33, 0xfffaba00);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_SUBMENU_BUTTON_ENABLE(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff888888);
    gui_tool_draw_fill_rect(vis, 0, 35, macro_w, macro_h - 35, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_PROGRESS_NORMAL(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_OK_BUTTON_NORMAL(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_OK_BUTTON_FOCSE(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xfffaba00);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_OK_BUTTON_DISABLE(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xff3372c9);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_BUTTON_GRAY(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xffc7c8c7);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_BUTTON_YELLOW(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xfffaba00);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_WHITE_BACKGROUND(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xffc7c8c7);
    gui_tool_draw_fill_rect(vis, 2, 2, macro_w - 4, macro_h - 4, 0xffffffff);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}


static D_Result _atv_IMG_ID_FS_SCROL_BACKGROUND(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff282828);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_BLACK_BACKGROUND(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff3b454f);
    gui_tool_draw_fill_rect(vis, 4, 4, macro_w - 8, macro_h - 8, 0xff0d0d0d);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_MEDIA_RED_POS(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, macro_w, macro_h, 0xff008000);
    gui_tool_draw_fill_rect(vis, 1, 1, macro_w - 2, macro_h - 2, 0xfff00000);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_FACTORY_YELLOW(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 480, 3, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 3, 3, 24, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 477, 3, 3, 24, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 27, 480, 3, 0xfffaba00);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_TEST_YELLOW(D_Visual *vis)
{
    gui_tool_draw_fill_rect(vis, 0, 0, 960, 3, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 3, 3, 534, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 957, 3, 3, 534, 0xfffaba00);
    gui_tool_draw_fill_rect(vis, 0, 537, 960, 3, 0xfffaba00);
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

static D_Result _atv_IMG_ID_FS_Wifi_password_bg(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 4, 0xffc7d9ff);
    gui_tool_draw_fill_round_rect(vis, 2, 2, macro_w-4, macro_h-4, 4, 0xff005998);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_Wifi_pw_title(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 4, 0xfff1a81b);
    gui_tool_draw_fill_round_rect(vis, 2, 2, macro_w - 4, macro_h - 4, 4, 0xffffffff);
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

static D_Result _atv_IMG_ID_FS_Zhilian_Mira(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff48823);
        gui_tool_draw_image(vis, (macro_w-100)/2, 8, 100, 83, atv_IMG_ID_zhilian_main_mira_pic, 0, 0, 100, 83);
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

static D_Result _atv_IMG_ID_FS_Zhilian_Dlna(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff46c554);
        gui_tool_draw_image(vis, (macro_w-82)/2, 8, 82, 83, atv_IMG_ID_zhilian_main_dlna_pic, 0, 0, 82, 83);
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

static D_Result _atv_IMG_ID_FS_main_zhilian_mode_bg(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 3, 0xff2c4be1);
    gui_tool_draw_fill_round_rect(vis, 1, 1, macro_w - 2, macro_h - 2, 3, 0xff170862);
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

static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Mira(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff48823);
	gui_tool_draw_image(vis, macro_w-110, (macro_h-77)/2, 94, 77, atv_IMG_ID_mini_phone_throw_screen, 0, 0, 94, 77);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Dlna(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff46c554);
	gui_tool_draw_image(vis, macro_w-110, (macro_h-84)/2, 84, 84, atv_IMG_ID_mini_dlna, 0, 0, 84, 84);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Source(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff1375e4);
	gui_tool_draw_image(vis, (macro_w - 80)/2, 55, 80, 84, atv_IMG_ID_mini_source, 0, 0, 80, 84);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Media(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xffef4a5a);
	gui_tool_draw_image(vis, (macro_w - 90)/2, 55, 90, 83, atv_IMG_ID_zhilian_main_media_pic, 0, 0, 90, 83);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Setting(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff00c289);
	gui_tool_draw_image(vis, (macro_w - 93)/2, 55, 93, 90, atv_IMG_ID_mini_set, 0, 0, 93, 90);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Iptv(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xff8557d3);
	gui_tool_draw_image(vis, (macro_w-84)/2, (macro_h-91)/2, 84, 91, atv_IMG_ID_mini_iptv, 0, 0, 84, 91);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_Mini_Zhilian_Airplay(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 6, 0xfff9746d);
	gui_tool_draw_image(vis, macro_w-110, (macro_h-77)/2, 100, 77, atv_IMG_ID_mini_airplay, 0, 0, 100, 77);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _atv_IMG_ID_FS_Connect_pro(D_Visual *vis)
{
    gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 0, 0xffffffff);
    gui_tool_draw_fill_round_rect(vis, 3, 3, macro_w-6, macro_h-6, 0,  0xffdbdbdb);
    gui_tool_set_transparency(vis, 0xFF);
    return D_OK;
}

static D_Result _atv_IMG_ID_FS_Ebook_List_Select(D_Visual *vis)
{
	gui_tool_draw_fill_round_rect(vis, 0, 0, macro_w, macro_h, 18, 0xfff1a81b);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static PREFIXCONST fGuiTool POSTCONST free_shape_entry[] =
{
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

    _atv_IMG_ID_FS_Media_Stop_Focus,
    _atv_IMG_ID_FS_Media_Last_Focus,
    _atv_IMG_ID_FS_Media_Next_focus,
    _atv_IMG_ID_FS_Media_Pause_Focus,
    _atv_IMG_ID_FS_Select_focus,
    _atv_IMG_ID_FS_SIGNAL_BACKGROUND,
    _atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL,
    _atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE,
    _atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_NORMAL,
    _atv_IMG_ID_FS_SIGNAL_BUTTON_LAST_FOCSE,
    _atv_IMG_ID_FS_MAIN_BUTTON_FOCSE,
    _atv_IMG_ID_FS_MAIN_MENU_BUTTON_FOCSE,
    _atv_IMG_ID_FS_SUBMENU_BUTTON_NORMAL,
    _atv_IMG_ID_FS_SUBMENU_BUTTON_FOCSE,
    _atv_IMG_ID_FS_SUBMENU_BUTTON_ENABLE,
    _atv_IMG_ID_FS_PROGRESS_NORMAL,
    _atv_IMG_ID_FS_OK_BUTTON_NORMAL,
    _atv_IMG_ID_FS_OK_BUTTON_FOCSE,
    _atv_IMG_ID_FS_OK_BUTTON_DISABLE,
    _atv_IMG_ID_FS_BUTTON_GRAY,
    _atv_IMG_ID_FS_BUTTON_YELLOW,
    _atv_IMG_ID_FS_WHITE_BACKGROUND,
    _atv_IMG_ID_FS_SCROL_BACKGROUND,
    _atv_IMG_ID_FS_BLACK_BACKGROUND,
    _atv_IMG_ID_FS_MEDIA_RED_POS,
    _atv_IMG_ID_FS_FACTORY_YELLOW,
    _atv_IMG_ID_FS_TEST_YELLOW,
    _atv_IMG_ID_FS_pop_bg,
    _atv_IMG_ID_FS_Wifi_password_bg,
    _atv_IMG_ID_FS_Wifi_pw_title,
    _atv_IMG_ID_FS_Zhilian_Source,
    _atv_IMG_ID_FS_Zhilian_Setting,
    _atv_IMG_ID_FS_Zhilian_Mira,
    _atv_IMG_ID_FS_Zhilian_Tsnet,
    _atv_IMG_ID_FS_Zhilian_Dlna,
    _atv_IMG_ID_FS_Zhilian_Iptv,
    _atv_IMG_ID_FS_main_zhilian_mode_bg,
    _atv_IMG_ID_FS_Zhilian_Media,
    _atv_IMG_ID_FS_Mini_Zhilian_Mira,
    _atv_IMG_ID_FS_Mini_Zhilian_Dlna,
    _atv_IMG_ID_FS_Mini_Zhilian_Source,
    _atv_IMG_ID_FS_Mini_Zhilian_Media,
    _atv_IMG_ID_FS_Mini_Zhilian_Setting,
    _atv_IMG_ID_FS_Mini_Zhilian_Iptv,
    _atv_IMG_ID_FS_Mini_Zhilian_Airplay,
    _atv_IMG_ID_FS_Connect_pro,
    _atv_IMG_ID_FS_Ebook_List_Select,
};

fGuiTool atv_LoadFreeShape(int id, int lanid)
{
    if(id < atv_IMG_ID_FS_START || id >= atv_IMG_ID_FS_ENUM_MAX)
        return NULL;
    id -= atv_IMG_ID_FS_START;
    if(id >= sizeof(free_shape_entry) / sizeof(free_shape_entry[0]))
        return NULL;
    return free_shape_entry[id];
}
