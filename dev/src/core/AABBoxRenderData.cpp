#include "core_pch.h"
#include "core/AABBoxRenderData.h"

#include "core_utils.h"
#include "core/Sys_Graphics.h"
#include "core/VertexFormat.h"
#include "core/RenderData.h"
#include "core/GeometryData.h"
#include "core/GPUBuffer.h"
#include "core/RenderManager.h"
#include "core/Material.h"

namespace ld3d
{

	AABBoxRenderData::AABBoxRenderData(void)
	{
		m_box.Make(math::Vector3(-1, -1, -1), math::Vector3(1, 1, 1));
	}


	AABBoxRenderData::~AABBoxRenderData(void)
	{
	}
	bool AABBoxRenderData::Initialize(RenderManagerPtr pRenderManager)
	{
		m_pRenderData = alloc_object<RenderData>();

		m_pRenderData->material = pRenderManager->CreateMaterialFromFile("./assets/standard/material/simple_line.material");

		if(m_pRenderData->material == nullptr)
		{
			return false;
		}

		VertexLayout vf;

		vf.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		
		m_pRenderData->geometry = pRenderManager->CreateGeometryData();

		if(m_pRenderData->geometry == nullptr)
		{
			return false;
		}
		m_pRenderData->geometry->BeginGeometry(PT_LINE_LIST);
		{
			m_pRenderData->geometry->AllocVertexBuffer(24 * sizeof(math::Vector3), nullptr, true, vf);
		}
		m_pRenderData->geometry->EndGeometry();

		m_pRenderData->vertex_count = 24;
		
		UpdateGeometry();


		return true;
	}
	void AABBoxRenderData::Release()
	{
		_release_and_reset(m_pRenderData->material);
		_release_and_reset(m_pRenderData->geometry);

		m_pRenderData.reset();
	}


	RenderDataPtr AABBoxRenderData::GetRenderData()
	{
		return m_pRenderData;
	}

	void AABBoxRenderData::SetBox(const math::AABBox& box)
	{
		m_box = box;
		UpdateGeometry();
	}
	void AABBoxRenderData::SetWorldMatrix(const math::Matrix44& world)
	{
		m_pRenderData->world_matrix = world;
	}
	void AABBoxRenderData::UpdateGeometry()
	{
		GPUBufferPtr pVB = m_pRenderData->geometry->GetVertexBuffer();
		math::Vector3* data = (math::Vector3*)pVB->Map(MAP_DISCARD);

		math::Vector3 min_v, max_v;

		min_v = m_box.GetMinCoord();
		max_v = m_box.GetMaxCoord();

		// verticle
		data[0] = min_v;
		data[1] = math::Vector3(min_v.x, max_v.y, min_v.z);

		data[2] = math::Vector3(max_v.x, min_v.y, min_v.z);
		data[3] = math::Vector3(max_v.x, max_v.y, min_v.z);

		data[4] = math::Vector3(max_v.x, min_v.y, max_v.z);
		data[5] = math::Vector3(max_v.x, max_v.y, max_v.z);

		data[6] = math::Vector3(min_v.x, min_v.y, max_v.z);
		data[7] = math::Vector3(min_v.x, max_v.y, max_v.z);

		// top
		data[8] = math::Vector3(min_v.x, max_v.y, min_v.z);
		data[9] = math::Vector3(max_v.x, max_v.y, min_v.z);

		data[10] = math::Vector3(max_v.x, max_v.y, min_v.z);
		data[11] = math::Vector3(max_v.x, max_v.y, max_v.z);

		data[12] = math::Vector3(max_v.x, max_v.y, max_v.z);
		data[13] = math::Vector3(min_v.x, max_v.y, max_v.z);

		data[14] = math::Vector3(min_v.x, max_v.y, min_v.z);
		data[15] = math::Vector3(min_v.x, max_v.y, max_v.z);


		// bottom
		data[16] = math::Vector3(min_v.x, min_v.y, min_v.z);
		data[17] = math::Vector3(max_v.x, min_v.y, min_v.z);

		data[18] = math::Vector3(max_v.x, min_v.y, min_v.z);
		data[19] = math::Vector3(max_v.x, min_v.y, max_v.z);

		data[20] = math::Vector3(max_v.x, min_v.y, max_v.z);
		data[21] = math::Vector3(min_v.x, min_v.y, max_v.z);

		data[22] = math::Vector3(min_v.x, min_v.y, min_v.z);
		data[23] = math::Vector3(min_v.x, min_v.y, max_v.z);


		pVB->Unmap();
	}
}
