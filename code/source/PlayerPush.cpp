#include "nsmb/stage/player/player.h"
#include "nsmb/stage/entity.h"
#include "nsmb/system/input.h"
#include "nsmb/system/function.h"

namespace PlayerPush {

static bool getPushing(Player* player)
{
	bool touchingWall = bool(player->collisionMgr.collisionResult & (player->direction ? CollisionMgr::Result::WallLeftAny : CollisionMgr::Result::WallRightAny));
	bool holdingKeys = player->keysHeld & (player->direction ? Keys::Left : Keys::Right);
	bool onGround = player->collisionFlag.ground;
	bool isMega = player->currentPowerup == PowerupState::Mega;

	return touchingWall && holdingKeys && onGround && !isMega;
}

static bool pushingState(Player* player, void* arg)
{
	if (player->mainStateStep == Func::Init)
	{
		player->mainStateStep = 1;
		player->setAnimation(46, 0, Player::FrameMode::Restart, 0x1000, 0);
		player->rotation.y = 0x4000 * StageEntity::unitDirection[player->direction];
		return true;
	}
	if (player->mainStateStep == Func::Exit)
	{
		return true;
	}

	PlayerCollisionFlag colFlag = player->collisionFlag;
	if (colFlag.ground && player->getJumpKeyPressed())
	{
		if (player->trySpinBlockJump())
			return true;
		if (((bool(*)(Player*))0x2111DEC)(player))
			return true;
	}

	if (getPushing(player))
	{
		player->updateAnimation();
	}
	else
	{
		player->switchMainState(ptmf_cast(rcast<bool(*)(Player*, void*)>(0x021135B8)));
	}

	return true;
}

ncp_hook(0x02106C10, 10)
void checkPushHook(Player* player)
{
	if (getPushing(player))
	{
		player->switchMainState(ptmf_cast(pushingState));
	}
}

}
