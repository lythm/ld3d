#pragma once

namespace ld3d
{
	class RenderTarget
	{
	public:

		virtual int												GetRenderTargetCount()											= 0;
		virtual TexturePtr										AsTexture(int index)											= 0;
		virtual void											SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer)		= 0;
		virtual DepthStencilBufferPtr							GetDepthStencilBuffer()											= 0;
		virtual void											Release()														= 0;
		virtual int												GetWidth(int index)												= 0;
		virtual int												GetHeight(int index)											= 0;
	protected:

		RenderTarget(void){}
		virtual ~RenderTarget(void){}
	};



	class RenderTarget2
	{
	public:

		virtual void											Release()														= 0;
		virtual int												GetWidth()														= 0;
		virtual int												GetHeight()														= 0;
		
	protected:

		RenderTarget2(void){}
		virtual ~RenderTarget2(void){}
	};
}
