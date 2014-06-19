#pragma once

#include "voxel/voxel_Coord.h"


namespace ld3d
{
	namespace voxel
	{
		class Octree
		{
		public:
			
			enum
			{
				INVALID_FACE_ID			= -1,
			};
			Octree(const Coord& region_origin);
			virtual ~Octree(void);

			const math::AABBox&					GetBound() const;
			void								SetBound(const math::AABBox& bound);

			void								SetChild(int iChild, OctreePtr pChild);
			OctreePtr							GetChild(int iChild);

			bool								IsLeaf() const;

			bool								AddChunk(ChunkPtr pChunk);
			void								RemoveChunk(ChunkPtr pChunk);
			void								FrustumCull(const math::ViewFrustum& vf, std::function<void (ChunkMeshPtr)> op);

			bool								RayPick(const math::Ray& r, Real& t);

		private:
			bool								SubDivideBound(const math::AABBox& bound, math::AABBox Bounds[8]);
			bool								_add_chunk(ChunkPtr pChunk);
			void								_remove_chunk(ChunkPtr pChunk);
		private:

			OctreePtr							m_pChildren[8];

			math::AABBox						m_bbox;

			ChunkPtr							m_pChunk;

			Coord								m_regionOrigin;
		};


	}
}