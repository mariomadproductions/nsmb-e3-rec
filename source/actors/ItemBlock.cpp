#include "ItemBlock.h"

const u32 ModelFileID = 1212 - 131;

void ItemBlock_DoHitBehavior(ItemBlock* block)
{
	Base_deleteIt(block);
}

void ItemBlock_HitFromTop(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER)
		return;

	if ((player->P.jumpBitfield & GROUNDPOUNDING) && (player->P.currentAnim != 0x15))
	{
		ItemBlock_DoHitBehavior(block);
	}
}

void ItemBlock_HitFromBottom(ItemBlock* block, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER)
		return;

	ItemBlock_DoHitBehavior(block);
}

void ItemBlock_HitFromSide(ItemBlock* block, EnemyActor* collider)
{
	if ((collider->actor.base.classID == 94) ||
		(collider->actor.base.classID == 95) ||
		(collider->actor.base.classID == 54) ||
		(collider->actor.base.classID == 40) ||
		(collider->activephysics.callback == (u32*)0x02099B6C))
	{
		ItemBlock_DoHitBehavior(block);
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
		block->color = (sprite_data >> 4) & 0xF;
		block->type = (sprite_data >> 8) & 0xF;

		block->actor.scale = block->small ? 0x900 : 0xD00;

		block->rot_timer = 0;

		ItemBlock_SetupCollision(block);

		return 1;
	}

	int ItemBlock_OnExecute(ItemBlock* block)
	{
		if (enemyActor_deleteIfOutOfRange(block, 0))
			return 1;

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