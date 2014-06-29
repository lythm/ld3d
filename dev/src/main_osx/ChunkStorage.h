#pragma once

#include "platform/platform.h"
#include <fstream>
#include <unordered_map>

#include <boost/filesystem.hpp>
namespace ld3d
{
	namespace voxel
	{
		class ChunkStorage
		{
		public:
			
			struct Region
			{
				// region key
				uint64										key;
				std::fstream								stream;
				std::unordered_map<uint64, uint64>			chunk_offset;
			};
			
			
			ChunkStorage();
			virtual ~ChunkStorage();

			bool											OpenWorld();
			void											CloseWorld();
			
			
			
			bool											ChunkExist() const;
			bool											LoadChunk();
			
			void											SaveChunk();
			
			
		private:
			void											OpenRegion();
			void											CloseRegion();
			
			void											AddToRegionCache();

		private:
			
			boost::filesystem::path							m_worldRoot;
			
			std::unordered_map<uint64, Region>				m_regions;
			
			std::list<Region>								m_regionCache;
			
		};
	}
}

