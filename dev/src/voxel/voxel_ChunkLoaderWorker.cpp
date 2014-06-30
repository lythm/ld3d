#include "voxel_pch.h"
#include "voxel_ChunkLoaderWorker.h"
#include "voxel_VoxelUtils.h"
#include "voxel/voxel_Chunk.h"
#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_WorldGen.h"

namespace ld3d
{
	namespace voxel
	{
		ChunkLoaderWorker::ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize) : 
			m_in(inQueueSize), 
			m_out(outQueueSize)
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

			m_pMeshizer->GenerateMesh(t.key, t.chunk_data, t.chunk_adjacency, chunk_mesh_base, t.mesh);

			while(m_out.push(t) == false)
			{
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		void ChunkLoaderWorker::_load_chunk(Command& t)
		{
			t.chunk_empty = m_pGenerator->GenChunk(t.key, t.chunk_data, t.chunk_adjacency) == false;

			if(t.gen_mesh && t.chunk_empty != true)
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
		
		void ChunkLoaderWorker::SetWorldGenerator(WorldGenPtr pWorldGen)
		{
			m_pGenerator = pWorldGen;
		}
	}
}
