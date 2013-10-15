#pragma once

#include "core/Light.h"

namespace ld3d
{
	class _DLL_CLASS SkyLight : public Light
	{
	public:
		SkyLight(void);
		virtual ~SkyLight(void);

		bool								Create(RenderManagerPtr pRenderManager);
		void								Release();
		void								RenderLight(RenderManagerPtr pRenderer);

		void								RenderShadowMap();
	private:
		bool								CreateShadowMap(int w, int h, G_FORMAT format);

	private:

		math::Vector3						m_dir;
		math::Color4						m_diff;

		MaterialPtr							m_pMaterial;
		RenderTexturePtr					m_pShadowMap;

		RenderManagerPtr					m_pRenderManager;
	};


}
