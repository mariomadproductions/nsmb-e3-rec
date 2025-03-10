#include "PlayerSpectate.hpp"
#include "nsmb/game.h"
#include "nsmb/stage/player/player.h"

namespace PlayerSpectate {

u32 sTargetForPlayer[2];
u32 sLocalTarget;

u32 getTarget(u32 playerID)
{
	return sTargetForPlayer[playerID];
};

void setTarget(u32 playerID, u32 targetPlayerID)
{
	sTargetForPlayer[playerID] = targetPlayerID;
	if (playerID == Game::localPlayerID)
		sLocalTarget = targetPlayerID;
};

NTR_USED Player* getLocalTargetPlayer()
{
	return Game::getPlayer(sLocalTarget);
}

NTR_USED static void onPlayerCreate(Player* player)
{
	u32 playerID = player->playerID;
	setTarget(playerID, 0);
	//setTarget(playerID, playerID);
}

asm(R"(

// Hook onPlayerCreate
ncp_jump_ov 0x020FF868, 10
	BL      _ZN14PlayerSpectateL14onPlayerCreateEP6Player
	LDR     R0, =0x02085A84 // Keep replaced instruction
	B       0x020FF86C      // Return to code

// (0x020BAA5C) StageLayout::onUpdate ----------------

ncp_repl_ov 0x020BACC0, 0, ".int _ZN14PlayerSpectate12sLocalTargetE"

// StageCamera

ncp_repl_ov 0x020CDF6C, 10, ".int _ZN14PlayerSpectate12sLocalTargetE"
ncp_repl_ov 0x020CE024, 10, "BL _ZN14PlayerSpectate20getLocalTargetPlayerEv"
ncp_repl_ov 0x020CE244, 10, "BL _ZN14PlayerSpectate20getLocalTargetPlayerEv"
ncp_repl_ov 0x020CE2F0, 10, ".int _ZN14PlayerSpectate12sLocalTargetE"
ncp_repl_ov 0x020CE654, 10, ".int _ZN14PlayerSpectate12sLocalTargetE"
ncp_repl_ov 0x020CE408, 10, ".int _ZN14PlayerSpectate12sLocalTargetE"
ncp_repl_ov 0x020CE460, 10, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x020B8CA8) ----------------

ncp_repl_ov 0x020B8D20, 0, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x01FFFE10) ----------------

ncp_repl 0x01FFFF74, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x020BBBDC) Player View Setup ----------------

ncp_repl_ov 0x020BC61C, 0, ".int _ZN14PlayerSpectate12sLocalTargetE"
ncp_repl_ov 0x020BC668, 0, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x020AD06C) ----------------

ncp_repl_ov 0x020AD26C, 0, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x0200D578) OAM::drawSprite ----------------

ncp_repl 0x0200D858, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x0200DC48) OAM::loadAffineSets ----------------

ncp_repl 0x0200DD74, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x02011F5C) Sound::updateSfxRange ----------------

ncp_repl 0x02012024, ".int _ZN14PlayerSpectate12sLocalTargetE"

// (0x02012038) Sound::playSFX ----------------

ncp_repl 0x020121D4, ".int _ZN14PlayerSpectate12sLocalTargetE"

)");

}
