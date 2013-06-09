#include "core_pch.h"
#include "..\..\include\core\PointLight.h"
#include "core\MeshUtil.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"
#include "core_utils.h"
#include "core\Material.h"
#include "core\RenderManager.h"
namespace ld3d
{
	PointLight::PointLight(void) : Light(LT_POINTLIGHT)
	{
		m_radius				= 10.0f;
		m_fallout				= 1.0f;
		m_nVerts				= 0;
		m_modifiedWorldTM.MakeIdentity();

	}


	PointLight::~PointLight(void)
	{
	}
	float PointLight::GetRadius()
	{
		return m_radius;
	}
	void PointLight::SetRadius(float r)
	{
		m_radius = r;
	}

	float PointLight::GetFallout()
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
		m_pVB = pRenderManager->CreateBuffer(BT_VERTEX_BUFFER, m_nVerts * sizeof(math::Vector3), pPos, false);
		mem_free(pPos);

		if(m_pVB == GPUBufferPtr())
		{
			return false;
		}

		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_point_light.fx");
		if(m_pMaterial == MaterialPtr())
		{
			return false;
		}
		VertexFormat vf;
		vf.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		m_pMaterial->SetVertexFormat(vf);

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
		

		m_pMaterial->SetCBByName("light", &l, sizeof(PointLightParam));
		m_pMaterial->SetGBuffer(pRenderManager->GetGBuffer());
		DrawLightVolumn(pRenderManager);
	}
	void PointLight::DrawLightVolumn(RenderManagerPtr pRenderManager)
	{
		const math::Matrix44& view = pRenderManager->GetViewMatrix();
		const math::Matrix44& proj = pRenderManager->GetProjMatrix();
		const math::Matrix44& world = GetWorldTM();

		m_pMaterial->SetWorldMatrix(world);
		m_pMaterial->SetViewMatrix(view);
		m_pMaterial->SetProjMatrix(proj);

		m_pMaterial->ApplyVertexFormat();
		
		pRenderManager->ClearDepthBuffer(DepthStencilBufferPtr(), CLEAR_STENCIL, 1.0f, 0);
		
		Sys_GraphicsPtr pGraphics = pRenderManager->GetSysGraphics();
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_STRIP);
		
		int nPass = 0;
		m_pMaterial->Begin(nPass);
		for(int i = 0; i < nPass; ++i)
		{
			m_pMaterial->ApplyPass(i);
			pGraphics->Draw(m_nVerts, 0);
		}
		m_pMaterial->End();
	}
	
	void PointLight::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
	const math::Matrix44& PointLight::GetWorldTM()
	{
		m_modifiedWorldTM = math::MatrixScale(math::Vector3(m_radius, m_radius, m_radius)) * Light::GetWorldTM();
		return m_modifiedWorldTM;
	}
}
