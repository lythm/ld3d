#include "core_pch.h"
#include "Time64.h"

namespace ld3d
{
	Time64::Time64(void)
	{
	}
	
	Time64::~Time64(void)
	{
	}

	uint64 Time64::_get_tick()
	{
		return (uint64)GetTickCount64();
	}
}
