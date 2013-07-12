#pragma once

#include "core\RenderTarget.h"

namespace ld3d
{
	class RenderWindow
	{
	public:

		virtual int															GetWidth()													= 0;
		virtual int															GetHeight()													= 0;
		virtual void														Release()													= 0;
	protected:
		RenderWindow(void){}
		virtual ~RenderWindow(void){}
	};


	class RenderWindow2 : public RenderTarget2
	{
	public:

		virtual int															GetWidth()													= 0;
		virtual int															GetHeight()													= 0;
		virtual void														Release()													= 0;
	protected:
		RenderWindow2(void) : RenderTarget2(RENDER_WINDOW){}
		virtual ~RenderWindow2(void){}
	};

	class RenderTexture2 : public RenderTarget2
	{
	public:
		virtual void														Release()													= 0;
		
		virtual int															GetTextureCount()											= 0;
		virtual void														AddTexture(Texture2Ptr pTex)								= 0;

		virtual Texture2Ptr													GetTexture(int index)										= 0;

		virtual void														SetDepthStencilBuffer(DepthStencilBufferPtr pDS)			= 0;
		virtual DepthStencilBufferPtr										GetDepthStencilBuffer()										= 0;

	protected:
		RenderTexture2() : RenderTarget2(RENDER_TEXTURE){}
		virtual ~RenderTexture2(){}
	};
}
