#pragma once

#include "math/math_all.h"

#include "core/g_format.h"

namespace ld3d
{
	class Sys_Graphics
	{
	public:

		virtual const GraphicsSetting&					GetGraphicsSetting()										= 0;

		virtual bool									Initialize(const GraphicsSetting& setting)					= 0;

		virtual void									Release()													= 0;
		
		virtual void									Draw(int vertexCount, int baseVertex)						= 0;
		virtual void									DrawIndexed(int count, 
																	int startindex,
																	int basevertex)									= 0;
		virtual void									SetPrimitiveType(PRIMITIVE_TYPE pt)							= 0;
		
		virtual int										GetFrameBufferWidth()										= 0;
		virtual int										GetFrameBufferHeight()										= 0;

		virtual void									ClearRenderTarget(RenderTargetPtr pTarget, 
																	int index,
																	const math::Color4& clr)						= 0; 

		virtual void									ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, 
																	CLEAR_DS_FLAG flag,
																	float d, 
																	int s)											= 0; 

		virtual void									Present()													= 0;

		virtual GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, 
																	int bytes, 
																	void* pInitData, 
																	bool dynamic)									= 0;

		virtual void									VSSetConstantBuffer(GPUBufferPtr pBuffer)					= 0;
		virtual void									PSSetConstantBuffer(GPUBufferPtr pBuffer)					= 0;

		virtual void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type)			= 0;
		virtual void									SetVertexBuffer(GPUBufferPtr pBuffer, 
																	unsigned int offset, 
																	unsigned int stride)							= 0;

		virtual TexturePtr								CreateTextureFromFile(const char* szFile)					= 0;

		virtual void									SetRenderTarget(RenderTargetPtr pRT)					= 0;

		virtual RenderTargetPtr							CreateRenderTarget(int count,
																	int w,
																	int h,
																	G_FORMAT formats[],
																	int miplvls = 1)								= 0;
		virtual DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, 
																	int h, 
																	G_FORMAT format)								= 0;

		virtual void									ResizeFrameBuffer(int cx, int cy)							= 0;

		virtual RenderWindowPtr							CreateRenderWindow(void* handle, 
																	int w, 
																	int h, 
																	G_FORMAT color_format, 
																	G_FORMAT ds_format, 
																	int backbufferCount, 
																	int multiSampleCount, 
																	int multiSampleQuality, 
																	bool windowed)									= 0;

		virtual void									SetRenderWindow(RenderWindowPtr pWnd)						= 0;

		virtual void									SetViewPort(int x, int y, int w, int h)						= 0;

		virtual RenderStatePtr							CreateRenderState()											= 0;
		virtual void									SetRenderState(RenderStatePtr pState)						= 0;
	protected:
		Sys_Graphics(void){}
		virtual ~Sys_Graphics(void){}
	};

	class Sys_Graphics2
	{
	public:

		virtual bool									Initialize(const GraphicsSetting& setting)										= 0;
		virtual void									Release()																		= 0;
		
		virtual RenderWindow2Ptr						CreateRenderWindow(void* handle, 
																	int w, 
																	int h, 
																	G_FORMAT color_format, 
																	G_FORMAT ds_format, 
																	int backbufferCount, 
																	int multiSampleCount, 
																	int multiSampleQuality, 
																	bool windowed)														= 0;
		virtual RenderTexture2Ptr						CreateRenderTexture()															= 0;
		virtual void									ClearRenderTarget(int index, const math::Color4& clr)							= 0;
		virtual void									ClearDepthStencil(CLEAR_DS_FLAG flag,
																	float d, 
																	int s)																= 0; 

		virtual GeometryDataPtr							CreateGeometryData()															= 0;
		virtual GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, 
																	int bytes, 
																	void* pInitData, 
																	bool dynamic)														= 0;
		virtual void									Present()																		= 0;

		virtual ShaderProgramPtr						CreateShaderProgram()															= 0;

		virtual void									SetShaderProgram(ShaderProgramPtr pProg)										= 0;

		virtual void									Draw(GeometryDataPtr pData,  
																	int vertexCount, 
																	int baseVertex)														= 0;

		virtual void									DrawIndexed(GeometryDataPtr pData,
																	int count, 
																	int startindex,
																	int basevertex)														= 0;

		virtual void									SetViewPort(int x, int y, int w, int h)											= 0;


		virtual void									SetRenderTarget(RenderTarget2Ptr pTarget)										= 0;

		virtual Texture2Ptr								CreateTexture1D(G_FORMAT format, int l, int lvls, bool dynamic)					= 0;
		virtual Texture2Ptr								CreateTexture2D(G_FORMAT format, int w, int h, int lvls, bool dynamic)			= 0;
		virtual Texture2Ptr								CreateTexture3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic)	= 0;

		virtual Texture2Ptr								CreateTextureFromFile(const char* szFile, bool dynamic)							= 0;

		virtual SamplerStatePtr							CreateSampler()																	= 0;

		virtual DepthStencilBufferPtr					CreateDepthStencilBuffer(G_FORMAT format, int w, int h)							= 0;

		virtual RenderState2Ptr							CreateRenderState()																= 0;
		virtual void									SetRenderState(RenderState2Ptr pState)											= 0;
		/////////////////////////////////////////////////////////////////


		virtual int										GetFrameBufferWidth()															= 0;
		virtual int										GetFrameBufferHeight()															= 0;

		virtual void									ResizeFrameBuffer(int cx, int cy)												= 0;
		
		
	protected:
		Sys_Graphics2(void){}
		virtual ~Sys_Graphics2(void){}
	};
}
