#include "core_pch.h"
#include "core/SpotLight.h"
#include "core/MeshUtil.h"
#include "core/Sys_Graphics.h"
#include "core_utils.h"
#include "core/GPUBuffer.h"
#include "core/Material.h"
#include "core/RenderManager.h"
#include "core/GeometryData.h"
#include "core/MaterialParameter.h"
#include "core/Texture.h"

namespace ld3d
{
	SpotLight::SpotLight(void) : Light(LT_SPOTLIGHT)
	{
		m_angle			= 40;
		m_nVerts		= 0;
		m_range			= 300;
		
		m_projTM.MakeIdentity();
		m_modifiedTM.MakeIdentity();
	}


	SpotLight::~SpotLight(void)
	{
	}
	bool SpotLight::Create(RenderManagerPtr pRenderManager)
	{
		math::Vector3* pVerts = MeshUtil::CreateSpotLightCone(m_range, m_angle, 50, m_nVerts);

		m_pGeometry = pRenderManager->CreateGeometryData();
		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			if(false == m_pGeometry->AllocVertexBuffer(sizeof(math::Vector3) * m_nVerts, pVerts, true, layout))
			{
				return false;
			}
		}
		m_pGeometry->EndGeometry();
				
		mem_free(pVerts);
		
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_spot_light.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}


		m_pTexture = pRenderManager->CreateTextureFromFile("./assets/standard/texture/001.dds");

		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("tex");

		pParam->SetParameterTexture(m_pTexture);


		UpdateLightProjMatrix();
		return true;
	}
	const float& SpotLight::GetAngle()
	{
		return m_angle;
	}
	void SpotLight::SetAngle(const float& angle)
	{
		m_angle = angle;

		UpdateLightVolume();
	}
	const float& SpotLight::GetRange()
	{
		return m_range;
	}
	void SpotLight::SetRange(const float& range)
	{
		m_range = range;
		UpdateLightVolume();

	}
	
	void SpotLight::Release()
	{
		_release_and_reset(m_pTexture);

		_release_and_reset(m_pMaterial);

		_release_and_reset(m_pGeometry);

	}
	void SpotLight::RenderLight(RenderManagerPtr pRenderManager)
	{
		const math::Matrix44& world = GetWorldTM();

		pRenderManager->SetMatrixBlock(m_pMaterial, world);
		
		using namespace math;

		struct SpotLightParam
		{
			Vector3			color;
			float			intensity;
			float			range;
			float			theta;
		};

		SpotLightParam l;
		
		l.intensity = GetIntensity();
		const math::Color4& diffClr = GetDiffuseColor();
		l.color = math::Vector3(diffClr.r, diffClr.g, diffClr.b);
		l.range = GetRange();

		l.theta = cosf(math::D2R(GetAngle()));

		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("light");
		
		if(pParam)
		{
			pParam->SetParameterBlock(&l, sizeof(SpotLightParam));
		}
	

		pRenderManager->SetGBuffer(m_pMaterial);
				
		Sys_GraphicsPtr pGraphics = pRenderManager->GetSysGraphics();

		pGraphics->ClearDepthStencil(CLEAR_STENCIL, 1, 0);

		
		int nPass = m_pMaterial->Begin();
		for(int i = 0; i < nPass; ++i)
		{
			m_pMaterial->ApplyPass(i);
			pGraphics->Draw(m_pGeometry, m_nVerts, 0);
		}
		m_pMaterial->End();
	}
	void SpotLight::UpdateLightVolume()
	{
		math::Vector3* pVerts = MeshUtil::CreateSpotLightCone(m_range, m_angle, 50, m_nVerts);

		GPUBufferPtr pVB = m_pGeometry->GetVertexBuffer();
		void* pData = pVB->Map(MAP_DISCARD);

		memcpy(pData, pVerts, sizeof(math::Vector3)* m_nVerts);
		
		pVB->Unmap();
				
		mem_free(pVerts);

		UpdateLightProjMatrix();
	}
	void SpotLight::UpdateLightProjMatrix()
	{
		using namespace math;
		Matrix44 world = GetWorldTM();
		
		math::Vector3 eye(0, 0, 0);
		math::Vector3 up(0, 1, 0);
		math::Vector3 at(0, 0, m_range);

		TransformCoord(eye, world);
		TransformCoord(at, world);
				
		Vector3 z_axis = at - eye;
		z_axis.Normalize();

		if(abs(Dot(z_axis, up)) > 0.999)
		{
			up.z = 0.1;
		}
		
		m_projTM = math::MatrixLookAtLH(eye, at, up) * math::MatrixPerspectiveFovLH(math::D2R(2 * m_angle), 1, 0.1f, m_range);
		
		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("light_matrix");
		
		if(pParam)
		{
			pParam->SetParameterMatrix(m_projTM);
		}
	}
	void SpotLight::SetWorldTM(const math::Matrix44& world)
	{
		Light::SetWorldTM(world);
		UpdateLightProjMatrix();
	}
	void SpotLight::SetTexture(TexturePtr pTex)
	{
		m_pTexture = pTex;
		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("tex");

		pParam->SetParameterTexture(m_pTexture);
	}
	TexturePtr SpotLight::GetTexture()
	{
		return m_pTexture;
	}
}
