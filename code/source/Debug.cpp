#include "nitro_if.h"

#include "nsmb/entity/scene.h"
#include "nsmb/system/input.h"
#include "util/collisionviewer.hpp"

namespace Debug
{
	bool collisionViewerEnabled = false;
	fx32 playerDragAccelX = 0;
	fx32 playerDragAccelY = 0;
	bool draggingPlayer = false;

	void update()
	{
		u16 keysHeld = Input::getHeldKeys(0);
		u16 keysPressed = Input::getPressedKeys(0);
		if ((keysHeld & Keys::Select) && (keysPressed & Keys::X))
		{
			collisionViewerEnabled = !collisionViewerEnabled;
		}

		if (Scene::currentSceneID == u16(SceneID::Stage))
		{
			Player* player = Game::getPlayer(0);
			if (keysHeld & Keys::X)
			{
				fx32 playerDragVelX = FX_Mul(0x1000, playerDragAccelX);
				if (keysHeld & Keys::Horizontal)
				{
					if (playerDragAccelX < 0x1000)
						playerDragAccelX = 0x1000;
					if (keysHeld & Keys::Left)
						player->position.x -= playerDragVelX;
					else if (keysHeld & Keys::Right)
						player->position.x += playerDragVelX;
					if (playerDragVelX < 0x18000)
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
					if (playerDragVelY < 0x18000)
						playerDragAccelY += 0x800;
				}
				else
				{
					playerDragAccelY = 0x1000;
				}

				if (!draggingPlayer)
				{
					player->beginCutscene(0);
					draggingPlayer = true;
				}
			}
			else if (draggingPlayer)
			{
				player->endCutscene();
				draggingPlayer = false;
			}
		}
	}

	void render3D()
	{
		if (collisionViewerEnabled && Scene::currentSceneID == u16(SceneID::Stage))
		{
			CollisionViewer::render();
		}
	}
}

ncp_jump(0x0200A6C0)
NTR_NAKED void inputFetchedHook() {asm(R"(
	BL      _ZN5Debug6updateEv
	ADD     SP, #4
	POP     {R4-R11,PC}
)");}

ncp_call(0x02004EFC)
NTR_NAKED void preSwapBufferHook() {asm(R"(
	BL      _ZN5Debug8render3DEv
	BL      NNS_G3dGeFlushBuffer
	B       0x02004EFC + 4
)");}
