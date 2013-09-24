#pragma once

#include "core/PostEffect.h"
namespace ld3d
{
	class PostEffect_FXAA : public PostEffect
	{
	public:
		PostEffect_FXAA(void);
		virtual ~PostEffect_FXAA(void);


		void									Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput);
		void									Release();	
	};


}