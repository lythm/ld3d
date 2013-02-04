#pragma once

#include "core\PostEffect.h"

namespace ld3d
{
	class EXPORT_CLASS PostEffect_GaussianBlur : public PostEffect
	{
	public:
		PostEffect_GaussianBlur(void);
		virtual ~PostEffect_GaussianBlur(void);


		bool									Initialize(RenderManagerPtr pRenderManager);
		void									Render(RenderManagerPtr pRenderer, RenderTargetPtr pInput, RenderTargetPtr pOutput);
		void									Release();

	private:
		MaterialPtr								m_pMaterial;
		RenderManagerPtr							m_pRenderManager;
	};


}
