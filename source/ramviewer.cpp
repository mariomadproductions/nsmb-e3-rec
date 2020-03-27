#include "nsmb.h"

extern "C" void nds_printf(u16 something[2], u16* screenPtr, const char* str, ...);

#define DEBUG_WHITE 0xD000
#define DEBUG_GREEN 0xE000
#define DEBUG_RED 0xF000

u8* ptr = (u8*)0x02000000;

int count = 0;
int pos = 4;

void debugScreenRamViewer()
{
	u16** topScreenPtr = (u16**) 0x020859EC;
	u16** bottomScreenPtr = (u16**)0x20859E8;
	bool* CARDi_IsPulledOutFlag = (bool*)0x2096B40;

	u16 something[2];

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
	
	something[0] = DEBUG_WHITE;
	something[1] = DEBUG_WHITE;
	nds_printf(something, *bottomScreenPtr + 32, "Unfortunately the game has");
	nds_printf(something, *bottomScreenPtr + 32 * 2, "crashed, please contact");
	nds_printf(something, *bottomScreenPtr + 32 * 3, "DUMMY#0000 on Discord.");
	nds_printf(something, *bottomScreenPtr + 32 * 5, "Provide screenshots and details on how the crash occured.");

	if(*CARDi_IsPulledOutFlag)
		nds_printf(something, *bottomScreenPtr + 32 * 8, "Crash reason: Game pulled out.");
	
	if(isDSiMode)
		nds_printf(something, *bottomScreenPtr + 32 * 22, "DSiMode = true");
	else
		nds_printf(something, *bottomScreenPtr + 32 * 22, "DSiMode = false");

	something[0] = DEBUG_GREEN;
	something[1] = DEBUG_GREEN;
	nds_printf(something, *topScreenPtr + 33, "%08x - RAM VIEWER", ptr);
	nds_printf(something, *topScreenPtr + 65+7-pos, "^");
	
/*	if(ptr == newptr && !first)
		return;
*/
	ptr = newptr;	

	for(int i = 0; i < 16*20; i++)
	{
		if(something[0] == DEBUG_GREEN)
			something[0] = something[1] = DEBUG_WHITE;
		else
			something[0] = something[1] = DEBUG_GREEN;
			
		nds_printf(something, *topScreenPtr + i*2+4*32, "%02x", *newptr++);
	}
}