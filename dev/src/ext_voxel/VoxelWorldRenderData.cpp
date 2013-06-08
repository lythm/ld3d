#include "voxel_pch.h"
#include "VoxelWorldRenderData.h"
#include "VoxelWorldChunk.h"

namespace ld3d
{
	VoxelWorldRenderData::VoxelWorldRenderData(void)
	{
		m_nVBBytes						= 1024 * 1024 * 4;
		m_nVBCurrent					= 0;

		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_nVBOffset						= 0;

		m_pRenderList					= nullptr;
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
		if(m_pRenderList == nullptr)
		{
			return;
		}
		MaterialPtr pMat = pMaterial == nullptr ? m_pMaterial : pMaterial;

		VoxelWorldChunk* pChunk = m_pRenderList;
		
		
		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;
		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;

		uint8* data = nullptr;
		if(bytesLeft <= sizeof(VoxelVertex) * 6)
		{
			data = (uint8*)m_pVertexBuffer->Map(MAP_DISCARD);
			m_nVBOffset = 0;
			m_nVBCurrent = 0;
			bytesLeft = m_nVBBytes;
		}
		else
		{
			data = (uint8*)m_pVertexBuffer->Map(MAP_NO_OVERWRITE);
		}

		while(pChunk)
		{
			for(size_t i = 0; i < pChunk->mesh.size(); ++i)
			{
				bytesLeft = m_nVBBytes - m_nVBCurrent;
				if(bytesLeft <= sizeof(VoxelVertex) * 6)
				{
					m_pVertexBuffer->Unmap();
					_draw(pSysGraphics, pMat);

					data = (uint8*)m_pVertexBuffer->Map(MAP_DISCARD);
					m_nVBOffset = 0;
					m_nVBCurrent = 0;
					bytesLeft = m_nVBBytes;
					m_nVertexCount = 0;
				}


				const VoxelFace& face = pChunk->mesh[i];
				VoxelVertex vert[6];
				
				vert[0].pos = face.verts[0];
				vert[1].pos = face.verts[1];
				vert[2].pos = face.verts[2];

				vert[3].pos = face.verts[1];
				vert[4].pos = face.verts[3];
				vert[5].pos = face.verts[2];


				for(int ivert = 0; ivert < 6; ++ivert)
				{
					vert[ivert].normal = face.normal;
				}
				
				memcpy(data + m_nVBCurrent, &vert, sizeof(VoxelVertex) * 6);
				m_nVBCurrent += sizeof(VoxelVertex) * 6;
				m_nVertexCount += 6;
			}
			pChunk = pChunk->render_list_next;
		}

		m_pVertexBuffer->Unmap();

		_draw(pSysGraphics, pMat);

		m_pRenderList = nullptr;
	}
	void VoxelWorldRenderData::_draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{

		if(m_nVertexCount == 0)
		{
			return;
		}

		pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_nVBOffset, m_nVertexStride);
		pSysGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pMaterial->ApplyVertexFormat();

		int nPass = 0;

		pMaterial->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			
			pMaterial->ApplyPass(i);

			pSysGraphics->Draw(m_nVertexCount, 0);
		}

		pMaterial->End();
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
	void VoxelWorldRenderData::PrepareRenderList(VoxelWorldChunk* pList)
	{
		m_pRenderList = pList;
	}
}
