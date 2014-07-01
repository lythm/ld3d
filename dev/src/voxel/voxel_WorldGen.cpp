#include "voxel_pch.h"
#include "voxel/voxel_WorldGen.h"

namespace ld3d
{
	namespace voxel
	{

		WorldGen::WorldGen(void)
		{
			m_noise.set_up(1, 20, 1, (int)os_get_tick());
			m_noiseBase.set_up(1, 5, 1, (int)os_get_tick());
		}

		WorldGen::~WorldGen(void)
		{
		}

		bool WorldGen::GenChunk(const ChunkKey& key, ChunkData& chunk_data, ChunkAdjacency& adj)
		{
			std::shared_ptr<HeightMap> pHM = GetHeightMap(key);

			chunk_data.Fill(0);

			Coord chunk_origin = key.ToChunkOrigin();

			if(chunk_origin.y > (pHM->max_height + 1))
			{
				return false;
			}

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
							if(h > 0.8)
							{
								chunk_data.Set(x, y, z, 3);
							}
							else if(h > 0.6)
							{
								chunk_data.Set(x, y, z, 2);
							}
							else if(h > 0.4)
							{
								chunk_data.Set(x, y, z, 5);
							}
							else if(h > 0.2)
							{
								chunk_data.Set(x, y, z, 1);
							}
							else
							{
								chunk_data.Set(x, y, z, 4);
							}
							ret = true;
							adj.OnBlockChange(x, y, z, true);
						}
					}
				}
			}

			return ret;
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
			Coord c = key.tochunkCoord();
			c.y = 0;
			ChunkKey k;
			k.FromChunkCoord(c);
			
			auto it = m_hms.find(k.AsUint64());
			if(it != m_hms.end())
			{
				return m_hms[k.AsUint64()];
			}

			std::shared_ptr<HeightMap> hm = std::make_shared<HeightMap>();
			GenHeightMap(k, *hm);

			m_hms[k.AsUint64()] = hm;

			return m_hms[k.AsUint64()];
		}
	}
}
