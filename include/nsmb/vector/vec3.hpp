#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"
#include "nsmb/misc.h"
#include "nsmb/fxmath.h"

#define Vec3_vtable ((void*)0x2039208)

extern "C"
{
	void Vec3_OperatorAdd(Vec3* out, const Vec3* in_a, const VecFx32* in_b);
	void Vec3_OperatorSub(Vec3* out, const Vec3* in_a, const VecFx32* in_b);
	void Vec3_OperatorMul(Vec3* out, const Vec3* in_a, const fx32 in_b);
	void Vec3_OperatorMulEqual(Vec3* inout, fx32 in);
	bool Vec3_OperatorEq(Vec3* in_a, const VecFx32* in_b);
	bool Vec3_OperatorNotEq(Vec3* in_a, const VecFx32* in_b);
	fx32 Vec3_Distance(const Vec3* in_a, const VecFx32* in_b);
	void Vec3_NormalizeImm(Vec3* out, const Vec3* in);
	bool Vec3_TryNormalize(Vec3* inout);
	void Vec3_Cross(Vec3* out, const VecFx32* in_a, const VecFx32* in_b);
	void Vec3_Cross2(Vec3* out, Vec3* dupe, const VecFx32* in_a, const VecFx32* in_b);
	void Vec3_RotXY(Vec3* out, fx16 angle);
	void Vec3_RotYZ(Vec3* out, fx16 angle);
	void Vec3_RotXZ(Vec3* out, fx16 angle);
}

class Vec3
{
public:
	void* vtable;
	union
	{
		fx32 a[3];
		struct
		{
			fx32 x, y, z;
		};
	};

	Vec3() : vtable(Vec3_vtable), x(0), y(0), z(0) {}
	Vec3(fx32 n) : vtable(Vec3_vtable), x(n), y(n), z(n) {}
	Vec3(fx32 x_, fx32 y_, fx32 z_) : vtable(Vec3_vtable), x(x_), y(y_), z(z_) {}
	Vec3(const VecFx32& v) : vtable(Vec3_vtable), x(v.x), y(v.y), z(v.z) {}
	Vec3(const Vec2& v) : vtable(Vec3_vtable), x(v.x), y(v.y), z(0) {}
	Vec3(const S16Vec3& v) : vtable(Vec3_vtable), x(v.x), y(v.y), z(v.z) {}

	VecFx32* ToVecFx32() { return cVFx32(x); }
	static VecFx32* ToVecFx32(Vec3& v) { return cVFx32(v.x); }

	// V3 <op> V3
	inline Vec3 operator + (const Vec3& v) { Vec3 out; Vec3::Add(out, *this, v); return out; }
	inline Vec3& operator += (const Vec3& v) { *this = *this + v; return *this; }
	inline Vec3 operator - (const Vec3& v) { Vec3 out; Vec3::Sub(out, *this, v); return out; }
	inline Vec3& operator -= (const Vec3& v) { *this = *this - v; return *this; }
	inline Vec3 operator * (const Vec3& v) { Vec3 out; Vec3::Mul(out, *this, v); return out; }
	inline Vec3& operator *= (const Vec3& v) { *this = *this * v; return *this; }
	inline Vec3 operator / (const Vec3& v) { Vec3 out; Vec3::Div(out, *this, v); return out; }
	inline Vec3& operator /= (const Vec3& v) { *this = *this / v; return *this; }

	// V3 <op> V2
	inline Vec3 operator + (const Vec2& v) { Vec3 out; Vec3::Add(out, *this, v); return out; }
	inline Vec3& operator += (const Vec2& v) { *this = *this + v; return *this; }
	inline Vec3 operator - (const Vec2& v) { Vec3 out; Vec3::Sub(out, *this, v); return out; }
	inline Vec3& operator -= (const Vec2& v) { *this = *this - v; return *this; }
	inline Vec3 operator * (const Vec2& v) { Vec3 out; Vec3::Mul(out, *this, v); return out; }
	inline Vec3& operator *= (const Vec2& v) { *this = *this * v; return *this; }
	inline Vec3 operator / (const Vec2& v) { Vec3 out; Vec3::Div(out, *this, v); return out; }
	inline Vec3& operator /= (const Vec2& v) { *this = *this / v; return *this; }

	// V3 <op> Fx
	inline Vec3 operator + (fx32 n) { Vec3 out; Vec3::Add(out, *this, n); return out; }
	inline Vec3& operator += (fx32 n) { *this = *this + n; return *this; }
	inline Vec3 operator - (fx32 n) { Vec3 out; Vec3::Sub(out, *this, n); return out; }
	inline Vec3& operator -= (fx32 n) { *this = *this - n; return *this; }
	inline Vec3 operator * (fx32 n) { Vec3 out; Vec3::Mul(out, *this, n); return out; }
	inline Vec3& operator *= (fx32 n) { Vec3_OperatorMulEqual(this, n); return *this; }
	inline Vec3 operator / (fx32 n) { Vec3 out; Vec3::Div(out, *this, n); return out; }
	inline Vec3& operator /= (fx32 n) { *this = *this / n; return *this; }

	// other
	inline Vec3 operator -() { Vec3 out(-x, -y, -z); return out; }
	inline bool operator==(const Vec3& v) { return Vec3_OperatorEq(this, cCV3(v)->ToVecFx32()); }
	inline bool operator!=(const Vec3& v) { return Vec3_OperatorNotEq(this, cCV3(v)->ToVecFx32()); }
	inline fx32& operator[](int i) { return a[i]; }

	// vector math
	inline Vec3& Rand() { return Vec3::Rand(*this); }
	inline Vec3& SetMag(fx32 mag) { return Vec3::SetMag(*this, mag); }
	inline fx32 Mag() { return Vec3::Mag(*this); }
	inline fx32 Mag2() { return Vec3::Mag2(*this); }
	inline fx32 Distance(const Vec3& v) { return Vec3::Distance(*this, v); }
	inline Vec3& Cross(const Vec3& v) { return Vec3::Cross(*this, *this, v); }
	inline fx32 Dot(const Vec3& v) { return Vec3::Dot(*this, v); }
	inline bool TryNormalize() { return Vec3::TryNormalize(*this, *this); }
	inline Vec3& Normalize() { return Vec3::Normalize(*this, *this); }
	inline Vec3& RotXY(fx16 angle) { return Vec3::RotXY(*this, *this, angle); }
	inline Vec3& RotYZ(fx16 angle) { return Vec3::RotYZ(*this, *this, angle); }
	inline Vec3& RotXZ(fx16 angle) { return Vec3::RotXZ(*this, *this, angle); }

	// other math
	inline Vec3& Abs() { return Vec3::Abs(*this, *this); }
	inline Vec3& Floor() { return Vec3::Floor(*this, *this); }
	inline Vec3& Ceil() { return Vec3::Ceil(*this, *this); }
	inline Vec3& Round() { return Vec3::Round(*this, *this); }
	inline Vec3& FlipX() { return Vec3::FlipX(*this, *this); }
	inline Vec3& FlipY() { return Vec3::FlipY(*this, *this); }
	inline Vec3& FlipZ() { return Vec3::FlipZ(*this, *this); }

	// V3 <op> V3
	static inline Vec3& Add(Vec3& out, const Vec3& in_a, const Vec3& in_b)
	{
		Vec3_OperatorAdd(&out, &in_a, cCV3(in_b)->ToVecFx32());
		return out;
	}

	static inline Vec3& Sub(Vec3& out, const Vec3& in_a, const Vec3& in_b)
	{
		Vec3_OperatorSub(&out, &in_a, cCV3(in_b)->ToVecFx32());
		return out;
	}

	static inline Vec3& Mul(Vec3& out, const Vec3& in_a, const Vec3& in_b)
	{
		out.x = in_a.x * in_b.x;
		out.y = in_a.y * in_b.y;
		out.z = in_a.z * in_b.z;
		return out;
	}

	static inline Vec3& Div(Vec3& out, const Vec3& in_a, const Vec3& in_b)
	{
		if (in_b.x == 0 || in_b.y == 0 || in_b.z == 0)
			return out;

		out.x = FX_Div(in_a.x, in_b.x);
		out.y = FX_Div(in_a.y, in_b.y);
		out.z = FX_Div(in_a.z, in_b.z);
		return out;
	}

	// V3 <op> V2
	static inline Vec3& Add(Vec3& out, const Vec3& in_a, const Vec2& in_b)
	{
		out.x = in_a.x + in_b.x;
		out.y = in_a.y + in_b.y;
		return out;
	}

	static inline Vec3& Sub(Vec3& out, const Vec3& in_a, const Vec2& in_b)
	{
		out.x = in_a.x - in_b.x;
		out.y = in_a.y - in_b.y;
		return out;
	}

	static inline Vec3& Mul(Vec3& out, const Vec3& in_a, const Vec2& in_b)
	{
		out.x = in_a.x * in_b.x;
		out.y = in_a.y * in_b.y;
		return out;
	}

	static inline Vec3& Div(Vec3& out, const Vec3& in_a, const Vec2& in_b)
	{
		if (in_b.x == 0 || in_b.y == 0)
			return out;

		out.x = FX_Div(in_a.x, in_b.x);
		out.y = FX_Div(in_a.y, in_b.y);
		return out;
	}

	// V3 <op> Fx
	static inline Vec3& Add(Vec3& out, const Vec3& in_a, const fx32 in_b)
	{
		out.x = in_a.x + in_b;
		out.y = in_a.y + in_b;
		out.z = in_a.z + in_b;
		return out;
	}

	static inline Vec3& Sub(Vec3& out, const Vec3& in_a, const fx32 in_b)
	{
		out.x = in_a.x - in_b;
		out.y = in_a.y - in_b;
		out.z = in_a.z - in_b;
		return out;
	}

	static inline Vec3& Mul(Vec3& out, const Vec3& in_a, const fx32 in_b)
	{
		Vec3_OperatorMul(&out, &in_a, in_b);
		return out;
	}

	static inline Vec3& Div(Vec3& out, const Vec3& in_a, const fx32 in_b)
	{
		if (in_b == 0)
			return out;

		out.x = FX_Div(in_a.x, in_b);
		out.y = FX_Div(in_a.y, in_b);
		out.z = FX_Div(in_a.z, in_b);
		return out;
	}

	// vector math
	static inline Vec3& Rand(Vec3& in)
	{
		in = Vec3(RNG(), RNG(), RNG());
		for (int i = 0; i < 3; i++) in[i] %= 0x100000;
		in.Normalize();
		return in;
	}

	static inline Vec3& SetMag(Vec3& in, fx32 mag)
	{
		in.Normalize();
		in *= mag;
		return in;
	}

	static inline fx32 Mag(const Vec3& in)
	{
		return VEC_Mag(cCV3(in)->ToVecFx32());
	}

	static inline fx32 Mag2(const Vec3& in)
	{
		u64 sq = (u64)in.x * (u64)in.x + (u64)in.y * (u64)in.y + (u64)in.z * (u64)in.z;
		return FX_Whole(sq) | HI64(sq) << 0x14;
	}

	static inline fx32 Distance(const Vec3& in_a, const Vec3& in_b)
	{
		return Vec3_Distance(&in_a, cCV3(in_b)->ToVecFx32());
	}

	static inline Vec3& Cross(Vec3& out, const Vec3& in_a, const Vec3& in_b)
	{
		Vec3_Cross(&out, cCV3(in_a)->ToVecFx32(), cCV3(in_b)->ToVecFx32());
		return out;
	}

	static inline fx32 Dot(const Vec3& in_a, const Vec3& in_b)
	{
		return VEC_DotProduct(cCV3(in_a)->ToVecFx32(), cCV3(in_b)->ToVecFx32());
	}

	static inline bool TryNormalize(Vec3& out, const Vec3& in)
	{
		out = in;
		return Vec3_TryNormalize(&out);
	}

	static inline Vec3& Normalize(Vec3& out, const Vec3& in)
	{
		Vec3_NormalizeImm(&out, &in);
		return out;
	}

	static inline Vec3& RotXY(Vec3& out, Vec3& in, fx16 angle)
	{
		out = in;
		Vec3_RotXY(&out, angle);
		return out;
	}

	static inline Vec3& RotYZ(Vec3& out, Vec3& in, fx16 angle)
	{
		out = in;
		Vec3_RotYZ(&out, angle);
		return out;
	}

	static inline Vec3& RotXZ(Vec3& out, Vec3& in, fx16 angle)
	{
		out = in;
		Vec3_RotXZ(&out, angle);
		return out;
	}

	// other math
	static inline Vec3& Abs(Vec3& out, const Vec3& in)
	{
		out.x = MATH_ABS(in.x);
		out.y = MATH_ABS(in.y);
		out.z = MATH_ABS(in.z);
		return out;
	}

	static inline Vec3& Floor(Vec3& out, const Vec3& in)
	{
		out.x = FX_Floor(in.x);
		out.y = FX_Floor(in.y);
		out.z = FX_Floor(in.z);
		return out;
	}

	static inline Vec3& Ceil(Vec3& out, const Vec3& in)
	{
		out.x = FX_Ceil(in.x);
		out.y = FX_Ceil(in.y);
		out.z = FX_Ceil(in.z);
		return out;
	}

	static inline Vec3& Round(Vec3& out, const Vec3& in)
	{
		out.x = FX_Round(in.x);
		out.y = FX_Round(in.y);
		out.z = FX_Round(in.z);
		return out;
	}

	static inline Vec3& FlipX(Vec3& out, const Vec3& in)
	{
		out.x = -in.x;
		out.y = in.y;
		out.z = in.z;
		return out;
	}

	static inline Vec3& FlipY(Vec3& out, const Vec3& in)
	{
		out.x = in.x;
		out.y = -in.y;
		out.z = in.z;
		return out;
	}

	static inline Vec3& FlipZ(Vec3& out, const Vec3& in)
	{
		out.x = in.x;
		out.y = in.y;
		out.z = -in.z;
		return out;
	}
};