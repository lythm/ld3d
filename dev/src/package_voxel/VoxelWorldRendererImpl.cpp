#include "voxel_pch.h"
#include "VoxelWorldRendererImpl.h"
#include "VoxelWorldImpl.h"
#include "core/MaterialTech.h"
#include "core/MaterialPass.h"

#include "VoxelWorldGeometryBuffer.h"
#include "VoxelWorldGeometryBufferIndexed.h"


namespace ld3d
{

	VoxelWorldRendererImpl::VoxelWorldRendererImpl(GameObjectManagerPtr pManager) : VoxelWorldRenderer(pManager)
	{
		m_bShowBound = false;

		SetVersion(g_packageVersion);

		m_worldMatrix.MakeIdentity();
	}


	VoxelWorldRendererImpl::~VoxelWorldRendererImpl(void)
	{
	}
	const bool&	VoxelWorldRendererImpl::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRendererImpl::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRendererImpl::OnAttach()
	{
		RegisterProperty<bool, VoxelWorldRendererImpl>(this,
				"Show Bound",
				&VoxelWorldRendererImpl::GetShowBound,
				&VoxelWorldRendererImpl::SetShowBound);
		

		m_pRenderManager		= m_pManager->GetRenderManager();
		m_pAABBoxRenderData = m_pManager->alloc_object<AABBoxRenderData>();
		m_pAABBoxRenderData->Initialize(m_pRenderManager);


		using namespace voxel;

		

		std::shared_ptr<VoxelWorldImpl> pWorld = std::dynamic_pointer_cast<VoxelWorldImpl>(m_pObject->GetComponent("Voxel.World"));
		if(pWorld != nullptr)
		{
			ResetWorld(pWorld->GetWorld(), pWorld->GetMaterials());
		}
		
		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&VoxelWorldRendererImpl::on_event_frustumcull, this, _1));

		

		m_pRenderData			= m_pManager->alloc_object<RenderData>();
		m_pRenderData->fr_draw	= std::bind(&VoxelWorldRendererImpl::Render, this, std::placeholders::_1);
		m_pRenderData->dr_draw	= std::bind(&VoxelWorldRendererImpl::Render, this, std::placeholders::_1);
		m_pRenderData->sm_draw	= std::bind(&VoxelWorldRendererImpl::RenderShadowMapGeo, this, std::placeholders::_1, std::placeholders::_2);
		
		m_pGeometryBuffer = m_pManager->alloc_object<VoxelWorldGeometryBufferIndexed>();
		if(m_pGeometryBuffer->Initialize(m_pRenderManager, (1024 * 1024 * 8) / sizeof(voxel::ChunkMesh::VoxelVertex)) == false)
		{
			return false;

		}

		m_pRenderData->geometry = m_pGeometryBuffer->GetGeometryData();
		m_renderList.reserve(20000);
		return true;
	}
	void VoxelWorldRendererImpl::OnDetach()
	{
		ClearPropertySet();

		m_pAABBoxRenderData->Release();

		m_pManager->RemoveEventHandler(m_hFrustumCull);

		_release_and_reset(m_pGeometryBuffer);

		m_pRenderData.reset();

		if(m_pWorldVP)
		{
			m_pWorldVP->Close();
			m_pWorldVP.reset();
		}
	}
	void VoxelWorldRendererImpl::Update(float dt)
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
	void VoxelWorldRendererImpl::BindWorldViewPort(GameObjectPtr pNode)
	{
		m_pViewPortRoot = pNode;
	}
	void VoxelWorldRendererImpl::MoveViewPortTo(uint32 x, uint32 y, uint32 z)
	{
		m_pWorldVP->MoveTo(voxel::Coord(x, y, z));
	}
	void VoxelWorldRendererImpl::ResetWorld(voxel::WorldPtr pWorld, const std::vector<MaterialPtr>& mats)
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
	void VoxelWorldRendererImpl::SetWorldViewPort(const voxel::Coord& center, uint32 size)
	{
		m_pWorldVP->MoveTo(center);
		m_pWorldVP->SetRadius(size);
	}
	void VoxelWorldRendererImpl::on_event_frustumcull(EventPtr pEvent)
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
		m_renderedChunk = 0;

		m_pWorldVP->FrustumCull(*(e->m_pViewFrustum), std::bind(&VoxelWorldRendererImpl::_add_mesh, this, std::placeholders::_1, std::placeholders::_2));

		m_pManager->GetRenderManager()->AddRenderData(layer_deferred, m_pRenderData);

	//	m_pManager->GetRenderManager()->AddRenderData(layer_forward, m_pAABBoxRenderData->GetRenderData());

	}
	void VoxelWorldRendererImpl::_add_mesh(const voxel::Coord& base, voxel::ChunkMeshPtr pMesh)
	{
		m_renderedChunk++;

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
	void VoxelWorldRendererImpl::Draw(Sys_GraphicsPtr pSysGraphics, GeometryDataPtr pGeo, MaterialPtr pMaterial, int baseVertex, int nVerts)
	{
		m_renderedVertex += nVerts;
		if(nVerts == 0)
		{
			return;
		}

		int nPass = pMaterial->Begin();

		for(int i = 0; i < nPass; ++i)
		{/*
			pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->Begin();
			pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->SetFillMode(RS_FILL_SOLID);
			pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->End();*/

			pMaterial->ApplyPass(i);
			pSysGraphics->Draw(pGeo, nVerts, baseVertex);


			/*pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->Begin();
			pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->SetFillMode(RS_FILL_WIREFRAME);
			pMaterial->GetTechByIndex(0)->GetPassByIndex(i)->GetRenderState()->End();
			

			pMaterial->ApplyPass(i);
			pSysGraphics->Draw(m_pGeometry, m_nVertexCount, baseVertex);*/
		}

		pMaterial->End();
	}

	void VoxelWorldRendererImpl::MultiDrawIndexed(Sys_GraphicsPtr pSysGraphics, GeometryDataPtr pGeo, MaterialPtr pMaterial, int draw_count, int index_count[], void* index[], int base_verts[])
	{
		/*m_renderedVertex += nVerts;
		if(nVerts == 0)
		{
			return;
		}
*/
		int nPass = pMaterial->Begin();

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);
			//pSysGraphics->Draw(pGeo, nVerts, baseVertex);

			pSysGraphics->MultiDrawIndexed(pGeo, draw_count, index_count, index, base_verts);
		}

		pMaterial->End();
	}
	void VoxelWorldRendererImpl::Render(RenderManagerPtr pManager)
	{
		m_renderedVertex = 0;
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
				_render_indexed(index, i);
				index = i;
				cur_base = r_base;
			}
		}

		_render_indexed(index, m_renderList.size());
	}
	void VoxelWorldRendererImpl::RenderShadowMapGeo(RenderManagerPtr pManager, MaterialPtr pMaterial)
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

	void VoxelWorldRendererImpl::_render(size_t begin, size_t end)
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
		
		uint32 mat_id = m_renderList[begin].sub.material_id;

		GeometryDataPtr pGeo = m_pGeometryBuffer->GetGeometryData();

		m_pGeometryBuffer->Begin(m_renderList[begin].sub.vertexCount);

		for(size_t i = begin; i < end; ++i)
		{
			const RenderUnit& unit = m_renderList[i];
			if(unit.sub.material_id != mat_id)
			{
				m_pGeometryBuffer->End();
				
				pMat = m_materials[mat_id];
			
				m_pRenderManager->SetMatrixBlock(pMat, world);

				Draw(pGraphics, pGeo, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());

				m_pGeometryBuffer->Begin(unit.sub.vertexCount);

				mat_id = unit.sub.material_id;
			}

			if(m_pGeometryBuffer->Push(unit.sub) == false)
			{
				m_pGeometryBuffer->End();

				pMat = m_materials[mat_id];
				
				m_pRenderManager->SetMatrixBlock(pMat, world);

				Draw(pGraphics, pGeo, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());

				m_pGeometryBuffer->Begin(unit.sub.vertexCount);

				m_pGeometryBuffer->Push(unit.sub);

				mat_id = unit.sub.material_id;
			}
		}

		m_pGeometryBuffer->End();

		pMat = m_materials[mat_id];
		
		m_pRenderManager->SetMatrixBlock(pMat, world);

		Draw(pGraphics, pGeo, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());

	}

	void VoxelWorldRendererImpl::_render_indexed(size_t begin, size_t end)
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
		
		uint32 mat_id = m_renderList[begin].sub.material_id;

		GeometryDataPtr pGeo = m_pGeometryBuffer->GetGeometryData();

		m_pGeometryBuffer->Begin(m_renderList[begin].sub.vertexCount);

		uint32 draw_count = 0;

		int index_count[1000];
		int base_verts[1000];
		void*  index[1000];

		int base_v = 0;
		int base_i = 0;


		struct VoxelVertex
		{
			math::Vector3										pos;
			math::Vector3										uv;
			float												ao;
			uint32												normal;
		};

		for(size_t i = begin; i < end; ++i)
		{
			const RenderUnit& unit = m_renderList[i];
			if(unit.sub.material_id != mat_id)
			{
				m_pGeometryBuffer->End();
				
				pMat = m_materials[mat_id];
			
				m_pRenderManager->SetMatrixBlock(pMat, world);

				MultiDrawIndexed(pGraphics, pGeo, pMat, draw_count, index_count, index, base_verts);
				
				draw_count	= 0;
				base_v		= 0;
				base_i		= 0;

				m_pGeometryBuffer->Begin(unit.sub.vertexCount);
				mat_id = unit.sub.material_id;
			}

			if(m_pGeometryBuffer->Push(unit.sub) == false)
			{
				m_pGeometryBuffer->End();

				pMat = m_materials[mat_id];
				
				m_pRenderManager->SetMatrixBlock(pMat, world);

				MultiDrawIndexed(pGraphics, pGeo, pMat, draw_count, index_count, index, base_verts);
				draw_count	= 0;
				base_v		= 0;
				base_i		= 0;

				m_pGeometryBuffer->Begin(unit.sub.vertexCount);

				m_pGeometryBuffer->Push(unit.sub);

				mat_id = unit.sub.material_id;
			}

			index_count[draw_count]		= unit.sub.indexCount;
			base_verts[draw_count]		= base_v + m_pGeometryBuffer->GetBaseVertex();

			index[draw_count]			= (void*)((base_i + m_pGeometryBuffer->GetBaseIndex()) * sizeof(uint16));

			draw_count++;

			base_v += unit.sub.vertexCount;
			base_i += unit.sub.indexCount;
		}

		m_pGeometryBuffer->End();

		pMat = m_materials[mat_id];
		
		m_pRenderManager->SetMatrixBlock(pMat, world);

	//	MultiDrawIndexed(pGraphics, pGeo, pMat, draw_count, index_count, index, base_verts);
		draw_count = 0;

		//Draw(pGraphics, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());
	}
	void VoxelWorldRendererImpl::_render_smg(size_t begin, size_t end, MaterialPtr pMaterial)
	{
		if(begin == end)
		{
			return;
		}
		
		MaterialPtr pMat = pMaterial;
		Sys_GraphicsPtr pGraphics = m_pRenderManager->GetSysGraphics();

		math::Matrix44 world = math::MatrixTranslation(m_renderList[begin].base.ToVector3());

		m_pRenderManager->SetMatrixBlock(pMat, world);

		using namespace voxel;

		GeometryDataPtr pGeo = m_pGeometryBuffer->GetGeometryData();

		m_pGeometryBuffer->Begin(m_renderList[begin].sub.vertexCount);

		for(size_t i = begin; i < end; ++i)
		{
			const RenderUnit& unit = m_renderList[i];

			if(m_pGeometryBuffer->Push(unit.sub) == false)
			{
				m_pGeometryBuffer->End();
				

				Draw(pGraphics, pGeo, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());

				m_pGeometryBuffer->Begin(unit.sub.vertexCount);

				m_pGeometryBuffer->Push(unit.sub);
			}
		}

		m_pGeometryBuffer->End();
		
		Draw(pGraphics, pGeo, pMat, m_pGeometryBuffer->GetBaseVertex(), m_pGeometryBuffer->GetVertexCount());

	}
	void VoxelWorldRendererImpl::RefreshMesh()
	{
		m_pWorldVP->RefreshMesh();
	}
	uint32 VoxelWorldRendererImpl::GetRenderedFaceCount()
	{
		return m_renderedVertex / 3;
	}
	uint32 VoxelWorldRendererImpl::GetRenderedVertexCount()
	{
		return m_renderedVertex;
	}
	uint32 VoxelWorldRendererImpl::GetRenderedVertexBytes()
	{
		return m_renderedVertex * sizeof(voxel::ChunkMesh::VoxelVertex); 
	}
	uint32 VoxelWorldRendererImpl::GetRenderedChunkCount()
	{
		return m_renderedChunk;
	}
}
