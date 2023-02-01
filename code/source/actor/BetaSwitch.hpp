#pragma once

#include "nsmb/stage/entity3danm.h"
#include "nsmb/physics/collider.h"

class BetaSwitch : public StageEntity3DAnm
{
public:
	Collider collider;
	u16 hitTimer;

	static ActorProfile profile;

	constexpr static ObjectInfo objectInfo = {
		16, 16, // position
		4, 4, // renderSize
		0, 0, // spawnOffset
		0, -16, // viewOffset
		CollisionSwitch::None, // collisionSwitch
		SpawnSettings::None // spawnSettings
	};

	static bool loadFiles();
	s32 onCreate() override;
	s32 onUpdate() override;
	s32 onDestroy() override;

	static void hitFromTop(StageActor& self, StageActor& other);
};
