#include "core_ext_pch.h"
#include "core/ext/PostEffectList.h"

#include "core/ext/PropertyManager.h"


namespace ld3d
{

	PostEffectList::PostEffectList(GameObjectManagerPtr pManager) : GameObjectComponent("PostEffectList", pManager)
	{
		SetVersion(g_packageVersion);
	}


	PostEffectList::~PostEffectList(void)
	{
	}
	
	bool PostEffectList::OnAttach()
	{
		m_pSSAO = m_pManager->alloc_object<PostEffect_SSAO>();

		m_pSSAO->Initialize(m_pManager->GetRenderManager());
		
		m_pManager->GetRenderManager()->AddPostEffect(m_pSSAO);

		m_pGBlur = m_pManager->alloc_object<PostEffect_GaussianBlur>();
		m_pGBlur->Initialize(m_pManager->GetRenderManager());
		//m_pManager->GetRenderManager()->AddPostEffect(m_pGBlur);

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("PostEffectList");
		{
			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				"Bias", 
				&PostEffect_SSAO::GetBias,
				&PostEffect_SSAO::SetBias);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				"Scale", 
				&PostEffect_SSAO::GetScale,
				&PostEffect_SSAO::SetScale);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				"Sample Rad", 
				&PostEffect_SSAO::GetSampleRad,
				&PostEffect_SSAO::SetSampleRad);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				"Intensity", 
				&PostEffect_SSAO::GetIntensity,
				&PostEffect_SSAO::SetIntensity);
		}
		pPM->End();

		return true;
	}
	void PostEffectList::OnDetach()
	{

	}
}
