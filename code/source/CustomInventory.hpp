#pragma once

#include <nsmb_nitro.hpp>

namespace CustomInventory
{
	u8 getPowerupOnSlot(int playerNo, int slot);
	void setPowerupOnSlot(int playerNo, int slot, u8 value);
	u8 getDroppingSlot(int playerNo);
	void setDroppingSlot(int playerNo, u8 value);
}
