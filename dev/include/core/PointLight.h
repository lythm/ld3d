#pragma once
#include "core/Light.h"

namespace ld3d
{
	class _DLL_CLASS PointLight : public Light
	{
	public:
		PointLight(void);
		virtual ~PointLight(void);


		bool					Create(RenderManagerPtr pRenderManager);

		float					GetRadius();
		void					SetRadius(float r);

		float					GetFallout();
		void					SetFallout(float f);

		const math::Matrix44&	GetWorldTM();
		void					Release();
		void					RenderLight(RenderManagerPtr pRenderManager);

	private:
		void					DrawLightVolumn(RenderManagerPtr pRenderManager);
	private:
		float					m_radius;
		float					m_fallout;
		
		GeometryDataPtr			m_pGeometry;
		int						m_nVerts;

		math::Matrix44			m_modifiedWorldTM;

		MaterialPtr			m_pMaterial;
	};
}
