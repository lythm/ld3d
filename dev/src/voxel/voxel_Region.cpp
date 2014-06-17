#include "voxel_pch.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel_ChunkManager.h"
#include "voxel_ChunkLoader.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_OctTree.h"

namespace ld3d
{
	namespace voxel
	{
		Region::Region(void)
		{
			m_modified		= false;
			m_coord			= Coord();
			m_loaded		= false;
			m_heightMap		= nullptr;
		}


		Region::~Region(void)
		{

		}
		bool Region::Load(ChunkLoaderPtr pLoader, bool sync, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded)
		{
			Coord region_origin = m_coord;
			region_origin.x *= REGION_SIZE;
			region_origin.y *= REGION_HEIGHT;
			region_origin.z *= REGION_SIZE;


			float* height_map = GetHeightmap();


			for(int32 x = 0; x < REGION_CHUNK_LENGTH; ++x)
			{
				for(int32 z = 0; z < REGION_CHUNK_LENGTH; ++z)
				{
					for(int32 y = 0; y < REGION_CHUNK_HEIGHT; ++y)
					{
						Coord chunk_coord(x, y, z);

						chunk_coord *= CHUNK_SIZE;

						math::AABBox chunk_aabbox(chunk_coord.ToVector3(), (chunk_coord + Coord(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE)).ToVector3()); 


						if(math::AABBoxIntersectAABBoxTest(m_heightMapAABBox, chunk_aabbox) == math::intersect_none)
						{
							continue;
						}
						chunk_coord += region_origin;

						ChunkKey key(chunk_coord);

						if(sync)
						{
							pLoader->LoadChunkSync(shared_from_this(), key, on_chunk_loaded);
						}
						else
						{
							pLoader->LoadChunk(shared_from_this(), key, on_chunk_loaded);
						}
					}
				}
			}
			return true;
		}
		bool Region::Save()
		{
			return true;
		}
		bool Region::GenChunk(const Coord& chunk_origin)
		{
			//	WorldGenPtr pGen = m_pWorld->GetWorldGen();

			//	pGen->GenChunk(chunk_origin);

			return true;
		}
		void Region::GenHeightmap()
		{
			if(m_heightMap == nullptr)
			{
				m_heightMap = (float*)GetAllocator()->Alloc(sizeof(float) * REGION_SIZE * REGION_SIZE);
			}

			PerlinNoise p(3, 1, 1, rand());

			const Bound& bound = m_pWorld->GetBound();

			uint32 ex, ey, ez;
			bound.GetExtent(ex, ey, ez);

			Coord region_origin = m_coord;
			region_origin.x *= REGION_SIZE;
			region_origin.y *= REGION_HEIGHT;
			region_origin.z *= REGION_SIZE;

			double max_h = 0;

			for(int32 x = 0; x < REGION_SIZE; ++x)
			{
				for(int32 z = 0; z < REGION_SIZE; ++z)
				{
					double h = p.Get(double(x + region_origin.x) / double(ex), double(z + region_origin.z) / double(ez));
					m_heightMap[z * REGION_SIZE + x] = h * (REGION_HEIGHT / 2.0f);

					if(h > max_h)
					{
						max_h = h;
					}
				}
			}

			m_heightMapAABBox.Make(math::Vector3(0, 0, 0), math::Vector3(REGION_SIZE, max_h, REGION_SIZE));
		}
		bool Region::GenRegion()
		{
			PerlinNoise p(3, 1, 1, rand());
			const Bound& bound = m_pWorld->GetBound();

			uint32 ex, ey, ez;
			bound.GetExtent(ex, ey, ez);

			//Coord region_origin = m_pWorld->ToRegionOrigin(m_coord);
			Coord region_origin = m_coord;
			region_origin.x *= REGION_SIZE;
			region_origin.y *= REGION_HEIGHT;
			region_origin.z *= REGION_SIZE;

			uint16 height_map[REGION_SIZE * REGION_SIZE];

			for(int32 x = 0; x < REGION_SIZE; ++x)
			{
				for(int32 z = 0; z < REGION_SIZE; ++z)
				{
					double h = p.Get(double(x + region_origin.x) / double(ex), double(z + region_origin.z) / double(ez));
					height_map[z * REGION_SIZE + x] = h * (REGION_HEIGHT / 2.0f);

					Coord c(x + region_origin.x, h * (REGION_HEIGHT / 2.0f), z + region_origin.z);
					m_pChunkManager->ReplaceBlock(c, 1);
				}
			}


			/*	uint8 chunk_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

			memset(chunk_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			bool empty_chunk = true;
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
			for(int z = 0; z < CHUNK_SIZE; ++z)
			{
			Coord c = Coord(x, 0, z) + chunk_origin;

			double h = p.Get(double(c.x) / double(ex), double(c.z) / double(ez));
			c.y = (h * REGION_HEIGHT) / 2;

			c -= chunk_origin;

			if(c.y < 0 || c.y >= CHUNK_SIZE)
			{
			continue;
			}

			empty_chunk = false;

			uint32 index = Chunk::ToIndex(c);

			chunk_data[index] = 1;
			}

			}

			if(empty_chunk == true)
			{
			return true;
			}

			ChunkPtr pChunk = pGen->GetWorld()->GetChunkManager()->CreateChunk(ChunkKey(chunk_origin), chunk_data);

			return true;*/
			return true;
		}
		bool Region::IsModified() const
		{
			return m_modified;
		}
		void Region::SetModified()
		{
			m_modified = true;
		}

		bool Region::Initialize(WorldPtr pWorld, const Coord& coord)
		{
			m_pWorld = pWorld;
			m_pChunkManager = pWorld->GetChunkManager();

			m_modified		= false;
			m_coord			= coord;
			m_loaded		= false;

			m_heightMapAABBox.Make(math::Vector3(0, 0, 0), math::Vector3(REGION_SIZE, REGION_HEIGHT, REGION_SIZE));

			m_pOctTree = std::allocate_shared<OctTree, std_allocator_adapter<OctTree>>(GetAllocator(), GetRegionOrigin());
			m_pOctTree->SetBound(math::AABBox(math::Vector3(0, 0, 0), math::Vector3(REGION_SIZE, REGION_HEIGHT, REGION_SIZE)));
			return true;
		}
		void Region::Release()
		{
			if(m_heightMap != nullptr)
			{
				GetAllocator()->Free(m_heightMap);
				m_heightMap = nullptr;
			}

			m_modified = false;
			m_coord = Coord();

			m_pChunkManager.reset();
			m_pOctTree.reset();
		}
		const Coord&  Region::GetRegionCoord() const
		{
			return m_coord;
		}
		Coord Region::GetRegionOrigin() const
		{
			Coord ori = m_coord;
			ori.x *= REGION_SIZE;
			ori.y *= REGION_HEIGHT;
			ori.z *= REGION_SIZE;

			return ori;
		}
		void Region::SetRegionCoord(const Coord& coord)
		{
			m_coord = coord;
		}
		bool Region::IsLoaded() const
		{
			return m_loaded;
		}
		void Region::SetLoaded(bool loaded)
		{
			m_loaded = loaded;
		}

		bool Region::Unload(ChunkLoaderPtr pLoader, bool sync)
		{
			Coord region_origin = m_coord;
			region_origin.x *= REGION_SIZE;
			region_origin.y *= REGION_HEIGHT;
			region_origin.z *= REGION_SIZE;

			for(int32 x = 0; x < REGION_CHUNK_LENGTH; ++x)
			{
				for(int32 z = 0; z < REGION_CHUNK_LENGTH; ++z)
				{
					for(int32 y = 0; y < REGION_CHUNK_HEIGHT; ++y)
					{
						Coord chunk_coord(x, y, z);
						chunk_coord *= CHUNK_SIZE;

						chunk_coord += region_origin;

						ChunkKey key(chunk_coord);

						if(nullptr == m_pChunkManager->FindChunk(key))
						{
							continue;
						}

						if(sync)
						{
							pLoader->UnloadChunkSync(shared_from_this(), key);
						}
						else
						{
							pLoader->UnloadChunk(shared_from_this(), key);
						}

					}
				}
			}


			return Save();
		}
		float* Region::GetHeightmap()
		{
			if(m_heightMap == nullptr)
			{
				GenHeightmap();
			}
			return m_heightMap;
		}
		bool Region::LoadChunk(ChunkPtr pChunk)
		{
			// load chunk
			const ChunkKey& key = pChunk->GetKey();

			float* height_map = GetHeightmap();

			Coord region_origin = GetRegionOrigin();
			Coord chunk_origin = key.ToChunkOrigin();

			Coord dc = chunk_origin - region_origin;

			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					int rx = x + dc.x;
					int rz = z + dc.z;
					float h = height_map[rz * REGION_SIZE + rx] * 100;

					if(h < (chunk_origin.y))
					{
						continue;
					}

					float dy = h - chunk_origin.y;

					dy = dy > CHUNK_SIZE ? CHUNK_SIZE : dy;

					for(int y = 0; y < dy; ++y)
					{
						pChunk->SetBlock(x, y, z, 1);
					}
				}
			}

			m_pOctTree->AddChunk(pChunk);
			return true;
		}
		bool Region::UnloadChunk(ChunkPtr pChunk)
		{
			// save or not
			if(pChunk->IsModified() == true)
			{
				// save
			}

			m_pOctTree->RemoveChunk(pChunk);

			return true;
		}
		void Region::FrustumCull(const math::ViewFrustum& vf, const std::function<void(ChunkMeshPtr)>& op)
		{
			m_pOctTree->FrustumCull(vf, op);
		}
	}
}

