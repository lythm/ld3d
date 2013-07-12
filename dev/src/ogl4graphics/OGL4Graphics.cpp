#include "ogl4graphics_pch.h"

#include "OGL4Graphics.h"
#include "OGL4Loader.h"
#include "OGL4RenderWindow.h"
#include "OGL4RenderTexture.h"
#include "OGL4Texture.h"
#include "OGL4Buffer.h"
#include "OGL4ShaderProgram.h"
#include "OGL4Shader.h"
#include "OGL4GeometryData.h"
#include "OGL4Convert.h"
#include "OGL4RenderState.h"
#include <sstream>
#include "OGL4Sampler.h"
#include "OGL4DepthStencilBuffer.h"

namespace ld3d
{

	std::function<void (const std::wstring& log)>			g_logger;

	void g_log(const std::wstring& str)
	{
		if(g_logger == nullptr)
		{
			return;
		}

		g_logger(str);
	}
	void g_log(const std::string& str)
	{
		if(g_logger == nullptr)
		{
			return;
		}
		std::wstring log;
		ld3d::Unicode::ANSI_2_UTF16(str, log);
		g_logger(log);
	}

#ifdef _DEBUG
	void APIENTRY _DebugCallback(GLenum source, 
		GLenum type, 
		GLuint id,
		GLenum severity, 
		GLsizei length,
		const GLchar* message, 
		const void* userParam)
	{
		std::stringstream str;

		switch(source)
		{
		case GL_DEBUG_SOURCE_API_ARB:
			str << "OpenGL";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
			str << "Windows";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
			str << "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
			str << "Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION_ARB:
			str << "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER_ARB:
			str << "Other";
			break;
		default:
			str << "unknown";
			break;
		}
		str<< "(";

		switch(type)
		{
		case GL_DEBUG_TYPE_ERROR_ARB:
			str << "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
			str << "Deprecated behavior";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
			str << "Undefined behavior";
			break;
		case GL_DEBUG_TYPE_PORTABILITY_ARB:
			str << "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE_ARB:
			str << "Performance";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			str << "Other";
			break;
		default:
			str << "unknown";
			break;
		}
		str<< ",";
		str << id ;
		str << ",";
		switch(severity)
		{
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			str << "High";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			str << "Medium";
			break;
		case GL_DEBUG_SEVERITY_LOW_ARB:
			str << "Low";
			break;
		default :
			str << "unknown";
			break;
		}

		str << "): ";
		str << message << std::endl;


		g_log(str.str());
	}

#define _ENABLE_GL_DEBUG_	glDebugMessageCallback(_DebugCallback, NULL);glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#else
#define _ENABLE_GL_DEBUG_	0;
#endif


}
EXPORT_C_API ld3d::Sys_Graphics2* CreateSys(const std::function<void (const std::wstring& log)>& logger)
{
	ld3d::g_logger = logger;
	return new ld3d::OGL4Graphics;
}

EXPORT_C_API void DestroySys(ld3d::Sys_Graphics2* pSys)
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
	void OGL4Graphics::ClearRenderTarget(int index, const math::Color4& clr)
	{
		glClearBufferfv(GL_COLOR, index, clr.v);
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

		m_pMainRW->EnableVSync(false);

		_ENABLE_GL_DEBUG_;


		glEnable(GL_DEPTH_TEST);

		m_pCurrentRW = m_pMainRW;

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

	void OGL4Graphics::DrawIndexed(GeometryDataPtr pData, int count, int startindex, int basevertex)
	{
		OGL4GeometryData* pGLData = (OGL4GeometryData*)pData.get();

		pGLData->Bind();

		glDrawElements(pGLData->GetPrimitiveType(), count, pGLData->GetIndexType(), 0);
	}
	void OGL4Graphics::Draw(GeometryDataPtr pData, int vertexCount, int baseVertex)
	{
		OGL4GeometryData* pGLData = (OGL4GeometryData*)pData.get();

		pGLData->Bind();

		glDrawArrays(pGLData->GetPrimitiveType(), baseVertex, vertexCount);
	}
	void OGL4Graphics::ClearDepthStencil(CLEAR_DS_FLAG flag, float d, int s)
	{
		switch(flag)
		{
		case CLEAR_DEPTH:
			glClearBufferfi(GL_DEPTH, 0, d, s);
			break;
		case CLEAR_STENCIL:
			glClearBufferfi(GL_STENCIL, 0, d, s);
			break;
		case CLEAR_ALL:
			glClearBufferfi(GL_DEPTH_STENCIL, 0, d, s);
			break;
		default:
			assert(0);
			break;
		}
	}
	void OGL4Graphics::Present()
	{
		m_pMainRW->Present();
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

	Texture2Ptr OGL4Graphics::CreateTextureFromFile(const char* szFile, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();

		if(pTex->CreateFromFile(szFile, dynamic) == false)
		{
			return Texture2Ptr();
		}
		return pTex;
	}

	DepthStencilBufferPtr OGL4Graphics::CreateDepthStencilBuffer(G_FORMAT format, int w, int h)
	{
		OGL4DepthStencilBufferPtr pDS = std::make_shared<OGL4DepthStencilBuffer>();
		if(false == pDS->Create(format, w, h))
		{
			pDS->Release();
			pDS.reset();
		}

		return pDS;
	}

	void OGL4Graphics::ResizeFrameBuffer(int cx, int cy)
	{
		m_pMainRW->Resize(cx, cy);
	}

	RenderStatePtr OGL4Graphics::CreateRenderState()
	{
		OGL4RenderStatePtr pState = std::make_shared<OGL4RenderState>();

		return pState;
	}
	void OGL4Graphics::SetRenderState(RenderStatePtr pState)
	{
	}
	RenderWindow2Ptr OGL4Graphics::CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed)
	{
		OGL4RenderWindowPtr pWnd = std::make_shared<OGL4RenderWindow>();
		if(pWnd->Create(handle, w, h, color_format, ds_format) == false)
		{
			pWnd.reset();
			return RenderWindow2Ptr();
		}

		return pWnd;
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
		glViewport(x, y, w, h);
	}

	RenderTexture2Ptr OGL4Graphics::CreateRenderTexture()
	{
		OGL4RenderTexturePtr pRT = std::make_shared<OGL4RenderTexture>();

		if(pRT->Create() == false)
		{
			pRT->Release();
			pRT.reset();
		}

		return pRT;
	}

	ShaderProgramPtr OGL4Graphics::CreateShaderProgram()
	{
		OGL4ShaderProgramPtr pProg = std::make_shared<OGL4ShaderProgram>();
		if(pProg->Create() == false)
		{
			pProg->Release();
			pProg = nullptr;
		}
		return pProg;
	}

	GeometryDataPtr OGL4Graphics::CreateGeometryData()
	{
		OGL4GeometryDataPtr pGD = std::make_shared<OGL4GeometryData>();
		if(pGD->Create() == false)
		{
			pGD->Release();
			pGD = nullptr;
		}

		return pGD;
	}


	void OGL4Graphics::SetShaderProgram(ShaderProgramPtr pProg)
	{
		if(pProg == nullptr)
		{
			glUseProgram(0);
			return;
		}

		((OGL4ShaderProgram*)pProg.get())->Use();
	}
	void OGL4Graphics::SetRenderTarget(RenderTarget2Ptr pTarget)
	{
		if(pTarget && pTarget->GetType() == RenderTarget2::RENDER_WINDOW)
		{
			m_pCurrentRW = std::dynamic_pointer_cast<OGL4RenderWindow>(pTarget);
			m_pCurrentRW->MakeCurrent();

			return;
		}

		m_pCurrentRW = m_pMainRW;
		m_pCurrentRW->MakeCurrent();

		if(pTarget == nullptr)
		{
			return;
		}

		// render texture

	}
	void OGL4Graphics::SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer)
	{

	}
	Texture2Ptr OGL4Graphics::CreateTexture1D(G_FORMAT format, int l, int lvls, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create1D(format, l, lvls, dynamic) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;

	}
	Texture2Ptr OGL4Graphics::CreateTexture2D(G_FORMAT format, int w, int h, int lvls, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create2D(format, w, h, lvls, dynamic) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;
	}
	Texture2Ptr OGL4Graphics::CreateTexture3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create3D(format, w, h, d, lvls, dynamic) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;
	}
	SamplerStatePtr	OGL4Graphics::CreateSampler()
	{
		OGL4SamplerPtr pSampler = std::make_shared<OGL4Sampler>();
		if(pSampler->Create() == false)
		{
			pSampler->Release();
			pSampler.reset();
		}
		return pSampler;
	}
}
