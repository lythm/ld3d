#include "core_pch.h"
#include "core/SkyLight.h"
#include "core/Sys_Graphics.h"
#include "core/GPUBuffer.h"
#include "core/Material.h"
#include "core/RenderManager.h"
#include "core/MaterialParameter.h"
#include "core/RenderTexture.h"
namespace ld3d
{
	SkyLight::SkyLight(void) : Light(LT_SKYLIGHT)
	{
	}


	SkyLight::~SkyLight(void)
	{
		m_pRenderManager.reset();
	}
	
	bool SkyLight::Create(RenderManagerPtr pRenderManager)
	{
		m_pRenderManager = pRenderManager;

		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_sky_light.material");
		
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		m_bCastShadow = true;

		if(m_bCastShadow)
		{
			int w = pRenderManager->GetFrameBufferWidth();
			int h = pRenderManager->GetFrameBufferHeight();

			if(CreateShadowMap(2048, 2048, G_FORMAT_R32_FLOAT) == false)
			{
				return false;
			}

		}
		return true;
	}
	void SkyLight::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
		m_pRenderManager.reset();
		
	}
	void SkyLight::RenderLight(RenderManagerPtr pRenderer)
	{
		if(GetEnabled() == false)
		{
			return;
		}

		const math::Matrix44& view = pRenderer->GetViewMatrix();
		const math::Matrix44& proj = pRenderer->GetProjMatrix();

		pRenderer->SetMatrixBlock(m_pMaterial, math::MatrixIdentity());
		
		const math::Matrix44& tm = GetWorldTM();

		math::Vector3 d = tm.GetRow3(2);

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

		pRenderer->SetGBuffer(m_pMaterial);

		pParam = m_pMaterial->GetParameterByName("shadow_map");
		pParam->SetParameterTexture(m_pShadowMap->GetTexture(0));


		math::Matrix44 l_proj = math::MatrixOrthoLH(800, 600, 0.1, 1000);
		math::Matrix44 l_view = m_worldTM;
		l_view.Invert();
		

		pParam = m_pMaterial->GetParameterByName("light_view");
		pParam->SetParameterMatrix(l_view);

		pParam = m_pMaterial->GetParameterByName("light_proj");
		pParam->SetParameterMatrix(l_proj);

		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
	bool SkyLight::CreateShadowMap(int w, int h, G_FORMAT format)
	{
		m_pShadowMap = m_pRenderManager->CreateRenderTexture(1, w, h, &format);
		if(m_pShadowMap == nullptr)
		{
			return false;
		}
		return true;
	}
	void SkyLight::RenderShadowMap(RenderManagerPtr pRenderer)
	{
		m_pRenderManager->SetRenderTarget(m_pShadowMap);
		m_pRenderManager->ClearDepthBuffer(CLEAR_ALL, 1.0f, 0);
		m_pRenderManager->ClearRenderTarget(0, math::Color4(1, 1, 1, 1));


		math::Matrix44 proj = math::MatrixOrthoLH(800, 600, 0.1, 1000);
		math::Matrix44 view = m_worldTM;
		view.Invert();
		
		m_pRenderManager->DrawShadowMapGeometry(view, proj);
	}
	RenderTexturePtr SkyLight::GetShadowMap()
	{
		return m_pShadowMap;
	}
}
