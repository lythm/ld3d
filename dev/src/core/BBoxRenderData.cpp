#include "core_pch.h"
#include "..\..\include\core\BBoxRenderData.h"
#include "core\Sys_Graphics.h"
#include "core\VertexFormat.h"
#include "core\Material.h"
#include "core\GPUBuffer.h"

namespace ld3d
{
	BBoxRenderData::BBoxRenderData(void)
	{
	}


	BBoxRenderData::~BBoxRenderData(void)
	{
	}
	bool BBoxRenderData::Initialize(Sys_Graphics2Ptr pGraphics)
	{
		/*m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/editor_grid.fx");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		VertexFormat vf;
		vf.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		m_pMaterial->SetVertexFormat(vf);

		m_pVertexBuffer = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, 24 * sizeof(math::Vector3), nullptr, true);
		if(m_pVertexBuffer == nullptr)
		{
			return false;
		}*/
		return true;
	}
	void BBoxRenderData::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
		
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer.reset();
		}

	}

	void BBoxRenderData::Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{
		MaterialPtr pMat = pMaterial == nullptr ? m_pMaterial : pMaterial;

		pSysGraphics->SetVertexBuffer(m_pVertexBuffer, 0, sizeof(math::Vector3));
		pSysGraphics->SetPrimitiveType(PT_LINE_LIST);

		pMat->ApplyVertexFormat();

		int nPass = 0;

		pMat->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			
			pMat->ApplyPass(i);

			pSysGraphics->Draw(24, 0);
		}

		pMat->End();
	}
	
	MaterialPtr BBoxRenderData::GetMaterial()
	{
		return m_pMaterial;
	}
	math::Matrix44 BBoxRenderData::GetWorldMatrix()
	{
		return m_world;
	}
	bool BBoxRenderData::IsDeferred()
	{
		return false;
	}
	void BBoxRenderData::SetBBox(const math::AABBox& box)
	{
		m_bbox = box;
		_fill_vb();
	}
	void BBoxRenderData::SetWorldMatrix(const math::Matrix44& world)
	{
		m_world = world;
	}
	void BBoxRenderData::_fill_vb()
	{
		math::Vector3* data = (math::Vector3*)m_pVertexBuffer->Map(MAP_DISCARD);

		math::Vector3 min_v, max_v;

		min_v = m_bbox.GetMinCoord();
		max_v = m_bbox.GetMaxCoord();

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


		m_pVertexBuffer->Unmap();
	}
}
