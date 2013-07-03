#include "ogl4graphics_pch.h"

#include "OGL4Graphics.h"
#include "OGL4Loader.h"
#include "OGL4RenderWindow.h"

#include "OGL4Buffer.h"

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
		m_pMainRW = std::make_shared<OGL4RenderWindow>();

		if(false == m_pMainRW->Create(setting.wnd, setting.frameBufferWidth, setting.frameBufferHeight, setting.frameBufferFormat, setting.depthStencilFormat))
		{
			m_pMainRW.reset();

			return false;
		}
		m_pMainRW->MakeCurrent();

		m_pLoader = std::make_shared<OGL4Loader>();

		if(m_pLoader->Load() == false)
		{
			return false;
		}


		
		return true;
	}
	void OGL4Graphics::Release()
	{
		if(m_pMainRW)
		{
			m_pMainRW->Release();
			m_pMainRW.reset();
		}

		if(m_pLoader)
		{
			m_pLoader->Unload();
			m_pLoader.reset();
		}
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
		m_pMainRW->Present();
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
		OGL4BufferPtr pGLBuffer = std::dynamic_pointer_cast<OGL4Buffer>(pBuffer);
		if(pGLBuffer == nullptr)
		{
			return;
		}

		pGLBuffer->Bind();
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 
	}
	GPUBufferPtr OGL4Graphics::CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic)
	{
		OGL4BufferPtr pBuffer = std::make_shared<OGL4Buffer>();
		if(pBuffer->Create(type, bytes, pInitData, dynamic) == false)
		{
			pBuffer.reset();

		}
		return pBuffer;
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
		m_pMainRW->Resize(cx, cy);
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
		OGL4RenderWindowPtr pWnd = std::make_shared<OGL4RenderWindow>();
		if(pWnd->Create(handle, w, h, color_format, ds_format) == false)
		{
			pWnd.reset();
			return RenderWindowPtr();
		}


		return pWnd;
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
