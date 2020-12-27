#include "BetaSwitch.h"

const u32 ModelFileID = { 1441 - 131 };
const u32 AnimFileID = { 1440 - 131 };

void BetaSwitch_HitFromTop(BetaSwitch* self, PlayerActor* player)
{
	//If not hit by player
	if (player->actor.actorType != T_PLAYER)
		return;

	solidCollisions_unregister(&self->sc);
	modelAnim3d_setAnimation(&self->model, 0, 0x40000000, 0x1000, 0);
	self->hitTimer = 1;
}

static SCInput BetaSwitch_scInput =
{
	-0x10000, //left
	0x20000, //top
	0x10000, //right
	0, //bottom
	(u32*)BetaSwitch_HitFromTop, //callbackTop
	nullptr, //callbackBottom
	nullptr, //callbackSide
	0, //unk1
	0, //unk2
	0, //unk3
	0 //padding
};

//MAIN ACTOR START ---------------------------------------------

extern "C"
{
	extern const u32 BetaSwitch_ActorSize = sizeof(BetaSwitch);

	int BetaSwitch_loadFiles()
	{
		nFS_LoadFileByIDToCache(ModelFileID, false);
		nFS_LoadFileByIDToCache(AnimFileID, false);
		return 1;
	}

	int BetaSwitch_OnCreate(BetaSwitch* self)
	{
		void* mdl = nFS_GetPtrToCachedFile(ModelFileID);
		void* anim = nFS_GetPtrToCachedFile(AnimFileID);

		modelAnim3d_ctor(&self->model);
		modelAnim3d_setup(&self->model, mdl, anim, 0, 0);
		modelAnim3d_setAnimation(&self->model, 0, 1, 0, 0);

		self->hitTimer = 0;

		self->actor.scale = 0xE00;
		self->actor.position.x += 0x8000;

		if(self->actor.base.spriteData & 1)
		{
			self->actor.scale /= 0x2000;
			self->actor.position.x -= 0x8000;
		}

		solidCollisions_init(&self->sc, self, &BetaSwitch_scInput, 0, 0, &self->actor.scale);
		solidCollisions_register(&self->sc);

		return 1;
	}

	int BetaSwitch_OnExecute(BetaSwitch* self)
	{
		int hitTimerF = self->hitTimer - 1;
		if(hitTimerF >= 0)
		{
			if(hitTimerF == 0)
			{
				PlaySNDEffect(8, nullptr);
			}
			else if(hitTimerF == 16)
			{
				activateEvent(self->info.eventIDs.targetID);

				VecFx16 axis = { -0x1000, -0x1000, 0x1000 };
				SpawnParticle(203, &self->actor.position);
				SpawnParticleAxis(203, &self->actor.position, &axis);

				Base_deleteIt(self);
			}
			self->hitTimer++;
		}
		anim3d_update(&self->model.anim);
		return 1;
	}

	int BetaSwitch_OnDraw(BetaSwitch* self)
	{
		model3d_draw(&self->model.model, &self->actor.position, &self->actor.rotation, &self->actor.scale);
		return 1;
	}

	int BetaSwitch_OnDelete(BetaSwitch* self)
	{
		solidCollisions_unregister(&self->sc);
		return 1;
	}
}