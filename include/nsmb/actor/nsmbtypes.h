#pragma once

// OH MY FUCKING GOD, SOMEONE PLEASE GET RID OF NSMBTYPES.H
// LIKE REALLY, THIS FILE IS A CRAPPY MESS!!!

#include "nitro/types.h"
#include "nsmb/vector.h"

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				     COLORS   					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

#define RED		(0xFF0000)
#define GREEN	(0x00FF00)
#define BLUE	(0x0000FF)

#define YELLOW	(0xFFFF00)
#define CYAN	(0x00FFFF)
#define MAGENTA	(0xFF00FF)

#define BLACK	(0x000000)
#define GREY	(0x7F7F7F)
#define WHITE	(0xFFFFFF)

#define ORANGE	(0xFF7F00)
#define PINK	(0xFF7FFF)
#define AQUA	(0x7FFFFF)

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				     MUSIC   					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef enum
{
	TRK_1 = 0x0001,
	TRK_2 = 0x0002,
	TRK_3 = 0x0004,
	TRK_4 = 0x0008,
	TRK_5 = 0x0010,
	TRK_6 = 0x0020,
	TRK_7 = 0x0040,
	TRK_8 = 0x0080,
	TRK_9 = 0x0100,
	TRK_10 = 0x0200,
	TRK_11 = 0x0400,
	TRK_12 = 0x0800,
	TRK_13 = 0x1000,
	TRK_14 = 0x2000,
	TRK_15 = 0x4000,
	TRK_16 = 0x8000
}	TRACKS;

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				 TILE BEHAVIORS					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

#define B_ENTRANCE		0x01000000
#define B_WATER			0x02000000
#define B_CLIMBABLE		0x04000000
#define B_PARTIAL_S		0x08000000

#define B_HARMFUL		0x10000000
#define B_INVISIBLE		0x20000000
#define B_SOLIDONBOT	0x40000000
#define B_SOLIDONTOP	0x80000000

#define B_SOLID			0x00010000
#define B_COIN			0x00020000
#define B_QUESTION		0x00040000
#define B_EXPLODABLE	0x00080000

#define B_BRICK			0x00100000
#define B_SLOPE			0x00200000
#define B_F_SLOPE		0x00400000
#define B_UNK2			0x00800000

#define B_UNK3			0x00000100
#define B_DONUT			0x00000200
#define B_UNK4			0x00000400
#define B_UNK5			0x00000800

#define B_ICE			0x00001000
#define B_SNOW			0x00002000
#define B_QUICKSAND		0x00003000
#define B_CONVEYOR_R	0x00004000
#define B_CONVEYOR_L	0x00005000
#define B_ROPE			0x00006000
#define B_GHOSTSTAIRS	0x00007000
#define B_UNK6			0x00008000
#define B_LEDGE			0x00009000
#define B_POLE			0x0000A000
#define B_NOSLIDING		0x0000B000
#define B_UNK7			0x0000C000
#define B_SLOWSPLAYER	0x0000D000
#define B_SANDY			0x0000E000
#define B_UNK8			0x0000F000




///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				   OTHER STUFF					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct {
	u32* onCreate;
	u32* beforeCreate;
	u32* afterCreate;
}	tVtable;

typedef struct {
	tVtable create;
	tVtable delet;
	tVtable execute;
	tVtable draw;
	u32* willBeDeleted;
	u32* moreHeapShit;
	u32* createHeap;
	u32* heapCreated;
	u32* dtor;
	u32* dtorFree;
	u32* getSomething;
	u32* incrementSomething;
	u32* execState0;
	u32* isInvisible;
	u32* execState1;
	u32* execState2;
	u32* execState3;
	u32* execState4;
	u32* execState5;
	u32 (*execState6)(...);
	u32 (*execState7)(...);
	u32* execState8;
	u32* execState9;
	u32* virt31;
	u32* virt32;
	u32* virt33;
	u32* virt34;
	u32* virt35;
	u32* virt36;
	u32(*virt37)(...);
	u32* virt38;
	u32* virt39;
	u32* execAllStates;
	u32* virt41;
	u32* virt42;
	u32* virt43;
	u32* virt44;
	u32* virt45;
	u32* virt46;
	u32* virt47;
	u32* virt48;
	u32* virt49;
	u32* virt50;
	u32* virt51;
	u32* virt52;
	u32* virt53;
	u32* virt54;
	u32* virt55;
	u32* virt56;
	u32* virt57;
	u32* virt58;
	u32* virt59;
	u32* virt60;
	u32* virt61;
	u32* virt62;
	u32* virt63;
	u32* virt64;
	u32* virt65;
	u32* virt66;
}	vTable;

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				COLLISION STUFF					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct
{
	s32 x, y, width, height;
} 	Rect2D;

typedef enum
#ifdef __cplusplus
	: u8
#endif
{
	F_Down,
	F_F_Up,
	Left,
	F_Right,
}	Facing;

typedef enum
#ifdef __cplusplus
	: u8
#endif
{
	D_Right,
	D_Left
}	Direction;

typedef enum
#ifdef __cplusplus
	: u8
#endif
{
	SMALL,
	SUPER,
	FIRE,
	MINI,
	MEGA,
	SHELL
}	Powerup;

typedef struct
{
	u8 triggerID;
	u8 targetID;
}	sDataEventIDs;


typedef enum DefeatedBitfield
{
	BLOCK_HIT = 128,
	NONE = 0,
	DISABLED = 1,
	DOFLY_HIT = 65536,
	ENEMY_HIT = 64,
	FIREBALL_HIT = 32,
	GROUNDPOUND_HIT = 16384,
	MEGA_HIT = 1024,
	SHELLPLAYER2_HIT = 2048,
	SHELLPLAYER_HIT = 32768,
	SLIDING_HIT = 4096,
	STARMAN_HIT = 512,
	STOMP_HIT = 8192,
	UNK = 7,
	UNK2 = 256
} DefeatedBitfield;

typedef struct ActorInfo
{
	u8 setToZero_1; /* apActor_ctor -- size? */
#ifdef __cplusplus
	Direction
#else
	u8
#endif
	direction;
	u8 ViewID;
	u8 someThing; /* apActor_ctor */
	BOOL beforeExecuteCompleted;
	u8 notAVector;
	u8 field_0x9;
	u16 stompedMaybe; /* spawnSprite (1 = held) */
	u16 spriteSettings; /* spawnSprite */
	u16 argh;
	u8 hitCountdown; /* hit related */
	u8 field_0x11;
	u8 field_0x12;
	u8 field_0x13;
	u32 dummyZ;
	u32 unk5[6];
	Vec3 unkV1; /* not constructed */
	u32 unk11[4];
	Vec3 unkVector;
	Vec3 movementStrength; /* oldGravity */
	u32 unk16[2];
	u32 eventMSINT; 		/* spawnSprite */
	u32 eventLSINT; 		/* spawnSprite */
	sDataEventIDs eventIDs; /* spawnSprite */
	u16 padMaybe;
	u32 executeThisState;
	u32 unk15; 			/* 20583cc */
	u32 playerNum; 		/* spawnSprite */
	u32 defeatSFXid; 	/* 1ffaa50 */
	u32 unk18;
	u32 bitfield2; 		/* 20582ec */
	u32 used;
	Vec3 wiggleScale;
	Vec2 ExistDist;
	Vec2 DrawDist;
	Vec2 DeleteDist;
	Vec2 collisionSelfPoss; /* hmmm */
	Vec2 collisionActorPos; /* HMMMMMM */
	u32 wiggleOscillate;
	u32 unk21;
	u32 unk22;
	DefeatedBitfield defeatedBitfield;
	s32 velX_sum;
	u16 wiggleCountdown;
	u16 divideVelBy2;
	u16 sizeMod; 		/* size? */
	u16 unk25_c;
	u16 unk25_e; 		/* mayro */
	u16 used1; 			/* weege */
	u16 unk26;
	u16 field_0x10e;
	u16* ptrToShort; 	/* spawnSprite */
	u8 defeatRelated;
	u8 field_0x115;
	u8 vryImprtntDECREMENT;
	u8 unk29;
	u32 unk30;
	u8* ptrToByte; 		/* spawnSprite */
	u8 marioDirection;
	u8 unk33;
	u8 scoreEnhancement;
	u8 unk34;
	u8 spawnedByCreateActorMaybe; /* spawnSprite */
	u8 field_0x125;
	u8 directionForBlockCallback;
	u8 virt62_related;
	u8 permanentDelete; 			/* 1 = permanent, incredible, isn't it? */
	u8 field_0x129;
	u8 usedInLiquid;
	u8 field_0x12b;
	u8 disableDefeatRoll;
	u8 invisible; /* maybe grabbable */
	u8 notMovableMaybe;
	u8 unk39;
	u8 setToOneIfODD;
	u8 unk40;
	u8 defeatedDirection;
	u8 freezeRelated;
	u8 behindFence; /* old notAModel, old posZpriority */
	u8 unk42;
	u8 unk43;
#ifdef __cplusplus
	Facing
#else
	u8
#endif
	facing; /* D-U-L-R */
} ActorInfo;

typedef struct
{
	u32 x;
	u32 y;
	u32 z;
}	XYZ;

struct PlayerActorInfo
{
	// size: 0x138
	u8 setToZero_1; /* apActor_ctor */
#ifdef __cplusplus
	Direction
#else
	u8
#endif // __cplusplus
		direction; 	// 1	1 = R, 0 = L
	u8 ViewID;
	u8 setToZero_2; /* apActor_ctor */
	u32 empty;
	u16 a;
	u16 field_0xa; /* spawnSprite */
	u16 bitfield; /* spawnSprite */
	u16 field_0xe;
	u32* c;
	u32* d;
	u32* e;
	u32* f;
	u32* g;
	u32* h;
	u32* i;
	u32* j;
	u16 A;
	u16 B;
	u16 C;
	u16 D;
	u16 E;
	u16 F;
	u16 G;
	u16 H;
	u16 I;
	u16 J;
	u16 K;
	u16 L;
	u32* unk3;
	u32* unk4;
	u32* unk5;
	u32* unk6;
	u32* unk7;
	u32* unk8;
	u32* unk9;
	XYZ movementStrength;	// has got something to do with the head position / visibility when dying
	u16 a1;
	u16 a2;
	u16 a3;
	u16 a4;
	u32 triggerIdBitmask; /* spawnSprite */ // 0x........FFFFFFFF
	u32 eventBitmask; /* spawnSprite */ // 0xFFFFFFFF........
	sDataEventIDs eventIDs; /* spawnSprite */
	u16 padMaybe;
	u32 executeThisState;
	u32 unk15; /* 20583cc */
	u32 playerNum; /* spawnSprite */
	u32* unk17; /* 1ffaa50 */
	u32 unk18;
	u32 bitfield2; /* 20582ec */
	u32 used;
	Vec3 oldScale;
	Vec2 ExistDist;
	Vec2 DrawDist;
	Vec2 DeleteDist;
	Vec2 collisionSelfVec; /* hmmm */
	Vec2 collisionActorVec; /* HMMMMMM */
	u32 oscillate;
	u32 unk21;
	u32 unk22;
	u32 rangedValue;
	s32 negative;
	u16 countdown;
	u16 divideVelBy2;
	u8 unk25_a;
	u8 unk25_b;
	u8 unk25_c;
	u8 unk25_d;
	u16 unk25_e;
	u16 used1;
	u32* unk26;
	u16* unk27; /* spawnSprite */
	u16 unk28;
	u8 DECREMENT;
	u8 unk29;
	u32 unk30;
	u8* unk31; /* spawnSprite */
	u8 marioDirection;
	u8 unk33;
	u8 scoreSomething;
	u8 unk34;
	u8 zero; /* spawnSprite */
	u8 field_0x125;
	u8 field_0x126;
	u8 field_0x127;
	u32 unk36;
	u8 unk37;
	u8 isInvisible;
	u8 movableMaybe;
	u8 unk39;
	u8 setToOneIfODD;
	u8 unk40;
	u8 someDirection;
	u8 unk41;
	u8 posZpriority;
	u8 unk42;
	u8 unk43;
#ifdef __cplusplus
	Facing
#else
	u8
#endif // __cplusplus
		facing;          // 137
};

typedef struct ActorInfo ActorInfo;
typedef struct PlayerActorInfo PlayerActorInfo;


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///				TEXTURE STUFF					///
///////////////////////////////////////////////////
///////////////////////////////////////////////////

typedef struct
{
	u32 texparam;
	u32 palbase;
} 	TexInfo;

typedef struct
{
	u32* vtable;
	u8* file;
	TexInfo info;
} 	CompTex;

typedef struct {
	Vec3 position;
	S16Vec3 rotation;
} 	PositionInfo;

typedef struct {
	u32* vtable;
	u16 field_0x4;
	u16 field_0x6;
	u16 field_0x8;
	s16 field_0xa;
	s16 field_0xc;
	s16 field_0xe;
}	field_0x258;

typedef struct {
	u32* mA_functions;
	Vec3 vector;
}	field_0x444;

typedef struct {
	u32* owner;
	u32 field_0x4;
	u32 unk;
	u32 field_0xc;
	u32 field_0x10;
	u32 field_0x14;
	u8 field_0x18;
	u8 wat;
	u8 field_0x1a;
	u8 field_0x1b;
}	field_0x428;

typedef struct {
	u32* vtable;
	Vec3 position;
	s32 offset;
	u32 startX;
	u16 timerRot;
	u16 idk;
	u8 isSpinning;
	u8 enable;
	u8 direction;
	u8 field_0x23;
}	spinState;

typedef struct {
	struct PlayerActor* owner;
	u32 field_0x4;
	u32 field_0x8;
	u32 field_0xc;
	u32 field_0x10;
	u32 field_0x14;
	u8 field_0x18;
	u8 field_0x19;
	u8 currentView;
	u8 field_0x1b;
	u32 field_0x1c;
}	field_0x458;