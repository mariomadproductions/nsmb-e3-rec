#include "ItemBlock.h"

const u32 ModelFileID[] = { 1212 - 131, 1213 - 131, 1214 - 131 };
const bool ResetRotationBug = true; //Enables a bug that existed in the beta

void ItemBlock_SetExecuteState(ItemBlock* block, void (*exec_func)(ItemBlock*))
{
	if (block->exec_func != exec_func)
	{
		if (block->exec_func)
		{
			block->exec_step = -1;
			block->exec_func(block);
		}

		block->exec_func = exec_func;

		block->exec_step = 0;
		block->exec_func(block);
	}
}

void ItemBlock_SetColor(ItemBlock* block, int color, bool setup = false)
{
	if (block->color != color || setup)
	{
		block->color = color;
		void* model_file = nFS_GetPtrToCachedFile(ModelFileID[block->color]);
		model3d_setup(&block->model, model_file, 0, 0);

		if (ResetRotationBug && !setup)
		{
			block->rot_timer = 0;
			block->actor.rotation.y = 0;
		}
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

void ItemBlock_HitBehavior(ItemBlock* block, bool animEnd)
{
	switch (block->type)
	{
	case ItemBlock::ACTIVATE_EVENT:
		if (!animEnd)
			break;

		activateEvent(block->info.eventIDs.targetID);
		break;
	case ItemBlock::ITEM_SPAWNER:
	{
		if (animEnd == (block->item != 3))
			break;

		Vec3 spawnPos = block->start_pos;
		int spriteData = block->item;
		if (block->item == 5)
		{
			spriteData |= 0x1000000;
		}
		if (block->top_pounded)
		{
			if (!block->puffs)
			{
				spriteData |= 0x60;
			}
			spawnPos.y -= block->half_size;
		}
		else
		{
			spawnPos.y += block->half_size - 0x10000;
		}
		if (block->puffs)
		{
			spriteData |= 0x1000000;
			spawnPos.y += 192 << 12;
		}

		int direction = (block->hit_actor->position.x > block->start_pos.x) ? 0x80000000 : 0;
		spriteData |= direction;

		CreateActor(31, spriteData, &spawnPos, 0, 0, 0);
		break;
	}
	default:
		break;
	}

	if (animEnd)
	{
		if (block->single_use)
		{
			if (block->puffs)
			{
				SpawnParticle(202, &block->actor.position);
				enemyActor_delete(block, 1);
			}
			else
			{
				block->type = ItemBlock::DOES_NOTHING;
				ItemBlock_SetColor(block, ItemBlock::GREEN);
				SetSpriteAtPosUsed(block->init_pos.x, block->init_pos.y, 1);
			}
		}
		if (!block->puffs)
		{
			ItemBlock_SetExecuteState(block, ItemBlock_RotateExecuteState);
		}
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
		int direction = block->top_pounded ? -1 : 1;
		if (block->hit_timer < 10)
		{
			block->actor.position.y += 0x1000 * direction;
			if (block->hit_timer == 9)
			{
				ItemBlock_HitBehavior(block, false);
			}
		}
		else
		{
			block->actor.position.y -= 0x1000 * direction;
			if (block->hit_timer == 19)
			{
				ItemBlock_HitBehavior(block, true);
			}
		}
		solidCollisions_setPos(&block->solid_collision);

		block->hit_timer++;
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
		block->hit_actor = &player->actor;
		ItemBlock_SetExecuteState(block, ItemBlock_HitExecuteState);
	}
}

void ItemBlock_HitFromBottom(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player or if being hit already
	if (player->actor.actorType != T_PLAYER || block->being_hit)
		return;

	block->hit_actor = &player->actor;
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
		block->hit_actor = &collider->actor;
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
		nFS_LoadFileByIDToCache(ModelFileID[0], false);
		nFS_LoadFileByIDToCache(ModelFileID[1], false);
		nFS_LoadFileByIDToCache(ModelFileID[2], false);
		return 1;
	}

	int ItemBlock_OnCreate(ItemBlock* block)
	{
		ItemBlock::sprite_data* sprite_data = (ItemBlock::sprite_data*)&block->actor.base.spriteData;
		block->type = sprite_data->type;
		block->color = sprite_data->color;
		block->direction = sprite_data->direction ? 1 : -1;
		block->size = sprite_data->size;
		block->item = sprite_data->item;
		block->single_use = sprite_data->single_use;
		block->puffs = sprite_data->puffs;
		block->half_size = (block->size * 0x1000) / 2;

		int tile_size = 0x20 * ((block->size + 9) / 16);
		block->info.DrawDist.x = tile_size;
		block->info.DrawDist.y = tile_size;

		block->init_pos = block->actor.position;
		if (GetSpriteAtPosUsed(block->init_pos.x, block->init_pos.y))
		{
			block->color = ItemBlock::GREEN;
			block->type = ItemBlock::DOES_NOTHING;
		}
		block->actor.scale = /*(block->size * 0x1000) / 32*/(block->size << 7);

		fx32 down_shift = sprite_data->down_shift;
		fx32 right_shift = sprite_data->right_shift;
		block->actor.position.y -= 0x1000 * down_shift;
		block->actor.position.x += 0x1000 * right_shift;

		block->start_pos = block->actor.position;

		model3d_ctor(&block->model);
		ItemBlock_SetColor(block, block->color, true);

		solidCollisions_init(&block->solid_collision, block, &ItemBlock_solidCollisionInput, 0, 0, &block->actor.scale);
		solidCollisions_register(&block->solid_collision);

		block->being_hit = false;
		block->rot_timer = 0;
		ItemBlock_SetExecuteState(block, ItemBlock_RotateExecuteState);

		return 1;
	}

	int ItemBlock_OnExecute(ItemBlock* block)
	{
		block->exec_func(block);
		enemyActor_deleteIfOutOfRange(block, 0);
		return 1;
	}

	int ItemBlock_OnDraw(ItemBlock* block)
	{
		model3d_draw(&block->model, &block->actor.position, &block->actor.rotation, &block->actor.scale);
		return 1;
	}

	int ItemBlock_OnDelete(ItemBlock* block)
	{
		solidCollisions_unregister(&block->solid_collision);
		return 1;
	}
}