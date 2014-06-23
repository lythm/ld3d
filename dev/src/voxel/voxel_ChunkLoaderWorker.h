#pragma once

#include "voxel/voxel_ChunkKey.h"
namespace ld3d
{
	namespace voxel
	{
		class ChunkLoaderWorker
		{
		public:

			struct Task
			{
				ChunkKey										key;
			};
			struct TaskResult
			{

			};

			ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize);
			virtual ~ChunkLoaderWorker(void);


			void																					_run();

		private:
			boost::lockfree::spsc_queue<Task, boost::lockfree::fixed_sized<true>>					m_in;
			boost::lockfree::spsc_queue<Task, boost::lockfree::fixed_sized<true>>					m_out;
		};


	}
}