#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"
#include "nsmb/misc.h"
#include "nsmb/fxmath.h"

#define S16Vec3_vtable ((void*)0x20391F8)

class S16Vec3
{
public:
	void* vtable;
	union
	{
		fx16 a[3];
		struct
		{
			fx16 x, y, z;
		};
	};

	S16Vec3() : vtable(S16Vec3_vtable), x(0), y(0), z(0) {}
	S16Vec3(fx16 n) : vtable(S16Vec3_vtable), x(n), y(n), z(n) {}
	S16Vec3(fx16 x_, fx16 y_, fx16 z_) : vtable(S16Vec3_vtable), x(x_), y(y_), z(z_) {}
	S16Vec3(const VecFx16& v) : vtable(S16Vec3_vtable), x(v.x), y(v.y), z(v.z) {}

	VecFx16* ToVecFx16() { return cVFx16(x); }
	static VecFx16* ToVecFx16(S16Vec3& v) { return cVFx16(v.x); }

	// S16V3 <op> S16V3
	inline S16Vec3 operator + (const S16Vec3& v) { S16Vec3 out; S16Vec3::Add(out, *this, v); return out; }
	inline S16Vec3& operator += (const S16Vec3& v) { *this = *this + v; return *this; }
	inline S16Vec3 operator - (const S16Vec3& v) { S16Vec3 out; S16Vec3::Sub(out, *this, v); return out; }
	inline S16Vec3& operator -= (const S16Vec3& v) { *this = *this - v; return *this; }
	inline S16Vec3 operator * (const S16Vec3& v) { S16Vec3 out; S16Vec3::Mul(out, *this, v); return out; }
	inline S16Vec3& operator *= (const S16Vec3& v) { *this = *this * v; return *this; }
	inline S16Vec3 operator / (const S16Vec3& v) { S16Vec3 out; S16Vec3::Div(out, *this, v); return out; }
	inline S16Vec3& operator /= (const S16Vec3& v) { *this = *this / v; return *this; }

	// V3 <op> Fx
	inline S16Vec3 operator + (fx16 n) { S16Vec3 out; S16Vec3::Add(out, *this, n); return out; }
	inline S16Vec3& operator += (fx16 n) { *this = *this + n; return *this; }
	inline S16Vec3 operator - (fx16 n) { S16Vec3 out; S16Vec3::Sub(out, *this, n); return out; }
	inline S16Vec3& operator -= (fx16 n) { *this = *this - n; return *this; }
	inline S16Vec3 operator * (fx16 n) { S16Vec3 out; S16Vec3::Mul(out, *this, n); return out; }
	inline S16Vec3& operator *= (fx16 n) { *this = *this * n; return *this; }
	inline S16Vec3 operator / (fx16 n) { S16Vec3 out; S16Vec3::Div(out, *this, n); return out; }
	inline S16Vec3& operator /= (fx16 n) { *this = *this / n; return *this; }

	// other
	inline S16Vec3 operator -() { S16Vec3 out(-x, -y, -z); return out; }
	inline bool operator ==(const S16Vec3& v) { return (x == v.x) && (y == v.y) && (z == v.z); }
	inline bool operator !=(const S16Vec3& v) { return !((x == v.x) && (y == v.y) && (z == v.z)); }
	inline fx16& operator[](int i) { return a[i]; }

	// vector math
	inline S16Vec3& Rand() { return S16Vec3::Rand(*this); }
	inline S16Vec3& SetMag(fx16 mag) { return S16Vec3::SetMag(*this, mag); }
	inline fx32 Mag() { return S16Vec3::Mag(*this); }
	inline fx32 Mag2() { return S16Vec3::Mag2(*this); }
	inline fx32 Distance(const S16Vec3& v) { return S16Vec3::Distance(*this, v); }
	inline S16Vec3& Cross(const S16Vec3& v) { return S16Vec3::Cross(*this, *this, v); }
	inline fx32 Dot(const S16Vec3& v) { return S16Vec3::Dot(*this, v); }
	inline bool TryNormalize() { return S16Vec3::TryNormalize(*this, *this); }
	inline S16Vec3& Normalize() { return S16Vec3::Normalize(*this, *this); }

	// other math
	inline S16Vec3& Abs() { return S16Vec3::Abs(*this, *this); }
	inline S16Vec3& Floor() { return S16Vec3::Floor(*this, *this); }
	inline S16Vec3& Ceil() { return S16Vec3::Ceil(*this, *this); }
	inline S16Vec3& Round() { return S16Vec3::Round(*this, *this); }
	inline S16Vec3& FlipX() { return S16Vec3::FlipX(*this, *this); }
	inline S16Vec3& FlipY() { return S16Vec3::FlipY(*this, *this); }
	inline S16Vec3& FlipZ() { return S16Vec3::FlipZ(*this, *this); }

	// S16V3 <op> S16V3
	static inline S16Vec3& Add(S16Vec3& out, const S16Vec3& in_a, const S16Vec3& in_b)
	{
		out.x = in_a.x + in_b.x;
		out.y = in_a.y + in_b.y;
		out.z = in_a.z + in_b.z;
		return out;
	}

	static inline S16Vec3& Sub(S16Vec3& out, const S16Vec3& in_a, const S16Vec3& in_b)
	{
		out.x = in_a.x - in_b.x;
		out.y = in_a.y - in_b.y;
		out.z = in_a.z - in_b.z;
		return out;
	}

	static inline S16Vec3& Mul(S16Vec3& out, const S16Vec3& in_a, const S16Vec3& in_b)
	{
		out.x = in_a.x * in_b.x;
		out.y = in_a.y * in_b.y;
		out.z = in_a.z * in_b.z;
		return out;
	}

	static inline S16Vec3& Div(S16Vec3& out, const S16Vec3& in_a, const S16Vec3& in_b)
	{
		if (in_b.x == 0 || in_b.y == 0 || in_b.z == 0)
			return out;

		out.x = (fx16)FX_Div((fx32)in_a.x, (fx32)in_b.x);
		out.y = (fx16)FX_Div((fx32)in_a.y, (fx32)in_b.y);
		out.z = (fx16)FX_Div((fx32)in_a.z, (fx32)in_b.z);
		return out;
	}

	// S16V3 <op> Fx
	static inline S16Vec3& Add(S16Vec3& out, const S16Vec3& in_a, const fx16 in_b)
	{
		out.x = in_a.x + in_b;
		out.y = in_a.y + in_b;
		out.z = in_a.z + in_b;
		return out;
	}

	static inline S16Vec3& Sub(S16Vec3& out, const S16Vec3& in_a, const fx16 in_b)
	{
		out.x = in_a.x - in_b;
		out.y = in_a.y - in_b;
		out.z = in_a.z - in_b;
		return out;
	}

	static inline S16Vec3& Mul(S16Vec3& out, const S16Vec3& in_a, const fx16 in_b)
	{
		// disgusting code taken from Vec3::operator*;
		u64 al = (u64)in_a.x * in_b;
		u64 bl = (u64)in_a.y * in_b;
		u64 cl = (u64)in_a.z * in_b;

		u32 a = (u32)al;
		u32 b = (u32)bl;
		u32 c = (u32)cl;

		//out.x = a + 0x800 >> 0xc | ((s32)(HI64(al)) + (u32)(0xfffff7ff < a)) * 0x100000;
		//out.y = b + 0x800 >> 0xc | ((s32)(HI64(bl)) + (u32)(0xfffff7ff < b)) * 0x100000;
		//out.z = c + 0x800 >> 0xc | ((s32)(HI64(cl)) + (u32)(0xfffff7ff < c)) * 0x100000;

		out.x = (a + 0x800) >> 0xc;
		out.y = (b + 0x800) >> 0xc;
		out.z = (c + 0x800) >> 0xc;


		return out;
	}

	static inline S16Vec3& Div(S16Vec3& out, const S16Vec3& in_a, const fx16 in_b)
	{
		if (in_b == 0)
			return out;

		out.x = (fx16)FX_Div((fx32)in_a.x, (fx32)in_b);
		out.y = (fx16)FX_Div((fx32)in_a.y, (fx32)in_b);
		out.z = (fx16)FX_Div((fx32)in_a.z, (fx32)in_b);
		return out;
	}

	// vector math
	static inline S16Vec3& Rand(S16Vec3& in)
	{
		in = S16Vec3(RNG(), RNG(), RNG());
		for (int i = 0; i < 3; i++) in[i] %= 0x100000;
		in.Normalize();
		return in;
	}

	static inline S16Vec3& SetMag(S16Vec3& in, fx16 mag)
	{
		in.Normalize();
		in *= mag;

		return in;
	}

	static inline fx32 Mag(const S16Vec3& in)
	{
		u64 sq = (u64)in.x * (u64)in.x + (u64)in.y * (u64)in.y + (u64)in.z * (u64)in.z;
		return (fx32)FX_Sqrt64(sq);
	}

	static inline fx32 Mag2(const S16Vec3& in)
	{
		u64 sq = (u64)in.x * (u64)in.x + (u64)in.y * (u64)in.y + (u64)in.z * (u64)in.z;
		return (fx32)(FX_Whole(sq) | HI64(sq) << 0x14);
	}

	static inline fx32 Distance(const S16Vec3& in_a, const S16Vec3& in_b)
	{
		return S16Vec3::Mag(*cCS16V3(in_a) - *cCS16V3(in_b));
	}

	static inline S16Vec3& Cross(S16Vec3& out, const S16Vec3& in_a, const S16Vec3& in_b)
	{
		VEC_Fx16CrossProduct(cCS16V3(in_a)->ToVecFx16(), cCS16V3(in_b)->ToVecFx16(), out.ToVecFx16());
		return out;
	}

	static inline fx32 Dot(const S16Vec3& in_a, const S16Vec3& in_b)
	{
		return VEC_Fx16DotProduct(cCS16V3(in_a)->ToVecFx16(), cCS16V3(in_b)->ToVecFx16());
	}

	static inline bool TryNormalize(S16Vec3& out, const S16Vec3& in)
	{
		if ((in.x == 0) && (in.x == 0) && (in.y == 0))
			return false;

		VEC_Fx16Normalize(cCS16V3(in)->ToVecFx16(), out.ToVecFx16());
		return true;
	}

	static inline S16Vec3& Normalize(S16Vec3& out, const S16Vec3& in)
	{
		VEC_Fx16Normalize(cCS16V3(in)->ToVecFx16(), out.ToVecFx16());
		return out;
	}

	// other math
	static inline S16Vec3& Abs(S16Vec3& out, const S16Vec3& in)
	{
		out.x = MATH_ABS(in.x);
		out.y = MATH_ABS(in.y);
		out.z = MATH_ABS(in.z);
		return out;
	}

	static inline S16Vec3& Floor(S16Vec3& out, const S16Vec3& in)
	{
		out.x = FX_Floor(in.x);
		out.y = FX_Floor(in.y);
		out.z = FX_Floor(in.z);
		return out;
	}

	static inline S16Vec3& Ceil(S16Vec3& out, const S16Vec3& in)
	{
		out.x = FX_Ceil(in.x);
		out.y = FX_Ceil(in.y);
		out.z = FX_Ceil(in.z);
		return out;
	}

	static inline S16Vec3& Round(S16Vec3& out, const S16Vec3& in)
	{
		out.x = FX_Round(in.x);
		out.y = FX_Round(in.y);
		out.z = FX_Round(in.z);
		return out;
	}

	static inline S16Vec3& FlipX(S16Vec3& out, const S16Vec3& in)
	{
		out.x = -in.x;
		out.y = in.y;
		out.z = in.z;
		return out;
	}

	static inline S16Vec3& FlipY(S16Vec3& out, const S16Vec3& in)
	{
		out.x = in.x;
		out.y = -in.y;
		out.z = in.z;
		return out;
	}

	static inline S16Vec3& FlipZ(S16Vec3& out, const S16Vec3& in)
	{
		out.x = in.x;
		out.y = in.y;
		out.z = -in.z;
		return out;
	}
};