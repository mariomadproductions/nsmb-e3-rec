#pragma once

//This file was made by TheGameratorT :D

//BNCL needs OAM.h to be included to be drawn
//This file only contains the BNCL structure and game pointers.

#include "nitro/types.h"

typedef struct
{
	u16 xpos;
	u16 ypos;
	u32 id;
} BNCLFileObj;

typedef struct
{
	char magic[4];
	u16 padding;
	u16 objCount;
	BNCLFileObj objs[];
} BNCLFile;

extern BNCLFile* BNCLFilePtr;
extern BNCLFile* BNCLFilePtrSub;