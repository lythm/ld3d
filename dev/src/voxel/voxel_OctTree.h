#pragma once

#include "voxel/voxel_Coord.h"


namespace ld3d
{
	namespace voxel
	{
		class OctTree
		{
		public:
			
			enum
			{
				INVALID_FACE_ID			= -1,
			};
			OctTree(const Coord& region_origin);
			virtual ~OctTree(void);

			const math::AABBox&					GetBound() const;
			void								SetBound(const math::AABBox& bound);

			void								SetChild(int iChild, OctTreePtr pChild);
			OctTreePtr							GetChild(int iChild);

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

			OctTreePtr							m_pChildren[8];

			math::AABBox						m_bbox;

			ChunkPtr							m_pChunk;

			Coord								m_regionOrigin;
		};


	}
}