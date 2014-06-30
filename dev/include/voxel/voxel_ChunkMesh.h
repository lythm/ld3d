#pragma once

#include "voxel/voxel_ChunkKey.h"


namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS ChunkMesh
		{
		public:

			struct VoxelVertex
			{
				math::Vector3										pos;
				math::Vector3										normal;
				math::Vector3										uv;
				//math::Vector4										ao;
				float												ao;
			};


			struct Subset
			{
				void*												vertexBuffer;
				uint32												vertexCount;
				uint8												type;
				uint32												material_id;
			};

			ChunkMesh(void);
			virtual ~ChunkMesh(void);

			void													Release();
			bool													Reset();
			bool													AllocVertexBuffer(uint32 nVerts);
			void*													GetVertexBuffer();

			uint32													GetVertexCount();

			void													AddSubset(const Subset& sub);

			uint32													GetSubsetCount();
			const Subset&											GetSubset(uint32 index);
		private:

			void*													m_pVertexBuffer;
			uint32													m_nVertexCount;
			uint32													m_vertexBufferBytes;

			std::vector<Subset>										m_subsets;
		};
	}
}
