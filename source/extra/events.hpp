#pragma once

#include "nitro/types.h"

namespace Event
{
	bool isActive(u32 id);
	void activate(u32 id);
	void deactivate(u32 id);
}
