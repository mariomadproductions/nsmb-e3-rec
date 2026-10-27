#pragma once

#include <nsmb/game/stage/entity3danm.hpp>
#include <nsmb/game/physics/collider.hpp>
#include <nsmb/game/stage/layout/data/object.hpp>

#include "objectids/e3betaswitch.hpp"

class BetaSwitch : public StageEntity3DAnm
{
public:
	Collider collider;
	u16 hitTimer;

	static ActorProfile Profile;

	constexpr static ObjectInfo ObjectInfo_Default = {
		16, 16, // position
		4, 4, // renderSize
		0, 0, // spawnOffset
		0, -16, // viewOffset
		EntityProperties::None, // properties
		SpawnSettings::None // spawnSettings
	};

	static bool loadFiles();
	s32 onCreate() override;
	s32 onUpdate() override;
	s32 onDestroy() override;

	static void hitFromTop(StageActor& self, StageActor& other);
};
