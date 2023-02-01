// Original assembly by Skawo
// https://nsmbhd.net/post/51362/
// Ported by TheGameratorT

#include "nsmb/graphics/particle.h"
#include "nsmb/stage/layout/data.h"

ncp_over(0x02022D9C)
static u8 infoForBank[] = {
	3, // Mega Goomba
	4, // Petey Piranha
	1, // Mummipokey
	6, // Lakithunder
	2, // Cheep Skipper
	5  // Monty Tank
};

ncp_jump(0x02022D98)
BossFileInfo* getBossParticleInfoHook()
{
	BossFileInfo* table = rcast<BossFileInfo*>(0x02026C80);

	u8 bossObjBank = Stage::getBlock<u8>(14)[15];
	StageObject* stageObjs = Stage::stageBlocks.stageObjs;

	if (bossObjBank < 2) // Not a boss
		return nullptr;

	if (bossObjBank == 2) // Bowser
	{
		// Find which bowser type
		for (u32 i = 0; ; i++)
		{
			StageObject* stageObj = &stageObjs[i];
			u16 stageObjID = stageObj->id;
			if (stageObjID == -1) // Array end
				break;
			if (stageObjID == 58) // Bowser
				return &table[0];
			if (stageObjID == 63) // Dry Bowser
				return &table[7];
		}
		return &table[8]; // Giant Bowser
	}

	// Other bosses
	return &table[infoForBank[bossObjBank - 3]];
}
