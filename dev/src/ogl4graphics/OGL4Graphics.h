#pragma once

#include "core/Sys_Graphics.h"


namespace ld3d
{
	class OGL4Graphics : public Sys_Graphics
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
		RenderWindowPtr							CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		
		RenderTexturePtr						CreateRenderTexture();
		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		TexturePtr								CreateTexture1D(G_FORMAT format, int l, int lvls, bool dynamic);
		TexturePtr								CreateTexture2D(G_FORMAT format, int w, int h, int lvls, bool dynamic);
		TexturePtr								CreateTexture2DMS(G_FORMAT format, int w, int h, int samples);
		TexturePtr								CreateTexture3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic);
		TexturePtr								CreateTextureFromFile(const char* szFile);

		TexturePtr								CopyTexture2D(TexturePtr pTex);

		ShaderProgramPtr						CreateShaderProgram();
		GeometryDataPtr							CreateGeometryData();

		void									SetShaderProgram(ShaderProgramPtr pProg);

		void									Draw(GeometryDataPtr pData, int vertexCount, int baseVertex);
		void									DrawIndexed(GeometryDataPtr pData, int count, int startindex, int basevertex);

		void									Draw(PRIMITIVE_TYPE prim, GPUBufferPtr pVertexBuffer, int vertexCount, int baseVertex, int bufferOffset, const VertexLayout& layout);
		void									DrawIndexed(PRIMITIVE_TYPE prim, GPUBufferPtr pVertexBuffer, GPUBufferPtr pIndexBuffer, G_FORMAT indexType, int count, int startindex, int basevertex, int vbOffset, const VertexLayout& layout);

		void									SetViewPort(int x, int y, int w, int h);

		void									SetRenderTarget(RenderTargetPtr pTarget);

		SamplerStatePtr							CreateSampler();

		DepthStencilBufferPtr					CreateDepthStencilBuffer(G_FORMAT format, int w, int h);
		DepthStencilBufferPtr					CreateDepthStencilBufferMS(G_FORMAT format, int w, int h, int samples);

		RenderStatePtr							CreateRenderState();
		void									SetRenderState(RenderStatePtr pState);
		int										GetFrameBufferWidth();
		int										GetFrameBufferHeight();
	
		void									OnResizeRenderWindow(int cx, int cy);


		void									ResetViewport();
	private:
		GraphicsSetting							m_setting;

		OGL4LoaderPtr							m_pLoader;

		OGL4RenderWindowPtr						m_pMainRW;

		OGL4RenderWindowPtr						m_pCurrentRW;

		OGL4RenderTexturePtr					m_pCurrentRT;
	};
}
