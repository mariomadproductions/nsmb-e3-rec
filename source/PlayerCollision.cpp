#include "nsmb/game.h"
#include "nsmb/stage/player/player.h"

namespace PlayerExt {

// ================ COLLISION ENABLED CONDITIONS ================

bool friendlyCollisionAllowed(int R0)
{
	bool hasStarman = false;
	for (int i = 0; i < Game::getPlayerCount(); i++)
	{
		if (Game::getStarmanTimer(i) != 0)
			hasStarman = true;
	}
	if ((R0 & 1) || hasStarman)
		return false;
	return true;
}

ncp_jump(0x021096E8, 10)
NTR_NAKED void friendlyCollisionAllowedHook() {asm(R"(
	BL      _ZN9PlayerExt24friendlyCollisionAllowedEi
	CMP     R0, #0
	BNE     0x02109704
	B       0x021096F0
)");}

// ================ RUNNING/BUMPING COLLISION ================

void customPlayerBump(Player* mario, Player* luigi, bool luigiInFront)
{
	bool marioHitLuigi = mario->velH > luigi->velH;
	bool equalHitForce = mario->velH == luigi->velH;

	int direction = luigiInFront ? 1 : -1;
	if (marioHitLuigi)
		direction *= -1;

	Vec2 relativePos = Vec2(0);
	if (equalHitForce)
	{
		relativePos.x = 0xC00 * direction;
		mario->tryPlayerBump(relativePos);
		relativePos.x = -0xC00 * direction;
		luigi->tryPlayerBump(relativePos);
	}
	else
	{
		if (marioHitLuigi)
		{
			relativePos.x = 0x1800 * direction;
			mario->tryPlayerBump(relativePos);
			relativePos.x = -1 * direction;
			luigi->tryPlayerBump(relativePos);
		}
		else
		{
			relativePos.x = -1 * direction;
			mario->tryPlayerBump(relativePos);
			relativePos.x = 0x1800 * direction;
			luigi->tryPlayerBump(relativePos);
		}
	}
}

// Mario in front of Luigi
ncp_repl(0x02109FDC, 10, R"(
	MOV     R0, R9
	MOV     R1, R8
	MOV     R2, #0
	BL      _ZN9PlayerExt16customPlayerBumpEP6PlayerS1_b
	B       0x0210A034
)")

// Mario behind Luigi
ncp_repl(0x02109D44, 10, R"(
	MOV     R0, R9
	MOV     R1, R8
	MOV     R2, #1
	BL      _ZN9PlayerExt16customPlayerBumpEP6PlayerS1_b
	B       0x02109D9C
)")

}
