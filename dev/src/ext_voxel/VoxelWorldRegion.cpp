#include "voxel_pch.h"
#include "VoxelWorldRegion.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldOctTree.h"

namespace ld3d
{
	VoxelWorldRegion::VoxelWorldRegion(void)
	{
		m_pDirtyList = nullptr;
		m_pRenderList = nullptr;
		m_pChunkMap = nullptr;
		m_faceCount = 0;
	}


	VoxelWorldRegion::~VoxelWorldRegion(void)
	{
	}
	bool VoxelWorldRegion::Initialize()
	{
		m_pPool = VoxelPoolPtr(new VoxelPool);
		if(m_pPool->Initialize(128 * 128 * 10) == false)
		{
			return false;
		}
		m_pChunkMap = new VoxelWorldChunk*[VOXEL_WORLD_CHUNK_MAP_SIZE];
		memset(m_pChunkMap, 0, sizeof(VoxelWorldChunk*) * VOXEL_WORLD_CHUNK_MAP_SIZE);
		m_pDirtyList = nullptr;
		m_faceCount = 0;

		m_pRoot = VoxelWorldOctTreePtr(new VoxelWorldOctTree);
		float size = VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_REGION_SIZE;

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
			assert(0);
			return nullptr;
		}
		pChunk->key = key;
		pChunk->in_dirty_list = false;
		memset(pChunk->data, VT_EMPTY, sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
		pChunk->next = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];
		pChunk->dirty_list_next = nullptr;
		pChunk->render_list_next = nullptr;
		pChunk->in_oct_tree = false;
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
	
	
	
	void VoxelWorldRegion::UpdateMesh()
	{
		while(m_pDirtyList)
		{
			GenChunkMesh(m_pDirtyList);
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
	void VoxelWorldRegion::FrustumCull(const ViewFrustum& vf)
	{
		m_pRenderList = nullptr;

		m_pRoot->FrustumCull(vf, boost::bind(&VoxelWorldRegion::AddChunkToRenderList, this, _1));
	}
	
	void VoxelWorldRegion::AddChunkToRenderList(VoxelWorldChunk* pChunk)
	{
		if(pChunk == nullptr || pChunk->mesh.size() == 0)
		{
			return;
		}
		if(m_pRenderList == nullptr)
		{
			pChunk->render_list_next = nullptr;
			m_pRenderList = pChunk;
			return;
		}

		pChunk->render_list_next = m_pRenderList;
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
	void VoxelWorldRegion::GenChunkMesh(VoxelWorldChunk* pChunk)
	{
		int delta = pChunk->mesh.size();

		pChunk->mesh.clear();


		std::list<VoxelFace> faces[6];
				

		for(int i = 0; i < VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE; ++i)
		{
			uint32 x ,y,z;

			_voxel_index_to_region(pChunk->key, i, x, y, z);

			if(Empty(x, y, z))
			{
				continue;
			}

			// x axis
			if(Empty(x - 1, y, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				
				faces[0].push_back(f);
			}

			if(Empty(x + 1, y, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x + 1, y, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y + 1, z)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x + 1, y + 1, z + 1)		* VOXEL_WORLD_BLOCK_SIZE;

				faces[1].push_back(f);
			}

			// y axis
			if(Empty(x , y - 1, z) && y != 0)
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y, z)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x + 1, y, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;

				faces[2].push_back(f);
			}

			if(Empty(x, y + 1, z))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y + 1, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y + 1, z )				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x + 1, y + 1, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				
				faces[3].push_back(f);
			}

			// z axis
			if(Empty(x, y, z - 1))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z)						* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x, y + 1, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x + 1, y, z)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x + 1, y + 1, z)				* VOXEL_WORLD_BLOCK_SIZE;
				
				faces[4].push_back(f);
			}

			if(Empty(x, y, z + 1))
			{
				VoxelFace f;
				f.clr = 0xffffffff;
				f.verts[0] = math::Vector3(x, y, z + 1)					* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[1] = math::Vector3(x + 1, y, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[2] = math::Vector3(x, y + 1, z + 1)				* VOXEL_WORLD_BLOCK_SIZE;
				f.verts[3] = math::Vector3(x + 1, y + 1, z + 1)			* VOXEL_WORLD_BLOCK_SIZE;
				
				faces[5].push_back(f);
			}
		}

		for(int i = 0; i < 6; ++i)
		{
			std::vector<VoxelFace> ret = CombineFace(faces[i], i);
			pChunk->mesh.insert(pChunk->mesh.begin(), ret.begin(), ret.end());
		}
		
		if(pChunk->in_oct_tree == false && pChunk->mesh.size() != 0)
		{
			if(false == m_pRoot->AddChunk(pChunk))
			{
				assert(0);
			}

			pChunk->in_oct_tree = true;
		}

		delta = pChunk->mesh.size() - delta;

		m_faceCount += delta;
	}
	std::vector<VoxelFace> VoxelWorldRegion::CombineFace(std::list<VoxelFace>& faces, int axis)
	{
		std::vector<VoxelFace> ret;

		std::list<VoxelFace>::iterator it = faces.begin();

		
		while(it != faces.end())
		{
			bool merged = false;
			for(size_t i = 0; i < ret.size(); ++i)
			{
				if(MergeWith(*it, ret[i], axis) == true)
				{
					merged = true;
					break;
				}
			}

			if(merged == false)
			{
				ret.push_back(*it);
			}
			
			++it;
		}

		return ret;
	}
	bool VoxelWorldRegion::CanMerge(VoxelFace& f1, VoxelFace& f2)
	{
		struct FaceEdge
		{
			uint32			a, b;
		};

		FaceEdge edges[4];

		edges[0].a = 0;
		edges[0].b = 1;

		edges[1].a = 1;
		edges[1].b = 3;

		edges[2].a = 3;
		edges[2].b = 2;

		edges[3].a = 2;
		edges[3].b = 0;

		int e1 = -1;
		int e2 = -1;

		for(int i1 = 0; i1 < 4; ++i1)
		{
			math::Vector3 a1, b1;

			a1 = f1.verts[edges[i1].a];
			b1 = f1.verts[edges[i1].b];
			
			for(int i2 = 0; i2 < 4; ++i2)
			{
				math::Vector3 a2, b2;
				a2 = f2.verts[edges[i2].a];
				b2 = f2.verts[edges[i2].b];

				if((a1 == a2 && b1 == b2) || (a1 == b2 && b1 == a2))
				{
					e1 = i1;
					e2 = i2;
					return true;
				}
			}
		}

		return false;
	}
	bool VoxelWorldRegion::MergeWith(VoxelFace& f1, VoxelFace& f2, int axis)
	{
		if(CanMerge(f1, f2) == false)
		{
			return false;
		}
		// merge f1 to f2
		math::Vector3 min_vert( 99999, 99999, 99999), max_vert(-99999, -99999, -99999);

		for(int i = 0; i < 4; ++i)
		{
			min_vert.x = min_vert.x > f1.verts[i].x ? f1.verts[i].x : min_vert.x;
			min_vert.y = min_vert.y > f1.verts[i].y ? f1.verts[i].y : min_vert.y;
			min_vert.z = min_vert.z > f1.verts[i].z ? f1.verts[i].z : min_vert.z;

			max_vert.x = max_vert.x < f1.verts[i].x ? f1.verts[i].x : max_vert.x;
			max_vert.y = max_vert.y < f1.verts[i].y ? f1.verts[i].y : max_vert.y;
			max_vert.z = max_vert.z < f1.verts[i].z ? f1.verts[i].z : max_vert.z;
		}

		for(int i = 0; i < 4; ++i)
		{
			min_vert.x = min_vert.x > f2.verts[i].x ? f2.verts[i].x : min_vert.x;
			min_vert.y = min_vert.y > f2.verts[i].y ? f2.verts[i].y : min_vert.y;
			min_vert.z = min_vert.z > f2.verts[i].z ? f2.verts[i].z : min_vert.z;

			max_vert.x = max_vert.x < f2.verts[i].x ? f2.verts[i].x : max_vert.x;
			max_vert.y = max_vert.y < f2.verts[i].y ? f2.verts[i].y : max_vert.y;
			max_vert.z = max_vert.z < f2.verts[i].z ? f2.verts[i].z : max_vert.z;
		}

		switch(axis)
		{
		case 0: // -x axis
			{
				f2.verts[0] = math::Vector3(min_vert.x, min_vert.y, min_vert.z);
				f2.verts[1] = math::Vector3(min_vert.x, min_vert.y, max_vert.z);
				f2.verts[2] = math::Vector3(min_vert.x, max_vert.y, min_vert.z);
				f2.verts[3] = math::Vector3(min_vert.x, max_vert.y, max_vert.z);
			}
			break;
		case 1: // +x axis
			{
				f2.verts[0] = math::Vector3(max_vert.x, min_vert.y, min_vert.z);
				f2.verts[1] = math::Vector3(max_vert.x, max_vert.y, min_vert.z);
				f2.verts[2] = math::Vector3(max_vert.x, min_vert.y, max_vert.z);
				f2.verts[3] = math::Vector3(max_vert.x, max_vert.y, max_vert.z);
			}
			break;
		case 2: // -y axis
			{
				f2.verts[0] = math::Vector3(min_vert.x, min_vert.y, min_vert.z);
				f2.verts[1] = math::Vector3(max_vert.x, min_vert.y, min_vert.z);
				f2.verts[2] = math::Vector3(min_vert.x, min_vert.y, max_vert.z);
				f2.verts[3] = math::Vector3(min_vert.x, min_vert.y, max_vert.z);
			}
			break;
		case 3: // +y axis
			{
				f2.verts[0] = math::Vector3(min_vert.x, max_vert.y, min_vert.z);
				f2.verts[1] = math::Vector3(min_vert.x, max_vert.y, max_vert.z);
				f2.verts[2] = math::Vector3(max_vert.x, max_vert.y, min_vert.z);
				f2.verts[3] = math::Vector3(max_vert.x, max_vert.y, max_vert.z);
			}
			break;
		case 4: // -z axis
			{
				f2.verts[0] = math::Vector3(min_vert.x, min_vert.y, min_vert.z);
				f2.verts[1] = math::Vector3(min_vert.x, max_vert.y, min_vert.z);
				f2.verts[2] = math::Vector3(max_vert.x, min_vert.y, min_vert.z);
				f2.verts[3] = math::Vector3(max_vert.x, max_vert.y, min_vert.z);
			}
			break;
		case 5: // +z axis
			{
				f2.verts[0] = math::Vector3(min_vert.x, min_vert.y, max_vert.z);
				f2.verts[1] = math::Vector3(max_vert.x, min_vert.y, max_vert.z);
				f2.verts[2] = math::Vector3(min_vert.x, max_vert.y, max_vert.z);
				f2.verts[3] = math::Vector3(max_vert.x, max_vert.y, max_vert.z);
			}
			break;
		default:
			assert(0);
			return false;
		}

		return true;
	}
}
