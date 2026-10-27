//by Pengu
#include <nsmb/game/stage/entity.hpp>
#include <nsmb/game/stage/player.hpp>
#include <nsmb/core/system/input.hpp>
#include <nsmb/core/system/function.hpp>

namespace PlayerPush {
	static bool getPushing(Player* player)
	{
		bool touchingWall = bool(player->collisionMgr.collisionResult & (player->direction ? CollisionMgr::Result::WallLeftAny : CollisionMgr::Result::WallRightAny));
		bool holdingKeys = player->keysHeld & (player->direction ? Keys::Left : Keys::Right);
		bool onGround = player->collisionFlag.ground && player->consecutiveJumps >= 0;
		bool isMega = player->currentPowerup == PowerupState::Mega;

		return touchingWall && holdingKeys && onGround && !isMega;
	}

	static bool pushingState(Player* player, void* arg)
	{
		if (player->mainStateStep == Func::Init)
		{
			player->mainStateStep = 1;
			player->setAnimation(46, 1, Player::FrameMode::Restart, 0x900, 0);
			player->rotation.y = 0x3550 * StageEntity::unitDirection[player->direction];
			return true;
		}
		if (player->mainStateStep == Func::Exit)
		{
			return true;
		}

		PlayerCollisionFlag colFlag = player->collisionFlag;
		if (colFlag.ground && player->getJumpKeyPressed())
		{
			player->consecutiveJumps = 0;
			if (player->tryJump(3.35fx, 5, true, true, 0)) {
				return true;
			}
			if (((bool(*)(Player*))0x2111DEC)(player))
				return true;
		}

		if (getPushing(player))
		{
			player->setAnimation(46, 1, Player::FrameMode::Continue, 0x900, 0);
			player->updateAnimation();
		}
		else
		{
			player->setAnimation(0, 1, Player::FrameMode::Restart, 0x1000, 0);	

			if (player->model.animationFinished() || player->keysHeld & (player->direction ? Keys::Left : Keys::Right)) {
				player->switchMainState(ptmf_cast(rcast<bool(*)(Player*, void*)>(0x02115aac)));
			}

			player->updateAnimation();
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
