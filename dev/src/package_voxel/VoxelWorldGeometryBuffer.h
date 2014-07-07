#pragma once

namespace ld3d
{
	class VoxelWorldGeometryBuffer
	{
	public:
		VoxelWorldGeometryBuffer(void);
		virtual ~VoxelWorldGeometryBuffer(void);

		bool										Initialize(RenderManagerPtr pRenderManager, uint32 nVerts);
		void										Release();


		void										Begin(uint32 verts_at_least);
		void										End();
		bool										Push(const voxel::ChunkMesh::Subset& sub);

		GeometryDataPtr								GetGeometryData();
		
		uint32										GetVertexCount();
		uint32										GetBaseVertex();

		
	private:
		uint32										m_nVBBytes;
		uint32										m_nVBCurrent;
		uint32										m_nVBOffset;
		uint32										m_nVertexStride;
		uint32										m_nVertexCount;
		uint32										m_baseVertex;
		GeometryDataPtr								m_pGeometry;

		GPUBufferPtr								m_pVB;
		uint8*										m_pData;
		RenderManagerPtr							m_pRenderManager;
	};


}