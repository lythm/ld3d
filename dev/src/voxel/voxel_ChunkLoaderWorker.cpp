#include "voxel_pch.h"
#include "voxel_ChunkLoaderWorker.h"

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
		void ChunkLoaderWorker::_run()
		{
			Task t;
			while(m_in.pop(t) == false)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}

		}
	}
}
