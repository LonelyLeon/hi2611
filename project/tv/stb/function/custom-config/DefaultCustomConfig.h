/*
    本文件使能被pCustomConfig.c包含
    本文件包含默认的用户配置
*/

#ifdef D_SYSTEM_WIN32
#include <SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_keysym.h>

/* SDL库定义键盘码虚拟遥控器 */
static const P_CustomIrKey SdlIr[] =
{
    {SDLK_0, D_KEY_0},
	{SDLK_KP0, D_KEY_0},
	{SDLK_1, D_KEY_1},
	{SDLK_KP1, D_KEY_1},
	{SDLK_2, D_KEY_2},
	{SDLK_KP2, D_KEY_2},
	{SDLK_3, D_KEY_3},
	{SDLK_KP3, D_KEY_3},
	{SDLK_4, D_KEY_4},
    {SDLK_KP4, D_KEY_4},
	{SDLK_5, D_KEY_5},
	{SDLK_KP5, D_KEY_5},
	{SDLK_6, D_KEY_6},
	{SDLK_KP6, D_KEY_6},
	{SDLK_7, D_KEY_7},
	{SDLK_KP7, D_KEY_7},
	{SDLK_8, D_KEY_8},
	{SDLK_KP8, D_KEY_8},
	{SDLK_9, D_KEY_9},
	{SDLK_KP9, D_KEY_9},
	{SDLK_UP, D_KEY_UP},
	{SDLK_DOWN, D_KEY_DOWN},
	{SDLK_LEFT, D_KEY_LEFT},
	{SDLK_RIGHT, D_KEY_RIGHT},
	{SDLK_PAGEUP, D_KEY_PGUP},
	{SDLK_PAGEDOWN, D_KEY_PGDOWN},
	{SDLK_RETURN, D_KEY_OK},
	{SDLK_ESCAPE, D_KEY_ESC},
	{SDLK_y, D_KEY_YELLOW},
	{SDLK_b, D_KEY_BLUE},
	{SDLK_g, D_KEY_GREEN},
	{SDLK_r, D_KEY_RED},
	{SDLK_p, D_KEY_POWER},
	{SDLK_o, D_KEY_MUTE},
	{SDLK_t, D_KEY_AUD_TRACK},
	{SDLK_i, D_KEY_INFO},
	{SDLK_m, D_KEY_MENU},
	{SDLK_s, D_KEY_SOURCE},
	{SDLK_a, D_KEY_AUDIO},
	{SDLK_u, D_KEY_PROGRAM_PLUS},
	{SDLK_n, D_KEY_PROGRAM_MINUS},
	{SDLK_h, D_KEY_VOLUME_MINUS},
	{SDLK_j, D_KEY_VOLUME_PLUS},
	{SDLK_c, D_KEY_F1},
	{SDLK_q, D_KEY_BACK},
	{SDLK_f, D_KEY_FAVOR},	//"F"键模拟设置喜爱节目键，liuwf 20130815
	{0xFFFF, D_KEY_DEADLINE},
};
#endif

//默认值
P_CustomConfig g_custom_config =
{
    /* 系统配置 */
    {
        0
	},
    /* 遥控器配置,最多同时支持4组 */
    {
        {0},
        {0},
        {0},
#ifdef D_SYSTEM_WIN32
        {0x53, 0x444C, (P_CustomIrKey*)SdlIr},
#endif
    },
};

