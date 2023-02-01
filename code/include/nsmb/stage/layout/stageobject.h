#pragma once

#include "nitro_if.h"

struct StageObject
{
	u16 id;
	u16 x;
	u16 y;
	u8 events[2];
	u32 settings;
};
