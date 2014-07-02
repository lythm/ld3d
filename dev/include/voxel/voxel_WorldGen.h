#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_ChunkData.h"
namespace ld3d
{
	namespace voxel
	{
		class WorldGen 
		{
		public:

			struct HeightMap
			{
				double											max_height;
				float											data[CHUNK_SIZE * CHUNK_SIZE];
			};

			WorldGen(void);
			virtual ~WorldGen(void);

			bool												GenChunk(const ChunkKey& key, ChunkData& chunk_data, ChunkAdjacency& adj);
			
		private:
			HeightMap*											GetHeightMap(const ChunkKey& key);
			void												GenHeightMap(const ChunkKey& key, HeightMap& hm);

			

		private:
			PerlinNoise											m_noise;
			PerlinNoise											m_noiseBase;

			std::unordered_map<uint64, HeightMap>				m_hms;
		};
	}
}
