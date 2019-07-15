#include	"tImageResource_tv.h"
#include	"tlanresource_tv.h"

#define macro_w (vis->rect.w) 
#define macro_h (vis->rect.h) 

static D_Result _tv_IMG_ID_FS_main_menu_bg(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 800, 480, tv_IMG_ID_Background, 0, 0, 800, 480);
	gui_tool_draw_image(vis, 0, 375, 800, 103, tv_IMG_ID_Menu_Buttom, 0, 0, 800, 103);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_bright(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Bright1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_scan_channel(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Search_Channel1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_channel_list(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Channel_list1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_show_scale(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Show_Scale1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_track(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 86, 86, tv_IMG_ID_Bottom_Black, 0, 0, 86, 86);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Track1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_volume(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Volume_White, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_full_screen(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Full_Screen_White, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_voice(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Volume_White, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_One_Loop_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_One_Loop_Play, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Random_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Random_Play, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Order_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 53, tv_IMG_ID_Order_Play, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Loop_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Loop_Play, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Sd(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_sd_icon1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_usb(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_usb_icon1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Select_Time(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Select_Time, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Screen_16(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Screen_16_White, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Music_On(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Music_On, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Play(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Play, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_speed(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Speed_1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Music_Off(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Music_Off, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Pause(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Pause, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Track_left(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Track_left, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_track_right(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Track_right, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_screen_4(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Screen_4_White, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_list_bottom(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, macro_h-424, 40, 424, tv_IMG_ID_Bottom_list_left, 0, 0, 40, 424);
	gui_tool_draw_image(vis, 40, macro_h-424, macro_w-40, 424, tv_IMG_ID_Bottom_list_middle, 0, 0, macro_w-40, 424);
	gui_tool_set_transparency(vis, 0xFF);
	gui_tool_draw_line(vis, 3, 0, 300, 0, 0xff007e88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Track_Stereo_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Track1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Track_Left_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Track_left, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Track_Right_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Track_right, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Screen_Full_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Full_Screen_White, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Screen_4_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Screen_4_White, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Screen_16_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Screen_16_White, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_One_Loop_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_One_Loop_Play, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Random_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Random_Play, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Order_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Order_Play, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Loop_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Loop_Play, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Sd_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_sd_icon1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Usb_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_usb_icon1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Music_On_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Music_On, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Music_Off_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Music_Off, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Play_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Play, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Pause_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Pause, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Revolve_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Loop_Play, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Slide_Speed_Focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Slide_Speed_1, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Ebook(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Ebook_manage2, 0, 0, 82, 88);
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Select_Button, 0, 0, 82, 88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_movie(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_movie_manage2, 0, 0, 82, 88);
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Select_Button, 0, 0, 82, 88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_File(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_tool_manage2, 0, 0, 82, 88);
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Select_Button, 0, 0, 82, 88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Calendar(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_calendar_manage2, 0, 0, 82, 88);
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Select_Button, 0, 0, 82, 88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Set_Up(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_tool_set2, 0, 0, 82, 88);
	gui_tool_draw_image(vis, 0, 0, 82, 88, tv_IMG_ID_Select_Button, 0, 0, 82, 88);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Tv_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_video(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Video_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_music(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Music_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_photo(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Photo_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_fm(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_FM_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tool(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Tool_Button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Tv_Channel_List_Red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Channel_list1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Tv_Volume_Red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Volume_White, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Scan_Channel_Red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Search_Channel1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Tv_Bright_Red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Bright1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Select_Time_Red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Select_Time, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Menu_Backgroud(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, macro_h-80, 800, 80, tv_IMG_ID_menu_backgroud, 0, 0, 800, 108);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_Pvr(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_pvr_button, 0, 0, 82, 82);
	gui_tool_draw_image(vis, 0, 0, 82, 82, tv_IMG_ID_Select_Button, 0, 0, 82, 82);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_pvr(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_pvr_icon1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_tv_pvr_red(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_pvr_icon1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _tv_IMG_ID_FS_pop_msg_bg(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 16, 42, tv_IMG_ID_Pop_Box_left, 0, 0, 16, 42);
	gui_tool_draw_image(vis, macro_w-16, 0, 16, 42, tv_IMG_ID_Pop_Box_right, 0, 0, 16, 42);
	gui_tool_draw_image(vis, 16, 0, macro_w-32, 42, tv_IMG_ID_Pop_Box_middle, 0, 0, 8, 42);
	gui_tool_draw_image(vis, 0, 42, 16, macro_h-42, tv_IMG_ID_Pop_Box_left, 0, 240-(macro_h-42), 16, macro_h-42);
	gui_tool_draw_image(vis, macro_w-16, 42, 16, macro_h-42, tv_IMG_ID_Pop_Box_right, 0, 240-(macro_h-42), 16, macro_h-42);
	gui_tool_draw_image(vis, 16, 42, macro_w-32, macro_h-42, tv_IMG_ID_Pop_Box_middle, 0, 240-(macro_h-42), 8, macro_h-42);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static D_Result _tv_IMG_ID_FS_calender_set_time(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Calendar_date1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_calender_set_time_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Calendar_date1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_calender_set_date(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Calendar_set1, 0, 0, 52, 52);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}
static D_Result _tv_IMG_ID_FS_calender_set_date_focus(D_Visual *vis)
{
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Black, 0, 0, 68, 68);
	gui_tool_draw_image(vis, 8, 8, 52, 52, tv_IMG_ID_Bottom_Calendar_set1, 0, 0, 52, 52);
	gui_tool_draw_image(vis, 0, 0, 68, 68, tv_IMG_ID_Bottom_Red, 0, 0, 68, 68);
	gui_tool_set_transparency(vis, 0xFF);
	return D_OK;
}

static PREFIXCONST fGuiTool POSTCONST free_shape_entry[]={
	_tv_IMG_ID_FS_main_menu_bg,
	_tv_IMG_ID_FS_tv_bright,
	_tv_IMG_ID_FS_scan_channel,
	_tv_IMG_ID_FS_tv_channel_list,
	_tv_IMG_ID_FS_show_scale,
	_tv_IMG_ID_FS_tv_track,
	_tv_IMG_ID_FS_tv_volume,
	_tv_IMG_ID_FS_full_screen,
	_tv_IMG_ID_FS_tv_voice,
	_tv_IMG_ID_FS_One_Loop_Play,
	_tv_IMG_ID_FS_Random_Play,
	_tv_IMG_ID_FS_Order_Play,
	_tv_IMG_ID_FS_Loop_Play,
	_tv_IMG_ID_FS_Sd,
	_tv_IMG_ID_FS_usb,
	_tv_IMG_ID_FS_Select_Time,
	_tv_IMG_ID_FS_Screen_16,
	_tv_IMG_ID_FS_Music_On,
	_tv_IMG_ID_FS_Slide_Play,
	_tv_IMG_ID_FS_Slide_speed,
	_tv_IMG_ID_FS_Music_Off,
	_tv_IMG_ID_FS_Slide_Pause,
	_tv_IMG_ID_FS_Track_left,
	_tv_IMG_ID_FS_track_right,
	_tv_IMG_ID_FS_screen_4,
	_tv_IMG_ID_FS_list_bottom,
	_tv_IMG_ID_FS_Track_Stereo_Focus,
	_tv_IMG_ID_FS_Track_Left_Focus,
	_tv_IMG_ID_FS_Track_Right_Focus,
	_tv_IMG_ID_FS_Screen_Full_Focus,
	_tv_IMG_ID_FS_Screen_4_Focus,
	_tv_IMG_ID_FS_Screen_16_Focus,
	_tv_IMG_ID_FS_One_Loop_Play_Focus,
	_tv_IMG_ID_FS_Random_Play_Focus,
	_tv_IMG_ID_FS_Order_Play_Focus,
	_tv_IMG_ID_FS_Loop_Play_Focus,
	_tv_IMG_ID_FS_Sd_focus,
	_tv_IMG_ID_FS_Usb_Focus,
	_tv_IMG_ID_FS_Music_On_Focus,
	_tv_IMG_ID_FS_Music_Off_Focus,
	_tv_IMG_ID_FS_Slide_Play_Focus,
	_tv_IMG_ID_FS_Slide_Pause_Focus,
	_tv_IMG_ID_FS_Slide_Revolve_Focus,
	_tv_IMG_ID_FS_Slide_Speed_Focus,
	_tv_IMG_ID_FS_Ebook,
	_tv_IMG_ID_FS_movie,
	_tv_IMG_ID_FS_File,
	_tv_IMG_ID_FS_Calendar,
	_tv_IMG_ID_FS_Set_Up,
	_tv_IMG_ID_FS_tv,
	_tv_IMG_ID_FS_video,
	_tv_IMG_ID_FS_music,
	_tv_IMG_ID_FS_photo,
	_tv_IMG_ID_FS_fm,
	_tv_IMG_ID_FS_tool,
	_tv_IMG_ID_FS_Tv_Channel_List_Red,
	_tv_IMG_ID_FS_Tv_Volume_Red,
	_tv_IMG_ID_FS_Scan_Channel_Red,
	_tv_IMG_ID_FS_Tv_Bright_Red,
	_tv_IMG_ID_FS_Select_Time_Red,
	_tv_IMG_ID_FS_Menu_Backgroud,
	_tv_IMG_ID_FS_Pvr,
	_tv_IMG_ID_FS_tv_pvr,
	_tv_IMG_ID_FS_tv_pvr_red,
	_tv_IMG_ID_FS_pop_msg_bg,
	_tv_IMG_ID_FS_calender_set_time,
	_tv_IMG_ID_FS_calender_set_time_focus,
	_tv_IMG_ID_FS_calender_set_date,
	_tv_IMG_ID_FS_calender_set_date_focus,
};
fGuiTool tv_LoadFreeShape(int id, int lanid)
{
	if(id<tv_IMG_ID_FS_START||id>=tv_IMG_ID_FS_ENUM_MAX)
		return NULL;
	id-=tv_IMG_ID_FS_START;
	if(id>=sizeof(free_shape_entry)/sizeof(free_shape_entry[0]))
		return NULL;
	return free_shape_entry[id];
}
