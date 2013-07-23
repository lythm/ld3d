#pragma once

#include "math/math_all.h"

#include "core/g_format.h"
#include "core/VertexFormat.h"
namespace ld3d
{
	class Sys_Graphics
	{
	public:

		virtual bool									Initialize(const GraphicsSetting& setting)										= 0;
		virtual void									Release()																		= 0;
		
		virtual RenderWindowPtr							CreateRenderWindow(void* handle, 
																	int w, 
																	int h, 
																	G_FORMAT color_format, 
																	G_FORMAT ds_format, 
																	int backbufferCount, 
																	int multiSampleCount, 
																	int multiSampleQuality, 
																	bool windowed)														= 0;
		virtual RenderTexturePtr						CreateRenderTexture()															= 0;
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
		virtual void									Draw(PRIMITIVE_TYPE prim, 
																	GPUBufferPtr pVertexBuffer, 
																	int vertexCount, 
																	int baseVertex, 
																	int bufferOffset, 
																	const VertexLayout& layout)											= 0;
		virtual void									DrawIndexed(PRIMITIVE_TYPE prim, 
																	GPUBufferPtr pVertexBuffer, 
																	GPUBufferPtr pIndexBuffer, 
																	G_FORMAT indexType, 
																	int count, 
																	int startindex, 
																	int basevertex, 
																	int vbOffset, 
																	const VertexLayout& layout)											= 0;
		virtual void									SetViewPort(int x, int y, int w, int h)											= 0;


		virtual void									SetRenderTarget(RenderTargetPtr pTarget)										= 0;

		virtual TexturePtr								CreateTexture1D(G_FORMAT format, int l, int lvls, bool dynamic)					= 0;
		virtual TexturePtr								CreateTexture2D(G_FORMAT format, int w, int h, int lvls, bool dynamic)			= 0;
		virtual TexturePtr								CreateTexture3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic)	= 0;

		virtual TexturePtr								CreateTextureFromFile(const char* szFile, bool dynamic)							= 0;

		virtual SamplerStatePtr							CreateSampler()																	= 0;

		virtual DepthStencilBufferPtr					CreateDepthStencilBuffer(G_FORMAT format, int w, int h)							= 0;

		virtual RenderStatePtr							CreateRenderState()																= 0;
		virtual void									SetRenderState(RenderStatePtr pState)											= 0;
		
		virtual int										GetFrameBufferWidth()															= 0;
		virtual int										GetFrameBufferHeight()															= 0;

		virtual void									OnResizeRenderWindow(int cx, int cy)											= 0;
		
	protected:
		Sys_Graphics(void){}
		virtual ~Sys_Graphics(void){}
	};
}
