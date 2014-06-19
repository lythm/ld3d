#pragma once

#include "voxel/voxel_Coord.h"
namespace ld3d
{
	namespace voxel
	{
		class Region : public RefCount, public std::enable_shared_from_this<Region>
		{
		public:
			Region();
			virtual ~Region(void);

			bool													Initialize(WorldPtr pWorld, const Coord& coord);
			void													Release();

			bool													Load(ChunkLoaderPtr pLoader, bool sync = false, const std::function<void(RegionPtr, ChunkPtr)>& on_chunk_loaded = std::function<void(RegionPtr, ChunkPtr)>());
			bool													Unload(ChunkLoaderPtr pLoader, bool sync = false);

			bool													Save();


			bool													GenRegion();
			bool													IsModified() const;
			void													SetModified();

			const Coord&											GetRegionCoord() const;
			void													SetRegionCoord(const Coord& coord);

			Coord													GetRegionOrigin() const;
			bool													IsLoaded() const;
			void													SetLoaded(bool loaded);

			float*													GetHeightmap();
			void													GenHeightmap();

			bool													LoadChunk(ChunkPtr pChunk);
			bool													UnloadChunk(ChunkPtr pChunk);

			void													FrustumCull(const math::ViewFrustum& vf, const std::function<void(ChunkMeshPtr)>& op);

			bool													RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal);

			void													AddChunk(ChunkPtr pChunk);
		private:

		private:
			
			bool													m_modified;

			Coord													m_coord;

			ChunkManagerPtr											m_pChunkManager;

			bool													m_loaded;

			WorldPtr												m_pWorld;

			float*													m_heightMap;

			math::AABBox											m_heightMapAABBox;

			OctreePtr												m_pOctTree;
		};
	}
}
