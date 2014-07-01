#pragma once

namespace ld3d
{
	namespace voxel
	{
		class ChunkStorage
		{
			struct worker
			{
				void operator()()
				{
				}
			};
		public:
			ChunkStorage(void);
			virtual ~ChunkStorage(void);

			bool													Initialize();
			void													Release();

		private:
			boost::thread											m_worker;
		};


	}
}