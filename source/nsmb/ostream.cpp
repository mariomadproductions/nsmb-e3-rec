#include "nsmb/ostream.hpp"

ostream cout;

ostream& operator<<(ostream& os, const char* char_ptr)
{
	bool end = false;
	for (int i = 0; i < 120; i++)
	{
		if (!end)
		{
			if ((ostream::buffer_arr_char[i] = char_ptr[i]) == '\0') end = true;
		}
		else
			ostream::buffer_arr_char[i] = '\0'; // fill the rest of the buffer with zeroes
	}
	ostream::stream_buffer(0);

	return os;
}

ostream& operator<<(ostream& os, uint32_t val)
{
	ostream::buffer_arr_u32[0] = 0x25307225; // ascii for %r0%

	for (int i = 1; i < 30; i++) ostream::buffer_arr_u32[i] = 0;

	ostream::stream_buffer(val);

	return os;
}

ostream& operator<<(ostream& os, uint64_t val)
{
	ostream::buffer_arr_u32[0] = 0x25317225; // ascii for %r1%
	ostream::buffer_arr_u32[1] = 0x25307225; // ascii for %r0%

	for (int i = 2; i < 30; i++) ostream::buffer_arr_u32[i] = 0;

	ostream::stream_buffer(val);

	return os;
}