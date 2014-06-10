#include "core_ext_pch.h"
#include "Impl_SkyBox.h"

namespace ld3d
{
	Impl_SkyBox::Impl_SkyBox(GameObjectManagerPtr pManager) : SkyBox(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_SkyBox::~Impl_SkyBox(void)
	{
	}
	void Impl_SkyBox::Update(float dt)
	{
		

	}

	bool Impl_SkyBox::OnAttach()
	{
		m_pRD = m_pManager->alloc_object<RenderData>();

		
		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		
		float size = 1.0f;
		int nVerts = 36;

		math::Vector3 verts[] = 
		{
			math::Vector3(-size, size, -size),
			math::Vector3(size, -size, -size),
			math::Vector3(size, size, -size),

			math::Vector3(-size, size, -size),
			math::Vector3(-size, -size, -size),
			math::Vector3(size, -size, -size),

			math::Vector3(-size, size, size),
			math::Vector3(size, size, size),
			math::Vector3(size, -size, size),

			math::Vector3(-size, size, size),
			math::Vector3(size, -size, size),
			math::Vector3(-size, -size, size),


			math::Vector3(-size, size, size),
			math::Vector3(size, size, -size),
			math::Vector3(size, size, size),

			math::Vector3(-size, size, size),
			math::Vector3(-size, size, -size),
			math::Vector3(size, size, -size),


			math::Vector3(-size, -size, size),
			math::Vector3(size, -size, size),
			math::Vector3(size, -size, -size),

			math::Vector3(-size, -size, size),
			math::Vector3(size, -size, -size),
			math::Vector3(-size, -size, -size),


			math::Vector3(-size, size, size),
			math::Vector3(-size, -size, -size),
			math::Vector3(-size, size, -size),

			math::Vector3(-size, size, size),
			math::Vector3(-size, -size, size),
			math::Vector3(-size, -size, -size),


			math::Vector3(size, size, size),
			math::Vector3(size, size, -size),
			math::Vector3(size, -size, -size),

			math::Vector3(size, size, size),
			math::Vector3(size, -size, -size),
			math::Vector3(size, -size, size),

		};

		m_pRD->geometry = m_pManager->GetRenderManager()->CreateGeometryData();

		m_pRD->geometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pRD->geometry->AllocVertexBuffer(sizeof(math::Vector3) * 36, verts, false, layout);
		}
		m_pRD->geometry->EndGeometry();

		m_pRD->base_vertex = 0;
		m_pRD->index_count = 0;
		m_pRD->start_index = 0;
		m_pRD->vertex_count = 36;
		m_pRD->world_matrix.MakeIdentity();

		m_pRD->material = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/skybox.material");

		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_SkyBox::on_event_frustum_cull, this, _1));


		m_pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/standard/texture/001.dds");

		MaterialParameterPtr pParam = m_pRD->material->GetParameterByName("sky_map");
		
		pParam->SetParameterTexture(m_pTex);
		
		m_pWorldPos = m_pRD->material->GetParameterByName("world_pos");
		return true;
	}
	void Impl_SkyBox::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
		m_pTex->Release();
		m_pRD->material->Release();
		m_pRD->geometry->Release();
		m_pRD.reset();
	}
	void Impl_SkyBox::on_event_frustum_cull(EventPtr pEvent)
	{
		m_pRD->world_matrix = m_pObject->GetWorldTransform();

		math::Vector3 pos = m_pRD->world_matrix.GetTranslation();
		
		m_pWorldPos->SetParameterVector(pos);
		
		m_pManager->GetRenderManager()->AddRenderData(layer_sky, m_pRD);
	}
}
