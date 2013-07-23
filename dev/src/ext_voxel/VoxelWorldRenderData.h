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
		Material2Ptr												GetMaterial();
		math::Matrix44											GetWorldMatrix();
		bool													IsDeferred();

		void													PrepareRenderList(VoxelWorldChunk* pList);

		RenderData2Ptr											GetRenderData();
	private:
		void													_draw(Sys_Graphics2Ptr pSysGraphics, Material2Ptr pMaterial);
	private:
		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		Material2Ptr											m_pMaterial;

		Sys_Graphics2Ptr										m_pGraphics;

		uint32													m_nVBBytes;
		uint32													m_nVBCurrent;
		uint32													m_nVBOffset;
		uint32													m_nVertexStride;
		uint32													m_nVertexCount;

		VoxelWorldChunk*										m_pRenderList;

		RenderData2Ptr											m_pRenderData;

		RenderManagerPtr										m_pRenderManager;

		VertexLayout											m_vertexLayout;
	};
}
