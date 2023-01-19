#pragma once

#include "nsmb/stage/entity3danm.h"
#include "nsmb/physics/collider.h"

class BetaSwitch : public StageEntity3DAnm
{
public:
	Collider collider;
	u16 hitTimer;

	static ActorProfile profile;

	static bool loadFiles();
	s32 onCreate() override;
	s32 onUpdate() override;
	s32 onDestroy() override;

	static void hitFromTop(StageActor& self, StageActor& other);
};
