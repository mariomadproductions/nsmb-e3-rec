#pragma once

#include "nitro/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

	bool isEventActive(u32 id);
	void activateEvent(u32 id);
	void deactivateEvent(u32 id);
	
	bool isItOdd(int value);
	bool isItEven(int value);

#ifdef __cplusplus
}
#endif