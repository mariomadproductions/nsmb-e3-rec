#pragma once

#include "nitro/types.h"
#include "nsmb/actor/nsmbtypes.h"
#include "nsmb/vector.h"

typedef struct collider_H
{
	u32 flags; 			  // 0. 0 = point, 1 = line
	u32 XPos;			  // 4
	u32 XPos2;			  // 8
	u32 YPos;		  	  // C

} collider_H;

typedef struct collider_V
{
	u32 flags; 			  // 0. 0 = point, 1 = line
	u32 YPos1;	  		  // 4. Positive goes up
	u32 YPos2;			  // 8. Positive goes up
	u32 DistFromCenter;	  // C

} collider_V;

typedef struct AnotherClass
{
	// size : 0x34
	u32* vtable;
	void* parent;
	Vec3* parentPos;
	u32 unk1;
	u32* ptr;
	u32* ptr_ReplacePrev;
	struct Collider* colliderPtr;
	Vec2 unkV1;
	u32 unk2;
	u32 unk3;
	u8 bytes[4];
} AnotherClass;

typedef struct Collider
{
	// size : 0xD8
	u32* vtable;
	void* owner;				// 4
	collider_H* botStruct;         // 8
	collider_H* topStruct;            // C
	collider_V* sideStruct;           // 10
	u32 UNK;                    // 14
	Vec3* parent_pos_ptr;
	Vec3* parent_velocity_ptr;
	u8* playerNumber;
	struct AnotherClass* anotherClassPTR;
	u32 unk1_6;
	u32 unk1_7;
	u32 xDeltaMaybe;
	u32 yDeltaMaybe;
	u32 unk1_10;
	u32 unk1_11;
	u32 unk1_12;
	u32 unk1_13;
	u32 unk1_14;
	u32 unk1_15;
	u32 unk1_16;
	Vec3 gravityParent;
	Vec2 parentPOS;
	Vec2 unkV3;
	u8 collisionBitfield; // actually an u32
	u8 isOnGround; //0x0 no ground 0x1: std ground 0x2: jump-through ground 0x10 sprite ground
	u8 unk24E;
	u8 unk24F;
	u32 unk2_2;
	u32 botBehaviors;
	u32 unk2_4;
	u16 someOtherBits;
	u8 player;
	u8 unk2_4_1;
	u8 unk2_5;
	u8 unk2_5_1;
	u8 unk2_6;
	u8 unk2_6_1;
	u32 unk2_7;
	u16 setToZero;
	u8 newSmth;
	u8 oldSmth;
	u32 unk2_9;
	u32 unk2_10;
	u16 unk2_11;
	u16 unk2_12;
	u8 VelX;
	u8 unk2_13;
	u8 solidTileBehavior;
	u8 unk2_15;
	u8 moreBits;
	u8 unk2_17;
	u8 unk2_18;
	u8 unk2_19;
	u8 someBits;
	u8 someDirection;
	u8 unk2_22;
	u8 unk2_23;
	u8 unk2_24;
	u8 unk2_25;
	u8 unk2_26;
	u8 unk2_27;
	struct AnotherClass anotherClass;
} Collider;

#ifdef __cplusplus
extern "C" {
#endif

	//Collider (checks tile collision)
#define cl_vtable ((u32*)0x20C7008)
	void collider_ctor(void* collider);
	void collider_dtor(void* collider);
	void collider_dtorFree(void* collider);

	void collider_resetStructs(void* collider);
	void collider_resetValues(void* collider);

	void collider_init(void* collider, void* actor, void* botStruct, void* topStruct, void* sideStruct, u32 unk);
	void collider_initNoActor(void* collider, Vec3* pos, Vec3* vel, u8* player, void* botStruct, void* topStruct, void* sideStruct, u32 unk);

	u32 collider_getSomething(void* collider);
	u32 collider_getSomethingSigned(void* collider);
	void collider_runSomething(void* collider);
	void collider_topSensorGetBehavior(void* collider);
	void collider_topSensorUpdate(void* collider, void* collisionBitfield);

	//Collider class (unknown)
#define clcl_vtable ((u32*)0x203C628)
	void colliderClass_ctor(void* colliderClass);
	void colliderClass_dtor(void* colliderClass);
	void colliderClass_dtorFree(void* colliderClass);

	void colliderClass_init(void* colliderClass, void* actor, u32 unk);
	void* colliderClass_pointerExists(void* colliderClass);

#ifdef __cplusplus
}
#endif