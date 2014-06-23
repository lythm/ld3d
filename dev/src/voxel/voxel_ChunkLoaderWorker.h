#pragma once

#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_ChunkAdjacency.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkLoaderWorker
		{
		public:
			enum
			{
				ev_exit,
				ev_load_chunk,
				ev_gen_mesh,
				ev_unload_chunk,

			};

			struct Subset
			{
				void*												vertexBuffer;
				uint32												vertexCount;
				uint8												type;
				uint32												material_id;
			};
			struct Task
			{
				uint32											ev;
				ChunkKey										key;
				uint8*											chunk_data;
				ChunkAdjacency									chunk_adjacency;
				bool											chunk_empty;

				ChunkMeshPtr									mesh;

			};
			struct TaskResult
			{

			};

			typedef boost::lockfree::spsc_queue<Task, boost::lockfree::fixed_sized<true>>			TaskQueue;

			ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize);
			virtual ~ChunkLoaderWorker(void);


			
			void																					Start();
			void																					Stop();
			void																					Join();
			

			bool																					PushTask(const Task& task);
			bool																					PopTask(Task& task);

			void																					SetMeshizer(MeshizerPtr pMeshizer);
		private:
			void																					_gen_mesh(Task& t);
			void																					_load_chunk(Task& t);
			void																					_run();
		private:
			TaskQueue																				m_in;
			TaskQueue																				m_out;
			MeshizerPtr																				m_pMeshizer;
			boost::thread																			m_thread;
		};
	}
}
