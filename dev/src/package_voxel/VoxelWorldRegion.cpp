#include "voxel_pch.h"
#include "VoxelWorldRegion.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldOctTree.h"

namespace ld3d
{
	static uint32 VoxelColorMap[VT_EMPTY] = 
	{
		0xff334455,
		0xff999999,
		0xffbbbbbb,
		0xffeeeeee,
		0xff00ffff,
		0xffee0000,
		0xff00ff00,
		0xff00cccc,


	};

	struct VoxelFace
	{
		math::Vector3			verts[4];
		math::Vector3			normal;
		uint8					type;
	};


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

				delete[] pTmp->vertex_buffer;
				pTmp->vertex_buffer = nullptr;

				pChunk = pChunk->map_next;
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
		if(pChunk->data[index] != VT_EMPTY)
		{
			pChunk->voxel_count--;
			pChunk->data[index] = VT_EMPTY;
		}
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
		
		if(pChunk->data[index] == VT_EMPTY)
		{
			pChunk->voxel_count++;
		}

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

		if(pChunk->data[index] != VT_EMPTY)
		{
			return false;
		}
		pChunk->data[index] = vt;
		pChunk->voxel_count++;
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

			pChunk = pChunk->map_next;
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
		pChunk->voxel_count = 0;
		memcpy(pChunk->data, data, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

		for(int i = 0; i < VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE; ++i)
		{
			if(pChunk->data[i] != VT_EMPTY)
			{
				pChunk->voxel_count++;
			}
		}

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
			if(pChunk->key == key)
			{
				return pChunk;
			}

			pChunk = pChunk->map_next;
		}

		pChunk = m_pPool->Alloc();
		if(pChunk == nullptr)
		{
			assert(0);
			return nullptr;
		}
		pChunk->voxel_count = 0;
		pChunk->key = key;
		pChunk->in_dirty_list = false;
		memset(pChunk->data, VT_EMPTY, sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
		pChunk->map_next = m_pChunkMap[key % VOXEL_WORLD_CHUNK_MAP_SIZE];
		pChunk->dirty_list_next = nullptr;
		pChunk->render_list_next = nullptr;
		pChunk->in_oct_tree = false;
		pChunk->vertex_buffer = nullptr;
		pChunk->vertex_count = 0;
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
		if(pChunk == nullptr || pChunk->vertex_count == 0)
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
		uint32 c_x, c_y, c_z;

		c_x = (uint32)pChunk->chunk_coord().x;
		c_y = (uint32)pChunk->chunk_coord().y;
		c_z = (uint32)pChunk->chunk_coord().z;


		std::vector<VoxelFace> mesh;

		int delta = pChunk->vertex_count / 3;

		uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE];

		memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

		// -x axis
		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					if(Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}

					if(Empty(c_x + x - 1, c_y + y, c_z + z))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[y][z] = pChunk->data[index];
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(x, r[i].x1, r[i].y1);
				f.verts[1] = math::Vector3(x, r[i].x1, r[i].y2 + 1);
				f.verts[2] = math::Vector3(x, r[i].x2 + 1, r[i].y1);
				f.verts[3] = math::Vector3(x, r[i].x2 + 1, r[i].y2 + 1);
				f.normal = math::Vector3(-1, 0, 0);
				f.type = r[i].type;
				mesh.push_back(f);
			}

		}

		// +x axis
		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					if(Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}

					if(Empty(c_x + x + 1, c_y + y, c_z + z))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[y][z] = pChunk->data[index];
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(x + 1, r[i].x1, r[i].y1);
				f.verts[1] = math::Vector3(x + 1, r[i].x2 + 1, r[i].y1);
				f.verts[2] = math::Vector3(x + 1, r[i].x1, r[i].y2 + 1);
				f.verts[3] = math::Vector3(x + 1, r[i].x2 + 1, r[i].y2 + 1);
				f.normal = math::Vector3(1, 0, 0);
				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// -y axis
		for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					int index = _voxel_local_to_index(x, y, z);

					if(Empty(c_x + x, c_y + y, c_z + z) || (c_y + y) == 0)
					{
						continue;
					}
					if(Empty(c_x + x, c_y + y - 1, c_z + z))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[x][z] = pChunk->data[index];
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, y, r[i].y1);
				f.verts[1] = math::Vector3(r[i].x2 + 1, y, r[i].y1);
				f.verts[2] = math::Vector3(r[i].x1, y, r[i].y2 + 1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, y, r[i].y2 + 1);
				f.normal = math::Vector3(0, -1, 0);
				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// +y axis
		for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					int index = _voxel_local_to_index(x, y, z);

					if(Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(Empty(c_x + x, c_y + y + 1, c_z + z))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[x][z] = pChunk->data[index];
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, y + 1, r[i].y1);
				f.verts[1] = math::Vector3(r[i].x1, y + 1, r[i].y2 + 1);
				f.verts[2] = math::Vector3(r[i].x2 + 1, y + 1, r[i].y1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, y + 1, r[i].y2 + 1);
				f.normal = math::Vector3(0, 1, 0);
				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// -z axis
		for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
				{
					int index = _voxel_local_to_index(x, y, z);

					if(Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(Empty(c_x + x, c_y + y, c_z + z - 1))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[x][y] = pChunk->data[index];
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, r[i].y1, z);
				f.verts[1] = math::Vector3(r[i].x1, r[i].y2 + 1, z);
				f.verts[2] = math::Vector3(r[i].x2 + 1, r[i].y1, z);
				f.verts[3] = math::Vector3(r[i].x2 + 1, r[i].y2 + 1, z);
				f.normal = math::Vector3(0, 0, -1);
				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// +z axis
		for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
				{
					int index = _voxel_local_to_index(x, y, z);

					if(Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(Empty(c_x + x, c_y + y, c_z + z + 1))
					{
						int index = _voxel_local_to_index(x, y, z);
						faces[x][y] = pChunk->data[index];
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, r[i].y1, z + 1);
				f.verts[1] = math::Vector3(r[i].x2 + 1, r[i].y1, z + 1);
				f.verts[2] = math::Vector3(r[i].x1, r[i].y2 + 1, z + 1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, r[i].y2 + 1, z + 1);
				f.normal = math::Vector3(0, 0, 1);
				f.type = r[i].type;

				mesh.push_back(f);
			}
		}

		delete[] pChunk->vertex_buffer;
		pChunk->vertex_buffer = nullptr;
		pChunk->vertex_count = 0;

		if(mesh.size() != 0)
		{
			pChunk->vertex_buffer = new VoxelVertex[mesh.size() * 6];
			pChunk->vertex_count = (int)mesh.size() * 6;
		
			VoxelVertex* pData = pChunk->vertex_buffer;
			
			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];
				uint32 clr = VoxelColorMap[face.type];

				pData->pos = face.verts[0] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;
				++pData;

				pData->pos = face.verts[1] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;
				++pData;

				pData->pos = face.verts[2] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;
				++pData;

				pData->pos = face.verts[1] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;
				++pData;

				pData->pos = face.verts[3] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;
				++pData;

				pData->pos = face.verts[2] + pChunk->chunk_coord();
				pData->normal = face.normal;
				pData->clr = clr;

				++pData;

			}
		}
		

		delta = (pChunk->vertex_count / 3) - delta;
		m_faceCount += delta;


		if(pChunk->in_oct_tree == false && pChunk->vertex_count != 0)
		{
			if(false == m_pRoot->AddChunk(pChunk))
			{
				assert(0);
			}

			pChunk->in_oct_tree = true;
		}

		
	}
	std::vector<VoxelWorldRegion::FaceRegion> VoxelWorldRegion::ExtractRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE])
	{
		std::vector<FaceRegion> result;

		while(true)
		{
			FaceRegion r;
			if(false == FindMaxRegion(faces, r))
			{
				break;
			}

			result.push_back(r);

			for(int x = r.x1; x <= r.x2; ++x)
			{
				for(int y = r.y1; y <= r.y2; ++y)
				{
					faces[x][y] = VT_EMPTY;
				}
			}
		}


		return result;
	}
	bool VoxelWorldRegion::FindMaxRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE], FaceRegion& r)
	{
		struct Stride
		{
			int x, y;
			int len;
			int type;
		};

		Stride max_v_s;
		max_v_s.len = 0;

		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			Stride s;
			s.len = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				if(faces[x][y] != VT_EMPTY)
				{
					s.x = x;
					s.y = y;
					s.type = faces[x][y];
					s.len = 1;
					break;
				}
			}

			if(s.len == 0)
			{
				continue;
			}

			for(int y = s.y + 1; y < VOXEL_WORLD_CHUNK_SIZE;++y)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}
				s.len++;
			}

			if(max_v_s.len < s.len)
			{
				max_v_s = s;
			}
		}

		if(max_v_s.len == 0)
		{
			return false;
		}


		std::vector<Stride> h_strides;
		Stride max_h_stride;
		max_h_stride.len = 0;


		for(int y = max_v_s.y; y < max_v_s.y + max_v_s.len; ++y)
		{
			Stride s;
			s.len = 0;
			s.y = y;
			s.type = max_v_s.type;

			for(int x = max_v_s.x; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}

				s.len ++;
			}

			s.x = max_v_s.x;

			for(int x = max_v_s.x - 1; x >= 0; --x)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}

				s.len ++;
				s.x = x;
			}

			h_strides.push_back(s);

			if(max_h_stride.len < s.len)
			{
				max_h_stride = s;
			}
		}

		int max_area = 0;

		for(int i = 0; i < h_strides.size(); ++i)
		{
			FaceRegion region;
			Stride s = h_strides[i];

			region.x1 = s.x;
			region.y1 = s.y;
			region.type = s.type;
			int v_len = 1;

			for(int ii = i + 1; ii < h_strides.size(); ++ii)
			{
				if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
				{
					break;
				}

				v_len ++;
			}

			for(int ii = i - 1; ii >= 0; --ii)
			{
				if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
				{
					break;
				}

				v_len ++;
				region.y1--;
			}

			region.x2 = region.x1 + s.len - 1;
			region.y2 = region.y1 + v_len - 1;
			int area = v_len * s.len;
			if(max_area < area)
			{
				max_area = area;
				r = region;
			}

		}

		return true;
	}

	VoxelWorldChunk** VoxelWorldRegion::GetChunkMap()
	{
		return m_pChunkMap;
	}
	uint32 VoxelWorldRegion::GetChunkCount()
	{
		return m_chunkCount;
	}
}
