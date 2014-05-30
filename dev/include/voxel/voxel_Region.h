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

			bool													Initialize(WorldPtr pWorld, const Coord& coord);
			void													Release();

			bool													Load();
			bool													Unload();
			bool													Save();

			bool													GenChunk(const Coord& chunk_coord);
			bool													GenRegion();
			bool													IsModified() const;
			void													SetModified();

			const Coord&											GetRegionCoord() const;
			void													SetRegionCoord(const Coord& coord);

			bool													IsLoaded() const;
			void													SetLoaded(bool loaded);

			void													IncRef();
			void													DecRef();
			int32													GetRef() const;
		private:
			
			bool													m_modified;

			Coord													m_coord;

			ChunkManagerPtr											m_pChunkManager;

			bool													m_loaded;

			int32													m_refCount;

			WorldPtr												m_pWorld;
		};
	}
}
