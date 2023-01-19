#include "nsmb/game.h"
#include "nsmb/player.h"
#include "nsmb/stage/entity.h"
#include "nsmb/sound/sound.h"
#include "extra/undocumented.hpp"

namespace CustomInventory
{
	static u8 invPowerup[2][3] = { 0 };
	static u8 droppingSlot[2] = { 0 };
	static u8 touchedSlot[2] = { 0 };

	u8 getPowerupOnSlot(int playerNo, int slot) { return invPowerup[playerNo][slot]; }
	void setPowerupOnSlot(int playerNo, int slot, u8 value) { invPowerup[playerNo][slot] = value; }
	u8 getDroppingSlot(int playerNo) { return droppingSlot[playerNo]; }
	void setDroppingSlot(int playerNo, u8 value) { droppingSlot[playerNo] = value; }
}

using namespace CustomInventory;

ncp_repl(0x02020240, "MOV R0, #1\nBX LR") // Replace powerup GET
ncp_repl(0x02020250, "BX LR") // Replace powerup SET

//Allow 3 rectangles to touch and save the touched one
ncp_repl(0x020C058C, 0, "MOV R1, R6")

ncp_call(0x020C0590, 0)
bool repl_020C0590_ov_00(int rect, int playerNo)
{
	if (rect >= 0 && rect < 3)
	{
		touchedSlot[playerNo] = rect;
		return false;
	}
	return true;
}

ncp_repl(0x020C0594, 0, R"(
	CMP     R0, #0
	ADDNE   SP, SP, #0x14
	POPNE   {R4-R7,PC}
	B       0x020C05C8
)")

//Check if the touched powerup slot isn't empty so it can proceed to dropping state
ncp_call(0x020BE1F0, 0)
bool repl_020BE1F0_ov_00(int playerNo)
{
	return getPowerupOnSlot(playerNo, touchedSlot[playerNo]) != 0;
}

//Set the dropping state and check something for the powerup being dropped instead
ncp_call(0x020C06BC, 0)
int repl_020C06BC_ov_00(int playerNo)
{
	setDroppingSlot(playerNo, touchedSlot[playerNo]);
	return getPowerupOnSlot(playerNo, getDroppingSlot(playerNo));
}

//Clear powerup on drop
ncp_call(0x020BF59C, 0)
void repl_020BF59C_ov_00(int playerNo, int zero)
{
	setPowerupOnSlot(playerNo, getDroppingSlot(playerNo), zero);
}

//Change the ReplaceInventoryItem system
ncp_jump(0x020D4A70, 10)
void nsub_020D4A70_ov_0A(Player* player, int playerNo, int newPowerup)
{
	for (int i = 0; i < 3; i++)
	{
		bool isSlotEmpty = getPowerupOnSlot(playerNo, i) == 0;
		if (isSlotEmpty)
		{
			setPowerupOnSlot(playerNo, i, newPowerup);
			setDroppingSlot(playerNo, i);
			UpdateInventoryPowerup(playerNo, i);
			return;
		}
	}

	bool replaced = false;
	for (int i = 0; i < 3; i++)
	{
		bool canReplace = false;
		int oldPowerup = getPowerupOnSlot(playerNo, i);

		switch (oldPowerup)
		{
		case 3:
			if ((u8)(newPowerup - 4) <= 1)
				canReplace = true;
			break;
		case 4:
			if (newPowerup == 3 || newPowerup == 5)
				canReplace = true;
			break;
		case 2:
			if ((u8)(newPowerup - 3) <= 2)
				canReplace = true;
			break;
		default:
			if (oldPowerup == 1 && newPowerup != 1)
				canReplace = true;
			break;
		}

		if (canReplace)
		{
			setPowerupOnSlot(playerNo, i, newPowerup);
			setDroppingSlot(playerNo, i);
			UpdateInventoryPowerup(playerNo, i);
			replaced = true;
			break;
		}
	}

	if (!replaced)
	{
		if (playerNo == Game::localPlayerID)
			SND::playSFX(0x17D);
		StageEntity::getCollectablePoints(4, playerNo);
	}
}
