#include "voxel_pch.h"
#include "voxel/voxel_Chunk.h"


namespace ld3d
{
	namespace voxel
	{
		Chunk::Chunk(ChunkManagerPtr pChunkManager, uint8 data[])
		{
			m_pChunkManager = pChunkManager;
			if(data == nullptr)
			{
				memset(m_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			}
			else
			{
				memcpy(m_data, data, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			}
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
		void Chunk::SetData(uint8 data[])
		{
			memcpy(m_data, data, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
		}
		uint8* Chunk::GetData()
		{
			return (uint8*)m_data;
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
	}
}
