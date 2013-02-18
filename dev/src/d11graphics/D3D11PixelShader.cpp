#include "d11graphics_pch.h"
#include "D3D11PixelShader.h"

namespace ld3d
{

	D3D11PixelShader::D3D11PixelShader(ID3D11Device* pDevice)
	{
		m_pDevice = pDevice;
	}


	D3D11PixelShader::~D3D11PixelShader(void)
	{
	}
	bool D3D11PixelShader::LoadFromFile(const char* szFile)
	{
		ID3D10Blob* pBlob = NULL;
		ID3D10Blob* pErrorBlob = NULL;

		if(FAILED(D3DX11CompileFromFileA(szFile, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &pBlob, &pErrorBlob, nullptr)))
		{
			return false;
		}

		if(FAILED(m_pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, & m_pShader)))
		{
			return false;
		}
		
		return true;
	}
	void D3D11PixelShader::Release()
	{
		if(m_pShader)
		{
			m_pShader->Release();
			m_pShader = nullptr;
		}
		m_pDevice = nullptr;
	}
	ID3D11PixelShader*	D3D11PixelShader::GetD3D11Shader()
	{
		return m_pShader;
	}
}

