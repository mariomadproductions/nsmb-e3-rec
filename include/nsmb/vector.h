#pragma once

#ifdef __cplusplus

class Vec2;
class Vec3;
class S16Vec3;

// macros for casting to other vectors
#define cV3(v)		reinterpret_cast<Vec3*>(&v)
#define cV2(v)		reinterpret_cast<Vec2*>(&v)
#define cS16V3(v)	reinterpret_cast<S16Vec3*>(&v)

// macros for casting to VecFx vectors
#define cVFx32(x)	reinterpret_cast<VecFx32*>(&x)
#define cVFx16(x)	reinterpret_cast<VecFx16*>(&x)

// macros for casting to non-const vectors
#define cCV3(v)		const_cast<Vec3*>(&v)
#define cCV2(v)		const_cast<Vec2*>(&v)
#define cCS16V3(v)	const_cast<S16Vec3*>(&v)

#include "nsmb/vector/s16vec3.hpp"
#include "nsmb/vector/vec2.hpp"
#include "nsmb/vector/vec3.hpp"

#else

typedef struct
{
	void* vtable;
	fx32 x, y, z;
} Vec3;

typedef struct
{
	void* vtable;
	fx32 x, y;
} Vec2;

typedef struct
{
	void* vtable;
	fx16 x, y, z, _;
} S16Vec3;

#endif