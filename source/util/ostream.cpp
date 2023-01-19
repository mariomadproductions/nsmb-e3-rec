#include "ostream.hpp"

#include <cstring>

asm(R"(
.global _ZN3log7ostream5flushEv
.global _ZN3log7ostream6bufferE

_ZN3log7ostream5flushEv:
	mov   r12,r12
	b     skip
	.word 0x00006464
_ZN3log7ostream6bufferE:
	.fill 120
	.word 0
skip:
	bx    lr
)");

namespace log
{

	ostream cout;
	u32 ostream::io_flags = ostream::Dec | ostream::Lowercase | u32(' ') << 24;

	void ostream::set_buffer(const char* char_ptr)
	{
		for (unsigned i = 0; i < buffer_size; i++)
		{
			if ((buffer[i] = char_ptr[i]) == '\0')
				break;
		}
	}

	static char get_hex_digit(u8 val) {

		if (val > 15) [[unlikely]]
			return ' ';

		if (val < 10)
			return val + '0';

		if (ostream::flags() & ostream::Uppercase)
			return (val - 10) + 'A';

		return (val - 10) + 'a';

	}

	static u32 put_decimal(char* str, u64 val, bool sign) {

		char buf[20];
		size_t pos = 0;

		if (sign) {
			str[pos++] = '-';
		}

		u32 digits = 1;
		for (u32 i = 0; i < 20; i++, digits++) {

			buf[i] = u32(val % 10) + '0';
			val /= 10;

			if (val == 0)
				break;
		}

		// Reverse string
		for (s32 i = digits - 1; i >= 0; i--) {
			str[pos++] = buf[i];
		}

		str[pos] = '\0';

		return pos;

	}

	static u32 put_hex(char* str, u64 val) {

		char buf[16];
		size_t pos = 0;

		u32 digits = 1;
		for (u32 i = 0; i < 16; i++, digits++) {

			buf[i] = get_hex_digit(val & 0xF);
			val >>= 4;

			if (val == 0)
				break;
		}

		// Reverse string
		for (s32 i = digits - 1; i >= 0; i--) {
			str[pos++] = buf[i];
		}

		str[pos] = '\0';

		return pos;

	}

	static u32 put_binary(char* str, u64 val) {

		char buf[64];
		size_t pos = 0;

		u32 digits = 1;
		for (u32 i = 0; i < 64; i++, digits++) {

			buf[i] = (val & 1) + '0';
			val >>= 1;

			if (val == 0)
				break;
		}

		// Reverse string
		for (s32 i = digits - 1; i >= 0; i--) {
			str[pos++] = buf[i];
		}

		str[pos] = '\0';

		return pos;

	}

	static u32 put_fill(char* str, u32 len) {

		// Respect given width
		s32 w = (ostream::flags() >> 16) & 0xFF;
		char ch = (ostream::flags() >> 24) & 0xFF;

		w -= len;

		if (w <= 0)
			return len;

		// Move string forward
		for (s32 i = len; i >= 0; i--) {
			str[i + w] = str[i];
		}

		// Append filling character
		for (u32 i = 0; i < w; i++) {
			str[i] = ch;
		}

		return len + w;

	}

	ostream& ostream::operator<<(u32 val)
	{
		char buf[256 + 32 + 1];
		u32 len = 0;

		if (ostream::flags() & ostream::Dec) {
			len = put_decimal(buf, val, false);
		}
		else if (ostream::flags() & ostream::Hex) {
			len = put_hex(buf, val);
		}
		else if (ostream::flags() & ostream::Bin) {
			len = put_binary(buf, val);
		}

		put_fill(buf, len);

		set_buffer(buf);
		flush();

		return *this;
	}

	ostream& ostream::operator<<(s32 val)
	{
		char buf[256 + 32 + 1];
		u32 len = 0;

		if (ostream::flags() & ostream::Dec) {
			len = put_decimal(buf, val < 0 ? -val : val, val < 0);
		}
		else if (ostream::flags() & ostream::Hex) {
			len = put_hex(buf, u32(val));
		}
		else if (ostream::flags() & ostream::Bin) {
			len = put_binary(buf, u32(val));
		}

		put_fill(buf, len);

		set_buffer(buf);
		flush();

		return *this;
	}

	ostream& ostream::operator<<(u64 val)
	{
		char buf[256 + 64 + 1];
		u32 len = 0;

		if (ostream::flags() & ostream::Dec) {
			len = put_decimal(buf, val, false);
		}
		else if (ostream::flags() & ostream::Hex) {
			len = put_hex(buf, val);
		}
		else if (ostream::flags() & ostream::Bin) {
			len = put_binary(buf, val);
		}

		put_fill(buf, len);

		set_buffer(buf);
		flush();

		return *this;
	}

	ostream& ostream::operator<<(s64 val)
	{
		char buf[256 + 64 + 1];
		u32 len = 0;

		if (ostream::flags() & ostream::Dec) {
			len = put_decimal(buf, val < 0 ? -val : val, val < 0);
		}
		else if (ostream::flags() & ostream::Hex) {
			len = put_hex(buf, val);
		}
		else if (ostream::flags() & ostream::Bin) {
			len = put_binary(buf, val);
		}

		put_fill(buf, len);

		set_buffer(buf);
		flush();

		return *this;
	}

	static void strrev(char* str)
	{
		size_t len = strlen(str);
		for (size_t i = 0, j = len - 1; i < j; i++, j--)
		{
			char tmp = str[i];
			str[i] = str[j];
			str[j] = tmp;
		}
	}


	// Converts an int to a string and returns the string length
	template<typename _Int>
	static int int_to_str(_Int value, char* str)
	{
		if (value == 0)
		{
			str[0] = '0';
			str[1] = '\0';
			return 1;
		}

		size_t spos = 0;
		bool neg = value < 0;
		if (neg) value = -value;

		for (; value != 0; value /= 10)
			str[spos++] = '0' + value % 10;

		str[spos] = '\0';
		strrev(str);

		return spos;
	}

	/*
		To get the whole part just shift 12 bits to the right.

		To get the fractional part, let's take 0x1842 for example:

		0x1842 / 0x1000 = 1.51611328125 @ Calculated with floats as reference
		0x842 * 10 = 0x5[294]
		0x294 * 10 = 0x1[9C8]
		0x9C8 * 10 = 0x6[1D0]
					   ^
		This is the fractional part.

		num: the fixed point number to convert
		decs: how many decimals to display (-1 = minimum)
		dec_bits: how many bits the fixed point uses for decimals
		str: the the pointer to the output string buffer
	*/
	template<typename _Int>
	static void fx_to_str(_Int num, size_t decs, size_t dec_bits, char* str)
	{
		typedef typename std::make_unsigned<_Int>::type _UInt;

		size_t spos = 0;

		_Int one = 1LL << dec_bits;
		_UInt dec_mask = one - 1;

		_Int whole = num / one;
		_UInt fract = ((num < 0) ? -num : num) & dec_mask;

		if (num < 0)
			str[spos++] = '-';

		spos += int_to_str(whole, &str[spos]);
		if (decs == 0 || (decs == -1 && fract == 0))
		{
			str[spos] = '\0';
			return;
		}

		str[spos++] = '.';

		// Parse the fractionary part
		size_t fcount = 0;
		_UInt fnext = fract;
		while (fnext != 0 && fcount != decs)
		{
			_UInt fnum = fnext * 10;
			_UInt fwhole = fnum >> dec_bits;
			fnext = fnum & dec_mask;
			str[spos++] = '0' + fwhole;
			fcount++;
		}

		if (decs != -1 && fcount < decs)
		{
			for (size_t i = fcount; i < decs; i++)
				str[spos++] = '0';
		}

		str[spos] = '\0';
	}

	ostream& ostream::operator<<(const Fx16& fx)
	{
		char buf[16];
		fx_to_str<s32>(fx, -1, 12, buf);
		return *this << (const char*)buf;
	}

	ostream& ostream::operator<<(const Fx32& fx)
	{
		char buf[21];
		fx_to_str<s32>(fx, 4, 12, buf);
		return *this << (const char*)buf;
	}

	ostream& ostream::operator<<(const Fx64& fx)
	{
		char buf[31];
		fx_to_str<s64>(fx, -1, 12, buf);
		return *this << (const char*)buf;
	}

	ostream& ostream::operator<<(const Fx64c& fx)
	{
		char buf[45];
		fx_to_str<s64>(fx, -1, 32, buf);
		return *this << (const char*)buf;
	}

}
