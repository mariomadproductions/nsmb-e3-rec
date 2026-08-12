#include <nsmb_nitro.hpp>

#include "extra/undocumented.hpp"

#define DEBUG_WHITE 0xD000
#define DEBUG_YELLOW 0xE000
#define DEBUG_AQUA 0xF000

#define COLOR_WHITE 0
#define COLOR_YELLOW 1
#define COLOR_AQUA 2

#define SCR_POS(scrn, x, y) (scrn + 32 * y + x)

namespace CrashScreen {

u16 isOpen = true;
u16 lastIsOpen = false;

struct TextEntry
{
	u8 color, screen;
	u16 pos;
	const char* text;

	constexpr TextEntry(u8 color, u8 screen, u8 x, u8 y, const char* text)
	{
		this->color = color;
		this->screen = screen;
		this->pos = 2 * (32 * y + x);
		this->text = text;
	}
};

const static TextEntry textEntries[] = {
	TextEntry(COLOR_AQUA, 0, 5, 3, "The game has crashed"),
	TextEntry(COLOR_WHITE, 0, 2, 6, "Please contact the hack team"),
	TextEntry(COLOR_WHITE, 0, 4, 7, "Send them the crash dump"),
	TextEntry(COLOR_WHITE, 0, 7, 10, "Discord contacts:"),
	TextEntry(COLOR_WHITE, 0, 10, 12, "@hiccup3675"),
	TextEntry(COLOR_WHITE, 0, 9, 14, "@thegameratort"),
	TextEntry(COLOR_YELLOW, 0, 6, 19, "Blame TheGameratorT"),

	TextEntry(COLOR_AQUA, 1, 2, 4, "Possible actions:"),
	TextEntry(COLOR_WHITE, 1, 4, 7, "START  > This screen"),
	TextEntry(COLOR_WHITE, 1, 4, 9, "SELECT > Crash dump"),
	TextEntry(COLOR_WHITE, 1, 4, 11, "L + R  > Restart"),

	TextEntry(COLOR_AQUA, 1, 2, 15, "GitHub:"),
	TextEntry(COLOR_WHITE, 1, 10, 15, "bit.ly/3b3jK1W"),
	TextEntry(COLOR_AQUA, 1, 2, 17, "NSMBHD:"),
	TextEntry(COLOR_WHITE, 1, 10, 17, "bit.ly/3od0FOl")
};

const static u16 colors[3][2] = {
	{ DEBUG_WHITE, DEBUG_WHITE },
	{ DEBUG_WHITE, DEBUG_YELLOW },
	{ DEBUG_WHITE, DEBUG_AQUA }
};

void drawDebugScreen()
{
	debug_drawTop();
	debug_drawBottom();
}

void create()
{
	// Stop all DMAs, this avoids garbled graphics caused by HDMA
	for (u32 i = 0; i < 4; i++)
		MI_StopDma(i);
}

void update()
{
	if (CARD_IsPulledOut())
	{
		drawDebugScreen();
		return;
	}

	u16 input = PAD_Read();

	if (input & PAD_BUTTON_START)
	{
		isOpen = true;
	}
	else if (input & PAD_BUTTON_SELECT)
	{
		isOpen = false;
	}
	else if ((input & PAD_BUTTON_L) && (input & PAD_BUTTON_R))
	{
		OS_EnableIrq();
		OS_EnableInterrupts();
		OS_ResetSystem(0);
		return;
	}

	if (lastIsOpen == isOpen)
		return;
	lastIsOpen = isOpen;

	debug_clear();

	if (!isOpen)
	{
		drawDebugScreen();
		return;
	}

	u16* screens[] = { *rcast<u16**>(0x020859EC), *rcast<u16**>(0x020859E8) };

	for (u32 i = 0; i < NTR_ARRAY_SIZE(textEntries); i++)
	{
		const TextEntry& e = textEntries[i];
		debug_printf(colors[e.color], rcast<u16*>(rcast<u8*>(screens[e.screen]) + e.pos), e.text);
	}

	char* buildTime = rcast<char*>(0x02088BB4);
	debug_printf(colors[COLOR_YELLOW], SCR_POS(screens[1], 1, 22), buildTime);
}

}

ncp_repl(0x0200460C, "NOP") // Do not disconnect the cartridge

ncp_repl(0x02005DD8, "MOV R2, #0x31") // Background color
ncp_repl(0x0203985C, ".short 0x037F") // Yellow font color
ncp_repl(0x0203987C, ".short 0x7F8F") // Aqua font color

ncp_repl(0x02005BA8, "MOV R5, #5; B 0x02005C1C") // Auto-open debug screen on crash

ncp_repl(0x02005C20, "NOP") // Do not run draw top twice
ncp_repl(0x02005C2C, "BL _ZN11CrashScreen6updateEv; NOP") // Hook our updater

ncp_jump(0x02005B24)
NTR_NAKED void crashScreenCreateHook()
{asm(R"(
	STRH    R0, [R2]
	BL      _ZN11CrashScreen6createEv
	B       0x02005B28
)");}
