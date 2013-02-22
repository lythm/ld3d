#pragma once

#include "core\Shader.h"

namespace ld3d
{
	class VertexShader : public Shader
	{
	public:


		virtual void												Release()									= 0;


	protected:
		VertexShader(void){}

		virtual ~VertexShader(void){}
	};
}
