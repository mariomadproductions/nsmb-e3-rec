#include "nitro_if.h"

#include "nsmb/entity/scene.h"
#include "nsmb/system/input.h"
#include "nsmb/system/function.h"
#include "util/collisionviewer.hpp"
#include "util/playerdragger.hpp"

namespace Debug
{
	bool collisionViewerEnabled = false;
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
			if (keysHeld & Keys::X)
			{
				if (!draggingPlayer)
				{
					PlayerDragger::beginDrag(Game::getPlayer(0));
					draggingPlayer = true;
				}
			}
			else
			{
				if (draggingPlayer)
				{
					PlayerDragger::endDrag(Game::getPlayer(0));
					draggingPlayer = false;
				}
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