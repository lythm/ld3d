#pragma once

#include "core/PostEffect.h"
namespace ld3d
{
	class _DLL_CLASS PostEffect_FXAA : public PostEffect
	{
	public:
		PostEffect_FXAA(void);
		virtual ~PostEffect_FXAA(void);

		bool									Initialize(RenderManagerPtr pRenderManager);
		void									Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput);
		void									Release();	


	private:
		MaterialPtr								m_pMaterial;
		MaterialParameterPtr					m_pSrcImage;
	};


}