#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"

#ifdef __cplusplus
extern "C" {
#endif
	u32 Sqrt64(u32 l, u32 h);
	u32 modulo(u32 num, u32 den);
#ifdef __cplusplus
}
#endif

// rounding numbers
#define FX_Ceil(n)		FX_Floor((fx32)(n)+(u32)0xfff)
#define FX_Round(n)		((((fx32)(n)&(u32)0x800)!=0)?FX_Ceil(n):FX_Floor(n))

#define HI64(n)		(fx32)((u64)(n)>>32)
#define LO64(n)		(fx32)((u64)(n))

// macro for 'quick' 64-bit square root
#define FX_Sqrt64(n)	Sqrt64(LO64(n), HI64(n))

// utilities
#define sign(n) ((n<0)?-1:1)