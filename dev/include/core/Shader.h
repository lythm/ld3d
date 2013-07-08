#pragma once

#include "core/g_format.h"

namespace ld3d
{
	class Shader
	{
	public:
		virtual SHADER_TYPE							GetType()												= 0;
		virtual void								Release()												= 0;
	protected:

		Shader(void){}

		virtual ~Shader(void){}
	};


}
