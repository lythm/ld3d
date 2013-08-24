#include "core_ext_pch.h"
#include "core/ext/Light_Sky.h"

#include "core/SkyLight.h"

#include "CorePackage.h"
namespace ld3d
{

	Light_Sky::Light_Sky(GameObjectManagerPtr pManager) : GameObjectComponent("SkyLight", pManager)
	{
		SetVersion(g_packageVersion);
	}


	Light_Sky::~Light_Sky(void)
	{
	}
	void Light_Sky::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}

	SkyLightPtr Light_Sky::GetLight()
	{
		return m_pLight;
	}
	
	bool Light_Sky::OnAttach()
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

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("SkyLight");
		{
			pPM->RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				"Cast Shadow", 
				&SkyLight::GetCastShadow,
				&SkyLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, SkyLight>(m_pLight.get(), 
				"Diffuse Color", 
				&SkyLight::GetDiffuseColor,
				&SkyLight::SetDiffuseColor);

			pPM->RegisterProperty<float, SkyLight>(m_pLight.get(), 
				"Intensity", 
				&SkyLight::GetIntensity,
				&SkyLight::SetIntensity);

			pPM->RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				"Enabled", 
				&SkyLight::GetEnabled,
				&SkyLight::SetEnabled);

		}
		pPM->End();

		return true;
	}
	void Light_Sky::OnDetach()
	{
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Light_Sky::OnSerialize(DataStream* pStream)
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
	bool Light_Sky::OnUnSerialize(DataStream* pStream, const Version& version)
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