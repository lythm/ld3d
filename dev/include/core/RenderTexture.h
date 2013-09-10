#pragma once

#include "core/RenderTarget.h"

namespace ld3d
{
	class RenderTexture : public RenderTarget
	{
	public:
		virtual void														Release()													= 0;

		virtual int															GetTextureCount()											= 0;
		virtual void														AttachTexture(TexturePtr pTex)								= 0;

		virtual TexturePtr													GetTexture(int index)										= 0;

		virtual void														SetDepthStencilBuffer(DepthStencilBufferPtr pDS)			= 0;
		virtual DepthStencilBufferPtr										GetDepthStencilBuffer()										= 0;

	protected:
		RenderTexture() : RenderTarget(RENDER_TEXTURE){}
		virtual ~RenderTexture(){}
	};
}