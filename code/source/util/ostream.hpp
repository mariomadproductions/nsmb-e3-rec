#pragma once

#include "nsmb/math/vector.h"
#include "extra/fx.hpp"


/*
	Utilily that allows for printing in C++ code

	Usage is the same as std::cout and it supports dec, hex, bin, lowercase and uppercase tokens
	
	Currently this utility is required for the NSMB Code Reference to work
*/

namespace log
{

	struct iomanip_token {};

	struct iomanip_dec : iomanip_token {};
	struct iomanip_hex : iomanip_token {};
	struct iomanip_bin : iomanip_token {};

	struct iomanip_lowercase : iomanip_token {};
	struct iomanip_uppercase : iomanip_token {};

	class ostream
	{
	public:

		static constexpr u32 Dec = 0x00000001;
		static constexpr u32 Hex = 0x00000002;
		static constexpr u32 Bin = 0x00000004;
		static constexpr u32 Lowercase = 0x00000010;
		static constexpr u32 Uppercase = 0x00000020;

	private:

		static constexpr u32 BaseMask = 0x0000000F;
		static constexpr u32 CaseMask = 0x000000F0;

		static constexpr u32 buffer_size = 120;
		static char buffer[buffer_size];
		static u32 io_flags;

	public:

		static void set_buffer(const char* char_ptr);
		static void flush();

		inline static u32 flags(u32 flags) {
			u32 old = io_flags;
			io_flags = flags;
			return old;
		}

		inline static u32 flags() {
			return io_flags;
		}

		constexpr ostream& operator<<(const iomanip_token&) {
			return *this;
		}

		inline ostream& operator<<(const iomanip_dec&) {
			io_flags &= ~BaseMask;
			io_flags |= Dec;
			return *this;
		}

		inline ostream& operator<<(const iomanip_hex&) {
			io_flags &= ~BaseMask;
			io_flags |= Hex;
			return *this;
		}

		inline ostream& operator<<(const iomanip_bin&) {
			io_flags &= ~BaseMask;
			io_flags |= Bin;
			return *this;
		}

		inline ostream& operator<<(const iomanip_lowercase&) {
			io_flags &= ~CaseMask;
			io_flags |= Lowercase;
			return *this;
		}

		inline ostream& operator<<(const iomanip_uppercase&) {
			io_flags &= ~CaseMask;
			io_flags |= Uppercase;
			return *this;
		}

		inline ostream& operator<<(const char* char_ptr)
		{
			set_buffer(char_ptr);
			flush();

			return *this;
		}

		inline ostream& operator<<(char character)
		{
			buffer[0] = character;
			buffer[1] = '\0';

			flush();

			return *this;
		}

		ostream& operator<<(u32 val);
		ostream& operator<<(s32 val);
		ostream& operator<<(u64 val);
		ostream& operator<<(s64 val);

		inline ostream& operator<<(u8 val) { return *this << char(val); }
		inline ostream& operator<<(s8 val) { return *this << char(val); }
		inline ostream& operator<<(u16 val) { return *this << u32(val); }
		inline ostream& operator<<(s16 val) { return *this << s32(val); }
		inline ostream& operator<<(unsigned val) { return *this << u32(val); }
		inline ostream& operator<<(int val) { return *this << s32(val); }

		template<typename T>
		inline ostream& operator<<(T* ptr) { return *this << reinterpret_cast<u32>(ptr); }
		inline ostream& operator<<(bool b) { return *this << ((io_flags & Uppercase) ? (b ? "TRUE" : "FALSE") : (b ? "true" : "false")); }

		inline ostream& operator<<(const Vec2& v) {
			*this << "[ " << v.x << ", " << v.y << " ]";
			return *this;
		}

		inline ostream& operator<<(const Vec3& v) {
			*this << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
			return *this;
		}

		inline ostream& operator<<(const Vec3s& v) {
			*this << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
			return *this;
		}

		//friend ostream& setw(ostream& os, u8 w);
		//friend ostream& setfill(ostream& os, char c);

		ostream& operator<<(const Fx16& fx);
		ostream& operator<<(const Fx32& fx);
		ostream& operator<<(const Fx64& fx);
		ostream& operator<<(const Fx64c& fx);

	};

	constexpr inline iomanip_dec dec;
	constexpr inline iomanip_hex hex;
	constexpr inline iomanip_bin bin;
	constexpr inline iomanip_lowercase lowercase;
	constexpr inline iomanip_uppercase uppercase;

	inline iomanip_token setw(u8 w) {

		u32 flags = ostream::flags();

		flags &= ~(0xFF << 16);
		flags |= u32(w) << 16;

		ostream::flags(flags);

		return {};

	}

	inline iomanip_token setfill(char c) {

		u32 flags = ostream::flags();

		flags &= ~(0xFF << 24);
		flags |= u32(c) << 24;

		ostream::flags(flags);

		return {};

	}

	extern ostream cout;

}
