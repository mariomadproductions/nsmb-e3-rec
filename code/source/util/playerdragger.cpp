#include "playerdragger.hpp"

#include "nsmb/player.h"
#include "nsmb/system/input.h"
#include "nsmb/system/function.h"

fx32 playerDragAccelX = 0;
fx32 playerDragAccelY = 0;

namespace PlayerDragger
{

bool dragState(Player* player, void* arg)
{
	if (player->transitionStateStep == Func::Init)
	{
		player->transitionStateStep = 1;
		player->rotation.y = 0;
		player->velH = 0;
		player->setAnimation(0, false, Player::FrameMode::Restart, 0x1000, 0);
		player->model.headFrameController.setFrame(0);
		player->model.bodyFrameController.setFrame(0);
		player->updateAnimation();
		return true;
	}
	if (player->transitionStateStep == Func::Exit)
	{
		return true;
	}

	u16 keysHeld = player->keysHeld;

	fx32 playerDragVelX = FX_Mul(0x1000, playerDragAccelX);
	if (keysHeld & Keys::Horizontal)
	{
		if (playerDragAccelX < 0x1000)
			playerDragAccelX = 0x1000;
		if (keysHeld & Keys::Left)
			player->position.x -= playerDragVelX;
		else if (keysHeld & Keys::Right)
			player->position.x += playerDragVelX;
		if (playerDragVelX < 0x10000)
			playerDragAccelX += 0x800;
	}
	else
	{
		playerDragAccelX = 0x1000;
	}

	fx32 playerDragVelY = FX_Mul(0x1000, playerDragAccelY);
	if (keysHeld & Keys::Vertical)
	{
		if (playerDragAccelY < 0x1000)
			playerDragAccelY = 0x1000;
		if (keysHeld & Keys::Down)
			player->position.y -= playerDragVelY;
		else if (keysHeld & Keys::Up)
			player->position.y += playerDragVelY;
		if (playerDragVelY < 0x10000)
			playerDragAccelY += 0x800;
	}
	else
	{
		playerDragAccelY = 0x1000;
	}

	return true;
}

void beginDrag(Player* player)
{
	player->switchMainState(ptmf_cast(rcast<bool(*)(Player*, void*)>(0x02115AAC)));
	player->switchTransitionState(ptmf_cast(dragState));
}

}
