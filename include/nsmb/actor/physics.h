#pragma once

#include "nitro/types.h"
#include "nsmb/vector.h"

typedef enum Shape
#ifdef __cplusplus
	: u8
#endif
{
	RECTANGLE,
	CIRCLE,
	TRAPEZOID_V,
	TRAPEZOID_H
} Shape;

typedef struct ActivePhysics
{
	// size: 0xB0
	u32* vtable;
	void* owner;						// 4
	u32 unk0;							// 8
	struct ActivePhysics* prevAPhysics;	// C
	struct ActivePhysics* firstAPhysics;// 10
	u32 offsetX;						// 14
	u32 offsetY;						// 18
	u32 sizeX;							// 1C
	u32 sizeY;							// 20
	u8 behavior1;						// 24
	u8 damageEnemy;						// 25
	u16 behavior2;						// 26
	u16 flags;							// 28
	u16 flagsFireball;					// 2A
	u32* callback;      				// 2C
	Vec2 vec;							// 30 
	s32 XContactPos;					// 3C
	u8	unk3[4];						// 40
	u32 unk4[8];						// 44
	s32 YContactPos;					// 64
	u32 unk5[9];						// 68
	u32 offsetX_trpez;					// 8C
	u32 offsetY_trpez;					// 90
	u32 sizeX_trpez;					// 94
	u32 sizeY_trpez;					// 98
	u32 to_info_used2;					// 9C
	u16 something;						// A0
	u16 collisionFlags;					// A2
	u8 unk7_1;							// A4
	u8 unk7_2;							// A5
	u8 someFlags;						// A6	// 0x2 is set when a collision occurs
	u8 collidePlayerNumber;				// A7
	u8 registered;						// A8
	u8 unk9;							// A9
#ifdef __cplusplus
	Shape
#else
	u8
#endif
		shape;                              // AA
	u8 unk10;							// AB
	u16 old_something;					// AC
	u16 unk12;							// AE

} ActivePhysics;

typedef void ActivePhysicsCallback(ActivePhysics*, ActivePhysics*);
typedef struct APInput
{
	u32 offsetX;        // 0
	u32 offsetY;        // 4
	u32 sizeX;            // 8
	u32 sizeY;            // C
	u8 behaviorA;        // 10
	u8 damageEnemies;    // 11
	u16 behaviorB;        // 12
	s16 flagsA;            // 14
	s16 flagsB;            // 16
	ActivePhysicsCallback* callback;        // 18
} APInput;

#ifdef __cplusplus
extern "C" {
#endif

#define ap_vtable ((u32*)0x20C6F10)
	void activePhysics_ctor(void* activePhysics);
	void activePhysics_dtor(void* activePhysics);
	void activePhysics_dtorFree(void* activePhysics);

	void activePhysics_init(void* activePhysics, void* actor, void* physics, u32 unk);
	void activePhysics_register(void* activePhysics);
	void activePhysics_unregister(void* activePhysics);

	void activePhysics_resetPointers(void* activePhysics);

#ifdef __cplusplus
}
#endif