#pragma once

#ifdef __cplusplus

#include <cstdint>

class ostream
{
	static void stream_buffer(uint64_t p0);
	static char buffer_arr_char[120];
	static uint32_t buffer_arr_u32[30];

	friend ostream& operator<<(ostream& os, const char* char_ptr);
	friend ostream& operator<<(ostream& os, uint32_t val);
	friend ostream& operator<<(ostream& os, uint64_t val);

	inline friend ostream& operator<<(ostream& os, void const* pointer) { return os << reinterpret_cast<uint32_t>(pointer); }
	inline friend ostream& operator<<(ostream& os, int val) { return os << static_cast<uint32_t>(val); }
	inline friend ostream& operator<<(ostream& os, unsigned val) { return os << static_cast<uint32_t>(val); }
	inline friend ostream& operator<<(ostream& os, int64_t val) { return os << static_cast<uint64_t>(val); }
	inline friend ostream& operator<<(ostream& os, long val) { return os << static_cast<uint32_t>(val); }
}
extern cout;

#endif // __cplusplus