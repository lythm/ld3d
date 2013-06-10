#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorldRenderer.h"
#include "VoxelWorldRenderData.h"
#include "VoxelWorldDataSet.h"
#include "ext_voxel\VoxelWorld.h"
#include "VoxelWorldChunk.h"

namespace ld3d
{
	VoxelWorldRenderer::VoxelWorldRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorldRenderer", pManager)
	{
		m_bShowBound = false;
		SetVersion(g_packageVersion);
	}


	VoxelWorldRenderer::~VoxelWorldRenderer(void)
	{
	}
	void VoxelWorldRenderer::Update()
	{
		
	}

	
	bool VoxelWorldRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorldRenderer");
		{
			pPM->RegisterProperty<bool, VoxelWorldRenderer>(this,
				L"Show Bound",
				&VoxelWorldRenderer::GetShowBound,
				&VoxelWorldRenderer::SetShowBound);
		}
		pPM->End();

		

		m_pRenderData = m_pManager->GetAllocator()->AllocObject<VoxelWorldRenderData>();
		if(m_pRenderData->Initialize(m_pManager->GetRenderManager()->GetSysGraphics()) == false)
		{
			return false;
		}

		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRenderer::on_event_frustumcull, this, _1));

		m_pWorld = boost::dynamic_pointer_cast<VoxelWorld>(m_pObject->GetComponent(L"VoxelWorld"));

		m_pBBoxRD = m_pManager->GetAllocator()->AllocObject<BBoxRenderData>();
		if(m_pBBoxRD->Initialize(m_pManager->GetRenderManager()->GetSysGraphics()) == false)
		{
			return false;
		}
		
		return true;
	}
	void VoxelWorldRenderer::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
		m_pRenderData->Release();
		m_pRenderData.reset();
		m_pBBoxRD->Release();
		m_pBBoxRD.reset();
	
	}
	
	void VoxelWorldRenderer::on_event_frustumcull(EventPtr pEvent)
	{
		if(m_bShowBound)
		{
			m_pBBoxRD->SetWorldMatrix(m_pObject->GetWorldTransform());
			m_pBBoxRD->SetBBox(math::AABBox(
				math::Vector3(0, 0, 0),
				math::Vector3(m_pWorld->GetWorldSizeX(), m_pWorld->GetWorldSizeY(), m_pWorld->GetWorldSizeZ())));
			m_pManager->GetRenderManager()->AddRenderData(m_pBBoxRD);
		}

		boost::shared_ptr<Event_FrustumCull> e = boost::dynamic_pointer_cast<Event_FrustumCull>(pEvent);

		VoxelWorldChunk* pList = m_pWorld->FrustumCull(e->m_pCamera);

		if(pList == nullptr)
		{
			return;
		}
		m_pRenderData->PrepareRenderList(pList);

		m_pManager->GetRenderManager()->AddRenderData(m_pRenderData);

	}
	const bool&	VoxelWorldRenderer::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRenderer::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRenderer::OnSerialize(DataStream* pStream)
	{
		pStream->WriteBool(m_bShowBound);
		
		return true;
	}
	bool VoxelWorldRenderer::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}

		m_bShowBound = pStream->ReadBool();
		
		return true;
	}
}
