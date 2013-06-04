#include "voxel_pch.h"
#include "VoxelWorldRenderData.h"

namespace ld3d
{
	VoxelWorldRenderData::VoxelWorldRenderData(void)
	{
		m_nVBBytes						= 1024 * 1024 * 4;
		m_nVBCurrent					= 0;

		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_nVBOffset						= 0;
	}


	VoxelWorldRenderData::~VoxelWorldRenderData(void)
	{
	}
	bool VoxelWorldRenderData::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
		m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/voxel_world.fx");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		VertexFormat vf;
		vf.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		vf.AddElement(VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32_FLOAT));
		m_pMaterial->SetVertexFormat(vf);

		m_pVertexBuffer = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, m_nVBBytes, nullptr, true);
		if(m_pVertexBuffer == nullptr)
		{
			return false;
		}
		m_nVBCurrent = 0;
		m_nVBOffset = 0;
		m_nVertexStride = sizeof(VoxelVertex);
		return true;
	}
	void VoxelWorldRenderData::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
		if(m_pIndexBuffer)
		{
			m_pIndexBuffer->Release();
			m_pIndexBuffer.reset();
		}
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer.reset();
		}
		m_pGraphics.reset();
	}

	void VoxelWorldRenderData::Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{
		if(m_nVertexCount == 0)
		{
			return;
		}
		pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_nVBOffset, m_nVertexStride);
		pSysGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		MaterialPtr pMat = pMaterial == nullptr ? m_pMaterial : pMaterial;

		pMat->ApplyVertexFormat();

		int nPass = 0;

		pMat->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			
			pMat->ApplyPass(i);

			pSysGraphics->Draw(m_nVertexCount, 0);
		}

		pMat->End();
	}
	MaterialPtr VoxelWorldRenderData::GetMaterial()
	{
		return m_pMaterial;
	}
	math::Matrix44 VoxelWorldRenderData::GetWorldMatrix()
	{
		return math::MatrixIdentity();
	}
	bool VoxelWorldRenderData::IsDeferred()
	{
		return true;
	}
	void VoxelWorldRenderData::PrepareData(const std::vector<VoxelFace>& data)
	{
	}
}
