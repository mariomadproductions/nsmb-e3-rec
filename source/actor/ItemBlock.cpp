#include "ItemBlock.hpp"

#include "nsmb/filesystem/cache.h"
#include "nsmb/graphics/particle.h"
#include "extra/events.hpp"
#include "extra/undocumented.hpp"

constexpr u32 ModelFileID[] = { 1212 - 131, 1213 - 131, 1214 - 131 };
constexpr bool ResetRotationBug = true; //Enables a bug that existed in the beta

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
	ItemBlock::SettingsData* pSettings = reinterpret_cast<ItemBlock::SettingsData*>(&settings);
	this->type = static_cast<Type>(pSettings->type);
	this->color = static_cast<Color>(pSettings->color);
	this->direction = pSettings->direction ? 1 : -1;
	this->size = pSettings->size;
	this->item = pSettings->item;
	this->singleUse = pSettings->singleUse;
	this->puffs = pSettings->puffs;
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

	this->position.y -= 0x1000 * pSettings->downShift;
	this->position.x += 0x1000 * pSettings->rightShift;

	this->startPos = this->position;

	this->setColor(this->color, true);

	this->collider.init(this, ItemBlock_colliderInfo, 0, 0, &this->scale);
	this->collider.link();

	this->beingHit = false;
	this->rotTimer = 0;
	this->setExecuteState(&ItemBlock::rotateExecuteState);

	return 1;
}

s32 ItemBlock::onUpdate()
{
	(this->*execFunc)();
	destroyInactive(0);
	return 1;
}

s32 ItemBlock::onDestroy()
{
	this->collider.unlink();
	return 1;
}

void ItemBlock::setExecuteState(void (ItemBlock::*execFunc)())
{
	if (this->execFunc != execFunc)
	{
		if (this->execFunc)
		{
			this->execStep = -1;
			(this->*execFunc)();
		}

		this->execFunc = execFunc;

		this->execStep = 0;
		(this->*execFunc)();
	}
}

void ItemBlock::setColor(Color color, bool setup)
{
	if (this->color != color || setup)
	{
		this->color = color;

		void* modelFile = FS::Cache::getFile(ModelFileID[static_cast<int>(this->color)]);
		this->model.create(modelFile, 0, 0);

		if (ResetRotationBug && !setup)
		{
			this->rotTimer = 0;
			this->rotation.y = 0;
		}
	}
}

void ItemBlock::rotateExecuteState()
{
	if (this->execStep)
	{
		if (this->execStep != -1)
		{
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
	}
	else
	{
		this->execStep = 1;
		this->position = this->startPos;
	}
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
		int spriteData = this->item;
		if (this->item == 5)
		{
			spriteData |= 0x1000000;
		}
		if (this->topPounded)
		{
			if (!this->puffs)
			{
				spriteData |= 0x60;
			}
			spawnPos.y -= this->halfSize;
		}
		else
		{
			spawnPos.y += this->halfSize - 0x10000;
		}
		if (this->puffs)
		{
			spriteData |= 0x1000000;
			spawnPos.y += 192 << 12;
		}

		int direction = (this->hitActor->position.x > this->startPos.x) ? 0x80000000 : 0;
		spriteData |= direction;

		Actor::spawnActor(31, spriteData, &spawnPos, 0, 0, 0);
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
			this->setExecuteState(&ItemBlock::rotateExecuteState);
		}
	}
}

void ItemBlock::hitExecuteState()
{
	if (this->execStep == -1)
	{
		this->beingHit = false;
		this->topPounded = false;
	}
	else if (this->execStep)
	{
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
	else
	{
		this->execStep = 1;
		this->beingHit = true;
		this->hitTimer = 0;
		this->position = this->startPos;
	}
}

void ItemBlock::hitFromTop(StageActor& _self, StageActor& other)
{
	ItemBlock& self = reinterpret_cast<ItemBlock&>(_self);

	//If not hit by player
	if (other.actorType != ActorType::Player || self.beingHit)
		return;

	Player& player = reinterpret_cast<Player&>(other);

	if (player.actionFlag.groundpounding && (player.animID != 0x15))
	{
		self.topPounded = true;
		self.hitActor = &player;
		self.setExecuteState(&ItemBlock::hitExecuteState);
	}
}

void ItemBlock::hitFromBottom(StageActor& _self, StageActor& other)
{
	ItemBlock& self = reinterpret_cast<ItemBlock&>(_self);

	//If not hit by player or if being hit already
	if (other.actorType != ActorType::Player || self.beingHit)
		return;

	self.hitActor = &other;
	self.setExecuteState(&ItemBlock::hitExecuteState);
}

void ItemBlock::hitFromSide(StageActor& _self, StageActor& other)
{
	ItemBlock& self = reinterpret_cast<ItemBlock&>(_self);

	if (self.beingHit)
		return;

	if ((other.id == 94) || (other.id == 95) || (other.id == 54) || (other.id == 40) ||
		(other.activeCollider.hitbox.callback == StageEntity::shellCallback))
	{
		self.hitActor = &other;
		self.setExecuteState(&ItemBlock::hitExecuteState);
	}
}
