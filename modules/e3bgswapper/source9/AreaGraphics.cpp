#include "e3bgswapper/BackgroundSwapper.hpp"

namespace BackgroundSwapperState
{
	u8 lastBG = 0;
	u8 lastFG = 0;
	u8 lastTS = 0;
}

ncp_hook(0x020BCFCC, 0)
void rememberAreaGraphicsHook()
{
	u8* PointerToBlock1 = *(u8**)0x0208B168;
	BackgroundSwapperState::lastBG = PointerToBlock1[6];
	BackgroundSwapperState::lastFG = PointerToBlock1[18];
	BackgroundSwapperState::lastTS = PointerToBlock1[12];
}
