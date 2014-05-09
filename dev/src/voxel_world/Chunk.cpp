#include "voxel_world_pch.h"
#include "..\..\include\voxel_world\Chunk.h"


namespace ld3d
{
	namespace voxel
	{

		Chunk::Chunk(void)
		{
			memset(m_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			m_pNext = nullptr;
		}


		Chunk::~Chunk(void)
		{
		}
		ChunkPtr Chunk::GetNext()
		{
			return m_pNext;
		}
		void Chunk::SetNext(ChunkPtr pNext)
		{
			m_pNext = pNext;
		}
		const ChunkKey& Chunk::GetKey() const
		{
			return m_key;
		}
		void Chunk::SetKey(const ChunkKey& key)
		{
			m_key = key;
		}
		void Chunk::RemoveBlock(uint32 index)
		{
			m_data[index] = VT_EMPTY;
		}
		void Chunk::ReplaceBlock(uint32 index, uint8 v)
		{
			m_data[index] = v;
		}
		void Chunk::AddBlock(uint32 index, uint8 v)
		{
			if(m_data[index] != VT_EMPTY)
			{
				return;
			}
			m_data[index] = v;
		}
	}
}
