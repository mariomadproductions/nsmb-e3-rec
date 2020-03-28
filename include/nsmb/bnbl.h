#pragma once

//This file was made by TheGameratorT :D

#include "nitro/types.h"
#include "nsmb/ostream.hpp"

typedef struct
{
	u16 xpos;
	u16 ypos;
	u8 width;
	u8 height;
} BNBLFileRectangle;

typedef struct
{
	char magic[4];
	u16 padding;
	u16 rectCount;
	BNBLFileRectangle rects[];
} BNBLFile;

extern BNBLFile* BNBLFilePtr;

#ifdef __cplusplus

class BNBL
{
private:
	BNBLFile* bnbl;

public:
	inline BNBL();
	inline BNBL(BNBLFile* bnbl);

	static int GetYPosFromAnchoredPos(u16 pos_field, int width);
	static int GetXPosFromAnchoredPos(u16 pos_field, int width);
	inline int GetRectangleAtPosition(int x, int y);
	inline int GetRectangleCount();
};

BNBL::BNBL() {
	this->bnbl = BNBLFilePtr;
}
BNBL::BNBL(BNBLFile* bnbl) {
	this->bnbl = bnbl;
}
int BNBL::GetRectangleAtPosition(int x, int y) {
	extern int BNBL_GetRectangleAtPosition(BNBLFile* bnbl, int x, int y);
	return BNBL_GetRectangleAtPosition(this->bnbl, x, y);
}
int BNBL::GetRectangleCount() {
	extern int BNBL_GetRectangleCount(BNBLFile* bnbl);
	return BNBL_GetRectangleCount(this->bnbl);
}

#else

int BNBL_GetYPosFromAnchoredPos(u16 pos_field, int width);
int BNBL_GetXPosFromAnchoredPos(u16 pos_field, int width);
int BNBL_GetRectangleAtPosition(BNBLFile* bnbl, int x, int y);
int BNBL_GetRectangleCount(BNBLFile* bnbl);

#endif
