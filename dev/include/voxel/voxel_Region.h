#pragma once

#include "voxel/voxel_Coord.h"
namespace ld3d
{
	namespace voxel
	{
		class Region
		{
		public:
			Region();
			virtual ~Region(void);

			bool													Initialize(ChunkManagerPtr pChunkManager, const Coord& coord);
			void													Release();

			bool													Load(WorldGenPtr pGen);
			bool													Save();

			bool													Gen(WorldGenPtr pGen);

			bool													IsModified() const;
			void													SetModified();

			void													Reset(const Coord& coord);

			const Coord&											GetRegionCoord() const;
			void													SetRegionCoord(const Coord& coord);

			bool													IsLoaded() const;
			void													SetLoaded(bool loaded);
		private:
			
			bool													m_modified;

			Coord													m_coord;

			ChunkManagerPtr											m_pChunkManager;

			bool													m_loaded;
		};
	}
}
