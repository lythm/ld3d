#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_Bound.h"

#include "voxel/voxel_ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS World : public std::enable_shared_from_this<World>
		{
		public:
			World(void);
			virtual ~World(void);

			bool											Create(const std::string& name, WorldGenPtr pGen, MeshizerPtr pMeshizer, Allocator* pAlloc = nullptr, Logger logger = Logger());

			void											Destroy();

			bool											AddBlock(const Coord& c, uint8 type);
			bool											ReplaceBlock(const Coord& c, uint8 type);
			bool											RemoveBlock(const Coord& c);
			bool											IsEmpty(const Coord& c);
			uint8											GetBlock(const Coord& c);
			void											UpdateBlock(const Coord& c);

			bool											Inside(const Coord& c) const;

			const Bound&									GetBound() const;		

			ChunkPtr										FindChunk(const ChunkKey& key);

			void											ClearDirtyChunks();

			void											Update(float dt);
			void											UpdateLoaderProcess();
			ChunkManagerPtr									GetChunkManager();
			RegionManagerPtr								GetRegionManager();

			void											SetMeshizer(MeshizerPtr pMeshizer);
			

			WorldGenPtr										GetWorldGen();

			void											AddDirtyChunkHandler(const std::function<void (ChunkPtr)>& handler);

			uint32											GetLoadingQueueSize() const;
			uint32											GetUnloadingQueueSize() const;

			uint32											GetChunkCount() const;

			ChunkLoaderPtr									GetChunkLoader();
		private:
		
			
		private:
			WorldGenPtr										m_pGen;
			Bound											m_worldBound;

			RegionManagerPtr								m_pRegionManager;
			ChunkManagerPtr									m_pChunkManager;
			ChunkLoaderPtr									m_pChunkLoader;
			std::string										m_name;
		};
	}
}
