#include "nsmb.h"

/*extern "C"
void PlayerActor_MyRunHitPlayerCollision(PlayerActor* mario, PlayerActor* luigi, bool marioInFront)
{
	u32 mario_contact_force = mario->actor.collisionBitfield;
	u32 luigi_contact_force = luigi->actor.collisionBitfield;

	int direction = marioInFront ? -1 : 1;

	bool MarioHitLuigi = mario_contact_force > luigi_contact_force;
	bool EqualHitForce = mario_contact_force == luigi_contact_force;

	Vec2 relative_pos = Vec2(0);
	if (EqualHitForce)
	{
		relative_pos.x = 0xC00 * direction;
		mario->actor.base.vtable->execState6(mario, &relative_pos);
		relative_pos.x = -0xC00 * direction;
		luigi->actor.base.vtable->execState6(luigi, &relative_pos);
	}
	else
	{
		if (MarioHitLuigi)
		{
			relative_pos.x = 0x1800 * direction;
			mario->actor.base.vtable->execState6(mario, &relative_pos);
			relative_pos.x = -1 * direction;
			luigi->actor.base.vtable->execState6(luigi, &relative_pos);
		}
		else
		{
			relative_pos.x = -1 * direction;
			mario->actor.base.vtable->execState6(mario, &relative_pos);
			relative_pos.x = 0x1800 * direction;
			luigi->actor.base.vtable->execState6(luigi, &relative_pos);
		}
	}
}*/
extern "C"
void PlayerActor_MyRunHitPlayerCollision(PlayerActor* mario, PlayerActor* luigi, bool luigiInFront)
{
	u32 mario_contact_force = mario->actor.collisionBitfield;
	u32 luigi_contact_force = luigi->actor.collisionBitfield;

	bool MarioHitLuigi = mario_contact_force > luigi_contact_force;
	bool EqualHitForce = mario_contact_force == luigi_contact_force;

	Vec2 relative_pos = Vec2(0);
	if (EqualHitForce)
	{
		relative_pos.x = 0xC00;
		mario->actor.base.vtable->execState6(mario, &relative_pos);
		relative_pos.x = -0xC00;
		luigi->actor.base.vtable->execState6(luigi, &relative_pos);
	}
	else
	{
		if (MarioHitLuigi)
		{
			relative_pos.x = 0x1800;
			mario->actor.base.vtable->execState6(mario, &relative_pos);
			relative_pos.x = -1;
			luigi->actor.base.vtable->execState6(luigi, &relative_pos);
		}
		else
		{
			relative_pos.x = -1;
			mario->actor.base.vtable->execState6(mario, &relative_pos);
			relative_pos.x = 0x1800;
			luigi->actor.base.vtable->execState6(luigi, &relative_pos);
		}
	}
}
//MARIO IN FRONT OF LUIGI
void nsub_02109FDC_ov_0A()
{
	asm("MOV     R0, R9");
	asm("MOV     R1, R8");
	asm("MOV     R2, #0");
	asm("BL      PlayerActor_MyRunHitPlayerCollision");
	asm("B       0x0210A034");
}
//MARIO BEHIND LUIGI
void nsub_02109D44_ov_0A()
{
	asm("MOV     R0, R9");
	asm("MOV     R1, R8");
	asm("MOV     R2, #1");
	asm("BL      PlayerActor_MyRunHitPlayerCollision");
	asm("B       0x02109D9C");
}