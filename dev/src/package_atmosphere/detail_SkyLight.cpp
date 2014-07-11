#include "package_atmosphere_pch.h"
#include "detail_SkyLight.h"

namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			namespace detail
			{
				SkyLight::SkyLight(void) : Light((LIGHT_TYPE)LT_SKYLIGHT)
				{
					SetShadowMapSize(4096, 4096);

					m_dir = math::Vector3(1, -1, 1);
				}


				SkyLight::~SkyLight(void)
				{
					m_pRenderManager.reset();
				}

				bool SkyLight::Create(RenderManagerPtr pRenderManager)
				{
					m_pRenderManager = pRenderManager;

					m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/atmosphere/material/skylight.material");

					if(m_pMaterial == nullptr)
					{
						return false;
					}

					//m_bCastShadow = true;

					if(false == m_pMaterial->SetCurrentTech(m_bCastShadow ? "with_shadow" : "with_no_shadow"))
					{
						return false;
					}

					if(m_bCastShadow)
					{
						ResizeShadowMap();
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

					struct DirLightParam
					{
						math::Vector3 d;
						float i;
						math::Vector3 c;
					};

					DirLightParam l;
					l.d = m_dir;
					l.i = GetIntensity();
					const math::Color4& diffClr = GetDiffuseColor();

					l.c = math::Vector3(diffClr.r, diffClr.g, diffClr.b);

					MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("light");
					pParam->SetParameterBlock(&l, sizeof(DirLightParam));

					pRenderer->SetGBuffer(m_pMaterial);

					if(m_bCastShadow)
					{
						pParam = m_pMaterial->GetParameterByName("shadow_map");

						pParam->SetParameterTexture(m_pShadowMap->GetTexture(0));
						pParam = m_pMaterial->GetParameterByName("light_tm");
						pParam->SetParameterMatrix(m_lightTM);
					}

					pRenderer->DrawFullScreenQuad(m_pMaterial);
				}
				bool SkyLight::CreateShadowMap(int w, int h, G_FORMAT format)
				{
					if(m_pRenderManager == nullptr)
					{
						return false;
					}
					m_pShadowMap = m_pRenderManager->CreateRenderTexture(1, w, h, &format, 1);
					if(m_pShadowMap == nullptr)
					{
						return false;
					}
					return true;
				}
				void SkyLight::RenderShadowMap(RenderManagerPtr pRenderer)
				{
					if(m_bCastShadow == false)
					{
						return;
					}
					if(m_pShadowMap == nullptr)
					{
						return;
					}

					math::Matrix44 proj = math::MatrixOrthoLH(100, 100, 0.1f, 20000);

					math::Matrix44 view = math::MatrixLookAtLH(-m_dir, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));

					m_lightTM = view * proj;

					math::ViewFrustum vf;
					vf.Update(view, proj);

					m_pRenderManager->EmitViewFrustumCullEvent(vf);

					m_pRenderManager->SetRenderTarget(m_pShadowMap);
					m_pRenderManager->ClearDepthBuffer(CLEAR_ALL, 1.0f, 0);
					m_pRenderManager->ClearRenderTarget(0, math::Color4(1, 1, 1, 1));

					m_pRenderManager->DrawShadowMapGeometry(view, proj);

					m_pRenderManager->Clear();
					//		m_pShadowMap->GetTexture(0)->GenMipmap();
				}
				RenderTexturePtr SkyLight::GetShadowMap()
				{
					return m_pShadowMap;
				}
				void SkyLight::SetCastShadow(const bool& bCast)
				{
					Light::SetCastShadow(bCast);

					if(m_pMaterial)
					{
						m_pMaterial->SetCurrentTech(bCast ? "with_shadow" : "with_no_shadow");
					}

					if(bCast && m_pShadowMap == nullptr)
					{
						ResizeShadowMap();
					}

					if(bCast == false && m_pShadowMap != nullptr)
					{
						m_pShadowMap->Release();
						m_pShadowMap.reset();
					}
				}
				void SkyLight::ResizeShadowMap()
				{
					if(m_pShadowMap)
					{
						m_pShadowMap->Release();
						m_pShadowMap.reset();
					}
					if(CreateShadowMap(m_shadowMapWidth, m_shadowMapHeight, G_FORMAT_R32_FLOAT) == false)
					{
						return;
					}
					return;
				}
				void SkyLight::SetLightDir(const math::Vector3& dir)
				{
					m_dir = dir;
					m_dir.Normalize();
				}
				const math::Vector3& SkyLight::GetLightDir() const
				{
					return m_dir;
				}
			}
		}
	}
}