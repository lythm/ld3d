#pragma once

#include "voxel/voxel_ChunkKey.h"


namespace ld3d
{
	namespace voxel
	{
		class ChunkMesh
		{
		public:

			struct Vertex
			{
				math::Vector3 pos;
				math::Vector3 normal;
				math::Vector3 uv;
				math::Vector4 color;
			};
			struct Subset
			{
				//
				// vector3 pos
				// vector3 normal
				// vector3 uv
				// vector4 color(ao);
				//


				std::vector<Vertex>							vertex_buffer;
				uint8										type;
				uint32										material_id;
			};
			ChunkMesh(void);
			virtual ~ChunkMesh(void);

			bool											UpdateMesh(WorldPtr pWorld, const ChunkKey& key);

		private:
			void*											m_pVertexBuffer;
			Coord											m_chunkCoord;

			std::vector<Subset>								m_subsets;
		};
	}
}
