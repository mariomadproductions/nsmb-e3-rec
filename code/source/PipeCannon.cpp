#include <nsmb/game/stage/entity.hpp>
#include <nsmb/game/stage/player/player.hpp>
#include <nsmb/game/stage/player/common.hpp>

// ============================================= PARTICLES =============================================

// Spawn Starman particles while being shot instead of the pipe cannon ones
ncp_jump(0x0210C8DC, 10)
NTR_NAKED void shootParticlesHook()
{asm(R"(
	MOV     R0, R4 // R0 = player
	BL      _ZN6Player19updateStarParticlesEv
	B       0x0210C92C
)");}

ncp_repl(0x020F87A0, 10, "B 0x020F87B4") // Do not spawn pipe cannon particles

// ============================================= INVINCIBILITY =============================================

// While being shot out of a pipe cannon the player is invincible and
// destroys whatever it touches, just like with a Starman.
NTR_USED static bool isPlayerInvincible(StageEntity* entity, u32 playerID, Player* player)
{
	bool beingShot = player->subActionFlag.flag20000000;

	if (Game::playerStarmanTimer[playerID] > 1 || beingShot)
	{
		if (beingShot)
			entity->spawnCoin();
		return true;
	}

	return false;
}

// StageEntity::playerCollision
ncp_jump(0x02098B08, 0)
NTR_NAKED void playerCollisionInvincibilityHook()
{asm(R"(
	MOV     R0, R7 // R0 = entity (R1 = playerID)
	MOV     R2, R4 // R2 = player
	BL      _ZL18isPlayerInvincibleP11StageEntitymP6Player
	CMP     R0, #0
	BEQ     0x02098B38 // Not invincible, damage the player
	B       0x02098B1C // Invincible, damage the entity
)");}

// ============================================= MISC =============================================

ncp_repl(0x020F8230, 10, "B 0x020F823C") // Fix pipe cannon desync
