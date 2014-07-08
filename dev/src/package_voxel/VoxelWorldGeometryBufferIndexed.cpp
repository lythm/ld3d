#include "voxel_pch.h"
#include "VoxelWorldGeometryBufferIndexed.h"

namespace ld3d
{
	VoxelWorldGeometryBufferIndexed::VoxelWorldGeometryBufferIndexed(void)
	{
		m_nVBBytes						= 1024 * 1024 * 8;
		m_nVBCurrent					= 0;
		m_nVBOffset						= 0;
		m_nVertexStride					= 0;
		m_nVertexCount					= 0;
		m_pVBData						= nullptr;
		m_baseVertex					= 0;

		m_nIBBytes						= 1024 * 1024 * 2;
		m_nIBOffset						= 0;
		m_nIBCurrent					= 0;
		m_nIndexCount					= 0;
		m_pIBData						= nullptr;
		m_baseIndex						= 0;
	}

	VoxelWorldGeometryBufferIndexed::~VoxelWorldGeometryBufferIndexed(void)
	{
	}
	bool VoxelWorldGeometryBufferIndexed::Initialize(RenderManagerPtr pRenderManager, uint32 nVerts)
	{
		m_pRenderManager	= pRenderManager;
		m_nVBBytes			= nVerts * sizeof(voxel::ChunkMesh::VoxelVertex);
		m_nIBBytes			= (nVerts * 6 / 4) * sizeof(uint16);

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32_FLOAT);
		
		m_pGeometry = m_pRenderManager->CreateGeometryData();
		
		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			if(false == m_pGeometry->AllocVertexBuffer(m_nVBBytes, nullptr, true, layout))
			{
				return false;
			}


			if(false == m_pGeometry->AllocIndexBuffer(m_nIBBytes, nullptr, true, G_FORMAT_R16_UINT))
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
		m_pVB					= m_pGeometry->GetVertexBuffer();
		m_pVBData				= nullptr;


		m_nIBOffset				= 0;
		m_nIBCurrent			= 0;
		m_nIndexCount			= 0;
		m_pIBData				= nullptr;
		
		m_pIB					= m_pGeometry->GetIndexBuffer();
		return true;
	}
	void VoxelWorldGeometryBufferIndexed::Release()
	{
		m_pVB.reset();
		m_pIB.reset();
		_release_and_reset(m_pGeometry);
	}
	void VoxelWorldGeometryBufferIndexed::Begin(uint32 verts_at_least)
	{
		m_nVertexCount		= 0;
		m_nVBOffset			= m_nVBCurrent;

		m_nIndexCount		= 0;
		m_nIBOffset			= m_nIBCurrent;

		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		
		m_pIBData = nullptr;
		m_pVBData = nullptr;


		if(bytesLeft <= (verts_at_least * sizeof(voxel::ChunkMesh::VoxelVertex)))
		{
			m_pVBData = (uint8*)m_pVB->Map(MAP_DISCARD, 0, m_nVBBytes);
			m_nVBOffset			= 0;
			m_nVBCurrent		= 0;

			m_pIBData = (uint8*)m_pIB->Map(MAP_DISCARD, 0, m_nIBBytes);
			m_nIBOffset			= 0;
			m_nIBCurrent		= 0;
		}
		else
		{
			m_pVBData = (uint8*)m_pVB->Map(MAP_NO_OVERWRITE, m_nVBCurrent, m_nVBBytes - m_nVBCurrent);

			m_pIBData = (uint8*)m_pIB->Map(MAP_NO_OVERWRITE, m_nIBCurrent, m_nIBBytes - m_nIBCurrent);
		}

		m_baseVertex = m_nVBOffset / m_nVertexStride;
		
		m_baseIndex	= m_nIBOffset / sizeof(uint16);
	}
	void VoxelWorldGeometryBufferIndexed::End()
	{
		m_pVBData = nullptr;
		m_pVB->Unmap();

		m_pIBData = nullptr;
		m_pIB->Unmap();

		m_pGeometry->CommitModify();
	}
	bool VoxelWorldGeometryBufferIndexed::Push(const voxel::ChunkMesh::Subset& sub)
	{
		using namespace voxel;

		uint32 bytesLeft = m_nVBBytes - m_nVBCurrent;
		if(bytesLeft <= sizeof(ChunkMesh::VoxelVertex) * sub.vertexCount)
		{
			return false;
		}

		ChunkMesh::VoxelVertex* pData = (ChunkMesh::VoxelVertex*)sub.vertexBuffer;

		uint32 bytes_copy = sizeof(ChunkMesh::VoxelVertex) * sub.vertexCount;
		memcpy(m_pVBData + m_nVBCurrent - m_nVBOffset, sub.vertexBuffer, bytes_copy);

		m_nVBCurrent		+= bytes_copy;
		m_nVertexCount		+= sub.vertexCount;

		bytes_copy = sizeof(uint16) * sub.indexCount;
		memcpy(m_pIBData + m_nIBCurrent - m_nIBOffset, sub.indexBuffer, bytes_copy);
				
		m_nIBCurrent		+= bytes_copy;
		m_nIndexCount		+= sub.indexCount;

		return true;
	}
	GeometryDataPtr VoxelWorldGeometryBufferIndexed::GetGeometryData()
	{
		return m_pGeometry;
	}
	uint32 VoxelWorldGeometryBufferIndexed::GetVertexCount()
	{
		return m_nVertexCount;
	}
	uint32 VoxelWorldGeometryBufferIndexed::GetBaseVertex()
	{
		return m_baseVertex;
	}
	uint32 VoxelWorldGeometryBufferIndexed::GetIndexCount()
	{
		return m_nIndexCount;
	}
	uint32 VoxelWorldGeometryBufferIndexed::GetBaseIndex()
	{
		return m_baseIndex;
	}
}
