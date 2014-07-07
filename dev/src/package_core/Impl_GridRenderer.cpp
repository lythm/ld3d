#include "core_ext_pch.h"
#include "Impl_GridRenderer.h"


#include "Impl_MeshData.h"

#include "core/GameObject.h"

#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"
#include "core/GPUBuffer.h"
#include "CorePackage.h"
#include "core/Event.h"

namespace ld3d
{

	Impl_GridRenderer::Impl_GridRenderer(GameObjectManagerPtr pManager) : GridRenderer(pManager)
	{
		SetVersion(g_packageVersion);

		m_pRenderManager = m_pManager->GetRenderManager();

		m_gridSize						= 1;
		m_size							= 100;

		m_color							= math::Color4(0.6f, 0.6f, 0.6f, 1);

	}


	Impl_GridRenderer::~Impl_GridRenderer(void)
	{
	}


	void Impl_GridRenderer::Update(float dt)
	{
	}

	bool Impl_GridRenderer::OnAttach()
	{

		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_GridRenderer::on_event_frustum_cull, this, _1));

		

		RegisterProperty<uint32, Impl_GridRenderer>(this,
			"Size", 
			&Impl_GridRenderer::GetSize,
			&Impl_GridRenderer::SetSize);

		RegisterProperty<uint32, Impl_GridRenderer>(this,
			"Grid Size", 
			&Impl_GridRenderer::GetGridSize,
			&Impl_GridRenderer::SetGridSize);

		RegisterProperty<math::Color4, Impl_GridRenderer>(this,
			"Color", 
			&Impl_GridRenderer::GetColor,
			&Impl_GridRenderer::SetColor);


		ResetGrid();

		return true;
	}
	void Impl_GridRenderer::OnDetach()
	{
		ClearPropertySet();
		m_pManager->RemoveEventHandler(m_hFrustumCull);


		m_pRenderData->geometry->Release();
		m_pRenderData->material->Release();

		m_pRenderManager.reset();

	}
	void Impl_GridRenderer::on_event_frustum_cull(EventPtr pEvent)
	{
		m_pRenderData->world_matrix = m_pObject->GetWorldTransform();

		if(m_pParamColor)
		{
			m_pParamColor->SetParameterColor(m_color);
		}

		m_pRenderManager->AddRenderData(layer_forward, m_pRenderData);

	}
	void Impl_GridRenderer::SetSize(uint32 size)
	{
		m_size = size;

		ResetGrid();
	}
	void Impl_GridRenderer::SetGridSize(uint32 gridSize)
	{
		m_gridSize = gridSize;
		ResetGrid();
	}

	uint32 Impl_GridRenderer::GetSize()
	{
		return m_size;
	}
	uint32 Impl_GridRenderer::GetGridSize()
	{
		return m_gridSize;
	}
	void Impl_GridRenderer::ResetGrid()
	{
		if(m_pRenderData == nullptr)
		{
			m_pRenderData = std::make_shared<RenderData>();
		}
		

		Sys_GraphicsPtr pGraphics = m_pRenderManager->GetSysGraphics();

		uint32 vb_bytes = sizeof(math::Vector3) * ((m_size / m_gridSize + 1) * 4);
		GPUBufferPtr pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, vb_bytes, NULL, true);

		m_pRenderData->vertex_count = (m_size / m_gridSize + 1) * 4;

		math::Vector3* pBuffer = (math::Vector3*)pVB->Map(MAP_DISCARD, 0, vb_bytes);

		math::Vector3* pBufferData = pBuffer;

		for(int i = 0; i < (m_size / m_gridSize + 1); ++i)
		{
			math::Vector3* vertex = pBuffer + i;

			vertex->x = -m_size/2 + m_gridSize * i;
			vertex->y = 0;
			vertex->z = m_size/2;
		}

		pBuffer += (m_size / m_gridSize + 1);
		for(int i = 0; i < (m_size / m_gridSize + 1); ++i)
		{
			math::Vector3* vertex = pBuffer + i;

			vertex->x = -m_size/2 + m_gridSize * i;
			vertex->y = 0;
			vertex->z = -m_size/2;
		}
		pBuffer += (m_size / m_gridSize + 1);



		for(int i = 0; i < (m_size / m_gridSize + 1); ++i)
		{
			math::Vector3* vertex = pBuffer + i;

			vertex->x = -m_size/2;
			vertex->y = 0;
			vertex->z = m_size/2 - m_gridSize * i;
		}
		pBuffer += (m_size / m_gridSize + 1);


		for(int i = 0; i < (m_size / m_gridSize + 1); ++i)
		{
			math::Vector3* vertex = pBuffer + i;

			vertex->x = m_size/2;
			vertex->y = 0;
			vertex->z = m_size/2 - m_gridSize * i;
		}

		pVB->Unmap();


		int line_count = (m_size / m_gridSize + 1) + (m_size / m_gridSize + 1) ;
		int index_count = line_count * 2;
		GPUBufferPtr pIB = pGraphics->CreateBuffer(BT_INDEX_BUFFER, index_count * sizeof(uint16), NULL, true);

		uint16 * pStart = (uint16*)pIB->Map(MAP_DISCARD, 0, index_count * sizeof(uint16));

		uint16 * pData = pStart;

		for(int i = 0; i < (m_size / m_gridSize + 1); ++i)
		{
			*(pStart + 2* i) = i;
			*(pStart + 2* i + 1) = i + m_size / m_gridSize + 1;
		}

		pStart += 2 * (m_size / m_gridSize + 1);
		for(int i = 0; i < (m_size / m_gridSize + 1) ; ++i)
		{
			*(pStart + 2* i) = i + 2 * (m_size / m_gridSize + 1);
			*(pStart + 2* i + 1) = i + m_size / m_gridSize + 1 + 2 * (m_size / m_gridSize + 1);
		}

		pIB->Unmap();

		if(m_pRenderData->material == nullptr)
		{
			m_pRenderData->material = m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/simple_line.material");
		}

		m_pParamColor = m_pRenderData->material->GetParameterByName("line_color");

		if(m_pRenderData->geometry)
		{
			m_pRenderData->geometry->Release();
		}

		m_pRenderData->geometry = m_pRenderManager->CreateGeometryData();

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pRenderData->geometry->BeginGeometry(PT_LINE_LIST);
		{
			m_pRenderData->geometry->AttachVertexBuffer(pVB, layout);
			m_pRenderData->geometry->AttachIndexBuffer(pIB, G_FORMAT_R16_UINT);
		}
		m_pRenderData->geometry->EndGeometry();
		m_pRenderData->index_count = index_count;

	}
	void Impl_GridRenderer::SetColor(const math::Color4& clr)
	{
		m_color = clr;
	}

	const math::Color4&	Impl_GridRenderer::GetColor() const
	{
		return m_color;
	}
}

