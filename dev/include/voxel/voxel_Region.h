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

			void													FrustumCull(const math::ViewFrustum& vf, const std::function<void(ChunkMeshPtr)>& op);

			bool													RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal);

			void													AddChunk(ChunkPtr pChunk);

			const Coord&											GetRegionOrigin();
		private:

		private:
			
			Coord													m_coord;

			ChunkManagerPtr											m_pChunkManager;

			WorldPtr												m_pWorld;

			OctreePtr												m_pOctTree;
		};
	}
}
