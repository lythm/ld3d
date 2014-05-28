#include "core_ext_pch.h"
#include "Impl_AABBoxRenderer.h"

#include "core/GameObject.h"

#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"
#include "core/GPUBuffer.h"
#include "CorePackage.h"
#include "core/Event.h"

namespace ld3d
{

	Impl_AABBoxRenderer::Impl_AABBoxRenderer(GameObjectManagerPtr pManager) : AABBoxRenderer(pManager)
	{
		SetVersion(g_packageVersion);

		m_pRenderManager = m_pManager->GetRenderManager();
	}


	Impl_AABBoxRenderer::~Impl_AABBoxRenderer(void)
	{
	}
	void Impl_AABBoxRenderer::SetAABBox(const math::AABBox& box)
	{
		if(m_pRD)
		{
			m_pRD->SetBox(box);
		}
	}
	void Impl_AABBoxRenderer::Update(float dt)
	{
	}

	bool Impl_AABBoxRenderer::OnAttach()
	{

		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_AABBoxRenderer::on_event_frustum_cull, this, _1));

		ResetRenderData();

		return true;
	}
	void Impl_AABBoxRenderer::ResetRenderData()
	{
		if(m_pRD)
		{
			m_pRD->Release();
		}
		m_pRD = m_pManager->alloc_object<AABBoxRenderData>();

		if(m_pRD->Initialize(m_pManager->GetRenderManager()) == false)
		{
			return;
		}
	}
	void Impl_AABBoxRenderer::OnDetach()
	{
		ClearPropertySet();
		m_pManager->RemoveEventHandler(m_hFrustumCull);

		m_pRD->Release();
		m_pRD.reset();
		
		m_pRenderManager.reset();

	}
	void Impl_AABBoxRenderer::on_event_frustum_cull(EventPtr pEvent)
	{
		m_pRD->SetWorldMatrix(m_pObject->GetWorldTransform());
		
		m_pRenderManager->AddRenderData(layer_forward, m_pRD->GetRenderData());

	}
}
