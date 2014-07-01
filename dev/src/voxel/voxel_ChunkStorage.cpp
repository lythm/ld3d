#include "voxel_pch.h"
#include "voxel_ChunkStorage.h"


namespace ld3d
{
	namespace voxel
	{

		ChunkStorage::ChunkStorage(void)
		{
		}


		ChunkStorage::~ChunkStorage(void)
		{
		}
		bool ChunkStorage::Initialize()
		{
			m_worker = boost::thread(worker());
			return true;
		}
		void ChunkStorage::Release()
		{
			m_worker.join();

		}
	}
}