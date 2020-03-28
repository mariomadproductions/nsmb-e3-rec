#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"
#include "nsmb/misc.h"
#include "nsmb/fxmath.h"

#define Vec2_vtable ((void*)0x20391E8)

extern "C"
{
	void Vec2_OperatorAdd(Vec2* out, const Vec2* in_a, const VecFx32* in_b);
	void Vec2_OperatorSub(Vec2* out, const Vec2* in_a, const VecFx32* in_b);
	void Vec2_OperatorMul(Vec2* out, const Vec2* in_a, const fx32 in_b);
	void Vec2_OperatorMulEqual(Vec2* inout, fx32 in);
	void Vec2_OperatorDiv(Vec2* inout_a, const Vec2* in_b, fx32 in_c);
	bool Vec2_OperatorEq(Vec2* in_a, const VecFx32* in_b);
	bool Vec2_OperatorNotEq(Vec2* in_a, const VecFx32* in_b);
	fx32 Vec2_Distance(const Vec2* in_a, const VecFx32* in_b);
	void Vec2_NormalizeImm(Vec2* out, const Vec2* in);
	bool Vec2_TryNormalize(Vec2* inout);
	fx32 Vec2_Cross(const Vec2* in_a, const VecFx32* in_b);
	fx32 Vec2_Mag(const Vec2* in);
	fx32 Vec2_Mag2(const Vec2* in);
}

class Vec2
{
public:
	void* vtable;
	union
	{
		fx32 a[2];
		struct
		{
			fx32 x, y;
		};
	};

	Vec2() : vtable(Vec2_vtable), x(0), y(0) {}
	Vec2(fx32 n) : vtable(Vec2_vtable), x(n), y(n) {}
	Vec2(fx32 x_, fx32 y_) : vtable(Vec2_vtable), x(x_), y(y_) {}
	Vec2(const VecFx32& v) : vtable(Vec2_vtable), x(v.x), y(v.y) {}

	VecFx32* ToVecFx32() { return cVFx32(x); }
	static VecFx32* ToVecFx32(Vec2& v) { return cVFx32(v.x); }

	// V2 <op> V2
	inline Vec2 operator + (const Vec2& v) { Vec2 out; Vec2::Add(out, *this, v); return out; }
	inline Vec2& operator += (const Vec2& v) { *this = *this + v; return *this; }
	inline Vec2 operator - (const Vec2& v) { Vec2 out; Vec2::Sub(out, *this, v); return out; }
	inline Vec2& operator -= (const Vec2& v) { *this = *this - v; return *this; }
	inline Vec2 operator * (const Vec2& v) { Vec2 out; Vec2::Mul(out, *this, v); return out; }
	inline Vec2& operator *= (const Vec2& v) { *this = *this * v; return *this; }
	inline Vec2 operator / (const Vec2& v) { Vec2 out; Vec2::Div(out, *this, v); return out; }
	inline Vec2& operator /= (const Vec2& v) { *this = *this / v; return *this; }

	// V2 <op> Fx
	inline Vec2 operator + (fx32 n) { Vec2 out; Vec2::Add(out, *this, n); return out; }
	inline Vec2& operator += (fx32 n) { *this = *this + n; return *this; }
	inline Vec2 operator - (fx32 n) { Vec2 out; Vec2::Sub(out, *this, n); return out; }
	inline Vec2& operator -= (fx32 n) { *this = *this - n; return *this; }
	inline Vec2 operator * (fx32 n) { Vec2 out; Vec2::Mul(out, *this, n); return out; }
	inline Vec2& operator *= (fx32 n) { Vec2_OperatorMulEqual(this, n); return *this; }
	inline Vec2 operator / (fx32 n) { Vec2 out; Vec2::Div(out, *this, n); return out; }
	inline Vec2& operator /= (fx32 n) { *this = *this / n; return *this; }

	// other
	inline Vec2 operator -() { Vec2 out(-x, -y); return out; }
	inline bool operator==(const Vec2& v) { return Vec2_OperatorEq(this, cCV2(v)->ToVecFx32()); }
	inline bool operator!=(const Vec2& v) { return Vec2_OperatorNotEq(this, cCV2(v)->ToVecFx32()); }
	inline fx32& operator[](int i) { return a[i]; }

	// vector math
	inline Vec2& Rand() { return Vec2::Rand(*this); }
	inline Vec2& SetMag(fx32 mag) { return Vec2::SetMag(*this, mag); }
	inline fx32 Mag() { return Vec2::Mag(*this); }
	inline fx32 Mag2() { return Vec2::Mag2(*this); }inline fx32 Distance(const Vec2& v) { return Vec2::Distance(*this, v); }
	inline fx32 Cross(const Vec2& v) { return Vec2::Cross(*this, v); }
	inline fx32 Dot(const Vec2& v) { return Vec2::Dot(*this, v); }
	inline bool TryNormalize() { return Vec2::TryNormalize(*this, *this); }
	inline Vec2& Normalize() { return Vec2::Normalize(*this, *this); }

	// other math
	inline Vec2& Abs() { return Vec2::Abs(*this, *this); }
	inline Vec2& Floor() { return Vec2::Floor(*this, *this); }
	inline Vec2& Ceil() { return Vec2::Ceil(*this, *this); }
	inline Vec2& Round() { return Vec2::Round(*this, *this); }
	inline Vec2& FlipX() { return Vec2::FlipX(*this, *this); }
	inline Vec2& FlipY() { return Vec2::FlipY(*this, *this); }

	// V2 <op> V2
	static inline Vec2& Add(Vec2& out, const Vec2& in_a, const Vec2& in_b)
	{
		Vec2_OperatorAdd(&out, &in_a, cCV2(in_b)->ToVecFx32());
		return out;
	}

	static inline Vec2& Sub(Vec2& out, const Vec2& in_a, const Vec2& in_b)
	{
		Vec2_OperatorSub(&out, &in_a, cCV2(in_b)->ToVecFx32());
		return out;
	}

	static inline Vec2& Mul(Vec2& out, const Vec2& in_a, const Vec2& in_b)
	{
		out.x = in_a.x * in_b.x;
		out.y = in_a.y * in_b.y;
		return out;
	}

	static inline Vec2& Div(Vec2& out, const Vec2& in_a, const Vec2& in_b)
	{
		if (in_b.x == 0 || in_b.y == 0)
			return out;

		out.x = FX_Div(in_a.x, in_b.x);
		out.y = FX_Div(in_a.y, in_b.y);
		return out;
	}

	// V2 <op> Fx
	static inline Vec2& Add(Vec2& out, const Vec2& in_a, const fx32 in_b)
	{
		out.x = in_a.x + in_b;
		out.y = in_a.y + in_b;
		return out;
	}

	static inline Vec2& Sub(Vec2& out, const Vec2& in_a, const fx32 in_b)
	{
		out.x = in_a.x - in_b;
		out.y = in_a.y - in_b;
		return out;
	}

	static inline Vec2& Mul(Vec2& out, const Vec2& in_a, const fx32 in_b)
	{
		Vec2_OperatorMul(&out, &in_a, in_b);
		return out;
	}

	static inline Vec2& Div(Vec2& out, const Vec2& in_a, const fx32 in_b)
	{
		Vec2_OperatorDiv(&out, &in_a, in_b);
		return out;
	}

	// vector math
	static inline Vec2& Rand(Vec2& in)
	{
		in = Vec2(RNG(), RNG());
		for (int i = 0; i < 2; i++) in[i] %= 0x100000;
		in.Normalize();
		return in;
	}

	static inline Vec2& SetMag(Vec2& in, fx32 mag)
	{
		in.Normalize();
		in *= mag;
		return in;
	}

	static inline fx32 Mag(const Vec2& in)
	{
		return Vec2_Mag(&in);
	}

	static inline fx32 Mag2(const Vec2& in)
	{
		return Vec2_Mag2(&in);
	}

	static inline fx32 Distance(const Vec2& in_a, const Vec2& in_b)
	{
		return Vec2_Distance(&in_a, cCV2(in_b)->ToVecFx32());
	}

	static inline fx32 Cross(const Vec2& in_a, const Vec2& in_b)
	{
		return Vec2_Cross(&in_a, cCV2(in_b)->ToVecFx32());
	}

	static inline fx32 Dot(const Vec2& in_a, const Vec2& in_b)
	{
		u32 xy = (u64)in_a.x * (u64)in_b.y;
		u32 yx = (u64)in_a.y * (u64)in_b.x;
		fx32 res =
			((xy + 0x800) >> 12 | ((fx32)((u64)xy >> 0x20) + (u32)(0xfffff7ff < xy)) * 0x100000) +
			((yx + 0x800) >> 12 | ((fx32)((u64)yx >> 0x20) + (u32)(0xfffff7ff < yx)) * 0x100000);
		return res;
	}

	static inline bool TryNormalize(Vec2& out, const Vec2& in)
	{
		out = in;
		return Vec2_TryNormalize(&out);
	}

	static inline Vec2& Normalize(Vec2& out, const Vec2& in)
	{
		Vec2_NormalizeImm(&out, &in);
		return out;
	}

	// other math
	static inline Vec2& Abs(Vec2& out, const Vec2& in)
	{
		out.x = MATH_ABS(in.x);
		out.y = MATH_ABS(in.y);
		return out;
	}

	static inline Vec2& Floor(Vec2& out, const Vec2& in)
	{
		out.x = FX_Floor(in.x);
		out.y = FX_Floor(in.y);
		return out;
	}

	static inline Vec2& Ceil(Vec2& out, const Vec2& in)
	{
		out.x = FX_Ceil(in.x);
		out.y = FX_Ceil(in.y);
		return out;
	}

	static inline Vec2& Round(Vec2& out, const Vec2& in)
	{
		out.x = FX_Round(in.x);
		out.y = FX_Round(in.y);
		return out;
	}

	static inline Vec2& FlipX(Vec2& out, const Vec2& in)
	{
		out.x = -in.x;
		out.y = in.y;
		return out;
	}

	static inline Vec2& FlipY(Vec2& out, const Vec2& in)
	{
		out.x = in.x;
		out.y = -in.y;
		return out;
	}
};