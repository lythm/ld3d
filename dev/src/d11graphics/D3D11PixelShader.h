#pragma once

#include "core\PixelShader.h"

namespace ld3d
{
	class D3D11PixelShader : public PixelShader
	{
	public:
		D3D11PixelShader(void);
		virtual ~D3D11PixelShader(void);
	};


}