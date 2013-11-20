#include "voxel_pch.h"
#include "VoxelWorldMesh.h"

namespace ld3d
{
	VoxelWorldMesh::VoxelWorldMesh(void)
	{
		m_pVertexBuffer				= nullptr;
		m_nVertexCount				= 0;
		m_vertexBufferBytes			= 0;

	}


	VoxelWorldMesh::~VoxelWorldMesh(void)
	{
	}
	bool VoxelWorldMesh::Reset()
	{
		m_nVertexCount				= 0;
		
		m_subsets.clear();

		return true;
	}
	bool VoxelWorldMesh::AllocVertexBuffer(uint32 nVerts)
	{
		uint32 bytes_need = nVerts * sizeof(VoxelVertex);

		if((bytes_need) > m_vertexBufferBytes)
		{
			if(m_pVertexBuffer)
			{
				delete m_pVertexBuffer;
			}
			m_pVertexBuffer = new uint8[bytes_need];
			m_vertexBufferBytes = bytes_need;
		}

		m_nVertexCount = nVerts;

		return true;
	}
	void* VoxelWorldMesh::GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}
	uint32 VoxelWorldMesh::GetVertexCount()
	{
		return m_nVertexCount;
	}
	void VoxelWorldMesh::Release()
	{
		if(m_pVertexBuffer)
		{
			delete m_pVertexBuffer;
			m_pVertexBuffer = nullptr;
		}

		m_subsets.clear();
	}
	void VoxelWorldMesh::AddSubset(const Subset& sub)
	{
		m_subsets.push_back(sub);
	}
	uint32 VoxelWorldMesh::GetSubsetCount()
	{
		return (uint32)m_subsets.size();
	}
	const VoxelWorldMesh::Subset& VoxelWorldMesh::GetSubset(uint32 index)
	{
		return m_subsets[index];
	}
}


