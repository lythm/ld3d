#include "core_ext_pch.h"
#include "..\..\include\core\ext\MeshRenderer.h"
#include "core\GameObject.h"
#include "core\ext\MeshData.h"
#include "core\RenderManager.h"
#include "core\Sys_Graphics.h"
#include "core\Mesh.h"
#include "core\GPUBuffer.h"
#include "core\SubMesh.h"
#include "core\ext\PropertyManager.h"

#include "CorePackage.h"

#include "core\Event.h"


namespace ld3d
{

	MeshRenderer::MeshRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"MeshRenderer", pManager)
	{
		m_deferred = true;
		m_pRenderManager = m_pManager->GetRenderManager();

		SetVersion(g_packageVersion);

	}

	MeshRenderer::~MeshRenderer(void)
	{
	}
	
	void MeshRenderer::SetDeferred(const bool& b)
	{
		m_deferred = b;
	}
	const bool& MeshRenderer::IsDeferred()
	{
		return m_deferred;
	}
	void MeshRenderer::Update(float dt)
	{
	}
	
	bool MeshRenderer::OnAttach()
	{
		MeshDataPtr pMD = std::dynamic_pointer_cast<MeshData>(m_pObject->GetComponent(L"MeshData"));

		if(pMD == MeshDataPtr())
		{
			return false;
		}
		Reset(pMD);

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		pPM->Begin(L"MeshRenderer");

		pPM->RegisterProperty<bool, MeshRenderer>(this,
			L"Deferred", 
			&MeshRenderer::IsDeferred,
			&MeshRenderer::SetDeferred);

		pPM->End();


		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&MeshRenderer::on_event_frustum_cull, this, _1));

		return true;
	}
	void MeshRenderer::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);

		m_pRenderManager.reset();

		for(auto v: m_Subsets)
		{
			v->geometry->Release();
			v->material->Release();
		}
		m_Subsets.clear();
	}
	void MeshRenderer::on_event_frustum_cull(EventPtr pEvent)
	{
		const math::Matrix44& world = m_pObject->GetWorldTransform();
		for(size_t i = 0; i < m_Subsets.size(); ++i)
		{
			m_Subsets[i]->world_matrix = world;
			m_pRenderManager->AddRenderData(m_Subsets[i]);
		}
	}
	void MeshRenderer::Reset(MeshDataPtr pMD)
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

			RenderData2Ptr pRD = m_pManager->alloc_object<RenderData2>();

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
