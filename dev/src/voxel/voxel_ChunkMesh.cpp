#include "voxel_pch.h"
#include "voxel/voxel_ChunkMesh.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_Chunk.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkMesh::ChunkMesh(void)
		{
			m_pVertexBuffer				= nullptr;
			m_nVertexCount				= 0;
			m_vertexBufferBytes			= 0;

		}


		ChunkMesh::~ChunkMesh(void)
		{
			if(m_pVertexBuffer)
			{
				GetAllocator()->Free(m_pVertexBuffer);
				m_pVertexBuffer = nullptr;
			}

			m_subsets.clear();
		}
		bool ChunkMesh::Reset()
		{
			m_nVertexCount				= 0;

			m_subsets.clear();

			return true;
		}
		bool ChunkMesh::AllocVertexBuffer(uint32 nVerts)
		{
			uint32 bytes_need = nVerts * sizeof(VoxelVertex);

			if((bytes_need) > m_vertexBufferBytes)
			{
				if(m_pVertexBuffer)
				{
					GetAllocator()->Free(m_pVertexBuffer);
				}
				m_pVertexBuffer = GetAllocator()->Alloc(bytes_need);
				m_vertexBufferBytes = bytes_need;
			}

			m_nVertexCount = nVerts;

			return true;
		}
		void* ChunkMesh::GetVertexBuffer()
		{
			return m_pVertexBuffer;
		}
		uint32 ChunkMesh::GetVertexCount()
		{
			return m_nVertexCount;
		}
		
		void ChunkMesh::AddSubset(const Subset& sub)
		{
			m_subsets.push_back(sub);
		}
		uint32 ChunkMesh::GetSubsetCount()
		{
			return (uint32)m_subsets.size();
		}
		const ChunkMesh::Subset& ChunkMesh::GetSubset(uint32 index)
		{
			return m_subsets[index];
		}

	}
}
