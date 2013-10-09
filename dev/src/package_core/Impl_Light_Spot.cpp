#include "core_ext_pch.h"
#include "Impl_Light_Spot.h"

#include "core_ext_pch.h"
#include "packages/core/Light_Spot.h"
#include "core/SpotLight.h"
#include "CorePackage.h"

namespace ld3d
{
	Impl_Light_Spot::Impl_Light_Spot(GameObjectManagerPtr pManager) : Light_Spot(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_Light_Spot::~Impl_Light_Spot(void)
	{
	}
	
	void Impl_Light_Spot::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	SpotLightPtr Impl_Light_Spot::GetLight()
	{
		return m_pLight;
	}
	

	bool Impl_Light_Spot::OnAttach()
	{
		m_pRenderManager = m_pManager->GetRenderManager();
		m_pLight = m_pManager->alloc_object<SpotLight>();
		m_pLight->Create(m_pRenderManager);
		m_pRenderManager->AddLight(m_pLight);

		RegisterProperty<bool, SpotLight>(m_pLight.get(), 
										"Cast Shadow", 
										&SpotLight::GetCastShadow,
										&SpotLight::SetCastShadow);

		RegisterProperty<math::Color4, SpotLight>(m_pLight.get(), 
										"Diffuse Color", 
										&SpotLight::GetDiffuseColor,
										&SpotLight::SetDiffuseColor);

		RegisterProperty<float, SpotLight>(m_pLight.get(), 
										"Intensity", 
										&SpotLight::GetIntensity,
										&SpotLight::SetIntensity);

		RegisterProperty<float, SpotLight>(m_pLight.get(), 
										"Angle", 
										&SpotLight::GetAngle,
										&SpotLight::SetAngle);

		RegisterProperty<float, SpotLight>(m_pLight.get(), 
										"Range", 
										&SpotLight::GetRange,
										&SpotLight::SetRange);

		RegisterProperty<bool, SpotLight>(m_pLight.get(), 
												"Enabled", 
												&SpotLight::GetEnabled,
												&SpotLight::SetEnabled);
	
		return true;
	}
	void Impl_Light_Spot::OnDetach()
	{
		ClearPropertySet();
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Impl_Light_Spot::OnSerialize(DataStream* pStream)
	{
		bool bEnabled = m_pLight->GetEnabled();
		pStream->WriteBool(bEnabled);

		bool bCastShadow = m_pLight->GetCastShadow();
		pStream->WriteBool(bCastShadow);

		math::Color4 diff = m_pLight->GetDiffuseColor();
		pStream->Write(&diff, sizeof(diff));

		float intensity = m_pLight->GetIntensity();
		pStream->WriteFloat32(intensity);

		float angle = m_pLight->GetAngle();
		pStream->WriteFloat32(angle);

		float range = m_pLight->GetRange();
		pStream->WriteFloat32(range);

		return true;

	}
	bool Impl_Light_Spot::OnUnSerialize(DataStream* pStream, const Version& version)
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

		float angle = pStream->ReadFloat32();
		m_pLight->SetAngle(angle);

		float range = pStream->ReadFloat32();
		m_pLight->SetRange(range);

		return true;
		
	}
}
