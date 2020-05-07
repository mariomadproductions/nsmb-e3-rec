#include "nsmb.h"

extern "C"
{
	void nds_printf(u16 colors[2], u16* screen_ptr, const char* str, ...);
	BOOL CARD_IsPulledOut(void);
}

#define DEBUG_WHITE 0xD000
#define DEBUG_GREEN 0xE000
#define DEBUG_RED 0xF000

static u8* ptr = (u8*)0x02000000;

static int pos = 4;

void debugScreenRamViewer()
{
	u16** top_scrn_ptr = (u16**) 0x020859EC;
	u16** btm_scrn_ptr = (u16**)0x20859E8;

	u16 font_color[2];

	//UPDATE KEYS
	nkeysHeld[1] = nkeysHeld[0];
	nkeysHeld[0] = PAD_Read();
	*nkeysDown = (nkeysHeld[0] & ~nkeysHeld[1]);
	
	u8* newptr = ptr;
	if(*nkeysDown & PAD_KEY_UP) newptr+=1<<(pos*4);
	if(*nkeysDown & PAD_KEY_DOWN) newptr-=1<<(pos*4);
	if(*nkeysDown & PAD_KEY_LEFT) pos++;
	if(*nkeysDown & PAD_KEY_RIGHT) pos--;
	if(pos > 7) pos = 7;
	if(pos < 0) pos = 0;
	
	font_color[0] = DEBUG_WHITE;
	font_color[1] = DEBUG_WHITE;

	if(CARD_IsPulledOut())
	{
		nds_printf(font_color, *btm_scrn_ptr + 32 * 8, "Crash reason: Game pulled out.");
	}
	else
	{
		nds_printf(font_color, *btm_scrn_ptr + 32, "Unfortunately the game has");
		nds_printf(font_color, *btm_scrn_ptr + 32 * 2, "crashed, please contact");
		nds_printf(font_color, *btm_scrn_ptr + 32 * 3, "TheGameratorT#1850 on Discord.");
		nds_printf(font_color, *btm_scrn_ptr + 32 * 5, "Provide screenshots and details on how the crash occured.");
	}
	
	if(isDSiMode)
		nds_printf(font_color, *btm_scrn_ptr + 32 * 22, "DSiMode = true");
	else
		nds_printf(font_color, *btm_scrn_ptr + 32 * 22, "DSiMode = false");

	font_color[0] = DEBUG_GREEN;
	font_color[1] = DEBUG_GREEN;
	nds_printf(font_color, *top_scrn_ptr + 33, "%08x - RAM VIEWER", ptr);
	nds_printf(font_color, *top_scrn_ptr + 65+7-pos, "^");
	
	ptr = newptr;	

	for(int i = 0; i < 16*20; i++)
	{
		if(font_color[0] == DEBUG_GREEN)
			font_color[0] = font_color[1] = DEBUG_WHITE;
		else
			font_color[0] = font_color[1] = DEBUG_GREEN;
			
		nds_printf(font_color, *top_scrn_ptr + i*2+4*32, "%02x", *newptr++);
	}
}