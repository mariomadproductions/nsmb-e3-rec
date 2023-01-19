#pragma once

#include "nsmb/stage/entity.h"

class BackgroundSwapper : public StageEntity
{
public:
	u8 BG_ID;
	u8 FG_ID;
	u8 TS_ID;

	static ActorProfile profile;

	s32 onCreate() override;
	s32 onUpdate() override;

	void loadBG();
	void loadFG();
	void loadTS();
	void doSwapping();
	void checkIfClose();
};