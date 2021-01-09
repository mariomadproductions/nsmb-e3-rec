#include "nsmb.h"

extern "C"
{
	void nds_printf(u16 colors[2], u16* screen_ptr, const char* str, ...);
}

#define DEBUG_WHITE 0xD000
#define DEBUG_GREEN 0xE000
#define DEBUG_RED 0xF000

NAKED void repl_02005DD8() { asm("MOV R2, #0x60"); }

void debugScreenRamViewer()
{
	u16* top_scrn_ptr = *(u16**)0x020859EC;
	u16* btm_scrn_ptr = *(u16**)0x020859E8;

	char* build_time = (char*)0x02088BB4;

	u16 font_color[2];

	font_color[0] = DEBUG_WHITE;

	if (CARD_IsPulledOut())
	{
		font_color[1] = DEBUG_WHITE;
		nds_printf(font_color, top_scrn_ptr + 32 * 8, "Game card pulled out.");
	}
	else
	{
		font_color[1] = DEBUG_RED;
		nds_printf(font_color, top_scrn_ptr + 32 *  3 +  5, "The game has crashed");
		font_color[1] = DEBUG_WHITE;
		nds_printf(font_color, top_scrn_ptr + 32 *  6 +  2, "Please contact the hack team");
		nds_printf(font_color, top_scrn_ptr + 32 *  7 +  4, "Send them the crash dump");
		nds_printf(font_color, top_scrn_ptr + 32 * 10 +  7, "Discord contacts:");
		nds_printf(font_color, top_scrn_ptr + 32 * 12 + 10, "Hiccup#3675");
		nds_printf(font_color, top_scrn_ptr + 32 * 14 +  6, "TheGameratorT#1850");
		font_color[1] = DEBUG_GREEN;
		nds_printf(font_color, top_scrn_ptr + 32 * 19 +  6, "Blame TheGameratorT");

		font_color[1] = DEBUG_RED;
		nds_printf(font_color, btm_scrn_ptr + 32 *  4 +  2, "Possible actions:");
		font_color[1] = DEBUG_WHITE;
		nds_printf(font_color, btm_scrn_ptr + 32 *  7 +  4, "START  > This screen");
		nds_printf(font_color, btm_scrn_ptr + 32 *  9 +  4, "SELECT > Crash dump");

		font_color[1] = DEBUG_RED;
		nds_printf(font_color, btm_scrn_ptr + 32 *  14 +  2, "GitHub:");
		nds_printf(font_color, btm_scrn_ptr + 32 *  16 +  2, "NSMBHD:");
		font_color[1] = DEBUG_WHITE;
		nds_printf(font_color, btm_scrn_ptr + 32 *  14 +  10, "bit.ly/3b3jK1W");
		nds_printf(font_color, btm_scrn_ptr + 32 *  16 +  10, "bit.ly/3od0FOl");

		font_color[1] = DEBUG_GREEN;
		nds_printf(font_color, btm_scrn_ptr + 32 * 22 +  1, build_time);
	}
}