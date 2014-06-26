#include "voxel_pch.h"
#include "voxel_ChunkLoaderWorker.h"
#include "voxel_VoxelUtils.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkLoaderWorker::ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize) : 
			m_in(inQueueSize), 
			m_out(outQueueSize), 
			m_noise(1, 50, 1, (int)os_get_tick()),
			m_noiseBase(1, 10, 1, (int)os_get_tick())
		{
		}


		ChunkLoaderWorker::~ChunkLoaderWorker(void)
		{
		}
		void ChunkLoaderWorker::SetMeshizer(MeshizerPtr pMeshizer)
		{
			m_pMeshizer = pMeshizer;
		}
		void ChunkLoaderWorker::_run()
		{
			while(true)
			{
				Command t;
				while(m_in.pop(t) == false)
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				}

				switch(t.id)
				{
				case cmd_exit:
					return;
				case cmd_load_chunk:
					_load_chunk(t);
					break;
				case cmd_gen_mesh:
					_gen_mesh(t);
					break;
				default:
					break;
				}
			}
		}
		void ChunkLoaderWorker::_gen_mesh(Command& t)
		{
			Coord chunk_origin = t.key.ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);
			
			Coord chunk_mesh_base = chunk_origin - region_origin;

			m_pMeshizer->DoGenerateMesh(t.key, t.chunk_data, t.chunk_adjacency, chunk_mesh_base, t.mesh);

			while(m_out.push(t) == false)
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		void ChunkLoaderWorker::_load_chunk(Command& t)
		{
			t.chunk_empty = GenerateChunk(t.key, t.chunk_data, t.chunk_adjacency) == false;

			if(t.gen_mesh)
			{
				_gen_mesh(t);
				return;
			}

			while(m_out.push(t) == false)
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		void ChunkLoaderWorker::Start()
		{
			m_thread = boost::thread(boost::bind(&ChunkLoaderWorker::_run, this));
		}
		void ChunkLoaderWorker::Join()
		{
			m_thread.join();
		}
		void ChunkLoaderWorker::Stop()
		{
			Command t;
			t.id = cmd_exit;
			m_in.push(t);
		}
		bool ChunkLoaderWorker::PushTask(const Command& task)
		{
			return m_in.push(task);
		}
		bool ChunkLoaderWorker::PopTask(Command& task)
		{
			return m_out.pop(task);
		}
		bool ChunkLoaderWorker::GenerateChunk(const ChunkKey& key, ChunkData& chunk_data, ChunkAdjacency& adj)
		{
			// load chunk
			chunk_data.Fill(0);

			Coord chunk_origin = key.ToChunkOrigin();
			
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

						vec1[0] = x + chunk_origin.x;
						vec1[1] = z + chunk_origin.z;
					

						vec1[0] /= 1000;
						vec1[1] /= 1000;

						double b = m_noiseBase.perlin_noise_2D(vec1);

						b *= 100;

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
	}
}
