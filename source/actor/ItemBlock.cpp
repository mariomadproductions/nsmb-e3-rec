#include "ItemBlock.hpp"

#include "nsmb/filesystem/cache.h"
#include "nsmb/graphics/particle.h"
#include "nsmb/system/function.h"
#include "extra/events.hpp"
#include "extra/undocumented.hpp"

constexpr u32 ModelFileID[] = { 1212 - 131, 1213 - 131, 1214 - 131 };
constexpr bool ResetRotationBug = true; // Enables a bug that existed in the beta

static ColliderInfo ItemBlock_colliderInfo =
{
	-0x10000, //left
	0x10000, //top
	0x10000, //right
	-0x10000, //bottom
	{
		ItemBlock::hitFromTop, //callbackTop
		ItemBlock::hitFromBottom, //callbackBottom
		ItemBlock::hitFromSide, //callbackSide
	}
};

ActorProfile ItemBlock::profile = {
	&constructObject<ItemBlock>,
	0xFD, 0x6C,
	ItemBlock::loadFiles
};

bool ItemBlock::loadFiles()
{
	FS::Cache::loadFile(ModelFileID[0], false);
	FS::Cache::loadFile(ModelFileID[1], false);
	FS::Cache::loadFile(ModelFileID[2], false);
	return true;
}

s32 ItemBlock::onCreate()
{
	Settings settings;
	settings.raw() = this->settings;

	this->type = Type(settings.type);
	this->color = Color(settings.color);
	this->direction = settings.direction ? 1 : -1;
	this->size = settings.size;
	this->item = settings.item;
	this->singleUse = settings.singleUse;
	this->puffs = settings.puffs;
	this->halfSize = (size * 0x1000) / 2;

	int tileSize = 0x20 * ((this->size + 9) / 16);
	this->renderSize.x = tileSize;
	this->renderSize.y = tileSize;

	this->initPos = this->position;
	if (GetSpriteAtPosUsed(this->initPos.x, this->initPos.y))
	{
		this->color = Color::Green;
		this->type = Type::DoesNothing;
	}
	this->scale = (this->size * 0x1000) / 32;

	this->position.y -= 0x1000 * settings.downShift;
	this->position.x += 0x1000 * settings.rightShift;

	this->startPos = this->position;

	alpha = 31;
	this->setColor(this->color, true);

	this->collider.init(this, ItemBlock_colliderInfo, 0, 0, &this->scale);
	this->collider.link();

	this->beingHit = false;
	this->rotTimer = 0;
	this->switchState(&ItemBlock::rotateState);

	return 1;
}

s32 ItemBlock::onUpdate()
{
	updateFunc(this);
	destroyInactive(0);
	return 1;
}

s32 ItemBlock::onDestroy()
{
	this->collider.unlink();
	return 1;
}

void ItemBlock::switchState(void (ItemBlock::*updateFunc)())
{
	auto updateFuncRaw = ptmf_cast(updateFunc);

	if (this->updateFunc != updateFuncRaw)
	{
		if (this->updateFunc)
		{
			this->updateStep = Func::Exit;
			this->updateFunc(this);
		}

		this->updateFunc = updateFuncRaw;

		this->updateStep = Func::Init;
		this->updateFunc(this);
	}
}

void ItemBlock::setColor(Color color, bool setup)
{
	if (this->color != color || setup)
	{
		this->color = color;

		void* modelFile = FS::Cache::getFile(ModelFileID[int(this->color)]);
		this->model.create(modelFile, 0, 0);

		if (ResetRotationBug && !setup)
		{
			this->rotTimer = 0;
			this->rotation.y = 0;
		}
	}
}

void ItemBlock::rotateState()
{
	if (this->updateStep == Func::Init)
	{
		this->updateStep = 1;
		this->position = this->startPos;
		return;
	}
	if (this->updateStep == Func::Exit)
	{
		return;
	}

	const int sleepTime = 10;
	const int rotateTime = 28;
	if (this->rotTimer > sleepTime)
	{
		this->rotation.y -= (0x4000 / rotateTime) * this->direction;
		if (this->rotTimer == rotateTime + sleepTime)
		{
			this->rotation.y = 0;
			this->rotTimer = -1;
		}
	}
	this->rotTimer++;
}

void ItemBlock::hitBehavior(bool animEnd)
{
	switch (this->type)
	{
	case Type::ActivateEvent:
		if (!animEnd)
			break;

		Event::activate(events[1]);
		break;
	case Type::ItemSpawner:
	{
		if (animEnd == (this->item != 3))
			break;

		Vec3 spawnPos = this->startPos;
		u32 settings = this->item;
		if (this->item == 5)
		{
			settings |= 0x1000000;
		}
		if (this->topPounded)
		{
			if (!this->puffs)
			{
				settings |= 0x60;
			}
			spawnPos.y -= this->halfSize;
		}
		else
		{
			spawnPos.y += this->halfSize - 0x10000;
		}
		if (this->puffs)
		{
			settings |= 0x1000000;
			spawnPos.y += 192 << 12;
		}

		u32 direction = (this->hitActor->position.x > this->startPos.x) ? 0x80000000 : 0;
		settings |= direction;

		Actor::spawnActor(31, settings, &spawnPos, 0, 0, 0);
		break;
	}
	default:
		break;
	}

	if (animEnd)
	{
		if (this->singleUse)
		{
			if (this->puffs)
			{
				Particle::Handler::createParticle(202, this->position);
				this->destroy(true);
			}
			else
			{
				this->type = Type::DoesNothing;
				this->setColor(Color::Green);
				SetSpriteAtPosUsed(this->initPos.x, this->initPos.y, 1);
			}
		}
		if (!this->puffs)
		{
			this->switchState(&ItemBlock::rotateState);
		}
	}
}

void ItemBlock::hitState()
{
	if (this->updateStep == Func::Init)
	{
		this->updateStep = 1;
		this->beingHit = true;
		this->hitTimer = 0;
		this->position = this->startPos;
		return;
	}
	if (this->updateStep == Func::Exit)
	{
		this->beingHit = false;
		this->topPounded = false;
		return;
	}

	int direction = this->topPounded ? -1 : 1;
	if (this->hitTimer < 10)
	{
		this->position.y += 0x1000 * direction;
		if (this->hitTimer == 9)
		{
			this->hitBehavior(false);
		}
	}
	else
	{
		this->position.y -= 0x1000 * direction;
		if (this->hitTimer == 19)
		{
			this->hitBehavior(true);
		}
	}
	this->collider.updatePosition();

	this->hitTimer++;
}

void ItemBlock::hitFromTop(StageActor& _self, StageActor& other)
{
	ItemBlock& self = scast<ItemBlock&>(_self);

	//If not hit by player
	if (other.actorType != ActorType::Player || self.beingHit)
		return;

	Player& player = scast<Player&>(other);

	if (player.actionFlag.groundpounding && (player.animID != 0x15))
	{
		self.topPounded = true;
		self.hitActor = &player;
		self.switchState(&ItemBlock::hitState);
	}
}

void ItemBlock::hitFromBottom(StageActor& _self, StageActor& other)
{
	ItemBlock& self = scast<ItemBlock&>(_self);

	//If not hit by player or if being hit already
	if (other.actorType != ActorType::Player || self.beingHit)
		return;

	self.hitActor = &other;
	self.switchState(&ItemBlock::hitState);
}

void ItemBlock::hitFromSide(StageActor& _self, StageActor& other)
{
	ItemBlock& self = scast<ItemBlock&>(_self);

	if (self.beingHit)
		return;

	if (bool(other.collisionMgr.sideSensor->flags & CollisionMgr::SensorFlags::ActivateQuestionBlocks))
	{
		self.hitActor = &other;
		self.switchState(&ItemBlock::hitState);
	}
}
