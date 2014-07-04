#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_Bound.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkCache;

		class _DLL_CLASS WorldViewport : public std::enable_shared_from_this<WorldViewport>
		{
		public:
			struct VPCylinder
			{
				Coord													center;
				uint32													radius;
				uint32													height;
			};
			struct VPSphere
			{
				Coord													center;
				uint32													radius;
			};

			WorldViewport();
			virtual ~WorldViewport(void);


			void														MoveTo(const Coord& c);

			bool														Open(WorldPtr pWorld, const Coord& center, uint32 raidus);
			void														Close();

			void														Update();

			const Coord	&												GetCenterCoord() const;
			void														SetDirtyChunkHandler(const std::function<void (const Coord&, ChunkPtr)>& handler);

			
			void														ClearDirtyChunkList();

			void														SetRadius(uint32 radius);
			void														FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op);

			void														RefreshMesh();
			//bool														RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal);
		private:
			void														UpdateVP();
			
			void														_on_dirty_chunk(ChunkPtr pChunk);
			
		private:
			WorldPtr													m_pWorld;
			ChunkLoaderPtr												m_pLoader;
			OctreeManagerPtr											m_pOctreeManager;
			ChunkManagerPtr												m_pChunkManager;
			std::function<void (const Coord&, ChunkPtr)>				handler_dirty_chunk;

			VPCylinder														m_VP;
			VPCylinder														m_lastVP;


			std::shared_ptr<ChunkCache>									m_pChunkCache;

											
		};
	}
}
