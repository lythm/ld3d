#pragma once

namespace ld3d
{
	struct VoxelWorldChunk;
	class VoxelWorldRenderData
	{
	public:
		VoxelWorldRenderData(void);
		virtual ~VoxelWorldRenderData(void);

		bool													Initialize(RenderManagerPtr pRS);
		void													Release();

		void													Render(RenderManagerPtr pManager);
		MaterialPtr												GetMaterial();
		math::Matrix44											GetWorldMatrix();
		bool													IsDeferred();

		void													PrepareRenderList(VoxelWorldChunk* pList);

		RenderDataPtr											GetRenderData();
	private:
		void													_draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial);
	private:
		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		MaterialPtr											m_pMaterial;

		Sys_GraphicsPtr										m_pGraphics;

		uint32													m_nVBBytes;
		uint32													m_nVBCurrent;
		uint32													m_nVBOffset;
		uint32													m_nVertexStride;
		uint32													m_nVertexCount;

		VoxelWorldChunk*										m_pRenderList;

		RenderDataPtr											m_pRenderData;

		RenderManagerPtr										m_pRenderManager;

		VertexLayout											m_vertexLayout;
	};
}
