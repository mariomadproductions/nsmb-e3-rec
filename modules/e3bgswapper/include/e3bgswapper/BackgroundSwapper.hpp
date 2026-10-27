#pragma once

#include <nsmb/game/stage/entity.hpp>
#include <nsmb/game/stage/layout/data/object.hpp>

#include "objectids/e3bgswapper.hpp"

// The graphics the screen holds now, by their background, foreground and
// tileset IDs. Set by the binary when an area loads, and by every swapper
// that changes them.
namespace BackgroundSwapperState
{
	extern u8 lastBG;
	extern u8 lastFG;
	extern u8 lastTS;
}

class BackgroundSwapper : public StageEntity
{
public:
	u8 BG_ID;
	u8 FG_ID;
	u8 TS_ID;

	static ActorProfile Profile;

	constexpr static ObjectInfo ObjectInfo_Default = {
		0, 0, // position
		0, 0, // renderSize
		0, 0, // spawnOffset
		0, 0, // viewOffset
		EntityProperties::None, // properties
		SpawnSettings::None // spawnSettings
	};

	s32 onCreate() override;
	s32 onUpdate() override;

	void loadBG();
	void loadFG();
	void loadTS();
	void doSwapping();
	void checkIfClose();
};
