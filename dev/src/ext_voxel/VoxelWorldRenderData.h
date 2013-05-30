#pragma once

namespace ld3d
{
	class VoxelWorldRenderData : public RenderData
	{
	public:
		VoxelWorldRenderData(void);
		virtual ~VoxelWorldRenderData(void);

		bool													Initialize(MaterialPtr pMaterial);
		void													Release();




		void													Render_Depth(Sys_GraphicsPtr pSysGraphics);
		void													Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr());
		MaterialPtr												GetMaterial();
		math::Matrix44											GetWorldMatrix();
		bool													IsDeferred();



	private:
		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		MaterialPtr												m_pMaterial;
	};
}
