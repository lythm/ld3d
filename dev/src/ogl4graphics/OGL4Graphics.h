#pragma once

#include "core\Sys_Graphics.h"

namespace ld3d
{
	class OGL4Graphics : public Sys_Graphics2
	{
	public:
		OGL4Graphics(void);
		virtual ~OGL4Graphics(void);


		void									ClearRenderTarget(int index, const math::Color4& clr);
		void									ClearDepthStencil(CLEAR_DS_FLAG flag, float d, int s); 
		void									Present();

		const GraphicsSetting&					GetGraphicsSetting();

		bool									Initialize(const GraphicsSetting& setting);
		void									Release();
		RenderWindow2Ptr						CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		
		RenderTexture2Ptr						CreateRenderTexture(int w, int h, G_FORMAT format);
		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);
		Texture2Ptr								CreateTexture1D(G_FORMAT format, int l);
		Texture2Ptr								CreateTexture2D(G_FORMAT format, int w, int h);
		Texture2Ptr								CreateTexture3D(G_FORMAT format, int w, int h, int d);

		ShaderProgramPtr						CreateShaderProgram();
		GeometryDataPtr							CreateGeometryData();

		void									SetShaderProgram(ShaderProgramPtr pProg);
		void									Draw(GeometryDataPtr pData, int vertexCount, int baseVertex);
		void									DrawIndexed(GeometryDataPtr pData, int count, int startindex, int basevertex);

		void									SetViewPort(int x, int y, int w, int h);

		void									SetRenderTargets(const std::vector<RenderTarget2Ptr>& targets);
		void									SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer);

		Texture2Ptr								CreateTextureFromFile(const char* szFile);

		//////////////////////////


		MaterialPtr								CreateMaterialFromFile(const char* szFile);

		

		DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, int h, G_FORMAT format);

		void									ResizeFrameBuffer(int cx, int cy);

		RenderStatePtr							CreateRenderState();
		void									SetRenderState(RenderStatePtr pState);
		
		RenderTargetPtr							GetDefaultRenderTarget();
		RenderTargetPtr							GetCurrentRenderTarget();
		int										GetFrameBufferWidth();
		int										GetFrameBufferHeight();

		

	private:
		GraphicsSetting							m_setting;

		OGL4LoaderPtr							m_pLoader;

		OGL4RenderWindowPtr						m_pMainRW;
	};
}
