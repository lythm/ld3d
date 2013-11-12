#pragma once

namespace ld3d
{
	class VoxelWorldMesh
	{
	public:

		VoxelWorldMesh(void);
		virtual ~VoxelWorldMesh(void);



	private:

		void*									m_pVertexBuffer;
		uint32									m_nVertexCount;
		uint32									m_vertexBufferBytes;

		uint32									m_materialID;
	};
}
