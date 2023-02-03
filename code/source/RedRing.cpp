#include "nsmb/entity/base.h"
#include "nsmb/entity/list.h"
#include "nsmb/stage/misc.h"
#include "nsmb/stage/entity.h"
#include "nsmb/stage/animatedtiles.h"
#include "nsmb/stage/layout/stagelayout.h"
#include "nsmb/stage/actors/ov54/redcoinring.h"
#include "nsmb/graphics/fader.h"
#include "extra/undocumented.hpp"

static u32 sRingCollected[2];
static u32* sRespawnEntrance = rcast<u32*>(0x0208B0B8);

class RedCoinRingExt : public RedCoinRing
{
public:
	inline u8 getRingID() { return settings & 0xF; }
	inline u8 getEntranceID() { return (settings >> 8) & 0xFF; }
	inline u8& frame() { return rcast<u8*>(&unused)[0]; }

	NTR_USED bool getCollected(u32 playerID)
	{
		return (sRingCollected[playerID] >> getRingID()) & 1;
	}

	NTR_USED void updateColor()
	{
		bool marioCollected = getCollected(0);
		bool luigiCollected = getCollected(1);

		u8 color = marioCollected | (luigiCollected << 1);

		animation.setFrame(color << FX32_SHIFT);
	}

	NTR_USED void onCollided(u32 playerID)
	{
		sRingCollected[playerID] |= (1 << getRingID());
		updateColor();

		sRespawnEntrance[playerID] = getEntranceID();
	}

	// Modify easeRotation so that the ring can stop rotating
	NTR_USED void easeRotation_override(s16& value, s16 endValue, s16 step)
	{
		s8 direction = StageEntity::unitDirection[direction ^ 1];
		u8& frame = this->frame();

		if (frame == 0x40)
		{
			rotation.y = -0x2000 * direction;
			switchState(RedCoinRing::sWaitCollect);
			return;
		}

		easeRotation(value, endValue, 0x30);
		frame++;
	}
};

// Set Red Ring allocation size
ncp_over(0x021539D8, 54)
static const u32 sizeof_RedRing = sizeof(RedCoinRingExt);

ncp_jump(0x021531DC, 54)
NTR_NAKED void ringOnCreateHook()
{asm(R"(
	MOV     R0, R4      // R0 = ring
	BL      _ZN14RedCoinRingExt11updateColorEv // Update color on create
	LDR     R0, [R4,#8] // Keep replaced instruction
	B       0x021531E0  // Return to code
)");}

ncp_repl(0x021535B4, 54, "BL _ZN14RedCoinRingExt21easeRotation_overrideERsss") // Override easeRotation

ncp_repl(0x02153284, 54, "NOP") // Do not reset the color on create

ncp_hook(0x0215E478, 54)
void ringResetCollectStateHook()
{
	sRingCollected[0] = 0;
	sRingCollected[1] = 0;
}

ncp_jump(0x0215365C, 54)
NTR_NAKED void ringCollisionCheckHook() // Do not allow player to hit ring if already collected
{asm(R"(
	BEQ     0x021537CC // If player pointer is null then continue to check next player
	PUSH    {R0}       // Save player pointer to stack
	MOV     R0, R6     // Pass actor as first argument
	MOV     R1, R5     // Pass player ID as second argument
	BL      _ZN14RedCoinRingExt12getCollectedEm // Execute the collect check function
	CMP     R0, #1     // Compare if ring is collected
	POP     {R0}       // Restore player pointer from stack
	BEQ     0x021537CC // If ring is collected then continue to check next player
	B       0x02153660 // Return to code in case all matches
)");}

// This hook also allows the ring to respawn on area change
ncp_over(0x021536A8, 54)
NTR_NAKED void ringCollidedHook()
{asm(R"(
	MOV     R0, R6 // R0 = ring
	MOV     R1, R5 // R1 = playerID
	BL      _ZN14RedCoinRingExt10onCollidedEm // Execute the ring collided function
	NOP            // Jump back to code
)");}

ncp_jump(0x021534E4, 54)
NTR_NAKED void ringSetupCollectedStateHook() // Set some ring variables on collected state enter
{asm(R"(
	MOV     R1, #0          // R1 = 0;
	STRB    R1, [R0,#0x4E4] // ring->frame() = R1;
	B       0x021534E8      // Return (Next instruction: ring->permanentDelete = R1;)
)");}

// ============================================= CORE RESPAWN =============================================

ncp_repl(0x0212B2DC, 11, "MOV R0, #1") // Do not decrement player lives
ncp_repl(0x02119CB8, 10, "NOP") // Do not freeze timer on player death

NTR_USED static bool customRespawnCondition() // Implement new system
{
	fx32 timeLeft = *rcast<fx32*>(0x020CA8B4);
	if (timeLeft == 0)
	{
		Stage::exitLevel(0);
		return false; // Do not respawn
	}
	return true; // Respawn
}

// Take total control of death/respawn check system and set arguments
ncp_repl(0x0212B314, 11, R"(
	BL      _ZL22customRespawnConditionv
	POP     {R4-R6,PC}
)");

NTR_USED static u32 getRespawnEntrance(u32 playerID)
{
	u32 entrance = sRespawnEntrance[playerID];
	if (entrance == 0)
		return GetStartEntranceID(playerID);
	return entrance;
}

ncp_repl(0x0201E558, R"(
	MOV     R0, R4
	BL      _ZL18getRespawnEntrancem
	B       0x0201E588
)")

static void destroyStageSprites()
{
	SceneNode* node = Game::actorTree.root;
	while (node)
	{
		Base* obj = node->object;
		if (obj->type == ObjectType::Actor)
		{
			Actor* actor = static_cast<Actor*>(obj);
			if (actor->actorType == ActorType::Entity)
				actor->destroy();
		}
		node = node->getNext();
	}
}

ncp_call(0x021188C4, 10)
void playerRespawnHook(Player* player)
{
	player->direction = 0;
	if (Game::getPlayerCount() == 1)
	{
		int& timeLeft = *rcast<int*>(0x020CA8B4);
		timeLeft = Stage::getBlock<u16>(1)[2] << 12;

		destroyStageSprites();

		u16* spawnedSprite1 = rcast<u16*>(0x020CA3CC);
		u16* spawnedSprite2 = rcast<u16*>(0x020CA64C);
		u16* spriteRespData = rcast<u16*>(0x02129220);
		MI_CpuClearFast(spawnedSprite1, 0x100);
		MI_CpuClearFast(spawnedSprite2, 0x200);
		MI_CpuFillFast(spriteRespData, 0xFFFFFFFF, 0x100);

		Stage::events = 0;

		AnimatedTiles::brickFrame = 0;
		AnimatedTiles::questionBlockFrame = 0;
		AnimatedTiles::coinFrame = 0;

		Stage::stageLayout->animateBrickBlocks();
		Stage::stageLayout->animateQuestionBlocks();
		Stage::stageLayout->animateCoins(0);

		// Freeze
		Stage::actorFreezeFlag |= ActorCategory::Actor;

		// Change fading transition
		Game::fader.fadingType = Fader::FadingType::FadeOnly;
	}
}

// Hook stage tile reset
ncp_jump(0x02118888, 10)
NTR_NAKED void stageTileResetHook()
{asm(R"(
	BL      _ZN4Game14getPlayerCountEv  // Get the player count
	CMP     R0, #1                      // Compare if it is 1
	BNE     .Return1                    // (If not) return

	ADD     R0, R8, #0xB00  // &player->isRespawning
	LDRSH   R0, [R0,#0x68]  // R0 = *R0
	CMP     R0, #0          // Compare if it is 0
	MOVNE   R0, #1          // (If not) R0 = 1
	LDRNE   R1, =0x020CAC98 // (If not) R1 = &level->resetStage
	STRBNE  R0, [R1]        // (If not) *R1 = R0

.Return1:
	LDR     R0, =0x2089506 // Keep replaced instruction
	B       0x0211888C     // Jump back to code
)");}

// Restore fading head transition on single player respawn
ncp_call(0x02118DC0, 10)
u32 restoreHeadTransitionHook(u32 playerID)
{
	if (Game::getPlayerCount() == 1)
		Game::fader.fadingType = Fader::FadingType::FadeMask;

	return Game::getPlayerCharacter(playerID); // Keep replaced instruction
}

ncp_repl(0x02118974, 10, "NOP") // Player doesn't blink on respawn
ncp_repl(0x021189B8, 10, "NOP") // Player visible during respawn fade

ncp_call(0x0211C584, 10)
void unfreezeHook(Player* player)
{
	if (Game::getPlayerCount() == 1)
		Stage::actorFreezeFlag &= ~ActorCategory::Actor;

	player->spawnDefault(); // Keep replaced instruction
}

ncp_repl(0x0211C470, 10, "B 0x0211C580") // No pipe entrance on respawn
