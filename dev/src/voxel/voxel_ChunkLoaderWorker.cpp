#include "voxel_pch.h"
#include "voxel_ChunkLoaderWorker.h"
#include "voxel_VoxelUtils.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkLoaderWorker::ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize) : m_in(inQueueSize), m_out(outQueueSize)
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
				Task t;
				while(m_in.pop(t) == false)
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				}

				switch(t.ev)
				{
				case ev_exit:
					return;
				case ev_load_chunk:
					_load_chunk(t);
					break;
				case ev_gen_mesh:
					_gen_mesh(t);
					break;
				default:
					break;
				}
			}
		}
		void ChunkLoaderWorker::_gen_mesh(Task& t)
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
		void ChunkLoaderWorker::_load_chunk(Task& t)
		{
			// load chunk
			const ChunkKey& key = t.key;

			Coord chunk_origin = key.ToChunkOrigin();
			memset(t.chunk_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			t.chunk_empty = true;
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < CHUNK_SIZE; ++z)
				{
					float h = 0;

					if(h < (chunk_origin.y))
					{
						continue;
					}

					float dy = h - chunk_origin.y;

					dy = dy > CHUNK_SIZE ? CHUNK_SIZE : dy;

					if(dy == 0)
					{
						dy = 1;
					}
					for(int y = 0; y < dy; ++y)
					{
						uint32 index = Chunk::ToIndex(x, y, z);
						t.chunk_data[index] = 1;
						t.chunk_empty = false;
						t.chunk_adjacency.OnBlockChange(x, y, z, true);
					}
				}
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
			Task t;
			t.ev = ev_exit;
			m_in.push(t);
		}
		bool ChunkLoaderWorker::PushTask(const Task& task)
		{
			return m_in.push(task);
		}
		bool ChunkLoaderWorker::PopTask(Task& task)
		{
			return m_out.pop(task);
		}
	}
}
