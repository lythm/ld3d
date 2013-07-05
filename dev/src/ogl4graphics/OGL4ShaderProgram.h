#pragma once

#include "core/ShaderProgram.h"

namespace ld3d
{
	class OGL4ShaderProgram : public ShaderProgram
	{
	public:
		OGL4ShaderProgram(void);
		virtual ~OGL4ShaderProgram(void);

		void												AttachShader(VertexShaderPtr pShader);
		void												AttachShader(PixelShaderPtr pShader);

		void												Release();
	};


}