#pragma once

#include "nitro/gx/g2_oam.h"
#include "nitro/types.h"
#include "nsmb/vector.h"

// Sprite control defines

// Attribute 0 consists of 8 bits of Y plus the following flags:
#define ATTR0_NORMAL			(0<<8)
#define ATTR0_ROTSCALE			(1<<8)
#define ATTR0_DISABLED			(2<<8)
#define ATTR0_ROTSCALE_DOUBLE	(3<<8)

#define ATTR0_TYPE_NORMAL		(0<<10)
#define ATTR0_TYPE_BLENDED		(1<<10)
#define ATTR0_TYPE_WINDOWED		(2<<10)
#define ATTR0_BMP				(3<<10)

#define ATTR0_MOSAIC			(1<<12)

#define ATTR0_COLOR_16		(0<<13) //16 color in tile mode...16 bit in bitmap mode
#define ATTR0_COLOR_256		(1<<13)

#define ATTR0_SQUARE		(0<<14)
#define ATTR0_WIDE			(1<<14)
#define ATTR0_TALL			(2<<14)

#define OBJ_Y(m)			((m)&0x00ff)

// Atribute 1 consists of 9 bits of X plus the following flags:
#define ATTR1_ROTDATA(n)      ((n)<<9)  // note: overlaps with flip flags
#define ATTR1_FLIP_X          (1<<12)
#define ATTR1_FLIP_Y          (1<<13)
#define ATTR1_SIZE_8          (0<<14)
#define ATTR1_SIZE_16         (1<<14)
#define ATTR1_SIZE_32         (2<<14)
#define ATTR1_SIZE_64         (3<<14)

#define OBJ_X(m)			((m)&0x01ff)

// Atribute 2 consists of the following:
#define ATTR2_PRIORITY(n)     ((n)<<10)
#define ATTR2_PALETTE(n)      ((n)<<12)
#define ATTR2_ALPHA(n)		  ((n)<<12)

#define ATTR2_DATA_END ((u32)(0xFFFF<<16))

typedef struct OAMEntry {
	u16 attr0;
	u16 attr1;
	u32 attr2;
} OAMEntry;

typedef struct
{
	u32 fileID;
	GXOamAttr** entriesTable;
	u32 entryCount;
	u32 ncgOffsetShifted;
}	NCGFileEntry;

typedef struct
{
	NCGFileEntry* fileInfo;
	u32 loaded;
}	NCGFileList;

typedef struct
{
	GXOamAttr* entries;
	u32 a0;
	u32 a1;
}	OAMFrameTableEntry;

typedef struct
{
	OAMFrameTableEntry* frameTable;
	u32 entries;
}	OAMAnimationsTableEntry;

typedef struct
{
	OAMFrameTableEntry* frameTable;
	u32 frameTableID;
	u32 currentFrameSize;
	u32 size;
	u16 currentFrame;
	u16 frames;
	u8 bitfield;	// 0x1 = always, 0x4 = size was adjusted to be positive
	u8 pad[3];
}	OAMSprite;

#ifdef __cplusplus
extern "C" {
#endif

	// Draws OAM relative to the level
	void OAM_DrawSprite(OAMEntry* entries, u32 posX, u32 posY, u8 corner, u8 palette, u8, Vec2* scale, u16 rotation, u16*, u32);

	// Draws OAM relative to a level sprite
	void OAM_DrawFromSprite(OAMSprite* sprite, u32 posX, u32 posY, u8 corner, u8 palette, u8, Vec2* scale, u16 rotation, u16*, u32);

	// Draws OAM relative to the top screen HUD
	void OAM_DrawHUD(OAMEntry* entries, u32 x, u32 y, u8 corner, u8 palette, u8, Vec2* scale, s16 rotation, u8, u8);

	// Draws OAM relative to the bottom screen HUD
	void OAM_DrawHUDSub(OAMEntry* entries, u32 x, u32 y, u8 corner, u8 palette, u8, Vec2* scale, s16 rotation, u8, u8);

	// Draws OAM relative to the top screen HUD offsetted by the position defined in the loaded BNCL file
	void OAM_DrawHUDFromLoadedBNCL(int index, OAMEntry* entries, u8 flip, u8 palette, int unk1, Vec2* scale, int unk2, int unk3, int unk4, int x_relativeshift, int y_relativeshift);

	// Draws OAM relative to the bottom screen HUD offsetted by the position defined in the loaded BNCL file
	void OAM_DrawHUDSubFromLoadedBNCL(int index, OAMEntry* entries, u8 flip, u8 palette, int unk1, Vec2* scale, int unk2, int unk3, int unk4, int x_relativeshift, int y_relativeshift);

	// Updates OAM digits
	void OAM_UpdateDigits(OAMEntry* entries, u32* entryTable, s32 value, s32 digitNo, u8 unk5);

	//////////////////////
	// Graphics loading //
	//////////////////////

	void loadNCGFile_intoVRam(u32 ListID);
	void loadNCGFile_intoVRam_OAM(NCGFileEntry* file);

	void loadNCGFile(NCGFileEntry* file);

#ifdef __cplusplus
}
#endif