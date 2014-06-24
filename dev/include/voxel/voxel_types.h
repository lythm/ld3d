#pragma once


#include <vector>

#include "platform/platform.h"

#include "math/math_all.h"

#include "utils/utils_all.h"

#include <memory>

#include <list>

namespace ld3d
{
	namespace voxel
	{
		const uint8  VT_EMPTY													= 0;

		
		const uint32 CHUNK_SIZE													= 16;										// int block
		const uint32 BLOCK_SIZE													= 1;

		const uint32 REGION_CHUNK_LENGTH										= 32;										// in chunk
		const uint32 REGION_SIZE												= REGION_CHUNK_LENGTH * CHUNK_SIZE;			// in block
		
		
		
		class World;
		class WorldGen;
		class WorldGenPass;
		class Chunk;
		class ChunkManager;
		class WorldViewport;
		class Meshizer;
		class ChunkMesh;
		//class ChunkLoader;
		class Octree;
		class PoolManager;
		class ChunkLoader;
		class OctreeManager;


		typedef std::shared_ptr<OctreeManager>									OctreeManagerPtr;
		typedef std::shared_ptr<ChunkLoader>								ChunkLoaderPtr;
		typedef std::shared_ptr<PoolManager>									PoolManagerPtr;
		typedef std::shared_ptr<Octree>											OctreePtr;
		typedef std::shared_ptr<ChunkMesh>										ChunkMeshPtr;
		//typedef std::shared_ptr<ChunkLoader>									ChunkLoaderPtr;
		typedef std::shared_ptr<Meshizer>										MeshizerPtr;
		typedef std::shared_ptr<WorldViewport>									WorldViewportPtr;
		typedef std::shared_ptr<World>											WorldPtr;
		typedef std::shared_ptr<WorldGen>										WorldGenPtr;
		typedef std::shared_ptr<WorldGenPass>									WorldGenPassPtr;
		typedef std::shared_ptr<Chunk>											ChunkPtr;
		typedef std::shared_ptr<ChunkManager>									ChunkManagerPtr;



		
	}		
}
