#include "voxel_pch.h"
#include "VoxelWorldRendererImpl.h"

#include "VoxelWorldDataSet.h"
#include "VoxelWorldImpl.h"
#include "VoxelWorldChunk.h"

namespace ld3d
{
	VoxelWorldRendererImpl::VoxelWorldRendererImpl(GameObjectManagerPtr pManager) : VoxelWorldRenderer(pManager)
	{
		m_bShowBound = false;
		SetVersion(g_packageVersion);

		m_pRenderList					= 0;

		m_nVBBytes						= 1024 * 1024 * 4;
		m_nVBCurrent					= 0;
		m_nVBOffset						= 0;
		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_worldMatrix.MakeIdentity();
	}


	VoxelWorldRendererImpl::~VoxelWorldRendererImpl(void)
	{
	}
	void VoxelWorldRendererImpl::Update(float dt)
	{
		m_worldMatrix = m_pObject->GetWorldTransform();
	}

	
	bool VoxelWorldRendererImpl::OnAttach()
	{
		
		RegisterProperty<bool, VoxelWorldRendererImpl>(this,
				"Show Bound",
				&VoxelWorldRendererImpl::GetShowBound,
				&VoxelWorldRendererImpl::SetShowBound);
				
		m_pRenderManager		= m_pManager->GetRenderManager();

		m_pRenderData			= m_pManager->alloc_object<RenderData>();
		m_pRenderData->fr_draw	= std::bind(&VoxelWorldRendererImpl::Render, this, std::placeholders::_1);
		m_pRenderData->dr_draw	= std::bind(&VoxelWorldRendererImpl::Render, this, std::placeholders::_1);
		m_pRenderData->dr		= true;
		
		m_pMaterial = m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/voxel_world.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R8G8B8A8_UNORM);
		
		m_pGeometry = m_pRenderManager->CreateGeometryData();
		
		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			if(false == m_pGeometry->AllocVertexBuffer(m_nVBBytes, nullptr, true, layout))
			{
				return false;
			}
		}
		m_pGeometry->EndGeometry();

		m_nVBCurrent			= 0;
		m_nVBOffset				= 0;
		m_nVertexStride			= layout.VertexStride();
		m_nVertexCount			= 0;



		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRendererImpl::on_event_frustumcull, this, _1));

		m_pWorld = std::dynamic_pointer_cast<VoxelWorldImpl>(m_pObject->GetComponent("VoxelWorld"));

		m_pBBoxRD = m_pManager->alloc_object<BBoxRenderData>();
		if(m_pBBoxRD->Initialize(m_pManager->GetRenderManager()->GetSysGraphics()) == false)
		{
			return false;
		}
		
		return true;
	}
	void VoxelWorldRendererImpl::OnDetach()
	{
		m_pMaterial->Release();
		m_pMaterial.reset();
		m_pGeometry->Release();
		m_pGeometry.reset();

		ClearPropertySet();
		m_pManager->RemoveEventHandler(m_hFrustumCull);
		m_pRenderData.reset();
		m_pBBoxRD->Release();
		m_pBBoxRD.reset();
	
	}
	
	void VoxelWorldRendererImpl::on_event_frustumcull(EventPtr pEvent)
	{
		if(m_bShowBound)
		{
			/*m_pBBoxRD->SetWorldMatrix(m_pObject->GetWorldTransform());
			m_pBBoxRD->SetBBox(math::AABBox(
				math::Vector3(0, 0, 0),
				math::Vector3(m_pWorld->GetWorldSizeX(), m_pWorld->GetWorldSizeY(), m_pWorld->GetWorldSizeZ())));
			m_pManager->GetRenderManager()->AddRenderData(m_pBBoxRD);*/
		}

		std::shared_ptr<Event_FrustumCull> e = std::dynamic_pointer_cast<Event_FrustumCull>(pEvent);

		m_pRenderList = m_pWorld->FrustumCull(e->m_pCamera);

		if(m_pRenderList == nullptr)
		{
			return;
		}
		
		m_pManager->GetRenderManager()->AddRenderData(layer_deferred, m_pRenderData);

	}
	const bool&	VoxelWorldRendererImpl::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRendererImpl::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRendererImpl::OnSerialize(DataStream* pStream)
	{
		pStream->WriteBool(m_bShowBound);
		
		return true;
	}
	bool VoxelWorldRendererImpl::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}

		m_bShowBound = pStream->ReadBool();
		
		return true;
	}
	void VoxelWorldRendererImpl::Render(RenderManagerPtr pManager)
	{
		if(m_pRenderList == nullptr)
		{
			return;
		}

		m_pRenderManager->SetMatrixBlock(m_pMaterial, m_worldMatrix);

		MaterialPtr pMat = m_pMaterial;
		Sys_GraphicsPtr pGraphics = m_pRenderManager->GetSysGraphics();
		GPUBufferPtr pVB = m_pGeometry->GetVertexBuffer();


		VoxelWorldChunk* pChunk = m_pRenderList;
		
		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;
		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;

		uint8* data = nullptr;
		if(bytesLeft <= sizeof(VoxelVertex) * pChunk->vertex_count)
		{
			data = (uint8*)pVB->Map(MAP_DISCARD);
			m_nVBOffset = 0;
			m_nVBCurrent = 0;
			bytesLeft = m_nVBBytes;
		}
		else
		{
			data = (uint8*)pVB->Map(MAP_NO_OVERWRITE);
		}

		while(pChunk)
		{
			if(pChunk->vertex_count == 0)
			{
				pChunk = pChunk->render_list_next;
				continue;
			}
			bytesLeft = m_nVBBytes - m_nVBCurrent;
			if(bytesLeft <= sizeof(VoxelVertex) * pChunk->vertex_count)
			{
				pVB->Unmap();
				Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

				data = (uint8*)pVB->Map(MAP_DISCARD);
				m_nVBOffset = 0;
				m_nVBCurrent = 0;
				bytesLeft = m_nVBBytes;
				m_nVertexCount = 0;
			}

			memcpy(data + m_nVBCurrent, pChunk->vertex_buffer, sizeof(VoxelVertex) * pChunk->vertex_count);
			
			m_nVBCurrent += sizeof(VoxelVertex) * pChunk->vertex_count;
			m_nVertexCount += pChunk->vertex_count;
			
			pChunk = pChunk->render_list_next;
		}

		pVB->Unmap();

		Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

		m_pRenderList = nullptr;

	}
	void VoxelWorldRendererImpl::Draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial, int baseVertex)
	{
		if(m_nVertexCount == 0)
		{
			return;
		}

		int nPass = pMaterial->Begin();

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);

			pSysGraphics->Draw(m_pGeometry, m_nVertexCount, baseVertex);
		}

		pMaterial->End();
	}
}
