#pragma once

#include "core/RenderTarget.h"

namespace ld3d
{
	class OGL4RenderTexture : public RenderTarget
	{
	public:
		OGL4RenderTexture(void);
		virtual ~OGL4RenderTexture(void);


		int												GetRenderTargetCount();
		TexturePtr										AsTexture(int index);
		void											SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer);
		DepthStencilBufferPtr							GetDepthStencilBuffer();
		void											Release();
		int												GetWidth(int index);
		int												GetHeight(int index);
	};


}