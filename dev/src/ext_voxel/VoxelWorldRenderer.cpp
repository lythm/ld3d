#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorldRenderer.h"
#include "VoxelWorldRenderData.h"
#include "VoxelWorldDataSet.h"
#include "ext_voxel\VoxelWorld.h"

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

		m_pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");

		m_pRenderData = m_pManager->GetAllocator()->AllocObject<VoxelWorldRenderData>();
		if(m_pRenderData->Initialize(m_pMaterial) == false)
		{
			return false;
		}

		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRenderer::on_event_frustumcull, this, _1));

		m_pWorld = boost::dynamic_pointer_cast<VoxelWorld>(m_pObject->GetComponent(L"VoxelWorld"));

		UpdateWorldMesh();

		return true;
	}
	void VoxelWorldRenderer::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
		m_pRenderData->Release();
		m_pRenderData.reset();

		m_pMaterial->Release();
		m_pMaterial.reset();
	}
	void VoxelWorldRenderer::UpdateWorldMesh()
	{
		if(m_pWorld == nullptr)
		{
			return;
		}
		VoxelWorldDataSetPtr pDataSet = m_pWorld->GetDataSet();

		std::vector<VoxelFace> faces = pDataSet->GenerateMesh();


	}
	void VoxelWorldRenderer::on_event_frustumcull(EventPtr pEvent)
	{
		m_pManager->GetRenderManager()->AddRenderData(m_pRenderData);
	}
	
}
