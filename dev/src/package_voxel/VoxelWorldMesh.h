#pragma once

namespace ld3d
{
	class VoxelWorldMesh
	{
	public:
		struct VoxelVertex
		{
			math::Vector3										pos;
			math::Vector3										normal;
			math::Vector2										uv;
		};


		struct Subset
		{
			void*												vertexBuffer;
			uint32												vertexCount;
			uint8												type;
		};

		VoxelWorldMesh(void);
		virtual ~VoxelWorldMesh(void);


		bool									Reset();
		void									Release();
		bool									AllocVertexBuffer(uint32 nVerts);
		void*									GetVertexBuffer();

		uint32									GetVertexCount();

		void									AddSubset(const Subset& sub);

		uint32									GetSubsetCount();
		const Subset&							GetSubset(uint32 index);
	private:

		void*									m_pVertexBuffer;
		uint32									m_nVertexCount;
		uint32									m_vertexBufferBytes;

		std::vector<Subset>						m_subsets;
	};
}
