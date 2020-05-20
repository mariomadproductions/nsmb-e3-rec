#pragma once

#include "nsmb.h"

struct ItemBlock
{
	enum type : u8
	{
		ACTIVATE_EVENT,
		ITEM_SPAWNER,
		DOES_NOTHING
	};

	enum color : u8
	{
		BLUE,
		GREEN,
		YELLOW
	};

	struct sprite_data {
		u32 down_shift : 4;
		u32 right_shift : 4;
		u32 type : 4;
		u32 color : 2;
		u32 direction : 1;
		u32 reserved1 : 1;
		u32 size : 8;
		u32 item : 5;
		u32 single_use : 1;
		u32 puffs : 1;
		u32 reserved2 : 1;
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

	Actor* hit_actor; //Last actor hitting the block

	Vec3 init_pos; //Used when setting spawn values
	Vec3 start_pos; //Used when changing states

	u8 type; //What happens on hit
	u8 color; //Block color
	s8 direction; //The rotation direction
	u8 size; //Block size
	s8 item; //The item to spawn
	s8 single_use; //If the block turns green after use
	s8 puffs; //If the block explodes
	fx32 half_size; //Used to get block top and bottom positions

	u8 top_pounded;
	u8 being_hit;

	u8 rot_timer;
	u8 hit_timer;

};