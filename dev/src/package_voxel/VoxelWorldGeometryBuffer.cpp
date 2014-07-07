#include "voxel_pch.h"
#include "VoxelWorldGeometryBuffer.h"

namespace ld3d
{

	VoxelWorldGeometryBuffer::VoxelWorldGeometryBuffer(void)
	{
		m_nVBBytes						= 1024 * 1024 * 8;
		m_nVBCurrent					= 0;
		m_nVBOffset						= 0;
		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_pData							= nullptr;
		m_baseVertex					= 0;
	}


	VoxelWorldGeometryBuffer::~VoxelWorldGeometryBuffer(void)
	{
	}
	bool VoxelWorldGeometryBuffer::Initialize(RenderManagerPtr pRenderManager, uint32 nVerts)
	{
		m_pRenderManager	= pRenderManager;
		m_nVBBytes			= nVerts * sizeof(voxel::ChunkMesh::VoxelVertex);
		m_pData				= nullptr;

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32_UINT);
		
		m_pGeometry = m_pRenderManager->CreateGeometryData();
		
		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			if(false == m_pGeometry->AllocVertexBuffer(m_nVBBytes, nullptr, true, layout))
			{
				return false;
			}
		}
		m_pGeometry->EndGeometry();

		m_nVBCurrent			= 0;
		m_nVBOffset				= 0;
		m_nVertexStride			= layout.VertexStride();
		m_nVertexCount			= 0;
		m_baseVertex			= 0;
		m_pVB = m_pGeometry->GetVertexBuffer();

		return true;
	}
	void VoxelWorldGeometryBuffer::Release()
	{
		m_pVB.reset();
		_release_and_reset(m_pGeometry);
	}

	void VoxelWorldGeometryBuffer::Begin(uint32 verts_at_least)
	{
		m_nVertexCount = 0;
		m_nVBOffset = m_nVBCurrent;

		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		
		m_pData = nullptr;
		if(bytesLeft <= (verts_at_least * sizeof(voxel::ChunkMesh::VoxelVertex)))
		{
			m_pData = (uint8*)m_pVB->Map(MAP_DISCARD, 0, m_nVBBytes);
			m_nVBOffset = 0;
			m_nVBCurrent = 0;
		}
		else
		{
			m_pData = (uint8*)m_pVB->Map(MAP_NO_OVERWRITE, m_nVBCurrent, m_nVBBytes - m_nVBCurrent);
		}

		m_baseVertex = m_nVBOffset / m_nVertexStride;
	}
	void VoxelWorldGeometryBuffer::End()
	{
		m_pData = nullptr;
		m_pVB->Unmap();
	}
	bool VoxelWorldGeometryBuffer::Push(const voxel::ChunkMesh::Subset& sub)
	{
		using namespace voxel;

		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * sub.vertexCount)
		{
			return false;
		}

		memcpy(m_pData + m_nVBCurrent - m_nVBOffset, sub.vertexBuffer, sizeof(ChunkMesh::VoxelVertex) * sub.vertexCount);

		m_nVBCurrent += sizeof(ChunkMesh::VoxelVertex) * sub.vertexCount;
		m_nVertexCount += sub.vertexCount;
		return true;
	}
	GeometryDataPtr VoxelWorldGeometryBuffer::GetGeometryData()
	{
		return m_pGeometry;
	}
	uint32 VoxelWorldGeometryBuffer::GetVertexCount()
	{
		return m_nVertexCount;
	}
	uint32 VoxelWorldGeometryBuffer::GetBaseVertex()
	{
		return m_baseVertex;
	}
}
