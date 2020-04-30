#pragma once

#include "nsmb.h"

struct ItemBlock
{
	enum type : u8
	{
		ACTIVATE_EVENT,
		MUSHROOM_SPAWNER,
		GREEN_UNK
	};

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

	void (*exec_func)(ItemBlock*);
	s8 exec_step;

	Vec3 start_pos;

	u8 size; //Block size
	fx32 half_size;
	u8 color; //Block color
	u8 type; //What happens on hit
	s8 direction; //The rotation direction

	u8 top_pounded;

	u8 rot_timer;
	u8 hit_timer;

};