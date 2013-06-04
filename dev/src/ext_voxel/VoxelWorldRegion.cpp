#include "voxel_pch.h"
#include "VoxelWorldRegion.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"

namespace ld3d
{
	VoxelWorldRegion::VoxelWorldRegion(void)
	{
		m_pDirtyList = nullptr;
		m_pChunkMap = nullptr;
	}


	VoxelWorldRegion::~VoxelWorldRegion(void)
	{
	}
	bool VoxelWorldRegion::Initialize()
	{
		m_pPool = VoxelPoolPtr(new VoxelPool);
		if(m_pPool->Initialize(64 * 64 * 10) == false)
		{
			return false;
		}
		m_pChunkMap = new VoxelWorldChunk*[VOXEL_WORLD_CHUNK_MAP_SIZE];
		memset(m_pChunkMap, 0, sizeof(VoxelWorldChunk*) * VOXEL_WORLD_CHUNK_MAP_SIZE);
		m_pDirtyList = nullptr;

		return true;
	}
	void VoxelWorldRegion::Release()
	{
		m_pDirtyList = nullptr;

		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = m_pChunkMap[i];
			while(pChunk)
			{
				VoxelWorldChunk* pTmp = pChunk;
				pChunk = pChunk->next;
				m_pPool->Free(pTmp);
			}
		}
		if(m_pChunkMap)
		{
			delete []m_pChunkMap;
			m_pChunkMap = nullptr;
		}

		if(m_pPool)
		{
			m_pPool->Release();
			m_pPool.reset();
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
		AddChunkToDirtyList(pChunk);
	}
	void VoxelWorldRegion::ConvertBlock(uint8 vt, uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);
		if(pChunk == nullptr)
		{
			return;
		}
		uint32 index = _voxel_region_to_index(x, y, z);
		pChunk->data[index] = vt;
		AddChunkToDirtyList(pChunk);
	}
	bool VoxelWorldRegion::Empty(uint32 x, uint32 y, uint32 z)
	{
		if(InRegion(x, y, z) == false)
		{
			return true;
		}
		return _get_voxel(x ,y, z) == VT_EMPTY;
	}
	bool VoxelWorldRegion::AddBlock(uint8 vt, uint32 x, uint32 y, uint32 z)
	{
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);

		if(pChunk == nullptr)
		{
			return false;
		}
		uint32 index = _voxel_region_to_index(x, y, z);

		if(pChunk->data[index] != VT_EMPTY)
		{
			return false;
		}
		pChunk->data[index] = vt;
		AddChunkToDirtyList(pChunk);
		return true;
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
		if(InRegion(x, y, z) == false)
		{
			return nullptr;
		}

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
	bool VoxelWorldRegion::InRegion(uint32 x, uint32 y, uint32 z)
	{
		uint32 regionsize = VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_REGION_SIZE;

		if(x > regionsize || y > regionsize || z > regionsize)
		{
			return false;
		}
		return true;
	}
	VoxelWorldChunk* VoxelWorldRegion::_add_chunk(uint32 x, uint32 y, uint32 z)
	{
		if(InRegion(x, y, z) == false)
		{
			return nullptr;
		}


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

		pChunk = m_pPool->Alloc();
		if(pChunk == nullptr)
		{
			int i = 0;
		}
		pChunk->key = key;
		pChunk->in_dirty_list = false;
		memset(pChunk->data, VT_EMPTY, sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
		pChunk->next = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];
		pChunk->dirty_list_next = nullptr;
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
	void VoxelWorldRegion::GenerateMesh()
	{
		UpdateMesh();

		m_mesh.clear();
		m_mesh.reserve(1000);

		int t = GetTickCount();

		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = m_pChunkMap[i];
			while(pChunk)
			{
				m_mesh.insert(m_mesh.end(), pChunk->mesh.begin(), pChunk->mesh.end());

				pChunk = pChunk->next;
			}
		}

		t = GetTickCount() - t;
		
	}
	void VoxelWorldRegion::GenerateChunkMesh(VoxelWorldChunk* pChunk)
	{
		pChunk->mesh.clear();
		for(int i = 0; i < VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE; ++i)
		{
			uint32 x ,y,z;

			_voxel_index_to_region(pChunk->key, i, x, y, z);

			// x axis
			if(Empty(x - 1, y, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(-1, 0, 0);
				}

				pChunk->mesh.push_back(f);
			}

			if(Empty(x + 1, y, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x + 1, y, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y + 1, z)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y + 1, z + 1)		* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x + 1, y, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x + 1, y + 1, z + 1)		* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x + 1, y, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;


				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(1, 0, 0);
				}

				pChunk->mesh.push_back(f);
			}

			// y axis
			if(Empty(x , y - 1, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x + 1, y, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;

				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(0, -1, 0);
				}
				pChunk->mesh.push_back(f);
			}

			if(Empty(x, y + 1, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y + 1, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x, y + 1, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x, y + 1, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x + 1, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;


				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(0, 1, 0);

				}
				pChunk->mesh.push_back(f);
			}

			// z axis
			if(Empty(x, y, z - 1))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)						* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y + 1, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x, y, z)						* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x + 1, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x + 1, y, z)					* VOXEL_WORLD_BLOCK_SIZE;


				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(0, 0, -1);
				}

				pChunk->mesh.push_back(f);
			}

			if(Empty(x, y, z + 1))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z + 1)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y + 1, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				f.verts[3] = math::Vector3(x, y, z + 1)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[4] = math::Vector3(x + 1, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[5] = math::Vector3(x + 1, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				for(int inormal = 0; inormal < 6; ++inormal)
				{
					f.normals[inormal] = math::Vector3(0, 0, 1);

				}
				pChunk->mesh.push_back(f);
			}
		}

	}
	const std::vector<VoxelFace>& VoxelWorldRegion::GetMeshData()
	{
		return m_mesh;
	}
	void VoxelWorldRegion::UpdateMesh()
	{
		while(m_pDirtyList)
		{
			GenerateChunkMesh(m_pDirtyList);
			m_pDirtyList->in_dirty_list = false;
			m_pDirtyList = m_pDirtyList->dirty_list_next;
		}
		m_pDirtyList = nullptr;
	}
	void VoxelWorldRegion::AddChunkToDirtyList(VoxelWorldChunk* pChunk)
	{
		if(pChunk == nullptr || pChunk->in_dirty_list == true)
		{
			return;
		}

		pChunk->in_dirty_list = true;
		if(m_pDirtyList == nullptr)
		{
			m_pDirtyList = pChunk;
			m_pDirtyList->dirty_list_next = nullptr;
			return;
		}
		pChunk->dirty_list_next = m_pDirtyList;
		m_pDirtyList = pChunk;
	}
}
