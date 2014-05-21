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

			bool													Gen(WorldGenPtr pGen);

			bool													IsModified() const;
			void													SetModified();

			void													Reset();
		private:
			std::vector<ChunkPtr>									m_chunks;

			bool													m_modified;

		};
	}
}
