#pragma once


#include "core/Sys_Time.h"

namespace ld3d
{
	class Time64 : public Sys_Time
	{
	public:
		Time64(void);
		virtual ~Time64(void);

	private:
		uint64								_get_tick();
	};
}