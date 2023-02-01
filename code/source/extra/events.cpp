#include "nitro/types.h"
#include "nsmb/stage/misc.h"

namespace Event
{
	constexpr bool isValid(u32 id)
	{
		return id != 0 && id < 64;
	}

	bool isActive(u32 id)
	{
		if (isValid(id))
		{
			return (Stage::events >> (id-1)) & 1;
		}
		return false;
	}

	void activate(u32 id)
	{
		if (isValid(id) && !isActive(id))
		{
			Stage::events |= 1LL << (id-1);
		}
	}

	void deactivate(u32 id)
	{
		if (isActive(id))
		{
			Stage::events &= ~(1LL << (id-1));
		}
	}
}
