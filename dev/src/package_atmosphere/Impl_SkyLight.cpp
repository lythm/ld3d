#include "package_atmosphere_pch.h"
#include "Impl_SkyLight.h"
#include "detail_SkyLight.h"
namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			Impl_SkyLight::Impl_SkyLight(GameObjectManagerPtr pManager) : SkyLight(pManager)
			{
				SetVersion(g_packageVersion);
			}


			Impl_SkyLight::~Impl_SkyLight(void)
			{
			}

			
			void Impl_SkyLight::Update(float dt)
			{
				if(m_pLight)
				{
					m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
				}
			}

			LightPtr Impl_SkyLight::GetLight()
			{
				return m_pLight;
			}
			void Impl_SkyLight::EnableShadow(bool enable)
			{
				m_pLight->SetCastShadow(enable);
			}
			bool Impl_SkyLight::OnAttach()
			{
				m_pRenderManager = m_pManager->GetRenderManager();
				m_pLight = m_pManager->alloc_object<detail::SkyLight>();
				if(false == m_pLight->Create(m_pRenderManager))
				{
					m_pLight->Release();
					m_pLight.reset();
					return false;
				}
				m_pRenderManager->AddLight(m_pLight);

				RegisterProperty<bool, detail::SkyLight>(m_pLight.get(), 
					"Cast Shadow", 
					&detail::SkyLight::GetCastShadow,
					&detail::SkyLight::SetCastShadow);

				RegisterProperty<math::Color4, detail::SkyLight>(m_pLight.get(), 
					"Diffuse Color", 
					&detail::SkyLight::GetDiffuseColor,
					&detail::SkyLight::SetDiffuseColor);

				RegisterProperty<float, detail::SkyLight>(m_pLight.get(), 
					"Intensity", 
					&detail::SkyLight::GetIntensity,
					&detail::SkyLight::SetIntensity);

				RegisterProperty<bool, detail::SkyLight>(m_pLight.get(), 
					"Enabled", 
					&detail::SkyLight::GetEnabled,
					&detail::SkyLight::SetEnabled);


				return true;
			}
			void Impl_SkyLight::OnDetach()
			{
				ClearPropertySet();
				m_pRenderManager->RemoveLight(m_pLight);
				m_pLight->Release();
				m_pLight.reset();
			}
			bool Impl_SkyLight::OnSerialize(DataStream* pStream)
			{
				bool bEnabled = m_pLight->GetEnabled();
				pStream->WriteBool(bEnabled);

				bool bCastShadow = m_pLight->GetCastShadow();
				pStream->WriteBool(bCastShadow);

				math::Color4 diff = m_pLight->GetDiffuseColor();
				pStream->Write(&diff, sizeof(diff));

				float intensity = m_pLight->GetIntensity();
				pStream->WriteFloat32(intensity);

				return true;

			}
			bool Impl_SkyLight::OnUnSerialize(DataStream* pStream, const Version& version)
			{
				if(version != GetVersion())
				{
					return false;
				}
				bool bEnabled = pStream->ReadBool();
				m_pLight->SetEnabled(bEnabled);

				bool bCastShadow = pStream->ReadBool();
				m_pLight->SetCastShadow(bCastShadow);

				math::Color4 diff;
				pStream->Read(&diff, sizeof(diff));
				m_pLight->SetDiffuseColor(diff);

				float intensity = pStream->ReadFloat32();
				m_pLight->SetIntensity(intensity);

				return true;

			}
			void Impl_SkyLight::SetLightDir(const math::Vector3& dir)
			{
				m_pLight->SetLightDir(dir);
			}
			const math::Vector3& Impl_SkyLight::GetLightDir() const
			{
				return m_pLight->GetLightDir();
			}
		}
	}
}