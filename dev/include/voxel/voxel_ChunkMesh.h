#pragma once

#include "voxel/voxel_ChunkKey.h"


namespace ld3d
{
	namespace voxel
	{
		class ChunkMesh
		{
		public:

			struct VoxelFace
			{
				math::Vector3			verts[4];
				math::Vector3			normal;
				math::Vector2			uv[4];
				uint8					type;
				math::Color4			ao[4];
			};


			ChunkMesh(void);
			virtual ~ChunkMesh(void);

			bool											UpdateMesh(WorldPtr pWorld, const ChunkKey& key);

		private:
			bool											_gen_mesh_simple(WorldPtr pWorld, ChunkPtr pChunk);
		private:
			void*											m_pVertexBuffer;
			Coord											m_chunkCoord;


			std::vector<VoxelFace>							m_mesh;
		};
	}
}
