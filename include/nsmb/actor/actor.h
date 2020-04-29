#pragma once

#include "nitro/types.h"
#include "nsmb/actor/nsmbtypes.h"
#include "nsmb/actor/collider.h"
#include "nsmb/actor/physics.h"
#include "nsmb/vector.h"

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///					LINKED LIST					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct TreeNode
{
	// size: 0x14
	u32* parent;		// 0
	u32* firstChild;	// 4
	u32* prev;			// 8
	u32* next;			// C
	u32* obj;			// 10
} TreeNode;

typedef struct OrderedLinkedListEntry
{
	// size: 0x10
	u32* parent;		// 0
	u32* firstChild;	// 4
	u32* obj;			// 8
	u16 order;			// C
	u16 order2;			// E
} OrderedLinkedListEntry;

typedef struct LinkedListEntry
{
	// size: 0xC
	u32* prev;			// 0
	u32* next;			// 4
	u32* obj;			// 8
} LinkedListEntry;

typedef struct ProcessLink
{
	// size: 0x40
	TreeNode linkConnect;				// 0
	OrderedLinkedListEntry linkExecute;	// 14
	OrderedLinkedListEntry linkDraw;	// 24
	LinkedListEntry linkIdLookup;		// 34
} ProcessLink;

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///					ACTOR STUFF					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct Base
{
	// size: 0x5C
	vTable* vtable;		// 0
	u32 id;				// 4
	u32 spriteData;		// 8
	u16 classID;		// C
	u8 created;			// E
	u8 deleted;			// F
	u8 unk1;			// 10
	u8 addedToList;		// 11
	u8 baseType;		// 12
	u8 unk2;			// 13
	ProcessLink link;	// 14
	u32 unk3;			// 54
	u32* heap;			// 58
} Base;

typedef enum ActorType
#ifdef __cplusplus
	: u8
#endif
{
	T_UNKNOWN,
	T_PLAYER,
	T_SPRITE
} ActorType;

typedef struct Actor
{
	Base base;
	Vec3 position;		// 5C -- inited from createSprite_pos
	Vec3 lastPos;	// 6C -- inited from createSprite_pos
	Vec3 speed;			// 7C -- inited to 0,0,0
	Vec3 maxSpeed;		// 8C -- seems to be used as a velocity vector?
	S16Vec3 rotation;	// 9C -- inited from createSprite_rot
	S16Vec3 lastRot;		// A8 -- inited from createSprite_rot

	u32 collisionBitfield;
	u32 unk[5];

	Vec3 velocity;		// CC -- velocity
	Vec3 accel;			// DC
	Vec3 scale;			// EC -- inited from createSprite_scale
	Vec3 unkv9;			// FC -- inited to 0,0,0
	Vec3 unkv10;		// 10C -- inited to 0x8000,0x8000,0x8000

#ifdef __cplusplus
	ActorType actorType;    // 11C -- inited to 0
#else
	u8 actorType;    // 11C -- inited to 0
#endif
	u8 unk5;                // 11D -- inited to 1
	u8 playerNumber;        // 11E -- inited from createSprite_player
	u8 actorBitfield;        // 11F -- inited to 0x80

} Actor;

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				BASIC ACTOR STRUCTURE			///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct EnemyActor
{
	// 0	-- Actor
	Actor actor;

	// 120	-- ActivePhysics
	ActivePhysics activephysics;

	// 1D0	-- Collider
	Collider collider;

	// 2BC	-- ActorInfo
	ActorInfo info;

} EnemyActor;

#ifdef __cplusplus
extern "C"
{
#endif

	// Spawns an actor in stage
	void CreateActor(u32 ClassID, u32 SpriteData, Vec3* Position, int, int, int);

	// Gets a spawned actor in stage
	void* GetSpawnedActor(u32 ClassID, int unk1, int unk2);

	void Base_deleteIt(void* actor);

	// Useful for gravity and tile collisions
	void enemyActor_velocityToMovement(void* actor);
	void enemyActor_accelToVelocity_Y(void* actor);
	void enemyActor_tileCollisionUpdate(void* actor);
	void enemyActor_anotherTileBehavior(void* actor);
	void enemyActor_shellReboundRelated(void* actor);
	BOOL enemyActor_deleteIfOutOfRange(void* actor, u8 unk);
	void enemyActor_dropCoin(void* actor);

	// EnemyActor Virts
	void enemyActor_virt31(void* actor, int, int, int, int, int);
	void enemyActor_virt32(void* actor, int, int, int, int, int);
	void enemyActor_virt33(void* actor, int, int, int, int, int);
	void enemyActor_virt34(void* actor, int, int, int, int, int);
	void enemyActor_virt35(void* actor, int, int, int, int, int);
	void enemyActor_virt36(void* actor, int, int, int, int, int);
	void enemyActor_virt37(void* actor, int, int, int, int, int);
	void enemyActor_virt38(void* actor, int, int, int, int, int);
	void enemyActor_virt39(void* actor, int, int, int, int, int);
	void enemyActor_virt41(void* actor, int, int, int, int, int);
	void enemyActor_virt42(void* actor, int, int, int, int, int);
	void enemyActor_virt43(void* actor, int, int, int, int, int);
	void enemyActor_virt44(void* actor, int, int, int, int, int);
	void enemyActor_virt45(void* actor, int, int, int, int, int);
	void enemyActor_virt46(void* actor, int, int, int, int, int);
	void enemyActor_virt47(void* actor, int, int, int, int, int);
	void enemyActor_virt48(void* actor, int, int, int, int, int);
	void enemyActor_virt49(void* actor, int, int, int, int, int);
	void enemyActor_virt50(void* actor, int, int, int, int, int);
	void enemyActor_virt51(void* actor, int, int, int, int, int);
	void enemyActor_virt52(void* actor, int, int, int, int, int);
	void enemyActor_virt53(void* actor, int, int, int, int, int);
	void enemyActor_virt54(void* actor, int, int, int, int, int);
	void enemyActor_virt55(void* actor, int, int, int, int, int);
	void enemyActor_virt56(void* actor, int, int, int, int, int);
	void enemyActor_virt57(void* actor, int, int, int, int, int);
	void enemyActor_virt58(void* actor, int, int, int, int, int);
	void enemyActor_virt59(void* actor, int, int, int, int, int);
	void enemyActor_virt60(void* actor, int, int, int, int, int);
	void enemyActor_virt61(void* actor, int, int, int, int, int);
	void enemyActor_virt62(void* actor, int, int, int, int, int);
	void enemyActor_virt63(void* actor, int, int, int, int, int);
	void enemyActor_virt64(void* actor, int, int, int, int, int);
	void enemyActor_virt65(void* actor, int, int, int, int, int);
	void enemyActor_virt66(void* actor, int, int, int, int, int);
	void enemyActor_execute(void* actor);
	void enemyActor_executeState2(void* actor);
	void enemyActor_executeState3(void* actor);
	void enemyActor_executeState4(void* actor);
	void enemyActor_executeState5(void* actor);
	void enemyActor_executeState6(void* actor);
	void enemyActor_executeState7(void* actor);
	void enemyActor_executeState8(void* actor);
	void enemyActor_executeState9(void* actor);

#ifdef __cplusplus
}
#endif