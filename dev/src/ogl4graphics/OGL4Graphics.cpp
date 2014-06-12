#include "ogl4graphics_pch.h"

#include "OGL4Graphics.h"
#include "OGL4Loader.h"

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
#include "OGL4RenderTexture.h"

#ifdef __APPLE__
#include "OGL4RenderWindow_osx.h"
#endif

#if defined(_WIN64) || defined(_WIN32)
#include "ogl4graphics_win/OGL4RenderWindow.h"
#endif
namespace ld3d
{

	Logger												g_logger;

	Logger& logger()
	{
		return g_logger;
	}
	

#if 1
//#ifdef _DEBUG
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


		logger() << str.str();

		return ;
	}

#define _ENABLE_GL_DEBUG_	glDebugMessageCallback(_DebugCallback, NULL);glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#else
#define _ENABLE_GL_DEBUG_	0;
#endif


}
_DLL_API ld3d::Sys_Graphics* CreateSys(ld3d::Logger& logger)
{
	ld3d::g_logger = logger;
	return new ld3d::OGL4Graphics;
}

_DLL_API void DestroySys(ld3d::Sys_Graphics* pSys)
{
	delete (ld3d::OGL4Graphics*)pSys;
}




namespace ld3d
{


	OGL4Graphics::OGL4Graphics(void)
	{
		m_viewPortX			= 0;
		m_viewPortY			= 0;
		m_viewPortW			= 0;
		m_viewPortH			= 0;
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

		if(setting.windowed == false)
		{
			m_pMainRW->Resize(setting.frameBufferWidth, setting.frameBufferHeight, true);
		}

		m_pMainRW->MakeCurrent();

		m_viewPortX = 0;
		m_viewPortY = 0;
		m_viewPortW = setting.frameBufferWidth;
		m_viewPortH = setting.frameBufferHeight;

		m_pLoader = std::make_shared<OGL4Loader>();

		if(m_pLoader->Load() == false)
		{
			return false;
		}

		m_pMainRW->EnableVSync(setting.vsync);

		_ENABLE_GL_DEBUG_;


		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		m_pCurrentRW = m_pMainRW;

		m_setting = setting;
		return true;
	}
	void OGL4Graphics::Release()
	{
		_release_and_reset(m_pMainRW);

		if(m_pLoader)
		{
			m_pLoader->Unload();
			m_pLoader.reset();
		}
	}

	void OGL4Graphics::Draw(PRIMITIVE_TYPE prim, GPUBufferPtr pVertexBuffer, int vertexCount, int baseVertex, int bufferOffset, const VertexLayout& layout)
	{
		glBindVertexArray(0);
		OGL4Buffer* pBuffer = (OGL4Buffer*)pVertexBuffer.get();

		unsigned int stride = layout.VertexStride();

		glBindBuffer(GL_ARRAY_BUFFER, pBuffer->GetBufferObject());

		unsigned int offset = 0;
		for(unsigned int i = 0; i < layout.AttrCount(); ++i)
		{
			glEnableVertexAttribArray(i);

			G_FORMAT type = layout.AttrType(i);

			unsigned int value_count = 0;
			GLenum gltype = GL_INVALID_ENUM;

			if(OGL4Convert::FormatToGLVertexAttr(type, value_count, gltype) == false)
			{
				assert(0);
			}

			glVertexAttribPointer(i, value_count, gltype, GL_FALSE, stride, (GLvoid*)(bufferOffset + offset));

			offset += layout.TypeBytes(type);
		}

		glDrawArrays(prim, baseVertex, vertexCount);
	}
	void OGL4Graphics::DrawIndexed(PRIMITIVE_TYPE prim, GPUBufferPtr pVertexBuffer,GPUBufferPtr pIndexBuffer, G_FORMAT indexType, int count, int startindex, int basevertex, int vbOffset, const VertexLayout& layout)
	{
		OGL4Buffer* pVB = (OGL4Buffer*)pVertexBuffer.get();

		unsigned int stride = layout.VertexStride();

		glBindBuffer(GL_ARRAY_BUFFER, pVB->GetBufferObject());

		unsigned int offset = 0;
		for(unsigned int i = 0; i < layout.AttrCount(); ++i)
		{
			glEnableVertexAttribArray(i);

			G_FORMAT type = layout.AttrType(i);

			unsigned int value_count = 0;
			GLenum gltype = GL_INVALID_ENUM;

			if(false == OGL4Convert::FormatToGLVertexAttr(type, value_count, gltype))
			{
				assert(0);
			}

			glVertexAttribPointer(i, value_count, gltype, GL_FALSE, stride, (GLvoid*)(vbOffset + offset));

			offset += layout.TypeBytes(type);
		}

		OGL4Buffer* pIB = (OGL4Buffer*)pIndexBuffer.get();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIB->GetBufferObject());


		GLenum glType = GL_INVALID_ENUM;
		switch(indexType)
		{
		case G_FORMAT_R32_UINT:
			glType = GL_UNSIGNED_INT;
			break;
		case G_FORMAT_R16_UINT:
			glType = GL_UNSIGNED_SHORT;
			break;
		default:
			assert(0);
			glType = GL_UNSIGNED_SHORT;
			break;
		}


		glDrawElements(prim, count, glType, 0);
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
			glClearBufferfv(GL_DEPTH, 0, &d);
			break;
		case CLEAR_STENCIL:
			glClearBufferiv(GL_STENCIL, 0, &s);
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
	
	TexturePtr OGL4Graphics::CreateTextureFromFile(const char* szFile)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();

		if(pTex->CreateFromFile(szFile) == false)
		{
			return TexturePtr();
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
	DepthStencilBufferPtr OGL4Graphics::CreateDepthStencilBufferMS(G_FORMAT format, int w, int h, int samples)
	{
		OGL4DepthStencilBufferPtr pDS = std::make_shared<OGL4DepthStencilBuffer>();
		if(false == pDS->CreateMS(format, w, h, samples))
		{
			pDS->Release();
			pDS.reset();
		}

		return pDS;
	}

	void OGL4Graphics::OnResizeRenderWindow(int cx, int cy)
	{
		m_pCurrentRW->OnResize(cx, cy);

		m_viewPortX = 0;
		m_viewPortY = 0;
		m_viewPortW = m_pCurrentRW->GetWidth();
		m_viewPortH = m_pCurrentRW->GetHeight();

		ResetViewport();

		m_setting.frameBufferWidth	= cx;
		m_setting.frameBufferHeight = cy;
	}
	void OGL4Graphics::ResizeRenderWindow(int cx, int cy, bool fullscreen)
	{
		m_pCurrentRW->Resize(cx, cy, fullscreen);

		m_viewPortX = 0;
		m_viewPortY = 0;
		m_viewPortW = m_pCurrentRW->GetWidth();
		m_viewPortH = m_pCurrentRW->GetHeight();

		ResetViewport();

		m_setting.frameBufferWidth	= cx;
		m_setting.frameBufferHeight = cy;

		m_setting.windowed = !fullscreen;
	}
	RenderStatePtr OGL4Graphics::CreateRenderState()
	{
		OGL4RenderStatePtr pState = std::make_shared<OGL4RenderState>();

		return pState;
	}
	void OGL4Graphics::SetRenderState(RenderStatePtr pState)
	{
		OGL4RenderState* pGLState = (OGL4RenderState*)pState.get();
		pGLState? pGLState->Apply() : 0;
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

	
	int	OGL4Graphics::GetFrameBufferWidth()
	{
		return m_setting.frameBufferWidth;
	}
	int	OGL4Graphics::GetFrameBufferHeight()
	{
		return m_setting.frameBufferHeight;
	}
	void OGL4Graphics::SetViewPort(int x, int y, int w, int h)
	{
		if(w <= 0 || h <= 0)
		{
			m_viewPortX = 0;
			m_viewPortY = 0;
			m_viewPortW = m_pCurrentRW->GetWidth();
			m_viewPortH = m_pCurrentRW->GetHeight();

			glViewport(m_viewPortX, m_viewPortY, m_viewPortW, m_viewPortH);
			return;
		}
		
		m_viewPortW = w;
		m_viewPortH = h;
		
		m_viewPortX = x;
		m_viewPortY = m_pCurrentRW->GetHeight() - y;

		m_viewPortY -= m_viewPortH;

		glViewport(m_viewPortX, m_viewPortY, m_viewPortW, m_viewPortH);

	}

	RenderTexturePtr OGL4Graphics::CreateRenderTexture()
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
	void OGL4Graphics::SetRenderTarget(RenderTargetPtr pTarget)
	{
		if(pTarget && pTarget->GetType() == RenderTarget::RENDER_WINDOW)
		{
			m_pCurrentRW = std::dynamic_pointer_cast<OGL4RenderWindow>(pTarget);
			m_pCurrentRW->MakeCurrent();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			ResetViewport();
			return;
		}

		if(m_pCurrentRW != m_pMainRW)
		{
			m_pCurrentRW = m_pMainRW;
			m_pCurrentRW->MakeCurrent();
			ResetViewport();
		}

		if(pTarget == nullptr)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			m_pCurrentRT = nullptr;
			ResetViewport();
			return;
		}

		// render texture
		m_pCurrentRT = std::dynamic_pointer_cast<OGL4RenderTexture>(pTarget);

		m_pCurrentRT->Bind();

		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		ResetViewport();

	}
	
	TexturePtr OGL4Graphics::CreateTexture1D(G_FORMAT format, int l, int lvls, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create1D(format, l, lvls, dynamic) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;

	}
	TexturePtr OGL4Graphics::CreateTexture2D(G_FORMAT format, int w, int h, int lvls, bool dynamic)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create2D(format, w, h, lvls, dynamic) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;
	}
	TexturePtr OGL4Graphics::CreateTexture2DMS(G_FORMAT format, int w, int h, int samples)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create2DMS(format, w, h, samples) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;
	}
	TexturePtr OGL4Graphics::CreateTexture3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic)
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
	void OGL4Graphics::ResetViewport()
	{
		if(m_pCurrentRT)
		{
			glViewport(0, 0, m_pCurrentRT->GetTexture(0)->GetWidth(), m_pCurrentRT->GetTexture(0)->GetHeight());
			return;
		}

		glViewport(m_viewPortX, m_viewPortY, m_viewPortW, m_viewPortH);
	}
	TexturePtr OGL4Graphics::CopyTexture2D(TexturePtr pTex)
	{
		return std::shared_ptr<OGL4Texture>();
	}
	int	OGL4Graphics::GetRenderWindowWidth()
	{
		return m_pCurrentRW->GetWidth();
	}
	int OGL4Graphics::GetRenderWindowHeight()
	{
		return m_pCurrentRW->GetHeight();
	}
	bool OGL4Graphics::IsFullscreen()
	{
		return m_pCurrentRW->IsFullscreen();
	}
	const std::vector<std::string>& OGL4Graphics::GetGLExtensions()
	{
		return m_pLoader->GetExt();
	}
	TexturePtr OGL4Graphics::Create2DArrayFromFiles(const std::vector<std::string>& files)
	{
		OGL4TexturePtr pTex = std::make_shared<OGL4Texture>();
		if(pTex->Create2DArrayFromFiles(files) == false)
		{
			pTex->Release();
			pTex.reset();
		}
		return pTex;
	}
}
