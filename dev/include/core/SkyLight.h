#pragma once

#include "core\Light.h"

namespace ld3d
{
	class EXPORT_CLASS SkyLight : public Light
	{
	public:
		SkyLight(void);
		virtual ~SkyLight(void);

		bool								Create(RenderSystemPtr pRs);
		void								Release();
		void								RenderLight(RenderSystemPtr pRenderer);

		void								RenderShadowMap();
	private:
		bool								CreateShadowMap(int w, int h, G_FORMAT format);

	private:

		math::Vector3						m_dir;
		math::Color4						m_diff;

		MaterialPtr							m_pMaterial;

		RenderTargetPtr						m_pShadowMap;
	};


}