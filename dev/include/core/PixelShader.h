#pragma once

#include "core\Shader.h"

namespace ld3d
{
	class PixelShader
	{
	public:

		virtual void																Release()								= 0;

	protected:

		PixelShader(void){}

		virtual ~PixelShader(void){}
	};


}
