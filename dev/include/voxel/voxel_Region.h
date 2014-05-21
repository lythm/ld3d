#pragma once

namespace ld3d
{
	namespace voxel
	{
		class Region
		{
		public:
			Region(void);
			virtual ~Region(void);


			bool													Load();
			bool													Save();
		private:
			ChunkPtr												m_chunks[REGION_SIZE][REGION_SIZE];

			bool													m_dirty;
		};


	}
}
