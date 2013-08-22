#include "core_ext_pch.h"
#include "core/ext/Light_Dir.h"
#include "core/DirectionalLight.h"
#include "core/RenderManager.h"
#include "core/GameObject.h"
#include "CorePackage.h"

namespace ld3d
{
	Light_Dir::Light_Dir(GameObjectManagerPtr pManager) : GameObjectComponent("DirectionalLight", pManager)
	{
		SetVersion(g_packageVersion);
	}


	Light_Dir::~Light_Dir(void)
	{
	}
	
	void Light_Dir::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	DirectionalLightPtr Light_Dir::GetLight()
	{
		return m_pLight;
	}
	bool Light_Dir::OnAttach()
	{
		m_pRenderManager = m_pManager->GetRenderManager();

		m_pLight = m_pManager->alloc_object<DirectionalLight>();
		m_pLight->Create(m_pRenderManager);

		m_pRenderManager->AddLight(m_pLight);

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));
		
		pPM->Begin("DirectionalLight");
		{
			pPM->RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
												"Cast Shadow", 
												&DirectionalLight::GetCastShadow,
												&DirectionalLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, DirectionalLight>(m_pLight.get(), 
												"Diffuse Color", 
												&DirectionalLight::GetDiffuseColor,
												&DirectionalLight::SetDiffuseColor);

			pPM->RegisterProperty<float, DirectionalLight>(m_pLight.get(), 
				"Intensity", 
				&DirectionalLight::GetIntensity,
				&DirectionalLight::SetIntensity);

			pPM->RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
				"Enabled", 
				&DirectionalLight::GetEnabled,
				&DirectionalLight::SetEnabled);

		}
		pPM->End();

		return true;
	}
	void Light_Dir::OnDetach()
	{
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Light_Dir::OnSerialize(DataStream* pStream)
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
	bool Light_Dir::OnUnSerialize(DataStream* pStream, const Version& version)
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
