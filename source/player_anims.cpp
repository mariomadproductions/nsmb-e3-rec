#include "nsmb.h"

/*void hook_02120BB8_ov_0A(int, int animNo)
{
	cout << "Animation: " << animNo << "\n";
}*/

/*void nsub_02120BB8_ov_0A(int, int animNo)
{
	nocashPrint1("call: %lr%, anim: %r0%\n", animNo);
}*/

void repl_02114DFC_ov_0A() { asm("MOV R5, #0x800"); } //Slow down rotation speed

//Walking transition delay
void repl_0211667C_ov_0A() {}
void repl_02116698_ov_0A(PlayerActor* player, int animationNo, int startFrame, int unk1, int updateSpeed, int unk2)
{
	//0x3C00 is the max walk animation speed
	if (updateSpeed > (0x3C00 / 2))
		updateSpeed = (0x3C00 / 2);

	if (player->P.currentAnim == 2)
	{
		PlayerActor_SetAnimationSpeed(player, updateSpeed);
	}
	else
	{
		if (player->P.currentAnim == 1)
		{
			fx32 xvel = MATH_ABS(player->actor.velocity.x);
			if (xvel >= 0x1800)
			{
				PlayerActor_SetAnimation(player, 2, startFrame, unk1, updateSpeed, unk2);
			}
			else
			{
				PlayerActor_SetAnimationSpeed(player, updateSpeed);
			}
		}
		else
		{
			PlayerActor_SetAnimation(player, 1, startFrame, unk1, updateSpeed, unk2);
		}
	}
}
void nsub_02116A14_ov_0A() { asm("CMP R0, #1"); asm("B 0x02116A18"); }
void repl_02116A2C_ov_0A() { asm("MOV R1, #1"); }

//void nsub_0210B06C() { nocashPrint("%lr%\n"); }