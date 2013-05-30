#include "voxel_pch.h"
#include "VoxelWorldDataSet.h"


namespace ld3d
{
	VoxelWorldDataSet::VoxelWorldDataSet(void)
	{
		m_pChunks = nullptr;
	}


	VoxelWorldDataSet::~VoxelWorldDataSet(void)
	{
	}
	bool VoxelWorldDataSet::Initialize()
	{
		m_pChunks = new VoxelChunk*[256 * 256 * 256];

		memset(m_pChunks, 0, sizeof(VoxelChunk*) * 256 * 256 * 256);

		return true;
	}
	void VoxelWorldDataSet::Release()
	{
		if(m_pChunks != nullptr)
		{
			delete []m_pChunks;
			m_pChunks = nullptr;
		}
	}
	void VoxelWorldDataSet::Update()
	{
	}
	uint32 VoxelWorldDataSet::_chunk_key(uint32 x, uint32 y, uint32 z)
	{
		uint32 c_x = x / 256;
		uint32 c_y = y / 256;
		uint32 c_z = z / 256;
		
		return ((c_x << 16) | (c_y << 8) | (c_z)) % 8;
	}
	uint32 VoxelWorldDataSet::_voxel_index(uint32 x, uint32 y, uint32 z)
	{
		uint32 v_x = x % 256;
		uint32 v_y = y % 256;
		uint32 v_z = z % 256;

		return v_x + v_z * 4 + v_y * 16;
	}
	uint8 VoxelWorldDataSet::GetVoxelType(uint32 x, uint32 y, uint32 z)
	{
		uint32 key = _chunk_key(x, y, z);

		VoxelChunk* pChunk = m_pChunks[key];

		while(pChunk)
		{
			if(pChunk->key == key)
			{
				break;
			}

			pChunk = pChunk->next;
		}

		uint32 index = _voxel_index(x, y, z);
		return pChunk == nullptr ? -1 : pChunk->data[index];
	}
	bool VoxelWorldDataSet::Exist(uint32 x, uint32 y, uint32 z)
	{
		return GetVoxelType(x, y, z) != -1;
	}
	bool VoxelWorldDataSet::AddVoxel(uint8 type, uint32 x, uint32 y, uint32 z)
	{
		uint32 key = _chunk_key(x, y, z);

		VoxelChunk* pChunk = m_pChunks[key];

		while(pChunk)
		{
			if(pChunk->key == key)
			{
				break;
			}

			pChunk = pChunk->next;
		}

		uint32 index = _voxel_index(x, y, z);

		if(pChunk != nullptr)
		{
			if(pChunk->data[index] != -1)
			{
				return false;
			}
			pChunk->data[index] = type;
			return true;
		}
		
		pChunk = new VoxelChunk;

		pChunk->key = key;
		memset(pChunk->data, -1, sizeof(uint8) * 64);
		
		pChunk->data[index] = type;

		pChunk->next = m_pChunks[key];
		m_pChunks[key] = pChunk;

		return true;
	}
	void VoxelWorldDataSet::RemoveVoxel(uint32 x, uint32 y, uint32 z)
	{
		uint32 key = _chunk_key(x, y, z);

		VoxelChunk* pChunk = m_pChunks[key];
		VoxelChunk* pPrev = nullptr;

		while(pChunk)
		{
			if(pChunk->key == key)
			{
				break;
			}
			
			pPrev = pChunk;
			
			pChunk = pChunk->next;
		}

		if(pChunk == nullptr)
		{
			return;
		}
		uint32 index = _voxel_index(x, y, z);

		pChunk->data[index] = -1;
		
		for(int i = 0; i < 64; ++i)
		{
			if(pChunk->data[i] != -1)
			{
				return;
			}
		}
		
		// remove empty chunk
		
		if(m_pChunks[key] == pChunk)
		{
			m_pChunks[key] = nullptr;
		}
		else
		{
			pPrev->next = pChunk->next;
		}

		delete pChunk;
	}
	uint8 VoxelWorldDataSet::Pick(const math::Ray& r)
	{
		return -1;
	}
}
