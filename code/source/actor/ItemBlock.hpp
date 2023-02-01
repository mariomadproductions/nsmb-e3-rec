#pragma once

#include "nsmb/stage/entity3d.h"
#include "nsmb/physics/collider.h"

class ItemBlock : public StageEntity3D
{
public:
	enum class Type : u8
	{
		ActivateEvent = 0,
		ItemSpawner = 1,
		DoesNothing = 2
	};

	enum class Color : u8
	{
		Blue = 0,
		Green = 1,
		Yellow = 2
	};

	struct Settings : BitFlag<u32>
	{
		u32 downShift : 4;
		u32 rightShift : 4;
		u32 type : 4;
		u32 color : 2;
		u32 direction : 1;
		u32 reserved1 : 1;
		u32 size : 8;
		u32 item : 5;
		u32 singleUse : 1;
		u32 puffs : 1;
		u32 reserved2 : 1;
	};

	Collider collider;

	void (*updateFunc)(ItemBlock*);
	s8 updateStep;

	Actor* hitActor; // Last actor hitting the block

	Vec3 initPos;  // Used when setting spawn values
	Vec3 startPos; // Used when changing states

	Type type;     // What happens on hit
	Color color;   // Block color
	s8 direction;  // The rotation direction
	u8 size;       // Block size
	s8 item;       // The item to spawn
	s8 singleUse;  // If the block turns green after use
	s8 puffs;      // If the block explodes
	fx32 halfSize; // Used to get block top and bottom positions

	u8 topPounded;
	u8 beingHit;

	u8 rotTimer;
	u8 hitTimer;

	static ActorProfile profile;

	constexpr static ObjectInfo objectInfo = {
		0, 0, // position
		0, 0, // renderSize
		0, 0, // spawnOffset
		0, 0, // viewOffset
		CollisionSwitch::None, // collisionSwitch
		SpawnSettings::None // spawnSettings
	};

	static bool loadFiles();
	s32 onCreate() override;
	s32 onUpdate() override;
	s32 onDestroy() override;

	void switchState(void (ItemBlock::*updateFunc)());
	void setColor(Color color, bool setup = false);
	void rotateState();
	void hitBehavior(bool animEnd);
	void hitState();
	static void hitFromTop(StageActor& self, StageActor& other);
	static void hitFromBottom(StageActor& self, StageActor& other);
	static void hitFromSide(StageActor& self, StageActor& other);
};
