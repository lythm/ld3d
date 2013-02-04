#pragma once

#include "types\types.h"


namespace ld3d
{
	class Sys_Time
	{
	public:

		virtual float								Second()										= 0;
		virtual uint64								Tick()											= 0;
		virtual void								Pause()											= 0;
		virtual void								Resume()										= 0;
		
		virtual void								Start()											= 0;
		virtual void								Stop()											= 0;
		
		virtual void								Update()										= 0;

	protected:

		Sys_Time(void)
		{
		}

		virtual ~Sys_Time(void)
		{
		}
	};


}