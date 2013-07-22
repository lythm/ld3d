#pragma once

#include "core/RenderTarget.h"

namespace ld3d
{
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