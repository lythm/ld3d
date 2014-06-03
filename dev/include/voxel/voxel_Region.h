#pragma once

#include "voxel/voxel_Coord.h"
namespace ld3d
{
	namespace voxel
	{
		class Region : public RefCount
		{
		public:
			Region();
			virtual ~Region(void);

			bool													Initialize(WorldPtr pWorld, const Coord& coord);
			void													Release();

			bool													Load();
			bool													Unload();
			bool													Save();

			bool													GenChunk(const Coord& chunk_origin);
			bool													GenRegion();
			bool													IsModified() const;
			void													SetModified();

			const Coord&											GetRegionCoord() const;
			void													SetRegionCoord(const Coord& coord);

			bool													IsLoaded() const;
			void													SetLoaded(bool loaded);

		private:
			
			bool													m_modified;

			Coord													m_coord;

			ChunkManagerPtr											m_pChunkManager;

			bool													m_loaded;

			WorldPtr												m_pWorld;
		};
	}
}
