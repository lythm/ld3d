#pragma once

#include "core\PixelShader.h"

namespace ld3d
{
	class D3D11PixelShader : public PixelShader
	{
	public:
		D3D11PixelShader(ID3D11Device* pDevice);
		virtual ~D3D11PixelShader(void);

		bool								LoadFromFile(const char* szFile);
		void								Release();

		ID3D11PixelShader*					GetD3D11Shader();

	private:
		ID3D11PixelShader*					m_pShader;
		ID3D11Device*						m_pDevice;

	};


}