#include "core_ext_pch.h"
#include "Impl_MeshRenderer.h"

#include "Impl_MeshData.h"

#include "core/GameObject.h"

#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"
#include "core/Mesh.h"
#include "core/GPUBuffer.h"
#include "core/SubMesh.h"

#include "CorePackage.h"

#include "core/Event.h"


namespace ld3d
{

	Impl_MeshRenderer::Impl_MeshRenderer(GameObjectManagerPtr pManager) : MeshRenderer(pManager)
	{
		m_deferred = true;
		m_pRenderManager = m_pManager->GetRenderManager();

		SetVersion(g_packageVersion);

	}

	Impl_MeshRenderer::~Impl_MeshRenderer(void)
	{
	}
	
	void Impl_MeshRenderer::SetDeferred(const bool& b)
	{
		m_deferred = b;
	}
	const bool& Impl_MeshRenderer::IsDeferred()
	{
		return m_deferred;
	}
	void Impl_MeshRenderer::Update(float dt)
	{
	}
	
	bool Impl_MeshRenderer::OnAttach()
	{
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pObject->GetComponent("MeshData"));

		if(pMD == MeshDataPtr())
		{
			return false;
		}
		Reset(pMD);

		

		RegisterProperty<bool, Impl_MeshRenderer>(this,
			"Deferred", 
			&Impl_MeshRenderer::IsDeferred,
			&Impl_MeshRenderer::SetDeferred);

		


		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_MeshRenderer::on_event_frustum_cull, this, _1));

		return true;
	}
	void Impl_MeshRenderer::OnDetach()
	{
		ClearPropertySet();
		m_pManager->RemoveEventHandler(m_hFrustumCull);

		m_pRenderManager.reset();

		for(auto v: m_Subsets)
		{
			v->geometry->Release();
			v->material->Release();
		}
		m_Subsets.clear();
	}
	void Impl_MeshRenderer::on_event_frustum_cull(EventPtr pEvent)
	{
		const math::Matrix44& world = m_pObject->GetWorldTransform();
		for(size_t i = 0; i < m_Subsets.size(); ++i)
		{
			m_Subsets[i]->world_matrix = world;
			m_pRenderManager->AddRenderData(m_Subsets[i]);
		}
	}
	void Impl_MeshRenderer::Reset(MeshDataPtr pMD)
	{
		if(pMD == NULL)
		{
			return;
		}

		MeshPtr pMesh = pMD->GetMesh();
		if(pMesh == nullptr)
		{
			return;
		}

		for(auto v: m_Subsets)
		{
			v->geometry->Release();
			v->material->Release();
		}
		
		m_Subsets.clear();

		void* indexData = pMesh->GetIndexData();
		void* vertexData = pMesh->GetVertexData();
		
		for(int i = 0; i < pMesh->GetSubMeshCount(); ++i)
		{
			SubMeshPtr pSub = pMesh->GetSubMesh(i);

			RenderDataPtr pRD = m_pManager->alloc_object<RenderData>();

			pRD->geometry = m_pRenderManager->CreateGeometryData();


			pRD->geometry->BeginGeometry(pSub->GetPrimitiveType());
			{
				pRD->geometry->AllocVertexBuffer(pSub->GetVertexDataBytes(), 
							(uint8*)vertexData + pSub->GetVertexDataOffset(), 
							false, 
							pSub->GetVertexFormat());

				if(indexData)
				{
					pRD->geometry->AllocIndexBuffer(pSub->GetIndexDataBytes(), 
							(uint8*)indexData + pSub->GetIndexDataOffset(), 
							false,
							pSub->GetIndexFormat());
				}
			}
			pRD->geometry->EndGeometry();

			pRD->base_vertex = 0;
			pRD->vertex_count = pSub->GetVertexCount();
			pRD->index_count = pSub->GetIndexCount();
			pRD->material = pSub->GetMaterial();
			pRD->dr = m_deferred;
			pRD->world_matrix = m_pObject->GetWorldTransform();
			pRD->start_index = 0;
			m_Subsets.push_back(pRD);
		}
	}
}
