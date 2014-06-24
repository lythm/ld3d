#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS ChunkAdjacency
		{
		public:
			enum 
			{
				n_x						= 2,
				p_x						= 3,
				n_y						= 4,
				p_y						= 5,
				n_z						= 6,
				p_z						= 7,
				all_vector				= 0xfc,
			};
			ChunkAdjacency();
			ChunkAdjacency(const ChunkKey& key);
			ChunkAdjacency(const ChunkAdjacency& other);
			~ChunkAdjacency(void);

			void											Reset();

			// set this block neightbour flag
			void											SetBlockAdjacency(int32 x, int32 y, int32 z, int32 v, bool val);
			bool											CheckBlockAdjacency(int32 x, int32 y, int32 z, int32 v) const;
			
			void											OnAdjacentChunkLoaded(const Coord& chunk_coord, ChunkPtr pChunk);
			
			void											OnBlockChange(int32 x, int32 y, int32 z, bool val);

			bool											IsVisible() const;
		private:

			bool											CheckVisiblity() const;

			bool											CheckCorrd(int32 x, int32 y, int32 z);
			
		private:
			uint8											m_blockAdjacency[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
			bool											m_visible;
			ChunkKey										m_key;
		};
	}
}
