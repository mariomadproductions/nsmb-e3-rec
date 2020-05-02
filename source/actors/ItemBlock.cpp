#include "ItemBlock.h"
#include <stdarg.h>

const u32 ModelFileID = 1212 - 131;

void ItemBlock_SetExecuteState(ItemBlock* block, void (*exec_func)(ItemBlock*))
{
	if (block->exec_func != exec_func)
	{
		block->exec_step = -1;
		block->exec_func(block);

		block->exec_func = exec_func;

		block->exec_step = 0;
		block->exec_func(block);
	}
}

void ItemBlock_RotateExecuteState(ItemBlock* block)
{
	if (block->exec_step)
	{
		if (block->exec_step != -1)
		{
			const int sleepTime = 10;
			const int rotateTime = 28;
			if (block->rot_timer > sleepTime)
			{
				block->actor.rotation.y -= (0x4000 / rotateTime) * block->direction;
				if (block->rot_timer == rotateTime + sleepTime)
				{
					block->actor.rotation.y = 0;
					block->rot_timer = -1;
				}
			}
			block->rot_timer++;
		}
	}
	else
	{
		block->exec_step = 1;
		block->actor.position = block->start_pos;
	}
}

void ItemBlock_HitBehavior(ItemBlock* block)
{
	switch (block->type)
	{
	case ItemBlock::ACTIVATE_EVENT:
		activateEvent(block->info.eventIDs.targetID);
		SpawnParticle(81, &block->actor.position);
		Base_deleteIt(block);
		break;
	case ItemBlock::MUSHROOM_SPAWNER:
	{
		Vec3 spawnPos = block->actor.position;
		int spriteData = 3;
		if (block->top_pounded)
		{
			spriteData |= 0x60;
			spawnPos.y -= block->half_size;
		}
		else
		{
			spawnPos.y += block->half_size - 0x10000;
		}
		CreateActor(31, spriteData, &spawnPos, 0, 0, 0);
		break;
	}
	case ItemBlock::GREEN_UNK:
		break;
	}
}

void ItemBlock_HitExecuteState(ItemBlock* block)
{
	if (block->exec_step == -1)
	{
		block->being_hit = false;
		block->top_pounded = false;
	}
	else if (block->exec_step)
	{
		bool is_drop_rand = block->type == ItemBlock::ACTIVATE_EVENT;
		int direction = block->top_pounded ? -1 : 1;
		if (block->hit_timer < 10 + (is_drop_rand))
		{
			block->actor.position.y += 0x1000 * direction;
			if (block->hit_timer == 10 && is_drop_rand)
			{
				goto hit_behavior;
			}
		}
		else
		{
			block->actor.position.y -= 0x1000 * direction;
			if (block->hit_timer == 20)
			{
				goto hit_behavior;
			}
		}
		solidCollisions_setPos(&block->sollid_collision);

		block->hit_timer++;
		return;

	hit_behavior:
		ItemBlock_HitBehavior(block);
		ItemBlock_SetExecuteState(block, ItemBlock_RotateExecuteState);
	}
	else
	{
		block->exec_step = 1;
		block->being_hit = true;
		block->hit_timer = 0;
		block->actor.position = block->start_pos;
	}
}

void ItemBlock_HitFromTop(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER || block->being_hit)
		return;

	if ((player->P.jumpBitfield & GROUNDPOUNDING) && (player->P.currentAnim != 0x15))
	{
		block->top_pounded = true;
		ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
	}
}

void ItemBlock_HitFromBottom(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player or if being hit already
	if (player->actor.actorType != T_PLAYER || block->being_hit)
		return;

	ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
}

void ItemBlock_HitFromSide(ItemBlock* block, EnemyActor* collider)
{
	if (block->being_hit)
		return;

	if ((collider->actor.base.classID == 94) ||
		(collider->actor.base.classID == 95) ||
		(collider->actor.base.classID == 54) ||
		(collider->actor.base.classID == 40) ||
		(collider->activephysics.callback == (u32*)0x02099B6C))
	{
		ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
	}
}

static SCInput ItemBlock_solidCollisionInput =
{
	-0x10000, //left
	0x10000, //top
	0x10000, //right
	-0x10000, //bottom
	(u32*)ItemBlock_HitFromTop, //callbackTop
	(u32*)ItemBlock_HitFromBottom, //callbackBottom
	(u32*)ItemBlock_HitFromSide, //callbackSide
	0, //unk1
	0, //unk2
	0, //unk3
	0 //padding
};

//MAIN ACTOR START ---------------------------------------------

extern "C"
{
	extern const u32 ItemBlock_ActorSize = sizeof(ItemBlock);

	int ItemBlock_loadFiles()
	{
		nFS_LoadFileByIDToCache(ModelFileID, false);
		return 1;
	}

	int ItemBlock_heapCreated(ItemBlock* block)
	{
		void* model_file = nFS_GetPtrToCachedFile(ModelFileID);
		model3d_ctor(&block->model);
		model3d_setup(&block->model, model_file, 0);
		return 1;
	}

	int ItemBlock_OnCreate(ItemBlock* block)
	{
		int tile_size = 0x20 * ((block->size + 9) / 16);
		block->info.DrawDist.x = tile_size;
		block->info.DrawDist.y = tile_size;

		u32 sprite_data = block->actor.base.spriteData;
		block->type = (sprite_data >> 8) & 0xF;
		block->color = (sprite_data >> 12) & 0x3;
		block->direction = ((sprite_data >> 14) & 1) ? 1 : -1;
		//(sprite_data >> 15) is free for a bool
		block->size = (sprite_data >> 16) & 0xFF;
		block->half_size = (block->size * 0x1000) / 2;

		block->actor.scale = (block->size * 0x1000) / 32;

		fx32 down_shift = sprite_data & 0xF;
		fx32 right_shift = (sprite_data >> 4) & 0xF;
		block->actor.position.y -= 0x1000 * down_shift;
		block->actor.position.x += 0x1000 * right_shift;

		block->start_pos = block->actor.position;

		solidCollisions_init(&block->sollid_collision, block, &ItemBlock_solidCollisionInput, 0, 0, &block->actor.scale);
		solidCollisions_register(&block->sollid_collision);

		block->being_hit = false;
		block->rot_timer = 0;
		ItemBlock_SetExecuteState(block, ItemBlock_RotateExecuteState);

		return 1;
	}

	int ItemBlock_OnExecute(ItemBlock* block)
	{
		if (enemyActor_deleteIfOutOfRange(block, 0))
			return 1;

		block->exec_func(block);

		return 1;
	}

	int ItemBlock_OnDraw(ItemBlock* block)
	{
		Vec3 model_pos = block->actor.position;
		model_pos.y -= block->half_size;
		model3d_draw(&block->model, &model_pos, &block->actor.rotation, &block->actor.scale);
		return 1;
	}

	int ItemBlock_OnDelete(ItemBlock* block)
	{
		solidCollisions_unregister(&block->sollid_collision);
		return 1;
	}
}