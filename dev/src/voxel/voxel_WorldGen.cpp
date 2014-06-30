#include "voxel_pch.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel/voxel_WorldGenPass.h"

namespace ld3d
{
	namespace voxel
	{

		WorldGen::WorldGen(void)
		{

		}

		WorldGen::~WorldGen(void)
		{
		}

		bool WorldGen::GenChunk(const ChunkKey& key, ChunkData& chunk_data, ChunkAdjacency& adj)
		{
			std::shared_ptr<HeightMap> pHM = GetHeightMap(key);

			chunk_data.Fill(0);

			Coord chunk_origin = key.ToChunkOrigin();

			/*if(chunk_origin.y > (pHM->max_height + 1))
			{
				return false;
			}*/

			bool ret = false;
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					for(int y = 0; y < CHUNK_SIZE; ++y)
					{
						/*if( (y + chunk_origin.y) > 50)
						{
						continue;
						}*/
						double vec[3];
						vec[0] = x + chunk_origin.x;
						vec[1] = y + chunk_origin.y;
						vec[2] = z + chunk_origin.z;


						vec[0] /= 1000;
						vec[1] /= 1000;
						vec[2] /= 1000;

						double h = m_noise.perlin_noise_3D(vec);

						h -= double(y + chunk_origin.y) / 50.0;

						double vec1[2];

						

						float b = pHM->data[x + z * CHUNK_SIZE];

						///// test

						//if((y + chunk_origin.y) > 50 || (y + chunk_origin.y) < 0)
						//{
						//	continue;
						//}
						//

						//chunk_data.Set(x, y, z, 2);
						//adj.OnBlockChange(x, y, z, true);
						//ret = true;
						//continue;
						//////// 


						if((y + chunk_origin.y) > b)
						{
							continue;
						}
						if(h > 0 && h < 1)
						{
							if(h > 0.5)
							{
								chunk_data.Set(x, y, z, 2);
							}
							else
							{
								chunk_data.Set(x, y, z, 1);
							}
							ret = true;
							adj.OnBlockChange(x, y, z, true);
						}
					}
				}
			}

			return ret;
		}

		bool WorldGen::Initialize()
		{
			m_noise.set_up(1, 20, 1, (int)os_get_tick());
			m_noiseBase.set_up(1, 5, 1, (int)os_get_tick());
			return true;
		}
		void WorldGen::Release()
		{
		}
		WorldPtr WorldGen::GetWorld()
		{
			return m_pWorld;
		}
		void WorldGen::SetWorld(WorldPtr pWorld)
		{
			m_pWorld = pWorld;
		}
		void WorldGen::AddPass(WorldGenPassPtr pPass)
		{
			m_passList.push_back(pPass);
		}
		void WorldGen::GenHeightMap(const ChunkKey& key, HeightMap& hm)
		{
			Coord chunk_origin = key.ToChunkOrigin();
			
			float max_height = std::numeric_limits<float>::lowest();
			
			for(int32 x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int32 z = 0; z < CHUNK_SIZE; ++z)
				{
					double vec[2];

					vec[0] = x + chunk_origin.x;
					vec[1] = z + chunk_origin.z;


					vec[0] /= 1000;
					vec[1] /= 1000;

					double b = m_noiseBase.perlin_noise_2D(vec);

					b *= 100;

					if(b > max_height)
					{
						max_height = b;
					}
					hm.data[z * CHUNK_SIZE + x] = b;
				}
			}

			hm.chunk_key = key;
			hm.max_height = max_height;
		}
		std::shared_ptr<WorldGen::HeightMap> WorldGen::GetHeightMap(const ChunkKey& key)
		{
			auto it = m_hms.find(key.AsUint64());
			if(it != m_hms.end())
			{
				return m_hms[key.AsUint64()];
			}

			std::shared_ptr<HeightMap> hm = std::make_shared<HeightMap>();
			GenHeightMap(key, *hm);

			m_hms[key.AsUint64()] = hm;

			return m_hms[key.AsUint64()];
		}
	}
}
