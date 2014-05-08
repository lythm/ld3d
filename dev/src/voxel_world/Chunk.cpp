#include "voxel_world_pch.h"
#include "..\..\include\voxel_world\Chunk.h"


namespace ld3d
{
	namespace voxel
	{

		Chunk::Chunk(void)
		{
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
	}
}
