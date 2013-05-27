#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorldRenderer.h"
#include "VoxelWorldRenderData.h"

namespace ld3d
{
	VoxelWorldRenderer::VoxelWorldRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorldRenderer", pManager)
	{
	}


	VoxelWorldRenderer::~VoxelWorldRenderer(void)
	{
	}
	void VoxelWorldRenderer::Update()
	{
		
	}

	const Version& VoxelWorldRenderer::GetVersion() const
	{
		return g_packageVersion;
	}
	bool VoxelWorldRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorldRenderer");
		{
			
		}
		pPM->End();


		m_pRenderData = m_pManager->GetAllocator()->AllocObject<VoxelWorldRenderData>();
		if(m_pRenderData->Initialize() == false)
		{
			return false;
		}


		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRenderer::on_event_frustumcull, this, _1));

		return true;
	}
	void VoxelWorldRenderer::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
		m_pRenderData->Release();
		m_pRenderData.reset();
	}
	void VoxelWorldRenderer::UpdateVoxelWorld(VoxelWorldPtr pWorld)
	{

	}
	void VoxelWorldRenderer::on_event_frustumcull(EventPtr pEvent)
	{

	}
}
