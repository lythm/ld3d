#include "voxel_pch.h"
#include "voxel/voxel_Chunk.h"


namespace ld3d
{
	namespace voxel
	{
		Chunk::Chunk(ChunkManagerPtr pChunkManager, uint8 data[])
		{
			m_pChunkManager = pChunkManager;

			memset(m_neighbour, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);

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
		ChunkMeshPtr Chunk::GetMesh()
		{
			return m_pMesh;
		}
		void Chunk::SetMesh(ChunkMeshPtr pMesh)
		{
			m_pMesh = pMesh;
		}

		bool Chunk::_check_coord_range(int32 x, int32 y, int32 z)
		{
			return (x >= 0 && x < CHUNK_SIZE) && ( y >= 0 && y < CHUNK_SIZE) && (z >= 0 && z < CHUNK_SIZE);
		}
		void Chunk::SetNeightbourFlag(int32 x, int32 y, int32 z, int32 neighbour, bool val)
		{
			if(_check_coord_range(x, y, z) == false)
			{
				return;
			}
			int32 index = ToIndex(x, y, z);
			SetNeightbourFlag(index, neighbour, val);
		}
		void Chunk::SetNeightbourFlag(int32 index, int32 neighbour, bool val)
		{
			if(val)
			{
				m_neighbour[index] |= (1 << neighbour);
			}
			else
			{
				m_neighbour[index] &= ~(1 << neighbour);
			}
		}
		void Chunk::UpdateAllNeighBour(int32 x, int32 y, int32 z, bool val)
		{
			SetNeightbourFlag(x - 1, y, z, p_x, val != VT_EMPTY);
			SetNeightbourFlag(x + 1, y, z, n_x, val != VT_EMPTY);

			SetNeightbourFlag(x, y - 1, z, p_y, val != VT_EMPTY);
			SetNeightbourFlag(x, y + 1, z, n_y, val != VT_EMPTY);

			SetNeightbourFlag(x, y, z - 1, p_z, val != VT_EMPTY);
			SetNeightbourFlag(x, y, z + 1, n_z, val != VT_EMPTY);
		}
		bool Chunk::CheckNeighbourFlag(int32 x, int32 y, int32 z, int32 neighbour)
		{
			int32 index = ToIndex(x, y, z);
			return CheckNeighbourFlag(index, neighbour);
		}
		bool Chunk::CheckNeighbourFlag(int32 index, int32 neighbour)
		{
			return (m_neighbour[index] & (1 << neighbour)) != 0;
		}
		uint8 Chunk::GetNeighbourFlag(int32 x, int32 y, int32 z)
		{
			int32 index = ToIndex(x, y, z);
			return GetNeighbourFlag(index);
		}
		uint8 Chunk::GetNeighbourFlag(int32 index)
		{
			return m_neighbour[index];
		}
	}
}
