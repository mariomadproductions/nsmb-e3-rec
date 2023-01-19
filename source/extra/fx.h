#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"

#define FX_Ceil(n) FX_Floor((fx32)(n)+(u32)0xfff)
#define FX_Round(n) ((((fx32)(n)&(u32)0x800)!=0)?FX_Ceil(n):FX_Floor(n))
