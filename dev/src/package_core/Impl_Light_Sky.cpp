#include "core_ext_pch.h"
#include "Impl_Light_Sky.h"


#include "core/SkyLight.h"

#include "CorePackage.h"
namespace ld3d
{

	Impl_Light_Sky::Impl_Light_Sky(GameObjectManagerPtr pManager) : Light_Sky(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_Light_Sky::~Impl_Light_Sky(void)
	{
	}
	void Impl_Light_Sky::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}

	SkyLightPtr Impl_Light_Sky::GetLight()
	{
		return m_pLight;
	}
	void Impl_Light_Sky::EnableShadow(bool enable)
	{
		m_pLight->SetCastShadow(enable);
	}
	bool Impl_Light_Sky::OnAttach()
	{
		m_pRenderManager = m_pManager->GetRenderManager();
		m_pLight = m_pManager->alloc_object<SkyLight>();
		if(false == m_pLight->Create(m_pRenderManager))
		{
			m_pLight->Release();
			m_pLight.reset();
			return false;
		}
		m_pRenderManager->AddLight(m_pLight);

		RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				"Cast Shadow", 
				&SkyLight::GetCastShadow,
				&SkyLight::SetCastShadow);

		RegisterProperty<math::Color4, SkyLight>(m_pLight.get(), 
				"Diffuse Color", 
				&SkyLight::GetDiffuseColor,
				&SkyLight::SetDiffuseColor);

		RegisterProperty<float, SkyLight>(m_pLight.get(), 
				"Intensity", 
				&SkyLight::GetIntensity,
				&SkyLight::SetIntensity);

		RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				"Enabled", 
				&SkyLight::GetEnabled,
				&SkyLight::SetEnabled);


		return true;
	}
	void Impl_Light_Sky::OnDetach()
	{
		ClearPropertySet();
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Impl_Light_Sky::OnSerialize(DataStream* pStream)
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
	bool Impl_Light_Sky::OnUnSerialize(DataStream* pStream, const Version& version)
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
	
}
