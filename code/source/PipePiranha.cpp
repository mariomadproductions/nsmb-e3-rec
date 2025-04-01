#include <nsmb/game/stage/actor.hpp>

ncp_call(0x21427a8,32) // PipePiranha::onCreate
static void piranhaInitAC(ActiveCollider* ppAC, StageActor* pp, const ActiveColliderInfo& acInfo, u8 layerID) {
    ppAC->init(pp,acInfo,layerID);
    pp->scale.set(1.4fx);
    pp->activeCollider.hitbox.rect = {0, 12.0fx, 12.0fx, 12.0fx};
}