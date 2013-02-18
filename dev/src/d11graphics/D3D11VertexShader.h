#pragma once

#include "core\VertexShader.h"

namespace ld3d
{
	class D3D11VertexShader : public VertexShader
	{
	public:
		D3D11VertexShader(ID3D11Device* pDevice);
		virtual ~D3D11VertexShader(void);

		bool								LoadFromFile(const char* szFile);
		void								Release();

		ID3D11VertexShader*					GetD3D11Shader();

	private:
		ID3D11VertexShader*					m_pShader;
		ID3D11Device*						m_pDevice;
	};


}