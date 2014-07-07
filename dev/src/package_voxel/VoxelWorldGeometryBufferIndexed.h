#pragma once

namespace ld3d
{
	class VoxelWorldGeometryBufferIndexed
	{
	public:
		VoxelWorldGeometryBufferIndexed(void);
		virtual ~VoxelWorldGeometryBufferIndexed(void);

		bool										Initialize(RenderManagerPtr pRenderManager, uint32 nVerts);
		void										Release();

		void										Begin(uint32 verts_at_least);
		void										End();

		bool										Push(const voxel::ChunkMesh::Subset& sub);

		GeometryDataPtr								GetGeometryData();
		
		uint32										GetVertexCount();
		uint32										GetBaseVertex();

		uint32										GetIndexCount();
		uint32										GetBaseIndex();

		uint8*										m_indexBufferCopy;

	private:
		uint32										m_nVBBytes;
		uint32										m_nVBCurrent;
		uint32										m_nVBOffset;
		uint32										m_nVertexStride;
		uint32										m_nVertexCount;
		uint32										m_baseVertex;

		GeometryDataPtr								m_pGeometry;

		GPUBufferPtr								m_pIB;
		GPUBufferPtr								m_pVB;
		uint8*										m_pIBData;
		uint8*										m_pVBData;
		RenderManagerPtr							m_pRenderManager;

		uint32										m_nIBBytes;
		uint32										m_nIBOffset;
		uint32										m_nIBCurrent;
		uint32										m_nIndexCount;
		uint32										m_baseIndex;

		
	};


}