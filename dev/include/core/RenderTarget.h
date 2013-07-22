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
		enum TARGET_TYPE
		{
			RENDER_TEXTURE,
			RENDER_WINDOW,
		};
		virtual void											Release()														= 0;
		

		TARGET_TYPE												GetType(){return m_type;}


		RenderTarget2(TARGET_TYPE type){m_type = type;}
		virtual ~RenderTarget2(void){}

	protected:
		TARGET_TYPE												m_type;
	};
}
