#include "voxel_pch.h"
#include "VoxelWorldRegion.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldOctTree.h"
#include "VoxelWorldUtils.h"
#include "VoxelWorldMesh.h"

namespace ld3d
{
	
	VoxelWorldRegion::VoxelWorldRegion(void)
	{
		m_pDirtyList = nullptr;
		m_pRenderList = nullptr;
		m_pChunkMap = nullptr;
		m_faceCount = 0;

		m_worldSizeX		= 0;
		m_worldSizeY		= 0;
		m_worldSizeZ		= 0;
		m_chunkCount		= 0;
	}


	VoxelWorldRegion::~VoxelWorldRegion(void)
	{
	}
	
	bool VoxelWorldRegion::Initialize(int sx, int sy, int sz)
	{
		m_pPool = VoxelPoolPtr(new VoxelPool);
		if(m_pPool->Initialize(256 * 256 * 2) == false)
		{
			return false;
		}
		m_pChunkMap = new VoxelWorldChunk*[VOXEL_WORLD_CHUNK_MAP_SIZE];
		memset(m_pChunkMap, 0, sizeof(VoxelWorldChunk*) * VOXEL_WORLD_CHUNK_MAP_SIZE);
		m_pDirtyList = nullptr;
		m_faceCount = 0;

		m_worldSizeX = sx;
		m_worldSizeY = sy;
		m_worldSizeZ = sz;

		int max_size = sx;
		max_size = max_size < sy ? sy : max_size;
		max_size = max_size < sz ? sz : max_size;

		m_pRoot = VoxelWorldOctTreePtr(new VoxelWorldOctTree);

		int m = int(max_size / VOXEL_WORLD_CHUNK_SIZE);
		int e = math::closest_expo(m);
		m = e < m ? e << 1 : e;

		float size = m * VOXEL_WORLD_CHUNK_SIZE;


		math::AABBox bound(math::Vector3(0, 0, 0), math::Vector3(size, size, size));

		m_pRoot->SetBound(bound);

		return true;
	}
	void VoxelWorldRegion::Release()
	{
		m_pDirtyList = nullptr;
		m_pRenderList = nullptr;
		m_pRoot.reset();

		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = m_pChunkMap[i];
			while(pChunk)
			{
				VoxelWorldChunk* pTmp = pChunk;

				pChunk = pChunk->GetMapNext();

				pTmp->Release();
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

		pChunk->SetBlock(index, VT_EMPTY);

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
		
		pChunk->SetBlock(index, vt);

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
		if(vt == VT_EMPTY)
		{
			return false;
		}
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);

		if(pChunk == nullptr)
		{
			return false;
		}
		uint32 index = _voxel_region_to_index(x, y, z);

		if(pChunk->GetBlock(index) != VT_EMPTY)
		{
			return false;
		}
		pChunk->SetBlock(index, vt);

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
			if(pChunk->GetKey() == key)
			{
				return pChunk;
			}

			pChunk = pChunk->GetMapNext();
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
	void VoxelWorldRegion::AddChunk(uint32 key, uint8 data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE])
	{
		uint32 x, y, z;
		_chunk_key_to_region(key, x, y, z);
		VoxelWorldChunk* pChunk = _add_chunk(x, y, z);
		if(pChunk == nullptr)
		{
			return;
		}
		pChunk->Load(key, data);

		AddChunkToDirtyList(pChunk);
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
			if(pChunk->GetKey() == key)
			{
				return pChunk;
			}

			pChunk = pChunk->GetMapNext();
		}

		pChunk = m_pPool->Alloc();
		if(pChunk == nullptr)
		{
			assert(0);
			return nullptr;
		}

		pChunk->Init(key, this);

		pChunk->SetMapNext(m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE]);

		m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE] = pChunk;
		++m_chunkCount;

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

		return pChunk->GetBlock(index);
	}



	void VoxelWorldRegion::UpdateMesh()
	{
		while(m_pDirtyList)
		{
			int delta = m_pDirtyList->GetMesh()->GetVertexCount() / 3;

			m_pDirtyList->UpdateMesh();

			m_faceCount = m_pDirtyList->GetMesh()->GetVertexCount() / 3 - delta;

			if(m_pDirtyList->IsInOctTree() == false && m_pDirtyList->GetMesh()->GetVertexCount() != 0)
			{
				if(false == m_pRoot->AddChunk(m_pDirtyList))
				{
					assert(0);
				}

				m_pDirtyList->SetInOctTree(true);
			}
		
			m_pDirtyList->SetDirty(false);
			m_pDirtyList = m_pDirtyList->GetDirtyListNext();
		}
		m_pDirtyList = nullptr;
	}
	void VoxelWorldRegion::AddChunkToDirtyList(VoxelWorldChunk* pChunk)
	{
		if(pChunk == nullptr || pChunk->IsDirty() == true)
		{
			return;
		}

		pChunk->SetDirty(true);

		if(m_pDirtyList == nullptr)
		{
			m_pDirtyList = pChunk;
			m_pDirtyList->SetDirtyListNext(nullptr);
			return;
		}
		pChunk->SetDirtyListNext(m_pDirtyList);
		m_pDirtyList = pChunk;
	}
	void VoxelWorldRegion::FrustumCull(const ViewFrustum& vf)
	{
		m_pRenderList = nullptr;

		m_pRoot->FrustumCull(vf, boost::bind(&VoxelWorldRegion::AddChunkToRenderList, this, _1));
	}

	void VoxelWorldRegion::AddChunkToRenderList(VoxelWorldChunk* pChunk)
	{
		if(pChunk == nullptr || pChunk->GetMesh()->GetVertexCount() == 0)
		{
			return;
		}
		if(m_pRenderList == nullptr)
		{
			pChunk->SetRenderListNext(nullptr);
			m_pRenderList = pChunk;
			return;
		}

		pChunk->SetRenderListNext(m_pRenderList);
		m_pRenderList = pChunk;
	}
	VoxelWorldChunk* VoxelWorldRegion::GetRenderList()
	{
		return m_pRenderList;
	}
	uint32	VoxelWorldRegion::GetFaceCount()
	{
		return m_faceCount;

	}
	

	VoxelWorldChunk** VoxelWorldRegion::GetChunkMap()
	{
		return m_pChunkMap;
	}
	uint32 VoxelWorldRegion::GetChunkCount()
	{
		return m_chunkCount;
	}
	VoxelWorldOctTreePtr VoxelWorldRegion::GetOctTreeRoot() const
	{
		return m_pRoot;
	}
	IntersectionResult VoxelWorldRegion::Intersect(const math::Ray& r)
	{
		IntersectionResult ret(IntersectionResult::no);

		Real t;
		if(m_pRoot->RayPick(r, t) == false)
		{
			return ret;
		}
		
		ret.ret = IntersectionResult::yes;
		ret.contact_point = r.GetPos(t);

		return ret;
	}
}
