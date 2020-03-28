#pragma once

#include "nitro/types.h"
#include "nsmb/vector.h"

typedef struct SCInput
{
	s32 left;
	s32 top;
	s32 right;
	s32 bottom;
	u32* callbackTop;
	u32* callbackBottom;
	u32* callbackSide;
	u16 unk1;
	u16 unk2;
	u16 unk3;
	u16 padding;
} SCInput;

typedef enum SCBehavior
{
	SC_COIN = 0x20000,
	SC_PASSTHROUGH = 0x20002,
	SC_UNK = 0xC0000,
	SC_SOLID = 0x100000,
} SCBehavior;

typedef struct SolidCollision
{
	// size: 0x6C
	void* owner;
	struct SolidCollision* prevSCollisions;
	struct SolidCollision* firstSCollisions;
	u32* unk3;
	u32 unk4;
	u32 unk5;
	u32* callbackTop;
	u32* callbackBot;
	u32* callbackSide;
	Vec2 DistToCenterScale2;
	Vec2 DistToEdge2;
	Vec2 DistToCenterScale;
	Vec2 DistToEdge;
	Vec2 DistToCenter;
	u32 behavior;
	u32 zero;
	bool registered;
	u8 unk6;
	u8 type;
	u8 subScales;

} SolidCollision;

#ifdef __cplusplus
extern "C" {
#endif

	//Solid collision (hitbox behaves like a tile (solid, coin, brick, etc))
	void solidCollisions_ctor(void* solidCollisions);

	void solidCollisions_init(void* solidCollisions, void* actor, void* physics, u32 behavior, u32 unk2, Vec3* scale);
	void solidCollisions_initNoStruct(void* solidCollisions, void* actor, u32 centerX, u32 centerY, u32 edgeX, u32 edgeY, u32* CallbackTop, u32* CallbackBot, u32* CallbackSide, u32 behavior, u8 unk6, Vec3* scale);
	void solidCollisions_register(void* solidCollisions);
	void solidCollisions_unregister(void* solidCollisions);

	void solidCollisions_setPos(void* solidCollisions);
	void solidCollisions_doSomething(void* solidCollisions);
	void solidCollisions_initStruct(void* solidCollisions);
	void solidCollisions_initComplex(void* solidCollisions, u32 centerX, u32 centerY, u32 edgeX, u32 edgeY, Vec3* scale);
	void solidCollisions_register(void* solidCollisions);
	void solidCollisions_resetPointers(void* solidCollisions);

#ifdef __cplusplus
}
#endif