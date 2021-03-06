#include "core_pch.h"
#include "core/PointLight.h"
#include "core/MeshUtil.h"
#include "core/Sys_Graphics.h"
#include "core/GeometryData.h"
#include "core_utils.h"
#include "core/Material.h"
#include "core/RenderManager.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	PointLight::PointLight(void) : Light(LT_POINTLIGHT)
	{
		m_radius				= 20.0f;
		m_fallout				= 1.0f;
		m_nVerts				= 0;
		m_modifiedWorldTM.MakeIdentity();

	}


	PointLight::~PointLight(void)
	{
	}
	const float& PointLight::GetRadius()
	{
		return m_radius;
	}
	void PointLight::SetRadius(float r)
	{
		m_radius = r;
	}

	const float& PointLight::GetFallout()
	{
		return m_fallout;
	}
	void PointLight::SetFallout(float f)
	{
		m_fallout = f;
	}
	bool PointLight::Create(RenderManagerPtr pRenderManager)
	{
		math::Vector3* pPos = MeshUtil::CreateSphere(1, 15, 15, m_nVerts);
		m_pGeometry = pRenderManager->CreateGeometryData();

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pGeometry->BeginGeometry(PT_TRIANGLE_STRIP);
		{
			m_pGeometry->AllocVertexBuffer(m_nVerts * sizeof(math::Vector3), pPos, false, layout);
		}
		m_pGeometry->EndGeometry();

		mem_free(pPos);

		
	/*	math::Vector3* pPos = MeshUtil::CreateCube(2, m_nVerts);
		m_pGeometry = pRenderManager->CreateGeometryData();

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pGeometry->AllocVertexBuffer(m_nVerts * sizeof(math::Vector3), pPos, false, layout);
		}
		m_pGeometry->EndGeometry();

		mem_free(pPos);*/
		

		
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_point_light.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}
		
		return true;
	}
	
	void PointLight::RenderLight(RenderManagerPtr pRenderManager)
	{
		using namespace math;

		struct PointLightParam
		{
			Vector3			color;
			float			intensity;
			float			radius;
		};

		PointLightParam l;
		
		l.intensity = GetIntensity();
		const math::Color4& diffClr = GetDiffuseColor();
		l.color = math::Vector3(diffClr.r, diffClr.g, diffClr.b);
		l.radius = GetRadius();
		
		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("light");

		pParam->SetParameterBlock(&l, sizeof(PointLightParam));

		pRenderManager->SetGBuffer(m_pMaterial);

		DrawLightVolumn(pRenderManager);
	}
	void PointLight::DrawLightVolumn(RenderManagerPtr pRenderManager)
	{
		const math::Matrix44& world = GetWorldTM();

		pRenderManager->SetMatrixBlock(m_pMaterial, world);

		pRenderManager->ClearDepthBuffer(CLEAR_STENCIL, 1.0f, 0);
		
		Sys_GraphicsPtr pGraphics = pRenderManager->GetSysGraphics();

		int nPass = m_pMaterial->Begin();
		for(int i = 0; i < nPass; ++i)
		{
			m_pMaterial->ApplyPass(i);
			pGraphics->Draw(m_pGeometry, m_nVerts, 0);
		}
		m_pMaterial->End();
	}
	
	void PointLight::Release()
	{
		_release_and_reset(m_pMaterial);

		_release_and_reset(m_pGeometry);
		
	}
	const math::Matrix44& PointLight::GetWorldTM()
	{
		m_modifiedWorldTM = Light::GetWorldTM();

		m_modifiedWorldTM.SetScale(math::Vector3(m_radius, m_radius, m_radius));

		return m_modifiedWorldTM;
	}
	bool PointLight::IsAffecting(const math::ViewFrustum& frustum)
	{
		math::Vector3 pos = GetWorldTM().GetRow3(3);

		math::Sphere sphere(pos, m_radius);

		return frustum.IntersectSphere(sphere);
	}
}
