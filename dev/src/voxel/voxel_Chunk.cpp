#include "voxel_pch.h"
#include "..\..\include\voxel\voxel_Chunk.h"


namespace ld3d
{
	namespace voxel
	{

		Chunk::Chunk(void)
		{
			memset(m_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
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
	}
}
