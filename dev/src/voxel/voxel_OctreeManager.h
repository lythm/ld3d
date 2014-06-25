#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class OctreeManager
		{
		public:
			OctreeManager(void);
			virtual ~OctreeManager(void);


			void											Update();
			void											AddChunk(ChunkPtr pChunk);
			void											RemoveChunk(ChunkPtr pChunk);
			void											Clear();
			void											FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op);

			int32											GetFaceCount();
		private:

			OctreePtr										FindOctree(const Coord& region_origin);
		private:

			std::list<OctreePtr>							m_octrees;

			int32											m_faceCount;

		};


	}
}