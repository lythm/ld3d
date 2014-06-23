#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS WorldViewport : public std::enable_shared_from_this<WorldViewport>
		{
		public:
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

			void														SetRegionLoadedHandler(const std::function<void (RegionPtr)>& handler);
			void														SetRegionUnloadedHandler(const std::function<void (RegionPtr)>& handler);

			void														SetRadius(uint32 radius);
			void														FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op);

			//bool														RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal);
		private:
			void														UpdateVP();
			
			void														_on_dirty_chunk(ChunkPtr pChunk);
			
		private:
			WorldPtr													m_pWorld;
			ChunkLoaderPtr												m_pLoader;
			ChunkLoaderAsyncPtr											m_pLoaderAsync;
			RegionManagerPtr											m_pRegionManager;
			
			std::function<void (const Coord&, ChunkPtr)>				handler_dirty_chunk;

			VPSphere													m_VP;
			VPSphere													m_lastVP;
		};
	}
}

