#pragma once

#include "nsmb.h"

struct ItemBlock
{
	// 0 -- Actor
	Actor actor;

	// 120 -- ActivePhysics
	ActivePhysics active_physics;

	// 1D0 -- Collider
	Collider collider;

	// 2BC -- ActorInfo
	ActorInfo info;

	// 3F4 -- ItemBlock only
	Model3d model;

	SolidCollision sollid_collision;

	u8 small; //If block is small
	u8 color; //Block color
	u8 type; //What happens on hit

	u8 rot_timer;

};