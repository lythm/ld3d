#include "core_pch.h"
#include "core/DirectionalLight.h"
#include "core/Sys_Graphics.h"

#include "core/Material.h"
#include "core/RenderManager.h"
#include "core/MaterialParameter.h"
#include "core/GeometryData.h"
#include "core_utils.h"

namespace ld3d
{
	DirectionalLight::DirectionalLight(void) : Light(LT_DIRLIGHT)
	{
	}


	DirectionalLight::~DirectionalLight(void)
	{
	}
	
	bool DirectionalLight::Create(RenderManagerPtr pRenderManager)
	{
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_directional_light.material");

		if(m_pMaterial == nullptr)
		{
			return false;
		}

		if(m_bCastShadow)
		{
			if(false == CreateShadowMap())
			{
				return false;
			}
		}
		return true;
	}
	void DirectionalLight::Release()
	{
		_release_and_reset(m_pMaterial);
	}
	void DirectionalLight::RenderLight(RenderManagerPtr pRenderer)
	{
		const math::Matrix44& view = pRenderer->GetViewMatrix();
		const math::Matrix44& proj = pRenderer->GetProjMatrix();


		pRenderer->SetMatrixBlock(m_pMaterial, math::MatrixIdentity());
		
		const math::Matrix44& tm = GetWorldTM();

		math::Vector3 d = tm.GetRow3(2);
		d.Normalize();

		struct DirLightParam
		{
			math::Vector3 d;
			float i;
			math::Vector3 c;
		};

		DirLightParam l;
		l.d = d;
		l.i = GetIntensity();
		const math::Color4& diffClr = GetDiffuseColor();

		l.c = math::Vector3(diffClr.r, diffClr.g, diffClr.b);

		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("light");
		pParam ? pParam->SetParameterBlock(&l, sizeof(DirLightParam)) : 0;

		pRenderer->SetGBuffer(m_pMaterial);
				
		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	bool DirectionalLight::CreateShadowMap()
	{
		return true;
	}
}
