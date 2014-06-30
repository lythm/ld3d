#pragma once

#include "voxel/voxel_Coord.h"
#include "voxel/voxel_ChunkKey.h"
#include <bitset>

namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS ChunkAdjacency
		{
		public:
			enum 
			{
				n_x						= 1,
				p_x						= 1 << 1,
				n_y						= 1 << 2,
				p_y						= 1 << 3,
				n_z						= 1 << 4,
				p_z						= 1 << 5,
				all_vector				= 0xfc,
			};
			ChunkAdjacency();
			ChunkAdjacency(const ChunkKey& key);
			ChunkAdjacency(const ChunkAdjacency& other);
			~ChunkAdjacency(void);

			void											Reset();

			bool											CheckBlockAdjacency(int32 x, int32 y, int32 z, int32 v) const;
			bool											CheckBlock(int32 x, int32 y, int32 z) const;
			void											UpdateChunkAdjacency(const ChunkKey& key, ChunkPtr pChunk);
			void											OnBlockChange(int32 x, int32 y, int32 z, bool val);

			bool											IsVisible() const;
			bool											IsComplete() const;
		private:
			// set this block neightbour flag
			bool											CheckVisiblity() const;

			bool											CheckCoord(int32 x, int32 y, int32 z) const;
			
			int32											ToIndex(int32 x, int32 y, int32 z) const;

			Coord											ToAdjacentBlockCoord(const Coord& c, uint32 adj) const;

			
		private:
			bool											m_visible;
			ChunkKey										m_key;

			std::bitset<(CHUNK_SIZE + 2) *
				(CHUNK_SIZE + 2) *
				(CHUNK_SIZE + 2)>							m_blocks;

			std::bitset<3 * 3 * 3>							m_adj;
		};
	}
}
