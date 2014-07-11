#include "package_atmosphere_pch.h"
#include "Impl_SkyDome.h"

namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			Impl_SkyDome::Impl_SkyDome(GameObjectManagerPtr pManager) : SkyDome(pManager)
			{
				SetVersion(g_packageVersion);
			}


			Impl_SkyDome::~Impl_SkyDome(void)
			{
			}
			bool Impl_SkyDome::OnAttach()
			{
				if(false == CreateSkyDome())
				{
					return false;
				}
				m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_SkyDome::on_event_frustum_cull, this, _1));


				return true;
			}
			void Impl_SkyDome::OnDetach()
			{
				m_pManager->RemoveEventHandler(m_hFrustumCull);
				m_pRD->material->Release();
				m_pRD->geometry->Release();
				m_pRD.reset();

			}
			bool Impl_SkyDome::CreateSkyDome()
			{
				std::vector<math::Vector3>	vb;
				std::vector<uint32>			ib;
				MeshUtil::CreateUnitIcoSphere(5, vb, ib, true);

				if(vb.size() == 0)
				{
					return false;
				}

				VertexLayout layout;
				layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

				m_pRD = m_pManager->alloc_object<RenderData>();

				m_pRD->geometry = m_pManager->GetRenderManager()->CreateGeometryData();

				m_pRD->geometry->BeginGeometry(PT_TRIANGLE_LIST);
				{
					if(false == m_pRD->geometry->AllocVertexBuffer(sizeof(math::Vector3) * vb.size(), vb.data(), false, layout))
					{
						return false;
					}
					if(false == m_pRD->geometry->AllocIndexBuffer(sizeof(uint32) * ib.size(), ib.data(), false, G_FORMAT_R32_UINT))
					{
						return false;
					}
				}
				m_pRD->geometry->EndGeometry();

				m_pRD->base_vertex = 0;
				m_pRD->vertex_count = vb.size();

				m_pRD->start_index = 0;
				m_pRD->index_count = ib.size();
				m_pRD->world_matrix.MakeIdentity();

				m_pRD->material = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/atmosphere/material/skydome.material");

				m_pWorldPos = m_pRD->material->GetParameterByName("world_pos");
				return true;
			}
			void Impl_SkyDome::on_event_frustum_cull(EventPtr pEvent)
			{
				m_pRD->world_matrix = m_pObject->GetWorldTransform();

				math::Vector3 pos = m_pRD->world_matrix.GetTranslation();

				m_pWorldPos->SetParameterVector(pos);

				m_pManager->GetRenderManager()->AddRenderData(layer_background, m_pRD);
			}
		}
	}

}