#include "core_ext_pch.h"
#include "Impl_Light_Dir.h"


#include "core/DirectionalLight.h"
#include "core/RenderManager.h"
#include "core/GameObject.h"
#include "CorePackage.h"

namespace ld3d
{
	Impl_Light_Dir::Impl_Light_Dir(GameObjectManagerPtr pManager) : Light_Dir(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_Light_Dir::~Impl_Light_Dir(void)
	{
	}
	
	void Impl_Light_Dir::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	DirectionalLightPtr Impl_Light_Dir::GetLight()
	{
		return m_pLight;
	}
	bool Impl_Light_Dir::OnAttach()
	{
		m_pRenderManager = m_pManager->GetRenderManager();

		m_pLight = m_pManager->alloc_object<DirectionalLight>();
		m_pLight->Create(m_pRenderManager);

		m_pRenderManager->AddLight(m_pLight);

		
		RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
												"Cast Shadow", 
												&DirectionalLight::GetCastShadow,
												&DirectionalLight::SetCastShadow);

		RegisterProperty<math::Color4, DirectionalLight>(m_pLight.get(), 
												"Diffuse Color", 
												&DirectionalLight::GetDiffuseColor,
												&DirectionalLight::SetDiffuseColor);

		RegisterProperty<float, DirectionalLight>(m_pLight.get(), 
												"Intensity", 
												&DirectionalLight::GetIntensity,
												&DirectionalLight::SetIntensity);

		RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
												"Enabled", 
												&DirectionalLight::GetEnabled,
												&DirectionalLight::SetEnabled);

		return true;
	}
	void Impl_Light_Dir::OnDetach()
	{
		ClearPropertySet();
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Impl_Light_Dir::OnSerialize(DataStream* pStream)
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
	bool Impl_Light_Dir::OnUnSerialize(DataStream* pStream, const Version& version)
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
