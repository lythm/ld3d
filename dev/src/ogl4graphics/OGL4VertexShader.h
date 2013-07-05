#pragma once

#include "core\VertexShader.h"
namespace ld3d
{
	class OGL4VertexShader : public VertexShader
	{
	public:
		OGL4VertexShader(void);
		virtual ~OGL4VertexShader(void);

		void												Release();
	};


}