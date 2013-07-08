#pragma once

#include "core/g_format.h"

namespace ld3d
{
	class Shader
	{
	public:
		
		virtual void								Release()												= 0;
	protected:

		Shader(void){}

		virtual ~Shader(void){}
	};


}
