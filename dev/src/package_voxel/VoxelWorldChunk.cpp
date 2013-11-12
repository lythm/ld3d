#include "voxel_pch.h"
#include "VoxelWorldChunk.h"

#include "VoxelWorldUtils.h"
#include "VoxelWorldMesh.h"

namespace ld3d
{
	VoxelWorldChunk::VoxelWorldChunk()
	{
		Reset();
	}
	void VoxelWorldChunk::Reset()
	{
		m_blockCount = 0;
		m_key = -1;
		m_dirty = false;
		memset(m_pData, VT_EMPTY, sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
		m_pDirtyListNext = nullptr;
		m_pRenderListNext = nullptr;
		m_inOctTree = false;
		vertex_buffer = nullptr;
		vertex_count = 0;

		m_pMapNext = nullptr;
	}
	VoxelWorldChunk::~VoxelWorldChunk()
	{

	}

	void VoxelWorldChunk::Init(uint32 key)
	{
		Reset();
		m_key = key;
	}
	void VoxelWorldChunk::SetMapNext(VoxelWorldChunk* pNext)
	{
		m_pMapNext = pNext;
	}
	VoxelWorldChunk* VoxelWorldChunk::GetMapNext()
	{
		return m_pMapNext;
	}
	uint32 VoxelWorldChunk::GetKey()
	{
		return m_key;
	}
	uint8* VoxelWorldChunk::GetBlockData()
	{
		return m_pData;
	}
	uint8 VoxelWorldChunk::GetBlock(uint32 index)
	{
		return m_pData[index];
	}
	void VoxelWorldChunk::SetBlock(uint32 index, uint8 value)
	{
		if(m_pData[index] == VT_EMPTY && value != VT_EMPTY)
		{
			m_blockCount++;
		}

		if(value == VT_EMPTY && m_pData[index] != VT_EMPTY)
		{
			m_blockCount--;
		}

		m_pData[index] = value;
	}
	void VoxelWorldChunk::SetDirtyListNext(VoxelWorldChunk* pNext)
	{
		m_pDirtyListNext = pNext;
	}
	VoxelWorldChunk* VoxelWorldChunk::GetDirtyListNext()
	{
		return m_pDirtyListNext;
	}
	void VoxelWorldChunk::SetRenderListNext(VoxelWorldChunk* pNext)
	{
		m_pRenderListNext = pNext;
	}
	VoxelWorldChunk* VoxelWorldChunk::GetRenderListNext()
	{
		return m_pRenderListNext;
	}
	void VoxelWorldChunk::SetDirty(bool dirty)
	{
		m_dirty = dirty;
	}
	bool VoxelWorldChunk::IsDirty()
	{
		return m_dirty;
	}
	void VoxelWorldChunk::SetInOctTree(bool value)
	{
		m_inOctTree = value;
	}
	bool VoxelWorldChunk::IsInOctTree()
	{
		return m_inOctTree;
	}
	math::Vector3 VoxelWorldChunk::GetChunkCoord()
	{
		uint32 c_x = (m_key >> 16) & 0x000000ff;
		uint32 c_y = (m_key >> 8) & 0x000000ff;
		uint32 c_z = m_key & 0x000000ff;

		float x = float(c_x * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);
		float y = float(c_y * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);
		float z = float(c_z * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE);

		return math::Vector3(x, y, z);
	}
	void VoxelWorldChunk::Load(uint32 key, uint8* data)
	{
		Reset();

		m_key = key;

		m_blockCount = 0;
		
		memcpy(m_pData, data, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

		for(int i = 0; i < VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE; ++i)
		{
			if(m_pData[i] != VT_EMPTY)
			{
				m_blockCount++;
			}
		}

	}
	uint32 VoxelWorldChunk::GetBlockCount()
	{
		return m_blockCount;
	}
	
	math::Vector3 VoxelWorldChunk::IndexToLocal(uint32 index)
	{
		math::Vector3 local;

		local.y = float(index / (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE));

		local.z = float((index % (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE)) / VOXEL_WORLD_CHUNK_SIZE);

		local.x = float((index % (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE)) % VOXEL_WORLD_CHUNK_SIZE);

		return local; 
	}
	math::Vector3 VoxelWorldChunk::IndexToGlobal(uint32 index)
	{
		return IndexToLocal(index) + GetChunkCoord();
	}

	void VoxelWorldChunk::UpdateMesh()
	{

	}

}
