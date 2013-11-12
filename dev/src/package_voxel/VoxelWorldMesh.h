#pragma once

namespace ld3d
{
	class VoxelWorldMesh
	{
	public:
		VoxelWorldMesh(void);
		virtual ~VoxelWorldMesh(void);



	private:
		TexturePtr								m_pTex;

		void*									m_pVertexBuffer;
		uint32									m_nVertexCount;

	};
}
