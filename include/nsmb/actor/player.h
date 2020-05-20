#pragma once

#include "nitro/types.h"
#include "nsmb/actor/nsmbtypes.h"
#include "nsmb/vector.h"
#include "nsmb/fxmath.h"
#include "nsmb/actor/actor.h"
#include "nsmb/model.h"

typedef enum ColliderCollisionBitfield {
	CLIMBABLE_LEFT = 64,
	CLIMBABLE_LEFT_2 = 256,
	CLIMBABLE_RIGHT = 128,
	CLIMBABLE_RIGHT_2 = 512,
	HIT_CEILING = 2,
	HIT_WALL_LEFT = 1024,
	HIT_WALL_RIGHT = 2048,
	HOVERING_TOUCHING_NORMAL_GROUND = 8192,
	IN_LIQUID = 4194304,
	ONGROUND = 1,
	PREDICT_TOUCHING_GROUND = 134217728,
	PUSHING_WALL = 4,
	SPECIAL_WALL_LEFT = 8,
	SPECIAL_WALL_RIGHT = 16,
	TOUCHING_SPRITE_GROUND = 32768,
	UNKNOWN_GROUND = 4096
} ColliderCollisionBitfield;

typedef enum PhysicsStateBitfield {
	GROUNDPOUND_BEFORE_GROUND = 16777216,
	IDLE_GROUNDPOUND = 128,
	LOW_HITBOX_STATE = 4,
	NOT_SHOOTING = 2,
	PIPE_OUT = 1,
	SWIMMING = 134217728,
	WATER_IN = 524288,
	WATER_OUT = 131072,
	WATER_OUT_JUMP = 262144
} PhysicsStateBitfield;

typedef enum TripleJumpRelated {
	GROUNDPOUNDING = 8388608,
	IN_SHELL = 4194304,
	JUMPING = 1048576,
	SLIDING_ON_WALL = 4,
	THROWING_ITEM = 128,
	WALL_JUMPING = 32
} TripleJumpRelated;

typedef enum MiscActionsBitfield {
	FALLING = 0x40,
	GROUNDPOUNDING_VINE = 0x20000,
	HOLDING_ITEM = 1,
	ON_VINE = 0x40000,
	SLIDING = 0x10,
	BEING_SHOOT_UP = 0x2000000,
	BEING_SHOOT = 0x20000000
} MiscActionsBitfield;

typedef struct PlayerActorOnly
{
	u32* function;
	u32					offset;
	u32* old_function;
	u32					old_offset;
	u16					unk4AC;
	u16					unk4B0;
	u32					unk4B4;
	u32					unk4B8;
	u32					unk4BC;
	u32					unk4C0;
	u32					unk4C4;
	u32					unk4C8;
	u32					unk4CC;
	u32					unk4D0;
	u32					unk4D4;
	u32					unk4D8;
	u32					unk4DC;
	u32					unk4E0;
	u32					unk4E4;
	u32					unk4E8;
	u32					unk4EC;
	u32					unk4F0;
	u32					unk4F4;
	u32					unk4F8;
	u32					unk4FC;
	u32					unk500;
	u32					unk504;
	u32					unk508;
	u32					unk50C;
	u32					unk510;
	u32					unk514;
	u32					unk518;
	u32					unk51C;
	u32					unk520;
	u32					unk524;
	u32					unk528;
	u32					unk52C;
	u32					unk530;
	u32					unk534;
	u32					unk538;
	u32					unk53C;
	u32					unk540;
	u32					unk544;
	u32					unk548;
	u32					unk54C;
	u32					unk550;
	u32					unk554;
	u32					unk558;
	u32					unk55C;
	u32					unk560;
	u32					unk564;
	u32					unk568;
	u32					unk56C;
	u32					unk570;
	u32					unk574;
	u32					unk578;
	u32					unk57C;
	u32					unk580;
	u32					unk584;
	u32					unk588;
	u32					unk58C;
	u32					unk590;
	u32					unk594;
	u32					unk598;
	u32					unk59C;
	u32					unk5A0;
	u32					unk5A4;
	u32					offsX;
	u32					offsY;
	u32					unk5B0;
	u32					unk5B4;
	u32					unk5B8;
	u32					unk5BC;
	u32					unk5C0;
	u32					unk5C4;
	u32					unk5C8;
	u32					unk5CC;
	u32					unk5D0;
	u32					unk5D4;
	u32					unk5D8;
	u32					unk5DC;
	u32					unk5E0;
	u32					unk5E4;
	u32					unk5E8;
	u32					unk5EC;
	u32					unk5F0;
	u32					unk5F4;
	u32					unk5F8;
	u32					unk5FC;
	u32					unk600;
	u32					unk604;
	u32					unk608;
	u32					unk60C;
	u32					unk610;
	u32					unk614;
	u32					unk618;
	u32					unk61C;
	u32					unk620;
	u32					unk624;
	u32					unk628;
	u32					unk62C;
	u32					unk630;
	u32					unk634;
	u32					unk638;
	u32					unk63C;
	u32					unk640;
	u32					unk644;
	u32					unk648;
	u32					unk64C;
	u32					unk650;
	u32					unk654;
	u32					unk658;
	u32					unk65C;
	u32					unk660;
	u32					unk664;
	u32					unk668;
	u32					unk66C;
	u32					unk670;
	u32					d;
	u32					unk678;
	u32					a;
	s32					b;
	u32					c;
	u8					e;
	u8					f;
	u8					g;
	u8					faceBitfield;
	u32* HeldItem;
	u32					unk68C;
	u32					unk690;
	u32					unk694;
	u32					unk698;
	u32					unk69C;
	u32					unk6A0;
	u32					unk6A4;
	u32					unk6A8;
	u32					unk6AC;
	u32					unk6B0;
	u32					unk6B4;
	u32					unk6B8;
	u32					unk6BC;
	u32					unk6C0;
	u32					unk6C4;
	u32					unk6C8;
	u32					unk6CC;
	spinState			spinstate;
	field_0x258			field_gay1;
	u32					unk708;
	u32					unk70C;
	field_0x258			field_gay2;
	u32					unk720;
	u32					unk724;
	Vec3				Vec3_4;
	Vec3				Vec3_5;
	Vec3				Vec3_6;
	u32					spinSetZero;
	u32					unk758;
	u32					unk75C;
	u32					unk760;
	u32					unk764;
	u32					unk768;
	u32                    currentAnim;
	u32                    unk770;
	u32                    unk774;
	u32    jumpBitfield; //0x778
	u32    miscActionsBitfield; //0x77C
	u32    physicsStateBitfield;
	u32                    unk784;
	ColliderCollisionBitfield    collBitfield;
	ColliderCollisionBitfield    oldCollBitfield;
	u32                    unk790;
	u32                    unk794;
	u32                    unk798;
	u8                    timer3;
	u8					unk79C_1;
	u8					unk79C_2;
	u8					unk79C_3;
	u16					ButtonsHeld;
	u16					ButtonsPressed;
	u32					unk7A4;
	u8					enteringAnEntrance;
	u8					virt64switch;
	u8					unk7AA;
	u8					powerupStateCurrent;
	u8					powerupStateOld;
	u8					powerupStateStart;
	u8					unk7AE;
	u8					unk7AF;
	u8					virt64thing;
	u8					unk7Ba;
	u8					unk7Bb;
	u8					unk7Bc;
	u32					player;
	u32					unk7B8;
	u8					unk7BC;
	u8					unk7BD;
	u8					unk7BE;
	u8					tripleJumpRelated7BF;
	u8					field_0x324;
	u8					timer2;
	u8					field_0x326;
	u8					field_0x327;
	u32					zeroInit1;
	u32					zeroInit2;
	u32					unk7D8;
	u32					unk7DC;
	collider_H			topStruct;
	collider_H			botStruct;
	collider_V			sideStruct;
	u32					field_0x368;
	u32					field_0x36c;
	u32					field_0x370;
	u32					field_0x374;
	ActivePhysics 		physics2;
	field_0x428			field_gay3;
	field_0x444			mA_functions;
	field_0x458			field_what;
	S16Vec3				S16Vec3_1;
	S16Vec3				S16Vec3_2;
	Vec3				Vec3_1;
	Vec3				Vec3_2;
	Vec3				Vec3_3;
	Vec2				Vec2_1;
	Vec2				Vec2_2;
	Vec2				Vec2_3;
	void*				movementStateFunc;
	u32					movementStateThumb;
	u32					unk988;
	u32					unk98C;
	void*				entranceStateFunc;
	u32					entranceStateThumb;
	u32					unk998;
	u32					unk99C;
	u32					unk9A0;
	u32					unk9A4;
	u32					unk9A8;
	u32					unk9AC;
	u32					unk9B0;
	u32					unk9B4;
	u32					setToZero;
	u32					unk9BC;
	u32					unk9C0;
	u32					unk9C4;
	u32					unk9C8;
	u32					unk9CC;
	u32					unk9D0;
	u32					unk9D4;
	u32					unk9D8;
	u32					unk9DC;
	u32					unk9E0;
	u32					unk9E4;
	u32					unk9E8;
	u32					unk9EC;
	u32					unk9F0;
	u32					unk9F4;
	u32					unk9F8;
	u32					unk9FC;
	u32					unkA00;
	u32					unkA04;
	u32					unkA08;
	u32					unkA0C;
	u32					unkA10;
	u32					unkA14;
	u32					unkA18;
	u32					notMega1;
	u32					notMega2;
	u32					unkA24;
	u32					unkA28;
	u32					unkA2C;
	u32					unkA30;
	u32					unkA34;
	u32					unkA38;
	u32					unkA3C;
	u32					unkA40;
	u32					unkA44;
	u32					unkA48;
	u32					unkA4C;
	u32					unkA50;
	u32					unkA54;
	u32					unkA58;
	u32					unkA5C;
	u32					unkA60;
	u32					unkA64;
	u32					unkA68;
	u32					unkA6C;
	u32					unkA70;
	u32					unkA74;
	u32					unkA78;
	u32					unkA7C;
	u32					unkA80;
	u32					unkA84;
	u32					unkA88;
	u32					miniSmth;
	u32					unkA90;
	u32					unkA94;
	u32					unkA98;
	u32					unkA9C;
	u32					unkAA0;
	u32					unkAA4;
	u32					unkAA8;
	u32					unkAAC;
	u32					unkAB0;
	u32					unkAB4;
	u32					unkAB8;
	u32					unkABC;
	u32					unkAC0;
	u32					unkAC4;
	u32					unkAC8;
	u32					unkACC;
	u32					unkAD0;
	u32					unkAD4;
	u32					unkAD8;
	u32					unkADC;
	u32					unkAE0;
	u32					unkAE4;
	u32					unkAE8;
	u32					unkAEC;
	u32					unkAF0;
	u32					unkAF4;
	u32					unkAF8;
	u32					unkAFC;
	u32					unkB00;
	u32					unkB04;
	u32					unkB08;
	u32					unkB0C;
	u32					unkB10;
	u32					unkB14;
	u32					unkB18;
	u32					unkB1C;
	u32					unkB20;
	u32					unkB24;
	u32					unkB28;
	u32					unkB2C;
	u32					unkB30;
	u32					unkB34;
	u32					unkB38;
	u32					unkB3C;
	u32					unkB40;
	u32					unkB44;
	u32					unkB48;
	u32					unkB4C;
	u32					unkB50;
	u32					unkB54;
	u32					unkB58;
	u32                    unkB5C;
	u32                    PlayerDeathTimer1;    //unkB60
	u32                    unkB64;
	u32                    PlayerDeathTimer2;    //unkB68
	u32					unkB6C;
	u32					unkB70;
	u32					unkB74;
	u16					timer;
	u16					spriteCollisionSomething;
	u32					unkB7C;
	u32					unkB80;
	u32					unkB84;
	u32					unkB88;
	u32					unkB8C;
	u32					unkB90;
	u32					unkB94;
	u32					unkB98;
	u8					unkB9C;
	u8					unkB9D;
	u8					movementStateStep; 			//Set to 1 when idle, 2 when moving (walking/running, falling, crounching), 3 when landing	
	u8					notInPipeCannon;
	u8					consecutiveJumps;
	u8					field_0x705;
	u8					field_0x706;
	u8					field_0x707;
	u16					field_0x708;
	u8					stateChangeTimer;
	u8					field_0x70b;				//Amount of frames that a powerup/damage transformation takes. Game sets it to 0x2805, and negates until 0	
	u32					unkBA8; 				 	//Set to 0x20000 on level begin, last digit is set to 7 when powerup is gained, and 3rd last digit is set to 1 when damage is taken.	
	u8					field_0x710;
	u8					entranceStateStep;
	u8					field_0x712;
	u8					currentModel;
	u8					field_0x714;
	u8					what;
	u8					field_0x716;
	u8					field_0x717;
	u8					field_0x718;
	u8					field_0x719;
	u8					modelTexture;
	u8					someValueSubtract;
	u8					field_0x71c;
	u8					field_0x71d;
	u8					somethingEight;
	u8					moveRelated1;
	u8					moveRelated2;
	u8					field_0x721;
	u8					field_0x722;
	u8					field_0x723;
	u32					unkBC0;
	u32					unkBC4;
	u8					groundpoundTimerMaybe;
	u8					idk2;
	u8					field_0x72e;
	u8					field_0x72f;
}	PlayerActorOnly;

typedef struct PlayerActor
{
	Actor				actor;				// 0	-- Actor
	ActivePhysics 		activephysics;		// 120	-- Active Physics
	Collider			collider;			// 1D0	-- Collider
	PlayerActorInfo		info;				// 2BC	-- Mario Info
	ModelAnim3d			model;				// 3F4	-- Model
	PlayerActorOnly		P;					// 49C	-- Player Stuff
}	PlayerActor;

#ifdef __cplusplus
extern "C"
{
#endif

	// Sets the player animation
	void PlayerActor_SetAnimation(PlayerActor* player, int animationNo, int startFrame, int unk1, int updateSpeed, int unk2);

	// Sets the player animation speed
	void PlayerActor_SetAnimationSpeed(PlayerActor* player, int updateSpeed);

	// Updates the player animation
	void PlayerActor_updateAnimation(PlayerActor* player);

	// Makes the player unable to move
	void PlayerActor_freeze(PlayerActor* player, BOOL isLookingAtBoss);

	// Makes the player able to move
	void PlayerActor_unfreeze(PlayerActor* player);

	// Sets the actor the player is holding.
	void PlayerActor_setHeldActor(PlayerActor* player, EnemyActor* actor);

	// Removes the actor the player is holding.
	void PlayerActor_removeHeldActor(PlayerActor* player, EnemyActor* actor);

	// Removes the item the player is holding.
	void PlayerActor_removeHeldItem(PlayerActor* player);

	// Spawns the starman particles from the player.
	void PlayerActor_SpawnStarmanParticles(PlayerActor* player);

	// Sets the player actor movement state.
	void PlayerActor_setMovementState(PlayerActor* player, int function_ptr, int thumb, int args);

	// Sets the player actor entrance state.
	void PlayerActor_setEntranceState(PlayerActor* player, int function_ptr, int thumb, int args);

	// Sets the player actor states as just respawned.
	void PlayerActor_setRespawnedState(PlayerActor* player);

	// Stops music to prepare death sequence
	void PlayerActor_stopMusicOnDeath(PlayerActor* player, int fadeFrame);

	// Gets the pointer to the local player.
	// WARNING: Causes desyncs in multiplayer if used incorrectly!
	PlayerActor* GetPtrToPlayerActor();

	// Gets the pointer to the player from it's player number.
	PlayerActor* GetPtrToPlayerActorByID(int playerNo);

	// Sets the pointer to the player for the player number.
	PlayerActor* SetPtrToPlayerActorByID(PlayerActor* player, int playerNo);

	// Gets the closest player number to an actor
	u32 GetPlayerFacingDirection(void* actor, Vec3* actorPos);

	// Gets the lives for player
	u32 GetLivesForPlayer(u32 playerNo);

	// Sets the lives for player
	void SetLivesForPlayer(u32 playerNo, u32 Lives);

	// Gets the powerup for player
	u8 GetPowerupForPlayer(u32 playerNo);

	// Sets the powerup for player
	void SetPowerupForPlayer(u32 playerNo, u8 Powerup);

	// Gets the score for player
	u32 GetScoreForPlayer(u32 playerNo);

	// Sets the score for player
	void SetScoreForPlayer(u32 playerNo, u32 Score);

	// Gets the inventory/storaged powerup for player
	u8 GetStoredPowerupForPlayer(u32 playerNo);

	// Sets the inventory/storaged powerup for player
	void SetStoredPowerupForPlayer(u32 playerNo, u8 Powerup);

	// Gets the character (Mario or Luigi) for player
	u8 GetCharacterForPlayer(u32 playerNo);

	// Sets the character (Mario or Luigi) for player
	void SetCharacterForPlayer(u32 playerNo, u8 Character);

	// Gives a coin to the a player and returns if it was successful
	BOOL GiveCoinToPlayer(u32 playerNo);

	// Gets the current coin count for player
	s32 GetCoinsForPlayer(u32 playerNo);

	// Sets the current coin count for player
	void SetCoinsForPlayer(u32 playerNo, s32 value);

	// Gets the starman time for player
	s32 GetStarmanTimeForPlayer(u32 playerNo);

	// Sets the starman time for player
	void SetStarmanTimeForPlayer(u32 playerNo, s32 value);

	// Gets the player count
	int GetPlayerCount();

	// Sets the player count
	void SetPlayerCount(u32 playerCount);

	// Returns if the specified player is dead
	int GetPlayerDeathState(u32 playerNo);

	// Sets if the specified player is dead
	void SetPlayerDeathState(u32 playerNo, int dead);

	// Gets the player count to spawn bitmask
	int GetPlayersToSpawnBitmask();

	// Sets the player count to spawn bitmask
	void SetPlayersToSpawnBitmask(u32 playersToSpawnBitmask);

	// Sets the entrance for player
	void SetEntranceIdForPlayer(u32 entranceId, u32 playerNo);

	// Gets the starting entrance for player
	u8 GetStartEntranceIDForPlayer(u32 playerNo);

	// Sets the respawning position for player
	inline void SetRespawnPositionForPlayer(int playerNo, fx32 x, fx32 y) {
		VecFx32* respawnPos = (VecFx32*)0x0208B0B8;
		respawnPos[playerNo].x = x;
		respawnPos[playerNo].y = y;
	}

#ifdef __cplusplus
}

#endif