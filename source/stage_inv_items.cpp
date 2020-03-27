#include "nsmb.h"

static u8 invPowerup[2][3] = { 0 };
static u8 droppingSlot[2] = { 0 };
static u8 touchedSlot[2] = { 0 };

extern "C" {
	u8 GetInventoryPowerupForPlayerSlot(int playerNo, int slot) { return invPowerup[playerNo][slot]; }
	void SetInventoryPowerupForPlayerSlot(int playerNo, int slot, u8 value) { invPowerup[playerNo][slot] = value; }
	u8 GetDroppingSlot(int playerNo) { return droppingSlot[playerNo]; }
	void SetDroppingSlot(int playerNo, u8 value) { droppingSlot[playerNo] = value; }
}

int nsub_02020240() { return 1; } //Replace powerup GET
void nsub_02020250() {} //Replace powerup SET

//Allow 3 rectangles to touch and save the touched one
bool repl_020C05A4_ov_00(int rect, int playerNo)
{
	asm("MOV R1, R6");
	if (rect >= 0 && rect < 3)
	{
		touchedSlot[playerNo] = rect;
		return false;
	}
	else
	{
		return true;
	}
}
void nsub_020C05B4_ov_00() { asm("B 0x020C05C8"); }

//Check if the touched powerup slot isn't empty so it can proceed to dropping state
bool repl_020BE1F0_ov_00(int playerNo)
{
	return GetInventoryPowerupForPlayerSlot(playerNo, touchedSlot[playerNo]) != 0;
}

//Set the dropping state and check something for the powerup being dropped instead
int repl_020C06BC_ov_00(int playerNo)
{
	SetDroppingSlot(playerNo, touchedSlot[playerNo]);
	return GetInventoryPowerupForPlayerSlot(playerNo, GetDroppingSlot(playerNo));
}

//Clear powerup on drop
void repl_020BF59C_ov_00(int playerNo, int zero)
{
	SetInventoryPowerupForPlayerSlot(playerNo, GetDroppingSlot(playerNo), zero);
}

//Change the ReplaceInventoryItem system
void nsub_020D4A70_ov_0A(PlayerActor* player, int playerNo, int newPowerup)
{
	for (int i = 0; i < 3; i++)
	{
		bool isSlotEmpty = GetInventoryPowerupForPlayerSlot(playerNo, i) == 0;
		if (isSlotEmpty)
		{
			SetInventoryPowerupForPlayerSlot(playerNo, i, newPowerup);
			SetDroppingSlot(playerNo, i);
			UpdateInventoryPowerup(playerNo, i);
			return;
		}
	}

	bool replaced = false;
	for (int i = 0; i < 3; i++)
	{
		bool canReplace = false;
		int oldPowerup = GetInventoryPowerupForPlayerSlot(playerNo, i);

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
			SetInventoryPowerupForPlayerSlot(playerNo, i, newPowerup);
			SetDroppingSlot(playerNo, i);
			UpdateInventoryPowerup(playerNo, i);
			replaced = true;
			break;
		}
	}

	if (!replaced)
	{
		int* localPlayerNo = (int*)0x02085A7C;
		if (playerNo == *localPlayerNo)
			PlaySNDEffect(0x17D, 0);
		GiveScoreItemForPlayer(4, playerNo);
	}
}