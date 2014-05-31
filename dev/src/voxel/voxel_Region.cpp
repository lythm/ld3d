#include "voxel_pch.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_WorldGen.h"

namespace ld3d
{
	namespace voxel
	{
		Region::Region(void)
		{
			m_modified		= false;
			m_coord			= Coord();
			m_loaded		= false;
			m_refCount		= 0;
		}


		Region::~Region(void)
		{
		}
		bool Region::Load()
		{
			GenRegion();
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
		bool Region::GenRegion()
		{

			PerlinNoise p(3, 1, 1, rand());


			const Bound& bound = m_pWorld->GetBound();
			
			uint32 ex, ey, ez;
			bound.GetExtent(ex, ey, ez);



			Coord region_origin = m_pWorld->ToRegionOrigin(m_coord);

			uint16 height_map[REGION_SIZE * REGION_SIZE];


			for(int32 x = 0; x < REGION_SIZE; ++x)
			{
				for(int32 z = 0; z < REGION_SIZE; ++z)
				{
					double h = p.Get(double(x + region_origin.x) / double(ex), double(z + region_origin.z) / double(ez));

				}
			}


			for(int32 x = 0; x < REGION_CHUNK_LENGTH; ++x)
			{
				for(int32 z = 0; z < REGION_CHUNK_LENGTH; ++z)
				{
					Coord c = Coord(x, 0, z) * CHUNK_SIZE + region_origin;

					double h = p.Get(double(c.x) / double(ex), double(c.z) / double(ez));
					
					height_map[x + z * REGION_SIZE] = (h * REGION_HEIGHT) / 2;


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
			m_refCount		= 0;

			return true;
		}
		void Region::Release()
		{
			m_modified = false;
			m_coord = Coord();

			m_pChunkManager.reset();
		}
		const Coord& Region::GetRegionCoord() const
		{
			return m_coord;
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
		void Region::IncRef()
		{
			++m_refCount;
		}
		void Region::DecRef()
		{
			--m_refCount;
		}
		int32 Region::GetRef() const
		{
			return m_refCount;
		}
		bool Region::Unload()
		{
			return Save();
		}
	}
}

