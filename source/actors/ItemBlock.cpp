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
	case ItemBlock::DROP_RAND_COINS:
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
		}
		else
		{
			if (block->small)
			{
				spawnPos.y += 0x4000;
			}
			else
			{
				spawnPos.y += 0xC000;
			}
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
		block->top_pounded = false;
	}
	else if (block->exec_step)
	{
		bool is_drop_rand = block->type == ItemBlock::DROP_RAND_COINS;
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
		block->hit_timer = 0;
		block->actor.position = block->start_pos;
	}
}

void ItemBlock_HitFromTop(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER)
		return;

	if ((player->P.jumpBitfield & GROUNDPOUNDING) && (player->P.currentAnim != 0x15))
	{
		block->top_pounded = true;
		ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
	}
}

void ItemBlock_HitFromBottom(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER)
		return;

	ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
}

void ItemBlock_HitFromSide(ItemBlock* block, EnemyActor* collider)
{
	if ((collider->actor.base.classID == 94) ||
		(collider->actor.base.classID == 95) ||
		(collider->actor.base.classID == 54) ||
		(collider->actor.base.classID == 40) ||
		(collider->activephysics.callback == (u32*)0x02099B6C))
	{
		ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
	}
}

void ItemBlock_SetupCollision(ItemBlock* block)
{
	SCInput solid_collision =
	{
		solid_collision.left = -0x12000,
		solid_collision.top = 0x1A000,
		solid_collision.right = 0x11000,
		solid_collision.bottom = 0,
		solid_collision.callbackTop = (u32*)ItemBlock_HitFromTop,
		solid_collision.callbackBottom = (u32*)ItemBlock_HitFromBottom,
		solid_collision.callbackSide = (u32*)ItemBlock_HitFromSide,
		solid_collision.unk1 = 0,
		solid_collision.unk2 = 0,
		solid_collision.unk3 = 0,
		solid_collision.padding = 0
	};
	if (block->small)
	{
		solid_collision.left = -0xC000;
		solid_collision.top = 0x13000;
		solid_collision.right = 0xB000;
	}

	solidCollisions_init(&block->sollid_collision, block, &solid_collision, 0, 0, 0);
	solidCollisions_register(&block->sollid_collision);
}

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
		model3d_init(&block->model);
		return 1;
	}

	int ItemBlock_OnCreate(ItemBlock* block)
	{
		u32 sprite_data = block->actor.base.spriteData;
		block->small = sprite_data & 1;
		block->direction = (sprite_data & 8) ? 1 : -1;
		block->color = (sprite_data >> 4) & 0xF;
		block->type = (sprite_data >> 8) & 0xF;

		bool shift_down = sprite_data & 2;
		bool shift_right = sprite_data & 4;
		int shift = block->small ? 0x8000 : 0xC000;
		if (shift_down)
		{
			block->actor.position.y -= shift;
		}
		if (shift_right)
		{
			block->actor.position.x += shift;
		}

		block->info.DrawDist.x = 0x20;
		block->start_pos = block->actor.position;
		block->actor.scale = block->small ? 0x900 : 0xD00;
		block->rot_timer = 0;

		ItemBlock_SetupCollision(block);
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
		model3d_draw(&block->model, &block->actor.position, &block->actor.rotation, &block->actor.scale);
		return 1;
	}

	int ItemBlock_OnDelete(ItemBlock* block)
	{
		solidCollisions_unregister(&block->sollid_collision);
		return 1;
	}
}