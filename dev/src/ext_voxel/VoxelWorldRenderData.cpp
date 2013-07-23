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
	bool VoxelWorldRenderData::Initialize(RenderManagerPtr pRS)
	{
		m_pRenderData = std::make_shared<RenderData>();

		m_pRenderData->fr_draw = std::bind(&VoxelWorldRenderData::Render, this, std::placeholders::_1);
		m_pRenderData->dr_draw = std::bind(&VoxelWorldRenderData::Render, this, std::placeholders::_1);
		m_pRenderData->dr = false;

		m_pRenderManager = pRS;
		m_pGraphics = pRS->GetSysGraphics();
		m_pMaterial = m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/voxel_world.fx");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		m_vertexLayout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		m_vertexLayout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		m_vertexLayout.AddAttribute(G_FORMAT_R8G8B8A8_UNORM);
		

		m_pVertexBuffer = m_pGraphics->CreateBuffer(BT_VERTEX_BUFFER, m_nVBBytes, nullptr, true);
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

	void VoxelWorldRenderData::Render(RenderManagerPtr pManager)
	{

		if(m_pRenderList == nullptr)
		{
			return;
		}
		MaterialPtr pMat = m_pMaterial;

		VoxelWorldChunk* pChunk = m_pRenderList;
		
		
		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;
		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;

		uint8* data = nullptr;
		if(bytesLeft <= sizeof(VoxelVertex) * pChunk->vertex_count)
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
			if(pChunk->vertex_count == 0)
			{
				pChunk = pChunk->render_list_next;
				continue;
			}
			bytesLeft = m_nVBBytes - m_nVBCurrent;
			if(bytesLeft <= sizeof(VoxelVertex) * pChunk->vertex_count)
			{
				m_pVertexBuffer->Unmap();
				_draw(m_pGraphics, pMat);

				data = (uint8*)m_pVertexBuffer->Map(MAP_DISCARD);
				m_nVBOffset = 0;
				m_nVBCurrent = 0;
				bytesLeft = m_nVBBytes;
				m_nVertexCount = 0;
			}

			memcpy(data + m_nVBCurrent, pChunk->vertex_buffer, sizeof(VoxelVertex) * pChunk->vertex_count);
			
			m_nVBCurrent += sizeof(VoxelVertex) * pChunk->vertex_count;
			m_nVertexCount += pChunk->vertex_count;
			
			pChunk = pChunk->render_list_next;
		}

		m_pVertexBuffer->Unmap();

		_draw(m_pGraphics, pMat);

		m_pRenderList = nullptr;


		/*if(m_pRenderList == nullptr)
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

		m_pRenderList = nullptr;*/
	}
	void VoxelWorldRenderData::_draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{
		if(m_nVertexCount == 0)
		{
			return;
		}

		int nPass = pMaterial->Begin();

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);

			pSysGraphics->Draw(PT_TRIANGLE_LIST, m_pVertexBuffer, m_nVertexCount, 0, m_nVBOffset, m_vertexLayout);
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
	RenderDataPtr VoxelWorldRenderData::GetRenderData()
	{
		return m_pRenderData;
	}

}
