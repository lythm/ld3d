#include "core_pch.h"
#include "..\..\include\core\DirectionalLight.h"
#include "core\Sys_Graphics.h"

#include "core\Material2.h"
#include "core\RenderManager.h"
#include "core/MaterialParameter.h"
#include "core/GeometryData.h"

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
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_directional_light.fx");

		if(m_pMaterial == nullptr)
		{
			return false;
		}

		if(m_bCastShadow)
		{

		}
		return true;
	}
	void DirectionalLight::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}
	void DirectionalLight::RenderLight(RenderManagerPtr pRenderer)
	{
		const math::Matrix44& view = pRenderer->GetViewMatrix();
		const math::Matrix44& proj = pRenderer->GetProjMatrix();


		pRenderer->UpdateMatrixBlock(m_pMaterial, math::MatrixIdentity());
		
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
		pParam->SetParameterBlock(&l, sizeof(DirLightParam));

		pRenderer->UpdateDRBuffer(m_pMaterial);
				
		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	bool DirectionalLight::CreateShadowMap()
	{
		return true;
	}
}
