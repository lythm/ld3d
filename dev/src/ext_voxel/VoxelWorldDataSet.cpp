#include "voxel_pch.h"
#include "VoxelWorldDataSet.h"

#include "ext_voxel\VoxelBlock.h"
#include "VoxelPool.h"


namespace ld3d
{
	VoxelWorldDataSet::VoxelWorldDataSet(void)
	{
		m_pChunks = nullptr;
		m_nChunks = 0;
		m_voxelSize = 1.0f;
	}


	VoxelWorldDataSet::~VoxelWorldDataSet(void)
	{
	}
	bool VoxelWorldDataSet::Initialize(float voxelSize)
	{
		m_voxelSize = voxelSize;
		m_pPool = VoxelPoolPtr(new VoxelPool);

		if(false == m_pPool->Initialize(256 * 256 * 128))
		{
			return false;
		}

		m_nChunks = 256 * 256 * 256;
		m_pChunks = new VoxelChunk*[m_nChunks];

		memset(m_pChunks, 0, sizeof(VoxelChunk*) * m_nChunks);

		return true;
	}
	void VoxelWorldDataSet::Release()
	{
		if(m_pChunks != nullptr)
		{
			delete []m_pChunks;
			m_pChunks = nullptr;
		}

		if(m_pPool)
		{
			m_pPool->Release();
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
	void VoxelWorldDataSet::_chunk_key_to_world(uint32 key, int32& x, int32& y, int32 &z)
	{

	}
	void VoxelWorldDataSet::_voxel_index_to_world(VoxelChunk* pChunk, uint32 index, int32& x, int32& y, int32& z)
	{
		int32 v_x, v_y, v_z;
		
		_voxel_index_to_local(index, v_x, v_y, v_z);

		_chunk_key_to_world(pChunk->key, x, y, z);

		x += v_x;
		y += v_y;
		z += v_z;
	}
	void VoxelWorldDataSet::_voxel_index_to_local(uint32 index, int32& x, int32& y, int32& z)
	{
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
		return pChunk == nullptr ? VT_EMPTY : pChunk->data[index];
	}
	bool VoxelWorldDataSet::Exist(uint32 x, uint32 y, uint32 z)
	{
		return GetVoxelType(x, y, z) != VT_EMPTY;
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
			if(pChunk->data[index] != VT_EMPTY)
			{
				return false;
			}
			pChunk->data[index] = type;
			return true;
		}
		
		pChunk = m_pPool->Alloc();;

		pChunk->key = key;
		memset(pChunk->data, VT_EMPTY, sizeof(uint8) * 64);
		
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

		pChunk->data[index] = VT_EMPTY;
		
		for(int i = 0; i < 64; ++i)
		{
			if(pChunk->data[i] != VT_EMPTY)
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

		m_pPool->Free(pChunk);
	}
	uint8 VoxelWorldDataSet::Pick(const math::Ray& r)
	{
		return VT_EMPTY;
	}
	std::vector<VoxelFace> VoxelWorldDataSet::GenerateMesh()
	{
		std::vector<VoxelFace> faces;

		for(int i = 0; i < m_nChunks; ++i)
		{
			VoxelChunk* pChunk = m_pChunks[i];

			while(pChunk)
			{
				for(int ii = 0; ii < 64; ++ii)
				{
					if(pChunk->data[ii] == VT_EMPTY)
					{
						continue;
					}



				}

				pChunk = pChunk->next;
			}

		}


		return faces;
	}
}
