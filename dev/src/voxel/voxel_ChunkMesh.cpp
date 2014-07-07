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

			m_pIndexBuffer				= nullptr;
			m_nIndexCount				= 0;
			m_nIndexBufferBytes			= 0;

		}
		ChunkMesh::~ChunkMesh(void)
		{
			if(m_pVertexBuffer)
			{
				delete m_pVertexBuffer;
				m_pVertexBuffer = nullptr;
			}

			if(m_pIndexBuffer)
			{
				delete m_pIndexBuffer;
				m_pIndexBuffer	= nullptr;
			}

			m_subsets.clear();
		}
		void ChunkMesh::Release()
		{
			if(m_pVertexBuffer)
			{
				delete m_pVertexBuffer;
				m_pVertexBuffer = nullptr;
			}
			if(m_pIndexBuffer)
			{
				delete m_pIndexBuffer;
				m_pIndexBuffer	= nullptr;
			}

			m_subsets.clear();

			Reset();
		}
		bool ChunkMesh::Reset()
		{
			m_nVertexCount				= 0;
			m_nIndexCount				= 0;

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
					delete m_pVertexBuffer;
				}
				m_pVertexBuffer = new char[bytes_need];
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
		bool ChunkMesh::AllocIndexBuffer(uint32 nIndexCount)
		{
			uint32 bytes_need = nIndexCount * sizeof(uint16);

			if((bytes_need) > m_nIndexBufferBytes)
			{
				if(m_pIndexBuffer)
				{
					delete m_pIndexBuffer;
				}
				m_pIndexBuffer = new char[bytes_need];
				m_nIndexBufferBytes = bytes_need;
			}

			m_nIndexCount = nIndexCount;

			return true;
		}
		void* ChunkMesh::GetIndexBuffer()
		{
			return m_pIndexBuffer;
		}
		uint32 ChunkMesh::GetIndexCount()
		{
			return m_nIndexCount;
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
