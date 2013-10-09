#include "core_ext_pch.h"
#include "Impl_Light_Point.h"


#include "core/PointLight.h"
#include "core/RenderManager.h"
#include "core/GameObject.h"
#include "CorePackage.h"

namespace ld3d
{
	Impl_Light_Point::Impl_Light_Point(GameObjectManagerPtr pManager) : Light_Point(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_Light_Point::~Impl_Light_Point(void)
	{
	}
	
	void Impl_Light_Point::Update(float dt)
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	PointLightPtr Impl_Light_Point::GetLight()
	{
		return m_pLight;
	}
	
	bool Impl_Light_Point::OnAttach()
	{
		m_pRenderManager = m_pManager->GetRenderManager();

		m_pLight = m_pManager->alloc_object<PointLight>();
		if(false == m_pLight->Create(m_pRenderManager))
		{
			return false;
		}

		m_pRenderManager->AddLight(m_pLight);

		
		RegisterProperty<bool, PointLight>(m_pLight.get(), 
										"Cast Shadow", 
										&PointLight::GetCastShadow,
										&PointLight::SetCastShadow);
		 
		RegisterProperty<math::Color4, PointLight>(m_pLight.get(), 
										"Diffuse Color", 
										&PointLight::GetDiffuseColor,
										&PointLight::SetDiffuseColor);

		
		RegisterProperty<float, PointLight>(m_pLight.get(), 
										"Radius", 
										&PointLight::GetRadius,
										&PointLight::SetRadius);

		RegisterProperty<float, PointLight>(m_pLight.get(), 
										"Intensity", 
										&PointLight::GetIntensity,
										&PointLight::SetIntensity);

		RegisterProperty<bool, PointLight>(m_pLight.get(), 
												"Enabled", 
												&PointLight::GetEnabled,
												&PointLight::SetEnabled);


		return true;
	}
	void Impl_Light_Point::OnDetach()
	{
		ClearPropertySet();
		m_pRenderManager->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
	bool Impl_Light_Point::OnSerialize(DataStream* pStream)
	{
		bool bEnabled = m_pLight->GetEnabled();
		pStream->WriteBool(bEnabled);

		bool bCastShadow = m_pLight->GetCastShadow();
		pStream->WriteBool(bCastShadow);

		math::Color4 diff = m_pLight->GetDiffuseColor();
		pStream->Write(&diff, sizeof(diff));

		float intensity = m_pLight->GetIntensity();
		pStream->WriteFloat32(intensity);

		float radius = m_pLight->GetRadius();
		pStream->WriteFloat32(radius);
		return true;

	}
	bool Impl_Light_Point::OnUnSerialize(DataStream* pStream, const Version& version)
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

		float radius = pStream->ReadFloat32();
		m_pLight->SetRadius(radius);

		return true;
		
	}
	
}