#include "nsmb/stage/player/player.h"

ncp_repl(0x02114DFC, 10, "MOV R5, #0xC00") // Slow down rotation speed

// Walking transition delay
ncp_repl(0x02116674, 10, "B 0x02116680")

ncp_call(0x02116698, 10)
void repl_02116698_ov_0A(Player* player, int id, bool doBlend, Player::FrameMode frameMode, fx32 speed, u16 frame)
{
	// 0x3C00 is the max walk animation speed
	if (speed > (0x3C00 / 2))
		speed = (0x3C00 / 2);

	if (player->animID == 2)
	{
		player->setBodyAnimationSpeed(speed);
	}
	else
	{
		if (player->animID == 1)
		{
			fx32 xvel = MATH_ABS(player->velocity.x);
			if (xvel >= 0x1800)
			{
				player->setAnimation(2, doBlend, frameMode, speed, frame);
			}
			else
			{
				player->setBodyAnimationSpeed(speed);
			}
		}
		else
		{
			player->setAnimation(1, doBlend, frameMode, speed, frame);
		}
	}
}
ncp_repl(0x02116A14, 10, "CMP R0, #1")
ncp_repl(0x02116A2C, 10, "MOV R1, #1")
