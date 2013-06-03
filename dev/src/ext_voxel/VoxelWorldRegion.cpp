#include "voxel_pch.h"
#include "VoxelWorldRegion.h"

#include "VoxelWorldChunk.h"

namespace ld3d
{
	VoxelWorldRegion::VoxelWorldRegion(void)
	{
	}


	VoxelWorldRegion::~VoxelWorldRegion(void)
	{
	}
	bool VoxelWorldRegion::Initialize()
	{
		m_pChunkMap = new VoxelWorldChunk*[VOXEL_WORLD_CHUNK_MAP_SIZE];
		memset(m_pChunkMap, 0, sizeof(VoxelWorldChunk*) * VOXEL_WORLD_CHUNK_MAP_SIZE);


		return true;
	}
	void VoxelWorldRegion::Release()
	{
		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = m_pChunkMap[i];
			while(pChunk)
			{
				VoxelWorldChunk* pTmp = pChunk;
				pChunk = pChunk->next;
				delete pTmp;
			}
		}
		if(m_pChunkMap)
		{
			delete []m_pChunkMap;
			m_pChunkMap = nullptr;
		}
	}
	void VoxelWorldRegion::Update()
	{
	}
	void VoxelWorldRegion::RemoveBlock(uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _get_chunk(x, y, z);
		if(pChunk == nullptr)
		{
			return;
		}
		uint32 index = _voxel_region_to_index(x, y, z);

		pChunk->data[index] = VT_EMPTY;
	}
	void VoxelWorldRegion::ConvertBlock(uint8 vt, uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);

		uint32 index = _voxel_region_to_index(x, y, z);
		pChunk->data[index] = vt;

	}
	bool VoxelWorldRegion::Empty(uint32 x, uint32 y, uint32 z)
	{
		return _get_voxel(x ,y, z) == VT_EMPTY;
	}
	bool VoxelWorldRegion::AddBlock(uint8 vt, uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);

		uint32 index = _voxel_region_to_index(x, y, z);

		if(pChunk->data[index] == VT_EMPTY)
		{
			pChunk->data[index] = vt;
			return true;
		}

		return false;
	}
	uint8 VoxelWorldRegion::GetBlock(uint32 x, uint32 y, uint32 z)
	{
		return _get_voxel(x, y, z);
	}
	uint32 VoxelWorldRegion::_chunk_key(uint32 x, uint32 y, uint32 z)
	{
		uint32 c_x = x / VOXEL_WORLD_CHUNK_SIZE;
		uint32 c_y = y / VOXEL_WORLD_CHUNK_SIZE;
		uint32 c_z = z / VOXEL_WORLD_CHUNK_SIZE;

		return ((c_x << 16) | (c_y << 8) | (c_z));
	}
	void VoxelWorldRegion::_chunk_key_to_region(uint32 key, uint32& x, uint32& y, uint32 &z)
	{
		uint32 cx = (key & 0x00ff0000) >> 16;
		uint32 cy = (key & 0x0000ff00) >> 8;
		uint32 cz = (key & 0x000000ff);

		x = cx * VOXEL_WORLD_CHUNK_SIZE;
		y = cy * VOXEL_WORLD_CHUNK_SIZE;
		z = cz * VOXEL_WORLD_CHUNK_SIZE;
	}
	uint32 VoxelWorldRegion::_voxel_local_to_index(uint32 x, uint32 y, uint32 z)
	{
		return x + z * VOXEL_WORLD_CHUNK_SIZE + y * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE;
	}
	uint32 VoxelWorldRegion::_voxel_region_to_index(uint32 x, uint32 y, uint32 z)
	{
		uint32 v_x = x % VOXEL_WORLD_CHUNK_SIZE;
		uint32 v_y = y % VOXEL_WORLD_CHUNK_SIZE;
		uint32 v_z = z % VOXEL_WORLD_CHUNK_SIZE;

		return _voxel_local_to_index(v_x, v_y, v_z);
	}

	void VoxelWorldRegion::_voxel_index_to_local(uint32 index, uint32& x, uint32& y, uint32& z)
	{
		y = index / (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

		z = (index % (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE)) / VOXEL_WORLD_CHUNK_SIZE;

		x = (index % (VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE)) % VOXEL_WORLD_CHUNK_SIZE;
	}
	void VoxelWorldRegion::_voxel_index_to_region(uint32 chunk_key, uint32 index, uint32& x, uint32& y, uint32& z)
	{
		uint32 v_x, v_y, v_z;

		_voxel_index_to_local(index, v_x, v_y, v_z);

		_chunk_key_to_region(chunk_key, x, y, z);

		x += v_x;
		y += v_y;
		z += v_z;
	}
	VoxelWorldChunk* VoxelWorldRegion::_get_chunk(uint32 x, uint32 y, uint32 z)
	{
		uint32 key = _chunk_key(x, y, z);

		VoxelWorldChunk* pChunk = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];

		while(pChunk)
		{
			if(pChunk->key == key)
			{
				return pChunk;
			}

			pChunk = pChunk->next;
		}
		
		return nullptr;

	}
	VoxelWorldChunk* VoxelWorldRegion::_add_chunk(uint32 x, uint32 y, uint32 z)
	{
		uint32 key = _chunk_key(x, y, z);

		VoxelWorldChunk* pChunk = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];

		while(pChunk)
		{
			if(pChunk->key == key)
			{
				return pChunk;
			}

			pChunk = pChunk->next;
		}

		pChunk = new VoxelWorldChunk;
		pChunk->key = key;
		memset(pChunk->data, VT_EMPTY, sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
		pChunk->next = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];
		m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE] = pChunk;

		return pChunk;
	}
	uint8 VoxelWorldRegion::_get_voxel(uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _get_chunk(x, y, z);

		if(pChunk == nullptr)
		{
			return VT_EMPTY;
		}
		uint32 index = _voxel_region_to_index(x, y, z);

		return pChunk->data[index];
	}
	std::vector<VoxelFace> VoxelWorldRegion::GenerateMesh()
	{
		std::vector<VoxelFace> faces;
		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = m_pChunkMap[i];
			while(pChunk)
			{
				std::vector<VoxelFace> chunk;
				chunk = GenerateChunkMesh(pChunk);

				faces.insert(faces.end(), chunk.begin(), chunk.end());

				pChunk = pChunk->next;
			}
		}

		return faces;
	}
	std::vector<VoxelFace> VoxelWorldRegion::GenerateChunkMesh(VoxelWorldChunk* pChunk)
	{
		std::vector<VoxelFace> faces;

		return faces;
	}
}
