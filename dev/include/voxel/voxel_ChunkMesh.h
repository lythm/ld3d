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
				math::Vector3										uv;
				float												ao;
				uint32												normal;
			};


			struct Subset
			{
				void*												vertexBuffer;
				uint32												vertexCount;
				uint32												material_id;

				void*												indexBuffer;
				uint32												indexCount;
			};

			ChunkMesh(void);
			virtual ~ChunkMesh(void);

			void													Release();
			bool													Reset();
			
			
			bool													AllocVertexBuffer(uint32 nVerts);
			void*													GetVertexBuffer();
			uint32													GetVertexCount();


			bool													AllocIndexBuffer(uint32 nIndexCount);
			void*													GetIndexBuffer();
			uint32													GetIndexCount();

			void													AddSubset(const Subset& sub);

			uint32													GetSubsetCount();
			const Subset&											GetSubset(uint32 index);
		private:

			void*													m_pVertexBuffer;
			uint32													m_nVertexCount;
			uint32													m_vertexBufferBytes;

			std::vector<Subset>										m_subsets;

			void*													m_pIndexBuffer;
			uint32													m_nIndexCount;
			uint32													m_nIndexBufferBytes;
		};
	}
}
