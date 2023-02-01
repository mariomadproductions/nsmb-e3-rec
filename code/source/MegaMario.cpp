#include "nsmb/stage/misc.h"
#include "nsmb/stage/entity.h"
#include "nsmb/stage/player/player.h"
#include "nsmb/physics/activecollider.h"
#include "nsmb/system/input.h"
#include "nsmb/system/function.h"
#include "extra/undocumented.hpp"

// Set zoom when growing to Mega form
ncp_call(0x0212027C, 10)
void megaGrowZoomHook(int item, int playerID)
{
	StageEntity::getCollectablePoints(item, playerID); // Keep replaced instruction
	Stage::setZoom(0x1400, 16, playerID, 0);
}
// Fancier but less accurate alternative:
// ncp_hook(0x02120344, 10) void megaMarioGrowZoomHook() { Stage::setZoom(0x1400, 64, 0, 0); }

// Set zoom when un-growing from Mega form
ncp_call(0x0212052C, 10)
void megaShrinkZoomHook(Player* player)
{
	player->megaShrunk(); // Keep replaced instruction
	Stage::setZoom(0x1000, 16, player->playerID, 0);
}

ncp_repl(0x02120288, 10, "MOV R1, #0x4B0") // Change Mega Mushroom duration

ncp_repl(0x02011A7C, "NOP") // Do not load Mega Mario music
ncp_repl(0x02120298, 10, "NOP") // Do not play Mega Mario music

// Mega Mushroom doesn't move around
ncp_repl(0x020D37E0, 10, "B 0x020D3818");
ncp_repl(0x020D368C, 10, "B 0x020D3694");

// MEGA KICK ===================================

namespace PlayerKicking
{

ActiveCollider sPlayerColilders[2];

void kickCollisionCallback(ActiveCollider& _self, ActiveCollider& _other)
{
	StageEntity& other = *static_cast<StageEntity*>(_other.owner);

	if (other.actorType != ActorType::Entity)
		return;

	if (other.id == 0xF1) // Tile particles actor?
		return;

	other.collisionType |= CollisionType::Entity;
}

void createKickColliders(Player* player)
{
	ActiveCollider* p = &sPlayerColilders[player->playerID];

	static ActiveColliderInfo info
	{
		.rect = { 0, 0, 0, 0 },
		.selfGroup = CollisionGroup::PlayerSpecial,
		.selfFlag = CollisionFlag::DamageEntity,
		.checkGroupMask = 0x93,
		.checkFlagMask = 0xFFDE,
		.options = 0,
		.callback = &kickCollisionCallback,
	};

	if (player->currentPowerup == PowerupState::Mega)
	{
		info.rect.halfWidth = 48 * (FX32_ONE >> 1);
		info.rect.halfHeight = 40 * (FX32_ONE >> 1);
	}
	else
	{
		info.rect.halfWidth = 16 * (FX32_ONE >> 1);
		info.rect.halfHeight = 12 * (FX32_ONE >> 1);
	}

	*p = ActiveCollider();
	p->init(player, info);
	p->link();
}

void destroyKickColliders(Player* player)
{
	ActiveCollider* p = &sPlayerColilders[player->playerID];
	p->unlink();
}

void updateKickColliders(Player* player)
{
	ActiveCollider* p = &sPlayerColilders[player->playerID];

	u32 footNodeID = 2;
	u32 legNodeID = 9;
	u32 rootNodeID = 5;

	Vec3 foot, leg, root;
#define COPY_NODE_VEC(n) \
		n.x = player->model.nodeTransforms[(n##NodeID)].m[3][0]; \
		n.y = player->model.nodeTransforms[(n##NodeID)].m[3][1]; \
		n.z = player->model.nodeTransforms[(n##NodeID)].m[3][2];

	COPY_NODE_VEC(foot);
	COPY_NODE_VEC(leg);
	COPY_NODE_VEC(root);


#define PRINT_VEC(v) v.x << " - " << v.y << " - " << v.z

	//cout << "Foot   : " << PRINT_VEC(foot) << "\n";
	//cout << "Root   : " << PRINT_VEC(root) << "\n";
	//cout << "Player : " << PRINT_VEC(player->actor.position) << "\n";

	Vec3 footOfs, legOfs;

	footOfs = foot - player->position;
	legOfs = leg - player->position;

	Vec3 footToRootOfs;
	footToRootOfs = foot - root;

	//cout << "Foot-Root : " << PRINT_VEC(footToRootOfs) << "\n";

	p->hitbox.rect.x = footOfs.x/* - p->sizeX*/;
	p->hitbox.rect.y = footOfs.y/* + p->sizeY*/;

	ActiveColliderDestroyBlocks(p, 0x06502800, player->direction, player->playerID, 0);
}

bool kickState(Player* player, void* arg)
{
	if (player->mainStateStep == Func::Init)
	{
		player->mainStateStep = 1;
		if (player->currentPowerup == PowerupState::Mega)
			player->actionFlag.flag40000000 = 1;
		player->setAnimation(83, 0, Player::FrameMode::Restart, 0x800, 0);

		createKickColliders(player);
		updateKickColliders(player);
		return true;
	}
	if (player->mainStateStep == Func::Exit)
	{
		destroyKickColliders(player);
		return true;
	}

	updateKickColliders(player);

	if (player->isBodyAnimationCompleted() || player->collisionFlag.ground)
	{
		player->switchMainState(ptmf_cast(rcast<bool(*)(Player*, void*)>(0x021135B8)));
	}
	else
	{
		if (player->mainStateStep == 0x17)
			player->setBodyAnimationSpeed(0x100); //Kick retraction speed

		player->updateAnimation();
		player->mainStateStep++;
	}

	return true;
}

bool checkKick(Player* player)
{
	bool rButtonDown = player->keysPressed & Keys::R;
	bool notSmall = player->currentPowerup != PowerupState::Small && player->currentPowerup != PowerupState::Mini;
	bool nearGround = player->collisionFlag.ground || player->collisionFlag.predictGround;
	bool goingDown = player->velocity.y < 0;
	bool notJumping2 = player->consecutiveJumps != 2;

	if (rButtonDown && notSmall && notJumping2 && !(nearGround && goingDown))
	{
		player->switchMainState(ptmf_cast(kickState));
		return true;
	}

	return false;
}

ncp_call(0x021136E0, 10)
bool checkKickHook(Player* player)
{
	if (checkKick(player))
		return true;
	return Player_checkGroundPound(player);
}

}
