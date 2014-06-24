#include "voxel_pch.h"
#include "voxel/voxel_Chunk.h"


namespace ld3d
{
	namespace voxel
	{
		Chunk::Chunk(ChunkManagerPtr pChunkManager, const ChunkKey& key, const ChunkData& data) : m_adjacency(key), m_data(data)
		{
			m_pChunkManager = pChunkManager;
			m_key = key;
			
			m_modified = false;
			m_dirty = false;
			m_counter = 0;

			m_userData = nullptr;
		}


		Chunk::~Chunk(void)
		{
		}
		const ChunkKey& Chunk::GetKey() const
		{
			return m_key;
		}
		void Chunk::SetKey(const ChunkKey& key)
		{
			m_key = key;
		}
		void Chunk::Update()
		{
		}
		bool Chunk::IsDirty() const
		{
			return m_dirty;
		}
		void Chunk::SetDirty(bool dirty)
		{
			m_dirty = dirty;
		}
		void Chunk::SetData(const ChunkData& data)
		{
			m_data = data;
		}
		
		ChunkData& Chunk::GetData()
		{
			return m_data;
		}
		bool Chunk::IsModified() const
		{
			return m_modified;
		}
		void Chunk::SetUserData(void* pData)
		{
			m_userData = pData;
		}
		void* Chunk::GetUserData()
		{
			return m_userData;
		}
		ChunkManagerPtr Chunk::GetChunkManager()
		{
			return m_pChunkManager;
		}
		ChunkMeshPtr Chunk::GetMesh()
		{
			return m_pMesh;
		}
		void Chunk::SetMesh(ChunkMeshPtr pMesh)
		{
			m_pMesh = pMesh;
		}

		ChunkAdjacency&	Chunk::GetAdjacency()
		{
			return m_adjacency;
		}
		void Chunk::SetAdjacency(const ChunkAdjacency& adj)
		{
			m_adjacency = adj;
		}
	}
}
