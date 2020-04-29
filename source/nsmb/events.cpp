#include "nsmb/events.h"

bool isEventActive(u32 id)
{
	if (id == 0)
	return false;

	u64 *activatorBitmask = (u64*)(0x0208AF3C);
	return (*activatorBitmask >> (id-1)) & 1;
}

void activateEvent(u32 id)
{
	if(!isEventActive(id) && id != 0)
	{
		u64 event2trigger = 1;
		event2trigger = event2trigger << (id-1);
		
		u64 *activatorBitmask = (u64*)(0x0208AF3C);
		
		*activatorBitmask += event2trigger;
	}
}

void deactivateEvent(u32 id)
{
	if(isEventActive(id) && id != 0)
	{
		u64 event2trigger = 1;
		event2trigger = event2trigger << (id-1);
		
		u64 *activatorBitmask = (u64*)(0x0208AF3C);
		
		*activatorBitmask -= event2trigger;
	}
}

bool isItOdd(int value)
{
	return ((value % 2) ? 1 : 0);
}

bool isItEven(int value)
{
	return ((value % 2) ? 0 : 1);
}