#include "BetaSwitch.hpp"

#include "nsmb/sound/sound.h"
#include "nsmb/filesystem/cache.h"
#include "nsmb/graphics/particle.h"
#include "extra/events.hpp"

constexpr u32 ModelFileID = { 1441 - 131 };
constexpr u32 AnimFileID = { 1440 - 131 };

static ColliderInfo BetaSwitch_colliderInfo =
{
	-0x10000, //left
	0x20000, //top
	0x10000, //right
	0, //bottom
	{
		BetaSwitch::hitFromTop, //callbackTop
		nullptr, //callbackBottom
		nullptr //callbackSide
	}
};

ActorProfile BetaSwitch::profile = {
	&constructObject<BetaSwitch>,
	0xFF, 0x5C,
	BetaSwitch::loadFiles
};

bool BetaSwitch::loadFiles()
{
	FS::Cache::loadFile(ModelFileID, false);
	FS::Cache::loadFile(AnimFileID, false);
	return true;
}

s32 BetaSwitch::onCreate()
{
	void* mdl = FS::Cache::getFile(ModelFileID);
	void* anim = FS::Cache::getFile(AnimFileID);

	model.create(mdl, anim, 0, 0, 0);
	model.init(0, FrameCtrl::Type::Looping, 0, 0);

	hitTimer = 0;

	scale = 0xE00;
	position.x += 0x8000;

	if (settings & 1)
	{
		scale /= 0x2000;
		position.x -= 0x8000;
	}

	collider.init(this, BetaSwitch_colliderInfo, 0, 0, &scale);
	collider.link();

	return 1;
}

s32 BetaSwitch::onUpdate()
{
	int hitTimerF = hitTimer - 1;
	if (hitTimerF >= 0)
	{
		if (hitTimerF == 0)
		{
			SND::playSFX(8, nullptr);
		}
		else if (hitTimerF == 16)
		{
			Event::activate(events[1]);

			VecFx16 axis = { -0x1000, -0x1000, 0x1000 };
			Particle::Handler::createParticle(203, position);
			Particle::Handler::createParticleAxis(203, position, &axis);

			Base::destroy();
		}
		hitTimer++;
	}
	return 1;
}

s32 BetaSwitch::onDestroy()
{
	collider.unlink();
	return 1;
}

void BetaSwitch::hitFromTop(StageActor& _self, StageActor& other)
{
	BetaSwitch& self = static_cast<BetaSwitch&>(_self);

	//If not hit by player
	if (other.actorType != ActorType::Player)
		return;

	self.collider.unlink();
	self.model.init(0, FrameCtrl::Type::Standard, 0x1000, 0);
	self.hitTimer = 1;
}
