#include "voxel_pch.h"
#include "VoxelWorldRendererImpl2.h"
#include "VoxelWorldImpl2.h"


namespace ld3d
{

	VoxelWorldRendererImpl2::VoxelWorldRendererImpl2(GameObjectManagerPtr pManager) : VoxelWorldRenderer(pManager)
	{
		m_bShowBound = false;

		SetVersion(g_packageVersion);


		m_nVBBytes						= 1024 * 1024 * 32;
		m_nVBCurrent					= 0;
		m_nVBOffset						= 0;
		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_worldMatrix.MakeIdentity();
	}


	VoxelWorldRendererImpl2::~VoxelWorldRendererImpl2(void)
	{
	}
	const bool&	VoxelWorldRendererImpl2::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRendererImpl2::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRendererImpl2::OnAttach()
	{
		RegisterProperty<bool, VoxelWorldRendererImpl2>(this,
				"Show Bound",
				&VoxelWorldRendererImpl2::GetShowBound,
				&VoxelWorldRendererImpl2::SetShowBound);
		

		m_pRenderManager		= m_pManager->GetRenderManager();
		m_pAABBoxRenderData = m_pManager->alloc_object<AABBoxRenderData>();
		m_pAABBoxRenderData->Initialize(m_pRenderManager);


		using namespace voxel;

		

		std::shared_ptr<VoxelWorldImpl2> pWorld = std::dynamic_pointer_cast<VoxelWorldImpl2>(m_pObject->GetComponent("VoxelWorld"));
		if(pWorld != nullptr)
		{
			ResetWorld(pWorld->GetWorld(), pWorld->GetMaterials());
		}
		
		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRendererImpl2::on_event_frustumcull, this, _1));

		

		m_pRenderData			= m_pManager->alloc_object<RenderData>();
		m_pRenderData->fr_draw	= std::bind(&VoxelWorldRendererImpl2::Render, this, std::placeholders::_1);
		m_pRenderData->dr_draw	= std::bind(&VoxelWorldRendererImpl2::Render, this, std::placeholders::_1);
		m_pRenderData->sm_draw	= std::bind(&VoxelWorldRendererImpl2::RenderShadowMapGeo, this, std::placeholders::_1, std::placeholders::_2);
		
		

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32A32_FLOAT);
		
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


		

		m_renderList.reserve(20000);
		return true;
	}
	void VoxelWorldRendererImpl2::OnDetach()
	{
		ClearPropertySet();

		m_pAABBoxRenderData->Release();

		m_pManager->RemoveEventHandler(m_hFrustumCull);

		_release_and_reset(m_pGeometry);
		
		m_pRenderData.reset();

		

		if(m_pWorldVP)
		{
			m_pWorldVP->Close();
			m_pWorldVP.reset();
		}
		
	
	}
	void VoxelWorldRendererImpl2::Update(float dt)
	{
		if(m_pViewPortRoot)
		{
			math::Vector3 pos = m_pViewPortRoot->GetWorldTransform().GetTranslation();
			m_pWorldVP->MoveTo(voxel::Coord(pos.x, pos.y, pos.z));
		}
		if(m_pWorldVP)
		{
			m_pWorldVP->Update();
		}
	}
	void VoxelWorldRendererImpl2::BindWorldViewPort(GameObjectPtr pNode)
	{
		m_pViewPortRoot = pNode;
	}
	void VoxelWorldRendererImpl2::MoveViewPortTo(uint32 x, uint32 y, uint32 z)
	{
		m_pWorldVP->MoveTo(voxel::Coord(x, y, z));
	}
	void VoxelWorldRendererImpl2::ResetWorld(voxel::WorldPtr pWorld, const std::vector<MaterialPtr>& mats)
	{
		if(m_pWorldVP)
		{
			m_pWorldVP->Close();
			m_pWorldVP.reset();
		}

		if(pWorld == nullptr)
		{
			return;
		}
		m_materials = mats;
		m_pWorldVP = m_pManager->alloc_object<voxel::WorldViewport>();

		using namespace voxel;

		voxel::Coord center = Coord(0, 0, 0);
		uint32 raidius = 64;

		
		if(false == m_pWorldVP->Open(pWorld, center, raidius))
		{
			return;
		}

		m_pAABBoxRenderData->SetBox(math::AABBox((center - Coord(raidius, raidius, raidius)).ToVector3(), (center + Coord(raidius, raidius, raidius)).ToVector3()));


	}
	void VoxelWorldRendererImpl2::SetWorldViewPort(const voxel::Coord& center, uint32 size)
	{
		m_pWorldVP->MoveTo(center);
		m_pWorldVP->SetRadius(size);
	}
	void VoxelWorldRendererImpl2::on_event_frustumcull(EventPtr pEvent)
	{
		m_worldMatrix = m_pObject->GetWorldTransform();

		/*if(m_bShowBound)
		{
			m_pAABBoxRD->SetWorldMatrix(m_pObject->GetWorldTransform());
			m_pAABBoxRD->SetBox(math::AABBox(
				math::Vector3(0, 0, 0),
				math::Vector3(m_pWorld->GetWorldSizeX(), m_pWorld->GetWorldSizeY(), m_pWorld->GetWorldSizeZ())));
			m_pManager->GetRenderManager()->AddRenderData(layer_forward, m_pAABBoxRD->GetRenderData());
		}*/

		std::shared_ptr<Event_FrustumCull> e = std::dynamic_pointer_cast<Event_FrustumCull>(pEvent);

		m_renderList.clear();

		m_pWorldVP->FrustumCull(*(e->m_pViewFrustum), std::bind(&VoxelWorldRendererImpl2::_add_mesh, this, std::placeholders::_1, std::placeholders::_2));

		m_pManager->GetRenderManager()->AddRenderData(layer_deferred, m_pRenderData);

		m_pManager->GetRenderManager()->AddRenderData(layer_forward, m_pAABBoxRenderData->GetRenderData());

	}
	void VoxelWorldRendererImpl2::_add_mesh(const voxel::Coord& base, voxel::ChunkMeshPtr pMesh)
	{
		using namespace voxel;
		for(uint32 i = 0; i < pMesh->GetSubsetCount(); ++i)
		{
			const ChunkMesh::Subset& sub = pMesh->GetSubset(i);
		
			RenderUnit unit;
			unit.base	= base;
			unit.mesh	= pMesh;
			unit.sub	= sub;
			m_renderList.push_back(unit);
		}
	}
	void VoxelWorldRendererImpl2::Draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial, int baseVertex)
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
	void VoxelWorldRendererImpl2::Render(RenderManagerPtr pManager)
	{
		if(m_renderList.size() == 0)
		{
			return;
		}

		using namespace voxel;

		Coord cur_base = m_renderList[0].base;
		size_t index = 0;
		for(size_t i = 0; i < m_renderList.size(); ++i)
		{
			const Coord& r_base = m_renderList[i].base;

			if(r_base != cur_base)
			{
				_render(index, i);
				index = i;
				cur_base = r_base;
			}
		}

		_render(index, m_renderList.size());
	}
	void VoxelWorldRendererImpl2::RenderShadowMapGeo(RenderManagerPtr pManager, MaterialPtr pMaterial)
	{
		if(m_renderList.size() == 0)
		{
			return;
		}

		using namespace voxel;

		Coord cur_base = m_renderList[0].base;
		size_t index = 0;
		for(size_t i = 0; i < m_renderList.size(); ++i)
		{
			const Coord& r_base = m_renderList[i].base;

			if(r_base != cur_base)
			{
				_render_smg(index, i, pMaterial);
				index = i;
				cur_base = r_base;
			}
		}

		_render_smg(index, m_renderList.size(), pMaterial);
	}

	void VoxelWorldRendererImpl2::_render(size_t begin, size_t end)
	{
		using namespace voxel;
		if(begin == end)
		{
			return;
		}

		math::Matrix44 world = math::MatrixTranslation(m_renderList[begin].base.ToVector3());

		std::sort(m_renderList.begin() + begin, 
			m_renderList.begin() + end, 
			[](const RenderUnit& a, const RenderUnit& b){return a.sub.material_id < b.sub.material_id;});

		MaterialPtr pMat = nullptr;
		Sys_GraphicsPtr pGraphics = m_pRenderManager->GetSysGraphics();
		GPUBufferPtr pVB = m_pGeometry->GetVertexBuffer();

		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;
		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		
		uint8* data = nullptr;
		if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * m_renderList[0].sub.vertexCount)
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

		uint32 mat_id = m_renderList[begin].sub.material_id;

		for(size_t i = begin; i < end; ++i)
		{
			const RenderUnit& unit = m_renderList[i];
			if(unit.sub.material_id != mat_id)
			{
				pVB->Unmap();

				pMat = m_materials[mat_id];
			
				m_pRenderManager->SetMatrixBlock(pMat, world);

				Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

				data = (uint8*)pVB->Map(MAP_NO_OVERWRITE);
				m_nVBOffset = m_nVBCurrent;
				m_nVertexCount = 0;
				mat_id = unit.sub.material_id;
			}


			bytesLeft = m_nVBBytes - m_nVBCurrent;
			if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount)
			{
				pVB->Unmap();
				pMat = m_materials[mat_id];
				
				m_pRenderManager->SetMatrixBlock(pMat, world);

				Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

				data = (uint8*)pVB->Map(MAP_DISCARD);
				m_nVBOffset = 0;
				m_nVBCurrent = 0;
				bytesLeft = m_nVBBytes;
				m_nVertexCount = 0;
				mat_id = unit.sub.material_id;
			}
			
			memcpy(data + m_nVBCurrent, unit.sub.vertexBuffer, sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount);
			
			m_nVBCurrent += sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount;
			m_nVertexCount += unit.sub.vertexCount;
		}

		pVB->Unmap();
		pMat = m_materials[mat_id];
		
		m_pRenderManager->SetMatrixBlock(pMat, world);


		Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

	}
	void VoxelWorldRendererImpl2::_render_smg(size_t begin, size_t end, MaterialPtr pMaterial)
	{
		if(begin == end)
		{
			return;
		}
		
		MaterialPtr pMat = pMaterial;
		Sys_GraphicsPtr pGraphics = m_pRenderManager->GetSysGraphics();
		GPUBufferPtr pVB = m_pGeometry->GetVertexBuffer();

		math::Matrix44 world = math::MatrixTranslation(m_renderList[begin].base.ToVector3());

		m_pRenderManager->SetMatrixBlock(pMat, world);

		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;
		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		

		using namespace voxel;

		uint8* data = nullptr;
		if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * m_renderList[0].sub.vertexCount)
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

		for(size_t i = begin; i < end; ++i)
		{
			const RenderUnit& unit = m_renderList[i];
			
			bytesLeft = m_nVBBytes - m_nVBCurrent;
			if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount)
			{
				pVB->Unmap();

				Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);

				data = (uint8*)pVB->Map(MAP_DISCARD);
				m_nVBOffset = 0;
				m_nVBCurrent = 0;
				bytesLeft = m_nVBBytes;
				m_nVertexCount = 0;
			}
			
			memcpy(data + m_nVBCurrent, unit.sub.vertexBuffer, sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount);
			
			m_nVBCurrent += sizeof(ChunkMesh::VoxelVertex) * unit.sub.vertexCount;
			m_nVertexCount += unit.sub.vertexCount;
		}

		pVB->Unmap();
		Draw(pGraphics, pMat, m_nVBOffset / m_nVertexStride);
	}
}
