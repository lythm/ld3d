#include "ogl4graphics_pch.h"

#include "OGL4Graphics.h"
#include "OGL4Loader.h"


namespace ld3d
{

	std::function<void (const std::wstring& log)>			g_logger;
}
EXPORT_C_API ld3d::Sys_Graphics* CreateSys(const std::function<void (const std::wstring& log)>& logger)
{
	ld3d::g_logger = logger;
	return new ld3d::OGL4Graphics;
}

EXPORT_C_API void DestroySys(ld3d::Sys_Graphics* pSys)
{
	delete (ld3d::OGL4Graphics*)pSys;
}




namespace ld3d
{
	OGL4Graphics::OGL4Graphics(void)
	{
	}


	OGL4Graphics::~OGL4Graphics(void)
	{
	}
	const GraphicsSetting& OGL4Graphics::GetGraphicsSetting()
	{
		return m_setting;
	}

	bool OGL4Graphics::Initialize(const GraphicsSetting& setting)
	{
		m_pLoader = std::make_shared<OGL4Loader>();

		if(m_pLoader->Load() == false)
		{
			return false;
		}




		return true;
	}
	void OGL4Graphics::Release()
	{


		m_pLoader->Unload();
		m_pLoader.reset();
	}

	void OGL4Graphics::SetPrimitiveType(PRIMITIVE_TYPE pt)
	{
	}
	void OGL4Graphics::DrawIndexed(int count, int startindex, int basevertex)
	{
	}
	void OGL4Graphics::Draw(int vertexCount, int baseVertex)
	{
	}
	void OGL4Graphics::ClearRenderTarget(RenderTargetPtr pTarget, int index, const math::Color4& clr)
	{
	}
	void OGL4Graphics::ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, CLEAR_DS_FLAG flag, float d, int s)
	{
	}
	void OGL4Graphics::Present()
	{
	}

	void OGL4Graphics::VSSetConstantBuffer(GPUBufferPtr pBuffer)
	{
	}
	void OGL4Graphics::PSSetConstantBuffer(GPUBufferPtr pBuffer)
	{
	}
	void OGL4Graphics::SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type)
	{
	}
	void OGL4Graphics::SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride)
	{
	}
	GPUBufferPtr OGL4Graphics::CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic)
	{
		return GPUBufferPtr();
	}
	MaterialPtr	OGL4Graphics::CreateMaterialFromFile(const char* szFile)
	{
		return MaterialPtr();
	}

	TexturePtr OGL4Graphics::CreateTextureFromFile(const char* szFile)
	{
		return TexturePtr();
	}
	void OGL4Graphics::SetRenderTarget(RenderTargetPtr pRT)
	{
	}
	TexturePtr OGL4Graphics::CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h)
	{
		return TexturePtr();
	}
		
	RenderTargetPtr	OGL4Graphics::CreateRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls)
	{
		return RenderTargetPtr();
	}
	DepthStencilBufferPtr OGL4Graphics::CreateDepthStencilBuffer(int w, int h, G_FORMAT format)
	{
		return DepthStencilBufferPtr();
	}

	void OGL4Graphics::ResizeFrameBuffer(int cx, int cy)
	{
	}

	RenderStatePtr OGL4Graphics::CreateRenderState()
	{
		return RenderStatePtr();
	}
	void OGL4Graphics::SetRenderState(RenderStatePtr pState)
	{
	}
	RenderWindowPtr OGL4Graphics::CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed)
	{
		return RenderWindowPtr();
	}
	void OGL4Graphics::SetRenderWindow(RenderWindowPtr pWnd)
	{
	}
	RenderTargetPtr	OGL4Graphics::GetDefaultRenderTarget()
	{
		return RenderTargetPtr();
	}
	RenderTargetPtr	OGL4Graphics::GetCurrentRenderTarget()
	{
		return RenderTargetPtr();
	}
	int	OGL4Graphics::GetFrameBufferWidth()
	{
		return 0;
	}
	int	OGL4Graphics::GetFrameBufferHeight()
	{
		return 0;
	}
	void OGL4Graphics::SetViewPort(int x, int y, int w, int h)
	{
	}
	VertexShaderPtr	OGL4Graphics::CreateVSFromFile(const char* szFile)
	{
		return VertexShaderPtr();
	}
	PixelShaderPtr OGL4Graphics::CreatePSFromFile(const char* szFile)
	{
		return PixelShaderPtr();
	}
	void OGL4Graphics::SetPixelShader(PixelShaderPtr pShader)
	{
	}
	void OGL4Graphics::SetVertexShader(VertexShaderPtr pShader)
	{
	}
}
