#pragma once

#include "nsmb.h"

struct BackgroundSwapper
{
	// 0 -- Actor
	Actor actor;

	// 120 -- ActivePhysics
	ActivePhysics activephysics;

	// 1D0 -- Collider
	Collider collider;

	// 2BC -- ActorInfo
	ActorInfo info;

	u8 BG_ID;
	u8 FG_ID;
	u8 TS_ID;
};