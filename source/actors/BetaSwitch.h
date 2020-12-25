#pragma once

#include "nsmb.h"

struct BetaSwitch
{
	// 0 -- Actor
	Actor actor;

	// 120 -- ActivePhysics
	ActivePhysics activephysics;

	// 1D0 -- Collider
	Collider collider;

	// 2BC -- ActorInfo
	ActorInfo info;

	// 3F4 -- Self only
	ModelAnim3d model;
	
	SolidCollision sc;

	u16 hitTimer;
};