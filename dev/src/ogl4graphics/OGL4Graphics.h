#pragma once

#include "core\Sys_Graphics.h"

namespace ld3d
{
	class OGL4Graphics : public Sys_Graphics
	{
	public:
		OGL4Graphics(void);
		virtual ~OGL4Graphics(void);


		const GraphicsSetting&					GetGraphicsSetting();

		bool									Initialize(const GraphicsSetting& setting);
		void									Release();

		void									SetPrimitiveType(PRIMITIVE_TYPE pt);
		void									DrawIndexed(int count, int startindex, int basevertex);
		void									Draw(int vertexCount, int baseVertex);

		void									ClearRenderTarget(RenderTargetPtr pTarget, int index, const math::Color4& clr);
		void									ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, CLEAR_DS_FLAG flag, float d, int s); 
		void									Present();

		void									VSSetConstantBuffer(GPUBufferPtr pBuffer);
		void									PSSetConstantBuffer(GPUBufferPtr pBuffer);
		void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type);
		void									SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride);

		

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		MaterialPtr								CreateMaterialFromFile(const char* szFile);

		TexturePtr								CreateTextureFromFile(const char* szFile);
		void									SetRenderTarget(RenderTargetPtr pRT);
		TexturePtr								CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h);

		
		RenderTargetPtr							CreateRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls = 1);
		DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, int h, G_FORMAT format);

		void									ResizeFrameBuffer(int cx, int cy);

		RenderStatePtr							CreateRenderState();
		void									SetRenderState(RenderStatePtr pState);
		RenderWindowPtr							CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		void									SetRenderWindow(RenderWindowPtr pWnd);
		RenderTargetPtr							GetDefaultRenderTarget();
		RenderTargetPtr							GetCurrentRenderTarget();
		int										GetFrameBufferWidth();
		int										GetFrameBufferHeight();

		void									SetViewPort(int x, int y, int w, int h);

		VertexShaderPtr							CreateVSFromFile(const char* szFile);
		PixelShaderPtr							CreatePSFromFile(const char* szFile);
		

		void									SetPixelShader(PixelShaderPtr pShader);
		void									SetVertexShader(VertexShaderPtr pShader);


	private:
		GraphicsSetting							m_setting;
	};


}