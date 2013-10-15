#pragma once
#include "core/Light.h"

namespace ld3d
{

	class _DLL_CLASS SpotLight : public Light
	{
	public:
		SpotLight(void);
		virtual ~SpotLight(void);

		bool							Create(RenderManagerPtr pRenderManager);
		const float&					GetAngle();
		void							SetAngle(const float& angle);

		const float&					GetRange();
		void							SetRange(const float& range);

		void							Release();
	
		void							RenderLight(RenderManagerPtr pRenderManager);

		void							SetWorldTM(const math::Matrix44& world);

		void							SetTexture(TexturePtr pTex);
		TexturePtr						GetTexture();

		bool							IsAffecting(const ViewFrustum& frustum);
	private:
		void							UpdateLightVolume();
		void							UpdateLightProjMatrix();
	private:
		float							m_angle;
		float							m_range;

		GeometryDataPtr					m_pGeometry;
		int								m_nVerts;

		MaterialPtr						m_pMaterial;

		math::Matrix44					m_modifiedTM;
		math::Matrix44					m_projTM;

		TexturePtr						m_pTexture;

	};

}