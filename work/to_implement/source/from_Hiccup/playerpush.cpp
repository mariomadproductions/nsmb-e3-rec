#include "nsmb.h"

//this is unfinished

static bool Player_pushingState(PlayerActor* self, s32 args) {

	if (self->P.movementStateStep == -1)
		return true;

	if (!self->P.movementStateStep) {
		PlayerActor_setAnimation(self, 0x2E, 0, 0, FX32_ONE, 0);
		self->P.movementStateStep++;
		return true;
	}

	PlayerActor_updateAnimation(self);
	
	return true;
}

void hook_02106C10_0A(PlayerActor* self) {
	
	bool touchingWall = bool(self->collider.collisionBitfield & (self->info.direction ? 42 : 21));
	bool holdingKeys = self->P.ButtonsHeld & (self->info.direction ? PAD_KEY_LEFT : PAD_KEY_RIGHT);
	bool onGround = (self->P.collBitfield & ColliderCollisionBitfield::ONGROUND);
	bool isMega = (self->P.powerup == Powerup::MEGA);

	if (touchingWall && holdingKeys && onGround && !isMega) {
		PlayerActor_setMovementState(self, reinterpret_cast<int>(Player_pushingState), 0, 0);
	} else if (self->P.movementStateFunc == reinterpret_cast<void*>(Player_pushingState)) {
		PlayerActor_setMovementState(self, 0x02115AAC, 0, 0); // set idle state
	}
}
